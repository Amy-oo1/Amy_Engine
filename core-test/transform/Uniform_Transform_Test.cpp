#include "gtest/gtest.h"

#include "math/Constant.h"

#include "transform/Uniform_Transform.h"

namespace Core::Transform::Uniform_Transform_Test {

	using NameSpace_Core::NameSpace_Math::Math_PI;
	using NameSpace_Core::NameSpace_Math::Math_PI_DIV_2;

	using namespace NameSpace_Core::NameSpace_Transform;

	TEST(Uniform_Transform_Test, DefaultConstructor) {
		Uniform_Transform t{};

		EXPECT_TRUE(t.Get_Rotation().Is_Equivalence_Rotate(Quaternion::IDENTITY));
		EXPECT_FLOAT_EQ(t.Get_Scale(), 1.0f);
		EXPECT_EQ(t.Get_Translation(), Vector3::ZERO);
	}

	TEST(Uniform_Transform_Test, ScaleTranslationConstructor) {
		ScaleTranslation_Transform st{ 2.5f, Vector3{1.0f, 2.0f, 3.0f} };
		Uniform_Transform t{ st };

		EXPECT_FLOAT_EQ(t.Get_Scale(), 2.5f);
		EXPECT_EQ(t.Get_Translation(), Vector3(1.0f, 2.0f, 3.0f));
		EXPECT_TRUE(t.Get_Rotation().Is_Equivalence_Rotate(Quaternion::IDENTITY));
	}

	TEST(Uniform_Transform_Test, QuaternionScaleTranslationConstructor) {
		Quaternion q{ Quaternion::Generate_By_AxisAngle(Vector3::UNIT_X, Radian{ Math_PI_DIV_2 }) };
		ScaleTranslation_Transform st{ 3.0f, Vector3{4.0f, 5.0f, 6.0f} };
		Uniform_Transform t{ q, st };

		EXPECT_TRUE(t.Get_Rotation().Is_Equivalence_Rotate(q));
		EXPECT_FLOAT_EQ(t.Get_Scale(), 3.0f);
		EXPECT_EQ(t.Get_Translation(), Vector3(4.0f, 5.0f, 6.0f));
	}

	TEST(Uniform_Transform_Test, FullParameterConstructor) {
		Quaternion q{ Quaternion::Generate_By_AxisAngle(Vector3::UNIT_X, Radian{ Math_PI_DIV_2 }) };
		Uniform_Transform t{ q, 2.0f, Vector3{5.0f, 6.0f, 7.0f} };

		EXPECT_TRUE(t.Get_Rotation().Is_Equivalence_Rotate(q));
		EXPECT_FLOAT_EQ(t.Get_Scale(), 2.0f);
		EXPECT_EQ(t.Get_Translation(), Vector3(5.0f, 6.0f, 7.0f));
	}

	TEST(Uniform_Transform_Test, QuaternionAssignment) {
		Uniform_Transform t{ ScaleTranslation_Transform{2.0f, Vector3{1.0f, 2.0f, 3.0f}} };
		Quaternion q{ Quaternion::Generate_By_AxisAngle(Vector3::UNIT_X, Radian{ Math_PI_DIV_2 }) };

		t = q;
		EXPECT_TRUE(t.Get_Rotation().Is_Equivalence_Rotate(q));
		EXPECT_EQ(t.Get_Translation(), Vector3::ZERO);
	}

	TEST(Uniform_Transform_Test, ScaleTranslationAssignment) {
		Uniform_Transform t{ Quaternion::Generate_By_AxisAngle(Vector3::UNIT_X, Radian{ Math_PI_DIV_2 }) };
		ScaleTranslation_Transform st{ 3.0f, Vector3{4.0f, 5.0f, 6.0f} };

		t = st;
		EXPECT_FLOAT_EQ(t.Get_Scale(), 3.0f);
		EXPECT_EQ(t.Get_Translation(), Vector3(4.0f, 5.0f, 6.0f));
		EXPECT_TRUE(t.Get_Rotation().Is_Equivalence_Rotate(Quaternion::IDENTITY)); // ÖØÖÃÐý×ª£¿
	}

