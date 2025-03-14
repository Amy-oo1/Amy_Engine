#include "physics/Physics_Scene.h"

#include "Jolt/Core/JobSystemThreadPool.h"

#include "global/Global_Systemer.h"

namespace NameSpace_Function::Namespace_Physics {

	using Namespace_Global::Global_Systemer;

	/*Physics_Scene::Physics_Scene(const Vector3& Gravity) :
		m_Config{ Physics_Config() },
		m_Jolt_Physics{
		std::make_shared<PhysicsSystem>(),
		std::make_shared<JobSystem>(JPH::JobSystemThreadPool(this->m_Config.m_Max_Job_Count,this->m_Config.m_Max_Barrier_Count,static_cast<int>(this->m_Config.m_Max_Conccurrent_Job_Count))),
		std::make_shared<TempAllocator>(16 * 1024 * 1024),
		std::make_shared<BroadPhaseLayerInterface>()} {
	}*/

}// namespace NameSpace_Function::Namespace_Physics