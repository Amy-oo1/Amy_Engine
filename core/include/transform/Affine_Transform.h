#pragma once

#include "math/Head_Math.h"

#include "transform/Orthogonal_Transform.h"
#include "transform/Uniform_Transform.h"

namespace NameSpace_Core::NameSpace_Transform {

	using NameSpace_Math::Radian;
	using NameSpace_Math::Vector3;
	using NameSpace_Math::Vector4;
	using NameSpace_Math::Matrix3x3;
	using NameSpace_Math::Matrix4x4;
	using NameSpace_Math::Quaternion;

	class Affine_Transform final {
	public:
		Affine_Transform(void) = default;

		Affine_Transform(const Affine_Transform&) = default;
		Affine_Transform(Affine_Transform&&) = default;

		Affine_Transform& operator=(const Affine_Transform&) = default;
		Affine_Transform& operator=(Affine_Transform&&) = default;

		Affine_Transform(const Matrix3x3& Basis, const Vector3 Translate);

		explicit Affine_Transform(const Quaternion& Rotate_Quaternion, const Vector3& Translate = Vector3::ZERO);
		explicit Affine_Transform(const Vector3& Translate);

		Affine_Transform(float Scale_X, float Scale_Y, float Scale_Z, const Vector3& Translate = Vector3::ZERO);

		explicit Affine_Transform(const Orthogonal_Transform& Temp_Orthogonal_Transform);
		explicit Affine_Transform(const Uniform_Transform& Temp_Unifom_Transform);

		~Affine_Transform(void) = default;

	public:
		Affine_Transform& operator=(const Quaternion& Rotate_Quaternion);
		Affine_Transform& operator=(const Vector3& Translate_Vector3);

		Affine_Transform& operator=(const Orthogonal_Transform& Temp_Orthogonal_Transform);
		Affine_Transform& operator=(const Uniform_Transform& Temp_Unifom_Transform);

		operator Matrix4x4(void)const;

		bool operator==(const Affine_Transform& R_HS)const;
		bool operator!=(const Affine_Transform& R_HS)const;

		const Affine_Transform operator*(const Affine_Transform& R_HS)const;

		const Vector3 operator*(const Vector3& Vec3)const;
		const Vector4 operator*(const Vector4& Vec4)const;

	public:
		const Vector3 Get_X(void)const;
		const Vector3 Get_Y(void)const;
		const Vector3 Get_Z(void)const;

		const Matrix3x3 Get_Basis(void)const;
		const Vector3 Get_Translation(void)const;

		void Set_X(const Vector3& X);
		void Set_Y(const Vector3& Y);
		void Set_Z(const Vector3& Z);

		void Set_Basis(const Matrix3x3& Basis);
		void Set_Translation(const Vector3& Translate);

		bool Has_Rotation(void)const;
		bool Has_Scale(void)const;
		bool Has_Negative_Scale(void)const;
		bool Has_Translation(void)const;

	public:
		static const Affine_Transform Generate_Rotation_X(const Radian& Angle);
		static const Affine_Transform Generate_Rotation_Y(const Radian& Angle);
		static const Affine_Transform Generate_Rotation_Z(const Radian& Angle);

		static const Affine_Transform Generate_Rotation(const Vector3& Axis, const Radian& Angle);
		static const Affine_Transform Generate_Rotation(const Quaternion& Rotate);

		static const Affine_Transform Generate_Scale(const Vector3& Not_Uniform_Scales);
		static const Affine_Transform Generate_Scale(float Uniform_Scale);

		static const Affine_Transform Generate_Translation(const Vector3& Translate_Vector3);

	public:
		static const Affine_Transform IDENTITY;

	private:
		Matrix3x3 m_Basis{ Matrix3x3::IDENTITY };
		Vector3 m_Translation{ Vector3::ZERO };

	};

}// namespace NameSpace_Core::NameSpace_Transform