#include "default_editor/Editor_Input_Manager.h"

#include<utility>
#include<functional>

#include "GLFW/glfw3.h"

#include "logger/System_Logger.h"

#include "utilities/Cpp_Lib_Facility.h"

#include "render/render_system/Render_Camera.h"

#include "render/window/Window_System.h"

#include "global/Global_Systemer.h"
#include "global/Global_Config.h"

#include "default_editor/Editor_Scene_Manager.h"
#include "default_editor/Editor_Global_Context.h"

namespace NameSpace_Editor {

	using NameSpace_Core::NameSpace_Logger::System_Logger;

	using NameSpace_Function::Namespace_Global::Global_Systemer;

	using NameSpace_Function::NameSpace_Render::NameSpace_Window::Window_System;

	using NameSpace_Editor::Editor_Scene_Manage;

	void Editor_Input_Manager::On_Reset(void) {
		if (!NameSpace_Function::Namespace_Global::Is_Editor_Mode)
			return;
		//TODO : 
	}

	void Editor_Input_Manager::On_Key(int Key, int Scancode, int Action, int Mods) {
		if (!NameSpace_Function::Namespace_Global::Is_Editor_Mode)
			return;

		if (GLFW_PRESS == Action) {
			switch (Key) {
			case GLFW_KEY_A:this->m_Editor_Command |= to_underlying(EDITOR_COMMAND::CAMERA_LEFT);
				break;
			case GLFW_KEY_S:this->m_Editor_Command |= to_underlying(EDITOR_COMMAND::CAMERA_BACK);
				break;
			case GLFW_KEY_W:this->m_Editor_Command |= to_underlying(EDITOR_COMMAND::CAMERA_FORWAD);
				break;
			case GLFW_KEY_D:this->m_Editor_Command |= to_underlying(EDITOR_COMMAND::CAMERA_RIGHT);
				break;
			case GLFW_KEY_Q:this->m_Editor_Command |= to_underlying(EDITOR_COMMAND::CAMERA_UP);
				break;
			case GLFW_KEY_E:this->m_Editor_Command |= to_underlying(EDITOR_COMMAND::CAMERA_DOWN);
				break;
			case GLFW_KEY_T:this->m_Editor_Command |= to_underlying(EDITOR_COMMAND::TRANSLATION_MODE);
				break;
			case GLFW_KEY_R:this->m_Editor_Command |= to_underlying(EDITOR_COMMAND::ROTATION_MODE);
				break;
			case GLFW_KEY_C:this->m_Editor_Command |= to_underlying(EDITOR_COMMAND::SCALE_MODE);
				break;
			case GLFW_KEY_ESCAPE:this->m_Editor_Command |= to_underlying(EDITOR_COMMAND::EXIT);
				break;
			case GLFW_KEY_DELETE:this->m_Editor_Command |= to_underlying(EDITOR_COMMAND::DELETE_OBJECT);
				break;
			default:
				System_Logger::Get_Instance().Log(System_Logger::Level::info, "Unknown Key Pressed");
				break;
			}
		}
		else if (GLFW_RELEASE == Action) {
			switch (Key) {
			case GLFW_KEY_A:this->m_Editor_Command &= ~to_underlying(EDITOR_COMMAND::CAMERA_LEFT);
				break;
			case GLFW_KEY_S:this->m_Editor_Command &= ~to_underlying(EDITOR_COMMAND::CAMERA_BACK);
				break;
			case GLFW_KEY_W:this->m_Editor_Command &= ~to_underlying(EDITOR_COMMAND::CAMERA_FORWAD);
				break;
			case GLFW_KEY_D:this->m_Editor_Command &= ~to_underlying(EDITOR_COMMAND::CAMERA_RIGHT);
				break;
			case GLFW_KEY_Q:this->m_Editor_Command &= ~to_underlying(EDITOR_COMMAND::CAMERA_UP);
				break;
			case GLFW_KEY_E:this->m_Editor_Command &= ~to_underlying(EDITOR_COMMAND::CAMERA_DOWN);
				break;
			case GLFW_KEY_T:this->m_Editor_Command &= ~to_underlying(EDITOR_COMMAND::TRANSLATION_MODE);
				break;
			case GLFW_KEY_R:this->m_Editor_Command &= ~to_underlying(EDITOR_COMMAND::ROTATION_MODE);
				break;
			case GLFW_KEY_C:this->m_Editor_Command &= ~to_underlying(EDITOR_COMMAND::SCALE_MODE);
				break;
			case GLFW_KEY_ESCAPE:this->m_Editor_Command &= ~to_underlying(EDITOR_COMMAND::EXIT);
				break;
			case GLFW_KEY_DELETE:this->m_Editor_Command &= ~to_underlying(EDITOR_COMMAND::DELETE_OBJECT);
				break;
			default:
				System_Logger::Get_Instance().Log(System_Logger::Level::info, "Unknown Key Pressed");
				break;
			}
		}
	}

