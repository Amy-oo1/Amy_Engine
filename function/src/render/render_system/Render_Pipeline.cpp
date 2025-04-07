#include "render/render_system/Render_Pipeline.h"

#include<memory>

#include "logger/System_Logger.h"


#include "render/rhi/vulkan/Vulkan_RHI.h"

#include "render/render_pass/Directional_Light_Pass.h"
#include "render/render_pass/Point_Light_Paass.h"
#include "render/render_pass/Main_Camera_Pass.h"
#include "render/render_pass/Color_Grading_Pass.h"
#include "render/render_pass/FXAA_Pass.h"
#include "render/render_pass/Tone_Mapping_Pass.h"
#include "render/render_pass/UI_Pass.h"
#include "render/render_pass/Combine_UI_Pass.h"
#include "render/render_pass/Pick_Pass.h"
#include "render/render_pass/Particle_Pass.h"


namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System {

	using std::static_pointer_cast;

	using NameSpace_Core::NameSpace_Logger::System_Logger;

	using NameSpace_Pass::Directional_Light_Pass;
	using NameSpace_Pass::Point_Light_Pass;
	using NameSpace_Pass::Main_Camera_Pass;
	using NameSpace_Pass::Color_Grading_Pass;
	using NameSpace_Pass::FXAA_Pass;
	using NameSpace_Pass::Tone_Mapping_Pass;
	using NameSpace_Pass::UI_Pass;
	using NameSpace_Pass::Combine_UI_Pass;
	using NameSpace_Pass::Pick_Pass;
	using NameSpace_Pass::Particle_Pass;

	using NameSpace_Pass::LayoutType;
	using NameSpace_Pass::RenderPipeLineType;


	using NameSpace_Pass::Point_Light_Render_Pass_Pre_Initialize_Info;
	using NameSpace_Pass::Directioal_Light_Render_Pass_Pre_Initialize_Info;
	using NameSpace_Pass::Main_Camera_Render_Pass_Per_Initialize_Info;
	using NameSpace_Pass::Particle_Paas_Render_Pass_Pre_Initialize_Info;
	using NameSpace_Pass::Tone_Mapping_Render_Pass_Pre_Initialize_Info;
	using NameSpace_Pass::Color_Grading_Render_Pass_Pre_Initialize_Info;
	using NameSpace_Pass::UI_Render_Pass_Pre_Initialize_Info;
	using NameSpace_Pass::Combine_UI_Render_Pass_Pre_Initialize_Info;
	using NameSpace_Pass::Pick_Render_Pass_Pre_Initialize_Info;
	using NameSpace_Pass::FXAA_Render_Pass_Pre_Initialize_Info;


	using NameSpace_Pass::Point_Light_Render_Pass_Post_Initialize_Info;
	using NameSpace_Pass::Directioal_Light_Render_Pass_Post_Initialize_Info;

	using NameSpace_Pass::Particle_Paas_Render_Pass_Post_Initialize_Info;
	using NameSpace_Pass::Tone_Mapping_Render_Pass_Post_Initialize_Info;
	using NameSpace_Pass::Color_Grading_Render_Pass_Post_Initialize_Info;
	using NameSpace_Pass::UI_Render_Pass_Post_Initialize_Info;
	using NameSpace_Pass::Combine_UI_Render_Pass_Post_Initialize_Info;
	using NameSpace_Pass::Pick_Render_Pass_Post_Initialize_Info;
	using NameSpace_Pass::FXAA_Render_Pass_Post_Initialize_Info;



	//TODO : Erase It
	using namespace NameSpace_Pass;

	Render_Pipeline::Render_Pipeline(const Render_Pipeline_Info& Pipeline_Info) :
		Render_Pipeline_Base{ Pipeline_Info },
		m_Point_Light_Pass{ std::make_shared<Point_Light_Pass>(Render_Pass_Command_Info{Pipeline_Info.RHI,Pipeline_Info.Resource}) },
		m_Directional_Light_Pass{ std::make_shared<Directional_Light_Pass>(Render_Pass_Command_Info{Pipeline_Info.RHI,Pipeline_Info.Resource}) },
		m_Main_Camera_Pass{ std::make_shared<Main_Camera_Pass>(Render_Pass_Command_Info{Pipeline_Info.RHI,Pipeline_Info.Resource}) },
		m_Color_Grading_Pass{ std::make_shared<Color_Grading_Pass>(Render_Pass_Command_Info{Pipeline_Info.RHI,Pipeline_Info.Resource}) },
		m_FXAA_Pass{ std::make_shared<FXAA_Pass>(Render_Pass_Command_Info{Pipeline_Info.RHI,Pipeline_Info.Resource}) },
		m_Tone_Mapping_Pass{ std::make_shared<Tone_Mapping_Pass>(Render_Pass_Command_Info{Pipeline_Info.RHI,Pipeline_Info.Resource}) },
		m_UI_Pass{ std::make_shared<UI_Pass>(Render_Pass_Command_Info{Pipeline_Info.RHI,Pipeline_Info.Resource}) },
		m_Combine_UI_Pass{ std::make_shared<Combine_UI_Pass>(Render_Pass_Command_Info{Pipeline_Info.RHI,Pipeline_Info.Resource}) },
		m_Pick_Pss{ std::make_shared<Pick_Pass>(Render_Pass_Command_Info{Pipeline_Info.RHI,Pipeline_Info.Resource}) },
		m_Particle_Pass{ std::make_shared<Particle_Pass>(Render_Pass_Command_Info{Pipeline_Info.RHI,Pipeline_Info.Resource}) } {
	}

	void Render_Pipeline::Set_Axis_Visable_State(bool State) const {
		static_pointer_cast<Main_Camera_Pass>(this->m_Main_Camera_Pass)->Set_Aixs_State(State);
	}

	void Render_Pipeline::Set_Window_UI_System(shared_ptr<Window_UI> UI) const {
		static_pointer_cast<UI_Pass>(this->m_UI_Pass)->Set_Window_UI_System(UI);
	}

	void Render_Pipeline::Passes_Update_After_Recreate_Swapchain(void) const {
		auto& Ref_Main_Camera_Pass{ *static_pointer_cast<Main_Camera_Pass>(this->m_Main_Camera_Pass) };
		auto& Ref_Tone_Mapping_Pass{ *static_pointer_cast<Tone_Mapping_Pass>(this->m_Tone_Mapping_Pass) };
		auto& Ref_Color_Grading_Pass{ *static_pointer_cast<Color_Grading_Pass>(this->m_Color_Grading_Pass) };
		auto& Ref_FXAA_Pass{ *static_pointer_cast<FXAA_Pass>(this->m_FXAA_Pass) };
		auto& Ref_UI_Pass{ *static_pointer_cast<UI_Pass>(this->m_UI_Pass) };
		auto& Ref_Combine_UI_Pass{ *static_pointer_cast<Combine_UI_Pass>(this->m_Combine_UI_Pass) };
		auto& Ref_Pick_Pass{ *static_pointer_cast<Pick_Pass>(this->m_Pick_Pss) };
		auto& Ref_Particle_Pass{ *static_pointer_cast<Particle_Pass>(this->m_Particle_Pass) };

		Ref_Main_Camera_Pass.Update_After_Frame_Buffer_ReCreate();
		//TODO : Ref_Particle_Pass.Pre_Inittialize(this->m_Particle_Pass_Pre_Info);

		Ref_Tone_Mapping_Pass.Update_After_Frame_Buffer_ReCreate(Ref_Main_Camera_Pass.Get_Frame_Buffer_Image_Views(_main_camera_pass_backup_buffer_odd));
		Ref_Color_Grading_Pass.Update_After_Frame_Buffer_ReCreate(Ref_Main_Camera_Pass.Get_Frame_Buffer_Image_Views(_main_camera_pass_backup_buffer_even));
		Ref_FXAA_Pass.Update_After_Frame_Buffer_ReCreate(Ref_Main_Camera_Pass.Get_Frame_Buffer_Image_Views(_main_camera_pass_post_process_buffer_odd));
		Ref_Combine_UI_Pass.Update_After_Frame_Buffer_ReCreate(
			Ref_Main_Camera_Pass.Get_Frame_Buffer_Image_Views(_main_camera_pass_backup_buffer_odd),
			Ref_Main_Camera_Pass.Get_Frame_Buffer_Image_Views(_main_camera_pass_backup_buffer_even)
		);
		Ref_Particle_Pass.Update_After_Frame_Buffer_ReCreate();//TODO : 
		Ref_Pick_Pass.ReCreate_Frame_Buffer();

	}

	void Render_Pipeline::Build_Render_Passes(const Render_Passes_Info& Passes_Info) {

		auto _Ref_Main_Cmera_Pass{ static_pointer_cast<Render_Pass>(this->m_Main_Camera_Pass) };
		auto Ref_Main_Camera_Pass{ static_pointer_cast<Main_Camera_Pass>(this->m_Main_Camera_Pass) };

		this->m_Point_Light_Pass->Pre_Inittialize(this->m_Point_Light_Pass_Pre_Info);

		this->m_Directional_Light_Pass->Pre_Inittialize(this->m_Directional_Light_Pass_Pre_Info);;

		this->m_Main_Camera_Pass_Pre_Info = std::make_shared<Main_Camera_Render_Pass_Per_Initialize_Info>();
		{
			auto& Main_Info{ *static_pointer_cast<Main_Camera_Render_Pass_Per_Initialize_Info>(this->m_Main_Camera_Pass_Pre_Info) };

			Main_Info.Enable_FXAA = Passes_Info.Enable_FXAA;
			Main_Info.Point_Light_Shadow_Color_Image_View = static_pointer_cast<Render_Pass>(this->m_Directional_Light_Pass)->Get_Frame_Buffer_Image_Views(0);
			Main_Info.Directional_Light_Shadow_Color_Image_View = static_pointer_cast<Render_Pass>(this->m_Point_Light_Pass)->Get_Frame_Buffer_Image_Views(0);
		}
		this->m_Main_Camera_Pass->Pre_Inittialize(this->m_Main_Camera_Pass_Pre_Info);

		this->m_Particle_Pass_Pre_Info = std::make_shared<Particle_Paas_Render_Pass_Pre_Initialize_Info>();
		{
			auto& Particle_Info{ *static_pointer_cast<Particle_Paas_Render_Pass_Pre_Initialize_Info>(this->m_Particle_Pass_Pre_Info) };

			Particle_Info.Depth_Image = this->m_RHI->Get_SwapChain_Depth_Image();
			Particle_Info.Normal_Image = _Ref_Main_Cmera_Pass->Get_Frame_Buffer_Image(_main_camera_pass_gbuffer_a);
		}
		//this->m_Particle_Pass->Pre_Inittialize(this->m_Particle_Pass_Pre_Info );

		this->m_Point_Light_Pass_Post_Info = std::make_shared<Point_Light_Render_Pass_Post_Initialize_Info>();
		{
			auto& Point_Light_Info{ *static_pointer_cast<Point_Light_Render_Pass_Post_Initialize_Info>(this->m_Point_Light_Pass_Post_Info) };

			Point_Light_Info.Per_Mesh_Set_Layout = _Ref_Main_Cmera_Pass->Get_Descriptor_Set_Layouts(_per_mesh);
		}
		this->m_Point_Light_Pass->Post_Inittialize(this->m_Point_Light_Pass_Post_Info);

		this->m_Directional_Light_Pass_Post_Info = std::make_shared<Directioal_Light_Render_Pass_Post_Initialize_Info>();
		{
			auto& Directional_Light_Info{ *static_pointer_cast<Directioal_Light_Render_Pass_Post_Initialize_Info>(this->m_Directional_Light_Pass_Post_Info) };
			Directional_Light_Info.Per_Mesh_Set_Layout = _Ref_Main_Cmera_Pass->Get_Descriptor_Set_Layouts(_per_mesh);
		}
		this->m_Directional_Light_Pass->Post_Inittialize(this->m_Directional_Light_Pass_Post_Info);

		this->m_Tone_Mapping_Pass_Pre_Info = std::make_shared<Tone_Mapping_Render_Pass_Pre_Initialize_Info>();
		{
			auto& Tone_Mapping_Info{ *static_pointer_cast<Tone_Mapping_Render_Pass_Pre_Initialize_Info>(this->m_Tone_Mapping_Pass_Pre_Info) };
			Tone_Mapping_Info.Render_Pass = _Ref_Main_Cmera_Pass->Get_Render_Pass();
			Tone_Mapping_Info.Input_Attachment = _Ref_Main_Cmera_Pass->Get_Frame_Buffer_Image_Views(_main_camera_pass_backup_buffer_odd);
		}
		this->m_Tone_Mapping_Pass->Pre_Inittialize(this->m_Tone_Mapping_Pass_Pre_Info);

		this->m_Color_Grading_Pass_Pre_Info = std::make_shared<Color_Grading_Render_Pass_Pre_Initialize_Info>();
		{
			auto& Color_Grading_Info{ *static_pointer_cast<Color_Grading_Render_Pass_Pre_Initialize_Info>(this->m_Color_Grading_Pass_Pre_Info) };
			Color_Grading_Info.Render_Pass = _Ref_Main_Cmera_Pass->Get_Render_Pass();
			Color_Grading_Info.Input_Attachment = _Ref_Main_Cmera_Pass->Get_Frame_Buffer_Image_Views(_main_camera_pass_backup_buffer_even);
		}
		this->m_Color_Grading_Pass->Pre_Inittialize(this->m_Color_Grading_Pass_Pre_Info);

		this->m_UI_Pass_Pre_Info = std::make_shared<UI_Render_Pass_Pre_Initialize_Info>();
		{
			auto& UI_Info{ *static_pointer_cast<UI_Render_Pass_Pre_Initialize_Info>(this->m_UI_Pass_Pre_Info) };

			UI_Info.Render_Pass = _Ref_Main_Cmera_Pass->Get_Render_Pass();
		}
		this->m_UI_Pass->Pre_Inittialize(this->m_UI_Pass_Pre_Info);

		this->m_Combine_UI_Pass_Pre_Info = std::make_shared<Combine_UI_Render_Pass_Pre_Initialize_Info>();
		{
			auto& Combine_UI_Info{ *static_pointer_cast<Combine_UI_Render_Pass_Pre_Initialize_Info>(this->m_Combine_UI_Pass_Pre_Info) };

			Combine_UI_Info.Render_Pass = _Ref_Main_Cmera_Pass->Get_Render_Pass();
			Combine_UI_Info.Scene_Input_attachment = _Ref_Main_Cmera_Pass->Get_Frame_Buffer_Image_Views(_main_camera_pass_backup_buffer_odd);
			Combine_UI_Info.UI_Input_attachment = _Ref_Main_Cmera_Pass->Get_Frame_Buffer_Image_Views(_main_camera_pass_backup_buffer_even);
		}
		this->m_Combine_UI_Pass->Pre_Inittialize(this->m_Combine_UI_Pass_Pre_Info);

		this->m_Pick_Pass_Pre_Info = std::make_shared<Pick_Render_Pass_Pre_Initialize_Info>();
		{
			auto& Pick_Info{ *static_pointer_cast<Pick_Render_Pass_Pre_Initialize_Info>(this->m_Pick_Pass_Pre_Info) };

			Pick_Info.Per_Mesh_Set_Layout = _Ref_Main_Cmera_Pass->Get_Descriptor_Set_Layouts(_per_mesh);
		}
		this->m_Pick_Pss->Pre_Inittialize(this->m_Pick_Pass_Pre_Info);

		this->m_FXAA_Pass_Pre_Info = std::make_shared<FXAA_Render_Pass_Pre_Initialize_Info>();
		{
			auto& FXAA_Info{ *static_pointer_cast<FXAA_Render_Pass_Pre_Initialize_Info>(this->m_FXAA_Pass_Pre_Info) };

			FXAA_Info.Render_Pass = _Ref_Main_Cmera_Pass->Get_Render_Pass();
			FXAA_Info.Input_Attachment = _Ref_Main_Cmera_Pass->Get_Frame_Buffer_Image_Views(_main_camera_pass_post_process_buffer_odd);
		}
		this->m_FXAA_Pass->Pre_Inittialize(this->m_FXAA_Pass_Pre_Info);

	}

	void Render_Pipeline::Prepare_Pass_Data(shared_ptr<Render_Resource_Base> Resource) {
		this->m_Main_Camera_Pass->PrePare_Pass_Data(Resource);
		this->m_Pick_Pss->PrePare_Pass_Data(Resource);
		this->m_Directional_Light_Pass->PrePare_Pass_Data(Resource);
		this->m_Point_Light_Pass->PrePare_Pass_Data(Resource);
		this->m_Particle_Pass->PrePare_Pass_Data(Resource);//TODO : 
	}

	void Render_Pipeline::Forwad_Render(shared_ptr<Empty_RHI> RHI, shared_ptr<Render_Resource_Base> Resource) {
		auto& Ref_Resource{ *static_pointer_cast<Render_Resource>(this->m_Render_Resource) };
		auto& Ref_Vulkan_RHI{ *static_pointer_cast<NameSpace_RHI::NameSpace_Vulkan_RHI::Vulkan_RHI>(this->m_RHI) };


		Ref_Resource.Reset_Ring_Buffer_Offset(this->m_RHI->Get_Current_Frame_Index());

		this->m_RHI->Wait_For_InFlight_Fence_PFN();

		this->m_RHI->Reset_InFlight_Command_Pool_PFN();

		if (!Ref_Vulkan_RHI.Prepare_Before_Pass(std::bind(&Render_Pipeline::Passes_Update_After_Recreate_Swapchain, this))) {
			System_Logger::Get_Instance().Log(System_Logger::Level::info, "Render_Pipeline::Forwad_Render : Prepare_Before_Pass Failed");

			return;
		}

		Ref_Vulkan_RHI.Submit_Render(std::bind(&Render_Pipeline::Passes_Update_After_Recreate_Swapchain, this));


	}

	void Render_Pipeline::Deferred_Render(shared_ptr<Empty_RHI> RHI, shared_ptr<Render_Resource_Base> Render_Resource)
	{
	}

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System