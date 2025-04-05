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
		this->UpData_Visiable_Objects_Directional_Light(Resource, Camera);
		this->Updata_Visiable_Objects_Point_Light(Resource);
		this->Updata_Visiable_Objects_Main_Camera(Resource, Camera);
		this->Updata_Visiable_Objects_Axis(Resource, Camera);
		this->Updata_Visiable_Objects_Particle(Resource, Camera);
	}

	void Render_Scene::Set_Visiable_Nodes(void) {
		Render_Pass::s_Visable_Node.Directional_Light_Visiable_Mesh_Nodes = &this->m_Directional_Light_Visible_Mesh_Nodes;

		Render_Pass::s_Visable_Node.Point_Lights_Visiable_Mesh_Nodes = &this->m_Point_Light_Visible_Mesh_Nodes;

		Render_Pass::s_Visable_Node.Main_Camera_Visiable_Mesh_Nodes = &this->m_Main_Camera_Visible_Mesh_Nodes;

		Render_Pass::s_Visable_Node.Axis_Node = &this->m_Axis_Node;
	}

	void Render_Scene::Add_Entity(size_t Instance_ID, GObject_ID GO_ID) {
		this->m_Mesh_Object_ID_Map[Instance_ID] = GO_ID;
	}

	void Render_Scene::Delete_Entity(GObject_ID ID) {
		for (auto& [Instance_Id, GO_ID] : this->m_Mesh_Object_ID_Map)
			if (GO_ID == ID) {
				this->m_Mesh_Object_ID_Map.erase(Instance_Id);
				break;
			}

		Game_Object_Part_ID Part_ID{ ID,0 };//NOTE : Part_ID = 0
		size_t Find_GUID{};

		auto Target_GUID{ this->m_Instance_ID_Allocator->Get_GUID(Game_Object_Part_ID{ ID,0 }) };
		if (INVALID_GUID != Target_GUID)
			for (auto It = this->m_Render_Entities.begin(); It != this->m_Render_Entities.end(); ++It)
				if (It->Instance_ID == Target_GUID) {
					this->m_Render_Entities.erase(It);

					break;
				}
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

	void Render_Scene::Updata_Visiable_Objects_Particle(shared_ptr<Render_Resource> Resource, shared_ptr<Render_Camera> Camera) {
		//TODO : 
	}

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System