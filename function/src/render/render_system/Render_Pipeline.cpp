#include "render/render_system/Render_Pipeline.h"

#include<memory>

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

		auto _Ref_Main_Cmera_Pass{ static_pointer_cast<Render_Pass>(this->m_Main_Camera_Pass) };
		auto Ref_Main_Camera_Pass{ static_pointer_cast<Main_Camera_Pass>(this->m_Main_Camera_Pass) };

		Point_Light_Render_Pass_Pre_Initialize_Info Point_Light_Pass_Pre_Info{};
		this->m_Point_Light_Pass->Pre_Inittialize(&Point_Light_Pass_Pre_Info);

		Directioal_Light_Render_Pass_Pre_Initialize_Info Directional_Light_Pass_Pre_Info{};
		this->m_Directional_Light_Pass->Pre_Inittialize(&Directional_Light_Pass_Pre_Info);;

		struct Main_Camera_Render_Pass_Per_Initialize_Info Main_Info {};
		{
			Main_Info.Enable_FXAA = Pipeline_Info.Enbale_FAXX;
			Main_Info.Point_Light_Shadow_Color_Image_View = static_pointer_cast<Render_Pass>(this->m_Directional_Light_Pass)->Get_Frame_Buffer_Image_Views(0);
			Main_Info.Directional_Light_Shadow_Color_Image_View = static_pointer_cast<Render_Pass>(this->m_Point_Light_Pass)->Get_Frame_Buffer_Image_Views(0);
		}
		this->m_Main_Camera_Pass->Pre_Inittialize(&Main_Info);

		Particle_Paas_Render_Pass_Pre_Initialize_Info Particle_Pass_Pre_Info{};
		{
			Particle_Pass_Pre_Info.Render_Pass = _Ref_Main_Cmera_Pass->Get_Render_Pass();
			Particle_Pass_Pre_Info.Depth_Image = this->m_RHI->Get_SwapChain_Depth_Image();
			Particle_Pass_Pre_Info.Normal_Image = _Ref_Main_Cmera_Pass->Get_Frame_Buffer_Image(_main_camera_pass_gbuffer_a);

		}
		//this->m_Particle_Pass->Pre_Inittialize(&Particle_Pass_Pre_Info);

		Point_Light_Render_Pass_Post_Initialize_Info Point_Light_Pass_Post_Info{};
		{
			Point_Light_Pass_Post_Info.Per_Mesh_Set_Layout = _Ref_Main_Cmera_Pass->Get_Descriptor_Set_Layouts(_per_mesh);
		}
		this->m_Point_Light_Pass->Post_Inittialize(&Point_Light_Pass_Post_Info);

		Directioal_Light_Render_Pass_Post_Initialize_Info Directional_Light_Pass_Post_Info{};
		{
			Directional_Light_Pass_Post_Info.Per_Mesh_Set_Layout = _Ref_Main_Cmera_Pass->Get_Descriptor_Set_Layouts(_per_mesh);
		}
		this->m_Directional_Light_Pass->Post_Inittialize(&Directional_Light_Pass_Post_Info);

		Tone_Mapping_Render_Pass_Pre_Initialize_Info Tone_Mapping_Pass_Pre_Info{};
		{
			Tone_Mapping_Pass_Pre_Info.Render_Pass = _Ref_Main_Cmera_Pass->Get_Render_Pass();
			Tone_Mapping_Pass_Pre_Info.Input_Attachment = _Ref_Main_Cmera_Pass->Get_Frame_Buffer_Image_Views(_main_camera_pass_backup_buffer_odd);
		}
		this->m_Tone_Mapping_Pass->Pre_Inittialize(&Tone_Mapping_Pass_Pre_Info);

		Color_Grading_Render_Pass_Pre_Initialize_Info Color_Grading_Pass_Pre_Info{};
		{
			Color_Grading_Pass_Pre_Info.Render_Pass = _Ref_Main_Cmera_Pass->Get_Render_Pass();
			Color_Grading_Pass_Pre_Info.Input_Attachment = _Ref_Main_Cmera_Pass->Get_Frame_Buffer_Image_Views(_main_camera_pass_backup_buffer_even);
		}
		this->m_Color_Grading_Pass->Pre_Inittialize(&Color_Grading_Pass_Pre_Info);

		UI_Render_Pass_Pre_Initialize_Info UI_Pass_Pre_Info{};
		{
			UI_Pass_Pre_Info.Render_Pass = _Ref_Main_Cmera_Pass->Get_Render_Pass();
		}
		this->m_UI_Pass->Pre_Inittialize(&UI_Pass_Pre_Info);

		Combine_UI_Render_Pass_Pre_Initialize_Info Combine_UI_Pass_Pre_Info{};
		{
			Combine_UI_Pass_Pre_Info.Render_Pass = _Ref_Main_Cmera_Pass->Get_Render_Pass();
			Combine_UI_Pass_Pre_Info.Scene_Input_attachment = _Ref_Main_Cmera_Pass->Get_Frame_Buffer_Image_Views(_main_camera_pass_backup_buffer_odd);
			Combine_UI_Pass_Pre_Info.UI_Input_attachment = _Ref_Main_Cmera_Pass->Get_Frame_Buffer_Image_Views(_main_camera_pass_backup_buffer_even);
		}
		this->m_Combine_UI_Pass->Pre_Inittialize(&Combine_UI_Pass_Pre_Info);

		Pick_Render_Pass_Pre_Initialize_Info Pick_Pass_Pre_Info{};
		{
			Pick_Pass_Pre_Info.Per_Mesh_Set_Layout = _Ref_Main_Cmera_Pass->Get_Descriptor_Set_Layouts(_per_mesh);
		}
		this->m_Pick_Pss->Pre_Inittialize(&Pick_Pass_Pre_Info);

		FXAA_Render_Pass_Pre_Initialize_Info FXAA_Pass_Pre_Info{};
		{
			FXAA_Pass_Pre_Info.Render_Pass = _Ref_Main_Cmera_Pass->Get_Render_Pass();
			FXAA_Pass_Pre_Info.Input_Attachment = _Ref_Main_Cmera_Pass->Get_Frame_Buffer_Image_Views(_main_camera_pass_post_process_buffer_odd);
		}
		this->m_FXAA_Pass->Pre_Inittialize(&FXAA_Pass_Pre_Info);

	}
}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System