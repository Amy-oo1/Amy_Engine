#include "gtest/gtest.h"

#include "math/Constant.h"
#include "transform/Orthogonal_Transform.h"

namespace Core::Transform::Orthogonal_Transform_Test {

    using NameSpace_Core::NameSpace_Math::Math_PI;
    using namespace NameSpace_Core::NameSpace_Transform;

    TEST(Orthogonal_Transform_Test, Default_Constructor) {
        Orthogonal_Transform t{};
        EXPECT_EQ(t.Get_Rotation(), Quaternion::IDENTITY);
        EXPECT_EQ(t.Get_Translation(), Vector3::ZERO);
    }

    TEST(Orthogonal_Transform_Test, RotationTranslation_Constructor) {
        Quaternion q{ Quaternion::Generate_By_AxisAngle(Vector3::UNIT_X, Radian(Math_PI / 2)) };
        Vector3 trans{ 1.0f, 2.0f, 3.0f };
        Orthogonal_Transform t{ q, trans };

        EXPECT_EQ(t.Get_Rotation(), q);
        EXPECT_EQ(t.Get_Translation(), trans);
    }

    TEST(Orthogonal_Transform_Test, Translation_OnlyConstructor) {
        Vector3 trans{ 5.0f, 6.0f, 7.0f };
        Orthogonal_Transform t{ trans };

        EXPECT_EQ(t.Get_Rotation(), Quaternion::IDENTITY);
        EXPECT_EQ(t.Get_Translation(), trans);
    }

    TEST(Orthogonal_Transform_Test, Assignment_Operators) {
    
        Quaternion q{ Quaternion::Generate_By_AxisAngle(Vector3::UNIT_Y, Radian(Math_PI)) };
        Orthogonal_Transform t1{};
        t1 = q;
        EXPECT_EQ(t1.Get_Rotation(), q);
        EXPECT_EQ(t1.Get_Translation(), Vector3::ZERO);

    
        Vector3 trans{ 2.0f, 3.0f, 4.0f };
        Orthogonal_Transform t2{};
        t2 = trans;
        EXPECT_EQ(t2.Get_Rotation(), Quaternion::IDENTITY);
        EXPECT_EQ(t2.Get_Translation(), trans);
    }

    TEST(Orthogonal_Transform_Test, Inverse_Operator) {
        Quaternion q{ Quaternion::Generate_By_AxisAngle(Vector3::UNIT_Z, Radian(Math_PI / 3)) };
        Vector3 trans{ 2.0f, 3.0f, 4.0f };

        Orthogonal_Transform t(q, trans);
        Orthogonal_Transform inv = ~t;

        EXPECT_EQ(inv.Get_Rotation(), ~q);
    }

    TEST(Orthogonal_Transform_Test, Comparison_Operators) {
        Quaternion q1{ Quaternion::Generate_By_AxisAngle(Vector3::UNIT_X, Radian(0.5f)) };
        Quaternion q2 { Quaternion::Generate_By_AxisAngle(Vector3::UNIT_Y, Radian(1.0f))};
        Vector3 trans1{ 1.0f, 2.0f, 3.0f };
        Vector3 trans2{ 4.0f, 5.0f, 6.0f };

        Orthogonal_Transform t1{ q1, trans1 };
        Orthogonal_Transform t2{ q1, trans1 };
        Orthogonal_Transform t3{ q2, trans1 };
        Orthogonal_Transform t4{ q1, trans2 };

        EXPECT_TRUE(t1 == t2);
        EXPECT_TRUE(t1 != t3);
        EXPECT_TRUE(t1 != t4);
    }

    TEST(Orthogonal_Transform_Test, Composition_Operator) {
     
        Orthogonal_Transform t1{
            Quaternion::Generate_By_AxisAngle(Vector3::UNIT_X, Radian(Math_PI / 2)),
            Vector3(1.0f, 0.0f, 0.0f)
        };
        Orthogonal_Transform t2{
            Quaternion::Generate_By_AxisAngle(Vector3::UNIT_Y, Radian(Math_PI / 2)),
            Vector3(0.0f, 1.0f, 0.0f)
        };

      
        Orthogonal_Transform combined{ t1 * t2 };

   
        Quaternion expected_rot{ t1.Get_Rotation() * t2.Get_Rotation() };
        Vector3 expected_trans{ t1.Get_Rotation() * t2.Get_Translation() + t1.Get_Translation() };

        EXPECT_EQ(combined.Get_Rotation(), expected_rot);
        EXPECT_EQ(combined.Get_Translation(), expected_trans);
    }

    TEST(Orthogonal_Transform_Test, Vector_Transformation) {
     
        Orthogonal_Transform t{
            Quaternion::Generate_By_AxisAngle(Vector3::UNIT_Z, Radian(Math_PI / 2)),
            Vector3{2.0f, 3.0f, 4.0f}
        };

        Vector4 point{ 1.0f, 0.0f, 0.0f, 1.0f };
        Vector4 transformed_point{ t * point };
        Vector4 expected_point{ 2.0f, 4.0f, 4.0f, 1.0f };

		EXPECT_NEAR(transformed_point.Get_X(), expected_point.Get_X(), 1e-5f);
		EXPECT_NEAR(transformed_point.Get_Y(), expected_point.Get_Y(), 1e-5f);
		EXPECT_NEAR(transformed_point.Get_Z(), expected_point.Get_Z(), 1e-5f);
    }

    TEST(Orthogonal_Transform_Test, Static_Generators) {
     
        Radian angle{ Math_PI / 4 };
        Orthogonal_Transform rotX{ Orthogonal_Transform::Generate_Rotation_X(angle) };

        auto expected{ Quaternion::Generate_By_AxisAngle(Vector3::UNIT_X, angle) };

		EXPECT_EQ(rotX.Get_Rotation(), expected);
        EXPECT_EQ(rotX.Get_Translation(), Vector3::ZERO);

    
        Vector3 trans{ 10.0f, 20.0f, 30.0f };

        Orthogonal_Transform translate{ Orthogonal_Transform::Generate_Translation(trans) };
        EXPECT_EQ(translate.Get_Rotation(), Quaternion::IDENTITY);
        EXPECT_EQ(translate.Get_Translation(), trans);
    }

    TEST(Orthogonal_Transform_Test, IdentityCheck) {
        EXPECT_EQ(Orthogonal_Transform::IDENTITY.Get_Rotation(), Quaternion::IDENTITY);
        EXPECT_EQ(Orthogonal_Transform::IDENTITY.Get_Translation(), Vector3::ZERO);
        EXPECT_EQ(Orthogonal_Transform::IDENTITY.Get_Matrix4x4(), Matrix4x4::IDENTITY);
    }

}// namespace Core::Transform::Orthogonal_Transform_Test