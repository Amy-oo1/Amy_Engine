#pragma once

#include<cstddef>

#include "math/Radian.h"

namespace NameSpace_Core::NameSpace_Math {

	class Vector3 final {
	public:
		Vector3(void) = default;

		Vector3(const Vector3&) = default;
		Vector3(Vector3&&) = default;

		Vector3& operator=(const Vector3&) = default;
		Vector3& operator=(Vector3&&) = default;

		explicit Vector3(float Scalar);
		Vector3(float X, float Y, float Z);

		~Vector3(void) = default;

	public:
		Vector3& operator=(float Scalar);

		const Vector3 operator+(void)const;
		const Vector3 operator-(void)const;

		const bool operator==(const Vector3& R_HS)const;
		const bool operator!=(const Vector3& R_HS)const;

		const bool operator<(const Vector3& R_HS)const;
		const bool operator>(const Vector3& R_HS)const;
		const bool operator<=(const Vector3& R_HS)const;
		const bool operator>=(const Vector3& R_HS)const;

		const Vector3 operator+(const Vector3& R_HS)const;
		const Vector3 operator+(float R_HS)const;
		friend const Vector3 operator+(float L_HS, const Vector3& R_HS);

		const Vector3 operator-(const Vector3& R_HS)const;
		const Vector3 operator-(float R_HS)const;
		friend const Vector3 operator-(float L_HS, const Vector3& R_HS);

		const Vector3 operator*(const Vector3& R_HS)const;
		const Vector3 operator*(float R_HS)const;
		friend const Vector3 operator*(float L_HS, const Vector3& R_HS);

		const Vector3 operator/(const Vector3& R_HS)const;
		const Vector3 operator/(float R_HS)const;
		friend const Vector3 operator/(float L_HS, const Vector3& R_HS);

		Vector3& operator+=(const Vector3& R_HS);
		Vector3& operator+=(float R_HS);

		Vector3& operator-=(const Vector3& R_HS);
		Vector3& operator-=(float R_HS);

		Vector3& operator*=(const Vector3& R_HS);
		Vector3& operator*=(float R_HS);

		Vector3& operator/=(const Vector3& R_HS);
		Vector3& operator/=(float R_HS);

		const float& operator[](size_t Index)const;
		float& operator[](size_t Index);

	public:

		const float Length(void)const;
		const float Length_Square(void) const;

		const float Distance(const Vector3& R_HS)const;
		const float Distance_Square(const Vector3& R_HS)const;

		const float Dot_Product(const Vector3& R_HS)const;
		const Vector3 Cross_Product(const Vector3& R_HS)const;

		const Vector3 Normalize(void)const;
		Vector3& To_Normalized(void);

		const Vector3 Project_Over(const Vector3& Not_Zero_Other)const;

		const Vector3 Reflect(const Vector3& Normal)const;

		const Vector3 Ceil(void)const;
		const Vector3 Floor(void)const;

		const Radian Angle_Between(const Vector3& R_HS)const;

		const Vector3 Middle_Point(const Vector3& R_HS);

	public:
		const float Get_X(void)const;
		const float Get_Y(void)const;
		const float Get_Z(void)const;

		void Set_X(float X);
		void Set_Y(float Y);
		void Set_Z(float Z);

		const bool Is_NaN(void)const;
		const bool Is_Unit(void)const;

	public:
		static const Vector3 ZERO;
		static const Vector3 ONE;
		static const Vector3 UNIT_X;
		static const Vector3 UNIT_Y;
		static const Vector3 UNIT_Z;

	private:
		float m_X{ 0.f };
		float m_Y{ 0.f };
		float m_Z{ 0.f };

	};

}// namespace NameSpace_Core::NameSpace_Math