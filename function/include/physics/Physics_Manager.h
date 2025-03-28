#pragma once

#include<vector>
#include<memory>

#include "math/Vector3.h"

#include "physics/Physics_Scene.h"

namespace NameSpace_Function::Namespace_Physics {

	using std::vector;
	using std::shared_ptr;
	using std::weak_ptr;

	using NameSpace_Core::NameSpace_Math::Vector3;

	class Physics_Manager final {
	private:
		Physics_Manager(const Physics_Manager&) = delete;
		Physics_Manager(Physics_Manager&&) = delete;

		Physics_Manager& operator=(const Physics_Manager&) = delete;
		Physics_Manager& operator=(Physics_Manager&&) = delete;

		Physics_Manager(void) = default;

	public:
		~Physics_Manager(void) = default;

	public:
		static Physics_Manager& Get_Instance(void);
		
		weak_ptr<Physics_Scene> Create_Scene(const Vector3& Gravity);
		void Destory_Scene(const weak_ptr<Physics_Scene>& Scene);

	private:
		vector<shared_ptr<Physics_Scene>> m_Scenes{};

	};

}// namespace NameSpace_Function::Namespace_Physics