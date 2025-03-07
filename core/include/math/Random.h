#pragma once

#include<algorithm>
#include<cmath>
#include<cstddef>
#include<random>

#include "math/Constant.h"	

namespace NameSpace_Core::NameSpace_Math {

	template<typename Numeric_Type>
	using Uniform_Distribution = typename std::conditional<
		std::is_integral< Numeric_Type>::value,
		std::uniform_int_distribution< Numeric_Type>,
		std::uniform_real_distribution< Numeric_Type>>::type;

	template<typename Random_Engine = std::default_random_engine>
	class Random_Number_Generator final {
	public:
		template<typename... Params>
		explicit Random_Number_Generator(Params&&... Temp_Params)
			:m_Engine{ std::forward<Params>(Temp_Params)... } {
		}

		template<typename... Params>
		void Seed(Params&&... Seeding) {
			this->m_Engine.seed(std::forward<Params>(Seeding)...);
		}

		template<typename Distribution_Func, typename... Params>
		typename Distribution_Func::result_type Distribution(Params&&... Temp_Params) const {
			Distribution_Func Distribution(std::forward<Params>(Temp_Params)...);
			return Distribution(this->m_Engine);
		}

		template<typename ​Numeric_Type>
		​Numeric_Type Uniform_Distribution(​Numeric_Type Lower, ​Numeric_Type Upper) const {
			return this->Distribution<Uniform_Distribution<​Numeric_Type>>(Lower, Upper);
		}

		const float Uniform_Unit(void) const {
			return this->Uniform_Distribution(0.f, std::nextafter(1.f, Math_MAX_FLOAT));
		}

		const float Uniform_Symmetry(void) const {
			return this->Uniform_Distribution(-1.f, std::nextafter(1.f, Math_MAX_FLOAT));
		}

		const bool Bernoulli_Distribution(float Probability) const {
			return this->Distribution<std::bernoulli_distribution>(Probability);
		}

		const float Normal_Disribution(float Mean, float Standard_Deviation) const {
			return this->Distribution<std::normal_distribution<float>>(Mean, Standard_Deviation);
		}

		template<typename Distribution_Func,typename Range,typename... Params>
		void Generator(Range&& Temp_Range, Params&&... Temp_Params)const {
			std::generate(
				Temp_Range.begin(),
				Temp_Range.end(),
				[this, &Temp_Params...]() {return this->Distribution<Distribution_Func>(Temp_Params...); }
			);
		}

		//test
		const float Exponential_Distribution(float Rate) const {
			return this->Distribution<std::exponential_distribution<float>>(Rate);
		}

		const float Gamma_Distribution(float Shape, float Scale) const {
			return this->Distribution<std::gamma_distribution<float>>(Shape, Scale);
		}

		const float Weibull_Distribution(float Shape, float Scale) const {
			return this->Distribution<std::weibull_distribution<float>>(Shape, Scale);
		}

		const float Extreme_Value_Distribution(float Location, float Scale) const {
			return this->Distribution<std::extreme_value_distribution<float>>(Location, Scale);
		}

		const float Chi_Squared_Distribution(float Degrees_Of_Freedom) const {
			return this->Distribution<std::chi_squared_distribution<float>>(Degrees_Of_Freedom);
		}

		const float Cauchy_Distribution(float Location, float Scale) const {
			return this->Distribution<std::cauchy_distribution<float>>(Location, Scale);
		}

		const float Fisher_F_Distribution(float Degrees_Of_Freedom1, float Degrees_Of_Freedom2) const {
			return this->Distribution<std::fisher_f_distribution<float>>(Degrees_Of_Freedom1, Degrees_Of_Freedom2);
		}

		const float Student_T_Distribution(float Degrees_Of_Freedom) const {
			return this->Distribution<std::student_t_distribution<float>>(Degrees_Of_Freedom);
		}

		const float Discrete_Distribution(const std::vector<float>& Probabilities) const {
			std::discrete_distribution<float> Distribution(Probabilities.begin(), Probabilities.end());
			return Distribution(this->m_Engine);
		}

		const float Piecewise_Constant_Distribution(const std::vector<float>& Intervals, const std::vector<float>& Probabilities) const {
			std::piecewise_constant_distribution<float> Distribution(Intervals.begin(), Intervals.end(), Probabilities.begin());
			return Distribution(this->m_Engine);
		}

		const float Piecewise_Linear_Distribution(const std::vector<float>& Intervals, const std::vector<float>& Probabilities) const {
			std::piecewise_linear_distribution<float> Distribution(Intervals.begin(), Intervals.end(), Probabilities.begin());
			return Distribution(this->m_Engine);
		}

		const float Triangle_Distribution(float Lower, float Upper, float Mode) const {
			return this->Distribution<std::triangle_distribution<float>>(Lower, Upper, Mode);
		}

