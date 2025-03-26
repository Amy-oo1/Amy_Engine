#pragma once

#include<cstdint>

#include "vma/vk_mem_alloc.h"
#include "vulkan/vulkan.h"


#include "math/Vector3.h"
#include "math/Vector4.h"
#include "math/Matrix4x4.h"

#include "render/rhi/empty_rhi/RHI_Type.h"
#include "render/rhi/empty_rhi/RHI_Class.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System {

	using NameSpace_Core::NameSpace_Math::Vector3;
	using NameSpace_Core::NameSpace_Math::Vector4;
	using NameSpace_Core::NameSpace_Math::Matrix4x4;

	using NameSpace_RHI::RHI_FORMAT;
	using NameSpace_RHI::RHI_Buffer;
	using NameSpace_RHI::RHI_Descriptor_Set;
	using NameSpace_RHI::RHI_Image;
	using NameSpace_RHI::RHI_Image_View;

	static constexpr uint32_t g_Point_Light_Shadow_map_Dimension = 2048;
	static constexpr uint32_t g_Directional_Light_Shadow_map_Dimension = 4096;

	static constexpr uint32_t g_Mesh_Per_Draw_Call_Max_Instance_Count = 64;
	static constexpr uint32_t g_Mesh_Vertex_Blending_Max_Joint_Count = 1024;
	static constexpr uint32_t g_Max_Point_Light_Count = 15;

	static constexpr uint32_t g_Particle_Billboard_Buffer_Size = 4096;

	struct alignas(16)
		Scene_Directional_Light final {
		Vector3 Direction;
		Vector3 Color;

	};

	struct alignas(16)
		Scene_Point_Light final {
		Vector3 Position;
		Vector3 Intensity;
		float Radius;

	};

	struct alignas(16)
		Mesh_Per_Frame_Storage_Buffer_Object final {
		Matrix4x4 Proj_View_Matrix;
		Vector3 Camera_Position;
		Vector3 Ambient_Light;
		uint32_t Point_Light_Num;

		Scene_Point_Light Scene_Point_Lights[g_Max_Point_Light_Count];
		Scene_Directional_Light m_Scene_Directional_Light;
		Matrix4x4 Directional_Light_View_Proj_Matrix;

	};

	struct alignas(16)
		Mesh_Instance final {
		float Enbale_Vertex_Blending;
		Matrix4x4 Model_Matrix;

	};

	struct alignas(16)
		Mesh_Per_Draw_Class_Storage_Buffer_Object final {
		Mesh_Instance Mesh_Instances[g_Mesh_Per_Draw_Call_Max_Instance_Count];

	};

	struct alignas(16)
		Mesh_Per_Material_Uniform_Buffer_Object final {
		Vector4 Nase_Color_Factor{ Vector4::ZERO };

		float Metallic_Factor{ 0.f };
		float Roughness_Factor{ 0.f };
		float Normal_Scale{ 0.f };
		float Occlusion_Strength{ 0.f };

		Vector3 Emissive_Factor{ Vector3::ZERO };
		int32_t Is_Blend = 0;
		uint32_t is_Double_Sided = 0;

	};

	struct alignas(16)
		Mesh_Per_Draw_Call_Vertex_Blending_Storage_Buffer_Object {
		Matrix4x4 Joint_Matrices[g_Mesh_Vertex_Blending_Max_Joint_Count * g_Mesh_Per_Draw_Call_Max_Instance_Count];

	};

	struct alignas(16)
		Mesh_Point_Light_Shadow_Per_Frame_Storage_Buffer_Object final {
		uint32_t Point_Light_Num;
		Vector4 Point_Lights_Position_And_Radius[g_Max_Point_Light_Count];

	};

	struct alignas(16)
		Mesh_Point_Light_Shadow_Per_Draw_Call_Storage_Buffer_Object final {
		Matrix4x4 Mesh_Instances[g_Mesh_Per_Draw_Call_Max_Instance_Count];

	};

	struct alignas(16)
		Mesh_Point_Light_Shadow_Per_Draw_Call_Vertex_Blending_Storage_Buffer_Object final {

		Matrix4x4 Joint_Matrices[g_Mesh_Vertex_Blending_Max_Joint_Count * g_Mesh_Per_Draw_Call_Max_Instance_Count];
	};

	struct alignas(16)
		Mesh_Directional_Light_Shadow_Per_Frame_Storage_Buffer_Object final {

		Matrix4x4 Light_Proj_View;

	};

	struct alignas(16)
		Mesh_Directional_Light_Shadow_Per_Draw_Call_Storage_Buffer_Object final {
		Mesh_Instance Mesh_Instances[g_Mesh_Per_Draw_Call_Max_Instance_Count];

	};

	struct alignas(16)
		Mesh_Directional_Light_Shadow_Per_Draw_CallVertex_Blending_Storage_Buffer_Object final {
		Matrix4x4 Joint_Matrices[g_Mesh_Vertex_Blending_Max_Joint_Count * g_Mesh_Per_Draw_Call_Max_Instance_Count];
	};

	struct alignas(16)
		Axis_Storage_Buffer_Object final {
		Matrix4x4 Model_Matrix{ Matrix4x4::IDENTITY };
		uint32_t Selected_Axis = 3;

	};

	struct alignas(16)
		Particle_Billboard_Per_Frame_Storage_Buffer_Object final {
		Matrix4x4 Prjo_View_Matrix;
		Vector3 Right_Direction;
		Vector3 Up_Direction;
		Vector3 Foward_Position;
	};

	struct alignas(16)
		Patricle_Collision_Pre_Frame_Storage_Buffer_Object final {
		Matrix4x4 View_Matrix;
		Matrix4x4 Proj_View_Matrix;
		Matrix4x4 Proj_Inv_Matrix;

	};

	struct alignas(16)
		Particle_Billboard_Per_Draw_Call_Storage_Buffer_Object final {
		Vector4 Positions[g_Particle_Billboard_Buffer_Size];
		Vector4 Sizes[g_Particle_Billboard_Buffer_Size];
		Vector4 Colors[g_Particle_Billboard_Buffer_Size];

	};

	struct alignas(16)
		Mesh_Inefficient_Pick_Per_Frame_Storage_Buffer_Object final {

		Matrix4x4 Proj_View_Matrix;
		uint32_t Render_Target_Width;
		uint32_t Render_Target_Height;

	};

	struct alignas(16)
		Mesh_Inefficient_Pick_Per_Draw_Call_Storage_Buffer_Object final {
		Matrix4x4 Model_Matrices[g_Mesh_Per_Draw_Call_Max_Instance_Count];
		uint32_t Node_IDs[g_Mesh_Per_Draw_Call_Max_Instance_Count];
		float Enable_Vertex_Blendings[g_Mesh_Per_Draw_Call_Max_Instance_Count];

	};

	struct alignas(16)
		Mesh_Inefficient_Pick_Per_Draw_Call_Vertex_Blending_Storage_Buffer_Object final {
		Matrix4x4 Joint_Matrices[g_Mesh_Vertex_Blending_Max_Joint_Count * g_Mesh_Per_Draw_Call_Max_Instance_Count];

	};

	struct Vulkan_Mesh final {
		bool Enable_Vertex_Blending;

		uint32_t Mesh_Vertex_Count;

		unique_ptr<RHI_Buffer> Mesh_Vertex_Position_Buffer;
		VmaAllocation Mesh_Vertex_Position_Allocation;

		unique_ptr<RHI_Buffer> Mesh_Vertex_Varying_Enable_Blending_Buffer;
		VmaAllocation Mesh_Vertex_Varying_Enable_Blending_Allocation;

		unique_ptr<RHI_Buffer> Mesh_Vertex_Joint_Binding_Buffer;
		VmaAllocation Mesh_Vertex_Joint_Binding_Allocation;

		unique_ptr<RHI_Descriptor_Set> Mesh_Vertex_Blending_Descriptor_Set;

		unique_ptr<RHI_Buffer> Mesh_Vertex_Varying_Buffer;
		VmaAllocation Mesh_Vertex_Varying_Allocation;

		uint32_t Mesh_Index_Count;

		unique_ptr<RHI_Buffer>  Mesh_Index_Buffer;
		VmaAllocation Mesh_Index_Allocation;
	};

	struct Vulkan_PBR_Texture_Data_Info final {
		void* Base_Color_Image_Pixels;
		uint32_t Base_Color_Image_Width;
		uint32_t Base_Color_Image_Height;
		RHI_FORMAT Base_Color_Image_Format;

		void* Metallic_Roughness_Image_Pixels;
		uint32_t Metallic_Roughness_Image_Width;
		uint32_t Metallic_Roughness_Image_Height;
		RHI_FORMAT Metallic_Roughness_Image_Format;

		void* Normal_Image_Pixels;
		uint32_t Normal_Image_Width;
		uint32_t Normal_Image_Height;
		RHI_FORMAT Normal_Image_Format;

		void* Occlusion_Image_Pixels;
		uint32_t Occlusion_Image_Width;
		uint32_t Occlusion_Image_Height;
		RHI_FORMAT Occlusion_Image_Format;

		void* Emissive_Image_Pixels;
		uint32_t Emissive_Image_Width;
		uint32_t Emissive_Image_Height;
		RHI_FORMAT Emissive_Image_Format;
	};

	struct Vulkan_PBR_Material final {
		unique_ptr<RHI_Image> Base_Color_Image;
		unique_ptr<RHI_Image_View> Base_Color_Image_View;
		VmaAllocation Base_Color_Image_Allocation;

		unique_ptr<RHI_Image>Metallic_Roughness_Image;
		unique_ptr<RHI_Image_View> Metallic_Roughness_Image_View;
		VmaAllocation Metallic_Roughness_Image_Allocation;

		unique_ptr<RHI_Image> Normal_Image;
		unique_ptr<RHI_Image_View> Normal_Image_View;
		VmaAllocation Normal_Image_Allocation;

		unique_ptr<RHI_Image> Occlusion_Image;
		unique_ptr<RHI_Image_View> Occlusion_Image_View;
		VmaAllocation Occlusion_Image_Allocation;

		unique_ptr<RHI_Image> Emissive_Image;
		unique_ptr<RHI_Image_View> Emissive_Image_View;
		VmaAllocation Emissive_Image_Allocation;

		unique_ptr<RHI_Buffer> Material_Uniform_Buffer;
		VmaAllocation Material_Uniform_Buffer_Allocation;

		RHI_Descriptor_Set* Material_Descriptor_Set;
	};

	struct alignas(16)
		Vulkan_Render_Mesh_Node final {
		const Matrix4x4* Model_Matrix{ nullptr };
		const Matrix4x4* Joint_Matrix{ nullptr };
		uint32_t Joint_Count{ 0 };

		Vulkan_Mesh* Ref_Mesh{ nullptr };
		Vulkan_PBR_Material* Ref_Material{ nullptr };

		uint32_t Node_ID;
		bool ENable_Vertex_Blending{ false };

	};

	struct alignas(16)
		Vulkan_Render_Axis_Node final {
		Matrix4x4 Model_Matrix{ Matrix4x4::IDENTITY };
		Vulkan_Mesh* Fef_Mesh{ nullptr };
		uint_fast32_t Node_ID;
		bool Enbale_Vertex_Blending{ false };
	};

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System