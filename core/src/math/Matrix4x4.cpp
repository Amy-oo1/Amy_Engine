#include "math/Matrix4x4.h"

#include<cassert>

#include "math/Constant.h"
#include  "math/Utilities.h"

namespace NameSpace_Core::NameSpace_Math {

	Matrix4x4::Matrix4x4(const Vector4& Row_0, const Vector4& Row_1, const Vector4& Row_2, const Vector4& Row_3) :
		m_Mat{ Row_0,Row_1,Row_2,Row_3 } {
	}

	Matrix4x4::Matrix4x4(const initializer_list<float>& List) {
		size_t  Cur = 0;

		for (auto Scalar_Iterator = List.begin(); Scalar_Iterator != List.end(); ++Scalar_Iterator, ++Cur) {
			this->m_Mat[Cur / 4][Cur % 4] = *Scalar_Iterator;
		}
	}

	Matrix4x4::Matrix4x4(const Vector4 CArrays[4])
		:Matrix4x4{
			CArrays[0],
			CArrays[1],
			CArrays[2],
			CArrays[3]
		} {
	}

	Matrix4x4::Matrix4x4(const float CArray[16])
		:Matrix4x4{
			CArray[0],CArray[1],CArray[2],CArray[3],
			CArray[4],CArray[5],CArray[6],CArray[7],
			CArray[8],CArray[9],CArray[10],CArray[11],
			CArray[12],CArray[13],CArray[14],CArray[15]
		} {
	}

	Matrix4x4::Matrix4x4(const float CArrays[4][4])
		:Matrix4x4{
			CArrays[0][0],CArrays[0][1],CArrays[0][2],CArrays[0][3],
			CArrays[1][0],CArrays[1][1],CArrays[1][2],CArrays[1][3],
			CArrays[2][0],CArrays[2][1],CArrays[2][2],CArrays[2][3],
			CArrays[3][0],CArrays[3][1],CArrays[3][2],CArrays[3][3]
		} {
	}

	Matrix4x4& Matrix4x4::operator=(const Vector4 CArray[4]) {
		return (*this) = Matrix4x4{ CArray };
	}

	Matrix4x4& Matrix4x4::operator=(const initializer_list<float>& List) {
		return (*this) = Matrix4x4{ List };
	}

	Matrix4x4& Matrix4x4::operator=(const float CArray[16]) {
		return (*this) = Matrix4x4{ CArray };
	}

	Matrix4x4& Matrix4x4::operator=(const float CArrays[4][4]) {
		return (*this) = Matrix4x4{ CArrays };
	}

	const Matrix4x4 Matrix4x4::operator+(void) const {
		return *this;
	}

	const Matrix4x4 Matrix4x4::operator-(void) const {
		return Matrix4x4{
			-this->m_Mat[0],
			-this->m_Mat[1],
			-this->m_Mat[2],
			-this->m_Mat[3]
		};
	}

	const bool Matrix4x4::operator==(const Matrix4x4& R_HS) const {
		for (size_t Row_Index = 0; Row_Index < 4; ++Row_Index)
			if (m_Mat[Row_Index] != R_HS.m_Mat[Row_Index])
				return false;
		return true;
	}

	const bool Matrix4x4::operator!=(const Matrix4x4& R_HS) const {
		return !(*this == R_HS);
	}

	const Matrix4x4 Matrix4x4::operator+(const Matrix4x4& R_HS) const {
		return Matrix4x4{
			this->m_Mat[0] + R_HS.m_Mat[0],
			this->m_Mat[1] + R_HS.m_Mat[1],
			this->m_Mat[2] + R_HS.m_Mat[2],
			this->m_Mat[3] + R_HS.m_Mat[3]
		};
	}

	const Matrix4x4 Matrix4x4::operator-(const Matrix4x4& R_HS) const {
		return Matrix4x4{
			this->m_Mat[0] - R_HS.m_Mat[0],
			this->m_Mat[1] - R_HS.m_Mat[1],
			this->m_Mat[2] - R_HS.m_Mat[2],
			this->m_Mat[3] - R_HS.m_Mat[3]
		};
	}

	const Matrix4x4 Matrix4x4::operator*(float R_HS) const {
		return Matrix4x4{
			this->m_Mat[0] * R_HS,
			this->m_Mat[1] * R_HS,
			this->m_Mat[2] * R_HS,
			this->m_Mat[3] * R_HS
		};
	}

