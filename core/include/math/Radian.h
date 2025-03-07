#pragma once

namespace NameSpace_Core::NameSpace_Math {

	class Degree;

	class Radian final {
	public:
		Radian(void) = default;

		Radian(const Radian&) = default;
		Radian(Radian&&) = default;

		Radian& operator=(const Radian&) = default;
		Radian& operator=(Radian&&) = default;

		explicit Radian(float Value);

		~Radian(void) = default;

	public:
		Radian& operator=(float Value);

		operator Degree(void) const;

		const Radian operator+(void) const;
		const Radian operator-(void) const;

		const bool operator==(const Radian& R_HS) const;
		const bool operator!=(const Radian& R_HS) const;

		const bool operator<(const Radian& R_HS) const;
		const bool operator>(const Radian& R_HS) const;
		const bool operator<=(const Radian& R_HS) const;
		const bool operator>=(const Radian& R_HS) const;

		const Radian operator+(float R_HS) const;
		const Radian operator+(const Radian& R_HS) const;
		friend const Radian operator+(float L_HS, const Radian& R_HS);

		const Radian operator-(float R_HS) const;
		const Radian operator-(const Radian& R_HS) const;
		friend const Radian operator-(float L_HS, const Radian& R_HS);

		const Radian operator*(const Radian& R_HS) const;
		const Radian operator*(float R_HS) const;
		friend const Radian operator*(float L_HS, const Radian& R_HS);

		const Radian operator/(float R_HS) const;
		const Radian operator/(const Radian& R_HS) const;
		friend const Radian operator/(float L_HS, const Radian& R_HS);

		Radian& operator+=(const Radian& R_HS);
		Radian& operator-=(const Radian& R_HS);
		Radian& operator*=(float R_HS);
		Radian& operator/=(float R_HS);

	public:
		const bool Is_NaN(void) const;
		const bool Is_Infinity(void) const;

	public:
		const float Get_Radian(void) const;

	public:
		static const Radian ZERO;
		static const Radian PI;

	private:
		float m_Radian{ 0.f };
	};

} // namespace NameSpace_Core::NameSpace_Math