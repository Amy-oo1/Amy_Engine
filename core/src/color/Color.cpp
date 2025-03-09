#include "color/Color.h"

#include<cassert>

namespace NameSpace_Core::NameSpace_Color {

	Color::Color(const Vector4& color)
		:m_Color{ color } {
	}

	Color::Color(float red, float green, float blue, float alpha)
		:m_Color{ red,green,blue,alpha } {
	}

	Color& Color::operator=(const Vector4& Val) {
		this->m_Color = Val;
		return *this;
	}

	Color::operator Vector4(void) const {
		return this->m_Color;
	}

	bool Color::operator==(const Color& other) const {
		return this->m_Color == other.m_Color;
	}

	bool Color::operator!=(const Color& other) const {
		return this->m_Color != other.m_Color;
	}

	const Color Color::operator*(float scalar) const {
		return Color{ this->m_Color * scalar };
	}

	const Color operator*(float scalar, const Color& color) {
		return color * scalar;
	}

	Color& Color::operator*=(float scalar) {
		return *this = *this * scalar;
	}

	float& Color::operator[](size_t index) {
		assert(index < 4);

		return this->m_Color[index];
	}

	const float& Color::operator[](size_t index) const {
		assert(index < 4);

		return this->m_Color[index];
	}

	float Color::Get_R(void) const {
		return this->m_Color[0];
	}

	float Color::Get_G(void) const {
		return this->m_Color[1];
	}

	float Color::Get_B(void) const {
		return this->m_Color[2];
	}

	float Color::Get_A(void) const {
		return this->m_Color[3];
	}

	void Color::Set_R(float red) {
		this->m_Color[0] = red;
	}

	void Color::Set_G(float green) {
		this->m_Color[1] = green;
	}

	void Color::Set_B(float blue) {
		this->m_Color[2] = blue;
	}

	void Color::Set_A(float alpha) {
		this->m_Color[3] = alpha;
	}

}// namespace NameSpace_Core::NameSpace_Color 