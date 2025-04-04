#include "render/render_pass/Main_Camera_Pass.h"  

#include<tuple>
#include<utility>

#include "render/render_system/Render_Mesh.h"
#include "render/render_pass/Render_Pass.h"

#include "render/rhi/empty_rhi/RHI_Class.h"
#include "render/rhi/empty_rhi/RHI_Type.h"
#include "render/rhi/empty_rhi/RHI_Struct.h"

#include "render/render_system/Render_Commmon.h"

#include "axis_vert.h"
#include "axis_frag.h"
#include "deferred_lighting_vert.h"
#include "deferred_lighting_frag.h"
#include "mesh_vert.h"
#include "mesh_frag.h"
#include "mesh_gbuffer_frag.h"
#include "skybox_vert.h"
#include "skybox_frag.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass {

	using std::static_pointer_cast;

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
	using NameSpace_RHI::RHI_BLEND_OP;

	using NameSpace_RHI::RHI_DESCRIPTOR_TYPE;

	using NameSpace_RHI::RHI_IMAGE_USAGE_FLAG_BITS;
	using NameSpace_RHI::RHI_IMAGE_ASPECT_FLAG_BITS;
	using NameSpace_RHI::RHI_MEMORY_PROPERTY_FLAG_BITS;
	using NameSpace_RHI::RHI_PIPELINE_STAGE_FLAG_BITS;
	using NameSpace_RHI::RHI_ACCESS_FLAG_BITS;
	using NameSpace_RHI::RHI_SHADER_STAGE_FLAG_BITS;
	using NameSpace_RHI::RHI_COLOR_COMPONENT_FLAG_BITS;
	using NameSpace_RHI::RHI_CULL_MODE_FLAG_BITS;
	using NameSpace_RHI::RHI_FRONT_FACE;
	using NameSpace_RHI::RHI_BLEND_FACTOR;
	using NameSpace_RHI::RHI_COMPARE_OP;
	using NameSpace_RHI::RHI_LOGIC_OP;

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
	using NameSpace_RHI::RHI_Frame_Buffer_Create_Info;
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
	using NameSpace_RHI::RHI_POLYGON_MODE;

	using NameSpace_RHI::RHI_DEPENDENCY_FLAG_BITS;

	using NameSpace_Render_System::Mesh_Vertex;

	using NameSpace_Render_System::Mesh_Directional_Light_Shadow_Per_Frame_Storage_Buffer_Object;
	using NameSpace_Render_System::Mesh_Per_Frame_Storage_Buffer_Object;
	using NameSpace_Render_System::Mesh_Per_Draw_Class_Storage_Buffer_Object;
	using NameSpace_Render_System::Mesh_Per_Draw_Call_Vertex_Blending_Storage_Buffer_Object;
	using NameSpace_Render_System::Axis_Storage_Buffer_Object;

	using NameSpace_RHI::RHI_DEFAULT_SAMPLER_TYPE;

	using NameSpace_Render_System::Mesh_Vertex;


	void Main_Camera_Pass::Pre_Inittialize(shared_ptr<Render_Pass_Pre_Initialize_Info> Init_Info) {
		const auto Main_Camera_Info{ static_pointer_cast<Main_Camera_Render_Pass_Per_Initialize_Info>(Init_Info) };
		{
			this->m_Enable_FXAA = Main_Camera_Info->Enable_FXAA;
			this->m_Point_Light_Shadow_Color_Image_View = Main_Camera_Info->Point_Light_Shadow_Color_Image_View;
			this->m_Directional_Light_Shadow_Color_Image_View = Main_Camera_Info->Directional_Light_Shadow_Color_Image_View;
		}

		this->Setup_Attachments();
		this->Setup_Render_Pass();
		this->Setup_Descriptor_Set_Layout();
		this->Setup_Pipeline();
		this->Setup_Descriptor_Set();
		this->Setup_Frame_Buffer_Descriptor_Set();
		this->Setup_SwapChain_Frame_Buffers();
	}

	void Main_Camera_Pass::Post_Inittialize(shared_ptr<Render_Pass_Post_Initialize_Info> Init_Info)
	{
	}

	void Main_Camera_Pass::PrePare_Pass_Data(shared_ptr<Render_Resource_Base> Resource)
	{
	}

	void Main_Camera_Pass::Draw(void)
	{
	}

	Main_Camera_Pass::Main_Camera_Pass(const Render_Pass_Command_Info& Command_Info)
		: Render_Pass{ Command_Info } {
	}

	bool Main_Camera_Pass::Get_Axis_State(void) const {
		return this->m_Is_Show_Axis;
	}

    void Main_Camera_Pass::Set_Aixs_State(bool State) {
        this->m_Is_Show_Axis = State;
    }

	void Main_Camera_Pass::Setup_Attachments(void) {
		this->m_Frame_Buffer.Width = this->m_RHI->Get_SwapChain_Extent().Width;
		this->m_Frame_Buffer.Height = this->m_RHI->Get_SwapChain_Extent().Height;
		this->m_Frame_Buffer.Layers = 1;

		auto& Ref_Attachements{ this->m_Frame_Buffer.Attachments };

		Ref_Attachements.resize(static_cast<size_t>(_main_camera_pass_custom_attachment_count) + _main_camera_pass_post_process_attachment_count + 2);

		Ref_Attachements[_main_camera_pass_gbuffer_a].Format = RHI_FORMAT::RHI_FORMAT_R8G8B8A8_UNORM;
		Ref_Attachements[_main_camera_pass_gbuffer_b].Format = RHI_FORMAT::RHI_FORMAT_R8G8B8A8_UNORM;
		Ref_Attachements[_main_camera_pass_gbuffer_c].Format = RHI_FORMAT::RHI_FORMAT_R8G8B8A8_SRGB;
		Ref_Attachements[_main_camera_pass_backup_buffer_odd].Format = RHI_FORMAT::RHI_FORMAT_R16G16B16A16_SFLOAT;
		Ref_Attachements[_main_camera_pass_backup_buffer_even].Format = RHI_FORMAT::RHI_FORMAT_R16G16B16A16_SFLOAT;
		Ref_Attachements[_main_camera_pass_post_process_buffer_odd].Format = RHI_FORMAT::RHI_FORMAT_R16G16B16A16_SFLOAT;
		Ref_Attachements[_main_camera_pass_post_process_buffer_even].Format = RHI_FORMAT::RHI_FORMAT_R16G16B16A16_SFLOAT;
		Ref_Attachements[_main_camera_pass_depth].Format = this->m_RHI->Get_Physical_Depth_Format();
		Ref_Attachements[_main_camera_pass_swap_chain_image].Format = this->m_RHI->Get_SwapChain_Image_Foramt();

		for (uint32_t Index_Buffer = 0; Index_Buffer < _main_camera_pass_custom_attachment_count; ++Index_Buffer) {
			RHI_Image_Usage_Flags Usage_Flag_Bits{ RHI_IMAGE_USAGE_FLAG_BITS::RHI_IMAGE_USAGE_INPUT_ATTACHMENT_BIT | RHI_IMAGE_USAGE_FLAG_BITS::RHI_IMAGE_USAGE_COLOR_ATTACHMENT_BIT };

			if (Index_Buffer == _main_camera_pass_gbuffer_a)
				Usage_Flag_Bits = Usage_Flag_Bits | RHI_IMAGE_USAGE_FLAG_BITS::RHI_IMAGE_USAGE_TRANSFER_SRC_BIT;
			else
				Usage_Flag_Bits = Usage_Flag_Bits | RHI_IMAGE_USAGE_FLAG_BITS::RHI_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT;

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

		for (uint32_t Index_Attachment = _main_camera_pass_custom_attachment_count; Index_Attachment < _main_camera_pass_custom_attachment_count + _main_camera_pass_post_process_attachment_count; ++Index_Attachment) {
			std::tie(Ref_Attachements[Index_Attachment].Image, Ref_Attachements[Index_Attachment].Image_Memory) = this->m_RHI->Create_Image(
				{ this->m_Frame_Buffer.Width,this->m_Frame_Buffer.Height },
				Ref_Attachements[Index_Attachment].Format,
				this->m_Frame_Buffer.Layers,
				1,
				RHI_IMAGE_TILING::RHI_IMAGE_TILING_OPTIMAL,
				RHI_IMAGE_USAGE_FLAG_BITS::RHI_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | RHI_IMAGE_USAGE_FLAG_BITS::RHI_IMAGE_USAGE_INPUT_ATTACHMENT_BIT | RHI_IMAGE_USAGE_FLAG_BITS::RHI_IMAGE_USAGE_SAMPLED_BIT,
				to_underlying(RHI_MEMORY_PROPERTY_FLAG_BITS::RHI_MEMORY_PROPERTY_DEVICE_LOCAL_BIT),
				0
			);

			Ref_Attachements[Index_Attachment].Image_View = this->m_RHI->Create_Image_View(
				Ref_Attachements[Index_Attachment].Image.get(),
				Ref_Attachements[Index_Attachment].Format,
				1,
				this->m_Frame_Buffer.Layers,
				RHI_IMAGE_VIEW_TYPE::RHI_IMAGE_VIEW_TYPE_2D,
				to_underlying(RHI_IMAGE_ASPECT_FLAG_BITS::RHI_IMAGE_ASPECT_COLOR_BIT)
			);
		}
	}

	void Main_Camera_Pass::Setup_Render_Pass(void) {
		//NOTE : Attachment
		RHI_Attachment_Description GBuffer_Normal_Attachment_Description{};
		RHI_Attachment_Description GBuffer_Metallic_Roughness_Shadingmodeid_Attachment_Description{};
		RHI_Attachment_Description GBuffer_Albedo_Odd_Attachment_Description{};
		RHI_Attachment_Description Backup_Buffer_Odd_Attachment_Description{};
		RHI_Attachment_Description Backup_Buffer_Even_Attachment_Description{};
		RHI_Attachment_Description Post_Process_Buffer_Odd_Color_Attachment_Description{};
		RHI_Attachment_Description Post_Process_Buffer_Even_Color_Attachment_Description{};
		RHI_Attachment_Description Depth_Attachment_Description{};
		RHI_Attachment_Description SwapChain_Attachment_Description{};

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

		{
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

			{
				Post_Process_Buffer_Odd_Color_Attachment_Description.Flags = 0;
				Post_Process_Buffer_Odd_Color_Attachment_Description.Format = this->m_Frame_Buffer.Attachments[_main_camera_pass_post_process_buffer_odd].Format;
				Post_Process_Buffer_Odd_Color_Attachment_Description.Samples = RHI_SAMPLE_COUNT_FLAG_BIT::RHI_SAMPLE_COUNT_1_BIT;
				Post_Process_Buffer_Odd_Color_Attachment_Description.Load_Op = RHI_ATTACHMENT_LOAD_OP::RHI_ATTACHMENT_LOAD_OP_CLEAR;
				Post_Process_Buffer_Odd_Color_Attachment_Description.Store_Op = RHI_ATTACHMENT_STORE_OP::RHI_ATTACHMENT_STORE_OP_DONT_CARE;
				Post_Process_Buffer_Odd_Color_Attachment_Description.Stencil_Load_Op = RHI_ATTACHMENT_LOAD_OP::RHI_ATTACHMENT_LOAD_OP_DONT_CARE;
				Post_Process_Buffer_Odd_Color_Attachment_Description.Stencil_Store_Op = RHI_ATTACHMENT_STORE_OP::RHI_ATTACHMENT_STORE_OP_DONT_CARE;
				Post_Process_Buffer_Odd_Color_Attachment_Description.Initial_Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_UNDEFINED;
				Post_Process_Buffer_Odd_Color_Attachment_Description.Final_Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			}

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

			{
				Depth_Attachment_Description.Flags = 0;
				Depth_Attachment_Description.Format = this->m_Frame_Buffer.Attachments[_main_camera_pass_depth].Format;
				Depth_Attachment_Description.Samples = RHI_SAMPLE_COUNT_FLAG_BIT::RHI_SAMPLE_COUNT_1_BIT;
				Depth_Attachment_Description.Load_Op = RHI_ATTACHMENT_LOAD_OP::RHI_ATTACHMENT_LOAD_OP_CLEAR;
				Depth_Attachment_Description.Store_Op = RHI_ATTACHMENT_STORE_OP::RHI_ATTACHMENT_STORE_OP_STORE;
				Depth_Attachment_Description.Stencil_Load_Op = RHI_ATTACHMENT_LOAD_OP::RHI_ATTACHMENT_LOAD_OP_DONT_CARE;
				Depth_Attachment_Description.Stencil_Store_Op = RHI_ATTACHMENT_STORE_OP::RHI_ATTACHMENT_STORE_OP_DONT_CARE;
				Depth_Attachment_Description.Initial_Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_UNDEFINED;
				Depth_Attachment_Description.Final_Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
			}

			{
				SwapChain_Attachment_Description.Flags = 0;
				SwapChain_Attachment_Description.Format = this->m_Frame_Buffer.Attachments[_main_camera_pass_swap_chain_image].Format;
				SwapChain_Attachment_Description.Samples = RHI_SAMPLE_COUNT_FLAG_BIT::RHI_SAMPLE_COUNT_1_BIT;
				SwapChain_Attachment_Description.Load_Op = RHI_ATTACHMENT_LOAD_OP::RHI_ATTACHMENT_LOAD_OP_CLEAR;
				SwapChain_Attachment_Description.Store_Op = RHI_ATTACHMENT_STORE_OP::RHI_ATTACHMENT_STORE_OP_STORE;
				SwapChain_Attachment_Description.Stencil_Load_Op = RHI_ATTACHMENT_LOAD_OP::RHI_ATTACHMENT_LOAD_OP_DONT_CARE;
				SwapChain_Attachment_Description.Stencil_Store_Op = RHI_ATTACHMENT_STORE_OP::RHI_ATTACHMENT_STORE_OP_DONT_CARE;
				SwapChain_Attachment_Description.Initial_Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_UNDEFINED;
				SwapChain_Attachment_Description.Final_Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_PRESENT_SRC_KHR;
			}
		}

		//NOTE; Base_Subpass
		RHI_Subpass_Description Base_Subpass{};

		RHI_Attachment_Reference Base_Pass_Color_Attachment_Reference_A{};
		RHI_Attachment_Reference Base_Pass_Color_Attachment_Reference_B{};
		RHI_Attachment_Reference Base_Pass_Color_Attachment_Reference_C{};
		const vector<const RHI_Attachment_Reference*> Base_Pass_Color_Attachments_References{
			&Base_Pass_Color_Attachment_Reference_A,
			&Base_Pass_Color_Attachment_Reference_B,
			&Base_Pass_Color_Attachment_Reference_C
		};

		RHI_Attachment_Reference Base_Pass_Depth_Attachment_Reference{};

		//NOTE : Deferred_Lighting_Subpass
		RHI_Subpass_Description Deferred_Lighting_Subpass{};

		RHI_Attachment_Reference Deferred_Lighting_Normal_Pass_Input_Attachments_Reference{};
		RHI_Attachment_Reference Deferred_Lighting_Metallic_Roughness_Shadingmodeid_Pass_Input_Attachments_Reference{};
		RHI_Attachment_Reference Deferred_Lighting_Albedo_Pass_Input_Attachments_Reference{};
		RHI_Attachment_Reference Deferred_Lighting_Pass_Depth_Input_Attachments_Reference{};
		const vector<const RHI_Attachment_Reference*> Deferred_Lighting_Input_Attachments_References{
			&Deferred_Lighting_Normal_Pass_Input_Attachments_Reference,
			&Deferred_Lighting_Metallic_Roughness_Shadingmodeid_Pass_Input_Attachments_Reference,
			&Deferred_Lighting_Albedo_Pass_Input_Attachments_Reference,
			&Deferred_Lighting_Pass_Depth_Input_Attachments_Reference
		};

		RHI_Attachment_Reference Deferred_Lighting_Dpeth_Attachments_Reference{};

		RHI_Attachment_Reference Deferred_Lighting_Backup_Odd_Color_Attachments_Reference{};
		const vector<const RHI_Attachment_Reference*> Deferred_Lighting_Color_Attachments_References{
			&Deferred_Lighting_Backup_Odd_Color_Attachments_Reference
		};

		//NOTE : Forward_Lighting_Subpass
		RHI_Subpass_Description Forward_Lighting_Subpass{};

		RHI_Attachment_Reference Forward_Lighting_Backup_Odd_Color_Pass_Attachments_Reference{};
		const vector<const RHI_Attachment_Reference*> Forward_Lighting_Color_Attachments_References{
			&Forward_Lighting_Backup_Odd_Color_Pass_Attachments_Reference
		};

		RHI_Attachment_Reference Forward_Lighting_Depth_Pass_Attachments_Reference{};

		//NOTE : Tone_Mapping_Subpass
		RHI_Subpass_Description Tone_Mapping_Subpass{};

		RHI_Attachment_Reference Tone_Mapping_Input_Attachments_Reference{};
		const vector<const RHI_Attachment_Reference*> Tone_Mapping_Input_Attachments_References{
			&Tone_Mapping_Input_Attachments_Reference
		};

		RHI_Attachment_Reference Tone_Mapping_Color_Attachments_Reference{};
		const vector<const RHI_Attachment_Reference*> Tone_Mapping_Color_Attachments_References{
			&Tone_Mapping_Color_Attachments_Reference
		};

		//NOTE : Color_Grading_Subpass
		RHI_Subpass_Description Color_Grading_Subpass{};

		RHI_Attachment_Reference Color_Grading_Pass_Input_Attachments_Reference{};
		const vector<const RHI_Attachment_Reference*> Color_Grading_Input_Attachments_References{
			&Color_Grading_Pass_Input_Attachments_Reference
		};

		RHI_Attachment_Reference Color_Grading_Color_Attachments_Reference{};
		const vector<const RHI_Attachment_Reference*> Color_Grading_Color_Attachment_References{
			&Color_Grading_Color_Attachments_Reference
		};

		//NOTE : FXAA_Subpass
		RHI_Subpass_Description FXAA_Subpass{};

		RHI_Attachment_Reference FXAA_Input_Attachments_Reference{};
		const vector<const RHI_Attachment_Reference*> FXAA_Input_Attachments_References{
			&FXAA_Input_Attachments_Reference
		};

		RHI_Attachment_Reference FXAA_Color_Attachments_Reference{};
		const vector<const RHI_Attachment_Reference*> FXAA_Color_Attachment_References{
			&FXAA_Color_Attachments_Reference
		};

		//NOTE : UI_Subpass
		RHI_Subpass_Description UI_Subpass{};

		RHI_Attachment_Reference UI_Pass_Color_Attachments_Reference{};
		const vector<const RHI_Attachment_Reference*> UI_Pass_Color_Attachment_References{
			&UI_Pass_Color_Attachments_Reference
		};

		const vector<uint32_t> UI_Pass_Depth_Attachment_References{ _main_camera_pass_backup_buffer_odd };

		//NOTE : Combine_UI_Subpass
		RHI_Subpass_Description Combine_UI_Subpass{};

		RHI_Attachment_Reference Combine_UI_Backup_Odd_Input_Attachment_Reference{};
		RHI_Attachment_Reference Combine_UI_Backup_Even_Input_Attachment_Reference{};
		const vector<const RHI_Attachment_Reference*> Combine_UI_Input_Attachments_References{
			&Combine_UI_Backup_Odd_Input_Attachment_Reference,
			&Combine_UI_Backup_Even_Input_Attachment_Reference
		};

		RHI_Attachment_Reference Combine_UI_SwapChain_Image_Color_Attachment_Reference{};
		const vector<const RHI_Attachment_Reference*> Combine_UI_Color_Attachment_References{
			&Combine_UI_SwapChain_Image_Color_Attachment_Reference
		};

		const vector<const RHI_Subpass_Description*> Subpasses_Descriptions{
			&Base_Subpass,
			&Deferred_Lighting_Subpass,
			&Forward_Lighting_Subpass,
			&Tone_Mapping_Subpass,
			&Color_Grading_Subpass,
			&FXAA_Subpass,
			&UI_Subpass,
			&Combine_UI_Subpass
		};

		{
			{
				{
					{
						Base_Pass_Color_Attachment_Reference_A.Attachment = _main_camera_pass_gbuffer_a;
						Base_Pass_Color_Attachment_Reference_A.Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
					}

					{
						Base_Pass_Color_Attachment_Reference_B.Attachment = _main_camera_pass_gbuffer_b;
						Base_Pass_Color_Attachment_Reference_B.Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
					}

					{
						Base_Pass_Color_Attachment_Reference_C.Attachment = _main_camera_pass_gbuffer_c;
						Base_Pass_Color_Attachment_Reference_C.Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
					}
				}

				{
					Base_Pass_Depth_Attachment_Reference.Attachment = _main_camera_pass_depth;
					Base_Pass_Depth_Attachment_Reference.Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
				}

				{
					Base_Subpass.Flags = 0;
					Base_Subpass.Pipeline_Bind_Point = RHI_PIPELINE_BIND_POINT::RHI_PIPELINE_BIND_POINT_GRAPHICS;
					Base_Subpass.Input_Attachments = nullptr;
					Base_Subpass.Color_Attachments = &Base_Pass_Color_Attachments_References;
					Base_Subpass.Resolve_Attachments = nullptr;
					Base_Subpass.Depth_Stencil_Attachment = &Base_Pass_Depth_Attachment_Reference;
					Base_Subpass.Preserve_Attachments = nullptr;
				}
			}

			{
				{
					{
						Deferred_Lighting_Normal_Pass_Input_Attachments_Reference.Attachment = _main_camera_pass_gbuffer_a;
						Deferred_Lighting_Normal_Pass_Input_Attachments_Reference.Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
					}

					{
						Deferred_Lighting_Metallic_Roughness_Shadingmodeid_Pass_Input_Attachments_Reference.Attachment = _main_camera_pass_gbuffer_b;
						Deferred_Lighting_Metallic_Roughness_Shadingmodeid_Pass_Input_Attachments_Reference.Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
					}

					{
						Deferred_Lighting_Albedo_Pass_Input_Attachments_Reference.Attachment = _main_camera_pass_gbuffer_c;
						Deferred_Lighting_Albedo_Pass_Input_Attachments_Reference.Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
					}

					{
						Deferred_Lighting_Pass_Depth_Input_Attachments_Reference.Attachment = _main_camera_pass_depth;
						Deferred_Lighting_Pass_Depth_Input_Attachments_Reference.Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
					}
				}

				{
					Deferred_Lighting_Dpeth_Attachments_Reference.Attachment = _main_camera_pass_depth;
					Deferred_Lighting_Dpeth_Attachments_Reference.Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
				}

				{
					Deferred_Lighting_Backup_Odd_Color_Attachments_Reference.Attachment = _main_camera_pass_backup_buffer_odd;
					Deferred_Lighting_Backup_Odd_Color_Attachments_Reference.Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
				}

				{
					Deferred_Lighting_Subpass.Flags = 0;
					Deferred_Lighting_Subpass.Pipeline_Bind_Point = RHI_PIPELINE_BIND_POINT::RHI_PIPELINE_BIND_POINT_GRAPHICS;
					Deferred_Lighting_Subpass.Input_Attachments = &Deferred_Lighting_Input_Attachments_References;
					Deferred_Lighting_Subpass.Color_Attachments = &Deferred_Lighting_Color_Attachments_References;
					Deferred_Lighting_Subpass.Resolve_Attachments = nullptr;
					Deferred_Lighting_Subpass.Depth_Stencil_Attachment = nullptr;
					Deferred_Lighting_Subpass.Preserve_Attachments = nullptr;
				}
			}

			{
				{
					Forward_Lighting_Backup_Odd_Color_Pass_Attachments_Reference.Attachment = _main_camera_pass_backup_buffer_odd;
					Forward_Lighting_Backup_Odd_Color_Pass_Attachments_Reference.Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
				}

				{
					Forward_Lighting_Depth_Pass_Attachments_Reference.Attachment = _main_camera_pass_depth;
					Forward_Lighting_Depth_Pass_Attachments_Reference.Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
				}

				{
					Forward_Lighting_Subpass.Flags = 0;
					Forward_Lighting_Subpass.Pipeline_Bind_Point = RHI_PIPELINE_BIND_POINT::RHI_PIPELINE_BIND_POINT_GRAPHICS;
					Forward_Lighting_Subpass.Input_Attachments = nullptr;
					Forward_Lighting_Subpass.Color_Attachments = &Forward_Lighting_Color_Attachments_References;
					Forward_Lighting_Subpass.Resolve_Attachments = nullptr;
					Forward_Lighting_Subpass.Depth_Stencil_Attachment = &Forward_Lighting_Depth_Pass_Attachments_Reference;
					Forward_Lighting_Subpass.Preserve_Attachments = nullptr;
				}
			}

			{
				{
					Tone_Mapping_Input_Attachments_Reference.Attachment = _main_camera_pass_backup_buffer_odd;
					Tone_Mapping_Input_Attachments_Reference.Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
				}

				{
					Tone_Mapping_Color_Attachments_Reference.Attachment = _main_camera_pass_backup_buffer_even;
					Tone_Mapping_Color_Attachments_Reference.Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
				}

				{
					Tone_Mapping_Subpass.Flags = 0;
					Tone_Mapping_Subpass.Pipeline_Bind_Point = RHI_PIPELINE_BIND_POINT::RHI_PIPELINE_BIND_POINT_GRAPHICS;
					Tone_Mapping_Subpass.Input_Attachments = &Tone_Mapping_Input_Attachments_References;
					Tone_Mapping_Subpass.Color_Attachments = &Tone_Mapping_Color_Attachments_References;
					Tone_Mapping_Subpass.Resolve_Attachments = nullptr;
					Tone_Mapping_Subpass.Depth_Stencil_Attachment = nullptr;
					Tone_Mapping_Subpass.Preserve_Attachments = nullptr;
				}
			}

			{
				{
					Color_Grading_Pass_Input_Attachments_Reference.Attachment = _main_camera_pass_backup_buffer_even;
					Color_Grading_Pass_Input_Attachments_Reference.Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
				}

				//NOTE: FXAA
				{
					if (this->m_Enable_FXAA)
						Color_Grading_Color_Attachments_Reference.Attachment = _main_camera_pass_post_process_buffer_odd;
					else
						Color_Grading_Color_Attachments_Reference.Attachment = _main_camera_pass_backup_buffer_odd;

					Color_Grading_Color_Attachments_Reference.Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
				}

				{
					Color_Grading_Subpass.Flags = 0;
					Color_Grading_Subpass.Pipeline_Bind_Point = RHI_PIPELINE_BIND_POINT::RHI_PIPELINE_BIND_POINT_GRAPHICS;
					Color_Grading_Subpass.Input_Attachments = &Color_Grading_Input_Attachments_References;
					Color_Grading_Subpass.Color_Attachments = &Color_Grading_Color_Attachment_References;
					Color_Grading_Subpass.Resolve_Attachments = nullptr;
					Color_Grading_Subpass.Depth_Stencil_Attachment = nullptr;
					Color_Grading_Subpass.Preserve_Attachments = nullptr;
				}
			}

			{
				{
					if (this->m_Enable_FXAA)
						FXAA_Input_Attachments_Reference.Attachment = _main_camera_pass_post_process_buffer_odd;
					else
						FXAA_Input_Attachments_Reference.Attachment = _main_camera_pass_backup_buffer_even;
					FXAA_Input_Attachments_Reference.Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
				}

				{
					FXAA_Color_Attachments_Reference.Attachment = _main_camera_pass_backup_buffer_odd;
					FXAA_Color_Attachments_Reference.Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
				}

				{
					FXAA_Subpass.Flags = 0;
					FXAA_Subpass.Pipeline_Bind_Point = RHI_PIPELINE_BIND_POINT::RHI_PIPELINE_BIND_POINT_GRAPHICS;
					FXAA_Subpass.Input_Attachments = &FXAA_Input_Attachments_References;
					FXAA_Subpass.Color_Attachments = &FXAA_Color_Attachment_References;
					FXAA_Subpass.Resolve_Attachments = nullptr;
					FXAA_Subpass.Depth_Stencil_Attachment = nullptr;
					FXAA_Subpass.Preserve_Attachments = nullptr;
				}
			}

			{

				{
					UI_Pass_Color_Attachments_Reference.Attachment = _main_camera_pass_backup_buffer_even;
					UI_Pass_Color_Attachments_Reference.Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
				}

				{
					UI_Subpass.Flags = 0;
					UI_Subpass.Pipeline_Bind_Point = RHI_PIPELINE_BIND_POINT::RHI_PIPELINE_BIND_POINT_GRAPHICS;
					UI_Subpass.Input_Attachments = nullptr;
					UI_Subpass.Color_Attachments = &UI_Pass_Color_Attachment_References;
					UI_Subpass.Resolve_Attachments = nullptr;
					UI_Subpass.Depth_Stencil_Attachment = nullptr;
					UI_Subpass.Preserve_Attachments = &UI_Pass_Depth_Attachment_References;
				}
			}

			{
				{
					Combine_UI_Backup_Odd_Input_Attachment_Reference.Attachment = _main_camera_pass_backup_buffer_odd;
					Combine_UI_Backup_Odd_Input_Attachment_Reference.Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
				}

				{
					Combine_UI_Backup_Even_Input_Attachment_Reference.Attachment = _main_camera_pass_backup_buffer_even;
					Combine_UI_Backup_Even_Input_Attachment_Reference.Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
				}

				{
					Combine_UI_SwapChain_Image_Color_Attachment_Reference.Attachment = _main_camera_pass_swap_chain_image;
					Combine_UI_SwapChain_Image_Color_Attachment_Reference.Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
				}

				{
					Combine_UI_Subpass.Flags = 0;
					Combine_UI_Subpass.Pipeline_Bind_Point = RHI_PIPELINE_BIND_POINT::RHI_PIPELINE_BIND_POINT_GRAPHICS;
					Combine_UI_Subpass.Input_Attachments = &Combine_UI_Input_Attachments_References;
					Combine_UI_Subpass.Color_Attachments = &Combine_UI_Color_Attachment_References;
					Combine_UI_Subpass.Resolve_Attachments = nullptr;
					Combine_UI_Subpass.Depth_Stencil_Attachment = nullptr;
					Combine_UI_Subpass.Preserve_Attachments = nullptr;
				}
			}
		}

		//NOTE : Subpass_Dependencies
		RHI_Subpass_Dependency Deferred_Lighting_Pass_Depend_On_Shadow_Map_Pass{};
		RHI_Subpass_Dependency Deferred_Lighting_Pass_Depend_On_Base_Pass{};
		RHI_Subpass_Dependency Forward_Lighting_Pass_Depend_On_Deferred_Lighting_Pass{};
		RHI_Subpass_Dependency Tone_Mapping_Pass_Depend_On_Forward_Lighting_Pass{};
		RHI_Subpass_Dependency Color_Grading_Pass_Depend_On_Tone_Mapping_Pass{};
		RHI_Subpass_Dependency FAXX_Pass_Depend_On_Color_Grading_Pass{};
		RHI_Subpass_Dependency UI_Pass_Depend_On_Fxaa_Pass{};
		RHI_Subpass_Dependency Combine_UI_Pass_Depend_On_UI_Pass{};

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

		{
			{
				Deferred_Lighting_Pass_Depend_On_Shadow_Map_Pass.Src_Subpass = RHI_SUBPASS_EXTERNAL;
				Deferred_Lighting_Pass_Depend_On_Shadow_Map_Pass.Dst_Subpass = _main_camera_subpass_deferred_lighting;
				Deferred_Lighting_Pass_Depend_On_Shadow_Map_Pass.Src_Stage_Mask = to_underlying(RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT);
				Deferred_Lighting_Pass_Depend_On_Shadow_Map_Pass.Dst_Stage_Mask = to_underlying(RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_FRAGMENT_SHADER_BIT);
				Deferred_Lighting_Pass_Depend_On_Shadow_Map_Pass.Src_Access_Mask = to_underlying(RHI_ACCESS_FLAG_BITS::RHI_ACCESS_COLOR_ATTACHMENT_WRITE_BIT);
				Deferred_Lighting_Pass_Depend_On_Shadow_Map_Pass.Dst_Access_Mask = to_underlying(RHI_ACCESS_FLAG_BITS::RHI_ACCESS_SHADER_READ_BIT);
				Deferred_Lighting_Pass_Depend_On_Shadow_Map_Pass.Dependency_Flags = 0;
			}

			{
				Deferred_Lighting_Pass_Depend_On_Base_Pass.Src_Subpass = _main_camera_subpass_basepass;
				Deferred_Lighting_Pass_Depend_On_Base_Pass.Dst_Subpass = _main_camera_subpass_deferred_lighting;
				Deferred_Lighting_Pass_Depend_On_Base_Pass.Src_Stage_Mask = RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
				Deferred_Lighting_Pass_Depend_On_Base_Pass.Dst_Stage_Mask = RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
				Deferred_Lighting_Pass_Depend_On_Base_Pass.Src_Access_Mask = RHI_ACCESS_FLAG_BITS::RHI_ACCESS_SHADER_WRITE_BIT | RHI_ACCESS_FLAG_BITS::RHI_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
				Deferred_Lighting_Pass_Depend_On_Base_Pass.Dst_Access_Mask = RHI_ACCESS_FLAG_BITS::RHI_ACCESS_SHADER_READ_BIT | RHI_ACCESS_FLAG_BITS::RHI_ACCESS_COLOR_ATTACHMENT_READ_BIT;
				Deferred_Lighting_Pass_Depend_On_Base_Pass.Dependency_Flags = to_underlying(RHI_DEPENDENCY_FLAG_BITS::RHI_DEPENDENCY_BY_REGION_BIT);
			}

			{
				Forward_Lighting_Pass_Depend_On_Deferred_Lighting_Pass.Src_Subpass = _main_camera_subpass_deferred_lighting;
				Forward_Lighting_Pass_Depend_On_Deferred_Lighting_Pass.Dst_Subpass = _main_camera_subpass_forward_lighting;
				Forward_Lighting_Pass_Depend_On_Deferred_Lighting_Pass.Src_Stage_Mask = RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
				Forward_Lighting_Pass_Depend_On_Deferred_Lighting_Pass.Dst_Stage_Mask = RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
				Forward_Lighting_Pass_Depend_On_Deferred_Lighting_Pass.Src_Access_Mask = RHI_ACCESS_FLAG_BITS::RHI_ACCESS_SHADER_WRITE_BIT | RHI_ACCESS_FLAG_BITS::RHI_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
				Forward_Lighting_Pass_Depend_On_Deferred_Lighting_Pass.Dst_Access_Mask = RHI_ACCESS_FLAG_BITS::RHI_ACCESS_SHADER_WRITE_BIT | RHI_ACCESS_FLAG_BITS::RHI_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
				Forward_Lighting_Pass_Depend_On_Deferred_Lighting_Pass.Dependency_Flags = to_underlying(RHI_DEPENDENCY_FLAG_BITS::RHI_DEPENDENCY_BY_REGION_BIT);
			}

			{
				Tone_Mapping_Pass_Depend_On_Forward_Lighting_Pass.Src_Subpass = _main_camera_subpass_forward_lighting;
				Tone_Mapping_Pass_Depend_On_Forward_Lighting_Pass.Dst_Subpass = _main_camera_subpass_tone_mapping;
				Tone_Mapping_Pass_Depend_On_Forward_Lighting_Pass.Src_Stage_Mask = RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
				Tone_Mapping_Pass_Depend_On_Forward_Lighting_Pass.Dst_Stage_Mask = RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
				Tone_Mapping_Pass_Depend_On_Forward_Lighting_Pass.Src_Access_Mask = RHI_ACCESS_FLAG_BITS::RHI_ACCESS_SHADER_WRITE_BIT | RHI_ACCESS_FLAG_BITS::RHI_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
				Tone_Mapping_Pass_Depend_On_Forward_Lighting_Pass.Dst_Access_Mask = RHI_ACCESS_FLAG_BITS::RHI_ACCESS_SHADER_READ_BIT | RHI_ACCESS_FLAG_BITS::RHI_ACCESS_COLOR_ATTACHMENT_READ_BIT;
				Tone_Mapping_Pass_Depend_On_Forward_Lighting_Pass.Dependency_Flags = to_underlying(RHI_DEPENDENCY_FLAG_BITS::RHI_DEPENDENCY_BY_REGION_BIT);
			}

			{
				Color_Grading_Pass_Depend_On_Tone_Mapping_Pass.Src_Subpass = _main_camera_subpass_tone_mapping;
				Color_Grading_Pass_Depend_On_Tone_Mapping_Pass.Dst_Subpass = _main_camera_subpass_color_grading;
				Color_Grading_Pass_Depend_On_Tone_Mapping_Pass.Src_Stage_Mask = RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
				Color_Grading_Pass_Depend_On_Tone_Mapping_Pass.Dst_Stage_Mask = RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
				Color_Grading_Pass_Depend_On_Tone_Mapping_Pass.Src_Access_Mask = RHI_ACCESS_FLAG_BITS::RHI_ACCESS_SHADER_WRITE_BIT | RHI_ACCESS_FLAG_BITS::RHI_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
				Color_Grading_Pass_Depend_On_Tone_Mapping_Pass.Dst_Access_Mask = RHI_ACCESS_FLAG_BITS::RHI_ACCESS_SHADER_READ_BIT | RHI_ACCESS_FLAG_BITS::RHI_ACCESS_COLOR_ATTACHMENT_READ_BIT;
				Color_Grading_Pass_Depend_On_Tone_Mapping_Pass.Dependency_Flags = to_underlying(RHI_DEPENDENCY_FLAG_BITS::RHI_DEPENDENCY_BY_REGION_BIT);
			}

			{
				FAXX_Pass_Depend_On_Color_Grading_Pass.Src_Subpass = _main_camera_subpass_color_grading;
				FAXX_Pass_Depend_On_Color_Grading_Pass.Dst_Subpass = _main_camera_subpass_fxaa;
				FAXX_Pass_Depend_On_Color_Grading_Pass.Src_Stage_Mask = RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
				FAXX_Pass_Depend_On_Color_Grading_Pass.Dst_Stage_Mask = RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
				FAXX_Pass_Depend_On_Color_Grading_Pass.Src_Access_Mask = RHI_ACCESS_FLAG_BITS::RHI_ACCESS_SHADER_WRITE_BIT | RHI_ACCESS_FLAG_BITS::RHI_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
				FAXX_Pass_Depend_On_Color_Grading_Pass.Dst_Access_Mask = RHI_ACCESS_FLAG_BITS::RHI_ACCESS_SHADER_READ_BIT | RHI_ACCESS_FLAG_BITS::RHI_ACCESS_COLOR_ATTACHMENT_READ_BIT;
				FAXX_Pass_Depend_On_Color_Grading_Pass.Dependency_Flags = 0; //to_underlying(RHI_DEPENDENCY_FLAG_BITS::RHI_DEPENDENCY_BY_REGION_BIT);
			}

			{
				UI_Pass_Depend_On_Fxaa_Pass.Src_Subpass = _main_camera_subpass_fxaa;
				UI_Pass_Depend_On_Fxaa_Pass.Dst_Subpass = _main_camera_subpass_ui;
				UI_Pass_Depend_On_Fxaa_Pass.Src_Stage_Mask = RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
				UI_Pass_Depend_On_Fxaa_Pass.Dst_Stage_Mask = RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
				UI_Pass_Depend_On_Fxaa_Pass.Src_Access_Mask = RHI_ACCESS_FLAG_BITS::RHI_ACCESS_SHADER_WRITE_BIT | RHI_ACCESS_FLAG_BITS::RHI_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
				UI_Pass_Depend_On_Fxaa_Pass.Dst_Access_Mask = RHI_ACCESS_FLAG_BITS::RHI_ACCESS_SHADER_READ_BIT | RHI_ACCESS_FLAG_BITS::RHI_ACCESS_COLOR_ATTACHMENT_READ_BIT;
				UI_Pass_Depend_On_Fxaa_Pass.Dependency_Flags = to_underlying(RHI_DEPENDENCY_FLAG_BITS::RHI_DEPENDENCY_BY_REGION_BIT);
			}

			{
				Combine_UI_Pass_Depend_On_UI_Pass.Src_Subpass = _main_camera_subpass_ui;
				Combine_UI_Pass_Depend_On_UI_Pass.Dst_Subpass = _main_camera_subpass_combine_ui;
				Combine_UI_Pass_Depend_On_UI_Pass.Src_Stage_Mask = RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
				Combine_UI_Pass_Depend_On_UI_Pass.Dst_Stage_Mask = RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
				Combine_UI_Pass_Depend_On_UI_Pass.Src_Access_Mask = RHI_ACCESS_FLAG_BITS::RHI_ACCESS_SHADER_WRITE_BIT | RHI_ACCESS_FLAG_BITS::RHI_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
				Combine_UI_Pass_Depend_On_UI_Pass.Dst_Access_Mask = RHI_ACCESS_FLAG_BITS::RHI_ACCESS_SHADER_READ_BIT | RHI_ACCESS_FLAG_BITS::RHI_ACCESS_COLOR_ATTACHMENT_READ_BIT;
				Combine_UI_Pass_Depend_On_UI_Pass.Dependency_Flags = to_underlying(RHI_DEPENDENCY_FLAG_BITS::RHI_DEPENDENCY_BY_REGION_BIT);
			}
		}

		RHI_Render_Pass_Create_Info Render_Pass_Create_Info{};
		{
			Render_Pass_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
			Render_Pass_Create_Info.Attachments = &Attachments_Descriptions;
			Render_Pass_Create_Info.Subpasses = &Subpasses_Descriptions;
			Render_Pass_Create_Info.Dependencies = &Subpass_Dependencies;
		}

		this->m_Frame_Buffer.Render_Pass = this->m_RHI->Create_Render_Pass(&Render_Pass_Create_Info);
	}

	void Main_Camera_Pass::Setup_Descriptor_Set_Layout(void) {
		this->m_Descriptors.resize(_layout_type_count);

		{
			RHI_Descriptor_Set_Layout_Binding Mesh_Mesh_Layout_Binding{};
			{
				Mesh_Mesh_Layout_Binding.Binding = 0;
				Mesh_Mesh_Layout_Binding.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_STORAGE_BUFFER;
				Mesh_Mesh_Layout_Binding.Descriptor_Count = 1;
				Mesh_Mesh_Layout_Binding.Stage_Flags = to_underlying(RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_VERTEX_BIT);
				Mesh_Mesh_Layout_Binding.Immutable_Samplers = nullptr;
			}
			const vector<const RHI_Descriptor_Set_Layout_Binding*> Mesh_Mesh_Layout_Bindings{
				&Mesh_Mesh_Layout_Binding
			};

			RHI_Descriptor_Set_Layout_Create_Info Mesh_Mesh_Layout_Create_Info{};
			{
				Mesh_Mesh_Layout_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
				Mesh_Mesh_Layout_Create_Info.Bindings = &Mesh_Mesh_Layout_Bindings;
			}

			this->m_Descriptors[_per_mesh].Descriptor_Set_Layout = this->m_RHI->Create_Descriptor_Set_Layout(&Mesh_Mesh_Layout_Create_Info);
		}

		{
			RHI_Descriptor_Set_Layout_Binding Mesh_Global_Layout_Per_Frame_Storage_Buffer_Binding{};
			{
				Mesh_Global_Layout_Per_Frame_Storage_Buffer_Binding.Binding = 0;
				Mesh_Global_Layout_Per_Frame_Storage_Buffer_Binding.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;
				Mesh_Global_Layout_Per_Frame_Storage_Buffer_Binding.Descriptor_Count = 1;
				Mesh_Global_Layout_Per_Frame_Storage_Buffer_Binding.Stage_Flags = RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_VERTEX_BIT | RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_FRAGMENT_BIT;
				Mesh_Global_Layout_Per_Frame_Storage_Buffer_Binding.Immutable_Samplers = nullptr;
			}

			RHI_Descriptor_Set_Layout_Binding Mesh_Global_Lyout_Per_Draw_Call_Storage_Buffer_Binding{};
			{
				Mesh_Global_Lyout_Per_Draw_Call_Storage_Buffer_Binding.Binding = 1;
				Mesh_Global_Lyout_Per_Draw_Call_Storage_Buffer_Binding.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;
				Mesh_Global_Lyout_Per_Draw_Call_Storage_Buffer_Binding.Descriptor_Count = 1;
				Mesh_Global_Lyout_Per_Draw_Call_Storage_Buffer_Binding.Stage_Flags = to_underlying(RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_VERTEX_BIT);
				Mesh_Global_Lyout_Per_Draw_Call_Storage_Buffer_Binding.Immutable_Samplers = nullptr;
			}

			RHI_Descriptor_Set_Layout_Binding Mesh_Global_Lyout_Per_Draw_Call_Vertex_Blending_Storage_Buffer_Binding{};
			{
				Mesh_Global_Lyout_Per_Draw_Call_Vertex_Blending_Storage_Buffer_Binding.Binding = 2;
				Mesh_Global_Lyout_Per_Draw_Call_Vertex_Blending_Storage_Buffer_Binding.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;
				Mesh_Global_Lyout_Per_Draw_Call_Vertex_Blending_Storage_Buffer_Binding.Descriptor_Count = 1;
				Mesh_Global_Lyout_Per_Draw_Call_Vertex_Blending_Storage_Buffer_Binding.Stage_Flags = to_underlying(RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_VERTEX_BIT);
				Mesh_Global_Lyout_Per_Draw_Call_Vertex_Blending_Storage_Buffer_Binding.Immutable_Samplers = nullptr;
			}

			RHI_Descriptor_Set_Layout_Binding Mesh_Global_Lyaout_BRDF_LUT_Image_Binding{};
			{
				Mesh_Global_Lyaout_BRDF_LUT_Image_Binding.Binding = 3;
				Mesh_Global_Lyaout_BRDF_LUT_Image_Binding.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
				Mesh_Global_Lyaout_BRDF_LUT_Image_Binding.Descriptor_Count = 1;
				Mesh_Global_Lyaout_BRDF_LUT_Image_Binding.Stage_Flags = to_underlying(RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_FRAGMENT_BIT);
				Mesh_Global_Lyaout_BRDF_LUT_Image_Binding.Immutable_Samplers = nullptr;
			}

			RHI_Descriptor_Set_Layout_Binding Mesh_Global_Layout_Irradiance_Image_Binding{};
			{
				Mesh_Global_Layout_Irradiance_Image_Binding.Binding = 4;
				Mesh_Global_Layout_Irradiance_Image_Binding.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
				Mesh_Global_Layout_Irradiance_Image_Binding.Descriptor_Count = 1;
				Mesh_Global_Layout_Irradiance_Image_Binding.Stage_Flags = to_underlying(RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_FRAGMENT_BIT);
				Mesh_Global_Layout_Irradiance_Image_Binding.Immutable_Samplers = nullptr;
			}

			RHI_Descriptor_Set_Layout_Binding Mesh_Global_Layout_Specular_Image_Binding{};
			{
				Mesh_Global_Layout_Specular_Image_Binding.Binding = 5;
				Mesh_Global_Layout_Specular_Image_Binding.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
				Mesh_Global_Layout_Specular_Image_Binding.Descriptor_Count = 1;
				Mesh_Global_Layout_Specular_Image_Binding.Stage_Flags = to_underlying(RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_FRAGMENT_BIT);
				Mesh_Global_Layout_Specular_Image_Binding.Immutable_Samplers = nullptr;
			}

			RHI_Descriptor_Set_Layout_Binding Mesh_Global_Layout_Point_Light_Shadow_Map_Image_Binding{};
			{
				Mesh_Global_Layout_Point_Light_Shadow_Map_Image_Binding.Binding = 6;
				Mesh_Global_Layout_Point_Light_Shadow_Map_Image_Binding.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
				Mesh_Global_Layout_Point_Light_Shadow_Map_Image_Binding.Descriptor_Count = 1;
				Mesh_Global_Layout_Point_Light_Shadow_Map_Image_Binding.Stage_Flags = to_underlying(RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_FRAGMENT_BIT);
				Mesh_Global_Layout_Point_Light_Shadow_Map_Image_Binding.Immutable_Samplers = nullptr;
			}

			RHI_Descriptor_Set_Layout_Binding Mesh_Global_Layout_Directional_Light_Shadow_Map_Image_Binding{};
			{
				Mesh_Global_Layout_Directional_Light_Shadow_Map_Image_Binding.Binding = 7;
				Mesh_Global_Layout_Directional_Light_Shadow_Map_Image_Binding.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
				Mesh_Global_Layout_Directional_Light_Shadow_Map_Image_Binding.Descriptor_Count = 1;
				Mesh_Global_Layout_Directional_Light_Shadow_Map_Image_Binding.Stage_Flags = to_underlying(RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_FRAGMENT_BIT);
				Mesh_Global_Layout_Directional_Light_Shadow_Map_Image_Binding.Immutable_Samplers = nullptr;
			}

			const vector<const RHI_Descriptor_Set_Layout_Binding*> Mesh_Global_Layout_Bingdings{
				&Mesh_Global_Layout_Per_Frame_Storage_Buffer_Binding,
				&Mesh_Global_Lyout_Per_Draw_Call_Storage_Buffer_Binding,
				&Mesh_Global_Lyout_Per_Draw_Call_Vertex_Blending_Storage_Buffer_Binding,
				&Mesh_Global_Lyaout_BRDF_LUT_Image_Binding,
				&Mesh_Global_Layout_Irradiance_Image_Binding,
				&Mesh_Global_Layout_Specular_Image_Binding,
				&Mesh_Global_Layout_Point_Light_Shadow_Map_Image_Binding,
				&Mesh_Global_Layout_Directional_Light_Shadow_Map_Image_Binding
			};

			RHI_Descriptor_Set_Layout_Create_Info Material_Layout_Create_Info{};
			{
				Material_Layout_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
				Material_Layout_Create_Info.Bindings = &Mesh_Global_Layout_Bingdings;
			}

			this->m_Descriptors[_mesh_global].Descriptor_Set_Layout = this->m_RHI->Create_Descriptor_Set_Layout(&Material_Layout_Create_Info);
		}

		{
			RHI_Descriptor_Set_Layout_Binding Mesh_Material_Layout_Uniform_Buffer_Binding{};
			{
				Mesh_Material_Layout_Uniform_Buffer_Binding.Binding = 0;
				Mesh_Material_Layout_Uniform_Buffer_Binding.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
				Mesh_Material_Layout_Uniform_Buffer_Binding.Descriptor_Count = 1;
				Mesh_Material_Layout_Uniform_Buffer_Binding.Stage_Flags = to_underlying(RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_FRAGMENT_BIT);
				Mesh_Material_Layout_Uniform_Buffer_Binding.Immutable_Samplers = nullptr;
			}

			RHI_Descriptor_Set_Layout_Binding Mesh_Material_Layout_Base_Color_Image_Binding{};
			{
				Mesh_Material_Layout_Base_Color_Image_Binding.Binding = 1;
				Mesh_Material_Layout_Base_Color_Image_Binding.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
				Mesh_Material_Layout_Base_Color_Image_Binding.Descriptor_Count = 1;
				Mesh_Material_Layout_Base_Color_Image_Binding.Stage_Flags = to_underlying(RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_FRAGMENT_BIT);
				Mesh_Material_Layout_Base_Color_Image_Binding.Immutable_Samplers = nullptr;
			}

			RHI_Descriptor_Set_Layout_Binding Mesh_Material_Layout_Metallic_Roughness_Image_Binding{};
			{
				Mesh_Material_Layout_Metallic_Roughness_Image_Binding.Binding = 2;
				Mesh_Material_Layout_Metallic_Roughness_Image_Binding.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
				Mesh_Material_Layout_Metallic_Roughness_Image_Binding.Descriptor_Count = 1;
				Mesh_Material_Layout_Metallic_Roughness_Image_Binding.Stage_Flags = to_underlying(RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_FRAGMENT_BIT);
				Mesh_Material_Layout_Metallic_Roughness_Image_Binding.Immutable_Samplers = nullptr;
			}

			RHI_Descriptor_Set_Layout_Binding Mesh_Material_Layout_Normal_Image_Binding{};
			{
				Mesh_Material_Layout_Normal_Image_Binding.Binding = 3;
				Mesh_Material_Layout_Normal_Image_Binding.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
				Mesh_Material_Layout_Normal_Image_Binding.Descriptor_Count = 1;
				Mesh_Material_Layout_Normal_Image_Binding.Stage_Flags = to_underlying(RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_FRAGMENT_BIT);
				Mesh_Material_Layout_Normal_Image_Binding.Immutable_Samplers = nullptr;
			}

			RHI_Descriptor_Set_Layout_Binding Mesh_Material_Layout_Occlusion_Image_Binding{};
			{
				Mesh_Material_Layout_Occlusion_Image_Binding.Binding = 4;
				Mesh_Material_Layout_Occlusion_Image_Binding.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
				Mesh_Material_Layout_Occlusion_Image_Binding.Descriptor_Count = 1;
				Mesh_Material_Layout_Occlusion_Image_Binding.Stage_Flags = to_underlying(RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_FRAGMENT_BIT);
				Mesh_Material_Layout_Occlusion_Image_Binding.Immutable_Samplers = nullptr;
			}

			RHI_Descriptor_Set_Layout_Binding Mesh_Material_Layout_Emissive_Image_Binding{};
			{
				Mesh_Material_Layout_Emissive_Image_Binding.Binding = 5;
				Mesh_Material_Layout_Emissive_Image_Binding.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
				Mesh_Material_Layout_Emissive_Image_Binding.Descriptor_Count = 1;
				Mesh_Material_Layout_Emissive_Image_Binding.Stage_Flags = to_underlying(RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_FRAGMENT_BIT);
				Mesh_Material_Layout_Emissive_Image_Binding.Immutable_Samplers = nullptr;
			}

			const vector<const RHI_Descriptor_Set_Layout_Binding*> Mesh_Material_Layout_Bindings{
				&Mesh_Material_Layout_Uniform_Buffer_Binding,
				&Mesh_Material_Layout_Base_Color_Image_Binding,
				&Mesh_Material_Layout_Metallic_Roughness_Image_Binding,
				&Mesh_Material_Layout_Normal_Image_Binding,
				&Mesh_Material_Layout_Occlusion_Image_Binding,
				&Mesh_Material_Layout_Emissive_Image_Binding
			};

			RHI_Descriptor_Set_Layout_Create_Info Texture_Layout_Create_Info{};
			{
				Texture_Layout_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
				Texture_Layout_Create_Info.Bindings = &Mesh_Material_Layout_Bindings;
			}

			this->m_Descriptors[_mesh_per_material].Descriptor_Set_Layout = this->m_RHI->Create_Descriptor_Set_Layout(&Texture_Layout_Create_Info);
		}

		{
			RHI_Descriptor_Set_Layout_Binding SkyBox_Layout_Per_Frame_Storage_Buffer_Binding{};
			{
				SkyBox_Layout_Per_Frame_Storage_Buffer_Binding.Binding = 0;
				SkyBox_Layout_Per_Frame_Storage_Buffer_Binding.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;
				SkyBox_Layout_Per_Frame_Storage_Buffer_Binding.Descriptor_Count = 1;
				SkyBox_Layout_Per_Frame_Storage_Buffer_Binding.Stage_Flags = to_underlying(RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_VERTEX_BIT);
				SkyBox_Layout_Per_Frame_Storage_Buffer_Binding.Immutable_Samplers = nullptr;
			}

			RHI_Descriptor_Set_Layout_Binding SkyBox_Layout_Specular_Image_Binding{};
			{
				SkyBox_Layout_Specular_Image_Binding.Binding = 1;
				SkyBox_Layout_Specular_Image_Binding.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
				SkyBox_Layout_Specular_Image_Binding.Descriptor_Count = 1;
				SkyBox_Layout_Specular_Image_Binding.Stage_Flags = to_underlying(RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_FRAGMENT_BIT);
				SkyBox_Layout_Specular_Image_Binding.Immutable_Samplers = nullptr;
			}

			const vector<const RHI_Descriptor_Set_Layout_Binding*> SkyBox_Layout_Bindings{
				&SkyBox_Layout_Per_Frame_Storage_Buffer_Binding,
				&SkyBox_Layout_Specular_Image_Binding
			};

			RHI_Descriptor_Set_Layout_Create_Info SkyBox_Layout_Create_Info{};
			{
				SkyBox_Layout_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
				SkyBox_Layout_Create_Info.Bindings = &SkyBox_Layout_Bindings;
			}

			this->m_Descriptors[_skybox].Descriptor_Set_Layout = this->m_RHI->Create_Descriptor_Set_Layout(&SkyBox_Layout_Create_Info);
		}

		{
			RHI_Descriptor_Set_Layout_Binding Axis_Layout_Per_Frame_Storage_Buffer_Binding{};
			{
				Axis_Layout_Per_Frame_Storage_Buffer_Binding.Binding = 0;
				Axis_Layout_Per_Frame_Storage_Buffer_Binding.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;
				Axis_Layout_Per_Frame_Storage_Buffer_Binding.Descriptor_Count = 1;
				Axis_Layout_Per_Frame_Storage_Buffer_Binding.Stage_Flags = to_underlying(RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_VERTEX_BIT);
				Axis_Layout_Per_Frame_Storage_Buffer_Binding.Immutable_Samplers = nullptr;
			}

			RHI_Descriptor_Set_Layout_Binding Axis_Layout_Storage_Buffer_Binding{};
			{
				Axis_Layout_Storage_Buffer_Binding.Binding = 1;
				Axis_Layout_Storage_Buffer_Binding.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_STORAGE_BUFFER;
				Axis_Layout_Storage_Buffer_Binding.Descriptor_Count = 1;
				Axis_Layout_Storage_Buffer_Binding.Stage_Flags = to_underlying(RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_VERTEX_BIT);
				Axis_Layout_Storage_Buffer_Binding.Immutable_Samplers = nullptr;
			}

			const vector<const RHI_Descriptor_Set_Layout_Binding*> Axis_Layout_Bindings{
				&Axis_Layout_Per_Frame_Storage_Buffer_Binding,
				&Axis_Layout_Storage_Buffer_Binding
			};

			RHI_Descriptor_Set_Layout_Create_Info Axis_Layout_Create_Info{};
			{
				Axis_Layout_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
				Axis_Layout_Create_Info.Bindings = &Axis_Layout_Bindings;
			}

			this->m_Descriptors[_axis].Descriptor_Set_Layout = this->m_RHI->Create_Descriptor_Set_Layout(&Axis_Layout_Create_Info);

		}

		{
			RHI_Descriptor_Set_Layout_Binding GBuffer_Normal_Global_Layout_Input_Attachment_Binding{};
			{
				GBuffer_Normal_Global_Layout_Input_Attachment_Binding.Binding = 0;
				GBuffer_Normal_Global_Layout_Input_Attachment_Binding.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_INPUT_ATTACHMENT;
				GBuffer_Normal_Global_Layout_Input_Attachment_Binding.Descriptor_Count = 1;
				GBuffer_Normal_Global_Layout_Input_Attachment_Binding.Stage_Flags = to_underlying(RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_FRAGMENT_BIT);
				GBuffer_Normal_Global_Layout_Input_Attachment_Binding.Immutable_Samplers = nullptr;
			}

			RHI_Descriptor_Set_Layout_Binding GBuffer_Metallic_Roughness_Shadingmodeid_Global_Layout_Input_Attachment_Binding{};
			{
				GBuffer_Metallic_Roughness_Shadingmodeid_Global_Layout_Input_Attachment_Binding.Binding = 1;
				GBuffer_Metallic_Roughness_Shadingmodeid_Global_Layout_Input_Attachment_Binding.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_INPUT_ATTACHMENT;
				GBuffer_Metallic_Roughness_Shadingmodeid_Global_Layout_Input_Attachment_Binding.Descriptor_Count = 1;
				GBuffer_Metallic_Roughness_Shadingmodeid_Global_Layout_Input_Attachment_Binding.Stage_Flags = to_underlying(RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_FRAGMENT_BIT);
				GBuffer_Metallic_Roughness_Shadingmodeid_Global_Layout_Input_Attachment_Binding.Immutable_Samplers = nullptr;
			}

			RHI_Descriptor_Set_Layout_Binding GBuffer_Albedo_Global_Layout_Input_Attachment_Binding{};
			{
				GBuffer_Albedo_Global_Layout_Input_Attachment_Binding.Binding = 2;
				GBuffer_Albedo_Global_Layout_Input_Attachment_Binding.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_INPUT_ATTACHMENT;
				GBuffer_Albedo_Global_Layout_Input_Attachment_Binding.Descriptor_Count = 1;
				GBuffer_Albedo_Global_Layout_Input_Attachment_Binding.Stage_Flags = to_underlying(RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_FRAGMENT_BIT);
				GBuffer_Albedo_Global_Layout_Input_Attachment_Binding.Immutable_Samplers = nullptr;
			}

			RHI_Descriptor_Set_Layout_Binding GBuffer_Depth_Emissive_Global_Layout_Input_Attachment_Binding{};
			{
				GBuffer_Depth_Emissive_Global_Layout_Input_Attachment_Binding.Binding = 3;
				GBuffer_Depth_Emissive_Global_Layout_Input_Attachment_Binding.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_INPUT_ATTACHMENT;
				GBuffer_Depth_Emissive_Global_Layout_Input_Attachment_Binding.Descriptor_Count = 1;
				GBuffer_Depth_Emissive_Global_Layout_Input_Attachment_Binding.Stage_Flags = to_underlying(RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_FRAGMENT_BIT);
				GBuffer_Depth_Emissive_Global_Layout_Input_Attachment_Binding.Immutable_Samplers = nullptr;
			}


			const vector<const RHI_Descriptor_Set_Layout_Binding*> GBuffer_Layout_Bindings{
				&GBuffer_Normal_Global_Layout_Input_Attachment_Binding,
				&GBuffer_Metallic_Roughness_Shadingmodeid_Global_Layout_Input_Attachment_Binding,
				&GBuffer_Albedo_Global_Layout_Input_Attachment_Binding,
				&GBuffer_Depth_Emissive_Global_Layout_Input_Attachment_Binding
			};

			RHI_Descriptor_Set_Layout_Create_Info GBuffer_Layout_Create_Info{};
			{
				GBuffer_Layout_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
				GBuffer_Layout_Create_Info.Bindings = &GBuffer_Layout_Bindings;
			}

			this->m_Descriptors[_deferred_lighting].Descriptor_Set_Layout = this->m_RHI->Create_Descriptor_Set_Layout(&GBuffer_Layout_Create_Info);
		}
	}

	void Main_Camera_Pass::Setup_Descriptor_Set(void) {
		this->Setup_Model_Global_Descriptor_Set();
		this->Setup_Skybox_Descriptor_Set();
		this->Setup_Axis_Descriptor_Set();
		this->Setup_GBuffer_Lighting_Descriptor_Set();
	}

	void Main_Camera_Pass::Setup_Pipeline(void) {

		this->m_Render_Pipelines.resize(_render_pipeline_type_count);

		//NOTE :Mesh GBuffer
		{
			vector<RHI_Descriptor_Set_Layout*> Descriptor_Set_Layouts{
					this->m_Descriptors[_mesh_global].Descriptor_Set_Layout.get(),
					this->m_Descriptors[_per_mesh].Descriptor_Set_Layout.get(),
					this->m_Descriptors[_mesh_per_material].Descriptor_Set_Layout.get(),
			};

			RHI_Pipeline_Layout_Create_Info Pipeline_Layout_Create_Info{};
			{
				Pipeline_Layout_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
				Pipeline_Layout_Create_Info.Flags = 0;
				Pipeline_Layout_Create_Info.Set_Layouts = &Descriptor_Set_Layouts;
				Pipeline_Layout_Create_Info.Push_Constant_Ranges = nullptr;
			}

			this->m_Render_Pipelines[_render_pipeline_type_mesh_gbuffer].Pipeline_Layout = this->m_RHI->Create_Pipeline_Layout(&Pipeline_Layout_Create_Info);

			unique_ptr<RHI_Shader_Module> Vertex_Shader_Module{ this->m_RHI->Create_Shader_Module(&MESH_VERT) };

			RHI_Pipeline_Shader_Stage_Create_Info Vert_Pipeline_Shader_Stage_Create_Inof{};
			{
				Vert_Pipeline_Shader_Stage_Create_Inof.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
				Vert_Pipeline_Shader_Stage_Create_Inof.Flags = 0;
				Vert_Pipeline_Shader_Stage_Create_Inof.Stage = RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_VERTEX_BIT;
				Vert_Pipeline_Shader_Stage_Create_Inof.Module = Vertex_Shader_Module.get();
				Vert_Pipeline_Shader_Stage_Create_Inof.Name = "main";
				Vert_Pipeline_Shader_Stage_Create_Inof.Specialization_Info = nullptr;
			}

			unique_ptr<RHI_Shader_Module> Fragment_Shader_Module{ this->m_RHI->Create_Shader_Module(&MESH_GBUFFER_FRAG) };

			RHI_Pipeline_Shader_Stage_Create_Info Frag_Pipeline_Shader_Stage_Create_Inof{};
			{
				Frag_Pipeline_Shader_Stage_Create_Inof.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
				Frag_Pipeline_Shader_Stage_Create_Inof.Flags = 0;
				Frag_Pipeline_Shader_Stage_Create_Inof.Stage = RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_FRAGMENT_BIT;
				Frag_Pipeline_Shader_Stage_Create_Inof.Module = Fragment_Shader_Module.get();
				Frag_Pipeline_Shader_Stage_Create_Inof.Name = "main";
				Frag_Pipeline_Shader_Stage_Create_Inof.Specialization_Info = nullptr;
			}

			const vector<const RHI_Pipeline_Shader_Stage_Create_Info*> Shader_Stages{
				&Vert_Pipeline_Shader_Stage_Create_Inof,
				&Frag_Pipeline_Shader_Stage_Create_Inof
			};

			RHI_Pipeline_Vertex_Input_State_Create_Info Vertex_Input_State_Create_Info{};
			{
				Vertex_Input_State_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
				Vertex_Input_State_Create_Info.Flags = 0;
				Vertex_Input_State_Create_Info.Vertex_Binding_Descriptions = Mesh_Vertex::Get_Vertex_Input_Binding_Description();
				Vertex_Input_State_Create_Info.Vertex_Attribute_Descriptions = Mesh_Vertex::Get_Vertex_Input_Attribute_Description();
			}

			RHI_Pipeline_Input_Assembly_State_Create_Info Input_Assembly_State_Create_Info{};
			{
				Input_Assembly_State_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
				Input_Assembly_State_Create_Info.Flags = 0;
				Input_Assembly_State_Create_Info.Topology = RHI_PRIMITIVE_TOPOLOGY::RHI_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
				Input_Assembly_State_Create_Info.Primitive_Restart_Enable = RHI_FALSE;
			}

			const vector<const RHI_Viewport*> Viewports{
					&this->m_RHI->Get_SwapChain_Viewport()
			};

			const vector<const RHI_Rect_2D*> Scissors{
				&this->m_RHI->Get_SwapChain_Scissor()
			};

			RHI_Pipeline_Viewport_State_Create_Info Viewport_State_Create_Info{};
			{
				Viewport_State_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
				Viewport_State_Create_Info.Flags = 0;
				Viewport_State_Create_Info.Viewports = &Viewports;
				Viewport_State_Create_Info.Scissors = &Scissors;
			}

			RHI_Pipeline_Rasterization_State_Create_Info Rasterization_State_Create_Info{};
			{
				Rasterization_State_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
				Rasterization_State_Create_Info.Flags = 0;
				Rasterization_State_Create_Info.Depth_Clamp_Enable = RHI_FALSE;
				Rasterization_State_Create_Info.Rasterizer_Discard_Enable = RHI_FALSE;
				Rasterization_State_Create_Info.Polygon_Mode = RHI_POLYGON_MODE::RHI_POLYGON_MODE_FILL;
				Rasterization_State_Create_Info.Cull_Mode = to_underlying(RHI_CULL_MODE_FLAG_BITS::RHI_CULL_MODE_BACK_BIT);
				Rasterization_State_Create_Info.Front_Face = RHI_FRONT_FACE::RHI_FRONT_FACE_COUNTER_CLOCKWISE;
				Rasterization_State_Create_Info.Depth_Bias_Enable = RHI_FALSE;
				Rasterization_State_Create_Info.Depth_Bias_Constant_Factor = 0.0f;
				Rasterization_State_Create_Info.Depth_Bias_Clamp = 0.0f;
				Rasterization_State_Create_Info.Depth_Bias_Slope_Factor = 0.0f;
				Rasterization_State_Create_Info.Line_Width = 1.0f;
			}

			RHI_Pipeline_Multisample_State_Create_Info Multisample_State_Create_Info{};
			{
				Multisample_State_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
				Multisample_State_Create_Info.Flags = 0;
				Multisample_State_Create_Info.Rasterization_Samples = RHI_SAMPLE_COUNT_FLAG_BIT::RHI_SAMPLE_COUNT_1_BIT;
				Multisample_State_Create_Info.Sample_Shading_Enable = RHI_FALSE;
				Multisample_State_Create_Info.Min_Sample_Shading = 0.0f;
			}

			RHI_Pipeline_Depth_Stencil_State_Create_Info Depth_Stencil_State_Create_Info{};
			{
				Depth_Stencil_State_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
				Depth_Stencil_State_Create_Info.Flags = 0;
				Depth_Stencil_State_Create_Info.Depth_Test_Enable = RHI_TRUE;
				Depth_Stencil_State_Create_Info.Depth_Write_Enable = RHI_TRUE;
				Depth_Stencil_State_Create_Info.Depth_Compare_Op = RHI_COMPARE_OP::RHI_COMPARE_OP_LESS;
				Depth_Stencil_State_Create_Info.Depth_Bounds_Test_Enable = RHI_FALSE;
				Depth_Stencil_State_Create_Info.Stencil_Test_Enable = RHI_FALSE;
				Depth_Stencil_State_Create_Info.Front = {};
				Depth_Stencil_State_Create_Info.Back = {};
				Depth_Stencil_State_Create_Info.Min_Depth_Bounds = 0.0f;
				Depth_Stencil_State_Create_Info.Max_Depth_Bounds = 1.0f;
			}

			RHI_Pipeline_Color_Blend_Attachment_State Color_Blend_Attachment{};
			{
				Color_Blend_Attachment.Blend_Enable = RHI_FALSE;
				Color_Blend_Attachment.Src_Color_Blend_Factor = RHI_BLEND_FACTOR::RHI_BLEND_FACTOR_ONE;
				Color_Blend_Attachment.Dst_Color_Blend_Factor = RHI_BLEND_FACTOR::RHI_BLEND_FACTOR_ZERO;
				Color_Blend_Attachment.Color_Blend_Op = RHI_BLEND_OP::RHI_BLEND_OP_ADD;
				Color_Blend_Attachment.Src_Alpha_Blend_Factor = RHI_BLEND_FACTOR::RHI_BLEND_FACTOR_ONE;
				Color_Blend_Attachment.Dst_Alpha_Blend_Factor = RHI_BLEND_FACTOR::RHI_BLEND_FACTOR_ZERO;
				Color_Blend_Attachment.Alpha_Blend_Op = RHI_BLEND_OP::RHI_BLEND_OP_ADD;
				Color_Blend_Attachment.Color_Write_Mask =
					RHI_COLOR_COMPONENT_FLAG_BITS::RHI_COLOR_COMPONENT_R_BIT |
					RHI_COLOR_COMPONENT_FLAG_BITS::RHI_COLOR_COMPONENT_G_BIT |
					RHI_COLOR_COMPONENT_FLAG_BITS::RHI_COLOR_COMPONENT_B_BIT |
					RHI_COLOR_COMPONENT_FLAG_BITS::RHI_COLOR_COMPONENT_A_BIT;
			}
			const vector<const RHI_Pipeline_Color_Blend_Attachment_State*> Color_Blend_Attachments{
					&Color_Blend_Attachment,
					&Color_Blend_Attachment,
					&Color_Blend_Attachment,
			};

			RHI_Pipeline_Color_Blend_State_Create_Info Color_Blend_State_Create_Info{};
			{
				Color_Blend_State_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
				Color_Blend_State_Create_Info.Flags = 0;
				Color_Blend_State_Create_Info.Logic_Op_Enable = RHI_FALSE;
				Color_Blend_State_Create_Info.Logic_Op = NameSpace_RHI::RHI_LOGIC_OP::RHI_LOGIC_OP_COPY;
				Color_Blend_State_Create_Info.Attachments = &Color_Blend_Attachments;
				Color_Blend_State_Create_Info.Blend_Constants = { 0.0f,0.0f,0.0f,0.0f };
			}

			const vector<RHI_DYNAMIC_STATE> Dynamic_States{
					RHI_DYNAMIC_STATE::RHI_DYNAMIC_STATE_VIEWPORT,
					RHI_DYNAMIC_STATE::RHI_DYNAMIC_STATE_SCISSOR
			};

			RHI_Pipeline_Dynamic_State_Create_Info Dynamic_State_Create_Info{};
			{
				Dynamic_State_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
				Dynamic_State_Create_Info.Flags = 0;
				Dynamic_State_Create_Info.Dynamic_States = &Dynamic_States;
			}

			RHI_Graphics_Pipeline_Create_Info Graphics_Pipeline_Create_Info{};
			{
				Graphics_Pipeline_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
				Graphics_Pipeline_Create_Info.Flags = 0;
				Graphics_Pipeline_Create_Info.Stages = &Shader_Stages;
				Graphics_Pipeline_Create_Info.Vertex_Input_State = &Vertex_Input_State_Create_Info;
				Graphics_Pipeline_Create_Info.Input_Assembly_State = &Input_Assembly_State_Create_Info;
				Graphics_Pipeline_Create_Info.Tessellation_State = nullptr;
				Graphics_Pipeline_Create_Info.Viewport_State = &Viewport_State_Create_Info;
				Graphics_Pipeline_Create_Info.Rasterization_State = &Rasterization_State_Create_Info;
				Graphics_Pipeline_Create_Info.Multisample_State = &Multisample_State_Create_Info;
				Graphics_Pipeline_Create_Info.Depth_Stencil_State = &Depth_Stencil_State_Create_Info;
				Graphics_Pipeline_Create_Info.Color_Blend_State = &Color_Blend_State_Create_Info;
				Graphics_Pipeline_Create_Info.Dynamic_State = &Dynamic_State_Create_Info;
				Graphics_Pipeline_Create_Info.Layout = this->m_Render_Pipelines[_render_pipeline_type_mesh_gbuffer].Pipeline_Layout.get();
				Graphics_Pipeline_Create_Info.Render_Pass = this->m_Frame_Buffer.Render_Pass.get();
				Graphics_Pipeline_Create_Info.Subpass = _main_camera_subpass_basepass;
				Graphics_Pipeline_Create_Info.Base_Pipeline_Handle = RHI_NULL_HANDLE;
				Graphics_Pipeline_Create_Info.Base_Pipeline_Index = 0;
			}

			this->m_Render_Pipelines[_render_pipeline_type_mesh_gbuffer].Pipeline = this->m_RHI->Create_Graphics_Pipeline(&Graphics_Pipeline_Create_Info);
		}

		//NOTE : Deferred Lighting
		{
			vector<RHI_Descriptor_Set_Layout*> Descriptor_Set_Layouts{
					this->m_Descriptors[_mesh_global].Descriptor_Set_Layout.get(),
					this->m_Descriptors[_deferred_lighting].Descriptor_Set_Layout.get(),
					this->m_Descriptors[_skybox].Descriptor_Set_Layout.get(),
			};

			RHI_Pipeline_Layout_Create_Info Pipeline_Layout_Create_Info{};
			{
				Pipeline_Layout_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
				Pipeline_Layout_Create_Info.Flags = 0;
				Pipeline_Layout_Create_Info.Set_Layouts = &Descriptor_Set_Layouts;
				Pipeline_Layout_Create_Info.Push_Constant_Ranges = nullptr;
			}

			this->m_Render_Pipelines[_render_pipeline_type_deferred_lighting].Pipeline_Layout = this->m_RHI->Create_Pipeline_Layout(&Pipeline_Layout_Create_Info);

			unique_ptr<RHI_Shader_Module> Vertex_Shader_Module{ this->m_RHI->Create_Shader_Module(&DEFERRED_LIGHTING_VERT) };

			RHI_Pipeline_Shader_Stage_Create_Info Vert_Pipeline_Shader_Stage_Create_Inof{};
			{
				Vert_Pipeline_Shader_Stage_Create_Inof.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
				Vert_Pipeline_Shader_Stage_Create_Inof.Flags = 0;
				Vert_Pipeline_Shader_Stage_Create_Inof.Stage = RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_VERTEX_BIT;
				Vert_Pipeline_Shader_Stage_Create_Inof.Module = Vertex_Shader_Module.get();
				Vert_Pipeline_Shader_Stage_Create_Inof.Name = "main";
				Vert_Pipeline_Shader_Stage_Create_Inof.Specialization_Info = nullptr;
			}

			unique_ptr<RHI_Shader_Module> Fragment_Shader_Module{ this->m_RHI->Create_Shader_Module(&DEFERRED_LIGHTING_FRAG) };

			RHI_Pipeline_Shader_Stage_Create_Info Frag_Pipeline_Shader_Stage_Create_Inof{};
			{
				Frag_Pipeline_Shader_Stage_Create_Inof.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
				Frag_Pipeline_Shader_Stage_Create_Inof.Flags = 0;
				Frag_Pipeline_Shader_Stage_Create_Inof.Stage = RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_FRAGMENT_BIT;
				Frag_Pipeline_Shader_Stage_Create_Inof.Module = Fragment_Shader_Module.get();
				Frag_Pipeline_Shader_Stage_Create_Inof.Name = "main";
				Frag_Pipeline_Shader_Stage_Create_Inof.Specialization_Info = nullptr;
			}

			const vector<const RHI_Pipeline_Shader_Stage_Create_Info*> Shader_Stages{
				&Vert_Pipeline_Shader_Stage_Create_Inof,
				&Frag_Pipeline_Shader_Stage_Create_Inof
			};

			RHI_Pipeline_Vertex_Input_State_Create_Info Vertex_Input_State_Create_Info{};
			{
				Vertex_Input_State_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
				Vertex_Input_State_Create_Info.Flags = 0;
				Vertex_Input_State_Create_Info.Vertex_Binding_Descriptions = nullptr;
				Vertex_Input_State_Create_Info.Vertex_Attribute_Descriptions = nullptr;
			}

			RHI_Pipeline_Input_Assembly_State_Create_Info Input_Assembly_State_Create_Info{};
			{
				Input_Assembly_State_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
				Input_Assembly_State_Create_Info.Flags = 0;
				Input_Assembly_State_Create_Info.Topology = RHI_PRIMITIVE_TOPOLOGY::RHI_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
				Input_Assembly_State_Create_Info.Primitive_Restart_Enable = RHI_FALSE;
			}

			const vector<const RHI_Viewport*> Viewports{
					&this->m_RHI->Get_SwapChain_Viewport()
			};

			const vector<const RHI_Rect_2D*> Scissors{
				&this->m_RHI->Get_SwapChain_Scissor()
			};

			RHI_Pipeline_Viewport_State_Create_Info Viewport_State_Create_Info{};
			{
				Viewport_State_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
				Viewport_State_Create_Info.Flags = 0;
				Viewport_State_Create_Info.Viewports = &Viewports;
				Viewport_State_Create_Info.Scissors = &Scissors;
			}

			RHI_Pipeline_Rasterization_State_Create_Info Rasterization_State_Create_Info{};
			{
				Rasterization_State_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
				Rasterization_State_Create_Info.Flags = 0;
				Rasterization_State_Create_Info.Depth_Clamp_Enable = RHI_FALSE;
				Rasterization_State_Create_Info.Rasterizer_Discard_Enable = RHI_FALSE;
				Rasterization_State_Create_Info.Polygon_Mode = RHI_POLYGON_MODE::RHI_POLYGON_MODE_FILL;
				Rasterization_State_Create_Info.Cull_Mode = to_underlying(RHI_CULL_MODE_FLAG_BITS::RHI_CULL_MODE_BACK_BIT);
				Rasterization_State_Create_Info.Front_Face = RHI_FRONT_FACE::RHI_FRONT_FACE_CLOCKWISE;
				Rasterization_State_Create_Info.Depth_Bias_Enable = RHI_FALSE;
				Rasterization_State_Create_Info.Depth_Bias_Constant_Factor = 0.0f;
				Rasterization_State_Create_Info.Depth_Bias_Clamp = 0.0f;
				Rasterization_State_Create_Info.Depth_Bias_Slope_Factor = 0.0f;
				Rasterization_State_Create_Info.Line_Width = 1.0f;
			}

			RHI_Pipeline_Multisample_State_Create_Info Multisample_State_Create_Info{};
			{
				Multisample_State_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
				Multisample_State_Create_Info.Flags = 0;
				Multisample_State_Create_Info.Rasterization_Samples = RHI_SAMPLE_COUNT_FLAG_BIT::RHI_SAMPLE_COUNT_1_BIT;
				Multisample_State_Create_Info.Sample_Shading_Enable = RHI_FALSE;
				Multisample_State_Create_Info.Min_Sample_Shading = 0.0f;
			}

			RHI_Pipeline_Depth_Stencil_State_Create_Info Depth_Stencil_State_Create_Info{};
			{
				Depth_Stencil_State_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
				Depth_Stencil_State_Create_Info.Flags = 0;
				Depth_Stencil_State_Create_Info.Depth_Test_Enable = RHI_FALSE;
				Depth_Stencil_State_Create_Info.Depth_Write_Enable = RHI_FALSE;
				Depth_Stencil_State_Create_Info.Depth_Compare_Op = NameSpace_RHI::RHI_COMPARE_OP::RHI_COMPARE_OP_ALWAYS;
				Depth_Stencil_State_Create_Info.Depth_Bounds_Test_Enable = RHI_FALSE;
				Depth_Stencil_State_Create_Info.Stencil_Test_Enable = RHI_FALSE;
				Depth_Stencil_State_Create_Info.Front = {};
				Depth_Stencil_State_Create_Info.Back = {};
				Depth_Stencil_State_Create_Info.Min_Depth_Bounds = 0.0f;
				Depth_Stencil_State_Create_Info.Max_Depth_Bounds = 1.0f;
			}

			RHI_Pipeline_Color_Blend_Attachment_State Color_Blend_Attachment{};
			{
				Color_Blend_Attachment.Blend_Enable = RHI_FALSE;
				Color_Blend_Attachment.Src_Color_Blend_Factor = RHI_BLEND_FACTOR::RHI_BLEND_FACTOR_ONE;
				Color_Blend_Attachment.Dst_Color_Blend_Factor = RHI_BLEND_FACTOR::RHI_BLEND_FACTOR_ONE;
				Color_Blend_Attachment.Color_Blend_Op = RHI_BLEND_OP::RHI_BLEND_OP_ADD;
				Color_Blend_Attachment.Src_Alpha_Blend_Factor = RHI_BLEND_FACTOR::RHI_BLEND_FACTOR_ONE;
				Color_Blend_Attachment.Dst_Alpha_Blend_Factor = RHI_BLEND_FACTOR::RHI_BLEND_FACTOR_ONE;
				Color_Blend_Attachment.Alpha_Blend_Op = RHI_BLEND_OP::RHI_BLEND_OP_ADD;
				Color_Blend_Attachment.Color_Write_Mask =
					RHI_COLOR_COMPONENT_FLAG_BITS::RHI_COLOR_COMPONENT_R_BIT |
					RHI_COLOR_COMPONENT_FLAG_BITS::RHI_COLOR_COMPONENT_G_BIT |
					RHI_COLOR_COMPONENT_FLAG_BITS::RHI_COLOR_COMPONENT_B_BIT |
					RHI_COLOR_COMPONENT_FLAG_BITS::RHI_COLOR_COMPONENT_A_BIT;
			}
			const vector<const RHI_Pipeline_Color_Blend_Attachment_State*> Color_Blend_Attachments{
				&Color_Blend_Attachment
			};

			RHI_Pipeline_Color_Blend_State_Create_Info Color_Blend_State_Create_Info{};
			{
				Color_Blend_State_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
				Color_Blend_State_Create_Info.Flags = 0;
				Color_Blend_State_Create_Info.Logic_Op_Enable = RHI_FALSE;
				Color_Blend_State_Create_Info.Logic_Op = RHI_LOGIC_OP::RHI_LOGIC_OP_COPY;
				Color_Blend_State_Create_Info.Attachments = &Color_Blend_Attachments;
				Color_Blend_State_Create_Info.Blend_Constants = { 0.0f,0.0f,0.0f,0.0f };
			}

			const vector<RHI_DYNAMIC_STATE> Dynamic_States{
					RHI_DYNAMIC_STATE::RHI_DYNAMIC_STATE_VIEWPORT,
					RHI_DYNAMIC_STATE::RHI_DYNAMIC_STATE_SCISSOR
			};

			RHI_Pipeline_Dynamic_State_Create_Info Dynamic_State_Create_Info{};
			{
				Dynamic_State_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
				Dynamic_State_Create_Info.Flags = 0;
				Dynamic_State_Create_Info.Dynamic_States = &Dynamic_States;
			}

			RHI_Graphics_Pipeline_Create_Info Graphics_Pipeline_Create_Info{};
			{
				Graphics_Pipeline_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
				Graphics_Pipeline_Create_Info.Flags = 0;
				Graphics_Pipeline_Create_Info.Stages = &Shader_Stages;
				Graphics_Pipeline_Create_Info.Vertex_Input_State = &Vertex_Input_State_Create_Info;
				Graphics_Pipeline_Create_Info.Input_Assembly_State = &Input_Assembly_State_Create_Info;
				Graphics_Pipeline_Create_Info.Tessellation_State = nullptr;
				Graphics_Pipeline_Create_Info.Viewport_State = &Viewport_State_Create_Info;
				Graphics_Pipeline_Create_Info.Rasterization_State = &Rasterization_State_Create_Info;
				Graphics_Pipeline_Create_Info.Multisample_State = &Multisample_State_Create_Info;
				Graphics_Pipeline_Create_Info.Depth_Stencil_State = &Depth_Stencil_State_Create_Info;
				Graphics_Pipeline_Create_Info.Color_Blend_State = &Color_Blend_State_Create_Info;
				Graphics_Pipeline_Create_Info.Dynamic_State = &Dynamic_State_Create_Info;
				Graphics_Pipeline_Create_Info.Layout = this->m_Render_Pipelines[_render_pipeline_type_deferred_lighting].Pipeline_Layout.get();
				Graphics_Pipeline_Create_Info.Render_Pass = this->m_Frame_Buffer.Render_Pass.get();
				Graphics_Pipeline_Create_Info.Subpass = _main_camera_subpass_deferred_lighting;
				Graphics_Pipeline_Create_Info.Base_Pipeline_Handle = RHI_NULL_HANDLE;
				Graphics_Pipeline_Create_Info.Base_Pipeline_Index = 0;
			}

			this->m_Render_Pipelines[_render_pipeline_type_deferred_lighting].Pipeline = this->m_RHI->Create_Graphics_Pipeline(&Graphics_Pipeline_Create_Info);
		}

		//NOTE : Mesh Lighting
		{
			vector<RHI_Descriptor_Set_Layout*> Descriptor_Set_Layouts{
					this->m_Descriptors[_mesh_global].Descriptor_Set_Layout.get(),
					this->m_Descriptors[_per_mesh].Descriptor_Set_Layout.get(),
					this->m_Descriptors[_mesh_per_material].Descriptor_Set_Layout.get(),
			};

			RHI_Pipeline_Layout_Create_Info Pipeline_Layout_Create_Info{};
			{

				Pipeline_Layout_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
				Pipeline_Layout_Create_Info.Flags = 0;
				Pipeline_Layout_Create_Info.Set_Layouts = &Descriptor_Set_Layouts;
				Pipeline_Layout_Create_Info.Push_Constant_Ranges = nullptr;
			}

			this->m_Render_Pipelines[_render_pipeline_type_mesh_lighting].Pipeline_Layout = this->m_RHI->Create_Pipeline_Layout(&Pipeline_Layout_Create_Info);

			unique_ptr<RHI_Shader_Module> Vertex_Shader_Module{ this->m_RHI->Create_Shader_Module(&MESH_VERT) };

			RHI_Pipeline_Shader_Stage_Create_Info Vert_Pipeline_Shader_Stage_Create_Inof{};
			{
				Vert_Pipeline_Shader_Stage_Create_Inof.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
				Vert_Pipeline_Shader_Stage_Create_Inof.Flags = 0;
				Vert_Pipeline_Shader_Stage_Create_Inof.Stage = RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_VERTEX_BIT;
				Vert_Pipeline_Shader_Stage_Create_Inof.Module = Vertex_Shader_Module.get();
				Vert_Pipeline_Shader_Stage_Create_Inof.Name = "main";
				Vert_Pipeline_Shader_Stage_Create_Inof.Specialization_Info = nullptr;
			}

			unique_ptr<RHI_Shader_Module> Fragment_Shader_Module{ this->m_RHI->Create_Shader_Module(&MESH_FRAG) };

			RHI_Pipeline_Shader_Stage_Create_Info Frag_Pipeline_Shader_Stage_Create_Inof{};
			{
				Frag_Pipeline_Shader_Stage_Create_Inof.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
				Frag_Pipeline_Shader_Stage_Create_Inof.Flags = 0;
				Frag_Pipeline_Shader_Stage_Create_Inof.Stage = RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_FRAGMENT_BIT;
				Frag_Pipeline_Shader_Stage_Create_Inof.Module = Fragment_Shader_Module.get();
				Frag_Pipeline_Shader_Stage_Create_Inof.Name = "main";
				Frag_Pipeline_Shader_Stage_Create_Inof.Specialization_Info = nullptr;
			}

			const vector<const RHI_Pipeline_Shader_Stage_Create_Info*> Shader_Stages{
				&Vert_Pipeline_Shader_Stage_Create_Inof,
				&Frag_Pipeline_Shader_Stage_Create_Inof
			};

			RHI_Pipeline_Vertex_Input_State_Create_Info Vertex_Input_State_Create_Info{};
			{
				Vertex_Input_State_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
				Vertex_Input_State_Create_Info.Flags = 0;
				Vertex_Input_State_Create_Info.Vertex_Binding_Descriptions = Mesh_Vertex::Get_Vertex_Input_Binding_Description();
				Vertex_Input_State_Create_Info.Vertex_Attribute_Descriptions = Mesh_Vertex::Get_Vertex_Input_Attribute_Description();
			}

			RHI_Pipeline_Input_Assembly_State_Create_Info Input_Assembly_State_Create_Info{};
			{
				Input_Assembly_State_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
				Input_Assembly_State_Create_Info.Flags = 0;
				Input_Assembly_State_Create_Info.Topology = RHI_PRIMITIVE_TOPOLOGY::RHI_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
				Input_Assembly_State_Create_Info.Primitive_Restart_Enable = RHI_FALSE;
			}

			const vector<const RHI_Viewport*> Viewports{
					&this->m_RHI->Get_SwapChain_Viewport()
			};

			const vector<const RHI_Rect_2D*> Scissors{
				&this->m_RHI->Get_SwapChain_Scissor()
			};

			RHI_Pipeline_Viewport_State_Create_Info Viewport_State_Create_Info{};
			{
				Viewport_State_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
				Viewport_State_Create_Info.Flags = 0;
				Viewport_State_Create_Info.Viewports = &Viewports;
				Viewport_State_Create_Info.Scissors = &Scissors;
			}

			RHI_Pipeline_Rasterization_State_Create_Info Rasterization_State_Create_Info{};
			{
				Rasterization_State_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
				Rasterization_State_Create_Info.Flags = 0;
				Rasterization_State_Create_Info.Depth_Clamp_Enable = RHI_FALSE;
				Rasterization_State_Create_Info.Rasterizer_Discard_Enable = RHI_FALSE;
				Rasterization_State_Create_Info.Polygon_Mode = RHI_POLYGON_MODE::RHI_POLYGON_MODE_FILL;
				Rasterization_State_Create_Info.Cull_Mode = to_underlying(RHI_CULL_MODE_FLAG_BITS::RHI_CULL_MODE_BACK_BIT);
				Rasterization_State_Create_Info.Front_Face = RHI_FRONT_FACE::RHI_FRONT_FACE_COUNTER_CLOCKWISE;
				Rasterization_State_Create_Info.Depth_Bias_Enable = RHI_FALSE;
				Rasterization_State_Create_Info.Depth_Bias_Constant_Factor = 0.0f;
				Rasterization_State_Create_Info.Depth_Bias_Clamp = 0.0f;
				Rasterization_State_Create_Info.Depth_Bias_Slope_Factor = 0.0f;
				Rasterization_State_Create_Info.Line_Width = 1.0f;
			}

			RHI_Pipeline_Multisample_State_Create_Info Multisample_State_Create_Info{};
			{
				Multisample_State_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
				Multisample_State_Create_Info.Flags = 0;
				Multisample_State_Create_Info.Rasterization_Samples = RHI_SAMPLE_COUNT_FLAG_BIT::RHI_SAMPLE_COUNT_1_BIT;
				Multisample_State_Create_Info.Sample_Shading_Enable = RHI_FALSE;
				Multisample_State_Create_Info.Min_Sample_Shading = 0.0f;
			}

			RHI_Pipeline_Depth_Stencil_State_Create_Info Depth_Stencil_State_Create_Info{};
			{
				Depth_Stencil_State_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
				Depth_Stencil_State_Create_Info.Flags = 0;
				Depth_Stencil_State_Create_Info.Depth_Test_Enable = RHI_TRUE;
				Depth_Stencil_State_Create_Info.Depth_Write_Enable = RHI_TRUE;
				Depth_Stencil_State_Create_Info.Depth_Compare_Op = RHI_COMPARE_OP::RHI_COMPARE_OP_LESS;
				Depth_Stencil_State_Create_Info.Depth_Bounds_Test_Enable = RHI_FALSE;
				Depth_Stencil_State_Create_Info.Stencil_Test_Enable = RHI_FALSE;
				Depth_Stencil_State_Create_Info.Front = {};
				Depth_Stencil_State_Create_Info.Back = {};
				Depth_Stencil_State_Create_Info.Min_Depth_Bounds = 0.0f;
				Depth_Stencil_State_Create_Info.Max_Depth_Bounds = 1.0f;
			}

			RHI_Pipeline_Color_Blend_Attachment_State Color_Blend_Attachment{};
			{
				Color_Blend_Attachment.Blend_Enable = RHI_FALSE;
				Color_Blend_Attachment.Src_Color_Blend_Factor = RHI_BLEND_FACTOR::RHI_BLEND_FACTOR_ONE;
				Color_Blend_Attachment.Dst_Color_Blend_Factor = RHI_BLEND_FACTOR::RHI_BLEND_FACTOR_ONE;
				Color_Blend_Attachment.Color_Blend_Op = RHI_BLEND_OP::RHI_BLEND_OP_ADD;
				Color_Blend_Attachment.Src_Alpha_Blend_Factor = RHI_BLEND_FACTOR::RHI_BLEND_FACTOR_ONE;
				Color_Blend_Attachment.Dst_Alpha_Blend_Factor = RHI_BLEND_FACTOR::RHI_BLEND_FACTOR_ONE;
				Color_Blend_Attachment.Alpha_Blend_Op = RHI_BLEND_OP::RHI_BLEND_OP_ADD;
				Color_Blend_Attachment.Color_Write_Mask =
					RHI_COLOR_COMPONENT_FLAG_BITS::RHI_COLOR_COMPONENT_R_BIT |
					RHI_COLOR_COMPONENT_FLAG_BITS::RHI_COLOR_COMPONENT_G_BIT |
					RHI_COLOR_COMPONENT_FLAG_BITS::RHI_COLOR_COMPONENT_B_BIT |
					RHI_COLOR_COMPONENT_FLAG_BITS::RHI_COLOR_COMPONENT_A_BIT;
			}
			const vector<const RHI_Pipeline_Color_Blend_Attachment_State*> Color_Blend_Attachments{
				&Color_Blend_Attachment
			};

			RHI_Pipeline_Color_Blend_State_Create_Info Color_Blend_State_Create_Info{};
			{
				Color_Blend_State_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
				Color_Blend_State_Create_Info.Flags = 0;
				Color_Blend_State_Create_Info.Logic_Op_Enable = RHI_FALSE;
				Color_Blend_State_Create_Info.Logic_Op = RHI_LOGIC_OP::RHI_LOGIC_OP_COPY;
				Color_Blend_State_Create_Info.Attachments = &Color_Blend_Attachments;
				Color_Blend_State_Create_Info.Blend_Constants = { 0.0f,0.0f,0.0f,0.0f };
			}

			const vector<RHI_DYNAMIC_STATE> Dynamic_States{
					RHI_DYNAMIC_STATE::RHI_DYNAMIC_STATE_VIEWPORT,
					RHI_DYNAMIC_STATE::RHI_DYNAMIC_STATE_SCISSOR
			};

			RHI_Pipeline_Dynamic_State_Create_Info Dynamic_State_Create_Info{};
			{
				Dynamic_State_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
				Dynamic_State_Create_Info.Flags = 0;
				Dynamic_State_Create_Info.Dynamic_States = &Dynamic_States;
			}

			RHI_Graphics_Pipeline_Create_Info Graphics_Pipeline_Create_Info{};
			{
				Graphics_Pipeline_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
				Graphics_Pipeline_Create_Info.Flags = 0;
				Graphics_Pipeline_Create_Info.Stages = &Shader_Stages;
				Graphics_Pipeline_Create_Info.Vertex_Input_State = &Vertex_Input_State_Create_Info;
				Graphics_Pipeline_Create_Info.Input_Assembly_State = &Input_Assembly_State_Create_Info;
				Graphics_Pipeline_Create_Info.Tessellation_State = nullptr;
				Graphics_Pipeline_Create_Info.Viewport_State = &Viewport_State_Create_Info;
				Graphics_Pipeline_Create_Info.Rasterization_State = &Rasterization_State_Create_Info;
				Graphics_Pipeline_Create_Info.Multisample_State = &Multisample_State_Create_Info;
				Graphics_Pipeline_Create_Info.Depth_Stencil_State = &Depth_Stencil_State_Create_Info;
				Graphics_Pipeline_Create_Info.Color_Blend_State = &Color_Blend_State_Create_Info;
				Graphics_Pipeline_Create_Info.Dynamic_State = &Dynamic_State_Create_Info;
				Graphics_Pipeline_Create_Info.Layout = this->m_Render_Pipelines[_render_pipeline_type_mesh_lighting].Pipeline_Layout.get();
				Graphics_Pipeline_Create_Info.Render_Pass = this->m_Frame_Buffer.Render_Pass.get();
				Graphics_Pipeline_Create_Info.Subpass = _main_camera_subpass_forward_lighting;
				Graphics_Pipeline_Create_Info.Base_Pipeline_Handle = RHI_NULL_HANDLE;
				Graphics_Pipeline_Create_Info.Base_Pipeline_Index = 0;
			}

			this->m_Render_Pipelines[_render_pipeline_type_mesh_lighting].Pipeline = this->m_RHI->Create_Graphics_Pipeline(&Graphics_Pipeline_Create_Info);
		}

		//NOTE : SkyBox
		{
			vector<RHI_Descriptor_Set_Layout*> Descriptor_Set_Layouts{
					this->m_Descriptors[_skybox].Descriptor_Set_Layout.get()
			};

			RHI_Pipeline_Layout_Create_Info Pipeline_Layout_Create_Info{};
			{
				Pipeline_Layout_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
				Pipeline_Layout_Create_Info.Flags = 0;
				Pipeline_Layout_Create_Info.Set_Layouts = &Descriptor_Set_Layouts;
				Pipeline_Layout_Create_Info.Push_Constant_Ranges = nullptr;
			}

			this->m_Render_Pipelines[_render_pipeline_type_skybox].Pipeline_Layout = this->m_RHI->Create_Pipeline_Layout(&Pipeline_Layout_Create_Info);

			unique_ptr<RHI_Shader_Module> Vertex_Shader_Module{ this->m_RHI->Create_Shader_Module(&SKYBOX_VERT) };

			RHI_Pipeline_Shader_Stage_Create_Info Vert_Pipeline_Shader_Stage_Create_Inof{};
			{
				Vert_Pipeline_Shader_Stage_Create_Inof.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
				Vert_Pipeline_Shader_Stage_Create_Inof.Flags = 0;
				Vert_Pipeline_Shader_Stage_Create_Inof.Stage = RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_VERTEX_BIT;
				Vert_Pipeline_Shader_Stage_Create_Inof.Module = Vertex_Shader_Module.get();
				Vert_Pipeline_Shader_Stage_Create_Inof.Name = "main";
				Vert_Pipeline_Shader_Stage_Create_Inof.Specialization_Info = nullptr;
			}

			unique_ptr<RHI_Shader_Module> Fragment_Shader_Module{ this->m_RHI->Create_Shader_Module(&SKYBOX_FRAG) };

			RHI_Pipeline_Shader_Stage_Create_Info Frag_Pipeline_Shader_Stage_Create_Inof{};
			{
				Frag_Pipeline_Shader_Stage_Create_Inof.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
				Frag_Pipeline_Shader_Stage_Create_Inof.Flags = 0;
				Frag_Pipeline_Shader_Stage_Create_Inof.Stage = RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_FRAGMENT_BIT;
				Frag_Pipeline_Shader_Stage_Create_Inof.Module = Fragment_Shader_Module.get();
				Frag_Pipeline_Shader_Stage_Create_Inof.Name = "main";
				Frag_Pipeline_Shader_Stage_Create_Inof.Specialization_Info = nullptr;
			}

			const vector<const RHI_Pipeline_Shader_Stage_Create_Info*> Shader_Stages{
				&Vert_Pipeline_Shader_Stage_Create_Inof,
				&Frag_Pipeline_Shader_Stage_Create_Inof
			};

			RHI_Pipeline_Vertex_Input_State_Create_Info Vertex_Input_State_Create_Info{};
			{
				Vertex_Input_State_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
				Vertex_Input_State_Create_Info.Flags = 0;
				Vertex_Input_State_Create_Info.Vertex_Binding_Descriptions = nullptr;
				Vertex_Input_State_Create_Info.Vertex_Attribute_Descriptions = nullptr;
			}

			RHI_Pipeline_Input_Assembly_State_Create_Info Input_Assembly_State_Create_Info{};
			{
				Input_Assembly_State_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
				Input_Assembly_State_Create_Info.Flags = 0;
				Input_Assembly_State_Create_Info.Topology = RHI_PRIMITIVE_TOPOLOGY::RHI_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
				Input_Assembly_State_Create_Info.Primitive_Restart_Enable = RHI_FALSE;
			}

			const vector<const RHI_Viewport*> Viewports{
					&this->m_RHI->Get_SwapChain_Viewport()
			};

			const vector<const RHI_Rect_2D*> Scissors{
				&this->m_RHI->Get_SwapChain_Scissor()
			};

			RHI_Pipeline_Viewport_State_Create_Info Viewport_State_Create_Info{};
			{
				Viewport_State_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
				Viewport_State_Create_Info.Flags = 0;
				Viewport_State_Create_Info.Viewports = &Viewports;
				Viewport_State_Create_Info.Scissors = &Scissors;
			}

			RHI_Pipeline_Rasterization_State_Create_Info Rasterization_State_Create_Info{};
			{
				Rasterization_State_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
				Rasterization_State_Create_Info.Flags = 0;
				Rasterization_State_Create_Info.Depth_Clamp_Enable = RHI_FALSE;
				Rasterization_State_Create_Info.Rasterizer_Discard_Enable = RHI_FALSE;
				Rasterization_State_Create_Info.Polygon_Mode = RHI_POLYGON_MODE::RHI_POLYGON_MODE_FILL;
				Rasterization_State_Create_Info.Cull_Mode = to_underlying(RHI_CULL_MODE_FLAG_BITS::RHI_CULL_MODE_BACK_BIT);
				Rasterization_State_Create_Info.Front_Face = RHI_FRONT_FACE::RHI_FRONT_FACE_COUNTER_CLOCKWISE;
				Rasterization_State_Create_Info.Depth_Bias_Enable = RHI_FALSE;
				Rasterization_State_Create_Info.Depth_Bias_Constant_Factor = 0.0f;
				Rasterization_State_Create_Info.Depth_Bias_Clamp = 0.0f;
				Rasterization_State_Create_Info.Depth_Bias_Slope_Factor = 0.0f;
				Rasterization_State_Create_Info.Line_Width = 1.0f;
			}

			RHI_Pipeline_Multisample_State_Create_Info Multisample_State_Create_Info{};
			{
				Multisample_State_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
				Multisample_State_Create_Info.Flags = 0;
				Multisample_State_Create_Info.Rasterization_Samples = RHI_SAMPLE_COUNT_FLAG_BIT::RHI_SAMPLE_COUNT_1_BIT;
				Multisample_State_Create_Info.Sample_Shading_Enable = RHI_FALSE;
				Multisample_State_Create_Info.Min_Sample_Shading = 0.0f;
			}

			RHI_Pipeline_Depth_Stencil_State_Create_Info Depth_Stencil_State_Create_Info{};
			{
				Depth_Stencil_State_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
				Depth_Stencil_State_Create_Info.Flags = 0;
				Depth_Stencil_State_Create_Info.Depth_Test_Enable = RHI_TRUE;
				Depth_Stencil_State_Create_Info.Depth_Write_Enable = RHI_TRUE;
				Depth_Stencil_State_Create_Info.Depth_Compare_Op = NameSpace_RHI::RHI_COMPARE_OP::RHI_COMPARE_OP_LESS;
				Depth_Stencil_State_Create_Info.Depth_Bounds_Test_Enable = RHI_FALSE;
				Depth_Stencil_State_Create_Info.Stencil_Test_Enable = RHI_FALSE;
				Depth_Stencil_State_Create_Info.Front = {};
				Depth_Stencil_State_Create_Info.Back = {};
				Depth_Stencil_State_Create_Info.Min_Depth_Bounds = 0.0f;
				Depth_Stencil_State_Create_Info.Max_Depth_Bounds = 1.0f;
			}

			RHI_Pipeline_Color_Blend_Attachment_State Color_Blend_Attachment{};
			{
				Color_Blend_Attachment.Blend_Enable = RHI_FALSE;
				Color_Blend_Attachment.Src_Color_Blend_Factor = RHI_BLEND_FACTOR::RHI_BLEND_FACTOR_ONE;
				Color_Blend_Attachment.Dst_Color_Blend_Factor = RHI_BLEND_FACTOR::RHI_BLEND_FACTOR_ZERO;
				Color_Blend_Attachment.Color_Blend_Op = RHI_BLEND_OP::RHI_BLEND_OP_ADD;
				Color_Blend_Attachment.Src_Alpha_Blend_Factor = RHI_BLEND_FACTOR::RHI_BLEND_FACTOR_ONE;
				Color_Blend_Attachment.Dst_Alpha_Blend_Factor = RHI_BLEND_FACTOR::RHI_BLEND_FACTOR_ZERO;
				Color_Blend_Attachment.Alpha_Blend_Op = RHI_BLEND_OP::RHI_BLEND_OP_ADD;
				Color_Blend_Attachment.Color_Write_Mask =
					RHI_COLOR_COMPONENT_FLAG_BITS::RHI_COLOR_COMPONENT_R_BIT |
					RHI_COLOR_COMPONENT_FLAG_BITS::RHI_COLOR_COMPONENT_G_BIT |
					RHI_COLOR_COMPONENT_FLAG_BITS::RHI_COLOR_COMPONENT_B_BIT |
					RHI_COLOR_COMPONENT_FLAG_BITS::RHI_COLOR_COMPONENT_A_BIT;
			}
			const vector<const RHI_Pipeline_Color_Blend_Attachment_State*> Color_Blend_Attachments{
				&Color_Blend_Attachment
			};

			RHI_Pipeline_Color_Blend_State_Create_Info Color_Blend_State_Create_Info{};
			{
				Color_Blend_State_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
				Color_Blend_State_Create_Info.Flags = 0;
				Color_Blend_State_Create_Info.Logic_Op_Enable = RHI_FALSE;
				Color_Blend_State_Create_Info.Logic_Op = NameSpace_RHI::RHI_LOGIC_OP::RHI_LOGIC_OP_COPY;
				Color_Blend_State_Create_Info.Attachments = &Color_Blend_Attachments;
				Color_Blend_State_Create_Info.Blend_Constants = { 0.0f,0.0f,0.0f,0.0f };
			}

			const vector<RHI_DYNAMIC_STATE> Dynamic_States{
				RHI_DYNAMIC_STATE::RHI_DYNAMIC_STATE_VIEWPORT,
				RHI_DYNAMIC_STATE::RHI_DYNAMIC_STATE_SCISSOR
			};

			RHI_Pipeline_Dynamic_State_Create_Info Dynamic_State_Create_Info{};
			{
				Dynamic_State_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
				Dynamic_State_Create_Info.Flags = 0;
				Dynamic_State_Create_Info.Dynamic_States = &Dynamic_States;
			}

			RHI_Graphics_Pipeline_Create_Info Graphics_Pipeline_Create_Info{};
			{
				Graphics_Pipeline_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
				Graphics_Pipeline_Create_Info.Flags = 0;
				Graphics_Pipeline_Create_Info.Stages = &Shader_Stages;
				Graphics_Pipeline_Create_Info.Vertex_Input_State = &Vertex_Input_State_Create_Info;
				Graphics_Pipeline_Create_Info.Input_Assembly_State = &Input_Assembly_State_Create_Info;
				Graphics_Pipeline_Create_Info.Tessellation_State = nullptr;
				Graphics_Pipeline_Create_Info.Viewport_State = &Viewport_State_Create_Info;
				Graphics_Pipeline_Create_Info.Rasterization_State = &Rasterization_State_Create_Info;
				Graphics_Pipeline_Create_Info.Multisample_State = &Multisample_State_Create_Info;
				Graphics_Pipeline_Create_Info.Depth_Stencil_State = &Depth_Stencil_State_Create_Info;
				Graphics_Pipeline_Create_Info.Color_Blend_State = &Color_Blend_State_Create_Info;
				Graphics_Pipeline_Create_Info.Dynamic_State = &Dynamic_State_Create_Info;
				Graphics_Pipeline_Create_Info.Layout = this->m_Render_Pipelines[_render_pipeline_type_skybox].Pipeline_Layout.get();
				Graphics_Pipeline_Create_Info.Render_Pass = this->m_Frame_Buffer.Render_Pass.get();
				Graphics_Pipeline_Create_Info.Subpass = _main_camera_subpass_forward_lighting;
				Graphics_Pipeline_Create_Info.Base_Pipeline_Handle = RHI_NULL_HANDLE;
				Graphics_Pipeline_Create_Info.Base_Pipeline_Index = 0;
			}

			this->m_Render_Pipelines[_render_pipeline_type_skybox].Pipeline = this->m_RHI->Create_Graphics_Pipeline(&Graphics_Pipeline_Create_Info);
		}

		//NOTE : Axis
		{
			vector<RHI_Descriptor_Set_Layout*> Descriptor_Set_Layouts{
					this->m_Descriptors[_axis].Descriptor_Set_Layout.get()
			};

			RHI_Pipeline_Layout_Create_Info Pipeline_Layout_Create_Info{};
			{
				Pipeline_Layout_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
				Pipeline_Layout_Create_Info.Flags = 0;
				Pipeline_Layout_Create_Info.Set_Layouts = &Descriptor_Set_Layouts;
				Pipeline_Layout_Create_Info.Push_Constant_Ranges = nullptr;
			}

			this->m_Render_Pipelines[_render_pipeline_type_axis].Pipeline_Layout = this->m_RHI->Create_Pipeline_Layout(&Pipeline_Layout_Create_Info);

			unique_ptr<NameSpace_RHI::RHI_Shader_Module> Vertex_Shader_Module{ this->m_RHI->Create_Shader_Module(&AXIS_VERT) };

			RHI_Pipeline_Shader_Stage_Create_Info Vert_Pipeline_Shader_Stage_Create_Inof{};
			{
				Vert_Pipeline_Shader_Stage_Create_Inof.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
				Vert_Pipeline_Shader_Stage_Create_Inof.Flags = 0;
				Vert_Pipeline_Shader_Stage_Create_Inof.Stage = RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_VERTEX_BIT;
				Vert_Pipeline_Shader_Stage_Create_Inof.Module = Vertex_Shader_Module.get();
				Vert_Pipeline_Shader_Stage_Create_Inof.Name = "main";
				Vert_Pipeline_Shader_Stage_Create_Inof.Specialization_Info = nullptr;
			}

			unique_ptr<NameSpace_RHI::RHI_Shader_Module> Fragment_Shader_Module{ this->m_RHI->Create_Shader_Module(&AXIS_FRAG) };

			RHI_Pipeline_Shader_Stage_Create_Info Frag_Pipeline_Shader_Stage_Create_Inof{};
			{
				Frag_Pipeline_Shader_Stage_Create_Inof.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
				Frag_Pipeline_Shader_Stage_Create_Inof.Flags = 0;
				Frag_Pipeline_Shader_Stage_Create_Inof.Stage = RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_FRAGMENT_BIT;
				Frag_Pipeline_Shader_Stage_Create_Inof.Module = Fragment_Shader_Module.get();
				Frag_Pipeline_Shader_Stage_Create_Inof.Name = "main";
				Frag_Pipeline_Shader_Stage_Create_Inof.Specialization_Info = nullptr;
			}

			const vector<const RHI_Pipeline_Shader_Stage_Create_Info*> Shader_Stages{
				&Vert_Pipeline_Shader_Stage_Create_Inof,
				&Frag_Pipeline_Shader_Stage_Create_Inof
			};

			RHI_Pipeline_Vertex_Input_State_Create_Info Vertex_Input_State_Create_Info{};
			{
				Vertex_Input_State_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
				Vertex_Input_State_Create_Info.Flags = 0;
				Vertex_Input_State_Create_Info.Vertex_Binding_Descriptions = Mesh_Vertex::Get_Vertex_Input_Binding_Description();
				Vertex_Input_State_Create_Info.Vertex_Attribute_Descriptions = Mesh_Vertex::Get_Vertex_Input_Attribute_Description();
			}

			RHI_Pipeline_Input_Assembly_State_Create_Info Input_Assembly_State_Create_Info{};
			{
				Input_Assembly_State_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
				Input_Assembly_State_Create_Info.Flags = 0;
				Input_Assembly_State_Create_Info.Topology = RHI_PRIMITIVE_TOPOLOGY::RHI_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
				Input_Assembly_State_Create_Info.Primitive_Restart_Enable = RHI_FALSE;
			}

			const vector<const RHI_Viewport*> Viewports{
					&this->m_RHI->Get_SwapChain_Viewport()
			};

			const vector<const RHI_Rect_2D*> Scissors{
				&this->m_RHI->Get_SwapChain_Scissor()
			};

			RHI_Pipeline_Viewport_State_Create_Info Viewport_State_Create_Info{};
			{
				Viewport_State_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
				Viewport_State_Create_Info.Flags = 0;
				Viewport_State_Create_Info.Viewports = &Viewports;
				Viewport_State_Create_Info.Scissors = &Scissors;
			}

			RHI_Pipeline_Rasterization_State_Create_Info Rasterization_State_Create_Info{};
			{
				Rasterization_State_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
				Rasterization_State_Create_Info.Flags = 0;
				Rasterization_State_Create_Info.Depth_Clamp_Enable = RHI_FALSE;
				Rasterization_State_Create_Info.Rasterizer_Discard_Enable = RHI_FALSE;
				Rasterization_State_Create_Info.Polygon_Mode = RHI_POLYGON_MODE::RHI_POLYGON_MODE_FILL;
				Rasterization_State_Create_Info.Cull_Mode = to_underlying(RHI_CULL_MODE_FLAG_BITS::RHI_CULL_MODE_NONE);
				Rasterization_State_Create_Info.Front_Face = RHI_FRONT_FACE::RHI_FRONT_FACE_COUNTER_CLOCKWISE;
				Rasterization_State_Create_Info.Depth_Bias_Enable = RHI_FALSE;
				Rasterization_State_Create_Info.Depth_Bias_Constant_Factor = 0.0f;
				Rasterization_State_Create_Info.Depth_Bias_Clamp = 0.0f;
				Rasterization_State_Create_Info.Depth_Bias_Slope_Factor = 0.0f;
				Rasterization_State_Create_Info.Line_Width = 1.0f;
			}

			RHI_Pipeline_Multisample_State_Create_Info Multisample_State_Create_Info{};
			{
				Multisample_State_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
				Multisample_State_Create_Info.Flags = 0;
				Multisample_State_Create_Info.Rasterization_Samples = RHI_SAMPLE_COUNT_FLAG_BIT::RHI_SAMPLE_COUNT_1_BIT;
				Multisample_State_Create_Info.Sample_Shading_Enable = RHI_FALSE;
				Multisample_State_Create_Info.Min_Sample_Shading = 0.0f;
			}

			RHI_Pipeline_Depth_Stencil_State_Create_Info Depth_Stencil_State_Create_Info{};
			{
				Depth_Stencil_State_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
				Depth_Stencil_State_Create_Info.Flags = 0;
				Depth_Stencil_State_Create_Info.Depth_Test_Enable = RHI_TRUE;
				Depth_Stencil_State_Create_Info.Depth_Write_Enable = RHI_TRUE;
				Depth_Stencil_State_Create_Info.Depth_Compare_Op = NameSpace_RHI::RHI_COMPARE_OP::RHI_COMPARE_OP_LESS;
				Depth_Stencil_State_Create_Info.Depth_Bounds_Test_Enable = RHI_FALSE;
				Depth_Stencil_State_Create_Info.Stencil_Test_Enable = RHI_FALSE;
				Depth_Stencil_State_Create_Info.Front = {};
				Depth_Stencil_State_Create_Info.Back = {};
				Depth_Stencil_State_Create_Info.Min_Depth_Bounds = 0.0f;
				Depth_Stencil_State_Create_Info.Max_Depth_Bounds = 1.0f;
			}

			RHI_Pipeline_Color_Blend_Attachment_State Color_Blend_Attachment{};
			{
				Color_Blend_Attachment.Blend_Enable = RHI_FALSE;
				Color_Blend_Attachment.Src_Color_Blend_Factor = RHI_BLEND_FACTOR::RHI_BLEND_FACTOR_ONE;
				Color_Blend_Attachment.Dst_Color_Blend_Factor = RHI_BLEND_FACTOR::RHI_BLEND_FACTOR_ZERO;
				Color_Blend_Attachment.Color_Blend_Op = RHI_BLEND_OP::RHI_BLEND_OP_ADD;
				Color_Blend_Attachment.Src_Alpha_Blend_Factor = RHI_BLEND_FACTOR::RHI_BLEND_FACTOR_ONE;
				Color_Blend_Attachment.Dst_Alpha_Blend_Factor = RHI_BLEND_FACTOR::RHI_BLEND_FACTOR_ZERO;
				Color_Blend_Attachment.Alpha_Blend_Op = RHI_BLEND_OP::RHI_BLEND_OP_ADD;
				Color_Blend_Attachment.Color_Write_Mask =
					RHI_COLOR_COMPONENT_FLAG_BITS::RHI_COLOR_COMPONENT_R_BIT |
					RHI_COLOR_COMPONENT_FLAG_BITS::RHI_COLOR_COMPONENT_G_BIT |
					RHI_COLOR_COMPONENT_FLAG_BITS::RHI_COLOR_COMPONENT_B_BIT |
					RHI_COLOR_COMPONENT_FLAG_BITS::RHI_COLOR_COMPONENT_A_BIT;
			}
			const vector<const RHI_Pipeline_Color_Blend_Attachment_State*> Color_Blend_Attachments{
				&Color_Blend_Attachment
			};

			RHI_Pipeline_Color_Blend_State_Create_Info Color_Blend_State_Create_Info{};
			{
				Color_Blend_State_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
				Color_Blend_State_Create_Info.Flags = 0;
				Color_Blend_State_Create_Info.Logic_Op_Enable = RHI_FALSE;
				Color_Blend_State_Create_Info.Logic_Op = NameSpace_RHI::RHI_LOGIC_OP::RHI_LOGIC_OP_COPY;
				Color_Blend_State_Create_Info.Attachments = &Color_Blend_Attachments;
				Color_Blend_State_Create_Info.Blend_Constants = { 0.0f,0.0f,0.0f,0.0f };
			}

			const vector<RHI_DYNAMIC_STATE> Dynamic_States{
					RHI_DYNAMIC_STATE::RHI_DYNAMIC_STATE_VIEWPORT,
					RHI_DYNAMIC_STATE::RHI_DYNAMIC_STATE_SCISSOR
			};

			RHI_Pipeline_Dynamic_State_Create_Info Dynamic_State_Create_Info{};
			{
				Dynamic_State_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
				Dynamic_State_Create_Info.Flags = 0;
				Dynamic_State_Create_Info.Dynamic_States = &Dynamic_States;
			}

			RHI_Graphics_Pipeline_Create_Info Graphics_Pipeline_Create_Info{};
			{
				Graphics_Pipeline_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
				Graphics_Pipeline_Create_Info.Flags = 0;
				Graphics_Pipeline_Create_Info.Stages = &Shader_Stages;
				Graphics_Pipeline_Create_Info.Vertex_Input_State = &Vertex_Input_State_Create_Info;
				Graphics_Pipeline_Create_Info.Input_Assembly_State = &Input_Assembly_State_Create_Info;
				Graphics_Pipeline_Create_Info.Tessellation_State = nullptr;
				Graphics_Pipeline_Create_Info.Viewport_State = &Viewport_State_Create_Info;
				Graphics_Pipeline_Create_Info.Rasterization_State = &Rasterization_State_Create_Info;
				Graphics_Pipeline_Create_Info.Multisample_State = &Multisample_State_Create_Info;
				Graphics_Pipeline_Create_Info.Depth_Stencil_State = &Depth_Stencil_State_Create_Info;
				Graphics_Pipeline_Create_Info.Color_Blend_State = &Color_Blend_State_Create_Info;
				Graphics_Pipeline_Create_Info.Dynamic_State = &Dynamic_State_Create_Info;
				Graphics_Pipeline_Create_Info.Layout = this->m_Render_Pipelines[_render_pipeline_type_axis].Pipeline_Layout.get();
				Graphics_Pipeline_Create_Info.Render_Pass = this->m_Frame_Buffer.Render_Pass.get();
				Graphics_Pipeline_Create_Info.Subpass = _main_camera_subpass_ui;
				Graphics_Pipeline_Create_Info.Base_Pipeline_Handle = RHI_NULL_HANDLE;
				Graphics_Pipeline_Create_Info.Base_Pipeline_Index = 0;
			}

			this->m_Render_Pipelines[_render_pipeline_type_axis].Pipeline = this->m_RHI->Create_Graphics_Pipeline(&Graphics_Pipeline_Create_Info);
		}
	}

	void Main_Camera_Pass::Setup_Model_Global_Descriptor_Set(void) {
		const vector<RHI_Descriptor_Set_Layout*> Descriptor_Set_Layouts{
				this->m_Descriptors[_mesh_global].Descriptor_Set_Layout.get()
		};

		RHI_Descriptor_Set_Allocate_Info Mesh_Global_Descriptor_Set_Allocate_Info{};
		{
			Mesh_Global_Descriptor_Set_Allocate_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
			Mesh_Global_Descriptor_Set_Allocate_Info.Descriptor_Pool = this->m_RHI->Get_Default_Descriptor_Pool();
			Mesh_Global_Descriptor_Set_Allocate_Info.Set_Layouts = &Descriptor_Set_Layouts;
		}

		this->m_Descriptors[_mesh_global].Descriptor_Set = std::move(this->m_RHI->Allocate_Descriptor_Sets(&Mesh_Global_Descriptor_Set_Allocate_Info).front());

		RHI_Descriptor_Buffer_Info Mesh_Per_Frame_Storage_Buffer_Info{};
		{
			Mesh_Per_Frame_Storage_Buffer_Info.Buffer = this->m_Global_Render_Resource->Storage_Buffer.Global_Upload_Ring_Buffer.get();
			Mesh_Per_Frame_Storage_Buffer_Info.Offset = 0;
			Mesh_Per_Frame_Storage_Buffer_Info.Range = sizeof(Mesh_Per_Frame_Storage_Buffer_Object);
		}
		const vector<const RHI_Descriptor_Buffer_Info*> Mesh_Per_Frame_Storage_Buffer_Infos{ &Mesh_Per_Frame_Storage_Buffer_Info };

		RHI_Descriptor_Buffer_Info Mesh_Per_Draw_Call_Storage_Buffer_Info{};
		{
			Mesh_Per_Draw_Call_Storage_Buffer_Info.Buffer = this->m_Global_Render_Resource->Storage_Buffer.Global_Upload_Ring_Buffer.get();
			Mesh_Per_Draw_Call_Storage_Buffer_Info.Offset = 0;
			Mesh_Per_Draw_Call_Storage_Buffer_Info.Range = sizeof(Mesh_Per_Draw_Class_Storage_Buffer_Object);
		}
		const vector<const RHI_Descriptor_Buffer_Info*> Mesh_Per_Draw_Call_Storage_Buffer_Infos{ &Mesh_Per_Draw_Call_Storage_Buffer_Info };

		RHI_Descriptor_Buffer_Info Mesh_Per_Draw_Call_Vertex_Blending_Storage_Buffer_Info{};
		{
			Mesh_Per_Draw_Call_Vertex_Blending_Storage_Buffer_Info.Buffer = this->m_Global_Render_Resource->Storage_Buffer.Global_Upload_Ring_Buffer.get();
			Mesh_Per_Draw_Call_Vertex_Blending_Storage_Buffer_Info.Offset = 0;
			Mesh_Per_Draw_Call_Vertex_Blending_Storage_Buffer_Info.Range = sizeof(Mesh_Per_Draw_Call_Vertex_Blending_Storage_Buffer_Object);
		}
		const vector<const RHI_Descriptor_Buffer_Info*> Mesh_Per_Draw_Call_Vertex_Blending_Storage_Buffer_Infos{ &Mesh_Per_Draw_Call_Vertex_Blending_Storage_Buffer_Info };

		RHI_Descriptor_Image_Info BRDF_Image_Info{};
		{
			BRDF_Image_Info.Sampler = this->m_Global_Render_Resource->IBL_Resource.BUDF_LUT_Sampler.get();
			BRDF_Image_Info.Image_View = this->m_Global_Render_Resource->IBL_Resource.BUDF_LUT_Image_View.get();
			BRDF_Image_Info.Image_Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		}
		const vector<const RHI_Descriptor_Image_Info*> BRDF_Image_Infos{
			&BRDF_Image_Info
		};

		RHI_Descriptor_Image_Info Irradiance_Image_Info{};
		{
			Irradiance_Image_Info.Sampler = this->m_Global_Render_Resource->IBL_Resource.Irradiance_Map_Sampler.get();
			Irradiance_Image_Info.Image_View = this->m_Global_Render_Resource->IBL_Resource.Irradiance_Map_Image_View.get();
			Irradiance_Image_Info.Image_Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		}
		const vector<const RHI_Descriptor_Image_Info*> Irradiance_Image_Infos{
			&Irradiance_Image_Info
		};

		RHI_Descriptor_Image_Info Prefiltered_Image_Info{};
		{
			Prefiltered_Image_Info.Sampler = this->m_Global_Render_Resource->IBL_Resource.Specular_Map_Sampler.get();
			Prefiltered_Image_Info.Image_View = this->m_Global_Render_Resource->IBL_Resource.Specular_Map_Image_View.get();
			Prefiltered_Image_Info.Image_Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		}
		const vector<const RHI_Descriptor_Image_Info*> Specular_Image_Infos{
			&Prefiltered_Image_Info
		};

		RHI_Descriptor_Image_Info Pointt_Light_Shadow_Map_Image_Info{};
		{
			Pointt_Light_Shadow_Map_Image_Info.Sampler = this->m_RHI->Get_Default_Sampler(RHI_DEFAULT_SAMPLER_TYPE::DEFAULT_SAMPLER_NEAREST);
			Pointt_Light_Shadow_Map_Image_Info.Image_View = this->m_Point_Light_Shadow_Color_Image_View;
			Pointt_Light_Shadow_Map_Image_Info.Image_Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		}
		const vector<const RHI_Descriptor_Image_Info*> Pointt_Light_Shadow_Map_Image_Infos{
			&Pointt_Light_Shadow_Map_Image_Info
		};

		RHI_Descriptor_Image_Info Directional_Light_Shadow_Map_Image_Info{};
		{
			Directional_Light_Shadow_Map_Image_Info.Sampler = this->m_RHI->Get_Default_Sampler(RHI_DEFAULT_SAMPLER_TYPE::DEFAULT_SAMPLER_NEAREST);
			Directional_Light_Shadow_Map_Image_Info.Image_View = this->m_Directional_Light_Shadow_Color_Image_View;
			Directional_Light_Shadow_Map_Image_Info.Image_Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		}
		const vector<const RHI_Descriptor_Image_Info*> Directional_Light_Shadow_Map_Image_Infos{
			&Directional_Light_Shadow_Map_Image_Info
		};

		/*	const vector<const RHI_Descriptor_Image_Info*> Image_Infos{
				&BRDF_Image_Info,
				&Irradiance_Image_Info,
				&Prefiltered_Image_Info,
				&Pointt_Light_Shadow_Map_Image_Info,
				&Directional_Light_Shadow_Map_Image_Info
			};*/

		RHI_Write_Descriptor_Set Per_Frame_Storage_Buffer_Write{};
		{
			Per_Frame_Storage_Buffer_Write.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			Per_Frame_Storage_Buffer_Write.Dst_Set = this->m_Descriptors[_mesh_global].Descriptor_Set.get();
			Per_Frame_Storage_Buffer_Write.Dst_Binding = 0;
			Per_Frame_Storage_Buffer_Write.Dst_Array_Element = 0;
			Per_Frame_Storage_Buffer_Write.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;
			Per_Frame_Storage_Buffer_Write.Buffer_Infos = &Mesh_Per_Frame_Storage_Buffer_Infos;
		}

		RHI_Write_Descriptor_Set Per_Draw_Call_Storage_Buffer_Write{};
		{
			Per_Draw_Call_Storage_Buffer_Write.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			Per_Draw_Call_Storage_Buffer_Write.Dst_Set = this->m_Descriptors[_mesh_global].Descriptor_Set.get();
			Per_Draw_Call_Storage_Buffer_Write.Dst_Binding = 1;
			Per_Draw_Call_Storage_Buffer_Write.Dst_Array_Element = 0;
			Per_Draw_Call_Storage_Buffer_Write.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;
			Per_Draw_Call_Storage_Buffer_Write.Buffer_Infos = &Mesh_Per_Draw_Call_Storage_Buffer_Infos;
		}

		RHI_Write_Descriptor_Set Mesh_Per_Draw_Call_Vertex_Blending_Storage_Buffer_Write{};
		{
			Mesh_Per_Draw_Call_Vertex_Blending_Storage_Buffer_Write.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			Mesh_Per_Draw_Call_Vertex_Blending_Storage_Buffer_Write.Dst_Set = this->m_Descriptors[_mesh_global].Descriptor_Set.get();
			Mesh_Per_Draw_Call_Vertex_Blending_Storage_Buffer_Write.Dst_Binding = 2;
			Mesh_Per_Draw_Call_Vertex_Blending_Storage_Buffer_Write.Dst_Array_Element = 0;
			Mesh_Per_Draw_Call_Vertex_Blending_Storage_Buffer_Write.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;
			Mesh_Per_Draw_Call_Vertex_Blending_Storage_Buffer_Write.Buffer_Infos = &Mesh_Per_Draw_Call_Vertex_Blending_Storage_Buffer_Infos;
		}

		RHI_Write_Descriptor_Set BRDF_Image_Write{};
		{
			BRDF_Image_Write.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			BRDF_Image_Write.Dst_Set = this->m_Descriptors[_mesh_global].Descriptor_Set.get();
			BRDF_Image_Write.Dst_Binding = 3;
			BRDF_Image_Write.Dst_Array_Element = 0;
			BRDF_Image_Write.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
			BRDF_Image_Write.Image_Infos = &BRDF_Image_Infos;
		}

		RHI_Write_Descriptor_Set Irradiance_Image_Write{};
		{
			Irradiance_Image_Write.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			Irradiance_Image_Write.Dst_Set = this->m_Descriptors[_mesh_global].Descriptor_Set.get();
			Irradiance_Image_Write.Dst_Binding = 4;
			Irradiance_Image_Write.Dst_Array_Element = 0;
			Irradiance_Image_Write.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
			Irradiance_Image_Write.Image_Infos = &Irradiance_Image_Infos;
		}

		RHI_Write_Descriptor_Set Specular_Image_Write{};
		{
			Specular_Image_Write.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			Specular_Image_Write.Dst_Set = this->m_Descriptors[_mesh_global].Descriptor_Set.get();
			Specular_Image_Write.Dst_Binding = 5;
			Specular_Image_Write.Dst_Array_Element = 0;
			Specular_Image_Write.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
			Specular_Image_Write.Image_Infos = &Specular_Image_Infos;
		}

		RHI_Write_Descriptor_Set Pointt_Light_Shadow_Map_Image_Write{};
		{
			Pointt_Light_Shadow_Map_Image_Write.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			Pointt_Light_Shadow_Map_Image_Write.Dst_Set = this->m_Descriptors[_mesh_global].Descriptor_Set.get();
			Pointt_Light_Shadow_Map_Image_Write.Dst_Binding = 6;
			Pointt_Light_Shadow_Map_Image_Write.Dst_Array_Element = 0;
			Pointt_Light_Shadow_Map_Image_Write.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
			Pointt_Light_Shadow_Map_Image_Write.Image_Infos = &Pointt_Light_Shadow_Map_Image_Infos;
		}

		RHI_Write_Descriptor_Set Directional_Light_Shadow_Map_Image_Write{};
		{
			Directional_Light_Shadow_Map_Image_Write.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			Directional_Light_Shadow_Map_Image_Write.Dst_Set = this->m_Descriptors[_mesh_global].Descriptor_Set.get();
			Directional_Light_Shadow_Map_Image_Write.Dst_Binding = 7;
			Directional_Light_Shadow_Map_Image_Write.Dst_Array_Element = 0;
			Directional_Light_Shadow_Map_Image_Write.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
			Directional_Light_Shadow_Map_Image_Write.Image_Infos = &Directional_Light_Shadow_Map_Image_Infos;
		}

		const vector<const RHI_Write_Descriptor_Set*> Writes{
			&Per_Frame_Storage_Buffer_Write,
			&Per_Draw_Call_Storage_Buffer_Write,
			&Mesh_Per_Draw_Call_Vertex_Blending_Storage_Buffer_Write,
			&BRDF_Image_Write,
			&Irradiance_Image_Write,
			&Specular_Image_Write,
			&Pointt_Light_Shadow_Map_Image_Write,
			&Directional_Light_Shadow_Map_Image_Write
		};

		this->m_RHI->Update_Descriptor_Sets(&Writes, nullptr);
	}

	void Main_Camera_Pass::Setup_Skybox_Descriptor_Set(void) {
		const vector<RHI_Descriptor_Set_Layout*> Skybox_Descriptor_Set_Layouts{
				this->m_Descriptors[_skybox].Descriptor_Set_Layout.get()
		};

		RHI_Descriptor_Set_Allocate_Info Skybox_Descriptor_Set_Allocate_Info{};
		{
			Skybox_Descriptor_Set_Allocate_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
			Skybox_Descriptor_Set_Allocate_Info.Descriptor_Pool = this->m_RHI->Get_Default_Descriptor_Pool();
			Skybox_Descriptor_Set_Allocate_Info.Set_Layouts = &Skybox_Descriptor_Set_Layouts;
		}
		this->m_Descriptors[_skybox].Descriptor_Set = std::move(this->m_RHI->Allocate_Descriptor_Sets(&Skybox_Descriptor_Set_Allocate_Info).front());

		RHI_Descriptor_Buffer_Info Mesh_Per_Frame_Storage_Buffer_Info{};
		{
			Mesh_Per_Frame_Storage_Buffer_Info.Buffer = this->m_Global_Render_Resource->Storage_Buffer.Global_Upload_Ring_Buffer.get();
			Mesh_Per_Frame_Storage_Buffer_Info.Offset = 0;
			Mesh_Per_Frame_Storage_Buffer_Info.Range = sizeof(Mesh_Per_Frame_Storage_Buffer_Object);
		}
		const vector<const RHI_Descriptor_Buffer_Info*> Mesh_Per_Frame_Storage_Buffer_Infos{
			&Mesh_Per_Frame_Storage_Buffer_Info
		};

		RHI_Descriptor_Image_Info Specular_Image_Info{};
		{
			Specular_Image_Info.Sampler = this->m_Global_Render_Resource->IBL_Resource.Specular_Map_Sampler.get();
			Specular_Image_Info.Image_View = this->m_Global_Render_Resource->IBL_Resource.Specular_Map_Image_View.get();
			Specular_Image_Info.Image_Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		}
		const vector<const RHI_Descriptor_Image_Info*> Specular_Image_Infos{
			&Specular_Image_Info
		};

		RHI_Write_Descriptor_Set Per_Frame_Storage_Buffer_Write{};
		{
			Per_Frame_Storage_Buffer_Write.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			Per_Frame_Storage_Buffer_Write.Dst_Set = this->m_Descriptors[_skybox].Descriptor_Set.get();
			Per_Frame_Storage_Buffer_Write.Dst_Binding = 0;
			Per_Frame_Storage_Buffer_Write.Dst_Array_Element = 0;
			Per_Frame_Storage_Buffer_Write.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;
			Per_Frame_Storage_Buffer_Write.Buffer_Infos = &Mesh_Per_Frame_Storage_Buffer_Infos;
		}

		RHI_Write_Descriptor_Set Specular_Image_Write{};
		{
			Specular_Image_Write.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			Specular_Image_Write.Dst_Set = this->m_Descriptors[_skybox].Descriptor_Set.get();
			Specular_Image_Write.Dst_Binding = 1;
			Specular_Image_Write.Dst_Array_Element = 0;
			Specular_Image_Write.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
			Specular_Image_Write.Image_Infos = &Specular_Image_Infos;
		}

		const vector<const RHI_Write_Descriptor_Set*> Writes{
			&Per_Frame_Storage_Buffer_Write,
			&Specular_Image_Write
		};

		this->m_RHI->Update_Descriptor_Sets(&Writes, nullptr);
	}

	void Main_Camera_Pass::Setup_Axis_Descriptor_Set(void) {
		const vector<RHI_Descriptor_Set_Layout*> Axis_Descriptor_Set_Layouts{
				this->m_Descriptors[_axis].Descriptor_Set_Layout.get()
		};

		RHI_Descriptor_Set_Allocate_Info Axis_Descriptor_Set_Allocate_Info{};
		{
			Axis_Descriptor_Set_Allocate_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
			Axis_Descriptor_Set_Allocate_Info.Descriptor_Pool = this->m_RHI->Get_Default_Descriptor_Pool();
			Axis_Descriptor_Set_Allocate_Info.Set_Layouts = &Axis_Descriptor_Set_Layouts;
		}

		this->m_Descriptors[_axis].Descriptor_Set = std::move(this->m_RHI->Allocate_Descriptor_Sets(&Axis_Descriptor_Set_Allocate_Info).front());

		RHI_Descriptor_Buffer_Info Mesh_Per_Frame_Storage_Buffer_Info{};
		{
			Mesh_Per_Frame_Storage_Buffer_Info.Buffer = this->m_Global_Render_Resource->Storage_Buffer.Global_Upload_Ring_Buffer.get();
			Mesh_Per_Frame_Storage_Buffer_Info.Offset = 0;
			Mesh_Per_Frame_Storage_Buffer_Info.Range = sizeof(Mesh_Per_Frame_Storage_Buffer_Object);
		}
		const vector<const RHI_Descriptor_Buffer_Info*> Mesh_Per_Frame_Storage_Buffer_Infos{
			&Mesh_Per_Frame_Storage_Buffer_Info
		};

		RHI_Descriptor_Buffer_Info Axis_Stroage_Buffer_Info{};
		{
			Axis_Stroage_Buffer_Info.Buffer = this->m_Global_Render_Resource->Storage_Buffer.Axis_Inefficient_Strogae_Buffer.get();
			Axis_Stroage_Buffer_Info.Offset = 0;
			Axis_Stroage_Buffer_Info.Range = sizeof(Axis_Storage_Buffer_Object);
		}
		const vector<const RHI_Descriptor_Buffer_Info*> Axis_Stroage_Buffer_Infos{
			&Axis_Stroage_Buffer_Info
		};

		RHI_Write_Descriptor_Set Per_Frame_Storage_Buffer_Write{};
		{
			Per_Frame_Storage_Buffer_Write.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			Per_Frame_Storage_Buffer_Write.Dst_Set = this->m_Descriptors[_axis].Descriptor_Set.get();
			Per_Frame_Storage_Buffer_Write.Dst_Binding = 0;
			Per_Frame_Storage_Buffer_Write.Dst_Array_Element = 0;
			Per_Frame_Storage_Buffer_Write.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;
			Per_Frame_Storage_Buffer_Write.Buffer_Infos = &Mesh_Per_Frame_Storage_Buffer_Infos;
		}

		RHI_Write_Descriptor_Set Axis_Stroage_Buffer_Write{};
		{
			Axis_Stroage_Buffer_Write.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			Axis_Stroage_Buffer_Write.Dst_Set = this->m_Descriptors[_axis].Descriptor_Set.get();
			Axis_Stroage_Buffer_Write.Dst_Binding = 1;
			Axis_Stroage_Buffer_Write.Dst_Array_Element = 0;
			Axis_Stroage_Buffer_Write.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_STORAGE_BUFFER;
			Axis_Stroage_Buffer_Write.Buffer_Infos = &Axis_Stroage_Buffer_Infos;
		}

		const vector<const RHI_Write_Descriptor_Set*> Writes{
			&Per_Frame_Storage_Buffer_Write,
			&Axis_Stroage_Buffer_Write
		};

		this->m_RHI->Update_Descriptor_Sets(&Writes, nullptr);

	}

	void Main_Camera_Pass::Setup_GBuffer_Lighting_Descriptor_Set(void) {
		const vector<RHI_Descriptor_Set_Layout*> GBuffer_Light_Descriptor_Set_Layouts{
			this->m_Descriptors[_deferred_lighting].Descriptor_Set_Layout.get()
		};

		RHI_Descriptor_Set_Allocate_Info GBuffer_Light_Descriptor_Set_Allocate_Info{};
		{
			GBuffer_Light_Descriptor_Set_Allocate_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
			GBuffer_Light_Descriptor_Set_Allocate_Info.Descriptor_Pool = this->m_RHI->Get_Default_Descriptor_Pool();
			GBuffer_Light_Descriptor_Set_Allocate_Info.Set_Layouts = &GBuffer_Light_Descriptor_Set_Layouts;
		}

		this->m_Descriptors[_deferred_lighting].Descriptor_Set = std::move(this->m_RHI->Allocate_Descriptor_Sets(&GBuffer_Light_Descriptor_Set_Allocate_Info).front());
	}

	void Main_Camera_Pass::Setup_Frame_Buffer_Descriptor_Set(void) {
		RHI_Descriptor_Image_Info GBuffer_Normal_Input_Attaachment_Info{};
		{
			GBuffer_Normal_Input_Attaachment_Info.Sampler = this->m_RHI->Get_Default_Sampler(RHI_DEFAULT_SAMPLER_TYPE::DEFAULT_SAMPLER_NEAREST);
			GBuffer_Normal_Input_Attaachment_Info.Image_View = this->m_Frame_Buffer.Attachments[_main_camera_pass_gbuffer_a].Image_View.get();
			GBuffer_Normal_Input_Attaachment_Info.Image_Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		}
		const vector<const RHI_Descriptor_Image_Info*> GBuffer_Normal_Input_Attaachment_Infos{
			&GBuffer_Normal_Input_Attaachment_Info
		};

		RHI_Descriptor_Image_Info GBuffer_Metallic_Roughness_Shadingmodeid_Input_Attachment_Info{};
		{
			GBuffer_Metallic_Roughness_Shadingmodeid_Input_Attachment_Info.Sampler = this->m_RHI->Get_Default_Sampler(RHI_DEFAULT_SAMPLER_TYPE::DEFAULT_SAMPLER_NEAREST);
			GBuffer_Metallic_Roughness_Shadingmodeid_Input_Attachment_Info.Image_View = this->m_Frame_Buffer.Attachments[_main_camera_pass_gbuffer_b].Image_View.get();
			GBuffer_Metallic_Roughness_Shadingmodeid_Input_Attachment_Info.Image_Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		}
		const vector<const RHI_Descriptor_Image_Info*> GBuffer_Metallic_Roughness_Shadingmodeid_Input_Attachment_Infos{
			&GBuffer_Metallic_Roughness_Shadingmodeid_Input_Attachment_Info
		};

		RHI_Descriptor_Image_Info GBuffer_Albedo_Input_Attachment_Info{};
		{
			GBuffer_Albedo_Input_Attachment_Info.Sampler = this->m_RHI->Get_Default_Sampler(RHI_DEFAULT_SAMPLER_TYPE::DEFAULT_SAMPLER_NEAREST);
			GBuffer_Albedo_Input_Attachment_Info.Image_View = this->m_Frame_Buffer.Attachments[_main_camera_pass_gbuffer_c].Image_View.get();
			GBuffer_Albedo_Input_Attachment_Info.Image_Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		}
		const vector<const RHI_Descriptor_Image_Info*> GBuffer_Albedo_Input_Attachment_Infos{
			&GBuffer_Albedo_Input_Attachment_Info
		};

		RHI_Descriptor_Image_Info GBuffer_Depth_Input_Attachment_Info{};
		{
			GBuffer_Depth_Input_Attachment_Info.Sampler = this->m_RHI->Get_Default_Sampler(RHI_DEFAULT_SAMPLER_TYPE::DEFAULT_SAMPLER_NEAREST);
			GBuffer_Depth_Input_Attachment_Info.Image_View = this->m_RHI->Get_SwapChain_Depth_Image_View();
			GBuffer_Depth_Input_Attachment_Info.Image_Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		}
		const vector<const RHI_Descriptor_Image_Info*> GBuffer_Depth_Input_Attachment_Infos{
			&GBuffer_Depth_Input_Attachment_Info
		};

		RHI_Write_Descriptor_Set GBuffer_Normal_Descriptor_Input_Attachment_Write_Info{};
		{
			GBuffer_Normal_Descriptor_Input_Attachment_Write_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			GBuffer_Normal_Descriptor_Input_Attachment_Write_Info.Dst_Set = this->m_Descriptors[_deferred_lighting].Descriptor_Set.get();
			GBuffer_Normal_Descriptor_Input_Attachment_Write_Info.Dst_Binding = 0;
			GBuffer_Normal_Descriptor_Input_Attachment_Write_Info.Dst_Array_Element = 0;
			GBuffer_Normal_Descriptor_Input_Attachment_Write_Info.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_INPUT_ATTACHMENT;
			GBuffer_Normal_Descriptor_Input_Attachment_Write_Info.Image_Infos = &GBuffer_Normal_Input_Attaachment_Infos;
		}

		RHI_Write_Descriptor_Set GBuffer_Metallic_Roughness_Shadingmodeid_Descriptor_Input_Attachment_Write_Info{};
		{
			GBuffer_Metallic_Roughness_Shadingmodeid_Descriptor_Input_Attachment_Write_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			GBuffer_Metallic_Roughness_Shadingmodeid_Descriptor_Input_Attachment_Write_Info.Dst_Set = this->m_Descriptors[_deferred_lighting].Descriptor_Set.get();
			GBuffer_Metallic_Roughness_Shadingmodeid_Descriptor_Input_Attachment_Write_Info.Dst_Binding = 1;
			GBuffer_Metallic_Roughness_Shadingmodeid_Descriptor_Input_Attachment_Write_Info.Dst_Array_Element = 0;
			GBuffer_Metallic_Roughness_Shadingmodeid_Descriptor_Input_Attachment_Write_Info.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_INPUT_ATTACHMENT;
			GBuffer_Metallic_Roughness_Shadingmodeid_Descriptor_Input_Attachment_Write_Info.Image_Infos = &GBuffer_Metallic_Roughness_Shadingmodeid_Input_Attachment_Infos;
		}

		RHI_Write_Descriptor_Set GBuffer_Albedo_Descriptor_Input_Attachment_Write_Info{};
		{
			GBuffer_Albedo_Descriptor_Input_Attachment_Write_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			GBuffer_Albedo_Descriptor_Input_Attachment_Write_Info.Dst_Set = this->m_Descriptors[_deferred_lighting].Descriptor_Set.get();
			GBuffer_Albedo_Descriptor_Input_Attachment_Write_Info.Dst_Binding = 2;
			GBuffer_Albedo_Descriptor_Input_Attachment_Write_Info.Dst_Array_Element = 0;
			GBuffer_Albedo_Descriptor_Input_Attachment_Write_Info.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_INPUT_ATTACHMENT;
			GBuffer_Albedo_Descriptor_Input_Attachment_Write_Info.Image_Infos = &GBuffer_Albedo_Input_Attachment_Infos;
		}

		RHI_Write_Descriptor_Set GBuffer_Depth_Descriptor_Input_Attachment_Write_Info{};
		{
			GBuffer_Depth_Descriptor_Input_Attachment_Write_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			GBuffer_Depth_Descriptor_Input_Attachment_Write_Info.Dst_Set = this->m_Descriptors[_deferred_lighting].Descriptor_Set.get();
			GBuffer_Depth_Descriptor_Input_Attachment_Write_Info.Dst_Binding = 3;
			GBuffer_Depth_Descriptor_Input_Attachment_Write_Info.Dst_Array_Element = 0;
			GBuffer_Depth_Descriptor_Input_Attachment_Write_Info.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_INPUT_ATTACHMENT;
			GBuffer_Depth_Descriptor_Input_Attachment_Write_Info.Image_Infos = &GBuffer_Depth_Input_Attachment_Infos;
		}

		const vector<const RHI_Write_Descriptor_Set*> Deferred_Lighting_Descriptor_Write_Infos{
			&GBuffer_Normal_Descriptor_Input_Attachment_Write_Info,
			&GBuffer_Metallic_Roughness_Shadingmodeid_Descriptor_Input_Attachment_Write_Info,
			&GBuffer_Albedo_Descriptor_Input_Attachment_Write_Info,
			&GBuffer_Depth_Descriptor_Input_Attachment_Write_Info
		};

		this->m_RHI->Update_Descriptor_Sets(&Deferred_Lighting_Descriptor_Write_Infos, nullptr);
	}

	void Main_Camera_Pass::Setup_SwapChain_Frame_Buffers(void) {
		this->m_Swapchain_Frame_Buffers.reserve(this->m_RHI->Get_SwapChain_Image_Size());

		for (uint32_t Index = 0; Index < this->m_RHI->Get_SwapChain_Image_Size(); ++Index) {

			const vector<RHI_Image_View*> Attachments{
				this->m_Frame_Buffer.Attachments[_main_camera_pass_gbuffer_a].Image_View.get(),
				this->m_Frame_Buffer.Attachments[_main_camera_pass_gbuffer_b].Image_View.get(),
				this->m_Frame_Buffer.Attachments[_main_camera_pass_gbuffer_c].Image_View.get(),
				this->m_Frame_Buffer.Attachments[_main_camera_pass_backup_buffer_odd].Image_View.get(),
				this->m_Frame_Buffer.Attachments[_main_camera_pass_backup_buffer_even].Image_View.get(),
				this->m_Frame_Buffer.Attachments[_main_camera_pass_post_process_buffer_odd].Image_View.get(),
				this->m_Frame_Buffer.Attachments[_main_camera_pass_post_process_buffer_even].Image_View.get(),
				this->m_RHI->Get_SwapChain_Depth_Image_View(),
				this->m_RHI->Get_SwapChain_Image_View(Index),
			};



			RHI_Frame_Buffer_Create_Info Frame_Buffer_Create_Info{};
			{
				Frame_Buffer_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
				Frame_Buffer_Create_Info.Flags = 0;
				Frame_Buffer_Create_Info.Render_Pass = this->m_Frame_Buffer.Render_Pass.get();
				Frame_Buffer_Create_Info.Attachments = &Attachments;
				Frame_Buffer_Create_Info.Width = this->m_RHI->Get_SwapChain_Extent().Width;
				Frame_Buffer_Create_Info.Height = this->m_RHI->Get_SwapChain_Extent().Height;//NOTE :Sync Member Variable
				Frame_Buffer_Create_Info.Layers = 1;
			}

			this->m_Swapchain_Frame_Buffers.emplace_back(this->m_RHI->Create_Frame_Buffer(&Frame_Buffer_Create_Info));
		}
	}

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass