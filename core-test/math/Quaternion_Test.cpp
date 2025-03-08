#include "gtest/gtest.h"

#include<cassert>
#include<cmath>

#include "math/Constant.h"
#include "math/Radian.h"
#include "math/Vector3.h"
#include "math/Matrix3x3.h"
#include "math/Matrix4x4.h"
#include "math/Quaternion.h"


namespace Core::Math::Quaternion_Test {

	using NameSpace_Core::NameSpace_Math::Math_PI;
	using NameSpace_Core::NameSpace_Math::Math_PI_DIV_2;
	using NameSpace_Core::NameSpace_Math::Math_PI_DIV_4;
	using NameSpace_Core::NameSpace_Math::Radian;
	using NameSpace_Core::NameSpace_Math::Vector3;
	using NameSpace_Core::NameSpace_Math::Matrix3x3;
	using NameSpace_Core::NameSpace_Math::Matrix4x4;
	using NameSpace_Core::NameSpace_Math::Quaternion;

	TEST(Quaternion_Test, Constructors) {
		Quaternion q1{};
		EXPECT_FLOAT_EQ(q1.Get_S(), 0.0f);
		EXPECT_EQ(q1.Get_Imaginary_Part(), Vector3(0.0f, 0.0f, 0.0f));

		Quaternion q2{ 1.0f, 2.0f, 3.0f, 4.0f };
		EXPECT_FLOAT_EQ(q2.Get_S(), 1.0f);
		EXPECT_EQ(q2.Get_Imaginary_Part(), Vector3(2.0f, 3.0f, 4.0f));

		Quaternion q3{ Vector3::UNIT_Z, Radian{Math_PI_DIV_2} };
		EXPECT_NEAR(q3.Get_S(), std::cos(Math_PI_DIV_4), 1e-5);

		auto axis = Vector3::UNIT_Z * std::sin(Math_PI_DIV_4);
		EXPECT_NEAR(q3.Get_X(), axis.Get_X(), 1e-5);
		EXPECT_NEAR(q3.Get_Y(), axis.Get_Y(), 1e-5);
		EXPECT_NEAR(q3.Get_Z(), axis.Get_Z(), 1e-5);
	}

	TEST(Quaternion_Test, Assignment_FromMatrix) {
		Matrix3x3 rot_x{
			1.f, 0.f, 0.f,
			0.f, 0.f,-1.f,
			0.f, 1.f, 0.f
		};

		Quaternion q{ rot_x };

		auto [axis, angle] = q.Get_AxisAngle();
		EXPECT_NEAR(angle.Get_Radian(), Math_PI_DIV_2, 1e-5);

		EXPECT_NEAR(axis.Get_X(), Vector3::UNIT_X.Get_X(), 1e-5);
		EXPECT_NEAR(axis.Get_Y(), Vector3::UNIT_X.Get_Y(), 1e-5);
		EXPECT_NEAR(axis.Get_Z(), Vector3::UNIT_X.Get_Z(), 1e-5);
	}

	TEST(Quaternion_Test, Unary_Operators) {
		Quaternion q{ 1.0f, 2.0f, 3.0f, 4.0f };

		EXPECT_EQ(+q, q);
		EXPECT_EQ(-q, Quaternion(-1.0f, -2.0f, -3.0f, -4.0f));
		EXPECT_EQ(~q, Quaternion(1.0f, -2.0f, -3.0f, -4.0f));
	}

	TEST(Quaternion_Test, Arithmetic_Operatiors) {
		Quaternion q1{ 1.0f, 2.0f, 3.0f, 4.0f };
		Quaternion q2{ 5.0f, 6.0f, 7.0f, 8.0f };

		Quaternion sum{ q1 + q2 };
		EXPECT_EQ(sum, Quaternion(6.0f, 8.0f, 10.0f, 12.0f));

		Quaternion prod{ q1 * q2 };
		EXPECT_EQ(prod, Quaternion(-60.0f, 12.0f, 30.0f, 24.0f));
	}

	TEST(Quaternion_Test, VectorRotation) {
		Quaternion q(Vector3::UNIT_Y, Radian(Math_PI));
		Vector3 v(1.0f, 0.0f, 0.0f);
		Vector3 rotated{ q * v };

		EXPECT_NEAR(rotated.Get_X(), -1.0f, 1e-5);
		EXPECT_NEAR(rotated.Get_Y(), 0.0f, 1e-5);
		EXPECT_NEAR(rotated.Get_Z(), 0.0f, 1e-5);
	}

	TEST(Quaternion_Test, Normalize) {
		Quaternion q{ 2.0f, 0.0f, 0.0f, 0.0f };
		Quaternion norm{ q.Normalize() };

		EXPECT_FLOAT_EQ(norm.Length(), 1.0f);
	}

