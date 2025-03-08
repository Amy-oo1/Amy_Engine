#pragma once

#include<initializer_list>

#include "math/Head_Math.h"

namespace NameSpace_Core::NameSpace_Bounding {

	using std::initializer_list;

	using NameSpace_Math::Vector3;

	class AxisAligned_Bounding_Box final {
	public:
		AxisAligned_Bounding_Box(void) = default;

		AxisAligned_Bounding_Box(const AxisAligned_Bounding_Box&) = default;
		AxisAligned_Bounding_Box(AxisAligned_Bounding_Box&&) = default;

		AxisAligned_Bounding_Box& operator=(const AxisAligned_Bounding_Box&) = default;
		AxisAligned_Bounding_Box& operator=(AxisAligned_Bounding_Box&&) = default;

		AxisAligned_Bounding_Box(const Vector3& Min, const Vector3& Max);

		~AxisAligned_Bounding_Box(void) = default;

	public:
		void Add_Point(const Vector3& Point);
		void Add_Point(const initializer_list<Vector3>& Points);

		void Add_Bounding_Box(const AxisAligned_Bounding_Box& Box);

	public:
		const Vector3 Get_Min(void)const;
		const Vector3 Get_Max(void)const;

		const Vector3 Get_Center(void)const;
		const Vector3 Get_Dimensions(void)const;

	public:
		static const AxisAligned_Bounding_Box Union(const AxisAligned_Bounding_Box& A, const AxisAligned_Bounding_Box& B);

	public:
		static const AxisAligned_Bounding_Box EMPTY;

	private:
		Vector3 m_Min{ NameSpace_Math::Math_MAX_FLOAT };
		Vector3 m_Max{ NameSpace_Math::Math_MIN_FLOAT };

	};

}// namespace NameSpace_Core::NameSpace_Bound