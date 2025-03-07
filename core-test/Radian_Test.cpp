
#include "pch.h"

#include <limits>

#include "math/Constant.h"
#include "math/Degree.h"
#include "math/Radian.h"

namespace Core::Math::Radian {

	using NameSpace_Core::NameSpace_Math::Math_PI;
	using NameSpace_Core::NameSpace_Math::Radian;
	using NameSpace_Core::NameSpace_Math::Degree;

	TEST(Radian_Test, Default_Constructor) {
		Radian defaultRad{};
		EXPECT_FLOAT_EQ(defaultRad.Get_Radian(), 0.0f);
	}

	TEST(Radian_Test, Parameterized_Constructor) {
		Radian explicitRad{ 3.14f };
		EXPECT_FLOAT_EQ(explicitRad.Get_Radian(), 3.14f);
	}

	TEST(Radian_Test, Copy_Constructor) {
		Radian explicitRad{ 3.14f };
		Radian copiedRad{ explicitRad };
		EXPECT_FLOAT_EQ(copiedRad.Get_Radian(), 3.14f);
	}

	TEST(Radian_Test, To_Degree_Convert) {
		Radian radian{ 3.14f };
		Degree degree = static_cast<Degree>(radian);
		EXPECT_FLOAT_EQ(degree.Get_Degree(), 179.90875f);
	}

	TEST(Radian_Test, Assignment_Operator) {
		Radian explicitRad{ 3.14f };
		EXPECT_FLOAT_EQ(explicitRad.Get_Radian(), 3.14f);
	}

	TEST(Radian_Test, Float_Assignment_Operator) {
		Radian radian{};
		radian = 3.14f;
		EXPECT_FLOAT_EQ(radian.Get_Radian(), 3.14f);
	}

	TEST(Radian_Test, UnaryPluss_Operator) {
		Radian posRad{ 2.5f };
		Radian posResult = +posRad;
		EXPECT_FLOAT_EQ(posResult.Get_Radian(), 2.5f);
	}

	TEST(Radian_Test, UnaryMinus_Operator) {
		Radian posRad{ 2.5f };
		Radian negRad = -posRad;
		EXPECT_FLOAT_EQ(negRad.Get_Radian(), -2.5f);
	}

	TEST(Radian_Test, Equality_Operator) {
		Radian r1{ 3.14f };
		Radian r2{ 3.14f };
		EXPECT_TRUE(r1 == r2);
	}

	TEST(Radian_Test, Inequality_Operator) {
		Radian r1{ 3.14f };
		Radian r2{ 6.28f };
		EXPECT_TRUE(r1 != r2);
	}

	TEST(Radian_Test, LessThan_Operator) {
		Radian r1{ 3.14f };
		Radian r2{ 6.28f };
		EXPECT_TRUE(r1 < r2);
	}

	TEST(Radian_Test, GreaterThan_Operator) {
		Radian r1{ 3.14f };
		Radian r2{ 6.28f };
		EXPECT_TRUE(r2 > r1);
	}

	TEST(Radian_Test, LessThan_Or_Equality_Operator) {
		Radian r1{ 3.14f };
		Radian r2{ 6.28f };
		EXPECT_TRUE(r1 <= r2);

		Radian r3{ 6.28f };
		Radian r4{ 6.28f };
		EXPECT_TRUE(r3 <= r4);
	}

	TEST(Radian_Test, GreaterThan_Or_Equality_Operator) {
		Radian r1{ 6.28f };
		Radian r2{ 3.14f };
		EXPECT_TRUE(r1 >= r2);

		Radian r3{ 6.28f };
		Radian r4{ 6.28f };
		EXPECT_TRUE(r3 >= r4);
	}

	TEST(Radian_Test, Addition_Operator) {
		Radian Radian1{ 30.0f };
		Radian Radian2{ 60.0f };

		Radian result1 = Radian1 + 60.f;
		Radian result2 = Radian1 + Radian2;
		Radian result3 = 60.f + Radian1;

		EXPECT_FLOAT_EQ(result1.Get_Radian(), 90.0f);
		EXPECT_FLOAT_EQ(result2.Get_Radian(), 90.0f);
		EXPECT_FLOAT_EQ(result3.Get_Radian(), 90.0f);
	}

