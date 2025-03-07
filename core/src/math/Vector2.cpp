#include "math/Vector2.h"

#include<cassert>

#include "math/Utilities.h"

namespace NameSpace_Core::NameSpace_Math {

	Vector2::Vector2(float Scalar)
		:Vector2{ Scalar, Scalar } {
	}

	Vector2::Vector2(float X, float Y) :
		m_X{ X },
		m_Y{ Y } {
	}

	Vector2& Vector2::operator=(float Scalar) {
		return *this = Vector2{ Scalar };
	}

	const Vector2 Vector2::operator+(void) const {
		return *this;
	}

	const Vector2 Vector2::operator-(void) const {
		return Vector2{
			-this->m_X,
			-this->m_Y
		};
	}

	const bool Vector2::operator==(const Vector2& R_HS) const {
		return
			NameSpace_Utilities::Real_Equal(this->m_X, R_HS.m_X) &&
			NameSpace_Utilities::Real_Equal(this->m_Y, R_HS.m_Y);
	}

	const bool Vector2::operator!=(const Vector2& R_HS) const {
		return !(*this == R_HS);
	}

	const bool Vector2::operator<(const Vector2& R_HS) const {
		return
			this->m_X < R_HS.m_X &&
			this->m_Y < R_HS.m_Y;
	}

	const bool Vector2::operator>(const Vector2& R_HS) const {
		return
			this->m_X > R_HS.m_X &&
			this->m_Y > R_HS.m_Y;
	}

	const bool Vector2::operator<=(const Vector2& R_HS) const {
		return !((*this) > R_HS);
	}

	const bool Vector2::operator>=(const Vector2& R_HS) const {
		return !((*this) < R_HS);
	}

	const Vector2 Vector2::operator+(const Vector2& R_HS) const {
		return Vector2{
			this->m_X + R_HS.m_X,
			this->m_Y + R_HS.m_Y
		};
	}

	const Vector2 Vector2::operator+(float R_HS) const {
		return (*this) + Vector2{ R_HS };
	}

	const Vector2 operator+(float L_HS, const Vector2& R_HS) {
		return   R_HS + L_HS;
	}

	const Vector2 Vector2::operator-(const Vector2& R_HS) const {
		return Vector2{
			this->m_X - R_HS.m_X,
			this->m_Y - R_HS.m_Y
		};
	}

	const Vector2 Vector2::operator-(float R_HS) const {
		return (*this) - Vector2{ R_HS };
	}

	const Vector2 operator-(float L_HS, const Vector2& R_HS) {
		return Vector2{ L_HS } - R_HS;
	}

	const Vector2 Vector2::operator*(const Vector2& R_HS) const {
		return Vector2{
			this->m_X * R_HS.m_X,
			this->m_Y * R_HS.m_Y
		};
	}

	const Vector2 Vector2::operator*(float R_HS) const {
		return (*this) * Vector2 { R_HS };
	}

	const Vector2 operator*(float L_HS, const Vector2& R_HS) {
		return R_HS * L_HS;
	}

	const Vector2 Vector2::operator/(const Vector2& R_HS) const {
		return Vector2{
			this->m_X / R_HS.m_X,
			this->m_Y / R_HS.m_Y
		};
	}

	const Vector2 Vector2::operator/(float R_HS) const {
		return (*this) / Vector2{ R_HS };
	}

	const Vector2 operator/(float L_HS, const Vector2& R_HS) {
		return Vector2{ L_HS } / R_HS;
	}

	Vector2& Vector2::operator+=(const Vector2& R_HS) {
		return *this = *this + R_HS;
	}

	Vector2& Vector2::operator+=(float R_HS) {
		return (*this) = (*this) + R_HS;
	}

	Vector2& Vector2::operator-=(const Vector2& R_HS) {
		return *this = *this - R_HS;
	}

	Vector2& Vector2::operator-=(float R_HS) {
		return (*this) = (*this) - R_HS;
	}

	Vector2& Vector2::operator*=(const Vector2& R_HS) {
		return (*this) = (*this) * R_HS;
	}

	Vector2& Vector2::operator*=(float R_HS) {
		return (*this) = (*this) * R_HS;
	}

