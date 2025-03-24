#pragma once

#include<functional>
#include<memory>

#include <vulkan/vulkan.h>

#include "rhi/empty_rhi/RHI_Class.h"

namespace NameSpace_Render::NameSpace_RHI::NameSpace_Vulkan_RHI {

	using std::function;
	using std::unique_ptr;

	class Vulkan_Instance final : public RHI_Instance {
	public:
		/*Vulkan_Instance(void) = default;
		*
		Vulkan_Instance(VkInstance res) {
			m_Resource.reset(res);
		}*/

		void Reset(VkInstance Res = nullptr) {
			m_Resource.reset(Res);
		}

		VkInstance Get() const {
			if (nullptr == m_Resource.get())
				LOG_ERROR("Get A Empty Instance Resource, Make Sure You Have Not Use It");

			return m_Resource.get();
		}

		void Set_Deleter(const function<void(VkInstance)>& Deleter) {
			this->m_Resource.get_deleter() = Deleter;
		}

	private:
		unique_ptr<VkInstance_T, function<void(VkInstance)>> m_Resource{ nullptr };

	};

	class Vulkan_Physical_Device final : public RHI_Physical_Device {
	public:
		/*Vulkan_Physical_Device(void) = default;
		*
		Vulkan_Physical_Device(VkPhysicalDevice res) {
			m_Resource.reset(res);
		}*/

		void Reset(VkPhysicalDevice res) {
			m_Resource.reset(res);
		}

		VkPhysicalDevice Get() const {
			if (nullptr == m_Resource.get())
				LOG_ERROR("Vulkan_Physical_Device::Get() : m_Resource is nullptr");

			return m_Resource.get();
		}

	private:
		unique_ptr<VkPhysicalDevice_T, function<void(VkPhysicalDevice)>> m_Resource{ nullptr ,[](auto PhysicalDevice) {if (nullptr != PhysicalDevice) { PhysicalDevice = nullptr; }; } };

	};

	class Vulkan_Logical_Device final : public RHI_Logical_Device {
	public:
		/*Vulkan_Logical_Device(void) = default;
		*
		Vulkan_Logical_Device(VkDevice res) {
			m_Resource.reset(res);
		}*/

		void Reset(VkDevice res) {
			m_Resource.reset(res);
		}

		VkDevice Get() const {
			if (nullptr == m_Resource.get())
				LOG_ERROR("Vulkan_Logical_Device::Get() : m_Resource is nullptr");

			return m_Resource.get();
		}

		void Set_Deleter(const function<void(VkDevice)>& Deleter) {
			this->m_Resource.get_deleter() = Deleter;
		}

	private:
		unique_ptr<VkDevice_T, function<void(VkDevice)>> m_Resource{ nullptr };

	};

	class Vulkan_Queue final : public RHI_Queue {
	public:
		/*Vulkan_Queue(void) = default;
		*
		Vulkan_Queue(VkQueue res) {
			m_Resource.reset(res);
		}*/
		void Reset(VkQueue res) {
			m_Resource.reset(res);
		}
		VkQueue Get() const {
			if (nullptr == m_Resource.get())
				LOG_ERROR("Vulkan_Command_Buffer::Get() : m_Resource is nullptr");

			return m_Resource.get();
		}

	private:
		unique_ptr<VkQueue_T, function<void(VkQueue)>> m_Resource{ nullptr,[](auto Queue) {if (nullptr != Queue) { Queue = nullptr; }; } };

	};

	class Vulkan_Command_Pool final : public RHI_Command_Pool {
	public:
		/*Vulkan_Command_Pool(void) = default;

		Vulkan_Command_Pool(VkCommandPool res) {
			m_Resource.reset(res);
		}*/

		void Reset(VkCommandPool res) {
			m_Resource.reset(res);
		}

		VkCommandPool Get() const {
			if (nullptr == m_Resource.get())
				LOG_ERROR("Vulkan_Command_Buffer::Get() : m_Resource is nullptr");

			return m_Resource.get();
		}

		void Set_Deleter(const function<void(VkCommandPool)>& Deleter) {
			this->m_Resource.get_deleter() = Deleter;
		}

	private:
		unique_ptr<VkCommandPool_T, function<void(VkCommandPool)>> m_Resource{ nullptr };

	};

	class Vulkan_Command_Buffer final : public RHI_Command_Buffer {
	public:
		/*Vulkan_Command_Buffer(void) = default;

		Vulkan_Command_Buffer(VkCommandBuffer res){
			m_Resource.reset(res);
		}*/

		void Reset(VkCommandBuffer res) {
			m_Resource.reset(res);
		}

		VkCommandBuffer Get() const {
			if (nullptr == m_Resource.get())
				LOG_ERROR("Vulkan_Command_Buffer::Get() : m_Resource is nullptr");

			return m_Resource.get();
		}

