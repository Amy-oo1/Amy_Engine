#include "gtest/gtest.h"

#include "math/Matrix3x3.h"
#include "math/Vector3.h"

namespace Core::Math::Matrix3x3_Test {

	using NameSpace_Core::NameSpace_Math::Vector3;
	using NameSpace_Core::NameSpace_Math::Matrix3x3;

	TEST(Matrix3x3_Test, Constructors) {

		Matrix3x3 m1{};
		EXPECT_EQ(m1[0], Vector3(0.0f, 0.0f, 0.0f));
		EXPECT_EQ(m1[1], Vector3(0.0f, 0.0f, 0.0f));
		EXPECT_EQ(m1[2], Vector3(0.0f, 0.0f, 0.0f));

		Matrix3x3 m2{
			1.0f, 2.0f, 3.0f,
			4.0f, 5.0f, 6.0f,
			7.0f, 8.0f, 9.0f
		};

		EXPECT_EQ(m2[0], Vector3(1.0f, 2.0f, 3.0f));
		EXPECT_EQ(m2[1], Vector3(4.0f, 5.0f, 6.0f));
		EXPECT_EQ(m2[2], Vector3(7.0f, 8.0f, 9.0f));

		Matrix3x3 m3{
			Vector3{1.0f, 2.0f, 3.0f},
			Vector3{4.0f, 5.0f, 6.0f},
			Vector3{7.0f, 8.0f, 9.0f}
		};

		EXPECT_EQ(m3[0], Vector3(1.0f, 2.0f, 3.0f));
		EXPECT_EQ(m3[1], Vector3(4.0f, 5.0f, 6.0f));
		EXPECT_EQ(m3[2], Vector3(7.0f, 8.0f, 9.0f));

		float cArrays[3][3]{
			{1.0f, 2.0f, 3.0f},
			{4.0f, 5.0f, 6.0f},
			{7.0f, 8.0f, 9.0f}
		};

		Matrix3x3 m4{ cArrays };
		EXPECT_EQ(m4[0], Vector3(1.0f, 2.0f, 3.0f));
		EXPECT_EQ(m4[1], Vector3(4.0f, 5.0f, 6.0f));
		EXPECT_EQ(m4[2], Vector3(7.0f, 8.0f, 9.0f));

		float cArray[9]{
			1.0f, 2.0f, 3.0f,
			4.0f, 5.0f, 6.0f,
			7.0f, 8.0f, 9.0f
		};

		Matrix3x3 m5{ cArray };
		EXPECT_EQ(m5[0], Vector3(1.0f, 2.0f, 3.0f));
		EXPECT_EQ(m5[1], Vector3(4.0f, 5.0f, 6.0f));
		EXPECT_EQ(m5[2], Vector3(7.0f, 8.0f, 9.0f));
	}

	TEST(Matrix3x3_Test, Assignment) {
		Matrix3x3 zero{};

		Matrix3x3 add{
			3.f,0.f ,0.f,
			0.f,3.f,0.f,
			0.f,0.f,3.f
		};

		Matrix3x3 ans{
			3.0f, 0.0f, 0.0f,
			0.0f, 3.0f, 0.0f,
			0.0f, 0.0f, 3.0f
		};

		EXPECT_EQ(zero = add, ans);
	}

	TEST(Matrix3x3_Test, Unary_Operators) {
		Matrix3x3 m{
			1.0f, 2.0f, 3.0f,
			4.0f, 5.0f, 6.0f,
			7.0f, 8.0f, 9.0f
		};

		Matrix3x3 un_m{
			-1.0f, -2.0f, -3.0f,
			-4.0f, -5.0f, -6.0f,
			-7.0f, -8.0f, -9.0f
		};

		EXPECT_EQ(+m, m);
		EXPECT_EQ(-m, un_m);
	}

	TEST(Matrix3x3_Test, Comparison_Operators) {
		Matrix3x3 m1{
			1.0f, 2.0f, 3.0f,
			4.0f, 5.0f, 6.0f,
			7.0f, 8.0f, 9.0f
		};
		Matrix3x3 m2{
			1.0f, 2.0f, 3.0f,
			4.0f, 5.0f, 6.0f,
			7.0f, 8.0f, 9.0f
		};
		Matrix3x3 m3{
			9.0f, 8.0f, 7.0f,
			6.0f, 5.0f, 4.0f,
			3.0f, 2.0f, 1.0f
		};
		EXPECT_TRUE(m1 == m2);
		EXPECT_TRUE(m1 != m3);
	}

