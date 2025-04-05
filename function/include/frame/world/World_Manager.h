#pragma once

#include<unordered_map>
#include<memory>

#include "file/File_System.h"

#include "common/World_Resource.h"

#include "physics/Physics_Scene.h"
#include "frame/level/Level.h"

namespace NameSpace_Function::NameSpace_Frame::NameSpace_World {

	using std::unordered_map;
	using std::shared_ptr;
	using std::weak_ptr;

	using NameSpace_Platform::NameSpace_File::path;

	using NameSpace_Resource::NameSpace_Common::World_Resource;

	using Namespace_Physics::Physics_Scene;
	using NameSpace_Level::Level;

	class World_Manager final {
	private:
		World_Manager(const World_Manager&) = delete;
		World_Manager(World_Manager&&) = delete;

		World_Manager& operator=(const World_Manager&) = delete;
		World_Manager& operator=(World_Manager&&) = delete;

		World_Manager(void) = default;

	public:
		~World_Manager(void) = default;


	public:
		weak_ptr<Level> Get_Current_Active_Level(void)const;

		void Tick(float Delta_Time);

	public:
		static World_Manager& Get_Instance(void);

		void Load_World(const path& World_URL);
		void Load_Level(const path& Level_URL);


	private:
		path m_Current_World_URL{};

		shared_ptr<World_Resource> m_Current_World_Resource{ nullptr };
		unordered_map<path, shared_ptr<Level>> m_Levels{};
		weak_ptr<Level> m_Current_Level;
	};

}// namespace NameSpace_Function::NameSpace_Frame::NameSpace_GObject