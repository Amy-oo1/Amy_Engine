#pragma once

#include<cstdint>
#include<vector>
#include<memory>

#include "math/Vector2.h"

namespace NameSpace_Editor {

	using std::shared_ptr;

	using NameSpace_Core::NameSpace_Math::Vector2;

	enum class EDITOR_COMMAND :uint32_t {
		CAMERA_LEFT = 1 << 0,		//A
		CAMERA_BACK = 1 << 1,		//S
		CAMERA_FORWAD = 1 << 2,		//w
		CAMERA_RIGHT = 1 << 3,		//D
		CAMERA_UP = 1 << 4,			//Q
		CAMERA_DOWN = 1 << 5,		//E
		TRANSLATION_MODE = 1 << 6,	//T
		ROTATION_MODE = 1 << 7,		//R
		SCALE_MODE = 1 << 8,		//C
		EXIT = 1 << 9,				//Esc
		DELETE_OBJECT = 1 << 10,	//Del

	};

	class Editor_Input_Manager final {
	private:
		Editor_Input_Manager(const Editor_Input_Manager&) = delete;
		Editor_Input_Manager(Editor_Input_Manager&&) = delete;

		Editor_Input_Manager& operator=(const Editor_Input_Manager&) = delete;
		Editor_Input_Manager& operator=(Editor_Input_Manager&&) = delete;

	public:
		Editor_Input_Manager(void) = default;

		~Editor_Input_Manager(void) = default;

	public:
		void On_Reset(void);
		void On_Key(int Key, int Scancode, int Action, int Mods);
		void On_Mouse_Button(int Button, int Action, int Mods);
		void On_Cursor_Pos(double X_Pos, double Y_Pos);
		void On_Cursor_Enter(int Entered);
		void On_Scroll(double X_Offset, double Y_Offset);
		void On_Window_Closed(void);


	public:
		bool Is_Cursor_In_Rect(Vector2 Pos, Vector2 Size) const;

		void Updata_Cursor_On_Axis(Vector2 Cursor, Vector2 Window_Pos, Vector2 Window_Size);


		void Register_Input(void);

	private:
		uint32_t m_Editor_Command{ 0 };

		Vector2 Window_Pos{ Vector2::ZERO };

		float   m_Mouse_X{ 0.0f };
		float   m_Mouse_Y{ 0.0f };
		float   m_Camera_Speed{ 0.05f };

		uint32_t m_Cursor_On_Axis{ 3 };

	};

}// namespace NameSpace_Editor