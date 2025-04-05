#include "render/render_system/Render_Resource.h"

#include<tuple>
#include<cmath>
#include<utility>

#include "logger/System_Logger.h"

#include "math/Constant.h"

#include "global/Global_Rendering.h"
#include "meta/generated/reflection/Global_Rendering.Generated_Reflection.h"

#include "render/rhi/vulkan/Vulkan_RHI.h"

#include "render/render_system/Render_Scene.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System {

	using NameSpace_Core::NameSpace_Logger::System_Logger;

	using NameSpace_Core::NameSpace_Math::Math_PI;

	using NameSpace_Resource::NameSpace_Global::SkyBox_Irradiance_Map;
	using NameSpace_Resource::NameSpace_Global::SkyBox_Specular_Map;
	using NameSpace_Resource::NameSpace_Global::Global_Rendering;

	using NameSpace_Resource::NameSpace_Global::Reflection_SkyBox_Irradiance_Map_Operator;
	using NameSpace_Resource::NameSpace_Global::Reflection_SkyBox_Specular_Map_Operator;
	using NameSpace_Resource::NameSpace_Global::Reflection_Global_Rendering_Operator;

	using NameSpace_RHI::RHI_Device_Size;

	using NameSpace_RHI::RHI_BUFFER_USAGE_FLAG_BITS;
	using NameSpace_RHI::RHI_MEMORY_PROPERTY_FLAG_BITS;

	using NameSpace_RHI::RHI_FILTER;
	using NameSpace_RHI::RHI_SAMPLER_ADDRESS_MODE;
	using NameSpace_RHI::RHI_COMPARE_OP;
	using NameSpace_RHI::RHI_BORDER_COLOR;
	using NameSpace_RHI::RHI_SAMPLER_MIPMAP_MODE;

	using NameSpace_RHI::RHI_DESCRIPTOR_TYPE;
	using NameSpace_RHI::RHI_IMAGE_LAYOUT;

	using NameSpace_RHI::RHI_STRUCT_TYPE;


	using NameSpace_RHI::RHI_Physical_Device_Properties;
	using NameSpace_RHI::RHI_Sampler_Create_Info;
	using NameSpace_RHI::RHI_Buffer_Create_Info;
	using NameSpace_RHI::RHI_Descriptor_Set_Allocate_Info;
	using NameSpace_RHI::RHI_Descriptor_Buffer_Info;
	using NameSpace_RHI::RHI_Descriptor_Image_Info;
	using NameSpace_RHI::NameSpace_Vulkan_RHI::Vulkan_RHI;

	using NameSpace_RHI::RHI_Write_Descriptor_Set;

	void Render_Resource::Create_Storge_Buffer(shared_ptr<Empty_RHI> RHI) {
		auto Ref_Vulkan_RHI{ static_cast<Vulkan_RHI*>(RHI.get()) };

		auto PhySical_Device_ProPerties{ Ref_Vulkan_RHI->Get_Physical_Device_Properties() };

		//NOTE : Global_Upload Storage Buffer
		auto& Ref_Stroage_Buffer{ this->m_Global_Render_Resource.Storage_Buffer };

		Ref_Stroage_Buffer.Min_Uniform_Buffer_Offset_Alignment = static_cast<uint32_t>(PhySical_Device_ProPerties.Limits.minUniformBufferOffsetAlignment);
		Ref_Stroage_Buffer.Min_Storage_Buffer_Offset_Alignment = static_cast<uint32_t>(PhySical_Device_ProPerties.Limits.minStorageBufferOffsetAlignment);
		//Ref_Stroage_Buffer.Max_Storage_Buffer_Range = static_cast<uint32_t>(PhySical_Device_ProPerties.Limits.maxStorageBufferRange);
		Ref_Stroage_Buffer.Non_Coherent_Atom_Size = static_cast<uint32_t>(PhySical_Device_ProPerties.Limits.nonCoherentAtomSize);

		std::tie(Ref_Stroage_Buffer.Global_Upload_Ring_Buffer, Ref_Stroage_Buffer.Global_Upload_Ring_Buffer_Memory) = Ref_Vulkan_RHI->Create_Buffer(
			1024 * 1024 * 128,//Ref_Stroage_Buffer.Max_Storage_Buffer_Range,//Do NOTE : Set Max Size
			to_underlying(RHI_BUFFER_USAGE_FLAG_BITS::RHI_BUFFER_USAGE_STORAGE_BUFFER_BIT),
			RHI_MEMORY_PROPERTY_FLAG_BITS::RHI_MEMORY_PROPERTY_HOST_VISIBLE_BIT | RHI_MEMORY_PROPERTY_FLAG_BITS::RHI_MEMORY_PROPERTY_HOST_COHERENT_BIT
		);

		Ref_Stroage_Buffer.Global_Upload_Ring_Buffers_Begin.resize(Vulkan_RHI::s_Frames_In_Flight);
		Ref_Stroage_Buffer.Global_Upload_Ring_Buffers_End.resize(Vulkan_RHI::s_Frames_In_Flight);
		Ref_Stroage_Buffer.Global_Upload_Ring_Buffers_Size.resize(Vulkan_RHI::s_Frames_In_Flight);
		for (uint32_t Index = 0; Index < Vulkan_RHI::s_Frames_In_Flight; ++Index) {
			Ref_Stroage_Buffer.Global_Upload_Ring_Buffers_Begin[Index] = (Ref_Stroage_Buffer.Max_Storage_Buffer_Range * Index) / Vulkan_RHI::s_Frames_In_Flight;
			Ref_Stroage_Buffer.Global_Upload_Ring_Buffers_End[Index] = (Ref_Stroage_Buffer.Max_Storage_Buffer_Range * (Index + 1)) / Vulkan_RHI::s_Frames_In_Flight;
			Ref_Stroage_Buffer.Global_Upload_Ring_Buffers_Size[Index] = Ref_Stroage_Buffer.Global_Upload_Ring_Buffers_End[Index] - Ref_Stroage_Buffer.Global_Upload_Ring_Buffers_Begin[Index];
		}

		//NOTE :Axis Storage Buffer
		std::tie(Ref_Stroage_Buffer.Axis_Inefficient_Strogae_Buffer, Ref_Stroage_Buffer.Axis_Inefficient_Strogae_Buffer_Memory) = Ref_Vulkan_RHI->Create_Buffer(
			Ref_Stroage_Buffer.Axis_Storage_Buffer_Size,
			to_underlying(RHI_BUFFER_USAGE_FLAG_BITS::RHI_BUFFER_USAGE_STORAGE_BUFFER_BIT),
			RHI_MEMORY_PROPERTY_FLAG_BITS::RHI_MEMORY_PROPERTY_HOST_VISIBLE_BIT | RHI_MEMORY_PROPERTY_FLAG_BITS::RHI_MEMORY_PROPERTY_HOST_COHERENT_BIT
		);

		//NOTE : Null Descriptor Storage Buffer
		std::tie(Ref_Stroage_Buffer.Global_Null_Descriptor_Storage_Buffer, Ref_Stroage_Buffer.Global_Null_Descriptor_Storage_Buffer_Memory) = Ref_Vulkan_RHI->Create_Buffer(
			Ref_Stroage_Buffer.Global_Null_Descriptor_Buffer_Size,
			RHI_BUFFER_USAGE_FLAG_BITS::RHI_BUFFER_USAGE_TRANSFER_SRC_BIT | RHI_BUFFER_USAGE_FLAG_BITS::RHI_BUFFER_USAGE_STORAGE_BUFFER_BIT,
			RHI_MEMORY_PROPERTY_FLAG_BITS::RHI_MEMORY_PROPERTY_HOST_VISIBLE_BIT | RHI_MEMORY_PROPERTY_FLAG_BITS::RHI_MEMORY_PROPERTY_HOST_COHERENT_BIT
		);
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
			Sampler_Create_Info.Max_Lod = RHI_WHOLE_SIZE;
			Sampler_Create_Info.Border_Color = RHI_BORDER_COLOR::RHI_BORDER_COLOR_FLOAT_OPAQUE_BLACK;
			Sampler_Create_Info.Unnormalized_Coordinates = RHI_FALSE;
		}

		auto& Ref_IBL_Resource{ this->m_Global_Render_Resource.IBL_Resource };

		if (RHI_NULL_HANDLE != Ref_IBL_Resource.BUDF_LUT_Sampler)
			System_Logger::Get_Instance().Log(System_Logger::Level::err, "BUDF_LUT_Texture_Sampler Already Created, Doing ReCreate");
		Ref_IBL_Resource.BUDF_LUT_Sampler = Ref_Vulkan_RHI->Create_Sampler(&Sampler_Create_Info);


		Sampler_Create_Info.Max_Lod = 8.f; //RHI_WHOLE_SIZE;
		if (RHI_NULL_HANDLE != Ref_IBL_Resource.Irradiance_Map_Sampler)
			System_Logger::Get_Instance().Log(System_Logger::Level::err, "Irradiance_Map_Texture_Sampler Already Created, Doing ReCreate");
		Ref_IBL_Resource.Irradiance_Map_Sampler = Ref_Vulkan_RHI->Create_Sampler(&Sampler_Create_Info);

		if (RHI_NULL_HANDLE != Ref_IBL_Resource.Specular_Map_Sampler)
			System_Logger::Get_Instance().Log(System_Logger::Level::err, "Specular_Map_Texture_Sampler Already Created, Doing ReCreate");
		Ref_IBL_Resource.Specular_Map_Sampler = Ref_Vulkan_RHI->Create_Sampler(&Sampler_Create_Info);
	}

	void Render_Resource::Create_IBL_Textures(shared_ptr<Empty_RHI> RHI, array<shared_ptr<Texture_Data>, 6> Irradiance_Maps, array<shared_ptr<Texture_Data>, 6> Specular_Maps) {
		auto Ref_Vulkan_RHI{ static_cast<Vulkan_RHI*>(RHI.get()) };
		auto& Ref_IBL_Resource{ this->m_Global_Render_Resource.IBL_Resource };

		const uint32_t Irradiance_Mip_Levels{ static_cast<uint32_t>(std::floor(log2(std::max(Irradiance_Maps[0]->Width, Irradiance_Maps[0]->Height)))) + 1 };

		std::tie(Ref_IBL_Resource.Irradiance_Map_Image, Ref_IBL_Resource.Irradiance_Map_Image_View, Ref_IBL_Resource.Irradiance_Map_Image_Allocation) = Ref_Vulkan_RHI->Create_Cube_Map(
			{ Irradiance_Maps[0]->Width, Irradiance_Maps[0]->Height },
			Irradiance_Maps[0]->Format,
			Irradiance_Mip_Levels,
			{ Irradiance_Maps[0]->Pixels.get(), Irradiance_Maps[1]->Pixels.get(), Irradiance_Maps[2]->Pixels.get(), Irradiance_Maps[3]->Pixels.get(), Irradiance_Maps[4]->Pixels.get(), Irradiance_Maps[5]->Pixels.get() }
		);

		const uint32_t Specular_Mip_Levels{ static_cast<uint32_t>(std::floor(log2(std::max(Specular_Maps[0]->Width, Specular_Maps[0]->Height)))) + 1 };

		std::tie(Ref_IBL_Resource.Specular_Map_Image, Ref_IBL_Resource.Specular_Map_Image_View, Ref_IBL_Resource.Specular_Map_Image_Allocation) = Ref_Vulkan_RHI->Create_Cube_Map(
			{ Specular_Maps[0]->Width, Specular_Maps[0]->Height },
			Specular_Maps[0]->Format,
			Specular_Mip_Levels,
			{ Specular_Maps[0]->Pixels.get(), Specular_Maps[1]->Pixels.get(), Specular_Maps[2]->Pixels.get(), Specular_Maps[3]->Pixels.get(), Specular_Maps[4]->Pixels.get(), Specular_Maps[5]->Pixels.get() }
		);

	}

	const Vulkan_Mesh& Render_Resource::Get_OR_Create_Vulkan_Mesh(shared_ptr<Empty_RHI> RHI, const Render_Entity& Render_Entity, const Render_Mesh_Data& Mesh_Data) {
		auto cIt{ this->m_Vulkan_Mesh_Map.find(Render_Entity.Mesh_Resource_ID) };
		if (this->m_Vulkan_Mesh_Map.end() != cIt)
			return cIt->second;

		uint32_t Index_Buffer_size{ static_cast<uint32_t>(Mesh_Data.Static_Mesh_Data.Index_Buffer->Data_Size) };
		void* Index_Buffer_Data{ Mesh_Data.Static_Mesh_Data.Index_Buffer->Data };

		uint32_t Vertex_Buffer_Size{ static_cast<uint32_t>(Mesh_Data.Static_Mesh_Data.Vertex_Buffer->Data_Size) };

		Mesh_Vertex_Data_Definition* Vertex_Buffer_Data{ reinterpret_cast<Mesh_Vertex_Data_Definition*>(Mesh_Data.Static_Mesh_Data.Vertex_Buffer->Data) };

		if (nullptr == Mesh_Data.Skeletion_Binding_Buffer)
			return this->m_Vulkan_Mesh_Map[Render_Entity.Mesh_Resource_ID] = this->Load_Mesh_Buffer(
				RHI,
				Index_Buffer_size,
				reinterpret_cast<uint16_t*>(Index_Buffer_Data),
				Vertex_Buffer_Size,
				Vertex_Buffer_Data
			);

		uint32_t Joint_Binding_Buffer_Size{ static_cast<uint32_t>(Mesh_Data.Skeletion_Binding_Buffer->Data_Size) };
		Mesh_Vertx_Binding_Data_Definition* Joint_Binding_Buffer_Data{ reinterpret_cast<Mesh_Vertx_Binding_Data_Definition*>(Mesh_Data.Skeletion_Binding_Buffer->Data) };

		return this->m_Vulkan_Mesh_Map[Render_Entity.Mesh_Resource_ID] = this->Load_Mesh_Binding_Buffer(
			RHI,
			Index_Buffer_size,
			reinterpret_cast<uint16_t*>(Index_Buffer_Data),
			Vertex_Buffer_Size,
			Vertex_Buffer_Data,
			Joint_Binding_Buffer_Size,
			Joint_Binding_Buffer_Data
		);
	}

	const Vulkan_PBR_Material& Render_Resource::Get_OR_Create_Vulkan_Material(shared_ptr<Empty_RHI> RHI, const Render_Entity& Render_Entity, const Render_Material_Data& Mesh_Data) {
		auto cIt{ this->m_Vulkan_PBR_Material_Map.find(Render_Entity.Material_Resource_ID) };
		if (this->m_Vulkan_PBR_Material_Map.end() != cIt)
			return cIt->second;

		auto Ref_Vulkan_RHI{ static_cast<Vulkan_RHI*>(RHI.get()) };

		//NOTE : Image
		Vulkan_PBR_Texture_Data_Info Texture_Data_Info{};
		{
			{
				Texture_Data_Info.Base_Color_Image_Width = Mesh_Data.Base_Color_Texture->Width;
				Texture_Data_Info.Base_Color_Image_Height = Mesh_Data.Base_Color_Texture->Height;
				Texture_Data_Info.Base_Color_Image_Format = Mesh_Data.Base_Color_Texture->Format;
				Texture_Data_Info.Base_Color_Image_Pixels = Mesh_Data.Base_Color_Texture->Pixels.get();
			}

			{
				Texture_Data_Info.Metallic_Roughness_Image_Width = Mesh_Data.Metallic_Roughness_Texture->Width;
				Texture_Data_Info.Metallic_Roughness_Image_Height = Mesh_Data.Metallic_Roughness_Texture->Height;
				Texture_Data_Info.Metallic_Roughness_Image_Format = Mesh_Data.Metallic_Roughness_Texture->Format;
				Texture_Data_Info.Metallic_Roughness_Image_Pixels = Mesh_Data.Metallic_Roughness_Texture->Pixels.get();
			}

			{
				Texture_Data_Info.Normal_Image_Width = Mesh_Data.Normal_Texture->Width;
				Texture_Data_Info.Normal_Image_Height = Mesh_Data.Normal_Texture->Height;
				Texture_Data_Info.Normal_Image_Format = Mesh_Data.Normal_Texture->Format;
				Texture_Data_Info.Normal_Image_Pixels = Mesh_Data.Normal_Texture->Pixels.get();
			}

			{
				Texture_Data_Info.Occlusion_Image_Width = Mesh_Data.Occlusion_Texture->Width;
				Texture_Data_Info.Occlusion_Image_Height = Mesh_Data.Occlusion_Texture->Height;
				Texture_Data_Info.Occlusion_Image_Format = Mesh_Data.Occlusion_Texture->Format;
				Texture_Data_Info.Occlusion_Image_Pixels = Mesh_Data.Occlusion_Texture->Pixels.get();
			}

			{
				Texture_Data_Info.Emissive_Image_Width = Mesh_Data.Emissive_Texture->Width;
				Texture_Data_Info.Emissive_Image_Height = Mesh_Data.Emissive_Texture->Height;
				Texture_Data_Info.Emissive_Image_Format = Mesh_Data.Emissive_Texture->Format;
				Texture_Data_Info.Emissive_Image_Pixels = Mesh_Data.Emissive_Texture->Pixels.get();
			}
		}

		Vulkan_PBR_Material Material = this->Load_PBR_Material_Image(
			RHI,
			Texture_Data_Info
		);

		//NOTE : Create Material Uniform Buffer
		{
			RHI_Device_Size Uniform_Buffer_size{ sizeof(Mesh_Per_Material_Uniform_Buffer_Object) };
			auto [Inefficient_Buffer, Inefficient_Buffer_Memory] = RHI->Create_Buffer(
				Uniform_Buffer_size,
				to_underlying(RHI_BUFFER_USAGE_FLAG_BITS::RHI_BUFFER_USAGE_UNIFORM_BUFFER_BIT),
				RHI_MEMORY_PROPERTY_FLAG_BITS::RHI_MEMORY_PROPERTY_HOST_VISIBLE_BIT | RHI_MEMORY_PROPERTY_FLAG_BITS::RHI_MEMORY_PROPERTY_HOST_COHERENT_BIT
			);

			void* Inefficient_Buffer_Mapped_Memory{ nullptr };
			Ref_Vulkan_RHI->Map_Memory(
				Inefficient_Buffer_Memory.get(),
				0,
				RHI_WHOLE_SIZE,
				0,
				&Inefficient_Buffer_Mapped_Memory
			);

			Mesh_Per_Material_Uniform_Buffer_Object* Uniform_Buffer_Object{ reinterpret_cast<Mesh_Per_Material_Uniform_Buffer_Object*>(Inefficient_Buffer_Mapped_Memory) };
			{
				Uniform_Buffer_Object->Base_Color_Factor = Render_Entity.Base_Color_Factor;
				Uniform_Buffer_Object->Metallic_Factor = Render_Entity.Metallic_Factor;
				Uniform_Buffer_Object->Roughness_Factor = Render_Entity.Roughness_Factor;
				Uniform_Buffer_Object->Normal_Scale = Render_Entity.Normal_Scale;
				Uniform_Buffer_Object->Occlusion_Strength = Render_Entity.Occlusion_Strength;
				Uniform_Buffer_Object->Emissive_Factor = Render_Entity.Emissive_Factor;
				Uniform_Buffer_Object->Is_Blend = Render_Entity.Is_Blend;
				Uniform_Buffer_Object->Is_Double_Sided = Render_Entity.Is_Double_Sided;
			}

			Ref_Vulkan_RHI->UnMap_Memory(Inefficient_Buffer_Memory.get());

			RHI_Buffer_Create_Info Buffer_Create_Info{};
			{
				Buffer_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
				Buffer_Create_Info.Size = Uniform_Buffer_size;
				Buffer_Create_Info.Usage = to_underlying(RHI_BUFFER_USAGE_FLAG_BITS::RHI_BUFFER_USAGE_UNIFORM_BUFFER_BIT);
			}

			VmaAllocationCreateInfo Allocation_Create_Info{};
			{
				Allocation_Create_Info.flags = 0;
				Allocation_Create_Info.usage = VMA_MEMORY_USAGE_CPU_TO_GPU;
			}

			std::tie(Material.Material_Uniform_Buffer, Material.Material_Uniform_Buffer_Allocation) = Ref_Vulkan_RHI->Create_Buffer_Alignment_VMA(
				&Buffer_Create_Info,
				&Allocation_Create_Info,
				nullptr,
				this->m_Global_Render_Resource.Storage_Buffer.Min_Uniform_Buffer_Offset_Alignment
			);

			Ref_Vulkan_RHI->Copy_Buffer(
				Inefficient_Buffer.get(),
				Material.Material_Uniform_Buffer.get(),
				0,
				0,
				Uniform_Buffer_size
			);

			Inefficient_Buffer.reset();
			Inefficient_Buffer_Memory.reset();
		}

		//NOTE : Descriptor_Set
		vector<RHI_Descriptor_Set_Layout*> Descriptor_Set_Layouts{
			this->m_Material_Descriptor_Set_Layout
		};

		RHI_Descriptor_Set_Allocate_Info Descriptor_Set_Allocate_Info{};
		{
			Descriptor_Set_Allocate_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
			Descriptor_Set_Allocate_Info.Descriptor_Pool = Ref_Vulkan_RHI->Get_Default_Descriptor_Pool();
			Descriptor_Set_Allocate_Info.Set_Layouts = &Descriptor_Set_Layouts;
		}

		Material.Material_Descriptor_Set = std::move(Ref_Vulkan_RHI->Allocate_Descriptor_Sets(&Descriptor_Set_Allocate_Info).front());

		//NOTE : Write Descriptor Set
		{
			RHI_Descriptor_Buffer_Info Material_Uniform_Buffer_Descriptor_Info{};
			{
				Material_Uniform_Buffer_Descriptor_Info.Buffer = Material.Material_Uniform_Buffer.get();
				Material_Uniform_Buffer_Descriptor_Info.Offset = 0;
				Material_Uniform_Buffer_Descriptor_Info.Range = sizeof(Mesh_Per_Material_Uniform_Buffer_Object);
			}

			RHI_Descriptor_Image_Info Base_Color_Image_Descriptor_Info{};
			{
				Base_Color_Image_Descriptor_Info.Sampler = Ref_Vulkan_RHI->Get_Mipmap_Sampler(Mesh_Data.Base_Color_Texture->Mip_Levels);
				Base_Color_Image_Descriptor_Info.Image_View = Material.Base_Color_Image_View.get();
				Base_Color_Image_Descriptor_Info.Image_Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			}

			RHI_Descriptor_Image_Info Metallic_Roughness_Image_Descriptor_Info{};
			{
				Metallic_Roughness_Image_Descriptor_Info.Sampler = Ref_Vulkan_RHI->Get_Mipmap_Sampler(Mesh_Data.Metallic_Roughness_Texture->Mip_Levels);
				Metallic_Roughness_Image_Descriptor_Info.Image_View = Material.Metallic_Roughness_Image_View.get();
				Metallic_Roughness_Image_Descriptor_Info.Image_Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			}

			RHI_Descriptor_Image_Info Normal_Image_Descriptor_Info{};
			{
				Normal_Image_Descriptor_Info.Sampler = Ref_Vulkan_RHI->Get_Mipmap_Sampler(Mesh_Data.Normal_Texture->Mip_Levels);
				Normal_Image_Descriptor_Info.Image_View = Material.Normal_Image_View.get();
				Normal_Image_Descriptor_Info.Image_Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			}

			RHI_Descriptor_Image_Info Occlusion_Image_Descriptor_Info{};
			{
				Occlusion_Image_Descriptor_Info.Sampler = Ref_Vulkan_RHI->Get_Mipmap_Sampler(Mesh_Data.Occlusion_Texture->Mip_Levels);
				Occlusion_Image_Descriptor_Info.Image_View = Material.Occlusion_Image_View.get();
				Occlusion_Image_Descriptor_Info.Image_Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			}

			RHI_Descriptor_Image_Info Emissive_Image_Descriptor_Info{};
			{
				Emissive_Image_Descriptor_Info.Sampler = Ref_Vulkan_RHI->Get_Mipmap_Sampler(Mesh_Data.Emissive_Texture->Mip_Levels);
				Emissive_Image_Descriptor_Info.Image_View = Material.Emissive_Image_View.get();
				Emissive_Image_Descriptor_Info.Image_Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			}

			vector<const RHI_Descriptor_Buffer_Info*> Material_Uniform_Buffer_Descriptor_Infos{ &Material_Uniform_Buffer_Descriptor_Info };
			RHI_Write_Descriptor_Set Material_Uniform_Buffer_Write_Descriptor_Set{};
			{
				Material_Uniform_Buffer_Write_Descriptor_Set.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
				Material_Uniform_Buffer_Write_Descriptor_Set.Dst_Set = Material.Material_Descriptor_Set.get();
				Material_Uniform_Buffer_Write_Descriptor_Set.Dst_Binding = 0;
				Material_Uniform_Buffer_Write_Descriptor_Set.Dst_Array_Element = 0;
				Material_Uniform_Buffer_Write_Descriptor_Set.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
				Material_Uniform_Buffer_Write_Descriptor_Set.Buffer_Infos = &Material_Uniform_Buffer_Descriptor_Infos;
			}

			vector<const RHI_Descriptor_Image_Info*> Base_Color_Image_Descriptor_Infos{ &Base_Color_Image_Descriptor_Info };
			RHI_Write_Descriptor_Set Base_Color_Image_Write_Descriptor_Set{};
			{
				Base_Color_Image_Write_Descriptor_Set.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
				Base_Color_Image_Write_Descriptor_Set.Dst_Set = Material.Material_Descriptor_Set.get();
				Base_Color_Image_Write_Descriptor_Set.Dst_Binding = 1;
				Base_Color_Image_Write_Descriptor_Set.Dst_Array_Element = 0;
				Base_Color_Image_Write_Descriptor_Set.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
				Base_Color_Image_Write_Descriptor_Set.Image_Infos = &Base_Color_Image_Descriptor_Infos;
			}

			vector<const RHI_Descriptor_Image_Info*> Metallic_Roughness_Image_Descriptor_Infos{ &Metallic_Roughness_Image_Descriptor_Info };
			RHI_Write_Descriptor_Set Metallic_Roughness_Image_Write_Descriptor_Set{};
			{
				Metallic_Roughness_Image_Write_Descriptor_Set.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
				Metallic_Roughness_Image_Write_Descriptor_Set.Dst_Set = Material.Material_Descriptor_Set.get();
				Metallic_Roughness_Image_Write_Descriptor_Set.Dst_Binding = 2;
				Metallic_Roughness_Image_Write_Descriptor_Set.Dst_Array_Element = 0;
				Metallic_Roughness_Image_Write_Descriptor_Set.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
				Metallic_Roughness_Image_Write_Descriptor_Set.Image_Infos = &Metallic_Roughness_Image_Descriptor_Infos;
			}

			vector<const RHI_Descriptor_Image_Info*> Normal_Image_Descriptor_Infos{ &Normal_Image_Descriptor_Info };
			RHI_Write_Descriptor_Set Normal_Image_Write_Descriptor_Set{};
			{
				Normal_Image_Write_Descriptor_Set.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
				Normal_Image_Write_Descriptor_Set.Dst_Set = Material.Material_Descriptor_Set.get();
				Normal_Image_Write_Descriptor_Set.Dst_Binding = 3;
				Normal_Image_Write_Descriptor_Set.Dst_Array_Element = 0;
				Normal_Image_Write_Descriptor_Set.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
				Normal_Image_Write_Descriptor_Set.Image_Infos = &Normal_Image_Descriptor_Infos;
			}

			vector<const RHI_Descriptor_Image_Info*> Occlusion_Image_Descriptor_Infos{ &Occlusion_Image_Descriptor_Info };
			RHI_Write_Descriptor_Set Occlusion_Image_Write_Descriptor_Set{};
			{
				Occlusion_Image_Write_Descriptor_Set.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
				Occlusion_Image_Write_Descriptor_Set.Dst_Set = Material.Material_Descriptor_Set.get();
				Occlusion_Image_Write_Descriptor_Set.Dst_Binding = 4;
				Occlusion_Image_Write_Descriptor_Set.Dst_Array_Element = 0;
				Occlusion_Image_Write_Descriptor_Set.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
				Occlusion_Image_Write_Descriptor_Set.Image_Infos = &Occlusion_Image_Descriptor_Infos;
			}

			vector<const RHI_Descriptor_Image_Info*> Emissive_Image_Descriptor_Infos{ &Emissive_Image_Descriptor_Info };
			RHI_Write_Descriptor_Set Emissive_Image_Write_Descriptor_Set{};
			{
				Emissive_Image_Write_Descriptor_Set.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
				Emissive_Image_Write_Descriptor_Set.Dst_Set = Material.Material_Descriptor_Set.get();
				Emissive_Image_Write_Descriptor_Set.Dst_Binding = 5;
				Emissive_Image_Write_Descriptor_Set.Dst_Array_Element = 0;
				Emissive_Image_Write_Descriptor_Set.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
				Emissive_Image_Write_Descriptor_Set.Image_Infos = &Emissive_Image_Descriptor_Infos;
			}

			vector<const RHI_Write_Descriptor_Set*> Write_Descriptor_Sets{
				&Material_Uniform_Buffer_Write_Descriptor_Set,
				&Base_Color_Image_Write_Descriptor_Set,
				&Metallic_Roughness_Image_Write_Descriptor_Set,
				&Normal_Image_Write_Descriptor_Set,
				&Occlusion_Image_Write_Descriptor_Set,
				&Emissive_Image_Write_Descriptor_Set
			};

			Ref_Vulkan_RHI->Update_Descriptor_Sets(&Write_Descriptor_Sets, nullptr);
		}

		return this->m_Vulkan_PBR_Material_Map[Render_Entity.Material_Resource_ID] = std::move(Material);
	}

	void Render_Resource::Reset_Ring_Buffer_Offset(uint32_t Current_Frame_Index) {
		this->m_Global_Render_Resource.Storage_Buffer.Global_Upload_Ring_Buffers_End[Current_Frame_Index] = this->m_Global_Render_Resource.Storage_Buffer.Global_Upload_Ring_Buffers_Begin[Current_Frame_Index];
	}

	const Vulkan_Mesh& Render_Resource::Get_Entity_Mesh(const Render_Entity& Entity) const {
		auto cIt{ this->m_Vulkan_Mesh_Map.find(Entity.Mesh_Resource_ID) };
		if (this->m_Vulkan_Mesh_Map.end() == cIt)
			System_Logger::Get_Instance().Log(System_Logger::Level::err, "Entity Mesh Not Found");

		return cIt->second;
	}

	const Vulkan_PBR_Material& Render_Resource::Get_Entity_Material(const Render_Entity& Entity) const {
		auto cIt{ this->m_Vulkan_PBR_Material_Map.find(Entity.Material_Resource_ID) };
		if (this->m_Vulkan_PBR_Material_Map.end() == cIt)
			System_Logger::Get_Instance().Log(System_Logger::Level::err, "Entity Material Not Found");

		return cIt->second;
	}

	Vulkan_Mesh Render_Resource::Load_Mesh_Binding_Buffer(shared_ptr<Empty_RHI> RHI, uint32_t Index_Buffer_Size, uint16_t* Index_Buffer_Data, uint32_t Vertex_Buffer_Size, const Mesh_Vertex_Data_Definition* Vertex_Buffer_Data, uint32_t Joint_Binding_Buffer_Size, const Mesh_Vertx_Binding_Data_Definition* Joint_Binding_Buffer_Data) {
		if (0 != (Vertex_Buffer_Size % sizeof(Mesh_Vertex_Data_Definition)))
			System_Logger::Get_Instance().Log(System_Logger::Level::err, "Vertex_Buffer_Size % sizeof(Mesh_Vertex_Data_Definition) != 0");


		if (0 != (Index_Buffer_Size % sizeof(uint16_t)))
			System_Logger::Get_Instance().Log(System_Logger::Level::err, "Joint_Binding_Buffer_Size % sizeof(uint16_t) != 0");

		uint32_t Vertex_Count{ Vertex_Buffer_Size / sizeof(Mesh_Vertex_Data_Definition) };
		uint32_t Index_Count{ Index_Buffer_Size / sizeof(uint16_t) };

		Vulkan_Mesh Vulkan_Mesh_Data{};
		Vulkan_Mesh_Data.Enable_Vertex_Blending = true;
		Vulkan_Mesh_Data.Mesh_Vertex_Count = Vertex_Count;
		Vulkan_Mesh_Data.Mesh_Index_Count = Index_Count;

		auto Ref_Vulkan_RHI{ static_cast<Vulkan_RHI*>(RHI.get()) };

		RHI_Device_Size
			Vertex_Position_Buffer_Size{ sizeof(Mesh_Vertex::Vulkan_Mesh_Vertex_Position) * Vertex_Count },
			Vertex_Varying_Enable_Bleding_Buffer_Size{ sizeof(Mesh_Vertex::Vulkan_Mesh_Vertex_Varying_Enable_Blending) * Vertex_Count },
			Vertex_Varying_Buffer_Size{ sizeof(Mesh_Vertex::Vulkan_Mesh_Vertex_Varying) * Vertex_Count },
			Vertex_Joint_Binding_Buffer_Size{ sizeof(Mesh_Vertex::Vulkan_Mesh_Vertex_Joint_Binding) * Index_Count };//NOTE : Index 

		RHI_Device_Size
			Vertex_Position_Buffer_Offset{ 0 },
			Vertex_Varying_Enable_Bleding_Buffer_Offset{ Vertex_Position_Buffer_Size },
			Vertex_Varying_Buffer_Offset{ Vertex_Varying_Enable_Bleding_Buffer_Offset + Vertex_Varying_Enable_Bleding_Buffer_Size },
			Vertex_Joint_Binding_Buffer_Offset{ Vertex_Varying_Buffer_Offset + Vertex_Varying_Buffer_Size };

		{
			RHI_Device_Size Inefficient_Staging_Buffer_Size{ Vertex_Position_Buffer_Size + Vertex_Varying_Enable_Bleding_Buffer_Size + Vertex_Varying_Buffer_Size + Vertex_Joint_Binding_Buffer_Size };

			auto [Inefficient_Staging_Buffer, Inefficient_Staging_Buffer_Memory] = RHI->Create_Buffer(
				Inefficient_Staging_Buffer_Size,
				to_underlying(RHI_BUFFER_USAGE_FLAG_BITS::RHI_BUFFER_USAGE_TRANSFER_SRC_BIT),
				RHI_MEMORY_PROPERTY_FLAG_BITS::RHI_MEMORY_PROPERTY_HOST_VISIBLE_BIT | RHI_MEMORY_PROPERTY_FLAG_BITS::RHI_MEMORY_PROPERTY_HOST_COHERENT_BIT
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
			Mesh_Vertex::Vulkan_Mesh_Vertex_Varying* Mesh_Vertex_Varying_Buffer{ reinterpret_cast<Mesh_Vertex::Vulkan_Mesh_Vertex_Varying*>(reinterpret_cast<uintptr_t>(Inefficient_Staging_Buffer_Mapped_Memory) + Vertex_Varying_Buffer_Offset) };
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
				Mesh_Vertex_Varying_Buffer[Vertex_Index].TexCoord = Vector2{
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

				float Total_Weight{
					Joint_Binding_Buffer_Data[Vertex_Buffer_Index].Weight0 +
					Joint_Binding_Buffer_Data[Vertex_Buffer_Index].Weight1 +
					Joint_Binding_Buffer_Data[Vertex_Buffer_Index].Weight2 +
					Joint_Binding_Buffer_Data[Vertex_Buffer_Index].Weight3
				};

				float Inv_Toal_Weight = { 0.f == Total_Weight ? 1.f : 1.f / Total_Weight };

				Mesh_Vertex_Joint_Binding_Buffer[Index_Index].Weights = Vector4{
					Joint_Binding_Buffer_Data[Vertex_Buffer_Index].Weight0 * Inv_Toal_Weight,
					Joint_Binding_Buffer_Data[Vertex_Buffer_Index].Weight1 * Inv_Toal_Weight,
					Joint_Binding_Buffer_Data[Vertex_Buffer_Index].Weight2 * Inv_Toal_Weight,
					Joint_Binding_Buffer_Data[Vertex_Buffer_Index].Weight3 * Inv_Toal_Weight
				};
			}

			Ref_Vulkan_RHI->UnMap_Memory(Inefficient_Staging_Buffer_Memory.get());

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
				Buffer_Create_Info.Usage = RHI_BUFFER_USAGE_FLAG_BITS::RHI_BUFFER_USAGE_TRANSFER_DST_BIT | RHI_BUFFER_USAGE_FLAG_BITS::RHI_BUFFER_USAGE_VERTEX_BUFFER_BIT;

				std::tie(Vulkan_Mesh_Data.Mesh_Vertex_Position_Buffer, Vulkan_Mesh_Data.Mesh_Vertex_Position_Allocation) = Ref_Vulkan_RHI->Create_Buffer_VMA(
					&Buffer_Create_Info,
					&Allocation_Create_Info,
					nullptr
				);

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
				Buffer_Create_Info.Usage = RHI_BUFFER_USAGE_FLAG_BITS::RHI_BUFFER_USAGE_TRANSFER_DST_BIT | RHI_BUFFER_USAGE_FLAG_BITS::RHI_BUFFER_USAGE_VERTEX_BUFFER_BIT;

				std::tie(Vulkan_Mesh_Data.Mesh_Vertex_Varying_Enable_Blending_Buffer, Vulkan_Mesh_Data.Mesh_Vertex_Varying_Enable_Blending_Allocation) = Ref_Vulkan_RHI->Create_Buffer_VMA(
					&Buffer_Create_Info,
					&Allocation_Create_Info,
					nullptr
				);

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
				Buffer_Create_Info.Usage = RHI_BUFFER_USAGE_FLAG_BITS::RHI_BUFFER_USAGE_TRANSFER_DST_BIT | RHI_BUFFER_USAGE_FLAG_BITS::RHI_BUFFER_USAGE_VERTEX_BUFFER_BIT;

				std::tie(Vulkan_Mesh_Data.Mesh_Vertex_Varying_Buffer, Vulkan_Mesh_Data.Mesh_Vertex_Varying_Allocation) = Ref_Vulkan_RHI->Create_Buffer_VMA(
					&Buffer_Create_Info,
					&Allocation_Create_Info,
					nullptr
				);

				Ref_Vulkan_RHI->Copy_Buffer(
					Inefficient_Staging_Buffer.get(),
					Vulkan_Mesh_Data.Mesh_Vertex_Varying_Buffer.get(),
					Vertex_Varying_Buffer_Offset,
					0,
					Vertex_Varying_Buffer_Size
				);
			}

			{
				Buffer_Create_Info.Size = Vertex_Joint_Binding_Buffer_Size;
				Buffer_Create_Info.Usage = RHI_BUFFER_USAGE_FLAG_BITS::RHI_BUFFER_USAGE_TRANSFER_DST_BIT | RHI_BUFFER_USAGE_FLAG_BITS::RHI_BUFFER_USAGE_STORAGE_BUFFER_BIT;

				std::tie(Vulkan_Mesh_Data.Mesh_Vertex_Joint_Binding_Buffer, Vulkan_Mesh_Data.Mesh_Vertex_Joint_Binding_Allocation) = Ref_Vulkan_RHI->Create_Buffer_VMA(
					&Buffer_Create_Info,
					&Allocation_Create_Info,
					nullptr
				);

				Ref_Vulkan_RHI->Copy_Buffer(
					Inefficient_Staging_Buffer.get(),
					Vulkan_Mesh_Data.Mesh_Vertex_Joint_Binding_Buffer.get(),
					Vertex_Joint_Binding_Buffer_Offset,
					0,
					Vertex_Joint_Binding_Buffer_Size
				);
			}

			//Inefficient_Staging_Buffer.reset();
			//Inefficient_Staging_Buffer_Memory.reset();
		}

		//NOTE: Index Buffer
		std::tie(Vulkan_Mesh_Data.Mesh_Index_Buffer, Vulkan_Mesh_Data.Mesh_Index_Allocation) = this->S_Load_Index_Buffer(
			RHI,
			Index_Buffer_Size,
			Index_Buffer_Data
		);

		//NOTE : Descriptor Set
		{
			const vector<RHI_Descriptor_Set_Layout*> Mesh_Descriptor_Set_Layouts{
				this->m_Mesh_Descriptor_Set_Layout
			};

			RHI_Descriptor_Set_Allocate_Info Mesh_Vertex_Blending_per_Mesh_Descriptor_Set_Allocate_Info{};
			{
				Mesh_Vertex_Blending_per_Mesh_Descriptor_Set_Allocate_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
				Mesh_Vertex_Blending_per_Mesh_Descriptor_Set_Allocate_Info.Descriptor_Pool = Ref_Vulkan_RHI->Get_Default_Descriptor_Pool();
				Mesh_Vertex_Blending_per_Mesh_Descriptor_Set_Allocate_Info.Set_Layouts = &Mesh_Descriptor_Set_Layouts;
			}

			Vulkan_Mesh_Data.Mesh_Vertex_Blending_Descriptor_Set = std::move(Ref_Vulkan_RHI->Allocate_Descriptor_Sets(&Mesh_Vertex_Blending_per_Mesh_Descriptor_Set_Allocate_Info).front());

			RHI_Descriptor_Buffer_Info Mesh_Vertex_Joint_Binding_Storage_Buffer_Info{};
			{
				Mesh_Vertex_Joint_Binding_Storage_Buffer_Info.Buffer = Vulkan_Mesh_Data.Mesh_Vertex_Joint_Binding_Buffer.get();
				Mesh_Vertex_Joint_Binding_Storage_Buffer_Info.Offset = 0;
				Mesh_Vertex_Joint_Binding_Storage_Buffer_Info.Range = Vertex_Joint_Binding_Buffer_Size;
			}
			const vector<const RHI_Descriptor_Buffer_Info*> Mesh_Vertex_Joint_Binding_Storage_Buffer_Infos{ &Mesh_Vertex_Joint_Binding_Storage_Buffer_Info };

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
			const vector<const RHI_Write_Descriptor_Set*> Mesh_Vertex_Joint_Binding_Storage_Buffer_Writes{ &Mesh_Vertex_Joint_Binding_Storage_Buffer_Write };

			RHI->Update_Descriptor_Sets(&Mesh_Vertex_Joint_Binding_Storage_Buffer_Writes, nullptr);
		}

		return Vulkan_Mesh_Data;
	}

	Vulkan_Mesh Render_Resource::Load_Mesh_Buffer(shared_ptr<Empty_RHI> RHI, uint32_t Index_Buffer_Size, uint16_t* Index_Buffer_Data, uint32_t Vertex_Buffer_Size, const Mesh_Vertex_Data_Definition* Vertex_Buffer_Data) {
		if (0 != (Vertex_Buffer_Size % sizeof(Mesh_Vertex_Data_Definition)))
			System_Logger::Get_Instance().Log(System_Logger::Level::err, "Vertex_Buffer_Size % sizeof(Mesh_Vertex_Data_Definition) != 0");

		uint32_t Vertex_Count{ Vertex_Buffer_Size / sizeof(Mesh_Vertex_Data_Definition) };
		uint32_t Index_Count{ Index_Buffer_Size / sizeof(uint16_t) };

		auto Ref_Vulkan_RHI{ static_cast<Vulkan_RHI*>(RHI.get()) };

		Vulkan_Mesh Vulkan_Mesh_Data{};
		Vulkan_Mesh_Data.Enable_Vertex_Blending = false;
		Vulkan_Mesh_Data.Mesh_Vertex_Count = Vertex_Count;
		Vulkan_Mesh_Data.Mesh_Index_Count = Index_Count;

		//NOTE Mesh Vertex Buffer
		{
			RHI_Device_Size
				Vertex_Position_Buffer_Size{ sizeof(Mesh_Vertex::Vulkan_Mesh_Vertex_Position) * Vertex_Count },
				Vertex_Varying_Enable_Buffer_Size{ sizeof(Mesh_Vertex::Vulkan_Mesh_Vertex_Varying_Enable_Blending) * Vertex_Count },
				Vertex_Varying_Buffer_Size{ sizeof(Mesh_Vertex::Vulkan_Mesh_Vertex_Varying) * Vertex_Count };

			RHI_Device_Size
				Vertex_Position_Buffer_Offset{ 0 },
				Vertex_Varying_Enable_Bleding_Buffer_Offset{ Vertex_Position_Buffer_Size },
				Vertex_Varying_Buffer_Offset{ Vertex_Varying_Enable_Bleding_Buffer_Offset + Vertex_Varying_Enable_Buffer_Size };

			RHI_Device_Size Inefficient_Staging_Buffer_Size{ Vertex_Position_Buffer_Size + Vertex_Varying_Enable_Buffer_Size + Vertex_Varying_Buffer_Size };

			auto [Inefficient_Staging_Buffer, Inefficient_Staging_Buffer_Memory] = RHI->Create_Buffer(
				Inefficient_Staging_Buffer_Size,
				to_underlying(RHI_BUFFER_USAGE_FLAG_BITS::RHI_BUFFER_USAGE_TRANSFER_SRC_BIT),
				RHI_MEMORY_PROPERTY_FLAG_BITS::RHI_MEMORY_PROPERTY_HOST_VISIBLE_BIT | RHI_MEMORY_PROPERTY_FLAG_BITS::RHI_MEMORY_PROPERTY_HOST_COHERENT_BIT
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
			Mesh_Vertex::Vulkan_Mesh_Vertex_Varying* Mesh_Vertex_Varying_Buffer{ reinterpret_cast<Mesh_Vertex::Vulkan_Mesh_Vertex_Varying*>(reinterpret_cast<uintptr_t>(Inefficient_Staging_Buffer_Mapped_Memory) + Vertex_Varying_Buffer_Offset) };

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
				Mesh_Vertex_Varying_Buffer[Vertex_Index].TexCoord = Vector2{
					Vertex_Buffer_Data[Vertex_Index].U,
					Vertex_Buffer_Data[Vertex_Index].V
				};
			}

			Ref_Vulkan_RHI->UnMap_Memory(Inefficient_Staging_Buffer_Memory.get());

			RHI_Buffer_Create_Info Buffer_Create_Info{};
			{
				Buffer_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
				Buffer_Create_Info.Usage = RHI_BUFFER_USAGE_FLAG_BITS::RHI_BUFFER_USAGE_TRANSFER_DST_BIT | RHI_BUFFER_USAGE_FLAG_BITS::RHI_BUFFER_USAGE_VERTEX_BUFFER_BIT;
			}

			VmaAllocationCreateInfo Allocation_Create_Info{};
			{
				//Allocation_Create_Info.flags = VMA_ALLOCATION_CREATE_MAPPED_BIT;
				Allocation_Create_Info.usage = VMA_MEMORY_USAGE_GPU_ONLY;
			}

			{
				Buffer_Create_Info.Size = Vertex_Position_Buffer_Size;

				std::tie(Vulkan_Mesh_Data.Mesh_Vertex_Position_Buffer, Vulkan_Mesh_Data.Mesh_Vertex_Position_Allocation) = Ref_Vulkan_RHI->Create_Buffer_VMA(
					&Buffer_Create_Info,
					&Allocation_Create_Info,
					nullptr
				);

				Ref_Vulkan_RHI->Copy_Buffer(
					Inefficient_Staging_Buffer.get(),
					Vulkan_Mesh_Data.Mesh_Vertex_Position_Buffer.get(),
					Vertex_Position_Buffer_Offset,
					0,
					Vertex_Position_Buffer_Size
				);
			}

			{
				Buffer_Create_Info.Size = Vertex_Varying_Enable_Buffer_Size;

				std::tie(Vulkan_Mesh_Data.Mesh_Vertex_Varying_Enable_Blending_Buffer, Vulkan_Mesh_Data.Mesh_Vertex_Varying_Enable_Blending_Allocation) = Ref_Vulkan_RHI->Create_Buffer_VMA(
					&Buffer_Create_Info,
					&Allocation_Create_Info,
					nullptr
				);

				Ref_Vulkan_RHI->Copy_Buffer(
					Inefficient_Staging_Buffer.get(),
					Vulkan_Mesh_Data.Mesh_Vertex_Varying_Enable_Blending_Buffer.get(),
					Vertex_Varying_Enable_Bleding_Buffer_Offset,
					0,
					Vertex_Varying_Enable_Buffer_Size
				);
			}

			{
				Buffer_Create_Info.Size = Vertex_Varying_Buffer_Size;
				Buffer_Create_Info.Usage = RHI_BUFFER_USAGE_FLAG_BITS::RHI_BUFFER_USAGE_TRANSFER_DST_BIT | RHI_BUFFER_USAGE_FLAG_BITS::RHI_BUFFER_USAGE_VERTEX_BUFFER_BIT;

				std::tie(Vulkan_Mesh_Data.Mesh_Vertex_Varying_Buffer, Vulkan_Mesh_Data.Mesh_Vertex_Varying_Allocation) = Ref_Vulkan_RHI->Create_Buffer_VMA(
					&Buffer_Create_Info,
					&Allocation_Create_Info,
					nullptr
				);

				Ref_Vulkan_RHI->Copy_Buffer(
					Inefficient_Staging_Buffer.get(),
					Vulkan_Mesh_Data.Mesh_Vertex_Varying_Buffer.get(),
					Vertex_Varying_Buffer_Offset,
					0,
					Vertex_Varying_Buffer_Size
				);
			}

			//Inefficient_Staging_Buffer.reset();
			//Inefficient_Staging_Buffer_Memory.reset();
		}

		//NOTE: Index Buffer
		std::tie(Vulkan_Mesh_Data.Mesh_Index_Buffer, Vulkan_Mesh_Data.Mesh_Index_Allocation) = this->S_Load_Index_Buffer(
			RHI,
			Index_Buffer_Size,
			Index_Buffer_Data
		);

		//NOTE : Descriptor Set
		{
			const vector<RHI_Descriptor_Set_Layout*> Mesh_Descriptor_Set_Layouts{
				this->m_Mesh_Descriptor_Set_Layout
			};

			RHI_Descriptor_Set_Allocate_Info Mesh_Vertex_Blending_per_Mesh_Descriptor_Set_Allocate_Info{};
			{
				Mesh_Vertex_Blending_per_Mesh_Descriptor_Set_Allocate_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
				Mesh_Vertex_Blending_per_Mesh_Descriptor_Set_Allocate_Info.Descriptor_Pool = Ref_Vulkan_RHI->Get_Default_Descriptor_Pool();
				Mesh_Vertex_Blending_per_Mesh_Descriptor_Set_Allocate_Info.Set_Layouts = &Mesh_Descriptor_Set_Layouts;
			}

			Vulkan_Mesh_Data.Mesh_Vertex_Blending_Descriptor_Set = std::move(Ref_Vulkan_RHI->Allocate_Descriptor_Sets(&Mesh_Vertex_Blending_per_Mesh_Descriptor_Set_Allocate_Info).front());

			RHI_Descriptor_Buffer_Info Mesh_Vertex_Joint_Binding_Storage_Buffer_Info{};
			{
				Mesh_Vertex_Joint_Binding_Storage_Buffer_Info.Buffer = this->m_Global_Render_Resource.Storage_Buffer.Global_Null_Descriptor_Storage_Buffer.get();
				Mesh_Vertex_Joint_Binding_Storage_Buffer_Info.Offset = 0;
				Mesh_Vertex_Joint_Binding_Storage_Buffer_Info.Range = 1;
			}
			const vector<const RHI_Descriptor_Buffer_Info*> Mesh_Vertex_Joint_Binding_Storage_Buffer_Infos{ &Mesh_Vertex_Joint_Binding_Storage_Buffer_Info };

			RHI_Write_Descriptor_Set Mesh_Vertex_Joint_Binding_Storage_Buffer_Write{};
			{
				Mesh_Vertex_Joint_Binding_Storage_Buffer_Write.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
				Mesh_Vertex_Joint_Binding_Storage_Buffer_Write.Dst_Set = Vulkan_Mesh_Data.Mesh_Vertex_Blending_Descriptor_Set.get();
				Mesh_Vertex_Joint_Binding_Storage_Buffer_Write.Dst_Binding = 0;
				Mesh_Vertex_Joint_Binding_Storage_Buffer_Write.Dst_Array_Element = 0;
				Mesh_Vertex_Joint_Binding_Storage_Buffer_Write.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_STORAGE_BUFFER;
				Mesh_Vertex_Joint_Binding_Storage_Buffer_Write.Buffer_Infos = &Mesh_Vertex_Joint_Binding_Storage_Buffer_Infos;
			}
			const vector<const RHI_Write_Descriptor_Set*> Mesh_Vertex_Joint_Binding_Storage_Buffer_Writes{ &Mesh_Vertex_Joint_Binding_Storage_Buffer_Write };

			RHI->Update_Descriptor_Sets(&Mesh_Vertex_Joint_Binding_Storage_Buffer_Writes, nullptr);
		}

		return Vulkan_Mesh_Data;
	}

	Vulkan_PBR_Material Render_Resource::Load_PBR_Material_Image(shared_ptr<Empty_RHI> RHI, const Vulkan_PBR_Texture_Data_Info& Texture_Data_Info) {
		auto Ref_Vulkan_RHI{ static_cast<Vulkan_RHI*>(RHI.get()) };

		Vulkan_PBR_Material Vulkan_PBR_Material_Data{};

		std::tie(Vulkan_PBR_Material_Data.Base_Color_Image, Vulkan_PBR_Material_Data.Base_Color_Image_View, Vulkan_PBR_Material_Data.Base_Color_Image_Allocation) = Ref_Vulkan_RHI->Create_Global_Image(
			{ Texture_Data_Info.Base_Color_Image_Width,Texture_Data_Info.Base_Color_Image_Height },
			Texture_Data_Info.Base_Color_Image_Format,
			0,
			Texture_Data_Info.Base_Color_Image_Pixels
		);

		std::tie(Vulkan_PBR_Material_Data.Metallic_Roughness_Image, Vulkan_PBR_Material_Data.Metallic_Roughness_Image_View, Vulkan_PBR_Material_Data.Metallic_Roughness_Image_Allocation) = Ref_Vulkan_RHI->Create_Global_Image(
			{ Texture_Data_Info.Metallic_Roughness_Image_Width,Texture_Data_Info.Metallic_Roughness_Image_Height },
			Texture_Data_Info.Metallic_Roughness_Image_Format,
			0,
			Texture_Data_Info.Metallic_Roughness_Image_Pixels
		);

		std::tie(Vulkan_PBR_Material_Data.Normal_Image, Vulkan_PBR_Material_Data.Normal_Image_View, Vulkan_PBR_Material_Data.Normal_Image_Allocation) = Ref_Vulkan_RHI->Create_Global_Image(
			{ Texture_Data_Info.Normal_Image_Width,Texture_Data_Info.Normal_Image_Height },
			Texture_Data_Info.Normal_Image_Format,
			0,
			Texture_Data_Info.Normal_Image_Pixels
		);

		std::tie(Vulkan_PBR_Material_Data.Occlusion_Image, Vulkan_PBR_Material_Data.Occlusion_Image_View, Vulkan_PBR_Material_Data.Occlusion_Image_Allocation) = Ref_Vulkan_RHI->Create_Global_Image(
			{ Texture_Data_Info.Occlusion_Image_Width,Texture_Data_Info.Occlusion_Image_Height },
			Texture_Data_Info.Occlusion_Image_Format,
			0,
			Texture_Data_Info.Occlusion_Image_Pixels
		);

		std::tie(Vulkan_PBR_Material_Data.Emissive_Image, Vulkan_PBR_Material_Data.Emissive_Image_View, Vulkan_PBR_Material_Data.Emissive_Image_Allocation) = Ref_Vulkan_RHI->Create_Global_Image(
			{ Texture_Data_Info.Emissive_Image_Width,Texture_Data_Info.Emissive_Image_Height },
			Texture_Data_Info.Emissive_Image_Format,
			0,
			Texture_Data_Info.Emissive_Image_Pixels
		);

		return Vulkan_PBR_Material_Data;
	}

	tuple<unique_ptr<RHI_Buffer>, VmaAllocation> Render_Resource::S_Load_Index_Buffer(shared_ptr<Empty_RHI> RHI, uint32_t Index_Buffer_Size, uint16_t* Index_Buffer_Data) {
		auto Ref_Vulkan_RHI{ static_cast<Vulkan_RHI*>(RHI.get()) };

		auto [Inefficient_Staging_Buffer, Inefficient_Staging_Buffer_Memory] = RHI->Create_Buffer(
			static_cast<RHI_Device_Size>(Index_Buffer_Size),
			to_underlying(RHI_BUFFER_USAGE_FLAG_BITS::RHI_BUFFER_USAGE_TRANSFER_SRC_BIT),
			RHI_MEMORY_PROPERTY_FLAG_BITS::RHI_MEMORY_PROPERTY_HOST_VISIBLE_BIT | RHI_MEMORY_PROPERTY_FLAG_BITS::RHI_MEMORY_PROPERTY_HOST_COHERENT_BIT
		);

		void* Inefficient_Staging_Buffer_Mapped_Memory{ nullptr };
		Ref_Vulkan_RHI->Map_Memory(
			Inefficient_Staging_Buffer_Memory.get(),
			0,
			RHI_WHOLE_SIZE,
			0,
			&Inefficient_Staging_Buffer_Mapped_Memory
		);
		memcpy(Inefficient_Staging_Buffer_Mapped_Memory, Index_Buffer_Data, Index_Buffer_Size);
		Ref_Vulkan_RHI->UnMap_Memory(Inefficient_Staging_Buffer_Memory.get());

		RHI_Buffer_Create_Info Buffer_Create_Info{};
		{
			Buffer_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
			Buffer_Create_Info.Size = static_cast<RHI_Device_Size>(Index_Buffer_Size);
			Buffer_Create_Info.Usage = RHI_BUFFER_USAGE_FLAG_BITS::RHI_BUFFER_USAGE_TRANSFER_DST_BIT | RHI_BUFFER_USAGE_FLAG_BITS::RHI_BUFFER_USAGE_INDEX_BUFFER_BIT;
		}

		VmaAllocationCreateInfo Allocation_Create_Info{};
		{
			//Allocation_Create_Info.flags = VMA_ALLOCATION_CREATE_MAPPED_BIT;
			Allocation_Create_Info.usage = VMA_MEMORY_USAGE_GPU_ONLY;
		}

		auto [Index_Buffer, Index_Buffer_Allocation] = Ref_Vulkan_RHI->Create_Buffer_VMA(
			&Buffer_Create_Info,
			&Allocation_Create_Info,
			nullptr
		);

		Ref_Vulkan_RHI->Copy_Buffer(
			Inefficient_Staging_Buffer.get(),
			Index_Buffer.get(),
			0,
			0,
			static_cast<RHI_Device_Size>(Index_Buffer_Size)
		);

		//Inefficient_Staging_Buffer.reset();
		//Inefficient_Staging_Buffer_Memory.reset();

		return { std::move(Index_Buffer), Index_Buffer_Allocation };
	}

	const Global_Render_Resource& Render_Resource::Get_Global_Render_Resource(void) const {
		return this->m_Global_Render_Resource;
	}

	void Render_Resource::Set_Mesh_Descriptor_Set_Layout(RHI_Descriptor_Set_Layout* Mesh_Descriptor_Set_Layout) {
		this->m_Mesh_Descriptor_Set_Layout = Mesh_Descriptor_Set_Layout;
	}

	void Render_Resource::Set_Material_Descriptor_Set_Layout(RHI_Descriptor_Set_Layout* Material_Descriptor_Set_Layout) {
		this->m_Material_Descriptor_Set_Layout = Material_Descriptor_Set_Layout;
	}

	void Render_Resource::Upload_Global_Render_Resource(shared_ptr<Empty_RHI> RHI, const Level_Resource_Desc& Level_Resource_Desc) {
		this->Create_Storge_Buffer(RHI);
		this->Map_Storage_Buffer(RHI);

		//NOTE :SkyBOX Irradiance
		array<shared_ptr<Texture_Data>, 6> SkyBox_Irradiance_Map{
			Render_Resource_Base::Load_Texture_HDR(Reflection_SkyBox_Irradiance_Map_Operator::Get_Positive_X_Map_URL_Attribute(Level_Resource_Desc.IBL_Resource_Desc.m_SkyBox_Irradiance_Map)),
			Render_Resource_Base::Load_Texture_HDR(Reflection_SkyBox_Irradiance_Map_Operator::Get_Negative_X_Map_URL_Attribute(Level_Resource_Desc.IBL_Resource_Desc.m_SkyBox_Irradiance_Map)),
			Render_Resource_Base::Load_Texture_HDR(Reflection_SkyBox_Irradiance_Map_Operator::Get_Positive_Y_Map_URL_Attribute(Level_Resource_Desc.IBL_Resource_Desc.m_SkyBox_Irradiance_Map)),
			Render_Resource_Base::Load_Texture_HDR(Reflection_SkyBox_Irradiance_Map_Operator::Get_Negative_Y_Map_URL_Attribute(Level_Resource_Desc.IBL_Resource_Desc.m_SkyBox_Irradiance_Map)),
			Render_Resource_Base::Load_Texture_HDR(Reflection_SkyBox_Irradiance_Map_Operator::Get_Positive_Z_Map_URL_Attribute(Level_Resource_Desc.IBL_Resource_Desc.m_SkyBox_Irradiance_Map)),
			Render_Resource_Base::Load_Texture_HDR(Reflection_SkyBox_Irradiance_Map_Operator::Get_Negative_Z_Map_URL_Attribute(Level_Resource_Desc.IBL_Resource_Desc.m_SkyBox_Irradiance_Map))
		};

		//NOTE :SkyBOX Specular
		array<shared_ptr<Texture_Data>, 6> SkyBox_Specular_Map{
			Render_Resource_Base::Load_Texture_HDR(Reflection_SkyBox_Specular_Map_Operator::Get_Positive_X_Map_URL_Attribute(Level_Resource_Desc.IBL_Resource_Desc.m_SkyBox_Specular_Map)),
			Render_Resource_Base::Load_Texture_HDR(Reflection_SkyBox_Specular_Map_Operator::Get_Negative_X_Map_URL_Attribute(Level_Resource_Desc.IBL_Resource_Desc.m_SkyBox_Specular_Map)),
			Render_Resource_Base::Load_Texture_HDR(Reflection_SkyBox_Specular_Map_Operator::Get_Positive_Y_Map_URL_Attribute(Level_Resource_Desc.IBL_Resource_Desc.m_SkyBox_Specular_Map)),
			Render_Resource_Base::Load_Texture_HDR(Reflection_SkyBox_Specular_Map_Operator::Get_Negative_Y_Map_URL_Attribute(Level_Resource_Desc.IBL_Resource_Desc.m_SkyBox_Specular_Map)),
			Render_Resource_Base::Load_Texture_HDR(Reflection_SkyBox_Specular_Map_Operator::Get_Positive_Z_Map_URL_Attribute(Level_Resource_Desc.IBL_Resource_Desc.m_SkyBox_Specular_Map)),
			Render_Resource_Base::Load_Texture_HDR(Reflection_SkyBox_Specular_Map_Operator::Get_Negative_Z_Map_URL_Attribute(Level_Resource_Desc.IBL_Resource_Desc.m_SkyBox_Specular_Map))
		};

		//NOTE : SkyBox BRDF LUT
		shared_ptr<Texture_Data> Ref_BDRF_LUT = Render_Resource_Base::Load_Texture_HDR(Level_Resource_Desc.IBL_Resource_Desc.BRDF_Map_URL);

		this->Create_IBL_Textures(RHI, SkyBox_Irradiance_Map, SkyBox_Specular_Map);

		std::tie(this->m_Global_Render_Resource.IBL_Resource.BUDF_LUT_Image, this->m_Global_Render_Resource.IBL_Resource.BUDF_LUT_Image_View, this->m_Global_Render_Resource.IBL_Resource.BUDF_LUT_Image_Allocation) = RHI->Create_Global_Image(
			{ Ref_BDRF_LUT->Width,Ref_BDRF_LUT->Height },
			Ref_BDRF_LUT->Format,
			Ref_BDRF_LUT->Mip_Levels,
			Ref_BDRF_LUT->Pixels.get()
		);

		this->Create_IBL_Samplers(RHI);


		//NOTE : Color Grading
		shared_ptr<Texture_Data> Ref_Color_Grading_Map = Render_Resource_Base::Load_Texture_HDR(Level_Resource_Desc.Color_Grading_Resource_Desc.Color_Grading_Map_URL);

		std::tie(this->m_Global_Render_Resource.Color_Grading_Resource.Color_Grading_Image, this->m_Global_Render_Resource.Color_Grading_Resource.Color_Grading_Image_View, this->m_Global_Render_Resource.Color_Grading_Resource.Color_Grading_Image_Allocation) = RHI->Create_Global_Image(
			{ Ref_Color_Grading_Map->Width,Ref_Color_Grading_Map->Height },
			Ref_Color_Grading_Map->Format,
			Ref_Color_Grading_Map->Mip_Levels,
			Ref_Color_Grading_Map->Pixels.get()
		);
	}

	void Render_Resource::Upload_Game_Object_Render_Resource(shared_ptr<Empty_RHI> RHI, const Render_Entity& Render_Entity, const Render_Mesh_Data& Meshe_Data, const Render_Material_Data& Material_Data) {
		this->Get_OR_Create_Vulkan_Mesh(RHI, Render_Entity, Meshe_Data);
		this->Get_OR_Create_Vulkan_Material(RHI, Render_Entity, Material_Data);
	}

	void Render_Resource::Upload_Game_Object_Render_Resource(shared_ptr<Empty_RHI> RHI, const Render_Entity& Render_Entity, const Render_Mesh_Data& Meshe_Data) {
		this->Get_OR_Create_Vulkan_Mesh(RHI, Render_Entity, Meshe_Data);
	}

	void Render_Resource::Upload_Game_Object_Render_Resource(shared_ptr<Empty_RHI> RHI, const Render_Entity& Render_Entity, const Render_Material_Data& Material_Data) {
		this->Get_OR_Create_Vulkan_Material(RHI, Render_Entity, Material_Data);
	}

	void Render_Resource::Updata_Per_Frame_Buffer(shared_ptr<Render_Scene> Scene, shared_ptr<Render_Camera> Camera) {

		Matrix4x4 View_Matrix{ Camera->Get_View_Matrix() };
		Matrix4x4 Proj_Matrix{ Camera->Get_Projection_Matrix() };
		Matrix4x4 View_Proj_Matrix{ Proj_Matrix * View_Matrix };
		Vector3 Camera_Position{ Camera->Get_Position() };

		Vector3 Ambient_Light{ static_cast<Vector3>(Scene->m_Ambient_Light) };
		uint32_t Point_Light_Num{ static_cast<uint32_t>(Scene->m_Point_Light_List.m_Light.size()) };

		this->m_Mesh_Per_Frame_Storage_Buffer_Object.Proj_View_Matrix = View_Proj_Matrix;
		this->m_Mesh_Per_Frame_Storage_Buffer_Object.Camera_Position = Camera_Position;
		this->m_Mesh_Per_Frame_Storage_Buffer_Object.Ambient_Light = Ambient_Light;
		this->m_Mesh_Per_Frame_Storage_Buffer_Object.Point_Light_Num = Point_Light_Num;

		this->m_Mesh_Point_Light_Shadow_Per_Frame_Storage_Buffer_Object.Point_Light_Num = Point_Light_Num;

		this->m_Particle_Collision_Pre_Frame_Storage_Buffer_Object.View_Matrix = View_Matrix;
		this->m_Particle_Collision_Pre_Frame_Storage_Buffer_Object.Proj_View_Matrix = View_Proj_Matrix;
		this->m_Particle_Collision_Pre_Frame_Storage_Buffer_Object.Proj_Inv_Matrix = Proj_Matrix.Inverse();

		for (uint32_t Index = 0; Index < Point_Light_Num; ++Index) {
			Vector3 Point_Light_Position{ Scene->m_Point_Light_List.m_Light[Index].Position };
			Vector3 Position_Light_Intensity{ Scene->m_Point_Light_List.m_Light[Index].Flux / (4.f * Math_PI) };

			float Point_Light_Radius{ Scene->m_Point_Light_List.m_Light[Index].Calculate_Radius() };

			this->m_Mesh_Per_Frame_Storage_Buffer_Object.Scene_Point_Lights[Index].Position = Point_Light_Position;
			this->m_Mesh_Per_Frame_Storage_Buffer_Object.Scene_Point_Lights[Index].Intensity = Position_Light_Intensity;
			this->m_Mesh_Per_Frame_Storage_Buffer_Object.Scene_Point_Lights[Index].Radius = Point_Light_Radius;

			this->m_Mesh_Point_Light_Shadow_Per_Frame_Storage_Buffer_Object.Point_Lights_Position_And_Radius[Index] = Vector4{ Point_Light_Position, Point_Light_Radius };
		}

		this->m_Mesh_Per_Frame_Storage_Buffer_Object.m_Scene_Directional_Light.Direction = Scene->m_Directional_Light.Direction.Normalize();
		this->m_Mesh_Per_Frame_Storage_Buffer_Object.m_Scene_Directional_Light.Color = static_cast<Vector3>(Scene->m_Directional_Light.m_Color);

		this->m_Mesh_Inefficient_Pick_Per_Frame_Storage_Buffer_Object.Proj_View_Matrix = View_Proj_Matrix;

		this->m_Particle_Billboard_Per_Frame_Storage_Buffer_Object.Prjo_View_Matrix = View_Proj_Matrix;
		this->m_Particle_Billboard_Per_Frame_Storage_Buffer_Object.Right_Direction = Camera->Get_Right();
		this->m_Particle_Billboard_Per_Frame_Storage_Buffer_Object.Forward_Direction = Camera->Get_Forward();
		this->m_Particle_Billboard_Per_Frame_Storage_Buffer_Object.Up_Direction = Camera->Get_Up();
	}

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System