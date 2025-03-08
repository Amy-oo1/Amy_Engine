#include "gtest/gtest.h"

#include <limits>

#include "math/Constant.h"
#include "math/Radian.h"
#include "math/Vector2.h"

namespace Core::Math::Vector2_Test {

	using NameSpace_Core::NameSpace_Math::Radian;
	using NameSpace_Core::NameSpace_Math::Vector2;

	TEST(Vector2_Test, Constructor) {
		Vector2 v1{};
		EXPECT_FLOAT_EQ(v1.Get_X(), 0.0f);
		EXPECT_FLOAT_EQ(v1.Get_Y(), 0.0f);

		Vector2 v2{ 5.0f };
		EXPECT_FLOAT_EQ(v2.Get_X(), 5.0f);
		EXPECT_FLOAT_EQ(v2.Get_Y(), 5.0f);

		Vector2 v3{ 2.0f, 3.0f };
		EXPECT_FLOAT_EQ(v3.Get_X(), 2.0f);
		EXPECT_FLOAT_EQ(v3.Get_Y(), 3.0f);
	}

	TEST(Vector2_Test, Assignment_Operator) {
		Vector2 v1{};
		v1 = 4.0f;

		EXPECT_FLOAT_EQ(v1.Get_X(), 4.0f);
		EXPECT_FLOAT_EQ(v1.Get_Y(), 4.0f);
	}

	TEST(Vector2_Test, Unary_Operator) {
		Vector2 v{ 2.0f, -3.0f };
		Vector2 unary_v{ -2.0f, 3.0f };

		EXPECT_EQ(+v, v);
		EXPECT_EQ(-v, unary_v);
	}

	TEST(Vector2_Test, Comparison_Operator) {
		Vector2 v1{ 2.0f, 3.0f };
		Vector2 v2{ 2.0f, 3.0f };
		Vector2 v3{ 1.0f, 4.0f };

		EXPECT_TRUE(v1 == v2);
		EXPECT_TRUE(v1 != v3);
	}

	TEST(Vector2_Test, Total_Order_Relation_Operator) {
		Vector2 v1{ 1.0f, 1.0f };
		Vector2 v2{ 2.0f, 2.0f };
		Vector2 v3{ 1.0f, 1.0f };
		Vector2 v4{ 2.0f, 2.0f };

		EXPECT_TRUE(v1 < v2);
		EXPECT_TRUE(v2 > v1);

		EXPECT_TRUE(v1 <= v2);
		EXPECT_TRUE(v2 >= v1);

		EXPECT_TRUE(v1 <= v3);
		EXPECT_TRUE(v2 >= v4);
	}

	TEST(Vector2_Test, Arithmetic_Operations) {
		Vector2 v1{ 2.0f, 3.0f };
		Vector2 v2{ 1.0f, 2.0f };

		EXPECT_EQ(v1 + v2, Vector2(3.0f, 5.0f));
		EXPECT_EQ(v1 + 5.0f, Vector2(7.0f, 8.0f));
		EXPECT_EQ(5.0f + v1, Vector2(7.0f, 8.0f));

		EXPECT_EQ(v1 - v2, Vector2(1.0f, 1.0f));
		EXPECT_EQ(v1 - 1.0f, Vector2(1.0f, 2.0f));
		EXPECT_EQ(5.0f - v1, Vector2(3.0f, 2.0f));

		EXPECT_EQ(v1 * v2, Vector2(2.0f, 6.0f));
		EXPECT_EQ(v1 * 2.0f, Vector2(4.0f, 6.0f));
		EXPECT_EQ(2.0f * v1, Vector2(4.0f, 6.0f));

		EXPECT_EQ(v1 / v2, Vector2(2.0f, 1.5f));
		EXPECT_EQ(v1 / 2.0f, Vector2(1.0f, 1.5f));
		EXPECT_EQ(6.0f / v1, Vector2(3.0f, 2.0f));
	}

	TEST(Vector2_Test, Compound_Assignments_Operatpr) {
		Vector2 v{ 2.0f, 3.0f };
		v += Vector2{ 1.0f, 2.0f };

		EXPECT_EQ(v, Vector2(3.0f, 5.0f));

		v += 2.0f;
		EXPECT_EQ(v, Vector2(5.0f, 7.0f));

		v -= Vector2{ 1.0f, 2.0f };
		EXPECT_EQ(v, Vector2(4.0f, 5.0f));

		v -= 2.0f;
		EXPECT_EQ(v, Vector2(2.0f, 3.0f));

		v *= Vector2{ 2.0f, 3.0f };
		EXPECT_EQ(v, Vector2(4.0f, 9.0f));

		v *= 0.5f;
		EXPECT_EQ(v, Vector2(2.0f, 4.5f));

		v /= Vector2{ 2.0f, 3.0f };
		EXPECT_EQ(v, Vector2(1.0f, 1.5f));

		v /= 0.5f;
		EXPECT_EQ(v, Vector2(2.0f, 3.0f));
	}