	TEST(Uniform_Transform_Test, Equality_Operator) {
		Uniform_Transform t1{
			Quaternion::Generate_By_AxisAngle(Vector3::UNIT_X, Radian{ Math_PI_DIV_2 }),
			ScaleTranslation_Transform{2.0f, Vector3{1.0f, 2.0f, 3.0f}}
		};
		Uniform_Transform t2 = t1;

		Uniform_Transform t3{
			Quaternion::Generate_By_AxisAngle(Vector3::UNIT_X, Radian{ Math_PI_DIV_2 }),
			ScaleTranslation_Transform{2.0f, Vector3{1.0f, 2.0f, 3.0f}}
		};

		Uniform_Transform t4{
			Quaternion::IDENTITY,
			ScaleTranslation_Transform{2.0f, Vector3{1.0f, 2.0f, 3.0f}}
		};

		EXPECT_TRUE(t1 == t2);
		EXPECT_TRUE(t1 == t3);
		EXPECT_TRUE(t1 != t4);
	}

	TEST(Uniform_Transform_Test, SetRotation) {
		Uniform_Transform t{};
		auto q = Quaternion::Generate_By_AxisAngle(Vector3::UNIT_X, Radian{ Math_PI_DIV_2 });
		t.Set_Rotation(q);
		EXPECT_TRUE(t.Get_Rotation().Is_Equivalence_Rotate(q));
	}

	TEST(Uniform_Transform_Test, SetScale) {
		Uniform_Transform t{};
		t.Set_Scale(2.5f);
		EXPECT_FLOAT_EQ(t.Get_Scale(), 2.5f);
		EXPECT_EQ(t.Get_Translation(), Vector3::ZERO);
	}

	TEST(Uniform_Transform_Test, SetTranslation) {
		Uniform_Transform t{};
		t.Set_Translation(Vector3{ 7.0f, 8.0f, 9.0f });
		EXPECT_EQ(t.Get_Translation(), Vector3(7.0f, 8.0f, 9.0f));
		EXPECT_FLOAT_EQ(t.Get_Scale(), 1.0f);
	}

	TEST(Uniform_Transform_Test, HasRotation) {
		Uniform_Transform t1{};
		Uniform_Transform t2{ Quaternion::Generate_By_AxisAngle(Vector3::UNIT_X, Radian{ Math_PI_DIV_2 }) };
		EXPECT_FALSE(t1.Has_Rotation());
		EXPECT_TRUE(t2.Has_Rotation());
	}

	TEST(Uniform_Transform_Test, HasNegativeScale) {
		Uniform_Transform t1{};
		Uniform_Transform t2{ Quaternion::IDENTITY, -1.0f, Vector3::ZERO };
		EXPECT_FALSE(t1.Has_Negative_Scale());
		EXPECT_TRUE(t2.Has_Negative_Scale());
	}

	TEST(Uniform_Transform_Test, GenerateRotationX) {
		auto t = Uniform_Transform::Generate_Rotation_X(Radian{ Math_PI_DIV_2 });
		Quaternion expected = Quaternion::Generate_By_AxisAngle(Vector3::UNIT_X, Radian{ Math_PI_DIV_2 });
		EXPECT_EQ(t.Get_Rotation(), expected);
		EXPECT_FLOAT_EQ(t.Get_Scale(), 1.0f);
		EXPECT_EQ(t.Get_Translation(), Vector3::ZERO);
	}

	TEST(Uniform_Transform_Test, GenerateScale) {
		auto t = Uniform_Transform::Generate_Scale(2.5f);
		EXPECT_FLOAT_EQ(t.Get_Scale(), 2.5f);
		EXPECT_TRUE(t.Get_Rotation().Is_Equivalence_Rotate(Quaternion::IDENTITY));
		EXPECT_EQ(t.Get_Translation(), Vector3::ZERO);
	}

	TEST(Uniform_Transform_Test, StaticIdentity) {
		const auto& identity = Uniform_Transform::IDENTITY;
		EXPECT_TRUE(identity.Get_Rotation().Is_Equivalence_Rotate(Quaternion::IDENTITY));
		EXPECT_FLOAT_EQ(identity.Get_Scale(), 1.0f);
		EXPECT_EQ(identity.Get_Translation(), Vector3::ZERO);
	}

}// namespace Core::Transform::Uniform_Transform_Test