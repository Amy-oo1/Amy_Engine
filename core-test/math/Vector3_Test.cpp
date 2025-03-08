#include "gtest/gtest.h"

#include <limits>
#include<math.h>

#include "math/Constant.h"
#include "math/Radian.h"
#include "math/Vector3.h"

namespace Core::Math::Vector3 {

	using NameSpace_Core::NameSpace_Math::Math_PI;
	using NameSpace_Core::NameSpace_Math::Radian;
	using NameSpace_Core::NameSpace_Math::Vector3;

	TEST(Vector3_Test, Constructors) {
		Vector3 v1{};
		EXPECT_FLOAT_EQ(v1.Get_X(), 0.0f);
		EXPECT_FLOAT_EQ(v1.Get_Y(), 0.0f);
		EXPECT_FLOAT_EQ(v1.Get_Z(), 0.0f);

		Vector3 v2{ 5.0f };
		EXPECT_FLOAT_EQ(v2.Get_X(), 5.0f);
		EXPECT_FLOAT_EQ(v2.Get_Y(), 5.0f);
		EXPECT_FLOAT_EQ(v2.Get_Z(), 5.0f);

		Vector3 v3{ 1.0f, 2.0f, 3.0f };
		EXPECT_FLOAT_EQ(v3.Get_X(), 1.0f);
		EXPECT_FLOAT_EQ(v3.Get_Y(), 2.0f);
		EXPECT_FLOAT_EQ(v3.Get_Z(), 3.0f);
	}

	TEST(Vector3_Test, Assignment_Operator) {
		Vector3 v{};
		v = 4.0f;
		EXPECT_EQ(v, Vector3(4.0f, 4.0f, 4.0f));
	}

	TEST(Vector3_Test, Unary_Operators) {
		Vector3 v{ 2.0f, -3.0f, 4.0f };

		EXPECT_EQ(+v, v);
		EXPECT_EQ(-v, Vector3(-2.0f, 3.0f, -4.0f));
	}

	TEST(Vector3_Test, Comparison_Operators) {
		Vector3 v1{ 1.0f, 2.0f, 3.0f };
		Vector3 v2{ 1.0f, 2.0f, 3.0f };
		Vector3 v3{ 4.0f, 5.0f, 6.0f };

		EXPECT_TRUE(v1 == v2);
		EXPECT_TRUE(v1 != v3);
	}

	TEST(Vector3_Test, Arithmetic_Operatiors) {
		Vector3 v1{ 1.0f, 2.0f, 3.0f };
		Vector3 v2{ 4.0f, 5.0f, 6.0f };

		EXPECT_EQ(v1 + v2, Vector3(5.0f, 7.0f, 9.0f));
		EXPECT_EQ(v1 + 2.0f, Vector3(3.0f, 4.0f, 5.0f));
		EXPECT_EQ(2.0f + v1, Vector3(3.0f, 4.0f, 5.0f));

		EXPECT_EQ(v1 - v2, Vector3(-3.0f, -3.0f, -3.0f));
		EXPECT_EQ(v1 - 1.0f, Vector3(0.0f, 1.0f, 2.0f));
		EXPECT_EQ(5.0f - v1, Vector3(4.0f, 3.0f, 2.0f));

		EXPECT_EQ(v1 * v2, Vector3(4.0f, 10.0f, 18.0f));
		EXPECT_EQ(v1 * 2.0f, Vector3(2.0f, 4.0f, 6.0f));
		EXPECT_EQ(2.0f * v1, Vector3(2.0f, 4.0f, 6.0f));

		EXPECT_EQ(v1 / v2, Vector3(0.25f, 0.4f, 0.5f));
		EXPECT_EQ(v1 / 2.0f, Vector3(0.5f, 1.0f, 1.5f));
		EXPECT_EQ(6.0f / v1, Vector3(6.0f, 3.0f, 2.0f));
	}

	TEST(Vector3_Test, Compound_Assignment_Operators) {
		Vector3 v{ 1.0f, 2.0f, 3.0f };

		v += Vector3(4.0f, 5.0f, 6.0f);
		EXPECT_EQ(v, Vector3(5.0f, 7.0f, 9.0f));

		v += 2.0f;
		EXPECT_EQ(v, Vector3(7.0f, 9.0f, 11.0f));

		v -= Vector3(1.0f, 2.0f, 3.0f);
		EXPECT_EQ(v, Vector3(6.0f, 7.0f, 8.0f));

		v -= 2.0f;
		EXPECT_EQ(v, Vector3(4.0f, 5.0f, 6.0f));

		v *= Vector3(2.0f, 3.0f, 4.0f);
		EXPECT_EQ(v, Vector3(8.0f, 15.0f, 24.0f));

		v *= 0.5f;
		EXPECT_EQ(v, Vector3(4.0f, 7.5f, 12.0f));

		v /= Vector3{ 2.0f, 3.0f, 4.0f };
		EXPECT_EQ(v, Vector3(2.0f, 2.5f, 3.0f));

		v /= 0.5f;
		EXPECT_EQ(v, Vector3(4.0f, 5.0f, 6.0f));
	}

