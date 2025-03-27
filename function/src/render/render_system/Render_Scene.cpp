#include "render/render_system/Render_Scene.h"

#include "math/Matrix4x4.h"

#include "render/render_system/Render_Utilities.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System {

	using NameSpace_Core::NameSpace_Math::Matrix4x4;

	void Render_Scene::Updata_Visiable_Objects(shared_ptr<Render_Resource> Resource, shared_ptr<Render_Camera> Camera){
		UpData_Visiable_Objects_Directional_Light(Resource, Camera);
		Updata_Visiable_Objects_Point_Light(Resource);
		Updata_Visiable_Objects_Main_Camera(Resource, Camera);
		Updata_Visiable_Objects_Axis(Resource, Camera);
	}

	void Render_Scene::Set_Visiable_Nodes(void){
		Render_Pass::s_Visable_Node.Directional_Light_Visiable_Mesh_Nodes = &this->m_Directional_Light_Visible_Mesh_Nodes;

		Render_Pass::s_Visable_Node.Point_Lights_Visiable_Mesh_Nodes = &this->m_Point_Light_Visible_Mesh_Nodes;

		Render_Pass::s_Visable_Node.Main_Camera_Visiable_Mesh_Nodes = &this->m_Main_Camera_Visible_Mesh_Nodes;

		Render_Pass::s_Visable_Node.Axis_Node = &this->m_Axis_Node;
	}

	void Render_Scene::UpData_Visiable_Objects_Directional_Light(shared_ptr<Render_Resource> Resource, shared_ptr<Render_Camera> Camera) {

		Matrix4x4 Directional_Light_Proj_View{ NameSpace_Utilities::Calculate_Direction_Light_View_Matrix(*this, *Camera) };

	}
	void Render_Scene::Updata_Visiable_Objects_Point_Light(shared_ptr<Render_Resource> Resource){
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