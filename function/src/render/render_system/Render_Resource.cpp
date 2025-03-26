#include "render/render_system/Render_Resource.h"

#include<utility>

#include "logger/System_Logger.h"

#include "render/rhi/vulkan/Vulkan_RHI.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System {

	using NameSpace_Core::NameSpace_Logger::System_Logger;

	using NameSpace_RHI::RHI_Device_Size;

	using NameSpace_RHI::RHI_Buffer_Usage_Flag_Bits;
	using NameSpace_RHI::RHI_Memory_Property_Flag_Bits;

	using NameSpace_RHI::RHI_FILTER;
	using NameSpace_RHI::RHI_SAMPLER_ADDRESS_MODE;
	using NameSpace_RHI::RHI_COMPARE_OP;
	using NameSpace_RHI::RHI_BORDER_COLOR;
	using NameSpace_RHI::RHI_SAMPLER_MIPMAP_MODE;

	using NameSpace_RHI::RHI_DESCRIPTOR_TYPE;

	using NameSpace_RHI::RHI_STRUCT_TYPE;


	using NameSpace_RHI::RHI_Physical_Device_Properties;
	using NameSpace_RHI::RHI_Sampler_Create_Info;
	using NameSpace_RHI::RHI_Buffer_Create_Info;
	using NameSpace_RHI::RHI_Descriptor_Set_Allocate_Info;
	using NameSpace_RHI::RHI_Descriptor_Buffer_Info;

	using NameSpace_RHI::NameSpace_Vulkan_RHI::Vulkan_RHI;

	using NameSpace_RHI::RHI_Write_Descriptor_Set;

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

	const Vulkan_Mesh& Render_Resource::Get_OR_Create_Vulkan_Resource(shared_ptr<Empty_RHI> RHI, const Render_Entity& Render_Entity, const Render_Mesh_Data& Mesh_Data) {
		auto cIt{ this->m_Vulkan_Mesh_Map.find(Render_Entity.Mesh_Resource_ID) };
		if (this->m_Vulkan_Mesh_Map.end() != cIt)
			return cIt->second;

		uint32_t Index_Buffer_size{ static_cast<uint32_t>(Mesh_Data.Static_Mesh_Data.Index_Buffer->Data_Size * sizeof(uint16_t)) };
		void* Index_Buffer_Data{ Mesh_Data.Static_Mesh_Data.Index_Buffer->Data };

		uint32_t Vertex_Buffer_Size{ static_cast<uint32_t>(Mesh_Data.Static_Mesh_Data.Vertex_Buffer->Data_Size) };

		Mesh_Vertex_Data_Definition* Vertex_Buffer_Data{ reinterpret_cast<Mesh_Vertex_Data_Definition*>(Mesh_Data.Static_Mesh_Data.Vertex_Buffer->Data) };

		if (nullptr != Mesh_Data.Skeletion_Binding_Buffer)
			return this->m_Vulkan_Mesh_Map[Render_Entity.Mesh_Resource_ID] = this->Parser_Updata_Vertex_Buffer(
				RHI,
				Index_Buffer_size,
				reinterpret_cast<uint16_t*>(Index_Buffer_Data),
				Vertex_Buffer_Size,
				Vertex_Buffer_Data
			);

		uint32_t Joint_Binding_Buffer_Size{ static_cast<uint32_t>(Mesh_Data.Skeletion_Binding_Buffer->Data_Size) };
		Mesh_Vertx_Binding_Data_Definition* Joint_Binding_Buffer_Data{ reinterpret_cast<Mesh_Vertx_Binding_Data_Definition*>(Mesh_Data.Skeletion_Binding_Buffer->Data) };

		return this->m_Vulkan_Mesh_Map[Render_Entity.Mesh_Resource_ID] = this->Parser_Updata_Vertex_Buffer_Binding(
			RHI,
			Index_Buffer_size,
			reinterpret_cast<uint16_t*>(Index_Buffer_Data),
			Vertex_Buffer_Size,
			Vertex_Buffer_Data,
			Joint_Binding_Buffer_Size,
			Joint_Binding_Buffer_Data
		);
	}

	Vulkan_Mesh Render_Resource::Parser_Updata_Vertex_Buffer_Binding(shared_ptr<Empty_RHI> RHI, uint32_t Index_Buffer_Size, uint16_t* Index_Buffer_Data, uint32_t Vertex_Buffer_Size, const Mesh_Vertex_Data_Definition* Vertex_Buffer_Data, uint32_t Joint_Binding_Buffer_Size, const Mesh_Vertx_Binding_Data_Definition* Joint_Binding_Buffer_Data) {
		if (0 != (Vertex_Buffer_Size % sizeof(Mesh_Vertex_Data_Definition)))
			System_Logger::Get_Instance().Log(System_Logger::Level::err, "Vertex_Buffer_Size % sizeof(Mesh_Vertex_Data_Definition) != 0");


		if (0 != (Index_Buffer_Size % sizeof(uint16_t)))
			System_Logger::Get_Instance().Log(System_Logger::Level::err, "Joint_Binding_Buffer_Size % sizeof(uint16_t) != 0");

		uint32_t Vertex_Count{ Vertex_Buffer_Size / sizeof(Mesh_Vertex_Data_Definition) };
		uint32_t Index_Count{ Index_Buffer_Size / sizeof(uint32_t) };


		RHI_Device_Size
			Vertex_Position_Buffer_Size{ sizeof(Mesh_Vertex::Vulkan_Mesh_Vertex_Position) * Vertex_Buffer_Size },
			Vertex_Varying_Enable_Bleding_Buffer_Size{ sizeof(Mesh_Vertex::Vulkan_Mesh_Vertex_Varying_Enable_Blending) * Vertex_Buffer_Size },
			Vertex_Varying_Buffer_Size{ sizeof(Mesh_Vertex::Vulkan_Mesh_Vertex_Varying) * Vertex_Buffer_Size },
			Vertex_Joint_Binding_Buffer_Size{ sizeof(Mesh_Vertex::Vulkan_Mesh_Vertex_Joint_Binding) * Joint_Binding_Buffer_Size };

		RHI_Device_Size Vertex_Position_Buffer_Offset{ 0 },
			Vertex_Varying_Enable_Bleding_Buffer_Offset{ Vertex_Position_Buffer_Size },
			Vertex_Varying_Bleding_Buffer_Offset{ Vertex_Varying_Enable_Bleding_Buffer_Offset + Vertex_Varying_Enable_Bleding_Buffer_Size },
			Vertex_Joint_Binding_Buffer_Offset{ Vertex_Varying_Bleding_Buffer_Offset + Vertex_Varying_Buffer_Size };

		RHI_Device_Size Inefficient_Staging_Buffer_Size{ Vertex_Position_Buffer_Size + Vertex_Varying_Enable_Bleding_Buffer_Size + Vertex_Varying_Buffer_Size + Vertex_Joint_Binding_Buffer_Size };

		auto Ref_Vulkan_RHI{ static_cast<Vulkan_RHI*>(RHI.get()) };

		auto [Inefficient_Staging_Buffer, Inefficient_Staging_Buffer_Memory] = RHI->Create_Buffer(
			Inefficient_Staging_Buffer_Size,
			RHI_Buffer_Usage_Flag_Bits::RHI_BUFFER_USAGE_TRANSFER_SRC_BIT,
			RHI_Memory_Property_Flag_Bits::RHI_MEMORY_PROPERTY_HOST_VISIBLE_BIT | RHI_Memory_Property_Flag_Bits::RHI_MEMORY_PROPERTY_HOST_COHERENT_BIT
		);

		void* Inefficient_Staging_Buffer_Mapped_Memory{ nullptr };
		Ref_Vulkan_RHI->Map_Memory(
			Inefficient_Staging_Buffer_Memory.get(),
			0,
			RHI_WHOLE_SIZE,
			0,
			&Inefficient_Staging_Buffer_Mapped_Memory
		);

		Mesh_Vertex::Vulkan_Mesh_Vertex_Position* Mehs_Vertex_Position_Buffer{ reinterpret_cast<Mesh_Vertex::Vulkan_Mesh_Vertex_Position*>(Inefficient_Staging_Buffer_Mapped_Memory) };
		Mesh_Vertex::Vulkan_Mesh_Vertex_Varying_Enable_Blending* Mesh_Vertex_Varying_Enable_Bleding_Buffer{ reinterpret_cast<Mesh_Vertex::Vulkan_Mesh_Vertex_Varying_Enable_Blending*>(reinterpret_cast<uintptr_t>(Inefficient_Staging_Buffer_Mapped_Memory) + Vertex_Varying_Enable_Bleding_Buffer_Offset) };
		Mesh_Vertex::Vulkan_Mesh_Vertex_Varying* Mesh_Vertex_Varying_Bleding_Buffer{ reinterpret_cast<Mesh_Vertex::Vulkan_Mesh_Vertex_Varying*>(reinterpret_cast<uintptr_t>(Inefficient_Staging_Buffer_Mapped_Memory) + Vertex_Varying_Bleding_Buffer_Offset) };
		Mesh_Vertex::Vulkan_Mesh_Vertex_Joint_Binding* Mesh_Vertex_Joint_Binding_Buffer{ reinterpret_cast<Mesh_Vertex::Vulkan_Mesh_Vertex_Joint_Binding*>(reinterpret_cast<uintptr_t>(Inefficient_Staging_Buffer_Mapped_Memory) + Vertex_Joint_Binding_Buffer_Offset) };

		for (uint32_t Vertex_Index = 0; Vertex_Index < Vertex_Count; ++Vertex_Index) {
			Mehs_Vertex_Position_Buffer[Vertex_Index].Position = Vector3{
				Vertex_Buffer_Data[Vertex_Index].X,
				Vertex_Buffer_Data[Vertex_Index].Y,
				Vertex_Buffer_Data[Vertex_Index].Z
			};
			Mesh_Vertex_Varying_Enable_Bleding_Buffer[Vertex_Index].Normal = Vector3{
				Vertex_Buffer_Data[Vertex_Index].NX ,
				Vertex_Buffer_Data[Vertex_Index].NY,
				Vertex_Buffer_Data[Vertex_Index].NZ
			};
			Mesh_Vertex_Varying_Enable_Bleding_Buffer[Vertex_Index].Tangent = Vector3{
				Vertex_Buffer_Data[Vertex_Index].TX ,
				Vertex_Buffer_Data[Vertex_Index].TY,
				Vertex_Buffer_Data[Vertex_Index].TZ
			};
			Mesh_Vertex_Varying_Bleding_Buffer[Vertex_Index].TexCoord = Vector2{
				Vertex_Buffer_Data[Vertex_Index].U,
				Vertex_Buffer_Data[Vertex_Index].V
			};
		}

		for (uint32_t Index_Index = 0; Index_Index < Index_Count; ++Index_Index) {
			uint32_t Vertex_Buffer_Index{ Index_Buffer_Data[Index_Index] };
			Mesh_Vertex_Joint_Binding_Buffer[Index_Index].Indices = {
				Joint_Binding_Buffer_Data[Vertex_Buffer_Index].Index0,
				Joint_Binding_Buffer_Data[Vertex_Buffer_Index].Index1,
				Joint_Binding_Buffer_Data[Vertex_Buffer_Index].Index2,
				Joint_Binding_Buffer_Data[Vertex_Buffer_Index].Index3
			};

			float Total_Weight{ Joint_Binding_Buffer_Data[Vertex_Buffer_Index].Weight0 + Joint_Binding_Buffer_Data[Vertex_Buffer_Index].Weight1 + Joint_Binding_Buffer_Data[Vertex_Buffer_Index].Weight2 + Joint_Binding_Buffer_Data[Vertex_Buffer_Index].Weight3 };
			float Inv_Toal_Weight = { 0 == Total_Weight ? 1.f : 1.f / Total_Weight };

			Mesh_Vertex_Joint_Binding_Buffer[Index_Index].Weights = Vector4{
				Joint_Binding_Buffer_Data[Vertex_Buffer_Index].Weight0 * Inv_Toal_Weight,
				Joint_Binding_Buffer_Data[Vertex_Buffer_Index].Weight1 * Inv_Toal_Weight,
				Joint_Binding_Buffer_Data[Vertex_Buffer_Index].Weight2 * Inv_Toal_Weight,
				Joint_Binding_Buffer_Data[Vertex_Buffer_Index].Weight3 * Inv_Toal_Weight
			};
		}

		Ref_Vulkan_RHI->UnMap_Memory(Inefficient_Staging_Buffer_Memory.get());

		Vulkan_Mesh Vulkan_Mesh_Data{};
		Vulkan_Mesh_Data.Enable_Vertex_Blending = true;
		Vulkan_Mesh_Data.Mesh_Vertex_Count = Vertex_Count;
		Vulkan_Mesh_Data.Mesh_Index_Count = Index_Count;

		RHI_Buffer_Create_Info Buffer_Create_Info{};
		{
			Buffer_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		}

		VmaAllocationCreateInfo Allocation_Create_Info{};
		{
			//Allocation_Create_Info.flags = VMA_ALLOCATION_CREATE_MAPPED_BIT;
			Allocation_Create_Info.usage = VMA_MEMORY_USAGE_GPU_ONLY;
		}

		{
			Buffer_Create_Info.Size = Vertex_Position_Buffer_Size;
			Buffer_Create_Info.Usage = RHI_Buffer_Usage_Flag_Bits::RHI_BUFFER_USAGE_TRANSFER_DST_BIT | RHI_Buffer_Usage_Flag_Bits::RHI_BUFFER_USAGE_VERTEX_BUFFER_BIT;

			auto [Vertex_Position_Buffer, Vertex_Position_Allocation] = Ref_Vulkan_RHI->Create_Buffer_VMA(
				Ref_Vulkan_RHI->Get_VMA_Allocator(),
				&Buffer_Create_Info,
				&Allocation_Create_Info,
				nullptr
			);

			Vulkan_Mesh_Data.Mesh_Vertex_Position_Buffer = std::move(Vertex_Position_Buffer);
			Vulkan_Mesh_Data.Mesh_Vertex_Position_Allocation = std::move(Vertex_Position_Allocation);

			Ref_Vulkan_RHI->Copy_Buffer(
				Inefficient_Staging_Buffer.get(),
				Vulkan_Mesh_Data.Mesh_Vertex_Position_Buffer.get(),
				Vertex_Position_Buffer_Offset,
				0,
				Vertex_Position_Buffer_Size
			);
		}

		{
			Buffer_Create_Info.Size = Vertex_Varying_Enable_Bleding_Buffer_Size;
			Buffer_Create_Info.Usage = RHI_Buffer_Usage_Flag_Bits::RHI_BUFFER_USAGE_TRANSFER_DST_BIT | RHI_Buffer_Usage_Flag_Bits::RHI_BUFFER_USAGE_VERTEX_BUFFER_BIT;

			auto [Vertex_Varying_Enable_Bleding_Buffer, Vertex_Varying_Enable_Bleding_Allocation] = Ref_Vulkan_RHI->Create_Buffer_VMA(
				Ref_Vulkan_RHI->Get_VMA_Allocator(),
				&Buffer_Create_Info,
				&Allocation_Create_Info,
				nullptr
			);

			Vulkan_Mesh_Data.Mesh_Vertex_Varying_Enable_Blending_Buffer = std::move(Vertex_Varying_Enable_Bleding_Buffer);
			Vulkan_Mesh_Data.Mesh_Vertex_Varying_Enable_Blending_Allocation = std::move(Vertex_Varying_Enable_Bleding_Allocation);

			Ref_Vulkan_RHI->Copy_Buffer(
				Inefficient_Staging_Buffer.get(),
				Vulkan_Mesh_Data.Mesh_Vertex_Varying_Enable_Blending_Buffer.get(),
				Vertex_Varying_Enable_Bleding_Buffer_Offset,
				0,
				Vertex_Varying_Enable_Bleding_Buffer_Size
			);
		}

		{
			Buffer_Create_Info.Size = Vertex_Varying_Buffer_Size;
			Buffer_Create_Info.Usage = RHI_Buffer_Usage_Flag_Bits::RHI_BUFFER_USAGE_TRANSFER_DST_BIT | RHI_Buffer_Usage_Flag_Bits::RHI_BUFFER_USAGE_VERTEX_BUFFER_BIT;

			auto [Vertex_Varying_Buffer, Vertex_Varying_Allocation] = Ref_Vulkan_RHI->Create_Buffer_VMA(
				Ref_Vulkan_RHI->Get_VMA_Allocator(),
				&Buffer_Create_Info,
				&Allocation_Create_Info,
				nullptr
			);
			Vulkan_Mesh_Data.Mesh_Vertex_Varying_Buffer = std::move(Vertex_Varying_Buffer);
			Vulkan_Mesh_Data.Mesh_Vertex_Varying_Allocation = std::move(Vertex_Varying_Allocation);

			Ref_Vulkan_RHI->Copy_Buffer(
				Inefficient_Staging_Buffer.get(),
				Vulkan_Mesh_Data.Mesh_Vertex_Varying_Buffer.get(),
				Vertex_Varying_Bleding_Buffer_Offset,
				0,
				Vertex_Varying_Buffer_Size
			);
		}

		{
			Buffer_Create_Info.Size = Vertex_Joint_Binding_Buffer_Size;
			Buffer_Create_Info.Usage = RHI_Buffer_Usage_Flag_Bits::RHI_BUFFER_USAGE_TRANSFER_DST_BIT | RHI_Buffer_Usage_Flag_Bits::RHI_BUFFER_USAGE_STORAGE_BUFFER_BIT;

			auto [Vertex_Joint_Bleding_Buffer, Vertex_Joint_Bleding_Allocation] = Ref_Vulkan_RHI->Create_Buffer_VMA(
				Ref_Vulkan_RHI->Get_VMA_Allocator(),
				&Buffer_Create_Info,
				&Allocation_Create_Info,
				nullptr
			);

			Vulkan_Mesh_Data.Mesh_Vertex_Joint_Binding_Buffer = std::move(Vertex_Joint_Bleding_Buffer);
			Vulkan_Mesh_Data.Mesh_Vertex_Joint_Binding_Allocation = std::move(Vertex_Joint_Bleding_Allocation);

			Ref_Vulkan_RHI->Copy_Buffer(
				Inefficient_Staging_Buffer.get(),
				Vulkan_Mesh_Data.Mesh_Vertex_Joint_Binding_Buffer.get(),
				Vertex_Joint_Binding_Buffer_Offset,
				0,
				Vertex_Joint_Binding_Buffer_Size
			);
		}

		Inefficient_Staging_Buffer.reset();
		Inefficient_Staging_Buffer_Memory.reset();

		//NOTE : Descriptor Set
		vector<RHI_Descriptor_Set_Layout*> Mesh_Descriptor_Set_Layouts{ this->m_Mesh_Descriptor_Set_Layout.get() };
		RHI_Descriptor_Set_Allocate_Info Mesh_Vertex_Blending_per_Mesh_Descriptor_Set_Allocate_Info{};
		{
			Mesh_Vertex_Blending_per_Mesh_Descriptor_Set_Allocate_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
			Mesh_Vertex_Blending_per_Mesh_Descriptor_Set_Allocate_Info.Descriptor_Pool = Ref_Vulkan_RHI->Get_Default_Descriptor_Pool();
			Mesh_Vertex_Blending_per_Mesh_Descriptor_Set_Allocate_Info.Descriptor_Set_Count = 1;
			Mesh_Vertex_Blending_per_Mesh_Descriptor_Set_Allocate_Info.Set_Layouts = &Mesh_Descriptor_Set_Layouts;
		}

		Vulkan_Mesh_Data.Mesh_Vertex_Blending_Descriptor_Set = std::move(Ref_Vulkan_RHI->Allocate_Descriptor_Sets(&Mesh_Vertex_Blending_per_Mesh_Descriptor_Set_Allocate_Info).front());

		RHI_Descriptor_Buffer_Info Mesh_Vertex_Joint_Binding_Storage_Buffer_Info{};
		{
			Mesh_Vertex_Joint_Binding_Storage_Buffer_Info.Buffer = Vulkan_Mesh_Data.Mesh_Vertex_Joint_Binding_Buffer.get();
			Mesh_Vertex_Joint_Binding_Storage_Buffer_Info.Offset = 0;
			Mesh_Vertex_Joint_Binding_Storage_Buffer_Info.Range = Vertex_Joint_Binding_Buffer_Size;
		}
		vector<const RHI_Descriptor_Buffer_Info*> Mesh_Vertex_Joint_Binding_Storage_Buffer_Infos{ &Mesh_Vertex_Joint_Binding_Storage_Buffer_Info };

		RHI_Write_Descriptor_Set Mesh_Vertex_Joint_Binding_Storage_Buffer_Write{};
		{
			Mesh_Vertex_Joint_Binding_Storage_Buffer_Write.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			Mesh_Vertex_Joint_Binding_Storage_Buffer_Write.Dst_Set = Vulkan_Mesh_Data.Mesh_Vertex_Blending_Descriptor_Set.get();
			Mesh_Vertex_Joint_Binding_Storage_Buffer_Write.Dst_Binding = 0;
			Mesh_Vertex_Joint_Binding_Storage_Buffer_Write.Dst_Array_Element = 0;
			Mesh_Vertex_Joint_Binding_Storage_Buffer_Write.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_STORAGE_BUFFER;
			Mesh_Vertex_Joint_Binding_Storage_Buffer_Write.Buffer_Infos = &Mesh_Vertex_Joint_Binding_Storage_Buffer_Infos;
			Mesh_Vertex_Joint_Binding_Storage_Buffer_Write.Texel_Buffer_Views = nullptr;
		}
		vector<const RHI_Write_Descriptor_Set*> Mesh_Vertex_Joint_Binding_Storage_Buffer_Writes{ &Mesh_Vertex_Joint_Binding_Storage_Buffer_Write };

		RHI->Update_Descriptor_Sets(
			&Mesh_Vertex_Joint_Binding_Storage_Buffer_Writes,
			nullptr
		);

		return Vulkan_Mesh_Data;
	}

	Vulkan_Mesh Render_Resource::Parser_Updata_Vertex_Buffer(shared_ptr<Empty_RHI> RHI, uint32_t Index_Buffer_Size, uint16_t* Index_Buffer_Data, uint32_t Vertex_Buffer_Size, const Mesh_Vertex_Data_Definition* Vertex_Buffer_Data) {
		if (0 != (Vertex_Buffer_Size % sizeof(Mesh_Vertex_Data_Definition)))
			System_Logger::Get_Instance().Log(System_Logger::Level::err, "Vertex_Buffer_Size % sizeof(Mesh_Vertex_Data_Definition) != 0");

		uint32_t Vertex_Count{ Vertex_Buffer_Size / sizeof(Mesh_Vertex_Data_Definition) };


		RHI_Device_Size
			Vertex_Position_Buffer_Size{ sizeof(Mesh_Vertex::Vulkan_Mesh_Vertex_Position) * Vertex_Buffer_Size },
			Vertex_Varying_Enable_Bleding_Buffer_Size{ sizeof(Mesh_Vertex::Vulkan_Mesh_Vertex_Varying_Enable_Blending) * Vertex_Buffer_Size },
			Vertex_Varying_Buffer_Size{ sizeof(Mesh_Vertex::Vulkan_Mesh_Vertex_Varying) * Vertex_Buffer_Size };

		RHI_Device_Size Vertex_Position_Buffer_Offset{ 0 },
			Vertex_Varying_Enable_Bleding_Buffer_Offset{ Vertex_Position_Buffer_Size },
			Vertex_Varying_Bleding_Buffer_Offset{ Vertex_Varying_Enable_Bleding_Buffer_Offset + Vertex_Varying_Enable_Bleding_Buffer_Size };

		RHI_Device_Size Inefficient_Staging_Buffer_Size{ Vertex_Position_Buffer_Size + Vertex_Varying_Enable_Bleding_Buffer_Size + Vertex_Varying_Buffer_Size };

		auto Ref_Vulkan_RHI{ static_cast<Vulkan_RHI*>(RHI.get()) };

		auto [Inefficient_Staging_Buffer, Inefficient_Staging_Buffer_Memory] = RHI->Create_Buffer(
			Inefficient_Staging_Buffer_Size,
			RHI_Buffer_Usage_Flag_Bits::RHI_BUFFER_USAGE_TRANSFER_SRC_BIT,
			RHI_Memory_Property_Flag_Bits::RHI_MEMORY_PROPERTY_HOST_VISIBLE_BIT | RHI_Memory_Property_Flag_Bits::RHI_MEMORY_PROPERTY_HOST_COHERENT_BIT
		);

		void* Inefficient_Staging_Buffer_Mapped_Memory{ nullptr };
		Ref_Vulkan_RHI->Map_Memory(
			Inefficient_Staging_Buffer_Memory.get(),
			0,
			RHI_WHOLE_SIZE,
			0,
			&Inefficient_Staging_Buffer_Mapped_Memory
		);

		Mesh_Vertex::Vulkan_Mesh_Vertex_Position* Mehs_Vertex_Position_Buffer{ reinterpret_cast<Mesh_Vertex::Vulkan_Mesh_Vertex_Position*>(Inefficient_Staging_Buffer_Mapped_Memory) };
		Mesh_Vertex::Vulkan_Mesh_Vertex_Varying_Enable_Blending* Mesh_Vertex_Varying_Enable_Bleding_Buffer{ reinterpret_cast<Mesh_Vertex::Vulkan_Mesh_Vertex_Varying_Enable_Blending*>(reinterpret_cast<uintptr_t>(Inefficient_Staging_Buffer_Mapped_Memory) + Vertex_Varying_Enable_Bleding_Buffer_Offset) };
		Mesh_Vertex::Vulkan_Mesh_Vertex_Varying* Mesh_Vertex_Varying_Bleding_Buffer{ reinterpret_cast<Mesh_Vertex::Vulkan_Mesh_Vertex_Varying*>(reinterpret_cast<uintptr_t>(Inefficient_Staging_Buffer_Mapped_Memory) + Vertex_Varying_Bleding_Buffer_Offset) };

		for (uint32_t Vertex_Index = 0; Vertex_Index < Vertex_Count; ++Vertex_Index) {
			Mehs_Vertex_Position_Buffer[Vertex_Index].Position = Vector3{
				Vertex_Buffer_Data[Vertex_Index].X,
				Vertex_Buffer_Data[Vertex_Index].Y,
				Vertex_Buffer_Data[Vertex_Index].Z
			};
			Mesh_Vertex_Varying_Enable_Bleding_Buffer[Vertex_Index].Normal = Vector3{
				Vertex_Buffer_Data[Vertex_Index].NX ,
				Vertex_Buffer_Data[Vertex_Index].NY,
				Vertex_Buffer_Data[Vertex_Index].NZ
			};
			Mesh_Vertex_Varying_Enable_Bleding_Buffer[Vertex_Index].Tangent = Vector3{
				Vertex_Buffer_Data[Vertex_Index].TX ,
				Vertex_Buffer_Data[Vertex_Index].TY,
				Vertex_Buffer_Data[Vertex_Index].TZ
			};
			Mesh_Vertex_Varying_Bleding_Buffer[Vertex_Index].TexCoord = Vector2{
				Vertex_Buffer_Data[Vertex_Index].U,
				Vertex_Buffer_Data[Vertex_Index].V
			};
		}

		Ref_Vulkan_RHI->UnMap_Memory(Inefficient_Staging_Buffer_Memory.get());

		Vulkan_Mesh Vulkan_Mesh_Data{};
		Vulkan_Mesh_Data.Enable_Vertex_Blending = false;
		Vulkan_Mesh_Data.Mesh_Vertex_Count = Vertex_Count;
		Vulkan_Mesh_Data.Mesh_Index_Count = std::numeric_limits<uint32_t>::max();

		RHI_Buffer_Create_Info Buffer_Create_Info{};
		{
			Buffer_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		}

		VmaAllocationCreateInfo Allocation_Create_Info{};
		{
			//Allocation_Create_Info.flags = VMA_ALLOCATION_CREATE_MAPPED_BIT;
			Allocation_Create_Info.usage = VMA_MEMORY_USAGE_GPU_ONLY;
		}

		{
			Buffer_Create_Info.Size = Vertex_Position_Buffer_Size;
			Buffer_Create_Info.Usage = RHI_Buffer_Usage_Flag_Bits::RHI_BUFFER_USAGE_TRANSFER_DST_BIT | RHI_Buffer_Usage_Flag_Bits::RHI_BUFFER_USAGE_VERTEX_BUFFER_BIT;

			auto [Vertex_Position_Buffer, Vertex_Position_Allocation] = Ref_Vulkan_RHI->Create_Buffer_VMA(
				Ref_Vulkan_RHI->Get_VMA_Allocator(),
				&Buffer_Create_Info,
				&Allocation_Create_Info,
				nullptr
			);

			Vulkan_Mesh_Data.Mesh_Vertex_Position_Buffer = std::move(Vertex_Position_Buffer);
			Vulkan_Mesh_Data.Mesh_Vertex_Position_Allocation = std::move(Vertex_Position_Allocation);

			Ref_Vulkan_RHI->Copy_Buffer(
				Inefficient_Staging_Buffer.get(),
				Vulkan_Mesh_Data.Mesh_Vertex_Position_Buffer.get(),
				Vertex_Position_Buffer_Offset,
				0,
				Vertex_Position_Buffer_Size
			);
		}

		{
			Buffer_Create_Info.Size = Vertex_Varying_Enable_Bleding_Buffer_Size;
			Buffer_Create_Info.Usage = RHI_Buffer_Usage_Flag_Bits::RHI_BUFFER_USAGE_TRANSFER_DST_BIT | RHI_Buffer_Usage_Flag_Bits::RHI_BUFFER_USAGE_VERTEX_BUFFER_BIT;

			auto [Vertex_Varying_Enable_Bleding_Buffer, Vertex_Varying_Enable_Bleding_Allocation] = Ref_Vulkan_RHI->Create_Buffer_VMA(
				Ref_Vulkan_RHI->Get_VMA_Allocator(),
				&Buffer_Create_Info,
				&Allocation_Create_Info,
				nullptr
			);

			Vulkan_Mesh_Data.Mesh_Vertex_Varying_Enable_Blending_Buffer = std::move(Vertex_Varying_Enable_Bleding_Buffer);
			Vulkan_Mesh_Data.Mesh_Vertex_Varying_Enable_Blending_Allocation = std::move(Vertex_Varying_Enable_Bleding_Allocation);

			Ref_Vulkan_RHI->Copy_Buffer(
				Inefficient_Staging_Buffer.get(),
				Vulkan_Mesh_Data.Mesh_Vertex_Varying_Enable_Blending_Buffer.get(),
				Vertex_Varying_Enable_Bleding_Buffer_Offset,
				0,
				Vertex_Varying_Enable_Bleding_Buffer_Size
			);
		}

		{
			Buffer_Create_Info.Size = Vertex_Varying_Buffer_Size;
			Buffer_Create_Info.Usage = RHI_Buffer_Usage_Flag_Bits::RHI_BUFFER_USAGE_TRANSFER_DST_BIT | RHI_Buffer_Usage_Flag_Bits::RHI_BUFFER_USAGE_VERTEX_BUFFER_BIT;

			auto [Vertex_Varying_Buffer, Vertex_Varying_Allocation] = Ref_Vulkan_RHI->Create_Buffer_VMA(
				Ref_Vulkan_RHI->Get_VMA_Allocator(),
				&Buffer_Create_Info,
				&Allocation_Create_Info,
				nullptr
			);
			Vulkan_Mesh_Data.Mesh_Vertex_Varying_Buffer = std::move(Vertex_Varying_Buffer);
			Vulkan_Mesh_Data.Mesh_Vertex_Varying_Allocation = std::move(Vertex_Varying_Allocation);

			Ref_Vulkan_RHI->Copy_Buffer(
				Inefficient_Staging_Buffer.get(),
				Vulkan_Mesh_Data.Mesh_Vertex_Varying_Buffer.get(),
				Vertex_Varying_Bleding_Buffer_Offset,
				0,
				Vertex_Varying_Buffer_Size
			);
		}

		Inefficient_Staging_Buffer.reset();
		Inefficient_Staging_Buffer_Memory.reset();

		//NOTE : Descriptor Set
		vector<RHI_Descriptor_Set_Layout*> Mesh_Descriptor_Set_Layouts{ this->m_Mesh_Descriptor_Set_Layout.get() };
		RHI_Descriptor_Set_Allocate_Info Mesh_Vertex_Blending_per_Mesh_Descriptor_Set_Allocate_Info{};
		{
			Mesh_Vertex_Blending_per_Mesh_Descriptor_Set_Allocate_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
			Mesh_Vertex_Blending_per_Mesh_Descriptor_Set_Allocate_Info.Descriptor_Pool = Ref_Vulkan_RHI->Get_Default_Descriptor_Pool();
			Mesh_Vertex_Blending_per_Mesh_Descriptor_Set_Allocate_Info.Descriptor_Set_Count = 1;
			Mesh_Vertex_Blending_per_Mesh_Descriptor_Set_Allocate_Info.Set_Layouts = &Mesh_Descriptor_Set_Layouts;
		}

		Vulkan_Mesh_Data.Mesh_Vertex_Blending_Descriptor_Set = std::move(Ref_Vulkan_RHI->Allocate_Descriptor_Sets(&Mesh_Vertex_Blending_per_Mesh_Descriptor_Set_Allocate_Info).front());

		RHI_Descriptor_Buffer_Info Mesh_Vertex_Joint_Binding_Storage_Buffer_Info{};
		{
			Mesh_Vertex_Joint_Binding_Storage_Buffer_Info.Buffer = this->m_Global_Render_Resource.Storage_Buffer.Global_Null_Descriptor_Storage_Buffer.get();
			Mesh_Vertex_Joint_Binding_Storage_Buffer_Info.Offset = 0;
			Mesh_Vertex_Joint_Binding_Storage_Buffer_Info.Range = 1;
		}
		vector<const RHI_Descriptor_Buffer_Info*> Mesh_Vertex_Joint_Binding_Storage_Buffer_Infos{ &Mesh_Vertex_Joint_Binding_Storage_Buffer_Info };

		RHI_Write_Descriptor_Set Mesh_Vertex_Joint_Binding_Storage_Buffer_Write{};
		{
			Mesh_Vertex_Joint_Binding_Storage_Buffer_Write.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			Mesh_Vertex_Joint_Binding_Storage_Buffer_Write.Dst_Set = Vulkan_Mesh_Data.Mesh_Vertex_Blending_Descriptor_Set.get();
			Mesh_Vertex_Joint_Binding_Storage_Buffer_Write.Dst_Binding = 0;
			Mesh_Vertex_Joint_Binding_Storage_Buffer_Write.Dst_Array_Element = 0;
			Mesh_Vertex_Joint_Binding_Storage_Buffer_Write.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_STORAGE_BUFFER;
			Mesh_Vertex_Joint_Binding_Storage_Buffer_Write.Buffer_Infos = &Mesh_Vertex_Joint_Binding_Storage_Buffer_Infos;
			Mesh_Vertex_Joint_Binding_Storage_Buffer_Write.Texel_Buffer_Views = nullptr;
		}
		vector<const RHI_Write_Descriptor_Set*> Mesh_Vertex_Joint_Binding_Storage_Buffer_Writes{ &Mesh_Vertex_Joint_Binding_Storage_Buffer_Write };

		RHI->Update_Descriptor_Sets(
			&Mesh_Vertex_Joint_Binding_Storage_Buffer_Writes,
			nullptr
		);

		return Vulkan_Mesh_Data;
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