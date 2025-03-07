#pragma once

#include<cstddef>

#include "math/Vector3.h"

namespace NameSpace_Core::NameSpace_Math {

	class Vector4 final{
	public:
		Vector4(void) = default;

		Vector4(const Vector4&) = default;
		Vector4(Vector4&&) = default;

		Vector4& operator=(const Vector4&) = default;
		Vector4& operator=(Vector4&&) = default;

		explicit Vector4(float Scalar);
		Vector4(float X, float Y, float Z, float W);
		Vector4(const Vector3& XYZ, float W);

		~Vector4(void) = default;

	public:
		Vector4& operator=(float R_Temp_Scalar);

		const Vector4 operator+(void)const;
		const Vector4 operator-(void)const;

		const bool operator==(const Vector4& R_Temp_Vector4)const;
		const bool operator!=(const Vector4& R_Temp_Vector4)const;

		const Vector4 operator+(const Vector4& R_Temp_Vector4)const;
		const Vector4 operator+(float R_Temp_Scalar)const;
		friend const Vector4 operator+(float L_Temp_Scalar, const Vector4& R_Temp_Vector4);

		const Vector4 operator-(const Vector4& R_Temp_Vector4)const;
		const Vector4 operator-(float R_Temp_Scalar)const;
		friend const Vector4 operator-(float L_Temp_Scalar, const Vector4& R_Temp_Vector4);

		const Vector4 operator*(const Vector4& R_Temp_Vector4)const;
		const Vector4 operator*(float R_Temp_Scalar)const;
		friend const Vector4 operator*(float L_Temp_Scalar, const Vector4& R_Temp_Vector4);

		const Vector4 operator/(const Vector4& R_Temp_Vector4)const;
		const Vector4 operator/(float R_Temp_Scalar)const;
		friend const Vector4 operator/(float L_Temp_Scalar, const Vector4& R_Temp_Vector4);

		Vector4& operator+=(const Vector4& R_Temp_Vector4);
		Vector4& operator+=(float R_Temp_Scalar);

		Vector4& operator-=(const Vector4& R_Temp_Vector4);
		Vector4& operator-=(float R_Temp_Scalar);

		Vector4& operator*=(const Vector4& R_Temp_Vector4);
		Vector4& operator*=(float R_Temp_Scalar);

		Vector4& operator/=(const Vector4& R_Temp_Vector4);
		Vector4& operator/=(float R_Temp_Scalar);

		const float& operator[](size_t Index)const;
		float& operator[](size_t Index);

	public:
		const float Dot_Product(const Vector4& R_Temp_Vector4)const;

		const Vector3 Homogeneous(void)const;

	public:
		const float Get_X(void)const;
		const float Get_Y(void)const;
		const float Get_Z(void)const;
		const float Get_W(void)const;
		const Vector3 Get_XYZ(void)const;

		void Set_X(float X);
		void Set_Y(float Y);
		void Set_Z(float Z);
		void Set_W(float W);
		void Set_XYZ(const Vector3& XYZ);

		const bool Is_NaN(void)const;
		
	public:
		static const Vector4 ZERO;
		static const Vector4 ONE;
		static const Vector4 UNIT_X;
		static const Vector4 UNIT_Y;
		static const Vector4 UNIT_Z;
		static const Vector4 UNIT_W;

	private:
		float m_X{ 0.f };
		float m_Y{ 0.f };
		float m_Z{ 0.f };
		float m_W{ 0.f };

	};

}// namespace NameSpace_Core::NameSpace_Math