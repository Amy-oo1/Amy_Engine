#pragma once

#include<cstddef>
#include<initializer_list>

#include "math/Vector3.h"
#include "math/Vector4.h"
#include "math/Matrix3x3.h"

namespace NameSpace_Core::NameSpace_Math {

	using std::initializer_list;

	class Matrix4x4 final {
	public:
		Matrix4x4(void) = default;

		Matrix4x4(const Matrix4x4&) = default;
		Matrix4x4(Matrix4x4&&) = default;

		Matrix4x4& operator=(const Matrix4x4&) = default;
		Matrix4x4& operator=(Matrix4x4&&) = default;


		Matrix4x4(const Vector4& Row_0, const Vector4& Row_1, const Vector4& Row_2, const Vector4& Row_3);
		explicit Matrix4x4(const initializer_list<float>& List);

		explicit Matrix4x4(const Vector4 CArrays[4]);
		explicit Matrix4x4(const float CArray[16]);
		explicit Matrix4x4(const float CArrays[4][4]);

		~Matrix4x4(void) = default;

	public:
		Matrix4x4& operator=(const initializer_list<float>& List);

		Matrix4x4& operator=(const Vector4 CArray[4]);
		Matrix4x4& operator=(const float Carray[16]);
		Matrix4x4& operator=(const float Carrays[4][4]);

		const Matrix4x4 operator+(void) const;
		const Matrix4x4 operator-(void) const;

		const bool operator==(const Matrix4x4& R_HS) const;
		const bool operator!=(const Matrix4x4& R_HS) const;

		const Matrix4x4 operator+(const Matrix4x4& R_HS) const;
		const Matrix4x4 operator-(const Matrix4x4& R_HS) const;

		const Matrix4x4 operator*(float R_HS) const;
		friend const Matrix4x4 operator*(float L_HS, const Matrix4x4& R_HS);

		const Vector4 operator*(const Vector4& R_HS) const;
		friend const Vector4 operator*(const Vector4& L_HS, const Matrix4x4& R_HS);

		const Matrix4x4 operator*(const Matrix4x4& R_HS) const;

		Matrix4x4& operator+=(const Matrix4x4& R_HS);
		Matrix4x4& operator-=(const Matrix4x4& R_HS);

		Matrix4x4& operator*=(float R_HS);
		Matrix4x4& operator*=(const Matrix4x4& R_HS);

		Vector4& operator[](size_t Row_Index);
		const Vector4& operator[](size_t Row_Index) const;

	public:
		const Vector4 Get_Row(size_t Row_Index) const;
		const Vector4 Get_Column(size_t Column_Index) const;

		const Matrix3x3 Get_LeftTop_Matrix3x3(void)const;

		void Set_Row(size_t Row_Index, const Vector4& Temp_Vector4);
		void Set_Row(size_t Row_Index, float Scale);
		void Set_Row(size_t Row_Index, float X, float Y, float Z, float W);
		void Set_Row(size_t Row_Index, const Vector3& Temp_Vector3, float W);

		void Set_Column(size_t Column_Index, const Vector4& Temp_Vector4);
		void Set_Column(size_t Column_Index, float Scale);
		void Set_Column(size_t Column_Index, float X, float Y, float Z,float W);
		void Set_Column(size_t Column_Index, const Vector3& Temp_Vector3, float W);

	public:
		const float Trace(void)const;

		const Matrix4x4 Transpose(void)const;
		Matrix4x4& To_Transpose(void);

		const float Determinant(void)const;

		const Matrix4x4 Adjoint(void)const;

		const Matrix4x4 Inverse(void)const;
		Matrix4x4& To_Inverse(void);

		const float Minor(size_t Out_Row, size_t Out_Column)const;

		const bool Is_Singular(void)const;
	
	public:
		static const Matrix4x4 Generate_Column_Order(const Vector4& Column_0, const Vector4& Column_1, const Vector4& Column_2, const Vector4& Column_3);
		static const Matrix4x4 Generate_Column_Order(const initializer_list<float>& List);

		static const Matrix4x4 Generate_Column_Order(const Vector4 CArrays[4]);
		static const Matrix4x4 Generate_Column_Order(const float CArray[4][4]);
		static const Matrix4x4 Generate_Column_Order(const float Carrays[16]);

	public:
		static const Matrix4x4 ZERO;
		static const Matrix4x4 UNIT_X;
		static const Matrix4x4 UNIT_Y;
		static const Matrix4x4 UNIT_Z;
		static const Matrix4x4 UNIT_W;
		static const Matrix4x4 IDENTITY;

	private:
		Vector4 m_Mat[4]{
			Vector4{0.f},
			Vector4{0.f},
			Vector4{0.f},
			Vector4{0.f}
		};

	};

}// namespace NameSpace_Core::NameSpace_Math