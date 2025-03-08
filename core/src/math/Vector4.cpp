#include "math/Vector4.h"

#include<cassert>

#include "math/Utilities.h"

namespace NameSpace_Core::NameSpace_Math {

	Vector4::Vector4(float Scalar) :
		Vector4{ Scalar,Scalar,Scalar,Scalar } {
	}

	Vector4::Vector4(float X, float Y, float Z, float W) :
		m_X{ X },
		m_Y{ Y },
		m_Z{ Z },
		m_W{ W } {
	}

	Vector4::Vector4(const Vector3& XYZ, float W) :
		Vector4{ XYZ.Get_X(),XYZ.Get_Y(),XYZ.Get_Z(),W } {
	}

	Vector4& Vector4::operator=(float R_HS) {
		return *this = Vector4{ R_HS };
	}

	const Vector4 Vector4::operator+(void) const {
		return *this;
	}

	const Vector4 Vector4::operator-(void) const {
		return Vector4{
			-this->m_X,
			-this->m_Y,
			-this->m_Z,
			-this->m_W
		};
	}

	const bool Vector4::operator==(const Vector4& R_HS) const {
		return
			NameSpace_Utilities::Real_Equal(this->m_X, R_HS.m_X) &&
			NameSpace_Utilities::Real_Equal(this->m_Y, R_HS.m_Y) &&
			NameSpace_Utilities::Real_Equal(this->m_Z, R_HS.m_Z) &&
			NameSpace_Utilities::Real_Equal(this->m_W, R_HS.m_W);
	}

	const bool Vector4::operator!=(const Vector4& R_HS) const {
		return !(*this == R_HS);
	}

	const Vector4 Vector4::operator+(const Vector4& R_HS) const {
		return Vector4{
			this->m_X + R_HS.m_X,
			this->m_Y + R_HS.m_Y,
			this->m_Z + R_HS.m_Z,
			this->m_W + R_HS.m_W
		};
	}

	const Vector4 Vector4::operator+(float R_HS) const {
		return *this + Vector4{ R_HS };
	}

	const Vector4 operator+(float L_SH, const Vector4& R_HS) {
		return R_HS + L_SH;
	}

	const Vector4 Vector4::operator-(const Vector4& R_HS) const {
		return Vector4{
			this->m_X - R_HS.m_X,
			this->m_Y - R_HS.m_Y,
			this->m_Z - R_HS.m_Z,
			this->m_W - R_HS.m_W
		};

	}

	const Vector4 Vector4::operator-(float R_HS) const {
		return *this - Vector4{ R_HS };
	}

	const Vector4 operator-(float L_SH, const Vector4& R_HS) {
		return Vector4{ L_SH } - R_HS;
	}

	const Vector4 Vector4::operator*(const Vector4& R_HS) const {
		return Vector4{
			this->m_X * R_HS.m_X,
			this->m_Y * R_HS.m_Y,
			this->m_Z * R_HS.m_Z,
			this->m_W * R_HS.m_W
		};
	}

	const Vector4 Vector4::operator*(float R_HS) const {
		return *this * Vector4{ R_HS };
	}

	const Vector4 operator*(float L_SH, const Vector4& R_HS) {
		return R_HS * L_SH;
	}

	const Vector4 Vector4::operator/(const Vector4& R_HS) const {
		assert(R_HS != Vector4::ZERO);

		return Vector4{
			this->m_X / R_HS.m_X,
			this->m_Y / R_HS.m_Y,
			this->m_Z / R_HS.m_Z,
			this->m_W / R_HS.m_W
		};
	}

	const Vector4 Vector4::operator/(float R_HS) const {
		return *this / Vector4{ R_HS };
	}

	const Vector4 operator/(float L_SH, const Vector4& R_HS) {
		return Vector4{ L_SH } / R_HS;
	}

	Vector4& Vector4::operator+=(const Vector4& R_HS) {
		return *this = *this + R_HS;
	}

	Vector4& Vector4::operator+=(float R_HS) {
		return *this = *this + R_HS;
	}

	Vector4& Vector4::operator-=(const Vector4& R_HS) {
		return *this = *this - R_HS;
	}

	Vector4& Vector4::operator-=(float R_HS) {
		return *this = *this - R_HS;
	}

	Vector4& Vector4::operator*=(const Vector4& R_HS) {
		return *this = *this * R_HS;
	}

	Vector4& Vector4::operator*=(float R_HS) {
		return *this = *this * R_HS;
	}

	Vector4& Vector4::operator/=(const Vector4& R_HS) {
		return *this = *this / R_HS;
	}

	Vector4& Vector4::operator/=(float R_HS) {
		return *this = *this / R_HS;
	}

	const float& Vector4::operator[](size_t Index) const {
		return *(&this->m_X + Index);
	}

	float& Vector4::operator[](size_t Index) {
		return *(&this->m_X + Index);
	}

	const float Vector4::Get_X(void) const {
		return this->m_X;
	}

	const float Vector4::Get_Y(void) const {
		return this->m_Y;
	}

	const float Vector4::Get_Z(void) const {
		return this->m_Z;
	}

	const float Vector4::Get_W(void) const {
		return this->m_W;
	}

	const Vector3 Vector4::Get_XYZ(void) const {
		return Vector3{
			this->m_X,
			this->m_Y,
			this->m_Z
		};
	}

	void Vector4::Set_X(float X) {
		this->m_X = X;
	}

	void Vector4::Set_Y(float Y) {
		this->m_Y = Y;
	}

	void Vector4::Set_Z(float Z) {
		this->m_Z = Z;
	}

	void Vector4::Set_W(float W) {
		this->m_W = W;
	}

	void Vector4::Set_XYZ(const Vector3& XYZ) {
		this->m_X = XYZ.Get_X();
		this->m_Y = XYZ.Get_Y();
		this->m_Z = XYZ.Get_Z();
	}

	const bool Vector4::Is_NaN(void) const {
		return
			NameSpace_Utilities::Is_NaN(this->m_X) ||
			NameSpace_Utilities::Is_NaN(this->m_Y) ||
			NameSpace_Utilities::Is_NaN(this->m_Z) ||
			NameSpace_Utilities::Is_NaN(this->m_W);
	}

	const float Vector4::Dot_Product(const Vector4& R_HS) const {
		return
			this->m_X * R_HS.m_X +
			this->m_Y * R_HS.m_Y +
			this->m_Z * R_HS.m_Z +
			this->m_W * R_HS.m_W;
	}

	const Vector3 Vector4::Homogeneous(void) const {
		assert(!NameSpace_Utilities::Real_Equal(this->m_W, 0.f));

		return this->Get_XYZ() / this->m_W;
	}

	const Vector4 Vector4::ZERO{};
	const Vector4 Vector4::ONE{ 1.f };
	const Vector4 Vector4::UNIT_X{ Vector3::UNIT_X,0.f };
	const Vector4 Vector4::UNIT_Y{ Vector3::UNIT_Y,0.f };
	const Vector4 Vector4::UNIT_Z{ Vector3::UNIT_Z,0.f };
	const Vector4 Vector4::UNIT_W{ Vector3::ZERO  ,1.f };

}// namespace NameSpace_Core::NameSpace_Math