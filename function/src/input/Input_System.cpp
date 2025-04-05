#include "input/Input_System.h"

#include<functional>

#include "logger/System_Logger.h"

#include "global/Global_Config.h"
#include "global/Global_Systemer.h"

//TODO input tounderying ,but it define in render/rhi/types.h

namespace NameSpace_Function::Namespace_Input {

	using NameSpace_Core::NameSpace_Logger::System_Logger;

	using Namespace_Global::Global_Systemer;

	Input_System::Input_System(shared_ptr<Window_System> Window)
		:m_Binding_Window{ Window } {
		this->Re_Binding(Window);
	}

	void Input_System::Re_Binding(shared_ptr<Window_System> Window) {
		this->m_Binding_Window = Window;

		if (nullptr == Window)
			System_Logger::Get_Instance().Log(System_Logger::Level::critical, "Input System No Window");

		this->m_Binding_Window->Register_On_Key_Func(std::bind(&Input_System::On_Key, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));

		this->m_Binding_Window->Register_On_Cursor_Pos_Func(std::bind(&Input_System::On_CUrsor_Pos, this, std::placeholders::_1, std::placeholders::_2));
	}

	uint32_t Input_System::Get_Game_Command(void) const {
		return this->m_Game_Commands;
	}

	void Input_System::Calculate_Cursor_Delta_Angles(void) {
		const auto& [Width, Height] {Global_Systemer::Get_Instance().Main_Window->Get_Window_Size()};
		if (Width == 0 || Height == 0)
			return;

		const auto& FOV{ Global_Systemer::Get_Instance().Main_Render_System->Get_Render_Camera()->Get_FOV() };

		auto Cursor_Delta_X{ Radian{Degree{this->m_Cursor_Delta_X}}.Get_Radian() };
		auto Cursor_Delta_Y{ Radian{Degree{this->m_Cursor_Delta_Y}}.Get_Radian() };

		this->m_Cursor_Yaw = Cursor_Delta_X * (FOV.Get_X() / static_cast<float>(Width));
		this->m_Cursor_Pitch = Cursor_Delta_Y * (FOV.Get_Y() / static_cast<float>(Height));

	}

	void Input_System::Tick(void) {
		if (this->m_Is_Focus_Mode) {
			/*this->m_Cursor_Yaw += Radian(this->m_Cursor_Delta_X * 0.1f);
			this->m_Cursor_Pitch += Radian(this->m_Cursor_Delta_Y * 0.1f);*/

			this->Calculate_Cursor_Delta_Angles();

			this->m_Game_Commands &= (std::numeric_limits<uint32_t>::max() ^ static_cast<uint32_t>(GAME_COMMAND::INVAID));
		}
		else {
			this->m_Cursor_Yaw = Radian(0.0f);
			this->m_Cursor_Pitch = Radian(0.0f);

			this->m_Game_Commands |= static_cast<uint32_t>(GAME_COMMAND::INVAID);
		}

		this->m_Cursor_Delta_X = 0.0f;
		this->m_Cursor_Delta_Y = 0.0f;
	
		System_Logger::Get_Instance().Log(System_Logger::Level::info, "Input_System::Tick : Cursor Yaw : {}, Cursor Pitch : {}", this->m_Cursor_Yaw.Get_Radian(), this->m_Cursor_Pitch.Get_Radian());
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
				this->m_Binding_Window->Set_Focus_Mode(this->m_Is_Focus_Mode = !this->m_Is_Focus_Mode);
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
