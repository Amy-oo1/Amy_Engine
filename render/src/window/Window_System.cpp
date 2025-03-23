#include "window/Window_System.h"

#include<mutex>

namespace NameSpace_Render::NameSpace_Window {

	Window_System::Window_System(const Window_System_Initialization_Info& init_info) {
		static std::once_flag Initialized_GLWF_Flag{};

		std::call_once(Initialized_GLWF_Flag, Window_System::Initialize_GLWF);

		this->m_Window.reset(glfwCreateWindow(init_info.Width, init_info.Height, init_info.Titile, nullptr, nullptr));
		if (nullptr == this->m_Window)
			LOG_ERROR("Failed to create window");

		++Window_System::s_Window_Count;

		this->m_Width = init_info.Width;
		this->m_Height = init_info.Height;

		glfwSetInputMode(this->m_Window.get(), GLFW_STICKY_KEYS, GLFW_FALSE);
		glfwSetInputMode(this->m_Window.get(), GLFW_STICKY_MOUSE_BUTTONS, GLFW_FALSE);
		glfwSetInputMode(this->m_Window.get(), GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);

		//Set The Callback
		{
			//TODO : 
			glfwSetWindowUserPointer(this->m_Window.get(), this);
			glfwSetKeyCallback(this->m_Window.get(), Window_System::Key_Call_Back);
			glfwSetCharModsCallback(this->m_Window.get(), Window_System::CharMods_Call_Back);
			glfwSetCharCallback(this->m_Window.get(), Window_System::Char_Call_Back);
			glfwSetMouseButtonCallback(this->m_Window.get(), Window_System::MouseButton_Call_Back);
			glfwSetCursorPosCallback(this->m_Window.get(), Window_System::CursorPos_Call_Back);
			glfwSetCursorEnterCallback(this->m_Window.get(), Window_System::CursorEnter_Call_Back);
			glfwSetScrollCallback(this->m_Window.get(), Window_System::Scroll_Call_Back);
			glfwSetDropCallback(this->m_Window.get(), Window_System::Drop_Call_Back);
			glfwSetWindowSizeCallback(this->m_Window.get(), Window_System::Window_Resize_Call_Back);
			glfwSetWindowCloseCallback(this->m_Window.get(), Window_System::Window_Close_Call_Back);
		}
	}

	GLFWwindow* NameSpace_Window::Window_System::Get_Window(void) {
		return this->m_Window.get();
	}

	void Window_System::Poll_Window_Events(void) {
		glfwPollEvents();
	}

	bool Window_System::Is_WIndow_Shoule_Close(void) {
		return glfwWindowShouldClose(this->m_Window.get());
	}

	void Window_System::ReSet_Window_Title(const string& Title) {
		glfwSetWindowTitle(this->m_Window.get(), Title.c_str());
	}

	const tuple<uint32_t, uint32_t> Window_System::Get_Window_Size(void) const {
		return { this->m_Width,this->m_Height };
	}

	const uint32_t NameSpace_Window::Window_System::Get_Window_Width(void) const {
		return this->m_Width;
	}

	const uint32_t NameSpace_Window::Window_System::Get_Window_Height(void) const {
		return this->m_Height;
	}

	void NameSpace_Window::Window_System::Register_On_Reset_Func(const On_Reset_Func& Func) {
		this->m_Reset_Call_Backs.push_back(Func);
	}

	void Window_System::Register_On_Key_Func(const On_Key_Func& Func) {
		this->m_Key_Call_Backs.push_back(Func);
	}

	void Window_System::Register_On_Char_Func(const On_Char_Func& Func) {
		this->m_Char_Call_Backs.push_back(Func);
	}

	void Window_System::Register_On_CharMods_Func(const On_CharMods_Func& Func) {
		this->m_CharMods_Call_Backs.push_back(Func);
	}

	void Window_System::Register_On_Mouse_Button_Func(const On_Mouse_Button_Func& Func) {
		this->m_Mouse_Button_Call_Backs.push_back(Func);
	}

	void Window_System::Register_On_Cursor_Pos_Func(const On_Cursor_Pos_Func& Func) {
		this->m_Cursor_Pos_Call_Backs.push_back(Func);
	}

	void Window_System::Register_On_Cursor_Enter_Func(const On_Cursor_Enter_Func& Func) {
		this->m_Cursor_Enter_Call_Backs.push_back(Func);
	}

	void Window_System::Register_On_Scroll_Func(const On_Scroll_Func& Func) {
		this->m_Scroll_Call_Backs.push_back(Func);
	}

	void Window_System::Register_On_Drop_Func(const On_Drop_Func& Func) {
		this->m_Drop_Call_Backs.push_back(Func);
	}

	void NameSpace_Window::Window_System::On_Reset(void) {
		for (const auto& Func : this->m_Reset_Call_Backs)
			Func();
	}

	void Window_System::On_Key(int Key, int Scancode, int Action, int Mods) {
		for (const auto& Func : this->m_Key_Call_Backs)
			Func(Key, Scancode, Action, Mods);
	}

