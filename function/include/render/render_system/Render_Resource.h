#pragma once

#include<cstdint>
#include<limits>
#include<tuple>
#include<array>
#include<vector>
#include<unordered_map>
#include<memory>
#include<algorithm>

#include "vma/vk_mem_alloc.h"

#include "math/Vector2.h"
#include"math/Vector3.h"
#include"math/Vector4.h"
#include "math/Matrix4x4.h"

#include "render/rhi/empty_rhi/RHI_Type.h"
#include "render/rhi/empty_rhi/RHI_Class.h"
#include "render/rhi/empty_rhi/RHI_Struct.h"
#include "render/rhi/vulkan/Vulkan_RHI_Resource.h"

#include "render/render_system/Render_Data_Struct.h"
#include "render/render_system/Render_Commmon.h"
#include "render/render_system/Render_Mesh.h"
#include "render/render_system/Render_Resource_Base.h"


namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System {

	//TODO :Remove
	class Render_Scene;

	using std::tuple;
	using std::array;
	using std::vector;
	using std::unordered_map;
	using std::unique_ptr;
	using std::shared_ptr;

	using NameSpace_Core::NameSpace_Math::Vector2;
	using NameSpace_Core::NameSpace_Math::Vector3;
	using NameSpace_Core::NameSpace_Math::Vector4;
	using NameSpace_Core::NameSpace_Math::Matrix4x4;

	using NameSpace_RHI::RHI_FORMAT;

	using NameSpace_RHI::RHI_Image;
	using NameSpace_RHI::RHI_Image_View;
	using NameSpace_RHI::RHI_Buffer;
	using NameSpace_RHI::RHI_Device_Memory;
	using NameSpace_RHI::RHI_Sampler;
	using NameSpace_RHI::RHI_Descriptor_Set_Layout;

	using NameSpace_RHI::NameSpace_Vulkan_RHI::Vulkan_Descriptor_Set_Layout;



	struct IBL_Resource final {
		unique_ptr<RHI_Image> BUDF_LUT_Image;
		unique_ptr<RHI_Image_View> BUDF_LUT_Image_View;
		unique_ptr<RHI_Sampler> BUDF_LUT_Sampler;
		VmaAllocation BUDF_LUT_Image_Allocation;

		unique_ptr<RHI_Image> Irradiance_Map_Image;
		unique_ptr<RHI_Image_View> Irradiance_Map_Image_View;
		unique_ptr<RHI_Sampler> Irradiance_Map_Sampler;
		VmaAllocation Irradiance_Map_Image_Allocation;

		unique_ptr<RHI_Image> Specular_Map_Image;
		unique_ptr<RHI_Image_View> Specular_Map_Image_View;
		unique_ptr<RHI_Sampler> Specular_Map_Sampler;
		VmaAllocation Specular_Map_Image_Allocation;

	};

	struct IBL_Resource_Data final {
		void* BUDF_LUT_Texture_Image_Pixels;
		uint32_t BUDF_LUT_Texture_Image_Width;
		uint32_t BUDF_LUT_Texture_Image_Height;
		RHI_FORMAT BUDF_LUT_Texture_Image_Format;

		array<void*, 6> Irradiance_Map_Texture_Image_Pixels;
		uint32_t Irradiance_Map_Texture_Image_Width;
		uint32_t Irradiance_Map_Texture_Image_Height;
		RHI_FORMAT Irradiance_Map_Texture_Image_Format;

		array<void*, 6> Specular_Map_Texture_Image_Pixels;
		uint32_t Specular_Map_Texture_Image_Width;
		uint32_t Specular_Map_Texture_Image_Height;
		RHI_FORMAT Specular_Map_Texture_Image_Format;

	};

	struct Color_Grading_Resource final {
		unique_ptr<RHI_Image> Color_Grading_Image;
		unique_ptr<RHI_Image_View> Color_Grading_Image_View;
		//RHI_Sampler* Color_Grading_LUT_Texture_Sampler;
		VmaAllocation Color_Grading_Image_Allocation;

	};

	struct IBL_Grading_Resource_Data final {
		void* Color_Grading_LUT_Texture_Image_Pixels;
		uint32_t Color_Grading_LUT_Texture_Image_Width;
		uint32_t Color_Grading_LUT_Texture_Image_Height;
		RHI_FORMAT Color_Grading_LUT_Texture_Image_Format;

	};

	struct Storage_Buffer final {
		uint32_t Min_Uniform_Buffer_Offset_Alignment{ 256 };//NOTE : HOST 64
		uint32_t Min_Storage_Buffer_Offset_Alignment{ 256 };//NOTE : HOST 16
		uint32_t Max_Storage_Buffer_Range{ 1 << 27 };//NOTE : Default 128MB
		uint32_t Non_Coherent_Atom_Size{ 256 };//NOTE : HOST  64

		unique_ptr<RHI_Buffer> Global_Upload_Ring_Buffer;
		unique_ptr<RHI_Device_Memory> Global_Upload_Ring_Buffer_Memory;
		void* Global_Upload_Ring_Buffer_Mapped_Mamary;
		vector<uint32_t> Global_Upload_Ring_Buffers_Begin;
		vector<uint32_t> Global_Upload_Ring_Buffers_End;
		vector<uint32_t> Global_Upload_Ring_Buffers_Size;

		static constexpr uint32_t Global_Null_Descriptor_Buffer_Size{ 64 };//NOTE : 256B
		unique_ptr<RHI_Buffer> Global_Null_Descriptor_Storage_Buffer;
		unique_ptr<RHI_Device_Memory> Global_Null_Descriptor_Storage_Buffer_Memory;

		static constexpr uint32_t Axis_Storage_Buffer_Size{ sizeof(Axis_Storage_Buffer_Object) };//NOTE : 256B
		unique_ptr<RHI_Buffer> Axis_Inefficient_Strogae_Buffer;
		unique_ptr<RHI_Device_Memory> Axis_Inefficient_Strogae_Buffer_Memory;
		void* Axis_Inefficient_Strogae_Buffer_Mapped_Memory;

	};

	struct Global_Render_Resource final {
		IBL_Resource IBL_Resource;
		Color_Grading_Resource Color_Grading_Resource;
		Storage_Buffer Storage_Buffer;

	};

	class Render_Resource final :public Render_Resource_Base {
		friend class Render_Scene;
	private:
		Render_Resource(const Render_Resource&) = delete;
		Render_Resource& operator=(const Render_Resource&) = delete;

	public:
		Render_Resource(void) = default;

		~Render_Resource(void) = default;


		void Create_Storge_Buffer(shared_ptr<Empty_RHI> RHI);

		void Map_Storage_Buffer(shared_ptr<Empty_RHI> RHI);

		void Un_Map_Storage_Resource(shared_ptr<Empty_RHI> RHI);

		void Create_IBL_Samplers(shared_ptr<Empty_RHI> RHI);

		void
			Create_IBL_Textures(
				shared_ptr<Empty_RHI> RHI,
				array<shared_ptr<Texture_Data>, 6> Irradiance_Maps,
				array<shared_ptr<Texture_Data>, 6> Specular_Maps
			);

		const Vulkan_Mesh&
			Get_OR_Create_Vulkan_Mesh(
				shared_ptr<Empty_RHI> RHI,
				const Render_Entity& Render_Entity,
				const Render_Mesh_Data& Mesh_Data
			);

		const Vulkan_PBR_Material&
			Get_OR_Create_Vulkan_Material(
				shared_ptr<Empty_RHI> RHI,
				const Render_Entity& Render_Entity,
				const Render_Material_Data& Mesh_Data
			);

		void Reset_Ring_Buffer_Offset(uint32_t Current_Frame_Index);

		[[nodiscard]] const Vulkan_Mesh& Get_Entity_Mesh(const Render_Entity& Entity)const;
		[[nodiscard]] const Vulkan_PBR_Material& Get_Entity_Material(const Render_Entity& Entity)const;

	private:
		[[nodiscard]] Vulkan_Mesh
			Load_Mesh_Binding_Buffer(
				shared_ptr<Empty_RHI> RHI,
				uint32_t Index_Buffer_Size,
				uint16_t* Index_Buffer_Data,
				uint32_t Vertex_Buffer_Size,
				const  Mesh_Vertex_Data_Definition* Vertex_Buffer_Data,
				uint32_t Joint_Binding_Buffer_Size,
				const  Mesh_Vertx_Binding_Data_Definition* Joint_Binding_Buffer_Data
			);

		[[nodiscard]] Vulkan_Mesh
			Load_Mesh_Buffer(
				shared_ptr<Empty_RHI> RHI,
				uint32_t Index_Buffer_Size,
				uint16_t* Index_Buffer_Data,
				uint32_t Vertex_Buffer_Size,
				const  Mesh_Vertex_Data_Definition* Vertex_Buffer_Data
			);

		[[nodiscard]] Vulkan_PBR_Material
			Load_PBR_Material_Image(
				shared_ptr<Empty_RHI> RHI,
				const Vulkan_PBR_Texture_Data_Info& Texture_Data_Info
			);


	private:
		[[nodiscard]] static tuple<
			unique_ptr<RHI_Buffer>,
			VmaAllocation>
			S_Load_Index_Buffer(
				shared_ptr<Empty_RHI> RHI,
				uint32_t Index_Buffer_Size,
				uint16_t* Index_Buffer_Data
			);


	public:
		static constexpr uint32_t s_Max_Global_Stroage_Buffer_Size{ 1 << 27 };

		const Global_Render_Resource& Get_Global_Render_Resource(void)const;

	public:
		RHI_Descriptor_Set_Layout* m_Mesh_Descriptor_Set_Layout{ nullptr };

		RHI_Descriptor_Set_Layout* m_Material_Descriptor_Set_Layout{ nullptr };

		Global_Render_Resource m_Global_Render_Resource;

		Mesh_Per_Frame_Storage_Buffer_Object m_Mesh_Per_Frame_Storage_Buffer_Object;
		Mesh_Point_Light_Shadow_Per_Frame_Storage_Buffer_Object m_Mesh_Point_Light_Shadow_Per_Frame_Storage_Buffer_Object;
		Mesh_Directional_Light_Shadow_Per_Frame_Storage_Buffer_Object m_Mesh_Directional_Light_Shadow_Per_Frame_Storage_Buffer_Object;

		Mesh_Inefficient_Pick_Per_Frame_Storage_Buffer_Object m_Mesh_Inefficient_Pick_Per_Frame_Storage_Buffer_Object;

		Particle_Billboard_Per_Frame_Storage_Buffer_Object m_Particle_Billboard_Per_Frame_Storage_Buffer_Object;
		Patricle_Collision_Pre_Frame_Storage_Buffer_Object m_Particle_Collision_Pre_Frame_Storage_Buffer_Object;

		Axis_Storage_Buffer_Object m_Axis_Storage_Buffer_Object;

		unordered_map<size_t, Vulkan_Mesh> m_Vulkan_Mesh_Map;
		unordered_map<size_t, Vulkan_PBR_Material> m_Vulkan_PBR_Material_Map;

	public:
		void Set_Mesh_Descriptor_Set_Layout(RHI_Descriptor_Set_Layout* Mesh_Descriptor_Set_Layout);
		void Set_Material_Descriptor_Set_Layout(RHI_Descriptor_Set_Layout* Material_Descriptor_Set_Layout);


		void
			Upload_Global_Render_Resource(
				shared_ptr<Empty_RHI> RHI,
				const Level_Resource_Desc& Level_Resource_Desc
			) override;


		void Upload_Game_Object_Render_Resource(
			shared_ptr<Empty_RHI> RHI,
			const Render_Entity& Render_Entity,
			const Render_Mesh_Data& Meshe_Data,
			const Render_Material_Data& Material_Data
		) override;


		void Upload_Game_Object_Render_Resource(
			shared_ptr<Empty_RHI> RHI,
			const Render_Entity& Render_Entity,
			const Render_Mesh_Data& Meshe_Data
		) override;


		void Upload_Game_Object_Render_Resource(
			shared_ptr<Empty_RHI> RHI,
			const Render_Entity& Render_Entity,
			const Render_Material_Data& Material_Data
		) override;


		void Updata_Per_Frame_Buffer(
			shared_ptr<Render_Scene> Scene,
			shared_ptr<Render_Camera> Camera
		) override;

	};

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System