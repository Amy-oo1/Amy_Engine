#pragma once

#include<cstdint>
#include<memory>

#include "math/Vector2.h"
#include "math/Vector3.h"
#include "math/Vector4.h"
#include "math/Quaternion.h"
#include "math/Matrix4x4.h"

#include "frame/object/GObject.h"
#include "frame/object/GObject_ID_Allocator.h"
#include "render/render_system/Render_Data_Struct.h"
#include "render/render_system/Render_Camera.h"

#include "default_editor/Editor_Axis.h"

namespace NameSpace_Editor {

	using std::shared_ptr;

	using NameSpace_Core::NameSpace_Math::Vector2;
	using NameSpace_Core::NameSpace_Math::Vector3;
	using NameSpace_Core::NameSpace_Math::Vector4;
	using NameSpace_Core::NameSpace_Math::Quaternion;
	using NameSpace_Core::NameSpace_Math::Matrix4x4;


	using NameSpace_Function::NameSpace_Frame::NameSpace_GObject::GObject;
	using NameSpace_Function::NameSpace_Frame::NameSpace_GObject::GObject_ID;
	using NameSpace_Function::NameSpace_Frame::NameSpace_GObject::GObject_ID_Allocator;
	using NameSpace_Function::NameSpace_Render::NameSpace_Render_System::Render_Entity;
	using NameSpace_Function::NameSpace_Render::NameSpace_Render_System::Render_Camera;

	enum class EDITOR_AXIS_MODE :uint32_t {
		TRANSLATE = 0,
		ROTATE,
		SCALE,
		DEFAULT
	};

	class Editor_Scene_Manage final {
	private:
		Editor_Scene_Manage(const Editor_Scene_Manage&) = delete;
		Editor_Scene_Manage& operator=(const Editor_Scene_Manage&) = delete;

	public:
		Editor_Scene_Manage(void) = default;

		~Editor_Scene_Manage(void) = default;


	public:

		void UpData_Axis_Resource(void);


	public:


		void Move_Entity(
			float New_Mouse_Pos_X,
			float New_Mouse_Pos_Y,
			float Last__Mouse_Pos_X,
			float Last_Mouse_Pos_Y,
			Vector2 Window_Pos,
			Vector2 Window_Size,
			size_t Cursor_On_Axis
		);

	private:
		Editor_Translation_Axis m_Translation_Axis{};
		Editor_Rotation_Axis m_Rotation_Axis{};
		Editor_Scale_Axis m_Scale_Axis{};

		GObject_ID m_Selected_Object_ID{ GObject_ID_Allocator::INVALID_GOBJECT_ID };
		Matrix4x4 m_Selected_Object_Transform{ Matrix4x4::IDENTITY };

		EDITOR_AXIS_MODE m_Editor_Axis_Mode{ EDITOR_AXIS_MODE::TRANSLATE };

		uint32_t m_Selected_Axis{ 3 };

		bool m_Is_Shouw_Axis{ true };

	};


}// namespace NameSpace_Editor