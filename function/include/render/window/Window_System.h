#pragma once

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include<cstdint>
#include<limits>
#include<tuple>
#include<vector>
#include<string>
#include<functional>
#include<memory>
#include<exception>

#include "logger/System_Logger.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Window {

	using NameSpace_Core::NameSpace_Logger::System_Logger;

	using std::tuple;
	using std::vector;
	using std::string;
	using std::function;
	using std::unique_ptr;

	struct Window_System_Initialization_Info final {
		uint32_t Width{ 1280 };
		uint32_t Height{ 720 };
		bool Is_Full_Screen{ false };

		const char* Titile{ "Amy_Engine" };
	};

	class Window_System final {
	public:
		using On_Reset_Func = std::function<void(void)>;
		using On_Key_Func = std::function<void(int, int, int, int)>;
		using On_Char_Func = std::function<void(unsigned int)>;
		using On_CharMods_Func = std::function<void(unsigned int, int)>;
		using On_Mouse_Button_Func = std::function<void(int, int, int)>;
		using On_Cursor_Pos_Func = std::function<void(double, double)>;
		using On_Cursor_Enter_Func = std::function<void(int)>;
		using On_Scroll_Func = std::function<void(double, double)>;
		using On_Drop_Func = std::function<void(int, const char**)>;

	private:
		Window_System(void) = delete;

		Window_System(const Window_System&) = delete;
		Window_System& operator=(const Window_System&) = delete;

	public:
		Window_System(const Window_System_Initialization_Info& init_info);

		~Window_System() = default;

	public:
		GLFWwindow* Get_Window(void);

		void Poll_Window_Events(void);

		bool Is_WIndow_Shoule_Close(void);
		void ReSet_Window_Title(const string& Title);
		const tuple<uint32_t, uint32_t> Get_Window_Size(void) const;
		const uint32_t Get_Window_Width(void)const;
		const uint32_t Get_Window_Height(void)const;

		void Register_On_Reset_Func(const On_Reset_Func& Func);
		void Register_On_Key_Func(const On_Key_Func& Func);
		void Register_On_Char_Func(const On_Char_Func& Func);
		void Register_On_CharMods_Func(const On_CharMods_Func& Func);
		void Register_On_Mouse_Button_Func(const On_Mouse_Button_Func& Func);
		void Register_On_Cursor_Pos_Func(const On_Cursor_Pos_Func& Func);
		void Register_On_Cursor_Enter_Func(const On_Cursor_Enter_Func& Func);
		void Register_On_Scroll_Func(const On_Scroll_Func& Func);
		void Register_On_Drop_Func(const On_Drop_Func& Func);
		//TODO : Add Register 


	private:
		void On_Reset(void);
		void On_Key(int Key, int Scancode, int Action, int Mods);
		void On_Char(unsigned int CodePoint);
		void On_CharMods(unsigned int CodePoint, int Mods);
		void On_Mouse_Button(int Button, int Action, int Mods);
		void On_Cursor_Pos(double X_Pos, double Y_Pos);
		void On_Cursor_Enter(int Entered);
		void On_Scroll(double X_Offset, double Y_Offset);
		void On_Drop(int Count, const char** Paths);

	private:
		static void Initialize_GLWF(void);

		static void Reset_Call_Back(GLFWwindow* Window);
		static void Key_Call_Back(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods);
		static void Char_Call_Back(GLFWwindow* Window, unsigned int CodePoint);
		static void CharMods_Call_Back(GLFWwindow* Window, unsigned int CodePoint, int Mods);
		static void MouseButton_Call_Back(GLFWwindow* Window, int Button, int Action, int Mods);
		static void CursorPos_Call_Back(GLFWwindow* Window, double X_Pos, double Y_Pos);
		static void CursorEnter_Call_Back(GLFWwindow* Window, int Entered);
		static void Scroll_Call_Back(GLFWwindow* Window, double X_Offset, double Y_Offset);
		static void Drop_Call_Back(GLFWwindow* Window, int Count, const char** Paths);
		static void Window_Resize_Call_Back(GLFWwindow* Window, int Width, int Height);
		static void Window_Close_Call_Back(GLFWwindow* Window);

	private:
		static inline uint32_t s_Window_Count{ 0 };

		static constexpr uint32_t s_Max_Window_Count{ std::numeric_limits<uint32_t>::max() };

		static constexpr auto Delete_GLFW_Window = [](GLFWwindow* Window)
			{
				if (nullptr != Window) {
					glfwDestroyWindow(Window);
					if (0 == --s_Window_Count)
						glfwTerminate();
				}
				else
					System_Logger::Get_Instance().Log(System_Logger::Level::err, "Failed to create GLFW window");
			};

	private:
		unique_ptr<GLFWwindow, decltype(Delete_GLFW_Window)> m_Window{ nullptr,Window_System::Delete_GLFW_Window };
		uint32_t m_Width{ 0 };
		uint32_t m_Height{ 0 };
		bool m_Is_Full_Screen{ false };

		vector<On_Reset_Func> m_Reset_Call_Backs{};
		vector<On_Key_Func> m_Key_Call_Backs{};
		vector<On_Char_Func> m_Char_Call_Backs{};
		vector<On_CharMods_Func> m_CharMods_Call_Backs{};
		vector<On_Mouse_Button_Func> m_Mouse_Button_Call_Backs{};
		vector<On_Cursor_Pos_Func> m_Cursor_Pos_Call_Backs{};
		vector<On_Cursor_Enter_Func> m_Cursor_Enter_Call_Backs{};
		vector<On_Scroll_Func> m_Scroll_Call_Backs{};
		vector<On_Drop_Func> m_Drop_Call_Backs{};

	};

} // namespace NameSpace_Function::NameSpace_Render::NameSpace_Window