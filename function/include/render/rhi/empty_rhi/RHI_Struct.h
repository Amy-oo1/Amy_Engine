#pragma once

#include<cstdint>
#include<tuple>
#include <optional>
#include<vector>
#include<array>
#include<memory>

#include "vulkan/vulkan.h"

#include "render/rhi/empty_rhi/RHI_Macro.h"
#include "render/rhi/empty_rhi/RHI_Type.h"
#include "render/rhi/empty_rhi/RHI_Class.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_RHI {

	using std::array;
	using std::vector;
	using std::unique_ptr;// TODO : Remove Unique_ptr
	using std::optional;// TODO : Use Optional
	using std::tuple;//TODO : Remove Tuple

	struct RHI_Extent_3D {
		uint32_t Width;
		uint32_t Height;
		uint32_t Depth;

		operator VkExtent3D() const {//TODO : Remove
			return VkExtent3D{ Width,Height,Depth };
		}
	};

	struct RHI_Offset_2D {
		int32_t X;
		int32_t Y;
	};
	struct RHI_Offset_3D {
		int32_t X;
		int32_t Y;
		int32_t Z;
	};

	struct RHI_Extent_2D {
		uint32_t Width;
		uint32_t Height;

		explicit operator RHI_Extent_3D() const {// TODO : Remove
			return RHI_Extent_3D{ Width,Height,1 };
		}

		operator VkExtent2D() const {// TODO : Remove
			return VkExtent2D{ Width,Height };
		}
	};

	struct RHI_Rect_2D {
		RHI_Offset_2D Offset;
		RHI_Extent_2D Extent;
	};
	struct RHI_Viewport {
		float X;
		float Y;
		float Width;
		float Height;
		float Min_Depth;
		float Max_Depth;
	};

	struct RHI_Command_Buffer_Allocate_Info final {
		RHI_STRUCT_TYPE sType;
		const void* pNext;
		RHI_Command_Pool* Command_Pool;
		RHI_COMMAND_BUFFER_LEVEL Level;
		uint32_t Command_Buffer_Count;
	};

	struct  RHI_Descriptor_Set_Allocate_Info final {
		RHI_STRUCT_TYPE sType;
		const void* pNext;
		RHI_Descriptor_Pool* Descriptor_Pool;
		const vector<RHI_Descriptor_Set_Layout*>* Set_Layouts;
	};

	struct RHI_Buffer_Create_Info final {
		RHI_STRUCT_TYPE sType;
		const void* pNext;
		RHI_Buffer_Create_Flags Flags;
		RHI_Device_Size Size;
		RHI_Buffer_Usage_Flags Usage;
		RHI_SHARING_MODE Sharing_Mode;
		uint32_t Queue_Family_Index_Count;
		const uint32_t* pQueue_Family_Indices;
	};

	struct RHI_Command_Pool_Create_Info final {
		RHI_STRUCT_TYPE sType;
		const void* pNext;
		RHI_Command_Pool_Create_Flags Flags;
		uint32_t Queue_Family_Index;

	};

	struct RHI_Descriptor_Pool_Size final {
		RHI_DESCRIPTOR_TYPE Type;
		uint32_t Descriptor_Count;
	};

	struct RHI_Descriptor_Pool_Create_Info final {
		RHI_STRUCT_TYPE sType;
		const void* pNext;
		RHI_Descriptor_Pool_Create_Flags Flags;
		uint32_t Max_Sets;
		const vector<const RHI_Descriptor_Pool_Size*>* Pool_Sizes;
	};

	struct RHI_Descriptor_Set_Layout_Binding final {
		uint32_t Binding;
		RHI_DESCRIPTOR_TYPE Descriptor_Type;
		uint32_t Descriptor_Count;
		RHI_Shader_Stage_Flags Stage_Flags;
		vector<RHI_Sampler*>* Immutable_Samplers;
	};

	struct RHI_Descriptor_Set_Layout_Create_Info final {
		RHI_STRUCT_TYPE sType;
		const void* pNext;
		RHI_Descriptor_Set_Layout_Create_Flags Flags;
		const vector<const RHI_Descriptor_Set_Layout_Binding*>* Bindings;
	};

	struct RHI_Fence_Create_Info final {
		RHI_STRUCT_TYPE sType;
		const void* pNext;
		RHI_Fence_Create_Flags Flags;
	};

	struct RHI_Frame_buffer_Create_Info final {
		RHI_STRUCT_TYPE sType;
		const void* pNext;
		RHI_Frame_Buffer_Create_Flags Flags;
		RHI_Render_Pass* Render_Pass;
		const vector<RHI_Image_View*>* Attachments;
		uint32_t Width;
		uint32_t Height;
		uint32_t Layers;
	};

	struct RHI_Specialization_Map_Entry {
		uint32_t Constant_ID;
		uint32_t Offset;
		size_t Size;
	};

	struct RHI_Specialization_Info {
		const vector<const RHI_Specialization_Map_Entry*>* Map_Entries;
		size_t Data_Size;
		const void* Data;
	};

	struct RHI_Vertex_Input_Binding_Description {
		uint32_t Binding;
		uint32_t Stride;
		RHI_VERTEX_INPUT_RATE Input_Rate;
	};

	struct RHI_Pipeline_Shader_Stage_Create_Info {
		RHI_STRUCT_TYPE sType;
		const void* pNext;
		RHI_Pipeline_Shader_Stage_Create_Flags Flags;
		RHI_SHADER_STAGE_FLAG_BITS Stage;
		RHI_Shader_Module* Module;
		const char* Name;
		const RHI_Specialization_Info* Specialization_Info;
	};

	struct RHI_Vertex_Input_Attribute_Description {
		uint32_t Location;
		uint32_t Binding;
		RHI_FORMAT Format;
		uint32_t Offset;
	};

	struct RHI_Pipeline_Vertex_Input_State_Create_Info {
		RHI_STRUCT_TYPE sType;
		const void* pNext;
		RHI_Pipeline_Vertex_Input_State_Create_Flags Flags;
		const vector<const RHI_Vertex_Input_Binding_Description*>* Vertex_Binding_Descriptions;
		const vector<const RHI_Vertex_Input_Attribute_Description*>* Vertex_Attribute_Descriptions;
	};

	struct RHI_Pipeline_Input_Assembly_State_Create_Info {
		RHI_STRUCT_TYPE sType;
		const void* pNext;
		RHI_Pipeline_Input_Assembly_State_Create_Flags Flags;
		RHI_PRIMITIVE_TOPOLOGY Topology;
		RHI_Bool32 Primitive_Restart_Enable;
	};

	struct RHI_Pipeline_Tessellation_State_Create_Info {
		RHI_STRUCT_TYPE sType;
		const void* pNext;
		RHI_Pipeline_Tessellation_State_Create_Flags Flags;
		uint32_t Patch_Control_Points;
	};

	struct RHI_Pipeline_Viewport_State_Create_Info {
		RHI_STRUCT_TYPE sType;
		const void* pNext;
		RHI_Pipeline_Viewport_State_Create_Flags Flags;
		const vector<const RHI_Viewport*>* Viewports;
		const vector<const RHI_Rect_2D*>* Scissors;
	};

	struct RHI_Pipeline_Rasterization_State_Create_Info {
		RHI_STRUCT_TYPE sType;
		const void* pNext;
		RHI_Pipeline_Rasterization_State_Create_Flags Flags;
		RHI_Bool32 Depth_Clamp_Enable;
		RHI_Bool32 Rasterizer_Discard_Enable;
		RHI_POLYGON_MODE Polygon_Mode;
		RHI_Cull_Mode_Flags Cull_Mode;
		RHI_FRONT_FACE Front_Face;
		RHI_Bool32 Depth_Bias_Enable;
		float Depth_Bias_Constant_Factor;
		float Depth_Bias_Clamp;
		float Depth_Bias_Slope_Factor;
		float Line_Width;
	};

	struct RHI_Pipeline_Multisample_State_Create_Info {
		RHI_STRUCT_TYPE sType;
		const void* pNext;
		RHI_Pipeline_Multisample_State_Create_Flags Flags;
		RHI_SAMPLE_COUNT_FLAG_BIT Rasterization_Samples;
		RHI_Bool32 Sample_Shading_Enable;
		float Min_Sample_Shading;
		const RHI_Sample_Mask* Sample_Mask;
		RHI_Bool32 Alpha_To_Coverage_Enable;
		RHI_Bool32 Alpha_To_One_Enable;
	};

	struct RHI_Stencil_Op_State {
		RHI_STENCIL_OP Fail_Op;
		RHI_STENCIL_OP Pass_Op;
		RHI_STENCIL_OP Depth_Fail_Op;
		RHI_COMPARE_OP Compare_Op;
		uint32_t Compare_Mask;
		uint32_t Write_Mask;
		uint32_t Reference;
	};

	struct RHI_Pipeline_Depth_Stencil_State_Create_Info {
		RHI_STRUCT_TYPE sType;
		const void* pNext;
		RHI_Pipeline_Depth_Stencil_State_Create_Flags Flags;
		RHI_Bool32 Depth_Test_Enable;
		RHI_Bool32 Depth_Write_Enable;
		RHI_COMPARE_OP Depth_Compare_Op;
		RHI_Bool32 Depth_Bounds_Test_Enable;
		RHI_Bool32 Stencil_Test_Enable;
		RHI_Stencil_Op_State Front;
		RHI_Stencil_Op_State Back;
		float Min_Depth_Bounds;
		float Max_Depth_Bounds;
	};

	struct RHI_Pipeline_Color_Blend_Attachment_State {
		RHI_Bool32 Blend_Enable;
		RHI_BLEND_FACTOR Src_Color_Blend_Factor;
		RHI_BLEND_FACTOR Dst_Color_Blend_Factor;
		RHI_BLEND_OP Color_Blend_Op;
		RHI_BLEND_FACTOR Src_Alpha_Blend_Factor;
		RHI_BLEND_FACTOR Dst_Alpha_Blend_Factor;
		RHI_BLEND_OP Alpha_Blend_Op;
		RHI_Color_Component_Flags Color_Write_Mask;
	};

	struct RHI_Pipeline_Color_Blend_State_Create_Info {
		RHI_STRUCT_TYPE sType;
		const void* pNext;
		RHI_Pipeline_Color_Blend_State_Create_Flags Flags;
		RHI_Bool32 Logic_Op_Enable;
		RHI_LOGIC_OP Logic_Op;
		const vector<const RHI_Pipeline_Color_Blend_Attachment_State*>* Attachments;
		std::array<float, 4> Blend_Constants;
	};

	struct RHI_Pipeline_Dynamic_State_Create_Info {
		RHI_STRUCT_TYPE sType;
		const void* pNext;
		RHI_Pipeline_Dynamic_State_Create_Flags Flags;
		const vector<RHI_DYNAMIC_STATE>* Dynamic_States;
	};

	struct RHI_Graphics_Pipeline_Create_Info {
		RHI_STRUCT_TYPE sType;
		const void* pNext;
		RHI_Graphics_Pipeline_Create_Flags Flags;
		const vector<const RHI_Pipeline_Shader_Stage_Create_Info*>* Stages;
		const RHI_Pipeline_Vertex_Input_State_Create_Info* Vertex_Input_State;
		const RHI_Pipeline_Input_Assembly_State_Create_Info* Input_Assembly_State;
		const RHI_Pipeline_Tessellation_State_Create_Info* Tessellation_State;
		const RHI_Pipeline_Viewport_State_Create_Info* Viewport_State;
		const RHI_Pipeline_Rasterization_State_Create_Info* Rasterization_State;
		const RHI_Pipeline_Multisample_State_Create_Info* Multisample_State;
		const RHI_Pipeline_Depth_Stencil_State_Create_Info* Depth_Stencil_State;
		const RHI_Pipeline_Color_Blend_State_Create_Info* Color_Blend_State;
		const RHI_Pipeline_Dynamic_State_Create_Info* Dynamic_State;
		RHI_Pipeline_Layout* Layout;
		RHI_Render_Pass* Render_Pass;
		uint32_t Subpass;
		RHI_Pipeline* Base_Pipeline_Handle;
		int32_t Base_Pipeline_Index;
	};

	struct RHI_Compute_Pipeline_Create_Info final {
		RHI_STRUCT_TYPE sType;
		const void* pNext;
		RHI_Compute_Pipeline_Create_Flags Flags;
		const RHI_Pipeline_Shader_Stage_Create_Info* Stage;
		RHI_Pipeline_Layout* Layout;
		RHI_Pipeline* Base_Pipeline_Handle;
		int32_t Base_Pipeline_Index;
	};

	struct RHI_Push_Constant_Range final {
		RHI_Shader_Stage_Flags Stage_Flags;
		uint32_t Offset;
		uint32_t Size;
	};

	struct RHI_Pipeline_Layout_Create_Info final {
		RHI_STRUCT_TYPE sType;
		const void* pNext;
		RHI_Pipeline_Layout_Create_Flags Flags;
		vector<RHI_Descriptor_Set_Layout*>* Set_Layouts;
		const vector<const RHI_Push_Constant_Range*>* Push_Constant_Ranges;
	};

	struct RHI_Attachment_Description final {
		RHI_Attachment_Description_Flags Flags;
		RHI_FORMAT Format;
		RHI_SAMPLE_COUNT_FLAG_BIT Samples;
		RHI_ATTACHMENT_LOAD_OP Load_Op;
		RHI_ATTACHMENT_STORE_OP Store_Op;
		RHI_ATTACHMENT_LOAD_OP Stencil_Load_Op;
		RHI_ATTACHMENT_STORE_OP Stencil_Store_Op;
		RHI_IMAGE_LAYOUT Initial_Layout;
		RHI_IMAGE_LAYOUT Final_Layout;
	};

	struct RHI_Attachment_Reference final {
		uint32_t Attachment;
		RHI_IMAGE_LAYOUT Layout;
	};

	struct RHI_Subpass_Description final {
		RHI_Subpass_Description_Flags Flags;
		RHI_PIPELINE_BIND_POINT Pipeline_Bind_Point;
		const vector<const RHI_Attachment_Reference*>* Input_Attachments;
		const vector<const RHI_Attachment_Reference*>* Color_Attachments;
		const vector<const RHI_Attachment_Reference*>* Resolve_Attachments;
		const RHI_Attachment_Reference* Depth_Stencil_Attachment;
		const vector<uint32_t>* Preserve_Attachments;
	};

	struct RHI_Subpass_Dependency final {
		uint32_t Src_Subpass;
		uint32_t Dst_Subpass;
		RHI_Pipeline_Stage_Flags Src_Stage_Mask;
		RHI_Pipeline_Stage_Flags Dst_Stage_Mask;
		RHI_Access_Flags Src_Access_Mask;
		RHI_Access_Flags Dst_Access_Mask;
		RHI_Dependency_Flags Dependency_Flags;
	};

	struct RHI_Render_Pass_Create_Info final {
		RHI_STRUCT_TYPE sType;
		const void* pNext;
		RHI_Render_Pass_Create_Flags Flags;
		const vector<const RHI_Attachment_Description*>* Attachments;
		const vector<const RHI_Subpass_Description*>* Subpasses;
		const vector<const RHI_Subpass_Dependency*>* Dependencies;
	};

	struct RHI_Sampler_Create_Info final {
		RHI_STRUCT_TYPE sType;
		const void* pNext;
		RHI_Sampler_Create_Flags Flags;
		RHI_FILTER Mag_Filter;
		RHI_FILTER Min_Filter;
		RHI_SAMPLER_MIPMAP_MODE Mipmap_Mode;
		RHI_SAMPLER_ADDRESS_MODE Address_Mode_U;
		RHI_SAMPLER_ADDRESS_MODE Address_Mode_V;
		RHI_SAMPLER_ADDRESS_MODE Address_Mode_W;
		float Mip_Lod_Bias;
		RHI_Bool32 Anisotropy_Enable;
		float Max_Anisotropy;
		RHI_Bool32 Compare_Enable;
		RHI_COMPARE_OP Compare_Op;
		float Min_Lod;
		float Max_Lod;
		RHI_BORDER_COLOR Border_Color;
		RHI_Bool32 Unnormalized_Coordinates;
	};

	struct RHI_Semaphore_Create_Info final {
		RHI_STRUCT_TYPE sType;
		const void* pNext;
		RHI_Semaphore_Create_Flags Flags;
	};

	struct RHI_Command_Buffer_Inheritance_Info final {
		RHI_STRUCT_TYPE sType;
		const void* pNext;
		RHI_Render_Pass* Render_Pass;
		uint32_t Subpass;
		RHI_Frame_Buffer* Frame_Buffer;
		RHI_Bool32 Occlusion_Query_Enable;
		RHI_Query_Control_Flags Query_Flags;
		RHI_Query_Pipeline_Statistic_Flags Pipeline_Statistics;
	};

	struct RHI_Command_Buffer_Begin_Info final {
		RHI_STRUCT_TYPE sType;
		const void* pNext;
		RHI_Command_Buffer_Begin_Flags Flags;
		const RHI_Command_Buffer_Inheritance_Info* Inheritance_Info;
	};

	struct RHI_Clear_Color_Value {
		optional<array<float, 4>> Float32;
		optional<array<int32_t, 4>> Int32;
		optional<array<uint32_t, 4>> Uint32;
	};

	struct RHI_Clear_Depth_Stencil_Value final {
		float Depth;
		uint32_t Stencil;
	};

	struct RHI_Clear_Value {
		optional<RHI_Clear_Color_Value> Color;
		optional<RHI_Clear_Depth_Stencil_Value> Depth_Stencil;
	};;

	struct RHI_Render_Pass_Begin_Info final {
		RHI_STRUCT_TYPE sType;
		const void* pNext;
		RHI_Render_Pass* Render_Pass;
		RHI_Frame_Buffer* Frame_Buffer;
		RHI_Rect_2D Render_Area;
		const vector<const RHI_Clear_Value*>* Clear_Values;
	};

	struct RHI_Clear_Attachment final {
		RHI_Image_Aspect_Flags Aspect_Mask;
		uint32_t Color_Attachment;
		RHI_Clear_Value Clear_Value;
	};

	struct RHI_Clear_Rect final {
		RHI_Rect_2D Rect;
		uint32_t Base_Array_Layer;
		uint32_t Layer_Count;
	};

	struct RHI_Image_Subresource_Layers final {
		RHI_Image_Aspect_Flags Aspect_Mask;
		uint32_t Mip_Level;
		uint32_t Base_Array_Layer;
		uint32_t Layer_Count;
	};

	struct RHI_Buffer_Image_Copy final {
		RHI_Device_Size Buffer_Offset;
		uint32_t Buffer_Row_Length;
		uint32_t Buffer_Image_Height;
		RHI_Image_Subresource_Layers Image_Subresource;
		RHI_Offset_3D Image_Offset;
		RHI_Extent_3D Image_Extent;
	};

	struct RHI_Buffer_Copy final {
		RHI_Device_Size Src_Offset;
		RHI_Device_Size Dst_Offset;
		RHI_Device_Size Size;
	};

	struct RHI_Memory_Barrier final {
		RHI_STRUCT_TYPE sType;
		const void* pNext;
		RHI_Access_Flags Src_Access_Mask;
		RHI_Access_Flags Dst_Access_Mask;
	};

	struct RHI_Buffer_Memory_Barrier final {
		RHI_STRUCT_TYPE sType;
		const void* pNext;
		RHI_Access_Flags Src_Access_Mask;
		RHI_Access_Flags Dst_Access_Mask;
		uint32_t Src_Queue_Family_Index;
		uint32_t Dst_Queue_Family_Index;
		RHI_Buffer* Buffer;
		RHI_Device_Size Offset;
		RHI_Device_Size Size;
	};

	struct RHI_Image_Subresource_Ranges final {
		RHI_Image_Aspect_Flags Aspect_Mask;
		uint32_t Base_Mip_Level;
		uint32_t Level_Count;
		uint32_t Base_Array_Layer;
		uint32_t Layer_Count;
	};

	struct RHI_Image_Memory_Barrier final {
		RHI_STRUCT_TYPE sType;
		const void* pNext;
		RHI_Access_Flags Src_Access_Mask;
		RHI_Access_Flags Dst_Access_Mask;
		RHI_IMAGE_LAYOUT Old_Layout;
		RHI_IMAGE_LAYOUT New_Layout;
		uint32_t Src_Queue_Family_Index;
		uint32_t Dst_Queue_Family_Index;
		RHI_Image* Image;
		RHI_Image_Subresource_Ranges SubResource_Ranges;
	};

	struct RHI_Descriptor_Image_Info final {
		RHI_Sampler* Sampler;
		RHI_Image_View* Image_View;
		RHI_IMAGE_LAYOUT Image_Layout;
	};

	struct RHI_Descriptor_Buffer_Info final {
		RHI_Buffer* Buffer;
		RHI_Device_Size Offset;
		RHI_Device_Size Range;
	};

	struct RHI_Write_Descriptor_Set final {
		RHI_STRUCT_TYPE sType;
		const void* pNext;
		RHI_Descriptor_Set* Dst_Set;
		uint32_t Dst_Binding;
		uint32_t Dst_Array_Element;
		RHI_DESCRIPTOR_TYPE Descriptor_Type;
		const vector<const RHI_Descriptor_Image_Info*>* Image_Infos;
		const vector<const RHI_Descriptor_Buffer_Info*>* Buffer_Infos;
		const vector<RHI_Buffer_View*>* Texel_Buffer_Views;
	};

	struct RHI_Copy_Descriptor_Set final {
		RHI_STRUCT_TYPE sType;
		const void* pNext;
		RHI_Descriptor_Set* Src_Set;
		uint32_t Src_Binding;
		uint32_t Src_Array_Element;
		RHI_Descriptor_Set* Dst_Set;
		uint32_t Dst_Binding;
		uint32_t Dst_Array_Element;
		uint32_t Descriptor_Count;
	};

	struct RHI_Submit_Info final {
		RHI_STRUCT_TYPE sType;
		const void* pNext;
		const vector<RHI_Semaphore*>* Wait_Semaphores;
		const vector<RHI_Pipeline_Stage_Flags>* Wait_Dst_Stage_Masks;
		const vector<RHI_Command_Buffer*>* Command_Buffers;
		const vector<RHI_Semaphore*>* Signal_Semaphores;
	};

	struct RHI_Physical_Device_Limits final {
		uint32_t maxImageDimension1D;
		uint32_t maxImageDimension2D;
		uint32_t maxImageDimension3D;
		uint32_t maxImageDimensionCube;
		uint32_t maxImageArrayLayers;
		uint32_t maxTexelBufferElements;
		uint32_t maxUniformBufferRange;
		uint32_t maxStorageBufferRange;
		uint32_t maxPushConstantsSize;
		uint32_t maxMemoryAllocationCount;
		uint32_t maxSamplerAllocationCount;
		RHI_Device_Size bufferImageGranularity;
		RHI_Device_Size sparseAddressSpaceSize;
		uint32_t maxBoundDescriptorSets;
		uint32_t maxPerStageDescriptorSamplers;
		uint32_t maxPerStageDescriptorUniformBuffers;
		uint32_t maxPerStageDescriptorStorageBuffers;
		uint32_t maxPerStageDescriptorSampledImages;
		uint32_t maxPerStageDescriptorStorageImages;
		uint32_t maxPerStageDescriptorInputAttachments;
		uint32_t maxPerStageResources;
		uint32_t maxDescriptorSetSamplers;
		uint32_t maxDescriptorSetUniformBuffers;
		uint32_t maxDescriptorSetUniformBuffersDynamic;
		uint32_t maxDescriptorSetStorageBuffers;
		uint32_t maxDescriptorSetStorageBuffersDynamic;
		uint32_t maxDescriptorSetSampledImages;
		uint32_t maxDescriptorSetStorageImages;
		uint32_t maxDescriptorSetInputAttachments;
		uint32_t maxVertexInputAttributes;
		uint32_t maxVertexInputBindings;
		uint32_t maxVertexInputAttributeOffset;
		uint32_t maxVertexInputBindingStride;
		uint32_t maxVertexOutputComponents;
		uint32_t maxTessellationGenerationLevel;
		uint32_t maxTessellationPatchSize;
		uint32_t maxTessellationControlPerVertexInputComponents;
		uint32_t maxTessellationControlPerVertexOutputComponents;
		uint32_t maxTessellationControlPerPatchOutputComponents;
		uint32_t maxTessellationControlTotalOutputComponents;
		uint32_t maxTessellationEvaluationInputComponents;
		uint32_t maxTessellationEvaluationOutputComponents;
		uint32_t maxGeometryShaderInvocations;
		uint32_t maxGeometryInputComponents;
		uint32_t maxGeometryOutputComponents;
		uint32_t maxGeometryOutputVertices;
		uint32_t maxGeometryTotalOutputComponents;
		uint32_t maxFragmentInputComponents;
		uint32_t maxFragmentOutputAttachments;
		uint32_t maxFragmentDualSrcAttachments;
		uint32_t maxFragmentCombinedOutputResources;
		uint32_t maxComputeSharedMemorySize;
		uint32_t maxComputeWorkGroupCount[3];
		uint32_t maxComputeWorkGroupInvocations;
		uint32_t maxComputeWorkGroupSize[3];
		uint32_t subPixelPrecisionBits;
		uint32_t subTexelPrecisionBits;
		uint32_t mipmapPrecisionBits;
		uint32_t maxDrawIndexedIndexValue;
		uint32_t maxDrawIndirectCount;
		float maxSamplerLodBias;
		float maxSamplerAnisotropy;
		uint32_t maxViewports;
		uint32_t maxViewportDimensions[2];
		float viewportBoundsRange[2];
		uint32_t viewportSubPixelBits;
		size_t minMemoryMapAlignment;
		RHI_Device_Size minTexelBufferOffsetAlignment;
		RHI_Device_Size minUniformBufferOffsetAlignment;
		RHI_Device_Size minStorageBufferOffsetAlignment;
		int32_t minTexelOffset;
		uint32_t maxTexelOffset;
		int32_t minTexelGatherOffset;
		uint32_t maxTexelGatherOffset;
		float minInterpolationOffset;
		float maxInterpolationOffset;
		uint32_t subPixelInterpolationOffsetBits;
		uint32_t maxFramebufferWidth;
		uint32_t maxFramebufferHeight;
		uint32_t maxFramebufferLayers;
		RHI_Sample_Count_Flags framebufferColorSampleCounts;
		RHI_Sample_Count_Flags framebufferDepthSampleCounts;
		RHI_Sample_Count_Flags framebufferStencilSampleCounts;
		RHI_Sample_Count_Flags framebufferNoAttachmentsSampleCounts;
		uint32_t maxColorAttachments;
		RHI_Sample_Count_Flags sampledImageColorSampleCounts;
		RHI_Sample_Count_Flags sampledImageIntegerSampleCounts;
		RHI_Sample_Count_Flags sampledImageDepthSampleCounts;
		RHI_Sample_Count_Flags sampledImageStencilSampleCounts;
		RHI_Sample_Count_Flags storageImageSampleCounts;
		uint32_t maxSampleMaskWords;
		RHI_Bool32 timestampComputeAndGraphics;
		float timestampPeriod;
		uint32_t maxClipDistances;
		uint32_t maxCullDistances;
		uint32_t maxCombinedClipAndCullDistances;
		uint32_t discreteQueuePriorities;
		float pointSizeRange[2];
		float lineWidthRange[2];
		float pointSizeGranularity;
		float lineWidthGranularity;
		RHI_Bool32 strictLines;
		RHI_Bool32 standardSampleLocations;
		RHI_Device_Size optimalBufferCopyOffsetAlignment;
		RHI_Device_Size optimalBufferCopyRowPitchAlignment;
		RHI_Device_Size nonCoherentAtomSize;
	};

	struct RHI_Physical_DeviceSparse_Properties final {
		RHI_Bool32 Residency_Standard_2D_Block_Shapes;
		RHI_Bool32 Residency_Standard_2D_Multisample_Block_Shapes;
		RHI_Bool32 Residency_Standard_3D_Block_Shapes;
		RHI_Bool32 Residency_Aligned_Mip_Size;
		RHI_Bool32 Residency_Non_Resident_Strict;
	};

	struct RHI_Physical_Device_Properties final {

		uint32_t Api_Version;
		uint32_t Driver_Version;
		uint32_t Vendor_ID;
		uint32_t Device_ID;
		RHI_PHYSICAL_DEVICE_TYPE Device_Type;
		char Device_Name[RHI_MAX_PHYSICAL_DEVICE_NAME_SIZE];
		uint8_t Pipeline_Cache_UUID[RHI_UUID_SIZE];
		RHI_Physical_Device_Limits Limits;
		RHI_Physical_DeviceSparse_Properties Sparse_Properties;
	};;

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_RHI