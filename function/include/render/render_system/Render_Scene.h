#pragma once

#include<optional>
#include<vector>
#include<memory>

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

	using std::shared_ptr;

	using NameSpace_Pass::Render_Pass;

	class Render_Scene final {
	public:
		void Updata_Visiable_Objects(
			shared_ptr<Render_Resource> Resource,
			shared_ptr<Render_Camera> Camera);

		void Set_Visiable_Nodes(void);



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




	public://TODO : 
		//NOTE : Light
		Ambient_Light m_Ambient_Light;
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



	};

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System
