#include "math/Vector3.h"

#include<cassert>

#include "math/Utilities.h"

namespace NameSpace_Core::NameSpace_Math {

	Vector3::Vector3(float Scalar)
		:Vector3{ Scalar, Scalar, Scalar } {
	}

	Vector3::Vector3(float X, float Y, float Z) :
		m_X{ X },
		m_Y{ Y },
		m_Z{ Z } {
	}

	Vector3& Vector3::operator=(float Scalar) {
		return *this = Vector3{ Scalar };
	}

	const Vector3 Vector3::operator+(void) const {
		return *this;
	}

	const Vector3 Vector3::operator-(void) const {
		return Vector3{
			-this->m_X,
			-this->m_Y,
			-this->m_Z
		};
	}

	const bool Vector3::operator==(const Vector3& R_HS) const {
		return
			NameSpace_Utilities::Real_Equal(this->m_X, R_HS.m_X) &&
			NameSpace_Utilities::Real_Equal(this->m_Y, R_HS.m_Y) &&
			NameSpace_Utilities::Real_Equal(this->m_Z, R_HS.m_Z);
	}

	const bool Vector3::operator!=(const Vector3& R_HS) const {
		return !(*this == R_HS);
	}

	const bool Vector3::operator<(const Vector3& R_HS) const {
		return
			this->m_X < R_HS.m_X &&
			this->m_Y < R_HS.m_Y &&
			this->m_Z < R_HS.m_Z;
	}

	const bool Vector3::operator>(const Vector3& R_HS) const {
		return
			this->m_X > R_HS.m_X &&
			this->m_Y > R_HS.m_Y &&
			this->m_Z > R_HS.m_Z;
	}

	const bool Vector3::operator<=(const Vector3& R_HS) const {
		return !((*this) > R_HS);
	}

	const bool Vector3::operator>=(const Vector3& R_HS) const {
		return !((*this) < R_HS);
	}

	const Vector3 Vector3::operator+(const Vector3& R_HS) const {
		return Vector3{
			this->m_X + R_HS.m_X,
			this->m_Y + R_HS.m_Y,
			this->m_Z + R_HS.m_Z
		};
	}

	const Vector3 Vector3::operator+(float R_HS) const {
		return (*this) + Vector3{ R_HS };
	}

	const Vector3 operator+(float L_HS, const Vector3& R_HS) {
		return R_HS + L_HS;
	}

	const Vector3 Vector3::operator-(const Vector3& R_HS) const {
		return Vector3{
			this->m_X - R_HS.m_X,
			this->m_Y - R_HS.m_Y,
			this->m_Z - R_HS.m_Z
		};
	}

	const Vector3 Vector3::operator-(float R_HS) const {
		return (*this) - Vector3{ R_HS };
	}

	const Vector3 operator-(float L_HS, const Vector3& R_HS) {
		return Vector3{ L_HS } - R_HS;
	}

	const Vector3 Vector3::operator*(const Vector3& R_HS) const {
		return Vector3{
			this->m_X * R_HS.m_X,
			this->m_Y * R_HS.m_Y,
			this->m_Z * R_HS.m_Z
		};
	}

	const Vector3 Vector3::operator*(float R_HS) const {
		return (*this) * Vector3 { R_HS };
	}

	const Vector3 operator*(float L_HS, const Vector3& R_HS) {
		return R_HS * L_HS;
	}

	const Vector3 Vector3::operator/(const Vector3& R_HS) const {
		return Vector3{
			this->m_X / R_HS.m_X,
			this->m_Y / R_HS.m_Y,
			this->m_Z / R_HS.m_Z
		};
	}

	const Vector3 Vector3::operator/(float R_HS) const {
		return (*this) / Vector3{ R_HS };
	}

	const Vector3 operator/(float L_HS, const Vector3& R_HS) {
		return Vector3{ L_HS } / R_HS;
	}

	Vector3& Vector3::operator+=(const Vector3& R_HS) {
		return *this = *this + R_HS;
	}

	Vector3& Vector3::operator+=(float R_HS) {
		return *this = *this + R_HS;
	}

	Vector3& Vector3::operator-=(const Vector3& R_HS) {
		return *this = *this - R_HS;
	}

	Vector3& Vector3::operator-=(float R_HS) {
		return *this = *this - R_HS;
	}

	Vector3& Vector3::operator*=(const Vector3& R_HS) {
		return *this = *this * R_HS;
	}

	Vector3& Vector3::operator*=(float R_HS) {
		return *this = *this * R_HS;
	}

	Vector3& Vector3::operator/=(const Vector3& R_HS) {
		return *this = *this / R_HS;
	}

	Vector3& Vector3::operator/=(float R_HS) {
		return *this = *this / R_HS;
	}

