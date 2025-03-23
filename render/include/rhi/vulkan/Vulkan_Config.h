#pragma once

namespace NameSpace_Render::NameSpace_RHI::NameSpace_Vulkan_RHI::NameSpace_Config {

	constexpr const char* Vulkan_Layer_Path{ "D:/Amy_Engine/third_party/VulkanSDK/1.4.309.0/Bin" };

	constexpr const int Validation_Layer_Size{ 1 };

	constexpr const char* Validation_Layers[]{ "VK_LAYER_KHRONOS_validation" };

	constexpr int API_Verssion = VK_API_VERSION_1_0;

	constexpr int Device_EXT_Size{ 1 };

	constexpr const char* Device_EXTs{ VK_KHR_SWAPCHAIN_EXTENSION_NAME };

	constexpr uint32_t Max_Vertex_Blending_Mesh_Count{ 256 };
	constexpr uint32_t Max_Material_Count{ 256 };

} // namespace NameSpace_Render::NameSpace_RHI::NameSpace_Vulkan_RHI::NameSpace_Config