	private:
		unique_ptr<VkCommandBuffer_T, function<void(VkCommandBuffer)>> m_Resource{ nullptr,[](auto CommandBuffer) {if (nullptr != CommandBuffer) { CommandBuffer = nullptr; }; } };

	};

	class Vulkan_Descriptor_Pool final : public RHI_Descriptor_Pool {
	public:
		/*Vulkan_Descriptor_Pool(void) = default;

		Vulkan_Descriptor_Pool(VkDescriptorPool res) {
			m_Resource.reset(res);
		}*/

		void Reset(VkDescriptorPool res) {
			m_Resource.reset(res);
		}

		VkDescriptorPool Get() const {
			if (nullptr == m_Resource.get())
				LOG_ERROR("Vulkan_Command_Buffer::Get() : m_Resource is nullptr");

			return m_Resource.get();
		}

		void Set_Deleter(const function<void(VkDescriptorPool)>& Deleter) {
			this->m_Resource.get_deleter() = Deleter;
		}

	private:
		unique_ptr<VkDescriptorPool_T, function<void(VkDescriptorPool)>> m_Resource{ nullptr };

	};

	class Vulkan_Descriptor_Set_Layout final : public RHI_Descriptor_Set_Layout {
	public:
		/*Vulkan_Descriptor_Set_Layout(void) = default;
		*
		Vulkan_Descriptor_Set_Layout(VkDescriptorSetLayout res) {
			m_Resource.reset(res);
		}*/

		void Reset(VkDescriptorSetLayout res) {
			m_Resource.reset(res);
		}

		VkDescriptorSetLayout Get() const {
			if (nullptr == m_Resource.get())
				LOG_ERROR("Vulkan_Command_Buffer::Get() : m_Resource is nullptr");

			return m_Resource.get();
		}

		void Set_Deleter(const function<void(VkDescriptorSetLayout)>& Deleter) {
			this->m_Resource.get_deleter() = Deleter;
		}

	private:
		unique_ptr<VkDescriptorSetLayout_T, function<void(VkDescriptorSetLayout)>> m_Resource{ nullptr };

	};

	class Vulkan_Descriptor_Set final : public RHI_Descriptor_Set {
	public:
		/*Vulkan_Descriptor_Set(void) = default;
		*
		Vulkan_Descriptor_Set(VkDescriptorSet res) {
			m_Resource.reset(res);
		}*/
		void Reset(VkDescriptorSet res) {
			if (nullptr == m_Resource.get())
				LOG_ERROR("Vulkan_Command_Buffer::Get() : m_Resource is nullptr");

			m_Resource.reset(res);
		}

		VkDescriptorSet Get() const {
			return m_Resource.get();
		}

	private:
		unique_ptr<VkDescriptorSet_T, function<void(VkDescriptorSet)>> m_Resource{ nullptr,[](auto DescriptorSet) {if (nullptr != DescriptorSet) { DescriptorSet = nullptr; }; } };

	};

	class Vulkan_Semaphore final : public RHI_Semaphore {
	public:
		/*Vulkan_Semaphore(void) = default;
		*
		Vulkan_Semaphore(VkSemaphore res) {
			m_Resource.reset(res);
		}*/

		void Reset(VkSemaphore res) {
			m_Resource.reset(res);
		}
		VkSemaphore Get() const {
			if (nullptr == m_Resource.get())
				LOG_ERROR("Vulkan_Command_Buffer::Get() : m_Resource is nullptr");

			return m_Resource.get();
		}

		void Set_Deleter(const function<void(VkSemaphore)>& Deleter) {
			this->m_Resource.get_deleter() = Deleter;
		}

	private:
		unique_ptr<VkSemaphore_T, function<void(VkSemaphore)>> m_Resource{ nullptr };

	};

	class Vulkan_Fence final : public RHI_Fence {
	public:
		/*Vulkan_Fence(void) = default;
		*
		Vulkan_Fence(VkFence res) {
			m_Resource.reset(res);
		}*/
		void Reset(VkFence res) {
			m_Resource.reset(res);
		}

		VkFence Get() const {
			if (nullptr == m_Resource.get())
				LOG_ERROR("Vulkan_Command_Buffer::Get() : m_Resource is nullptr");

			return m_Resource.get();
		}

		void Set_Deleter(const function<void(VkFence)>& Deleter) {
			this->m_Resource.get_deleter() = Deleter;
		}

	private:
		unique_ptr<VkFence_T, function<void(VkFence)>> m_Resource{ nullptr };

	};

	class Vulkan_Sampler final : public RHI_Sampler {
	public:
		/*Vulkan_Sampler(void) = default;
		*
		Vulkan_Sampler(VkSampler res) {
			m_Resource.reset(res);
		}*/
		void Reset(VkSampler res) {
			m_Resource.reset(res);
		}

