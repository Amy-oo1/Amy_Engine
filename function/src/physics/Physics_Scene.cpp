#include "physics/Physics_Scene.h"

#include "Jolt/Core/JobSystemThreadPool.h"
#include "Jolt/Core/TempAllocator.h"
#include "Jolt/Physics/PhysicsSettings.h"

#include "global/Global_Systemer.h"

#include "physics/Utilities_Physics.h"

namespace NameSpace_Function::Namespace_Physics {

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

}// namespace NameSpace_Function::Namespace_Physics