	TEST(Vector3_Test, Accessor_Operators) {
		Vector3 v{ 1.0f, 2.0f, 3.0f };

		EXPECT_FLOAT_EQ(v[0], 1.0f);
		EXPECT_FLOAT_EQ(v[1], 2.0f);
		EXPECT_FLOAT_EQ(v[2], 3.0f);
		v[0] = 5.0f;
		v[1] = 6.0f;
		v[2] = 7.0f;
		EXPECT_EQ(v, Vector3(5.0f, 6.0f, 7.0f));
	}

	TEST(Vector3_Test, Length) {
		Vector3 v{ 2.0f, 3.0f, 6.0f };

		EXPECT_FLOAT_EQ(v.Length(), 7.0f); // sqrt(4 + 9 + 36) = 7
		EXPECT_FLOAT_EQ(v.Length_Square(), 49.0f);
	}

	TEST(Vector3_Test, Distance) {
		Vector3 v1{ 1.0f, 2.0f, 3.0f };
		Vector3 v2{ 4.0f, 6.0f, 8.0f };

		EXPECT_NEAR(v1.Distance(v2), std::sqrt(50.f), 1e-5);
		EXPECT_FLOAT_EQ(v1.Distance_Square(v2), 50.0f);
	}

	TEST(Vector3_Test, Dot_Cross) {
		Vector3 v1{ 1.0f, 2.0f, 3.0f };
		Vector3 v2{ 4.0f, 5.0f, 6.0f };

		EXPECT_FLOAT_EQ(v1.Dot_Product(v2), 32.0f); // 4 + 10 + 18
		EXPECT_EQ(v1.Cross_Product(v2), Vector3(-3.0f, 6.0f, -3.0f));
	}

	TEST(Vector3_Test, Normalize) {
		Vector3 v{ 2.0f, 0.0f, 0.0f };

		Vector3 norm = v.Normalize();
		EXPECT_FLOAT_EQ(norm.Length(), 1.0f);
		EXPECT_TRUE(norm.Is_Unit());
	}

	TEST(Vector3_Test, Project) {
		Vector3 v{ 5.0f, 0.0f, 0.0f };
		Vector3 axis{ 1.0f, 0.0f, 0.0f };

		Vector3 proj = v.Project_Over(axis);
		EXPECT_EQ(proj, Vector3(5.0f, 0.0f, 0.0f));
	}

	TEST(Vector3_Test, Reflect) {
		Vector3 v{ 1.0f, -1.0f, 0.0f };
		Vector3 normal{ 0.0f, 1.0f, 0.0f };

		Vector3 reflected = v.Reflect(normal);
		EXPECT_EQ(reflected, Vector3(1.0f, 1.0f, 0.0f));
	}

	TEST(Vector3_Test, AngleBetween) {
		Vector3 v1{ 1.0f, 0.0f, 0.0f };
		Vector3 v2{ 0.0f, 1.0f, 0.0f };

		Radian angle = v1.Angle_Between(v2);
		EXPECT_NEAR(angle.Get_Radian(), Math_PI / 2, 1e-5);
	}

	TEST(Vector3_Test, StaticConstants) {
		EXPECT_EQ(Vector3::ZERO, Vector3(0.0f, 0.0f, 0.0f));
		EXPECT_EQ(Vector3::ONE, Vector3(1.0f, 1.0f, 1.0f));
		EXPECT_EQ(Vector3::UNIT_X, Vector3(1.0f, 0.0f, 0.0f));
		EXPECT_EQ(Vector3::UNIT_Y, Vector3(0.0f, 1.0f, 0.0f));
		EXPECT_EQ(Vector3::UNIT_Z, Vector3(0.0f, 0.0f, 1.0f));
	}

	TEST(Vector3_Test, Edge_Case) {
		Vector3 Zero{ 0.f };
		const Vector3 Const_Zero{ 0.f };

		EXPECT_DEATH(Zero / Const_Zero, ".*");

		EXPECT_DEATH(Zero[3], ".*");
		EXPECT_DEATH(Const_Zero[3], ".*");

		EXPECT_DEATH(Zero.Normalize(), ".*");
		EXPECT_DEATH(Zero.Project_Over(Const_Zero), ".*");
		EXPECT_DEATH(Zero.Reflect(Const_Zero),".*");
		EXPECT_DEATH(Zero.Angle_Between(Const_Zero), ".*");

	}

}// namespace Core::Math::Vector3