#include "physics/Physics_Scene.h"

#include "Jolt/Core/Reference.h"
#include "Jolt/Core/JobSystemThreadPool.h"
#include "Jolt/Core/TempAllocator.h"
#include "Jolt/Physics/PhysicsSettings.h"
#include "Jolt/Physics/Body/BodyInterface.h"
#include "Jolt/Physics/Body/Body.h"
#include "Jolt/Physics/Body/BodyID.h"
#include "Jolt/Physics/Body/BodyCreationSettings.h"
#include "Jolt/Physics/Body/MotionType.h"
#include "Jolt/Physics/Body/BodyLock.h"
#include "Jolt/Physics/EActivation.h"
#include "Jolt/Physics/Collision/NarrowPhaseQuery.h"
#include "Jolt/Physics/Collision/RayCast.h"
#include "Jolt/Physics/Collision/CollisionCollectorImpl.h"
#include "Jolt/Physics/Collision/CastResult.h"

#include "meta/generated/reflection/Basic_Shape.Generated_Reflection.h"
#include "meta/generated/reflection/Rigid_Body.Generated_Reflection.h"

#include "global/Global_Systemer.h"

#include "physics/Utilities_Physics.h"

namespace NameSpace_Function::Namespace_Physics {

	using JPH::BodyInterface;
	using JPH::BodyCreationSettings;

	using NameSpace_Resource::NameSpace_Components::Reflection_Rigid_Body_Shape_Operator;
	using NameSpace_Resource::NameSpace_Components::Reflection_Rigid_Body_Res_Operator;

	using Namespace_Global::Global_Systemer;

	using namespace NameSpace_Utilites;

	Physics_Scene::Physics_Scene(const Vector3& Gravity)
		:m_Config{ Physics_Config() } {

		this->m_Jolt_Physics.m_Physics_System = std::make_shared<PhysicsSystem>();

		this->m_Jolt_Physics.m_Job_System = std::make_shared<JPH::JobSystemThreadPool>(
			this->m_Config.m_Max_Job_Count,
			this->m_Config.m_Max_Barrier_Count,
			static_cast<int>(this->m_Config.m_Max_Conccurrent_Job_Count)
		);

		//NOTE : 16MB Buffer
		this->m_Jolt_Physics.m_Temp_Allocator = std::make_shared<JPH::TempAllocatorImpl>(16 * 1024 * 1024);

		this->m_Jolt_Physics.m_Broad_Phase_Layer_Interface = std::make_shared<BP_Layer_Interface_Impl>();

		this->m_Jolt_Physics.m_Physics_System->Init(
			this->m_Config.m_Max_Body_Count,
			this->m_Config.m_Body_Mutex_Count,
			this->m_Config.m_Max_body_Pair,
			this->m_Config.m_Max_Contact_COnstraints,
			*this->m_Jolt_Physics.m_Broad_Phase_Layer_Interface,
			My_ObjectVsBroadPhaseLayerFilter{},
			My_ObjectLayerPairFilter{}
		);

		//NOTE : Use Default Setting
		this->m_Jolt_Physics.m_Physics_System->SetPhysicsSettings(JPH::PhysicsSettings());

		this->m_Jolt_Physics.m_Physics_System->SetGravity(Convert_Vec3(Gravity));

		this->m_Config.m_Gravity = Gravity;
	}

	const Vector3& Physics_Scene::Get_Gravity(void) const {
		return this->m_Config.m_Gravity;
	}

	uint32_t Physics_Scene::Create_RigidBody(const Affine_Transform& Global_Transform, const shared_ptr<Rigid_Body_Res>& Body_Res) {
		const vector<Physics_Scene::JPH_Shape_Data> Shapes{ Creata_JPH_Shapes(
			Global_Transform,
			Reflection_Rigid_Body_Res_Operator::Get_Shapes_Attribute(Body_Res))
		};

		if (Shapes.empty())
			return JPH::BodyID::cInvalidBodyID;

		JPH::Ref<StaticCompoundShapeSettings> Static_Compound_Shape_Settings{ Create_Static_Static_Compound_Shape(Shapes) };

		BodyCreationSettings Creation_Settings{
			Static_Compound_Shape_Settings,
			Convert_Vec3(Global_Transform.Get_Translation()),
			Convert_Quat(Global_Transform.Get_Rotation()),
			JPH::EMotionType::Static,
			Layers::NON_MOVING
		};

		BodyInterface& Body_Interface{ this->m_Jolt_Physics.m_Physics_System->GetBodyInterface() };

		My_Body JPH_Body{
			Body_Interface.CreateBodyWithoutID(Creation_Settings),
			[&Body_Interface](JPH::Body* InBody)->void {if (nullptr != InBody)Body_Interface.DestroyBody(InBody->GetID()); }
		};

		if (nullptr == JPH_Body) {
			System_Logger::Get_Instance().Log(System_Logger::Level::err, "Body Is Not Initialized");

			return JPH::BodyID::cInvalidBodyID;
		}

		const auto& Body_ID{ JPH_Body->GetID() };
		Body_Interface.AddBody(Body_ID, JPH::EActivation::Activate
		);

		this->m_Bodies.emplace(Body_ID.GetIndexAndSequenceNumber(), std::move(JPH_Body));

		return Body_ID.GetIndexAndSequenceNumber();
	}

	void Physics_Scene::Remove_RigidBody(uint32_t Body_ID) {
		this->m_Pending_Remove_Bodies.emplace_back(Body_ID);
	}

