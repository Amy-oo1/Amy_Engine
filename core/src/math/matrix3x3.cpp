#include "math/Matrix3x3.h"

#include<cassert>

#include "math/Utilities.h"

namespace NameSpace_Core::NameSpace_Math {

	Matrix3x3::Matrix3x3(const Vector3& Row_0, const Vector3& Row_1, const Vector3& Row_2) :
		m_Mat{ Row_0,Row_1,Row_2 } {
	}

	Matrix3x3::Matrix3x3(const initializer_list<float>& List) {
		size_t  Cur = 0;

		for (auto Scalar_Iterator = List.begin(); Scalar_Iterator != List.end(); ++Scalar_Iterator, ++Cur) {
			this->m_Mat[Cur / 3][Cur % 3] = *Scalar_Iterator;
		}
	}

	Matrix3x3::Matrix3x3(const Vector3 CArrays[3])
		:Matrix3x3{
			CArrays[0],
			CArrays[1],
			CArrays[2]
		} {
	}

	Matrix3x3::Matrix3x3(const float CArray[9])
		:Matrix3x3{
			CArray[0],CArray[1],CArray[2],
			CArray[3],CArray[4],CArray[5],
			CArray[6],CArray[7],CArray[8]
		} {
	}

	Matrix3x3::Matrix3x3(const float CArrays[3][3])
		:Matrix3x3{
			CArrays[0][0],CArrays[0][1],CArrays[0][2],
			CArrays[1][0],CArrays[1][1],CArrays[1][2],
			CArrays[2][0],CArrays[2][1],CArrays[2][2]
		} {
	}

	Matrix3x3& Matrix3x3::operator=(const initializer_list<float>& List) {
		return(*this) = Matrix3x3{ List };
	}

	Matrix3x3& Matrix3x3::operator=(const Vector3 CArrays[3]) {
		return (*this) = Matrix3x3{ CArrays };
	}

	Matrix3x3& Matrix3x3::operator=(const float CArrarys[3][3]) {
		return (*this) = Matrix3x3{ CArrarys };
	}

	Matrix3x3& Matrix3x3::operator=(const float CArray[9]) {
		return (*this) = Matrix3x3{ CArray };
	}

	const Matrix3x3 Matrix3x3::operator+(void) const {
		return *this;
	}

	const Matrix3x3 Matrix3x3::operator-(void) const {
		return Matrix3x3{
			-this->m_Mat[0],
			-this->m_Mat[1],
			-this->m_Mat[2]
		};
	}

	const bool Matrix3x3::operator==(const Matrix3x3& R_HS) const {
		for (size_t Row_Index = 0; Row_Index < 3; ++Row_Index)
			if (m_Mat[Row_Index] != R_HS.m_Mat[Row_Index])
				return false;
		return true;
	}

	const bool Matrix3x3::operator!=(const Matrix3x3& R_HS) const {
		return !(*this == R_HS);
	}

	const Matrix3x3 Matrix3x3::operator+(const Matrix3x3& R_HS) const {
		return Matrix3x3{
			this->m_Mat[0] + R_HS.m_Mat[0],
			this->m_Mat[1] + R_HS.m_Mat[1],
			this->m_Mat[2] + R_HS.m_Mat[2]
		};
	}

	const Matrix3x3 Matrix3x3::operator-(const Matrix3x3& RHS) const {
		return Matrix3x3{
			this->m_Mat[0] - RHS.m_Mat[0],
			this->m_Mat[1] - RHS.m_Mat[1],
			this->m_Mat[2] - RHS.m_Mat[2]
		};
	}

	const Matrix3x3 Matrix3x3::operator*(float RHS) const {
		return Matrix3x3{
			this->m_Mat[0] * RHS,
			this->m_Mat[1] * RHS,
			this->m_Mat[2] * RHS
		};
	}

	const Matrix3x3 operator*(float LHS, const Matrix3x3& RHS) {
		return RHS * LHS;
	}

	const Vector3 Matrix3x3::operator*(const Vector3& R_HS) const {
		Vector3 Prod_Vector3{};

		for (size_t Row_Index = 0; Row_Index < 3; ++Row_Index)
			Prod_Vector3[Row_Index] = m_Mat[Row_Index].Dot_Product(R_HS);

		return Prod_Vector3;
	}

	const Vector3 operator*(const Vector3& L_HS, const Matrix3x3& R_HS) {
		return R_HS.Transpose() * L_HS;
	}

