#pragma once

#include<cstdint>
#include<vector>
#include<mutex>

#include "math/Vector2.h"
#include "math/Vector3.h"
#include "math/Quaternion.h"
#include "math/Matrix4x4.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System {

	using std::vector;

	using NameSpace_Core::NameSpace_Math::Vector2;
	using NameSpace_Core::NameSpace_Math::Vector3;
	using NameSpace_Core::NameSpace_Math::Quaternion;
	using NameSpace_Core::NameSpace_Math::Matrix4x4;

	enum class RENDER_CAMERA_TYPE :uint32_t {
		EDITOR = 0,
		MOTOR = 1
	};

	struct Render_Camera {
	private:
		Render_Camera(const Render_Camera&) = delete;
		Render_Camera& operator=(const Render_Camera&) = delete;

	public:
		Render_Camera(void) = default;

		~Render_Camera(void) = default;

	public:
		RENDER_CAMERA_TYPE m_Camera_Type{ RENDER_CAMERA_TYPE::EDITOR };

		static const inline Vector3
			X{ Vector3::UNIT_X },
			Y{ Vector3::UNIT_Y },
			Z{ Vector3::UNIT_Z };

		static constexpr float MIN_FLV{ 10.f };
		static constexpr float MAX_FOV{ 89.f };
		static constexpr int MAIN_VIEW_MATRIX_INDEX{ 0 };

		Vector3 m_Position{ Vector3::ZERO };
		Quaternion m_Rotation{ Quaternion::IDENTITY };
		Quaternion M_InV_Rotation{ Quaternion::IDENTITY };
		float m_Z_Near{ 0.1f };
		float m_Z_Far{ 1000.0f };
		Vector3 m_Up_Axis{ Render_Camera::Y };

		vector<Matrix4x4> m_View_Matrices{ Matrix4x4::IDENTITY };

		void Set_Current_Camera_Type(RENDER_CAMERA_TYPE Camera_Type);

		void Set_Main_View_Matrix(const Matrix4x4& View_Matrix, RENDER_CAMERA_TYPE Camera_Type = RENDER_CAMERA_TYPE::EDITOR);

		void Move(Vector3 Direction);
		void Rotate(Vector2 Delta);
		void Zoom(float Offset);
		void Look_At(const Vector3& Postion, const Vector3& Target, const Vector3& Up);

		void Set_Z_Near(float Z_Near);
		void Set_Z_Far(float Z_Far);

		void Set_Aspect(const Vector2& Aspect);
		void Set_FOV_X(float FOV);

		const Vector3 Get_Position(void) const;
		const Quaternion Get_Rotation(void) const;
		const Vector3 Get_ForWard(void) const;
		const Vector3 Get_Up(void) const;
		const Vector3 Get_Right(void) const;
		const Vector2 Get_FOV(void)const;
		const Matrix4x4 Get_View_Matrix(void) const;
		const Matrix4x4 Get_Projection_Matrix(void) const;
		const Matrix4x4 Get_Look_At_Matrix(void) const;
		float Get_FOV_Deprecated(void) const;

		
	protected:
		float m_Aspect{ 0.f };
		float m_FOV_X{ 89.f };
		float m_FOV_Y{ 0.f };

		std::mutex m_View_Matrix_Mutex;
	};

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System