		VkSampler Get() const {
			if (nullptr == m_Resource.get())
				LOG_ERROR("Vulkan_Command_Buffer::Get() : m_Resource is nullptr");

			return m_Resource.get();
		}

		void Set_Deleter(const function<void(VkSampler)>& Deleter) {
			this->m_Resource.get_deleter() = Deleter;
		}

	private:
		unique_ptr<VkSampler_T, function<void(VkSampler)>> m_Resource{ nullptr };

	};

	class Vulkan_Shader_Module final : public RHI_Shader_Module {
	public:
		/*Vulkan_Shader_Module(void) = default;
		*
		Vulkan_Shader_Module(VkShaderModule res) {
			m_Resource.reset(res);
		}*/

		void Reset(VkShaderModule res) {
			m_Resource.reset(res);
		}

		VkShaderModule Get() const {
			if (nullptr == m_Resource.get())
				LOG_ERROR("Vulkan_Command_Buffer::Get() : m_Resource is nullptr");

			return m_Resource.get();
		}

		void Set_Deleter(const function<void(VkShaderModule)>& Deleter) {
			this->m_Resource.get_deleter() = Deleter;
		}

	private:
		unique_ptr<VkShaderModule_T, function<void(VkShaderModule)>> m_Resource{ nullptr };
	};

	class Vulkan_Buffer final : public RHI_Buffer {
	public:
		/*Vulkan_Buffer(void) = default;
		*
		Vulkan_Buffer(VkBuffer res) {
			m_Resource.reset(res);
		}*/
		void Reset(VkBuffer res) {
			m_Resource.reset(res);
		}

		VkBuffer Get() const {
			if (nullptr == m_Resource.get())
				LOG_ERROR("Vulkan_Command_Buffer::Get() : m_Resource is nullptr");

			return m_Resource.get();
		}

		void Set_Deleter(const function<void(VkBuffer)>& Deleter) {
			this->m_Resource.get_deleter() = Deleter;
		}

	private:
		unique_ptr<VkBuffer_T, function<void(VkBuffer)>> m_Resource{ nullptr };

	};

	class Vulkan_Buffer_View final : public RHI_Buffer_View {
	public:
		/*VUlkan_Buffer_View(void) = default;
		*
		VUlkan_Buffer_View(VkBufferView res) {
			m_Resource.reset(res);
		}*/

		void Reset(VkBufferView res) {
			m_Resource.reset(res);
		}

		VkBufferView Get() const {
			if (nullptr == m_Resource.get())
				LOG_ERROR("Vulkan_Command_Buffer::Get() : m_Resource is nullptr");
			return m_Resource.get();
		}

		void Set_Deleter(const function<void(VkBufferView)>& Deleter) {
			this->m_Resource.get_deleter() = Deleter;
		}

	private:
		unique_ptr<VkBufferView_T, function<void(VkBufferView)>> m_Resource{ nullptr };

	};

	class Vulkan_Device_Memory final : public RHI_Device_Memory {
	public:
		/*Vulkan_Device_Memory(void) = default;
		*
		Vulkan_Device_Memory(VkDeviceMemory res) {
			m_Resource.reset(res);
		}*/

		void Reset(VkDeviceMemory res) {
			m_Resource.reset(res);
		}

		VkDeviceMemory Get() const {
			if (nullptr == m_Resource.get())
				LOG_ERROR("Vulkan_Command_Buffer::Get() : m_Resource is nullptr");

			return m_Resource.get();
		}

		void Set_Deleter(const function<void(VkDeviceMemory)>& Deleter) {
			this->m_Resource.get_deleter() = Deleter;
		}

	private:
		unique_ptr<VkDeviceMemory_T, function<void(VkDeviceMemory)>> m_Resource{ nullptr };

	};

	class Vulkan_Image final : public RHI_Image {
	public:
		/*Vulkan_Image(void) = default;
		*
		Vulkan_Image(VkImage res) {
			m_Resource.reset(res);
		}*/

		void Reset(VkImage res) {
			m_Resource.reset(res);
		}

		VkImage Get() const {
			if (nullptr == m_Resource.get())
				LOG_ERROR("Vulkan_Command_Buffer::Get() : m_Resource is nullptr");

			return m_Resource.get();
		}

		void Set_Deleter(const function<void(VkImage)>& Deleter) {
			this->m_Resource.get_deleter() = Deleter;
		}

	private:
		unique_ptr<VkImage_T, function<void(VkImage)>> m_Resource{ nullptr };

	};

	class Vulkan_Image_View final : public RHI_Image_View {
	public:
		/*Vulkan_Image_View(void) = default;
		*
		Vulkan_Image_View(VkImageView res) {
			m_Resource.reset(res);
		}*/

		void Reset(VkImageView res) {
			m_Resource.reset(res);
		}

