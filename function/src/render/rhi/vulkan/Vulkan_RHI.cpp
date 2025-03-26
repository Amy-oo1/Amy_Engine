#include "render/rhi/vulkan/Vulkan_RHI.h"

#if defined(_MSC_VER)
#include <sdkddkver.h>
#define WIN32_LEAN_AND_MEAN 1
#define NOGDICAPMASKS 1
#define NOVIRTUALKEYCODES 1
#define NOWINMESSAGES 1
#define NOWINSTYLES 1
#define NOSYSMETRICS 1
#define NOMENUS 1
#define NOICONS 1
#define NOKEYSTATES 1
#define NOSYSCOMMANDS 1
#define NORASTEROPS 1
#define NOSHOWWINDOW 1
#define NOATOM 1
#define NOCLIPBOARD 1
#define NOCOLOR 1
#define NOCTLMGR 1
#define NODRAWTEXT 1
#define NOGDI 1
#define NOKERNEL 1
#define NOUSER 1
#define NONLS 1
#define NOMB 1
#define NOMEMMGR 1
#define NOMETAFILE 1
#define NOMINMAX 1
#define NOMSG 1
#define NOOPENFILE 1
#define NOSCROLL 1
#define NOSERVICE 1
#define NOSOUND 1
#define NOTEXTMETRIC 1
#define NOWH 1
#define NOWINOFFSETS 1
#define NOCOMM 1
#define NOKANJI 1
#define NOHELP 1
#define NOPROFILER 1
#define NODEFERWINDOWPOS 1
#define NOMCX 1
#include <Windows.h>
#else
#error Unknown Compiler
#endif

#include<iostream>
#include<sstream>
#include<stdexcept>
#include<unordered_set>
#include<unordered_map>
#include<functional>
#include<algorithm>
#include<mutex>

#include "logger/System_Logger.h"

#include "render/rhi/vulkan/Vulkan_RHI_Macro.h"
#include "render/rhi/vulkan/Vulkan_Config.h"
#include "render/rhi/vulkan/Vulkan_Utilities.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_RHI::NameSpace_Vulkan_RHI {

	static std::mutex g_alloc_mutex;

	using std::unordered_set;
	using std::unordered_map;
	using std::function;
	using std::runtime_error;

	using NameSpace_Core::NameSpace_Logger::System_Logger;

	//NOTE : Constructor
	Vulkan_RHI::Vulkan_RHI(const RHI_Initialization_Info& init_info) :
		Empty_RHI{},
		m_Window{ init_info.Window_System },
		m_Viewport{ 0.f,0.f,static_cast<float>(init_info.Window_System->Get_Window_Width()),static_cast<float>(init_info.Window_System->Get_Window_Height()),0.f,1.f },
		m_Scissor{ {0,0},{init_info.Window_System->Get_Window_Width(),init_info.Window_System->Get_Window_Height()} } {

		//NOTE : Init Info
#ifdef _MSC_VER
		SetEnvironmentVariableA("VK_LAYER_PATH", NameSpace_Config::Vulkan_Layer_Path);
		//SetEnvironmentVariableA("DISABLE_LAYER_AMD_SWITCHABLE_GRAPHICS_1", "1");
#else
#error Unsupported compiler
#endif // _MSC_VER

		//NOTE : Init Debug Info
#ifdef _DEBUG
		this->m_Validation_Layers.reserve(NameSpace_Config::Validation_Layer_Size);
		for (int Index = 0; Index < NameSpace_Config::Validation_Layer_Size; ++Index)
			this->m_Validation_Layers.emplace_back(NameSpace_Config::Validation_Layers[Index]);
#endif // _DEBUG
	}

	Vulkan_RHI::~Vulkan_RHI() {
		//TODO : Destroy All Vulkan Resource

		for (auto& Command_Pool : this->m_RHI_Command_Pools)
			Command_Pool.reset();
		this->m_Default_RHI_Command_Pool.reset();

		this->m_RHI_Logical_Device.reset();

		this->m_VK_Surface.reset();

		this->m_RHI_Instance.reset();
	}

	//NOTE : Mraco Debug
#ifdef _DEBUG
	bool Vulkan_RHI::Check_Vaildation_Layer_Support(void) {
		uint32_t Layer_Count;
		THROW_IF_VK_FAILED(vkEnumerateInstanceLayerProperties(&Layer_Count, nullptr));

		vector<VkLayerProperties> Available_Layers{};
		Available_Layers.resize(Layer_Count);
		THROW_IF_VK_FAILED(vkEnumerateInstanceLayerProperties(&Layer_Count, Available_Layers.data()));

		for (const auto& Layer_Name : this->m_Validation_Layers) {
			bool layer_Is_Found = false;

			for (const auto& Layer_Propery : Available_Layers)
				if (string{ Layer_Name } == string{ Layer_Propery.layerName }) {
					layer_Is_Found = true;
					break;
				}

			if (!layer_Is_Found)
				return false;
		}

		return true;
	}

	VKAPI_ATTR VkBool32 VKAPI_CALL Vulkan_RHI::Debug_Call_Back(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
		std::cerr << "Validation layer: " << pCallbackData->pMessage << std::endl;

		//NOTE : This Return Common Is VK_FALSE, We Should Not  Debug Failedtaion Layer Just it's Warning
		return VK_FALSE;
	}

	void Vulkan_RHI::Build_Debug_Messenger_Create_Info(void) {
		this->m_Vk_Debug_Utils_Messenger_Create_Info_EXT.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		this->m_Vk_Debug_Utils_Messenger_Create_Info_EXT.messageSeverity =
			//VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;

		this->m_Vk_Debug_Utils_Messenger_Create_Info_EXT.messageType =
			VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

		this->m_Vk_Debug_Utils_Messenger_Create_Info_EXT.pfnUserCallback = Vulkan_RHI::Debug_Call_Back;
		this->m_Vk_Debug_Utils_Messenger_Create_Info_EXT.pUserData = nullptr;
	}

	const VkResult Vulkan_RHI::Create_DebugUtils_Messenger_EXT(VkInstance Instance, const VkDebugUtilsMessengerCreateInfoEXT* Create_Info, const VkAllocationCallbacks* Allocator, VkDebugUtilsMessengerEXT* m_Debug_Messenger) {
		auto Func = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(Instance, "vkCreateDebugUtilsMessengerEXT"));
		if (nullptr != Func)
			return Func(Instance, Create_Info, Allocator, m_Debug_Messenger);
		else
			return VK_ERROR_EXTENSION_NOT_PRESENT;
	}

	void Vulkan_RHI::Destroy_DebugUtils_Messenger_EXT(VkInstance Instance, VkDebugUtilsMessengerEXT m_Debug_Messenger, const VkAllocationCallbacks* Allocator) {
		auto Func = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(Instance, "vkDestroyDebugUtilsMessengerEXT"));

		if (nullptr != Func)
			Func(Instance, m_Debug_Messenger, Allocator);
	}

	void Vulkan_RHI::Set_Debug_Messenger() {
		THROW_IF_VK_FAILED(Vulkan_RHI::Create_DebugUtils_Messenger_EXT(
			static_cast<Vulkan_Instance*>(this->m_RHI_Instance.get())->Get(),
			&this->m_Vk_Debug_Utils_Messenger_Create_Info_EXT,
			this->m_Allocator.get(),
			&this->m_Debug_Messenger)
		);

		F_vkCmdBeginDebugUtilsLabelEXT = reinterpret_cast<PFN_vkCmdBeginDebugUtilsLabelEXT>(vkGetInstanceProcAddr(static_cast<Vulkan_Instance*>(this->m_RHI_Instance.get())->Get(), "vkCmdBeginDebugUtilsLabelEXT"));
		F_vkCmdEndDebugUtilsLabelEXT = reinterpret_cast<PFN_vkCmdEndDebugUtilsLabelEXT>(vkGetInstanceProcAddr(static_cast<Vulkan_Instance*>(this->m_RHI_Instance.get())->Get(), "vkCmdEndDebugUtilsLabelEXT"));
	}
