#include "gtest/gtest.h"

#include <limits>

#include "math/Vector3.h"
#include "math/Vector4.h"

namespace Core::Math::Vector4_Test {

	using NameSpace_Core::NameSpace_Math::Vector3;
	using NameSpace_Core::NameSpace_Math::Vector4;

	TEST(Vector4_Test, Constructors) {
		Vector4 v1{};
		EXPECT_FLOAT_EQ(v1.Get_X(), 0.0f);
		EXPECT_FLOAT_EQ(v1.Get_Y(), 0.0f);
		EXPECT_FLOAT_EQ(v1.Get_Z(), 0.0f);
		EXPECT_FLOAT_EQ(v1.Get_W(), 0.0f);

		Vector4 v2{ 5.0f };
		EXPECT_EQ(v2, Vector4(5.0f, 5.0f, 5.0f, 5.0f));

		Vector4 v3{ 1.0f, 2.0f, 3.0f, 4.0f };
		EXPECT_EQ(v3.Get_XYZ(), Vector3(1.0f, 2.0f, 3.0f));
		EXPECT_FLOAT_EQ(v3.Get_W(), 4.0f);

		Vector4 v4{ Vector3{5.0f, 6.0f, 7.0f}, 8.0f };
		EXPECT_EQ(v4, Vector4(5.0f, 6.0f, 7.0f, 8.0f));
	}

	TEST(Vector4_Test, Assignment) {
		Vector4 v{};
		v = 3.0f;
		EXPECT_EQ(v, Vector4(3.0f, 3.0f, 3.0f, 3.0f));
	}

	TEST(Vector4_Test, Unary_Operators) {
		Vector4 v{ 2.0f, -3.0f, 4.0f, -5.0f };
		EXPECT_EQ(+v, v);
		EXPECT_EQ(-v, Vector4(-2.0f, 3.0f, -4.0f, 5.0f));
	}

	TEST(Vector4_Test, Comparison_Operators) {
		Vector4 v1{ 1.0f, 2.0f, 3.0f, 4.0f };
		Vector4 v2{ 1.0f, 2.0f, 3.0f, 4.0f };
		Vector4 v3{ 5.0f, 6.0f, 7.0f, 8.0f };

		EXPECT_TRUE(v1 == v2);
		EXPECT_TRUE(v1 != v3);
	}

	TEST(Vector4_Test, Arithmetic_Operators) {
		Vector4 v1{ 1.0f, 2.0f, 3.0f, 4.0f };
		Vector4 v2{ 5.0f, 6.0f, 7.0f, 8.0f };

		EXPECT_EQ(v1 + v2, Vector4(6.0f, 8.0f, 10.0f, 12.0f));
		EXPECT_EQ(v1 - v2, Vector4(-4.0f, -4.0f, -4.0f, -4.0f));

		EXPECT_EQ(v1 + 2.0f, Vector4(3.0f, 4.0f, 5.0f, 6.0f));
		EXPECT_EQ(3.0f + v1, Vector4(4.0f, 5.0f, 6.0f, 7.0f));
		EXPECT_EQ(v1 - 1.0f, Vector4(0.0f, 1.0f, 2.0f, 3.0f));
		EXPECT_EQ(5.0f - v1, Vector4(4.0f, 3.0f, 2.0f, 1.0f));

		EXPECT_EQ(v1 * v2, Vector4(5.0f, 12.0f, 21.0f, 32.0f));
		EXPECT_EQ(v1 / v2, Vector4(0.2f, 0.3333333f, 0.4285714f, 0.5f));

		EXPECT_EQ(v1 * 2.0f, Vector4(2.0f, 4.0f, 6.0f, 8.0f));
		EXPECT_EQ(3.0f * v1, Vector4(3.0f, 6.0f, 9.0f, 12.0f));
		EXPECT_EQ(v1 / 2.0f, Vector4(0.5f, 1.0f, 1.5f, 2.0f));
		EXPECT_EQ(6.0f / v1, Vector4(6.0f, 3.0f, 2.0f, 1.5f));
	}