		VkImageView Get() const {
			if (nullptr == m_Resource.get())
				LOG_ERROR("Vulkan_Command_Buffer::Get() : m_Resource is nullptr");

			return m_Resource.get();
		}

		void Set_Deleter(const function<void(VkImageView)>& Deleter) {
			this->m_Resource.get_deleter() = Deleter;
		}

	private:
		unique_ptr<VkImageView_T, function<void(VkImageView)>> m_Resource{ nullptr };

	};

	class Vulkan_Frame_Buffer final : public RHI_Frame_Buffer {
	public:
		/*Vulkan_Frame_Buffer(void) = default;
		*
		Vulkan_Frame_Buffer(VkFramebuffer res) {
			m_Resource.reset(res);
		}*/

		void Reset(VkFramebuffer res) {
			m_Resource.reset(res);
		}

		VkFramebuffer Get() const {
			if (nullptr == m_Resource.get())
				LOG_ERROR("Vulkan_Command_Buffer::Get() : m_Resource is nullptr");

			return m_Resource.get();
		}

		void Set_Deleter(const function<void(VkFramebuffer)>& Deleter) {
			this->m_Resource.get_deleter() = Deleter;
		}

	private:
		unique_ptr<VkFramebuffer_T, function<void(VkFramebuffer)>> m_Resource{ nullptr };

	};

	class Vulkan_Render_Pass final : public RHI_Render_Pass {
	public:
		/*Vulkan_Render_Pass(void) = default;
		*
		Vulkan_Render_Pass(VkRenderPass res) {
			m_Resource.reset(res);
		}*/

		void Reset(VkRenderPass res) {
			m_Resource.reset(res);
		}

		VkRenderPass Get() const {
			if (nullptr == m_Resource.get())
				LOG_ERROR("Vulkan_Command_Buffer::Get() : m_Resource is nullptr");

			return m_Resource.get();
		}

		void Set_Deleter(const function<void(VkRenderPass)>& Deleter) {
			this->m_Resource.get_deleter() = Deleter;
		}

	private:
		unique_ptr<VkRenderPass_T, function<void(VkRenderPass)>> m_Resource{ nullptr };

	};

	class Vulkan_Pipeline final : public RHI_Pipeline {
	public:
		/*Vulkan_Pipeline(void) = default;
		*
		Vulkan_Pipeline(VkPipeline res) {
			m_Resource.reset(res);
		}*/

		void Reset(VkPipeline res) {
			m_Resource.reset(res);
		}

		VkPipeline Get() const {
			if (nullptr == m_Resource.get())
				LOG_ERROR("Vulkan_Command_Buffer::Get() : m_Resource is nullptr");

			return m_Resource.get();
		}

		void Set_Deleter(const function<void(VkPipeline)>& Deleter) {
			this->m_Resource.get_deleter() = Deleter;
		}

	private:
		unique_ptr<VkPipeline_T, function<void(VkPipeline)>> m_Resource{ nullptr };

	};

	class Vulkan_Pieline_Cache final : public RHI_Pipeline_Cache {
	public:
		/*Vulkan_Pieline_Cache(void) = default;
		*
		Vulkan_Pieline_Cache(VkPipelineCache res) {
			m_Resource.reset(res);
		}*/

		void Reset(VkPipelineCache res) {
			m_Resource.reset(res);
		}

		VkPipelineCache Get() const {
			if (nullptr == m_Resource.get())
				LOG_ERROR("Vulkan_Command_Buffer::Get() : m_Resource is nullptr");

			return m_Resource.get();
		}

		void Set_Deleter(const function<void(VkPipelineCache)>& Deleter) {
			this->m_Resource.get_deleter() = Deleter;
		}

	private:
		unique_ptr<VkPipelineCache_T, function<void(VkPipelineCache)>> m_Resource{ nullptr };

	};

	class Vulkan_Pipeline_Layout final : public RHI_Pipeline_Layout {
	public:
		/*Vulkan_Pipeline_Layout(void) = default;
		*
		Vulkan_Pipeline_Layout(VkPipelineLayout res) {
			m_Resource.reset(res);
		}*/

		void Reset(VkPipelineLayout res) {
			m_Resource.reset(res);
		}

		VkPipelineLayout Get() const {
			if (nullptr == m_Resource.get())
				LOG_ERROR("Vulkan_Command_Buffer::Get() : m_Resource is nullptr");

			return m_Resource.get();
		}

		void Set_Deleter(const function<void(VkPipelineLayout)>& Deleter) {
			this->m_Resource.get_deleter() = Deleter;
		}

	private:
		unique_ptr<VkPipelineLayout_T, function<void(VkPipelineLayout)>> m_Resource{ nullptr };

	};



}// namespace NameSpace_Render::NameSpace_RHI::NameSpace_Vulkan_RHI