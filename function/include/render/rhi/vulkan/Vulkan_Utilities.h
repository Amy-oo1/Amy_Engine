#pragma once

#include<array>
#include<utility>
#include<initializer_list>
#include<limits>
#include<tuple>

#include "render/rhi/empty_rhi/Empty_RHI.h"

#include<vector>

namespace NameSpace_Function::NameSpace_Render::NameSpace_RHI::NameSpace_Vulkan_RHI::NameSpace_Utilities {

	using std::tuple;
	using std::array;
	using std::vector;

	[[nodiscard]] uint32_t
		Find_Memory_Type(
			VkPhysicalDevice Physical_Device,
			uint32_t Type_Filter,
			VkMemoryPropertyFlags Property_Flags
		);

	void
		Create_Buffer(
			VkPhysicalDevice Physical_Device,
			VkDevice Logical_Device,
			VkDeviceSize Size,
			VkBufferUsageFlags Usage,
			VkMemoryPropertyFlags Properties,
			const VkAllocationCallbacks* Allocator,
			VkBuffer& Buffer,
			VkDeviceMemory& Buffer_Memory
		);



	[[nodiscard]] VkDeviceSize
		Get_Image_Byte_Size(
			uint32_t Image_Wedtih,
			uint32_t Image_Height,
			VkFormat Format
		);

	[[nodiscard]] const VkImageView
		Create_Image_View(
			VkDevice Logical_Device,
			const VkAllocationCallbacks* Allocator,
			VkImage Image,
			VkFormat Format,
			uint32_t Mip_Levels,
			VkImageAspectFlags Image_Aspect_Flags,
			VkImageViewType View_Type,
			uint32_t Layout_Count
		);

	[[nodiscard]] const VkCommandBuffer Begin_SingleTime_Commands(VkDevice Logical_Device, VkCommandPool Command_Pool);

	void
		End_SingleTIme_Commands(
			VkDevice Logical_Device,
			VkCommandPool Command_Pool,
			VkQueue Graphics_Queue,
			VkCommandBuffer Command_Buffer

		);

	void
		Transition_Image_Layout(
			VkDevice Logical_Device,
			VkCommandPool Command_Pool,
			VkQueue Graphics_Queue,
			VkImage Image,
			uint32_t Mip_Levels,
			VkFormat Format,
			VkImageAspectFlagBits Aspect_Flags,
			VkImageLayout Old_Layout,
			VkImageLayout New_Layout,
			uint32_t Layer_Count
		);

	void
		Copy_Buffer_To_Image(
			VkDevice Logical_Device,
			VkCommandPool Command_Pool,
			VkQueue Graphics_Queue,
			VkBuffer Buffer,
			VkImage Image,
			VkExtent2D Image_ExTent_2D,
			uint32_t Layer_Count
		);

	void
		Generate_Mipmaps(
			VkPhysicalDevice Physical_Device,
			VkDevice Logical_Device,
			VkCommandPool Command_Pool,
			VkQueue Graphics_Queue,
			VkImage Image,
			VkExtent2D Image_ExTent_2D,
			VkFormat Image_Format,
			uint32_t Mip_Levels,
			uint32_t Layer_Count
		);

	void Create_Global_Image(
		VkPhysicalDevice Physical_Device,
		VkDevice Logical_Device,
		const VkAllocationCallbacks* VK_Allocator,
		VkCommandPool Command_Pool,
		VkQueue Graphics_Queue,
		VmaAllocator VMA_Allocator,
		VkExtent2D Image_Extent,
		VkFormat Format,
		uint32_t Mip_levels,
		void* Image_Pixels,
		VkImage& Image,
		VkImageView& Image_View,
		VmaAllocation& Image_Allocation
	);


	void
		Create_Cube_Map(
			VkPhysicalDevice Physical_Device,
			VkDevice Logical_Device,
			const VkAllocationCallbacks* VK_Allocator,
			VkCommandPool Command_Pool,
			VkQueue Graphics_Queue,
			VmaAllocator VMA_Allocator,
			VkExtent2D Image_Extent,
			VkFormat Format,
			uint32_t Mip_levels,
			array<void*, 6> Image_Pixels,
			VkImage& Image,
			VkImageView& Image_View,
			VmaAllocation& Image_Allocation
		);





	const VkShaderModule Create_Shader_Module(VkDevice Logical_Device, const vector<unsigned char>& Code);

	void Create_Image(
		VkPhysicalDevice		Physical_Device,
		VkDevice				Device,
		VkExtent2D				Image_Extent,
		VkFormat				Format,
		uint32_t				Mip_levels,
		VkSampleCountFlagBits   Samples,
		VkImageTiling			Image_Tiling,
		VkImageUsageFlags		Image_Usage_Flags,
		VkMemoryPropertyFlags	Memory_Property_Flags,
		VkImage& Image,
		VkDeviceMemory& Memory,
		VkImageCreateFlags		Image_Create_Flags,
		uint32_t				Array_Layers,
		const VkAllocationCallbacks* pAllocator);

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_RHI::NameSpace_Vulkan_RHI::NameSpace_Utilities