	void Editor_Input_Manager::On_Mouse_Button(int Button, int Action, int Mods) {
		//TODO : 
	}

	void Editor_Input_Manager::On_Cursor_Pos(double X_Pos, double Y_Pos) {
		if (!NameSpace_Function::Namespace_Global::Is_Editor_Mode)
			return;

		float Angular_Velocity{ 180.f / static_cast<float>(std::max(Editor_Global_Context::Get_Instance().m_Window_System->Get_Window_Width(),Editor_Global_Context::Get_Instance().m_Window_System->Get_Window_Height())) };

		if (this->m_Mouse_X >= 0.f && this->m_Mouse_Y >= 0.f) {

			if (Editor_Global_Context::Get_Instance().m_Window_System->Is_Mouse_Button_Down(GLFW_MOUSE_BUTTON_RIGHT)) {
				glfwSetInputMode(Editor_Global_Context::Get_Instance().m_Window_System->Get_Window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

				Editor_Global_Context::Get_Instance().m_Camera->Rotate(Vector2{ static_cast<float>(X_Pos - this->m_Mouse_X),static_cast<float>(Y_Pos - this->m_Mouse_Y) } *Angular_Velocity);
			}
			else if (Editor_Global_Context::Get_Instance().m_Window_System->Is_Mouse_Button_Down(GLFW_MOUSE_BUTTON_LEFT)) {

				Editor_Global_Context::Get_Instance().m_Scene_Manager->Move_Entity(
					static_cast<float>(X_Pos),
					static_cast<float>(Y_Pos),
					this->m_Mouse_X,
					this->m_Mouse_Y,
					Window_Pos,
					Vector2{static_cast<float>(Editor_Global_Context::Get_Instance().m_Window_System->Get_Window_Width()), static_cast<float>(Editor_Global_Context::Get_Instance().m_Window_System->Get_Window_Height())},
					this->m_Cursor_On_Axis
				);

				glfwSetInputMode(Editor_Global_Context::Get_Instance().m_Window_System->Get_Window(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			}
			else {
				glfwSetInputMode(Editor_Global_Context::Get_Instance().m_Window_System->Get_Window(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

				if (this->Is_Cursor_In_Rect(Window_Pos, Vector2{ static_cast<float>(Editor_Global_Context::Get_Instance().m_Window_System->Get_Window_Width()), static_cast<float>(Editor_Global_Context::Get_Instance().m_Window_System->Get_Window_Height()) })) {

					Vector2 Curosor{
						this->m_Mouse_X - static_cast<float>(Editor_Global_Context::Get_Instance().m_Window_System->Get_Window_Width()),
						this->m_Mouse_Y - static_cast<float>(Editor_Global_Context::Get_Instance().m_Window_System->Get_Window_Height())
					};

					//TODO :
				}

			}

		}
		//TODO : 

		this->m_Mouse_X = X_Pos;
		this->m_Mouse_Y = Y_Pos;
	}

	void Editor_Input_Manager::On_Cursor_Enter(int Entered) {
		if (Entered) {
			this->m_Mouse_X = 0.f;
			this->m_Mouse_Y = 0.f;
		}
		else {
			this->m_Mouse_X = -1.f;
			this->m_Mouse_Y = -1.f;
		}
		glfwSetInputMode(Editor_Global_Context::Get_Instance().m_Window_System->Get_Window(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	void Editor_Input_Manager::On_Scroll(double X_Offset, double Y_Offset) {
		if (!NameSpace_Function::Namespace_Global::Is_Editor_Mode)
			return;

		//TODO :Add In Window Rect 

		if (Editor_Global_Context::Get_Instance().m_Window_System->Is_Mouse_Button_Down(GLFW_MOUSE_BUTTON_RIGHT)) {
			if (0 < Y_Offset)
				this->m_Camera_Speed *= 1.2f;
			else if (0 > Y_Offset)
				this->m_Camera_Speed *= 0.8f;
		}
		else
			Editor_Global_Context::Get_Instance().m_Camera->Zoom(static_cast<float>(Y_Offset) * 2.f);
	}

	void Editor_Input_Manager::On_Window_Closed(void) {
		//TODO : 
	}

	bool Editor_Input_Manager::Is_Cursor_In_Rect(Vector2 Pos, Vector2 Size) const {
		if (this->m_Mouse_X >= Pos.Get_X() && this->m_Mouse_X <= Pos.Get_X() + Size.Get_X() &&
			this->m_Mouse_Y >= Pos.Get_Y() && this->m_Mouse_Y <= Pos.Get_Y() + Size.Get_Y())
			return true;
		else
			return false;
	}

	void Editor_Input_Manager::Updata_Cursor_On_Axis(Vector2 Cursor, Vector2 Window_Pos, Vector2 Window_Size) {
		//TODO : 
	}

	void Editor_Input_Manager::Register_Input(void) {
		auto Ref_Window{ Editor_Global_Context::Get_Instance().m_Window_System };

		Ref_Window->Register_On_Reset_Func(std::bind(&Editor_Input_Manager::On_Reset, this));
		Ref_Window->Register_On_Cursor_Pos_Func(std::bind(&Editor_Input_Manager::On_Cursor_Pos, this, std::placeholders::_1, std::placeholders::_2));
		Ref_Window->Register_On_Cursor_Enter_Func(std::bind(&Editor_Input_Manager::On_Cursor_Enter, this, std::placeholders::_1));
		Ref_Window->Register_On_Scroll_Func(std::bind(&Editor_Input_Manager::On_Scroll, this, std::placeholders::_1, std::placeholders::_2));
		Ref_Window->Register_On_Scroll_Func(std::bind(&Editor_Input_Manager::On_Scroll, this, std::placeholders::_1, std::placeholders::_2));
		Ref_Window->Register_On_Mouse_Button_Func(std::bind(&Editor_Input_Manager::On_Mouse_Button, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		Ref_Window->Register_On_Window_Close_Func(std::bind(&Editor_Input_Manager::On_Window_Closed, this));
		Ref_Window->Register_On_Key_Func(std::bind(&Editor_Input_Manager::On_Key, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	}

	void Editor_Input_Manager::Tick(float Delta_Time) {
		this->Process_Editor_Command();
	}

	void Editor_Input_Manager::Process_Editor_Command(void) const {
		float			camera_speed = this->m_Camera_Speed;
		auto			editor_camera{ Editor_Global_Context::Get_Instance().m_Camera };
		Quaternion		camera_rotate{ editor_camera->Get_Rotation().Inverse() };
		Vector3			camera_relative_pos{ 0, 0, 0 };

		if (to_underlying(EDITOR_COMMAND::CAMERA_FORWAD) & this->m_Editor_Command)
			camera_relative_pos += camera_rotate * Vector3{ 0, camera_speed, 0 };
		if (to_underlying(EDITOR_COMMAND::CAMERA_BACK) & this->m_Editor_Command)
			camera_relative_pos += camera_rotate * Vector3{ 0, -camera_speed, 0 };
		if (to_underlying(EDITOR_COMMAND::CAMERA_LEFT) & this->m_Editor_Command)
			camera_relative_pos += camera_rotate * Vector3{ -camera_speed, 0, 0 };
		if (to_underlying(EDITOR_COMMAND::CAMERA_RIGHT) & this->m_Editor_Command)
			camera_relative_pos += camera_rotate * Vector3{ camera_speed, 0, 0 };
		if (to_underlying(EDITOR_COMMAND::CAMERA_UP) & this->m_Editor_Command)
			camera_relative_pos += Vector3{ 0, 0, camera_speed };
		if (to_underlying(EDITOR_COMMAND::CAMERA_DOWN) & this->m_Editor_Command)
			camera_relative_pos += Vector3{ 0, 0, -camera_speed };
		if (to_underlying(EDITOR_COMMAND::DELETE_OBJECT) & this->m_Editor_Command)
			Editor_Global_Context::Get_Instance().m_Scene_Manager->On_Delete_Selected_Object();

		editor_camera->Move(camera_relative_pos);
	}

}// namespace NameSpace_Editor