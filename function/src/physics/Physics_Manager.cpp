#include "physics/Physics_Manager.h"

#include "logger/System_Logger.h"

namespace NameSpace_Function::Namespace_Physics {

	using NameSpace_Core::NameSpace_Logger::System_Logger;

	Physics_Manager& Physics_Manager::Get_Instance(void) {
		static Physics_Manager Instance{};

		return Instance;
	}

	weak_ptr<Physics_Scene> Physics_Manager::Create_Scene(const Vector3& Gravity) {
		shared_ptr<Physics_Scene> Scene = std::make_shared<Physics_Scene>(Gravity);
		m_Scenes.push_back(Scene);

		return Scene;
	}

	void Physics_Manager::Destory_Scene(const weak_ptr<Physics_Scene>& Scene) {
		if (shared_ptr<Physics_Scene> Scene_Shared = Scene.lock()) {
			const auto Iter = std::find(m_Scenes.begin(), m_Scenes.end(), Scene_Shared);

			if (Iter != m_Scenes.end())
				m_Scenes.erase(Iter);
			else
				System_Logger::Get_Instance().Log(System_Logger::Level::err, "Physics Scene Not Found");
		}
	}

}// namespace NameSpace_Function::Namespace_Physics