	TEST(Vector4_Test, Compound_Assignment_Operator) {
		Vector4 v{ 1.0f, 2.0f, 3.0f, 4.0f };
		v += Vector4{ 5.0f, 6.0f, 7.0f, 8.0f };
		EXPECT_EQ(v, Vector4(6.0f, 8.0f, 10.0f, 12.0f));

		v -= Vector4{ 1.0f, 2.0f, 3.0f, 4.0f };
		EXPECT_EQ(v, Vector4(5.0f, 6.0f, 7.0f, 8.0f));

		v *= 2.0f;
		EXPECT_EQ(v, Vector4(10.0f, 12.0f, 14.0f, 16.0f));

		v /= 4.0f;
		EXPECT_EQ(v, Vector4(2.5f, 3.0f, 3.5f, 4.0f));
	}

	TEST(Vector4_Test, Accessors_Operator) {
		Vector4 v{ 1.0f, 2.0f, 3.0f, 4.0f };
		EXPECT_FLOAT_EQ(v[0], 1.0f);
		EXPECT_FLOAT_EQ(v[1], 2.0f);
		EXPECT_FLOAT_EQ(v[2], 3.0f);
		EXPECT_FLOAT_EQ(v[3], 4.0f);

		v[0] = 5.0f;
		v[3] = 6.0f;
		EXPECT_EQ(v, Vector4(5.0f, 2.0f, 3.0f, 6.0f));
	}

	TEST(Vector4_Test, Dot_Product) {
		Vector4 v1{ 1.0f, 2.0f, 3.0f, 4.0f };
		Vector4 v2{ 5.0f, 6.0f, 7.0f, 8.0f };

		EXPECT_FLOAT_EQ(v1.Dot_Product(v2), 70.0f);
	}

	TEST(Vector4_Test, Homogeneous) {
		Vector4 v{ 2.0f, 4.0f, 6.0f, 2.0f };
		Vector3 hv{ v.Homogeneous() };

		EXPECT_EQ(hv, Vector3(1.0f, 2.0f, 3.0f));
	}

	TEST(Vector4_Test, GettersSetters) {
		Vector4 v;
		v.Set_X(1.0f);
		v.Set_Y(2.0f);
		v.Set_Z(3.0f);
		v.Set_W(4.0f);
		EXPECT_EQ(v.Get_XYZ(), Vector3(1.0f, 2.0f, 3.0f));
		EXPECT_FLOAT_EQ(v.Get_W(), 4.0f);

		v.Set_XYZ(Vector3{ 5.0f, 6.0f, 7.0f });
		EXPECT_EQ(v, Vector4(5.0f, 6.0f, 7.0f, 4.0f));
	}

	TEST(Vector4_Test, IsNaN) {
		float nanVal = std::numeric_limits<float>::quiet_NaN();
		Vector4 v{ 1.0f, nanVal, 3.0f, 4.0f };
		EXPECT_TRUE(v.Is_NaN());
	}

	TEST(Vector4_Test, Static_Constants) {
		EXPECT_EQ(Vector4::ZERO, Vector4(0.0f, 0.0f, 0.0f, 0.0f));
		EXPECT_EQ(Vector4::ONE, Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		EXPECT_EQ(Vector4::UNIT_X, Vector4(1.0f, 0.0f, 0.0f, 0.0f));
		EXPECT_EQ(Vector4::UNIT_Y, Vector4(0.0f, 1.0f, 0.0f, 0.0f));
		EXPECT_EQ(Vector4::UNIT_Z, Vector4(0.0f, 0.0f, 1.0f, 0.0f));
		EXPECT_EQ(Vector4::UNIT_W, Vector4(0.0f, 0.0f, 0.0f, 1.0f));
	}

	TEST(Vector4_Test, Edge_Case) {
		Vector4 Zero{ 0.f };
		const Vector4 Const_Zero{ 0.f };

		EXPECT_DEATH((Zero / Const_Zero), ".*");

		EXPECT_DEATH(Zero[4], ".*");
		EXPECT_DEATH(Const_Zero[4], ".*");

		EXPECT_DEATH(Zero.Homogeneous(), ".*");
	}

}// namespace Core::Math::Vector4_Test