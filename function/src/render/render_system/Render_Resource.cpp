#include "render/render_system/Render_Resource.h"

#include<utility>

#include "render/rhi/vulkan/Vulkan_RHI.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System {

	using NameSpace_RHI::RHI_Buffer_Usage_Flag_Bits;

	using NameSpace_RHI::RHI_Physical_Device_Properties;
	using NameSpace_RHI::RHI_Memory_Property_Flag_Bits;

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