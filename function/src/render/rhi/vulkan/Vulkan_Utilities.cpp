#include "render/rhi/vulkan/Vulkan_Utilities.h"

#include<exception>

#include "render/rhi/vulkan/Vulkan_RHI_Macro.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_RHI::NameSpace_Vulkan_RHI::NameSpace_Utilities {

	using std::runtime_error;

	uint32_t Find_Memory_Type(VkPhysicalDevice Physical_Device, uint32_t Type_Filter, VkMemoryPropertyFlags Property_Flags) {
		VkPhysicalDeviceMemoryProperties Memory_Properties{};
		vkGetPhysicalDeviceMemoryProperties(Physical_Device, &Memory_Properties);

		for (uint32_t Index = 0; Index < Memory_Properties.memoryTypeCount; ++Index)
			if (Type_Filter & (1 << Index) && (Memory_Properties.memoryTypes[Index].propertyFlags & Property_Flags) == Property_Flags)
				return Index;

		throw runtime_error("Failed to find suitable memory type!");

		return std::numeric_limits<uint32_t>::max();
	}

	void Create_Buffer(VkPhysicalDevice Physical_Device, VkDevice Logical_Device, VkDeviceSize Size, VkBufferUsageFlags Usage, VkMemoryPropertyFlags Properties, const VkAllocationCallbacks* Allocator, VkBuffer& Buffer, VkDeviceMemory& Buffer_Memory) {
		VkBufferCreateInfo Buffer_Info{};
		{
			Buffer_Info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
			Buffer_Info.size = Size;
			Buffer_Info.usage = Usage;
			Buffer_Info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		}

		THROW_IF_VK_FAILED(vkCreateBuffer(Logical_Device, &Buffer_Info, Allocator, &Buffer));

		VkMemoryRequirements Memory_Requirements{};
		vkGetBufferMemoryRequirements(Logical_Device, Buffer, &Memory_Requirements);

		VkMemoryAllocateInfo Memory_Allocate_Info{};
		{
			Memory_Allocate_Info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
			Memory_Allocate_Info.allocationSize = Memory_Requirements.size;
			Memory_Allocate_Info.memoryTypeIndex = NameSpace_Utilities::Find_Memory_Type(Physical_Device, Memory_Requirements.memoryTypeBits, Properties);
		}

		THROW_IF_VK_FAILED(vkAllocateMemory(Logical_Device, &Memory_Allocate_Info, Allocator, &Buffer_Memory));

		THROW_IF_VK_FAILED(vkBindBufferMemory(Logical_Device, Buffer, Buffer_Memory, 0));
	}

	VkDeviceSize Get_Image_Byte_Size(uint32_t Image_Wedtih, uint32_t Image_Height, VkFormat Format) {
		switch (Format) {
		case VK_FORMAT_R8G8B8_UNORM:
			return static_cast<VkDeviceSize>(Image_Wedtih) * Image_Height * 3;
		case VK_FORMAT_R8G8B8_SRGB:
			return static_cast<VkDeviceSize>(Image_Wedtih) * Image_Height * 3;
		case VK_FORMAT_R8G8B8A8_UNORM:
			return static_cast<VkDeviceSize>(Image_Wedtih) * Image_Height * 4;
		case VK_FORMAT_R8G8B8A8_SRGB:
			return static_cast<VkDeviceSize>(Image_Wedtih) * Image_Height * 4;
		case VK_FORMAT_R32_SFLOAT:
			return static_cast<VkDeviceSize>(Image_Wedtih) * Image_Height * 4;
		case VK_FORMAT_R32G32_SFLOAT:
			return static_cast<VkDeviceSize>(Image_Wedtih) * Image_Height * 8;
		case VK_FORMAT_R32G32B32_SFLOAT:
			return static_cast<VkDeviceSize>(Image_Wedtih) * Image_Height * 12;
		case VK_FORMAT_R32G32B32A32_SFLOAT:
			return static_cast<VkDeviceSize>(Image_Wedtih) * Image_Height * 16;
		case VK_FORMAT_R16G16B16A16_SFLOAT:
			return static_cast<VkDeviceSize>(Image_Wedtih) * Image_Height * 8;
		case VK_FORMAT_R16G16B16A16_UNORM:
			return static_cast<VkDeviceSize>(Image_Wedtih) * Image_Height * 8;
		case VK_FORMAT_R16G16B16A16_SNORM:
			return static_cast<VkDeviceSize>(Image_Wedtih) * Image_Height * 8;
		case VK_FORMAT_R16G16B16A16_SINT:
			return static_cast<VkDeviceSize>(Image_Wedtih) * Image_Height * 8;
		case VK_FORMAT_R16G16B16A16_UINT:
			return static_cast<VkDeviceSize>(Image_Wedtih) * Image_Height * 8;
		case VK_FORMAT_R16G16B16A16_SSCALED:
			return static_cast<VkDeviceSize>(Image_Wedtih) * Image_Height * 8;
		default:
			throw runtime_error("Failed to get image byte size!");
			break;
		}
	};

	const VkImageView Create_Image_View(VkDevice Logical_Device, const VkAllocationCallbacks* Allocator, VkImage Image, VkFormat Format, uint32_t Mip_Levels, VkImageAspectFlags Image_Aspect_Flags, VkImageViewType View_Type, uint32_t Layout_Count) {
		VkComponentMapping Component_Mapping{};
		{
			Component_Mapping.r = VK_COMPONENT_SWIZZLE_IDENTITY;
			Component_Mapping.g = VK_COMPONENT_SWIZZLE_IDENTITY;
			Component_Mapping.b = VK_COMPONENT_SWIZZLE_IDENTITY;
			Component_Mapping.a = VK_COMPONENT_SWIZZLE_IDENTITY;
		}

		VkImageSubresourceRange Subresource_Range{};
		{
			Subresource_Range.aspectMask = Image_Aspect_Flags;
			Subresource_Range.baseMipLevel = 0;
			Subresource_Range.levelCount = Mip_Levels;
			Subresource_Range.baseArrayLayer = 0;
			Subresource_Range.layerCount = Layout_Count;
		}

		VkImageViewCreateInfo View_Info{};
		{
			View_Info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			View_Info.image = Image;
			View_Info.viewType = View_Type;
			View_Info.format = Format;
			View_Info.components = Component_Mapping;
			View_Info.subresourceRange = Subresource_Range;
		}

		VkImageView Image_View{ nullptr };
		THROW_IF_VK_FAILED(vkCreateImageView(Logical_Device, &View_Info, Allocator, &Image_View));

		return Image_View;
	}

	const VkCommandBuffer Begin_SingleTime_Commands(VkDevice Logical_Device, VkCommandPool Command_Pool) {
		VkCommandBufferAllocateInfo Allocate_Info{};
		{
			Allocate_Info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
			Allocate_Info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
			Allocate_Info.commandPool = Command_Pool;
			Allocate_Info.commandBufferCount = 1;
		}

		VkCommandBuffer Command_Buffer{ nullptr };
		THROW_IF_VK_FAILED(vkAllocateCommandBuffers(Logical_Device, &Allocate_Info, &Command_Buffer));

		VkCommandBufferBeginInfo Begin_Info{};
		{
			Begin_Info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			Begin_Info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
		}

		THROW_IF_VK_FAILED(vkBeginCommandBuffer(Command_Buffer, &Begin_Info));

		return Command_Buffer;
	}

	void End_SingleTIme_Commands(VkDevice Logical_Device, VkCommandPool Command_Pool, VkQueue Graphics_Queue, VkCommandBuffer Command_Buffer) {
		THROW_IF_VK_FAILED(vkEndCommandBuffer(Command_Buffer));

		VkSubmitInfo Submit_Info{};
		{
			Submit_Info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
			Submit_Info.commandBufferCount = 1;
			Submit_Info.pCommandBuffers = &Command_Buffer;
		}

		THROW_IF_VK_FAILED(vkQueueSubmit(Graphics_Queue, 1, &Submit_Info, VK_NULL_HANDLE));

		THROW_IF_VK_FAILED(vkQueueWaitIdle(Graphics_Queue));

		vkFreeCommandBuffers(Logical_Device, Command_Pool, 1, &Command_Buffer);
	}

	void Transition_Image_Layout(VkDevice Logical_Device, VkCommandPool Command_Pool, VkQueue Graphics_Queue, VkImage Image, uint32_t Mip_Levels, VkFormat Format, VkImageAspectFlagBits Aspect_Flags, VkImageLayout Old_Layout, VkImageLayout New_Layout, uint32_t Layer_Count) {
		VkCommandBuffer Command_Buffer{ Begin_SingleTime_Commands(Logical_Device, Command_Pool) };

		VkAccessFlags Source_Access_Mask{}, Destination_Access_Mask{};
		VkPipelineStageFlags Source_Stage{}, Destination_Stage{};
		{
			if (VK_IMAGE_LAYOUT_UNDEFINED == Old_Layout && VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL == New_Layout) {
				Source_Access_Mask = VK_ACCESS_NONE;
				Destination_Access_Mask = VK_ACCESS_TRANSFER_WRITE_BIT;

				Source_Stage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
				Destination_Stage = VK_PIPELINE_STAGE_TRANSFER_BIT;
			}
			else if (VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL == Old_Layout && VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL == New_Layout) {
				Source_Access_Mask = VK_ACCESS_TRANSFER_WRITE_BIT;
				Destination_Access_Mask = VK_ACCESS_SHADER_READ_BIT;

				Source_Stage = VK_PIPELINE_STAGE_TRANSFER_BIT;
				Destination_Stage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
			}
			else
				throw std::invalid_argument("Unsupported layout transition!");
		}

		VkImageSubresourceRange Sub_Resource_Range{};
		{
			Sub_Resource_Range.aspectMask = Aspect_Flags;
			Sub_Resource_Range.baseMipLevel = 0;
			Sub_Resource_Range.levelCount = Mip_Levels;
			Sub_Resource_Range.baseArrayLayer = 0;
			Sub_Resource_Range.layerCount = Layer_Count;
		}

		VkImageMemoryBarrier Barrier{};
		{
			Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
			Barrier.oldLayout = Old_Layout;
			Barrier.newLayout = New_Layout;
			Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			Barrier.image = Image;
			Barrier.subresourceRange = Sub_Resource_Range;
			Barrier.srcAccessMask = Source_Access_Mask;
			Barrier.dstAccessMask = Destination_Access_Mask;
		}

		vkCmdPipelineBarrier(
			Command_Buffer,
			Source_Stage, Destination_Stage,
			0, 0, nullptr,
			0, nullptr,
			1, &Barrier
		);

		End_SingleTIme_Commands(Logical_Device, Command_Pool, Graphics_Queue, Command_Buffer);
	}

	void Copy_Buffer_To_Image(VkDevice Logical_Device, VkCommandPool Command_Pool, VkQueue Graphics_Queue, VkBuffer Buffer, VkImage Image, VkExtent2D Image_ExTent_2D, uint32_t Layer_Count) {
		VkCommandBuffer Command_Buffer{ Begin_SingleTime_Commands(Logical_Device, Command_Pool) };

		VkImageSubresourceLayers Subresource{};
		{
			Subresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			Subresource.mipLevel = 0;
			Subresource.baseArrayLayer = 0;
			Subresource.layerCount = Layer_Count;
		}

		VkBufferImageCopy Region{};
		{
			Region.bufferOffset = 0;
			Region.bufferRowLength = 0;
			Region.bufferImageHeight = 0;
			Region.imageSubresource = Subresource;
			Region.imageOffset = { 0, 0, 0 };
			Region.imageExtent = { Image_ExTent_2D.width, Image_ExTent_2D.height, 1 };
		}

		vkCmdCopyBufferToImage(
			Command_Buffer,
			Buffer,
			Image,
			VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
			1,
			&Region
		);

		End_SingleTIme_Commands(Logical_Device, Command_Pool, Graphics_Queue, Command_Buffer);
	}

	void Generate_Mipmaps(VkPhysicalDevice Physical_Device, VkDevice Logical_Device, VkCommandPool Command_Pool, VkQueue Graphics_Queue, VkImage Image, VkExtent2D Image_ExTent_2D, VkFormat Image_Format, uint32_t Mip_Levels, uint32_t Layer_Count) {

		VkFormatProperties Format_Properties{};
		vkGetPhysicalDeviceFormatProperties(Physical_Device, Image_Format, &Format_Properties);

		if (!(Format_Properties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT))
			throw runtime_error("Texture image format does not support linear blitting!");

		VkCommandBuffer Command_Buffer{ Begin_SingleTime_Commands(Logical_Device, Command_Pool) };

		VkImageSubresourceRange Image_Sub_Resource_Range{};
		{
			Image_Sub_Resource_Range.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			Image_Sub_Resource_Range.baseArrayLayer = 0;
			Image_Sub_Resource_Range.layerCount = Layer_Count;
			Image_Sub_Resource_Range.levelCount = 1;
		}

		VkImageMemoryBarrier Barrier{};
		{
			Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
			Barrier.image = Image;
			Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			Barrier.subresourceRange = Image_Sub_Resource_Range;
		}

		int32_t Mip_Width = Image_ExTent_2D.width;
		int32_t Mip_Height = Image_ExTent_2D.height;
		for (uint32_t Mip_Level = 1; Mip_Level < Mip_Levels; ++Mip_Level) {
			Barrier.subresourceRange.baseMipLevel = Mip_Level - 1;
			Barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
			Barrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
			Barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
			Barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;

			vkCmdPipelineBarrier(
				Command_Buffer,
				VK_PIPELINE_STAGE_TRANSFER_BIT,
				VK_PIPELINE_STAGE_TRANSFER_BIT,
				0,
				0, nullptr,
				0, nullptr,
				1, &Barrier
			);

			VkImageBlit Blit{};
			{
				{
					Blit.srcOffsets[0] = { 0,0,0 };
					Blit.srcOffsets[1] = { Mip_Width,Mip_Height,1 };
					Blit.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
					Blit.srcSubresource.mipLevel = Mip_Level - 1;
					Blit.srcSubresource.baseArrayLayer = 0;
					Blit.srcSubresource.layerCount = Layer_Count;
				}

				{
					Blit.dstOffsets[0] = { 0,0,0 };
					Blit.dstOffsets[1] = {
						Mip_Width > 1 ? Mip_Width / 2 : 1,
						Mip_Height > 1 ? Mip_Height / 2 : 1,
						1
					};
					Blit.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
					Blit.dstSubresource.mipLevel = Mip_Level;
					Blit.dstSubresource.baseArrayLayer = 0;
					Blit.dstSubresource.layerCount = Layer_Count;
				}
			}

			vkCmdBlitImage(
				Command_Buffer,
				Image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
				Image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
				1, &Blit,
				VK_FILTER_LINEAR
			);

			{
				Barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
				Barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
				Barrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
				Barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
			}

			vkCmdPipelineBarrier(
				Command_Buffer,
				VK_PIPELINE_STAGE_TRANSFER_BIT,
				VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
				0,
				0, nullptr,
				0, nullptr,
				1, &Barrier
			);

			if (Mip_Width > 1) Mip_Width /= 2;
			if (Mip_Height > 1) Mip_Height /= 2;
		}

		{
			Barrier.subresourceRange.baseMipLevel = Mip_Levels - 1;
			Barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
			Barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			Barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
			Barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
		}

		vkCmdPipelineBarrier(
			Command_Buffer,
			VK_PIPELINE_STAGE_TRANSFER_BIT,
			VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
			0,
			0, nullptr,
			0, nullptr,
			1, &Barrier
		);

		End_SingleTIme_Commands(Logical_Device, Command_Pool, Graphics_Queue, Command_Buffer);
	}

	void Create_Global_Image(VkPhysicalDevice Physical_Device, VkDevice Logical_Device, const VkAllocationCallbacks* VK_Allocator, VkCommandPool Command_Pool, VkQueue Graphics_Queue, VmaAllocator VMA_Allocator, VkExtent2D Image_Extent, VkFormat Format, uint32_t Mip_levels, void* Image_Pixels, VkImage& Image, VkImageView& Image_View, VmaAllocation& Image_Allocation) {
		VkDeviceSize Image_Byte_Size{ Get_Image_Byte_Size(Image_Extent.width, Image_Extent.height, Format) };

		VkBuffer Staging_Buffer{ nullptr };
		VkDeviceMemory Staging_Memory{ nullptr };
		Create_Buffer(
			Physical_Device,
			Logical_Device,
			Image_Byte_Size,
			VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
			VK_Allocator,
			Staging_Buffer,
			Staging_Memory);

		void* Dst_Data{ nullptr };
		vkMapMemory(Logical_Device, Staging_Memory, 0, Image_Byte_Size, 0, &Dst_Data);
		memcpy(Dst_Data, Image_Pixels, static_cast<size_t>(Image_Byte_Size));
		vkUnmapMemory(Logical_Device, Staging_Memory);

		VkImageCreateInfo Image_Create_Info{};
		{
			Image_Create_Info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
			Image_Create_Info.flags = 0;
			Image_Create_Info.imageType = VK_IMAGE_TYPE_2D;
			Image_Create_Info.format = Format;
			Image_Create_Info.extent = { Image_Extent.width, Image_Extent.height, 1 };
			Image_Create_Info.mipLevels = Mip_levels;
			Image_Create_Info.arrayLayers = 1;
			Image_Create_Info.samples = VK_SAMPLE_COUNT_1_BIT;
			Image_Create_Info.tiling = VK_IMAGE_TILING_OPTIMAL;
			Image_Create_Info.usage = VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
			Image_Create_Info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
			Image_Create_Info.queueFamilyIndexCount = 0;//TODO : Set this
			Image_Create_Info.pQueueFamilyIndices = nullptr;
			Image_Create_Info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		}

		VmaAllocationCreateInfo Allocation_Create_Info{};
		{
			Allocation_Create_Info.usage = VMA_MEMORY_USAGE_GPU_ONLY;
		}

		vmaCreateImage(
			VMA_Allocator,
			&Image_Create_Info,
			&Allocation_Create_Info,
			&Image,
			&Image_Allocation,
			VK_NULL_HANDLE
		);

		Transition_Image_Layout(
			Logical_Device,
			Command_Pool,
			Graphics_Queue,
			Image,
			Mip_levels,
			Format,
			VK_IMAGE_ASPECT_COLOR_BIT,
			VK_IMAGE_LAYOUT_UNDEFINED,
			VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
			1
		);

		Copy_Buffer_To_Image(
			Logical_Device,
			Command_Pool,
			Graphics_Queue,
			Staging_Buffer,
			Image,
			Image_Extent,
			1
		);

		vkDestroyBuffer(Logical_Device, Staging_Buffer, VK_Allocator);
		vkFreeMemory(Logical_Device, Staging_Memory, VK_Allocator);

		Generate_Mipmaps(
			Physical_Device,
			Logical_Device,
			Command_Pool,
			Graphics_Queue,
			Image,
			Image_Extent,
			Format,
			Mip_levels,
			1
		);

		Image_View = Create_Image_View(
			Logical_Device,
			VK_Allocator,
			Image,
			Format,
			Mip_levels,
			VK_IMAGE_ASPECT_COLOR_BIT,
			VK_IMAGE_VIEW_TYPE_2D,
			1
		);
	}

	void Create_Cube_Map(VkPhysicalDevice Physical_Device, VkDevice Logical_Device, const VkAllocationCallbacks* VK_Allocator, VkCommandPool Command_Pool, VkQueue Graphics_Queue, VmaAllocator VMA_Allocator, VkExtent2D Image_Extent, VkFormat Format, uint32_t Mip_levels, array<void*, 6> Image_Pixels, VkImage& Image, VkImageView& Image_View, VmaAllocation& Image_Allocation) {
		VkDeviceSize
			Image_Byte_Size{ Get_Image_Byte_Size(Image_Extent.width, Image_Extent.height, Format) },
			Cube_Byte_Size{ Image_Byte_Size * 6 };

		VkImageCreateInfo Image_Create_Info{};
		{
			Image_Create_Info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
			Image_Create_Info.flags = VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT;
			Image_Create_Info.imageType = VK_IMAGE_TYPE_2D;
			Image_Create_Info.format = Format;
			Image_Create_Info.extent = { Image_Extent.width, Image_Extent.height, 1 };
			Image_Create_Info.mipLevels = Mip_levels;
			Image_Create_Info.arrayLayers = 6;
			Image_Create_Info.samples = VK_SAMPLE_COUNT_1_BIT;
			Image_Create_Info.tiling = VK_IMAGE_TILING_OPTIMAL;
			Image_Create_Info.usage = VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
			Image_Create_Info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
			Image_Create_Info.queueFamilyIndexCount = 0;//TODO : Set this
			Image_Create_Info.pQueueFamilyIndices = nullptr;
			Image_Create_Info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		}

		VmaAllocationCreateInfo Allocation_Create_Info{};
		{
			Allocation_Create_Info.usage = VMA_MEMORY_USAGE_GPU_ONLY;
		}

		vmaCreateImage(
			VMA_Allocator,
			&Image_Create_Info,
			&Allocation_Create_Info,
			&Image,
			&Image_Allocation,
			VK_NULL_HANDLE
		);

		VkBuffer Staging_Buffer{ nullptr };
		VkDeviceMemory Staging_Memory{ nullptr };
		Create_Buffer(
			Physical_Device,
			Logical_Device,
			Image_Byte_Size,
			VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
			VK_Allocator,
			Staging_Buffer,
			Staging_Memory
		);

		void* Dst_Data{ nullptr };
		vkMapMemory(Logical_Device, Staging_Memory, 0, Cube_Byte_Size, 0, &Dst_Data);
		for (size_t Index = 0; Index < 6; ++Index)
			memcpy(
				static_cast<unsigned char*>(Dst_Data) + Image_Byte_Size * Index,
				Image_Pixels[Index],
				static_cast<size_t>(Image_Byte_Size)
			);
		vkUnmapMemory(Logical_Device, Staging_Memory);

		Transition_Image_Layout(
			Logical_Device,
			Command_Pool,
			Graphics_Queue,
			Image,
			Mip_levels,
			Format,
			VK_IMAGE_ASPECT_COLOR_BIT,
			VK_IMAGE_LAYOUT_UNDEFINED,
			VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
			6
		);

		Copy_Buffer_To_Image(
			Logical_Device,
			Command_Pool,
			Graphics_Queue,
			Staging_Buffer,
			Image,
			Image_Extent,
			6
		);

		vkDestroyBuffer(Logical_Device, Staging_Buffer, VK_Allocator);
		vkFreeMemory(Logical_Device, Staging_Memory, VK_Allocator);

		Generate_Mipmaps(
			Physical_Device,
			Logical_Device,
			Command_Pool,
			Graphics_Queue,
			Image,
			Image_Extent,
			Format,
			Mip_levels,
			6
		);

		Image_View = Create_Image_View(
			Logical_Device,
			VK_Allocator,
			Image,
			Format,
			Mip_levels,
			VK_IMAGE_ASPECT_COLOR_BIT,
			VK_IMAGE_VIEW_TYPE_CUBE,
			6
		);
	}







	const VkShaderModule Create_Shader_Module(VkDevice Logical_Device, const vector<unsigned char>& Code) {
		VkShaderModuleCreateInfo Create_Info{};
		{
			Create_Info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
			Create_Info.codeSize = Code.size();
			Create_Info.pCode = reinterpret_cast<const uint32_t*>(Code.data());
		}

		VkShaderModule Shader_Module{ nullptr };
		THROW_IF_VK_FAILED(vkCreateShaderModule(Logical_Device, &Create_Info, nullptr, &Shader_Module));
		return Shader_Module;
	}






	void Create_Image(
		VkPhysicalDevice Physical_Device,
		VkDevice Device,
		VkExtent2D Image_Extent,
		VkFormat Format,
		uint32_t Mip_levels,
		VkSampleCountFlagBits Samples,
		VkImageTiling Image_Tiling,
		VkImageUsageFlags Image_Usage_Flags,
		VkMemoryPropertyFlags Memory_Property_Flags,
		VkImage& Image,
		VkDeviceMemory& Memory,
		VkImageCreateFlags Image_Create_Flags,
		uint32_t Array_Layers,
		const VkAllocationCallbacks* pAllocator) {
		VkImageCreateInfo Image_Info{};
		{
			Image_Info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
			Image_Info.imageType = VK_IMAGE_TYPE_2D;
			Image_Info.extent = { Image_Extent.width, Image_Extent.height, 1 };
			Image_Info.mipLevels = Mip_levels;
			Image_Info.arrayLayers = Array_Layers;
			Image_Info.format = Format;
			Image_Info.tiling = Image_Tiling;
			Image_Info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			Image_Info.usage = Image_Usage_Flags;
			Image_Info.samples = Samples;
			Image_Info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
			Image_Info.flags = Image_Create_Flags;
		}

		THROW_IF_VK_FAILED(vkCreateImage(Device, &Image_Info, nullptr, &Image));

		VkMemoryRequirements Memory_Requirements{};
		vkGetImageMemoryRequirements(Device, Image, &Memory_Requirements);

		VkMemoryAllocateInfo Memory_Allocate_Info{};
		{
			Memory_Allocate_Info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
			Memory_Allocate_Info.allocationSize = Memory_Requirements.size;
			Memory_Allocate_Info.memoryTypeIndex = Find_Memory_Type(Physical_Device, Memory_Requirements.memoryTypeBits, Memory_Property_Flags);
		}

		THROW_IF_VK_FAILED(vkAllocateMemory(Device, &Memory_Allocate_Info, pAllocator, &Memory));
		THROW_IF_VK_FAILED(vkBindImageMemory(Device, Image, Memory, 0));
	}




	/*void Create_Image(
		VkDevice Logical_Device,
		uint32_t Width,
		uint32_t Height,
		uint32_t Mip_Levels,
		VkFormat Format,
		VkSampleCountFlagBits Num_Samples,
		VkImageTiling Tiling,
		VkImageUsageFlags Usage,
		VkMemoryPropertyFlags Properties,
		VkImage& Image,
		VkDeviceMemory& Image_Memory) {
		VkImageCreateInfo Image_Create_Info{};
		{
			Image_Create_Info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
			Image_Create_Info.imageType = VK_IMAGE_TYPE_2D;
			Image_Create_Info.extent.width = Width;
			Image_Create_Info.extent.height = Height;
			Image_Create_Info.extent.depth = 1;
			Image_Create_Info.mipLevels = Mip_Levels;
			Image_Create_Info.arrayLayers = 1;
			Image_Create_Info.format = Format;
			Image_Create_Info.tiling = Tiling;
			Image_Create_Info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			Image_Create_Info.usage = Usage;
			Image_Create_Info.samples = Num_Samples;
			Image_Create_Info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		}

		THROW_IF_VK_FAILED(vkCreateImage(this->m_Logical_Device.get(), &Image_Create_Info, nullptr, &Image));

		VkMemoryRequirements Memory_Requirements{};
		vkGetImageMemoryRequirements(this->m_Logical_Device.get(), Image, &Memory_Requirements);

		VkMemoryAllocateInfo Memory_Allocate_Info{};
		{
			Memory_Allocate_Info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
			Memory_Allocate_Info.allocationSize = Memory_Requirements.size;
			Memory_Allocate_Info.memoryTypeIndex = this->Find_Memory_Type(Memory_Requirements.memoryTypeBits, Properties);
		}

		THROW_IF_VK_FAILED(vkAllocateMemory(this->m_Logical_Device.get(), &Memory_Allocate_Info, nullptr, &Image_Memory));

		THROW_IF_VK_FAILED(vkBindImageMemory(this->m_Logical_Device.get(), Image, Image_Memory, 0));
	}*/


}// namespace NameSpace_Function::NameSpace_Render::NameSpace_RHI::NameSpace_Vulkan_RHI::NameSpace_Utilities