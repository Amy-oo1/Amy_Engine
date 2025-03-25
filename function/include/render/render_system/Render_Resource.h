#pragma once

#include<cstdint>
#include<array>
#include<vector>
#include<unordered_map>
#include<memory>
#include<algorithm>

#include "vma/vk_mem_alloc.h"

#include "render/rhi/empty_rhi/RHI_Type.h"
#include "render/rhi/empty_rhi/RHI_Class.h"
#include "render/rhi/empty_rhi/RHI_Struct.h"
#include "render/render_system/Render_Data_Struct.h"
#include "render/render_system/Render_Commmon.h"
#include "render/render_system/Render_Resource_Base.h"


namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System {

	using std::array;
	using std::vector;
	using std::unordered_map;
	using std::unique_ptr;
	using std::shared_ptr;

	using NameSpace_RHI::RHI_FORMAT;

	using NameSpace_RHI::RHI_Image;
	using NameSpace_RHI::RHI_Image_View;
	using NameSpace_RHI::RHI_Sampler;
	using NameSpace_RHI::RHI_Buffer;
	using NameSpace_RHI::RHI_Device_Memory;

	struct IBL_Resource final {
		unique_ptr<RHI_Image> BUDF_LUT_Texture_Image;
		unique_ptr<RHI_Image_View> BUDF_LUT_Texture_Image_View;
		unique_ptr<RHI_Sampler> BUDF_LUT_Texture_Sampler;
		VmaAllocation BUDF_LUT_Texture_Allocation;

		unique_ptr<RHI_Image> Irradiance_Map_Texture_Image;
		unique_ptr<RHI_Image_View> Irradiance_Map_Texture_Image_View;
		unique_ptr<RHI_Sampler> Irradiance_Map_Texture_Sampler;
		VmaAllocation Irradiance_Map_Texture_Allocation;

		unique_ptr<RHI_Image> Specular_Map_Texture_Image;
		unique_ptr<RHI_Image_View> Specular_Map_Texture_Image_View;
		unique_ptr<RHI_Sampler> Specular_Map_Texture_Sampler;
		VmaAllocation Specular_Map_Texture_Allocation;

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
		RHI_Image* Color_Grading_LUT_Texture_Image;
		RHI_Image_View* Color_Grading_LUT_Texture_Image_View;
		//RHI_Sampler* Color_Grading_LUT_Texture_Sampler;
		VmaAllocation Color_Grading_LUT_Texture_Allocation;

	};

	struct IBL_Grading_Resource_Data final {
		void* Color_Grading_LUT_Texture_Image_Pixels;
		uint32_t Color_Grading_LUT_Texture_Image_Width;
		uint32_t Color_Grading_LUT_Texture_Image_Height;
		RHI_FORMAT Color_Grading_LUT_Texture_Image_Format;

	};

	struct Storage_Buffer final {
		uint32_t Min_Uniform_Buffer_Offset_Alignment{ 256 };
		uint32_t Min_Storage_Buffer_Offset_Alignment{ 256 };
		uint32_t Max_Storage_Buffer_Range{ 1 << 27 };//NOTE : Default 128MB
		uint32_t Non_Coherent_Atom_Size{ 256 };

		unique_ptr<RHI_Buffer> Global_Upload_Ring_Buffer;
		unique_ptr<RHI_Device_Memory> Global_Upload_Ring_Buffer_Memory;
		void* Global_Upload_Ring_Buffer_Mapped_Mamary;
		vector<uint32_t> Global_Upload_Ring_Buffers_Begin;
		vector<uint32_t> Global_Upload_Ring_Buffers_End;
		vector<uint32_t> Global_Upload_Ring_Buffers_Size;

		static constexpr uint32_t Global_Null_Descriptor_Buffer_Size{ sizeof(Axis_Storage_Buffer_Object) };//NOTE : 256B
		unique_ptr<RHI_Buffer> Global_Null_Descriptor_Storage_Buffer;
		unique_ptr<RHI_Device_Memory> Global_Null_Descriptor_Storage_Buffer_Memory;

		static constexpr uint32_t Axis_Storage_Buffer_Size{ 64 };//NOTE : 256B
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



	private:
		void Create_Storge_Buffer(shared_ptr<Empty_RHI> RHI);

		void Map_Storage_Buffer(shared_ptr<Empty_RHI> RHI);

		void Un_Map_Storage_Resource(shared_ptr<Empty_RHI> RHI);

		void Create_IBL_Samplers(shared_ptr<Empty_RHI> RHI);

		void Create_IBL_Textures(
			shared_ptr<Empty_RHI> RHI,
			array<shared_ptr<Texture_Data>, 6> Irradiance_Maps,
			array<shared_ptr<Texture_Data>, 6> Specular_Maps
		);


	public:
		static constexpr uint32_t s_Max_Global_Stroage_Buffer_Size{ 1 << 27 };


	private:
		Global_Render_Resource m_Global_Render_Resource;
		IBL_Resource_Data m_IBL_Resource_Data;
		IBL_Grading_Resource_Data m_IBL_Grading_Resource_Data;
		//TODO : Add Color Grading Data
		//TODO : Add Storage Buffer Data


	public:



		void
			UpLoad_Global_Render_Resource(
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
			//TODO
			shared_ptr<Render_Camera> Camera
		) override;

	};

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System