	const Matrix3x3 Matrix3x3::operator*(const Matrix3x3& R_HS) const {
		Matrix3x3 Prod_Matrix3x3{};

		for (size_t Row_Index = 0; Row_Index < 3; ++Row_Index)
			for (size_t Column_Index = 0; Column_Index < 3; ++Column_Index)
				Prod_Matrix3x3[Row_Index][Column_Index] = m_Mat[Row_Index].Dot_Product(R_HS.Get_Column(Column_Index));

		return Prod_Matrix3x3;
	}

	const Matrix3x3 Matrix3x3::operator/(float R_HS) const{
		assert(R_HS != 0.f);

		return *this * (1.0f / R_HS);
	}

	Matrix3x3& Matrix3x3::operator+=(const Matrix3x3& R_HS) {
		return (*this) = *this + R_HS;
	}

	Matrix3x3& Matrix3x3::operator-=(const Matrix3x3& R_HS) {
		return (*this) = *this - R_HS;
	}

	Matrix3x3& Matrix3x3::operator*=(float R_HS) {
		return (*this) = *this * R_HS;
	}

	Matrix3x3& Matrix3x3::operator*=(const Matrix3x3& R_HS) {
		return (*this) = *this * R_HS;
	}

	Matrix3x3& Matrix3x3::operator/=(float R_HS){
		return (*this) = *this / R_HS;
	}

	Vector3& Matrix3x3::operator[](size_t Index) {
		assert(Index < 3&&"Index Out Of Range");

		return this->m_Mat[Index];
	}

	const Vector3& Matrix3x3::operator[](size_t Row_Index) const {
		assert(Row_Index < 3 && "Index Out Of Range");

		return this->m_Mat[Row_Index];
	}

	const float Matrix3x3::Trace(void) const {
		return
			this->m_Mat[0][0] +
			this->m_Mat[1][1] +
			this->m_Mat[2][2];
	}

	const Matrix3x3 Matrix3x3::Transpose(void) const {
		Matrix3x3 Transpose_Matrix3x3{};

		for (size_t Row_Index = 0; Row_Index < 3; ++Row_Index)
			for (size_t Column_Index = 0; Column_Index < 3; ++Column_Index)
				Transpose_Matrix3x3[Row_Index][Column_Index] = this->m_Mat[Column_Index][Row_Index];

		return Transpose_Matrix3x3;
	}

	Matrix3x3& Matrix3x3::To_Transpose(void) {
		return (*this) = this->Transpose();
	}

	const float Matrix3x3::Determinant(void) const {
		float cofactor00 = m_Mat[1][1] * m_Mat[2][2] - m_Mat[1][2] * m_Mat[2][1];
		float cofactor10 = m_Mat[1][2] * m_Mat[2][0] - m_Mat[1][0] * m_Mat[2][2];
		float cofactor20 = m_Mat[1][0] * m_Mat[2][1] - m_Mat[1][1] * m_Mat[2][0];

		return  m_Mat[0][0] * cofactor00 + m_Mat[0][1] * cofactor10 + m_Mat[0][2] * cofactor20;

		return m_Mat[0].Dot_Product(m_Mat[1].Cross_Product(m_Mat[2]));
	}

	const Matrix3x3 Matrix3x3::Adjoint(void) const {
		return Matrix3x3{
			this->Minor(0, 0),-this->Minor(1, 0),this->Minor(2, 0),
			-this->Minor(0, 1),this->Minor(1, 1),-this->Minor(2, 1),
			this->Minor(0, 2),-this->Minor(1, 2),this->Minor(2, 2)
		};
	}

	const Matrix3x3 Matrix3x3::Inverse(void) const {
		assert(!this->Is_Singular());

		return Matrix3x3{
			m_Mat[1].Cross_Product(m_Mat[2]) / this->Determinant(),
			m_Mat[2].Cross_Product(m_Mat[0]) / this->Determinant(),
			m_Mat[0].Cross_Product(m_Mat[1]) / this->Determinant()
		}.Transpose();
	}

	Matrix3x3& Matrix3x3::To_Inverse(void) {
		return (*this) = this->Inverse();
	}

	const Matrix3x3 Matrix3x3::Gram_Schmidt(void) const {
		return Matrix3x3{
			(m_Mat[0]).Normalize(),
			(m_Mat[1] - m_Mat[1].Project_Over(m_Mat[0])).Normalize(),
			(m_Mat[2] - m_Mat[2].Project_Over(m_Mat[0]) - m_Mat[2].Project_Over(m_Mat[1])).Normalize()
		};
	}

