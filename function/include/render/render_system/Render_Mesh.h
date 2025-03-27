#pragma once

#include<array>
#include<vector>

#include "math/Vector2.h"
#include "math/Vector3.h"
#include "math/Vector4.h"

#include "render/rhi/empty_rhi/RHI_Type.h"
#include "render/rhi/empty_rhi/RHI_Struct.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System {

	using std::array;
	using std::vector;

	using NameSpace_RHI::RHI_VERTEX_INPUT_RATE;
	using NameSpace_RHI::RHI_FORMAT;

	using NameSpace_RHI::RHI_Vertex_Input_Binding_Description;
	using NameSpace_RHI::RHI_Vertex_Input_Attribute_Description;

	using NameSpace_Core::NameSpace_Math::Vector2;
	using NameSpace_Core::NameSpace_Math::Vector3;
	using NameSpace_Core::NameSpace_Math::Vector4;

	struct Mesh_Vertex final {

		struct Vulkan_Mesh_Vertex_Position final {
			Vector3 Position;
		};

		struct Vulkan_Mesh_Vertex_Varying_Enable_Blending final {
			Vector3 Normal;
			Vector3 Tangent;
		};

		struct Vulkan_Mesh_Vertex_Varying final {
			Vector2 TexCoord;
		};

		struct Vulkan_Mesh_Vertex_Joint_Binding final {
			array<int, 4> Indices;
			Vector4 Weights;
		};

		static constexpr RHI_Vertex_Input_Binding_Description Position_Binding_Description{
			0,
			sizeof(Vulkan_Mesh_Vertex_Position),
			RHI_VERTEX_INPUT_RATE::RHI_VERTEX_INPUT_RATE_VERTEX
		};

		static constexpr RHI_Vertex_Input_Binding_Description Varying_Enable_Blending_Binding_Description{
			1,
			sizeof(Vulkan_Mesh_Vertex_Varying_Enable_Blending),
			RHI_VERTEX_INPUT_RATE::RHI_VERTEX_INPUT_RATE_VERTEX
		};

		static constexpr RHI_Vertex_Input_Binding_Description Varying_Binding_Description{
			2,
			sizeof(Vulkan_Mesh_Vertex_Varying),
			RHI_VERTEX_INPUT_RATE::RHI_VERTEX_INPUT_RATE_VERTEX
		};

		static constexpr RHI_Vertex_Input_Attribute_Description Position_Attribute_Description{
			0,
			0,
			RHI_FORMAT::RHI_FORMAT_R32G32B32_SFLOAT,
			offsetof(Vulkan_Mesh_Vertex_Position, Position)
		};

		static constexpr RHI_Vertex_Input_Attribute_Description Normal_Attribute_Description{
			1,
			1,
			RHI_FORMAT::RHI_FORMAT_R32G32B32_SFLOAT,
			offsetof(Vulkan_Mesh_Vertex_Varying_Enable_Blending, Normal)
		};

		static constexpr RHI_Vertex_Input_Attribute_Description Tangent_Attribute_Description{
			2,
			1,
			RHI_FORMAT::RHI_FORMAT_R32G32_SFLOAT,
			 offsetof(Vulkan_Mesh_Vertex_Varying_Enable_Blending, Tangent)
		};

		static constexpr RHI_Vertex_Input_Attribute_Description TexCoord_Attribute_Description{
			3,
			2,
			RHI_FORMAT::RHI_FORMAT_R32G32_SFLOAT,
			offsetof(Vulkan_Mesh_Vertex_Varying, TexCoord)
		};

		const vector<const RHI_Vertex_Input_Binding_Description*>* Get_Vertex_Input_Binding_Description(void);//NOTE : Return All Of The Binding Description

		const vector<const RHI_Vertex_Input_Attribute_Description*>* Get_Vertex_Input_Attribute_Description(void);// NOTE : Return All Of The Attribute Description

	};

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System