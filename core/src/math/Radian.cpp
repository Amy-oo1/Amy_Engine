#include "math/Radian.h"

#include "math/Degree.h"
#include "math/Constant.h"
#include "math/Utilities.h"

namespace NameSpace_Core::NameSpace_Math {

	Radian::Radian(float Value) :
		m_Radian{ Value } {
	}

	Radian& Radian::operator=(float Value) {
		this->m_Radian = Value;
		return *this;
	}

	Radian::operator Degree(void) const {
		return Degree{ this->m_Radian * Math_180_DIV_PI };
	}

	const Radian Radian::operator+(void) const {
		return *this;
	}

	const Radian Radian::operator-(void) const {
		return Radian{ -this->m_Radian };
	}

	const bool Radian::operator==(const Radian& R_HS) const {
		return NameSpace_Utilities::Real_Equal(this->m_Radian, R_HS.m_Radian);
	}

	const bool Radian::operator!=(const Radian& R_HS) const {
		return  !(*this == R_HS);
	}

	const bool Radian::operator<(const Radian& R_HS) const {
		return this->m_Radian < R_HS.m_Radian;
	}

	const bool Radian::operator>(const Radian& R_HS) const {
		return this->m_Radian > R_HS.m_Radian;
	}

	const bool Radian::operator<=(const Radian& R_HS) const {
		return !(*this > R_HS);
	}

	const bool Radian::operator>=(const Radian& R_HS) const {
		return !(*this < R_HS);
	}

	const Radian Radian::operator+(float R_HS) const {
		return Radian{ this->m_Radian + R_HS };
	}

	const Radian Radian::operator+(const Radian& R_HS) const {
		return (*this) + R_HS.m_Radian;
	}

	const Radian operator+(float L_HS, const Radian& R_HS) {
		return  R_HS + L_HS;
	}

	const Radian Radian::operator-(float R_HS) const {
		return Radian{ this->m_Radian - R_HS };
	}

	const Radian Radian::operator-(const Radian& R_HS) const {
		return (*this) - R_HS.m_Radian;
	}

	const Radian operator-(float L_HS, const Radian& R_HS) {
		return Radian{ L_HS - R_HS.m_Radian };
	}

	const Radian Radian::operator*(float R_HS) const {
		return Radian{ this->m_Radian * R_HS };
	}

	const Radian Radian::operator*(const Radian& R_HS) const {
		return (*this) * R_HS.m_Radian;
	}

	const Radian operator*(float L_HS, const Radian& R_HS) {
		return R_HS * L_HS;
	}

	const Radian Radian::operator/(float R_HS) const {
		return Radian{ this->m_Radian / R_HS };
	}

	const Radian Radian::operator/(const Radian& R_HS) const {
		return (*this) / R_HS.m_Radian;
	}

	const Radian operator/(float L_HS, const Radian& R_HS) {
		return Radian{ L_HS / R_HS.m_Radian };
	}

	Radian& Radian::operator+=(const Radian& R_HS) {
		return *this = *this + R_HS;
	}

	Radian& Radian::operator-=(const Radian& R_HS) {
		return *this = *this - R_HS;
	}

	Radian& Radian::operator*=(float R_HS) {
		return *this = (*this) * R_HS;
	}

	Radian& Radian::operator/=(float R_HS) {
		return	*this = (*this) / R_HS;
	}

	const bool Radian::Is_NaN(void) const {
		return NameSpace_Utilities::Is_NaN(this->m_Radian);
	}

	const bool Radian::Is_Infinity(void) const {
		return NameSpace_Utilities::Is_Infinity(this->m_Radian);
	}

	const float Radian::Get_Radian(void) const {
		return this->m_Radian;
	}

	const Radian Radian::ZERO{ 0.f };
	const Radian Radian::PI{ Math_PI };

}// namespace NameSpace_Core::NameSpace_Math