	Vector2& Vector2::operator/=(const Vector2& R_HS) {
		return (*this) = (*this) / R_HS;
	}

	Vector2& Vector2::operator/=(float R_HS) {
		return (*this) = (*this) / R_HS;
	}

	float& Vector2::operator[](size_t Index) {
		return *(&this->m_X + Index);
	}

	const float& Vector2::operator[](size_t Index) const {
		return *(&this->m_X + Index);
	}

	const float Vector2::Length(void) const {
		return NameSpace_Utilities::Hypot(this->m_X, this->m_Y);
	}

	const float Vector2::Length_Square(void) const {
		return this->m_X * this->m_X + this->m_Y * this->m_Y;
	}

	const float Vector2::Distance(const Vector2& R_HS) const {
		return (*this - R_HS).Length();
	}

	const float Vector2::Distance_Square(const Vector2& R_HS) const {
		return (*this - R_HS).Length_Square();
	}

	const float Vector2::Dot_Product(const Vector2& R_HS) const {
		return this->m_X * R_HS.m_X + this->m_Y * R_HS.m_Y;
	}

	const float Vector2::Cross_Product(const Vector2& R_HS) const {
		return
			this->m_X * R_HS.m_Y -
			this->m_Y * R_HS.m_X;
	}

	const Vector2 Vector2::Normalize(void) const {
		assert((!NameSpace_Utilities::Real_Equal(this->Length(), 0.f)) && ("Vector3 Is Zero"));

		return (*this) * (1.f / this->Length());
	}

	Vector2& Vector2::To_Normalized(void) {
		return *this = this->Normalize();
	}

	const Vector2 Vector2::Project_Over(const Vector2& Not_Zero_Other) const {
		assert(!NameSpace_Utilities::Real_Equal(Not_Zero_Other.Length(), 0.f));

		return Not_Zero_Other * (this->Dot_Product(Not_Zero_Other) / Not_Zero_Other.Length_Square());
	}

	const Vector2 Vector2::Reflect(const Vector2& Normal) const {
		assert(Normal.Is_Unit());

		return *this - Normal * (2.f * this->Dot_Product(Normal));
	}

	const Radian Vector2::Angle_Between(const Vector2& R_HS) const {
		return Radian{ NameSpace_Utilities::Acos(this->Dot_Product(R_HS) / (this->Length() * R_HS.Length())) };
	}

	const Vector2 Vector2::Perpendicular(void) const {
		return Vector2{
			-this->m_Y,
			this->m_X
		};
	}

	const Vector2 Vector2::Ceil(void) const {
		return Vector2{
			NameSpace_Utilities::Ceil(this->m_X),
			NameSpace_Utilities::Ceil(this->m_Y)
		};

	}

	const Vector2 Vector2::Floor(void) const {
		return Vector2{
			NameSpace_Utilities::Floor(this->m_X),
			NameSpace_Utilities::Floor(this->m_Y)
		};
	}

	const Vector2 Vector2::Middle_Point(const Vector2& R_HS) const {
		return Vector2{
			this->m_X * 0.5f + R_HS.m_X * 0.5f,
			this->m_Y * 0.5f + R_HS.m_Y * 0.5f
		};
	}

	const float Vector2::Get_X(void) const {
		return this->m_X;
	}

	const float Vector2::Get_Y(void) const {
		return this->m_Y;
	}

	void Vector2::Set_X(float X) {
		this->m_X = X;
	}

	void Vector2::Set_Y(float Y) {
		this->m_Y = Y;
	}

	const bool Vector2::Is_NaN(void) const {
		return NameSpace_Utilities::Is_NaN(this->m_X) ||
			NameSpace_Utilities::Is_NaN(this->m_Y);
	}

	const bool Vector2::Is_Unit(void) const {
		return NameSpace_Utilities::Real_Equal(this->Length(), 1.f);
	}

	const Vector2 Vector2::ZERO{};
	const Vector2 Vector2::ONE{ 1.f };
	const Vector2 Vector2::UNIT_X{ 1.f,0.f };
	const Vector2 Vector2::UNIT_Y{ 0.f,1.f };

}// namespace NameSpace_Core::NameSpace_Math