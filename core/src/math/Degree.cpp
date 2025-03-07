#include "math/Degree.h"

#include "math/Radian.h"
#include "math/Constant.h"
#include "math/Utilities.h"

namespace NameSpace_Core::NameSpace_Math {

	Degree::Degree(float Value) :
		m_Degree{ Value } {
	}

	Degree& Degree::operator=(float Value) {
		this->m_Degree = Value;
		return *this;
	}

	Degree::operator Radian(void) const {
		return Radian{ this->m_Degree * Math_PI_DIV_180 };
	}

	const Degree Degree::operator+(void) const {
		return *this;
	}

	const Degree Degree::operator-(void) const {
		return Degree{ -this->m_Degree };
	}

	const Degree Degree::operator+(float R_HS) const {
		return Degree{ this->m_Degree + R_HS };
	}

	const Degree Degree::operator+(const Degree& R_HS) const {
		return (*this) + R_HS.m_Degree;
	}

	const bool Degree::operator==(const Degree& R_HS) const {
		return NameSpace_Utilities::Real_Equal(this->m_Degree, R_HS.m_Degree);
	}

	const bool Degree::operator!=(const Degree& R_HS) const {
		return !(*this == R_HS);
	}

	const bool Degree::operator<(const Degree& R_HS) const {
		return this->m_Degree < R_HS.m_Degree;
	}

	const bool Degree::operator>(const Degree& R_HS) const {
		return this->m_Degree > R_HS.m_Degree;
	}

	const bool Degree::operator<=(const Degree& R_HS) const {
		return !(*this > R_HS);
	}

	const bool Degree::operator>=(const Degree& R_HS) const {
		return !(*this < R_HS);
	}

	const Degree operator+(float L_HS, const Degree& R_HS) {
		return R_HS + L_HS;
	}

	const Degree Degree::operator-(float R_HS) const {
		return Degree{ this->m_Degree - R_HS };
	}

	const Degree Degree::operator-(const Degree& R_HS) const {
		return (*this) - R_HS.m_Degree;
	}

	const Degree operator-(float L_HS, const Degree& R_HS) {
		return Degree{ L_HS - R_HS.m_Degree };
	}

	const Degree Degree::operator*(float R_HS) const {
		return Degree{ this->m_Degree * R_HS };
	}

	const Degree Degree::operator*(const Degree& R_HS) const {
		return (*this) * R_HS.m_Degree;
	}

	const Degree operator*(float L_HS, const Degree& R_HS) {
		return R_HS * L_HS;
	}

	const Degree Degree::operator/(float R_HS) const {
		return Degree{ this->m_Degree / R_HS };
	}

	const Degree Degree::operator/(const Degree& R_HS) const {
		return (*this) / R_HS.m_Degree;
	}

	const Degree operator/(float L_HS, const Degree& R_HS) {
		return Degree{ L_HS / R_HS.m_Degree };
	}

	Degree& Degree::operator+=(const Degree& R_HS) {
		return *this = *this + R_HS;
	}

	Degree& Degree::operator-=(const Degree& R_HS) {
		return *this = *this - R_HS;
	}

	Degree& Degree::operator*=(float R_HS) {
		return *this = (*this) * R_HS;
	}

	Degree& Degree::operator/=(float R_HS) {
		return *this = (*this) / R_HS;
	}

	const bool Degree::Is_NaN(void) const {
		return NameSpace_Utilities::Is_NaN(this->m_Degree);
	}

	const bool Degree::Is_Infinity(void) const {
		return NameSpace_Utilities::Is_Infinity(this->m_Degree);
	}

	const float Degree::Get_Degree(void) const {
		return this->m_Degree;
	}

}// namespace NameSpace_Core::NameSpace_Math