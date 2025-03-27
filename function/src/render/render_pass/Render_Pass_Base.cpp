#include "render/render_pass/Render_Pass_Base.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass {

	Render_Pass_Base::Render_Pass_Base(const Render_Pass_Command_Info& Command_Info) :
		m_RHI{ Command_Info.RHI },
		m_Resource{ Command_Info.Resource } {
	}

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass