#include "pch.h"

#include "math/Degree.h"

namespace NameSpace_Core::NameSpace_Math {

    TEST(Degree_Test, Default_Constructor) {
        Degree degree{};
        EXPECT_FLOAT_EQ(degree.Get_Degree(), 0.0f);
    }

    TEST(Degree_Test, Parameterized_Constructor) {
        Degree degree(45.0f);
        EXPECT_FLOAT_EQ(degree.Get_Degree(), 45.0f);
    }

    TEST(Degree_Test, Copy_Constructor) {
        Degree degree1(90.0f);
        Degree degree2(degree1);
        EXPECT_FLOAT_EQ(degree2.Get_Degree(), 90.0f);
    }

    TEST(Degree_Test, Assignment_Operator) {
        Degree degree1(30.0f);
        Degree degree2{};
        degree2 = degree1;
        EXPECT_FLOAT_EQ(degree2.Get_Degree(), 30.0f);
    }

    TEST(Degree_Test, FloatAssignment_Operator) {
        Degree degree;
        degree = 60.0f;
        EXPECT_FLOAT_EQ(degree.Get_Degree(), 60.0f);
    }

    TEST(Degree_Test, UnaryPlus_SOperator) {
        Degree degree(45.0f);
        Degree result = +degree;
        EXPECT_FLOAT_EQ(result.Get_Degree(), 45.0f);
    }

    TEST(Degree_Test, UnaryMinus_Operator) {
        Degree degree(45.0f);
        Degree result = -degree;
        EXPECT_FLOAT_EQ(result.Get_Degree(), -45.0f);
    }

    TEST(Degree_Test, Equality_Operator) {
        Degree degree1(90.0f);
        Degree degree2(90.0f);
        EXPECT_TRUE(degree1 == degree2);
    }

    TEST(Degree_Test, Inequality_Operator) {
        Degree degree1(90.0f);
        Degree degree2(45.0f);
        EXPECT_TRUE(degree1 != degree2);
    }

    TEST(Degree_Test, LessThan_Operator) {
        Degree degree1(30.0f);
        Degree degree2(60.0f);
        EXPECT_TRUE(degree1 < degree2);
    }

    TEST(DegreeTest, GreaterThanOperator) {
        Degree degree1(60.0f);
        Degree degree2(30.0f);
        EXPECT_TRUE(degree1 > degree2);
    }

    TEST(DegreeTest, AdditionOperator) {
        Degree degree1(30.0f);
        Degree degree2(60.0f);
        Degree result = degree1 + degree2;
        EXPECT_FLOAT_EQ(result.Get_Degree(), 90.0f);
    }

    TEST(DegreeTest, SubtractionOperator) {
        Degree degree1(90.0f);
        Degree degree2(30.0f);
        Degree result = degree1 - degree2;
        EXPECT_FLOAT_EQ(result.Get_Degree(), 60.0f);
    }

    TEST(DegreeTest, MultiplicationOperator) {
        Degree degree(30.0f);
        Degree result = degree * 2.0f;
        EXPECT_FLOAT_EQ(result.Get_Degree(), 60.0f);
    }

    TEST(DegreeTest, DivisionOperator) {
        Degree degree(60.0f);
        Degree result = degree / 2.0f;
        EXPECT_FLOAT_EQ(result.Get_Degree(), 30.0f);
    }

    TEST(DegreeTest, AdditionAssignmentOperator) {
        Degree degree(30.0f);
        degree += Degree(60.0f);
        EXPECT_FLOAT_EQ(degree.Get_Degree(), 90.0f);
    }

    TEST(DegreeTest, SubtractionAssignmentOperator) {
        Degree degree(90.0f);
        degree -= Degree(30.0f);
        EXPECT_FLOAT_EQ(degree.Get_Degree(), 60.0f);
    }

    TEST(DegreeTest, MultiplicationAssignmentOperator) {
        Degree degree(30.0f);
        degree *= 2.0f;
        EXPECT_FLOAT_EQ(degree.Get_Degree(), 60.0f);
    }

    TEST(DegreeTest, DivisionAssignmentOperator) {
        Degree degree(60.0f);
        degree /= 2.0f;
        EXPECT_FLOAT_EQ(degree.Get_Degree(), 30.0f);
    }

    TEST(DegreeTest, IsNaN) {
        Degree degree(std::numeric_limits<float>::quiet_NaN());
        EXPECT_TRUE(degree.Is_NaN());
    }

    TEST(DegreeTest, IsInfinity) {
        Degree degree(std::numeric_limits<float>::infinity());
        EXPECT_TRUE(degree.Is_Infinity());
    }

} // namespace NameSpace_Core::NameSpace_Math