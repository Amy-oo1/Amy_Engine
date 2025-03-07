#include "math/Utilities.h"

#include<cmath>
#include<corecrt_math.h>
#include<algorithm>

namespace NameSpace_Core::NameSpace_Math::NameSpace_Utilities {

	const float Abs(float Value) {
		return std::fabsf(Value);
	}

	const float Ceil(float Value){
		return std::ceil(Value);
	}

	const float Floor(float Value){
		return std::floor(Value);
	}

	const float Sqrt(float Value) {
		return  std::sqrtf(Value);
	}

	const float Pow(float Value, float Index) {
		return std::powf(Value, Index);
	}

	const float Cos(float Value) {
		return std::cosf(Value);
	}

	const float Cos(const Radian& Value) {
		return Cos(Value.Get_Radian());
	}

	const float Sin(float Value) {
		return std::sinf(Value);
	}

	const float Sin(const Radian& Value) {
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

	const bool Real_Equal(float LHS, float RHS, float Tolerance) {
		return std::abs(LHS - RHS) <= Tolerance;
	}

	const float Hypot(float X, float Y){
		return std::hypot(X, Y);
	}

	const float Hypot(float X, float Y, float Z){
		return std::hypot(X, Y, Z);
	}

	const bool Is_NaN(float Value){
		return std::isnan(Value);
	}

	const bool Is_Infinity(float Value){
		return std::isinf(Value);
	}

}// namespace NameSpace_Core::NameSpace_Math::NameSpace_Utilities