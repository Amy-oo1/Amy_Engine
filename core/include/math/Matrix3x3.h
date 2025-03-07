#pragma once

#include<cstddef>
#include<tuple>
#include<initializer_list>

#include "math/Vector3.h"

namespace NameSpace_Core::NameSpace_Math {

	using std::tuple;
	using std::initializer_list;

	class Matrix3x3 final {
	public:
		Matrix3x3(void) = default;

		Matrix3x3(const Matrix3x3&) = default;
		Matrix3x3(Matrix3x3&&) = default;

		Matrix3x3& operator=(const Matrix3x3&) = default;
		Matrix3x3& operator=(Matrix3x3&&) = default;

		Matrix3x3(const Vector3& Row_0, const Vector3& Row_1, const Vector3& Row_2);
		explicit Matrix3x3(const initializer_list<float>& List);

		explicit Matrix3x3(const Vector3 CArray[3]);
		explicit Matrix3x3(const float CArrays[3][3]);
		explicit Matrix3x3(const float CArray[9]);

		~Matrix3x3(void) = default;

	public:
		Matrix3x3& operator=(const initializer_list<float>& List);

		Matrix3x3& operator=(const Vector3 Temp_Vector3_CArrays[3]);
		Matrix3x3& operator=(const float CArrarys[3][3]);
		Matrix3x3& operator=(const float CArray[9]);

		const Matrix3x3 operator+(void)const;
		const Matrix3x3 operator-(void)const;

		const bool operator==(const Matrix3x3& R_HS)const;
		const bool operator!=(const Matrix3x3& R_HS)const;

		const Matrix3x3 operator+(const Matrix3x3& R_HS)const;
		const Matrix3x3 operator-(const Matrix3x3& R_HS)const;

		const Matrix3x3 operator*(float R_HS)const;
		friend const Matrix3x3 operator*(float L_HS, const Matrix3x3& R_HS);

		const Vector3 operator*(const Vector3& R_HS)const;
		friend const Vector3 operator*(const Vector3& L_HS, const Matrix3x3& R_HS);

		const Matrix3x3 operator*(const Matrix3x3& R_HS)const;

		const Matrix3x3 operator/(float R_HS)const;

		Matrix3x3& operator+=(const Matrix3x3& R_HS);
		Matrix3x3& operator-=(const Matrix3x3& R_HS);

		Matrix3x3& operator*=(float R_HS);
		Matrix3x3& operator*=(const Matrix3x3& R_HS);

		Matrix3x3& operator/=(float R_HS);

		Vector3& operator[](size_t Row_Index);
		const Vector3& operator[](size_t Row_Index)const;

	public:
		const float Trace(void)const;

		const Matrix3x3 Transpose(void)const;
		Matrix3x3& To_Transpose(void);

		const float Determinant(void)const;

		const Matrix3x3 Adjoint(void)const;

		const Matrix3x3 Inverse(void)const;
		Matrix3x3& To_Inverse(void);

		const Matrix3x3 Gram_Schmidt(void)const;
		Matrix3x3& To_Gram_Schmidt(void);

		const float Minor(size_t Out_Row, size_t Out_Column)const;

		tuple<Matrix3x3, Matrix3x3, Matrix3x3> Calculate_QDU_Decomposition(void)const;

	public:
		const Vector3 Get_Row(size_t Row_Index)const;
		const Vector3 Get_Column(size_t Column_Index)const;

		void Set_Row(size_t Row_Index, const Vector3& Temp_Vector3);
		void Set_Row(size_t Row_Index, float Scale);
		void Set_Row(size_t Row_Index, float X, float Y, float Z);

		void Set_Column(size_t Column_Index, const Vector3& Temp_Vector3);
		void Set_Column(size_t Column_Index, float Scale);
		void Set_Column(size_t Column_Index, float X, float Y, float Z);

		const bool Is_Singular(void)const;

	public:
		static const Matrix3x3 Generate_Column_Order(const Vector3& Column_0, const Vector3& Column_1, const Vector3& Column_2);
		static const Matrix3x3 Generate_Column_Order(const initializer_list<float>& List);

		static const Matrix3x3 Generate_Column_Order(const Vector3 CArrays[3]);
		static const Matrix3x3 Generate_Column_Order(const float CArray[3][3]);
		static const Matrix3x3 Generate_Column_Order(const float Carrays[9]);

	public:
		static const Matrix3x3 ZERO;
		static const Matrix3x3 IDENTITY;

	private:
		Vector3 m_Mat[3]{
			Vector3{0.f},
			Vector3{0.f},
			Vector3{0.f}
		};

	};

}// namespace NameSpace_Core::NameSpace_Math