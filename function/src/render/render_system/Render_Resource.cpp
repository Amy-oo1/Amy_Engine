#include "render/render_system/Render_Resource.h"

#include<utility>

#include "logger/System_Logger.h"

#include "render/rhi/vulkan/Vulkan_RHI.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System {

	using NameSpace_Core::NameSpace_Logger::System_Logger;

	using NameSpace_RHI::RHI_STRUCT_TYPE;

	using NameSpace_RHI::RHI_FILTER;
	using NameSpace_RHI::RHI_SAMPLER_ADDRESS_MODE;
	using NameSpace_RHI::RHI_COMPARE_OP;
	using NameSpace_RHI::RHI_BORDER_COLOR;
	using NameSpace_RHI::RHI_SAMPLER_MIPMAP_MODE;

	using NameSpace_RHI::RHI_Buffer_Usage_Flag_Bits;
	using NameSpace_RHI::RHI_Memory_Property_Flag_Bits;

	using NameSpace_RHI::RHI_Physical_Device_Properties;
	using NameSpace_RHI::RHI_Sampler_Create_Info;

	using NameSpace_RHI::NameSpace_Vulkan_RHI::Vulkan_RHI;

	void Render_Resource::Create_Storge_Buffer(shared_ptr<Empty_RHI> RHI) {
		auto Ref_Vulkan_RHI{ static_cast<Vulkan_RHI*>(RHI.get()) };

		auto PhySical_Device_ProPerties{ Ref_Vulkan_RHI->Get_Physical_Device_Properties() };

		uint32_t Frames_In_Flight{ Vulkan_RHI::s_Frames_In_Flight };

		//NOTE : Global_Upload Storage Buffer
		auto& Ref_Stroage_Buffer{ this->m_Global_Render_Resource.Storage_Buffer };

		Ref_Stroage_Buffer.Min_Uniform_Buffer_Offset_Alignment = static_cast<uint32_t>(PhySical_Device_ProPerties.Limits.minUniformBufferOffsetAlignment);
		Ref_Stroage_Buffer.Min_Storage_Buffer_Offset_Alignment = static_cast<uint32_t>(PhySical_Device_ProPerties.Limits.minStorageBufferOffsetAlignment);
		Ref_Stroage_Buffer.Max_Storage_Buffer_Range = static_cast<uint32_t>(PhySical_Device_ProPerties.Limits.maxStorageBufferRange);
		Ref_Stroage_Buffer.Non_Coherent_Atom_Size = static_cast<uint32_t>(PhySical_Device_ProPerties.Limits.nonCoherentAtomSize);

		auto [Storage_Buffer, Strage_Memory] = Ref_Vulkan_RHI->Create_Buffer(
			Ref_Stroage_Buffer.Max_Storage_Buffer_Range,//NOTE : Set Max Size
			RHI_Buffer_Usage_Flag_Bits::RHI_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT,
			RHI_Memory_Property_Flag_Bits::RHI_MEMORY_PROPERTY_HOST_VISIBLE_BIT | RHI_Memory_Property_Flag_Bits::RHI_MEMORY_PROPERTY_HOST_COHERENT_BIT
		);
		Ref_Stroage_Buffer.Global_Upload_Ring_Buffer = std::move(Storage_Buffer);
		Ref_Stroage_Buffer.Global_Upload_Ring_Buffer_Memory = std::move(Strage_Memory);

		Ref_Stroage_Buffer.Global_Upload_Ring_Buffers_Begin.resize(Ref_Stroage_Buffer.Max_Storage_Buffer_Range);
		Ref_Stroage_Buffer.Global_Upload_Ring_Buffers_End.resize(Ref_Stroage_Buffer.Max_Storage_Buffer_Range);
		Ref_Stroage_Buffer.Global_Upload_Ring_Buffers_Size.resize(Ref_Stroage_Buffer.Max_Storage_Buffer_Range);
		for (uint32_t Index = 0; Index < Frames_In_Flight; ++Index) {
			Ref_Stroage_Buffer.Global_Upload_Ring_Buffers_Begin[Index] = (Ref_Stroage_Buffer.Max_Storage_Buffer_Range * Index) / Ref_Stroage_Buffer.Max_Storage_Buffer_Range;
			Ref_Stroage_Buffer.Global_Upload_Ring_Buffers_End[Index] = (Ref_Stroage_Buffer.Max_Storage_Buffer_Range * (Index + 1)) / Ref_Stroage_Buffer.Max_Storage_Buffer_Range;
			Ref_Stroage_Buffer.Global_Upload_Ring_Buffers_Size[Index] = Ref_Stroage_Buffer.Global_Upload_Ring_Buffers_End[Index] - Ref_Stroage_Buffer.Global_Upload_Ring_Buffers_Begin[Index];
		}

		//NOTE :Axis Storage Buffer
		auto [Axis_Buffer, Axis_Memory] = Ref_Vulkan_RHI->Create_Buffer(
			Ref_Stroage_Buffer.Axis_Storage_Buffer_Size,
			RHI_Buffer_Usage_Flag_Bits::RHI_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT,
			RHI_Memory_Property_Flag_Bits::RHI_MEMORY_PROPERTY_HOST_VISIBLE_BIT | RHI_Memory_Property_Flag_Bits::RHI_MEMORY_PROPERTY_HOST_COHERENT_BIT
		);
		Ref_Stroage_Buffer.Axis_Inefficient_Strogae_Buffer = std::move(Axis_Buffer);
		Ref_Stroage_Buffer.Axis_Inefficient_Strogae_Buffer_Memory = std::move(Axis_Memory);


		//NOTE : Null Descriptor Storage Buffer
		auto [Null_Descriptor_Buffer, Null_Descriptor_Memory] = Ref_Vulkan_RHI->Create_Buffer(
			Ref_Stroage_Buffer.Global_Null_Descriptor_Buffer_Size,
			RHI_Buffer_Usage_Flag_Bits::RHI_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT,
			RHI_Memory_Property_Flag_Bits::RHI_MEMORY_PROPERTY_HOST_VISIBLE_BIT | RHI_Memory_Property_Flag_Bits::RHI_MEMORY_PROPERTY_HOST_COHERENT_BIT
		);
		Ref_Stroage_Buffer.Global_Null_Descriptor_Storage_Buffer = std::move(Null_Descriptor_Buffer);
		Ref_Stroage_Buffer.Global_Null_Descriptor_Storage_Buffer_Memory = std::move(Null_Descriptor_Memory);
	}

	void Render_Resource::Map_Storage_Buffer(shared_ptr<Empty_RHI> RHI) {
		auto Ref_Vulkan_RHI{ static_cast<Vulkan_RHI*>(RHI.get()) };
		auto& Ref_Stroage_Buffer{ this->m_Global_Render_Resource.Storage_Buffer };

		Ref_Vulkan_RHI->Map_Memory(
			Ref_Stroage_Buffer.Global_Upload_Ring_Buffer_Memory.get(),
			0,
			RHI_WHOLE_SIZE,
			0,
			&Ref_Stroage_Buffer.Global_Upload_Ring_Buffer_Mapped_Mamary
		);

		Ref_Vulkan_RHI->Map_Memory(
			Ref_Stroage_Buffer.Axis_Inefficient_Strogae_Buffer_Memory.get(),
			0,
			RHI_WHOLE_SIZE,
			0,
			&Ref_Stroage_Buffer.Axis_Inefficient_Strogae_Buffer_Mapped_Memory
		);
	}

	void Render_Resource::Un_Map_Storage_Resource(shared_ptr<Empty_RHI> RHI) {
		auto Ref_Vulkan_RHI{ static_cast<Vulkan_RHI*>(RHI.get()) };

		auto& Ref_Stroage_Buffer{ this->m_Global_Render_Resource.Storage_Buffer };

		Ref_Vulkan_RHI->UnMap_Memory(Ref_Stroage_Buffer.Global_Upload_Ring_Buffer_Memory.get());
		Ref_Vulkan_RHI->UnMap_Memory(Ref_Stroage_Buffer.Axis_Inefficient_Strogae_Buffer_Memory.get());
	}

	void Render_Resource::Create_IBL_Samplers(shared_ptr<Empty_RHI> RHI) {
		auto Ref_Vulkan_RHI{ static_cast<Vulkan_RHI*>(RHI.get()) };

		auto PhySical_Device_ProPerties{ Ref_Vulkan_RHI->Get_Physical_Device_Properties() };

		RHI_Sampler_Create_Info Sampler_Create_Info{};
		{
			Sampler_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
			Sampler_Create_Info.Mag_Filter = RHI_FILTER::RHI_FILTER_LINEAR;
			Sampler_Create_Info.Min_Filter = RHI_FILTER::RHI_FILTER_LINEAR;
			Sampler_Create_Info.Mipmap_Mode = RHI_SAMPLER_MIPMAP_MODE::RHI_SAMPLER_MIPMAP_MODE_LINEAR;
			Sampler_Create_Info.Address_Mode_U = RHI_SAMPLER_ADDRESS_MODE::RHI_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
			Sampler_Create_Info.Address_Mode_V = RHI_SAMPLER_ADDRESS_MODE::RHI_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
			Sampler_Create_Info.Address_Mode_W = RHI_SAMPLER_ADDRESS_MODE::RHI_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
			Sampler_Create_Info.Mip_Lod_Bias = 0;
			Sampler_Create_Info.Anisotropy_Enable = RHI_TRUE;//TODO :Config Anisotropy
			Sampler_Create_Info.Max_Anisotropy = PhySical_Device_ProPerties.Limits.maxSamplerAnisotropy;
			Sampler_Create_Info.Compare_Enable = RHI_FALSE;
			Sampler_Create_Info.Compare_Op = RHI_COMPARE_OP::RHI_COMPARE_OP_ALWAYS;
			Sampler_Create_Info.Min_Lod = 0.f;
			Sampler_Create_Info.Max_Lod = 0.f;
			Sampler_Create_Info.Border_Color = RHI_BORDER_COLOR::RHI_BORDER_COLOR_FLOAT_OPAQUE_BLACK;
			Sampler_Create_Info.Unnormalized_Coordinates = RHI_FALSE;
		}

		auto& Ref_IBL_Resource{ this->m_Global_Render_Resource.IBL_Resource };

		if (RHI_NULL_HANDLE != Ref_IBL_Resource.BUDF_LUT_Texture_Sampler)
			System_Logger::Get_Instance().Log(System_Logger::Level::err, "BUDF_LUT_Texture_Sampler Already Created, Doing ReCreate");
		Ref_IBL_Resource.BUDF_LUT_Texture_Sampler = std::move(Ref_Vulkan_RHI->Create_Sampler(&Sampler_Create_Info));


		Sampler_Create_Info.Max_Lod = 8.f; //RHI_WHOLE_SIZE;
		if (RHI_NULL_HANDLE != Ref_IBL_Resource.Irradiance_Map_Texture_Sampler)
			System_Logger::Get_Instance().Log(System_Logger::Level::err, "Irradiance_Map_Texture_Sampler Already Created, Doing ReCreate");
		Ref_IBL_Resource.Irradiance_Map_Texture_Sampler = std::move(Ref_Vulkan_RHI->Create_Sampler(&Sampler_Create_Info));

		if (RHI_NULL_HANDLE != Ref_IBL_Resource.Specular_Map_Texture_Sampler)
			System_Logger::Get_Instance().Log(System_Logger::Level::err, "Specular_Map_Texture_Sampler Already Created, Doing ReCreate");
		Ref_IBL_Resource.Specular_Map_Texture_Sampler = std::move(Ref_Vulkan_RHI->Create_Sampler(&Sampler_Create_Info));
	}

	void Render_Resource::Create_IBL_Textures(shared_ptr<Empty_RHI> RHI, array<shared_ptr<Texture_Data>, 6> Irradiance_Maps, array<shared_ptr<Texture_Data>, 6> Specular_Maps) {
		auto Ref_Vulkan_RHI{ static_cast<Vulkan_RHI*>(RHI.get()) };
		auto& Ref_IBL_Resource{ this->m_Global_Render_Resource.IBL_Resource };

		auto [Irradiance_Image, Irradiance_Image_View, Irradiance_Image_Allocation] = Ref_Vulkan_RHI->Create_Cube_Map(
			{ Irradiance_Maps[0]->Width, Irradiance_Maps[0]->Height },
			Irradiance_Maps[0]->Format,
			Irradiance_Maps[0]->Mip_Levels,
			{ Irradiance_Maps[0]->Pixels.get(), Irradiance_Maps[1]->Pixels.get(), Irradiance_Maps[2]->Pixels.get(), Irradiance_Maps[3]->Pixels.get(), Irradiance_Maps[4]->Pixels.get(), Irradiance_Maps[5]->Pixels.get() }
		);
		Ref_IBL_Resource.Irradiance_Map_Texture_Image = std::move(Irradiance_Image);
		Ref_IBL_Resource.Irradiance_Map_Texture_Image_View = std::move(Irradiance_Image_View);
		Ref_IBL_Resource.Irradiance_Map_Texture_Allocation = std::move(Irradiance_Image_Allocation);

		auto [Specular_Image, Specular_Image_View, Specular_Image_Allocation] = Ref_Vulkan_RHI->Create_Cube_Map(
			{ Specular_Maps[0]->Width, Specular_Maps[0]->Height },
			Specular_Maps[0]->Format,
			Specular_Maps[0]->Mip_Levels,
			{ Specular_Maps[0]->Pixels.get(), Specular_Maps[1]->Pixels.get(), Specular_Maps[2]->Pixels.get(), Specular_Maps[3]->Pixels.get(), Specular_Maps[4]->Pixels.get(), Specular_Maps[5]->Pixels.get() }
		);
		Ref_IBL_Resource.Specular_Map_Texture_Image = std::move(Specular_Image);
		Ref_IBL_Resource.Specular_Map_Texture_Image_View = std::move(Specular_Image_View);
		Ref_IBL_Resource.Specular_Map_Texture_Allocation = std::move(Specular_Image_Allocation);

	}




	void Render_Resource::UpLoad_Global_Render_Resource(shared_ptr<Empty_RHI> RHI, const Level_Resource_Desc& Level_Resource_Desc)
	{
	}

	void Render_Resource::Upload_Game_Object_Render_Resource(shared_ptr<Empty_RHI> RHI, const Render_Entity& Render_Entity, const Render_Mesh_Data& Meshe_Data, const Render_Material_Data& Material_Data)
	{
	}

	void Render_Resource::Upload_Game_Object_Render_Resource(shared_ptr<Empty_RHI> RHI, const Render_Entity& Render_Entity, const Render_Mesh_Data& Meshe_Data)
	{
	}

	void Render_Resource::Upload_Game_Object_Render_Resource(shared_ptr<Empty_RHI> RHI, const Render_Entity& Render_Entity, const Render_Material_Data& Material_Data)
	{
	}

	void Render_Resource::Updata_Per_Frame_Buffer(shared_ptr<Render_Camera> Camera)
	{
	}

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System