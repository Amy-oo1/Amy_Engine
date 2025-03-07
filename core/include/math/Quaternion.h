#pragma once

#include<utility>

#include "math/Constant.h"
#include "math/Radian.h"
#include "math/Vector3.h"
#include "math/Matrix3x3.h"
#include "math/Matrix4x4.h"

namespace NameSpace_Core::NameSpace_Math {

	using std::pair;

	class  Quaternion final {
	public:
		enum class Index { s = 0, i = 1, j = 2, k = 3 };

	public:
		Quaternion(void) = default;

		Quaternion(const Quaternion&) = default;
		Quaternion(Quaternion&&) = default;

		Quaternion& operator=(const Quaternion&) = default;
		Quaternion& operator=(Quaternion&&) = default;

		Quaternion(float S, float X, float Y, float Z);
		Quaternion(float Real_Part, const Vector3& Imaginary_Part);

		Quaternion(const Vector3&  Axis, const Radian& Angle);
		Quaternion(const Radian& Pitch, const Radian& Yaw, const Radian& Roll);

		explicit Quaternion(const Matrix3x3& Rotation_Matrix3x3);
		explicit Quaternion(const Matrix4x4& Rotation_Matrix4x4);

		~Quaternion(void) = default;
	public:
		Quaternion& operator=(const Matrix3x3& Rotation_Matrix3x3);
		Quaternion& operator=(const Matrix4x4& Rotation_Matrix4x4);

	public:
		const Quaternion operator+(void) const;
		const Quaternion operator-(void) const;

		const Quaternion operator~(void)const;

		const bool operator==(const Quaternion& R_HS) const;
		const bool operator!=(const Quaternion& R_HS) const;

		const Quaternion operator+(const Quaternion& R_HS)const;
		const Quaternion operator-(const Quaternion& R_HS)const;

		const Quaternion operator*(const Quaternion& R_HS)const;

		const Quaternion operator*(float R_HS) const;
		friend const Quaternion operator*(float L_HS, const Quaternion& R_HS);

		const Vector3 operator*(const Vector3& R_HS)const;

		Quaternion& operator+=(const Quaternion& R_HS);
		Quaternion& operator-=(const Quaternion& R_HS);

		Quaternion& operator*=(const Quaternion& R_HS);

		Quaternion& operator*=(float R_HS);

		const float& operator[](Quaternion::Index Index)const;
		float& operator[](Quaternion::Index Index);

	public:
		const float Length(void)const;
		const float Length_Square(void)const;

		const bool Is_Equivalence_Rotate(const Quaternion& Temp_Quaternion, float Tolerance=Math_FLOAT_EPSILON)const;

		const Quaternion Normalize(void)const;
		Quaternion& To_Normalize(void);

		const Quaternion Conjugation(void)const;

		const Quaternion Inverse(void) const;

		const float Dot_Product(const Quaternion& Temp_Quaternion)const;

		const Matrix3x3 Get_Rotation_Matrix3x3(void) const;
		const Matrix4x4 Get_Rotation_Matrix4x4(void) const;

		const pair<Vector3, Radian> Get_AxisAngle(void)const;

		const Radian Get_Pitch(void)const;
		const Radian Get_Yaw(void)const;
		const Radian Get_Roll(void)const;

	public:
		const float Get_S(void) const;
		const float Get_X(void) const;
		const float Get_Y(void) const;
		const float Get_Z(void) const;

		const float Get_Real_Part(void)const;
		const Vector3 Get_Imaginary_Part(void)const;

		const bool Is_NaN(void)const;

	public:
		static const Quaternion Generate_By_AxisAngle(const Vector3& Axis, const Radian& Angle);

		static const Quaternion Generate_By_RotationMatrix(const Matrix3x3& Rotation_Matrix3x3);
		static const Quaternion Generate_By_RotationMatrix(const Matrix4x4& Rotation_Matrix4x4);

		pair<Vector3, Radian> To_AxisAngle_Representation(void)const;


		static const Quaternion Normalized_Lerp(const Quaternion& P, const Quaternion& Q, float T, bool Use_Shortest_Path);
		static const Quaternion Spherical_Lerp(const Quaternion& P, const Quaternion& Q, float T, bool Use_Shortest_Path);

	public:
		static const Quaternion ZERO;
		static const Quaternion IDENTITY;

	private:
		pair<float, Vector3> m_Quat{ 0.f, Vector3{ 0.f,0.f,0.f} };

	};

}// namespace NameSpace_Core::NameSpace_Math