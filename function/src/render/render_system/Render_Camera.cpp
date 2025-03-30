#include "render/render_system/Render_Camera.h"

#include <algorithm>

namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System {

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
		//TODO: Implement this function
	}

	void Render_Camera::Zoom(float Offset) {
		this->m_FOV_X = std::clamp(this->m_FOV_X + Offset, Render_Camera::MIN_FLV, Render_Camera::MAX_FOV);
	}

	void Render_Camera::Look_At(const Vector3& Postion, const Vector3& Target, const Vector3& Up) {
		//TODO
	}

	void Render_Camera::Set_Z_Near(float Z_Near){
		this->m_Z_Near = Z_Near;
	}

	void Render_Camera::Set_Z_Far(float Z_Far){
		this->m_Z_Far = Z_Far;
	}

	void Render_Camera::Set_Aspect(const Vector2& Aspect) {
		//TODO
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

	const Vector3 Render_Camera::Get_ForWard(void) const {
		return this->m_Rotation * Render_Camera::Z;
	}

	const Vector3 Render_Camera::Get_Up(void) const {
		return this->m_Rotation * Render_Camera::Y;
	}

	const Vector3 Render_Camera::Get_Right(void) const {
		return this->m_Rotation * Render_Camera::X;
	}

	const Vector2 Render_Camera::Get_FOV(void) const {
		return Vector2{ this->m_FOV_X,this->m_FOV_Y };
	}

	const Matrix4x4 Render_Camera::Get_View_Matrix(void) const {
		return this->m_View_Matrices[Render_Camera::MAIN_VIEW_MATRIX_INDEX];
	}

	const Matrix4x4 Render_Camera::Get_Projection_Matrix(void) const {
		return Matrix4x4::IDENTITY;
		//TODO
	}

	const Matrix4x4 Render_Camera::Get_Look_At_Matrix(void) const {
		return Matrix4x4::IDENTITY;//TODO
		//TODO
	}

	float Render_Camera::Get_FOV_Deprecated(void) const {
		return 0.f;// TODO
	}

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System