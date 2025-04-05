#pragma once

#include<cstddef>

#include "math/Vector3.h"
#include "math/Vector4.h"

namespace NameSpace_Core::NameSpace_Color {

	using NameSpace_Math::Vector3;
	using NameSpace_Math::Vector4;

	class Color final {
	public:
		Color(void) = default;

		Color(const Color& other) = default;
		Color(Color&& other) noexcept = default;

		Color& operator=(const Color& other) = default;
		Color& operator=(Color&& other) noexcept = default;

		explicit Color(const Vector4& color);
		Color(float red, float green, float blue, float alpha = 1.f);

		~Color(void) = default;

	public:
		Color& operator=(const Vector4& Val);

		explicit operator Vector4(void) const;
		explicit operator Vector3(void) const;

		bool operator==(const Color& other) const;
		bool operator!=(const Color& other) const;

		const Color operator*(float scalar) const;
		friend const Color operator*(float scalar, const Color& color);;

		Color& operator*=(float scalar);

		float& operator[](size_t index);
		const float& operator[](size_t index) const;

	public:
		[[nodiscard]] float Get_R(void) const;
		[[nodiscard]] float Get_G(void) const;
		[[nodiscard]] float Get_B(void) const;
		[[nodiscard]] float Get_A(void) const;

		void Set_R(float red);
		void Set_G(float green);
		void Set_B(float blue);
		void Set_A(float alpha);

	private:
		Vector4 m_Color{ 1.0f, 1.0f, 1.0f, 1.0f };

	};

}// namespace NameSpace_Core::NameSpace_Color
