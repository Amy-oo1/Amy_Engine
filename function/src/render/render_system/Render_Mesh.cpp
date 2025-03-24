#include "render/render_system/Render_Mesh.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System {

	using NameSpace_RHI::RHI_VERTEX_INPUT_RATE;
	using NameSpace_RHI::RHI_FORMAT;

	array<RHI_Vertex_Input_Binding_Description, 3> Mesh_Vertex::Get_Vertex_Input_Binding_Description(void) {
		array< RHI_Vertex_Input_Binding_Description, 3> Binding_Description{};
		{
			Binding_Description[0].Binding = 0;
			Binding_Description[0].Stride = sizeof(Vulkan_Mesh_Vertex_Position);
			Binding_Description[0].Input_Rate = RHI_VERTEX_INPUT_RATE::RHI_VERTEX_INPUT_RATE_VERTEX;
		}

		{
			Binding_Description[1].Binding = 1;
			Binding_Description[1].Stride = sizeof(Vulkan_Mesh_Vertex_Varying_Enable_Blending);
			Binding_Description[1].Input_Rate = RHI_VERTEX_INPUT_RATE::RHI_VERTEX_INPUT_RATE_VERTEX;
		}

		{
			Binding_Description[2].Binding = 2;
			Binding_Description[2].Stride = sizeof(Vulkan_Mesh_Vertex_Varying);
			Binding_Description[2].Input_Rate = RHI_VERTEX_INPUT_RATE::RHI_VERTEX_INPUT_RATE_VERTEX;
		}

		return Binding_Description;

	};

	array<RHI_Vertex_Input_Attribute_Description, 4> Mesh_Vertex::Get_Vertex_Input_Attribute_Description(void)
	{
		array< RHI_Vertex_Input_Attribute_Description, 4> Attribute_Description{};
		{
			Attribute_Description[0].Binding = 0;
			Attribute_Description[0].Location = 0;
			Attribute_Description[0].Format = RHI_FORMAT::RHI_FORMAT_R32G32B32_SFLOAT;
			Attribute_Description[0].Offset = offsetof(Vulkan_Mesh_Vertex_Position, Position);
		}

		{
			Attribute_Description[1].Binding = 1;
			Attribute_Description[1].Location = 1;
			Attribute_Description[1].Format = RHI_FORMAT::RHI_FORMAT_R32G32B32_SFLOAT;
			Attribute_Description[1].Offset = offsetof(Vulkan_Mesh_Vertex_Varying_Enable_Blending, Normal);
		}

		{
			Attribute_Description[2].Binding = 1;
			Attribute_Description[2].Location = 2;
			Attribute_Description[2].Format = RHI_FORMAT::RHI_FORMAT_R32G32_SFLOAT;
			Attribute_Description[2].Offset = offsetof(Vulkan_Mesh_Vertex_Varying_Enable_Blending, Tangent);
		}

		{
			Attribute_Description[3].Binding = 2;
			Attribute_Description[3].Location = 3;
			Attribute_Description[3].Format = RHI_FORMAT::RHI_FORMAT_R32G32B32_SFLOAT;
			Attribute_Description[3].Offset = offsetof(Vulkan_Mesh_Vertex_Varying, TexCoord);
		}

		return Attribute_Description;
	};

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System