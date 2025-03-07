#include "pch.h"

#include "math/Degree.h"
#include "math/Radian.h"

namespace Core::Math::Degree {

	using NameSpace_Core::NameSpace_Math::Radian;
	using  NameSpace_Core::NameSpace_Math::Degree;

	TEST(Degree_Test, Default_Constructor) {
		Degree degree{};
		EXPECT_FLOAT_EQ(degree.Get_Degree(), 0.0f);
	}

	TEST(Degree_Test, Parameterized_Constructor) {
		Degree degree{ 45.0f };
		EXPECT_FLOAT_EQ(degree.Get_Degree(), 45.0f);
	}

	TEST(Degree_Test, Copy_Constructor) {
		Degree degree1{ 90.0f };
		Degree degree2{ degree1 };
		EXPECT_FLOAT_EQ(degree2.Get_Degree(), 90.0f);
	}

	TEST(Degree_Test, To_Radian_Convert) {
		Degree degree{ 90.0f };
		Radian radian = static_cast<Radian>(degree);
		EXPECT_FLOAT_EQ(radian.Get_Radian(), 1.5707964f);
	}

	TEST(Degree_Test, Assignment_Operator) {
		Degree degree1{ 30.0f };
		Degree degree2{};
		degree2 = degree1;
		EXPECT_FLOAT_EQ(degree2.Get_Degree(), 30.0f);
	}

	TEST(Degree_Test, Float_Assignment_Operator) {
		Degree degree;
		degree = 60.0f;
		EXPECT_FLOAT_EQ(degree.Get_Degree(), 60.0f);
	}

	TEST(Degree_Test, UnaryPluss_Operator) {
		Degree degree{ 45.0f };
		Degree result = +degree;
		EXPECT_FLOAT_EQ(result.Get_Degree(), 45.0f);
	}

	TEST(Degree_Test, UnaryMinus_Operator) {
		Degree degree(45.0f);
		Degree result = -degree;
		EXPECT_FLOAT_EQ(result.Get_Degree(), -45.0f);
	}

	TEST(Degree_Test, Equality_Operator) {
		Degree degree1{ 90.0f };
		Degree degree2{ 90.0f };
		EXPECT_TRUE(degree1 == degree2);
	}

	TEST(Degree_Test, Inequality_Operator) {
		Degree degree1{ 90.0f };
		Degree degree2{ 45.0f };
		EXPECT_TRUE(degree1 != degree2);
	}

	TEST(Degree_Test, LessThan_Operator) {
		Degree degree1{ 30.0f };
		Degree degree2{ 60.0f };
		EXPECT_TRUE(degree1 < degree2);
	}

	TEST(Degree_Test, GreaterThan_Operator) {
		Degree degree1{ 60.0f };
		Degree degree2{ 30.0f };
		EXPECT_TRUE(degree1 > degree2);
	}

	TEST(Degree_Test, LessThan_Or_Equality_Operator) {
		Degree degree1{ 30.0f };
		Degree degree2{ 60.0f };
		EXPECT_TRUE(degree1 <= degree2);

		Degree degree3{ 60.0f };
		Degree degree4{ 60.0f };
		EXPECT_TRUE(degree3 <= degree4);
	}

	TEST(Degree_Test, GreaterThan_Or_Equality_Operator) {
		Degree degree1{ 60.0f };
		Degree degree2{ 30.0f };
		EXPECT_TRUE(degree1 >= degree2);

		Degree degree3{ 60.0f };
		Degree degree4{ 60.0f };
		EXPECT_TRUE(degree3 >= degree4);
	}

	TEST(Degree_Test, Addition_Operator) {
		Degree degree1{ 30.0f };
		Degree degree2{ 60.0f };

		Degree result1 = degree1 + 60.f;
		Degree result2 = degree1 + degree2;
		Degree result3 = 60.f + degree1;

		EXPECT_FLOAT_EQ(result1.Get_Degree(), 90.0f);
		EXPECT_FLOAT_EQ(result2.Get_Degree(), 90.0f);
		EXPECT_FLOAT_EQ(result3.Get_Degree(), 90.0f);
	}