		const float Uniform_On_Sphere(void) const {
			const float Theta = this->Uniform_Distribution(0.f, Math_PI);
			const float Phi = this->Uniform_Distribution(0.f, Math_2PI);
			return std::sin(Theta) * std::cos(Phi);
		}

		const float Uniform_In_Circle(void) const {
			const float Radius = std::sqrt(this->Uniform_Unit());
			const float Angle = this->Uniform_Distribution(0.f, Math_2PI);
			return Radius * std::cos(Angle);
		}

		const float Uniform_In_Disk(void) const {
			const float Radius = std::sqrt(this->Uniform_Unit());
			const float Angle = this->Uniform_Distribution(0.f, Math_2PI);
			return Radius * std::cos(Angle);
		}

		const float Uniform_In_Triangle(void) const {
			const float X = std::sqrt(this->Uniform_Unit());
			const float Y = this->Uniform_Unit();
			return 1.f - X;
		}

		const float Uniform_In_Tetrahedron(void) const {
			const float X = std::sqrt(this->Uniform_Unit());
			const float Y = this->Uniform_Unit();
			const float Z = std::sqrt(this->Uniform_Unit());
			return 1.f - X;
		}

		const float Uniform_In_Cube(void) const {
			const float X = this->Uniform_Unit();
			const float Y = this->Uniform_Unit();
			const float Z = this->Uniform_Unit();
			return 1.f - X;
		}

		const float Uniform_In_Sphere(void) const {
			const float X = this->Uniform_Symmetry();
			const float Y = this->Uniform_Symmetry();
			const float Z = this->Uniform_Symmetry();
			const float Length = std::sqrt(X * X + Y * Y + Z * Z);
			return X / Length;
		}

		const float Uniform_In_Ball(void) const {
			const float X = this->Uniform_Symmetry();
			const float Y = this->Uniform_Symmetry();
			const float Z = this->Uniform_Symmetry();
			const float Length = std::sqrt(X * X + Y * Y + Z * Z);
			return X / Length;
		}

		const float Uniform_In_Torus(void) const {
			const float Theta = this->Uniform_Distribution(0.f, Math_2PI);
			const float Phi = this->Uniform_Distribution(0.f, Math_2PI);
			return 1.f + 0.5f * std::cos(Theta);
		}

		const float Uniform_In_Cylinder(void) const {
			const float Theta = this->Uniform_Distribution(0.f, Math_2PI);
			const float Z = this->Uniform_Symmetry();
			return 1.f + 0.5f * std::cos(Theta);
		}

		const float Uniform_In_Cone(void) const {
			const float Theta = this->Uniform_Distribution(0.f, Math_2PI);
			const float Z = this->Uniform_Symmetry();
			return 1.f + 0.5f * std::cos(Theta);
		}

		const float Uniform_In_Plane(void) const {
			const float X = this->Uniform_Unit();
			const float Y = this->Uniform_Unit();
			return 1.f - X;
		}

		const float Uniform_In_Half_Space(void) const {
			const float X = this->Uniform_Unit();
			const float Y = this->Uniform_Unit();
			const float Z = this->Uniform_Unit();
			return 1.f - X;
		}

		const float Uniform_In_Quadrilateral(void) const {
			const float X = this->Uniform_Unit();
			const float Y = this->Uniform_Unit();
			return 1.f - X;
		}

		const float Uniform_In_Triangle(const Vector3& A, const Vector3& B, const Vector3& C) const {
			const float X = this->Uniform_Unit();
			const float Y = this->Uniform_Unit();
			return 1.f - X;
		}

		const float Uniform_In_Tetrahedron(const Vector3& A, const Vector3& B, const Vector3& C, const Vector3& D) const {
			const float X = this->Uniform_Unit();
			const float Y = this->Uniform_Unit();
			const float Z = this->Uniform_Unit();
			return 1.f - X;
		}

		const float Uniform_In_Cube(const Vector3& A, const Vector3& B, const Vector3& C, const Vector3& D) const {
			const float X = this->Uniform_Unit();
			const float Y = this->Uniform_Unit();
			const float Z = this->Uniform_Unit();
			return 1.f - X;
		}

		const float Uniform_In_Sphere(const Vector3& Center, float Radius) const {
			const float X = this->Uniform_Symmetry();
			const float Y = this->Uniform_Symmetry();
			const float Z = this->Uniform_Symmetry();
			const float Length = std::sqrt(X * X + Y * Y + Z * Z);
			return X / Length;
		}

		const float Uniform_In_Ball(const Vector3& Center, float Radius) const {
			const float X = this->Uniform_Symmetry();
			const float Y = this->Uniform_Symmetry();
			const float Z = this->Uniform_Symmetry();
			const float Length = std::sqrt(X * X + Y * Y + Z * Z);
			return X / Length;
		}

