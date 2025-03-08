#include "gtest/gtest.h"

#include<limits>

#include "math/Vector3.h"
#include "math/Vector4.h"
#include "math/Matrix3x3.h"
#include "math/Matrix4x4.h"


namespace Core::Math::Matrix4x4_Test {

    using NameSpace_Core::NameSpace_Math::Vector3;
    using NameSpace_Core::NameSpace_Math::Vector4;
    using NameSpace_Core::NameSpace_Math::Matrix3x3;
    using NameSpace_Core::NameSpace_Math::Matrix4x4;
    using NameSpace_Core::NameSpace_Math::Matrix4x4;
    TEST(Matrix4x4_Test, Constructors) {
        Matrix4x4 m1{};
        EXPECT_EQ(m1[0], Vector4(0.0f, 0.0f, 0.0f, 0.0f));
        EXPECT_EQ(m1[3], Vector4(0.0f, 0.0f, 0.0f, 0.0f));

        Matrix4x4 m2{
            Vector4(1.0f, 2.0f, 3.0f, 4.0f),
            Vector4(5.0f, 6.0f, 7.0f, 8.0f),
            Vector4(9.0f, 10.0f, 11.0f, 12.0f),
            Vector4(13.0f, 14.0f, 15.0f, 16.0f)
        };
        EXPECT_EQ(m2[1], Vector4(5.0f, 6.0f, 7.0f, 8.0f));

        Matrix4x4 m3{
            1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
            9.0f, 10.0f, 11.0f, 12.0f,
            13.0f, 14.0f, 15.0f, 16.0f
        };
        EXPECT_EQ(m3[2], Vector4(9.0f, 10.0f, 11.0f, 12.0f));
    }

    TEST(Matrix4x4_Test, Assignment_Operators) {
        Matrix4x4 m{};
        m = {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };
        EXPECT_EQ(m, Matrix4x4::IDENTITY);

        float arr[16] = {
            2.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 2.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 2.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 2.0f
        };
        m = arr;
        EXPECT_EQ(m[0][0], 2.0f);
    }

    TEST(Matrix4x4_Test, Unary_Operators) {
        Matrix4x4 m{
            1.0f, -2.0f, 3.0f, -4.0f,
            5.0f, -6.0f, 7.0f, -8.0f,
            9.0f, -10.0f, 11.0f, -12.0f,
            13.0f, -14.0f, 15.0f, -16.0f
        };
        EXPECT_EQ(+m, m);
        EXPECT_EQ(-m[0], Vector4(-1.0f, 2.0f, -3.0f, 4.0f));
    }

    TEST(Matrix4x4_Test, Comparison_Operators) {
        Matrix4x4 m1{ Matrix4x4::IDENTITY };
        Matrix4x4 m2{
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };
        Matrix4x4 m3{
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f
        };
        EXPECT_TRUE(m1 == m2);
        EXPECT_TRUE(m1 != m3);
    }

    TEST(Matrix4x4_Test, ArithmeticOperations) {
        Matrix4x4 m1{
            1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
            9.0f, 10.0f, 11.0f, 12.0f,
            13.0f,14.0f, 15.0f, 16.0f
        };
        Matrix4x4 m2 = m1 * 2.0f;
        EXPECT_EQ(m2[0], Vector4(2.0f, 4.0f, 6.0f, 8.0f));

        Matrix4x4 m3 = m1 + m2;
        EXPECT_EQ(m3[1], Vector4(15.0f, 18.0f, 21.0f, 24.0f));
    }

    TEST(Matrix4x4_Test, MatrixVector_Multiplication) {
        Matrix4x4 m{
            2.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 3.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 4.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 5.0f
        };
        Vector4 v{ 1.0f, 2.0f, 3.0f, 4.0f };
        EXPECT_EQ(m * v, Vector4(2.0f, 6.0f, 12.0f, 20.0f));
    }

    TEST(Matrix4x4_Test, MatrixMatrix_Multiplication) {
        Matrix4x4 m1{
            1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
            9.0f, 10.0f, 11.0f, 12.0f,
            13.0f, 14.0f, 15.0f, 16.0f
        };
        Matrix4x4 m2{ m1 * Matrix4x4::IDENTITY };
        EXPECT_EQ(m2, m1);
    }

    TEST(Matrix4x4_Test, Trace) {
        Matrix4x4 m{
            1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
            9.0f, 10.0f, 11.0f, 12.0f,
            13.0f, 14.0f, 15.0f, 16.0f
        };
        EXPECT_FLOAT_EQ(m.Trace(), 1.0f + 6.0f + 11.0f + 16.0f);
    }

