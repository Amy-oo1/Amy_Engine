#pragma once

#include<array>

#include "math/Vector2.h"
#include "math/Vector3.h"
#include "math/Vector4.h"

#include "render/rhi/empty_rhi/RHI_Struct.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System {

	using std::array;

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
			Vector4 Weigths;
		};

		static  array< RHI_Vertex_Input_Binding_Description, 3>
			Get_Vertex_Input_Binding_Description(void);

		static array< RHI_Vertex_Input_Attribute_Description, 4>
			Get_Vertex_Input_Attribute_Description(void);

	};

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System