	const float& Vector3::operator[](size_t Index) const {
		return *(&this->m_X + Index);
	}

	float& Vector3::operator[](size_t Index) {
		return *(&this->m_X + Index);
	}

	const float Vector3::Length(void) const {
		return NameSpace_Utilities::Hypot(this->m_X, this->m_Y, this->m_Z);
	}

	const float Vector3::Length_Square(void) const {
		return
			this->m_X * this->m_X +
			this->m_Y * this->m_Y +
			this->m_Z * this->m_Z;
	}

	const float Vector3::Distance(const Vector3& R_HS) const {
		return ((*this) - R_HS).Length();
	}

	const float Vector3::Distance_Square(const Vector3& R_HS) const {
		return ((*this) - R_HS).Length_Square();
	}

	const float Vector3::Dot_Product(const Vector3& R_HS) const {
		return
			this->m_X * R_HS.m_X +
			this->m_Y * R_HS.m_Y +
			this->m_Z * R_HS.m_Z;
	}

	const Vector3 Vector3::Cross_Product(const Vector3& R_HS) const {
		return Vector3{
			this->m_Y * R_HS.m_Z - this->m_Z * R_HS.m_Y,
			this->m_Z * R_HS.m_X - this->m_X * R_HS.m_Z,
			this->m_X * R_HS.m_Y - this->m_Y * R_HS.m_X
		};
	}

	const Vector3 Vector3::Normalize(void) const {
		assert(!NameSpace_Utilities::Real_Equal(this->Length(), 0.f) && "Vector3 Is Zero");

		return (*this) * (1.0f / this->Length());
	}

	Vector3& Vector3::To_Normalized(void) {
		return *this = this->Normalize();
	}

	const Vector3 Vector3::Project_Over(const Vector3& Not_Zeor_Other) const {
		assert(!NameSpace_Utilities::Real_Equal(Not_Zeor_Other.Length(), 0.f));

		return Not_Zeor_Other * (this->Dot_Product(Not_Zeor_Other) / Not_Zeor_Other.Length_Square());
	}

	const Vector3 Vector3::Reflect(const Vector3& Normal) const {
		return *this - Normal * (2.0f * this->Dot_Product(Normal));
	}

	const Vector3 Vector3::Ceil(void) const {
		return Vector3{
			NameSpace_Utilities::Ceil(this->m_X),
			NameSpace_Utilities::Ceil(this->m_Y),
			NameSpace_Utilities::Ceil(this->m_Z)
		};
	}

	const Vector3 Vector3::Floor(void) const {
		return Vector3{
			NameSpace_Utilities::Floor(this->m_X),
			NameSpace_Utilities::Floor(this->m_Y),
			NameSpace_Utilities::Floor(this->m_Z)
		};
	}

	const Radian Vector3::Angle_Between(const Vector3& R_HS) const {
		assert(*this != Vector3::ZERO && R_HS != Vector3::ZERO);

		return NameSpace_Utilities::Acos(this->Dot_Product(R_HS) / (this->Length() * R_HS.Length()));
	}

	const Vector3 Vector3::Middle_Point(const Vector3& R_HS) {
		return Vector3{
			this->m_X * 0.5f + R_HS.m_X * 0.5f,
			this->m_Y * 0.5f + R_HS.m_Y * 0.5f,
			this->m_Z * 0.5f + R_HS.m_Z * 0.5f
		};
	}

	const float Vector3::Get_X(void) const {
		return this->m_X;
	}

	const float Vector3::Get_Y(void) const {
		return this->m_Y;
	}

	const float Vector3::Get_Z(void) const {
		return this->m_Z;
	}

	void Vector3::Set_X(float X) {
		this->m_X = X;
	}

	void Vector3::Set_Y(float Y) {
		this->m_Y = Y;
	}

	void Vector3::Set_Z(float Z) {
		this->m_Z = Z;
	}

	const bool Vector3::Is_NaN(void) const {
		return
			NameSpace_Utilities::Is_NaN(this->m_X) ||
			NameSpace_Utilities::Is_NaN(this->m_Y) ||
			NameSpace_Utilities::Is_NaN(this->m_Z);
	}

	const bool Vector3::Is_Unit(void) const {
		return   NameSpace_Utilities::Real_Equal(this->Length_Square(), 1.f);
	}

	const Vector3 Vector3::ZERO{};
	const Vector3 Vector3::ONE{ 1.f };
	const Vector3 Vector3::UNIT_X{ 1.f, 0.f, 0.f };
	const Vector3 Vector3::UNIT_Y{ 0.f, 1.f, 0.f };
	const Vector3 Vector3::UNIT_Z{ 0.f, 0.f, 1.f };

}// namespace NameSpace_Core::NameSpace_Math