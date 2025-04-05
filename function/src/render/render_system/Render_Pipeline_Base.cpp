#include "render/render_system/Render_Pipeline_Base.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System {

	Render_Pipeline_Base::Render_Pipeline_Base(const Render_Pipeline_Info& Pipeline_Info) :
		m_RHI{ Pipeline_Info.RHI },
		m_Render_Resource{ Pipeline_Info.Resource } {
	}

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System