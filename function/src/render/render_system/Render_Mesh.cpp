#include "render/render_system/Render_Mesh.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System {

	const vector<const RHI_Vertex_Input_Binding_Description*>* Mesh_Vertex::Get_Vertex_Input_Binding_Description(void) {
		static const vector<const RHI_Vertex_Input_Binding_Description*> Binding_Descriptions{
			&Mesh_Vertex::Position_Binding_Description,
			&Mesh_Vertex::Varying_Enable_Blending_Binding_Description,
			&Mesh_Vertex::Varying_Binding_Description
		};

		return &Binding_Descriptions;
	};

	const vector<const RHI_Vertex_Input_Attribute_Description*>* Mesh_Vertex::Get_Vertex_Input_Attribute_Description(void) {
		static const vector<const RHI_Vertex_Input_Attribute_Description*> Attribute_Descriptions{
			&Mesh_Vertex::Position_Attribute_Description,
			&Mesh_Vertex::Normal_Attribute_Description,
			&Mesh_Vertex::Tangent_Attribute_Description,
			&Mesh_Vertex::TexCoord_Attribute_Description
		};

		return &Attribute_Descriptions;
	};

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System