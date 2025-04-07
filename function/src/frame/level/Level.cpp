#include "frame/level/Level.h"

#include "logger/System_Logger.h"

#include "meta/generated/reflection/Level_Resource.Generated_Reflection.h"

#include "manage/Resource_Manager.h"

#include "global/Global_Config.h"
#include "global/Global_Systemer.h"

namespace NameSpace_Function::NameSpace_Frame::NameSpace_Level {

	using NameSpace_Core::NameSpace_Logger::System_Logger;

	using NameSpace_Resource::NameSpace_Common::Reflection_Level_Resource_Operator;

	using NameSpace_Resource::NameSpace_Manage::Resource_Manager;

	using Namespace_Global::Global_Systemer;

	/*Level::Level(const path& Level_Resource_URL) {
		this->Load_Level(Level_Resource_URL);
	}*/

	void Level::Load_Level(const path& Level_Resource_URL) {
		this->m_Level_Resource_URL = Level_Resource_URL;
		this->m_Level_Resource = Resource_Manager::Load<Level_Resource>(Level_Resource_URL);

		//Global_Systemer::Get_Instance().Physics_Manager.Create_Scene(Reflection_Level_Resource_Operator::Get_Gravity_Attribute(this->m_Level_Resource));

		for (const auto& Object_Res : Reflection_Level_Resource_Operator::Get_Objects_Attribute(this->m_Level_Resource))
			this->Create_Object(Object_Res);
	}

	GObject_ID Level::Create_Object(const shared_ptr<Object_Instance>& Object_Instance_Res) {
		auto  Temp_ID{ GObject_ID_Allocator::Alloc() };

		this->m_Objects.emplace(
			Temp_ID,
			std::make_shared<GObject>(Object_Instance_Res)
		);

		return Temp_ID;
	}

	weak_ptr<GObject> Level::Get_Object(GObject_ID Object_ID) const {
		auto It = this->m_Objects.find(Object_ID);
		if (It != this->m_Objects.end())
			return It->second;
		else
			return weak_ptr<GObject>{};
	}

	void Level::Delete_Object(GObject_ID Object_ID) {
		auto It = this->m_Objects.find(Object_ID);
		if (It != this->m_Objects.end()) {
			auto Object{ It->second };
			if (Object &&
				this->m_Character &&
				(this->m_Character->Get_Object_ID() == Object_ID))
				this->m_Character->Set_Character_Object(nullptr);

			this->m_Objects.erase(It);
		}
		else
			System_Logger::Get_Instance().Log(System_Logger::Level::err, "Level::Delete_Object", "Object Not Found");
	}

	void Level::Tick(float Delta_Time) {
		for (auto& [_, Object] : this->m_Objects)
			if (Object)
				Object->Tick(Delta_Time);

		if (this->m_Is_Character_Active && false == Namespace_Global::Is_Editor_Mode)
			this->m_Character->Tick(Delta_Time);

		auto Physic_Scene{ this->m_Physics_Scene.lock() };
		if (Physic_Scene)
			Physic_Scene->Tick(Delta_Time);
		else
			System_Logger::Get_Instance().Log(System_Logger::Level::err, "Level::Tick : Physics Scene Not Found");
	}



}// namespace NameSpace_Function::NameSpace_Frame::NameSpace_Level