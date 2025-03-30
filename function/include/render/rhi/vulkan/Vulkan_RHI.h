#pragma once

#include<limits>
#include<tuple>
#include<optional>
#include<string>
#include<array>
#include<vector>
#include<unordered_map>
#include<memory>

#include "vulkan/vulkan.h"

#include "render/window/Window_System.h"

#include "render/rhi/empty_rhi/RHI_Class.h"
#include "render/rhi/empty_rhi/Empty_RHI.h"
#include "render/rhi/vulkan/Vulkan_RHI_Resource.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_RHI::NameSpace_Vulkan_RHI {

	using std::numeric_limits;
	using std::tuple;
	using std::optional;
	using std::string;
	using std::array;
	using std::vector;
	using std::unique_ptr;
	using std::unordered_map;


	class Vulkan_RHI final : public Empty_RHI {
	private:
		struct Queue_Family_Indices final {
			uint32_t Graphics_Family;
			uint32_t Present_Family;
			uint32_t Compute_Family;
		};

		struct Queues final {
			VkQueue Graphic_Queue{ nullptr };
			VkQueue Present_Queue{ nullptr };
			VkQueue Compute_Queue{ nullptr };

			unique_ptr<RHI_Queue> Graphic_RHI_Queue{ std::make_unique<Vulkan_Queue>() };
			unique_ptr<RHI_Queue> Present_RHI_Queue{ std::make_unique<Vulkan_Queue>() };
			unique_ptr<RHI_Queue> Compute_RHI_Queue{ std::make_unique<Vulkan_Queue>() };
		};

		struct Swap_Chain_Support_Details final {
			VkSurfaceCapabilitiesKHR Capabilities{};
			vector<VkSurfaceFormatKHR> Formats{};
			vector<VkPresentModeKHR> Present_Modes{};
		};

	private:
		Vulkan_RHI(void) = delete;

		Vulkan_RHI(const Vulkan_RHI&) = delete;
		Vulkan_RHI& operator=(const Vulkan_RHI&) = delete;

		//TODO : Constant Variable
	public:
		Vulkan_RHI(const RHI_Initialization_Info& init_info);

		~Vulkan_RHI(void);

		// TODO : Macro 
#ifdef _DEBUG
	private:
		bool Check_Vaildation_Layer_Support(void);

		static VKAPI_ATTR VkBool32 VKAPI_CALL
			Debug_Call_Back(
				VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
				VkDebugUtilsMessageTypeFlagsEXT messageType,
				const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
				void* pUserData
			);

		void Build_Debug_Messenger_Create_Info(void);

		static const VkResult
			Create_DebugUtils_Messenger_EXT(
				VkInstance Instance,
				const VkDebugUtilsMessengerCreateInfoEXT* Create_Info,
				const VkAllocationCallbacks* Allocator,
				VkDebugUtilsMessengerEXT* m_Debug_Messenger
			);

		static void
			Destroy_DebugUtils_Messenger_EXT(
				VkInstance Instance,
				VkDebugUtilsMessengerEXT m_Debug_Messenger,
				const VkAllocationCallbacks* Allocator
			);

		void Set_Debug_Messenger(void);

		vector<const char*> m_Validation_Layers{};

		VkDebugUtilsMessengerCreateInfoEXT m_Vk_Debug_Utils_Messenger_Create_Info_EXT{};
		VkDebugUtilsMessengerEXT m_Debug_Messenger{};

		PFN_vkCmdBeginDebugUtilsLabelEXT F_vkCmdBeginDebugUtilsLabelEXT{ nullptr };
		PFN_vkCmdEndDebugUtilsLabelEXT F_vkCmdEndDebugUtilsLabelEXT{ nullptr };

#endif // DEBUG

		//TODO : Public Func
	public:
		//TODO Set Function 
		void Create_Surface(void);//TODO : Direct12 Not Have Surface 

		//TODO Get Func
		[[nodiscard]] size_t Get_API_Version(void)const;
		[[nodiscard]] VkAllocationCallbacks* Get_Allocator(void)const;
		[[nodiscard]] VmaAllocator Get_VMA_Allocator(void) const;
		[[nodiscard]] GLFWwindow* Get_GLFW_Window(void)const;
		[[nodiscard]] uint32_t Get_Graphics_Queue_Family(void)const;


		//TODO : Private Member Func
	private:
		void Create_Allocator(void);
		void Reset_Instance_Deleters(VkInstance Instance, const VkAllocationCallbacks* Allocator);
		void Reset_Device_Deleters(VkDevice Device, const VkAllocationCallbacks* pAllocator);

		void Get_Device_ProcAddrs(void);
		void Create_VAM_Allocator(void);

		void Create_Nearest_Sampler(void);
		void Create_Linear_Sampler(void);

		void Create_SwapChain_Depth_Image(void);
		void Clear_SwapChain(void);

		//TODO : Static Public Func
	public:
		[[nodiscard]] static const vector<const char*> S_Get_Instance_Extensions_Require(void);

		[[nodiscard]] static void* VKAPI_CALL
			S_Allocation(
				void* pUserData,
				size_t size,
				size_t alignment,
				VkSystemAllocationScope /*allocationScope*/
			);
		[[nodiscard]] static void* VKAPI_CALL
			S_Reallocation(
				void* pUserData,
				void* original,
				size_t size,
				size_t alignment,
				VkSystemAllocationScope allocationScope
			);

		[[nodiscard]] static void VKAPI_CALL S_Free(void* pUserData, void* memory);

		[[nodiscard]] static const vector<const char*> S_Get_Physical_Device_Extensions_Require(void);

		[[nodiscard]] static bool
			S_Check_Physical_Device_Extension_Support(
				VkPhysicalDevice Device,
				const vector<const char*>& Require_Extensions
			);
		[[nodiscard]] static bool
			S_Is_Device_Suitable(
				VkPhysicalDevice Device,
				const vector<const char*>& Require_Extensions
			);

		[[nodiscard]] static  VkSampleCountFlagBits S_Get_Max_Usable_Sample_Count(VkPhysicalDevice Physical_Device);

		[[nodiscard]] static uint32_t
			S_Get_Physical_Device_Queue_Present_Family(
				VkPhysicalDevice Physical_Device,
				VkSurfaceKHR Surface,
				uint32_t Graphics_Family_Index = numeric_limits<uint32_t>::max()
			);
		[[nodiscard]] static uint32_t
			S_Find_Queue_Families(
				VkPhysicalDevice Physical_Device,
				VkQueueFlagBits Vk_Queue_FlagBit
			);
		[[nodiscard]] static const Queue_Family_Indices
			S_Get_Queue_Framies(
				VkPhysicalDevice Physical_Device, VkSurfaceKHR Suraface
			);

		[[nodiscard]] static const VkFormat
			S_Find_Supported_Format(
				VkPhysicalDevice Physical_Device,
				const vector<VkFormat>& Candidates,
				VkImageTiling Tiling,
				VkFormatFeatureFlags Features
			);

		[[nodiscard]] static const Swap_Chain_Support_Details
			S_Query_Swap_Chain_Support_Details(
				const VkPhysicalDevice Physical_Device,
				VkSurfaceKHR Suraface
			);

		[[nodiscard]] static const VkSurfaceFormatKHR S_Choose_SwapChain_Surface_Format(const vector<VkSurfaceFormatKHR>& Available_Formats);

		[[nodiscard]] static const VkPresentModeKHR S_Choose_SwapChain_Present_Mode(const vector<VkPresentModeKHR>& Available_Present_Modes);

		[[nodiscard]] static const VkExtent2D S_Choose_SwapChain_Extent(const shared_ptr<Window_System>& Window, const VkSurfaceCapabilitiesKHR& Capabilities);



		//NOTE :Parser RHI Struct To Vulkan Struct
		[[nodiscard]] static const optional<VkWriteDescriptorSet>
			S_Parser_RHI_Write_Descriptor_Set(
				const RHI_Write_Descriptor_Set* Write_Descriptor_Set,
				optional<vector<VkDescriptorImageInfo>>& Image_Infos,
				optional<vector<VkDescriptorBufferInfo>>& Buffer_Infos,
				optional<vector<VkBufferView>>& vk_Buffer_Views
			);

		[[nodiscard]] static const optional<vector< VkAttachmentReference>>
			S_Parser_RHI_Attachment_Reference(
				const vector<const RHI_Attachment_Reference*>* Attachment_References
			);

		[[nodiscard]] static const optional<vector<VkPipelineShaderStageCreateInfo>>
			S_Parse_RHI_Pipeline_Shader_Stage_Create_Info(
				const vector<const RHI_Pipeline_Shader_Stage_Create_Info*>* Stages,
				vector<optional<vector<VkSpecializationMapEntry>>>& vk_Specialization_Map_Entryss,
				vector<optional<VkSpecializationInfo>>& vk_Specialization_Infos
			);

		[[nodiscard]] static const optional<VkPipelineVertexInputStateCreateInfo>
			S_Parser_RHI_Pipeline_Vertex_Input_State_Create_Info(
				const RHI_Pipeline_Vertex_Input_State_Create_Info* Vertex_Input_State_Create_Info,
				optional<vector<VkVertexInputBindingDescription>>& vk_Vertex_Input_Binding_Descriptions,
				optional<vector<VkVertexInputAttributeDescription>>& vk_Vertex_Input_Attribute_Descriptions
			);

		[[nodiscard]] static const optional<VkPipelineInputAssemblyStateCreateInfo>
			S_Parser_RHI_Pipeline_Input_Assembly_State_Create_Info(
				const RHI_Pipeline_Input_Assembly_State_Create_Info* vk_Input_Assembly_State_Create_Info
			);

		[[nodiscard]] static const optional<VkPipelineTessellationStateCreateInfo>
			S_Parser_RHI_Pipeline_Tessellation_State_Create_Info(
				const RHI_Pipeline_Tessellation_State_Create_Info* vk_Tessellation_State_Create_Info
			);

		[[nodiscard]] static const optional<VkPipelineViewportStateCreateInfo>
			S_Parser_RHI_Pipeline_Viewport_State_Create_Info(
				const RHI_Pipeline_Viewport_State_Create_Info* vk_Viewport_State_Create_Info,
				optional<vector<VkViewport>>& Viewports,
				optional<vector<VkRect2D>>& Scissors
			);

		[[nodiscard]] static const optional<VkPipelineRasterizationStateCreateInfo>
			S_Parser_RHI_Pipeline_Rasterization_State_Create_Info(
				const RHI_Pipeline_Rasterization_State_Create_Info* vk_Rasterization_State_Create_Info
			);

		[[nodiscard]] static const optional<VkPipelineMultisampleStateCreateInfo>
			S_Parser_RHI_Pipeline_Multisample_State_Create_Info(
				const RHI_Pipeline_Multisample_State_Create_Info* vk_Multisample_State_Create_Info,
				optional<VkSampleMask>& vk_Sample_Mask
			);

		[[nodiscard]] static const optional<VkPipelineDepthStencilStateCreateInfo>
			S_Parser_RHI_Pipeline_Depth_Stencil_State_Create_Info(
				const RHI_Pipeline_Depth_Stencil_State_Create_Info* vk_Depth_Stencil_State_Create_Info,
				VkStencilOpState& vk_Front_Stencil_Op_State,
				VkStencilOpState& vk_Back_Stencil_Op_State
			);

		[[nodiscard]] static const optional<VkPipelineColorBlendStateCreateInfo>
			S_Parser_RHI_Pipeline_Color_Blend_State_Create_Info(
				const RHI_Pipeline_Color_Blend_State_Create_Info* vk_Color_Blend_State_Create_Info,
				optional<vector<VkPipelineColorBlendAttachmentState>>& vk_Color_Blend_Attachment_States,
				array<float, 4>& Blend_Constants
			);

		[[nodiscard]] static const optional<VkPipelineDynamicStateCreateInfo>
			S_Parser_RHI_Pipeline_Dynamic_State_Create_Info(
				const RHI_Pipeline_Dynamic_State_Create_Info* vk_Dynamic_State_Create_Info,
				optional<vector<VkDynamicState>>& vk_Dynamic_States
			);

		//NOTE : Static Member Variable
	public:
		static constexpr uint32_t s_Frames_In_Flight{ 3 };

	private:

		//TODO : Member Variable
	private:
		//NOTE : Other Member Variable

		// NOTE : Function Pointers
		PFN_vkWaitForFences					F_vkWaitForFences{ nullptr };
		PFN_vkResetFences					F_vkResetFences{ nullptr };
		PFN_vkResetCommandPool				F_vkResetCommandPool{ nullptr };
		PFN_vkBeginCommandBuffer			F_vkBeginCommandBuffer{ nullptr };
		PFN_vkEndCommandBuffer				F_vkEndCommandBuffer{ nullptr };
		PFN_vkCmdBeginRenderPass			F_vkCmdBeginRenderPass{ nullptr };
		PFN_vkCmdNextSubpass				F_vkCmdNextSubpass{ nullptr };
		PFN_vkCmdEndRenderPass				F_vkCmdEndRenderPass{ nullptr };
		PFN_vkCmdBindPipeline				F_vkCmdBindPipeline{ nullptr };
		PFN_vkCmdSetViewport				F_vkCmdSetViewport{ nullptr };
		PFN_vkCmdSetScissor					F_vkCmdSetScissor{ nullptr };
		PFN_vkCmdBindVertexBuffers			F_vkCmdBindVertexBuffers{ nullptr };
		PFN_vkCmdBindIndexBuffer			F_vkCmdBindIndexBuffer{ nullptr };
		PFN_vkCmdBindDescriptorSets			F_vkCmdBindDescriptorSets{ nullptr };
		PFN_vkCmdDrawIndexed				F_vkCmdDrawIndexed{ nullptr };
		PFN_vkCmdClearAttachments			F_vkCmdClearAttachments{ nullptr };

		//NOTE : Window System Variable
		shared_ptr<Window_System> m_Window{ nullptr };
		RHI_Viewport m_Viewport{};
		RHI_Rect_2D m_Scissor{};

		//Vulkan Variable
		unique_ptr<VkAllocationCallbacks> m_Allocator{ nullptr };
		vector<const char*> m_Physical_Device_Extensions{};
		VkSampleCountFlagBits m_Msaa_Samples{ VK_SAMPLE_COUNT_1_BIT };

		//VMA
		VmaAllocator m_VMA_Allocator{ nullptr };

		//Deleter
		function<void(VkInstance)>				m_VK_Instance_Deleter{ nullptr };
		function<void(VkSurfaceKHR)>			m_VK_Surface_Deleter{ nullptr };
		function<void(VkDevice)>				m_VK_Device_Deleter{ nullptr };
		function<void(VkCommandPool)>			m_VK_Command_Pool_Deleter{ nullptr };
		function<void(VkDescriptorPool)>		m_VK_Descriptor_Pool_Deleter{ nullptr };
		function<void(VkSemaphore)>				m_VK_Semaphore_Deleter{ nullptr };
		function<void(VkFence)>					m_VK_Fence_Deleter{ nullptr };
		function<void(VkSwapchainKHR)>			m_VK_SwapChain_Deleter{ nullptr };
		function<void(VkImageView)>				m_VK_Image_View_Deleter{ nullptr };
		function<void(VkSampler)>				m_VK_Sampler_Deleter{ nullptr };
		function<void(VkShaderModule)>			m_VK_Shader_Module_Deleter{ nullptr };
		function<void(VkBuffer)>				m_VK_Buffer_Deleter{ nullptr };
		function<void(VkImage)>					m_VK_Image_Deleter{ nullptr };
		function<void(VkDeviceMemory)>			m_VK_Device_Memory_Deleter{ nullptr };
		function<void(VkDescriptorSetLayout)>	m_VK_Descriptor_Set_Layout_Deleter{ nullptr };
		function<void(VkFramebuffer)>			m_VK_Frame_Buffer_Deleter{ nullptr };
		function<void(VkRenderPass)>			m_VK_Render_Pass_Deleter{ nullptr };
		function<void(VkPipeline)>				m_VK_Pipeline_Deleter{ nullptr };
		function<void(VkPipelineCache)>			m_VK_Pipeline_Cache_Deleter{ nullptr };
		function<void(VkPipelineLayout)>		m_VK_Pipeline_Layout_Deleter{ nullptr };


		//Class Resource
		unique_ptr<RHI_Instance> m_RHI_Instance{ std::make_unique<Vulkan_Instance>() };

		unique_ptr<VkSurfaceKHR_T, decltype(m_VK_Surface_Deleter)> m_VK_Surface{ nullptr };

		unique_ptr<RHI_Physical_Device> m_RHI_Physical_Device{ std::make_unique<Vulkan_Physical_Device>() };
		VkPhysicalDevice m_VK_Physical_Device{ nullptr };

		unique_ptr<RHI_Logical_Device> m_RHI_Logical_Device{ std::make_unique<Vulkan_Logical_Device>() };
		VkDevice m_Logical_VK_Device{ nullptr };

		Queue_Family_Indices m_Queue_Family_Indices{};
		Queues m_Queues{};

		unique_ptr<RHI_Command_Pool> m_Default_RHI_Command_Pool{ std::make_unique<Vulkan_Command_Pool>() };
		VkCommandPool m_Default_VK_Command_Pool{ nullptr };
		array<unique_ptr<RHI_Command_Pool>, s_Frames_In_Flight> m_RHI_Command_Pools{ std::make_unique<Vulkan_Command_Pool>(),std::make_unique<Vulkan_Command_Pool>(),std::make_unique<Vulkan_Command_Pool>() };//TODO : Erase Repeat Code
		array<VkCommandPool, s_Frames_In_Flight> m_VK_Command_Pools{ nullptr,nullptr,nullptr };

		array<unique_ptr<RHI_Command_Buffer>, s_Frames_In_Flight> m_RHI_Command_Buffers{ std::make_unique<Vulkan_Command_Buffer>(),std::make_unique<Vulkan_Command_Buffer>() ,std::make_unique<Vulkan_Command_Buffer>() };
		array<VkCommandBuffer, s_Frames_In_Flight> m_VK_Command_Buffers{ nullptr,nullptr,nullptr };
		uint8_t m_Current_Frame{ 0 };

		unique_ptr<RHI_Descriptor_Pool> m_Default_RHI_Descriptor_Pool{ std::make_unique<Vulkan_Descriptor_Pool>() };
		VkDescriptorPool m_Default_VK_Descriptor_Pool{ nullptr };

		unique_ptr<RHI_Sampler> m_Linear_RHI_Sampler{ std::make_unique<Vulkan_Sampler>() };
		unique_ptr<RHI_Sampler> m_Nearest_RHI_Sampler{ std::make_unique<Vulkan_Sampler>() };
		unordered_map<uint32_t, unique_ptr<RHI_Sampler>> m_Mipmap_RHI_Samplers{};

		Swap_Chain_Support_Details m_Swap_Chain_Support_Details{};

		//TODO: Sync Window Fields
		VkFormat m_SwapChain_Image_Format{};
		VkExtent2D m_SwapChain_Extent{};
		uint32_t m_SwapChain_Image_Count{ std::numeric_limits<uint32_t>::max() };

		unique_ptr<VkSwapchainKHR_T, decltype(m_VK_SwapChain_Deleter)> m_Vk_SwapChain{ nullptr };

		vector<VkImage> m_SwapChain_VK_Images{};
		vector<unique_ptr<RHI_Image>> m_SwapChain_RHI_Images{};
		
		vector<VkImageView> m_SwapChain_VK_Image_Views{};
		vector<unique_ptr<RHI_Image_View>> m_SwapChain_RHI_Image_Views{};

		unique_ptr<RHI_Image> m_SwapChain_Depth_RHI_Image{ std::make_unique<Vulkan_Image>() };
		unique_ptr<RHI_Device_Memory> m_SwapChain_Depth_RHI_Device_Memory{ std::make_unique<Vulkan_Device_Memory>() };
		unique_ptr<RHI_Image_View> m_SwapChain_Depth_RHI_Image_View{ std::make_unique<Vulkan_Image_View>() };

		array<unique_ptr<RHI_Semaphore>, s_Frames_In_Flight> m_Image_available_For_Render_RHI_Semaphores{ std::make_unique<Vulkan_Semaphore>(),std::make_unique<Vulkan_Semaphore>(),std::make_unique<Vulkan_Semaphore>() };
		array<unique_ptr<RHI_Semaphore>, s_Frames_In_Flight> m_Image_Finished_For_Present_RHI_Semaphores{ std::make_unique<Vulkan_Semaphore>(),std::make_unique<Vulkan_Semaphore>(),std::make_unique<Vulkan_Semaphore>() };
		array<unique_ptr<RHI_Semaphore>, s_Frames_In_Flight> m_Image_Available_For_TeCopy_RHI_Semaphores{ std::make_unique<Vulkan_Semaphore>(),std::make_unique<Vulkan_Semaphore>(),std::make_unique<Vulkan_Semaphore>() };
		array<unique_ptr<RHI_Fence>, s_Frames_In_Flight> m_InFlight_RHI_Fences{ std::make_unique<Vulkan_Fence>(),std::make_unique<Vulkan_Fence>(),std::make_unique<Vulkan_Fence>() };

		//TODO : Override Func
	public:
		void Create_Instance(void) override;//NOTE : Instance Life Time Is The Same As The Application
		[[nodiscard]] RHI_Instance* Get_Instance(void) const override;

		void Create_Physical_Device(void) override;// NOTE : Physical Device Life Time Is The Same As The Application
		[[nodiscard]] const RHI_Physical_Device_Properties Get_Physical_Device_Properties(void) const override;
		[[nodiscard]] RHI_Physical_Device* Get_Physical_Device(void) const override;
		[[nodiscard]] const RHI_FORMAT Get_Physical_Depth_Format(void)const override;

		void Create_Logical_Device(void) override;
		[[nodiscard]] RHI_Logical_Device* Get_Logical_Device(void) const override;

		[[nodiscard]] RHI_Queue* Get_Graphics_Queue(void) const override;//Command Queue

		[[nodiscard]] unique_ptr<RHI_Command_Pool>
			Create_Command_Pool(
				const RHI_Command_Pool_Create_Info* Create_Info) override;

		void Create_Default_Command_Pool(void) override;

		[[nodiscard]] RHI_Descriptor_Pool* Get_Default_Descriptor_Pool(void)const override;

		[[nodiscard]] vector<unique_ptr<RHI_Command_Buffer>>
			Allocate_Command_Buffers(
				const RHI_Command_Buffer_Allocate_Info* Allocate_Info
			) override;

		void Allocate_Default_Command_Buffers(void) override;

		[[nodiscard]] unique_ptr<RHI_Command_Buffer> Begin_SingleTime_Command(void) override;

		void End_SingleTime_Command(unique_ptr<RHI_Command_Buffer> Command_Buffer) override;

		void Create_SwapChain(void) override;
		void Create_SwapChhain_Image_Views(void) override;

		[[nodiscard]] tuple<
			unique_ptr<RHI_Buffer>,
			unique_ptr<RHI_Device_Memory>>
			Create_Buffer(
				RHI_Device_Size Size,
				RHI_Buffer_Usage_Flags Usage,
				RHI_Memory_Property_Flags Properties
			) override;

		[[nodiscard]] tuple<
			unique_ptr<RHI_Buffer>,
			VmaAllocation>
			Create_Buffer_VMA(
				const RHI_Buffer_Create_Info* Buffer_Create_Info,
				const VmaAllocationCreateInfo* Allocation_Create_Info,
				VmaAllocationInfo* AllocationInfo
			) override;

		[[nodiscard]] tuple<
			unique_ptr<RHI_Buffer>,
			VmaAllocation>
			Create_Buffer_Alignment_VMA(
				const RHI_Buffer_Create_Info* Buffer_Create_Info,
				const VmaAllocationCreateInfo* Allocation_Create_Info,
				VmaAllocationInfo* AllocationInfo,
				RHI_Device_Size Min_Alignment
			) override;

		void
			Copy_Buffer(
				RHI_Buffer* Src_Buffer,
				RHI_Buffer* Dst_Buffer,
				RHI_Device_Size Src_Offset,
				RHI_Device_Size Dst_Offset,
				RHI_Device_Size Size
			) override;

		//NOTE : Image
		[[nodiscard]] virtual tuple<
			unique_ptr<RHI_Image>,
			unique_ptr<RHI_Device_Memory>>
			Create_Image(
				RHI_Extent_2D Image_Extent,
				RHI_FORMAT Image_Format,
				uint32_t Array_Layers,
				uint32_t Mip_levels,
				RHI_IMAGE_TILING Image_Tiling,
				RHI_Image_Usage_Flags Image_Usage_Flags,
				RHI_Memory_Property_Flags Memory_Property_Flags,
				RHI_Image_Create_Flags Image_Create_Flags
			) override;

		[[nodiscard]] unique_ptr<RHI_Image_View>
			Create_Image_View(
				RHI_Image* Image,
				RHI_FORMAT Format,
				uint32_t Mip_levels,
				uint32_t Layout_Count,
				RHI_IMAGE_VIEW_TYPE View_Type,
				RHI_Image_Aspect_Flags Image_Aspect_Flags
			) override;

		[[nodiscard]] tuple<
			unique_ptr<RHI_Image>,
			unique_ptr<RHI_Image_View>,
			VmaAllocation>
			Create_Global_Image(
				RHI_Extent_2D Image_Extent,
				RHI_FORMAT Image_Format,
				uint32_t Mip_levels,
				void* Image_Pixels
			) override;

		[[nodiscard]] tuple<
			unique_ptr<RHI_Image>,
			unique_ptr<RHI_Image_View>,
			VmaAllocation>
			Create_Cube_Map(
				RHI_Extent_2D Image_Extent,
				RHI_FORMAT Image_Format,
				uint32_t Mip_levels,
				array<void*, 6> Image_Pixels
			) override;

		//NOTE : Memory
		void
			Map_Memory(
				RHI_Device_Memory* Memory,
				RHI_Device_Size Offset,
				RHI_Device_Size Size,
				RHI_Memopy_Map_Flags Flags,
				void** Data
			) override;

		void UnMap_Memory(RHI_Device_Memory* Memory) override;

		//NOTE : Sampler
		[[nodiscard]] virtual unique_ptr<RHI_Sampler>
			Create_Sampler(
				const RHI_Sampler_Create_Info* Create_Info
			) override;

		void Create_Default_Sampler(void) override;

		[[nodiscard]] RHI_Sampler* Get_Default_Sampler(RHI_DEFAULT_SAMPLER_TYPE Type) override;

		[[nodiscard]] RHI_Sampler*
			Get_Mipmap_Sampler(
				uint32_t Mip_Levels
			) override;

		[[nodiscard]] virtual unique_ptr<RHI_Render_Pass>
			Create_Render_Pass(
				const RHI_Render_Pass_Create_Info* Create_Info
			) override;

		[[nodiscard]] unique_ptr<RHI_Frame_Buffer>
			Create_Frame_Buffer(
				const RHI_Frame_buffer_Create_Info* Create_Info
			) override;

		[[nodiscard]] unique_ptr<RHI_Descriptor_Pool>
			Create_Descriptor_Pool(
				const RHI_Descriptor_Pool_Create_Info* Create_Info
			) override;

		void Create_Default_Descriptor_Pool(void) override;

		[[nodiscard]] unique_ptr<RHI_Descriptor_Set_Layout>
			Create_Descriptor_Set_Layout(
				const RHI_Descriptor_Set_Layout_Create_Info* Create_Info
			) override;

		[[nodiscard]] vector<unique_ptr<RHI_Descriptor_Set>>
			Allocate_Descriptor_Sets(
				const RHI_Descriptor_Set_Allocate_Info* Allocate_Info
			) override;

		void
			Update_Descriptor_Sets(
				const vector<const RHI_Write_Descriptor_Set*>* Descriptor_Writes,
				const vector<const RHI_Copy_Descriptor_Set*>* Descriptor_Copies
			) override;

		[[nodiscard]] unique_ptr<RHI_Shader_Module>
			Create_Shader_Module(
				const vector<unsigned char>* Shader_Code
			) override;

		[[nodiscard]] unique_ptr<RHI_Pipeline_Layout>
			Create_Pipeline_Layout(
				const RHI_Pipeline_Layout_Create_Info* Create_Info
			) override;

		[[nodiscard]] unique_ptr<RHI_Pipeline>
			Create_Graphics_Pipeline(
				const RHI_Graphics_Pipeline_Create_Info* Create_Info,
				RHI_Pipeline_Cache* Pipeline_Cache = nullptr
			) override;

		[[nodiscard]] virtual unique_ptr<RHI_Semaphore>
			Create_Semaphore(
				const RHI_Semaphore_Create_Info* Create_Info
			) override;

		[[nodiscard]] unique_ptr<RHI_Fence>
			Create_Fence(
				const RHI_Fence_Create_Info* Create_Info
			) override;

		void Create_Sync_Primitices(void)override;

		void Initialize(void) override;

		void Re_Create_SwapChain(void) override;

	private:




		bool Re_Set_Command_Pool_PFN(void);

		bool Wait_For_Fence(void);


	private:


		[[nodiscard]] static const optional<VkClearValue>
			Parser_RHI_Clear_Value(
				const RHI_Clear_Value* Clear_Value
			);








	private:


	private:



		bool Set_Buffer_Data(tuple<unique_ptr<RHI_Buffer>, unique_ptr<RHI_Device_Memory>> Buffer_And_Memory, RHI_Device_Size Offset, RHI_Device_Size Size, void* Data) override;

		//[[nodiscard]] unique_ptr<RHI_Buffer> Create_Buffer_With_Alignment_VMA(
		//	VmaAllocator Vma_Allocator,
		//	const RHI_Buffer_Create_Info& Buffer_Create_Info,
		//	const VmaAllocationCreateInfo* pAllocation_Create_Info,
		//	RHI_Device_Size Min_Alignment,
		//	VmaAllocation* pAllocation,
		//	VmaAllocationInfo* pAllocationInfo) override;


		[[nodiscard]] unique_ptr<RHI_Pipeline>
			Create_Compute_Pipeline(
				optional<RHI_Pipeline_Cache*> Pipeline_Cache,
				const RHI_Compute_Pipeline_Create_Info* pCreateInfos
			) override;



		bool
			Wait_For_Fences_PFN(
				const vector<RHI_Fence*> Fences,
				RHI_Bool32 Wait_All,
				uint64_t Time_Out
			) override;

		bool
			Wait_For_Fence_PFN(
				RHI_Fence* Fences,
				uint64_t Time_Out
			) override;

		bool
			Reset_Fences_PFN(
				vector<RHI_Fence*> Fences
			) override;


		bool
			Reset_Fence_PFN(
				RHI_Fence* Fence
			) override;

		bool
			Reset_Command_Pool_PFN(
				RHI_Command_Pool* Command_Pool,
				RHI_Command_Pool_Reset_Flags Flags
			) override;

		bool
			Begin_Command_Buffer_PFN(
				RHI_Command_Buffer* Command_Buffer,
				const RHI_Command_Buffer_Begin_Info* Begin_Command_Info
			) override;

		bool
			End_Command_Buffer_PFN(
				RHI_Command_Buffer* Command_Buffer
			) override;

		void
			Cmd_Begin_Render_Pass_PFN(
				RHI_Command_Buffer* Command_Buffer,
				const RHI_Render_Pass_Begin_Info* Render_Pass_Begin,
				RHI_SUBPASS_CONTENTS  Contents) override;

		void
			Cmd_Next_Subpass_PFN(
				RHI_Command_Buffer* Command_Buffer,
				RHI_SUBPASS_CONTENTS contents
			) override;

		void
			Cmd_End_Render_Pass_PFN(
				RHI_Command_Buffer* Command_Buffer
			) override;

		void
			Cmd_Bind_Pipeline_PFN(
				RHI_Command_Buffer* Command_Buffer,
				RHI_PEPELINE_BIND_POINT Pipeline_Bind_Point,
				RHI_Pipeline* Pipeline
			) override;

		void
			Cmd_Set_Viewports_PFN(
				RHI_Command_Buffer* Command_Buffer,
				uint32_t First_Viewport_Index,
				const vector<const RHI_Viewport*>* Viewports
			) override;

		void
			Cmd_Set_Viewport_PFN(
				RHI_Command_Buffer* Command_Buffer,
				const RHI_Viewport* Viewport
			) override;

		void
			Cmd_Set_Scissors_PFN(
				RHI_Command_Buffer* Command_Buffer,
				uint32_t First_Scissor_Index,
				const vector<const RHI_Rect_2D*>* Scissors
			) override;

		void
			Cmd_Set_Scissors_PFN(
				RHI_Command_Buffer* Command_Buffer,
				const RHI_Rect_2D* Scissors
			) override;

		void
			Cmd_Bind_Vertex_Buffers_PFN(
				RHI_Command_Buffer* Command_Buffer,
				uint32_t First_Binding_Index,
				const vector<RHI_Buffer*>* Buffers,
				const vector<RHI_Device_Size>* Offsets
			) override;

		void
			Cmd_Bind_Vertex_Buffer_PFN(
				RHI_Command_Buffer* Command_Buffer,
				RHI_Buffer* Buffers,
				RHI_Device_Size* Offsets
			) override;

		void
			Cmd_Bind_Index_Buffer_PFN(
				RHI_Command_Buffer* Command_Buffer,
				RHI_Buffer* Buffer,
				RHI_Device_Size Offset,
				RHI_INDEX_TYPE Index_Type
			) override;

		void
			Cmd_Bind_Descriptor_Sets_PFN(
				RHI_Command_Buffer* Command_Buffer,
				RHI_PEPELINE_BIND_POINT Pipeline_Bind_Point,
				RHI_Pipeline_Layout* Layout,
				uint32_t First_Set_Index,
				const vector<RHI_Descriptor_Set*>* Descriptor_Sets,
				const vector<uint32_t>* Dynamic_Offsets = nullptr
			) override;

		void
			Cmd_Bind_Descriptor_Set_PFN(
				RHI_Command_Buffer* Command_Buffer,
				RHI_PEPELINE_BIND_POINT Pipeline_Bind_Point,
				RHI_Pipeline_Layout* Layout,
				RHI_Descriptor_Set* Descriptor_Sets,
				const vector<uint32_t>* Dynamic_Offsets = nullptr
			) override;

		void
			Cmd_Draw_Indexed_PFN(
				RHI_Command_Buffer* Command_Buffer,
				uint32_t Index_Count,
				uint32_t Instance_Count,
				uint32_t First_Index,
				int32_t VertexOffset,
				uint32_t First_Instance
			) override;

		void Cmd_Clear_Attachments_PFN(
			RHI_Command_Buffer* Command_Buffer,
			const vector<const RHI_Clear_Attachment*>* Attachments,
			const vector<const RHI_Clear_Rect*>* Rects
		)override;

		void Cmd_Clear_Attachment_PFN(
			RHI_Command_Buffer* Command_Buffer,
			const RHI_Clear_Attachment* Attachment,
			const RHI_Clear_Rect* Rect
		) override;

		void
			Cmd_Copy_Image_To_Buffer(
				RHI_Command_Buffer* Command_Buffer,
				RHI_Image* Src_Image,
				RHI_IMAGE_LAYOUT Src_Image_Layout,
				RHI_Buffer* Dst_Buffer,
				const vector<const RHI_Buffer_Image_Copy*>* Regions
			) override;

		void
			Cmd_Copy_Image_X(
				RHI_Command_Buffer* Command_Buffer,
				RHI_Image* Src_Image,
				RHI_IMAGE_ASPECT_FLAG_BITS Src_Flag,
				RHI_Image* Dst_Image,
				RHI_IMAGE_ASPECT_FLAG_BITS Dst_Flag,
				RHI_Extent_2D Extent
			) override;


		void
			Cmd_Copy_Buffer(
				RHI_Command_Buffer* Command_Buffer,
				RHI_Buffer* Src_Buffer,
				RHI_Buffer* Dst_Buffer,
				const vector<const RHI_Buffer_Copy*>* Regions
			) override;


		void
			Cmd_Draw(
				RHI_Command_Buffer* Command_Buffer,
				uint32_t Vertex_Count,
				uint32_t Instance_Count,
				uint32_t First_Vertex_Index,
				uint32_t First_Instance_Index
			) override;

		void
			Cmd_Dispatch(
				RHI_Command_Buffer* Command_Buffer,
				uint32_t Group_Count_X,
				uint32_t Group_Count_Y,
				uint32_t Group_Count_Z
			) override;

		void
			Cmd_Dispatch_Indirect(
				RHI_Command_Buffer* Command_Buffer,
				RHI_Buffer* Buffer,
				RHI_Device_Size Offset
			) override;

		void
			Cmd_Pipeline_Barrier(
				RHI_Command_Buffer* Command_Buffer,
				RHI_Pipeline_Stage_Flags Src_Stage_Mask,
				RHI_Pipeline_Stage_Flags Dst_Stage_Mask,
				RHI_Dependency_Flags Dependency_Flags,
				const vector<const RHI_Memory_Barrier*>* Memory_Barriers,
				const vector<const RHI_Buffer_Memory_Barrier*>* Buffer_Memory_Barriers,
				const vector<const RHI_Image_Memory_Barrier*>* Image_Memory_Barriers
			) override;



		bool
			Queue_Submit(
				RHI_Queue* Queue,
				const vector<const RHI_Submit_Info*>* Submits,
				RHI_Fence* Fence
			) override;

		bool
			Queue_Wait_Idle(
				RHI_Queue* Queue
			) override;


	};

} // namespace NameSpace_Function::NameSpace_Render::NameSpace_RHI::NameSpace_Vulkan_RHI