#include "math/Degree.h"

#include<cassert>

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

    bool Degree::operator==(const Degree& R_HS) const {
        return NameSpace_Utilities::Real_Equal(this->m_Degree, R_HS.m_Degree);
    }

    bool Degree::operator!=(const Degree& R_HS) const {
        return !(*this == R_HS);
    }

    bool Degree::operator<(const Degree& R_HS) const {
        return this->m_Degree < R_HS.m_Degree;
    }

    bool Degree::operator>(const Degree& R_HS) const {
        return this->m_Degree > R_HS.m_Degree;
    }

    bool Degree::operator<=(const Degree& R_HS) const {
        return !(*this > R_HS);
    }

    bool Degree::operator>=(const Degree& R_HS) const {
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
        assert(!NameSpace_Utilities::Real_Equal(R_HS, 0.f));
        return Degree{ this->m_Degree / R_HS };
    }

    const Degree Degree::operator/(const Degree& R_HS) const {
        assert(R_HS != Degree{ 0.f });
        return (*this) / R_HS.m_Degree;
    }

    const Degree operator/(float L_HS, const Degree& R_HS) {
        assert(R_HS != Degree{ 0.f });
        return Degree{ L_HS / R_HS.m_Degree };
    }

    Degree& Degree::operator+=(const Degree& R_HS) {
        return *this = *this + R_HS;
    }

    Degree& Degree::operator+=(float R_HS) {
        return *this = *this + R_HS;
    }

    Degree& Degree::operator-=(const Degree& R_HS) {
        return *this = *this - R_HS;
    }

    Degree& Degree::operator-=(float R_HS) {
        return *this = *this - R_HS;
    }

    Degree& Degree::operator*=(const Degree& R_HS) {
        return *this = (*this) * R_HS;
    }

    Degree& Degree::operator*=(float R_HS) {
        return *this = (*this) * R_HS;
    }

    Degree& Degree::operator/=(const Degree& R_HS) {
        return *this = (*this) / R_HS;
    }

    Degree& Degree::operator/=(float R_HS) {
        return *this = (*this) / R_HS;
    }

    bool Degree::Is_NaN(void) const {
        return NameSpace_Utilities::Is_NaN(this->m_Degree);
    }

    bool Degree::Is_Infinity(void) const {
        return NameSpace_Utilities::Is_Infinity(this->m_Degree);
    }

    float Degree::Get_Degree(void) const {
        return this->m_Degree;
    }

}// namespace NameSpace_Core::NameSpace_Math