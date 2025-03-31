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

	using NameSpace_Pass::Main_Camera_Pass_Inittialize_Info;

	//TODO : Erase It
	using namespace NameSpace_Pass;

	Render_Pipeline::Render_Pipeline(const Render_Pipeline_Info& Pipeline_Info) :
		Render_Pipeline_Base{ Pipeline_Info },
		m_Directional_Light_Pass{ std::make_shared<Directional_Light_Pass>(Render_Pass_Command_Info{Pipeline_Info.RHI,Pipeline_Info.Resource}) },
		m_Point_Light_Pass{ std::make_shared<Point_Light_Pass>(Render_Pass_Command_Info{Pipeline_Info.RHI,Pipeline_Info.Resource}) },
		m_Main_Camera_Pass{ std::make_shared<Main_Camera_Pass>(Render_Pass_Command_Info{Pipeline_Info.RHI,Pipeline_Info.Resource}) },
		m_Color_Grading_Pass{ std::make_shared<Color_Grading_Pass>(Render_Pass_Command_Info{Pipeline_Info.RHI,Pipeline_Info.Resource}) },
		m_FXAA_Pass{ std::make_shared<FXAA_Pass>(Render_Pass_Command_Info{Pipeline_Info.RHI,Pipeline_Info.Resource}) },
		m_Tone_Mapping_Pass{ std::make_shared<Tone_Mapping_Pass>(Render_Pass_Command_Info{Pipeline_Info.RHI,Pipeline_Info.Resource}) },
		m_UI_Pass{ std::make_shared<UI_Pass>(Render_Pass_Command_Info{Pipeline_Info.RHI,Pipeline_Info.Resource}) },
		m_Combine_UI_Pass{ std::make_shared<Combine_UI_Pass>(Render_Pass_Command_Info{Pipeline_Info.RHI,Pipeline_Info.Resource}) },
		m_Pick_Pss{ std::make_shared<Pick_Pass>(Render_Pass_Command_Info{Pipeline_Info.RHI,Pipeline_Info.Resource}) },
		m_Particle_Pass{ std::make_shared<Particle_Pass>(Render_Pass_Command_Info{Pipeline_Info.RHI,Pipeline_Info.Resource}) } {

		auto Ref_Main_Camera_Pass{ static_pointer_cast<Main_Camera_Pass>(this->m_Main_Camera_Pass) };

		this->m_Directional_Light_Pass->Pre_Inittialize(nullptr);
		this->m_Point_Light_Pass->Pre_Inittialize(nullptr);
		this->m_Particle_Pass->Pre_Inittialize(nullptr);

		struct Main_Camera_Pass_Inittialize_Info Main_Info {};
		{
			Main_Info.Enable_FXAA = Pipeline_Info.Enbale_FAXX;
		}

		Ref_Main_Camera_Pass->Set_Driectional_Light_Shadow_Color_Image_View(static_pointer_cast<Render_Pass>(this->m_Directional_Light_Pass)->Get_Frame_Buffer_Image_Views()[0]);
		Ref_Main_Camera_Pass->Set_Point_Light_Shadow_Color_Image_View(static_pointer_cast<Render_Pass>(this->m_Point_Light_Pass)->Get_Frame_Buffer_Image_Views()[0]);




		this->m_Main_Camera_Pass->Pre_Inittialize(&Main_Info);




	}
}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System