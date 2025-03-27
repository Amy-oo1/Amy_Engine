#include "render/render_pass/Directional_Light_Pass.h"

#include<tuple>
#include<utility>

#include "render/rhi/empty_rhi/RHI_Class.h"
#include "render/rhi/empty_rhi/RHI_Type.h"
#include "render/rhi/empty_rhi/RHI_Struct.h"

#include "render/render_system/Render_Commmon.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass {

	using NameSpace_RHI::RHI_STRUCT_TYPE;
	using NameSpace_RHI::RHI_IMAGE_TILING;
	using NameSpace_RHI::RHI_IMAGE_VIEW_TYPE;
	using NameSpace_RHI::RHI_SAMPLE_COUNT_FLAG_BIT;
	using NameSpace_RHI::RHI_ATTACHMENT_LOAD_OP;
	using NameSpace_RHI::RHI_ATTACHMENT_STORE_OP;
	using NameSpace_RHI::RHI_IMAGE_LAYOUT;
	using NameSpace_RHI::RHI_PIPELINE_BIND_POINT;

	using NameSpace_RHI::RHI_DESCRIPTOR_TYPE;

	using NameSpace_RHI::RHI_Image_Usage_Flag_Bits;
	using NameSpace_RHI::RHI_Image_Aspect_Flag_Bits;
	using NameSpace_RHI::RHI_Memory_Property_Flag_Bits;
	using NameSpace_RHI::RHI_Pipeline_Stage_Flag_Bits;
	using NameSpace_RHI::RHI_Access_Flag_Bits;
	using NameSpace_RHI::RHI_Shader_Stage_Flag_Bits;

	using NameSpace_RHI::RHI_Attachment_Description;
	using NameSpace_RHI::RHI_Attachment_Reference;
	using NameSpace_RHI::RHI_Subpass_Description;
	using NameSpace_RHI::RHI_Subpass_Dependency;

	using NameSpace_RHI::RHI_Descriptor_Set_Layout_Binding;

	using NameSpace_RHI::RHI_Render_Pass_Create_Info;
	using NameSpace_RHI::RHI_Frame_buffer_Create_Info;
	using NameSpace_RHI::RHI_Descriptor_Set_Layout_Create_Info;
	using NameSpace_RHI::RHI_Descriptor_Set_Allocate_Info;

	using NameSpace_Render_System::g_Directional_Light_Shadow_map_Dimension;


	void Directional_Light_Pass::Setup_Attachments(void) {
		this->m_Frame_Buffer.Width = g_Directional_Light_Shadow_map_Dimension;
		this->m_Frame_Buffer.Height = g_Directional_Light_Shadow_map_Dimension;

		auto& Ref_Attachments{ this->Render_Pass::m_Frame_Buffer.Attachments };

		Ref_Attachments.resize(2);
		//NOTE : Color
		{
			Ref_Attachments[0].Format = RHI_FORMAT::RHI_FORMAT_R32_SFLOAT;

			std::tie(Ref_Attachments[0].Image, Ref_Attachments[0].Image_Memory) = this->m_RHI->Create_Image(
				{ this->m_Frame_Buffer.Width,this->m_Frame_Buffer.Height },
				Ref_Attachments[0].Format,
				1,
				1,
				RHI_IMAGE_TILING::RHI_IMAGE_TILING_OPTIMAL,
				RHI_Image_Usage_Flag_Bits::RHI_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | RHI_Image_Usage_Flag_Bits::RHI_IMAGE_USAGE_SAMPLED_BIT,
				RHI_Memory_Property_Flag_Bits::RHI_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
				0
			);

			Ref_Attachments[0].Image_View = this->m_RHI->Create_Image_View(
				Ref_Attachments[0].Image.get(),
				Ref_Attachments[0].Format,
				1,
				1,
				RHI_IMAGE_VIEW_TYPE::RHI_IMAGE_VIEW_TYPE_2D,
				RHI_Image_Aspect_Flag_Bits::RHI_IMAGE_ASPECT_COLOR_BIT
			);
		}

		//NOTE : Depth
		{
			Ref_Attachments[1].Format = this->m_RHI->Get_Physical_Depth_Format();
			std::tie(Ref_Attachments[1].Image, Ref_Attachments[1].Image_Memory) = this->m_RHI->Create_Image(
				{ this->m_Frame_Buffer.Width,this->m_Frame_Buffer.Height },
				Ref_Attachments[1].Format,
				1,
				1,
				RHI_IMAGE_TILING::RHI_IMAGE_TILING_OPTIMAL,
				RHI_Image_Usage_Flag_Bits::RHI_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | RHI_Image_Usage_Flag_Bits::RHI_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT,
				RHI_Memory_Property_Flag_Bits::RHI_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
				0
			);
			Ref_Attachments[1].Image_View = this->m_RHI->Create_Image_View(
				Ref_Attachments[1].Image.get(),
				Ref_Attachments[1].Format,
				1,
				1,
				RHI_IMAGE_VIEW_TYPE::RHI_IMAGE_VIEW_TYPE_2D,
				RHI_Image_Aspect_Flag_Bits::RHI_IMAGE_ASPECT_DEPTH_BIT
			);
		}
	}

	void Directional_Light_Pass::Setup_Render_Pass(void) {
		RHI_Attachment_Description Color_Attachment_Description{};
		{
			Color_Attachment_Description.Flags = 0;
			Color_Attachment_Description.Format = this->m_Frame_Buffer.Attachments[0].Format;
			Color_Attachment_Description.Samples = RHI_SAMPLE_COUNT_FLAG_BIT::RHI_SAMPLE_COUNT_1_BIT;
			Color_Attachment_Description.Load_Op = RHI_ATTACHMENT_LOAD_OP::RHI_ATTACHMENT_LOAD_OP_CLEAR;
			Color_Attachment_Description.Store_Op = RHI_ATTACHMENT_STORE_OP::RHI_ATTACHMENT_STORE_OP_STORE;
			Color_Attachment_Description.Stencil_Load_Op = RHI_ATTACHMENT_LOAD_OP::RHI_ATTACHMENT_LOAD_OP_DONT_CARE;
			Color_Attachment_Description.Stencil_Store_Op = RHI_ATTACHMENT_STORE_OP::RHI_ATTACHMENT_STORE_OP_DONT_CARE;
			Color_Attachment_Description.Initial_Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_UNDEFINED;
			Color_Attachment_Description.Final_Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		}

		RHI_Attachment_Description Depth_Attachment_Description{};
		{
			Depth_Attachment_Description.Flags = 0;
			Depth_Attachment_Description.Format = this->m_Frame_Buffer.Attachments[1].Format;
			Depth_Attachment_Description.Samples = RHI_SAMPLE_COUNT_FLAG_BIT::RHI_SAMPLE_COUNT_1_BIT;
			Depth_Attachment_Description.Load_Op = RHI_ATTACHMENT_LOAD_OP::RHI_ATTACHMENT_LOAD_OP_CLEAR;
			Depth_Attachment_Description.Store_Op = RHI_ATTACHMENT_STORE_OP::RHI_ATTACHMENT_STORE_OP_DONT_CARE;
			Depth_Attachment_Description.Stencil_Load_Op = RHI_ATTACHMENT_LOAD_OP::RHI_ATTACHMENT_LOAD_OP_DONT_CARE;
			Depth_Attachment_Description.Stencil_Store_Op = RHI_ATTACHMENT_STORE_OP::RHI_ATTACHMENT_STORE_OP_DONT_CARE;
			Depth_Attachment_Description.Initial_Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_UNDEFINED;
			Depth_Attachment_Description.Final_Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
		}
		const vector<const RHI_Attachment_Description*> Attachments_Descriptions{
			&Color_Attachment_Description,
			&Depth_Attachment_Description
		};

		RHI_Attachment_Reference Color_Attachment_Reference{};
		{
			Color_Attachment_Reference.Attachment = 0;
			Color_Attachment_Reference.Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		}
		const vector<const RHI_Attachment_Reference*> Color_Attachments_References{ &Color_Attachment_Reference };

		RHI_Attachment_Reference Depth_Attachment_Reference{};
		{
			Depth_Attachment_Reference.Attachment = 1;
			Depth_Attachment_Reference.Layout = RHI_IMAGE_LAYOUT::RHI_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
		}

		RHI_Subpass_Description Sub_Pass{};
		{
			Sub_Pass.Flags = 0;
			Sub_Pass.Pipeline_Bind_Point = RHI_PIPELINE_BIND_POINT::RHI_PIPELINE_BIND_POINT_GRAPHICS;
			Sub_Pass.Input_Attachments = nullptr;
			Sub_Pass.Color_Attachments = &Color_Attachments_References;
			Sub_Pass.Resolve_Attachments = nullptr;
			Sub_Pass.Depth_Stencil_Attachment = &Depth_Attachment_Reference;
			Sub_Pass.Preserve_Attachments = nullptr;
		}
		const vector<const RHI_Subpass_Description*> Subpasses{ &Sub_Pass };

		RHI_Subpass_Dependency Sub_Pass_Dependency{};
		{
			Sub_Pass_Dependency.Src_Subpass = RHI_SUBPASS_EXTERNAL;
			Sub_Pass_Dependency.Dst_Subpass = 0;
			Sub_Pass_Dependency.Src_Stage_Mask = RHI_Pipeline_Stage_Flag_Bits::RHI_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			Sub_Pass_Dependency.Dst_Stage_Mask = RHI_Pipeline_Stage_Flag_Bits::RHI_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
			Sub_Pass_Dependency.Src_Access_Mask = RHI_Access_Flag_Bits::RHI_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
			Sub_Pass_Dependency.Dst_Access_Mask = 0;// RHI_Access_Flag_Bits::RHI_ACCESS_COLOR_ATTACHMENT_READ_BIT | RHI_ACCESS_FLAG_BITS::RHI_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
			Sub_Pass_Dependency.Dependency_Flags = 0;
		}
		const vector<const RHI_Subpass_Dependency*> Subpass_Dependencies{ &Sub_Pass_Dependency };

		RHI_Render_Pass_Create_Info Render_Pass_Create_Info{};
		{
			Render_Pass_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
			Render_Pass_Create_Info.Flags = 0;
			Render_Pass_Create_Info.Attachments = &Attachments_Descriptions;
			Render_Pass_Create_Info.Subpasses = &Subpasses;
			Render_Pass_Create_Info.Dependencies = &Subpass_Dependencies;
		}

		this->m_Frame_Buffer.Render_Pass = this->m_RHI->Create_Render_Pass(&Render_Pass_Create_Info);
	}

	void Directional_Light_Pass::Setup_Frame_Buffer(void) {
		vector<RHI_Image_View*> Attachments{
			this->m_Frame_Buffer.Attachments[0].Image_View.get(),
			this->m_Frame_Buffer.Attachments[1].Image_View.get()
		};

		RHI_Frame_buffer_Create_Info Frame_Buffer_Create_Info{};
		{
			Frame_Buffer_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
			Frame_Buffer_Create_Info.Flags = 0;
			Frame_Buffer_Create_Info.Render_Pass = this->m_Frame_Buffer.Render_Pass.get();
			Frame_Buffer_Create_Info.Attachments = &Attachments;
			Frame_Buffer_Create_Info.Width = this->m_Frame_Buffer.Width;
			Frame_Buffer_Create_Info.Height = this->m_Frame_Buffer.Height;
			Frame_Buffer_Create_Info.Layers = 1;
		}
	}

	void Directional_Light_Pass::Setup_Descriptor_Set_Layout(void) {
		RHI_Descriptor_Set_Layout_Binding Per_Frame_Storage_Buffer_Binding{};
		{
			Per_Frame_Storage_Buffer_Binding.Binding = 0;
			Per_Frame_Storage_Buffer_Binding.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;
			Per_Frame_Storage_Buffer_Binding.Descriptor_Count = 1;
			Per_Frame_Storage_Buffer_Binding.Stage_Flags = RHI_Shader_Stage_Flag_Bits::RHI_SHADER_STAGE_VERTEX_BIT;
			Per_Frame_Storage_Buffer_Binding.Immutable_Samplers = nullptr;
		}

		RHI_Descriptor_Set_Layout_Binding Per_Draw_Call_Storage_Buffer_Binding{};
		{
			Per_Draw_Call_Storage_Buffer_Binding.Binding = 1;
			Per_Draw_Call_Storage_Buffer_Binding.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;
			Per_Draw_Call_Storage_Buffer_Binding.Descriptor_Count = 1;
			Per_Draw_Call_Storage_Buffer_Binding.Stage_Flags = RHI_Shader_Stage_Flag_Bits::RHI_SHADER_STAGE_VERTEX_BIT;
			Per_Draw_Call_Storage_Buffer_Binding.Immutable_Samplers = nullptr;
		}

		RHI_Descriptor_Set_Layout_Binding Per_Draw_Call_Vertex_Blending_Storage_Buffer_Binding{};
		{
			Per_Draw_Call_Vertex_Blending_Storage_Buffer_Binding.Binding = 2;
			Per_Draw_Call_Vertex_Blending_Storage_Buffer_Binding.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;
			Per_Draw_Call_Vertex_Blending_Storage_Buffer_Binding.Descriptor_Count = 1;
			Per_Draw_Call_Vertex_Blending_Storage_Buffer_Binding.Stage_Flags = RHI_Shader_Stage_Flag_Bits::RHI_SHADER_STAGE_VERTEX_BIT;
			Per_Draw_Call_Vertex_Blending_Storage_Buffer_Binding.Immutable_Samplers = nullptr;
		}
		const vector<const RHI_Descriptor_Set_Layout_Binding*> Bindings{
			&Per_Frame_Storage_Buffer_Binding,
			&Per_Draw_Call_Storage_Buffer_Binding,
			&Per_Draw_Call_Vertex_Blending_Storage_Buffer_Binding
		};

		RHI_Descriptor_Set_Layout_Create_Info Descriptor_Set_Layout_Create_Info{};
		{
			Descriptor_Set_Layout_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
			Descriptor_Set_Layout_Create_Info.Flags = 0;
			Descriptor_Set_Layout_Create_Info.Bindings = &Bindings;
		}

		this->m_Descriptors[0].Descriptor_Set_Layout = this->m_RHI->Create_Descriptor_Set_Layout(&Descriptor_Set_Layout_Create_Info);

	}

	void Directional_Light_Pass::Setup_Descriptor_Set(void) {
		const vector<RHI_Descriptor_Set_Layout*> Descriptor_Set_Layouts{ this->m_Descriptors[0].Descriptor_Set_Layout.get() };

		RHI_Descriptor_Set_Allocate_Info Descriptor_Set_Allocate_Info{};
		{
			Descriptor_Set_Allocate_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
			Descriptor_Set_Allocate_Info.Descriptor_Pool = this->m_RHI->Get_Default_Descriptor_Pool();
			Descriptor_Set_Allocate_Info.Set_Layouts = &Descriptor_Set_Layouts;
		}

		this->m_Descriptors[0].Descriptor_Set = std::move(this->m_RHI->Allocate_Descriptor_Sets(&Descriptor_Set_Allocate_Info).front());
	}

	void Directional_Light_Pass::Post_Inittialize(void)
	{
	}
	void Directional_Light_Pass::PrePare_Pass_Data(shared_ptr<Render_Resource_Base> Resource)
	{
	}
	void Directional_Light_Pass::Draw(void)
	{
	}
}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass