#include "default_editor/Editor_Scene_Manager.h"

#include "file/File_System.h"

#include "math/Degree.h"
#include "math/Radian.h"

#include "logger/System_Logger.h"
#include "transform/Affine_Transform.h"

#include "frame/components/transform/Transform_Component.h"
#include "render/render_system/Render_Obejct.h"
#include "render/render_system/Render_Swap_Context.h"

#include "render/render_system/Render_Data_Struct.h"

#include "global/Global_Systemer.h"

#include "default_editor/Editor_Global_Context.h"

namespace NameSpace_Editor {

	using NameSpace_Platform::NameSpace_File::path;

	using NameSpace_Core::NameSpace_Logger::System_Logger;
	using NameSpace_Core::NameSpace_Math::Degree;
	using NameSpace_Core::NameSpace_Math::Radian;
	using NameSpace_Core::NameSpace_Transform::Affine_Transform;

	using NameSpace_Function::NameSpace_Frame::NameSpace_Components::NameSpace_Transform::Transform_Component;

	using NameSpace_Function::NameSpace_Render::NameSpace_Render_System::Game_Object_Part_ID;
	using NameSpace_Function::NameSpace_Render::NameSpace_Render_System::Mesh_Source_Desc;
	using NameSpace_Function::NameSpace_Render::NameSpace_Render_System::Render_Swap_Context;
	using NameSpace_Function::NameSpace_Render::NameSpace_Render_System::Game_Object_Desc;

	using NameSpace_Function::Namespace_Global::Global_Systemer;

	void Editor_Scene_Manage::UpData_Axis_Resource(void) {
		auto Instance_Id_Allocator{ Editor_Global_Context::Get_Instance().m_Render_System->Get_Instance_ID_Allocator() };
		auto Mesh_Resource_Id_Allocator{ Editor_Global_Context::Get_Instance().m_Render_System->Get_Mesh_Resource_ID_Allocator() };
		//auto Material_Resource_Id_Allocator{ Editor_Global_Context::Get_Instance().m_Render_System->Get_Material_Resource_ID_Allocator() };

		{
			Game_Object_Part_ID Axis_Instance_Id{ 0xFFAA, 0xFFAA };
			Mesh_Source_Desc Mesh_URL_Desc{ path{"%%Translation_Axis%%"} };

			this->m_Translation_Axis.Instance_ID = Instance_Id_Allocator->Allocate_GUID(Axis_Instance_Id);
			this->m_Translation_Axis.Mesh_Resource_ID = Mesh_Resource_Id_Allocator->Allocate_GUID(Mesh_URL_Desc);
		}

		{
			Game_Object_Part_ID Axis_Instance_Id{ 0xFFBB, 0xFFBB };
			Mesh_Source_Desc Mesh_URL_Desc{ path{"%%Rotation_Axis%%"} };
			this->m_Rotation_Axis.Instance_ID = Instance_Id_Allocator->Allocate_GUID(Axis_Instance_Id);
			this->m_Rotation_Axis.Mesh_Resource_ID = Mesh_Resource_Id_Allocator->Allocate_GUID(Mesh_URL_Desc);
		}

		{
			Game_Object_Part_ID Axis_Instance_Id{ 0xFFCC, 0xFFCC };
			Mesh_Source_Desc Mesh_URL_Desc{ path{"%%Scale_Axis%%"} };
			this->m_Scale_Axis.Instance_ID = Instance_Id_Allocator->Allocate_GUID(Axis_Instance_Id);
			this->m_Scale_Axis.Mesh_Resource_ID = Mesh_Resource_Id_Allocator->Allocate_GUID(Mesh_URL_Desc);
		}

		Editor_Global_Context::Get_Instance().m_Render_System->Create_Axis(
			&this->m_Translation_Axis,
			&this->m_Rotation_Axis,
			&this->m_Scale_Axis
		);

	}

	void Editor_Scene_Manage::Tick(float Delta_Time) const {
		auto Selected_Object{ this->Get_Selected_Object().lock() };
		if (Selected_Object) {
			shared_ptr<Transform_Component> Component{ Selected_Object->TryGet_Component<Transform_Component>(string{ "TransformComponent" }) };

			if (Component)
				Component->Set_Dirty_Flag(true);
		}
	}

	weak_ptr<GObject> Editor_Scene_Manage::Get_Selected_Object(void) const {
		if (GObject_ID_Allocator::INVALID_GOBJECT_ID != this->m_Selected_Object_ID) {
			auto Level{ Global_Systemer::Get_Instance().World_Manager.Get_Current_Active_Level().lock() };
			if (Level)
				return  Level->Get_Object(this->m_Selected_Object_ID);
			else
				System_Logger::Get_Instance().Log(System_Logger::Level::err, "Editor_Scene_Manage::Get_Selected_Object", "Level is not found");
		}
		else
			return weak_ptr<GObject>{};
	}

	void Editor_Scene_Manage::Move_Entity(float New_Mouse_Pos_X, float New_Mouse_Pos_Y, float Last_Mouse_Pos_X, float Last_Mouse_Pos_Y, Vector2 Window_Pos, Vector2 Window_Size, size_t Cursor_On_Axis) {
		Matrix4x4 Model_Matrix = this->m_Selected_Object_Transform;

		float Angular_Velocity{ 180.f / static_cast<float>(std::max(Window_Size.Get_X(), Window_Size.Get_Y())) };

		Vector2 Delta_Mouse_Move_UV{ New_Mouse_Pos_X - Last_Mouse_Pos_X,New_Mouse_Pos_Y - Last_Mouse_Pos_Y };

		Vector3 Model_Translate{};
		Quaternion Model_Rotaion{};
		Vector3 Model_Scale{};
		Model_Matrix.Decom_Position(&Model_Translate, &Model_Rotaion, &Model_Scale);

		Matrix4x4
			Axis_Modle_Matrix{ Matrix4x4::Generate_Translate(Model_Translate) },
			View_Matrix{ Editor_Global_Context::Get_Instance().m_Camera->Get_Look_At_Matrix() },
			Proj_Matrix{ Editor_Global_Context::Get_Instance().m_Camera->Get_Projection_Matrix() };

		Vector4 Model_Origin_Clip_Position{ Proj_Matrix * View_Matrix * Vector4{Model_Translate,1.f} };
		Model_Origin_Clip_Position /= Model_Origin_Clip_Position.Get_W();

		Vector2 Model_Origin_Clip_UV{ (Model_Origin_Clip_Position.Get_X() + 1) * 0.5f,(Model_Origin_Clip_Position.Get_Y() + 1) * 0.5f };

		Vector4 Axis_X_Local_Position_4{ 1.f,0.f,0.f,1.f };
		if (EDITOR_AXIS_MODE::SCALE == this->m_Editor_Axis_Mode)
			Axis_X_Local_Position_4 = Model_Rotaion.Get_Rotation_Matrix4x4() * Axis_X_Local_Position_4;

		Vector4 Axis_X_World_Position_4{ Axis_Modle_Matrix * Axis_X_Local_Position_4 };
		Axis_X_World_Position_4.Set_W(1.f);

		Vector4 Axis_X_Clip_Position{ Proj_Matrix * View_Matrix * Axis_X_World_Position_4 };
		Axis_X_Clip_Position /= Axis_X_Clip_Position.Get_W();
		Vector2 Axis_X_Clip_UV{ (Axis_X_Clip_Position.Get_X() + 1) * 0.5f,(Axis_X_Clip_Position.Get_Y() + 1) * 0.5f };
		Vector2 Axis_X_Clip_Direction_UV{ Axis_X_Clip_UV - Model_Origin_Clip_UV };
		Axis_X_Clip_Direction_UV.To_Normalized();

		Vector4 Axis_Y_Local_Position_4{ 0.f,1.f,0.f,1.f };
		if (EDITOR_AXIS_MODE::SCALE == this->m_Editor_Axis_Mode)
			Axis_Y_Local_Position_4 = Model_Rotaion.Get_Rotation_Matrix4x4() * Axis_Y_Local_Position_4;

		Vector4 Axis_Y_World_Position_4{ Axis_Modle_Matrix * Axis_Y_Local_Position_4 };
		Axis_Y_World_Position_4.Set_W(1.f);

		Vector4 Axis_Y_Clip_Position{ Proj_Matrix * View_Matrix * Axis_Y_World_Position_4 };
		Axis_Y_Clip_Position /= Axis_Y_Clip_Position.Get_W();
		Vector2 Axis_Y_Clip_UV{ (Axis_Y_Clip_Position.Get_X() + 1) * 0.5f,(Axis_Y_Clip_Position.Get_Y() + 1) * 0.5f };
		Vector2 Axis_Y_Clip_Direction_UV{ Axis_Y_Clip_UV - Model_Origin_Clip_UV };
		Axis_Y_Clip_Direction_UV.To_Normalized();


		Vector4 Axis_Z_Local_Position_4{ 0.f,0.f,1.f,1.f };
		if (EDITOR_AXIS_MODE::SCALE == this->m_Editor_Axis_Mode)
			Axis_Z_Local_Position_4 = Model_Rotaion.Get_Rotation_Matrix4x4() * Axis_Z_Local_Position_4;

		Vector4 Axis_Z_World_Position_4{ Axis_Modle_Matrix * Axis_Z_Local_Position_4 };
		Axis_Z_World_Position_4.Set_W(1.f);

		Vector4 Axis_Z_Clip_Position{ Proj_Matrix * View_Matrix * Axis_Z_World_Position_4 };
		Axis_Z_Clip_Position /= Axis_Z_Clip_Position.Get_W();
		Vector2 Axis_Z_Clip_UV{ (Axis_Z_Clip_Position.Get_X() + 1) * 0.5f,(Axis_Z_Clip_Position.Get_Y() + 1) * 0.5f };
		Vector2 Axis_Z_Clip_Direction_UV{ Axis_Z_Clip_UV - Model_Origin_Clip_UV };
		Axis_Z_Clip_Direction_UV.To_Normalized();

		Matrix4x4 New_Model_Matrix{ Matrix4x4::IDENTITY };
		if (EDITOR_AXIS_MODE::TRANSLATE == this->m_Editor_Axis_Mode) {
			Vector3 Move_Vector{ Vector3::ZERO };
			if (0 == Cursor_On_Axis)
				Move_Vector.Set_X(Delta_Mouse_Move_UV.Dot_Product(Axis_X_Clip_Direction_UV) * Angular_Velocity);
			else if (1 == Cursor_On_Axis)
				Move_Vector.Set_Y(Delta_Mouse_Move_UV.Dot_Product(Axis_Y_Clip_Direction_UV) * Angular_Velocity);
			else if (2 == Cursor_On_Axis)
				Move_Vector.Set_Z(Delta_Mouse_Move_UV.Dot_Product(Axis_Z_Clip_Direction_UV) * Angular_Velocity);
			else
				System_Logger::Get_Instance().Log(System_Logger::Level::err, " Unknown Axis");


			Matrix4x4 Translate_Mat{ Affine_Transform(Vector3::ONE,Quaternion::IDENTITY,Move_Vector) };
			New_Model_Matrix = Axis_Modle_Matrix * Translate_Mat;

			New_Model_Matrix = New_Model_Matrix * Model_Rotaion.Get_Rotation_Matrix4x4();
			New_Model_Matrix = New_Model_Matrix * Matrix4x4::Generate_Sacle(Model_Scale);

			Vector3 New_Translate{};
			Quaternion New_Rotation{};
			Vector3 New_Sacle{};
			New_Model_Matrix.Decom_Position(&New_Translate, &New_Rotation, &New_Sacle);

			Matrix4x4 Translate_Matrix{ Matrix4x4::Generate_Translate(New_Translate) };
			Matrix4x4 Scale_Matrix{ Matrix4x4::Generate_Sacle(New_Sacle) };
			Matrix4x4 Axis_Model_Matrix{ Translate_Matrix * Scale_Matrix };

			this->m_Translation_Axis.Model_Matrix = Axis_Model_Matrix;
			this->m_Rotation_Axis.Model_Matrix = Axis_Model_Matrix;
			this->m_Scale_Axis.Model_Matrix = Axis_Model_Matrix;

			Editor_Global_Context::Get_Instance().m_Render_System->Set_Visable_Axis(this->m_Translation_Axis);
		}
		else if (EDITOR_AXIS_MODE::ROTATE == this->m_Editor_Axis_Mode) {
			float Last_Mouse_U{ (Last_Mouse_Pos_X - Window_Pos.Get_X()) / Window_Size.Get_X() };
			float Last_Mouse_V{ (Last_Mouse_Pos_Y - Window_Pos.Get_Y()) / Window_Size.Get_Y() };
			float New_Mouse_U{ (New_Mouse_Pos_X - Window_Pos.Get_X()) / Window_Size.Get_X() };
			float New_Mouse_V{ (New_Mouse_Pos_Y - Window_Pos.Get_Y()) / Window_Size.Get_Y() };
			Vector2 Last_Mouse_UV{ Last_Mouse_U - Model_Origin_Clip_UV.Get_X(),Last_Mouse_V - Model_Origin_Clip_UV.Get_Y() };
			Vector2 New_Mouse_UV{ New_Mouse_U - Model_Origin_Clip_UV.Get_X(),New_Mouse_V - Model_Origin_Clip_UV.Get_Y() };

			float Move_Radian{};
			Vector3 Axis_Of_Radian{ Vector3::ZERO };
			if (0 == Cursor_On_Axis) {
				Move_Radian = (Delta_Mouse_Move_UV * Angular_Velocity).Length();
				if (Editor_Global_Context::Get_Instance().m_Camera->Get_Forward().Dot_Product(Vector3::UNIT_X) < 0)
					Move_Radian = -Move_Radian;
				Axis_Of_Radian.Set_X(1.f);
			}
			else if (1 == Cursor_On_Axis) {
				Move_Radian = (Delta_Mouse_Move_UV * Angular_Velocity).Length();
				if (Editor_Global_Context::Get_Instance().m_Camera->Get_Forward().Dot_Product(Vector3::UNIT_X) < 0)
					Move_Radian = -Move_Radian;
				Axis_Of_Radian.Set_Y(1.f);
			}
			else if (2 == Cursor_On_Axis) {
				Move_Radian = (Delta_Mouse_Move_UV * Angular_Velocity).Length();
				if (Editor_Global_Context::Get_Instance().m_Camera->Get_Forward().Dot_Product(Vector3::UNIT_X) < 0)
					Move_Radian = -Move_Radian;
				Axis_Of_Radian.Set_Z(1.f);
			}
			else
				System_Logger::Get_Instance().Log(System_Logger::Level::err, " Unknown Axis");

			if (Last_Mouse_UV.Distance(New_Mouse_UV) < 0.f)
				Move_Radian -= Move_Radian;

			Quaternion Move_Ret{ Quaternion::Generate_By_AxisAngle(Axis_Of_Radian,Radian{Move_Radian}) };

			New_Model_Matrix = Axis_Modle_Matrix * Move_Ret.Get_Rotation_Matrix4x4();
			New_Model_Matrix = New_Model_Matrix * Model_Rotaion.Get_Rotation_Matrix4x4();
			New_Model_Matrix = New_Model_Matrix * Matrix4x4::Generate_Sacle(Model_Scale);
			Vector3 New_Translate{};
			Quaternion New_Rotation{};
			Vector3 New_Sacle{};
			New_Model_Matrix.Decom_Position(&New_Translate, &New_Rotation, &New_Sacle);

			Matrix4x4 Translate_Matrix{ Matrix4x4::Generate_Translate(New_Translate) };
			Matrix4x4 Scale_Matrix{ Matrix4x4::Generate_Sacle(New_Sacle) };
			Matrix4x4 Axis_Model_Matrix{ Translate_Matrix * Scale_Matrix };

			this->m_Translation_Axis.Model_Matrix = Axis_Model_Matrix;
			this->m_Rotation_Axis.Model_Matrix = Axis_Model_Matrix;
			this->m_Scale_Axis.Model_Matrix = Axis_Model_Matrix;



		}
		else {
			//TODO :
		}

		this->m_Selected_Object_Transform = New_Model_Matrix;
	}

	void Editor_Scene_Manage::On_GObject_Selected(GObject_ID Selected_Object_ID) {

		if (this->m_Selected_Object_ID == Selected_Object_ID)
			System_Logger::Get_Instance().Log(System_Logger::Level::info, "Editor_Scene_Manage::On_GObject_Selected", "Selected Object ID is same");
		else if (GObject_ID_Allocator::INVALID_GOBJECT_ID == Selected_Object_ID) {
			this->m_Selected_Object_ID = Selected_Object_ID;

			System_Logger::Get_Instance().Log(System_Logger::Level::err, "Editor_Scene_Manage::On_GObject_Selected", "Selected Object ID is invalid");
			return;
		}
		else if (GObject_ID_Allocator::INVALID_GOBJECT_ID != this->m_Selected_Object_ID) {
			this->m_Selected_Object_ID = Selected_Object_ID;

			auto Last_Selected_Object{ this->Get_Selected_Object().lock() };
			if (Last_Selected_Object) {
				auto Trans{ Last_Selected_Object->TryGet_Component<Transform_Component>(string{ "TransformComponent" }) };
				if (Trans)
					System_Logger::Get_Instance().Log(System_Logger::Level::info, "TUDO");
				else
					System_Logger::Get_Instance().Log(System_Logger::Level::err, "Editor_Scene_Manage::On_GObject_Selected", "Transform Component is not found");
			}
		}
	}

	void Editor_Scene_Manage::On_Delete_Selected_Object(void) {
		auto Selected_Object{ this->Get_Selected_Object().lock() };

		if (nullptr != Selected_Object) {
			auto Level{ Global_Systemer::Get_Instance().World_Manager.Get_Current_Active_Level().lock() };

			if (nullptr != Level) {
				Level->Delete_Object(this->m_Selected_Object_ID);

				auto& Swap_Conotext{ *Editor_Global_Context::Get_Instance().m_Render_System->Get_Render_Swap_Context() };
				Swap_Conotext.Get_SwapData(Render_Swap_Context::SWAPDATA_TYPE::SWAPDATA_TYPE_LOGIC).Add_Delete_Game_Object(Game_Object_Desc{ Selected_Object->Get_ID(),{} });
			}
			else
				System_Logger::Get_Instance().Log(System_Logger::Level::err, "Editor_Input_Manager::On_Delete_Selected_Object", "Level is not found");
		}
		else {
			System_Logger::Get_Instance().Log(System_Logger::Level::info, "No Object Selected");
		}

		this->On_GObject_Selected(GObject_ID_Allocator::INVALID_GOBJECT_ID);
	}


}// namespace NameSpace_Editor