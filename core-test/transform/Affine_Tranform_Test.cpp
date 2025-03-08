#include "gtest/gtest.h"

#include  "math/Constant.h"
#include "transform/Affine_Transform.h"

namespace Core::Transform::Affine_Transform_Test {

	using NameSpace_Core::NameSpace_Math::Math_PI_DIV_2;
	using NameSpace_Core::NameSpace_Math::Math_PI_DIV_4;
	using namespace NameSpace_Core::NameSpace_Transform;

	TEST(Affine_Transform_Test, DefaultConstructor) {
		Affine_Transform t{};
		EXPECT_EQ(t.Get_Basis(), Matrix3x3::IDENTITY);
		EXPECT_EQ(t.Get_Translation(), Vector3::ZERO);
	}

	TEST(Affine_Transform_Test, MatrixBasis_Constructor) {
		Matrix3x3 basis{
			1.0f, 2.0f, 3.0f,
			4.0f, 5.0f, 6.0f,
			7.0f, 8.0f, 9.0f
		};
		Vector3 translate{ 10.0f, 11.0f, 12.0f };

		Affine_Transform t{ basis, translate };
		EXPECT_EQ(t.Get_Basis(), basis);
		EXPECT_EQ(t.Get_Translation(), translate);
	}

	TEST(Affine_Transform_Test, Quaternion_Constructor) {
		Quaternion q = Quaternion::Generate_By_AxisAngle(Vector3::UNIT_X, Radian{ Math_PI_DIV_2 });
		Affine_Transform t{ q };
		Matrix3x3 expected{ q.Get_Rotation_Matrix3x3() };

		EXPECT_EQ(t.Get_Basis(), expected);
		EXPECT_EQ(t.Get_Translation(), Vector3::ZERO);
	}

	TEST(Affine_Transform_Test, TranslationConstructor) {
		Vector3 translate{ 5.0f, 6.0f, 7.0f };
		Affine_Transform t{ translate };

		EXPECT_EQ(t.Get_Basis(), Matrix3x3::IDENTITY);
		EXPECT_EQ(t.Get_Translation(), translate);
	}

	TEST(Affine_Transform_Test, ScaleXYZ_Constructor) {
		Affine_Transform t{ 2.0f, 3.0f, 4.0f, Vector3{5.0f, 6.0f, 7.0f} };
		Matrix3x3 expected{
			2.0f, 0.0f, 0.0f,
			0.0f, 3.0f, 0.0f,
			0.0f, 0.0f, 4.0f
		};

		EXPECT_EQ(t.Get_Basis(), expected);
		EXPECT_EQ(t.Get_Translation(), Vector3(5.0f, 6.0f, 7.0f));
	}

	TEST(Affine_Transform_Test, OrthogonalConversionConstructor) {
		Orthogonal_Transform ot{
			Quaternion::Generate_By_AxisAngle(Vector3::UNIT_Y ,Radian{Math_PI_DIV_4}),
			Vector3{1.0f, 2.0f, 3.0f}
		};

		Affine_Transform t{ ot };
		EXPECT_EQ(t.Get_Basis(), ot.Get_Rotation().Get_Rotation_Matrix3x3());
		EXPECT_EQ(t.Get_Translation(), ot.Get_Translation());
	}

	TEST(Affine_Transform_Test, UniformScaleConversionConstructor) {
		Uniform_Transform ut{ Quaternion::IDENTITY,  2.0f, Vector3{3.0f, 4.0f, 5.0f} };
		Affine_Transform t{ ut };

		Matrix3x3 expected{
			2.0f, 0.0f, 0.0f,
			0.0f, 2.0f, 0.0f,
			0.0f, 0.0f, 2.0f
		};

		EXPECT_EQ(t.Get_Basis(), expected);
		EXPECT_EQ(t.Get_Translation(), Vector3(3.0f, 4.0f, 5.0f));
	}

	TEST(Affine_Transform_Test, QuaternionAssignment) {
		Affine_Transform t;
		Quaternion q = Quaternion::Generate_By_AxisAngle(Vector3::UNIT_X, Radian{ 3.1415926f });
		t = q;

		EXPECT_EQ(t.Get_Basis(), q.Get_Rotation_Matrix3x3());
		EXPECT_EQ(t.Get_Translation(), Vector3::ZERO);
	}

	TEST(Affine_Transform_Test, TranslationAssignment) {
		Affine_Transform t{};
		t = Vector3{ 5.0f, 6.0f, 7.0f };

		EXPECT_EQ(t.Get_Basis(), Matrix3x3::IDENTITY);
		EXPECT_EQ(t.Get_Translation(), Vector3(5.0f, 6.0f, 7.0f));
	}

