#pragma once

#include<string>
#include<unordered_map>
#include<memory>
#include<utility>

#include "file/File_System.h"

#include "common/Object_Resource.h"
#include "common/Level_Resource.h"

#include "frame/object/GObject_ID_Allocator.h"
#include "frame/object/GObject.h"
#include "physics/Physics_Scene.h"
#include "character/Character.h"

namespace NameSpace_Function::NameSpace_Frame::NameSpace_Level {

	using NameSpace_Platform::NameSpace_File::path;

	using NameSpace_Resource::NameSpace_Common::Object_Instance;
	using NameSpace_Resource::NameSpace_Common::Level_Resource;

	using NameSpace_GObject::GObject_ID;
	using NameSpace_GObject::GObject_ID_Allocator;
	using NameSpace_GObject::GObject;
	using Namespace_Physics::Physics_Scene;
	using Namespace_Character::Character;

	using std::string;
	using std::unordered_map;
	using std::shared_ptr;
	using std::weak_ptr;

	class Level final :public std::enable_shared_from_this<Level> {
	private:
		Level(const Level&) = delete;
		Level(Level&&) = delete;

		Level& operator=(const Level&) = delete;
		Level& operator=(Level&&) = delete;

	public:
		Level(void) = default;

		//Level(const path& Level_Resource_URL);

		~Level(void) = default;

		void Load_Level(const path& Level_Resource_URL);

		GObject_ID Create_Object(const shared_ptr<Object_Instance>& Object_Instance_Res);

		weak_ptr<GObject> Get_Object(GObject_ID Object_ID) const;
		void Delete_Object(GObject_ID Object_ID);

		void Tick(float Delta_Time);

	private:
		path m_Level_Resource_URL{};
		shared_ptr<Level_Resource> m_Level_Resource{ nullptr };

		unordered_map<GObject_ID, shared_ptr<GObject>> m_Objects{};

		bool m_Is_Character_Active{ false };
		shared_ptr<Character> m_Character{};

		weak_ptr<Physics_Scene> m_Physics_Scene{};

	};

}// namespace NameSpace_Function::NameSpace_Frame::NameSpace_Level