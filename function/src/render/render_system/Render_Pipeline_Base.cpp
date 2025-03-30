#include "render/render_system/Render_Pipeline_Base.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System {

	Render_Pipeline_Base::Render_Pipeline_Base(const Render_Pipeline_Info& Pipeline_Info){
	}

	void Render_Pipeline_Base::Prepare_Pass_Data(shared_ptr<Render_Resource_Base> Render_Resource)
	{
	}

	void Render_Pipeline_Base::Forwad_Render(shared_ptr<Empty_RHI> RHI, shared_ptr<Render_Resource_Base> Render_Resource)
	{
	}

	void Render_Pipeline_Base::Deferred_Render(shared_ptr<Empty_RHI> RHI, shared_ptr<Render_Resource_Base> Render_Resource)
	{
	}

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System