	TEST(Radian_Test, Subtraction_Operator) {
		Radian Radian1{ 90.0f };
		Radian Radian2{ 60.0f };

		Radian result1 = Radian1 - 30.f;
		Radian result2 = Radian1 - Radian2;
		Radian result3 = 90.f - Radian2;

		EXPECT_FLOAT_EQ(result1.Get_Radian(), 60.0f);
		EXPECT_FLOAT_EQ(result2.Get_Radian(), 30.0f);
		EXPECT_FLOAT_EQ(result3.Get_Radian(), 30.0f);
	}

	TEST(Radian_Test, Multiplication_Operator) {
		Radian Radian1{ 30.0f };
		Radian Radian2{ 2.0f };

		Radian result1 = Radian1 * 2.0f;
		Radian result2 = Radian1 * Radian2;
		Radian result3 = 2.0f * Radian1;

		EXPECT_FLOAT_EQ(result1.Get_Radian(), 60.0f);
		EXPECT_FLOAT_EQ(result2.Get_Radian(), 60.0f);
		EXPECT_FLOAT_EQ(result3.Get_Radian(), 60.0f);
	}

	TEST(Radian_Test, Division_Operator) {
		Radian Radian1{ 60.0f };
		Radian Radian2{ 2.0f };

		Radian result1 = Radian1 / 2.0f;
		Radian result2 = Radian1 / Radian2;
		Radian result3 = 60.0f / Radian2;

		EXPECT_FLOAT_EQ(result1.Get_Radian(), 30.0f);
		EXPECT_FLOAT_EQ(result2.Get_Radian(), 30.0f);
		EXPECT_FLOAT_EQ(result3.Get_Radian(), 30.0f);
	}

	TEST(Radian_Test, Addition_Assignment_Operator) {
		Radian result1{ 30.0f };
		result1 += Radian{ 60.0f };
		EXPECT_FLOAT_EQ(result1.Get_Radian(), 90.0f);

		Radian result2{ 30.0f };
		result2 += 60.0f;
		EXPECT_FLOAT_EQ(result2.Get_Radian(), 90.0f);
	}

	TEST(Radian_Test, Subtraction_Assignment_Operator) {
		Radian result1{ 90.0f };
		result1 -= Radian{ 30.0f };
		EXPECT_FLOAT_EQ(result1.Get_Radian(), 60.0f);

		Radian result2{ 90.0f };
		result2 -= 30.0f;
		EXPECT_FLOAT_EQ(result2.Get_Radian(), 60.0f);
	}

	TEST(Radian_Test, Multiplication_Assignment_Operator) {
		Radian result1{ 30.0f };
		result1 *= Radian{ 2.0f };
		EXPECT_FLOAT_EQ(result1.Get_Radian(), 60.0f);

		Radian result2{ 30.0f };
		result2 *= 2.0f;
		EXPECT_FLOAT_EQ(result2.Get_Radian(), 60.0f);
	}

	TEST(Radian_Test, Division_Assignment_Operator) {
		Radian result1{ 60.0f };
		result1 /= Radian{ 2.0f };
		EXPECT_FLOAT_EQ(result1.Get_Radian(), 30.0f);

		Radian result2{ 60.0f };
		result2 /= 2.0f;
		EXPECT_FLOAT_EQ(result2.Get_Radian(), 30.0f);
	}

	TEST(Radian_Test, Is_NaN) {
		float nanVal = std::numeric_limits<float>::quiet_NaN();
		Radian nanRad{ nanVal };
		EXPECT_TRUE(nanRad.Is_NaN());
	}

	TEST(Radian_Test, Is_Infinity) {
		float infVal = std::numeric_limits<float>::infinity();
		Radian posInfRad(infVal);
		Radian negInfRad(-infVal);
		EXPECT_TRUE(posInfRad.Is_Infinity());
		EXPECT_TRUE(negInfRad.Is_Infinity());
	}

	TEST(Radian_Test, Static_Constants) {
		EXPECT_FLOAT_EQ(Radian::ZERO.Get_Radian(), 0.0f);
		EXPECT_FLOAT_EQ(Radian::PI.Get_Radian(), Math_PI);
	}

}// namespace Test::Math::Radian