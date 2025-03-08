#pragma once

#include "math/Head_Math.h"

#include "transform/ScaleTranslation_Transform.h"

namespace NameSpace_Core::NameSpace_Transform {

	using NameSpace_Math::Radian;
	using NameSpace_Math::Vector3;
	using NameSpace_Math::Vector4;
	using NameSpace_Math::Matrix4x4;
	using NameSpace_Math::Quaternion;

	class Uniform_Transform final {
	public:
		Uniform_Transform(void) = default;

		Uniform_Transform(const Uniform_Transform&) = default;
		Uniform_Transform(Uniform_Transform&&) = default;

		Uniform_Transform& operator=(const Uniform_Transform&) = default;
		Uniform_Transform& operator=(Uniform_Transform&&) = default;

		explicit Uniform_Transform(const ScaleTranslation_Transform& ScaleTranslation);
		explicit Uniform_Transform(const Quaternion& Rotate, const ScaleTranslation_Transform& Scale_Translation = ScaleTranslation_Transform::IDENTITY);
		Uniform_Transform(const Quaternion& Rotate, float Scale, const Vector3& Translate);

		~Uniform_Transform(void) = default;

	public:
		Uniform_Transform& operator=(const Quaternion& Rotate);
		Uniform_Transform& operator=(const ScaleTranslation_Transform& ScaleTranslation);

		const bool operator==(const Uniform_Transform& R_HS)const;
		const bool operator!=(const Uniform_Transform& R_HS)const;

		const Vector3 operator*(const Vector3& Vec3)const;

	public:
		const Quaternion Get_Rotation(void)const;
		const float Get_Scale(void)const;
		const Vector3 Get_Translation(void)const;
		const ScaleTranslation_Transform Get_Scale_Translation(void)const;

		const Matrix4x4 Get_Matrix4x4(void)const;

		void Set_Rotation(const Quaternion& Rotate);
		void Set_Scale(float Scale);
		void Set_Translation(const Vector3& Translate);
		void Set_Scale_Translation(const ScaleTranslation_Transform& Scale_Translation);

		const bool Has_Rotation(void)const;
		const bool Has_Scale(void)const;
		const bool Has_Negative_Scale(void)const;
		const bool Has_Tranlation(void)const;

	public:
		static const Uniform_Transform Generate_Rotation_X(const Radian& Angle);
		static const Uniform_Transform Generate_Rotation_Y(const Radian& Angle);
		static const Uniform_Transform Generate_Rotation_Z(const Radian& Angle);

		static const Uniform_Transform Generate_Rotation(const Vector3& Axis, const Radian& Angle);
		static const Uniform_Transform Generate_Rotation(const Quaternion& Rotate_Quaternion);

		static const Uniform_Transform Generate_Scale(float Scale);

		static const Uniform_Transform Generate_Translation(const Vector3& Translate);

	public:
		static const Uniform_Transform IDENTITY;

	private:
		Quaternion m_Rotation{ Quaternion::IDENTITY };
		ScaleTranslation_Transform m_Sacle_Transform{ ScaleTranslation_Transform::IDENTITY };

	};

}// namespace NameSpace_Core::NameSpace_Transform