#endif // _DEBUG

	//Public Func
	void Vulkan_RHI::Create_Surface(void) {
		VkSurfaceKHR Surface{ nullptr };
		THROW_IF_VK_FAILED(glfwCreateWindowSurface(static_cast<Vulkan_Instance*>(this->m_RHI_Instance.get())->Get(), this->m_Window->Get_Window(), this->m_Allocator.get(), &Surface));
		this->m_VK_Surface.reset(Surface);
	}

	void Vulkan_RHI::Create_Default_Command_Pool(void) {
		//NOTE : Default Graphics Command Pool
		{
			VkCommandPoolCreateInfo Command_Pool_Create_Info{};
			{
				Command_Pool_Create_Info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
				Command_Pool_Create_Info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
				Command_Pool_Create_Info.queueFamilyIndex = this->m_Queue_Family_Indices.Graphics_Family;
			}

			THROW_IF_VK_FAILED(vkCreateCommandPool(this->m_Logical_VK_Device, &Command_Pool_Create_Info, this->m_Allocator.get(), &this->m_Default_VK_Command_Pool));
			static_cast<Vulkan_Command_Pool*>(this->m_Default_RHI_Command_Pool.get())->Reset(m_Default_VK_Command_Pool);
		}

		//NOTE : Other Command Pools
		{
			VkCommandPoolCreateInfo Command_Pool_Create_Info{};
			{
				Command_Pool_Create_Info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
				Command_Pool_Create_Info.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
				Command_Pool_Create_Info.queueFamilyIndex = this->m_Queue_Family_Indices.Graphics_Family;
			}

			for (uint32_t Index = 0; Index < s_Frames_In_Flight; ++Index) {
				THROW_IF_VK_FAILED(vkCreateCommandPool(this->m_Logical_VK_Device, &Command_Pool_Create_Info, this->m_Allocator.get(), &this->m_VK_Command_Pools[Index]));
				static_cast<Vulkan_Command_Pool*>(this->m_RHI_Command_Pools[Index].get())->Reset(this->m_VK_Command_Pools[Index]);
			}

		}
	}

	void Vulkan_RHI::Allocate_Default_Command_Buffers(void) {
		for (uint32_t Index = 0; Index < s_Frames_In_Flight; ++Index) {
			VkCommandBufferAllocateInfo Command_Buffer_Allocate_Info{};
			{
				Command_Buffer_Allocate_Info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
				Command_Buffer_Allocate_Info.commandPool = this->m_VK_Command_Pools[Index];
				Command_Buffer_Allocate_Info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
				Command_Buffer_Allocate_Info.commandBufferCount = 1;
			}

			THROW_IF_VK_FAILED(vkAllocateCommandBuffers(this->m_Logical_VK_Device, &Command_Buffer_Allocate_Info, &this->m_VK_Command_Buffers[Index]));
			static_cast<Vulkan_Command_Buffer*>(this->m_RHI_Command_Buffers[Index].get())->Reset(this->m_VK_Command_Buffers[Index]);
		}
	}

	VmaAllocator Vulkan_RHI::Get_VMA_Allocator(void) const {
		return this->m_VMA_Allocator;
	}

	RHI_Descriptor_Pool* NameSpace_Render::NameSpace_RHI::NameSpace_Vulkan_RHI::Vulkan_RHI::Get_Default_Descriptor_Pool(void) const {
		return this->m_Default_RHI_Descriptor_Pool.get();
	}

	//Private Func
	void Vulkan_RHI::Create_Allocator(void) {

		VkAllocationCallbacks Allocator{};
		{
			Allocator.pUserData = nullptr;
			Allocator.pfnAllocation = static_cast<PFN_vkAllocationFunction>(&Vulkan_RHI::S_Allocation);
			Allocator.pfnReallocation = static_cast<PFN_vkReallocationFunction>(&Vulkan_RHI::S_Reallocation);
			Allocator.pfnFree = static_cast<PFN_vkFreeFunction>(&Vulkan_RHI::S_Free);
			Allocator.pfnInternalAllocation = nullptr;
			Allocator.pfnInternalFree = nullptr;
		}

		//this->m_Allocator = std::make_unique<VkAllocationCallbacks>(Allocator);
	}

	void Vulkan_RHI::Reset_Instance_Deleters(VkInstance Instance, const VkAllocationCallbacks* Allocator) {
		if (nullptr == Instance)
			throw runtime_error("Vulkan instance is nullptr!");

		{
			this->m_VK_Instance_Deleter = [Allocator](VkInstance Instance) {if (nullptr != Instance) vkDestroyInstance(Instance, Allocator); };
			this->m_VK_Surface_Deleter = [Instance, Allocator](VkSurfaceKHR Surface) {if (nullptr != Surface)vkDestroySurfaceKHR(Instance, Surface, Allocator); };
			this->m_VK_Device_Deleter = [Instance, Allocator](VkDevice Device) {if (nullptr != Device)vkDestroyDevice(Device, Allocator); };
		}

		{
			static_cast<Vulkan_Instance*>(this->m_RHI_Instance.get())->Set_Deleter(this->m_VK_Instance_Deleter);
			this->m_VK_Surface.get_deleter() = this->m_VK_Surface_Deleter;
			static_cast<Vulkan_Logical_Device*>(this->m_RHI_Logical_Device.get())->Set_Deleter(this->m_VK_Device_Deleter);
		}
	}

	void Vulkan_RHI::Reset_Device_Deleters(VkDevice Device, const VkAllocationCallbacks* pAllocator) {
		if (nullptr == Device)
			throw runtime_error("Vulkan device is nullptr!");

		{
			this->m_VK_Command_Pool_Deleter = [Device, pAllocator](VkCommandPool Command_Pool) {if (nullptr != Command_Pool) vkDestroyCommandPool(Device, Command_Pool, pAllocator); };
			this->m_VK_Descriptor_Pool_Deleter = [Device, pAllocator](VkDescriptorPool Descriptor_Pool) {if (nullptr != Descriptor_Pool) vkDestroyDescriptorPool(Device, Descriptor_Pool, pAllocator); };
			this->m_VK_Semaphore_Deleter = [Device, pAllocator](VkSemaphore Semaphore) {if (nullptr != Semaphore) vkDestroySemaphore(Device, Semaphore, pAllocator); };
			this->m_VK_Fence_Deleter = [Device, pAllocator](VkFence Fence) {if (nullptr != Fence) vkDestroyFence(Device, Fence, pAllocator); };
			this->m_VK_SwapChain_Deleter = [Device, pAllocator](VkSwapchainKHR SwapChain) {if (nullptr != SwapChain) vkDestroySwapchainKHR(Device, SwapChain, pAllocator); };
			this->m_VK_Image_View_Deleter = [Device, pAllocator](VkImageView ImageView) {if (nullptr != ImageView) vkDestroyImageView(Device, ImageView, pAllocator); };

			this->m_VK_Sampler_Deleter = [Device, pAllocator](VkSampler Sampler) {if (nullptr != Sampler) vkDestroySampler(Device, Sampler, pAllocator); };

			this->m_VK_Shader_Module_Deleter = [Device, pAllocator](VkShaderModule Shader_Module) {if (nullptr != Shader_Module) vkDestroyShaderModule(Device, Shader_Module, pAllocator); };

			this->m_VK_Buffer_Deleter = [Device, pAllocator](VkBuffer Buffer) {if (nullptr != Buffer) vkDestroyBuffer(Device, Buffer, pAllocator); };
			this->m_VK_Image_Deleter = [Device, pAllocator](VkImage Image) {if (nullptr != Image) vkDestroyImage(Device, Image, pAllocator); };
			this->m_VK_Device_Memory_Deleter = [Device, pAllocator](VkDeviceMemory Device_Memory) {if (nullptr != Device_Memory) vkFreeMemory(Device, Device_Memory, pAllocator); };

			this->m_VK_Descriptor_Set_Layout_Deleter = [Device, pAllocator](VkDescriptorSetLayout Descriptor_Set_Layout) {if (nullptr != Descriptor_Set_Layout) vkDestroyDescriptorSetLayout(Device, Descriptor_Set_Layout, pAllocator); };

			this->m_VK_Frame_Buffer_Deleter = [Device, pAllocator](VkFramebuffer Frame_Buffer) {if (nullptr != Frame_Buffer) vkDestroyFramebuffer(Device, Frame_Buffer, pAllocator); };

			this->m_VK_Render_Pass_Deleter = [Device, pAllocator](VkRenderPass Render_Pass) {if (nullptr != Render_Pass) vkDestroyRenderPass(Device, Render_Pass, pAllocator); };

			this->m_VK_Pipeline_Deleter = [Device, pAllocator](VkPipeline Pipeline) {if (nullptr != Pipeline) vkDestroyPipeline(Device, Pipeline, pAllocator); };

			this->m_VK_Pipeline_Cache_Deleter = [Device, pAllocator](VkPipelineCache Pipeline_Cache) {if (nullptr != Pipeline_Cache) vkDestroyPipelineCache(Device, Pipeline_Cache, pAllocator); };


			this->m_VK_Pipeline_Layout_Deleter = [Device, pAllocator](VkPipelineLayout Pipeline_Layout) {if (nullptr != Pipeline_Layout) vkDestroyPipelineLayout(Device, Pipeline_Layout, pAllocator); };

		}

		{
			static_cast<Vulkan_Command_Pool*>(this->m_Default_RHI_Command_Pool.get())->Set_Deleter(this->m_VK_Command_Pool_Deleter);
			for (auto& Command_Pool : this->m_RHI_Command_Pools)
				static_cast<Vulkan_Command_Pool*>(Command_Pool.get())->Set_Deleter(this->m_VK_Command_Pool_Deleter);

			static_cast<Vulkan_Descriptor_Pool*>(this->m_RHI_Descriptor_Pool.get())->Set_Deleter(this->m_VK_Descriptor_Pool_Deleter);

			for (uint32_t Index = 0; Index < s_Frames_In_Flight; ++Index) {
				static_cast<Vulkan_Semaphore*>(this->m_Image_available_For_Render_RHI_Semaphores[Index].get())->Set_Deleter(this->m_VK_Semaphore_Deleter);
				static_cast<Vulkan_Semaphore*>(this->m_Image_Finished_For_Present_RHI_Semaphores[Index].get())->Set_Deleter(this->m_VK_Semaphore_Deleter);
				static_cast<Vulkan_Semaphore*>(this->m_Image_Available_For_TeCopy_RHI_Semaphores[Index].get())->Set_Deleter(this->m_VK_Semaphore_Deleter);
				static_cast<Vulkan_Fence*>(this->m_InFlight_RHI_Fences[Index].get())->Set_Deleter(this->m_VK_Fence_Deleter);
			}

			this->m_Vk_SwapChain.get_deleter() = this->m_VK_SwapChain_Deleter;

			for (auto& Image_View : this->m_SwapChain_Image_Views)
				Image_View.get_deleter() = this->m_VK_Image_View_Deleter;

			{
				static_cast<Vulkan_Sampler*>(this->m_Linear_RHI_Sampler.get())->Set_Deleter(this->m_VK_Sampler_Deleter);
				static_cast<Vulkan_Sampler*>(this->m_Nearest_RHI_Sampler.get())->Set_Deleter(this->m_VK_Sampler_Deleter);
			}

		}
	}

	void Vulkan_RHI::Get_Device_ProcAddrs(void) {
		F_vkCmdBeginDebugUtilsLabelEXT = reinterpret_cast<PFN_vkCmdBeginDebugUtilsLabelEXT>(vkGetDeviceProcAddr(this->m_Logical_VK_Device, "vkCmdBeginDebugUtilsLabelEXT"));
		F_vkCmdEndDebugUtilsLabelEXT = reinterpret_cast<PFN_vkCmdEndDebugUtilsLabelEXT>(vkGetDeviceProcAddr(this->m_Logical_VK_Device, "vkCmdEndDebugUtilsLabelEXT"));
		F_vkWaitForFences = reinterpret_cast<PFN_vkWaitForFences>(vkGetDeviceProcAddr(this->m_Logical_VK_Device, "vkWaitForFences"));
		F_vkResetFences = reinterpret_cast<PFN_vkResetFences>(vkGetDeviceProcAddr(this->m_Logical_VK_Device, "vkResetFences"));
		F_vkResetCommandPool = reinterpret_cast<PFN_vkResetCommandPool>(vkGetDeviceProcAddr(this->m_Logical_VK_Device, "vkResetCommandPool"));
		F_vkBeginCommandBuffer = reinterpret_cast<PFN_vkBeginCommandBuffer>(vkGetDeviceProcAddr(this->m_Logical_VK_Device, "vkBeginCommandBuffer"));
		F_vkEndCommandBuffer = reinterpret_cast<PFN_vkEndCommandBuffer>(vkGetDeviceProcAddr(this->m_Logical_VK_Device, "vkEndCommandBuffer"));
		F_vkCmdBeginRenderPass = reinterpret_cast<PFN_vkCmdBeginRenderPass>(vkGetDeviceProcAddr(this->m_Logical_VK_Device, "vkCmdBeginRenderPass"));
		F_vkCmdNextSubpass = reinterpret_cast<PFN_vkCmdNextSubpass>(vkGetDeviceProcAddr(this->m_Logical_VK_Device, "vkCmdNextSubpass"));
		F_vkCmdEndRenderPass = reinterpret_cast<PFN_vkCmdEndRenderPass>(vkGetDeviceProcAddr(this->m_Logical_VK_Device, "vkCmdEndRenderPass"));
		F_vkCmdBindPipeline = reinterpret_cast<PFN_vkCmdBindPipeline>(vkGetDeviceProcAddr(this->m_Logical_VK_Device, "vkCmdBindPipeline"));
		F_vkCmdSetViewport = reinterpret_cast<PFN_vkCmdSetViewport>(vkGetDeviceProcAddr(this->m_Logical_VK_Device, "vkCmdSetViewport"));
		F_vkCmdSetScissor = reinterpret_cast<PFN_vkCmdSetScissor>(vkGetDeviceProcAddr(this->m_Logical_VK_Device, "vkCmdSetScissor"));
		F_vkCmdBindVertexBuffers = reinterpret_cast<PFN_vkCmdBindVertexBuffers>(vkGetDeviceProcAddr(this->m_Logical_VK_Device, "vkCmdBindVertexBuffers"));
		F_vkCmdBindIndexBuffer = reinterpret_cast<PFN_vkCmdBindIndexBuffer>(vkGetDeviceProcAddr(this->m_Logical_VK_Device, "vkCmdBindIndexBuffer"));
		F_vkCmdBindDescriptorSets = reinterpret_cast<PFN_vkCmdBindDescriptorSets>(vkGetDeviceProcAddr(this->m_Logical_VK_Device, "vkCmdBindDescriptorSets"));
		F_vkCmdDrawIndexed = reinterpret_cast<PFN_vkCmdDrawIndexed>(vkGetDeviceProcAddr(this->m_Logical_VK_Device, "vkCmdDrawIndexed"));
		F_vkCmdClearAttachments = reinterpret_cast<PFN_vkCmdClearAttachments>(vkGetDeviceProcAddr(this->m_Logical_VK_Device, "vkCmdClearAttachments"));
	}



	//Static Func
	const vector<const char*> Vulkan_RHI::S_Get_Instance_Extensions_Require(void) {
		uint32_t GLFW_Extension_Count{};
		const char** GLFW_Extensions{ glfwGetRequiredInstanceExtensions(&GLFW_Extension_Count) };

		vector<const char*> Extensions{ GLFW_Extensions, GLFW_Extensions + GLFW_Extension_Count };

#ifdef _DEBUG
		Extensions.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif // _DEBUG

		return Extensions;
	}

	void* VKAPI_CALL Vulkan_RHI::S_Allocation(void* pUserData, size_t size, size_t alignment, VkSystemAllocationScope) {
#if defined(_WIN32)
		std::lock_guard<std::mutex> lock(g_alloc_mutex);
		return _aligned_malloc(size, alignment);
#else
		void* ptr = nullptr;
		posix_memalign(&ptr, alignment, size);
		return ptr;
#endif
	}

	void* VKAPI_CALL Vulkan_RHI::S_Reallocation(
		void* pUserData,
		void* original,
		size_t size,
		size_t alignment,
		VkSystemAllocationScope allocationScope) {
		std::lock_guard<std::mutex> lock(g_alloc_mutex);
		if (size == 0) {
			_aligned_free(original);
			return nullptr;
		}

		void* new_mem = _aligned_malloc(size, alignment);
		if (!new_mem) return nullptr;

		_aligned_free(original);
		return new_mem;
	}

	void VKAPI_CALL Vulkan_RHI::S_Free(void* pUserData, void* memory) {
#if defined(_WIN32)
		std::lock_guard<std::mutex> lock(g_alloc_mutex);
		_aligned_free(memory);
#else
		free(memory);
#endif
	}

	const vector<const char*> Vulkan_RHI::S_Get_Physical_Device_Extensions_Require(void) {
		vector<const char*> Physical_Device_Extensions{};
		Physical_Device_Extensions.reserve(NameSpace_Config::Device_EXT_Size);

		for (int Index = 0; Index < NameSpace_Config::Device_EXT_Size; ++Index)
			Physical_Device_Extensions.emplace_back(NameSpace_Config::Device_EXTs);

		return Physical_Device_Extensions;
	}

	bool Vulkan_RHI::S_Check_Physical_Device_Extension_Support(VkPhysicalDevice Device, const vector<const char*>& Require_Extensions) {
		uint32_t Extension_Size{};
		THROW_IF_VK_FAILED(vkEnumerateDeviceExtensionProperties(Device, nullptr, &Extension_Size, nullptr));
		vector<VkExtensionProperties> Available_Extensions{};
		Available_Extensions.resize(Extension_Size);
		THROW_IF_VK_FAILED(vkEnumerateDeviceExtensionProperties(Device, nullptr, &Extension_Size, Available_Extensions.data()));

		std::unordered_set<string> Required_Extensions{};
		for (const auto& Extension : Require_Extensions)
			Required_Extensions.emplace(Extension);

		for (const auto& Available_Extension : Available_Extensions)
			Required_Extensions.erase(string{ Available_Extension.extensionName });//NOTE : extensionName Is const char*

		return Required_Extensions.empty();
	}

	bool Vulkan_RHI::S_Is_Device_Suitable(VkPhysicalDevice Device, const vector<const char*>& Require_Extensions) {
		if (false == S_Check_Physical_Device_Extension_Support(Device, Require_Extensions))
			return false;

		VkPhysicalDeviceProperties Device_Properties{};
		vkGetPhysicalDeviceProperties(Device, &Device_Properties);

		VkPhysicalDeviceFeatures Device_Features{};
		vkGetPhysicalDeviceFeatures(Device, &Device_Features);

		//TODO : Set More Condition
		return
			Device_Properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
			Device_Features.geometryShader &&
			Device_Features.samplerAnisotropy;
	}

	VkSampleCountFlagBits Vulkan_RHI::S_Get_Max_Usable_Sample_Count(VkPhysicalDevice Physical_Device) {
		VkPhysicalDeviceProperties Physical_Device_Properties{};
		vkGetPhysicalDeviceProperties(Physical_Device, &Physical_Device_Properties);
		VkSampleCountFlags Counts{ Physical_Device_Properties.limits.framebufferColorSampleCounts & Physical_Device_Properties.limits.framebufferDepthSampleCounts };

		if (0 != (Counts & VK_SAMPLE_COUNT_64_BIT)) return VK_SAMPLE_COUNT_64_BIT;
		if (0 != (Counts & VK_SAMPLE_COUNT_32_BIT)) return VK_SAMPLE_COUNT_32_BIT;
		if (0 != (Counts & VK_SAMPLE_COUNT_16_BIT)) return VK_SAMPLE_COUNT_16_BIT;
		if (0 != (Counts & VK_SAMPLE_COUNT_8_BIT)) return VK_SAMPLE_COUNT_8_BIT;
		if (0 != (Counts & VK_SAMPLE_COUNT_4_BIT)) return VK_SAMPLE_COUNT_4_BIT;
		if (0 != (Counts & VK_SAMPLE_COUNT_2_BIT)) return VK_SAMPLE_COUNT_2_BIT;
		return VK_SAMPLE_COUNT_1_BIT;
	}

	uint32_t Vulkan_RHI::S_Find_Queue_Families(VkPhysicalDevice Physical_Device, VkQueueFlagBits Vk_Queue_FlagBit) {
		uint32_t Queue_Family_Count;
		vkGetPhysicalDeviceQueueFamilyProperties(Physical_Device, &Queue_Family_Count, nullptr);

		vector<VkQueueFamilyProperties> Queue_Families;
		Queue_Families.resize(Queue_Family_Count);
		vkGetPhysicalDeviceQueueFamilyProperties(Physical_Device, &Queue_Family_Count, Queue_Families.data());

		for (auto CIt = Queue_Families.cbegin(); CIt != Queue_Families.cend(); ++CIt)
			if (CIt->queueFlags & Vk_Queue_FlagBit)
				return  static_cast<uint32_t>(CIt - Queue_Families.cbegin());

		throw runtime_error("Failed to find a suitable GPU!");

		return std::numeric_limits<uint32_t>::max();
	}

	uint32_t Vulkan_RHI::S_Get_Physical_Device_Queue_Present_Family(VkPhysicalDevice Physical_Device, VkSurfaceKHR Surface, uint32_t Graphics_Family_Index) {
		uint32_t Queue_Family_Count{};
		vkGetPhysicalDeviceQueueFamilyProperties(Physical_Device, &Queue_Family_Count, nullptr);

		vector<VkQueueFamilyProperties> Queue_Families{};
		Queue_Families.resize(Queue_Family_Count);
		vkGetPhysicalDeviceQueueFamilyProperties(Physical_Device, &Queue_Family_Count, Queue_Families.data());

		uint32_t Queue_Family_Index{ numeric_limits<uint32_t>::max() };
		for (auto CIt = Queue_Families.cbegin(); CIt != Queue_Families.cend(); ++CIt) {
			VkBool32 Present_Support{ false };
			THROW_IF_VK_FAILED(vkGetPhysicalDeviceSurfaceSupportKHR(Physical_Device, static_cast<uint32_t>(CIt - Queue_Families.cbegin()), Surface, &Present_Support));

			if (Present_Support) {
				Queue_Family_Index = static_cast<uint32_t>(CIt - Queue_Families.cbegin());

				//NOTE : First Chose Queue Family With Graphics Bit
				if (Queue_Family_Index == Graphics_Family_Index)
					return Queue_Family_Index;
			}
		}

		return Queue_Family_Index;
	}

	const Vulkan_RHI::Queue_Family_Indices Vulkan_RHI::S_Get_Queue_Framies(VkPhysicalDevice Physical_Device, VkSurfaceKHR Suraface) {
		Queue_Family_Indices Queue_Family_Indices{};

		Queue_Family_Indices.Graphics_Family = Vulkan_RHI::S_Find_Queue_Families(Physical_Device, VK_QUEUE_GRAPHICS_BIT);
		if (numeric_limits<uint32_t>::max() == Queue_Family_Indices.Graphics_Family)
			throw runtime_error("Failed to find a queue family with graphics bit!");

		//NOTE : Queue Family Should Be Unique,Because It Maybe Same
		Queue_Family_Indices.Present_Family = Vulkan_RHI::S_Get_Physical_Device_Queue_Present_Family(Physical_Device, Suraface, Queue_Family_Indices.Graphics_Family);
		if (numeric_limits<uint32_t>::max() == Queue_Family_Indices.Present_Family)
			throw runtime_error("Failed to find a queue family with present bit!");

		Queue_Family_Indices.Compute_Family = Vulkan_RHI::S_Find_Queue_Families(Physical_Device, VK_QUEUE_COMPUTE_BIT);
		if (numeric_limits<uint32_t>::max() == Queue_Family_Indices.Compute_Family)
			throw runtime_error("Failed to find a queue family with compute bit!");

		return Queue_Family_Indices;
	}

	const optional<VkWriteDescriptorSet> Vulkan_RHI::Parser_RHI_Write_Descriptor_Set(const RHI_Write_Descriptor_Set* Write_Descriptor_Set, optional<vector<VkDescriptorImageInfo>>& Image_Infos, optional<vector<VkDescriptorBufferInfo>>& Buffer_Infos, optional<vector<VkBufferView>>& vk_Buffer_Views) {
		if (nullptr == Write_Descriptor_Set)
			return std::nullopt;

		if (nullptr == Write_Descriptor_Set->Image_Infos || Write_Descriptor_Set->Image_Infos->empty())
			Image_Infos = std::nullopt;
		else {
			Image_Infos = std::make_optional<vector<VkDescriptorImageInfo>>();
			Image_Infos->reserve(Write_Descriptor_Set->Image_Infos->size());
			for (const auto& Image_Info : *Write_Descriptor_Set->Image_Infos) {
				VkDescriptorImageInfo vk_Image_Info{};
				{
					vk_Image_Info.sampler = static_cast<Vulkan_Sampler*>(Image_Info->Sampler)->Get();
					vk_Image_Info.imageView = static_cast<Vulkan_Image_View*>(Image_Info->ImageView)->Get();
					vk_Image_Info.imageLayout = static_cast<VkImageLayout>(Image_Info->Image_Layout);
				}

				Image_Infos->push_back(vk_Image_Info);
			}
		}

		if (nullptr == Write_Descriptor_Set->Buffer_Infos || Write_Descriptor_Set->Buffer_Infos->empty())
			Buffer_Infos = std::nullopt;
		else {
			Buffer_Infos = std::make_optional<vector<VkDescriptorBufferInfo>>();
			Buffer_Infos->reserve(Write_Descriptor_Set->Buffer_Infos->size());
			for (const auto& Buffer_Info : *Write_Descriptor_Set->Buffer_Infos) {
				VkDescriptorBufferInfo vk_Buffer_Info{};
				{
					vk_Buffer_Info.buffer = static_cast<Vulkan_Buffer*>(Buffer_Info->Buffer)->Get();
					vk_Buffer_Info.offset = static_cast<VkDeviceSize>(Buffer_Info->Offset);
					vk_Buffer_Info.range = static_cast<VkDeviceSize>(Buffer_Info->Range);
				}

				Buffer_Infos->push_back(vk_Buffer_Info);
			}
		}

		if (nullptr == Write_Descriptor_Set->Texel_Buffer_Views || Write_Descriptor_Set->Texel_Buffer_Views->empty())
			vk_Buffer_Views = std::nullopt;
		else {
			vk_Buffer_Views = std::make_optional<vector<VkBufferView>>();
			vk_Buffer_Views->reserve(Write_Descriptor_Set->Texel_Buffer_Views->size());

			for (const auto& Buffer_View : *Write_Descriptor_Set->Texel_Buffer_Views)
				vk_Buffer_Views->push_back(static_cast<Vulkan_Buffer_View*>(Buffer_View)->Get());
		}

		VkWriteDescriptorSet vk_Write_Descriptor_Set{};
		{
			vk_Write_Descriptor_Set.sType = static_cast<VkStructureType>(Write_Descriptor_Set->sType);
			vk_Write_Descriptor_Set.pNext = Write_Descriptor_Set->pNext;
			vk_Write_Descriptor_Set.dstSet = static_cast<Vulkan_Descriptor_Set*>(Write_Descriptor_Set->Dst_Set)->Get();
			vk_Write_Descriptor_Set.dstBinding = Write_Descriptor_Set->Dst_Binding;
			vk_Write_Descriptor_Set.dstArrayElement = Write_Descriptor_Set->Dst_Array_Element;
			vk_Write_Descriptor_Set.descriptorCount = Write_Descriptor_Set->Descriptor_Count;
			vk_Write_Descriptor_Set.descriptorType = static_cast<VkDescriptorType>(Write_Descriptor_Set->Descriptor_Type);
			vk_Write_Descriptor_Set.pImageInfo = Image_Infos.has_value() ? Image_Infos->data() : nullptr;
			vk_Write_Descriptor_Set.pBufferInfo = Buffer_Infos.has_value() ? Buffer_Infos->data() : nullptr;
			vk_Write_Descriptor_Set.pTexelBufferView = vk_Buffer_Views.has_value() ? vk_Buffer_Views->data() : nullptr;
		}

		return std::make_optional(vk_Write_Descriptor_Set);
	}






	//NOTE : Override Func
	void Vulkan_RHI::Create_Instance(void) {
		if (nullptr != static_cast<Vulkan_Instance*>(this->m_RHI_Instance.get())->Get())
			throw runtime_error("Vulkan Instance Already Created!");

#ifdef _DEBUG
		if (false == this->Check_Vaildation_Layer_Support())
			System_Logger::Get_Instance().Log(System_Logger::Level::err, "Validation layers requested, but not available!");

		this->Build_Debug_Messenger_Create_Info();
#endif // _DEBUG

		VkApplicationInfo VK_Application_Info{};
		{
			VK_Application_Info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
			VK_Application_Info.pApplicationName = "Amy_Engine_Render";
			VK_Application_Info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
			VK_Application_Info.pEngineName = "Amy_Engine";
			VK_Application_Info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
			VK_Application_Info.apiVersion = NameSpace_Config::API_Verssion;
		}

		const auto& Extensions = Vulkan_RHI::S_Get_Instance_Extensions_Require();

		VkInstanceCreateInfo Instance_Create_Info = {};
		{
			Instance_Create_Info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			Instance_Create_Info.pApplicationInfo = &VK_Application_Info;
#ifdef _DEBUG
			Instance_Create_Info.pNext = reinterpret_cast<const void*>(&this->m_Vk_Debug_Utils_Messenger_Create_Info_EXT);
			Instance_Create_Info.enabledLayerCount = static_cast<uint32_t>(this->m_Validation_Layers.size());
			Instance_Create_Info.ppEnabledLayerNames = this->m_Validation_Layers.data();
#else
			Instance_Create_Info.pNext = nullptr;
			Instance_Create_Info.enabledLayerCount = 0;
			Instance_Create_Info.ppEnabledLayerNames = nullptr;
#endif // _DEBUG
			Instance_Create_Info.enabledExtensionCount = static_cast<uint32_t>(Extensions.size());
			Instance_Create_Info.ppEnabledExtensionNames = Extensions.data();
		}

		VkInstance VK_Instance{ nullptr };
		THROW_IF_VK_FAILED(vkCreateInstance(&Instance_Create_Info, this->m_Allocator.get(), &VK_Instance));
		static_cast<Vulkan_Instance*>(this->m_RHI_Instance.get())->Reset(VK_Instance);

		this->Reset_Instance_Deleters(static_cast<Vulkan_Instance*>(this->m_RHI_Instance.get())->Get(), this->m_Allocator.get());

#ifdef _DEBUG
		this->Set_Debug_Messenger();
#endif // _DEBUG
	}

	RHI_Instance* Vulkan_RHI::Get_Instance(void) {
		return this->m_RHI_Instance.get();
	}

	void Vulkan_RHI::Create_Physical_Device(void) {
		uint32_t Device_Count{ 0 };
		THROW_IF_VK_FAILED(vkEnumeratePhysicalDevices(static_cast<Vulkan_Instance*>(this->m_RHI_Instance.get())->Get(), &Device_Count, nullptr));
		if (0 == Device_Count)
			throw runtime_error("Failed to find GPUs with Vulkan support!");

		this->m_Physical_Device_Extensions = Vulkan_RHI::S_Get_Physical_Device_Extensions_Require();

		//TODO : Choose Better Device
		vector<VkPhysicalDevice> Devices{};
		Devices.resize(Device_Count);
		THROW_IF_VK_FAILED(vkEnumeratePhysicalDevices(static_cast<Vulkan_Instance*>(this->m_RHI_Instance.get())->Get(), &Device_Count, Devices.data()));
		for (const auto& Device : Devices)
			if (S_Is_Device_Suitable(Device, this->m_Physical_Device_Extensions)) {
				this->m_VK_Physical_Device = Device;
				break;
			}

		static_cast<Vulkan_Physical_Device*>(this->m_RHI_Physical_Device.get())->Reset(this->m_VK_Physical_Device);

		if (nullptr == this->m_VK_Physical_Device)
			throw runtime_error("Failed to find a suitable GPU!");

		//NOTE : Note Phyiscsal Device Info
		this->m_Msaa_Samples = S_Get_Max_Usable_Sample_Count(this->m_VK_Physical_Device);
	}

	const RHI_Physical_Device_Properties Vulkan_RHI::Get_Physical_Device_Properties(void) {
		VkPhysicalDeviceProperties VK_Physical_Device_Properties;
		vkGetPhysicalDeviceProperties(this->m_VK_Physical_Device, &VK_Physical_Device_Properties);

		RHI_Physical_Device_Properties Properties{};
		{
			Properties.Api_Version = VK_Physical_Device_Properties.apiVersion;
			Properties.Driver_Version = VK_Physical_Device_Properties.driverVersion;
			Properties.Vendor_ID = VK_Physical_Device_Properties.vendorID;
			Properties.Device_ID = VK_Physical_Device_Properties.deviceID;
			Properties.Device_Type = static_cast<RHI_PHYSICAL_DEVICE_TYPE>(VK_Physical_Device_Properties.deviceType);
			for (uint32_t Index = 0; Index < RHI_MAX_PHYSICAL_DEVICE_NAME_SIZE; ++Index)
				Properties.Device_Name[Index] = VK_Physical_Device_Properties.deviceName[Index];
			for (uint32_t Index = 0; Index < RHI_UUID_SIZE; ++Index)
				Properties.Pipeline_Cache_UUID[Index] = VK_Physical_Device_Properties.pipelineCacheUUID[Index];
			Properties.Sparse_Properties.Residency_Standard_2D_Block_Shapes = static_cast<VkBool32>(VK_Physical_Device_Properties.sparseProperties.residencyStandard2DBlockShape);
			Properties.Sparse_Properties.Residency_Standard_2D_Multisample_Block_Shapes = static_cast<VkBool32>(VK_Physical_Device_Properties.sparseProperties.residencyStandard2DMultisampleBlockShape);
			Properties.Sparse_Properties.Residency_Standard_3D_Block_Shapes = static_cast<VkBool32>(VK_Physical_Device_Properties.sparseProperties.residencyStandard3DBlockShape);
			Properties.Sparse_Properties.Residency_Aligned_Mip_Size = static_cast<VkBool32>(VK_Physical_Device_Properties.sparseProperties.residencyAlignedMipSize);
			Properties.Sparse_Properties.Residency_Non_Resident_Strict = static_cast<VkBool32>(VK_Physical_Device_Properties.sparseProperties.residencyNonResidentStrict);

			Properties.Limits.maxImageDimension1D = VK_Physical_Device_Properties.limits.maxImageDimension1D;
			Properties.Limits.maxImageDimension2D = VK_Physical_Device_Properties.limits.maxImageDimension2D;
			Properties.Limits.maxImageDimension3D = VK_Physical_Device_Properties.limits.maxImageDimension3D;
			Properties.Limits.maxImageDimensionCube = VK_Physical_Device_Properties.limits.maxImageDimensionCube;
			Properties.Limits.maxImageArrayLayers = VK_Physical_Device_Properties.limits.maxImageArrayLayers;
			Properties.Limits.maxTexelBufferElements = VK_Physical_Device_Properties.limits.maxTexelBufferElements;
			Properties.Limits.maxUniformBufferRange = VK_Physical_Device_Properties.limits.maxUniformBufferRange;
			Properties.Limits.maxStorageBufferRange = VK_Physical_Device_Properties.limits.maxStorageBufferRange;
			Properties.Limits.maxPushConstantsSize = VK_Physical_Device_Properties.limits.maxPushConstantsSize;
			Properties.Limits.maxMemoryAllocationCount = VK_Physical_Device_Properties.limits.maxMemoryAllocationCount;
			Properties.Limits.maxSamplerAllocationCount = VK_Physical_Device_Properties.limits.maxSamplerAllocationCount;
			Properties.Limits.bufferImageGranularity = static_cast<VkDeviceSize>(VK_Physical_Device_Properties.limits.bufferImageGranularity);
			Properties.Limits.sparseAddressSpaceSize = static_cast<VkDeviceSize>(VK_Physical_Device_Properties.limits.sparseAddressSpaceSize);
			Properties.Limits.maxBoundDescriptorSets = VK_Physical_Device_Properties.limits.maxBoundDescriptorSets;
			Properties.Limits.maxPerStageDescriptorSamplers = VK_Physical_Device_Properties.limits.maxPerStageDescriptorSamplers;
			Properties.Limits.maxPerStageDescriptorUniformBuffers = VK_Physical_Device_Properties.limits.maxPerStageDescriptorUniformBuffers;
			Properties.Limits.maxPerStageDescriptorStorageBuffers = VK_Physical_Device_Properties.limits.maxPerStageDescriptorStorageBuffers;
			Properties.Limits.maxPerStageDescriptorSampledImages = VK_Physical_Device_Properties.limits.maxPerStageDescriptorSampledImages;
			Properties.Limits.maxPerStageDescriptorStorageImages = VK_Physical_Device_Properties.limits.maxPerStageDescriptorStorageImages;
			Properties.Limits.maxPerStageDescriptorInputAttachments = VK_Physical_Device_Properties.limits.maxPerStageDescriptorInputAttachments;
			Properties.Limits.maxPerStageResources = VK_Physical_Device_Properties.limits.maxPerStageResources;
			Properties.Limits.maxDescriptorSetSamplers = VK_Physical_Device_Properties.limits.maxDescriptorSetSamplers;
			Properties.Limits.maxDescriptorSetUniformBuffers = VK_Physical_Device_Properties.limits.maxDescriptorSetUniformBuffers;
			Properties.Limits.maxDescriptorSetUniformBuffersDynamic = VK_Physical_Device_Properties.limits.maxDescriptorSetUniformBuffersDynamic;
			Properties.Limits.maxDescriptorSetStorageBuffers = VK_Physical_Device_Properties.limits.maxDescriptorSetStorageBuffers;
			Properties.Limits.maxDescriptorSetStorageBuffersDynamic = VK_Physical_Device_Properties.limits.maxDescriptorSetStorageBuffersDynamic;
			Properties.Limits.maxDescriptorSetSampledImages = VK_Physical_Device_Properties.limits.maxDescriptorSetSampledImages;
			Properties.Limits.maxDescriptorSetStorageImages = VK_Physical_Device_Properties.limits.maxDescriptorSetStorageImages;
			Properties.Limits.maxDescriptorSetInputAttachments = VK_Physical_Device_Properties.limits.maxDescriptorSetInputAttachments;
			Properties.Limits.maxVertexInputAttributes = VK_Physical_Device_Properties.limits.maxVertexInputAttributes;
			Properties.Limits.maxVertexInputBindings = VK_Physical_Device_Properties.limits.maxVertexInputBindings;
			Properties.Limits.maxVertexInputAttributeOffset = VK_Physical_Device_Properties.limits.maxVertexInputAttributeOffset;
			Properties.Limits.maxVertexInputBindingStride = VK_Physical_Device_Properties.limits.maxVertexInputBindingStride;
			Properties.Limits.maxVertexOutputComponents = VK_Physical_Device_Properties.limits.maxVertexOutputComponents;
			Properties.Limits.maxTessellationGenerationLevel = VK_Physical_Device_Properties.limits.maxTessellationGenerationLevel;
			Properties.Limits.maxTessellationPatchSize = VK_Physical_Device_Properties.limits.maxTessellationPatchSize;
			Properties.Limits.maxTessellationControlPerVertexInputComponents = VK_Physical_Device_Properties.limits.maxTessellationControlPerVertexInputComponents;
			Properties.Limits.maxTessellationControlPerVertexOutputComponents = VK_Physical_Device_Properties.limits.maxTessellationControlPerVertexOutputComponents;
			Properties.Limits.maxTessellationControlPerPatchOutputComponents = VK_Physical_Device_Properties.limits.maxTessellationControlPerPatchOutputComponents;
			Properties.Limits.maxTessellationControlTotalOutputComponents = VK_Physical_Device_Properties.limits.maxTessellationControlTotalOutputComponents;
			Properties.Limits.maxTessellationEvaluationInputComponents = VK_Physical_Device_Properties.limits.maxTessellationEvaluationInputComponents;
			Properties.Limits.maxTessellationEvaluationOutputComponents = VK_Physical_Device_Properties.limits.maxTessellationEvaluationOutputComponents;
			Properties.Limits.maxGeometryShaderInvocations = VK_Physical_Device_Properties.limits.maxGeometryShaderInvocations;
			Properties.Limits.maxGeometryInputComponents = VK_Physical_Device_Properties.limits.maxGeometryInputComponents;
			Properties.Limits.maxGeometryOutputComponents = VK_Physical_Device_Properties.limits.maxGeometryOutputComponents;
			Properties.Limits.maxGeometryOutputVertices = VK_Physical_Device_Properties.limits.maxGeometryOutputVertices;
			Properties.Limits.maxGeometryTotalOutputComponents = VK_Physical_Device_Properties.limits.maxGeometryTotalOutputComponents;
			Properties.Limits.maxFragmentInputComponents = VK_Physical_Device_Properties.limits.maxFragmentInputComponents;
			Properties.Limits.maxFragmentOutputAttachments = VK_Physical_Device_Properties.limits.maxFragmentOutputAttachments;
			Properties.Limits.maxFragmentDualSrcAttachments = VK_Physical_Device_Properties.limits.maxFragmentDualSrcAttachments;
			Properties.Limits.maxFragmentCombinedOutputResources = VK_Physical_Device_Properties.limits.maxFragmentCombinedOutputResources;
			Properties.Limits.maxComputeSharedMemorySize = VK_Physical_Device_Properties.limits.maxComputeSharedMemorySize;
			for (uint32_t Index = 0; Index < 3; ++Index)
				Properties.Limits.maxComputeWorkGroupCount[Index] = VK_Physical_Device_Properties.limits.maxComputeWorkGroupCount[Index];
			Properties.Limits.maxComputeWorkGroupInvocations = VK_Physical_Device_Properties.limits.maxComputeWorkGroupInvocations;
			for (uint32_t Index = 0; Index < 3; ++Index)
				Properties.Limits.maxComputeWorkGroupSize[Index] = VK_Physical_Device_Properties.limits.maxComputeWorkGroupSize[Index];
			Properties.Limits.subPixelPrecisionBits = VK_Physical_Device_Properties.limits.subPixelPrecisionBits;
			Properties.Limits.subTexelPrecisionBits = VK_Physical_Device_Properties.limits.subTexelPrecisionBits;
			Properties.Limits.mipmapPrecisionBits = VK_Physical_Device_Properties.limits.mipmapPrecisionBits;
			Properties.Limits.maxDrawIndexedIndexValue = VK_Physical_Device_Properties.limits.maxDrawIndexedIndexValue;
			Properties.Limits.maxDrawIndirectCount = VK_Physical_Device_Properties.limits.maxDrawIndirectCount;
			Properties.Limits.maxSamplerLodBias = VK_Physical_Device_Properties.limits.maxSamplerLodBias;
			Properties.Limits.maxSamplerAnisotropy = VK_Physical_Device_Properties.limits.maxSamplerAnisotropy;
			Properties.Limits.maxViewports = VK_Physical_Device_Properties.limits.maxViewports;
			for (uint32_t Index = 0; Index < 2; ++Index)
				Properties.Limits.maxViewportDimensions[Index] = VK_Physical_Device_Properties.limits.maxViewportDimensions[Index];
			for (uint32_t Index = 0; Index < 2; Index++)
				Properties.Limits.viewportBoundsRange[Index] = VK_Physical_Device_Properties.limits.viewportBoundsRange[Index];
			Properties.Limits.viewportSubPixelBits = VK_Physical_Device_Properties.limits.viewportSubPixelBits;
			Properties.Limits.minMemoryMapAlignment = VK_Physical_Device_Properties.limits.minMemoryMapAlignment;
			Properties.Limits.minTexelBufferOffsetAlignment = static_cast<VkDeviceSize>(VK_Physical_Device_Properties.limits.minTexelBufferOffsetAlignment);
			Properties.Limits.minUniformBufferOffsetAlignment = static_cast<VkDeviceSize>(VK_Physical_Device_Properties.limits.minUniformBufferOffsetAlignment);
			Properties.Limits.minStorageBufferOffsetAlignment = static_cast<VkDeviceSize>(VK_Physical_Device_Properties.limits.minStorageBufferOffsetAlignment);
			Properties.Limits.minTexelOffset = VK_Physical_Device_Properties.limits.minTexelOffset;
			Properties.Limits.maxTexelOffset = VK_Physical_Device_Properties.limits.maxTexelOffset;
			Properties.Limits.minTexelGatherOffset = VK_Physical_Device_Properties.limits.minTexelGatherOffset;
			Properties.Limits.maxTexelGatherOffset = VK_Physical_Device_Properties.limits.maxTexelGatherOffset;
			Properties.Limits.minInterpolationOffset = VK_Physical_Device_Properties.limits.minInterpolationOffset;
			Properties.Limits.maxInterpolationOffset = VK_Physical_Device_Properties.limits.maxInterpolationOffset;
			Properties.Limits.subPixelInterpolationOffsetBits = VK_Physical_Device_Properties.limits.subPixelInterpolationOffsetBits;
			Properties.Limits.maxFramebufferWidth = VK_Physical_Device_Properties.limits.maxFramebufferWidth;
			Properties.Limits.maxFramebufferHeight = VK_Physical_Device_Properties.limits.maxFramebufferHeight;
			Properties.Limits.maxFramebufferLayers = VK_Physical_Device_Properties.limits.maxFramebufferLayers;
			Properties.Limits.framebufferColorSampleCounts = static_cast<VkSampleCountFlags>(VK_Physical_Device_Properties.limits.framebufferColorSampleCounts);
			Properties.Limits.framebufferDepthSampleCounts = static_cast<VkSampleCountFlags>(VK_Physical_Device_Properties.limits.framebufferDepthSampleCounts);
			Properties.Limits.framebufferStencilSampleCounts = static_cast<VkSampleCountFlags>(VK_Physical_Device_Properties.limits.framebufferStencilSampleCounts);
			Properties.Limits.framebufferNoAttachmentsSampleCounts = static_cast<VkSampleCountFlags>(VK_Physical_Device_Properties.limits.framebufferNoAttachmentsSampleCounts);
			Properties.Limits.maxColorAttachments = VK_Physical_Device_Properties.limits.maxColorAttachments;
			Properties.Limits.sampledImageColorSampleCounts = static_cast<VkSampleCountFlags>(VK_Physical_Device_Properties.limits.sampledImageColorSampleCounts);
			Properties.Limits.sampledImageIntegerSampleCounts = static_cast<VkSampleCountFlags>(VK_Physical_Device_Properties.limits.sampledImageIntegerSampleCounts);
			Properties.Limits.sampledImageDepthSampleCounts = static_cast<VkSampleCountFlags>(VK_Physical_Device_Properties.limits.sampledImageDepthSampleCounts);
			Properties.Limits.sampledImageStencilSampleCounts = static_cast<VkSampleCountFlags>(VK_Physical_Device_Properties.limits.sampledImageStencilSampleCounts);
			Properties.Limits.storageImageSampleCounts = static_cast<VkSampleCountFlags>(VK_Physical_Device_Properties.limits.storageImageSampleCounts);
			Properties.Limits.maxSampleMaskWords = VK_Physical_Device_Properties.limits.maxSampleMaskWords;
			Properties.Limits.timestampComputeAndGraphics = static_cast<VkBool32>(VK_Physical_Device_Properties.limits.timestampComputeAndGraphics);
			Properties.Limits.timestampPeriod = VK_Physical_Device_Properties.limits.timestampPeriod;
			Properties.Limits.maxClipDistances = VK_Physical_Device_Properties.limits.maxClipDistances;
			Properties.Limits.maxCullDistances = VK_Physical_Device_Properties.limits.maxCullDistances;
			Properties.Limits.maxCombinedClipAndCullDistances = VK_Physical_Device_Properties.limits.maxCombinedClipAndCullDistances;
			Properties.Limits.discreteQueuePriorities = VK_Physical_Device_Properties.limits.discreteQueuePriorities;
			for (uint32_t Index = 0; Index < 2; Index++)
				Properties.Limits.pointSizeRange[Index] = VK_Physical_Device_Properties.limits.pointSizeRange[Index];
			for (uint32_t Index = 0; Index < 2; Index++)
				Properties.Limits.lineWidthRange[Index] = VK_Physical_Device_Properties.limits.lineWidthRange[Index];
			Properties.Limits.pointSizeGranularity = VK_Physical_Device_Properties.limits.pointSizeGranularity;
			Properties.Limits.lineWidthGranularity = VK_Physical_Device_Properties.limits.lineWidthGranularity;
			Properties.Limits.strictLines = static_cast<VkBool32>(VK_Physical_Device_Properties.limits.strictLines);
			Properties.Limits.standardSampleLocations = static_cast<VkBool32>(VK_Physical_Device_Properties.limits.standardSampleLocations);
			Properties.Limits.optimalBufferCopyOffsetAlignment = static_cast<VkDeviceSize>(VK_Physical_Device_Properties.limits.optimalBufferCopyOffsetAlignment);
			Properties.Limits.optimalBufferCopyRowPitchAlignment = static_cast<VkDeviceSize>(VK_Physical_Device_Properties.limits.optimalBufferCopyRowPitchAlignment);
			Properties.Limits.nonCoherentAtomSize = static_cast<VkDeviceSize>(VK_Physical_Device_Properties.limits.nonCoherentAtomSize);
		}

		return Properties;
	}

	RHI_Physical_Device* Vulkan_RHI::Get_Physical_Device(void) {
		return this->m_RHI_Physical_Device.get();
	}

	void Vulkan_RHI::Create_Logical_Device(void) {
		if (nullptr != this->m_Logical_VK_Device)
			throw runtime_error("Vulkan Logical Device Already Created!");

		this->m_Queue_Family_Indices = Vulkan_RHI::S_Get_Queue_Framies(this->m_VK_Physical_Device, this->m_VK_Surface.get());

		//NOTE : Queue Family Should Be Unique,Because It Maybe Same
		std::unordered_set<uint32_t> Unique_Queue_Families{
			this->m_Queue_Family_Indices.Graphics_Family,
			this->m_Queue_Family_Indices.Present_Family,
			this->m_Queue_Family_Indices.Compute_Family
		};

		//NOTE : Refence Continue From Create_Instance
		constexpr float Queue_Priority{ 1.0f };

		vector<VkDeviceQueueCreateInfo> Queue_Create_Infos{};
		Queue_Create_Infos.reserve(Unique_Queue_Families.size());
		{
			for (const auto& Queue_Family : Unique_Queue_Families) {
				VkDeviceQueueCreateInfo Queue_Create_Info{};
				Queue_Create_Info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
				Queue_Create_Info.queueFamilyIndex = Queue_Family;
				Queue_Create_Info.queueCount = 1;
				Queue_Create_Info.pQueuePriorities = &Queue_Priority;
				Queue_Create_Infos.emplace_back(Queue_Create_Info);
			}
		}

		VkPhysicalDeviceFeatures Physical_Device_Features{};
		{
			Physical_Device_Features.samplerAnisotropy = VK_TRUE;
			Physical_Device_Features.fragmentStoresAndAtomics = VK_TRUE;
			Physical_Device_Features.independentBlend = VK_TRUE;
		}

		VkDeviceCreateInfo Device_Create_Info{};
		{
			Device_Create_Info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
			Device_Create_Info.queueCreateInfoCount = static_cast<uint32_t>(Queue_Create_Infos.size());
			Device_Create_Info.pQueueCreateInfos = Queue_Create_Infos.data();
			Device_Create_Info.enabledExtensionCount = static_cast<uint32_t>(this->m_Physical_Device_Extensions.size());
			Device_Create_Info.ppEnabledExtensionNames = this->m_Physical_Device_Extensions.data();
			Device_Create_Info.pEnabledFeatures = &Physical_Device_Features;
		}


		THROW_IF_VK_FAILED(vkCreateDevice(this->m_VK_Physical_Device, &Device_Create_Info, this->m_Allocator.get(), &this->m_Logical_VK_Device));
		static_cast<Vulkan_Logical_Device*>(this->m_RHI_Logical_Device.get())->Reset(this->m_Logical_VK_Device);

		{
			vkGetDeviceQueue(this->m_Logical_VK_Device, this->m_Queue_Family_Indices.Graphics_Family, 0, &this->m_Queues.Graphic_Queue);
			vkGetDeviceQueue(this->m_Logical_VK_Device, this->m_Queue_Family_Indices.Present_Family, 0, &this->m_Queues.Present_Queue);
			vkGetDeviceQueue(this->m_Logical_VK_Device, this->m_Queue_Family_Indices.Compute_Family, 0, &this->m_Queues.Compute_Queue);

			static_cast<Vulkan_Queue*>(this->m_Queues.Graphic_RHI_Queue.get())->Reset(this->m_Queues.Graphic_Queue);
			static_cast<Vulkan_Queue*>(this->m_Queues.Present_RHI_Queue.get())->Reset(this->m_Queues.Present_Queue);
			static_cast<Vulkan_Queue*>(this->m_Queues.Compute_RHI_Queue.get())->Reset(this->m_Queues.Compute_Queue);
		}

		this->Get_Device_ProcAddrs();

		this->Reset_Device_Deleters(this->m_Logical_VK_Device, this->m_Allocator.get());
	}

	RHI_Logical_Device* Vulkan_RHI::Get_Logical_Device(void) {
		return this->m_RHI_Logical_Device.get();
	}

	RHI_Queue* Vulkan_RHI::Get_Graphics_Queue(void) {
		return this->m_Queues.Graphic_RHI_Queue.get();
	}

	unique_ptr<RHI_Command_Pool> Vulkan_RHI::Create_Command_Pool(const RHI_Command_Pool_Create_Info* Create_Info) {

		VkCommandPoolCreateInfo Command_Pool_Create_Info{};
		{
			Command_Pool_Create_Info.sType = static_cast<VkStructureType>(Create_Info->sType);
			Command_Pool_Create_Info.pNext = Create_Info->pNext;
			Command_Pool_Create_Info.flags = static_cast<VkCommandPoolCreateFlags>(Create_Info->Flags);
			Command_Pool_Create_Info.queueFamilyIndex = Create_Info->Queue_Family_Index;
		}

		VkCommandPool VK_Command_Pool{ nullptr };
		THROW_IF_VK_FAILED(vkCreateCommandPool(this->m_Logical_VK_Device, &Command_Pool_Create_Info, this->m_Allocator.get(), &VK_Command_Pool));
		auto Command_Pool{ std::make_unique<Vulkan_Command_Pool>() };
		static_cast<Vulkan_Command_Pool*>(Command_Pool.get())->Set_Deleter(this->m_VK_Command_Pool_Deleter);
		static_cast<Vulkan_Command_Pool*>(Command_Pool.get())->Reset(VK_Command_Pool);

		return Command_Pool;
	}

	const vector<unique_ptr<RHI_Command_Buffer>> Vulkan_RHI::Allocate_Command_Buffers(const RHI_Command_Buffer_Allocate_Info* Allocate_Info) {
		VkCommandBufferAllocateInfo Command_Buffer_Allocate_Info{};
		{
			Command_Buffer_Allocate_Info.sType = static_cast<VkStructureType>(Allocate_Info->sType);
			Command_Buffer_Allocate_Info.pNext = Allocate_Info->pNext;
			Command_Buffer_Allocate_Info.commandPool = static_cast<Vulkan_Command_Pool*>(Allocate_Info->Command_Pool)->Get();
			Command_Buffer_Allocate_Info.level = static_cast<VkCommandBufferLevel>(Allocate_Info->Level);
			Command_Buffer_Allocate_Info.commandBufferCount = Allocate_Info->Command_Buffer_Count;
		}

		vector<VkCommandBuffer> Command_Buffers{};
		Command_Buffers.resize(Allocate_Info->Command_Buffer_Count, nullptr);
		THROW_IF_VK_FAILED(vkAllocateCommandBuffers(this->m_Logical_VK_Device, &Command_Buffer_Allocate_Info, Command_Buffers.data()));

		vector<unique_ptr<RHI_Command_Buffer>> RHI_Command_Buffers{};
		RHI_Command_Buffers.reserve(Allocate_Info->Command_Buffer_Count);
		for (size_t Index = 0; Index < Allocate_Info->Command_Buffer_Count; ++Index) {
			RHI_Command_Buffers.emplace_back(std::make_unique<Vulkan_Command_Buffer>());
			static_cast<Vulkan_Command_Buffer*>(RHI_Command_Buffers[Index].get())->Reset(Command_Buffers[Index]);
		}

		return RHI_Command_Buffers;
	}

	tuple<unique_ptr<RHI_Buffer>, unique_ptr<RHI_Device_Memory>> Vulkan_RHI::Create_Buffer(RHI_Device_Size Size, RHI_Buffer_Usage_Flags Usage, RHI_Memory_Property_Flags Properties) {
		VkBuffer  Temp_Buffer{ nullptr };
		VkDeviceMemory Temp_Device_Memory{ nullptr };

		NameSpace_Utilities::Create_Buffer(
			this->m_VK_Physical_Device,
			this->m_Logical_VK_Device,
			Size,
			static_cast<VkBufferUsageFlags>(Usage),
			static_cast<VkMemoryPropertyFlags>(Properties),
			this->m_Allocator.get(),
			Temp_Buffer,
			Temp_Device_Memory
		);

		unique_ptr<RHI_Buffer> Buffer{ std::make_unique<Vulkan_Buffer>() };
		static_cast<Vulkan_Buffer*>(Buffer.get())->Set_Deleter(this->m_VK_Buffer_Deleter);
		static_cast<Vulkan_Buffer*>(Buffer.get())->Reset(Temp_Buffer);

		unique_ptr<RHI_Device_Memory> Device_Memory{ std::make_unique<Vulkan_Device_Memory>() };
		static_cast<Vulkan_Device_Memory*>(Device_Memory.get())->Set_Deleter(this->m_VK_Device_Memory_Deleter);
		static_cast<Vulkan_Device_Memory*>(Device_Memory.get())->Reset(Temp_Device_Memory);

		return std::make_tuple(std::move(Buffer), std::move(Device_Memory));
	}

	tuple<unique_ptr<RHI_Buffer>, VmaAllocation> Vulkan_RHI::Create_Buffer_VMA(VmaAllocator Vma_Allocator, const RHI_Buffer_Create_Info* Buffer_Create_Info, const VmaAllocationCreateInfo* Allocation_Create_Info, VmaAllocationInfo* AllocationInfo) {
		VkBufferCreateInfo vk_Buffer_Create_Info{};
		{
			vk_Buffer_Create_Info.sType = static_cast<VkStructureType>(Buffer_Create_Info->sType);
			vk_Buffer_Create_Info.pNext = Buffer_Create_Info->pNext;
			vk_Buffer_Create_Info.flags = static_cast<VkBufferCreateFlags>(Buffer_Create_Info->Flags);
			vk_Buffer_Create_Info.size = static_cast<VkDeviceSize>(Buffer_Create_Info->Size);
			vk_Buffer_Create_Info.usage = static_cast<VkBufferUsageFlags>(Buffer_Create_Info->Usage);
			vk_Buffer_Create_Info.sharingMode = static_cast<VkSharingMode>(Buffer_Create_Info->Sharing_Mode);
			vk_Buffer_Create_Info.queueFamilyIndexCount = Buffer_Create_Info->Queue_Family_Index_Count;
			vk_Buffer_Create_Info.pQueueFamilyIndices = Buffer_Create_Info->pQueue_Family_Indices;
		}

		VkBuffer VK_Buffer{ nullptr };
		VmaAllocation Allocation{ nullptr };
		THROW_IF_VK_FAILED(vmaCreateBuffer(Vma_Allocator, &vk_Buffer_Create_Info, Allocation_Create_Info, &VK_Buffer, &Allocation, AllocationInfo));
		unique_ptr<RHI_Buffer> Buffer{ std::make_unique<Vulkan_Buffer>() };
		static_cast<Vulkan_Buffer*>(Buffer.get())->Set_Deleter(this->m_VK_Buffer_Deleter);
		static_cast<Vulkan_Buffer*>(Buffer.get())->Reset(VK_Buffer);

		return std::make_tuple(std::move(Buffer), Allocation);
	}

	void Vulkan_RHI::Copy_Buffer(RHI_Buffer* Src_Buffer, RHI_Buffer* Dst_Buffer, RHI_Device_Size Src_Offset, RHI_Device_Size Dst_Offset, RHI_Device_Size Size) {
		unique_ptr<RHI_Command_Buffer> Command_Buffer{ this->Begin_SingleTime_Commands() };

		VkBufferCopy Copy_Region{};
		{
			Copy_Region.srcOffset = static_cast<VkDeviceSize>(Src_Offset);
			Copy_Region.dstOffset = static_cast<VkDeviceSize>(Dst_Offset);
			Copy_Region.size = static_cast<VkDeviceSize>(Size);
		}

		vkCmdCopyBuffer(static_cast<Vulkan_Command_Buffer*>(Command_Buffer.get())->Get(), static_cast<Vulkan_Buffer*>(Src_Buffer)->Get(), static_cast<Vulkan_Buffer*>(Dst_Buffer)->Get(), 1, &Copy_Region);
		this->End_SingleTime_Commands(std::move(Command_Buffer));
	}

	tuple<unique_ptr<RHI_Image>, unique_ptr<RHI_Image_View>, VmaAllocation> Vulkan_RHI::Create_Cube_Map(RHI_Extent_2D Image_Extent, RHI_FORMAT Image_Format, uint32_t Mip_levels, array<void*, 6> Image_Pixels) {
		VkImage VK_Image{ nullptr };
		VkImageView VK_Image_View{ nullptr };
		VmaAllocation VMA_Allocation{ nullptr };
		NameSpace_Utilities::Create_Cube_Map(
			this->m_VK_Physical_Device,
			this->m_Logical_VK_Device,
			this->m_Allocator.get(),
			this->m_Default_VK_Command_Pool,
			this->m_Queues.Graphic_Queue,
			this->m_VMA_Allocator,
			{ Image_Extent.Width, Image_Extent.Height },
			static_cast<VkFormat>(Image_Format),
			Mip_levels,
			Image_Pixels,
			VK_Image,
			VK_Image_View,
			VMA_Allocation
		);

		unique_ptr<RHI_Image> Image{ std::make_unique<Vulkan_Image>() };
		static_cast<Vulkan_Image*>(Image.get())->Set_Deleter(this->m_VK_Image_Deleter);
		static_cast<Vulkan_Image*>(Image.get())->Reset(VK_Image);

		unique_ptr<RHI_Image_View> Image_View{ std::make_unique<Vulkan_Image_View>() };
		static_cast<Vulkan_Image_View*>(Image_View.get())->Set_Deleter(this->m_VK_Image_View_Deleter);
		static_cast<Vulkan_Image_View*>(Image_View.get())->Reset(VK_Image_View);

		return std::make_tuple(std::move(Image), std::move(Image_View), VMA_Allocation);
	}

	void Vulkan_RHI::Map_Memory(RHI_Device_Memory* Memory, RHI_Device_Size Offset, RHI_Device_Size Size, RHI_Memopy_Map_Flags Flags, void** Data) {
		THROW_IF_VK_FAILED(vkMapMemory(this->m_Logical_VK_Device, static_cast<Vulkan_Device_Memory*>(Memory)->Get(), Offset, Size, static_cast<VkMemoryMapFlags>(Flags), Data));
	}

	void Vulkan_RHI::UnMap_Memory(RHI_Device_Memory* Memory) {
		vkUnmapMemory(this->m_Logical_VK_Device, static_cast<Vulkan_Device_Memory*>(Memory)->Get());
	}

	unique_ptr<RHI_Sampler> Vulkan_RHI::Create_Sampler(const RHI_Sampler_Create_Info* Create_Info) {
		VkSamplerCreateInfo vk_Sampler_Create_Info{};
		{
			vk_Sampler_Create_Info.sType = static_cast<VkStructureType>(Create_Info->sType);
			vk_Sampler_Create_Info.pNext = Create_Info->pNext;
			vk_Sampler_Create_Info.flags = static_cast<VkSamplerCreateFlags>(Create_Info->Flags);
			vk_Sampler_Create_Info.magFilter = static_cast<VkFilter>(Create_Info->Mag_Filter);
			vk_Sampler_Create_Info.minFilter = static_cast<VkFilter>(Create_Info->Min_Filter);
			vk_Sampler_Create_Info.mipmapMode = static_cast<VkSamplerMipmapMode>(Create_Info->Mipmap_Mode);
			vk_Sampler_Create_Info.addressModeU = static_cast<VkSamplerAddressMode>(Create_Info->Address_Mode_U);
			vk_Sampler_Create_Info.addressModeV = static_cast<VkSamplerAddressMode>(Create_Info->Address_Mode_V);
			vk_Sampler_Create_Info.addressModeW = static_cast<VkSamplerAddressMode>(Create_Info->Address_Mode_W);
			vk_Sampler_Create_Info.mipLodBias = Create_Info->Mip_Lod_Bias;
			vk_Sampler_Create_Info.anisotropyEnable = static_cast<VkBool32>(Create_Info->Anisotropy_Enable);
			vk_Sampler_Create_Info.maxAnisotropy = Create_Info->Max_Anisotropy;
			vk_Sampler_Create_Info.compareEnable = static_cast<VkBool32>(Create_Info->Compare_Enable);
			vk_Sampler_Create_Info.compareOp = static_cast<VkCompareOp>(Create_Info->Compare_Op);
			vk_Sampler_Create_Info.minLod = Create_Info->Min_Lod;
			vk_Sampler_Create_Info.maxLod = Create_Info->Max_Lod;
			vk_Sampler_Create_Info.borderColor = static_cast<VkBorderColor>(Create_Info->Border_Color);
			vk_Sampler_Create_Info.unnormalizedCoordinates = static_cast<VkBool32>(Create_Info->Unnormalized_Coordinates);
		}

		VkSampler vk_Sampler{};
		THROW_IF_VK_FAILED(vkCreateSampler(this->m_Logical_VK_Device, &vk_Sampler_Create_Info, this->m_Allocator.get(), &vk_Sampler));
		unique_ptr<RHI_Sampler> Sampler{ std::make_unique<Vulkan_Sampler>() };
		static_cast<Vulkan_Sampler*>(Sampler.get())->Set_Deleter(this->m_VK_Sampler_Deleter);
		static_cast<Vulkan_Sampler*>(Sampler.get())->Reset(vk_Sampler);

		return Sampler;
	}

	 vector<unique_ptr<RHI_Descriptor_Set>> Vulkan_RHI::Allocate_Descriptor_Sets(const RHI_Descriptor_Set_Allocate_Info* Allocate_Info) {
		vector<VkDescriptorSetLayout> Descriptor_Set_Layouts{};
		Descriptor_Set_Layouts.reserve(Allocate_Info->Descriptor_Set_Count);
		for (size_t Index = 0; Index < Allocate_Info->Descriptor_Set_Count; ++Index)
			Descriptor_Set_Layouts.emplace_back(static_cast<Vulkan_Descriptor_Set_Layout*>(Allocate_Info->Set_Layouts->at(Index))->Get());

		VkDescriptorSetAllocateInfo Descriptor_Set_Allocate_Info{};
		{
			Descriptor_Set_Allocate_Info.sType = static_cast<VkStructureType>(Allocate_Info->sType);
			Descriptor_Set_Allocate_Info.pNext = Allocate_Info->pNext;
			Descriptor_Set_Allocate_Info.descriptorPool = static_cast<Vulkan_Descriptor_Pool*>(Allocate_Info->Descriptor_Pool)->Get();
			Descriptor_Set_Allocate_Info.descriptorSetCount = Allocate_Info->Descriptor_Set_Count;
			Descriptor_Set_Allocate_Info.pSetLayouts = Descriptor_Set_Layouts.data();
		}

		vector<VkDescriptorSet> Descriptor_Sets{};
		Descriptor_Sets.resize(Allocate_Info->Descriptor_Set_Count, nullptr);
		THROW_IF_VK_FAILED(vkAllocateDescriptorSets(this->m_Logical_VK_Device, &Descriptor_Set_Allocate_Info, Descriptor_Sets.data()));

		vector<unique_ptr<RHI_Descriptor_Set>> RHI_Descriptor_Sets{};
		RHI_Descriptor_Sets.reserve(Allocate_Info->Descriptor_Set_Count);
		for (size_t Index = 0; Index < Allocate_Info->Descriptor_Set_Count; ++Index) {
			RHI_Descriptor_Sets.emplace_back(std::make_unique<Vulkan_Descriptor_Set>());
			static_cast<Vulkan_Descriptor_Set*>(RHI_Descriptor_Sets[Index].get())->Reset(Descriptor_Sets[Index]);
		}

		return RHI_Descriptor_Sets;
	}

	void Vulkan_RHI::Update_Descriptor_Sets(const vector<const RHI_Write_Descriptor_Set*>* Descriptor_Writes, const vector<const RHI_Copy_Descriptor_Set*>* Descriptor_Copies) {
		vector<VkWriteDescriptorSet> vk_Write_Descriptor_Sets{};
		if (nullptr != Descriptor_Writes && (!Descriptor_Writes->empty())) {
			vector<optional<vector<VkDescriptorImageInfo>>> Image_Infos{};
			vector<optional<vector<VkDescriptorBufferInfo>>> Buffer_Infos{};
			vector<optional<vector<VkBufferView>>> vk_Buffer_Views;

			vk_Write_Descriptor_Sets.reserve(Descriptor_Writes->size());
			Image_Infos.reserve(Descriptor_Writes->size());
			Buffer_Infos.reserve(Descriptor_Writes->size());
			vk_Buffer_Views.reserve(Descriptor_Writes->size());

			for (const auto& Descriptor_Write : *Descriptor_Writes) {
				if (nullptr == Descriptor_Write)
					throw runtime_error("Descriptor Write is nullptr!");

				optional<vector<VkDescriptorImageInfo>> vk_Image_Info{};
				optional<vector<VkDescriptorBufferInfo>> vk_Buffer_Info{};
				optional<vector<VkBufferView>> vk_Buffer_View{};
				const auto vk_Write_Descriptor_Set{ Vulkan_RHI::Parser_RHI_Write_Descriptor_Set(Descriptor_Write, vk_Image_Info, vk_Buffer_Info, vk_Buffer_View) };

				Image_Infos.emplace_back(vk_Image_Info);
				Buffer_Infos.emplace_back(vk_Buffer_Info);
				vk_Buffer_Views.emplace_back(vk_Buffer_View);

				vk_Write_Descriptor_Sets.emplace_back(vk_Write_Descriptor_Set.value());

			}

			vector<VkCopyDescriptorSet> vk_Copy_Descriptor_Sets{};
			if (nullptr != Descriptor_Copies && !Descriptor_Copies->empty()) {
				vk_Copy_Descriptor_Sets.reserve(Descriptor_Copies->size());
				for (const auto& Descriptor_Copy : *Descriptor_Copies) {
					if (nullptr == Descriptor_Copy)
						throw runtime_error("Descriptor Copy is nullptr!");

					VkCopyDescriptorSet vk_Copy_Descriptor_Set{};
					{
						vk_Copy_Descriptor_Set.sType = static_cast<VkStructureType>(Descriptor_Copy->sType);
						vk_Copy_Descriptor_Set.pNext = Descriptor_Copy->pNext;
						vk_Copy_Descriptor_Set.srcSet = static_cast<Vulkan_Descriptor_Set*>(Descriptor_Copy->Src_Set)->Get();
						vk_Copy_Descriptor_Set.srcBinding = Descriptor_Copy->Src_Binding;
						vk_Copy_Descriptor_Set.srcArrayElement = Descriptor_Copy->Src_Array_Element;
						vk_Copy_Descriptor_Set.dstSet = static_cast<Vulkan_Descriptor_Set*>(Descriptor_Copy->Dst_Set)->Get();
						vk_Copy_Descriptor_Set.dstBinding = Descriptor_Copy->Dst_Binding;
						vk_Copy_Descriptor_Set.dstArrayElement = Descriptor_Copy->Dst_Array_Element;
						vk_Copy_Descriptor_Set.descriptorCount = Descriptor_Copy->Descriptor_Count;
					}

					vk_Copy_Descriptor_Sets.emplace_back(vk_Copy_Descriptor_Set);
				}
			}

			vkUpdateDescriptorSets(
				this->m_Logical_VK_Device,
				vk_Write_Descriptor_Sets.size(),
				vk_Write_Descriptor_Sets.data(),
				vk_Copy_Descriptor_Sets.size(),
				vk_Copy_Descriptor_Sets.data()
			);
		}
		else
			System_Logger::Get_Instance().Log(System_Logger::Level::err, "Empty Input");
	}


	void Vulkan_RHI::Run(void) {
		this->Create_Allocator();
		this->Create_Instance();
		this->Create_Surface();
		this->Create_Physical_Device();
		this->Create_Logical_Device();
		this->Create_Default_Command_Pool();
		this->Allocate_Default_Command_Buffers();
		//this->Create_Descriptor_Pool();
		//this->Create_Sync_Primitices();
		//this->Create_SwapChain();
		//this->Create_SwapChhain_Image_Views();
		//TODO : Add SwapChain Image Depth Image View
	}

	void Vulkan_RHI::CleanUp_SwapChain(void)
	{
	}

	void Vulkan_RHI::Re_Create_SwapChain(void)
	{
	}






	void Vulkan_RHI::Create_Descriptor_Pool(void) {
		array<VkDescriptorPoolSize, 7> Pool_Sizes{};
		{
			//TODO Erase Magic Number
			{
				Pool_Sizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
				Pool_Sizes[0].descriptorCount = 3 + 2 + 2 + 2 + 1 + 1 + 3 + 3;
			}

			{
				Pool_Sizes[1].type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
				Pool_Sizes[1].descriptorCount = 1 + 1 + 1 * NameSpace_Config::Max_Vertex_Blending_Mesh_Count;
			}

			{
				Pool_Sizes[2].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
				Pool_Sizes[2].descriptorCount = 1 * NameSpace_Config::Max_Material_Count;
			}

			{
				Pool_Sizes[3].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
				Pool_Sizes[3].descriptorCount = 3 + 5 * NameSpace_Config::Max_Material_Count + 1 + 1;
			}

			{
				Pool_Sizes[4].type = VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT;
				Pool_Sizes[4].descriptorCount = 4 + 1 + 1 + 2;
			}

			{
				Pool_Sizes[5].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
				Pool_Sizes[5].descriptorCount = 3;
			}

			{
				Pool_Sizes[6].type = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
				Pool_Sizes[6].descriptorCount = 1;
			}
		}

		//NOTE :  // +SkyBox + Axis Descriptor Set
		VkDescriptorPoolCreateInfo Pool_Info{};
		{
			Pool_Info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
			Pool_Info.poolSizeCount = static_cast<uint32_t>(Pool_Sizes.size());
			Pool_Info.pPoolSizes = Pool_Sizes.data();
			Pool_Info.maxSets = 1 + 1 + 1 + NameSpace_Config::Max_Vertex_Blending_Mesh_Count + NameSpace_Config::Max_Material_Count + 1 + 1;
		}

		VkDescriptorPool Descriptor_Pool{ nullptr };
		THROW_IF_VK_FAILED(vkCreateDescriptorPool(this->m_Logical_VK_Device, &Pool_Info, this->m_Allocator.get(), &Descriptor_Pool));
		if (nullptr == this->m_RHI_Descriptor_Pool)
			this->m_RHI_Descriptor_Pool = std::make_unique<Vulkan_Descriptor_Pool>();
		static_cast<Vulkan_Descriptor_Pool*>(this->m_RHI_Descriptor_Pool.get())->Reset(Descriptor_Pool);
	}

	void Vulkan_RHI::Create_Sync_Primitices(void) {
		VkSemaphoreCreateInfo Semaphore_Info{};
		{
			Semaphore_Info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
		}

		VkFenceCreateInfo Fence_Info{};
		{
			Fence_Info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
			Fence_Info.flags = VK_FENCE_CREATE_SIGNALED_BIT;
		}

		VkSemaphore Semaphore{ nullptr };
		VkFence InFlight_Fence{ nullptr };
		for (uint32_t Index = 0; Index < Vulkan_RHI::s_Frames_In_Flight; ++Index) {
			{
				THROW_IF_VK_FAILED(vkCreateSemaphore(this->m_Logical_VK_Device, &Semaphore_Info, this->m_Allocator.get(), &Semaphore));
				if (nullptr == this->m_Image_available_For_Render_RHI_Semaphores[Index])
					this->m_Image_available_For_Render_RHI_Semaphores[Index] = std::make_unique<Vulkan_Semaphore>();
				static_cast<Vulkan_Semaphore*>(this->m_Image_available_For_Render_RHI_Semaphores[Index].get())->Reset(Semaphore);
			}

			{
				THROW_IF_VK_FAILED(vkCreateSemaphore(this->m_Logical_VK_Device, &Semaphore_Info, this->m_Allocator.get(), &Semaphore));
				if (nullptr == this->m_Image_Finished_For_Present_RHI_Semaphores[Index])
					this->m_Image_Finished_For_Present_RHI_Semaphores[Index] = std::make_unique<Vulkan_Semaphore>();
				static_cast<Vulkan_Semaphore*>(this->m_Image_Finished_For_Present_RHI_Semaphores[Index].get())->Reset(Semaphore);
			}

			{
				THROW_IF_VK_FAILED(vkCreateSemaphore(this->m_Logical_VK_Device, &Semaphore_Info, this->m_Allocator.get(), &Semaphore));
				if (nullptr == this->m_Image_Available_For_TeCopy_RHI_Semaphores[Index])
					this->m_Image_Available_For_TeCopy_RHI_Semaphores[Index] = std::make_unique<Vulkan_Semaphore>();
				static_cast<Vulkan_Semaphore*>(this->m_Image_Available_For_TeCopy_RHI_Semaphores[Index].get())->Reset(Semaphore);
			}

			{
				THROW_IF_VK_FAILED(vkCreateFence(this->m_Logical_VK_Device, &Fence_Info, this->m_Allocator.get(), &InFlight_Fence));
				if (nullptr == this->m_InFlight_RHI_Fences[Index])
					this->m_InFlight_RHI_Fences[Index] = std::make_unique<Vulkan_Fence>();
				static_cast<Vulkan_Fence*>(this->m_InFlight_RHI_Fences[Index].get())->Reset(InFlight_Fence);
			}
		}
	}

	void Vulkan_RHI::Create_SwapChain(void) {
		this->m_Swap_Chain_Support_Details = Vulkan_RHI::Query_Swap_Chain_Support_Details(this->m_VK_Physical_Device, this->m_VK_Surface.get());

		const VkSurfaceFormatKHR Surface_Format{ Vulkan_RHI::Choose_SwapChain_Surface_Format(this->m_Swap_Chain_Support_Details.Formats) };
		const VkPresentModeKHR Present_Mode{ Vulkan_RHI::Choose_SwapChain_Present_Mode(this->m_Swap_Chain_Support_Details.Present_Modes) };
		const VkExtent2D Swap_Chain_Extent{ Vulkan_RHI::Choose_SwapChain_Extent(this->m_Window,this->m_Swap_Chain_Support_Details.Capabilities) };

		//NOTE : Choose Image Count ,We Want One More Image Than Min Image Count
		uint32_t Image_Count{ this->m_Swap_Chain_Support_Details.Capabilities.minImageCount + 1 };
		Image_Count = std::clamp(Image_Count, this->m_Swap_Chain_Support_Details.Capabilities.minImageCount, this->m_Swap_Chain_Support_Details.Capabilities.maxImageCount);

		//TODO : Why We Need Graphics And Present Family
		vector<uint32_t> Queue_Family_Indices{ this->m_Queue_Family_Indices.Graphics_Family,this->m_Queue_Family_Indices.Present_Family };
		VkSharingMode Sharing_Mode{ VK_SHARING_MODE_EXCLUSIVE };

		if (this->m_Queue_Family_Indices.Graphics_Family != this->m_Queue_Family_Indices.Present_Family)
			Sharing_Mode = VK_SHARING_MODE_CONCURRENT;

		VkSwapchainCreateInfoKHR Swap_Chain_Create_Info{};
		{
			Swap_Chain_Create_Info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
			Swap_Chain_Create_Info.surface = this->m_VK_Surface.get();
			Swap_Chain_Create_Info.minImageCount = Image_Count;
			Swap_Chain_Create_Info.imageFormat = Surface_Format.format;
			Swap_Chain_Create_Info.imageColorSpace = Surface_Format.colorSpace;
			Swap_Chain_Create_Info.imageExtent = Swap_Chain_Extent;
			Swap_Chain_Create_Info.imageArrayLayers = 1;
			Swap_Chain_Create_Info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
			Swap_Chain_Create_Info.imageSharingMode = Sharing_Mode;
			Swap_Chain_Create_Info.queueFamilyIndexCount = static_cast<uint32_t>(Queue_Family_Indices.size());
			Swap_Chain_Create_Info.pQueueFamilyIndices = Queue_Family_Indices.data();
			Swap_Chain_Create_Info.preTransform = this->m_Swap_Chain_Support_Details.Capabilities.currentTransform;
			Swap_Chain_Create_Info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
			Swap_Chain_Create_Info.presentMode = Present_Mode;
			//NOTE : Should Not Read Back Buffer
			Swap_Chain_Create_Info.clipped = VK_TRUE;
			Swap_Chain_Create_Info.oldSwapchain = VK_NULL_HANDLE;
		}

		VkSwapchainKHR SwapChain{ nullptr };
		THROW_IF_VK_FAILED(vkCreateSwapchainKHR(this->m_Logical_VK_Device, &Swap_Chain_Create_Info, nullptr, &SwapChain));
		this->m_Vk_SwapChain.reset(SwapChain);

		THROW_IF_VK_FAILED(vkGetSwapchainImagesKHR(this->m_Logical_VK_Device, this->m_Vk_SwapChain.get(), &Image_Count, nullptr));
		this->m_SwapChain_VK_Images.resize(Image_Count);
		THROW_IF_VK_FAILED(vkGetSwapchainImagesKHR(this->m_Logical_VK_Device, this->m_Vk_SwapChain.get(), &Image_Count, this->m_SwapChain_VK_Images.data()));

		//NOTE : Refence SwapChain Info
		{
			this->m_SwapChain_Image_Format = Surface_Format.format;
			this->m_SwapChain_Extent = Swap_Chain_Extent;
			this->m_Scissor = { {0,0},{Swap_Chain_Extent.width,Swap_Chain_Extent.height} };
		}
	}

	void Vulkan_RHI::Create_SwapChhain_Image_Views(void) {
		this->m_SwapChain_Image_Views.resize(this->m_SwapChain_VK_Images.size());
		for (size_t Index = 0; Index < this->m_SwapChain_VK_Images.size(); ++Index) {

			VkImageView Image_View{ NameSpace_Utilities::Create_Image_View(
				this->m_Logical_VK_Device,
				this->m_Allocator.get(),
				this->m_SwapChain_VK_Images[Index],
				this->m_SwapChain_Image_Format,
				1,
					VK_IMAGE_ASPECT_COLOR_BIT,
				VK_IMAGE_VIEW_TYPE_2D,
				1)
			};

			this->m_SwapChain_Image_Views[Index].reset(Image_View);
		}
	}

	void Vulkan_RHI::Create_Resource_Allocator(void) {
		//VmaVulkanFunctions Vulkan_Functions{};
		//{
		//	Vulkan_Functions.vkGetInstanceProcAddr = vkGetInstanceProcAddr;
		//	Vulkan_Functions.vkGetDeviceProcAddr = vkGetDeviceProcAddr;
		//}

		//VmaAllocatorCreateInfo Allocator_Create_Info{};
		//{
		//	Allocator_Create_Info.vulkanApiVersion = NameSpace_Config::API_Verssion;
		//	Allocator_Create_Info.instance = this->m_VK_Instance.get();
		//	Allocator_Create_Info.physicalDevice = this->m_VK_Physical_Device;
		//	Allocator_Create_Info.device = this->m_Logical_VK_Device.get();

		//	//NOTE : Default 256MiB
		//	Allocator_Create_Info.preferredLargeHeapBlockSize = 0;
		//	Allocator_Create_Info.pVulkanFunctions = &Vulkan_Functions;
		//}

		//THROW_IF_VK_FAILED(vmaCreateAllocator(&Allocator_Create_Info, &this->m_Vma_Allocator));
	}


	void Vulkan_RHI::Create_Nearest_Sampler(void) {
		VkPhysicalDeviceProperties Properties{};
		vkGetPhysicalDeviceProperties(this->m_VK_Physical_Device, &Properties);

		VkSamplerCreateInfo Sampler_Create_Info{};
		{
			Sampler_Create_Info.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
			Sampler_Create_Info.magFilter = VK_FILTER_NEAREST;
			Sampler_Create_Info.minFilter = VK_FILTER_NEAREST;
			Sampler_Create_Info.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
			Sampler_Create_Info.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
			Sampler_Create_Info.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
			Sampler_Create_Info.anisotropyEnable = VK_FALSE;
			Sampler_Create_Info.maxAnisotropy = Properties.limits.maxSamplerAnisotropy;
			Sampler_Create_Info.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
			Sampler_Create_Info.unnormalizedCoordinates = VK_FALSE;
			Sampler_Create_Info.compareEnable = VK_FALSE;
			Sampler_Create_Info.compareOp = VK_COMPARE_OP_ALWAYS;
			Sampler_Create_Info.mipmapMode = VK_SAMPLER_MIPMAP_MODE_NEAREST;
			Sampler_Create_Info.mipLodBias = 0.0f;
			Sampler_Create_Info.minLod = 0.0f;
			Sampler_Create_Info.maxLod = VK_LOD_CLAMP_NONE;
		}

		VkSampler Sampler{ nullptr };
		THROW_IF_VK_FAILED(vkCreateSampler(this->m_Logical_VK_Device, &Sampler_Create_Info, this->m_Allocator.get(), &Sampler));

		static_cast<Vulkan_Sampler*>(this->m_Linear_RHI_Sampler.get())->Reset(Sampler);
	}


	void Vulkan_RHI::Create_Linear_Sampler(void) {
		VkPhysicalDeviceProperties Properties{};
		vkGetPhysicalDeviceProperties(this->m_VK_Physical_Device, &Properties);

		VkSamplerCreateInfo Sampler_Create_Info{};
		{
			Sampler_Create_Info.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
			Sampler_Create_Info.magFilter = VK_FILTER_LINEAR;
			Sampler_Create_Info.minFilter = VK_FILTER_LINEAR;
			Sampler_Create_Info.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
			Sampler_Create_Info.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
			Sampler_Create_Info.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
			Sampler_Create_Info.anisotropyEnable = VK_FALSE;
			Sampler_Create_Info.maxAnisotropy = Properties.limits.maxSamplerAnisotropy;
			Sampler_Create_Info.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
			Sampler_Create_Info.unnormalizedCoordinates = VK_FALSE;
			Sampler_Create_Info.compareEnable = VK_FALSE;
			Sampler_Create_Info.compareOp = VK_COMPARE_OP_ALWAYS;
			Sampler_Create_Info.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
			Sampler_Create_Info.mipLodBias = 0.0f;
			Sampler_Create_Info.minLod = 0.0f;
			Sampler_Create_Info.maxLod = VK_LOD_CLAMP_NONE;
		}

		VkSampler Sampler{ nullptr };
		THROW_IF_VK_FAILED(vkCreateSampler(this->m_Logical_VK_Device, &Sampler_Create_Info, this->m_Allocator.get(), &Sampler));

		static_cast<Vulkan_Sampler*>(this->m_Nearest_RHI_Sampler.get())->Reset(Sampler);
	}



	VkFormat Vulkan_RHI::Find_Supported_Format(const VkPhysicalDevice& Physical_Device, const vector<VkFormat>& Candidates, VkImageTiling Tiling, VkFormatFeatureFlags Features) {
		for (const auto& Candidate : Candidates) {
			VkFormatProperties Properties{};
			vkGetPhysicalDeviceFormatProperties(Physical_Device, Candidate, &Properties);

			if (VK_IMAGE_TILING_LINEAR == Tiling && (Properties.linearTilingFeatures & Features) == Features)
				return Candidate;
			else if (VK_IMAGE_TILING_OPTIMAL == Tiling && (Properties.optimalTilingFeatures & Features) == Features)
				return Candidate;
		}
		throw runtime_error("Failed to find supported format!");

		return VK_FORMAT_UNDEFINED;
	}

	VkFormat Vulkan_RHI::Find_Depth_Format(const VkPhysicalDevice& Physical_Device) {
		return Vulkan_RHI::Find_Supported_Format(
			Physical_Device,
			{ VK_FORMAT_D32_SFLOAT,VK_FORMAT_D32_SFLOAT_S8_UINT,VK_FORMAT_D24_UNORM_S8_UINT },
			VK_IMAGE_TILING_OPTIMAL,
			VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
		);
	}












	const Vulkan_RHI::Swap_Chain_Support_Details Vulkan_RHI::Query_Swap_Chain_Support_Details(const VkPhysicalDevice& Physical_Device, VkSurfaceKHR Surface) {
		Swap_Chain_Support_Details SwapChain_Details{};
		THROW_IF_VK_FAILED(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(Physical_Device, Surface, &SwapChain_Details.Capabilities));

		uint32_t Format_Count{};
		THROW_IF_VK_FAILED(vkGetPhysicalDeviceSurfaceFormatsKHR(Physical_Device, Surface, &Format_Count, nullptr));

		if (0 != Format_Count) {
			SwapChain_Details.Formats.resize(Format_Count);
			THROW_IF_VK_FAILED(vkGetPhysicalDeviceSurfaceFormatsKHR(Physical_Device, Surface, &Format_Count, SwapChain_Details.Formats.data()));
		}
		else
			throw runtime_error("Failed to find a suitable GPU!");

		uint32_t Present_Mode_Count{};
		(vkGetPhysicalDeviceSurfacePresentModesKHR(Physical_Device, Surface, &Present_Mode_Count, nullptr));
		if (0 != Present_Mode_Count) {
			SwapChain_Details.Present_Modes.resize(Present_Mode_Count);
			THROW_IF_VK_FAILED(vkGetPhysicalDeviceSurfacePresentModesKHR(Physical_Device, Surface, &Present_Mode_Count, SwapChain_Details.Present_Modes.data()));
		}
		else
			throw runtime_error("Failed to find a suitable GPU!");

		return SwapChain_Details;

	}

	const VkSurfaceFormatKHR Vulkan_RHI::Choose_SwapChain_Surface_Format(const vector<VkSurfaceFormatKHR>& Available_Formats) {
		for (const auto& Available_Format : Available_Formats)
			if (VK_FORMAT_B8G8R8A8_SRGB == Available_Format.format && VK_COLOR_SPACE_SRGB_NONLINEAR_KHR == Available_Format.colorSpace)
				return Available_Format;

		//NOTE : Default Return First Format
		return Available_Formats.front();
	}

	const VkPresentModeKHR Vulkan_RHI::Choose_SwapChain_Present_Mode(const vector<VkPresentModeKHR>& Available_Present_Modes) {
		for (const auto& Available_Present_Mode : Available_Present_Modes)
			if (VK_PRESENT_MODE_MAILBOX_KHR == Available_Present_Mode)
				return Available_Present_Mode;

		//NOTE : Default Return FIFO ,If Device Suppert Present Queue ,IT Must Support FIFO
		return VK_PRESENT_MODE_FIFO_KHR;
	}

	const VkExtent2D Vulkan_RHI::Choose_SwapChain_Extent(const shared_ptr<Window_System>& Window, const VkSurfaceCapabilitiesKHR& Capabilities) {
		if (numeric_limits<uint32_t>::max() != Capabilities.currentExtent.width)
			return Capabilities.currentExtent;
		else {
			VkExtent2D Actual_Extent{ Window->Get_Window_Width(),Window->Get_Window_Height() };

			Actual_Extent.width = std::clamp(Actual_Extent.width, Capabilities.minImageExtent.width, Capabilities.maxImageExtent.width);
			Actual_Extent.height = std::clamp(Actual_Extent.height, Capabilities.minImageExtent.height, Capabilities.maxImageExtent.height);

			return Actual_Extent;
		}
	}

	const unique_ptr<RHI_Sampler>& Vulkan_RHI::Get_Default_Sampler(RHI_DEFAULT_SAMPLER_TYPE Type) {
		switch (Type)
		{
		case RHI_DEFAULT_SAMPLER_TYPE::DEFAULT_SAMPLER_LINEAR:
			return this->m_Linear_RHI_Sampler;
		case RHI_DEFAULT_SAMPLER_TYPE::DEFAULT_SAMPLER_NEAREST:
			return this->m_Nearest_RHI_Sampler;
		default:
			throw runtime_error("Failed to find default sampler!");
			break;
		}
	}

	const unique_ptr<RHI_Sampler>& Vulkan_RHI::Get_Mipmap_Sampler(uint32_t width, uint32_t height) {
		if (0 == width || 0 == height)
			throw runtime_error("Failed to find mipmap sampler!");

		uint32_t Mip_Levels{ static_cast<uint32_t>(std::floor(std::log2(std::max(width, height))) + 1) };

		auto It = this->m_Mipmap_RHI_Samplers.find(Mip_Levels);
		if (this->m_Mipmap_RHI_Samplers.cend() == It) {
			VkPhysicalDeviceProperties Properties{};
			vkGetPhysicalDeviceProperties(this->m_VK_Physical_Device, &Properties);

			VkSamplerCreateInfo Sampler_Create_Info{};
			{
				Sampler_Create_Info.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
				Sampler_Create_Info.magFilter = VK_FILTER_LINEAR;
				Sampler_Create_Info.minFilter = VK_FILTER_LINEAR;
				Sampler_Create_Info.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
				Sampler_Create_Info.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
				Sampler_Create_Info.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
				Sampler_Create_Info.anisotropyEnable = VK_TRUE;
				Sampler_Create_Info.maxAnisotropy = Properties.limits.maxSamplerAnisotropy;
				Sampler_Create_Info.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
				Sampler_Create_Info.unnormalizedCoordinates = VK_FALSE;
				Sampler_Create_Info.compareEnable = VK_FALSE;
				Sampler_Create_Info.compareOp = VK_COMPARE_OP_ALWAYS;
				Sampler_Create_Info.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
				Sampler_Create_Info.mipLodBias = 0.0f;
				Sampler_Create_Info.minLod = 0.0f;
				Sampler_Create_Info.maxLod = static_cast<float>(Mip_Levels - 1);
			}

			VkSampler Mipmap_Sampler{ nullptr };
			THROW_IF_VK_FAILED(vkCreateSampler(this->m_Logical_VK_Device, &Sampler_Create_Info, this->m_Allocator.get(), &Mipmap_Sampler));
			this->m_Mipmap_RHI_Samplers[Mip_Levels] = std::make_unique<Vulkan_Sampler>();
			static_cast<Vulkan_Sampler*>(this->m_Mipmap_RHI_Samplers[Mip_Levels].get())->Set_Deleter(this->m_VK_Sampler_Deleter);
			static_cast<Vulkan_Sampler*>(this->m_Mipmap_RHI_Samplers[Mip_Levels].get())->Reset(Mipmap_Sampler);

			return this->m_Mipmap_RHI_Samplers[Mip_Levels];
		}
		else
			return It->second;
	}

	const unique_ptr<RHI_Shader_Module> Vulkan_RHI::Create_Shader_Module(const vector<unsigned char>& Shader_Code) {

		unique_ptr<Vulkan_Shader_Module> Shader{ std::make_unique<Vulkan_Shader_Module>() };

		static_cast<Vulkan_Shader_Module*>(Shader.get())->Set_Deleter(this->m_VK_Shader_Module_Deleter);
		static_cast<Vulkan_Shader_Module*>(Shader.get())->Reset(NameSpace_Utilities::Create_Shader_Module(this->m_Logical_VK_Device, Shader_Code));
		return  Shader;
	}


	bool Vulkan_RHI::Set_Buffer_Data(tuple<unique_ptr<RHI_Buffer>, unique_ptr<RHI_Device_Memory>> Buffer_And_Memory, RHI_Device_Size Offset, RHI_Device_Size Size, void* Data) {
		const auto& [Buffer, Device_Memory] = Buffer_And_Memory;
		if (nullptr == Buffer || nullptr == Device_Memory)
			throw runtime_error("Buffer or Device Memory is nullptr!");

		void* Dst_Data{ nullptr };
		//NOTE : No Sue Place Memory EXT
		THROW_IF_VK_FAILED(vkMapMemory(this->m_Logical_VK_Device, static_cast<Vulkan_Device_Memory*>(Device_Memory.get())->Get(), Offset, Size, 0, &Dst_Data));
		std::memcpy(Dst_Data, Data, static_cast<size_t>(Size));
		vkUnmapMemory(this->m_Logical_VK_Device, static_cast<Vulkan_Device_Memory*>(Device_Memory.get())->Get());

		return true;
	}

	/*unique_ptr<RHI_Buffer> Vulkan_RHI::Create_Buffer_With_Alignment_VMA(VmaAllocator Vma_Allocator, const RHI_Buffer_Create_Info& Buffer_Create_Info, const VmaAllocationCreateInfo* pAllocation_Create_Info, RHI_Device_Size Min_Alignment, VmaAllocation* pAllocation, VmaAllocationInfo* pAllocationInfo) {
		VkBufferCreateInfo vk_Buffer_Create_Info{};
		{
			vk_Buffer_Create_Info.sType = static_cast<VkStructureType>(Buffer_Create_Info.sType);
			vk_Buffer_Create_Info.pNext = Buffer_Create_Info.pNext;
			vk_Buffer_Create_Info.flags = static_cast<VkBufferCreateFlags>(Buffer_Create_Info.Flags);
			vk_Buffer_Create_Info.size = static_cast<VkDeviceSize>(Buffer_Create_Info.Size);
			vk_Buffer_Create_Info.usage = static_cast<VkBufferUsageFlags>(Buffer_Create_Info.Usage);
			vk_Buffer_Create_Info.sharingMode = static_cast<VkSharingMode>(Buffer_Create_Info.Sharing_Mode);
			vk_Buffer_Create_Info.queueFamilyIndexCount = Buffer_Create_Info.Queue_Family_Index_Count;
			vk_Buffer_Create_Info.pQueueFamilyIndices = Buffer_Create_Info.pQueue_Family_Indices;
		}

		VkBuffer Temp_Buffer{ nullptr };
		THROW_IF_VK_FAILED(vmaCreateBufferWithAlignment(Vma_Allocator, &vk_Buffer_Create_Info, pAllocation_Create_Info, static_cast<VkDeviceSize>(Min_Alignment), &Temp_Buffer, pAllocation, pAllocationInfo));
		unique_ptr<RHI_Buffer> Buffer{ std::make_unique<Vulkan_Buffer>() };
		static_cast<Vulkan_Buffer*>(Buffer.get())->Set_Deleter(this->m_VK_Buffer_Deleter);
		static_cast<Vulkan_Buffer*>(Buffer.get())->Reset(Temp_Buffer);

		return Buffer;
	}*/

	unique_ptr<RHI_Command_Buffer> Vulkan_RHI::Begin_SingleTime_Commands(void) {
		VkCommandBufferAllocateInfo Allocate_Info{};
		{
			Allocate_Info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
			Allocate_Info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
			Allocate_Info.commandPool = static_cast<Vulkan_Command_Pool*>(this->m_Default_RHI_Command_Pool.get())->Get();
			Allocate_Info.commandBufferCount = 1;
		}

		VkCommandBuffer Command_Buffer{ nullptr };
		THROW_IF_VK_FAILED(vkAllocateCommandBuffers(this->m_Logical_VK_Device, &Allocate_Info, &Command_Buffer));

		VkCommandBufferBeginInfo Begin_Info{};
		{
			Begin_Info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			Begin_Info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
		}

		THROW_IF_VK_FAILED(this->F_vkBeginCommandBuffer(Command_Buffer, &Begin_Info));
		unique_ptr<RHI_Command_Buffer> RHI_Command_Buffer{ std::make_unique<Vulkan_Command_Buffer>() };
		static_cast<Vulkan_Command_Buffer*>(RHI_Command_Buffer.get())->Reset(Command_Buffer);

		return RHI_Command_Buffer;
	}

	void Vulkan_RHI::End_SingleTime_Commands(unique_ptr<RHI_Command_Buffer> Command_Buffer) {
		VkCommandBuffer VK_Command_Buffer{ static_cast<Vulkan_Command_Buffer*>(Command_Buffer.get())->Get() };

		THROW_IF_VK_FAILED(this->F_vkEndCommandBuffer(VK_Command_Buffer));

		VkSubmitInfo Submit_Info{};
		{
			Submit_Info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
			Submit_Info.commandBufferCount = 1;
			Submit_Info.pCommandBuffers = &VK_Command_Buffer;
		}

		THROW_IF_VK_FAILED(vkQueueSubmit(this->m_Queues.Graphic_Queue, 1, &Submit_Info, VK_NULL_HANDLE));
		THROW_IF_VK_FAILED(vkQueueWaitIdle(this->m_Queues.Graphic_Queue));

		vkFreeCommandBuffers(this->m_Logical_VK_Device, static_cast<Vulkan_Command_Pool*>(this->m_Default_RHI_Command_Pool.get())->Get(), 1, &VK_Command_Buffer);
	}

	tuple<unique_ptr<RHI_Image>, unique_ptr<RHI_Device_Memory>> Vulkan_RHI::Create_Image(RHI_Extent_2D Image_Extent, RHI_FORMAT Image_Format, uint32_t Mip_levels, RHI_SAMPLE_COUNT_FLAG_BIT Num_Samples, RHI_IMAGE_TILING Image_Tiling, RHI_Image_Usage_Flags Image_Usage_Flags, RHI_Memory_Property_Flags Memory_Property_Flags, RHI_Image_Create_Flags Image_Create_Flags, uint32_t Array_Layers) {
		VkImage VK_Image{ nullptr };
		VkDeviceMemory VK_Device_Memory{ nullptr };
		NameSpace_Utilities::Create_Image(
			this->m_VK_Physical_Device,
			this->m_Logical_VK_Device,
			static_cast<VkExtent2D>(Image_Extent),
			static_cast<VkFormat>(Image_Format),
			Mip_levels,
			static_cast<VkSampleCountFlagBits>(Num_Samples),
			static_cast<VkImageTiling>(Image_Tiling),
			static_cast<VkImageUsageFlags>(Image_Usage_Flags),
			static_cast<VkMemoryPropertyFlags>(Memory_Property_Flags),
			VK_Image,
			VK_Device_Memory,
			static_cast<VkImageCreateFlags>(Image_Create_Flags),
			Array_Layers,
			this->m_Allocator.get()
		);

		unique_ptr<RHI_Image> Image{ std::make_unique<Vulkan_Image>() };
		static_cast<Vulkan_Image*>(Image.get())->Set_Deleter(this->m_VK_Image_Deleter);
		static_cast<Vulkan_Image*>(Image.get())->Reset(VK_Image);

		unique_ptr<RHI_Device_Memory> Device_Memory{ std::make_unique<Vulkan_Device_Memory>() };
		static_cast<Vulkan_Device_Memory*>(Device_Memory.get())->Set_Deleter(this->m_VK_Device_Memory_Deleter);
		static_cast<Vulkan_Device_Memory*>(Device_Memory.get())->Reset(VK_Device_Memory);

		return std::make_tuple(std::move(Image), std::move(Device_Memory));
	}

	unique_ptr<RHI_Image_View> Vulkan_RHI::Create_Image_View(const unique_ptr<RHI_Image> Image, RHI_FORMAT Format, uint32_t Mip_levels, RHI_Image_Aspect_Flags Image_Aspect_Flags, RHI_IMAGE_VIEW_TYPE View_Type, uint32_t Layout_Count) {
		unique_ptr<RHI_Image_View> Image_View{ std::make_unique<Vulkan_Image_View>() };
		static_cast<Vulkan_Image_View*>(Image_View.get())->Set_Deleter(this->m_VK_Image_View_Deleter);

		static_cast<Vulkan_Image_View*>(Image_View.get())->Reset(NameSpace_Utilities::Create_Image_View(
			this->m_Logical_VK_Device,
			this->m_Allocator.get(),
			static_cast<Vulkan_Image*>(Image.get())->Get(),
			static_cast<VkFormat>(Format),
			Mip_levels,
			static_cast<VkImageAspectFlags>(Image_Aspect_Flags),
			static_cast<VkImageViewType>(View_Type),
			Layout_Count
		));

		return Image_View;
	}

	tuple<unique_ptr<RHI_Image>, unique_ptr<RHI_Image_View>, unique_ptr<RHI_Device_Memory>> Vulkan_RHI::Create_Global_Image()
	{
		return tuple<unique_ptr<RHI_Image>, unique_ptr<RHI_Image_View>, unique_ptr<RHI_Device_Memory>>();
	}










	unique_ptr<RHI_Descriptor_Pool> Vulkan_RHI::Create_Descriptor_Pool(RHI_Descriptor_Pool_Create_Info Create_Info) {
		vector<VkDescriptorPoolSize> Pool_Sizes{};
		Pool_Sizes.reserve(Create_Info.Pool_Sizes.size());
		for (size_t Index = 0; Index < Create_Info.Pool_Sizes.size(); ++Index)
			Pool_Sizes.emplace_back(VkDescriptorPoolSize{ static_cast<VkDescriptorType>(Create_Info.Pool_Sizes[Index].Type), Create_Info.Pool_Sizes[Index].Descriptor_Count });

		VkDescriptorPoolCreateInfo Descriptor_Pool_Create_Info{};
		{
			Descriptor_Pool_Create_Info.sType = static_cast<VkStructureType>(Create_Info.sType);
			Descriptor_Pool_Create_Info.pNext = Create_Info.pNext;
			Descriptor_Pool_Create_Info.flags = static_cast<VkDescriptorPoolCreateFlags>(Create_Info.Flags);
			Descriptor_Pool_Create_Info.maxSets = Create_Info.Max_Sets;
			Descriptor_Pool_Create_Info.poolSizeCount = Pool_Sizes.size();
			Descriptor_Pool_Create_Info.pPoolSizes = Pool_Sizes.data();
		}

		VkDescriptorPool VK_Descriptor_Pool{ nullptr };
		THROW_IF_VK_FAILED(vkCreateDescriptorPool(this->m_Logical_VK_Device, &Descriptor_Pool_Create_Info, this->m_Allocator.get(), &VK_Descriptor_Pool));
		auto Descriptor_Pool{ std::make_unique<Vulkan_Descriptor_Pool>() };
		static_cast<Vulkan_Descriptor_Pool*>(Descriptor_Pool.get())->Set_Deleter(this->m_VK_Descriptor_Pool_Deleter);
		static_cast<Vulkan_Descriptor_Pool*>(Descriptor_Pool.get())->Reset(VK_Descriptor_Pool);

		return Descriptor_Pool;
	}

	unique_ptr<RHI_Descriptor_Set_Layout> Vulkan_RHI::Create_Descriptor_Set_Layout(const RHI_Descriptor_Set_LayOut_Create_Info pCreateInfo) {
		vector<VkDescriptorSetLayoutBinding> Bindings{};
		Bindings.reserve(pCreateInfo.Bindings.size());
		for (size_t Index = 0; Index < pCreateInfo.Bindings.size(); ++Index) {
			vector<VkSampler> Samplers{};
			Samplers.reserve(pCreateInfo.Bindings[Index].Immutable_Samplers.size());
			for (size_t Sampler_Index = 0; Sampler_Index < pCreateInfo.Bindings[Index].Immutable_Samplers.size(); ++Sampler_Index)
				Samplers.emplace_back(static_cast<Vulkan_Sampler*>(pCreateInfo.Bindings[Index].Immutable_Samplers[Sampler_Index].get())->Get());

			VkDescriptorSetLayoutBinding Binding{};
			{
				Binding.binding = pCreateInfo.Bindings[Index].Binding;
				Binding.descriptorType = static_cast<VkDescriptorType>(pCreateInfo.Bindings[Index].Descriptor_Type);
				Binding.descriptorCount = pCreateInfo.Bindings[Index].Descriptor_Count;
				Binding.stageFlags = static_cast<VkShaderStageFlags>(pCreateInfo.Bindings[Index].Stage_Flags);
				Binding.pImmutableSamplers = Samplers.data();
			}

			Bindings.emplace_back(Binding);
		}

		VkDescriptorSetLayoutCreateInfo Descriptor_Set_Layout_Create_Info{};
		{
			Descriptor_Set_Layout_Create_Info.sType = static_cast<VkStructureType>(pCreateInfo.sType);
			Descriptor_Set_Layout_Create_Info.pNext = pCreateInfo.pNext;
			Descriptor_Set_Layout_Create_Info.flags = static_cast<VkDescriptorSetLayoutCreateFlags>(pCreateInfo.Flags);
			Descriptor_Set_Layout_Create_Info.bindingCount = Bindings.size();
			Descriptor_Set_Layout_Create_Info.pBindings = Bindings.data();
		}

		VkDescriptorSetLayout VK_Descriptor_Set_Layout{ nullptr };
		THROW_IF_VK_FAILED(vkCreateDescriptorSetLayout(this->m_Logical_VK_Device, &Descriptor_Set_Layout_Create_Info, this->m_Allocator.get(), &VK_Descriptor_Set_Layout));
		auto Descriptor_Set_Layout{ std::make_unique<Vulkan_Descriptor_Set_Layout>() };
		static_cast<Vulkan_Descriptor_Set_Layout*>(Descriptor_Set_Layout.get())->Set_Deleter(this->m_VK_Descriptor_Set_Layout_Deleter);
		static_cast<Vulkan_Descriptor_Set_Layout*>(Descriptor_Set_Layout.get())->Reset(VK_Descriptor_Set_Layout);

		return Descriptor_Set_Layout;
	}

	unique_ptr<RHI_Fence> Vulkan_RHI::Create_Fence(const RHI_Fence_Create_Info pCreateInfo) {
		VkFenceCreateInfo Fence_Create_Info{};
		{
			Fence_Create_Info.sType = static_cast<VkStructureType>(pCreateInfo.sType);
			Fence_Create_Info.pNext = pCreateInfo.pNext;
			Fence_Create_Info.flags = static_cast<VkFenceCreateFlags>(pCreateInfo.Flags);
		}

		VkFence VK_Fence{ nullptr };
		THROW_IF_VK_FAILED(vkCreateFence(this->m_Logical_VK_Device, &Fence_Create_Info, this->m_Allocator.get(), &VK_Fence));
		auto Fence{ std::make_unique<Vulkan_Fence>() };
		static_cast<Vulkan_Fence*>(Fence.get())->Set_Deleter(this->m_VK_Fence_Deleter);
		static_cast<Vulkan_Fence*>(Fence.get())->Reset(VK_Fence);

		return Fence;
	}

	unique_ptr<RHI_Frame_Buffer> Vulkan_RHI::Create_Frame_Buffer(const RHI_Frame_buffer_Create_Info Create_Info) {
		vector<VkImageView> Attachments{};
		Attachments.reserve(Create_Info.Attachments.size());
		for (size_t Index = 0; Index < Create_Info.Attachments.size(); ++Index)
			Attachments.emplace_back(static_cast<Vulkan_Image_View*>(Create_Info.Attachments[Index].get())->Get());

		VkFramebufferCreateInfo Frame_Buffer_Create_Info{};
		{
			Frame_Buffer_Create_Info.sType = static_cast<VkStructureType>(Create_Info.sType);
			Frame_Buffer_Create_Info.pNext = Create_Info.pNext;
			Frame_Buffer_Create_Info.flags = static_cast<VkFramebufferCreateFlags>(Create_Info.Flags);
			Frame_Buffer_Create_Info.renderPass = static_cast<Vulkan_Render_Pass*>(Create_Info.Render_Pass.get())->Get();
			Frame_Buffer_Create_Info.attachmentCount = Attachments.size();
			Frame_Buffer_Create_Info.pAttachments = Attachments.data();
			Frame_Buffer_Create_Info.width = Create_Info.Width;
			Frame_Buffer_Create_Info.height = Create_Info.Height;
			Frame_Buffer_Create_Info.layers = Create_Info.Layers;
		}

		VkFramebuffer VK_Frame_Buffer{ nullptr };
		THROW_IF_VK_FAILED(vkCreateFramebuffer(this->m_Logical_VK_Device, &Frame_Buffer_Create_Info, this->m_Allocator.get(), &VK_Frame_Buffer));
		auto Frame_Buffer{ std::make_unique<Vulkan_Frame_Buffer>() };
		static_cast<Vulkan_Frame_Buffer*>(Frame_Buffer.get())->Set_Deleter(this->m_VK_Frame_Buffer_Deleter);
		static_cast<Vulkan_Frame_Buffer*>(Frame_Buffer.get())->Reset(VK_Frame_Buffer);

		return Frame_Buffer;
	}


	const optional<vector<VkPipelineShaderStageCreateInfo>> Vulkan_RHI::Parse_RHI_Pipeline_Shader_Stage_Create_Info(const vector<const RHI_Pipeline_Shader_Stage_Create_Info*>* Stages, vector<optional<vector<VkSpecializationMapEntry>>>& vk_Specialization_Map_Entryss, vector<optional<VkSpecializationInfo>>& vk_Specialization_Infos) {
		vector<VkPipelineShaderStageCreateInfo> vk_Pipeline_Shader_Stage_Create_Infos{};
		if (nullptr == Stages || Stages->empty())
			return std::nullopt;

		vk_Pipeline_Shader_Stage_Create_Infos.reserve(Stages->size());


		vk_Specialization_Map_Entryss.reserve(Stages->size());
		vk_Specialization_Infos.reserve(Stages->size());

		for (size_t Index = 0; Index < Stages->size(); ++Index) {
			if (nullptr == Stages->at(Index)->Specialization_Info) {
				vk_Specialization_Infos.emplace_back(std::nullopt);//NOTO : Empty
			}
			else
			{
				if (nullptr == Stages->at(Index)->Specialization_Info->Map_Entries || Stages->at(Index)->Specialization_Info->Map_Entries->empty())
					vk_Specialization_Map_Entryss.emplace_back(std::nullopt);//NOTO : Empty
				else {
					vector<VkSpecializationMapEntry> vk_Specialization_Map_Entrys{};
					vk_Specialization_Map_Entrys.reserve(Stages->at(Index)->Specialization_Info->Map_Entries->size());

					for (size_t Entry_Index = 0; Entry_Index < Stages->at(Index)->Specialization_Info->Map_Entries->size(); ++Entry_Index) {
						if (nullptr == Stages->at(Index)->Specialization_Info->Map_Entries->at(Entry_Index))
							throw runtime_error("Specialization Map Entry is nullptr!");

						VkSpecializationMapEntry vk_Specialization_Map_Entry{};
						{
							vk_Specialization_Map_Entry.constantID = Stages->at(Index)->Specialization_Info->Map_Entries->at(Entry_Index)->Constant_ID;
							vk_Specialization_Map_Entry.offset = Stages->at(Index)->Specialization_Info->Map_Entries->at(Entry_Index)->Offset;
							vk_Specialization_Map_Entry.size = Stages->at(Index)->Specialization_Info->Map_Entries->at(Entry_Index)->Size;
						}

						vk_Specialization_Map_Entrys.emplace_back(vk_Specialization_Map_Entry);
					}

					vk_Specialization_Map_Entryss.emplace_back(vk_Specialization_Map_Entrys);
				}


				VkSpecializationInfo vk_Specialization_Info{};
				{
					vk_Specialization_Info.mapEntryCount = vk_Specialization_Map_Entryss[Index].has_value() ? vk_Specialization_Map_Entryss[Index]->size() : 0;
					vk_Specialization_Info.pMapEntries = vk_Specialization_Map_Entryss[Index].has_value() ? vk_Specialization_Map_Entryss[Index]->data() : nullptr;
					vk_Specialization_Info.dataSize = Stages->at(Index)->Specialization_Info->Data_Size;
					vk_Specialization_Info.pData = Stages->at(Index)->Specialization_Info->Data;
				}

				vk_Specialization_Infos.emplace_back(vk_Specialization_Info);
			}

			VkPipelineShaderStageCreateInfo vk_Pipeline_Shader_Stage_Create_Info{};
			{
				vk_Pipeline_Shader_Stage_Create_Info.sType = static_cast<VkStructureType>(Stages->at(Index)->sType);
				vk_Pipeline_Shader_Stage_Create_Info.pNext = Stages->at(Index)->pNext;
				vk_Pipeline_Shader_Stage_Create_Info.flags = static_cast<VkPipelineShaderStageCreateFlags>(Stages->at(Index)->Flags);
				vk_Pipeline_Shader_Stage_Create_Info.stage = static_cast<VkShaderStageFlagBits>(Stages->at(Index)->Stage);
				vk_Pipeline_Shader_Stage_Create_Info.module = static_cast<Vulkan_Shader_Module*>(Stages->at(Index)->Module)->Get();
				vk_Pipeline_Shader_Stage_Create_Info.pName = Stages->at(Index)->pName;
				vk_Pipeline_Shader_Stage_Create_Info.pSpecializationInfo = vk_Specialization_Infos[Index].has_value() ? &vk_Specialization_Infos[Index].value() : nullptr;
			}

			vk_Pipeline_Shader_Stage_Create_Infos.emplace_back(vk_Pipeline_Shader_Stage_Create_Info);
		}

		return std::make_optional(vk_Pipeline_Shader_Stage_Create_Infos);
	}

	const optional<VkPipelineVertexInputStateCreateInfo> Vulkan_RHI::Parser_RHI_Pipeline_Vertex_Input_State_Create_Info(const RHI_Pipeline_Vertex_Input_State_Create_Info* Vertex_Input_State_Create_Info, optional<vector<VkVertexInputBindingDescription>>& vk_Vertex_Input_Binding_Descriptions, optional<vector<VkVertexInputAttributeDescription>>& vk_Vertex_Input_Attribute_Descriptions) {
		if (nullptr == Vertex_Input_State_Create_Info)
			return std::nullopt;
		if (nullptr == Vertex_Input_State_Create_Info->Vertex_Binding_Descriptions || Vertex_Input_State_Create_Info->Vertex_Binding_Descriptions->empty())
			vk_Vertex_Input_Binding_Descriptions = std::nullopt;
		else {
			vk_Vertex_Input_Binding_Descriptions = std::make_optional<vector<VkVertexInputBindingDescription>>();
			vk_Vertex_Input_Binding_Descriptions->reserve(Vertex_Input_State_Create_Info->Vertex_Binding_Descriptions->size());

			for (size_t Index = 0; Index < Vertex_Input_State_Create_Info->Vertex_Binding_Descriptions->size(); ++Index) {
				if (nullptr == Vertex_Input_State_Create_Info->Vertex_Binding_Descriptions->at(Index))
					throw runtime_error("Vertex Binding Description is nullptr!");

				VkVertexInputBindingDescription vk_Vertex_Input_Binding_Description{};
				{
					vk_Vertex_Input_Binding_Description.binding = Vertex_Input_State_Create_Info->Vertex_Binding_Descriptions->at(Index)->Binding;
					vk_Vertex_Input_Binding_Description.stride = Vertex_Input_State_Create_Info->Vertex_Binding_Descriptions->at(Index)->Stride;
					vk_Vertex_Input_Binding_Description.inputRate = static_cast<VkVertexInputRate>(Vertex_Input_State_Create_Info->Vertex_Binding_Descriptions->at(Index)->Input_Rate);
				}

				vk_Vertex_Input_Binding_Descriptions->emplace_back(vk_Vertex_Input_Binding_Description);
			}
		}

		if (nullptr == Vertex_Input_State_Create_Info->Vertex_Attribute_Descriptions || Vertex_Input_State_Create_Info->Vertex_Attribute_Descriptions->empty())
			vk_Vertex_Input_Attribute_Descriptions = std::nullopt;
		else {
			vk_Vertex_Input_Attribute_Descriptions = std::make_optional<vector<VkVertexInputAttributeDescription>>();
			vk_Vertex_Input_Attribute_Descriptions->reserve(Vertex_Input_State_Create_Info->Vertex_Attribute_Descriptions->size());

			for (size_t Index = 0; Index < Vertex_Input_State_Create_Info->Vertex_Attribute_Descriptions->size(); ++Index) {
				if (nullptr == Vertex_Input_State_Create_Info->Vertex_Attribute_Descriptions->at(Index))
					throw runtime_error("Vertex Attribute Description is nullptr!");

				VkVertexInputAttributeDescription vk_Vertex_Input_Attribute_Description{};
				{
					vk_Vertex_Input_Attribute_Description.location = Vertex_Input_State_Create_Info->Vertex_Attribute_Descriptions->at(Index)->Location;
					vk_Vertex_Input_Attribute_Description.binding = Vertex_Input_State_Create_Info->Vertex_Attribute_Descriptions->at(Index)->Binding;
					vk_Vertex_Input_Attribute_Description.format = static_cast<VkFormat>(Vertex_Input_State_Create_Info->Vertex_Attribute_Descriptions->at(Index)->Format);
					vk_Vertex_Input_Attribute_Description.offset = Vertex_Input_State_Create_Info->Vertex_Attribute_Descriptions->at(Index)->Offset;
				}

				vk_Vertex_Input_Attribute_Descriptions->emplace_back(vk_Vertex_Input_Attribute_Description);
			}
		}

		VkPipelineVertexInputStateCreateInfo vk_Pipeline_Vertex_Input_State_Create_Info{};
		{
			vk_Pipeline_Vertex_Input_State_Create_Info.sType = static_cast<VkStructureType>(Vertex_Input_State_Create_Info->sType);
			vk_Pipeline_Vertex_Input_State_Create_Info.pNext = Vertex_Input_State_Create_Info->pNext;
			vk_Pipeline_Vertex_Input_State_Create_Info.flags = static_cast<VkPipelineVertexInputStateCreateFlags>(Vertex_Input_State_Create_Info->Flags);
			vk_Pipeline_Vertex_Input_State_Create_Info.vertexBindingDescriptionCount = vk_Vertex_Input_Binding_Descriptions.has_value() ? vk_Vertex_Input_Binding_Descriptions->size() : 0;
			vk_Pipeline_Vertex_Input_State_Create_Info.pVertexBindingDescriptions = vk_Vertex_Input_Binding_Descriptions.has_value() ? vk_Vertex_Input_Binding_Descriptions->data() : nullptr;
			vk_Pipeline_Vertex_Input_State_Create_Info.vertexAttributeDescriptionCount = vk_Vertex_Input_Attribute_Descriptions.has_value() ? vk_Vertex_Input_Attribute_Descriptions->size() : 0;
			vk_Pipeline_Vertex_Input_State_Create_Info.pVertexAttributeDescriptions = vk_Vertex_Input_Attribute_Descriptions.has_value() ? vk_Vertex_Input_Attribute_Descriptions->data() : nullptr;
		}

		return std::make_optional(vk_Pipeline_Vertex_Input_State_Create_Info);
	}

	const optional<VkPipelineInputAssemblyStateCreateInfo> Vulkan_RHI::Parser_RHI_Pipeline_Input_Assembly_State_Create_Info(const RHI_Pipeline_Input_Assembly_State_Create_Info* vk_Input_Assembly_State_Create_Info) {
		if (nullptr == vk_Input_Assembly_State_Create_Info)
			return std::nullopt;

		VkPipelineInputAssemblyStateCreateInfo vk_Pipeline_Input_Assembly_State_Create_Info{};
		{
			vk_Pipeline_Input_Assembly_State_Create_Info.sType = static_cast<VkStructureType>(vk_Input_Assembly_State_Create_Info->sType);
			vk_Pipeline_Input_Assembly_State_Create_Info.pNext = vk_Input_Assembly_State_Create_Info->pNext;
			vk_Pipeline_Input_Assembly_State_Create_Info.flags = static_cast<VkPipelineInputAssemblyStateCreateFlags>(vk_Input_Assembly_State_Create_Info->Flags);
			vk_Pipeline_Input_Assembly_State_Create_Info.topology = static_cast<VkPrimitiveTopology>(vk_Input_Assembly_State_Create_Info->Topology);
			vk_Pipeline_Input_Assembly_State_Create_Info.primitiveRestartEnable = static_cast<VkBool32>(vk_Input_Assembly_State_Create_Info->Primitive_Restart_Enable);
		}

		return std::make_optional(vk_Pipeline_Input_Assembly_State_Create_Info);
	}

	const optional<VkPipelineTessellationStateCreateInfo> Vulkan_RHI::Parser_RHI_Pipeline_Tessellation_State_Create_Info(const RHI_Pipeline_Tessellation_State_Create_Info* vk_Tessellation_State_Create_Info) {
		if (nullptr == vk_Tessellation_State_Create_Info)
			return std::nullopt;

		VkPipelineTessellationStateCreateInfo vk_Pipeline_Tessellation_State_Create_Info{};
		{
			vk_Pipeline_Tessellation_State_Create_Info.sType = static_cast<VkStructureType>(vk_Tessellation_State_Create_Info->sType);
			vk_Pipeline_Tessellation_State_Create_Info.pNext = vk_Tessellation_State_Create_Info->pNext;
			vk_Pipeline_Tessellation_State_Create_Info.flags = static_cast<VkPipelineTessellationStateCreateFlags>(vk_Tessellation_State_Create_Info->Flags);
			vk_Pipeline_Tessellation_State_Create_Info.patchControlPoints = vk_Tessellation_State_Create_Info->Patch_Control_Points;
		}

		return std::make_optional(vk_Pipeline_Tessellation_State_Create_Info);
	}

	const optional<VkPipelineViewportStateCreateInfo> Vulkan_RHI::Parser_RHI_Pipeline_Viewport_State_Create_Info(const RHI_Pipeline_Viewport_State_Create_Info* vk_Viewport_State_Create_Info, optional<vector<VkViewport>>& Viewports, optional<vector<VkRect2D>>& Scissors) {
		if (nullptr == vk_Viewport_State_Create_Info)
			return std::nullopt;

		if (nullptr == vk_Viewport_State_Create_Info->Viewports || vk_Viewport_State_Create_Info->Viewports->empty())
			Viewports = std::nullopt;
		else {
			Viewports = std::make_optional<vector<VkViewport>>();
			Viewports->reserve(vk_Viewport_State_Create_Info->Viewports->size());

			for (size_t Index = 0; Index < vk_Viewport_State_Create_Info->Viewports->size(); ++Index) {
				if (nullptr == vk_Viewport_State_Create_Info->Viewports->at(Index))
					throw runtime_error("Viewport is nullptr!");

				VkViewport vk_Viewport{};
				{
					vk_Viewport.x = vk_Viewport_State_Create_Info->Viewports->at(Index)->X;
					vk_Viewport.y = vk_Viewport_State_Create_Info->Viewports->at(Index)->Y;
					vk_Viewport.width = vk_Viewport_State_Create_Info->Viewports->at(Index)->Width;
					vk_Viewport.height = vk_Viewport_State_Create_Info->Viewports->at(Index)->Height;
					vk_Viewport.minDepth = vk_Viewport_State_Create_Info->Viewports->at(Index)->Min_Depth;
					vk_Viewport.maxDepth = vk_Viewport_State_Create_Info->Viewports->at(Index)->Max_Depth;
				}
				Viewports->emplace_back(vk_Viewport);
			}
		}

		if (nullptr == vk_Viewport_State_Create_Info->Scissors || vk_Viewport_State_Create_Info->Scissors->empty())
			Scissors = std::nullopt;
		else {
			Scissors = std::make_optional<vector<VkRect2D>>();
			Scissors->reserve(vk_Viewport_State_Create_Info->Scissors->size());
			for (size_t Index = 0; Index < vk_Viewport_State_Create_Info->Scissors->size(); ++Index) {
				if (nullptr == vk_Viewport_State_Create_Info->Scissors->at(Index))
					throw runtime_error("Scissor is nullptr!");

				VkRect2D vk_Rect2D{};
				{
					vk_Rect2D.offset = { vk_Viewport_State_Create_Info->Scissors->at(Index)->Offset.X, vk_Viewport_State_Create_Info->Scissors->at(Index)->Offset.Y };
					vk_Rect2D.extent = { vk_Viewport_State_Create_Info->Scissors->at(Index)->Extent.Width, vk_Viewport_State_Create_Info->Scissors->at(Index)->Extent.Height };
				}

				Scissors->emplace_back(vk_Rect2D);
			}
		}

		VkPipelineViewportStateCreateInfo vk_Pipeline_Viewport_State_Create_Info{};
		{
			vk_Pipeline_Viewport_State_Create_Info.sType = static_cast<VkStructureType>(vk_Viewport_State_Create_Info->sType);
			vk_Pipeline_Viewport_State_Create_Info.pNext = vk_Viewport_State_Create_Info->pNext;
			vk_Pipeline_Viewport_State_Create_Info.flags = static_cast<VkPipelineViewportStateCreateFlags>(vk_Viewport_State_Create_Info->Flags);
			vk_Pipeline_Viewport_State_Create_Info.viewportCount = Viewports.has_value() ? Viewports->size() : 0;
			vk_Pipeline_Viewport_State_Create_Info.pViewports = Viewports.has_value() ? Viewports->data() : nullptr;
			vk_Pipeline_Viewport_State_Create_Info.scissorCount = Scissors.has_value() ? Scissors->size() : 0;
			vk_Pipeline_Viewport_State_Create_Info.pScissors = Scissors.has_value() ? Scissors->data() : nullptr;
		}

		return std::make_optional(vk_Pipeline_Viewport_State_Create_Info);
	}

	const optional<VkPipelineRasterizationStateCreateInfo> Vulkan_RHI::Parser_RHI_Pipeline_Rasterization_State_Create_Info(const RHI_Pipeline_Rasterization_State_Create_Info* vk_Rasterization_State_Create_Info) {
		if (nullptr == vk_Rasterization_State_Create_Info)
			return std::nullopt;

		VkPipelineRasterizationStateCreateInfo vk_Pipeline_Rasterization_State_Create_Info{};
		{
			vk_Pipeline_Rasterization_State_Create_Info.sType = static_cast<VkStructureType>(vk_Rasterization_State_Create_Info->sType);
			vk_Pipeline_Rasterization_State_Create_Info.pNext = vk_Rasterization_State_Create_Info->pNext;
			vk_Pipeline_Rasterization_State_Create_Info.flags = static_cast<VkPipelineRasterizationStateCreateFlags>(vk_Rasterization_State_Create_Info->Flags);
			vk_Pipeline_Rasterization_State_Create_Info.depthClampEnable = static_cast<VkBool32>(vk_Rasterization_State_Create_Info->Depth_Clamp_Enable);
			vk_Pipeline_Rasterization_State_Create_Info.rasterizerDiscardEnable = static_cast<VkBool32>(vk_Rasterization_State_Create_Info->Rasterizer_Discard_Enable);
			vk_Pipeline_Rasterization_State_Create_Info.polygonMode = static_cast<VkPolygonMode>(vk_Rasterization_State_Create_Info->Polygon_Mode);
			vk_Pipeline_Rasterization_State_Create_Info.cullMode = static_cast<VkCullModeFlags>(vk_Rasterization_State_Create_Info->Cull_Mode);
			vk_Pipeline_Rasterization_State_Create_Info.frontFace = static_cast<VkFrontFace>(vk_Rasterization_State_Create_Info->Front_Face);
			vk_Pipeline_Rasterization_State_Create_Info.depthBiasEnable = static_cast<VkBool32>(vk_Rasterization_State_Create_Info->Depth_Bias_Enable);
			vk_Pipeline_Rasterization_State_Create_Info.depthBiasConstantFactor = vk_Rasterization_State_Create_Info->Depth_Bias_Constant_Factor;
			vk_Pipeline_Rasterization_State_Create_Info.depthBiasClamp = vk_Rasterization_State_Create_Info->Depth_Bias_Clamp;
			vk_Pipeline_Rasterization_State_Create_Info.depthBiasSlopeFactor = vk_Rasterization_State_Create_Info->Depth_Bias_Slope_Factor;
			vk_Pipeline_Rasterization_State_Create_Info.lineWidth = vk_Rasterization_State_Create_Info->Line_Width;
		}

		return std::make_optional(vk_Pipeline_Rasterization_State_Create_Info);
	}

	const optional<VkPipelineMultisampleStateCreateInfo> Vulkan_RHI::Parser_RHI_Pipeline_Multisample_State_Create_Info(const RHI_Pipeline_Multisample_State_Create_Info* vk_Multisample_State_Create_Info, optional<VkSampleMask>& vk_Sample_Mask) {
		if (nullptr == vk_Multisample_State_Create_Info)
			return std::nullopt;

		if (nullptr == vk_Multisample_State_Create_Info->Sample_Mask)
			vk_Sample_Mask = std::nullopt;
		else {
			vk_Sample_Mask = std::make_optional<VkSampleMask>();
			vk_Sample_Mask = *vk_Multisample_State_Create_Info->Sample_Mask;
		}

		VkPipelineMultisampleStateCreateInfo vk_Pipeline_Multisample_State_Create_Info{};
		{
			vk_Pipeline_Multisample_State_Create_Info.sType = static_cast<VkStructureType>(vk_Multisample_State_Create_Info->sType);
			vk_Pipeline_Multisample_State_Create_Info.pNext = vk_Multisample_State_Create_Info->pNext;
			vk_Pipeline_Multisample_State_Create_Info.flags = static_cast<VkPipelineMultisampleStateCreateFlags>(vk_Multisample_State_Create_Info->Flags);
			vk_Pipeline_Multisample_State_Create_Info.rasterizationSamples = static_cast<VkSampleCountFlagBits>(vk_Multisample_State_Create_Info->Rasterization_Samples);
			vk_Pipeline_Multisample_State_Create_Info.sampleShadingEnable = static_cast<VkBool32>(vk_Multisample_State_Create_Info->Sample_Shading_Enable);
			vk_Pipeline_Multisample_State_Create_Info.minSampleShading = vk_Multisample_State_Create_Info->Min_Sample_Shading;
			vk_Pipeline_Multisample_State_Create_Info.pSampleMask = vk_Sample_Mask.has_value() ? &vk_Sample_Mask.value() : nullptr;
			vk_Pipeline_Multisample_State_Create_Info.alphaToCoverageEnable = static_cast<VkBool32>(vk_Multisample_State_Create_Info->Alpha_To_Coverage_Enable);
			vk_Pipeline_Multisample_State_Create_Info.alphaToOneEnable = static_cast<VkBool32>(vk_Multisample_State_Create_Info->Alpha_To_One_Enable);
		}

		return std::make_optional(vk_Pipeline_Multisample_State_Create_Info);
	}

	const optional<VkPipelineDepthStencilStateCreateInfo> Vulkan_RHI::Parser_RHI_Pipeline_Depth_Stencil_State_Create_Info(const RHI_Pipeline_Depth_Stencil_State_Create_Info* vk_Depth_Stencil_State_Create_Info, VkStencilOpState& vk_Front_Stencil_Op_State, VkStencilOpState& vk_Back_Stencil_Op_State) {
		if (nullptr == vk_Depth_Stencil_State_Create_Info)
			return std::nullopt;

		{
			vk_Front_Stencil_Op_State.failOp = static_cast<VkStencilOp>(vk_Depth_Stencil_State_Create_Info->Front.Fail_Op);
			vk_Front_Stencil_Op_State.passOp = static_cast<VkStencilOp>(vk_Depth_Stencil_State_Create_Info->Front.Pass_Op);
			vk_Front_Stencil_Op_State.depthFailOp = static_cast<VkStencilOp>(vk_Depth_Stencil_State_Create_Info->Front.Depth_Fail_Op);
			vk_Front_Stencil_Op_State.compareOp = static_cast<VkCompareOp>(vk_Depth_Stencil_State_Create_Info->Front.Compare_Op);
		}

		{
			vk_Back_Stencil_Op_State.failOp = static_cast<VkStencilOp>(vk_Depth_Stencil_State_Create_Info->Back.Fail_Op);
			vk_Back_Stencil_Op_State.passOp = static_cast<VkStencilOp>(vk_Depth_Stencil_State_Create_Info->Back.Pass_Op);
			vk_Back_Stencil_Op_State.depthFailOp = static_cast<VkStencilOp>(vk_Depth_Stencil_State_Create_Info->Back.Depth_Fail_Op);
			vk_Back_Stencil_Op_State.compareOp = static_cast<VkCompareOp>(vk_Depth_Stencil_State_Create_Info->Back.Compare_Op);
		}

		VkPipelineDepthStencilStateCreateInfo vk_Pipeline_Depth_Stencil_State_Create_Info{};
		{
			vk_Pipeline_Depth_Stencil_State_Create_Info.sType = static_cast<VkStructureType>(vk_Depth_Stencil_State_Create_Info->sType);
			vk_Pipeline_Depth_Stencil_State_Create_Info.pNext = vk_Depth_Stencil_State_Create_Info->pNext;
			vk_Pipeline_Depth_Stencil_State_Create_Info.flags = static_cast<VkPipelineDepthStencilStateCreateFlags>(vk_Depth_Stencil_State_Create_Info->Flags);
			vk_Pipeline_Depth_Stencil_State_Create_Info.depthTestEnable = static_cast<VkBool32>(vk_Depth_Stencil_State_Create_Info->Depth_Test_Enable);
			vk_Pipeline_Depth_Stencil_State_Create_Info.depthWriteEnable = static_cast<VkBool32>(vk_Depth_Stencil_State_Create_Info->Depth_Write_Enable);
			vk_Pipeline_Depth_Stencil_State_Create_Info.depthCompareOp = static_cast<VkCompareOp>(vk_Depth_Stencil_State_Create_Info->Depth_Compare_Op);
			vk_Pipeline_Depth_Stencil_State_Create_Info.depthBoundsTestEnable = static_cast<VkBool32>(vk_Depth_Stencil_State_Create_Info->Depth_Bounds_Test_Enable);
			vk_Pipeline_Depth_Stencil_State_Create_Info.stencilTestEnable = static_cast<VkBool32>(vk_Depth_Stencil_State_Create_Info->Stencil_Test_Enable);
			vk_Pipeline_Depth_Stencil_State_Create_Info.front = vk_Front_Stencil_Op_State;
			vk_Pipeline_Depth_Stencil_State_Create_Info.back = vk_Back_Stencil_Op_State;
			vk_Pipeline_Depth_Stencil_State_Create_Info.minDepthBounds = vk_Depth_Stencil_State_Create_Info->Min_Depth_Bounds;
			vk_Pipeline_Depth_Stencil_State_Create_Info.maxDepthBounds = vk_Depth_Stencil_State_Create_Info->Max_Depth_Bounds;
		}

		return std::make_optional(vk_Pipeline_Depth_Stencil_State_Create_Info);
	}

	const optional<VkPipelineColorBlendStateCreateInfo> Vulkan_RHI::Parser_RHI_Pipeline_Color_Blend_State_Create_Info(const RHI_Pipeline_Color_Blend_State_Create_Info* vk_Color_Blend_State_Create_Info, optional<vector<VkPipelineColorBlendAttachmentState>>& vk_Color_Blend_Attachment_States, array<float, 4>& Blend_Constants) {
		if (nullptr == vk_Color_Blend_State_Create_Info)
			return std::nullopt;

		if (nullptr == vk_Color_Blend_State_Create_Info->Attachments || vk_Color_Blend_State_Create_Info->Attachments->empty())
			vk_Color_Blend_Attachment_States = std::nullopt;
		else {
			vk_Color_Blend_Attachment_States = std::make_optional<vector<VkPipelineColorBlendAttachmentState>>();
			vk_Color_Blend_Attachment_States->reserve(vk_Color_Blend_State_Create_Info->Attachments->size());

			for (size_t Index = 0; Index < vk_Color_Blend_State_Create_Info->Attachments->size(); ++Index) {
				if (nullptr == vk_Color_Blend_State_Create_Info->Attachments->at(Index))
					throw runtime_error("Color Blend Attachment State is nullptr!");

				VkPipelineColorBlendAttachmentState vk_Pipeline_Color_Blend_Attachment_State{};
				{
					vk_Pipeline_Color_Blend_Attachment_State.blendEnable = static_cast<VkBool32>(vk_Color_Blend_State_Create_Info->Attachments->at(Index)->Blend_Enable);
					vk_Pipeline_Color_Blend_Attachment_State.srcColorBlendFactor = static_cast<VkBlendFactor>(vk_Color_Blend_State_Create_Info->Attachments->at(Index)->Src_Color_Blend_Factor);
					vk_Pipeline_Color_Blend_Attachment_State.dstColorBlendFactor = static_cast<VkBlendFactor>(vk_Color_Blend_State_Create_Info->Attachments->at(Index)->Dst_Color_Blend_Factor);
					vk_Pipeline_Color_Blend_Attachment_State.colorBlendOp = static_cast<VkBlendOp>(vk_Color_Blend_State_Create_Info->Attachments->at(Index)->Color_Blend_Op);
					vk_Pipeline_Color_Blend_Attachment_State.srcAlphaBlendFactor = static_cast<VkBlendFactor>(vk_Color_Blend_State_Create_Info->Attachments->at(Index)->Src_Alpha_Blend_Factor);
					vk_Pipeline_Color_Blend_Attachment_State.dstAlphaBlendFactor = static_cast<VkBlendFactor>(vk_Color_Blend_State_Create_Info->Attachments->at(Index)->Dst_Alpha_Blend_Factor);
					vk_Pipeline_Color_Blend_Attachment_State.alphaBlendOp = static_cast<VkBlendOp>(vk_Color_Blend_State_Create_Info->Attachments->at(Index)->Alpha_Blend_Op);
					vk_Pipeline_Color_Blend_Attachment_State.colorWriteMask = static_cast<VkColorComponentFlags>(vk_Color_Blend_State_Create_Info->Attachments->at(Index)->Color_Write_Mask);
				}

				vk_Color_Blend_Attachment_States->emplace_back(vk_Pipeline_Color_Blend_Attachment_State);
			}
		}


		Blend_Constants = vk_Color_Blend_State_Create_Info->Blend_Constan;

		VkPipelineColorBlendStateCreateInfo vk_Pipeline_Color_Blend_State_Create_Info{};
		{
			vk_Pipeline_Color_Blend_State_Create_Info.sType = static_cast<VkStructureType>(vk_Color_Blend_State_Create_Info->sType);
			vk_Pipeline_Color_Blend_State_Create_Info.pNext = vk_Color_Blend_State_Create_Info->pNext;
			vk_Pipeline_Color_Blend_State_Create_Info.flags = static_cast<VkPipelineColorBlendStateCreateFlags>(vk_Color_Blend_State_Create_Info->Flags);
			vk_Pipeline_Color_Blend_State_Create_Info.logicOpEnable = static_cast<VkBool32>(vk_Color_Blend_State_Create_Info->Logic_Op_Enable);
			vk_Pipeline_Color_Blend_State_Create_Info.logicOp = static_cast<VkLogicOp>(vk_Color_Blend_State_Create_Info->Logic_Op);
			vk_Pipeline_Color_Blend_State_Create_Info.attachmentCount = vk_Color_Blend_Attachment_States.has_value() ? vk_Color_Blend_Attachment_States->size() : 0;
			vk_Pipeline_Color_Blend_State_Create_Info.pAttachments = vk_Color_Blend_Attachment_States.has_value() ? vk_Color_Blend_Attachment_States->data() : nullptr;
			vk_Pipeline_Color_Blend_State_Create_Info.blendConstants[0] = Blend_Constants[0];
			vk_Pipeline_Color_Blend_State_Create_Info.blendConstants[1] = Blend_Constants[1];
			vk_Pipeline_Color_Blend_State_Create_Info.blendConstants[2] = Blend_Constants[2];
			vk_Pipeline_Color_Blend_State_Create_Info.blendConstants[3] = Blend_Constants[3];
		}

		return std::make_optional(vk_Pipeline_Color_Blend_State_Create_Info);
	}

	const optional<VkPipelineDynamicStateCreateInfo> Vulkan_RHI::Parser_RHI_Pipeline_Dynamic_State_Create_Info(const RHI_Pipeline_Dynamic_State_Create_Info* vk_Dynamic_State_Create_Info, optional<vector<VkDynamicState>>& vk_Dynamic_States) {
		if (nullptr == vk_Dynamic_State_Create_Info)
			return std::nullopt;

		if (nullptr == vk_Dynamic_State_Create_Info->Dynamic_States || vk_Dynamic_State_Create_Info->Dynamic_States->empty())
			vk_Dynamic_States = std::nullopt;
		else {
			vk_Dynamic_States = std::make_optional<vector<VkDynamicState>>();
			vk_Dynamic_States->reserve(vk_Dynamic_State_Create_Info->Dynamic_States->size());

			for (size_t Index = 0; Index < vk_Dynamic_State_Create_Info->Dynamic_States->size(); ++Index) {
				if (nullptr == vk_Dynamic_State_Create_Info->Dynamic_States->at(Index))
					throw runtime_error("Dynamic State is nullptr!");

				vk_Dynamic_States->push_back(static_cast<VkDynamicState>(*vk_Dynamic_State_Create_Info->Dynamic_States->at(Index)));
			}
		}

		VkPipelineDynamicStateCreateInfo vk_Pipeline_Dynamic_State_Create_Info{};
		{
			vk_Pipeline_Dynamic_State_Create_Info.sType = static_cast<VkStructureType>(vk_Dynamic_State_Create_Info->sType);
			vk_Pipeline_Dynamic_State_Create_Info.pNext = vk_Dynamic_State_Create_Info->pNext;
			vk_Pipeline_Dynamic_State_Create_Info.flags = static_cast<VkPipelineDynamicStateCreateFlags>(vk_Dynamic_State_Create_Info->Flags);
			vk_Pipeline_Dynamic_State_Create_Info.dynamicStateCount = vk_Dynamic_States.has_value() ? vk_Dynamic_States->size() : 0;
			vk_Pipeline_Dynamic_State_Create_Info.pDynamicStates = vk_Dynamic_States.has_value() ? vk_Dynamic_States->data() : nullptr;
		}

		return std::make_optional(vk_Pipeline_Dynamic_State_Create_Info);
	}

	const optional<vector<VkAttachmentReference>> Vulkan_RHI::Parser_RHI_Attachment_Reference(const vector<const RHI_Attachment_Reference*>* Attachment_References) {
		if (nullptr == Attachment_References || Attachment_References->empty())
			return std::nullopt;

		vector<VkAttachmentReference> vk_Attachment_References{};
		vk_Attachment_References.reserve(Attachment_References->size());
		for (size_t Index = 0; Index < Attachment_References->size(); ++Index) {
			if (nullptr == Attachment_References->at(Index))
				throw runtime_error("Attachment Reference is nullptr!");

			VkAttachmentReference vk_Attachment_Reference{};
			{
				vk_Attachment_Reference.attachment = Attachment_References->at(Index)->Attachment;
				vk_Attachment_Reference.layout = static_cast<VkImageLayout>(Attachment_References->at(Index)->Layout);
			}

			vk_Attachment_References.emplace_back(vk_Attachment_Reference);
		}

		return std::make_optional(vk_Attachment_References);
	}

	const optional<VkClearValue> Vulkan_RHI::Parser_RHI_Clear_Value(const RHI_Clear_Value* Clear_Value) {
		if (nullptr == Clear_Value)
			return std::nullopt;

		VkClearValue vk_Clear_Value{};
		if (Clear_Value->Color.has_value() && (!Clear_Value->Depth_Stencil.has_value())) {
			if (Clear_Value->Color->Float32.has_value() && (!Clear_Value->Color->Int32.has_value()) && (!Clear_Value->Color->Uint32.has_value())) {
				vk_Clear_Value.color.float32[0] = Clear_Value->Color->Float32->at(0);
				vk_Clear_Value.color.float32[1] = Clear_Value->Color->Float32->at(1);
				vk_Clear_Value.color.float32[2] = Clear_Value->Color->Float32->at(2);
				vk_Clear_Value.color.float32[3] = Clear_Value->Color->Float32->at(3);
			}
			else if ((!Clear_Value->Color->Float32.has_value()) && Clear_Value->Color->Int32.has_value() && (!Clear_Value->Color->Uint32.has_value())) {
				vk_Clear_Value.color.int32[0] = Clear_Value->Color->Int32->at(0);
				vk_Clear_Value.color.int32[1] = Clear_Value->Color->Int32->at(1);
				vk_Clear_Value.color.int32[2] = Clear_Value->Color->Int32->at(2);
				vk_Clear_Value.color.int32[3] = Clear_Value->Color->Int32->at(3);
			}
			else if ((!Clear_Value->Color->Float32.has_value()) && (!Clear_Value->Color->Int32.has_value()) && Clear_Value->Color->Uint32.has_value()) {
				vk_Clear_Value.color.uint32[0] = Clear_Value->Color->Uint32->at(0);
				vk_Clear_Value.color.uint32[1] = Clear_Value->Color->Uint32->at(1);
				vk_Clear_Value.color.uint32[2] = Clear_Value->Color->Uint32->at(2);
				vk_Clear_Value.color.uint32[3] = Clear_Value->Color->Uint32->at(3);
			}
			else
				System_Logger::Get_Instance().Log(System_Logger::Level::err, "Union ");

		}
		else if (Clear_Value->Depth_Stencil.has_value() && (!Clear_Value->Color.has_value())) {
			vk_Clear_Value.depthStencil.depth = Clear_Value->Depth_Stencil->Depth;
			vk_Clear_Value.depthStencil.stencil = Clear_Value->Depth_Stencil->Stencil;
		}
		else
			System_Logger::Get_Instance().Log(System_Logger::Level::err, "Union ");

		return std::make_optional(vk_Clear_Value);
	}





	unique_ptr<RHI_Pipeline> Vulkan_RHI::Create_Graphics_Pipeline(optional<RHI_Pipeline_Cache*> Pipeline_Cache, const RHI_Graphics_Pipeline_Create_Info* Create_Info) {

		vector<optional<vector<VkSpecializationMapEntry>>> vk_Specialization_Map_Entryss{};
		vector<optional<VkSpecializationInfo>> vk_Specialization_Infos{};
		auto vk_Pipeline_Shader_Stage_Create_Infos{ Vulkan_RHI::Parse_RHI_Pipeline_Shader_Stage_Create_Info(Create_Info->Stages, vk_Specialization_Map_Entryss, vk_Specialization_Infos) };

		optional<vector<VkVertexInputBindingDescription>> vk_Vertex_Input_Binding_Descriptions{};
		optional<vector<VkVertexInputAttributeDescription>> vk_Vertex_Input_Attribute_Descriptions{};
		auto vk_Pipeline_Vertex_Input_State_Create_Info{ Vulkan_RHI::Parser_RHI_Pipeline_Vertex_Input_State_Create_Info(Create_Info->Vertex_Input_State, vk_Vertex_Input_Binding_Descriptions, vk_Vertex_Input_Attribute_Descriptions) };

		auto vk_Pipeline_Input_Assembly_State_Create_Info{ Vulkan_RHI::Parser_RHI_Pipeline_Input_Assembly_State_Create_Info(Create_Info->Input_Assembly_State) };

		auto vk_Pipeline_Tessellation_State_Create_Info{ Vulkan_RHI::Parser_RHI_Pipeline_Tessellation_State_Create_Info(Create_Info->Tessellation_State) };

		optional<vector<VkViewport>> Viewports{};
		optional<vector<VkRect2D>> Scissors{};
		auto vk_Pipeline_Viewport_State_Create_Info{ Vulkan_RHI::Parser_RHI_Pipeline_Viewport_State_Create_Info(Create_Info->Viewport_State, Viewports, Scissors) };

		auto vk_Pipeline_Rasterization_State_Create_Info{ Vulkan_RHI::Parser_RHI_Pipeline_Rasterization_State_Create_Info(Create_Info->Rasterization_State) };

		optional<VkSampleMask> vk_Sample_Mask{};
		auto vk_Pipeline_Multisample_State_Create_Info{ Vulkan_RHI::Parser_RHI_Pipeline_Multisample_State_Create_Info(Create_Info->Multisample_State, vk_Sample_Mask) };

		VkStencilOpState vk_Front_Stencil_Op_State{}, vk_Back_Stencil_Op_State{};
		auto vk_Pipeline_Depth_Stencil_State_Create_Info{ Vulkan_RHI::Parser_RHI_Pipeline_Depth_Stencil_State_Create_Info(Create_Info->Depth_Stencil_State, vk_Front_Stencil_Op_State, vk_Back_Stencil_Op_State) };

		optional<vector<VkPipelineColorBlendAttachmentState>> vk_Color_Blend_Attachment_States{};
		array<float, 4> Blend_Constant{};
		auto vk_Pipeline_Color_Blend_State_Create_Info{ Vulkan_RHI::Parser_RHI_Pipeline_Color_Blend_State_Create_Info(Create_Info->Color_Blend_State, vk_Color_Blend_Attachment_States, Blend_Constant) };

		optional<vector<VkDynamicState>> vk_Dynamic_States{};
		auto vk_Pipeline_Dynamic_State_Create_Info{ Vulkan_RHI::Parser_RHI_Pipeline_Dynamic_State_Create_Info(Create_Info->Dynamic_State, vk_Dynamic_States) };

		VkGraphicsPipelineCreateInfo vk_Graphics_Pipeline_Create_Info{};
		{
			vk_Graphics_Pipeline_Create_Info.sType = static_cast<VkStructureType>(Create_Info->sType);
			vk_Graphics_Pipeline_Create_Info.pNext = Create_Info->pNext;
			vk_Graphics_Pipeline_Create_Info.flags = static_cast<VkPipelineCreateFlags>(Create_Info->Flags);
			vk_Graphics_Pipeline_Create_Info.stageCount = vk_Pipeline_Shader_Stage_Create_Infos.has_value() ? vk_Pipeline_Shader_Stage_Create_Infos->size() : 0;
			vk_Graphics_Pipeline_Create_Info.pStages = vk_Pipeline_Shader_Stage_Create_Infos.has_value() ? vk_Pipeline_Shader_Stage_Create_Infos->data() : nullptr;
			vk_Graphics_Pipeline_Create_Info.pVertexInputState = vk_Pipeline_Vertex_Input_State_Create_Info.has_value() ? &vk_Pipeline_Vertex_Input_State_Create_Info.value() : nullptr;
			vk_Graphics_Pipeline_Create_Info.pInputAssemblyState = vk_Pipeline_Input_Assembly_State_Create_Info.has_value() ? &vk_Pipeline_Input_Assembly_State_Create_Info.value() : nullptr;
			vk_Graphics_Pipeline_Create_Info.pTessellationState = vk_Pipeline_Tessellation_State_Create_Info.has_value() ? &vk_Pipeline_Tessellation_State_Create_Info.value() : nullptr;
			vk_Graphics_Pipeline_Create_Info.pViewportState = vk_Pipeline_Viewport_State_Create_Info.has_value() ? &vk_Pipeline_Viewport_State_Create_Info.value() : nullptr;
			vk_Graphics_Pipeline_Create_Info.pRasterizationState = vk_Pipeline_Rasterization_State_Create_Info.has_value() ? &vk_Pipeline_Rasterization_State_Create_Info.value() : nullptr;
			vk_Graphics_Pipeline_Create_Info.pMultisampleState = vk_Pipeline_Multisample_State_Create_Info.has_value() ? &vk_Pipeline_Multisample_State_Create_Info.value() : nullptr;
			vk_Graphics_Pipeline_Create_Info.pDepthStencilState = vk_Pipeline_Depth_Stencil_State_Create_Info.has_value() ? &vk_Pipeline_Depth_Stencil_State_Create_Info.value() : nullptr;
			vk_Graphics_Pipeline_Create_Info.pColorBlendState = vk_Pipeline_Color_Blend_State_Create_Info.has_value() ? &vk_Pipeline_Color_Blend_State_Create_Info.value() : nullptr;
			vk_Graphics_Pipeline_Create_Info.pDynamicState = vk_Pipeline_Dynamic_State_Create_Info.has_value() ? &vk_Pipeline_Dynamic_State_Create_Info.value() : nullptr;
			vk_Graphics_Pipeline_Create_Info.layout = static_cast<Vulkan_Pipeline_Layout*>(Create_Info->Layout)->Get();
			vk_Graphics_Pipeline_Create_Info.renderPass = static_cast<Vulkan_Render_Pass*>(Create_Info->Render_Pass)->Get();
			vk_Graphics_Pipeline_Create_Info.subpass = Create_Info->Subpass;
			vk_Graphics_Pipeline_Create_Info.basePipelineHandle = static_cast<Vulkan_Pipeline*>(Create_Info->Base_Pipeline_Handle)->Get();
			vk_Graphics_Pipeline_Create_Info.basePipelineIndex = Create_Info->Base_Pipeline_Index;
		}

		VkPipelineCache vk_Pipeline_Cache{ Pipeline_Cache.has_value() ? static_cast<Vulkan_Pieline_Cache*>(Pipeline_Cache.value())->Get() : nullptr };

		VkPipeline vk_Pipeline{};
		THROW_IF_VK_FAILED(vkCreateGraphicsPipelines(this->m_Logical_VK_Device, vk_Pipeline_Cache, 1, &vk_Graphics_Pipeline_Create_Info, this->m_Allocator.get(), &vk_Pipeline));
		unique_ptr<RHI_Pipeline> Pipeline{ std::make_unique<Vulkan_Pipeline>() };
		static_cast<Vulkan_Pipeline*>(Pipeline.get())->Set_Deleter(this->m_VK_Pipeline_Deleter);
		static_cast<Vulkan_Pipeline*>(Pipeline.get())->Reset(vk_Pipeline);

		return Pipeline;
	}

	unique_ptr<RHI_Pipeline> Vulkan_RHI::Create_Compute_Pipeline(optional<RHI_Pipeline_Cache*> Pipeline_Cache, const RHI_Compute_Pipeline_Create_Info* pCreateInfos) {
		vector<optional<vector<VkSpecializationMapEntry>>> vk_Specialization_Map_Entryss{};
		vector<optional<VkSpecializationInfo>> vk_Specialization_Infos{};
		vector<const RHI_Pipeline_Shader_Stage_Create_Info*> Stages{ pCreateInfos->Stage };
		auto vk_Pipeline_Shader_Stage_Create_Infos{ Vulkan_RHI::Parse_RHI_Pipeline_Shader_Stage_Create_Info(&Stages, vk_Specialization_Map_Entryss, vk_Specialization_Infos) };
		if (!vk_Pipeline_Shader_Stage_Create_Infos.has_value() || vk_Pipeline_Shader_Stage_Create_Infos->empty())
			throw runtime_error("Compute Pipeline Shader Stage Create Info is nullptr or empty!");

		VkComputePipelineCreateInfo vk_Compute_Pipeline_Create_Info{};
		{
			vk_Compute_Pipeline_Create_Info.sType = static_cast<VkStructureType>(pCreateInfos->sType);
			vk_Compute_Pipeline_Create_Info.pNext = pCreateInfos->pNext;
			vk_Compute_Pipeline_Create_Info.flags = static_cast<VkPipelineCreateFlags>(pCreateInfos->Flags);
			vk_Compute_Pipeline_Create_Info.stage = vk_Pipeline_Shader_Stage_Create_Infos->front();
			vk_Compute_Pipeline_Create_Info.layout = static_cast<Vulkan_Pipeline_Layout*>(pCreateInfos->Layout)->Get();
			vk_Compute_Pipeline_Create_Info.basePipelineHandle = static_cast<Vulkan_Pipeline*>(pCreateInfos->Base_Pipeline_Handle)->Get();
			vk_Compute_Pipeline_Create_Info.basePipelineIndex = pCreateInfos->Base_Pipeline_Index;
		}

		VkPipelineCache vk_Pipeline_Cache{ Pipeline_Cache.has_value() ? static_cast<Vulkan_Pieline_Cache*>(Pipeline_Cache.value())->Get() : nullptr };
		VkPipeline vk_Pipeline{};
		THROW_IF_VK_FAILED(vkCreateComputePipelines(this->m_Logical_VK_Device, vk_Pipeline_Cache, 1, &vk_Compute_Pipeline_Create_Info, this->m_Allocator.get(), &vk_Pipeline));
		unique_ptr<RHI_Pipeline> Pipeline{ std::make_unique<Vulkan_Pipeline>() };
		static_cast<Vulkan_Pipeline*>(Pipeline.get())->Set_Deleter(this->m_VK_Pipeline_Deleter);
		static_cast<Vulkan_Pipeline*>(Pipeline.get())->Reset(vk_Pipeline);

		return Pipeline;
	}

	unique_ptr<RHI_Pipeline_Layout> Vulkan_RHI::Create_Pipeline_Layout(const RHI_Pipeline_Layout_Create_Info* Create_Info) {
		vector<VkDescriptorSetLayout> vk_Descriptor_Set_Layouts{};
		vk_Descriptor_Set_Layouts.reserve(Create_Info->Set_Layouts->size());
		for (const auto& Descriptor_Set_Layout : *Create_Info->Set_Layouts)
			vk_Descriptor_Set_Layouts.push_back(static_cast<const Vulkan_Descriptor_Set_Layout*>(Descriptor_Set_Layout)->Get());

		vector<VkPushConstantRange> vk_Push_Constant_Ranges{};
		vk_Push_Constant_Ranges.reserve(Create_Info->Push_Constant_Ranges->size());
		for (const auto& Push_Constant_Range : *Create_Info->Push_Constant_Ranges) {
			VkPushConstantRange vk_Push_Constant_Range{};
			{
				vk_Push_Constant_Range.stageFlags = static_cast<VkShaderStageFlags>(Push_Constant_Range->Stage_Flags);
				vk_Push_Constant_Range.offset = Push_Constant_Range->Offset;
				vk_Push_Constant_Range.size = Push_Constant_Range->Size;
			}

			vk_Push_Constant_Ranges.emplace_back(vk_Push_Constant_Range);
		}

		VkPipelineLayoutCreateInfo vk_Pipeline_Layout_Create_Info{}; {
			vk_Pipeline_Layout_Create_Info.sType = static_cast<VkStructureType>(Create_Info->sType);
			vk_Pipeline_Layout_Create_Info.pNext = Create_Info->pNext;
			vk_Pipeline_Layout_Create_Info.flags = static_cast<VkPipelineLayoutCreateFlags>(Create_Info->Flags);
			vk_Pipeline_Layout_Create_Info.setLayoutCount = vk_Descriptor_Set_Layouts.size();
			vk_Pipeline_Layout_Create_Info.pSetLayouts = vk_Descriptor_Set_Layouts.data();
			vk_Pipeline_Layout_Create_Info.pushConstantRangeCount = vk_Push_Constant_Ranges.size();
			vk_Pipeline_Layout_Create_Info.pPushConstantRanges = vk_Push_Constant_Ranges.data();
		}

		VkPipelineLayout vk_Pipeline_Layout{};
		THROW_IF_VK_FAILED(vkCreatePipelineLayout(this->m_Logical_VK_Device, &vk_Pipeline_Layout_Create_Info, this->m_Allocator.get(), &vk_Pipeline_Layout));
		unique_ptr<RHI_Pipeline_Layout> Pipeline_Layout{ std::make_unique<Vulkan_Pipeline_Layout>() };
		static_cast<Vulkan_Pipeline_Layout*>(Pipeline_Layout.get())->Set_Deleter(this->m_VK_Pipeline_Layout_Deleter);
		static_cast<Vulkan_Pipeline_Layout*>(Pipeline_Layout.get())->Reset(vk_Pipeline_Layout);

		return Pipeline_Layout;
	}

	unique_ptr<RHI_Render_Pass> Vulkan_RHI::Create_Render_Pass(const RHI_Render_Pass_Create_Info* Create_Info) {
		vector<VkAttachmentDescription> vk_Attachment_Descriptions{};
		if (nullptr != Create_Info->Attachments && (!Create_Info->Attachments->empty())) {
			vk_Attachment_Descriptions.reserve(Create_Info->Attachments->size());
			for (const auto& Attachment : *Create_Info->Attachments) {
				VkAttachmentDescription vk_Attachment_Description{};
				{
					vk_Attachment_Description.flags = static_cast<VkAttachmentDescriptionFlags>(Attachment->Flags);
					vk_Attachment_Description.format = static_cast<VkFormat>(Attachment->Format);
					vk_Attachment_Description.samples = static_cast<VkSampleCountFlagBits>(Attachment->Samples);
					vk_Attachment_Description.loadOp = static_cast<VkAttachmentLoadOp>(Attachment->Load_Op);
					vk_Attachment_Description.storeOp = static_cast<VkAttachmentStoreOp>(Attachment->Store_Op);
					vk_Attachment_Description.stencilLoadOp = static_cast<VkAttachmentLoadOp>(Attachment->Stencil_Load_Op);
					vk_Attachment_Description.stencilStoreOp = static_cast<VkAttachmentStoreOp>(Attachment->Stencil_Store_Op);
					vk_Attachment_Description.initialLayout = static_cast<VkImageLayout>(Attachment->Initial_Layout);
					vk_Attachment_Description.finalLayout = static_cast<VkImageLayout>(Attachment->Final_Layout);
				}

				vk_Attachment_Descriptions.emplace_back(vk_Attachment_Description);
			}
		}

		vector<VkSubpassDescription> vk_Subpass_Descriptions{};
		if (nullptr != Create_Info->Subpasses && !Create_Info->Subpasses->empty()) {
			vk_Subpass_Descriptions.reserve(Create_Info->Subpasses->size());
			for (const auto& Subpass : *Create_Info->Subpasses) {
				const vector<const RHI_Attachment_Reference*> Depth_Stencil_Attachment{ Subpass->Depth_Stencil_Attachment };
				const auto vk_Input_Attachments{ Vulkan_RHI::Parser_RHI_Attachment_Reference(Subpass->Input_Attachments) };
				const auto vk_Color_Attachments{ Vulkan_RHI::Parser_RHI_Attachment_Reference(Subpass->Color_Attachments) };
				const auto vk_Resolve_Attachments{ Vulkan_RHI::Parser_RHI_Attachment_Reference(Subpass->Resolve_Attachments) };
				const auto vk_Depth_Stencil_Attachment{ Vulkan_RHI::Parser_RHI_Attachment_Reference(&Depth_Stencil_Attachment) };

				vector<uint32_t> Preserve_Attachments{};
				if (nullptr != Subpass->Preserve_Attachments && !Subpass->Preserve_Attachments->empty()) {
					Preserve_Attachments.reserve(Subpass->Preserve_Attachments->size());

					for (const auto& Preserve_Attachment : *Subpass->Preserve_Attachments)
						Preserve_Attachments.push_back(Preserve_Attachment);
				}

				VkSubpassDescription vk_Subpass_Description{};
				{
					vk_Subpass_Description.flags = static_cast<VkSubpassDescriptionFlags>(Subpass->Flags);
					vk_Subpass_Description.pipelineBindPoint = static_cast<VkPipelineBindPoint>(Subpass->Pipeline_Bind_Point);
					vk_Subpass_Description.inputAttachmentCount = vk_Input_Attachments.has_value() ? vk_Input_Attachments->size() : 0;
					vk_Subpass_Description.pInputAttachments = vk_Input_Attachments.has_value() ? vk_Input_Attachments->data() : nullptr;
					vk_Subpass_Description.colorAttachmentCount = vk_Color_Attachments.has_value() ? vk_Color_Attachments->size() : 0;
					vk_Subpass_Description.pColorAttachments = vk_Color_Attachments.has_value() ? vk_Color_Attachments->data() : nullptr;
					vk_Subpass_Description.pResolveAttachments = vk_Resolve_Attachments.has_value() ? vk_Resolve_Attachments->data() : nullptr;
					vk_Subpass_Description.pDepthStencilAttachment = vk_Depth_Stencil_Attachment.has_value() ? &vk_Depth_Stencil_Attachment.value().front() : nullptr;
					vk_Subpass_Description.preserveAttachmentCount = Preserve_Attachments.size();
					vk_Subpass_Description.pPreserveAttachments = Preserve_Attachments.data();
				}

				vk_Subpass_Descriptions.emplace_back(vk_Subpass_Description);
			}
		}

		vector<VkSubpassDependency> vk_Subpass_Dependencies{};
		if (nullptr != Create_Info->Dependencies && !Create_Info->Dependencies->empty()) {
			vk_Subpass_Dependencies.reserve(Create_Info->Dependencies->size());

			for (const auto& Subpass_Dependency : *Create_Info->Dependencies) {
				VkSubpassDependency vk_Subpass_Dependency{};
				{
					vk_Subpass_Dependency.srcSubpass = Subpass_Dependency->Src_Subpass;
					vk_Subpass_Dependency.dstSubpass = Subpass_Dependency->Dst_Subpass;
					vk_Subpass_Dependency.srcStageMask = static_cast<VkPipelineStageFlags>(Subpass_Dependency->Src_Stage_Mask);
					vk_Subpass_Dependency.dstStageMask = static_cast<VkPipelineStageFlags>(Subpass_Dependency->Dst_Stage_Mask);
					vk_Subpass_Dependency.srcAccessMask = static_cast<VkAccessFlags>(Subpass_Dependency->Src_Access_Mask);
					vk_Subpass_Dependency.dstAccessMask = static_cast<VkAccessFlags>(Subpass_Dependency->Dst_Access_Mask);
					vk_Subpass_Dependency.dependencyFlags = static_cast<VkDependencyFlags>(Subpass_Dependency->Dependency_Flags);
				}

				vk_Subpass_Dependencies.emplace_back(vk_Subpass_Dependency);
			}
		}

		VkRenderPassCreateInfo vk_Render_Pass_Create_Info{};
		{
			vk_Render_Pass_Create_Info.sType = static_cast<VkStructureType>(Create_Info->sType);
			vk_Render_Pass_Create_Info.pNext = Create_Info->pNext;
			vk_Render_Pass_Create_Info.flags = static_cast<VkRenderPassCreateFlags>(Create_Info->Flags);
			vk_Render_Pass_Create_Info.attachmentCount = static_cast<uint32_t>(vk_Attachment_Descriptions.size());
			vk_Render_Pass_Create_Info.pAttachments = vk_Attachment_Descriptions.data();
			vk_Render_Pass_Create_Info.subpassCount = static_cast<uint32_t>(vk_Subpass_Descriptions.size());
			vk_Render_Pass_Create_Info.pSubpasses = vk_Subpass_Descriptions.data();
			vk_Render_Pass_Create_Info.dependencyCount = static_cast<uint32_t>(vk_Subpass_Dependencies.size());
			vk_Render_Pass_Create_Info.pDependencies = vk_Subpass_Dependencies.data();
		}

		VkRenderPass vk_Render_Pass{};
		THROW_IF_VK_FAILED(vkCreateRenderPass(this->m_Logical_VK_Device, &vk_Render_Pass_Create_Info, this->m_Allocator.get(), &vk_Render_Pass));
		unique_ptr<RHI_Render_Pass> Render_Pass{ std::make_unique<Vulkan_Render_Pass>() };
		static_cast<Vulkan_Render_Pass*>(Render_Pass.get())->Set_Deleter(this->m_VK_Render_Pass_Deleter);
		static_cast<Vulkan_Render_Pass*>(Render_Pass.get())->Reset(vk_Render_Pass);

		return Render_Pass;
	}



	unique_ptr<RHI_Semaphore> Vulkan_RHI::Create_Semaphore(const RHI_Semaphore_Create_Info* Create_Info) {
		VkSemaphoreCreateInfo vk_Semaphore_Create_Info{};
		{
			vk_Semaphore_Create_Info.sType = static_cast<VkStructureType>(Create_Info->sType);
			vk_Semaphore_Create_Info.pNext = Create_Info->pNext;
			vk_Semaphore_Create_Info.flags = static_cast<VkSemaphoreCreateFlags>(Create_Info->Flags);
		}

		VkSemaphore vk_Semaphore{};
		THROW_IF_VK_FAILED(vkCreateSemaphore(this->m_Logical_VK_Device, &vk_Semaphore_Create_Info, this->m_Allocator.get(), &vk_Semaphore));
		unique_ptr<RHI_Semaphore> Semaphore{ std::make_unique<Vulkan_Semaphore>() };
		static_cast<Vulkan_Semaphore*>(Semaphore.get())->Set_Deleter(this->m_VK_Semaphore_Deleter);
		static_cast<Vulkan_Semaphore*>(Semaphore.get())->Reset(vk_Semaphore);

		return Semaphore;
	}

	bool Vulkan_RHI::Wait_For_Fences_PFN(const vector<RHI_Fence*> Fences, RHI_Bool32 Wait_All, uint64_t Time_Out) {
		vector<VkFence> vk_Fences{};
		vk_Fences.reserve(Fences.size());
		for (const auto& Fence : Fences)
			vk_Fences.push_back(static_cast<Vulkan_Fence*>(Fence)->Get());

		VkBool32 vk_Wait_All{ static_cast<VkBool32>(Wait_All) };

		VkResult vk_Result{ vkWaitForFences(this->m_Logical_VK_Device, vk_Fences.size(), vk_Fences.data(), vk_Wait_All, Time_Out) };
		if (VK_SUCCESS != vk_Result) {
			if (VK_TIMEOUT == vk_Result)
				return false;
			THROW_IF_VK_FAILED(vk_Result);
		}

		return true;
	}

	bool Vulkan_RHI::Wait_For_Fence_PFN(RHI_Fence* Fences, uint64_t Time_Out) {
		VkFence vk_Fence{ static_cast<Vulkan_Fence*>(Fences)->Get() };

		VkResult vk_Result{ vkWaitForFences(this->m_Logical_VK_Device, 1, &vk_Fence, VK_TRUE, Time_Out) };

		if (VK_SUCCESS != vk_Result) {
			if (VK_TIMEOUT == vk_Result)
				return false;
			THROW_IF_VK_FAILED(vk_Result);

		}
		return true;
	}

	bool Vulkan_RHI::Reset_Fences_PFN(vector<RHI_Fence*> Fences) {
		vector<VkFence> vk_Fences{};
		vk_Fences.reserve(Fences.size());
		for (const auto& Fence : Fences)
			vk_Fences.push_back(static_cast<Vulkan_Fence*>(Fence)->Get());

		THROW_IF_VK_FAILED(vkResetFences(this->m_Logical_VK_Device, vk_Fences.size(), vk_Fences.data()));

		return true;
	}

	bool Vulkan_RHI::Reset_Fence_PFN(RHI_Fence* Fence) {
		VkFence vk_Fence{ static_cast<Vulkan_Fence*>(Fence)->Get() };

		THROW_IF_VK_FAILED(vkResetFences(this->m_Logical_VK_Device, 1, &vk_Fence));

		return true;
	}

	bool Vulkan_RHI::Reset_Command_Pool_PFN(RHI_Command_Pool* Command_Pool, RHI_Command_Pool_Reset_Flags Flags) {
		VkCommandPool vk_Command_Pool{ static_cast<Vulkan_Command_Pool*>(Command_Pool)->Get() };

		THROW_IF_VK_FAILED(vkResetCommandPool(this->m_Logical_VK_Device, vk_Command_Pool, static_cast<VkCommandPoolResetFlags>(Flags)));

		return true;
	}

	bool Vulkan_RHI::Begin_Command_Buffer_PFN(RHI_Command_Buffer* Command_Buffer, const RHI_Command_Buffer_Begin_Info* Begin_Command_Info) {
		VkCommandBufferInheritanceInfo vk_Command_Buffer_Inheritance_Info{};
		{
			vk_Command_Buffer_Inheritance_Info.sType = static_cast<VkStructureType>(Begin_Command_Info->Inheritance_Info->sType);
			vk_Command_Buffer_Inheritance_Info.pNext = Begin_Command_Info->pNext;
			vk_Command_Buffer_Inheritance_Info.renderPass = static_cast<Vulkan_Render_Pass*>(Begin_Command_Info->Inheritance_Info->Render_Pass)->Get();
			vk_Command_Buffer_Inheritance_Info.subpass = Begin_Command_Info->Inheritance_Info->Subpass;
			vk_Command_Buffer_Inheritance_Info.framebuffer = static_cast<Vulkan_Frame_Buffer*>(Begin_Command_Info->Inheritance_Info->Frame_Buffer)->Get();
			vk_Command_Buffer_Inheritance_Info.occlusionQueryEnable = static_cast<VkBool32>(Begin_Command_Info->Inheritance_Info->Occlusion_Query_Enable);
			vk_Command_Buffer_Inheritance_Info.queryFlags = static_cast<VkQueryControlFlags>(Begin_Command_Info->Inheritance_Info->Query_Flags);
			vk_Command_Buffer_Inheritance_Info.pipelineStatistics = static_cast<VkQueryPipelineStatisticFlags>(Begin_Command_Info->Inheritance_Info->Pipeline_Statistics);
		}

		VkCommandBufferBeginInfo vk_Command_Buffer_Begin_Info{};
		{
			vk_Command_Buffer_Begin_Info.sType = static_cast<VkStructureType>(Begin_Command_Info->sType);
			vk_Command_Buffer_Begin_Info.pNext = Begin_Command_Info->pNext;
			vk_Command_Buffer_Begin_Info.flags = static_cast<VkCommandBufferUsageFlags>(Begin_Command_Info->Flags);
			vk_Command_Buffer_Begin_Info.pInheritanceInfo = &vk_Command_Buffer_Inheritance_Info;
		}

		VkCommandBuffer vk_Command_Buffer{ static_cast<Vulkan_Command_Buffer*>(Command_Buffer)->Get() };

		THROW_IF_VK_FAILED(vkBeginCommandBuffer(vk_Command_Buffer, &vk_Command_Buffer_Begin_Info));

		return true;

	}

	bool Vulkan_RHI::End_Command_Buffer_PFN(RHI_Command_Buffer* Command_Buffer) {
		VkCommandBuffer vk_Command_Buffer{ static_cast<Vulkan_Command_Buffer*>(Command_Buffer)->Get() };

		THROW_IF_VK_FAILED(vkEndCommandBuffer(vk_Command_Buffer));

		return true;
	}

	void Vulkan_RHI::Cmd_Begin_Render_Pass_PFN(RHI_Command_Buffer* Command_Buffer, const RHI_Render_Pass_Begin_Info* Render_Pass_Begin, RHI_SUBPASS_CONTENTS Content) {
		vector<VkClearValue> vk_Clear_Values{};
		if (nullptr == Render_Pass_Begin->Clear_Values || Render_Pass_Begin->Clear_Values->empty()) {
			vk_Clear_Values.reserve(Render_Pass_Begin->Clear_Values->size());
			for (const auto& Clear_Value : *Render_Pass_Begin->Clear_Values) {
				const auto vk_Clear_Value{ Vulkan_RHI::Parser_RHI_Clear_Value(Clear_Value) };
				if (!vk_Clear_Value.has_value())
					throw runtime_error("Clear Value is nullptr!");

				vk_Clear_Values.emplace_back(vk_Clear_Value.value());
			}
		}

		VkRenderPassBeginInfo vk_Render_Pass_Begin_Info{};
		{
			vk_Render_Pass_Begin_Info.sType = static_cast<VkStructureType>(Render_Pass_Begin->sType);
			vk_Render_Pass_Begin_Info.pNext = Render_Pass_Begin->pNext;
			vk_Render_Pass_Begin_Info.renderPass = static_cast<Vulkan_Render_Pass*>(Render_Pass_Begin->Render_Pass)->Get();
			vk_Render_Pass_Begin_Info.framebuffer = static_cast<Vulkan_Frame_Buffer*>(Render_Pass_Begin->Frame_Buffer)->Get();
			vk_Render_Pass_Begin_Info.renderArea.offset.x = Render_Pass_Begin->Render_Area.Offset.X;
			vk_Render_Pass_Begin_Info.renderArea.offset.y = Render_Pass_Begin->Render_Area.Offset.Y;
			vk_Render_Pass_Begin_Info.renderArea.extent.width = Render_Pass_Begin->Render_Area.Extent.Width;
			vk_Render_Pass_Begin_Info.renderArea.extent.height = Render_Pass_Begin->Render_Area.Extent.Height;
			vk_Render_Pass_Begin_Info.clearValueCount = vk_Clear_Values.size();
			vk_Render_Pass_Begin_Info.pClearValues = vk_Clear_Values.data();
		}

		VkCommandBuffer vk_Command_Buffer{ static_cast<Vulkan_Command_Buffer*>(Command_Buffer)->Get() };
		vkCmdBeginRenderPass(vk_Command_Buffer, &vk_Render_Pass_Begin_Info, static_cast<VkSubpassContents>(Content));
	}

	void Vulkan_RHI::Cmd_Next_Subpass_PFN(RHI_Command_Buffer* Command_Buffer, RHI_SUBPASS_CONTENTS Content) {
		VkCommandBuffer vk_Command_Buffer{ static_cast<Vulkan_Command_Buffer*>(Command_Buffer)->Get() };

		vkCmdNextSubpass(vk_Command_Buffer, static_cast<VkSubpassContents>(Content));
	}

	void Vulkan_RHI::Cmd_End_Render_Pass_PFN(RHI_Command_Buffer* Command_Buffer) {
		VkCommandBuffer vk_Command_Buffer{ static_cast<Vulkan_Command_Buffer*>(Command_Buffer)->Get() };

		vkCmdEndRenderPass(vk_Command_Buffer);
	}

	void Vulkan_RHI::Cmd_Bind_Pipeline_PFN(RHI_Command_Buffer* Command_Buffer, RHI_PEPELINE_BIND_POINT Pipeline_Bind_Point, RHI_Pipeline* Pipeline) {
		VkCommandBuffer vk_Command_Buffer{ static_cast<Vulkan_Command_Buffer*>(Command_Buffer)->Get() };
		VkPipeline vk_Pipeline{ static_cast<Vulkan_Pipeline*>(Pipeline)->Get() };

		vkCmdBindPipeline(vk_Command_Buffer, static_cast<VkPipelineBindPoint>(Pipeline_Bind_Point), vk_Pipeline);
	}

	void Vulkan_RHI::Cmd_Set_Viewports_PFN(RHI_Command_Buffer* Command_Buffer, uint32_t First_Viewport_Index, const vector<const RHI_Viewport*>* Viewports) {
		if (nullptr == Viewports || Viewports->empty())
			throw runtime_error("Viewports is nullptr or empty!");

		vector<VkViewport> vk_Viewports{};
		vk_Viewports.reserve(Viewports->size());
		for (const auto& Viewport : *Viewports) {
			if (nullptr == Viewport)
				throw runtime_error("Viewport is nullptr!");

			VkViewport vk_Viewport{};
			{
				vk_Viewport.x = Viewport->X;
				vk_Viewport.y = Viewport->Y;
				vk_Viewport.width = Viewport->Width;
				vk_Viewport.height = Viewport->Height;
				vk_Viewport.minDepth = Viewport->Min_Depth;
				vk_Viewport.maxDepth = Viewport->Max_Depth;
			}

			vk_Viewports.emplace_back(vk_Viewport);
		}

		VkCommandBuffer vk_Command_Buffer{ static_cast<Vulkan_Command_Buffer*>(Command_Buffer)->Get() };

		vkCmdSetViewport(vk_Command_Buffer, First_Viewport_Index, vk_Viewports.size(), vk_Viewports.data());
	}

	void Vulkan_RHI::Cmd_Set_Viewport_PFN(RHI_Command_Buffer* Command_Buffer, const RHI_Viewport* Viewport) {
		if (nullptr == Viewport)
			throw runtime_error("Viewport is nullptr!");

		VkViewport vk_Viewport{};
		{
			vk_Viewport.x = Viewport->X;
			vk_Viewport.y = Viewport->Y;
			vk_Viewport.width = Viewport->Width;
			vk_Viewport.height = Viewport->Height;
			vk_Viewport.minDepth = Viewport->Min_Depth;
			vk_Viewport.maxDepth = Viewport->Max_Depth;
		}

		VkCommandBuffer vk_Command_Buffer{ static_cast<Vulkan_Command_Buffer*>(Command_Buffer)->Get() };

		vkCmdSetViewport(vk_Command_Buffer, 0, 1, &vk_Viewport);
	}

	void Vulkan_RHI::Cmd_Set_Scissors_PFN(RHI_Command_Buffer* Command_Buffer, uint32_t First_Scissor_Index, const vector<const RHI_Rect_2D*>* Scissors) {
		if (nullptr == Scissors || Scissors->empty())
			throw runtime_error("Scissors is nullptr or empty!");

		vector<VkRect2D> vk_Scissors{};
		vk_Scissors.reserve(Scissors->size());
		for (const auto& Scissor : *Scissors) {
			if (nullptr == Scissor)
				throw runtime_error("Scissor is nullptr!");

			VkRect2D vk_Scissor{};
			{
				vk_Scissor.offset.x = Scissor->Offset.X;
				vk_Scissor.offset.y = Scissor->Offset.Y;
				vk_Scissor.extent.width = Scissor->Extent.Width;
				vk_Scissor.extent.height = Scissor->Extent.Height;
			}

			vk_Scissors.emplace_back(vk_Scissor);
		}

		VkCommandBuffer vk_Command_Buffer{ static_cast<Vulkan_Command_Buffer*>(Command_Buffer)->Get() };

		vkCmdSetScissor(vk_Command_Buffer, First_Scissor_Index, vk_Scissors.size(), vk_Scissors.data());
	}

	void Vulkan_RHI::Cmd_Set_Scissors_PFN(RHI_Command_Buffer* Command_Buffer, const RHI_Rect_2D* Scissors) {
		if (nullptr == Scissors)
			throw runtime_error("Scissors is nullptr!");

		VkRect2D vk_Scissor{};
		{
			vk_Scissor.offset.x = Scissors->Offset.X;
			vk_Scissor.offset.y = Scissors->Offset.Y;
			vk_Scissor.extent.width = Scissors->Extent.Width;
			vk_Scissor.extent.height = Scissors->Extent.Height;
		}

		VkCommandBuffer vk_Command_Buffer{ static_cast<Vulkan_Command_Buffer*>(Command_Buffer)->Get() };

		vkCmdSetScissor(vk_Command_Buffer, 0, 1, &vk_Scissor);
	}

	void Vulkan_RHI::Cmd_Bind_Vertex_Buffers_PFN(RHI_Command_Buffer* Command_Buffer, uint32_t First_Binding_Index, const vector<RHI_Buffer*>* Buffers, const vector<RHI_Device_Size>* Offsets) {
		if (nullptr == Buffers || Buffers->empty())
			throw runtime_error("Buffers is nullptr or empty!");

		if (nullptr == Offsets || Offsets->empty())
			throw runtime_error("Offsets is nullptr or empty!");

		if (Buffers->size() != Offsets->size())
			throw runtime_error("Buffers size is not equal to Offsets size!");

		vector<VkBuffer> vk_Buffers{};
		vk_Buffers.reserve(Buffers->size());
		for (const auto& Buffer : *Buffers)
			vk_Buffers.push_back(static_cast<Vulkan_Buffer*>(Buffer)->Get());

		vector<VkDeviceSize> vk_Offsets{};
		vk_Offsets.reserve(Offsets->size());
		for (const auto& Offset : *Offsets)
			vk_Offsets.push_back(static_cast<VkDeviceSize>(Offset));

		VkCommandBuffer vk_Command_Buffer{ static_cast<Vulkan_Command_Buffer*>(Command_Buffer)->Get() };

		vkCmdBindVertexBuffers(vk_Command_Buffer, First_Binding_Index, vk_Buffers.size(), vk_Buffers.data(), vk_Offsets.data());
	}

	void Vulkan_RHI::Cmd_Bind_Vertex_Buffer_PFN(RHI_Command_Buffer* Command_Buffer, RHI_Buffer* Buffers, RHI_Device_Size* Offsets) {
		VkBuffer vk_Buffers{ static_cast<Vulkan_Buffer*>(Buffers)->Get() };
		VkDeviceSize vk_Offsets{ static_cast<VkDeviceSize>(*Offsets) };
		VkCommandBuffer vk_Command_Buffer{ static_cast<Vulkan_Command_Buffer*>(Command_Buffer)->Get() };

		vkCmdBindVertexBuffers(vk_Command_Buffer, 0, 1, &vk_Buffers, &vk_Offsets);
	}

	void Vulkan_RHI::Cmd_Bind_Index_Buffer_PFN(RHI_Command_Buffer* Command_Buffer, RHI_Buffer* Buffer, RHI_Device_Size Offset, RHI_INDEX_TYPE Index_Type) {
		VkBuffer vk_Buffer{ static_cast<Vulkan_Buffer*>(Buffer)->Get() };
		VkDeviceSize vk_Offset{ static_cast<VkDeviceSize>(Offset) };
		VkCommandBuffer vk_Command_Buffer{ static_cast<Vulkan_Command_Buffer*>(Command_Buffer)->Get() };

		vkCmdBindIndexBuffer(vk_Command_Buffer, vk_Buffer, vk_Offset, static_cast<VkIndexType>(Index_Type));
	}

	void Vulkan_RHI::Cmd_Bind_Descriptor_Sets_PFN(RHI_Command_Buffer* Command_Buffer, RHI_PEPELINE_BIND_POINT Pipeline_Bind_Point, RHI_Pipeline_Layout* Layout, uint32_t First_Set_Index, const vector<RHI_Descriptor_Set*>* Descriptor_Sets, const vector<uint32_t>* Dynamic_Offsets) {
		if (nullptr == Descriptor_Sets || Descriptor_Sets->empty())
			throw runtime_error("Descriptor Sets is nullptr or empty!");

		vector<VkDescriptorSet> vk_Descriptor_Sets{};
		vk_Descriptor_Sets.reserve(Descriptor_Sets->size());
		for (const auto& Descriptor_Set : *Descriptor_Sets)
			vk_Descriptor_Sets.push_back(static_cast<Vulkan_Descriptor_Set*>(Descriptor_Set)->Get());

		VkPipelineLayout vk_Pipeline_Layout{ static_cast<Vulkan_Pipeline_Layout*>(Layout)->Get() };
		VkCommandBuffer vk_Command_Buffer{ static_cast<Vulkan_Command_Buffer*>(Command_Buffer)->Get() };

		if (nullptr == Dynamic_Offsets)
			vkCmdBindDescriptorSets(vk_Command_Buffer, static_cast<VkPipelineBindPoint>(Pipeline_Bind_Point), vk_Pipeline_Layout, First_Set_Index, vk_Descriptor_Sets.size(), vk_Descriptor_Sets.data(), 0, nullptr);
		else
			vkCmdBindDescriptorSets(vk_Command_Buffer, static_cast<VkPipelineBindPoint>(Pipeline_Bind_Point), vk_Pipeline_Layout, First_Set_Index, vk_Descriptor_Sets.size(), vk_Descriptor_Sets.data(), Dynamic_Offsets->size(), Dynamic_Offsets->data());
	}

	void Vulkan_RHI::Cmd_Bind_Descriptor_Set_PFN(RHI_Command_Buffer* Command_Buffer, RHI_PEPELINE_BIND_POINT Pipeline_Bind_Point, RHI_Pipeline_Layout* Layout, RHI_Descriptor_Set* Descriptor_Sets, const vector<uint32_t>* Dynamic_Offsets) {
		VkDescriptorSet vk_Descriptor_Sets{ static_cast<Vulkan_Descriptor_Set*>(Descriptor_Sets)->Get() };
		VkPipelineLayout vk_Pipeline_Layout{ static_cast<Vulkan_Pipeline_Layout*>(Layout)->Get() };
		VkCommandBuffer vk_Command_Buffer{ static_cast<Vulkan_Command_Buffer*>(Command_Buffer)->Get() };

		if (nullptr == Dynamic_Offsets)
			vkCmdBindDescriptorSets(vk_Command_Buffer, static_cast<VkPipelineBindPoint>(Pipeline_Bind_Point), vk_Pipeline_Layout, 0, 1, &vk_Descriptor_Sets, 0, nullptr);
		else
			vkCmdBindDescriptorSets(vk_Command_Buffer, static_cast<VkPipelineBindPoint>(Pipeline_Bind_Point), vk_Pipeline_Layout, 0, 1, &vk_Descriptor_Sets, Dynamic_Offsets->size(), Dynamic_Offsets->data());
	}

	void Vulkan_RHI::Cmd_Draw_Indexed_PFN(RHI_Command_Buffer* Command_Buffer, uint32_t Index_Count, uint32_t Instance_Count, uint32_t First_Index, int32_t VertexOffset, uint32_t First_Instance) {
		VkCommandBuffer vk_Command_Buffer{ static_cast<Vulkan_Command_Buffer*>(Command_Buffer)->Get() };

		vkCmdDrawIndexed(vk_Command_Buffer, Index_Count, Instance_Count, First_Index, VertexOffset, First_Instance);
	}

	void Vulkan_RHI::Cmd_Clear_Attachments_PFN(RHI_Command_Buffer* Command_Buffer, const vector<const RHI_Clear_Attachment*>* Attachments, const vector<const RHI_Clear_Rect*>* Rects) {
		if (nullptr == Attachments || Attachments->empty())
			throw runtime_error("Attachments is nullptr or empty!");

		if (nullptr == Rects || Rects->empty())
			throw runtime_error("Rects is nullptr or empty!");

		if (Attachments->size() != Rects->size())
			throw runtime_error("Attachments size is not equal to Rects size!");

		vector<VkClearAttachment> vk_Clear_Attachments{};
		vk_Clear_Attachments.reserve(Attachments->size());
		for (const auto& Attachment : *Attachments) {
			if (nullptr == Attachment)
				throw runtime_error("Attachment is nullptr!");

			VkClearAttachment vk_Clear_Attachment{};
			{
				vk_Clear_Attachment.aspectMask = static_cast<VkImageAspectFlags>(Attachment->Aspect_Mask);
				vk_Clear_Attachment.colorAttachment = Attachment->Color_Attachment;
				vk_Clear_Attachment.clearValue = Vulkan_RHI::Parser_RHI_Clear_Value(&Attachment->Clear_Value).value();
			}

			vk_Clear_Attachments.emplace_back(vk_Clear_Attachment);
		}
		vector<VkClearRect> vk_Clear_Rects{};
		vk_Clear_Rects.reserve(Rects->size());
		for (const auto& Rect : *Rects) {
			if (nullptr == Rect)
				throw runtime_error("Rect is nullptr!");

			VkClearRect vk_Clear_Rect{};
			{
				vk_Clear_Rect.rect.offset.x = Rect->Rect.Offset.X;
				vk_Clear_Rect.rect.offset.y = Rect->Rect.Offset.Y;
				vk_Clear_Rect.rect.extent.width = Rect->Rect.Extent.Width;
				vk_Clear_Rect.rect.extent.height = Rect->Rect.Extent.Height;
				vk_Clear_Rect.baseArrayLayer = Rect->Base_Array_Layer;
				vk_Clear_Rect.layerCount = Rect->Layer_Count;
			}

			vk_Clear_Rects.emplace_back(vk_Clear_Rect);
		}

		VkCommandBuffer vk_Command_Buffer{ static_cast<Vulkan_Command_Buffer*>(Command_Buffer)->Get() };

		vkCmdClearAttachments(vk_Command_Buffer, vk_Clear_Attachments.size(), vk_Clear_Attachments.data(), vk_Clear_Rects.size(), vk_Clear_Rects.data());
	}

	void Vulkan_RHI::Cmd_Clear_Attachment_PFN(RHI_Command_Buffer* Command_Buffer, const RHI_Clear_Attachment* Attachment, const RHI_Clear_Rect* Rect) {
		if (nullptr == Attachment)
			throw runtime_error("Attachment is nullptr!");

		if (nullptr == Rect)
			throw runtime_error("Rect is nullptr!");

		VkClearAttachment vk_Clear_Attachment{};
		{
			vk_Clear_Attachment.aspectMask = static_cast<VkImageAspectFlags>(Attachment->Aspect_Mask);
			vk_Clear_Attachment.colorAttachment = Attachment->Color_Attachment;
			vk_Clear_Attachment.clearValue = Vulkan_RHI::Parser_RHI_Clear_Value(&Attachment->Clear_Value).value();
		}

		VkClearRect vk_Clear_Rect{};
		{
			vk_Clear_Rect.rect.offset.x = Rect->Rect.Offset.X;
			vk_Clear_Rect.rect.offset.y = Rect->Rect.Offset.Y;
			vk_Clear_Rect.rect.extent.width = Rect->Rect.Extent.Width;
			vk_Clear_Rect.rect.extent.height = Rect->Rect.Extent.Height;
			vk_Clear_Rect.baseArrayLayer = Rect->Base_Array_Layer;
			vk_Clear_Rect.layerCount = Rect->Layer_Count;
		}

		VkCommandBuffer vk_Command_Buffer{ static_cast<Vulkan_Command_Buffer*>(Command_Buffer)->Get() };

		vkCmdClearAttachments(vk_Command_Buffer, 1, &vk_Clear_Attachment, 1, &vk_Clear_Rect);
	}

	void Vulkan_RHI::Cmd_Copy_Image_To_Buffer(RHI_Command_Buffer* Command_Buffer, RHI_Image* Src_Image, RHI_IMAGE_LAYOUT Src_Image_Layout, RHI_Buffer* Dst_Buffer, const vector<const RHI_Buffer_Image_Copy*>* Regions) {
		if (nullptr == Regions || Regions->empty())
			throw runtime_error("Regions is nullptr or empty!");

		vector<VkBufferImageCopy> vk_Buffer_Image_Copies{};
		vk_Buffer_Image_Copies.reserve(Regions->size());
		for (const auto& Region : *Regions) {
			if (nullptr == Region)
				throw runtime_error("Region is nullptr!");

			VkBufferImageCopy vk_Buffer_Image_Copy{};
			{
				vk_Buffer_Image_Copy.bufferOffset = Region->Buffer_Offset;
				vk_Buffer_Image_Copy.bufferRowLength = Region->Buffer_Row_Length;
				vk_Buffer_Image_Copy.bufferImageHeight = Region->Buffer_Image_Height;
				vk_Buffer_Image_Copy.imageSubresource.aspectMask = static_cast<VkImageAspectFlags>(Region->Image_Subresource.Aspect_Mask);
				vk_Buffer_Image_Copy.imageSubresource.mipLevel = Region->Image_Subresource.Mip_Level;
				vk_Buffer_Image_Copy.imageSubresource.baseArrayLayer = Region->Image_Subresource.Base_Array_Layer;
				vk_Buffer_Image_Copy.imageSubresource.layerCount = Region->Image_Subresource.Layer_Count;
				vk_Buffer_Image_Copy.imageOffset.x = Region->Image_Offset.X;
				vk_Buffer_Image_Copy.imageOffset.y = Region->Image_Offset.Y;
				vk_Buffer_Image_Copy.imageOffset.z = Region->Image_Offset.Z;
				vk_Buffer_Image_Copy.imageExtent.width = Region->Image_Extent.Width;
				vk_Buffer_Image_Copy.imageExtent.height = Region->Image_Extent.Height;
				vk_Buffer_Image_Copy.imageExtent.depth = Region->Image_Extent.Depth;
			}

			vk_Buffer_Image_Copies.emplace_back(vk_Buffer_Image_Copy);
		}

		VkImage vk_Src_Image{ static_cast<Vulkan_Image*>(Src_Image)->Get() };
		VkBuffer vk_Dst_Buffer{ static_cast<Vulkan_Buffer*>(Dst_Buffer)->Get() };
		VkCommandBuffer vk_Command_Buffer{ static_cast<Vulkan_Command_Buffer*>(Command_Buffer)->Get() };

		vkCmdCopyImageToBuffer(vk_Command_Buffer, vk_Src_Image, static_cast<VkImageLayout>(Src_Image_Layout), vk_Dst_Buffer, vk_Buffer_Image_Copies.size(), vk_Buffer_Image_Copies.data());
	}

	void Vulkan_RHI::Cmd_Copy_Image_X(RHI_Command_Buffer* Command_Buffer, RHI_Image* Src_Image, RHI_IMAGE_ASPECT_FLAG_BITS Src_Flag, RHI_Image* Dst_Image, RHI_IMAGE_ASPECT_FLAG_BITS Dst_Flag, RHI_Extent_2D Extent) {
		VkImageCopy vk_Image_Copy{};
		{
			vk_Image_Copy.srcSubresource.aspectMask = static_cast<VkImageAspectFlags>(Src_Flag);
			vk_Image_Copy.srcSubresource.mipLevel = 0;
			vk_Image_Copy.srcSubresource.baseArrayLayer = 0;
			vk_Image_Copy.srcSubresource.layerCount = 1;
			vk_Image_Copy.srcOffset = { 0, 0, 0 };
			vk_Image_Copy.dstSubresource.aspectMask = static_cast<VkImageAspectFlags>(Dst_Flag);
			vk_Image_Copy.dstSubresource.mipLevel = 0;
			vk_Image_Copy.dstSubresource.baseArrayLayer = 0;
			vk_Image_Copy.dstSubresource.layerCount = 1;
			vk_Image_Copy.dstOffset = { 0, 0, 0 };
			vk_Image_Copy.extent.width = Extent.Width;
			vk_Image_Copy.extent.height = Extent.Height;
			vk_Image_Copy.extent.depth = 1;
		}

		VkImage vk_Src_Image{ static_cast<Vulkan_Image*>(Src_Image)->Get() };
		VkImage vk_Dst_Image{ static_cast<Vulkan_Image*>(Dst_Image)->Get() };
		VkCommandBuffer vk_Command_Buffer{ static_cast<Vulkan_Command_Buffer*>(Command_Buffer)->Get() };

		vkCmdCopyImage(vk_Command_Buffer, vk_Src_Image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, vk_Dst_Image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &vk_Image_Copy);
	}

	void Vulkan_RHI::Cmd_Copy_Buffer(RHI_Command_Buffer* Command_Buffer, RHI_Buffer* Src_Buffer, RHI_Buffer* Dst_Buffer, const vector<const RHI_Buffer_Copy*>* Regions) {
		if (nullptr == Regions || Regions->empty())
			throw runtime_error("Regions is nullptr or empty!");

		vector<VkBufferCopy> vk_Buffer_Copies{};
		vk_Buffer_Copies.reserve(Regions->size());
		for (const auto& Region : *Regions) {
			if (nullptr == Region)
				throw runtime_error("Region is nullptr!");

			VkBufferCopy vk_Buffer_Copy{};
			{
				vk_Buffer_Copy.srcOffset = Region->Src_Offset;
				vk_Buffer_Copy.dstOffset = Region->Dst_Offset;
				vk_Buffer_Copy.size = Region->Size;
			}

			vk_Buffer_Copies.emplace_back(vk_Buffer_Copy);
		}

		VkBuffer vk_Src_Buffer{ static_cast<Vulkan_Buffer*>(Src_Buffer)->Get() };
		VkBuffer vk_Dst_Buffer{ static_cast<Vulkan_Buffer*>(Dst_Buffer)->Get() };
		VkCommandBuffer vk_Command_Buffer{ static_cast<Vulkan_Command_Buffer*>(Command_Buffer)->Get() };

		vkCmdCopyBuffer(vk_Command_Buffer, vk_Src_Buffer, vk_Dst_Buffer, vk_Buffer_Copies.size(), vk_Buffer_Copies.data());
	}

	void Vulkan_RHI::Cmd_Draw(RHI_Command_Buffer* Command_Buffer, uint32_t Vertex_Count, uint32_t Instance_Count, uint32_t First_Vertex_Index, uint32_t First_Instance_Index) {
		VkCommandBuffer vk_Command_Buffer{ static_cast<Vulkan_Command_Buffer*>(Command_Buffer)->Get() };

		vkCmdDraw(vk_Command_Buffer, Vertex_Count, Instance_Count, First_Vertex_Index, First_Instance_Index);
	}

	void Vulkan_RHI::Cmd_Dispatch(RHI_Command_Buffer* Command_Buffer, uint32_t Group_Count_X, uint32_t Group_Count_Y, uint32_t Group_Count_Z) {
		VkCommandBuffer vk_Command_Buffer{ static_cast<Vulkan_Command_Buffer*>(Command_Buffer)->Get() };

		vkCmdDispatch(vk_Command_Buffer, Group_Count_X, Group_Count_Y, Group_Count_Z);
	}

	void Vulkan_RHI::Cmd_Dispatch_Indirect(RHI_Command_Buffer* Command_Buffer, RHI_Buffer* Buffer, RHI_Device_Size Offset) {
		VkCommandBuffer vk_Command_Buffer{ static_cast<Vulkan_Command_Buffer*>(Command_Buffer)->Get() };
		VkBuffer vk_Buffer{ static_cast<Vulkan_Buffer*>(Buffer)->Get() };

		vkCmdDispatchIndirect(vk_Command_Buffer, vk_Buffer, static_cast<VkDeviceSize>(Offset));
	}

	void Vulkan_RHI::Cmd_Pipeline_Barrier(RHI_Command_Buffer* Command_Buffer, RHI_Pipeline_Stage_Flags Src_Stage_Mask, RHI_Pipeline_Stage_Flags Dst_Stage_Mask, RHI_Dependency_Flags Dependency_Flags, const vector<const RHI_Memory_Barrier*>* Memory_Barriers, const vector<const RHI_Buffer_Memory_Barrier*>* Buffer_Memory_Barriers, const vector<const RHI_Image_Memory_Barrier*>* Image_Memory_Barriers) {
		vector<VkMemoryBarrier> vk_Memory_Barriers{};
		if (nullptr != Memory_Barriers && !Memory_Barriers->empty()) {
			vk_Memory_Barriers.reserve(Memory_Barriers->size());
			for (const auto& Memory_Barrier : *Memory_Barriers) {
				if (nullptr == Memory_Barrier)
					throw runtime_error("Memory Barrier is nullptr!");

				VkMemoryBarrier vk_Memory_Barrier{};
				{
					vk_Memory_Barrier.sType = static_cast<VkStructureType>(Memory_Barrier->sType);
					vk_Memory_Barrier.pNext = Memory_Barrier->pNext;
					vk_Memory_Barrier.srcAccessMask = static_cast<VkAccessFlags>(Memory_Barrier->Src_Access_Mask);
					vk_Memory_Barrier.dstAccessMask = static_cast<VkAccessFlags>(Memory_Barrier->Dst_Access_Mask);
				}

				vk_Memory_Barriers.emplace_back(vk_Memory_Barrier);
			}
		}

		vector<VkBufferMemoryBarrier> vk_Buffer_Memory_Barriers{};
		if (nullptr != Buffer_Memory_Barriers && !Buffer_Memory_Barriers->empty()) {
			vk_Buffer_Memory_Barriers.reserve(Buffer_Memory_Barriers->size());
			for (const auto& Buffer_Memory_Barrier : *Buffer_Memory_Barriers) {
				if (nullptr == Buffer_Memory_Barrier)
					throw runtime_error("Buffer Memory Barrier is nullptr!");

				VkBufferMemoryBarrier vk_Buffer_Memory_Barrier{};
				{
					vk_Buffer_Memory_Barrier.sType = static_cast<VkStructureType>(Buffer_Memory_Barrier->sType);
					vk_Buffer_Memory_Barrier.pNext = Buffer_Memory_Barrier->pNext;
					vk_Buffer_Memory_Barrier.srcAccessMask = static_cast<VkAccessFlags>(Buffer_Memory_Barrier->Src_Access_Mask);
					vk_Buffer_Memory_Barrier.dstAccessMask = static_cast<VkAccessFlags>(Buffer_Memory_Barrier->Dst_Access_Mask);
					vk_Buffer_Memory_Barrier.srcQueueFamilyIndex = Buffer_Memory_Barrier->Src_Queue_Family_Index;
					vk_Buffer_Memory_Barrier.dstQueueFamilyIndex = Buffer_Memory_Barrier->Dst_Queue_Family_Index;
					vk_Buffer_Memory_Barrier.buffer = static_cast<Vulkan_Buffer*>(Buffer_Memory_Barrier->Buffer)->Get();
					vk_Buffer_Memory_Barrier.offset = Buffer_Memory_Barrier->Offset;
					vk_Buffer_Memory_Barrier.size = Buffer_Memory_Barrier->Size;
				}

				vk_Buffer_Memory_Barriers.emplace_back(vk_Buffer_Memory_Barrier);
			}
		}

		vector<VkImageMemoryBarrier> vk_Image_Memory_Barriers{};
		if (nullptr != Image_Memory_Barriers && !Image_Memory_Barriers->empty()) {
			vk_Image_Memory_Barriers.reserve(Image_Memory_Barriers->size());
			for (const auto& Image_Memory_Barrier : *Image_Memory_Barriers) {
				if (nullptr == Image_Memory_Barrier)
					throw runtime_error("Image Memory Barrier is nullptr!");

				VkImageMemoryBarrier vk_Image_Memory_Barrier{};
				{
					vk_Image_Memory_Barrier.sType = static_cast<VkStructureType>(Image_Memory_Barrier->sType);
					vk_Image_Memory_Barrier.pNext = Image_Memory_Barrier->pNext;
					vk_Image_Memory_Barrier.srcAccessMask = static_cast<VkAccessFlags>(Image_Memory_Barrier->Src_Access_Mask);
					vk_Image_Memory_Barrier.dstAccessMask = static_cast<VkAccessFlags>(Image_Memory_Barrier->Dst_Access_Mask);
					vk_Image_Memory_Barrier.oldLayout = static_cast<VkImageLayout>(Image_Memory_Barrier->Old_Layout);
					vk_Image_Memory_Barrier.newLayout = static_cast<VkImageLayout>(Image_Memory_Barrier->New_Layout);
					vk_Image_Memory_Barrier.srcQueueFamilyIndex = Image_Memory_Barrier->Src_Queue_Family_Index;
					vk_Image_Memory_Barrier.dstQueueFamilyIndex = Image_Memory_Barrier->Dst_Queue_Family_Index;
					vk_Image_Memory_Barrier.image = static_cast<Vulkan_Image*>(Image_Memory_Barrier->Image)->Get();
					vk_Image_Memory_Barrier.subresourceRange.aspectMask = static_cast<VkImageAspectFlags>(Image_Memory_Barrier->SubResource_Ranges.Aspect_Mask);
					vk_Image_Memory_Barrier.subresourceRange.baseMipLevel = Image_Memory_Barrier->SubResource_Ranges.Base_Mip_Level;
					vk_Image_Memory_Barrier.subresourceRange.levelCount = Image_Memory_Barrier->SubResource_Ranges.Level_Count;
					vk_Image_Memory_Barrier.subresourceRange.baseArrayLayer = Image_Memory_Barrier->SubResource_Ranges.Base_Array_Layer;
					vk_Image_Memory_Barrier.subresourceRange.layerCount = Image_Memory_Barrier->SubResource_Ranges.Layer_Count;
				}

				vk_Image_Memory_Barriers.emplace_back(vk_Image_Memory_Barrier);
			}
		}

		VkCommandBuffer vk_Command_Buffer{ static_cast<Vulkan_Command_Buffer*>(Command_Buffer)->Get() };

		vkCmdPipelineBarrier(vk_Command_Buffer, static_cast<VkPipelineStageFlags>(Src_Stage_Mask), static_cast<VkPipelineStageFlags>(Dst_Stage_Mask), static_cast<VkDependencyFlags>(Dependency_Flags), vk_Memory_Barriers.size(), vk_Memory_Barriers.data(), vk_Buffer_Memory_Barriers.size(), vk_Buffer_Memory_Barriers.data(), vk_Image_Memory_Barriers.size(), vk_Image_Memory_Barriers.data());
	}

	bool Vulkan_RHI::Queue_Submit(RHI_Queue* Queue, const vector<const RHI_Submit_Info*>* Submits, RHI_Fence* Fence) {
		if (nullptr == Submits || Submits->empty())
			throw runtime_error("Submits is nullptr or empty!");

		vector<VkSubmitInfo> vk_Submit_Infos{};
		vector<optional<vector<VkSemaphore>>> vk_Wait_Semaphores_List{};
		vector<optional<vector<VkPipelineStageFlags>>> vk_Wait_Dst_Stge_Masks_List{};
		vector<optional<vector<VkCommandBuffer>>> vk_Command_Buffers_List{};
		vector<optional<vector<VkSemaphore>>> vk_Signal_Semaphores_List{};

		vk_Submit_Infos.reserve(Submits->size());
		vk_Wait_Semaphores_List.reserve(Submits->size());
		vk_Wait_Dst_Stge_Masks_List.reserve(Submits->size());
		vk_Command_Buffers_List.reserve(Submits->size());
		vk_Signal_Semaphores_List.reserve(Submits->size());

		for (const auto& Submit : *Submits) {
			if (nullptr == Submit)
				throw runtime_error("Submit is nullptr!");

			const size_t vk_Wait_Semaphore_Count = (nullptr != Submit->Wait_Semaphores) ? Submit->Wait_Semaphores->size() : 0;
			const size_t vk_Wait_Dst_Stage_Mask_Count = (nullptr != Submit->Wait_Dst_Stage_Masks) ? Submit->Wait_Dst_Stage_Masks->size() : 0;
			const size_t vk_Command_Buffer_Count = (nullptr != Submit->Command_Buffers) ? Submit->Command_Buffers->size() : 0;
			const size_t vk_Signal_Semaphore_Count = (nullptr != Submit->Signal_Semaphores) ? Submit->Signal_Semaphores->size() : 0;

			//TODO : Add Size Check

			if (nullptr != Submit->Wait_Semaphores && !Submit->Wait_Semaphores->empty()) {
				vector<VkSemaphore> vk_Wait_Semaphores{};
				vk_Wait_Semaphores.reserve(Submit->Wait_Semaphores->size());

				for (const auto& Wait_Semaphore : *Submit->Wait_Semaphores)
					vk_Wait_Semaphores.push_back(static_cast<Vulkan_Semaphore*>(Wait_Semaphore)->Get());

				vk_Wait_Semaphores_List.emplace_back(std::make_optional(vk_Wait_Semaphores));
			}
			else
				vk_Wait_Semaphores_List.emplace_back(std::nullopt);

			if (nullptr != Submit->Wait_Dst_Stage_Masks && !Submit->Wait_Dst_Stage_Masks->empty()) {
				vector<VkPipelineStageFlags> vk_Wait_Dst_Stage_Masks{};
				vk_Wait_Dst_Stage_Masks.reserve(Submit->Wait_Dst_Stage_Masks->size());

				for (const auto& Wait_Dst_Stage_Mask : *Submit->Wait_Dst_Stage_Masks)
					vk_Wait_Dst_Stage_Masks.push_back(static_cast<VkPipelineStageFlags>(Wait_Dst_Stage_Mask));

				vk_Wait_Dst_Stge_Masks_List.emplace_back(std::make_optional(vk_Wait_Dst_Stage_Masks));
			}
			else
				vk_Wait_Dst_Stge_Masks_List.emplace_back(std::nullopt);

			if (nullptr != Submit->Command_Buffers && !Submit->Command_Buffers->empty()) {
				vector<VkCommandBuffer> vk_Command_Buffers{};
				vk_Command_Buffers.reserve(Submit->Command_Buffers->size());
				for (const auto& Command_Buffer : *Submit->Command_Buffers)
					vk_Command_Buffers.push_back(static_cast<Vulkan_Command_Buffer*>(Command_Buffer)->Get());
				vk_Command_Buffers_List.emplace_back(std::make_optional(vk_Command_Buffers));
			}
			else
				vk_Command_Buffers_List.emplace_back(std::nullopt);

			if (nullptr != Submit->Signal_Semaphores && !Submit->Signal_Semaphores->empty()) {
				vector<VkSemaphore> vk_Signal_Semaphores{};
				vk_Signal_Semaphores.reserve(Submit->Signal_Semaphores->size());
				for (const auto& Signal_Semaphore : *Submit->Signal_Semaphores)
					vk_Signal_Semaphores.push_back(static_cast<Vulkan_Semaphore*>(Signal_Semaphore)->Get());
				vk_Signal_Semaphores_List.emplace_back(std::make_optional(vk_Signal_Semaphores));
			}
			else
				vk_Signal_Semaphores_List.emplace_back(std::nullopt);

			VkSubmitInfo vk_Submit_Info{};
			{
				vk_Submit_Info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
				vk_Submit_Info.pNext = nullptr;
				vk_Submit_Info.waitSemaphoreCount = static_cast<uint32_t>(vk_Wait_Semaphores_List.back().value().size());
				vk_Submit_Info.pWaitSemaphores = vk_Wait_Semaphores_List.back().value().data();
				vk_Submit_Info.pWaitDstStageMask = vk_Wait_Dst_Stge_Masks_List.back().value().data();
				vk_Submit_Info.commandBufferCount = static_cast<uint32_t>(vk_Command_Buffers_List.back().value().size());
				vk_Submit_Info.pCommandBuffers = vk_Command_Buffers_List.back().value().data();
				vk_Submit_Info.signalSemaphoreCount = static_cast<uint32_t>(vk_Signal_Semaphores_List.back().value().size());
				vk_Submit_Info.pSignalSemaphores = vk_Signal_Semaphores_List.back().value().data();
			}

			vk_Submit_Infos.emplace_back(vk_Submit_Info);
		}

		VkQueue vk_Queue{ static_cast<Vulkan_Queue*>(Queue)->Get() };
		VkFence vk_Fence{ nullptr != Fence ? static_cast<Vulkan_Fence*>(Fence)->Get() : VK_NULL_HANDLE };

		VkResult vk_Result{ vkQueueSubmit(vk_Queue, vk_Submit_Infos.size(), vk_Submit_Infos.data(), vk_Fence) };

	}

	bool Vulkan_RHI::Queue_Wait_Idle(RHI_Queue* Queue) {
		VkQueue vk_Queue{ static_cast<Vulkan_Queue*>(Queue)->Get() };

		VkResult vk_Result{ vkQueueWaitIdle(vk_Queue) };

		return vk_Result == VK_SUCCESS;
	}

}// namespace NameSpace_Function::NameSpace_RHI::NameSpace_Vulkan_RHI