	TEST(Quaternion_Test, Inverse) {
		Quaternion q{ Quaternion::IDENTITY };
		EXPECT_EQ(q.Inverse(), q);

		Quaternion q2{ 1.0f, 1.0f, 0.0f, 0.0f };
		q2.To_Normalize();
		Quaternion inv = { q2.Inverse() };

		Quaternion ans{ q2 * inv };

		EXPECT_NEAR(ans.Get_S(), Quaternion::IDENTITY.Get_S(), 1e-5);
		EXPECT_NEAR(ans.Get_X(), Quaternion::IDENTITY.Get_X(), 1e-5);
		EXPECT_NEAR(ans.Get_Y(), Quaternion::IDENTITY.Get_Y(), 1e-5);
		EXPECT_NEAR(ans.Get_Z(), Quaternion::IDENTITY.Get_Z(), 1e-5);
	}

	TEST(Quaternion_Test, Matrix_Conversion) {
		Quaternion q{ Vector3::UNIT_X, Radian(Math_PI_DIV_2) };
		Matrix3x3 mat{ q.Get_Rotation_Matrix3x3() };
		Matrix3x3 expected{
			1.0f, 0.0f,  0.0f,
			0.0f, 0.0f, -1.0f,
			0.0f, 1.0f,  0.0f
		};

		EXPECT_EQ(mat, expected);
	}

	TEST(Quaternion_Test, AxisAngle_Conversion) {
		Quaternion q{ Vector3::UNIT_X, Radian(Math_PI) };
		auto [axis, angle] = q.Get_AxisAngle();

		EXPECT_NEAR(angle.Get_Radian(), Math_PI, 1e-5);
		EXPECT_NEAR(axis.Get_X(), Vector3::UNIT_X.Get_X(), 1e-5);
		EXPECT_NEAR(axis.Get_Y(), Vector3::UNIT_X.Get_Y(), 1e-5);
		EXPECT_NEAR(axis.Get_Z(), Vector3::UNIT_X.Get_Z(), 1e-5);
	}

	TEST(Quaternion_Test, Nlerp) {
		Quaternion q1{ Quaternion::IDENTITY };
		Quaternion q2{ Vector3::UNIT_Z, Radian{Math_PI_DIV_2} };

		Quaternion result{ Quaternion::Normalized_Lerp(q1, q2, 0.5f, true) };
		Quaternion expected{ Vector3::UNIT_Z, Radian(Math_PI_DIV_4) };

		EXPECT_NEAR(result.Get_S(), expected.Get_S(), 1e-5);
		EXPECT_NEAR(result.Get_X(), expected.Get_X(), 1e-5);
		EXPECT_NEAR(result.Get_Y(), expected.Get_Y(), 1e-5);
		EXPECT_NEAR(result.Get_Z(), expected.Get_Z(), 1e-5);
	}

	TEST(Quaternion_Test, Slerp) {
		Quaternion q1{ Quaternion::IDENTITY };
		Quaternion q2{ Vector3::UNIT_Z, Radian{Math_PI_DIV_2} };

		Quaternion result{ Quaternion::Spherical_Lerp(q1, q2, 0.5f, true) };
		Quaternion expected{ Vector3::UNIT_Z, Radian(Math_PI_DIV_4) };

		EXPECT_NEAR(result.Get_S(), expected.Get_S(), 1e-5);
		EXPECT_NEAR(result.Get_X(), expected.Get_X(), 1e-5);
		EXPECT_NEAR(result.Get_Y(), expected.Get_Y(), 1e-5);
		EXPECT_NEAR(result.Get_Z(), expected.Get_Z(), 1e-5);
	}

	TEST(Quaternion_Test, Static_Constants) {
		EXPECT_EQ(Quaternion::ZERO, Quaternion(0.0f, 0.0f, 0.0f, 0.0f));
		EXPECT_EQ(Quaternion::IDENTITY, Quaternion(1.0f, 0.0f, 0.0f, 0.0f));
	}

	TEST(Quaternion_DeathTest, NormalizeZeroQuaternion) {
		Quaternion zero{ Quaternion::ZERO };
		EXPECT_DEATH(zero.Normalize(), ".*");
	}

	TEST(Quaternion_DeathTest, InverseZeroQuaternion) {
		Quaternion zero{ Quaternion::ZERO };
		EXPECT_DEATH(zero.Inverse(), ".*");
	}

	TEST(Quaternion_DeathTest, ConstructWithZeroAxis) {
		EXPECT_DEATH(Quaternion(Vector3::ZERO, Radian(1.0f)), ".*");
	}

	TEST(Quaternion_DeathTest, InvalidSlerpInput) {
		Quaternion zero{ Quaternion::ZERO };
		Quaternion valid{ 1.0f, 0.0f, 0.0f, 0.0f };

		EXPECT_DEATH(Quaternion::Spherical_Lerp(zero, valid, 0.5f, true), ".*");

		EXPECT_DEATH(Quaternion::Spherical_Lerp(valid, zero, 0.5f, true), ".*");
	}

}// namespace Core::Math::Quaternion_Test