#include "render/render_system/Render_Scene.h"

#include<cassert>

#include "math/Matrix4x4.h"
#include "bounding/Bounding_Sphere.h"

#include "render/render_system/Render_Utilities.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System {

	using NameSpace_Core::NameSpace_Math::Matrix4x4;
	using NameSpace_Core::NameSpace_Bounding::Bounding_Sphere;

	using NameSpace_Pass::Render_Pass;

	using namespace NameSpace_Utilities;

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

		Resource->m_Mesh_Per_Frame_Storage_Buffer_Object.Directional_Light_View_Proj_Matrix = Directional_Light_Proj_View;
		Resource->m_Mesh_Directional_Light_Shadow_Per_Frame_Storage_Buffer_Object.Light_Proj_View = Directional_Light_Proj_View;

		this->m_Directional_Light_Visible_Mesh_Nodes.clear();

		ClusterFrustum frustum =
			CreateClusterFrustumFromMatrix(Directional_Light_Proj_View, -1.0, 1.0, -1.0, 1.0, 0.0, 1.0);

		for (const auto& entity : this->m_Render_Entities)
		{
			AxisAligned_Bounding_Box mesh_asset_bounding_box{ entity.Bounding_Box };

			if (TiledFrustumIntersectBox(frustum, BoundingBoxTransform(mesh_asset_bounding_box, entity.Model_Matrix)))
			{
				this->m_Directional_Light_Visible_Mesh_Nodes.emplace_back();
				Vulkan_Render_Mesh_Node& temp_node = this->m_Directional_Light_Visible_Mesh_Nodes.back();

				temp_node.Model_Matrix = &entity.Model_Matrix;

				assert(entity.Joint_Matrices.size() <= g_Mesh_Vertex_Blending_Max_Joint_Count);
				if (!entity.Joint_Matrices.empty())
				{
					temp_node.Joint_Count = static_cast<uint32_t>(entity.Joint_Matrices.size());
					temp_node.Joint_Matrices = entity.Joint_Matrices.data();
				}
				temp_node.Node_ID = entity.Instance_ID;

				const Vulkan_Mesh& mesh_asset = Resource->Get_Entity_Mesh(entity);
				temp_node.Ref_Mesh = const_cast<Vulkan_Mesh*>(&mesh_asset);
				temp_node.Enable_Vertex_Blending = entity.Enable_Vertex_Blending;

				const Vulkan_PBR_Material& material_asset = Resource->Get_Entity_Material(entity);
				temp_node.Ref_Material = const_cast<Vulkan_PBR_Material*>(&material_asset);
			}
		}

	}

	void Render_Scene::Updata_Visiable_Objects_Point_Light(shared_ptr<Render_Resource> Resource) {
		this->m_Point_Light_Visible_Mesh_Nodes.clear();

		std::vector<Bounding_Sphere> point_lights_bounding_spheres;
		uint32_t                    point_light_num = static_cast<uint32_t>(this->m_Point_Light_List.m_Light.size());
		point_lights_bounding_spheres.reserve(point_light_num);
		for (size_t i = 0; i < point_light_num; i++)
			point_lights_bounding_spheres.emplace_back(this->m_Point_Light_List.m_Light[i].Position, this->m_Point_Light_List.m_Light[i].Calculate_Radius());

		for (const auto& entity : this->m_Render_Entities)
		{
			AxisAligned_Bounding_Box mesh_asset_bounding_box{ entity.Bounding_Box };

			bool intersect_with_point_lights = true;
			for (size_t i = 0; i < point_light_num; i++)
			{
				if (!BoxIntersectsWithSphere(BoundingBoxTransform(mesh_asset_bounding_box, entity.Model_Matrix),
					point_lights_bounding_spheres[i]))
				{
					intersect_with_point_lights = false;
					break;
				}
			}

			if (intersect_with_point_lights)
			{
				this->m_Point_Light_Visible_Mesh_Nodes.emplace_back();
				Vulkan_Render_Mesh_Node& temp_node = this->m_Point_Light_Visible_Mesh_Nodes.back();

				temp_node.Model_Matrix = &entity.Model_Matrix;

				assert(entity.Joint_Matrices.size() <= g_Mesh_Vertex_Blending_Max_Joint_Count);
				if (!entity.Joint_Matrices.empty())
				{
					temp_node.Joint_Count = static_cast<uint32_t>(entity.Joint_Matrices.size());
					temp_node.Joint_Matrices = entity.Joint_Matrices.data();
				}
				temp_node.Node_ID = entity.Instance_ID;


				const Vulkan_Mesh& mesh_asset = Resource->Get_Entity_Mesh(entity);
				temp_node.Ref_Mesh = const_cast<Vulkan_Mesh*>(&mesh_asset);
				temp_node.Enable_Vertex_Blending = entity.Enable_Vertex_Blending;

				const Vulkan_PBR_Material& material_asset = Resource->Get_Entity_Material(entity);
				temp_node.Ref_Material = const_cast<Vulkan_PBR_Material*>(&material_asset);
			}
		}

	}

	void Render_Scene::Updata_Visiable_Objects_Main_Camera(shared_ptr<Render_Resource> Resource, shared_ptr<Render_Camera> Camera) {
		this->m_Main_Camera_Visible_Mesh_Nodes.clear();

		Matrix4x4 View_Matrix{ Camera->Get_View_Matrix() };
		Matrix4x4 Proj_Matrix{ Camera->Get_Projection_Matrix() };
		Matrix4x4 View_Proj_Matrix{ Proj_Matrix * View_Matrix };

		ClusterFrustum frustum =
			CreateClusterFrustumFromMatrix(Proj_Matrix, -1.0, 1.0, -1.0, 1.0, 0.0, 1.0);

		
		for (const auto& entity : this->m_Render_Entities)
		{
			AxisAligned_Bounding_Box mesh_asset_bounding_box{ entity.Bounding_Box };
			
			if (TiledFrustumIntersectBox(frustum, BoundingBoxTransform(mesh_asset_bounding_box, entity.Model_Matrix)))
			{
				this->m_Main_Camera_Visible_Mesh_Nodes.emplace_back();
				Vulkan_Render_Mesh_Node& temp_node = this->m_Main_Camera_Visible_Mesh_Nodes.back();
				temp_node.Model_Matrix = &entity.Model_Matrix;
				
				assert(entity.Joint_Matrices.size() <= g_Mesh_Vertex_Blending_Max_Joint_Count);
				if (!entity.Joint_Matrices.empty())
				{
					temp_node.Joint_Count = static_cast<uint32_t>(entity.Joint_Matrices.size());
					temp_node.Joint_Matrices = entity.Joint_Matrices.data();
				}

				temp_node.Node_ID = entity.Instance_ID;
				const Vulkan_Mesh& mesh_asset = Resource->Get_Entity_Mesh(entity);
				
				temp_node.Ref_Mesh = const_cast<Vulkan_Mesh*>(&mesh_asset);
				temp_node.Enable_Vertex_Blending = entity.Enable_Vertex_Blending;
				
				const Vulkan_PBR_Material& material_asset = Resource->Get_Entity_Material(entity);
				temp_node.Ref_Material = const_cast<Vulkan_PBR_Material*>(&material_asset);
			}
		}
	}

	void Render_Scene::Updata_Visiable_Objects_Axis(shared_ptr<Render_Resource> Resource, shared_ptr<Render_Camera> Camera)
	{
		if (this->m_Render_Axis.has_value())
		{
			Render_Entity& axis = *this->m_Render_Axis;

			this->m_Axis_Node.Model_Matrix = axis.Model_Matrix;
			this->m_Axis_Node.Node_ID = axis.Instance_ID;

			const Vulkan_Mesh& mesh_asset = Resource->Get_Entity_Mesh(axis);
			this->m_Axis_Node.Ref_Mesh = const_cast<Vulkan_Mesh*>(&mesh_asset);
			this->m_Axis_Node.Enbale_Vertex_Blending = axis.Enable_Vertex_Blending;
		}
	}

	void Render_Scene::Updata_Visiable_Objects_Particle(shared_ptr<Render_Resource> Resource, shared_ptr<Render_Camera> Camera) {
		//TODO : 
	}

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System