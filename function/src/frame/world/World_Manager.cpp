#include "frame/world/World_Manager.h"

#include "meta/generated/reflection/World_Resource.Generated_Reflection.h"

#include "logger/System_Logger.h"

#include "common/World_Resource.h"
#include "config/Resource_Configer.h"
#include "manage/Resource_Manager.h"

namespace NameSpace_Function::NameSpace_Frame::NameSpace_World {

	using NameSpace_Core::NameSpace_Logger::System_Logger;

	using NameSpace_Resource::NameSpace_Common::World_Resource;
	using NameSpace_Resource::NameSpace_Common::Reflection_World_Resource_Operator;
	using NameSpace_Resource::NameSpace_Config::Resource_Configer;
	using NameSpace_Resource::NameSpace_Manage::Resource_Manager;

	weak_ptr<Level> World_Manager::Get_Current_Active_Level(void) const {
		return this->m_Current_Level;
	}

	void World_Manager::Tick(float Delta_Time) {
		if (nullptr == this->m_Current_World_Resource)
			this->Load_World(Resource_Configer::Get_Instance().Get_Default_World_Resource_URL());

		auto Acitve_Level{ this->m_Current_Level.lock() };
		if (nullptr != Acitve_Level)
			Acitve_Level->Tick(Delta_Time);
		else
			System_Logger::Get_Instance().Log(System_Logger::Level::err, "World_Manager::Tick : Current Level is nullptr");
	}

	World_Manager& World_Manager::Get_Instance(void) {
		static World_Manager Instance{};

		return Instance;
	}

	void World_Manager::Load_World(const path& World_URL) {
		System_Logger::Get_Instance().Log(System_Logger::Level::info, "World_Manager::Load_World :{}", World_URL.generic_string());

		this->m_Current_World_Resource = Resource_Manager::Load<World_Resource>(World_URL);

		this->Load_Level(
			Reflection_World_Resource_Operator::Get_Default_Level_URL_Attribute(this->m_Current_World_Resource)
		);
	}

	void World_Manager::Load_Level(const path& Level_URL) {
		auto  Level_Instance{ std::make_shared<Level>(Level_URL) };
		this->m_Levels.emplace(Level_URL, Level_Instance);

		this->m_Current_Level = Level_Instance;
	}

}// namespace NameSpace_Function::NameSpace_Frame::NameSpace_World