    TEST(Matrix4x4_Test, Transpose) {
        Matrix4x4 m{
            1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
            9.0f, 10.0f, 11.0f, 12.0f,
            13.0f, 14.0f, 15.0f, 16.0f
        };
        Matrix4x4 transposed{ m.Transpose() };
        EXPECT_EQ(transposed.Get_Column(0), Vector4(1.0f, 2.0f, 3.0f, 4.0f));
    }

    TEST(Matrix4x4_Test, Determinant) {
        Matrix4x4 diag{
            2.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 3.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 4.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 5.0f
        };
        EXPECT_FLOAT_EQ(diag.Determinant(), 2.0f * 3.0f * 4.0f * 5.0f);

        Matrix4x4 singular{
            1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
            9.0f, 10.0f, 11.0f, 12.0f,
            13.0f, 14.0f, 15.0f, 16.0f
        };
        EXPECT_FLOAT_EQ(singular.Determinant(), 0.0f);
    }

    TEST(Matrix4x4_Test, Adjoint) {
        Matrix4x4 m{
            2.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 3.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 4.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 5.0f
        };
        Matrix4x4 adj{ m.Adjoint() };
        EXPECT_EQ(adj[0][0], 3.0f * 4.0f * 5.0f);
    }

    TEST(Matrix4x4_Test, Inverse) {
        Matrix4x4 m{
            2.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 3.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 4.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 5.0f
        };
        Matrix4x4 inv{ m.Inverse() };

        EXPECT_FLOAT_EQ(inv[0][0], 1.0f / 2.0f);
        EXPECT_FLOAT_EQ(inv[3][3], 1.0f / 5.0f);
    }

    TEST(Matrix4x4_Test, Minor) {
        Matrix4x4 m{
            1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
            9.0f, 10.0f, 11.0f, 12.0f,
            13.0f, 14.0f, 15.0f, 16.0f
        };
        float minor{ m.Minor(0, 0) };
        Matrix3x3 sub{
            6.0f, 7.0f, 8.0f,
            10.0f, 11.0f, 12.0f,
            14.0f, 15.0f, 16.0f
        };

        EXPECT_FLOAT_EQ(minor, sub.Determinant());
    }

    TEST(Matrix4x4_Test, GetSet_RowColumn) {
        Matrix4x4 m{};

        m.Set_Row(0, Vector4(1.0f, 2.0f, 3.0f, 4.0f));
        EXPECT_EQ(m.Get_Row(0), Vector4(1.0f, 2.0f, 3.0f, 4.0f));

        m.Set_Row(1, 5.0f);
        EXPECT_EQ(m.Get_Row(1), Vector4(5.0f, 5.0f, 5.0f, 5.0f));

        m.Set_Column(2, Vector3{ 6.0f, 7.0f, 8.0f }, 9.0f);
        EXPECT_EQ(m.Get_Column(2), Vector4(6.0f, 7.0f, 8.0f, 9.0f));
    }

    TEST(Matrix4x4_Test, GetLeftTopMatrix3x3) {
        Matrix4x4 m{
            1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
            9.0f, 10.0f, 11.0f, 12.0f,
            13.0f, 14.0f, 15.0f, 16.0f
        };
        Matrix3x3 sub{ m.Get_LeftTop_Matrix3x3() };

        EXPECT_EQ(sub[0], Vector3(1.0f, 2.0f, 3.0f));
        EXPECT_EQ(sub[2], Vector3(9.0f, 10.0f, 11.0f));
    }

    TEST(Matrix4x4_Test, Generate_ColumnOrder) {
        Vector4 cols[4]{
            Vector4(1.0f, 5.0f, 9.0f, 13.0f),
            Vector4(2.0f, 6.0f, 10.0f, 14.0f),
            Vector4(3.0f, 7.0f, 11.0f, 15.0f),
            Vector4(4.0f, 8.0f, 12.0f, 16.0f)
        };

        Matrix4x4 m{ Matrix4x4::Generate_Column_Order(cols) };

        EXPECT_EQ(m.Get_Column(0), cols[0]);
        EXPECT_EQ(m[0], Vector4(1.0f, 2.0f, 3.0f, 4.0f));
    }

    TEST(Matrix4x4_Test, Static_Constants) {
        EXPECT_EQ(Matrix4x4::ZERO[0], Vector4(0.0f, 0.0f, 0.0f, 0.0f));
        EXPECT_EQ(Matrix4x4::IDENTITY[0], Vector4(1.0f, 0.0f, 0.0f, 0.0f));
        EXPECT_EQ(Matrix4x4::IDENTITY[3], Vector4(0.0f, 0.0f, 0.0f, 1.0f));
    }

    TEST(Matrix4x4_Test, Edge_Cases) {

        Matrix4x4 zero = Matrix4x4::ZERO;
        EXPECT_TRUE(zero.Is_Singular());

        EXPECT_DEATH(zero.Inverse(), ".*");
    }

}// namespace Core::Math::Matrix4x4_Test