	void Window_System::On_Char(unsigned int CodePoint) {
		for (const auto& Func : this->m_Char_Call_Backs)
			Func(CodePoint);
	}

	void Window_System::On_CharMods(unsigned int CodePoint, int Mods) {
		for (const auto& Func : this->m_CharMods_Call_Backs)
			Func(CodePoint, Mods);
	}

	void Window_System::On_Mouse_Button(int Button, int Action, int Mods) {
		for (const auto& Func : this->m_Mouse_Button_Call_Backs)
			Func(Button, Action, Mods);
	}

	void Window_System::On_Cursor_Pos(double X_Pos, double Y_Pos) {
		for (const auto& Func : this->m_Cursor_Pos_Call_Backs)
			Func(X_Pos, Y_Pos);
	}

	void Window_System::On_Cursor_Enter(int Entered) {
		for (const auto& Func : this->m_Cursor_Enter_Call_Backs)
			Func(Entered);
	}

	void Window_System::On_Scroll(double X_Offset, double Y_Offset) {
		for (const auto& Func : this->m_Scroll_Call_Backs)
			Func(X_Offset, Y_Offset);
	}

	void Window_System::On_Drop(int Count, const char** Paths) {
		for (const auto& Func : this->m_Drop_Call_Backs)
			Func(Count, Paths);
	}

	void Window_System::Initialize_GLWF(void) {
		if (GLFW_FALSE == glfwInit())
			LOG_ERROR("Failed to initialize GLFW");

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	}

	void NameSpace_Window::Window_System::Reset_Call_Back(GLFWwindow* Window) {
		const auto& App{ static_cast<Window_System*>(glfwGetWindowUserPointer(Window)) };
		if (nullptr == App)
			LOG_ERROR("App is nullptr");

		App->On_Reset();
	}

	void Window_System::Key_Call_Back(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods) {
		const auto& App{ static_cast<Window_System*>(glfwGetWindowUserPointer(Window)) };
		if (nullptr == App)
			LOG_ERROR("App is nullptr");

		App->On_Key(Key, Scancode, Action, Mods);
	}

	void Window_System::Char_Call_Back(GLFWwindow* Window, unsigned int CodePoint) {
		const auto& App{ static_cast<Window_System*>(glfwGetWindowUserPointer(Window)) };
		if (nullptr == App)
			LOG_ERROR("App is nullptr");

		App->On_Char(CodePoint);
	}

	void Window_System::CharMods_Call_Back(GLFWwindow* Window, unsigned int CodePoint, int Mods) {
		const auto& App{ static_cast<Window_System*>(glfwGetWindowUserPointer(Window)) };
		if (nullptr == App)
			LOG_ERROR("App is nullptr");

		App->On_CharMods(CodePoint, Mods);
	}

	void Window_System::MouseButton_Call_Back(GLFWwindow* Window, int Button, int Action, int Mods) {
		const auto& App{ static_cast<Window_System*>(glfwGetWindowUserPointer(Window)) };
		if (nullptr == App)
			LOG_ERROR("App is nullptr");

		App->On_Mouse_Button(Button, Action, Mods);
	}

	void Window_System::CursorPos_Call_Back(GLFWwindow* Window, double X_Pos, double Y_Pos) {
		const auto& App{ static_cast<Window_System*>(glfwGetWindowUserPointer(Window)) };
		if (nullptr == App)
			LOG_ERROR("App is nullptr");

		App->On_Cursor_Pos(X_Pos, Y_Pos);
	}

	void Window_System::CursorEnter_Call_Back(GLFWwindow* Window, int Entered) {
		const auto& App{ static_cast<Window_System*>(glfwGetWindowUserPointer(Window)) };
		if (nullptr == App)
			LOG_ERROR("App is nullptr");

		App->On_Cursor_Enter(Entered);
	}

	void Window_System::Scroll_Call_Back(GLFWwindow* Window, double X_Offset, double Y_Offset) {
		const auto& App{ static_cast<Window_System*>(glfwGetWindowUserPointer(Window)) };
		if (nullptr == App)
			LOG_ERROR("App is nullptr");

		App->On_Scroll(X_Offset, Y_Offset);
	}

	void Window_System::Drop_Call_Back(GLFWwindow* Window, int Count, const char** Paths) {
		const auto& App{ static_cast<Window_System*>(glfwGetWindowUserPointer(Window)) };
		if (nullptr == App)
			LOG_ERROR("App is nullptr");

		App->On_Drop(Count, Paths);
	}

	void Window_System::Window_Resize_Call_Back(GLFWwindow* Window, int Width, int Height) {
		const auto& App{ static_cast<Window_System*>(glfwGetWindowUserPointer(Window)) };
		if (nullptr == App) {
			LOG_ERROR("App is nullptr");
			throw std::runtime_error("App is nullptr");
		}


		App->m_Width = static_cast<uint32_t>(Width);
		App->m_Height = static_cast<uint32_t>(Height);
	}

	void Window_System::Window_Close_Call_Back(GLFWwindow* Window) {
		glfwSetWindowShouldClose(Window, GLFW_TRUE);
	}

} // namespace NameSpace_Window