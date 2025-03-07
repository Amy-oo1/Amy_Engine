#pragma once

#include<initializer_list>
#include<limits>

#include "math/Constant.h"
#include "math/Radian.h"
#include "math/Vector2.h"
#include "math/Vector3.h"
#include "math/Vector4.h"

namespace NameSpace_Core::NameSpace_Math::NameSpace_Utilities {

	using std::initializer_list;

	const float Abs(float Value);
	const float Ceil(float Value);
	const float Floor(float Value);

	const float Sqrt(float Value);

	const float Pow(float Value, float Index);

	const float Cos(float Value);
	const float Cos(const Radian& Value);
	const float Sin(float Value);
	const float Sin(const Radian& Value);

	const Radian Acos(float Value);
	const Radian Asin(float Value);
	const Radian Atan(float Value);
	const Radian Atan2(float Y, float X);

	const bool Real_Equal(float LHS, float RHS, float Tolerance = std::numeric_limits<float>::epsilon());

	const float Hypot(float X, float Y);
	const float Hypot(float X, float Y, float Z);

	template<typename T>
	const T Get_NaN(void) {
		return std::numeric_limits<T>::quiet_NaN();
	}

	const bool Is_NaN(float Value);

	const bool Is_Infinity(float Value);

	template<class T>
	inline const T Min(const T& LHS, const T& RHS) {
		return LHS < RHS ? LHS : RHS;
	}

	template<typename T>
	inline const T Min(const initializer_list<T>& List) {
		T Min_Value = *List.begin();

		for (const T& Value : List)
			Min_Value = Min(Min_Value, Value);

		return Min_Value;
	}

	template<typename T>
	inline const T Max(const T& L_HS, const T& R_HS) {
		return L_HS > R_HS ? L_HS : R_HS;
	}

	template<typename T>
	inline const T Max(const initializer_list<T>& List) {
		T Max_Value = *List.begin();

		for (const T& Value : List)
			Max_Value = Max(Max_Value, Value);

		return Max_Value;
	}

	template<>
	inline const Vector2 Min<Vector2>(const Vector2& L_HS, const Vector2& R_HS) {
		return Vector2{
			Min(L_HS.Get_X(), R_HS.Get_X()),
			Min(L_HS.Get_Y(), R_HS.Get_Y())
		};
	}

	template<>
	inline const Vector2 Min<Vector2>(const initializer_list<Vector2>& List) {
		Vector2 Min_Value = *List.begin();

		for (const Vector2& Value : List)
			Min_Value = Min(Min_Value, Value);

		return Min_Value;
	}

	template<>
	inline const Vector2 Max<Vector2>(const Vector2& L_HS, const Vector2& R_HS) {
		return Vector2{
			Max(L_HS.Get_X(), R_HS.Get_X()),
			Max(L_HS.Get_Y(), R_HS.Get_Y())
		};
	}

	template<>
	inline const Vector2 Max<Vector2>(const initializer_list<Vector2>& List) {
		Vector2 Max_Value = *List.begin();

		for (const Vector2& Value : List)
			Max_Value = Max(Max_Value, Value);

		return Max_Value;
	}

	template<>
	inline const Vector3 Min<Vector3>(const Vector3& L_HS, const Vector3& R_HS) {
		return Vector3{
			Min(L_HS.Get_X(), R_HS.Get_X()),
			Min(L_HS.Get_Y(), R_HS.Get_Y()),
			Min(L_HS.Get_Z(), R_HS.Get_Z())
		};
	}

	template<>
	inline const Vector3 Min<Vector3>(const initializer_list<Vector3>& List) {
		Vector3 Min_Value = *List.begin();

		for (const Vector3& Value : List)
			Min_Value = Min(Min_Value, Value);

		return Min_Value;
	}

	template<>
	inline const Vector3 Max<Vector3>(const Vector3& L_HS, const Vector3& R_HS) {
		return Vector3{
			Max(L_HS.Get_X(), R_HS.Get_X()),
			Max(L_HS.Get_Y(), R_HS.Get_Y()),
			Max(L_HS.Get_Z(), R_HS.Get_Z())
		};
	}

	template<>
	inline const Vector3 Max<Vector3>(const initializer_list<Vector3>& List) {
		Vector3 Max_Value = *List.begin();

		for (const Vector3& Value : List)
			Max_Value = Max(Max_Value, Value);

		return Max_Value;
	}

	template<>
	inline const Vector4 Min<Vector4>(const Vector4& L_HS, const Vector4& R_HS) {
		return Vector4{
			Min(L_HS.Get_X(), R_HS.Get_X()),
			Min(L_HS.Get_Y(), R_HS.Get_Y()),
			Min(L_HS.Get_Z(), R_HS.Get_Z()),
			Min(L_HS.Get_W(), R_HS.Get_W())
		};
	}

	template<>
	inline const Vector4 Min<Vector4>(const initializer_list<Vector4>& List) {
		Vector4 Min_Value = *List.begin();

		for (const Vector4& Value : List)
			Min_Value = Min(Min_Value, Value);

		return Min_Value;
	}

	template<>
	inline const Vector4 Max<Vector4>(const Vector4& L_HS, const Vector4& R_HS) {
		return Vector4{
			Max(L_HS.Get_X(), R_HS.Get_X()),
			Max(L_HS.Get_Y(), R_HS.Get_Y()),
			Max(L_HS.Get_Z(), R_HS.Get_Z()),
			Max(L_HS.Get_W(), R_HS.Get_W())
		};
	}

	template<>
	inline const Vector4 Max<Vector4>(const initializer_list<Vector4>& List) {
		Vector4 Max_Value = *List.begin();

		for (const Vector4& Value : List)
			Max_Value = Max(Max_Value, Value);

		return Max_Value;
	}

	template<typename T>
	inline const T Sign(const T& Value) {
		return Value < 0 ? static_cast<T>(-1) : static_cast<T>(1);
	}

	template<typename T>
	inline const T Lerp(const T& LHS, const T& RHS, float Alpha) {
		return LHS + (RHS - LHS) * Alpha;
	}

	template<typename T>
	inline const T Clamp(const T& Value, const T& Min, const T& Max) {
		return Value < Min ? Min : (Value > Max ? Max : Value);
	}

}// namespace NameSpace_Core::NameSpace_Math::NameSpace_Utilities