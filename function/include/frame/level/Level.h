#pragma once

#include<string>
#include<unordered_map>
#include<memory>

#include "file/File_System.h"

#include "frame/object/GObject_ID_Allocator.h"
#include "frame/object/GObject.h"
#include "physics/Physics_Scene.h"
#include "character/Character.h"

namespace NameSpace_Function::NameSpace_Frame::NameSpace_Level {

	using NameSpace_Platform::NameSpace_File::path;

	using NameSpace_GObject::GObject_ID;
	using NameSpace_GObject::GObject;
	using Namespace_Physics::Physics_Scene;
	using Namespace_Character::Character;

	using std::string;
	using std::unordered_map;
	using std::shared_ptr;
	using std::weak_ptr;

	class Level final {
	public:
		/*Level(const path& Level_Resource_URL, const shared_ptr<Physics_Scene>& Physics_Scene);
		~Level(void) = default;
		void Load(void);
		void Unload(void);
		void Update(void);
		void Add_Object(const shared_ptr<GObject>& Object);
		void Remove_Object(const GObject_ID& Object_ID);
		const shared_ptr<GObject> Get_Object(const GObject_ID& Object_ID) const;
		const shared_ptr<Character> Get_Character(void) const;
		const path& Get_Level_Resource_URL(void) const;
		const unordered_map<GObject_ID, shared_ptr<GObject>>& Get_Objects(void) const;
		const weak_ptr<Physics_Scene>& Get_Physics_Scene(void) const;
		void Set_Character(const shared_ptr<Character>& Character);
*/

	private:
		path m_Level_Resource_URL{};
		unordered_map<GObject_ID, shared_ptr<GObject>> m_Objects{};

		shared_ptr<Character> m_Character{};

		weak_ptr<Physics_Scene> m_Physics_Scene{};

	};

}// namespace NameSpace_Function::NameSpace_Frame::NameSpace_Level