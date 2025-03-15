#pragma once

#include<limits>
#include<vector>
#include<unordered_map>
#include<cstdint>
#include<memory>

#include "Jolt/Jolt.h"
#include "Jolt/Core/JobSystem.h"
#include "Jolt/Physics/Collision/Shape/Shape.h"
#include "Jolt/Core/TempAllocator.h"
#include "Jolt/Physics/PhysicsSystem.h"
#include "Jolt/Physics/Collision/BroadPhase/BroadPhase.h"
#include "Jolt/Physics/Collision/Shape/StaticCompoundShape.h"
#include "Jolt/Renderer/DebugRenderer.h"

#include "math/Vector3.h"
#include "transform/Affine_Transform.h"
#include "bounding/Bounding_Box_AxisAligned.h"

#include "components/rigid_body/Basic_Shape.h"
#include "components/rigid_body/Rigid_Body.h"

#include "physics/Physics_Config.h"

namespace NameSpace_Function::Namespace_Physics {

	using std::vector;
	using std::unordered_map;
	using std::shared_ptr;
	using std::unique_ptr;

	using JPH::PhysicsSystem;
	using JPH::JobSystem;
	using JPH::TempAllocator;
	using JPH::BroadPhaseLayerInterface;
	using JPH::DebugRenderer;
	using JPH::Shape;
	using JPH::StaticCompoundShapeSettings;

	using NameSpace_Core::NameSpace_Math::Vector3;
	using NameSpace_Core::NameSpace_Transform::Affine_Transform;

	using NameSpace_Resource::NameSpace_Components::Geometry_Box;
	using NameSpace_Resource::NameSpace_Components::Geometry_Sphere;
	using NameSpace_Resource::NameSpace_Components::Geometry_Cylinder;
	using NameSpace_Resource::NameSpace_Components::Rigid_Body_Shape;
	using NameSpace_Resource::NameSpace_Components::Rigid_Body_Res;

	struct Physics_Hit_Info final {
		static constexpr uint32_t INVALID_ID{ std::numeric_limits<uint32_t>::max() };

		Vector3 Hit_Position{ Vector3::ZERO };
		Vector3 Hit_Normal{ Vector3::ZERO };
		float Hit_Distance{ 0.0f };
		uint32_t Hit_Body_ID{ INVALID_ID };
	};

	class Physics_Scene {
	protected:
		struct Jolt_Physics final {
			shared_ptr<PhysicsSystem> m_Physics_System{ nullptr };
			shared_ptr<JobSystem> m_Job_System{ nullptr };
			shared_ptr<TempAllocator> m_Temp_Allocator{ nullptr };
			shared_ptr<BroadPhaseLayerInterface> m_Broad_Phase_Layer_Interface{ nullptr };

			int m_Collision_Steps{ 1 };
			int m_Integration_Sub_Steps{ 1 };
		};

		struct JPH_Shape_Data {
			shared_ptr<Shape> Shape_Data;
			Affine_Transform Loac_Transform{ Affine_Transform::IDENTITY };
			Vector3 Global_Scale{ Vector3::ONE };
		};

	public:
		using My_Body = unique_ptr<JPH::Body, std::function<void(JPH::Body*)>>;

	public:
		Physics_Scene(void) = delete;

		Physics_Scene(const Physics_Scene&) = delete;
		Physics_Scene(Physics_Scene&&) = delete;

		const Physics_Scene& operator=(const Physics_Scene&) = delete;
		const Physics_Scene& operator=(Physics_Scene&&) = delete;


		Physics_Scene(const Vector3& Gravity);

		virtual ~Physics_Scene(void) = default;

	public:
		const Vector3& Get_Gravity(void)const;

		uint32_t Create_RigidBody(const Affine_Transform& Global_Transform, const shared_ptr< Rigid_Body_Res>& Body_Res);

		void Remove_RigidBody(uint32_t Body_ID);

		void Update_RigidBody_Global_Transform(uint32_t Body_ID, const Affine_Transform& Global_Transform);

		void Tick(float Delta_Time);

		const vector<Physics_Hit_Info>  Ray_Cast(const Vector3& Ray_Origin, const Vector3& Ray_Direction, float Ray_Length);

	private:
		static const vector<JPH_Shape_Data> Creata_JPH_Shapes(const Affine_Transform& Global_Tranform, const vector<shared_ptr<Rigid_Body_Shape>> My_Shapes);

		static const JPH::Ref<JPH::StaticCompoundShapeSettings> Create_Static_Static_Compound_Shape(const vector<JPH_Shape_Data>& Shapes);

	protected:
		Physics_Config m_Config{};

		Jolt_Physics m_Jolt_Physics{};

		unordered_map<uint32_t, My_Body> m_Bodies{};

		vector<uint32_t> m_Pending_Remove_Bodies{};

	};

}// namespace NameSpace_Function::Namespace_Physics