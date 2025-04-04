#include "render/render_system/Render_Scene.h"

#include "math/Matrix4x4.h"

#include "render/render_system/Render_Utilities.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System {

	using NameSpace_Core::NameSpace_Math::Matrix4x4;

	void Render_Scene::Set_Ambient_Light(const Color& Ambient_Light) {
		this->m_Ambient_Light = Ambient_Light;
	}

	void Render_Scene::Set_Directional_Light(const Directional_Light& Directional_Light) {
		this->m_Directional_Light = Directional_Light;
	}

	shared_ptr<Render_GUID_Allocator<Game_Object_Part_ID>> Render_Scene::Get_Instance_ID_Allocator(void) const {
		return this->m_Instance_ID_Allocator;
	}

	shared_ptr<Render_GUID_Allocator<Mesh_Source_Desc>> Render_Scene::Get_Mesh_Resource_ID_Allocator(void) const {
		return this->m_Mesh_Resource_ID_Allocator;
	}

	shared_ptr<Render_GUID_Allocator<Material_Source_Desc>> Render_Scene::Get_Material_Resource_ID_Allocator(void) const {
		return this->m_Material_Resource_ID_Allocator;
	}

	void Render_Scene::Updata_Visiable_Objects(shared_ptr<Render_Resource> Resource, shared_ptr<Render_Camera> Camera) {
		UpData_Visiable_Objects_Directional_Light(Resource, Camera);
		Updata_Visiable_Objects_Point_Light(Resource);
		Updata_Visiable_Objects_Main_Camera(Resource, Camera);
		Updata_Visiable_Objects_Axis(Resource, Camera);
	}

	void Render_Scene::Set_Visiable_Nodes(void) {
		Render_Pass::s_Visable_Node.Directional_Light_Visiable_Mesh_Nodes = &this->m_Directional_Light_Visible_Mesh_Nodes;

		Render_Pass::s_Visable_Node.Point_Lights_Visiable_Mesh_Nodes = &this->m_Point_Light_Visible_Mesh_Nodes;

		Render_Pass::s_Visable_Node.Main_Camera_Visiable_Mesh_Nodes = &this->m_Main_Camera_Visible_Mesh_Nodes;

		Render_Pass::s_Visable_Node.Axis_Node = &this->m_Axis_Node;
	}

	void Render_Scene::UpData_Visiable_Objects_Directional_Light(shared_ptr<Render_Resource> Resource, shared_ptr<Render_Camera> Camera) {

		Matrix4x4 Directional_Light_Proj_View{ NameSpace_Utilities::Calculate_Direction_Light_View_Matrix(*this, *Camera) };

	}
	void Render_Scene::Updata_Visiable_Objects_Point_Light(shared_ptr<Render_Resource> Resource) {
		//TODO :
	}
	void Render_Scene::Updata_Visiable_Objects_Main_Camera(shared_ptr<Render_Resource> Resource, shared_ptr<Render_Camera> Camera)
	{
	}

	void Render_Scene::Updata_Visiable_Objects_Axis(shared_ptr<Render_Resource> Resource, shared_ptr<Render_Camera> Camera)
	{
		//TODO :
	}

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System