	TEST(Matrix3x3_Test, Compound_Assignment_Operators) {
		Matrix3x3 T{};

		Matrix3x3 add{
			2.0f, 2.0f, 2.0f,
			2.0f, 2.0f, 2.0f,
			2.0f, 2.0f, 2.0f
		};

		Matrix3x3 sub{
			2.f, 2.f, 2.f,
			2.f, 2.f, 2.f,
			2.f, 2.f, 2.f
		};

		Matrix3x3 mul{
			2.0f, 0.0f, 0.0f,
			0.0f, 2.0f, 0.0f,
			0.0f, 0.0f, 2.0f
		};

		Matrix3x3 ans_add{
			2.0f, 2.0f, 2.0f,
			2.0f, 2.0f, 2.0f,
			2.0f, 2.0f, 2.0f
		};

		Matrix3x3 ans_sub{
			-2.f, -2.f, -2.f,
			-2.f, -2.f, -2.f,
			-2.f, -2.f, -2.f
		};

		Matrix3x3 ans_mul{
			0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f
		};

		EXPECT_EQ(T += add, ans_add);
		T = Matrix3x3::ZERO;

		EXPECT_EQ(T -= sub, ans_sub);
		T = Matrix3x3::ZERO;

		EXPECT_EQ(T *= mul, ans_mul);
		T = Matrix3x3::ZERO;


		EXPECT_EQ(T /= 1.f, Matrix3x3());
		T = Matrix3x3::ZERO;

		EXPECT_EQ(T *= 1.f, Matrix3x3());
		T = Matrix3x3::ZERO;
	}

	TEST(Matrix3x3_Test, Index) {
		Matrix3x3 m{
			1.0f, 2.0f, 3.0f,
			4.0f, 5.0f, 6.0f,
			7.0f, 8.0f, 9.0f
		};
		EXPECT_EQ(m[0], Vector3(1.0f, 2.0f, 3.0f));
		EXPECT_EQ(m[1], Vector3(4.0f, 5.0f, 6.0f));
		EXPECT_EQ(m[2], Vector3(7.0f, 8.0f, 9.0f));
		EXPECT_FLOAT_EQ(m[0][0], 1.0f);
		EXPECT_FLOAT_EQ(m[0][1], 2.0f);
		EXPECT_FLOAT_EQ(m[0][2], 3.0f);
		EXPECT_FLOAT_EQ(m[1][0], 4.0f);
		EXPECT_FLOAT_EQ(m[1][1], 5.0f);
		EXPECT_FLOAT_EQ(m[1][2], 6.0f);
		EXPECT_FLOAT_EQ(m[2][0], 7.0f);
		EXPECT_FLOAT_EQ(m[2][1], 8.0f);
		EXPECT_FLOAT_EQ(m[2][2], 9.0f);
	}

	TEST(Matrix3x3_Test, Arithmetic_Operatiors) {
		Matrix3x3 m1{
			1.0f, 2.0f, 3.0f,
			4.0f, 5.0f, 6.0f,
			7.0f, 8.0f, 9.0f
		};
		Matrix3x3 m2{
			9.0f, 8.0f, 7.0f,
			6.0f, 5.0f, 4.0f,
			3.0f, 2.0f, 1.0f
		};

		Matrix3x3 sum{ m1 + m2 };

		Matrix3x3 ans{
			10.0f, 10.0f, 10.0f,
			10.0f, 10.0f, 10.0f,
			10.0f, 10.0f, 10.0f
		};

		EXPECT_EQ(sum, ans);

		Matrix3x3 diff{ m1 - m2 };

		Matrix3x3 ans2{
			-8.0f, -6.0f, -4.0f,
			-2.0f, 0.0f, 2.0f,
			4.0f, 6.0f, 8.0f
		};

		EXPECT_EQ(diff, ans2);

		Matrix3x3 scaled{ m1 * 2.0f };
		EXPECT_EQ(scaled[0], Vector3(2.0f, 4.0f, 6.0f));
	}