	const Matrix4x4 operator*(float L_HS, const Matrix4x4& R_HS) {
		return R_HS * L_HS;
	}

	const Vector4 Matrix4x4::operator*(const Vector4& R_HS) const {
		return Vector4{
			m_Mat[0].Dot_Product(R_HS),
			m_Mat[1].Dot_Product(R_HS),
			m_Mat[2].Dot_Product(R_HS),
			m_Mat[3].Dot_Product(R_HS)
		};
	}

	const Vector4 operator*(const Vector4& L_HS, const Matrix4x4& R_HS) {
		return (R_HS.Transpose() * L_HS);
	}

	const Matrix4x4 Matrix4x4::operator*(const Matrix4x4& R_HS) const {
		Matrix4x4 Prod_Matrix4x4{};

		for (size_t Row_Index = 0; Row_Index < 4; ++Row_Index)
			for (size_t Column_Index = 0; Column_Index < 4; ++Column_Index)
				Prod_Matrix4x4[Row_Index][Column_Index] = this->m_Mat[Row_Index].Dot_Product(R_HS.Get_Column(Column_Index));

		return Prod_Matrix4x4;
	}

	Matrix4x4& Matrix4x4::operator+=(const Matrix4x4& R_HS) {
		return (*this) = (*this) + R_HS;
	}

	Matrix4x4& Matrix4x4::operator-=(const Matrix4x4& R_HS) {
		return (*this) = (*this) - R_HS;
	}

