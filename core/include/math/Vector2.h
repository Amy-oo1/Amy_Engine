#pragma once

#include<cstddef>

#include "math/Radian.h"

namespace NameSpace_Core::NameSpace_Math {

	class Vector2 {
	public:
		Vector2(void) = default;

		Vector2(const Vector2&) = default;
		Vector2(Vector2&&) = default;

		Vector2& operator=(const Vector2&) = default;
		Vector2& operator=(Vector2&&) = default;

		explicit Vector2(float Scalar);
		Vector2(float Temp_X, float Temp_Y);

		~Vector2(void) = default;

	public:
		Vector2& operator=(float Scalar);

		const Vector2 operator+(void)const;
		const Vector2 operator-(void)const;

		const bool operator==(const Vector2& R_HS)const;
		const bool operator!=(const Vector2& R_HS)const;

		const bool operator<(const Vector2& R_HS)const;
		const bool operator>(const Vector2& R_HS)const;
		const bool operator<=(const Vector2& R_HS)const;
		const bool operator>=(const Vector2& R_HS)const;


		const Vector2 operator+(const Vector2& R_HS)const;
		const Vector2 operator+(float R_HS)const;
		friend const Vector2 operator+(float L_HS, const Vector2& R_HS);

		const Vector2 operator-(const Vector2& R_HS)const;
		const Vector2 operator-(float R_HS)const;
		friend const Vector2 operator-(float L_HS, const Vector2& R_HS);

		const Vector2 operator*(const Vector2& R_HS)const;
		const Vector2 operator*(float R_HS)const;
		friend const Vector2 operator*(float L_HS, const Vector2& R_HS);

		const Vector2 operator/(const Vector2& R_HS)const;
		const Vector2 operator/(float R_HS)const;
		friend const Vector2 operator/(float L_HS, const Vector2& R_HS);

		Vector2& operator+=(const Vector2& R_HS);
		Vector2& operator+=(float R_HS);

		Vector2& operator-=(const Vector2& R_HS);
		Vector2& operator-=(float R_HS);

		Vector2& operator*=(const Vector2& R_HS);
		Vector2& operator*=(float R_HS);

		Vector2& operator/=(const Vector2& R_HS);
		Vector2& operator/=(float R_HS);

		float& operator[](size_t Index);
		const float& operator[](size_t Index)const;

	public:
		const float Length(void)const;
		const float Length_Square(void)const;

		const float Distance(const Vector2& R_HS)const;
		const float Distance_Square(const Vector2& R_HS)const;

		const float Dot_Product(const Vector2& R_HS)const;
		const float Cross_Product(const Vector2& R_HS)const;

		const Vector2 Normalize(void)const;
		Vector2& To_Normalized(void);

		const Vector2 Project_Over(const Vector2& Not_Zero_Other)const;		

		const Vector2 Reflect(const Vector2& Normal)const;

		const Radian Angle_Between(const Vector2& R_HS)const;

		const Vector2 Perpendicular(void)const;

		const Vector2 Ceil(void)const;
		const Vector2 Floor(void)const;

		const Vector2 Middle_Point(const Vector2& R_HS)const;

	public:
		const float Get_X(void) const;
		const float Get_Y(void) const;

		void Set_X(float X);
		void Set_Y(float Y);

		const bool Is_NaN(void) const;
		const bool Is_Unit(void) const;

	public:
		static const Vector2 ZERO;
		static const Vector2 ONE;
		static const Vector2 UNIT_X;
		static const Vector2 UNIT_Y;

	private:
		float m_X{ 0.f };
		float m_Y{ 0.f };

	};

}// namespace NameSpace_Core::NameSpace_Math