	TEST(Matrix3x3_Test, MatrixVector_Multiplication) {
		Matrix3x3 m{
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f
		};
		Vector3 v{ 2.0f, 3.0f, 4.0f };
		EXPECT_EQ(m * v, v);

		Matrix3x3 m2{
			1.0f, 2.0f, 3.0f,
			4.0f, 5.0f, 6.0f,
			7.0f, 8.0f, 9.0f
		};
		Vector3 v2{ 1.0f, 2.0f, 3.0f };
		EXPECT_EQ(v2 * m2, Vector3(30.0f, 36.0f, 42.0f));
	}

	TEST(Matrix3x3_Test, MatrixMatrix_Multiplication) {
		Matrix3x3 m1{
			1.0f, 2.0f, 3.0f,
			4.0f, 5.0f, 6.0f,
			7.0f, 8.0f, 9.0f
		};
		Matrix3x3 m2{
			9.0f, 8.0f, 7.0f,
			6.0f, 5.0f, 4.0f,
			3.0f, 2.0f, 1.0f
		};

		Matrix3x3 prod{ m1 * m2 };
		EXPECT_EQ(prod[0], Vector3(30.0f, 24.0f, 18.0f));
		EXPECT_EQ(prod[1], Vector3(84.0f, 69.0f, 54.0f));
		EXPECT_EQ(prod[2], Vector3(138.0f, 114.0f, 90.0f));
	}

	TEST(Matrix3x3_Test, Scalar_Division) {
		Matrix3x3 m{
			1.0f, 2.0f, 3.0f,
			4.0f, 5.0f, 6.0f,
			7.0f, 8.0f, 9.0f
		};
		Matrix3x3 div{ m / 2.0f };
		EXPECT_EQ(div[0], Vector3(0.5f, 1.0f, 1.5f));
	}

	TEST(Matrix3x3_Test, Trace) {
		Matrix3x3 m{
			1.0f, 2.0f, 3.0f,
			4.0f, 5.0f, 6.0f,
			7.0f, 8.0f, 9.0f
		};
		EXPECT_FLOAT_EQ(m.Trace(), 15.0f);
	}

	TEST(Matrix3x3_Test, Transpose) {
		Matrix3x3 m{
			1.0f, 2.0f, 3.0f,
			4.0f, 5.0f, 6.0f,
			7.0f, 8.0f, 9.0f
		};

		Matrix3x3 transposed{ m.Transpose() };
		EXPECT_EQ(transposed[0], Vector3(1.0f, 4.0f, 7.0f));
		EXPECT_EQ(transposed[1], Vector3(2.0f, 5.0f, 8.0f));
		EXPECT_EQ(transposed[2], Vector3(3.0f, 6.0f, 9.0f));
	}

	TEST(Matrix3x3_Test, Determinant) {
		Matrix3x3 m{
			2.0f, 0.0f, 0.0f,
			0.0f, 3.0f, 0.0f,
			0.0f, 0.0f, 4.0f
		};

		EXPECT_FLOAT_EQ(m.Determinant(), 24.0f);
	}

	TEST(Matrix3x3_Test, Adjoint) {
		Matrix3x3 m{
			1.0f, 2.0f, 3.0f,
			4.0f, 5.0f, 6.0f,
			7.0f, 8.0f, 9.0f
		};

		Matrix3x3 adj{ m.Adjoint() };
		EXPECT_FLOAT_EQ(adj[0][0], -3.0f);
		EXPECT_FLOAT_EQ(adj[0][1], -6.0f);
		EXPECT_FLOAT_EQ(adj[0][2], -3.0f);
	}

	TEST(Matrix3x3_Test, Inverse) {
		Matrix3x3 m{
			1,2,3,
			0,1,4,
			5,6,0
		};

		Matrix3x3 ans{
			-24.0f, 18.0f, 5.0f,
			20.0f, -15.0f, -4.0f,
			-5.0f, 4.0f, 1.0f
		};

		Matrix3x3 inv{ m.Inverse() };
		EXPECT_EQ(inv, ans);
	}

	TEST(Matrix3x3_Test, GramSchmidt) {
		Matrix3x3 m{
			1.0f, 1.0f, 1.0f,
			0.0f, 1.0f, 1.0f,
			0.0f, 0.0f, 1.0f
		};
		Matrix3x3 ortho{ m.Gram_Schmidt() };

		EXPECT_TRUE(ortho[0].Is_Unit());
		EXPECT_TRUE(ortho[1].Is_Unit());
		EXPECT_TRUE(ortho[2].Is_Unit());

		EXPECT_NEAR(ortho[0].Dot_Product(ortho[1]), 0.0f, 1e-3);
		EXPECT_NEAR(ortho[1].Dot_Product(ortho[2]), 0.0f, 1e-3);
	}

