#include "frame/components/mesh/Mesh_Component.h"


#include "meta/generated/reflection/Mesh.Generated_Reflection.h"
#include "meta/generated/reflection/Render_Obejct.Generated_Reflection.h"

#include "manage/Resource_Manager.h"
#include "components/mesh/Mesh.h"
#include "components/material/Materia.h"
#include "meta/generated/reflection/Materia.Generated_Reflection.h"

namespace NameSpace_Function::NameSpace_Frame::NameSpace_Components {

	using NameSpace_Resource::NameSpace_Components::Reflection_Mesh_Resource_Operator;
	using NameSpace_Resource::NameSpace_Components::Reflection_Mesh_Sub_Operator;
	using NameSpace_Render::NameSpace_Render_System::Reflection_Game_Object_Part_Desc_Operator;
	using NameSpace_Render::NameSpace_Render_System::Game_Object_Part_Desc;
	using NameSpace_Render::NameSpace_Render_System::Reflection_Game_Object_Material_Desc_Operator;
	using NameSpace_Resource::NameSpace_Components::Material;
	using NameSpace_Resource::NameSpace_Components::Reflection_Material_Operator;
	using NameSpace_Function::NameSpace_Render::NameSpace_Render_System::Game_Object_Mesh_Desc;
	using NameSpace_Function::NameSpace_Render::NameSpace_Render_System::Reflection_Game_Object_Mesh_Desc_Operator;


	using NameSpace_Resource::NameSpace_Manage::Resource_Manager;
	using NameSpace_Resource::NameSpace_Components::Mesh_Sub;

	using NameSpace_Render::NameSpace_Render_System::Game_Object_Mesh_Desc;
	using NameSpace_Render::NameSpace_Render_System::Reflection_Game_Object_Mesh_Desc_Operator;
	using NameSpace_Render::NameSpace_Render_System::Reflection_Game_Object_Part_Desc_Operator;
	using NameSpace_Render::NameSpace_Render_System::Game_Object_Material_Desc;
	using NameSpace_Render::NameSpace_Render_System::Reflection_Game_Object_Material_Desc_Operator;

	void Mesh_Component::Post_Load_Resource(weak_ptr<GObject> Parent_Object) {
		this->m_Parent_GObject = Parent_Object;

		this->m_Raw_Meshes.reserve(Reflection_Mesh_Resource_Operator::Get_Sub_Meshes_CPPVector_Size(this->m_Mesh_Res));
		for (const auto& Sub_Mesh : Reflection_Mesh_Resource_Operator::Get_Sub_Meshes_Attribute(this->m_Mesh_Res)) {
			auto Temp_Desc{ std::make_shared<Game_Object_Part_Desc>() };

			{
				//NOTE : Mesh
				auto Mes_Desc{ std::make_shared<Game_Object_Mesh_Desc>() };
				{
					Reflection_Game_Object_Mesh_Desc_Operator::Set_Field_Mesh_URL_Attribute(Mes_Desc, Reflection_Mesh_Sub_Operator::Get_OBJ_URL_Attribute(Sub_Mesh));
				}
				Reflection_Game_Object_Part_Desc_Operator::Set_Field_Mesh_Desc_Attribute(Temp_Desc, Mes_Desc);

				//NOTE : Material
				shared_ptr<Game_Object_Material_Desc> Material_Desc{ nullptr };
				if (!Reflection_Mesh_Sub_Operator::Get_Material_URL_Attribute(Sub_Mesh).empty())
				{
					Material_Desc = std::make_shared<Game_Object_Material_Desc>();
					Reflection_Game_Object_Material_Desc_Operator::Set_Field_Is_With_Texture_Attribute(Material_Desc, true);

					auto Material_Res{ Resource_Manager::Load<Material>(Reflection_Mesh_Sub_Operator::Get_Material_URL_Attribute(Sub_Mesh)) };

					Reflection_Game_Object_Material_Desc_Operator::Set_Field_Base_Color_URL_Attribute(Material_Desc, Reflection_Material_Operator::Get_Base_Colour_Texture_URL_Attribute(Material_Res));
					Reflection_Game_Object_Material_Desc_Operator::Set_Field_Metallic_Roughness_URL_Attribute(Material_Desc, Reflection_Material_Operator::Get_Metallic_Roughness_Texture_URL_Attribute(Material_Res));
					Reflection_Game_Object_Material_Desc_Operator::Set_Field_Normal_URL_Attribute(Material_Desc, Reflection_Material_Operator::Get_Normal_Texture_URL_Attribute(Material_Res));
					Reflection_Game_Object_Material_Desc_Operator::Set_Field_Occlusion_URL_Attribute(Material_Desc, Reflection_Material_Operator::Get_Occlusion_Texture_URL_Attribute(Material_Res));
					Reflection_Game_Object_Material_Desc_Operator::Set_Field_Emissive_URL_Attribute(Material_Desc, Reflection_Material_Operator::Get_Emissive_Texture_URL_Attribute(Material_Res));

				}
				Reflection_Game_Object_Part_Desc_Operator::Set_Field_Material_Desc_Attribute(Temp_Desc, Material_Desc);

				//TODO :Tramsform
			}
		}
	}

	void Mesh_Component::Tick(float Delta_Time)
	{
	}


}// namespace NameSpace_Function::NameSpace_Frame::NameSpace_Components