	Matrix4x4& Matrix4x4::operator*=(float R_HS) {
		return (*this) = (*this) * R_HS;
	}

	Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& R_HS) {
		return (*this) = (*this) * R_HS;
	}

	Vector4& Matrix4x4::operator[](size_t Row_Index) {
		return this->m_Mat[Row_Index];
	}

	const Vector4& Matrix4x4::operator[](size_t Row_Index) const {
		return this->m_Mat[Row_Index];
	}

	const Vector4 Matrix4x4::Get_Row(size_t Row_Index) const {
		return this->m_Mat[Row_Index];
	}

	const Vector4 Matrix4x4::Get_Column(size_t Column_Index) const {
		return Vector4{
			this->m_Mat[0][Column_Index],
			this->m_Mat[1][Column_Index],
			this->m_Mat[2][Column_Index],
			this->m_Mat[3][Column_Index]
		};
	}

	const Matrix3x3 Matrix4x4::Get_LeftTop_Matrix3x3(void) const {
		return Matrix3x3{
			this->m_Mat[0].Get_XYZ(),
			this->m_Mat[1].Get_XYZ(),
			this->m_Mat[2].Get_XYZ()
		};
	}

	void Matrix4x4::Set_Row(size_t Row_Index, const Vector4& Temp_Vector4) {
		this->m_Mat[Row_Index] = Temp_Vector4;
	}

	void Matrix4x4::Set_Row(size_t Row_Index, float Scale) {
		this->m_Mat[Row_Index] = Vector4{ Scale };
	}

	void Matrix4x4::Set_Row(size_t Row_Index, float X, float Y, float Z, float W) {
		this->m_Mat[Row_Index] = Vector4{ X,Y,Z,W };
	}

	void Matrix4x4::Set_Row(size_t Row_Index, const Vector3& Temp_Vector3, float W) {
		this->m_Mat[Row_Index] = Vector4{ Temp_Vector3,W };
	}

	void Matrix4x4::Set_Column(size_t Column_Index, const Vector4& Temp_Vector4) {
		this->m_Mat[0][Column_Index] = Temp_Vector4[0];
		this->m_Mat[1][Column_Index] = Temp_Vector4[1];
		this->m_Mat[2][Column_Index] = Temp_Vector4[2];
		this->m_Mat[3][Column_Index] = Temp_Vector4[3];
	}

	void Matrix4x4::Set_Column(size_t Column_Index, float Scale) {
		for (size_t Row_Index = 0; Row_Index < 4; ++Row_Index)
			this->m_Mat[Row_Index][Column_Index] = Scale;
	}

	void Matrix4x4::Set_Column(size_t Column_Index, float X, float Y, float Z, float W) {
		this->m_Mat[0][Column_Index] = X;
		this->m_Mat[1][Column_Index] = Y;
		this->m_Mat[2][Column_Index] = Z;
		this->m_Mat[3][Column_Index] = W;
	}

	void Matrix4x4::Set_Column(size_t Column_Index, const Vector3& Temp_Vector3, float W) {
		this->m_Mat[0][Column_Index] = Temp_Vector3.Get_X();
		this->m_Mat[1][Column_Index] = Temp_Vector3.Get_Y();
		this->m_Mat[2][Column_Index] = Temp_Vector3.Get_Z();
		this->m_Mat[3][Column_Index] = W;
	}

	const float Matrix4x4::Trace(void) const {
		return this->m_Mat[0][0] + this->m_Mat[1][1] + this->m_Mat[2][2] + this->m_Mat[3][3];
	}

	const Matrix4x4 Matrix4x4::Transpose(void) const {
		Matrix4x4 Transpose_Matrix4x4{};

		for (size_t Row_Index = 0; Row_Index < 4; ++Row_Index)
			for (size_t Column_Index = 0; Column_Index < 4; ++Column_Index)
				Transpose_Matrix4x4[Row_Index][Column_Index] = m_Mat[Column_Index][Row_Index];

		return Transpose_Matrix4x4;
	}

	Matrix4x4& Matrix4x4::To_Transpose(void) {
		return (*this) = this->Transpose();
	}

	const float Matrix4x4::Determinant(void) const {
		return m_Mat[0][0] * this->Minor(0, 0) - m_Mat[0][1] * this->Minor(0, 1) + m_Mat[0][2] * this->Minor(0, 2) - m_Mat[0][3] * this->Minor(0, 3);
	}

	const Matrix4x4 Matrix4x4::Adjoint(void) const {
		return Matrix4x4{
			this->Minor(0, 0),-this->Minor(1, 0),this->Minor(2, 0),-this->Minor(3, 0),
			-this->Minor(0, 1),this->Minor(1, 1),-this->Minor(2, 1),this->Minor(3, 1),
			this->Minor(0, 2),-this->Minor(1, 2),this->Minor(2, 2),-this->Minor(3, 2),
			-this->Minor(0, 3),this->Minor(1, 3),-this->Minor(2, 3),this->Minor(3, 3)
		};
	}

	const Matrix4x4 Matrix4x4::Inverse(void) const {
		assert(!this->Is_Singular());

		return this->Adjoint() * (1.f / this->Determinant());
	}

	Matrix4x4& Matrix4x4::To_Inverse(void) {
		return (*this) = this->Inverse();
	}

	const float Matrix4x4::Minor(size_t Out_Row, size_t Out_Column) const {
		Matrix3x3 Temp{};

		for (int Row_Index = 0, Temp_Row = 0; Row_Index < 4; ++Row_Index) {
			if (Row_Index == Out_Row) continue;

			for (int Column_Index = 0, Temp_Column = 0; Column_Index < 4; ++Column_Index) {
				if (Column_Index == Out_Column) continue;

				Temp[Temp_Row][Temp_Column] = m_Mat[Row_Index][Column_Index];
				++Temp_Column;
			}
			++Temp_Row;
		}

		return Temp.Determinant();
	}

	const bool Matrix4x4::Is_Singular(void) const{
		return NameSpace_Utilities::Real_Equal(this->Determinant(), 0.f);
	}

	const Matrix4x4 Matrix4x4::Generate_Column_Order(const Vector4& Column_0, const Vector4& Column_1, const Vector4& Column_2, const Vector4& Column_3) {
		return Matrix4x4{ Column_0,Column_1,Column_2,Column_3 }.Transpose();
	}

	const Matrix4x4 Matrix4x4::Generate_Column_Order(const Vector4 Temp_Vector4_CArrays[4]) {
		return Matrix4x4{ Temp_Vector4_CArrays }.Transpose();
	}

	const Matrix4x4 Matrix4x4::Generate_Column_Order(const float CArray[4][4]) {
		return Matrix4x4{ CArray }.Transpose();
	}

	const Matrix4x4 Matrix4x4::Generate_Column_Order(const float Carrays[16]) {
		return Matrix4x4{ Carrays }.Transpose();

	}

	const Matrix4x4 Matrix4x4::Generate_Column_Order(const initializer_list<float>& Scalars) {
		return Matrix4x4{ Scalars }.Transpose();
	}

	const Matrix4x4 Matrix4x4::ZERO{};
	const Matrix4x4 Matrix4x4::IDENTITY{ Vector4::UNIT_X,Vector4::UNIT_Y,Vector4::UNIT_Z ,Vector4::UNIT_W };

}// namespace NameSpace_Core::NameSpace_Math