	TEST(Matrix3x3_Test, Minor) {
		Matrix3x3 m{
			1.0f, 2.0f, 3.0f,
			4.0f, 5.0f, 6.0f,
			7.0f, 8.0f, 9.0f
		};

		float minor{ m.Minor(0, 0) };
		EXPECT_FLOAT_EQ(minor, (5.0f * 9.0f - 6.0f * 8.0f));
	}

	TEST(Matrix3x3_Test, Set_Column) {
		Matrix3x3 m{};
		m.Set_Column(0, Vector3{ 1.0f, 2.0f, 3.0f });
		EXPECT_EQ(m.Get_Column(0), Vector3(1.0f, 2.0f, 3.0f));

		m.Set_Column(1, Vector3{ 4.0f, 5.0f, 6.0f });
		EXPECT_EQ(m.Get_Column(1), Vector3(4.0f, 5.0f, 6.0f));

		m.Set_Column(2, 2.0f);
		EXPECT_EQ(m.Get_Column(2), Vector3(2.0f, 2.0f, 2.0f));
	}

	TEST(Matrix3x3_Test, Set_Row) {
		Matrix3x3 m{};
		m.Set_Row(0, Vector3{ 1.0f, 2.0f, 3.0f });
		EXPECT_EQ(m.Get_Row(0), Vector3(1.0f, 2.0f, 3.0f));

		m.Set_Row(1, 4.0f);
		EXPECT_EQ(m.Get_Row(1), Vector3(4.0f, 4.0f, 4.0f));

		m.Set_Row(2, Vector3{ 5.0f, 6.0f, 7.0f });
		EXPECT_EQ(m.Get_Row(2), Vector3(5.0f, 6.0f, 7.0f));
	}

	TEST(Matrix3x3_Test, Is_Singular) {
		Matrix3x3 singular{
			1.0f, 2.0f, 3.0f,
			4.0f, 5.0f, 6.0f,
			 7.0f, 8.0f, 9.0f
		};
		EXPECT_TRUE(singular.Is_Singular());

		Matrix3x3 nonsingular{
			2.0f, 0.0f, 0.0f,
			0.0f, 3.0f, 0.0f,
			0.0f, 0.0f, 4.0f
		};
		EXPECT_FALSE(nonsingular.Is_Singular());
	}

	TEST(Matrix3x3_Test, Generate_Column_Order) {
		Vector3 cols[3]{
			Vector3{1.0f, 4.0f, 7.0f},
			Vector3{2.0f, 5.0f, 8.0f},
			Vector3{3.0f, 6.0f, 9.0f}
		};
		Matrix3x3 m{ Matrix3x3::Generate_Column_Order(cols) };
		EXPECT_EQ(m[0], Vector3(1.0f, 2.0f, 3.0f));
		EXPECT_EQ(m[1], Vector3(4.0f, 5.0f, 6.0f));
		EXPECT_EQ(m[2], Vector3(7.0f, 8.0f, 9.0f));
	}

	TEST(Matrix3x3_Test, Static_Constants) {
		EXPECT_EQ(Matrix3x3::ZERO[0], Vector3(0.0f, 0.0f, 0.0f));
		EXPECT_EQ(Matrix3x3::ZERO[1], Vector3(0.0f, 0.0f, 0.0f));
		EXPECT_EQ(Matrix3x3::ZERO[2], Vector3(0.0f, 0.0f, 0.0f));

		EXPECT_EQ(Matrix3x3::IDENTITY[0], Vector3(1.0f, 0.0f, 0.0f));
		EXPECT_EQ(Matrix3x3::IDENTITY[1], Vector3(0.0f, 1.0f, 0.0f));
		EXPECT_EQ(Matrix3x3::IDENTITY[2], Vector3(0.0f, 0.0f, 1.0f));
	}

	TEST(Matirx3x3_Test, Rdge_Case) {
		Matrix3x3 Zero{ 0.f };
		Matrix3x3 Const_Zero{ 0.f };

		EXPECT_DEATH(Zero / 0.f, ".*");

		EXPECT_DEATH(Zero[4], ".*");
		EXPECT_DEATH(Const_Zero[4], ".*");

		EXPECT_DEATH(Zero.Inverse(), ".*");
		
	}

}//namespace Core::Math::Matrix3x3_Test