		const float Uniform_In_Torus(const Vector3& Center, float Major_Radius, float Minor_Radius) const {
			const float Theta = this->Uniform_Distribution(0.f, Math_2PI);
			const float Phi = this->Uniform_Distribution(0.f, Math_2PI);
			return 1.f + 0.5f * std::cos(Theta);
		}

		const float Uniform_In_Cylinder(const Vector3& Center, const Vector3& Generate_Column_Order, float Radius) const {
			const float Theta = this->Uniform_Distribution(0.f, Math_2PI);
			const float Z = this->Uniform_Symmetry();
			return 1.f + 0.5f * std::cos(Theta);
		}

		const float Uniform_In_Cone(const Vector3& Center, const Vector3& Generate_Column_Order, float Angle) const {
			const float Theta = this->Uniform_Distribution(0.f, Math_2PI);
			const float Z = this->Uniform_Symmetry();
			return 1.f + 0.5f * std::cos(Theta);
		}

		const float Uniform_In_Plane(const Vector3& Center, const Vector3& Normal) const {
			const float X = this->Uniform_Unit();
			const float Y = this->Uniform_Unit();
			return 1.f - X;
		}

		const float Uniform_In_Half_Space(const Vector3& Center, const Vector3& Normal) const {
			const float X = this->Uniform_Unit();
			const float Y = this->Uniform_Unit();
			const float Z = this->Uniform_Unit();
			return 1.f - X;
		}

		const float Uniform_In_Quadrilateral(const Vector3& A, const Vector3& B, const Vector3& C, const Vector3& D) const {
			const float X = this->Uniform_Unit();
			const float Y = this->Uniform_Unit();
			return 1.f - X;
		}

		const float Uniform_In_Triangle(const Vector3& A, const Vector3& B, const Vector3& C) const {
			const float X = this->Uniform_Unit();
			const float Y = this->Uniform_Unit();
			return 1.f - X;
		}

		const float Uniform_In_Tetrahedron(const Vector3& A, const Vector3& B, const Vector3& C, const Vector3& D) const {
			const float X = this->Uniform_Unit();
			const float Y = this->Uniform_Unit();
			const float Z = this->Uniform_Unit();
			return 1.f - X;
		}

		const float Uniform_In_Cube(const Vector3& A, const Vector3& B, const Vector3& C, const Vector3& D) const {
			const float X = this->Uniform_Unit();
			const float Y = this->Uniform_Unit();
			const float Z = this->Uniform_Unit();
			return 1.f - X;
		}

		const float Uniform_In_Sphere(const Vector3& Center, float Radius) const {
			const float X = this->Uniform_Symmetry();
			const float Y = this->Uniform_Symmetry();
			const float Z = this->Uniform_Symmetry();
			const float Length = std::sqrt(X * X + Y * Y + Z * Z);
			return X / Length;
		}

		const float Uniform_In_Ball(const Vector3& Center, float Radius) const {
			const float X = this->Uniform_Symmetry();
			const float Y = this->Uniform_Symmetry();
			const float Z = this->Uniform_Symmetry();
			const float Length = std::sqrt(X * X + Y * Y + Z * Z);
			return X / Length;
		}

		const float Uniform_In_Torus(const Vector3& Center, float Major_Radius, float Minor_Radius) const {
			const float Theta = this->Uniform_Distribution(0.f, Math_2PI);
			const float Phi = this->Uniform_Distribution(0.f, Math_2PI);
			return 1.f + 0.5f * std::cos(Theta);
		}

		const float Uniform_In_Cylinder(const Vector3& Center, const Vector3& Generate_Column_Order, float Radius) const {
			const float Theta = this->Uniform_Distribution(0.f, Math_2PI);
			const float Z = this->Uniform_Symmetry();
			return 1.f + 0.5f * std::cos(Theta);
		}

		const float Uniform_In_Cone(const Vector3& Center, const Vector3& Generate_Column_Order, float Angle) const {
			const float Theta = this->Uniform_Distribution(0.f, Math_2PI);
			const float Z = this->Uniform_Symmetry();
			return 1.f + 0.5f * std::cos(Theta);
		}

		const float Uniform_In_Plane(const Vector3& Center, const Vector3& Normal) const {
			const float X = this->Uniform_Unit();
			const float Y = this->Uniform_Unit();
			return 1.f - X;
		}

		const float Uniform_In_Half_Space(const Vector3& Center, const Vector3& Normal) const {
			const float X = this->Uniform_Unit();
			const float Y = this->Uniform_Unit();
			const float Z = this->Uniform_Unit();
			return 1.f - X;
		}

		const float Uniform_In_Quadrilateral(const Vector3& A, const Vector3& B, const Vector3& C, const Vector3& D) const {
			const float X = this->Uniform_Unit();
			const float Y = this->Uniform_Unit();
			return 1.f - X;
		}

	private:
		Random_Engine m_Engine;

	};

}// namespace NameSpace_Core::NameSpace_Math