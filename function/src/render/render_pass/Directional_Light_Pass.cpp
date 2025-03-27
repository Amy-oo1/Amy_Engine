#include "render/render_pass/Directional_Light_Pass.h"

#include<tuple>
#include<utility>

#include "render/rhi/empty_rhi/RHI_Class.h"
#include "render/rhi/empty_rhi/RHI_Type.h"
#include "render/rhi/empty_rhi/RHI_Struct.h"

#include "render/render_system/Render_Commmon.h"
#include "render/render_system/Render_Mesh.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass {

	using NameSpace_RHI::RHI_STRUCT_TYPE;
	using NameSpace_RHI::RHI_IMAGE_TILING;
	using NameSpace_RHI::RHI_IMAGE_VIEW_TYPE;
	using NameSpace_RHI::RHI_SAMPLE_COUNT_FLAG_BIT;
	using NameSpace_RHI::RHI_ATTACHMENT_LOAD_OP;
	using NameSpace_RHI::RHI_ATTACHMENT_STORE_OP;
	using NameSpace_RHI::RHI_IMAGE_LAYOUT;
	using NameSpace_RHI::RHI_PIPELINE_BIND_POINT;
	using NameSpace_RHI::RHI_PRIMITIVE_TOPOLOGY;

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

	using NameSpace_Render_System::Mesh_Directional_Light_Shadow_Per_Frame_Storage_Buffer_Object;

	using NameSpace_Render_System::Mesh_Vertex;

	using NameSpace_Render_System::g_Directional_Light_Shadow_map_Dimension;

	Directional_Light_Pass::Directional_Light_Pass(const Render_Pass_Command_Info& Command_Info) :
		Render_Pass{ Command_Info } {
		this->Setup_Attachments();
		this->Setup_Render_Pass();
		this->Setup_Frame_Buffer();

		this->m_Descriptors.resize(1);
		this->Setup_Descriptor_Set_Layout();
	}

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
				RHI_IMAGE_USAGE_FLAG_BITS::RHI_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | RHI_IMAGE_USAGE_FLAG_BITS::RHI_IMAGE_USAGE_SAMPLED_BIT,
				to_underlying(RHI_MEMORY_PROPERTY_FLAG_BITS::RHI_MEMORY_PROPERTY_DEVICE_LOCAL_BIT),
				0
			);

			Ref_Attachments[0].Image_View = this->m_RHI->Create_Image_View(
				Ref_Attachments[0].Image.get(),
				Ref_Attachments[0].Format,
				1,
				1,
				RHI_IMAGE_VIEW_TYPE::RHI_IMAGE_VIEW_TYPE_2D,
				to_underlying(RHI_IMAGE_ASPECT_FLAG_BITS::RHI_IMAGE_ASPECT_COLOR_BIT)
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
				RHI_IMAGE_USAGE_FLAG_BITS::RHI_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | RHI_IMAGE_USAGE_FLAG_BITS::RHI_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT,
				to_underlying(RHI_MEMORY_PROPERTY_FLAG_BITS::RHI_MEMORY_PROPERTY_DEVICE_LOCAL_BIT),
				0
			);
			Ref_Attachments[1].Image_View = this->m_RHI->Create_Image_View(
				Ref_Attachments[1].Image.get(),
				Ref_Attachments[1].Format,
				1,
				1,
				RHI_IMAGE_VIEW_TYPE::RHI_IMAGE_VIEW_TYPE_2D,
				to_underlying(RHI_IMAGE_ASPECT_FLAG_BITS::RHI_IMAGE_ASPECT_DEPTH_BIT)
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
			Sub_Pass_Dependency.Src_Stage_Mask = to_underlying(RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT);
			Sub_Pass_Dependency.Dst_Stage_Mask = to_underlying(RHI_PIPELINE_STAGE_FLAG_BITS::RHI_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT);
			Sub_Pass_Dependency.Src_Access_Mask = to_underlying(RHI_ACCESS_FLAG_BITS::RHI_ACCESS_COLOR_ATTACHMENT_WRITE_BIT);
			Sub_Pass_Dependency.Dst_Access_Mask = 0;// RHI_ACCESS_FLAG_BITS::RHI_ACCESS_COLOR_ATTACHMENT_READ_BIT | RHI_ACCESS_FLAG_BITS::RHI_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
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
			Per_Frame_Storage_Buffer_Binding.Stage_Flags = to_underlying(RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_VERTEX_BIT);
			Per_Frame_Storage_Buffer_Binding.Immutable_Samplers = nullptr;
		}

		RHI_Descriptor_Set_Layout_Binding Per_Draw_Call_Storage_Buffer_Binding{};
		{
			Per_Draw_Call_Storage_Buffer_Binding.Binding = 1;
			Per_Draw_Call_Storage_Buffer_Binding.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;
			Per_Draw_Call_Storage_Buffer_Binding.Descriptor_Count = 1;
			Per_Draw_Call_Storage_Buffer_Binding.Stage_Flags = to_underlying(RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_VERTEX_BIT);
			Per_Draw_Call_Storage_Buffer_Binding.Immutable_Samplers = nullptr;
		}

		RHI_Descriptor_Set_Layout_Binding Per_Draw_Call_Vertex_Blending_Storage_Buffer_Binding{};
		{
			Per_Draw_Call_Vertex_Blending_Storage_Buffer_Binding.Binding = 2;
			Per_Draw_Call_Vertex_Blending_Storage_Buffer_Binding.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;
			Per_Draw_Call_Vertex_Blending_Storage_Buffer_Binding.Descriptor_Count = 1;
			Per_Draw_Call_Vertex_Blending_Storage_Buffer_Binding.Stage_Flags = to_underlying(RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_VERTEX_BIT);
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

		RHI_Descriptor_Buffer_Info Per_Frame_Storage_Buffer_Info{};
		{
			Per_Frame_Storage_Buffer_Info.Buffer = this->m_Global_Render_Resource->Storage_Buffer.Global_Upload_Ring_Buffer.get();
			Per_Frame_Storage_Buffer_Info.Offset = 0;
			Per_Frame_Storage_Buffer_Info.Range = sizeof(Mesh_Directional_Light_Shadow_Per_Frame_Storage_Buffer_Object);
		}
		const vector<const RHI_Descriptor_Buffer_Info*> Per_Frame_Storage_Buffer_Infos{ &Per_Frame_Storage_Buffer_Info };

		RHI_Descriptor_Buffer_Info Per_Draw_Call_Storage_Buffer_Info{};
		{
			Per_Draw_Call_Storage_Buffer_Info.Buffer = this->m_Global_Render_Resource->Storage_Buffer.Global_Upload_Ring_Buffer.get();
			Per_Draw_Call_Storage_Buffer_Info.Offset = 0;
			Per_Draw_Call_Storage_Buffer_Info.Range = sizeof(Mesh_Directional_Light_Shadow_Per_Frame_Storage_Buffer_Object);
		}
		const vector<const RHI_Descriptor_Buffer_Info*> Per_Draw_Call_Storage_Buffer_Infos{ &Per_Draw_Call_Storage_Buffer_Info };

		RHI_Descriptor_Buffer_Info Per_Draw_Call_Vertex_Blending_Storage_Buffer_Info{};
		{
			Per_Draw_Call_Vertex_Blending_Storage_Buffer_Info.Buffer = this->m_Global_Render_Resource->Storage_Buffer.Global_Upload_Ring_Buffer.get();
			Per_Draw_Call_Vertex_Blending_Storage_Buffer_Info.Offset = 0;
			Per_Draw_Call_Vertex_Blending_Storage_Buffer_Info.Range = sizeof(Mesh_Directional_Light_Shadow_Per_Frame_Storage_Buffer_Object);
		}
		const vector<const RHI_Descriptor_Buffer_Info*> Per_Draw_Call_Vertex_Blending_Storage_Buffer_Infos{ &Per_Draw_Call_Vertex_Blending_Storage_Buffer_Info };

		RHI_Write_Descriptor_Set Per_Frame_Storage_Buffer_Write{};
		{
			Per_Frame_Storage_Buffer_Write.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			Per_Frame_Storage_Buffer_Write.Dst_Set = this->m_Descriptors[0].Descriptor_Set.get();
			Per_Frame_Storage_Buffer_Write.Dst_Binding = 0;
			Per_Frame_Storage_Buffer_Write.Dst_Array_Element = 0;
			Per_Frame_Storage_Buffer_Write.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;
			Per_Frame_Storage_Buffer_Write.Buffer_Infos = &Per_Frame_Storage_Buffer_Infos;
		}

		RHI_Write_Descriptor_Set Per_Draw_Call_Storage_Buffer_Write{};
		{
			Per_Draw_Call_Storage_Buffer_Write.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			Per_Draw_Call_Storage_Buffer_Write.Dst_Set = this->m_Descriptors[0].Descriptor_Set.get();
			Per_Draw_Call_Storage_Buffer_Write.Dst_Binding = 1;
			Per_Draw_Call_Storage_Buffer_Write.Dst_Array_Element = 0;
			Per_Draw_Call_Storage_Buffer_Write.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;
			Per_Draw_Call_Storage_Buffer_Write.Buffer_Infos = &Per_Draw_Call_Storage_Buffer_Infos;
		}

		RHI_Write_Descriptor_Set Per_Draw_Call_Vertex_Blending_Storage_Buffer_Write{};
		{
			Per_Draw_Call_Vertex_Blending_Storage_Buffer_Write.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			Per_Draw_Call_Vertex_Blending_Storage_Buffer_Write.Dst_Set = this->m_Descriptors[0].Descriptor_Set.get();
			Per_Draw_Call_Vertex_Blending_Storage_Buffer_Write.Dst_Binding = 2;
			Per_Draw_Call_Vertex_Blending_Storage_Buffer_Write.Dst_Array_Element = 0;
			Per_Draw_Call_Vertex_Blending_Storage_Buffer_Write.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;
			Per_Draw_Call_Vertex_Blending_Storage_Buffer_Write.Buffer_Infos = &Per_Draw_Call_Vertex_Blending_Storage_Buffer_Infos;
		}

		const vector<const RHI_Write_Descriptor_Set*> Writes{
			&Per_Frame_Storage_Buffer_Write,
			&Per_Draw_Call_Storage_Buffer_Write,
			&Per_Draw_Call_Vertex_Blending_Storage_Buffer_Write
		};

		this->m_RHI->Update_Descriptor_Sets(&Writes, nullptr);
	}

	void Directional_Light_Pass::Setup_Pipeline(void) {
		RHI_Pipeline_Shader_Stage_Create_Info Vert_Pipeline_Shader_Stage_Create_Inof{};
		{
			//NOTE : Destroyed in the RHI
			unique_ptr<NameSpace_RHI::RHI_Shader_Module> Vertex_Shader_Module{ this->m_RHI->Create_Shader_Module(&this->m_Vertex_Shader_Code) };

			{
				Vert_Pipeline_Shader_Stage_Create_Inof.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
				Vert_Pipeline_Shader_Stage_Create_Inof.Flags = 0;
				Vert_Pipeline_Shader_Stage_Create_Inof.Stage = RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_VERTEX_BIT;
				Vert_Pipeline_Shader_Stage_Create_Inof.Module = Vertex_Shader_Module.get();
				Vert_Pipeline_Shader_Stage_Create_Inof.Name = "main";
				Vert_Pipeline_Shader_Stage_Create_Inof.Specialization_Info = nullptr;
			}
		}

		RHI_Pipeline_Shader_Stage_Create_Info Frag_Pipeline_Shader_Stage_Create_Inof{};
		{
			//NOTE : Destroyed in the RHI
			unique_ptr<NameSpace_RHI::RHI_Shader_Module> Fragment_Shader_Module{ this->m_RHI->Create_Shader_Module(&this->m_Fragment_Shader_Code) };

			{
				Frag_Pipeline_Shader_Stage_Create_Inof.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
				Frag_Pipeline_Shader_Stage_Create_Inof.Flags = 0;
				Frag_Pipeline_Shader_Stage_Create_Inof.Stage = RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_FRAGMENT_BIT;
				Frag_Pipeline_Shader_Stage_Create_Inof.Module = Fragment_Shader_Module.get();
				Frag_Pipeline_Shader_Stage_Create_Inof.Name = "main";
				Frag_Pipeline_Shader_Stage_Create_Inof.Specialization_Info = nullptr;
			}
		}

		const vector<const RHI_Pipeline_Shader_Stage_Create_Info*> Shader_Stages{
			&Vert_Pipeline_Shader_Stage_Create_Inof,
			&Frag_Pipeline_Shader_Stage_Create_Inof
		};

		RHI_Pipeline_Vertex_Input_State_Create_Info Vertex_Input_State_Create_Info{};
		{
			vector<const RHI_Vertex_Input_Binding_Description*> Vertex_Input_Binding_Descriptions{
						&Mesh_Vertex::Position_Binding_Description
			};
			vector<const RHI_Vertex_Input_Attribute_Description*> Vertex_Input_Attribute_Descriptions{
				&Mesh_Vertex::Position_Attribute_Description
			};

			{
				Vertex_Input_State_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
				Vertex_Input_State_Create_Info.Flags = 0;
				Vertex_Input_State_Create_Info.Vertex_Binding_Descriptions = &Vertex_Input_Binding_Descriptions;
				Vertex_Input_State_Create_Info.Vertex_Attribute_Descriptions = &Vertex_Input_Attribute_Descriptions;
			}
		}

		RHI_Pipeline_Input_Assembly_State_Create_Info Input_Assembly_State_Create_Info{};
		{
			Input_Assembly_State_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
			Input_Assembly_State_Create_Info.Flags = 0;
			Input_Assembly_State_Create_Info.Topology = RHI_PRIMITIVE_TOPOLOGY::RHI_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
			Input_Assembly_State_Create_Info.Primitive_Restart_Enable = RHI_FALSE;
		}

		RHI_Pipeline_Viewport_State_Create_Info Viewport_State_Create_Info{};
		{
			RHI_Viewport Viewport{};
			{
				Viewport.X = 0.0f;
				Viewport.Y = 0.0f;
				Viewport.Width = static_cast<float>(this->m_Frame_Buffer.Width);
				Viewport.Height = static_cast<float>(this->m_Frame_Buffer.Height);
				Viewport.Min_Depth = 0.0f;
				Viewport.Max_Depth = 1.0f;
			}
			const vector<const RHI_Viewport*> Viewports{ &Viewport };

			RHI_Rect_2D Scissor{};
			{
				Scissor.Offset = { 0,0 };
				Scissor.Extent = { this->m_Frame_Buffer.Width,this->m_Frame_Buffer.Height };
			}
			const vector<const RHI_Rect_2D*> Scissors{ &Scissor };

			{
				Viewport_State_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
				Viewport_State_Create_Info.Flags = 0;
				Viewport_State_Create_Info.Viewports = &Viewports;
				Viewport_State_Create_Info.Scissors = &Scissors;
			}
		}

		RHI_Pipeline_Rasterization_State_Create_Info Rasterization_State_Create_Info{};
		{
			Rasterization_State_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
			Rasterization_State_Create_Info.Flags = 0;
			Rasterization_State_Create_Info.Depth_Clamp_Enable = RHI_FALSE;
			Rasterization_State_Create_Info.Rasterizer_Discard_Enable = RHI_FALSE;
			Rasterization_State_Create_Info.Polygon_Mode = NameSpace_RHI::RHI_POLYGON_MODE::RHI_POLYGON_MODE_FILL;
			Rasterization_State_Create_Info.Cull_Mode = to_underlying(NameSpace_RHI::RHI_CULL_MODE_FLAG_BITS::RHI_CULL_MODE_BACK_BIT);
			Rasterization_State_Create_Info.Front_Face = NameSpace_RHI::RHI_FRONT_FACE::RHI_FRONT_FACE_COUNTER_CLOCKWISE;
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

		RHI_Pipeline_Color_Blend_State_Create_Info Color_Blend_State_Create_Info{};
		{
			RHI_Pipeline_Color_Blend_Attachment_State Color_Blend_Attachment{};
			{
				Color_Blend_Attachment.Blend_Enable = RHI_FALSE;
				Color_Blend_Attachment.Src_Color_Blend_Factor = NameSpace_RHI::RHI_BLEND_FACTOR::RHI_BLEND_FACTOR_ONE;
				Color_Blend_Attachment.Dst_Color_Blend_Factor = NameSpace_RHI::RHI_BLEND_FACTOR::RHI_BLEND_FACTOR_ZERO;
				Color_Blend_Attachment.Color_Blend_Op = NameSpace_RHI::RHI_BLEND_OP::RHI_BLEND_OP_ADD;
				Color_Blend_Attachment.Src_Alpha_Blend_Factor = NameSpace_RHI::RHI_BLEND_FACTOR::RHI_BLEND_FACTOR_ONE;
				Color_Blend_Attachment.Dst_Alpha_Blend_Factor = NameSpace_RHI::RHI_BLEND_FACTOR::RHI_BLEND_FACTOR_ZERO;
				Color_Blend_Attachment.Alpha_Blend_Op = NameSpace_RHI::RHI_BLEND_OP::RHI_BLEND_OP_ADD;
				Color_Blend_Attachment.Color_Write_Mask =
					RHI_COLOR_COMPONENT_FLAG_BITS::RHI_COLOR_COMPONENT_R_BIT |
					RHI_COLOR_COMPONENT_FLAG_BITS::RHI_COLOR_COMPONENT_G_BIT |
					RHI_COLOR_COMPONENT_FLAG_BITS::RHI_COLOR_COMPONENT_B_BIT |
					RHI_COLOR_COMPONENT_FLAG_BITS::RHI_COLOR_COMPONENT_A_BIT;
			}

			const vector<const RHI_Pipeline_Color_Blend_Attachment_State*> Color_Blend_Attachments{ &Color_Blend_Attachment };

			{
				Color_Blend_State_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
				Color_Blend_State_Create_Info.Flags = 0;
				Color_Blend_State_Create_Info.Logic_Op_Enable = RHI_FALSE;
				Color_Blend_State_Create_Info.Logic_Op = NameSpace_RHI::RHI_LOGIC_OP::RHI_LOGIC_OP_COPY;
				Color_Blend_State_Create_Info.Attachments = &Color_Blend_Attachments;
				Color_Blend_State_Create_Info.Blend_Constants = { 0.0f,0.0f,0.0f,0.0f };
			}
		}

		RHI_Pipeline_Dynamic_State_Create_Info Dynamic_State_Create_Info{};
		{
			Dynamic_State_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
			Dynamic_State_Create_Info.Flags = 0;
			Dynamic_State_Create_Info.Dynamic_States = nullptr;
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
			Graphics_Pipeline_Create_Info.Render_Pass = this->m_Frame_Buffer.Render_Pass.get();
			Graphics_Pipeline_Create_Info.Subpass = 0;
			Graphics_Pipeline_Create_Info.Base_Pipeline_Handle = RHI_NULL_HANDLE;
			Graphics_Pipeline_Create_Info.Base_Pipeline_Index = 0;
		}

		this->m_Render_Pipelines[0].Pipeline = this->m_RHI->Create_Graphics_Pipeline(&Graphics_Pipeline_Create_Info);
	}

	void Directional_Light_Pass::Post_Inittialize(void)
	{
	}

	void Directional_Light_Pass::PrePare_Pass_Data(shared_ptr<Render_Resource_Base> Resource) {
		this->m_Global_Render_Resource = std::dynamic_pointer_cast<Global_Render_Resource>(Resource);
		this->Setup_Descriptor_Set();

		this->Setup_Pipeline();
	}

	void Directional_Light_Pass::Draw(void) {
		//TODO : Implement
	}
}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass