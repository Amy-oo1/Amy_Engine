#include "input/Input_System.h"

#include<functional>

#include "logger/System_Logger.h"

#include "global/Global_Config.h"

//TODO input tounderying ,but it define in render/rhi/types.h

namespace NameSpace_Function::Namespace_Input {

	using NameSpace_Core::NameSpace_Logger::System_Logger;

	Input_System::Input_System(shared_ptr<Window_System> Window)
		:m_Window{ Window } {
		this->Re_Binding(Window);
	}

	void Input_System::Re_Binding(shared_ptr<Window_System> Window) {
		this->m_Window = Window;

		if (nullptr == Window)
			System_Logger::Get_Instance().Log(System_Logger::Level::critical, "Input System No Window");

		this->m_Window->Register_On_Key_Func(std::bind(&Input_System::On_Key, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));

		this->m_Window->Register_On_Cursor_Pos_Func(std::bind(&Input_System::On_CUrsor_Pos, this, std::placeholders::_1, std::placeholders::_2));
	}

	void Input_System::On_Key(int Key, int Scancode, int Action, int Mods)
	{
		if (false == Namespace_Global::Is_Editor_Mode)
			this->On_Key_Game_Mode(Key, Scancode, Action, Mods);
	}

	void Input_System::On_CUrsor_Pos(double X_Pos, double Y_Pos)
	{
		if (this->m_Is_Focus_Mode) {
			this->m_Cursor_Delta_X = this->m_Cursor_Last_X - X_Pos;
			this->m_Cursor_Delta_Y = this->m_Cursor_Last_Y - Y_Pos;
		}
		this->m_Cursor_Last_X = X_Pos;
		this->m_Cursor_Last_Y = Y_Pos;
	}

	void Input_System::On_Key_Game_Mode(int Key, int Scancode, int Action, int Mods) {
		//TODO :Add JUMP
		this->m_Game_Commands &= (std::numeric_limits<uint32_t>::max() ^ static_cast<uint32_t>(GAME_COMMAND::UP));

		if (GLFW_PRESS == Action) {
			switch (Key) {
			case GLFW_KEY_W:
				this->m_Game_Commands |= static_cast<uint32_t>(GAME_COMMAND::FORWARD);
				break;
			case GLFW_KEY_S:
				this->m_Game_Commands |= static_cast<uint32_t>(GAME_COMMAND::BACKWARD);
				break;
			case GLFW_KEY_A:
				this->m_Game_Commands |= static_cast<uint32_t>(GAME_COMMAND::LEFT);
				break;
			case GLFW_KEY_D:
				this->m_Game_Commands |= static_cast<uint32_t>(GAME_COMMAND::RIGHT);
				break;
			case GLFW_KEY_SPACE:
				//this->m_Game_Commands |= static_cast<uint32_t>(GAME_COMMAND::UP);
				break;
			case GLFW_KEY_LEFT_SHIFT:
				this->m_Game_Commands |= static_cast<uint32_t>(GAME_COMMAND::SPRINT);
				break;
			case  GLFW_KEY_LEFT_CONTROL:
				this->m_Game_Commands |= static_cast<uint32_t>(GAME_COMMAND::DOWN);
				break;
			case GLFW_KEY_F:
				this->m_Game_Commands |= static_cast<uint32_t>(GAME_COMMAND::FIRE);
				break;
			case GLFW_KEY_C:
				this->m_Game_Commands |= static_cast<uint32_t>(GAME_COMMAND::FREE_CAMERA);
				break;
			case GLFW_KEY_LEFT_ALT:
				this->m_Window->Set_Focus_Mode(this->m_Is_Focus_Mode = !this->m_Is_Focus_Mode);
				break;
			default:
				break;
			}
		}
		else if (GLFW_RELEASE == Action) {
			switch (Key) {
			case GLFW_KEY_W:
				this->m_Game_Commands &= (std::numeric_limits<uint32_t>::max() ^ static_cast<uint32_t>(GAME_COMMAND::FORWARD));
				break;
			case GLFW_KEY_S:
				this->m_Game_Commands &= (std::numeric_limits<uint32_t>::max() ^ static_cast<uint32_t>(GAME_COMMAND::BACKWARD));
				break;
			case GLFW_KEY_A:
				this->m_Game_Commands &= (std::numeric_limits<uint32_t>::max() ^ static_cast<uint32_t>(GAME_COMMAND::LEFT));
				break;
			case GLFW_KEY_D:
				this->m_Game_Commands &= (std::numeric_limits<uint32_t>::max() ^ static_cast<uint32_t>(GAME_COMMAND::RIGHT));
				break;
			case GLFW_KEY_SPACE:
				this->m_Game_Commands &= (std::numeric_limits<uint32_t>::max() ^ static_cast<uint32_t>(GAME_COMMAND::UP));
				break;
			case GLFW_KEY_LEFT_SHIFT:
				this->m_Game_Commands &= (std::numeric_limits<uint32_t>::max() ^ static_cast<uint32_t>(GAME_COMMAND::SPRINT));
				break;
			case  GLFW_KEY_LEFT_CONTROL:
				this->m_Game_Commands &= (std::numeric_limits<uint32_t>::max() ^ static_cast<uint32_t>(GAME_COMMAND::DOWN));
				break;
			case GLFW_KEY_F:
				this->m_Game_Commands &= (std::numeric_limits<uint32_t>::max() ^ static_cast<uint32_t>(GAME_COMMAND::FIRE));
				break;
			case GLFW_KEY_C:
				this->m_Game_Commands &= (std::numeric_limits<uint32_t>::max() ^ static_cast<uint32_t>(GAME_COMMAND::FREE_CAMERA));
				break;
			default:
				break;
			}
		}
	}

}// namespace NameSpace_Function::Namespace_Input
