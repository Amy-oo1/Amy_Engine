#pragma once

#include "math/Head_Math.h"

namespace NameSpace_Core::NameSpace_Transform {

	using NameSpace_Math::Radian;
	using NameSpace_Math::Vector3;
	using NameSpace_Math::Vector4;
	using NameSpace_Math::Matrix4x4;
	using NameSpace_Math::Quaternion;

	class Orthogonal_Transform final {
	public:
		Orthogonal_Transform(void) = default;

		Orthogonal_Transform(const Orthogonal_Transform&) = default;
		Orthogonal_Transform(Orthogonal_Transform&&) = default;

		Orthogonal_Transform& operator=(const Orthogonal_Transform&) = default;
		Orthogonal_Transform& operator=(Orthogonal_Transform&&) = default;

		Orthogonal_Transform(const Quaternion& Rotate_Quaternion, const Vector3& Translate_Vector3 = Vector3::ZERO);

		explicit Orthogonal_Transform(const Vector3& Translate_Vector3);

		~Orthogonal_Transform(void) = default;

	public:
		const Orthogonal_Transform& operator=(const Quaternion& Rotate_Quaternion);

		const Orthogonal_Transform& operator=(const Vector3& Translate_Vector3);

		const Orthogonal_Transform operator~(void)const;

		bool operator==(const Orthogonal_Transform& R_HS)const;
		bool operator!=(const Orthogonal_Transform& R_HS)const;

		const Orthogonal_Transform operator*(const Orthogonal_Transform& R_HS)const;

		const Vector3 operator*(const Vector3& Vec3)const;
		const Vector4 operator*(const Vector4& Vec4)const;

	public:
		const Quaternion Get_Rotation(void)const;
		const Vector3 Get_Translation(void)const;

		void Set_Rotation(const Quaternion& Rotate_Quaternion);
		void Set_Translation(const Vector3& Translate_Vector3);

		bool Has_Rotation(void)const;
		bool Has_Translation(void)const;

		const Matrix4x4 Get_Matrix4x4(void)const;

	public:
		static const Orthogonal_Transform Generate_Rotation_X(const Radian& Angle);
		static const Orthogonal_Transform Generate_Rotation_Y(const Radian& Angle);
		static const Orthogonal_Transform Generate_Rotation_Z(const Radian& Angle);

		static const Orthogonal_Transform Generate_Rotation(const Vector3& Axis, const Radian& Angle);
		static const Orthogonal_Transform Generate_Rotation(const Quaternion& Rotate_Quaternion);

		static const Orthogonal_Transform Generate_Translation(const Vector3& Translate);

	public:
		static const Orthogonal_Transform IDENTITY;

	private:
		Quaternion m_Rotation{ Quaternion::IDENTITY };
		Vector3 m_Translation{ Vector3::ZERO };
	};

}// NameSpace_Core::NameSpace_Transform