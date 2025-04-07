#include "render/render_pass/Render_Pass.h"

#include "render/render_system/Render_Resource.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass {

	Visiable_Node Render_Pass::s_Visable_Node{};

	using std::static_pointer_cast;

	using NameSpace_Render_System::Render_Resource;

	Render_Pass::Render_Pass(const Render_Pass_Command_Info& Command_Info) :
		Render_Pass_Base{ Command_Info },
		m_Global_Render_Resource{ &static_pointer_cast<Render_Resource>(Command_Info.Resource)->Get_Global_Render_Resource() } {
	}

	RHI_Image* Render_Pass::Get_Frame_Buffer_Image(uint32_t Index) const {
		return this->m_Frame_Buffer.Attachments[Index].Image.get();
	}

	RHI_Image_View* Render_Pass::Get_Frame_Buffer_Image_Views(uint32_t Index) const {
		return this->m_Frame_Buffer.Attachments[Index].Image_View.get();
	}

	RHI_Descriptor_Set_Layout* Render_Pass::Get_Descriptor_Set_Layouts(uint32_t Index) const {
		return this->m_Descriptors[Index].Descriptor_Set_Layout.get();
	}

	RHI_Render_Pass* Render_Pass::Get_Render_Pass(void) const {
		return this->m_Frame_Buffer.Render_Pass.get();
	}

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass