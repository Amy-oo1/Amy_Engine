#include "render/render_system/Render_Camera.h"

#include "math/Degree.h"
#include "math/Radian.h"
#include "math/Utilities.h"

#include <algorithm>

namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System {

	using NameSpace_Core::NameSpace_Math::Degree;
	using NameSpace_Core::NameSpace_Math::Radian;

	using NameSpace_Core::NameSpace_Math::NameSpace_Utilities::Tan;
	using NameSpace_Core::NameSpace_Math::NameSpace_Utilities::Atan2;
	using NameSpace_Core::NameSpace_Math::NameSpace_Utilities::Atan;

	using NameSpace_Core::NameSpace_Math::NameSpace_Utilities::Make_Look_At;
	using NameSpace_Core::NameSpace_Math::NameSpace_Utilities::Make_Perspective_Matrix;

	void Render_Camera::Set_Current_Camera_Type(RENDER_CAMERA_TYPE Camera_Type) {
		std::lock_guard<std::mutex> Lock{ this->m_View_Matrix_Mutex };
		this->m_Camera_Type = Camera_Type;
	}

	void Render_Camera::Set_Main_View_Matrix(const Matrix4x4& View_Matrix, RENDER_CAMERA_TYPE Camera_Type) {
		std::lock_guard<std::mutex> Lock{ this->m_View_Matrix_Mutex };

		this->m_Camera_Type = Camera_Type;
		this->m_View_Matrices[Render_Camera::MAIN_VIEW_MATRIX_INDEX] = View_Matrix;

		Vector3 S{ View_Matrix[0][0],View_Matrix[0][1],View_Matrix[0][2] };
		Vector3 U{ View_Matrix[1][0],View_Matrix[1][1],View_Matrix[1][2] };
		Vector3 F{ View_Matrix[2][0],View_Matrix[2][1],View_Matrix[2][2] };

		this->m_Position = S * (-View_Matrix[0][3]) + U * (-View_Matrix[1][3]) + F * (-View_Matrix[2][3]);
	}

	void Render_Camera::Move(Vector3 Direction) {
		this->m_Position += Direction;
	}

	void Render_Camera::Rotate(Vector2 Delta) {
		Delta = Vector2{ Radian(Delta.Get_X()).Get_Radian(),Radian(Delta.Get_Y()).Get_Radian() };

		float Dot{ this->m_Up_Axis.Dot_Product(this->Forwad()) };

		if ((Dot < -0.99f && Delta.Get_X()>0.f) ||
			(Dot > 0.99f && Delta.Get_X() < 0.f))
			Delta.Set_X(0.f);

		Quaternion Pitch{ Quaternion::Generate_By_AxisAngle(Render_Camera::X,Radian(Delta.Get_X())) };
		Quaternion Yaw{ Quaternion::Generate_By_AxisAngle(Render_Camera::Y,Radian(Delta.Get_Y())) };

		this->m_Rotation = (Pitch * this->m_Rotation * Yaw).Normalize();
		this->m_Inv_Rotation = this->m_Rotation.Conjugation();
	}

	void Render_Camera::Zoom(float Offset) {
		this->m_FOV_X = std::clamp(this->m_FOV_X + Offset, Render_Camera::MIN_FLV, Render_Camera::MAX_FOV);
	}

	void Render_Camera::Look_At(const Vector3& Postion, const Vector3& Target, const Vector3& Up) {
		this->m_Position = Postion;
		Vector3 Forward = (Target - Postion).Normalize();

		this->m_Rotation = Quaternion::Get_Rotation_TO(Forward, Vector3::UNIT_Y);

		Vector3 Right = Forward.Cross_Product(Up.Normalize()).Normalize();
		Vector3 New_Up = Right.Cross_Product(Forward).Normalize();
		Quaternion Up_Rotation{ Quaternion::Get_Rotation_TO(this->m_Rotation * New_Up,Render_Camera::Z) };

		this->m_Rotation = Up_Rotation * this->m_Rotation;

		this->m_Inv_Rotation = this->m_Rotation.Conjugation();
	}

	void Render_Camera::Set_Z_Near(float Z_Near) {
		this->m_Z_Near = Z_Near;
	}

	void Render_Camera::Set_Z_Far(float Z_Far) {
		this->m_Z_Far = Z_Far;
	}

	void Render_Camera::Set_Aspect(const Vector2& Aspect) {
		this->m_Aspect = Aspect.Get_X() / Aspect.Get_Y();



		this->m_FOV_Y = Degree(Radian(Atan((Tan(Degree(this->m_FOV_X) * 0.5f) / this->m_Aspect) * 2.f))).Get_Degree();
	}

	void Render_Camera::Set_FOV_X(float FOV) {
		//TODO
	}

	const Vector3 Render_Camera::Get_Position(void) const {
		return this->m_Position;
	}

	const Quaternion Render_Camera::Get_Rotation(void) const {
		return this->m_Rotation;
	}

	const Vector3 Render_Camera::Get_Forward(void) const {
		return this->m_Inv_Rotation * Render_Camera::Z;
	}

	const Vector3 Render_Camera::Get_Up(void) const {
		return this->m_Inv_Rotation * Render_Camera::Y;
	}

	const Vector3 Render_Camera::Get_Right(void) const {
		return this->m_Inv_Rotation * Render_Camera::X;
	}

	const Vector2 Render_Camera::Get_FOV(void) const {
		return Vector2{ this->m_FOV_X,this->m_FOV_Y };
	}

	const Matrix4x4 Render_Camera::Get_View_Matrix(void) const {
		return this->m_View_Matrices[Render_Camera::MAIN_VIEW_MATRIX_INDEX];
	}

	const Matrix4x4 Render_Camera::Get_Projection_Matrix(void) const {
		Matrix4x4 fix_mat{ 1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };

		return fix_mat * Make_Perspective_Matrix(
			Radian(Degree(this->m_FOV_X)),
			this->m_Aspect,
			this->m_Z_Near,
			this->m_Z_Far
		);
	}

	const Matrix4x4 Render_Camera::Get_Look_At_Matrix(void) const {
		return Make_Look_At(
			this->m_Position,
			this->m_Position + this->Forwad(),
			this->Up()
		);
	}

	float Render_Camera::Get_FOV_Deprecated(void) const {
		return 0.f;// TODO
	}

	const Vector3 Render_Camera::Forwad(void) const {
		return this->m_Inv_Rotation * Render_Camera::Y;
	}

	const Vector3 Render_Camera::Up(void) const {
		return this->m_Inv_Rotation * Render_Camera::Z;
	}

	const Vector3 Render_Camera::Right(void) const {
		return this->m_Inv_Rotation * Render_Camera::X;
	}

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System