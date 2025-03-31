#include "render/render_pass/Render_Pass.h"

#include "render/render_system/Render_Resource.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass {

	using NameSpace_Render_System::Render_Resource;

	Render_Pass::Render_Pass(const Render_Pass_Command_Info& Command_Info) :
		Render_Pass_Base{ Command_Info } {
	}

	vector<RHI_Image_View*> Render_Pass::Get_Frame_Buffer_Image_Views(void) const{
		vector<RHI_Image_View*> Image_Views;
		Image_Views.reserve(this->m_Frame_Buffer.Attachments.size());

		for (const auto& Attachment : this->m_Frame_Buffer.Attachments)
			Image_Views.push_back(Attachment.Image_View.get());

		return Image_Views;
	}

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass