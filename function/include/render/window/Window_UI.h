#pragma once

#include<memory>

#include "render/window/Window_System.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Window {

	using std::shared_ptr;

	class Window_UI {
	private:
		Window_UI(const Window_UI&) = delete;
		Window_UI(Window_UI&&) = delete;

		Window_UI& operator=(const Window_UI&) = delete;
		Window_UI& operator=(Window_UI&&) = delete;
	public:
		Window_UI(void) = default;

		~Window_UI(void) = default;
	};

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Window