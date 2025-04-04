#pragma once

#include<memory>

#include "render/window/Window_System.h"
#include "render/render_system/Render_Camera.h"
#include "render/render_system/Render_System.h"
//#include "Engine.h"

#include "default_editor/Editor_Scene_Manager.h"
#include "default_editor/Editor_Input_Manager.h"

namespace NameSpace_Editor {

	using std::unique_ptr;
	using std::shared_ptr;

	using NameSpace_Function::NameSpace_Render::NameSpace_Window::Window_System;
	using NameSpace_Function::NameSpace_Render::NameSpace_Render_System::Render_Camera;
	using NameSpace_Function::NameSpace_Render::NameSpace_Render_System::Render_System;
	//using NameSpace_Function::Amy_Engine;


	class Editor_Global_Context final {
	private:
		Editor_Global_Context(const Editor_Global_Context&) = delete;
		Editor_Global_Context(Editor_Global_Context&&) = delete;

		Editor_Global_Context& operator=(const Editor_Global_Context&) = delete;
		Editor_Global_Context& operator=(Editor_Global_Context&&) = delete;

		Editor_Global_Context(void);

	public:
		~Editor_Global_Context(void) = default;

		static Editor_Global_Context& Get_Instance(void);

		shared_ptr<Window_System> m_Window_System{ nullptr };
		shared_ptr<Render_System> m_Render_System{ nullptr };
		shared_ptr<Render_Camera> m_Camera{ nullptr };

		shared_ptr<Editor_Scene_Manage> m_Scene_Manager{ nullptr };
		shared_ptr<Editor_Input_Manager> m_Input_Manager{ nullptr };

	};

}// namespace NameSpace_Editor