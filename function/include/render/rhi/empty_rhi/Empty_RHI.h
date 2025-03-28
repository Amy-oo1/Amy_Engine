#pragma once

#include<tuple>
#include<array>
#include <vector>
#include <memory>

#include "vulkan/vulkan.h"
#include "vma/vk_mem_alloc.h"

#include "render/window/Window_System.h"

#include "render/rhi/empty_rhi/RHI_Type.h"
#include "render/rhi/empty_rhi/RHI_Class.h"
#include "render/rhi/empty_rhi/RHI_Struct.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_RHI {

	using std::tuple;
	using std::array;
	using std::vector;
	using std::unique_ptr;
	using std::shared_ptr;

	using  NameSpace_Render::NameSpace_Window::Window_System;

	struct RHI_Initialization_Info
	{
		shared_ptr<Window_System> Window_System;
	};

	class Empty_RHI {
	private:
		Empty_RHI(const Empty_RHI&) = delete;
		Empty_RHI& operator=(const Empty_RHI&) = delete;

	public:
		Empty_RHI(void) = default;

		virtual ~Empty_RHI() = default;



		virtual void Create_Instance(void) = 0;//NOTE : Instance Life Time Is The Same As The Application
		[[nodiscard]] virtual RHI_Instance* Get_Instance(void) const = 0;

		virtual void Create_Physical_Device(void) = 0;// NOTE : Physical Device Life Time Is The Same As The Application
		[[nodiscard]] virtual RHI_Physical_Device* Get_Physical_Device(void) const = 0;
		[[nodiscard]] virtual const RHI_FORMAT Get_Physical_Depth_Format(void) const = 0;

		[[nodiscard]] virtual const RHI_Physical_Device_Properties Get_Physical_Device_Properties(void) const = 0;

		virtual void Create_Logical_Device(void) = 0;// NOTE : Logical Device Life Time Is The Same As The Application
		[[nodiscard]] virtual RHI_Logical_Device* Get_Logical_Device(void) const = 0;

		[[nodiscard]] virtual RHI_Queue* Get_Graphics_Queue(void) const = 0;//Command Queue

		//NOTE : Command
		[[nodiscard]] virtual unique_ptr<RHI_Command_Pool>
			Create_Command_Pool(
				const RHI_Command_Pool_Create_Info* Create_Info) = 0;

		[[nodiscard]] virtual RHI_Descriptor_Pool* Get_Default_Descriptor_Pool(void)const = 0;

		[[nodiscard]] virtual const vector<unique_ptr<RHI_Command_Buffer>>
			Allocate_Command_Buffers(
				const RHI_Command_Buffer_Allocate_Info* Allocate_Info
			) = 0;

		[[nodiscard]] virtual tuple<
			unique_ptr<RHI_Buffer>,
			unique_ptr<RHI_Device_Memory>>
			Create_Buffer(
				RHI_Device_Size Size,
				RHI_Buffer_Usage_Flags Usage,
				RHI_Memory_Property_Flags Properties
			) = 0;

		[[nodiscard]] virtual tuple<
			unique_ptr<RHI_Buffer>,
			VmaAllocation>
			Create_Buffer_VMA(
				const RHI_Buffer_Create_Info* Buffer_Create_Info,
				const VmaAllocationCreateInfo* Allocation_Create_Info,
				VmaAllocationInfo* AllocationInfo
			) = 0;

		[[nodiscard]] virtual tuple<
			unique_ptr<RHI_Buffer>,
			VmaAllocation>
			Create_Buffer_Alignment_VMA(
				const RHI_Buffer_Create_Info* Buffer_Create_Info,
				const VmaAllocationCreateInfo* Allocation_Create_Info,
				VmaAllocationInfo* AllocationInfo,
				RHI_Device_Size Min_Alignment
			) = 0;

		virtual void
			Copy_Buffer(
				RHI_Buffer* Src_Buffer,
				RHI_Buffer* Dst_Buffer,
				RHI_Device_Size Src_Offset,
				RHI_Device_Size Dst_Offset,
				RHI_Device_Size Size
			) = 0;


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
			) = 0;

		[[nodiscard]] virtual unique_ptr<RHI_Image_View>
			Create_Image_View(
				RHI_Image* Image,
				RHI_FORMAT Format,
				uint32_t Mip_levels,
				uint32_t Layout_Count,
				RHI_IMAGE_VIEW_TYPE View_Type,
				RHI_Image_Aspect_Flags Image_Aspect_Flags
			) = 0;


		[[nodiscard]] virtual tuple<
			unique_ptr<RHI_Image>,
			unique_ptr<RHI_Image_View>,
			VmaAllocation>
			Create_Global_Image(
				RHI_Extent_2D Image_Extent,
				RHI_FORMAT Image_Format,
				uint32_t Mip_levels,
				void* Image_Pixels
			) = 0;

		[[nodiscard]] virtual tuple<
			unique_ptr<RHI_Image>,
			unique_ptr<RHI_Image_View>,
			VmaAllocation>
			Create_Cube_Map(
				RHI_Extent_2D Image_Extent,
				RHI_FORMAT Image_Format,
				uint32_t Mip_levels,
				array<void*, 6> Image_Pixels
			) = 0;



		//NOTE : Memory
		virtual void
			Map_Memory(
				RHI_Device_Memory* Memory,
				RHI_Device_Size Offset,
				RHI_Device_Size Size,
				RHI_Memopy_Map_Flags Flags,
				void** Data
			) = 0;

		virtual void UnMap_Memory(RHI_Device_Memory* Memory) = 0;

		//NOTE :Sampler
		[[nodiscard]] virtual unique_ptr<RHI_Sampler>
			Create_Sampler(
				const RHI_Sampler_Create_Info* Create_Info
			) = 0;

		[[nodiscard]] virtual RHI_Sampler*
			Get_Mipmap_Sampler(
				uint32_t Mip_Levels
			) = 0;

		[[nodiscard]] virtual unique_ptr<RHI_Render_Pass>
			Create_Render_Pass(
				const RHI_Render_Pass_Create_Info* Create_Info
			) = 0;

		[[nodiscard]] virtual unique_ptr<RHI_Frame_Buffer>
			Create_Frame_Buffer(
				const RHI_Frame_buffer_Create_Info* Create_Info
			) = 0;

		[[nodiscard]] virtual unique_ptr<RHI_Descriptor_Pool>
			Create_Descriptor_Pool(
				const RHI_Descriptor_Pool_Create_Info* Create_Info
			) = 0;

		[[nodiscard]] virtual unique_ptr<RHI_Descriptor_Set_Layout>
			Create_Descriptor_Set_Layout(
				const RHI_Descriptor_Set_Layout_Create_Info* Create_Info
			) = 0;

		[[nodiscard]] virtual vector<unique_ptr<RHI_Descriptor_Set>>
			Allocate_Descriptor_Sets(
				const RHI_Descriptor_Set_Allocate_Info* Allocate_Info
			) = 0;

		virtual void
			Update_Descriptor_Sets(
				const vector<const RHI_Write_Descriptor_Set*>* Descriptor_Writes,
				const vector<const RHI_Copy_Descriptor_Set*>* Descriptor_Copies
			) = 0;

		[[nodiscard]] virtual unique_ptr<RHI_Shader_Module>
			Create_Shader_Module(
				const vector<unsigned char>* Shader_Code
			) = 0;

		[[nodiscard]] virtual unique_ptr<RHI_Pipeline_Layout>
			Create_Pipeline_Layout(
				const RHI_Pipeline_Layout_Create_Info* Create_Info
			) = 0;

		[[nodiscard]] virtual unique_ptr<RHI_Pipeline>
			Create_Graphics_Pipeline(
				const RHI_Graphics_Pipeline_Create_Info* Create_Info,
				RHI_Pipeline_Cache* Pipeline_Cache = nullptr
			) = 0;







		virtual void Run(void) = 0;

		virtual void CleanUp_SwapChain(void) = 0;
		virtual void Re_Create_SwapChain(void) = 0;


	private:

		virtual void Create_SwapChain(void) = 0;

		virtual void Create_SwapChhain_Image_Views(void) = 0;

		//TODO : Add SwapChain Image Depth Image View

		[[nodiscard]] virtual const unique_ptr<RHI_Sampler>& Get_Default_Sampler(RHI_DEFAULT_SAMPLER_TYPE Type) = 0;

		virtual bool Set_Buffer_Data(tuple<unique_ptr<RHI_Buffer>, unique_ptr<RHI_Device_Memory>> Buffer_And_Memory, RHI_Device_Size Offset, RHI_Device_Size Size, void* Data) = 0;

		[[nodiscard]] virtual unique_ptr<RHI_Command_Buffer> Begin_SingleTime_Commands(void) = 0;
		virtual void End_SingleTime_Commands(unique_ptr<RHI_Command_Buffer> Command_Buffer) = 0;



		//TODO : 


		[[nodiscard]] virtual unique_ptr<RHI_Fence>
			Create_Fence(const RHI_Fence_Create_Info pCreateInfo) = 0;



		[[nodiscard]] virtual unique_ptr<RHI_Pipeline>
			Create_Compute_Pipeline(
				optional<RHI_Pipeline_Cache*> Pipeline_Cache,
				const RHI_Compute_Pipeline_Create_Info* pCreateInfos
			) = 0;


		[[nodiscard]] virtual unique_ptr<RHI_Semaphore>
			Create_Semaphore(const RHI_Semaphore_Create_Info* Create_Info
			) = 0;

		virtual bool
			Wait_For_Fences_PFN(
				const vector<RHI_Fence*> Fences,
				RHI_Bool32 Wait_All,
				uint64_t Time_Out
			) = 0;

		virtual bool
			Wait_For_Fence_PFN(
				RHI_Fence* Fences,
				uint64_t Time_Out
			) = 0;

		virtual bool
			Reset_Fences_PFN(
				vector<RHI_Fence*> Fences
			) = 0;

		virtual bool
			Reset_Fence_PFN(
				RHI_Fence* Fence
			) = 0;

		virtual bool
			Reset_Command_Pool_PFN(
				RHI_Command_Pool* Command_Pool,
				RHI_Command_Pool_Reset_Flags Flags
			) = 0;

		virtual bool
			Begin_Command_Buffer_PFN(
				RHI_Command_Buffer* Command_Buffer,
				const RHI_Command_Buffer_Begin_Info* Begin_Command_Info
			) = 0;

		virtual bool
			End_Command_Buffer_PFN(
				RHI_Command_Buffer* Command_Buffer
			) = 0;

		virtual void
			Cmd_Begin_Render_Pass_PFN(
				RHI_Command_Buffer* Command_Buffer,
				const RHI_Render_Pass_Begin_Info* Render_Pass_Begin,
				RHI_SUBPASS_CONTENTS  Contents) = 0;

		virtual void
			Cmd_Next_Subpass_PFN(
				RHI_Command_Buffer* Command_Buffer,
				RHI_SUBPASS_CONTENTS contents
			) = 0;


		virtual void
			Cmd_End_Render_Pass_PFN(
				RHI_Command_Buffer* Command_Buffer
			) = 0;

		virtual void
			Cmd_Bind_Pipeline_PFN(
				RHI_Command_Buffer* Command_Buffer,
				RHI_PEPELINE_BIND_POINT Pipeline_Bind_Point,
				RHI_Pipeline* Pipeline
			) = 0;

		virtual void
			Cmd_Set_Viewports_PFN(
				RHI_Command_Buffer* Command_Buffer,
				uint32_t First_Viewport_Index,
				const vector<const RHI_Viewport*>* Viewports
			) = 0;

		virtual void
			Cmd_Set_Viewport_PFN(
				RHI_Command_Buffer* Command_Buffer,
				const RHI_Viewport* Viewport
			) = 0;

		virtual void
			Cmd_Set_Scissors_PFN(
				RHI_Command_Buffer* Command_Buffer,
				uint32_t First_Scissor_Index,
				const vector<const RHI_Rect_2D*>* Scissors
			) = 0;

		virtual void
			Cmd_Set_Scissors_PFN(
				RHI_Command_Buffer* Command_Buffer,
				const RHI_Rect_2D* Scissors
			) = 0;

		virtual void
			Cmd_Bind_Vertex_Buffers_PFN(
				RHI_Command_Buffer* Command_Buffer,
				uint32_t First_Binding_Index,
				const vector<RHI_Buffer*>* Buffers,
				const vector<RHI_Device_Size>* Offsets
			) = 0;

		virtual void
			Cmd_Bind_Vertex_Buffer_PFN(
				RHI_Command_Buffer* Command_Buffer,
				RHI_Buffer* Buffers,
				RHI_Device_Size* Offsets
			) = 0;

		virtual void
			Cmd_Bind_Index_Buffer_PFN(
				RHI_Command_Buffer* Command_Buffer,
				RHI_Buffer* Buffer,
				RHI_Device_Size Offset,
				RHI_INDEX_TYPE Index_Type
			) = 0;

		virtual void
			Cmd_Bind_Descriptor_Sets_PFN(
				RHI_Command_Buffer* Command_Buffer,
				RHI_PEPELINE_BIND_POINT Pipeline_Bind_Point,
				RHI_Pipeline_Layout* Layout,
				uint32_t First_Set_Index,
				const vector<RHI_Descriptor_Set*>* Descriptor_Sets,
				const vector<uint32_t>* Dynamic_Offsets = nullptr
			) = 0;

		virtual void
			Cmd_Bind_Descriptor_Set_PFN(
				RHI_Command_Buffer* Command_Buffer,
				RHI_PEPELINE_BIND_POINT Pipeline_Bind_Point,
				RHI_Pipeline_Layout* Layout,
				RHI_Descriptor_Set* Descriptor_Sets,
				const vector<uint32_t>* Dynamic_Offsets = nullptr
			) = 0;


		virtual void
			Cmd_Draw_Indexed_PFN(
				RHI_Command_Buffer* Command_Buffer,
				uint32_t Index_Count,
				uint32_t Instance_Count,
				uint32_t First_Index,
				int32_t VertexOffset,
				uint32_t First_Instance
			) = 0;

		virtual void Cmd_Clear_Attachments_PFN(
			RHI_Command_Buffer* Command_Buffer,
			const vector<const RHI_Clear_Attachment*>* Attachments,
			const vector<const RHI_Clear_Rect*>* Rects
		) = 0;

		virtual void Cmd_Clear_Attachment_PFN(
			RHI_Command_Buffer* Command_Buffer,
			const RHI_Clear_Attachment* Attachment,
			const RHI_Clear_Rect* Rect
		) = 0;

		virtual void
			Cmd_Copy_Image_To_Buffer(
				RHI_Command_Buffer* Command_Buffer,
				RHI_Image* Src_Image,
				RHI_IMAGE_LAYOUT Src_Image_Layout,
				RHI_Buffer* Dst_Buffer,
				const vector<const RHI_Buffer_Image_Copy*>* Regions
			) = 0;




		virtual void
			Cmd_Copy_Image_X(
				RHI_Command_Buffer* Command_Buffer,
				RHI_Image* Src_Image,
				RHI_IMAGE_ASPECT_FLAG_BITS Src_Flag,
				RHI_Image* Dst_Image,
				RHI_IMAGE_ASPECT_FLAG_BITS Dst_Flag,
				RHI_Extent_2D Extent
			) = 0;


		virtual void
			Cmd_Copy_Buffer(
				RHI_Command_Buffer* Command_Buffer,
				RHI_Buffer* Src_Buffer,
				RHI_Buffer* Dst_Buffer,
				const vector<const RHI_Buffer_Copy*>* Regions
			) = 0;

		virtual void
			Cmd_Draw(
				RHI_Command_Buffer* Command_Buffer,
				uint32_t Vertex_Count,
				uint32_t Instance_Count,
				uint32_t First_Vertex_Index,
				uint32_t First_Instance_Index
			) = 0;

		virtual void
			Cmd_Dispatch(
				RHI_Command_Buffer* Command_Buffer,
				uint32_t Group_Count_X,
				uint32_t Group_Count_Y,
				uint32_t Group_Count_Z
			) = 0;

		virtual void
			Cmd_Dispatch_Indirect(
				RHI_Command_Buffer* Command_Buffer,
				RHI_Buffer* Buffer,
				RHI_Device_Size Offset
			) = 0;

		virtual void
			Cmd_Pipeline_Barrier(
				RHI_Command_Buffer* Command_Buffer,
				RHI_Pipeline_Stage_Flags Src_Stage_Mask,
				RHI_Pipeline_Stage_Flags Dst_Stage_Mask,
				RHI_Dependency_Flags Dependency_Flags,
				const vector<const RHI_Memory_Barrier*>* Memory_Barriers,
				const vector<const RHI_Buffer_Memory_Barrier*>* Buffer_Memory_Barriers,
				const vector<const RHI_Image_Memory_Barrier*>* Image_Memory_Barriers
			) = 0;


		virtual bool
			Queue_Submit(
				RHI_Queue* Queue,
				const vector<const RHI_Submit_Info*>* Submits,
				RHI_Fence* Fence
			) = 0;


		virtual bool
			Queue_Wait_Idle(
				RHI_Queue* Queue
			) = 0;

	};
} // namespace NameSpace_Function::NameSpace_Render::NameSpace_RHI::NameSpace_Vulkan_RHI