	void Physics_Scene::Update_RigidBody_Global_Transform(uint32_t Body_ID, const Affine_Transform& Global_Transform) {
		this->m_Jolt_Physics.m_Physics_System->GetBodyInterface().SetPositionAndRotation(
			JPH::BodyID{ Body_ID },
			Convert_Vec3(Global_Transform.Get_Translation()),
			Convert_Quat(Global_Transform.Get_Rotation()),
			JPH::EActivation::Activate
		);
	}

	void Physics_Scene::Tick(float Delta_Time) {
		const float Time_Step = 1.f / this->m_Config.m_Updata_Frequency;

		this->m_Jolt_Physics.m_Physics_System->Update(
			Time_Step,
			this->m_Jolt_Physics.m_Collision_Steps,
			//TODO : Sub_Teps ?
			//this->m_Jolt_Physics.m_Integration_Sub_Steps,
			this->m_Jolt_Physics.m_Temp_Allocator.get(),
			this->m_Jolt_Physics.m_Job_System.get()
		);

		for (const uint32_t Temp_Body_ID : this->m_Pending_Remove_Bodies) {
			this->m_Jolt_Physics.m_Physics_System->GetBodyInterface().RemoveBody(JPH::BodyID{ Temp_Body_ID }
			);

			this->m_Bodies.erase(Temp_Body_ID);
		}
		this->m_Pending_Remove_Bodies.clear();
	}

	const vector<Physics_Hit_Info> Physics_Scene::Ray_Cast(const Vector3& Ray_Origin, const Vector3& Ray_Direction, float Ray_Length) {
		const JPH::RRayCast In_Ray{
			Convert_Vec3(Ray_Origin),
			Convert_Vec3(Ray_Direction.Normalize() * Ray_Length)
		};

		const JPH::NarrowPhaseQuery& Scene_Query{ this->m_Jolt_Physics.m_Physics_System->GetNarrowPhaseQuery() };

		//TODO : Defualt RayCast Settings
		const JPH::RayCastSettings Ray_Cast_Settings{};
		JPH::AllHitCollisionCollector<JPH::CastRayCollector> Collector;
		Scene_Query.CastRay(In_Ray, Ray_Cast_Settings, Collector);

		if (!Collector.HadHit())
			return {};

		Collector.Sort();

		vector<JPH::RayCastResult> RayCast_Resourct{ Collector.mHits.begin(),Collector.mHits.end() };

		vector<Physics_Hit_Info> Hit_Infos{};
		Hit_Infos.reserve(RayCast_Resourct.size());

		for (const auto& Temp_Hit_Resourt : RayCast_Resourct) {
			const Vec3 Hit_Point{ In_Ray.GetPointOnRay(Temp_Hit_Resourt.mFraction) };

			const JPH::BodyLockRead Body_Lock{
				this->m_Jolt_Physics.m_Physics_System->GetBodyLockInterface(),Temp_Hit_Resourt.mBodyID
			};

			const JPH::Body& HIt_body{ Body_Lock.GetBody() };

			const Vec3 Hit_Nornal{ HIt_body.GetWorldSpaceSurfaceNormal(Temp_Hit_Resourt.mSubShapeID2,Hit_Point) };

			Hit_Infos.emplace_back(Physics_Hit_Info{
				Convert_Vec3(Hit_Point),
				Convert_Vec3(Hit_Nornal),
				(Ray_Length * Temp_Hit_Resourt.mFraction),
				Temp_Hit_Resourt.mBodyID.GetIndexAndSequenceNumber()
				}
			);
		}

		return Hit_Infos;
	}

	const vector<Physics_Scene::JPH_Shape_Data> Physics_Scene::Creata_JPH_Shapes(const Affine_Transform& Global_Tranform, const vector<shared_ptr<Rigid_Body_Shape>> My_Shapes) {
		vector<JPH_Shape_Data> Data{};
		Data.reserve(My_Shapes.size());

		for (const shared_ptr<Rigid_Body_Shape>& Temp_Shape : My_Shapes) {
			JPH_Shape_Data Res{};

			const Affine_Transform Global_Transform{ Global_Tranform * Reflection_Rigid_Body_Shape_Operator::Get_Local_Transform_Attribute(Temp_Shape) };
			const Vector3 Global_Scale{ Global_Transform.Get_Scale() };

			shared_ptr<Shape> JPH_Shape{ Convert_Shape(Temp_Shape, Global_Scale) };

			if (nullptr == JPH_Shape) {
				System_Logger::Get_Instance().Log(System_Logger::Level::err, "Shape Is Not Initialized");
				continue;
			}

			Data.emplace_back(JPH_Shape_Data{
				JPH_Shape,
				Reflection_Rigid_Body_Shape_Operator::Get_Local_Transform_Attribute(Temp_Shape),
				Global_Scale
				}
			);
		}

		if (Data.empty())
			System_Logger::Get_Instance().Log(System_Logger::Level::err, "Shape Is Not Initialized");
		return Data;
	}

	const JPH::Ref<StaticCompoundShapeSettings> Physics_Scene::Create_Static_Static_Compound_Shape(const vector<JPH_Shape_Data>& Shapes) {
		JPH::Ref<StaticCompoundShapeSettings> Static_Compund_shape_setting = new StaticCompoundShapeSettings{};

		for (const auto& [Temp_Shape, Loacl_Transform, Global_Sccale] : Shapes)
			Static_Compund_shape_setting->AddShape(
				Convert_Vec3(Loacl_Transform.Get_Translation() * Global_Sccale),
				Convert_Quat(Loacl_Transform.Get_Rotation()),
				Temp_Shape.get()
			);

		return Static_Compund_shape_setting;
	}

}// namespace NameSpace_Function::Namespace_Physics