	TEST(Affine_Transform_Test, Matrix4x4Conversion) {
		Matrix3x3 basis{
			1.0f, 2.0f, 3.0f,
			4.0f, 5.0f, 6.0f,
			7.0f, 8.0f, 9.0f
		};
		Vector3 translate{ 10.0f, 11.0f, 12.0f };
		Affine_Transform t{ basis, translate };

		Matrix4x4 expected{
			1.0f, 2.0f, 3.0f, 10.0f,
			4.0f, 5.0f, 6.0f, 11.0f,
			7.0f, 8.0f, 9.0f, 12.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
		EXPECT_EQ(static_cast<Matrix4x4>(t), expected);
	}

	TEST(Affine_Transform_Test, EqualityOperator) {
		Affine_Transform t1{
			Matrix3x3{
				1.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 1.0f
			},
			Vector3{5.0f, 6.0f, 7.0f}
		};

		Affine_Transform t2 = t1;
		EXPECT_TRUE(t1 == t2);

		Affine_Transform t3{
			Matrix3x3{
				2.0f, 0.0f, 0.0f,
				0.0f, 2.0f, 0.0f,
				0.0f, 0.0f, 2.0f
			},
			Vector3{5.0f, 6.0f, 7.0f}
		};
		EXPECT_TRUE(t1 != t3);
	}

	TEST(Affine_Transform_Test, MultiplicationOperator) {
		Affine_Transform scale{
			Matrix3x3{
				2.0f, 0.0f, 0.0f,
				0.0f, 3.0f, 0.0f,
				0.0f, 0.0f, 4.0f
			},
			Vector3{1.0f, 2.0f, 3.0f}
		};

		Affine_Transform translate{
			Matrix3x3::IDENTITY,
			Vector3{4.0f, 5.0f, 6.0f}
		};

		auto combined = scale * translate;

		Matrix3x3 expected_basis{ scale.Get_Basis() * translate.Get_Basis() };
		Vector3 expected_translation{ scale.Get_Basis() * translate.Get_Translation() + scale.Get_Translation() };

		EXPECT_EQ(combined.Get_Basis(), expected_basis);
		EXPECT_EQ(combined.Get_Translation(), expected_translation);
	}

	TEST(Affine_Transform_Test, Vector3Transformation) {
		Affine_Transform t{
			Matrix3x3{
				2.0f, 0.0f, 0.0f,
				0.0f, 3.0f, 0.0f,
				0.0f, 0.0f, 4.0f
			},
			Vector3{1.0f, 2.0f, 3.0f}
		};

		Vector3 v{ 1.0f, 1.0f, 1.0f };
		Vector3 result{ t * v };
		EXPECT_EQ(result, Vector3(3.0f, 5.0f, 7.0f));
	}

	TEST(Affine_Transform_Test, Vector4Transformation) {
		Affine_Transform t{
			Matrix3x3{
				1.0f, 2.0f, 3.0f,
				4.0f, 5.0f, 6.0f,
				7.0f, 8.0f, 9.0f
			},
			Vector3{10.0f, 11.0f, 12.0f}
		};

		Vector4 v{ 2.0f, 3.0f, 4.0f, 1.0f };
		Vector4 result{ t * v };

		Vector3 expected_xyz{ t.Get_Basis() * Vector3(2.0f, 3.0f, 4.0f) + t.Get_Translation() };
		EXPECT_EQ(result, Vector4(expected_xyz, 1.0f));
	}

	TEST(Affine_Transform_Test, GenerateRotationX) {
		auto t{ Affine_Transform::Generate_Rotation_X(Radian{ Math_PI_DIV_2 }) };
		Matrix3x3 expected{ Quaternion::Generate_By_AxisAngle(Vector3::UNIT_X, Radian{ Math_PI_DIV_2 }).Get_Rotation_Matrix3x3() };

		EXPECT_EQ(t.Get_Basis(), expected);
		EXPECT_EQ(t.Get_Translation(), Vector3::ZERO);
	}

	TEST(Affine_Transform_Test, Static_Identity) {
		auto identity = Affine_Transform::IDENTITY;

		EXPECT_EQ(identity.Get_Basis(), Matrix3x3::IDENTITY);
		EXPECT_EQ(identity.Get_Translation(), Vector3::ZERO);
	}

}// namespace Core::Transform::Affine_Transform_Test