#pragma once

#include<memory>

#include "render/window/Window_UI.h"

#include "render/render_system/Render_Pipeline_Base.h"
#include "render/render_pass/Render_Pass_Base.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass {

	class Main_Camera_Pass;

	using NameSpace_RHI::RHI_PIPELINE_BIND_POINT;
	using NameSpace_RHI::RHI_PIPELINE_STAGE_FLAG_BITS;
	using NameSpace_RHI::RHI_ACCESS_FLAG_BITS;
	using NameSpace_RHI::RHI_SHADER_STAGE_FLAG_BITS;
	using NameSpace_Render_System::Render_Pipeline_Base;
	using NameSpace_Render_System::Render_Pipeline_Info;
	using NameSpace_Render_System::Render_Passes_Info;
}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass


namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System {

	using std::shared_ptr;

	using NameSpace_Pass::Render_Pass_Base;

	using NameSpace_Window::Window_UI;

	using NameSpace_Pass::Render_Pass_Pre_Initialize_Info;
	using NameSpace_Pass::Render_Pass_Post_Initialize_Info;



	class Render_Pipeline final : public Render_Pipeline_Base {
		friend class Render_System;
		//friend class Render_Main_Camera_Pass;
	private:
		Render_Pipeline(const Render_Pipeline&) = delete;
		Render_Pipeline& operator=(const Render_Pipeline&) = delete;

	public:
		Render_Pipeline(const Render_Pipeline_Info& Pipeline_Info);

		~Render_Pipeline(void) = default;

	public:

		void Set_Axis_Visable_State(bool State) const;

		void Set_Window_UI_System(shared_ptr<Window_UI> UI) const;

		void Passes_Update_After_Recreate_Swapchain(void) const;

		shared_ptr<Render_Pass_Base> m_Point_Light_Pass{ nullptr };
		shared_ptr<Render_Pass_Base> m_Directional_Light_Pass{ nullptr };
		shared_ptr<Render_Pass_Base> m_Main_Camera_Pass{ nullptr };
		shared_ptr<Render_Pass_Base> m_Particle_Pass{ nullptr };
		shared_ptr<Render_Pass_Base> m_Tone_Mapping_Pass{ nullptr };
		shared_ptr<Render_Pass_Base> m_Color_Grading_Pass{ nullptr };
		shared_ptr<Render_Pass_Base> m_UI_Pass{ nullptr };
		shared_ptr<Render_Pass_Base>m_Combine_UI_Pass{ nullptr };
		shared_ptr<Render_Pass_Base> m_Pick_Pss{ nullptr };
		shared_ptr<Render_Pass_Base> m_FXAA_Pass{ nullptr };

		shared_ptr<Render_Pass_Pre_Initialize_Info> m_Point_Light_Pass_Pre_Info{ nullptr };
		shared_ptr<Render_Pass_Pre_Initialize_Info> m_Directional_Light_Pass_Pre_Info{ nullptr };
		shared_ptr<Render_Pass_Pre_Initialize_Info> m_Main_Camera_Pass_Pre_Info{ nullptr };
		shared_ptr<Render_Pass_Pre_Initialize_Info> m_Particle_Pass_Pre_Info{ nullptr };
		shared_ptr<Render_Pass_Pre_Initialize_Info> m_Tone_Mapping_Pass_Pre_Info{ nullptr };
		shared_ptr<Render_Pass_Pre_Initialize_Info> m_Color_Grading_Pass_Pre_Info{ nullptr };
		shared_ptr<Render_Pass_Pre_Initialize_Info> m_UI_Pass_Pre_Info{ nullptr };
		shared_ptr<Render_Pass_Pre_Initialize_Info> m_Combine_UI_Pass_Pre_Info{ nullptr };
		shared_ptr<Render_Pass_Pre_Initialize_Info> m_Pick_Pass_Pre_Info{ nullptr };
		shared_ptr<Render_Pass_Pre_Initialize_Info> m_FXAA_Pass_Pre_Info{ nullptr };

		shared_ptr<Render_Pass_Post_Initialize_Info> m_Point_Light_Pass_Post_Info{ nullptr };
		shared_ptr<Render_Pass_Post_Initialize_Info> m_Directional_Light_Pass_Post_Info{ nullptr };
		shared_ptr<Render_Pass_Post_Initialize_Info> m_Particle_Pass_Post_Info{ nullptr };
		shared_ptr<Render_Pass_Post_Initialize_Info> m_Tone_Mapping_Pass_Post_Info{ nullptr };
		shared_ptr<Render_Pass_Post_Initialize_Info> m_Color_Grading_Pass_Post_Info{ nullptr };
		shared_ptr<Render_Pass_Post_Initialize_Info> m_UI_Pass_Post_Info{ nullptr };
		shared_ptr<Render_Pass_Post_Initialize_Info> m_Combine_UI_Pass_Post_Info{ nullptr };
		shared_ptr<Render_Pass_Post_Initialize_Info> m_Pick_Pass_Post_Info{ nullptr };
		shared_ptr<Render_Pass_Post_Initialize_Info> m_FXAA_Pass_Post_Info{ nullptr };

	public:
		void Build_Render_Passes(const Render_Passes_Info& Passes_Info) override;

		void Prepare_Pass_Data(shared_ptr<Render_Resource_Base> Resource) override;

		void Forwad_Render(shared_ptr<Empty_RHI> RHI, shared_ptr<Render_Resource_Base> Resource) override;

		void Deferred_Render(shared_ptr<Empty_RHI> RHI, shared_ptr<Render_Resource_Base> Resource) override;
	};

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System