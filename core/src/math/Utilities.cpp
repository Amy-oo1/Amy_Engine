#include "math/Utilities.h"

#include<cmath>
#include<corecrt_math.h>
#include<algorithm>

namespace NameSpace_Core::NameSpace_Math::NameSpace_Utilities {

	float Abs(float Value) {
		return std::fabsf(Value);
	}

	float Ceil(float Value) {
		return std::ceil(Value);
	}

	float Floor(float Value) {
		return std::floor(Value);
	}

	float Sqrt(float Value) {
		return  std::sqrtf(Value);
	}

	float Pow(float Value, float Index) {
		return std::powf(Value, Index);
	}

	float Tan(float Value) {
		return std::tan(Value);
	}

	float Tan(const Radian& Value) {
		return Tan(Value.Get_Radian());
	}

	float Cos(float Value) {
		return std::cosf(Value);
	}

	float Cos(const Radian& Value) {
		return Cos(Value.Get_Radian());
	}

	float Sin(float Value) {
		return std::sinf(Value);
	}

	float Sin(const Radian& Value) {
		return Sin(Value.Get_Radian());
	}

	const Radian Acos(float Value) {
		return Radian{ std::acosf(Value) };
	}

	const Radian Asin(float Value) {
		return Radian{ std::asinf(Value) };
	}

	const Radian Atan(float Value) {
		return Radian{ std::atanf(Value) };
	}

	const Radian Atan2(float Y, float X) {
		return Radian{ std::atan2f(Y,X) };
	}

	bool Real_Equal(float LHS, float RHS, float Tolerance) {
		return std::abs(LHS - RHS) <= Tolerance;
	}

	float Hypot(float X, float Y) {
		return std::hypot(X, Y);
	}

	float Hypot(float X, float Y, float Z) {
		return std::hypot(X, Y, Z);
	}

	bool Is_NaN(float Value) {
		return std::isnan(Value);
	}

	bool Is_Infinity(float Value) {
		return std::isinf(Value);
	}

	const Matrix4x4 Make_Look_At(const Vector3& Position, const Vector3& Target, const Vector3& Up) {
		const Vector3 Normalize_Up{ Up.Normalize() };

		Vector3
			F{ (Target - Position).Normalize() },
			S{ F.Cross_Product(Normalize_Up).Normalize() },
			U{ S.Cross_Product(F).Normalize() };

		Matrix4x4 View_Mat{
			Vector4{S,-S.Dot_Product(Position)},
			Vector4{U,-U.Dot_Product(Position)},
			Vector4{-F,F.Dot_Product(Position)},
			Vector4{0.f,0.f,0.f,1.f}
		};

		return View_Mat;
	}

	const Matrix4x4 Make_Perspective_Matrix(Radian FOV, float Aspect, float Z_Near, float Z_Far) {
		float Tan_Hale_FOV_Y{ Tan(FOV.Get_Radian() * 0.5f) };

		Matrix4x4 Ret{ Matrix4x4::ZERO };
		Ret[0][0] = 1.f / (Tan_Hale_FOV_Y * Aspect);
		Ret[1][1] = 1.f / Tan_Hale_FOV_Y;
		Ret[2][2] = (Z_Far /*+ Z_Near*/) / (Z_Near - Z_Far);
		Ret[2][3] = (/*2.f **/ Z_Far * Z_Near) / (Z_Near - Z_Far);
		Ret[3][2] = -1.f;

		return Ret;
	}

	Matrix4x4 makeOrthographicProjectionMatrix01(float left, float right, float bottom, float top, float znear, float zfar)
	{
		float inv_width = 1.0f / (right - left);
		float inv_height = 1.0f / (top - bottom);
		float inv_distance = 1.0f / (zfar - znear);

		float A = 2 * inv_width;
		float B = 2 * inv_height;
		float C = -(right + left) * inv_width;
		float D = -(top + bottom) * inv_height;
		float q = -1 * inv_distance;
		float qn = -znear * inv_distance;

		// NB: This creates 'uniform' orthographic projection matrix,
		// which depth range [-1,1], right-handed rules
		//
		// [ A   0   0   C  ]
		// [ 0   B   0   D  ]
		// [ 0   0   q   qn ]
		// [ 0   0   0   1  ]
		//
		// A = 2 * / (right - left)
		// B = 2 * / (top - bottom)
		// C = - (right + left) / (right - left)
		// D = - (top + bottom) / (top - bottom)
		// q = - 1 / (far - near)
		// qn = - near / (far - near)

		Matrix4x4 proj_matrix = Matrix4x4::ZERO;
		proj_matrix[0][0] = A;
		proj_matrix[0][3] = C;
		proj_matrix[1][1] = B;
		proj_matrix[1][3] = D;
		proj_matrix[2][2] = q;
		proj_matrix[2][3] = qn;
		proj_matrix[3][3] = 1;

		return proj_matrix;
	}

}// namespace NameSpace_Core::NameSpace_Math::NameSpace_Utilities