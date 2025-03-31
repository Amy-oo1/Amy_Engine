#pragma once

#include<memory>

#include "render/render_system/Render_Pipeline_Base.h"
#include "render/render_pass/Render_Pass_Base.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System {

	using std::shared_ptr;

	using NameSpace_Pass::Render_Pass_Base;

	class Render_Pipeline final : public Render_Pipeline_Base {
	private:
		Render_Pipeline(const Render_Pipeline&) = delete;
		Render_Pipeline& operator=(const Render_Pipeline&) = delete;

	public:
		Render_Pipeline(const Render_Pipeline_Info& Pipeline_Info);

		~Render_Pipeline(void) = default;


		shared_ptr<Render_Pass_Base> m_Directional_Light_Pass{ nullptr };
		shared_ptr<Render_Pass_Base> m_Point_Light_Pass{ nullptr };
		shared_ptr<Render_Pass_Base> m_Main_Camera_Pass{ nullptr };
		shared_ptr<Render_Pass_Base> m_Color_Grading_Pass{ nullptr };
		shared_ptr<Render_Pass_Base> m_FXAA_Pass{ nullptr };
		shared_ptr<Render_Pass_Base> m_Tone_Mapping_Pass{ nullptr };
		shared_ptr<Render_Pass_Base> m_UI_Pass{ nullptr };
		shared_ptr<Render_Pass_Base>m_Combine_UI_Pass{ nullptr };
		shared_ptr<Render_Pass_Base> m_Pick_Pss{ nullptr };
		shared_ptr<Render_Pass_Base> m_Particle_Pass{ nullptr };
	};

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System