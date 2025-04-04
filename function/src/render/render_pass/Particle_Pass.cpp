#include "render/render_pass/Particle_Pass.h"

#include<tuple>
#include<random>

#include "meta/generated/reflection/Global_Particle.Generated_Reflection.h"

#include "config/Resource_Configer.h"
#include "manage/Resource_Manager.h"

#include "particle/Particle_Manager.h"


#include "particle_emit_comp.h"
#include "particle_kickoff_comp.h"
#include "particle_simulate_comp.h"
#include "particlebillboard_vert.h"
#include "particlebillboard_frag.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass {

	using std::static_pointer_cast;

	using NameSpace_Resource::NameSpace_Global::Reflection_Global_Particle_Operator;

	using NameSpace_Resource::NameSpace_Config::Resource_Configer;
	using NameSpace_Resource::NameSpace_Manage::Resource_Manager;

	using NameSpace_Particle::Particle_Manager;

	using NameSpace_RHI::RHI_BUFFER_USAGE_FLAG_BITS;


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



	using NameSpace_RHI::RHI_BLEND_FACTOR;
	using NameSpace_RHI::RHI_BLEND_OP;
	using NameSpace_RHI::RHI_LOGIC_OP;
	using NameSpace_RHI::RHI_COMPARE_OP;


	Particle_Pass::Particle_Pass(const Render_Pass_Command_Info& Command_Info)
		:Render_Pass{ Command_Info } {
		std::random_device Random_Device;;
		std::seed_seq Seed{ Random_Device()/*,Random_Device(),Random_Device(),Random_Device()*/ };

		this->m_Random_Engine.Seed(Seed);
	}

	void Particle_Pass::Set_Render_Pass_Handle(RHI_Render_Pass* Render_Pass) {
		this->m_Render_Pass = Render_Pass;
	}

	void Particle_Pass::Setup_Uniform_Buffer(void) {
		std::tie(this->m_Scene_Uniform_Buffer, this->m_Scene_Uniform_Memory) = this->m_RHI->Create_Buffer(
			sizeof(Patricle_Collision_Pre_Frame_Storage_Buffer_Object),
			to_underlying(RHI_BUFFER_USAGE_FLAG_BITS::RHI_BUFFER_USAGE_UNIFORM_BUFFER_BIT),
			RHI_IMAGE_USAGE_FLAG_BITS::RHI_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | RHI_IMAGE_USAGE_FLAG_BITS::RHI_IMAGE_USAGE_SAMPLED_BIT
		);

		std::tie(this->m_Compute_Uniform_Buffer, this->m_Compute_Uniform_Memory) = this->m_RHI->Create_Buffer(
			sizeof(Compute_Uniform_Buffer_Object),
			to_underlying(RHI_BUFFER_USAGE_FLAG_BITS::RHI_BUFFER_USAGE_UNIFORM_BUFFER_BIT),
			RHI_IMAGE_USAGE_FLAG_BITS::RHI_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | RHI_IMAGE_USAGE_FLAG_BITS::RHI_IMAGE_USAGE_SAMPLED_BIT
		);

		std::tie(this->m_Particle_Billbord_Uniform_Buffer, this->m_Particle_Billbord_Uniform_Memory) = this->m_RHI->Create_Buffer(
			sizeof(Particle_Billboard_Per_Frame_Storage_Buffer_Object),
			to_underlying(RHI_BUFFER_USAGE_FLAG_BITS::RHI_BUFFER_USAGE_UNIFORM_BUFFER_BIT),
			RHI_IMAGE_USAGE_FLAG_BITS::RHI_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | RHI_IMAGE_USAGE_FLAG_BITS::RHI_IMAGE_USAGE_SAMPLED_BIT
		);

		this->m_RHI->Map_Memory(this->m_Scene_Uniform_Memory.get(), 0, RHI_WHOLE_SIZE, 0, &this->m_Scene_Uniform_Buffer_Mapped);
		this->m_RHI->Map_Memory(this->m_Compute_Uniform_Memory.get(), 0, RHI_WHOLE_SIZE, 0, &this->m_Compute_Uniform_Buffer_Mapped);

		const auto& Global_Particle_Resource{ Particle_Manager::Get_Instance().Get_Global_Particle() };
		{
			this->m_Compute_Uniform_Buffer_Object.Emit_Gap = Reflection_Global_Particle_Operator::Get_Emit_Gap_Attribute(Global_Particle_Resource);
			this->m_Compute_Uniform_Buffer_Object.Emit_Count = Reflection_Global_Particle_Operator::Get_Emit_Count_Attribute(Global_Particle_Resource);
			this->m_Compute_Uniform_Buffer_Object.Max_Life = Reflection_Global_Particle_Operator::Get_Max_Life_Attribute(Global_Particle_Resource);
			this->m_Compute_Uniform_Buffer_Object.Time_Step = Reflection_Global_Particle_Operator::Get_Time_Step_Attribute(Global_Particle_Resource);
			this->m_Compute_Uniform_Buffer_Object.Gravity = Reflection_Global_Particle_Operator::Get_Gravity_Attribute(Global_Particle_Resource);
		}

		{
			float rand0 = this->m_Random_Engine.Uniform_Distribution<float>(0, 1000) * 0.001f;
			float rand1 = this->m_Random_Engine.Uniform_Distribution<float>(0, 1000) * 0.001f;
			float rand2 = this->m_Random_Engine.Uniform_Distribution<float>(0, 1000) * 0.001f;

			this->m_Compute_Uniform_Buffer_Object.Pack = Vector4{ rand0,rand1,rand2,static_cast<float>(this->m_RHI->Get_Current_Frame_Index()) };
		}

		const auto& SwapChain_Viewpot{ this->m_RHI->Get_SwapChain_Viewport() };
		this->m_Compute_Uniform_Buffer_Object.Viewport = Uvec4{ SwapChain_Viewpot.X,SwapChain_Viewpot.Y,SwapChain_Viewpot.Width,SwapChain_Viewpot.Height };

		const auto& Swap_Scisor{ this->m_RHI->Get_SwapChain_Scissor() };
		this->m_Compute_Uniform_Buffer_Object.Extent.Set_X(Swap_Scisor.Extent.Width);
		this->m_Compute_Uniform_Buffer_Object.Extent.Set_Y(Swap_Scisor.Extent.Height);
		this->m_Compute_Uniform_Buffer_Object.Extent.Set_Z(SwapChain_Viewpot.Min_Depth);
		this->m_Compute_Uniform_Buffer_Object.Extent.Set_W(SwapChain_Viewpot.Max_Depth);

		memcpy(this->m_Scene_Uniform_Buffer_Mapped, &this->m_Compute_Uniform_Buffer_Object, sizeof(Compute_Uniform_Buffer_Object));
	}

	void Particle_Pass::Setup_Descriptor_Set_Layout(void) {
		this->m_Descriptors.resize(3);

		//NOTE : Computle_Descroptor_Set
		{
			RHI_Descriptor_Set_Layout_Binding Per_Frame_Uniform_Layout_Binding{};
			{
				Per_Frame_Uniform_Layout_Binding.Binding = 0;
				Per_Frame_Uniform_Layout_Binding.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
				Per_Frame_Uniform_Layout_Binding.Descriptor_Count = 1;
				Per_Frame_Uniform_Layout_Binding.Stage_Flags = to_underlying(RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_COMPUTE_BIT);
				Per_Frame_Uniform_Layout_Binding.Immutable_Samplers = nullptr;
			}

			RHI_Descriptor_Set_Layout_Binding Per_Frame_Storgae_Layout_Binding{};
			{
				Per_Frame_Storgae_Layout_Binding.Binding = 1;
				Per_Frame_Storgae_Layout_Binding.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_STORAGE_BUFFER;
				Per_Frame_Storgae_Layout_Binding.Descriptor_Count = 1;
				Per_Frame_Storgae_Layout_Binding.Stage_Flags = to_underlying(RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_COMPUTE_BIT);
				Per_Frame_Storgae_Layout_Binding.Immutable_Samplers = nullptr;
			}

			RHI_Descriptor_Set_Layout_Binding Per_Frame_Counter_Layout_Binding{};
			{
				Per_Frame_Counter_Layout_Binding.Binding = 2;
				Per_Frame_Counter_Layout_Binding.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_STORAGE_BUFFER;
				Per_Frame_Counter_Layout_Binding.Descriptor_Count = 1;
				Per_Frame_Counter_Layout_Binding.Stage_Flags = to_underlying(RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_COMPUTE_BIT);
				Per_Frame_Counter_Layout_Binding.Immutable_Samplers = nullptr;
			}

			RHI_Descriptor_Set_Layout_Binding Per_Frame_Indirect_Dispatch_Argument_Layout_Binding{};
			{
				Per_Frame_Indirect_Dispatch_Argument_Layout_Binding.Binding = 3;
				Per_Frame_Indirect_Dispatch_Argument_Layout_Binding.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_STORAGE_BUFFER;
				Per_Frame_Indirect_Dispatch_Argument_Layout_Binding.Descriptor_Count = 1;
				Per_Frame_Indirect_Dispatch_Argument_Layout_Binding.Stage_Flags = to_underlying(RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_COMPUTE_BIT);
				Per_Frame_Indirect_Dispatch_Argument_Layout_Binding.Immutable_Samplers = nullptr;
			}

			RHI_Descriptor_Set_Layout_Binding Per_Frame_Alive_List_Layout_Binding{};
			{
				Per_Frame_Alive_List_Layout_Binding.Binding = 4;
				Per_Frame_Alive_List_Layout_Binding.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_STORAGE_BUFFER;
				Per_Frame_Alive_List_Layout_Binding.Descriptor_Count = 1;
				Per_Frame_Alive_List_Layout_Binding.Stage_Flags = to_underlying(RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_COMPUTE_BIT);
				Per_Frame_Alive_List_Layout_Binding.Immutable_Samplers = nullptr;
			}

			RHI_Descriptor_Set_Layout_Binding Per_Frame_Dead_Layout_Binding{};
			{
				Per_Frame_Dead_Layout_Binding.Binding = 5;
				Per_Frame_Dead_Layout_Binding.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_STORAGE_BUFFER;
				Per_Frame_Dead_Layout_Binding.Descriptor_Count = 1;
				Per_Frame_Dead_Layout_Binding.Stage_Flags = to_underlying(RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_COMPUTE_BIT);
				Per_Frame_Dead_Layout_Binding.Immutable_Samplers = nullptr;
			}

			RHI_Descriptor_Set_Layout_Binding Per_Frame_Alive_List_Next_Layout_Binding{};
			{
				Per_Frame_Alive_List_Next_Layout_Binding.Binding = 6;
				Per_Frame_Alive_List_Next_Layout_Binding.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_STORAGE_BUFFER;
				Per_Frame_Alive_List_Next_Layout_Binding.Descriptor_Count = 1;
				Per_Frame_Alive_List_Next_Layout_Binding.Stage_Flags = to_underlying(RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_COMPUTE_BIT);
				Per_Frame_Alive_List_Next_Layout_Binding.Immutable_Samplers = nullptr;
			}

			RHI_Descriptor_Set_Layout_Binding Per_Frame_Particle_Resource_Layout_Binding{};
			{
				Per_Frame_Particle_Resource_Layout_Binding.Binding = 7;
				Per_Frame_Particle_Resource_Layout_Binding.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_STORAGE_BUFFER;
				Per_Frame_Particle_Resource_Layout_Binding.Descriptor_Count = 1;
				Per_Frame_Particle_Resource_Layout_Binding.Stage_Flags = to_underlying(RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_COMPUTE_BIT);
				Per_Frame_Particle_Resource_Layout_Binding.Immutable_Samplers = nullptr;
			}

			RHI_Descriptor_Set_Layout_Binding Per_Frame_Scene_Uniform_Buffer_Layout_Binding{};
			{
				Per_Frame_Scene_Uniform_Buffer_Layout_Binding.Binding = 8;
				Per_Frame_Scene_Uniform_Buffer_Layout_Binding.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
				Per_Frame_Scene_Uniform_Buffer_Layout_Binding.Descriptor_Count = 1;
				Per_Frame_Scene_Uniform_Buffer_Layout_Binding.Stage_Flags = to_underlying(RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_COMPUTE_BIT);
				Per_Frame_Scene_Uniform_Buffer_Layout_Binding.Immutable_Samplers = nullptr;
			}

			RHI_Descriptor_Set_Layout_Binding Per_Frame_Position_Layout_Binding{};
			{
				Per_Frame_Position_Layout_Binding.Binding = 9;
				Per_Frame_Position_Layout_Binding.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_STORAGE_BUFFER;
				Per_Frame_Position_Layout_Binding.Descriptor_Count = 1;
				Per_Frame_Position_Layout_Binding.Stage_Flags = to_underlying(RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_COMPUTE_BIT);
				Per_Frame_Position_Layout_Binding.Immutable_Samplers = nullptr;
			}

			RHI_Descriptor_Set_Layout_Binding Per_Frame_Image_Layout_Binding{};
			{
				Per_Frame_Image_Layout_Binding.Binding = 10;
				Per_Frame_Image_Layout_Binding.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
				Per_Frame_Image_Layout_Binding.Descriptor_Count = 1;
				Per_Frame_Image_Layout_Binding.Stage_Flags = to_underlying(RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_COMPUTE_BIT);
				Per_Frame_Image_Layout_Binding.Immutable_Samplers = nullptr;
			}

			const vector<const RHI_Descriptor_Set_Layout_Binding*> Computle_Descroptor_Set_Bindings{
				&Per_Frame_Uniform_Layout_Binding,
				&Per_Frame_Storgae_Layout_Binding,
				&Per_Frame_Counter_Layout_Binding,
				&Per_Frame_Indirect_Dispatch_Argument_Layout_Binding,
				&Per_Frame_Alive_List_Layout_Binding,
				&Per_Frame_Dead_Layout_Binding,
				&Per_Frame_Alive_List_Next_Layout_Binding,
				&Per_Frame_Particle_Resource_Layout_Binding,
				&Per_Frame_Scene_Uniform_Buffer_Layout_Binding,
				&Per_Frame_Position_Layout_Binding,
				&Per_Frame_Image_Layout_Binding
			};

			RHI_Descriptor_Set_Layout_Create_Info Computle_Descroptor_Set_Layout_Create_Info{};
			{
				Computle_Descroptor_Set_Layout_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
				Computle_Descroptor_Set_Layout_Create_Info.Flags = 0;
				Computle_Descroptor_Set_Layout_Create_Info.Bindings = &Computle_Descroptor_Set_Bindings;
			}

			this->m_Descriptors[0].Descriptor_Set_Layout = this->m_RHI->Create_Descriptor_Set_Layout(&Computle_Descroptor_Set_Layout_Create_Info);
		}

		//NOTE : Scene Depth and NormalSet
		{
			RHI_Descriptor_Set_Layout_Binding GBuffer_Normal_Global_Layout_Input_Attachment_Binding{};
			{
				GBuffer_Normal_Global_Layout_Input_Attachment_Binding.Binding = 0;
				GBuffer_Normal_Global_Layout_Input_Attachment_Binding.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_STORAGE_IMAGE;
				GBuffer_Normal_Global_Layout_Input_Attachment_Binding.Descriptor_Count = 1;
				GBuffer_Normal_Global_Layout_Input_Attachment_Binding.Stage_Flags = to_underlying(RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_COMPUTE_BIT);
				GBuffer_Normal_Global_Layout_Input_Attachment_Binding.Immutable_Samplers = nullptr;
			}

			RHI_Descriptor_Set_Layout_Binding GBuffer_Position_Global_Layout_Input_Attachment_Binding{};
			{
				GBuffer_Position_Global_Layout_Input_Attachment_Binding.Binding = 1;
				GBuffer_Position_Global_Layout_Input_Attachment_Binding.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
				GBuffer_Position_Global_Layout_Input_Attachment_Binding.Descriptor_Count = 1;
				GBuffer_Position_Global_Layout_Input_Attachment_Binding.Stage_Flags = to_underlying(RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_COMPUTE_BIT);
				GBuffer_Position_Global_Layout_Input_Attachment_Binding.Immutable_Samplers = nullptr;
			}

			const vector<const RHI_Descriptor_Set_Layout_Binding*> GBuffer_Lighting_Global_Set_Layout_Bingds{
				&GBuffer_Normal_Global_Layout_Input_Attachment_Binding,
					&GBuffer_Position_Global_Layout_Input_Attachment_Binding
			};

			RHI_Descriptor_Set_Layout_Create_Info GBuffer_Lighting_Global_Set_Layout_Create_Info{};
			{
				GBuffer_Lighting_Global_Set_Layout_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
				GBuffer_Lighting_Global_Set_Layout_Create_Info.Flags = 0;
				GBuffer_Lighting_Global_Set_Layout_Create_Info.Bindings = &GBuffer_Lighting_Global_Set_Layout_Bingds;
			}

			this->m_Descriptors[1].Descriptor_Set_Layout = this->m_RHI->Create_Descriptor_Set_Layout(&GBuffer_Lighting_Global_Set_Layout_Create_Info);
		}

		//Billboard
		{
			RHI_Descriptor_Set_Layout_Binding Particle_Billboard_Global_Layout_Per_Frame_Storage_Buffer_Binding{};
			{
				Particle_Billboard_Global_Layout_Per_Frame_Storage_Buffer_Binding.Binding = 0;
				Particle_Billboard_Global_Layout_Per_Frame_Storage_Buffer_Binding.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
				Particle_Billboard_Global_Layout_Per_Frame_Storage_Buffer_Binding.Descriptor_Count = 1;
				Particle_Billboard_Global_Layout_Per_Frame_Storage_Buffer_Binding.Stage_Flags = to_underlying(RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_VERTEX_BIT);
				Particle_Billboard_Global_Layout_Per_Frame_Storage_Buffer_Binding.Immutable_Samplers = nullptr;
			}

			RHI_Descriptor_Set_Layout_Binding Particle_Billboard_Global_Layout_Per_Draw_Call_Storage_Buffer_Binding{};
			{
				Particle_Billboard_Global_Layout_Per_Draw_Call_Storage_Buffer_Binding.Binding = 1;
				Particle_Billboard_Global_Layout_Per_Draw_Call_Storage_Buffer_Binding.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_STORAGE_BUFFER;
				Particle_Billboard_Global_Layout_Per_Draw_Call_Storage_Buffer_Binding.Descriptor_Count = 1;
				Particle_Billboard_Global_Layout_Per_Draw_Call_Storage_Buffer_Binding.Stage_Flags = to_underlying(RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_VERTEX_BIT);
				Particle_Billboard_Global_Layout_Per_Draw_Call_Storage_Buffer_Binding.Immutable_Samplers = nullptr;
			}

			RHI_Descriptor_Set_Layout_Binding Particle_Billboard_Global_Layout_Image_Binding{};
			{
				Particle_Billboard_Global_Layout_Image_Binding.Binding = 2;
				Particle_Billboard_Global_Layout_Image_Binding.Descriptor_Type = RHI_DESCRIPTOR_TYPE::RHI_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
				Particle_Billboard_Global_Layout_Image_Binding.Descriptor_Count = 1;
				Particle_Billboard_Global_Layout_Image_Binding.Stage_Flags = to_underlying(RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_FRAGMENT_BIT);
				Particle_Billboard_Global_Layout_Image_Binding.Immutable_Samplers = nullptr;
			}

			const vector<const RHI_Descriptor_Set_Layout_Binding*> Billboard_Set_Layout_Bingds{
				&Particle_Billboard_Global_Layout_Per_Frame_Storage_Buffer_Binding,
				&Particle_Billboard_Global_Layout_Per_Draw_Call_Storage_Buffer_Binding
			};

			RHI_Descriptor_Set_Layout_Create_Info Billboard_Set_Layout_Create_Info{};
			{
				Billboard_Set_Layout_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
				Billboard_Set_Layout_Create_Info.Flags = 0;
				Billboard_Set_Layout_Create_Info.Bindings = &Billboard_Set_Layout_Bingds;
			}
			this->m_Descriptors[2].Descriptor_Set_Layout = this->m_RHI->Create_Descriptor_Set_Layout(&Billboard_Set_Layout_Create_Info);
		}
	}

	/*void Particle_Pass::Setup_Descriptor_Set(void) {
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
	}*/

	void Particle_Pass::Setup_Pipeline(void) {
		this->m_Render_Pipelines.resize(static_cast<size_t>(2) + _Compute_Pipeline_Type_Count);

		this->Setup_Graphics_Pipeline();
		this->Setup_Compute_Pipeline();
	}

	void Particle_Pass::Setup_Compute_Pipeline(void) {
		vector<RHI_Descriptor_Set_Layout*> Descriptor_Set_Layouts{
				this->m_Descriptors[0].Descriptor_Set_Layout.get(),
				this->m_Descriptors[1].Descriptor_Set_Layout.get(),
		};

		RHI_Pipeline_Layout_Create_Info Pipeline_Layout_Create_Info{};
		{
			Pipeline_Layout_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
			Pipeline_Layout_Create_Info.Flags = 0;
			Pipeline_Layout_Create_Info.Set_Layouts = &Descriptor_Set_Layouts;
			Pipeline_Layout_Create_Info.Push_Constant_Ranges = nullptr;
		}

		this->m_Render_Pipelines[0].Pipeline_Layout = this->m_RHI->Create_Pipeline_Layout(&Pipeline_Layout_Create_Info);

		/*RHI_Specialization_Map_Entry Specialization_Map_Entry{};
		{
			Specialization_Map_Entry.Constant_ID = 0;
			Specialization_Map_Entry.Offset = 0;
			Specialization_Map_Entry.Size = sizeof(uint32_t);
		}

		const vector<const RHI_Specialization_Map_Entry*> Specialization_Map_Entries{
			&Specialization_Map_Entry
		};

		uint32_t Buffer_Element_Data{};

		RHI_Specialization_Info Specialization_Info{};
		{
			Specialization_Info.Map_Entries = &Specialization_Map_Entries;
			Specialization_Info.Data_Size = sizeof(uint32_t);
			Specialization_Info.Data = &Buffer_Element_Data;
		}*/

		{
			unique_ptr<RHI_Shader_Module> Kickoff_Compute_Shader_Module{ this->m_RHI->Create_Shader_Module(&PARTICLE_KICKOFF_COMP) };

			RHI_Pipeline_Shader_Stage_Create_Info Kickoff_Compute_Pipeline_Shader_Stage_Create_Info{};
			{
				Kickoff_Compute_Pipeline_Shader_Stage_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
				Kickoff_Compute_Pipeline_Shader_Stage_Create_Info.Flags = 0;
				Kickoff_Compute_Pipeline_Shader_Stage_Create_Info.Stage = RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_COMPUTE_BIT;
				Kickoff_Compute_Pipeline_Shader_Stage_Create_Info.Module = Kickoff_Compute_Shader_Module.get();
				Kickoff_Compute_Pipeline_Shader_Stage_Create_Info.Name = "main";
				Kickoff_Compute_Pipeline_Shader_Stage_Create_Info.Specialization_Info = nullptr;
			}

			RHI_Compute_Pipeline_Create_Info Kickoff_Compute_Pipeline_Create_Info{};
			{
				Kickoff_Compute_Pipeline_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
				Kickoff_Compute_Pipeline_Create_Info.Flags = 0;
				Kickoff_Compute_Pipeline_Create_Info.Stage = &Kickoff_Compute_Pipeline_Shader_Stage_Create_Info;
				Kickoff_Compute_Pipeline_Create_Info.Layout = this->m_Render_Pipelines[0].Pipeline_Layout.get();
				Kickoff_Compute_Pipeline_Create_Info.Base_Pipeline_Handle = RHI_NULL_HANDLE;
				Kickoff_Compute_Pipeline_Create_Info.Base_Pipeline_Index = 0;
			}

			this->m_Render_Pipelines[_Compute_Pipeline_Type_Kickoff].Pipeline = this->m_RHI->Create_Compute_Pipeline(&Kickoff_Compute_Pipeline_Create_Info);
		}

		{
			unique_ptr<RHI_Shader_Module> Emit_Compute_Shader_Module{ this->m_RHI->Create_Shader_Module(&PARTICLE_EMIT_COMP) };

			RHI_Pipeline_Shader_Stage_Create_Info Emit_Compute_Pipeline_Shader_Stage_Create_Info{};
			{
				Emit_Compute_Pipeline_Shader_Stage_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
				Emit_Compute_Pipeline_Shader_Stage_Create_Info.Flags = 0;
				Emit_Compute_Pipeline_Shader_Stage_Create_Info.Stage = RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_COMPUTE_BIT;
				Emit_Compute_Pipeline_Shader_Stage_Create_Info.Module = Emit_Compute_Shader_Module.get();
				Emit_Compute_Pipeline_Shader_Stage_Create_Info.Name = "main";
				Emit_Compute_Pipeline_Shader_Stage_Create_Info.Specialization_Info = nullptr;
			}

			RHI_Compute_Pipeline_Create_Info Emit_Compute_Pipeline_Create_Info{};
			{
				Emit_Compute_Pipeline_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
				Emit_Compute_Pipeline_Create_Info.Flags = 0;
				Emit_Compute_Pipeline_Create_Info.Stage = &Emit_Compute_Pipeline_Shader_Stage_Create_Info;
				Emit_Compute_Pipeline_Create_Info.Layout = this->m_Render_Pipelines[0].Pipeline_Layout.get();
				Emit_Compute_Pipeline_Create_Info.Base_Pipeline_Handle = RHI_NULL_HANDLE;
				Emit_Compute_Pipeline_Create_Info.Base_Pipeline_Index = 0;
			}

			this->m_Render_Pipelines[_Compute_Pipeline_Type_Emit].Pipeline = this->m_RHI->Create_Compute_Pipeline(&Emit_Compute_Pipeline_Create_Info);
		}

		{
			unique_ptr<RHI_Shader_Module> Simulate_Compute_Shader_Module{ this->m_RHI->Create_Shader_Module(&PARTICLE_SIMULATE_COMP) };

			RHI_Pipeline_Shader_Stage_Create_Info Simulate_Compute_Pipeline_Shader_Stage_Create_Info{};
			{
				Simulate_Compute_Pipeline_Shader_Stage_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
				Simulate_Compute_Pipeline_Shader_Stage_Create_Info.Flags = 0;
				Simulate_Compute_Pipeline_Shader_Stage_Create_Info.Stage = RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_COMPUTE_BIT;
				Simulate_Compute_Pipeline_Shader_Stage_Create_Info.Module = Simulate_Compute_Shader_Module.get();
				Simulate_Compute_Pipeline_Shader_Stage_Create_Info.Name = "main";
				Simulate_Compute_Pipeline_Shader_Stage_Create_Info.Specialization_Info = nullptr;
			}

			RHI_Compute_Pipeline_Create_Info Simulate_Compute_Pipeline_Create_Info{};
			{
				Simulate_Compute_Pipeline_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
				Simulate_Compute_Pipeline_Create_Info.Flags = 0;
				Simulate_Compute_Pipeline_Create_Info.Stage = &Simulate_Compute_Pipeline_Shader_Stage_Create_Info;
				Simulate_Compute_Pipeline_Create_Info.Layout = this->m_Render_Pipelines[0].Pipeline_Layout.get();
				Simulate_Compute_Pipeline_Create_Info.Base_Pipeline_Handle = RHI_NULL_HANDLE;
				Simulate_Compute_Pipeline_Create_Info.Base_Pipeline_Index = 0;
			}

			this->m_Render_Pipelines[_Compute_Pipeline_Type_Simulate].Pipeline = this->m_RHI->Create_Compute_Pipeline(&Simulate_Compute_Pipeline_Create_Info);
		}
	}

	void Particle_Pass::Setup_Graphics_Pipeline(void) {
		const vector<RHI_Descriptor_Set_Layout*> Descriptor_Set_Layouts{
				this->m_Descriptors[2].Descriptor_Set_Layout.get(),
		};

		RHI_Pipeline_Layout_Create_Info Pipeline_Layout_Create_Info{};
		{
			Pipeline_Layout_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
			Pipeline_Layout_Create_Info.Flags = 0;
			Pipeline_Layout_Create_Info.Set_Layouts = &Descriptor_Set_Layouts;
			Pipeline_Layout_Create_Info.Push_Constant_Ranges = nullptr;
		}

		this->m_Render_Pipelines[_Graphics_Grapics_Type_Particle].Pipeline_Layout = this->m_RHI->Create_Pipeline_Layout(&Pipeline_Layout_Create_Info);

		unique_ptr<RHI_Shader_Module> Vertex_Shader_Module{ this->m_RHI->Create_Shader_Module(&PARTICLEBILLBOARD_VERT) };

		RHI_Pipeline_Shader_Stage_Create_Info Vert_Pipeline_Shader_Stage_Create_Inof{};
		{
			Vert_Pipeline_Shader_Stage_Create_Inof.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
			Vert_Pipeline_Shader_Stage_Create_Inof.Flags = 0;
			Vert_Pipeline_Shader_Stage_Create_Inof.Stage = RHI_SHADER_STAGE_FLAG_BITS::RHI_SHADER_STAGE_VERTEX_BIT;
			Vert_Pipeline_Shader_Stage_Create_Inof.Module = Vertex_Shader_Module.get();
			Vert_Pipeline_Shader_Stage_Create_Inof.Name = "main";
			Vert_Pipeline_Shader_Stage_Create_Inof.Specialization_Info = nullptr;
		}


		unique_ptr<RHI_Shader_Module> Fragment_Shader_Module{ this->m_RHI->Create_Shader_Module(&PARTICLEBILLBOARD_FRAG) };

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
			Rasterization_State_Create_Info.Polygon_Mode = NameSpace_RHI::RHI_POLYGON_MODE::RHI_POLYGON_MODE_FILL;
			Rasterization_State_Create_Info.Cull_Mode = to_underlying(NameSpace_RHI::RHI_CULL_MODE_FLAG_BITS::RHI_CULL_MODE_BACK_BIT);
			Rasterization_State_Create_Info.Front_Face = NameSpace_RHI::RHI_FRONT_FACE::RHI_FRONT_FACE_CLOCKWISE;
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
			Depth_Stencil_State_Create_Info.Depth_Write_Enable = RHI_FALSE;
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
			Color_Blend_Attachment.Blend_Enable = RHI_TRUE;
			Color_Blend_Attachment.Src_Color_Blend_Factor = RHI_BLEND_FACTOR::RHI_BLEND_FACTOR_ONE;
			Color_Blend_Attachment.Dst_Color_Blend_Factor = RHI_BLEND_FACTOR::RHI_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
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
			Graphics_Pipeline_Create_Info.Layout = this->m_Render_Pipelines[_Graphics_Grapics_Type_Particle].Pipeline_Layout.get();
			Graphics_Pipeline_Create_Info.Render_Pass = this->m_Render_Pass;
			Graphics_Pipeline_Create_Info.Subpass = _main_camera_subpass_forward_lighting;
			Graphics_Pipeline_Create_Info.Base_Pipeline_Handle = RHI_NULL_HANDLE;
			Graphics_Pipeline_Create_Info.Base_Pipeline_Index = 0;
		}

		this->m_Render_Pipelines[_Graphics_Grapics_Type_Particle].Pipeline = this->m_RHI->Create_Graphics_Pipeline(&Graphics_Pipeline_Create_Info);
	}

	void Particle_Pass::Setup_Attachments(void) {

		//NOTE : Billboard Image
		{
			const auto& Billboard_Image_Resource{ Render_Resource_Base::Load_Texture_HDR(Resource_Manager::URL_To_File_Full_Path(Particle_Manager::Get_Instance().Get_Particle_Billboard_Image_URL())) };

			std::tie(this->m_Particle_Billbord_Image, this->m_Particle_Billbord_Image_View, this->m_Particle_Billbord_Image_Allocation) = this->m_RHI->Create_Global_Image(
				{ Billboard_Image_Resource->Width,Billboard_Image_Resource->Height },
				Billboard_Image_Resource->Format,
				Billboard_Image_Resource->Mip_Levels,
				Billboard_Image_Resource->Pixels.get()
			);

			const auto& Loge_Image_Resource{ Render_Resource_Base::Load_Texture_HDR(Resource_Manager::URL_To_File_Full_Path(Particle_Manager::Get_Instance().Get_Particle_Billboard_Image_URL())) };

			std::tie(this->m_Particle_Billbord_Image, this->m_Particle_Billbord_Image_View, this->m_Particle_Billbord_Image_Allocation) = this->m_RHI->Create_Global_Image(
				{ Loge_Image_Resource->Width,Loge_Image_Resource->Height },
				Loge_Image_Resource->Format,
				Loge_Image_Resource->Mip_Levels,
				Loge_Image_Resource->Pixels.get()
			);
		}

		this->m_Frame_Buffer.Width = this->m_RHI->Get_SwapChain_Extent().Width;
		this->m_Frame_Buffer.Height = this->m_RHI->Get_SwapChain_Extent().Height;
		this->m_Frame_Buffer.Layers = 1;

		auto& Ref_Attachments{ this->m_Frame_Buffer.Attachments };

		Ref_Attachments.resize(_Attachment_Type_Count);

		Ref_Attachments[_Attachment_Type_Src_Depth].Format = this->m_RHI->Get_Physical_Depth_Format();
		Ref_Attachments[_Attachment_Type_Dst_Depth].Format = this->m_RHI->Get_Physical_Depth_Format();

		Ref_Attachments[_Attachment_Type_Src_Normal].Format = RHI_FORMAT::RHI_FORMAT_R8G8B8A8_UNORM;
		Ref_Attachments[_Attachment_Type_Dst_Normal].Format = RHI_FORMAT::RHI_FORMAT_R8G8B8A8_UNORM;


		std::tie(Ref_Attachments[_Attachment_Type_Dst_Depth].Image, Ref_Attachments[_Attachment_Type_Dst_Depth].Image_Memory) = this->m_RHI->Create_Image(
			{ this->m_Frame_Buffer.Width,this->m_Frame_Buffer.Height },
			this->m_RHI->Get_Physical_Depth_Format(),
			this->m_Frame_Buffer.Layers,
			1,
			RHI_IMAGE_TILING::RHI_IMAGE_TILING_OPTIMAL,
			RHI_IMAGE_USAGE_FLAG_BITS::RHI_IMAGE_USAGE_STORAGE_BIT | RHI_IMAGE_USAGE_FLAG_BITS::RHI_IMAGE_USAGE_TRANSFER_DST_BIT,
			to_underlying(RHI_MEMORY_PROPERTY_FLAG_BITS::RHI_MEMORY_PROPERTY_DEVICE_LOCAL_BIT),
			0
		);

		Ref_Attachments[0].Image_View = this->m_RHI->Create_Image_View(
			Ref_Attachments[0].Image.get(),
			this->m_RHI->Get_Physical_Depth_Format(),
			1,
			this->m_Frame_Buffer.Layers,
			RHI_IMAGE_VIEW_TYPE::RHI_IMAGE_VIEW_TYPE_2D,
			to_underlying(RHI_IMAGE_ASPECT_FLAG_BITS::RHI_IMAGE_ASPECT_DEPTH_BIT)
		);

		std::tie(Ref_Attachments[1].Image, Ref_Attachments[1].Image_Memory) = this->m_RHI->Create_Image(
			{ this->m_Frame_Buffer.Width,this->m_Frame_Buffer.Height },
			RHI_FORMAT::RHI_FORMAT_R8G8B8A8_UNORM,
			this->m_Frame_Buffer.Layers,
			1,
			RHI_IMAGE_TILING::RHI_IMAGE_TILING_OPTIMAL,
			RHI_IMAGE_USAGE_FLAG_BITS::RHI_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | RHI_IMAGE_USAGE_FLAG_BITS::RHI_IMAGE_USAGE_SAMPLED_BIT,
			to_underlying(RHI_MEMORY_PROPERTY_FLAG_BITS::RHI_MEMORY_PROPERTY_DEVICE_LOCAL_BIT),
			0
		);

		Ref_Attachments[1].Image_View = this->m_RHI->Create_Image_View(
			Ref_Attachments[1].Image.get(),
			RHI_FORMAT::RHI_FORMAT_R8G8B8A8_UNORM,
			1,
			this->m_Frame_Buffer.Layers,
			RHI_IMAGE_VIEW_TYPE::RHI_IMAGE_VIEW_TYPE_2D,
			to_underlying(RHI_IMAGE_ASPECT_FLAG_BITS::RHI_IMAGE_ASPECT_DEPTH_BIT)
		);


	}

	void Particle_Pass::Pre_Inittialize(shared_ptr<Render_Pass_Pre_Initialize_Info> Init_Info) {
		//const auto Partile_Info{ static_cast<const Particle_Paas_Render_Pass_Pre_Initialize_Info*>(Init_Info) };
		//{
		//	this->m_Render_Pass = Partile_Info->Render_Pass;
		//	this->m_Src_Depth_Image = Partile_Info->Depth_Image;
		//	this->m_Src_Normal_Image = Partile_Info->Normal_Image;
		//	//TODO : Add More
		//}

		//this->Setup_Uniform_Buffer();
		//this->Setup_Descriptor_Set_Layout();
		//this->Setup_Pipeline();
		//this->Setup_Attachments();
		//this->Setup_Descriptor_Set();



		RHI_Command_Buffer_Allocate_Info Compute_Command_Buffer_Allocate_Info{};
		{
			Compute_Command_Buffer_Allocate_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
			Compute_Command_Buffer_Allocate_Info.Command_Pool = this->m_RHI->Get_Default_Command_Pool();
			Compute_Command_Buffer_Allocate_Info.Level = RHI_COMMAND_BUFFER_LEVEL::RHI_COMMAND_BUFFER_LEVEL_PRIMARY;
			Compute_Command_Buffer_Allocate_Info.Command_Buffer_Count = 1;
		}

		this->m_Compute_Command_Buffer = std::move(this->m_RHI->Allocate_Command_Buffers(&Compute_Command_Buffer_Allocate_Info).front());
		this->m_Copy_Command_Buffer = std::move(this->m_RHI->Allocate_Command_Buffers(&Compute_Command_Buffer_Allocate_Info).front());

		RHI_Fence_Create_Info Fence_Create_Info{};
		{
			Fence_Create_Info.sType = RHI_STRUCT_TYPE::RHI_STRUCTURE_TYPE_FENCE_CREATE_INFO;
			Fence_Create_Info.Flags = 0;
		}

		this->m_Fence = this->m_RHI->Create_Fence(&Fence_Create_Info);
	}

	void Particle_Pass::Post_Inittialize(shared_ptr<Render_Pass_Post_Initialize_Info> Init_Info)
	{
	}

	void Particle_Pass::PrePare_Pass_Data(shared_ptr<Render_Resource_Base> Resource)
	{
	}

	void Particle_Pass::Draw(void)
	{
	}

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass