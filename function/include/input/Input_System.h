#pragma once

#include<cstdint>
#include<limits>
#include<memory>

#include "math/Radian.h"

#include "render/window/Window_System.h"

namespace NameSpace_Function::Namespace_Input {

	using std::shared_ptr;

	using NameSpace_Core::NameSpace_Math::Radian;

	using NameSpace_Render::NameSpace_Window::Window_System;

	enum class GAME_COMMAND : uint32_t {
		FORWARD = 1 << 0,// W
		BACKWARD = 1 << 1,// S
		LEFT = 1 << 2,// A
		RIGHT = 1 << 3,// D
		UP = 1 << 4,// SPACE
		DOWN = 1 << 5,//LEFT CONTROL
		SPRINT = 1 << 6,// LEFT SHIFT
		FIRE = 1 << 7,// F
		FREE_CAMERA = 1 << 8,// C
		INVAID = std::numeric_limits<uint32_t>::max()
	};

	class Input_System final {
	private:
		Input_System(const Input_System&) = delete;
		Input_System& operator=(const Input_System&) = delete;

	public:
		Input_System(shared_ptr<Window_System> Window);

		~Input_System(void) = default;

	public:
		void Re_Binding(shared_ptr<Window_System> Window);

	private:
		void On_Key(int Key, int Scancode, int Action, int Mods);

		void On_CUrsor_Pos(double X_Pos, double Y_Pos);

		void On_Key_Game_Mode(int Key, int Scancode, int Action, int Mods);

	private:
		shared_ptr<Window_System> m_Binding_Window{ nullptr };
		bool m_Is_Focus_Mode{ false };

		uint32_t m_Game_Commands{ 0 };
		Radian m_Cursor_Yaw{ 0.0f };
		Radian m_Cursor_Pitch{ 0.0f };

		uint32_t m_Cursor_Delta_X{ 0 };
		uint32_t m_Cursor_Delta_Y{ 0 };

		uint32_t m_Cursor_Last_X{ 0 };
		uint32_t m_Cursor_Last_Y{ 0 };

	};

}// namespace NameSpace_Function::Namespace_Input