#pragma once

namespace NameSpace_Core::NameSpace_Math {

	class Radian;

	class Degree final {
	public:
		Degree(void) = default;

		Degree(const Degree&) = default;
		Degree(Degree&&) = default;

		Degree& operator=(const Degree&) = default;
		Degree& operator=(Degree&&) = default;

		explicit Degree(float Value);

		~Degree(void) = default;

	public:
		Degree& operator=(float Value);

		explicit operator Radian(void) const;

		const Degree operator+(void) const;
		const Degree operator-(void) const;

		const bool operator==(const Degree& R_HS) const;
		const bool operator!=(const Degree& R_HS) const;

		const bool operator<(const Degree& R_HS) const;
		const bool operator>(const Degree& R_HS) const;
		const bool operator<=(const Degree& R_HS) const;
		const bool operator>=(const Degree& R_HS) const;

		const Degree operator+(float R_HS)const;
		const Degree operator+(const Degree& R_HS) const;
		friend const Degree operator+(float L_HS, const Degree& R_HS);

		const Degree operator-(float R_HS)const;
		const Degree operator-(const Degree& R_HS) const;
		friend const Degree operator-(float L_HS, const Degree& R_HS);

		const Degree operator*(float R_HS) const;
		const Degree operator*(const Degree& R_HS) const;
		friend const Degree operator*(float L_HS, const Degree& R_HS);

		const Degree operator/(float R_HS) const;
		const Degree operator/(const Degree& R_HS) const;
		friend const Degree operator/(float L_HS, const Degree& R_HS);

		Degree& operator+=(const Degree& R_HS);
		Degree& operator+=(float R_HS);

		Degree& operator-=(const Degree& R_HS);
		Degree& operator-=(float R_HS);

		Degree& operator*= (const Degree& R_HS);
		Degree& operator*=(float R_HS);
		
		Degree& operator/=(const Degree& R_HS);
		Degree& operator/=(float R_HS);

	public:
		const bool Is_NaN(void)const;
		const bool Is_Infinity(void)const;

	public:
		const float Get_Degree(void) const;

	private:
		float m_Degree{ 0.f };
	};
} // namespace NameSpace_Core::NameSpace_Math