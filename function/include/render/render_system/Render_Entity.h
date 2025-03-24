#pragma once

#include<cstdint>
#include<vector>

#include "math/Vector4.h"
#include "math/Matrix4x4.h"
#include "bounding/Bounding_Box_AxisAligned.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System {

	using std::vector;

	using NameSpace_Core::NameSpace_Math::Vector4;
	using NameSpace_Core::NameSpace_Math::Matrix4x4;
	using NameSpace_Core::NameSpace_Bounding::AxisAligned_Bounding_Box;

	struct Render_Entity final {
		uint32_t Instance_ID{ 0 };
		Matrix4x4 Model_Matrix{ Matrix4x4::IDENTITY };

		//NOTE : Mesh
		size_t Mesh_Resource_ID{ 0 };
		bool Enable_Vertex_Blending{ false };
		vector<Matrix4x4> Joint_Matrices{};
		AxisAligned_Bounding_Box Bounding_Box{ AxisAligned_Bounding_Box::EMPTY };

		//NOTE : Material
		size_t Material_Resource_ID{ 0 };
		bool Is_Blend{ false };
		bool Is_Double_Sided{ false };

		Vector4 Base_Color_Factor{ Vector4::ONE };
		float Metallic_Factor{ 1.f };
		float Roughness_Factor{ 1.f };
		Vector4 Emissive_Factor{ Vector4::ONE };

		float Normal_Scale{ 1.f };
		float Occlusion_Strength{ 1.f };
	};

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System