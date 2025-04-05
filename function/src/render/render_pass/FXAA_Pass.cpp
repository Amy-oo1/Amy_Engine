#include "render/render_pass/FXAA_Pass.h"

#include "render/rhi/empty_rhi/RHI_Class.h"
#include "render/rhi/empty_rhi/RHI_Type.h"
#include "render/rhi/empty_rhi/RHI_Struct.h"

#include "render/render_system/Render_Commmon.h"
#include "render/render_system/Render_Mesh.h"

#include "fxaa_vert.h"
#include "fxaa_frag.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass {

	using std::static_pointer_cast;

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


	using NameSpace_RHI::RHI_BLEND_FACTOR;
	using NameSpace_RHI::RHI_BLEND_OP;
	using NameSpace_RHI::RHI_LOGIC_OP;
	using NameSpace_RHI::RHI_COMPARE_OP;
	using NameSpace_RHI::RHI_Shader_Module;
	using NameSpace_RHI::RHI_POLYGON_MODE;
	using NameSpace_RHI::RHI_CULL_MODE_FLAG_BITS;
	using NameSpace_RHI::RHI_FRONT_FACE;
	using NameSpace_RHI::RHI_DYNAMIC_STATE;

	using NameSpace_Render_System::Mesh_Directional_Light_Shadow_Per_Frame_Storage_Buffer_Object;

	using NameSpace_Render_System::Mesh_Vertex;


	FXAA_Pass::FXAA_Pass(const Render_Pass_Command_Info& Command_Info)
		:Render_Pass{ Command_Info } {
	}

	void FXAA_Pass::Update_After_Frame_Buffer_ReCreate(RHI_Image_View* Input_Attachment) {
		this->m_Input_Attachment = Input_Attachment;

		RHI_Descriptor_Image_Info Post_Process_Per_Frame_Input_Attachment_Info{};
		{
			Post_Process_Per_Frame_Input_Attachment_Info.Sampler = this->m_RHI->Get_Default_Sampler(RHI_DEFAULT_SAMPLER_TYPE::DEFAULT_SAMPLER_NEAREST);
			Post_Process_Per_Frame_Input_Attachment_Info.Image_View = this->m_Input_Attachment;
			Post_Process_Per_Frame_Input_Attachment_Info.Image_Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		}
		const vector<const RHI_Descriptor_Image_Info*> Per_Frame_Scene_Input_Attachment_Infos{ &Post_Process_Per_Frame_Input_Attachment_Info };

		RHI_Write_Descriptor_Set Post_Process_Per_Frame_Input_Write_Descriptor_Set{};
		{
			Post_Process_Per_Frame_Input_Write_Descriptor_Set.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			Post_Process_Per_Frame_Input_Write_Descriptor_Set.Dst_Set = this->m_Descriptors[0].Descriptor_Set.get();
			Post_Process_Per_Frame_Input_Write_Descriptor_Set.Dst_Binding = 0;
			Post_Process_Per_Frame_Input_Write_Descriptor_Set.Dst_Array_Element = 0;
			Post_Process_Per_Frame_Input_Write_Descriptor_Set.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
			Post_Process_Per_Frame_Input_Write_Descriptor_Set.Image_Infos = &Per_Frame_Scene_Input_Attachment_Infos;
		}
		const vector<const RHI_Write_Descriptor_Set*> Write_Descriptor_Sets{ &Post_Process_Per_Frame_Input_Write_Descriptor_Set };

		this->m_RHI->Update_Descriptor_Sets(&Write_Descriptor_Sets, nullptr);
	}

	void FXAA_Pass::Setup_Descriptor_Set_Layout(void) {
		this->m_Descriptors.resize(1);

		RHI_Descriptor_Set_Layout_Binding Post_Process_Global__Layout_Color_Binding{};
		{
			Post_Process_Global__Layout_Color_Binding.Binding = 0;
			Post_Process_Global__Layout_Color_Binding.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
			Post_Process_Global__Layout_Color_Binding.Descriptor_Count = 1;
			Post_Process_Global__Layout_Color_Binding.Stage_Flags = to_underlying(RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_FRAGMENT_BIT);
			Post_Process_Global__Layout_Color_Binding.Immutable_Samplers = nullptr;
		}
		const vector<const RHI_Descriptor_Set_Layout_Binding*> Bindings{ &Post_Process_Global__Layout_Color_Binding, };

		RHI_Descriptor_Set_Layout_Create_Info Descriptor_Set_Layout_Create_Info{};
		{
			Descriptor_Set_Layout_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
			Descriptor_Set_Layout_Create_Info.Flags = 0;
			Descriptor_Set_Layout_Create_Info.Bindings = &Bindings;
		}

		this->m_Descriptors[0].Descriptor_Set_Layout = this->m_RHI->Create_Descriptor_Set_Layout(&Descriptor_Set_Layout_Create_Info);
	}

	void FXAA_Pass::Setup_Descriptor_Set(void) {
		const vector<RHI_Descriptor_Set_Layout*> Descriptor_Set_Layouts{ this->m_Descriptors[0].Descriptor_Set_Layout.get() };

		RHI_Descriptor_Set_Allocate_Info Descriptor_Set_Allocate_Info{};
		{
			Descriptor_Set_Allocate_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
			Descriptor_Set_Allocate_Info.Descriptor_Pool = this->m_RHI->Get_Default_Descriptor_Pool();
			Descriptor_Set_Allocate_Info.Set_Layouts = &Descriptor_Set_Layouts;
		}

		this->m_Descriptors[0].Descriptor_Set = std::move(this->m_RHI->Allocate_Descriptor_Sets(&Descriptor_Set_Allocate_Info).front());
	}

	void FXAA_Pass::Setup_Pipeline(void) {
		this->m_Render_Pipelines.resize(1);

		vector<RHI_Descriptor_Set_Layout*> Descriptor_Set_Layouts{
				this->m_Descriptors[0].Descriptor_Set_Layout.get()
		};

		RHI_Pipeline_Layout_Create_Info Pipeline_Layout_Create_Info{};
		{
			Pipeline_Layout_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
			Pipeline_Layout_Create_Info.Flags = 0;
			Pipeline_Layout_Create_Info.Set_Layouts = &Descriptor_Set_Layouts;
			Pipeline_Layout_Create_Info.Push_Constant_Ranges = nullptr;
		}
		this->m_Render_Pipelines[0].Pipeline_Layout = this->m_RHI->Create_Pipeline_Layout(&Pipeline_Layout_Create_Info);


		unique_ptr<RHI_Shader_Module> Vertex_Shader_Module{ this->m_RHI->Create_Shader_Module(&FXAA_VERT) };

		RHI_Pipeline_Shader_Stage_Create_Info Vert_Pipeline_Shader_Stage_Create_Inof{};
		{
			Vert_Pipeline_Shader_Stage_Create_Inof.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
			Vert_Pipeline_Shader_Stage_Create_Inof.Flags = 0;
			Vert_Pipeline_Shader_Stage_Create_Inof.Stage = RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_VERTEX_BIT;
			Vert_Pipeline_Shader_Stage_Create_Inof.Module = Vertex_Shader_Module.get();
			Vert_Pipeline_Shader_Stage_Create_Inof.Name = "main";
			Vert_Pipeline_Shader_Stage_Create_Inof.Specialization_Info = nullptr;
		}

		unique_ptr<RHI_Shader_Module> Fragment_Shader_Module{ this->m_RHI->Create_Shader_Module(&FXAA_FRAG) };

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
			Input_Assembly_State_Create_Info.Topology = RHI_PRIMITIVE_TOPOLOGY::RHI_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
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
		const vector<const RHI_Pipeline_Color_Blend_Attachment_State*> Color_Blend_Attachments{ &Color_Blend_Attachment };

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
			Graphics_Pipeline_Create_Info.Layout = this->m_Render_Pipelines[0].Pipeline_Layout.get();
			Graphics_Pipeline_Create_Info.Render_Pass = this->m_Render_Pass;
			Graphics_Pipeline_Create_Info.Subpass = _main_camera_subpass_fxaa;
			Graphics_Pipeline_Create_Info.Base_Pipeline_Handle = RHI_NULL_HANDLE;
			Graphics_Pipeline_Create_Info.Base_Pipeline_Index = 0;
		}

		this->m_Render_Pipelines[0].Pipeline = this->m_RHI->Create_Graphics_Pipeline(&Graphics_Pipeline_Create_Info);
	}

	void FXAA_Pass::Draw(void) {
		//TODO : Implement
	}

	void FXAA_Pass::Pre_Inittialize(shared_ptr<Render_Pass_Pre_Initialize_Info> Init_Info) {
		const auto FXAA_Info{ static_pointer_cast<FXAA_Render_Pass_Pre_Initialize_Info>(Init_Info) };
		{
			this->m_Render_Pass = FXAA_Info->Render_Pass;
			this->m_Input_Attachment = FXAA_Info->Input_Attachment;
		}

		this->Setup_Descriptor_Set_Layout();
		this->Setup_Pipeline();
		this->Setup_Descriptor_Set();

		this->Update_After_Frame_Buffer_ReCreate(this->m_Input_Attachment);
	}

	void FXAA_Pass::Post_Inittialize(shared_ptr<Render_Pass_Post_Initialize_Info> Init_Info)
	{
	}

	void FXAA_Pass::PrePare_Pass_Data(shared_ptr<Render_Resource_Base> Resource)
	{
	}

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass