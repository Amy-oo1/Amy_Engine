#pragma once

#include<limits>
#include<vector>
#include<cstdint>
#include<memory>

#include "Jolt/Jolt.h"
#include "Jolt/Core/JobSystem.h"
#include "Jolt/Core/TempAllocator.h"
#include "Jolt/Physics/PhysicsSystem.h"
#include "Jolt/Physics/Collision/BroadPhase/BroadPhase.h"
#include "Jolt/Renderer/DebugRenderer.h"

#include "math/Vector3.h"
#include "transform/Affine_Transform.h"
#include "bounding/Bounding_Box_AxisAligned.h"

#include "components/rigid_body/Basic_Shape.h"
#include "components/rigid_body/Rigid_Body.h"

#include "physics/Physics_Config.h"

namespace NameSpace_Function::Namespace_Physics {

	using std::vector;
	using std::shared_ptr;

	using JPH::PhysicsSystem;
	using JPH::JobSystem;
	using JPH::TempAllocator;
	using JPH::BroadPhaseLayerInterface;
	using JPH::DebugRenderer;

	using NameSpace_Core::NameSpace_Math::Vector3;
	using NameSpace_Core::NameSpace_Transform::Affine_Transform;

	using NameSpace_Resource::NameSpace_Components::Geometry_Box;
	using NameSpace_Resource::NameSpace_Components::Geometry_Sphere;
	using NameSpace_Resource::NameSpace_Components::Geometry_Cylinder;
	using NameSpace_Resource::NameSpace_Components::Rigid_Body_Shape;

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


	protected:
		Physics_Config m_Config{};

		Jolt_Physics m_Jolt_Physics{};

		vector<uint32_t> m_Pending_Remove_Bodies{};

	};

}// namespace NameSpace_Function::Namespace_Physics