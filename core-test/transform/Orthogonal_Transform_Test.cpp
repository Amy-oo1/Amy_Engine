//#include "gtest/gtest.h"
//
//#include "transform/Orthogonal_Transform.h"
//
//namespace Core::Transform::Orthogonal_Transform_ {
//
//    using namespace NameSpace_Core::NameSpace_Transform;
//
//    TEST(OrthogonalTransform, DefaultConstructor) {
//        Orthogonal_Transform t;
//        EXPECT_EQ(t.Get_Rotation(), Quaternion::IDENTITY);
//        EXPECT_EQ(t.Get_Translation(), Vector3::ZERO);
//    }
//
//    TEST(OrthogonalTransform, RotationTranslationConstructor) {
//        Quaternion q = Quaternion::Generate_By_AxisAngle(Vector3::UNIT_X, Radian(Math_PI / 2));
//        Vector3 trans(1.0f, 2.0f, 3.0f);
//        Orthogonal_Transform t(q, trans);
//
//        EXPECT_EQ(t.Get_Rotation(), q);
//        EXPECT_EQ(t.Get_Translation(), trans);
//    }
//
//    TEST(OrthogonalTransform, TranslationOnlyConstructor) {
//        Vector3 trans(5.0f, 6.0f, 7.0f);
//        Orthogonal_Transform t(trans);
//
//        EXPECT_EQ(t.Get_Rotation(), Quaternion::IDENTITY);
//        EXPECT_EQ(t.Get_Translation(), trans);
//    }
//
//    TEST(OrthogonalTransform, AssignmentOperators) {
//    
//        Quaternion q = Quaternion::Generate_By_AxisAngle(Vector3::UNIT_Y, Radian(Math_PI));
//        Orthogonal_Transform t1;
//        t1 = q;
//        EXPECT_EQ(t1.Get_Rotation(), q);
//        EXPECT_EQ(t1.Get_Translation(), Vector3::ZERO);
//
//    
//        Vector3 trans(2.0f, 3.0f, 4.0f);
//        Orthogonal_Transform t2;
//        t2 = trans;
//        EXPECT_EQ(t2.Get_Rotation(), Quaternion::IDENTITY);
//        EXPECT_EQ(t2.Get_Translation(), trans);
//    }
//
//    TEST(OrthogonalTransform, InverseOperator) {
//        Quaternion q = Quaternion::Generate_By_AxisAngle(Vector3::UNIT_Z, Radian(Math_PI / 3));
//        Vector3 trans(2.0f, 3.0f, 4.0f);
//        Orthogonal_Transform t(q, trans);
//        Orthogonal_Transform inv = ~t;
//
//
//        EXPECT_TRUE(inv.Get_Rotation().IsApproximatelyEqual(q.Conjugation(), 1e-5f));
//        EXPECT_TRUE(inv.Get_Translation().IsApproximatelyEqual(-(q.Conjugation() * trans), 1e-5f));
//    }
//
//    TEST(OrthogonalTransform, ComparisonOperators) {
//        Quaternion q1 = Quaternion::Generate_By_AxisAngle(Vector3::UNIT_X, Radian(0.5f));
//        Quaternion q2 = Quaternion::Generate_By_AxisAngle(Vector3::UNIT_Y, Radian(1.0f));
//        Vector3 trans1(1.0f, 2.0f, 3.0f);
//        Vector3 trans2(4.0f, 5.0f, 6.0f);
//
//        Orthogonal_Transform t1(q1, trans1);
//        Orthogonal_Transform t2(q1, trans1);
//        Orthogonal_Transform t3(q2, trans1);
//        Orthogonal_Transform t4(q1, trans2);
//
//        EXPECT_TRUE(t1 == t2);
//        EXPECT_TRUE(t1 != t3);
//        EXPECT_TRUE(t1 != t4);
//    }
//
//    TEST(OrthogonalTransform, CompositionOperator) {
//     
//        Orthogonal_Transform t1(
//            Quaternion::Generate_By_AxisAngle(Vector3::UNIT_X, Radian(Math_PI / 2)),
//            Vector3(1.0f, 0.0f, 0.0f)
//        );
//        Orthogonal_Transform t2(
//            Quaternion::Generate_By_AxisAngle(Vector3::UNIT_Y, Radian(Math_PI / 2)),
//            Vector3(0.0f, 1.0f, 0.0f)
//        );
//
//      
//        Orthogonal_Transform combined = t1 * t2;
//
//   
//        Quaternion expected_rot = t1.Get_Rotation() * t2.Get_Rotation();
//        Vector3 expected_trans = t1.Get_Rotation() * t2.Get_Translation() + t1.Get_Translation();
//
//        EXPECT_TRUE(combined.Get_Rotation().IsApproximatelyEqual(expected_rot, 1e-5f));
//        EXPECT_TRUE(combined.Get_Translation().IsApproximatelyEqual(expected_trans, 1e-5f));
//    }
//
//    TEST(OrthogonalTransform, VectorTransformation) {
//     
//        Orthogonal_Transform t(
//            Quaternion::Generate_By_AxisAngle(Vector3::UNIT_Z, Radian(Math_PI / 2)),
//            Vector3(2.0f, 3.0f, 4.0f)
//        );
//
//       
//        Vector3 vec(1.0f, 0.0f, 0.0f);
//        Vector3 transformed = t * vec;
//        Vector3 expected_vec(0.0f, 1.0f, 0.0f);
//        EXPECT_TRUE(transformed.IsApproximatelyEqual(expected_vec, 1e-5f));
//
//     
//        Vector4 point(1.0f, 0.0f, 0.0f, 1.0f);
//        Vector4 transformed_point = t * point;
//        Vector4 expected_point(2.0f, 4.0f, 4.0f, 1.0f); // (0,1,0) + (2,3,4)
//        EXPECT_TRUE(transformed_point.IsApproximatelyEqual(expected_point, 1e-5f));
//    }
//
//    TEST(OrthogonalTransform, MatrixConversion) {
//        Quaternion q = Quaternion::Generate_By_AxisAngle(Vector3::UNIT_X, Radian(Math_PI / 3));
//        Vector3 trans(5.0f, 6.0f, 7.0f);
//        Orthogonal_Transform t(q, trans);
//
//      
//        Matrix4x4 mat = t.Get_Matrix4x4();
//        Matrix4x4 expected = q.Get_Rotation_Matrix4x4();
//        expected[3] = Vector4(trans, 1.0f);
//
//        EXPECT_TRUE(mat.IsApproximatelyEqual(expected, 1e-5f));
//    }
//
//    TEST(OrthogonalTransform, StaticGenerators) {
//     
//        Radian angle(Math_PI / 4);
//        Orthogonal_Transform rotX = Orthogonal_Transform::Generate_Rotation_X(angle);
//        EXPECT_TRUE(rotX.Get_Rotation().IsApproximatelyEqual(
//            Quaternion::Generate_By_AxisAngle(Vector3::UNIT_X, angle),
//            1e-5f
//        ));
//        EXPECT_EQ(rotX.Get_Translation(), Vector3::ZERO);
//
//    
//        Vector3 trans(10.0f, 20.0f, 30.0f);
//        Orthogonal_Transform translate = Orthogonal_Transform::Generate_Translation(trans);
//        EXPECT_EQ(translate.Get_Rotation(), Quaternion::IDENTITY);
//        EXPECT_EQ(translate.Get_Translation(), trans);
//    }
//
//    TEST(OrthogonalTransform, IdentityCheck) {
//        EXPECT_EQ(Orthogonal_Transform::IDENTITY.Get_Rotation(), Quaternion::IDENTITY);
//        EXPECT_EQ(Orthogonal_Transform::IDENTITY.Get_Translation(), Vector3::ZERO);
//        EXPECT_TRUE(Orthogonal_Transform::IDENTITY.Get_Matrix4x4().IsApproximatelyEqual(Matrix4x4::IDENTITY, 1e-5f));
//    }
//
//}// namespace Core::Transform::Orthogonal_Transform