#pragma once

#include<string>
#include<unordered_set>
#include<memory>

#include "default_editor/Editor_Scene_Manager.h"
#include "default_editor/Editor_Input_Manager.h"

#include "render/window/Window_UI.h"

#include "Engine.h"

namespace NameSpace_Editor {

	using std::string;
	using std::unordered_set;
	//using std::shared_ptr;
	using std::unique_ptr;

	using NameSpace_Function::NameSpace_Render::NameSpace_Window::Window_UI;
	using NameSpace_Function::Amy_Engine;

	class Amy_Editor final {
		friend class Editor;
	private:
		Amy_Editor(void) = delete;

		Amy_Editor(const Amy_Editor&) = delete;
		Amy_Editor(Amy_Editor&&) = delete;

		Amy_Editor& operator=(const Amy_Editor&) = delete;
		Amy_Editor& operator=(Amy_Editor&&) = delete;

	public:
		Amy_Editor(unique_ptr<Amy_Engine>&& Engine);

		~Amy_Editor(void);


	public:
		void Register_Editor_Tick_Component(const string& Name);

	public:
		unordered_set<string> m_Editor_Tick_Component_Type{};

	private:
		unique_ptr<Amy_Engine> m_Engine{ nullptr };
		shared_ptr<Window_UI> m_Editor_UI{ nullptr };

	};

}// namespace NameSpace_Editor