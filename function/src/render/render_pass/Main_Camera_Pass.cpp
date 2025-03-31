#include "render/render_pass/Main_Camera_Pass.h"  

#include<tuple>

#include "render/render_pass/Render_Pass.h"  

namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass {

	using NameSpace_Resource::NameSpace_Global::Reflection_Global_Particle_Operator;


	using NameSpace_RHI::RHI_BUFFER_USAGE_FLAG_BITS;

	using NameSpace_RHI::RHI_Image_Usage_Flags;


	using NameSpace_RHI::RHI_STRUCT_TYPE;
	using NameSpace_RHI::RHI_IMAGE_TILING;
	using NameSpace_RHI::RHI_IMAGE_VIEW_TYPE;
	using NameSpace_RHI::RHI_SAMPLE_COUNT_FLAG_BIT;
	using NameSpace_RHI::RHI_ATTACHMENT_LOAD_OP;
	using NameSpace_RHI::RHI_ATTACHMENT_STORE_OP;
	using NameSpace_RHI::RHI_IMAGE_LAYOUT;
	using NameSpace_RHI::RHI_PIPELINE_BIND_POINT;
	using NameSpace_RHI::RHI_PRIMITIVE_TOPOLOGY;
	using NameSpace_RHI::RHI_DEFAULT_SAMPLER_TYPE;
	using NameSpace_RHI::RHI_Shader_Module;

	using NameSpace_RHI::RHI_DESCRIPTOR_TYPE;

	using NameSpace_RHI::RHI_IMAGE_USAGE_FLAG_BITS;
	using NameSpace_RHI::RHI_IMAGE_ASPECT_FLAG_BITS;
	using NameSpace_RHI::RHI_MEMORY_PROPERTY_FLAG_BITS;
	using NameSpace_RHI::RHI_PIPELINE_STAGE_FLAG_BITS;
	using NameSpace_RHI::RHI_ACCESS_FLAG_BITS;
	using NameSpace_RHI::RHI_SHADER_STAGE_FLAG_BITS;
	using NameSpace_RHI::RHI_COLOR_COMPONENT_FLAG_BITS;

	using NameSpace_RHI::RHI_Attachment_Description;
	using NameSpace_RHI::RHI_Attachment_Reference;
	using NameSpace_RHI::RHI_Subpass_Description;
	using NameSpace_RHI::RHI_Subpass_Dependency;
	using NameSpace_RHI::RHI_Descriptor_Set_Layout_Binding;
	using NameSpace_RHI::RHI_Write_Descriptor_Set;
	using NameSpace_RHI::RHI_Vertex_Input_Binding_Description;
	using NameSpace_RHI::RHI_Vertex_Input_Attribute_Description;
	using NameSpace_RHI::RHI_Viewport;
	using NameSpace_RHI::RHI_Rect_2D;
	using NameSpace_RHI::RHI_Pipeline_Color_Blend_Attachment_State;

	using NameSpace_RHI::RHI_Render_Pass_Create_Info;
	using NameSpace_RHI::RHI_Frame_buffer_Create_Info;
	using NameSpace_RHI::RHI_Descriptor_Set_Layout_Create_Info;
	using NameSpace_RHI::RHI_Descriptor_Set_Allocate_Info;
	using NameSpace_RHI::RHI_Descriptor_Buffer_Info;
	using NameSpace_RHI::RHI_Descriptor_Image_Info;

	using NameSpace_RHI::RHI_Pipeline_Layout_Create_Info;
	using NameSpace_RHI::RHI_Pipeline_Shader_Stage_Create_Info;
	using NameSpace_RHI::RHI_Pipeline_Vertex_Input_State_Create_Info;
	using NameSpace_RHI::RHI_Pipeline_Input_Assembly_State_Create_Info;
	using NameSpace_RHI::RHI_Pipeline_Viewport_State_Create_Info;
	using NameSpace_RHI::RHI_Pipeline_Rasterization_State_Create_Info;
	using NameSpace_RHI::RHI_Pipeline_Multisample_State_Create_Info;
	using NameSpace_RHI::RHI_Pipeline_Depth_Stencil_State_Create_Info;
	using NameSpace_RHI::RHI_Pipeline_Color_Blend_State_Create_Info;
	using NameSpace_RHI::RHI_Pipeline_Dynamic_State_Create_Info;
	using NameSpace_RHI::RHI_Graphics_Pipeline_Create_Info;


	using NameSpace_RHI::RHI_Specialization_Map_Entry;
	using NameSpace_RHI::RHI_Specialization_Info;
	using NameSpace_RHI::RHI_Compute_Pipeline_Create_Info;
	using NameSpace_RHI::RHI_DYNAMIC_STATE;

	using NameSpace_RHI::RHI_Command_Buffer_Allocate_Info;
	using NameSpace_RHI::RHI_COMMAND_BUFFER_LEVEL;
	using NameSpace_RHI::RHI_Fence_Create_Info;

	using NameSpace_RHI::RHI_DEPENDENCY_FLAG_BITS;


	void Main_Camera_Pass::Pre_Inittialize(const Render_Pass_Inittialize_Info* Init_Info) {
		this->m_Enable_FXAA = static_cast<const Main_Camera_Pass_Inittialize_Info*>(Init_Info)->Enable_FXAA;

		this->m_Particle_Pass = static_cast<const Main_Camera_Pass_Inittialize_Info*>(Init_Info)->Particle_Pass;



	}

	void Main_Camera_Pass::Post_Inittialize(void)
	{
	}

	void Main_Camera_Pass::PrePare_Pass_Data(shared_ptr<Render_Resource_Base> Resource)
	{
	}

	void Main_Camera_Pass::Draw(void)
	{
	}

	void Main_Camera_Pass::Set_Driectional_Light_Shadow_Color_Image_View(RHI_Image_View* Image_View) {
		this->m_Driectional_Light_Shadow_Color_Image_View = Image_View;
	}

	void Main_Camera_Pass::Set_Point_Light_Shadow_Color_Image_View(RHI_Image_View* Image_View) {
		this->m_Point_Light_Shadow_Color_Image_View = Image_View;
	}

	void Main_Camera_Pass::Setup_Attachments(void) {
		this->m_Frame_Buffer.Width = this->m_RHI->Get_SwapChain_Extent().Width;
		this->m_Frame_Buffer.Height = this->m_RHI->Get_SwapChain_Extent().Height;
		this->m_Frame_Buffer.Layers = 1;

		auto& Ref_Attachements{ this->m_Frame_Buffer.Attachments };

		Ref_Attachements.resize(_main_camera_pass_custom_attachment_count + _main_camera_pass_post_process_attachment_count);

		Ref_Attachements[_main_camera_pass_gbuffer_a].Format = RHI_FORMAT::RHI_FORMAT_R8G8B8A8_UNORM;
		Ref_Attachements[_main_camera_pass_gbuffer_b].Format = RHI_FORMAT::RHI_FORMAT_R8G8B8A8_UNORM;
		Ref_Attachements[_main_camera_pass_gbuffer_c].Format = RHI_FORMAT::RHI_FORMAT_R8G8B8A8_SRGB;
		Ref_Attachements[_main_camera_pass_backup_buffer_odd].Format = RHI_FORMAT::RHI_FORMAT_R16G16B16A16_SFLOAT;
		Ref_Attachements[_main_camera_pass_backup_buffer_even].Format = RHI_FORMAT::RHI_FORMAT_R16G16B16A16_SFLOAT;
		Ref_Attachements[_main_camera_pass_post_process_buffer_odd].Format = RHI_FORMAT::RHI_FORMAT_R16G16B16A16_SFLOAT;
		Ref_Attachements[_main_camera_pass_post_process_buffer_even].Format = RHI_FORMAT::RHI_FORMAT_R16G16B16A16_SFLOAT;

		for (uint32_t Index_Buffer = 0; Index_Buffer < _main_camera_pass_custom_attachment_count; ++Index_Buffer) {
			RHI_Image_Usage_Flags Usage_Flag_Bits{ RHI_IMAGE_USAGE_FLAG_BITS::RHI_IMAGE_USAGE_INPUT_ATTACHMENT_BIT | RHI_IMAGE_USAGE_FLAG_BITS::RHI_IMAGE_USAGE_COLOR_ATTACHMENT_BIT };

			if (Index_Buffer == _main_camera_pass_gbuffer_a)
				Usage_Flag_Bits = Usage_Flag_Bits | RHI_IMAGE_USAGE_FLAG_BITS::RHI_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT;
			else
				Usage_Flag_Bits = Usage_Flag_Bits | RHI_IMAGE_USAGE_FLAG_BITS::RHI_IMAGE_USAGE_SAMPLED_BIT;

			std::tie(Ref_Attachements[Index_Buffer].Image, Ref_Attachements[Index_Buffer].Image_Memory) = this->m_RHI->Create_Image(
				{ this->m_Frame_Buffer.Width,this->m_Frame_Buffer.Height },
				Ref_Attachements[Index_Buffer].Format,
				this->m_Frame_Buffer.Layers,
				1,
				RHI_IMAGE_TILING::RHI_IMAGE_TILING_OPTIMAL,
				Usage_Flag_Bits,
				to_underlying(RHI_MEMORY_PROPERTY_FLAG_BITS::RHI_MEMORY_PROPERTY_DEVICE_LOCAL_BIT),
				0
			);

			Ref_Attachements[Index_Buffer].Image_View = this->m_RHI->Create_Image_View(
				Ref_Attachements[Index_Buffer].Image.get(),
				Ref_Attachements[Index_Buffer].Format,
				1,
				this->m_Frame_Buffer.Layers,
				RHI_IMAGE_VIEW_TYPE::RHI_IMAGE_VIEW_TYPE_2D,
				to_underlying(RHI_IMAGE_ASPECT_FLAG_BITS::RHI_IMAGE_ASPECT_COLOR_BIT)
			);
		}

		for (uint32_t Index_Buffer = _main_camera_pass_custom_attachment_count; Index_Buffer < _main_camera_pass_custom_attachment_count + _main_camera_pass_post_process_attachment_count; ++Index_Buffer) {
			std::tie(Ref_Attachements[Index_Buffer].Image, Ref_Attachements[Index_Buffer].Image_Memory) = this->m_RHI->Create_Image(
				{ this->m_Frame_Buffer.Width,this->m_Frame_Buffer.Height },
				Ref_Attachements[Index_Buffer].Format,
				this->m_Frame_Buffer.Layers,
				1,
				RHI_IMAGE_TILING::RHI_IMAGE_TILING_OPTIMAL,
				RHI_IMAGE_USAGE_FLAG_BITS::RHI_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | RHI_IMAGE_USAGE_FLAG_BITS::RHI_IMAGE_USAGE_INPUT_ATTACHMENT_BIT | RHI_IMAGE_USAGE_FLAG_BITS::RHI_IMAGE_USAGE_SAMPLED_BIT,
				to_underlying(RHI_MEMORY_PROPERTY_FLAG_BITS::RHI_MEMORY_PROPERTY_DEVICE_LOCAL_BIT),
				0
			);

			Ref_Attachements[Index_Buffer].Image_View = this->m_RHI->Create_Image_View(
				Ref_Attachements[Index_Buffer].Image.get(),
				Ref_Attachements[Index_Buffer].Format,
				1,
				this->m_Frame_Buffer.Layers,
				RHI_IMAGE_VIEW_TYPE::RHI_IMAGE_VIEW_TYPE_2D,
				to_underlying(RHI_IMAGE_ASPECT_FLAG_BITS::RHI_IMAGE_ASPECT_COLOR_BIT)
			);
		}
	}

	void Main_Camera_Pass::Setup_Render_Pass(void) {
		RHI_Attachment_Description GBuffer_Normal_Attachment_Description{};
		{
			GBuffer_Normal_Attachment_Description.Flags = 0;
			GBuffer_Normal_Attachment_Description.Format = this->m_Frame_Buffer.Attachments[_main_camera_pass_gbuffer_a].Format;
			GBuffer_Normal_Attachment_Description.Samples = RHI_SAMPLE_COUNT_FLAG_BIT::RHI_SAMPLE_COUNT_1_BIT;
			GBuffer_Normal_Attachment_Description.Load_Op = RHI_ATTACHMENT_LOAD_OP::RHI_ATTACHMENT_LOAD_OP_CLEAR;
			GBuffer_Normal_Attachment_Description.Store_Op = RHI_ATTACHMENT_STORE_OP::RHI_ATTACHMENT_STORE_OP_STORE;
			GBuffer_Normal_Attachment_Description.Stencil_Load_Op = RHI_ATTACHMENT_LOAD_OP::RHI_ATTACHMENT_LOAD_OP_DONT_CARE;
			GBuffer_Normal_Attachment_Description.Stencil_Store_Op = RHI_ATTACHMENT_STORE_OP::RHI_ATTACHMENT_STORE_OP_DONT_CARE;
			GBuffer_Normal_Attachment_Description.Initial_Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_UNDEFINED;
			GBuffer_Normal_Attachment_Description.Final_Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		}

		RHI_Attachment_Description GBuffer_Metallic_Roughness_Shadingmodeid_Attachment_Description{};
		{
			GBuffer_Metallic_Roughness_Shadingmodeid_Attachment_Description.Flags = 0;
			GBuffer_Metallic_Roughness_Shadingmodeid_Attachment_Description.Format = this->m_Frame_Buffer.Attachments[_main_camera_pass_gbuffer_b].Format;
			GBuffer_Metallic_Roughness_Shadingmodeid_Attachment_Description.Samples = RHI_SAMPLE_COUNT_FLAG_BIT::RHI_SAMPLE_COUNT_1_BIT;
			GBuffer_Metallic_Roughness_Shadingmodeid_Attachment_Description.Load_Op = RHI_ATTACHMENT_LOAD_OP::RHI_ATTACHMENT_LOAD_OP_CLEAR;
			GBuffer_Metallic_Roughness_Shadingmodeid_Attachment_Description.Store_Op = RHI_ATTACHMENT_STORE_OP::RHI_ATTACHMENT_STORE_OP_DONT_CARE;
			GBuffer_Metallic_Roughness_Shadingmodeid_Attachment_Description.Stencil_Load_Op = RHI_ATTACHMENT_LOAD_OP::RHI_ATTACHMENT_LOAD_OP_DONT_CARE;
			GBuffer_Metallic_Roughness_Shadingmodeid_Attachment_Description.Stencil_Store_Op = RHI_ATTACHMENT_STORE_OP::RHI_ATTACHMENT_STORE_OP_DONT_CARE;
			GBuffer_Metallic_Roughness_Shadingmodeid_Attachment_Description.Initial_Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_UNDEFINED;
			GBuffer_Metallic_Roughness_Shadingmodeid_Attachment_Description.Final_Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		}

		RHI_Attachment_Description GBuffer_Albedo_Odd_Attachment_Description{};
		{
			GBuffer_Albedo_Odd_Attachment_Description.Flags = 0;
			GBuffer_Albedo_Odd_Attachment_Description.Format = this->m_Frame_Buffer.Attachments[_main_camera_pass_gbuffer_c].Format;
			GBuffer_Albedo_Odd_Attachment_Description.Samples = RHI_SAMPLE_COUNT_FLAG_BIT::RHI_SAMPLE_COUNT_1_BIT;
			GBuffer_Albedo_Odd_Attachment_Description.Load_Op = RHI_ATTACHMENT_LOAD_OP::RHI_ATTACHMENT_LOAD_OP_CLEAR;
			GBuffer_Albedo_Odd_Attachment_Description.Store_Op = RHI_ATTACHMENT_STORE_OP::RHI_ATTACHMENT_STORE_OP_DONT_CARE;
			GBuffer_Albedo_Odd_Attachment_Description.Stencil_Load_Op = RHI_ATTACHMENT_LOAD_OP::RHI_ATTACHMENT_LOAD_OP_DONT_CARE;
			GBuffer_Albedo_Odd_Attachment_Description.Stencil_Store_Op = RHI_ATTACHMENT_STORE_OP::RHI_ATTACHMENT_STORE_OP_DONT_CARE;
			GBuffer_Albedo_Odd_Attachment_Description.Initial_Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_UNDEFINED;
			GBuffer_Albedo_Odd_Attachment_Description.Final_Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		}

		RHI_Attachment_Description Backup_Buffer_Odd_Attachment_Description{};
		{
			Backup_Buffer_Odd_Attachment_Description.Flags = 0;
			Backup_Buffer_Odd_Attachment_Description.Format = this->m_Frame_Buffer.Attachments[_main_camera_pass_backup_buffer_odd].Format;
			Backup_Buffer_Odd_Attachment_Description.Samples = RHI_SAMPLE_COUNT_FLAG_BIT::RHI_SAMPLE_COUNT_1_BIT;
			Backup_Buffer_Odd_Attachment_Description.Load_Op = RHI_ATTACHMENT_LOAD_OP::RHI_ATTACHMENT_LOAD_OP_CLEAR;
			Backup_Buffer_Odd_Attachment_Description.Store_Op = RHI_ATTACHMENT_STORE_OP::RHI_ATTACHMENT_STORE_OP_DONT_CARE;
			Backup_Buffer_Odd_Attachment_Description.Stencil_Load_Op = RHI_ATTACHMENT_LOAD_OP::RHI_ATTACHMENT_LOAD_OP_DONT_CARE;
			Backup_Buffer_Odd_Attachment_Description.Stencil_Store_Op = RHI_ATTACHMENT_STORE_OP::RHI_ATTACHMENT_STORE_OP_DONT_CARE;
			Backup_Buffer_Odd_Attachment_Description.Initial_Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_UNDEFINED;
			Backup_Buffer_Odd_Attachment_Description.Final_Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		}

		RHI_Attachment_Description Backup_Buffer_Even_Attachment_Description{};
		{
			Backup_Buffer_Even_Attachment_Description.Flags = 0;
			Backup_Buffer_Even_Attachment_Description.Format = this->m_Frame_Buffer.Attachments[_main_camera_pass_backup_buffer_even].Format;
			Backup_Buffer_Even_Attachment_Description.Samples = RHI_SAMPLE_COUNT_FLAG_BIT::RHI_SAMPLE_COUNT_1_BIT;
			Backup_Buffer_Even_Attachment_Description.Load_Op = RHI_ATTACHMENT_LOAD_OP::RHI_ATTACHMENT_LOAD_OP_CLEAR;
			Backup_Buffer_Even_Attachment_Description.Store_Op = RHI_ATTACHMENT_STORE_OP::RHI_ATTACHMENT_STORE_OP_DONT_CARE;
			Backup_Buffer_Even_Attachment_Description.Stencil_Load_Op = RHI_ATTACHMENT_LOAD_OP::RHI_ATTACHMENT_LOAD_OP_DONT_CARE;
			Backup_Buffer_Even_Attachment_Description.Stencil_Store_Op = RHI_ATTACHMENT_STORE_OP::RHI_ATTACHMENT_STORE_OP_DONT_CARE;
			Backup_Buffer_Even_Attachment_Description.Initial_Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_UNDEFINED;
			Backup_Buffer_Even_Attachment_Description.Final_Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		}

		RHI_Attachment_Description Post_Process_Buffer_Odd_Color_Attachment_Description{};
		{
			Post_Process_Buffer_Odd_Color_Attachment_Description.Flags = 0;
			Post_Process_Buffer_Odd_Color_Attachment_Description.Format = this->m_Frame_Buffer.Attachments[_main_camera_pass_post_process_buffer_odd].Format;
			Post_Process_Buffer_Odd_Color_Attachment_Description.Samples = RHI_SAMPLE_COUNT_FLAG_BIT::RHI_SAMPLE_COUNT_1_BIT;
			Post_Process_Buffer_Odd_Color_Attachment_Description.Load_Op = RHI_ATTACHMENT_LOAD_OP::RHI_ATTACHMENT_LOAD_OP_CLEAR;
			Post_Process_Buffer_Odd_Color_Attachment_Description.Store_Op = RHI_ATTACHMENT_STORE_OP::RHI_ATTACHMENT_STORE_OP_STORE;
			Post_Process_Buffer_Odd_Color_Attachment_Description.Stencil_Load_Op = RHI_ATTACHMENT_LOAD_OP::RHI_ATTACHMENT_LOAD_OP_DONT_CARE;
			Post_Process_Buffer_Odd_Color_Attachment_Description.Stencil_Store_Op = RHI_ATTACHMENT_STORE_OP::RHI_ATTACHMENT_STORE_OP_DONT_CARE;
			Post_Process_Buffer_Odd_Color_Attachment_Description.Initial_Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_UNDEFINED;
			Post_Process_Buffer_Odd_Color_Attachment_Description.Final_Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		}

		RHI_Attachment_Description Post_Process_Buffer_Even_Color_Attachment_Description{};
		{
			Post_Process_Buffer_Even_Color_Attachment_Description.Flags = 0;
			Post_Process_Buffer_Even_Color_Attachment_Description.Format = this->m_Frame_Buffer.Attachments[_main_camera_pass_post_process_buffer_even].Format;
			Post_Process_Buffer_Even_Color_Attachment_Description.Samples = RHI_SAMPLE_COUNT_FLAG_BIT::RHI_SAMPLE_COUNT_1_BIT;
			Post_Process_Buffer_Even_Color_Attachment_Description.Load_Op = RHI_ATTACHMENT_LOAD_OP::RHI_ATTACHMENT_LOAD_OP_CLEAR;
			Post_Process_Buffer_Even_Color_Attachment_Description.Store_Op = RHI_ATTACHMENT_STORE_OP::RHI_ATTACHMENT_STORE_OP_STORE;
			Post_Process_Buffer_Even_Color_Attachment_Description.Stencil_Load_Op = RHI_ATTACHMENT_LOAD_OP::RHI_ATTACHMENT_LOAD_OP_DONT_CARE;
			Post_Process_Buffer_Even_Color_Attachment_Description.Stencil_Store_Op = RHI_ATTACHMENT_STORE_OP::RHI_ATTACHMENT_STORE_OP_DONT_CARE;
			Post_Process_Buffer_Even_Color_Attachment_Description.Initial_Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_UNDEFINED;
			Post_Process_Buffer_Even_Color_Attachment_Description.Final_Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		}

		RHI_Attachment_Description Depth_Attachment_Description{};
		{
			Depth_Attachment_Description.Flags = 0;
			Depth_Attachment_Description.Format = this->m_RHI->Get_Physical_Depth_Format();
			Depth_Attachment_Description.Samples = RHI_SAMPLE_COUNT_FLAG_BIT::RHI_SAMPLE_COUNT_1_BIT;
			Depth_Attachment_Description.Load_Op = RHI_ATTACHMENT_LOAD_OP::RHI_ATTACHMENT_LOAD_OP_CLEAR;
			Depth_Attachment_Description.Store_Op = RHI_ATTACHMENT_STORE_OP::RHI_ATTACHMENT_STORE_OP_STORE;
			Depth_Attachment_Description.Stencil_Load_Op = RHI_ATTACHMENT_LOAD_OP::RHI_ATTACHMENT_LOAD_OP_CLEAR;
			Depth_Attachment_Description.Stencil_Store_Op = RHI_ATTACHMENT_STORE_OP::RHI_ATTACHMENT_STORE_OP_DONT_CARE;
			Depth_Attachment_Description.Initial_Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_UNDEFINED;
			Depth_Attachment_Description.Final_Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
		}

		RHI_Attachment_Description SwapChain_Attachment_Description{};
		{
			SwapChain_Attachment_Description.Flags = 0;
			SwapChain_Attachment_Description.Format = this->m_RHI->Get_SwapChain_Image_Foramt();
			SwapChain_Attachment_Description.Samples = RHI_SAMPLE_COUNT_FLAG_BIT::RHI_SAMPLE_COUNT_1_BIT;
			SwapChain_Attachment_Description.Load_Op = RHI_ATTACHMENT_LOAD_OP::RHI_ATTACHMENT_LOAD_OP_CLEAR;
			SwapChain_Attachment_Description.Store_Op = RHI_ATTACHMENT_STORE_OP::RHI_ATTACHMENT_STORE_OP_STORE;
			SwapChain_Attachment_Description.Stencil_Load_Op = RHI_ATTACHMENT_LOAD_OP::RHI_ATTACHMENT_LOAD_OP_DONT_CARE;
			SwapChain_Attachment_Description.Stencil_Store_Op = RHI_ATTACHMENT_STORE_OP::RHI_ATTACHMENT_STORE_OP_DONT_CARE;
			SwapChain_Attachment_Description.Initial_Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_UNDEFINED;
			SwapChain_Attachment_Description.Final_Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_PRESENT_SRC_KHR;
		}

		const vector<const RHI_Attachment_Description*> Attachments_Descriptions{
			&GBuffer_Normal_Attachment_Description,
			&GBuffer_Metallic_Roughness_Shadingmodeid_Attachment_Description,
			&GBuffer_Albedo_Odd_Attachment_Description,
			&Backup_Buffer_Odd_Attachment_Description,
			&Backup_Buffer_Even_Attachment_Description,
			&Post_Process_Buffer_Odd_Color_Attachment_Description,
			&Post_Process_Buffer_Even_Color_Attachment_Description,
			&Depth_Attachment_Description,
			&SwapChain_Attachment_Description
		};

		RHI_Attachment_Reference Base_Pass_Color_Attachment_Reference_A{};
		{
			Base_Pass_Color_Attachment_Reference_A.Attachment = 0;
			Base_Pass_Color_Attachment_Reference_A.Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		}

		RHI_Attachment_Reference Base_Pass_Color_Attachment_Reference_B{};
		{
			Base_Pass_Color_Attachment_Reference_B.Attachment = 1;
			Base_Pass_Color_Attachment_Reference_B.Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		}

		RHI_Attachment_Reference Base_Pass_Color_Attachment_Reference_C{};
		{
			Base_Pass_Color_Attachment_Reference_C.Attachment = 2;
			Base_Pass_Color_Attachment_Reference_C.Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		}

		const vector<const RHI_Attachment_Reference*> Color_Attachments_References{
			&Base_Pass_Color_Attachment_Reference_A,
			&Base_Pass_Color_Attachment_Reference_B,
			&Base_Pass_Color_Attachment_Reference_C
		};

		RHI_Attachment_Reference Base_Pass_Depth_Attachment_Reference{};
		{
			Base_Pass_Depth_Attachment_Reference.Attachment = _main_camera_pass_depth;
			Base_Pass_Depth_Attachment_Reference.Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
		}

		RHI_Subpass_Description Base_Pass{};
		{
			Base_Pass.Flags = 0;
			Base_Pass.Pipeline_Bind_Point = RHI_PIPELINE_BIND_POINT::RHI_PIPELINE_BIND_POINT_GRAPHICS;
			Base_Pass.Input_Attachments = nullptr;
			Base_Pass.Color_Attachments = &Color_Attachments_References;
			Base_Pass.Resolve_Attachments = nullptr;
			Base_Pass.Depth_Stencil_Attachment = &Base_Pass_Depth_Attachment_Reference;
			Base_Pass.Preserve_Attachments = nullptr;
		}

		const vector<const RHI_Subpass_Description*> Subpasses{ &Base_Pass };

		RHI_Attachment_Reference Deferred_Lighting_Normal_Pass_Input_Attachments_Reference{};
		{
			Deferred_Lighting_Normal_Pass_Input_Attachments_Reference.Attachment = _main_camera_pass_gbuffer_a;
			Deferred_Lighting_Normal_Pass_Input_Attachments_Reference.Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		}

		RHI_Attachment_Reference Deferred_Lighting_Metallic_Roughness_Shadingmodeid_Pass_Input_Attachments_Reference{};
		{
			Deferred_Lighting_Metallic_Roughness_Shadingmodeid_Pass_Input_Attachments_Reference.Attachment = _main_camera_pass_gbuffer_b;
			Deferred_Lighting_Metallic_Roughness_Shadingmodeid_Pass_Input_Attachments_Reference.Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		}

		RHI_Attachment_Reference Deferred_Lighting_Albedo_Pass_Input_Attachments_Reference{};
		{
			Deferred_Lighting_Albedo_Pass_Input_Attachments_Reference.Attachment = _main_camera_pass_gbuffer_c;
			Deferred_Lighting_Albedo_Pass_Input_Attachments_Reference.Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		}

		const vector<const RHI_Attachment_Reference*> Deferred_Lighting_Input_Attachments_References{
			&Deferred_Lighting_Normal_Pass_Input_Attachments_Reference,
			&Deferred_Lighting_Metallic_Roughness_Shadingmodeid_Pass_Input_Attachments_Reference,
			&Deferred_Lighting_Albedo_Pass_Input_Attachments_Reference
		};

		RHI_Attachment_Reference Deferred_Lighting_Dpeth_Attachments_Reference{};
		{
			Deferred_Lighting_Dpeth_Attachments_Reference.Attachment = _main_camera_pass_depth;
			Deferred_Lighting_Dpeth_Attachments_Reference.Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		}

		const vector<const RHI_Attachment_Reference*> Deferred_Lighting_Input_Attachments_References{
			&Deferred_Lighting_Normal_Pass_Input_Attachments_Reference
		};

		RHI_Attachment_Reference Deferred_Lighting_Backup_Odd_Color_Attachments_Reference{};
		{
			Deferred_Lighting_Backup_Odd_Color_Attachments_Reference.Attachment = _main_camera_pass_backup_buffer_odd;
			Deferred_Lighting_Backup_Odd_Color_Attachments_Reference.Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		}

		const vector<const RHI_Attachment_Reference*> Deferred_Lighting_Color_Attachments_References{
			&Deferred_Lighting_Backup_Odd_Color_Attachments_Reference
		};

		RHI_Subpass_Description Deferred_Lighting{};
		{
			Deferred_Lighting.Flags = 0;
			Deferred_Lighting.Pipeline_Bind_Point = RHI_PIPELINE_BIND_POINT::RHI_PIPELINE_BIND_POINT_GRAPHICS;
			Deferred_Lighting.Input_Attachments = &Deferred_Lighting_Input_Attachments_References;
			Deferred_Lighting.Color_Attachments = &Deferred_Lighting_Color_Attachments_References;
			Deferred_Lighting.Resolve_Attachments = nullptr;
			Deferred_Lighting.Depth_Stencil_Attachment = nullptr;
			Deferred_Lighting.Preserve_Attachments = nullptr;
		}

		RHI_Attachment_Reference Forward_Lighting_Backup_Odd_Color_Pass_Attachments_Reference{};
		{
			Forward_Lighting_Backup_Odd_Color_Pass_Attachments_Reference.Attachment = _main_camera_pass_backup_buffer_odd;
			Forward_Lighting_Backup_Odd_Color_Pass_Attachments_Reference.Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		}

		const vector<const RHI_Attachment_Reference*> Forward_Lighting_Color_Attachments_References{
			&Forward_Lighting_Backup_Odd_Color_Pass_Attachments_Reference
		};

		RHI_Attachment_Reference Forward_Lighting_Depth_Pass_Attachments_Reference{};
		{
			Forward_Lighting_Depth_Pass_Attachments_Reference.Attachment = _main_camera_pass_backup_buffer_even;
			Forward_Lighting_Depth_Pass_Attachments_Reference.Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
		}

		RHI_Subpass_Description Forward_Lighting{};
		{
			Forward_Lighting.Flags = 0;
			Forward_Lighting.Pipeline_Bind_Point = RHI_PIPELINE_BIND_POINT::RHI_PIPELINE_BIND_POINT_GRAPHICS;
			Forward_Lighting.Input_Attachments = nullptr;
			Forward_Lighting.Color_Attachments = &Forward_Lighting_Color_Attachments_References;
			Forward_Lighting.Resolve_Attachments = nullptr;
			Forward_Lighting.Depth_Stencil_Attachment = &Forward_Lighting_Depth_Pass_Attachments_Reference;
			Forward_Lighting.Preserve_Attachments = nullptr;
		}

		RHI_Attachment_Reference Tone_Mapping_Input_Attachments_Reference{};
		{
			Tone_Mapping_Input_Attachments_Reference.Attachment = _main_camera_pass_backup_buffer_odd;
			Tone_Mapping_Input_Attachments_Reference.Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		}

		const vector<const RHI_Attachment_Reference*> Tone_Mapping_Input_Attachments_References{
			&Tone_Mapping_Input_Attachments_Reference
		};

		RHI_Attachment_Reference Tone_Mapping_Color_Attachments_Reference{};
		{
			Tone_Mapping_Color_Attachments_Reference.Attachment = _main_camera_pass_post_process_buffer_odd;
			Tone_Mapping_Color_Attachments_Reference.Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		}

		const vector<const RHI_Attachment_Reference*> Tone_Mapping_Color_Attachments_References{
			&Tone_Mapping_Color_Attachments_Reference
		};

		RHI_Subpass_Description Tone_Mapping{};
		{
			Tone_Mapping.Flags = 0;
			Tone_Mapping.Pipeline_Bind_Point = RHI_PIPELINE_BIND_POINT::RHI_PIPELINE_BIND_POINT_GRAPHICS;
			Tone_Mapping.Input_Attachments = &Tone_Mapping_Input_Attachments_References;
			Tone_Mapping.Color_Attachments = &Tone_Mapping_Color_Attachments_References;
			Tone_Mapping.Resolve_Attachments = nullptr;
			Tone_Mapping.Depth_Stencil_Attachment = nullptr;
			Tone_Mapping.Preserve_Attachments = nullptr;
		}

		RHI_Attachment_Reference Color_Grading_Pass_Input_Attachments_Reference{};
		{
			Color_Grading_Pass_Input_Attachments_Reference.Attachment = _main_camera_pass_backup_buffer_even;
			Color_Grading_Pass_Input_Attachments_Reference.Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		}

		const vector<const RHI_Attachment_Reference*> Color_Grading_Input_Attachments_References{
			&Color_Grading_Pass_Input_Attachments_Reference
		};

		//NOTE: FXAA
		RHI_Attachment_Reference Color_Grading_Color_Attachments_Reference{};
		{
			if (this->m_Enable_FXAA)
				Color_Grading_Color_Attachments_Reference.Attachment = _main_camera_pass_post_process_buffer_odd;
			else
				Color_Grading_Color_Attachments_Reference.Attachment = _main_camera_pass_backup_buffer_odd;

			Color_Grading_Color_Attachments_Reference.Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		}

		const vector<const RHI_Attachment_Reference*> Color_Grading_Color_Attachment_References{
			&Color_Grading_Color_Attachments_Reference
		};

		RHI_Subpass_Description Color_Grading_Pass{};
		{
			Color_Grading_Pass.Flags = 0;
			Color_Grading_Pass.Pipeline_Bind_Point = RHI_PIPELINE_BIND_POINT::RHI_PIPELINE_BIND_POINT_GRAPHICS;
			Color_Grading_Pass.Input_Attachments = &Color_Grading_Input_Attachments_References;
			Color_Grading_Pass.Color_Attachments = &Color_Grading_Color_Attachment_References;
			Color_Grading_Pass.Resolve_Attachments = nullptr;
			Color_Grading_Pass.Depth_Stencil_Attachment = nullptr;
			Color_Grading_Pass.Preserve_Attachments = nullptr;
		}

		RHI_Attachment_Reference FXAA_Input_Attachments_Reference{};
		{
			if (this->m_Enable_FXAA)
				FXAA_Input_Attachments_Reference.Attachment = _main_camera_pass_backup_buffer_odd;
			else
				FXAA_Input_Attachments_Reference.Attachment = _main_camera_pass_backup_buffer_even;
			FXAA_Input_Attachments_Reference.Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		}

		const vector<const RHI_Attachment_Reference*> FXAA_Input_Attachments_References{
			&FXAA_Input_Attachments_Reference
		};

		RHI_Attachment_Reference FXAA_Color_Attachments_Reference{};
		{
			FXAA_Color_Attachments_Reference.Attachment = _main_camera_pass_backup_buffer_odd;
			FXAA_Color_Attachments_Reference.Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		}

		const vector<const RHI_Attachment_Reference*> FXAA_Color_Attachment_References{
			&FXAA_Color_Attachments_Reference
		};

		RHI_Subpass_Description FXAA_Pass{};
		{
			FXAA_Pass.Flags = 0;
			FXAA_Pass.Pipeline_Bind_Point = RHI_PIPELINE_BIND_POINT::RHI_PIPELINE_BIND_POINT_GRAPHICS;
			FXAA_Pass.Input_Attachments = &FXAA_Input_Attachments_References;
			FXAA_Pass.Color_Attachments = &FXAA_Color_Attachment_References;
			FXAA_Pass.Resolve_Attachments = nullptr;
			FXAA_Pass.Depth_Stencil_Attachment = nullptr;
			FXAA_Pass.Preserve_Attachments = nullptr;
		}

		RHI_Attachment_Reference UI_Pass_Color_Attachments_Reference{};
		{
			UI_Pass_Color_Attachments_Reference.Attachment = _main_camera_pass_backup_buffer_even;
			UI_Pass_Color_Attachments_Reference.Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		}

		const vector<const RHI_Attachment_Reference*> UI_Pass_Color_Attachment_References{
			&UI_Pass_Color_Attachments_Reference
		};

		vector<uint32_t> UI_Pass_Depth_Attachment_References{ _main_camera_pass_backup_buffer_odd };
		
		RHI_Subpass_Description UI_Pass{};
		{
			UI_Pass.Flags = 0;
			UI_Pass.Pipeline_Bind_Point = RHI_PIPELINE_BIND_POINT::RHI_PIPELINE_BIND_POINT_GRAPHICS;
			UI_Pass.Input_Attachments = nullptr;
			UI_Pass.Color_Attachments = &UI_Pass_Color_Attachment_References;
			UI_Pass.Resolve_Attachments = nullptr;
			UI_Pass.Depth_Stencil_Attachment = nullptr;
			UI_Pass.Preserve_Attachments = &UI_Pass_Depth_Attachment_References;
		}

		RHI_Attachment_Reference Combine_UI_Backup_Odd_Input_Attachment_Reference{};
		{
			Combine_UI_Backup_Odd_Input_Attachment_Reference.Attachment = _main_camera_pass_backup_buffer_odd;
			Combine_UI_Backup_Odd_Input_Attachment_Reference.Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		}

		RHI_Attachment_Reference Combine_UI_Backup_Even_Input_Attachment_Reference{};
		{
			Combine_UI_Backup_Even_Input_Attachment_Reference.Attachment = _main_camera_pass_backup_buffer_even;
			Combine_UI_Backup_Even_Input_Attachment_Reference.Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		}

		const vector<const RHI_Attachment_Reference*> Combine_UI_Input_Attachments_References{
			&Combine_UI_Backup_Odd_Input_Attachment_Reference,
			&Combine_UI_Backup_Even_Input_Attachment_Reference
		};

		RHI_Attachment_Reference Combine_UI_SwapChain_Image_Color_Attachment_Reference{};
		{
			Combine_UI_SwapChain_Image_Color_Attachment_Reference.Attachment = _main_camera_pass_post_process_buffer_odd;
			Combine_UI_SwapChain_Image_Color_Attachment_Reference.Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		}

		const vector<const RHI_Attachment_Reference*> Combine_UI_Color_Attachment_References{
			&Combine_UI_SwapChain_Image_Color_Attachment_Reference
		};

		RHI_Subpass_Description Combine_UI_Pass{};
		{
			Combine_UI_Pass.Flags = 0;
			Combine_UI_Pass.Pipeline_Bind_Point = RHI_PIPELINE_BIND_POINT::RHI_PIPELINE_BIND_POINT_GRAPHICS;
			Combine_UI_Pass.Input_Attachments = &Combine_UI_Input_Attachments_References;
			Combine_UI_Pass.Color_Attachments = &Combine_UI_Color_Attachment_References;
			Combine_UI_Pass.Resolve_Attachments = nullptr;
			Combine_UI_Pass.Depth_Stencil_Attachment = nullptr;
			Combine_UI_Pass.Preserve_Attachments = nullptr;
		}

		const vector<const RHI_Subpass_Description*> Subpasses_Descriptions{
			&Base_Pass,
			&Deferred_Lighting,
			&Forward_Lighting,
			&Tone_Mapping,
			&Color_Grading_Pass,
			&FXAA_Pass,
			&UI_Pass,
			&Combine_UI_Pass
		};

		RHI_Subpass_Dependency Deferred_Lighting_Pass_Depend_On_Shadow_Map_Pass{};
		{
			Deferred_Lighting_Pass_Depend_On_Shadow_Map_Pass.Src_Subpass = RHI_SUBPASS_EXTERNAL;
			Deferred_Lighting_Pass_Depend_On_Shadow_Map_Pass.Dst_Subpass = _main_camera_subpass_deferred_lighting;
			Deferred_Lighting_Pass_Depend_On_Shadow_Map_Pass.Src_Stage_Mask = to_underlying(RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT);
			Deferred_Lighting_Pass_Depend_On_Shadow_Map_Pass.Dst_Stage_Mask = to_underlying(RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_FRAGMENT_SHADER_BIT);
			Deferred_Lighting_Pass_Depend_On_Shadow_Map_Pass.Src_Access_Mask = to_underlying(RHI_ACCESS_FLAG_BITS::RHI_ACCESS_COLOR_ATTACHMENT_WRITE_BIT);
			Deferred_Lighting_Pass_Depend_On_Shadow_Map_Pass.Dst_Access_Mask = to_underlying(RHI_ACCESS_FLAG_BITS::RHI_ACCESS_SHADER_READ_BIT);
			Deferred_Lighting_Pass_Depend_On_Shadow_Map_Pass.Dependency_Flags = 0;
		}

		RHI_Subpass_Dependency Deferred_Lighting_Pass_Depend_On_Base_Pass{};
		{
			Deferred_Lighting_Pass_Depend_On_Base_Pass.Src_Subpass = _main_camera_subpass_basepass;
			Deferred_Lighting_Pass_Depend_On_Base_Pass.Dst_Subpass = _main_camera_subpass_deferred_lighting;
			Deferred_Lighting_Pass_Depend_On_Base_Pass.Src_Stage_Mask = RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			Deferred_Lighting_Pass_Depend_On_Base_Pass.Dst_Stage_Mask = RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			Deferred_Lighting_Pass_Depend_On_Base_Pass.Src_Access_Mask = RHI_ACCESS_FLAG_BITS::RHI_ACCESS_SHADER_WRITE_BIT | RHI_ACCESS_FLAG_BITS::RHI_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
			Deferred_Lighting_Pass_Depend_On_Base_Pass.Dst_Access_Mask = RHI_ACCESS_FLAG_BITS::RHI_ACCESS_SHADER_READ_BIT | RHI_ACCESS_FLAG_BITS::RHI_ACCESS_COLOR_ATTACHMENT_READ_BIT;
			Deferred_Lighting_Pass_Depend_On_Base_Pass.Dependency_Flags =to_underlying(RHI_DEPENDENCY_FLAG_BITS::RHI_DEPENDENCY_BY_REGION_BIT);
		}

		RHI_Subpass_Dependency Forward_Lighting_Pass_Depend_On_Deferred_Lighting_Pass{};
		{
			Forward_Lighting_Pass_Depend_On_Deferred_Lighting_Pass.Src_Subpass = _main_camera_subpass_deferred_lighting;
			Forward_Lighting_Pass_Depend_On_Deferred_Lighting_Pass.Dst_Subpass = _main_camera_subpass_forward_lighting;
			Forward_Lighting_Pass_Depend_On_Deferred_Lighting_Pass.Src_Stage_Mask = RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			Forward_Lighting_Pass_Depend_On_Deferred_Lighting_Pass.Dst_Stage_Mask = RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			Forward_Lighting_Pass_Depend_On_Deferred_Lighting_Pass.Src_Access_Mask = RHI_ACCESS_FLAG_BITS::RHI_ACCESS_SHADER_WRITE_BIT | RHI_ACCESS_FLAG_BITS::RHI_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
			Forward_Lighting_Pass_Depend_On_Deferred_Lighting_Pass.Dst_Access_Mask = RHI_ACCESS_FLAG_BITS::RHI_ACCESS_SHADER_WRITE_BIT | RHI_ACCESS_FLAG_BITS::RHI_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
			Forward_Lighting_Pass_Depend_On_Deferred_Lighting_Pass.Dependency_Flags = to_underlying(RHI_DEPENDENCY_FLAG_BITS::RHI_DEPENDENCY_BY_REGION_BIT);
		}

		RHI_Subpass_Dependency Tone_Mapping_Pass_Depend_On_Forward_Lighting_Pass{};
		{
			Tone_Mapping_Pass_Depend_On_Forward_Lighting_Pass.Src_Subpass = _main_camera_subpass_forward_lighting;
			Tone_Mapping_Pass_Depend_On_Forward_Lighting_Pass.Dst_Subpass = _main_camera_subpass_tone_mapping;
			Tone_Mapping_Pass_Depend_On_Forward_Lighting_Pass.Src_Stage_Mask = RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			Tone_Mapping_Pass_Depend_On_Forward_Lighting_Pass.Dst_Stage_Mask = RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			Tone_Mapping_Pass_Depend_On_Forward_Lighting_Pass.Src_Access_Mask = RHI_ACCESS_FLAG_BITS::RHI_ACCESS_SHADER_WRITE_BIT | RHI_ACCESS_FLAG_BITS::RHI_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
			Tone_Mapping_Pass_Depend_On_Forward_Lighting_Pass.Dst_Access_Mask = RHI_ACCESS_FLAG_BITS::RHI_ACCESS_SHADER_READ_BIT | RHI_ACCESS_FLAG_BITS::RHI_ACCESS_COLOR_ATTACHMENT_READ_BIT;
			Tone_Mapping_Pass_Depend_On_Forward_Lighting_Pass.Dependency_Flags = to_underlying(RHI_DEPENDENCY_FLAG_BITS::RHI_DEPENDENCY_BY_REGION_BIT);
		}

		RHI_Subpass_Dependency Color_Grading_Pass_Depend_On_Tone_Mapping_Pass{};
		{
			Color_Grading_Pass_Depend_On_Tone_Mapping_Pass.Src_Subpass = _main_camera_subpass_tone_mapping;
			Color_Grading_Pass_Depend_On_Tone_Mapping_Pass.Dst_Subpass = _main_camera_subpass_color_grading;
			Color_Grading_Pass_Depend_On_Tone_Mapping_Pass.Src_Stage_Mask = RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			Color_Grading_Pass_Depend_On_Tone_Mapping_Pass.Dst_Stage_Mask = RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			Color_Grading_Pass_Depend_On_Tone_Mapping_Pass.Src_Access_Mask = RHI_ACCESS_FLAG_BITS::RHI_ACCESS_SHADER_WRITE_BIT | RHI_ACCESS_FLAG_BITS::RHI_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
			Color_Grading_Pass_Depend_On_Tone_Mapping_Pass.Dst_Access_Mask = RHI_ACCESS_FLAG_BITS::RHI_ACCESS_SHADER_READ_BIT | RHI_ACCESS_FLAG_BITS::RHI_ACCESS_COLOR_ATTACHMENT_READ_BIT;
			Color_Grading_Pass_Depend_On_Tone_Mapping_Pass.Dependency_Flags = to_underlying(RHI_DEPENDENCY_FLAG_BITS::RHI_DEPENDENCY_BY_REGION_BIT);
		}

		RHI_Subpass_Dependency FAXX_Pass_Depend_On_Color_Grading_Pass{};
		{
			FAXX_Pass_Depend_On_Color_Grading_Pass.Src_Subpass = _main_camera_subpass_fxaa;
			FAXX_Pass_Depend_On_Color_Grading_Pass.Dst_Subpass = _main_camera_subpass_color_grading;
			FAXX_Pass_Depend_On_Color_Grading_Pass.Src_Stage_Mask = RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			FAXX_Pass_Depend_On_Color_Grading_Pass.Dst_Stage_Mask = RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			FAXX_Pass_Depend_On_Color_Grading_Pass.Src_Access_Mask = RHI_ACCESS_FLAG_BITS::RHI_ACCESS_SHADER_WRITE_BIT | RHI_ACCESS_FLAG_BITS::RHI_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
			FAXX_Pass_Depend_On_Color_Grading_Pass.Dst_Access_Mask = RHI_ACCESS_FLAG_BITS::RHI_ACCESS_SHADER_READ_BIT | RHI_ACCESS_FLAG_BITS::RHI_ACCESS_COLOR_ATTACHMENT_READ_BIT;
			FAXX_Pass_Depend_On_Color_Grading_Pass.Dependency_Flags = 0; //to_underlying(RHI_DEPENDENCY_FLAG_BITS::RHI_DEPENDENCY_BY_REGION_BIT);
		}

		RHI_Subpass_Dependency UI_Pass_Depend_On_Fxaa_Pass{};
		{
			UI_Pass_Depend_On_Fxaa_Pass.Src_Subpass = _main_camera_subpass_fxaa;
			UI_Pass_Depend_On_Fxaa_Pass.Dst_Subpass = _main_camera_subpass_ui;
			UI_Pass_Depend_On_Fxaa_Pass.Src_Stage_Mask = RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			UI_Pass_Depend_On_Fxaa_Pass.Dst_Stage_Mask = RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			UI_Pass_Depend_On_Fxaa_Pass.Src_Access_Mask = RHI_ACCESS_FLAG_BITS::RHI_ACCESS_SHADER_WRITE_BIT | RHI_ACCESS_FLAG_BITS::RHI_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
			UI_Pass_Depend_On_Fxaa_Pass.Dst_Access_Mask = RHI_ACCESS_FLAG_BITS::RHI_ACCESS_SHADER_READ_BIT | RHI_ACCESS_FLAG_BITS::RHI_ACCESS_COLOR_ATTACHMENT_READ_BIT;
			UI_Pass_Depend_On_Fxaa_Pass.Dependency_Flags =to_underlying(RHI_DEPENDENCY_FLAG_BITS::RHI_DEPENDENCY_BY_REGION_BIT);
		}

		RHI_Subpass_Dependency Combine_UI_Pass_Depend_On_UI_Pass{};
		{
			Combine_UI_Pass_Depend_On_UI_Pass.Src_Subpass = _main_camera_subpass_ui;
			Combine_UI_Pass_Depend_On_UI_Pass.Dst_Subpass = _main_camera_subpass_combine_ui;
			Combine_UI_Pass_Depend_On_UI_Pass.Src_Stage_Mask = RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			Combine_UI_Pass_Depend_On_UI_Pass.Dst_Stage_Mask = RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			Combine_UI_Pass_Depend_On_UI_Pass.Src_Access_Mask = RHI_ACCESS_FLAG_BITS::RHI_ACCESS_SHADER_WRITE_BIT | RHI_ACCESS_FLAG_BITS::RHI_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
			Combine_UI_Pass_Depend_On_UI_Pass.Dst_Access_Mask = RHI_ACCESS_FLAG_BITS::RHI_ACCESS_SHADER_READ_BIT | RHI_ACCESS_FLAG_BITS::RHI_ACCESS_COLOR_ATTACHMENT_READ_BIT;
			Combine_UI_Pass_Depend_On_UI_Pass.Dependency_Flags = to_underlying(RHI_DEPENDENCY_FLAG_BITS::RHI_DEPENDENCY_BY_REGION_BIT);
		}

		const vector<const RHI_Subpass_Dependency*> Subpass_Dependencies{
			&Deferred_Lighting_Pass_Depend_On_Shadow_Map_Pass,
			&Deferred_Lighting_Pass_Depend_On_Base_Pass,
			&Forward_Lighting_Pass_Depend_On_Deferred_Lighting_Pass,
			&Tone_Mapping_Pass_Depend_On_Forward_Lighting_Pass,
			&Color_Grading_Pass_Depend_On_Tone_Mapping_Pass,
			&FAXX_Pass_Depend_On_Color_Grading_Pass,
			&UI_Pass_Depend_On_Fxaa_Pass,
			&Combine_UI_Pass_Depend_On_UI_Pass
		};

	
		RHI_Render_Pass_Create_Info Render_Pass_Create_Info{};
		{
			Render_Pass_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
			Render_Pass_Create_Info.Attachments =&Attachments_Descriptions;
			Render_Pass_Create_Info.Subpasses = &Subpasses_Descriptions;
			Render_Pass_Create_Info.Dependencies = &Subpass_Dependencies;

		}

		this->m_Frame_Buffer.Render_Pass = this->m_RHI->Create_Render_Pass(&Render_Pass_Create_Info);
	}

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass