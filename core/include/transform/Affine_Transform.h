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

	class Affine_Tranform final {
	public:
		Affine_Tranform(void) = default;

		Affine_Tranform(const Affine_Tranform&) = default;
		Affine_Tranform(Affine_Tranform&&) = default;

		Affine_Tranform& operator=(const Affine_Tranform&) = default;
		Affine_Tranform& operator=(Affine_Tranform&&) = default;

		Affine_Tranform(const Matrix3x3& Basis, const Vector3 Translate);

		explicit Affine_Tranform(const Quaternion& Rotate_Quaternion, const Vector3& Translate = Vector3::ZERO);
		explicit Affine_Tranform(const Vector3& Translate);

		Affine_Tranform(float Scale_X, float Scale_Y, float Scale_Z, const Vector3& Translate = Vector3::ZERO);

		explicit Affine_Tranform(const Orthogonal_Transform& Temp_Orthogonal_Transform);
		explicit Affine_Tranform(const Uniform_Transform& Temp_Unifom_Transform);

		~Affine_Tranform(void) = default;

	public:
		Affine_Tranform& operator=(const Quaternion& Rotate_Quaternion);
		Affine_Tranform& operator=(const Vector3& Translate_Vector3);

		Affine_Tranform& operator=(const Orthogonal_Transform& Temp_Orthogonal_Transform);
		Affine_Tranform& operator=(const Uniform_Transform& Temp_Unifom_Transform);

		operator Matrix4x4(void)const;

		bool operator==(const Affine_Tranform& R_HS)const;
		bool operator!=(const Affine_Tranform& R_HS)const;

		const Affine_Tranform operator*(const Affine_Tranform& R_HS)const;

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
		static const Affine_Tranform Generate_Rotation_X(const Radian& Angle);
		static const Affine_Tranform Generate_Rotation_Y(const Radian& Angle);
		static const Affine_Tranform Generate_Rotation_Z(const Radian& Angle);

		static const Affine_Tranform Generate_Rotation(const Vector3& Axis, const Radian& Angle);
		static const Affine_Tranform Generate_Rotation(const Quaternion& Rotate);

		static const Affine_Tranform Generate_Scale(const Vector3& Not_Uniform_Scales);
		static const Affine_Tranform Generate_Scale(float Uniform_Scale);

		static const Affine_Tranform Generate_Translation(const Vector3& Translate_Vector3);

	public:
		static const Affine_Tranform IDENTITY;

	private:
		Matrix3x3 m_Basis{ Matrix3x3::IDENTITY };
		Vector3 m_Translation{ Vector3::ZERO };

	};

}// namespace NameSpace_Core::NameSpace_Transform