	TEST(Vector2_Test, Accessors_Operator) {
		Vector2 v{ 2.0f, 3.0f };
		EXPECT_FLOAT_EQ(v[0], 2.0f);
		EXPECT_FLOAT_EQ(v[1], 3.0f);

		v[0] = 5.0f;
		v[1] = 6.0f;
		EXPECT_EQ(v, Vector2(5.0f, 6.0f));
	}

	TEST(Vector2_Test, Length) {
		Vector2 v{ 3.0f, 4.0f };
		EXPECT_FLOAT_EQ(v.Length(), 5.0f);
		EXPECT_FLOAT_EQ(v.Length_Square(), 25.0f);
	}

	TEST(Vector2_Test, Distance) {
		Vector2 v1{ 1.0f, 2.0f };
		Vector2 v2{ 4.0f, 6.0f };

		EXPECT_FLOAT_EQ(v1.Distance(v2), 5.0f);
		EXPECT_FLOAT_EQ(v1.Distance_Square(v2), 25.0f);
	}

	TEST(Vector2_Test, Dot_Cross) {
		Vector2 v1{ 2.0f, 3.0f };
		Vector2 v2{ 4.0f, 5.0f };

		EXPECT_FLOAT_EQ(v1.Dot_Product(v2), 23.0f);
		EXPECT_FLOAT_EQ(v1.Cross_Product(v2), -2.0f);
	}

	TEST(Vector2_Test, Normalize) {
		Vector2 v{ 3.0f, 4.0f };
		Vector2 norm{ v.Normalize() };

		EXPECT_FLOAT_EQ(norm.Length(), 1.0f);
		EXPECT_TRUE(norm.Is_Unit());
		EXPECT_EQ(norm, v.To_Normalized());
	}

	TEST(Vector2_Test, Project) {
		Vector2 v{ 5.0f, 0.0f };
		Vector2 axis{ 1.0f, 0.0f };

		Vector2 proj{ v.Project_Over(axis) };
		EXPECT_EQ(proj, Vector2(5.0f, 0.0f));
	}

	TEST(Vector2_Test, Reflect) {
		Vector2 v{ 1.0f, -1.0f };
		Vector2 normal{ 0.0f, 1.0f };

		Vector2 reflected{ v.Reflect(normal) };
		EXPECT_EQ(reflected, Vector2(1.0f, 1.0f));
	}

	TEST(Vector2_Test, AngleBetween) {
		Vector2 v1{ 1.0f, 0.0f };
		Vector2 v2{ 0.0f, 1.0f };

		Radian angle{ v1.Angle_Between(v2) };
		EXPECT_NEAR(angle.Get_Radian(), NameSpace_Core::NameSpace_Math::Math_PI_DIV_2, 1e-5);
	}

	TEST(Vector2_Test, Perpendicular) {
		Vector2 v{ 2.0f, 3.0f };
		EXPECT_EQ(v.Perpendicular(), Vector2(-3.0f, 2.0f));
	}

	TEST(Vector2_Test, Static_Constants) {
		EXPECT_EQ(Vector2::ZERO, Vector2(0.0f, 0.0f));
		EXPECT_EQ(Vector2::ONE, Vector2(1.0f, 1.0f));
		EXPECT_EQ(Vector2::UNIT_X, Vector2(1.0f, 0.0f));
		EXPECT_EQ(Vector2::UNIT_Y, Vector2(0.0f, 1.0f));
	}

	TEST(Vector2_Test, Edge_Case) {
		Vector2 Zero{ 0.f };
		const Vector2 Const_Zero{ 0.f };

		EXPECT_DEATH(Zero / Const_Zero, ".*");

		EXPECT_DEATH(Zero[3], ".*");
		EXPECT_DEATH(Const_Zero[3], ".*");

		EXPECT_DEATH(Zero.Normalize(), ".*");
		EXPECT_DEATH(Const_Zero.Project_Over(Vector2::ZERO), ".*");
		EXPECT_DEATH(Zero.Reflect(Vector2::ZERO), ".*");
		EXPECT_DEATH(Zero.Angle_Between(Vector2::ZERO), ".*");

	}

}// namespace Core::Math::Vector2_Test