	Matrix3x3& Matrix3x3::To_Gram_Schmidt(void) {
		return (*this) = this->Gram_Schmidt();
	}

	const float Matrix3x3::Minor(size_t Out_Row, size_t Out_Column) const {
		float Temp_Matirx2x2[2][2]{};

		for (size_t R = 0; R < 3; ++R) {
			for (size_t C = 0; C < 3; ++C)
				if (R == Out_Row || C == Out_Column)
					continue;
				else
					Temp_Matirx2x2[R < Out_Row ? R : R - 1][C < Out_Column ? C : C - 1] = this->m_Mat[R][C];
		}

		return
			(Temp_Matirx2x2[0][0] * Temp_Matirx2x2[1][1] -
				Temp_Matirx2x2[0][1] * Temp_Matirx2x2[1][0])
			* (((Out_Row + Out_Column) % 2 == 0) ? 1.f : -1.f);
	}

	tuple<Matrix3x3, Matrix3x3, Matrix3x3> Matrix3x3::Calculate_QDU_Decomposition(void) const {
		Matrix3x3 Q{ this->Gram_Schmidt() }, R{ Q.Transpose() * (*this) }, D{ Matrix3x3::ZERO }, U{ Matrix3x3::ZERO };

		for (size_t Index = 0; Index < 3; ++Index) {
			D[Index][Index] = R[Index][Index];
			U[Index][Index] = 1.0f;
		}

		for (size_t Row_Index = 0; Row_Index < 3; ++Row_Index)
			for (size_t Column_Index = Row_Index + 1; Column_Index < 3; ++Column_Index)
				U[Row_Index][Column_Index] = R[Row_Index][Column_Index];

		return { Q,D,U };
	}

	const Vector3 Matrix3x3::Get_Row(size_t Row_Index) const {
		return this->m_Mat[Row_Index];
	}

	const Vector3 Matrix3x3::Get_Column(size_t Column_Index)const {
		return Vector3{
			this->m_Mat[0][Column_Index],
			this->m_Mat[1][Column_Index],
			this->m_Mat[2][Column_Index]
		};
	}

	void Matrix3x3::Set_Row(size_t Row_Index, const Vector3& Temp_Vector3) {
		m_Mat[Row_Index] = Temp_Vector3;
	}

	void Matrix3x3::Set_Row(size_t Row_Index, float Scale) {
		m_Mat[Row_Index] = Vector3{ Scale };
	}

	void Matrix3x3::Set_Row(size_t Row_Index, float X, float Y, float Z) {
		m_Mat[Row_Index] = Vector3{ X,Y,Z };
	}

	void Matrix3x3::Set_Column(size_t Column_Index, const Vector3& R_Temp_Vector3) {
		for (size_t Row_Index = 0; Row_Index < 3; ++Row_Index)
			m_Mat[Row_Index][Column_Index] = R_Temp_Vector3[Row_Index];
	}

	void Matrix3x3::Set_Column(size_t Column_Index, float Scale) {
		this->Set_Column(Column_Index, Scale, Scale, Scale);
	}

	void Matrix3x3::Set_Column(size_t Column_Index, float X, float Y, float Z) {
		this->Set_Column(Column_Index, Vector3{ X,Y,Z });
	}

	const bool Matrix3x3::Is_Singular(void) const {
		return NameSpace_Utilities::Real_Equal(this->Determinant(), 0.f);
	}

	const Matrix3x3 Matrix3x3::Generate_Column_Order(const Vector3& Column_0, const Vector3& Column_1, const Vector3& Column_2) {
		return Matrix3x3{ Column_0,Column_1,Column_2 }.Transpose();
	}

	const Matrix3x3 Matrix3x3::Generate_Column_Order(const initializer_list<float>& List) {
		return Matrix3x3{ List }.Transpose();
	}

	const Matrix3x3 Matrix3x3::Generate_Column_Order(const Vector3 CArrays[3]) {
		return Matrix3x3{ CArrays }.Transpose();
	}

	const Matrix3x3 Matrix3x3::Generate_Column_Order(const float CArray[3][3]) {
		return Matrix3x3{ CArray }.Transpose();
	}

	const Matrix3x3 Matrix3x3::Generate_Column_Order(const float Carrays[9]) {
		return Matrix3x3{ Carrays }.Transpose();
	}

	const Matrix3x3 Matrix3x3::ZERO{};
	const Matrix3x3 Matrix3x3::IDENTITY{ Vector3::UNIT_X,Vector3::UNIT_Y,Vector3::UNIT_Z };

}// namespace NameSpace_Core::NameSpace_Math