#include "physics/Physics_Scene.h"

#include "Jolt/Core/Reference.h"
#include "Jolt/Core/JobSystemThreadPool.h"
#include "Jolt/Core/TempAllocator.h"
#include "Jolt/Physics/PhysicsSettings.h"
#include "Jolt/Physics/Body/BodyInterface.h"

#include "meta/generated/reflection/Basic_Shape.Generated_Reflection.h"
#include "meta/generated/reflection/Rigid_Body.Generated_Reflection.h"

#include "global/Global_Systemer.h"

#include "physics/Utilities_Physics.h"

namespace NameSpace_Function::Namespace_Physics {

	using JPH::BodyInterface;

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

		const BodyInterface& Body_Interface{ this->m_Jolt_Physics.m_Physics_System->GetBodyInterface() };


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

	JPH::Ref<JPH::StaticCompoundShapeSettings> Physics_Scene::Create_Static_Static_Compound_Shape(const vector<JPH_Shape_Data>& Shapes){
		JPH::Ref<StaticCompoundShapeSettings> Static_Compund_shape_setting = new StaticCompoundShapeSettings{};

		for (const auto&[Temp_Shape,Loacl_Transform,Global_Sccale] : Shapes) {
			Static_Compund_shape_setting->AddShape(
				Convert_Vec3(Loacl_Transform.Get_Translation()*Global_Sccale),
				Convert_Quat(Loacl_Transform.Get_Rotation()),

			)
		}
	}



}// namespace NameSpace_Function::Namespace_Physics