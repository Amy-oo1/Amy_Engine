#pragma once

#include "render/render_system/Render_Resource.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System {

	struct Render_Pipeline_Info final {
		bool Enbale_FAXX{ false };
		shared_ptr<Render_Resource_Base> Resource;
	};

	class Render_Pipeline_Base {
	private:
		Render_Pipeline_Base(const Render_Pipeline_Base&) = delete;
		Render_Pipeline_Base& operator=(const Render_Pipeline_Base&) = delete;

	public:
		/*	Render_Pipeline_Base(const Render_Pipeline_Info& Pipeline_Info) :
				m_Resource{ Pipeline_Info.Resource } {
			}*/

		virtual ~Render_Pipeline_Base(void) = default;


	};

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System