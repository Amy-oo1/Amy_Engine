#include "default_editor/Editor_Global_Context.h"

#include "global/Global_Systemer.h"

namespace NameSpace_Editor {

	using NameSpace_Function::Namespace_Global::Global_Systemer;

	Editor_Global_Context::Editor_Global_Context(void) :
		m_Window_System{ Global_Systemer::Get_Instance().Main_Window },
		m_Render_System{ Global_Systemer::Get_Instance().Main_Render_System },
		m_Camera{ this->m_Render_System->Get_Render_Camera() },
		m_Scene_Manager{ std::make_shared<Editor_Scene_Manage>() },
		m_Input_Manager{ std::make_shared<Editor_Input_Manager>() } {
	}

	Editor_Global_Context& Editor_Global_Context::Get_Instance(void) {
		static Editor_Global_Context Instance{};

		return Instance;
	}

}// namespace NameSpace_Editor