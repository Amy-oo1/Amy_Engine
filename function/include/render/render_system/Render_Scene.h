#pragma once

#include<cstdint>
#include<optional>
#include<vector>
#include<unordered_map>
#include<memory>

#include "file/File_System.h"

#include "color/Color.h"

#include "frame/object/GObject_ID_Allocator.h"
#include "render/render_system/Render_Commmon.h"
#include "render/render_system/Light.h"
#include "render/render_system/Render_GUID_Allocator.h"
#include "render/render_system/Render_Obejct.h"
#include "render/render_system/Render_Entity.h"
#include "render/render_system/Render_Resource.h"
#include "render/render_pass/Render_Pass.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System {

	using std::optional;
	using std::vector;
	using std::unordered_map;

	using std::shared_ptr;

	using NameSpace_Platform::NameSpace_File::path;

	using NameSpace_Core::NameSpace_Color::Color;

	using NameSpace_Pass::Render_Pass;

	class Render_Scene final {
	private:
		Render_Scene(const Render_Scene&) = delete;
		Render_Scene& operator=(const Render_Scene&) = delete;

	public:

		Render_Scene(void) = default;

		~Render_Scene(void) = default;



	public:
		void Set_Ambient_Light(const Color& Ambient_Light);
		void Set_Directional_Light(const Directional_Light& Directional_Light);


		shared_ptr<Render_GUID_Allocator<Game_Object_Part_ID>> Get_Instance_ID_Allocator(void)const;
		shared_ptr<Render_GUID_Allocator<Mesh_Source_Desc>> Get_Mesh_Resource_ID_Allocator(void)const;
		shared_ptr<Render_GUID_Allocator<Material_Source_Desc>> Get_Material_Resource_ID_Allocator(void)const;

	public:


		void Updata_Visiable_Objects(
			shared_ptr<Render_Resource> Resource,
			shared_ptr<Render_Camera> Camera);

		void Set_Visiable_Nodes(void);

		void Add_Entity(size_t Instance_ID,GObject_ID GO_ID);
		void Delete_Entity(GObject_ID ID);



	private:
		void UpData_Visiable_Objects_Directional_Light(
			shared_ptr<Render_Resource> Resource,
			shared_ptr<Render_Camera> Camera);


		void Updata_Visiable_Objects_Point_Light(
			shared_ptr<Render_Resource> Resource);


		void Updata_Visiable_Objects_Main_Camera(
			shared_ptr<Render_Resource> Resource,
			shared_ptr<Render_Camera> Camera);

		void Updata_Visiable_Objects_Axis(
			shared_ptr<Render_Resource> Resource,
			shared_ptr<Render_Camera> Camera);

		void Updata_Visiable_Objects_Particle(
			shared_ptr<Render_Resource> Resource,
			shared_ptr<Render_Camera> Camera
		);


	public://TODO : 
		//NOTE : Light
		Color m_Ambient_Light;
		Directional_Light m_Directional_Light;
		Point_Light_List m_Point_Light_List;

		//NOTE : Render Entities
		vector<Render_Entity> m_Render_Entities;

		//NOTE : Axis For Editor
		optional<Render_Entity> m_Render_Axis;

		//Visible Object (UPdatted Per Frame)
		vector<Vulkan_Render_Mesh_Node> m_Directional_Light_Visible_Mesh_Nodes;
		vector<Vulkan_Render_Mesh_Node> m_Point_Light_Visible_Mesh_Nodes;
		vector<Vulkan_Render_Mesh_Node> m_Main_Camera_Visible_Mesh_Nodes;

		Vulkan_Render_Axis_Node m_Axis_Node;


		shared_ptr<Render_GUID_Allocator<Game_Object_Part_ID>>m_Instance_ID_Allocator{ std::make_shared<Render_GUID_Allocator<Game_Object_Part_ID>>() };
		shared_ptr<Render_GUID_Allocator<Mesh_Source_Desc>> m_Mesh_Resource_ID_Allocator{ std::make_shared<Render_GUID_Allocator<Mesh_Source_Desc>>() };
		shared_ptr<Render_GUID_Allocator<Material_Source_Desc>> m_Material_Resource_ID_Allocator{ std::make_shared<Render_GUID_Allocator<Material_Source_Desc>>() };

		unordered_map<size_t, GObject_ID> m_Mesh_Object_ID_Map;

	};

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System