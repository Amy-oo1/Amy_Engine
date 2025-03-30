#pragma once

#include "render/render_system/Render_Pipeline_Base.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System {

	class Render_Pipeline final : public Render_Pipeline_Base {
	private:
		Render_Pipeline(const Render_Pipeline&) = delete;
		Render_Pipeline& operator=(const Render_Pipeline&) = delete;

	public:
		Render_Pipeline(const Render_Pipeline_Info& Pipeline_Info);

		~Render_Pipeline(void) = default;

	};

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System