	TEST(Degree_Test, Subtraction_Operator) {
		Degree degree1{ 90.0f };
		Degree degree2{ 30.0f };

		Degree result1 = degree1 - 30.0f;
		Degree result2 = degree1 - degree2;
		Degree result3 = 90.0f - degree2;

		EXPECT_FLOAT_EQ(result1.Get_Degree(), 60.0f);
		EXPECT_FLOAT_EQ(result2.Get_Degree(), 60.0f);
		EXPECT_FLOAT_EQ(result3.Get_Degree(), 60.0f);
	}

	TEST(Degree_Test, Multiplication_Operator) {
		Degree degree1{ 30.0f };
		Degree degree2{ 2.0f };

		Degree result1 = degree1 * 2.0f;
		Degree result2 = degree1 * degree2;
		Degree result3 = 2.0f * degree1;

		EXPECT_FLOAT_EQ(result1.Get_Degree(), 60.0f);
		EXPECT_FLOAT_EQ(result2.Get_Degree(), 60.0f);
		EXPECT_FLOAT_EQ(result3.Get_Degree(), 60.0f);
	}

	TEST(Degree_Test, Division_Operator) {
		Degree degree1{ 60.0f };
		Degree degree2{ 2.0f };

		Degree result1 = degree1 / 2.0f;
		Degree result2 = degree1 / degree2;
		Degree result3 = 60.0f / degree2;

		EXPECT_FLOAT_EQ(result1.Get_Degree(), 30.0f);
		EXPECT_FLOAT_EQ(result2.Get_Degree(), 30.0f);
		EXPECT_FLOAT_EQ(result3.Get_Degree(), 30.0f);
	}

	TEST(Degree_Test, Addition_Assignment_Operator) {
		Degree degree1{ 30.0f };
		degree1 += Degree{ 60.0f };
		EXPECT_FLOAT_EQ(degree1.Get_Degree(), 90.0f);

		Degree degree2{ 30.0f };
		degree2 += 60.f;
		EXPECT_FLOAT_EQ(degree2.Get_Degree(), 90.0f);
	}

	TEST(Degree_Test, Subtraction_Assignment_Operator) {
		Degree degree1{ 90.0f };
		degree1 -= Degree{ 30.0f };
		EXPECT_FLOAT_EQ(degree1.Get_Degree(), 60.0f);

		Degree degree2{ 90.0f };
		degree2 -= 30.0f;
		EXPECT_FLOAT_EQ(degree2.Get_Degree(), 60.0f);
	}

	TEST(Degree_Test, Multiplication_Assignment_Operator) {
		Degree degree1{ 30.0f };
		degree1 *= Degree{ 2.0f };
		EXPECT_FLOAT_EQ(degree1.Get_Degree(), 60.0f);

		Degree degree2{ 30.0f };
		degree2 *= 2.0f;
		EXPECT_FLOAT_EQ(degree2.Get_Degree(), 60.0f);
	}


	TEST(Degree_Test, Division_Assignment_Operator) {
		Degree degree1{ 60.0f };
		degree1 /= 2.0f;
		EXPECT_FLOAT_EQ(degree1.Get_Degree(), 30.0f);

		Degree degree2{ 60.0f };
		degree2 /= Degree{ 2.0f };
		EXPECT_FLOAT_EQ(degree2.Get_Degree(), 30.0f);
	}

	TEST(Degree_Test, Is_NaN) {
		Degree degree{ std::numeric_limits<float>::quiet_NaN() };
		EXPECT_TRUE(degree.Is_NaN());
	}

	TEST(Degree_Test, Is_Infinity) {
		Degree degree{ std::numeric_limits<float>::infinity() };
		EXPECT_TRUE(degree.Is_Infinity());
		EXPECT_TRUE((-degree).Is_Infinity());
	}

}// namespace Core::Math::Degre