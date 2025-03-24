#include "render_system/Render_System.h"

#include<memory>

#include "window/Window_System.h"

namespace NameSpace_Render::NameSpace_Render_System {

	using std::shared_ptr;

	using NameSpace_Window::Window_System;

	struct Render_System_Initialization_Info final{
		shared_ptr<Window_System> Window_System;
	};


	class Render_System final {
	private:
		Render_System(const Render_System&) = delete;
		Render_System& operator=(const Render_System&) = delete;

	};

}// namespace NameSpace_Render::NameSpace_Render_System