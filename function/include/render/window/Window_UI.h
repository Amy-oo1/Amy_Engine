#pragma once

#include<memory>

#include "render/window/Window_System.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Window {

	using std::shared_ptr;

	class Window_UI {
		virtual void Init(void) = 0;
	};

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Window