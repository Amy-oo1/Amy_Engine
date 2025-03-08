#include "bounding/Bounding_Box_AxisAligned.h"

namespace NameSpace_Core::NameSpace_Bounding {

	using NameSpace_Math::NameSpace_Utilities::Min;
	using NameSpace_Math::NameSpace_Utilities::Max;

	AxisAligned_Bounding_Box::AxisAligned_Bounding_Box(const Vector3& Min, const Vector3& Max) :
		m_Min{ Min },
		m_Max{ Max } {
	}

	void AxisAligned_Bounding_Box::Add_Point(const Vector3& Point) {
		this->m_Min = Min(Point, this->m_Min);
		this->m_Max = Max(Point, this->m_Max);
	}

	void AxisAligned_Bounding_Box::Add_Point(const initializer_list<Vector3>& Points) {
		for (const auto& Point : Points)
			this->Add_Point(Point);
	}

	void AxisAligned_Bounding_Box::Add_Bounding_Box(const AxisAligned_Bounding_Box& Box) {
		*this = AxisAligned_Bounding_Box::Union(*this, Box);
	}

	const Vector3 AxisAligned_Bounding_Box::Get_Min(void)const {
		return this->m_Min;
	}

	const Vector3 AxisAligned_Bounding_Box::Get_Max(void)const {
		return this->m_Max;
	}

	const Vector3 AxisAligned_Bounding_Box::Get_Center(void)const {
		return this->m_Min * 0.5f + this->m_Max * 0.5f;
	}

	const Vector3 AxisAligned_Bounding_Box::Get_Dimensions(void)const {
		return Max(this->m_Max - this->m_Min, Vector3::ZERO);
	}

	const AxisAligned_Bounding_Box AxisAligned_Bounding_Box::Union(const AxisAligned_Bounding_Box& A, const AxisAligned_Bounding_Box& B) {
		return AxisAligned_Bounding_Box{
			Min(A.Get_Min(), B.Get_Min()),
			Max(A.Get_Max(), B.Get_Max())
		};
	}

	const AxisAligned_Bounding_Box AxisAligned_Bounding_Box::EMPTY;

}// namespace NameSpace_Core::NameSpace_Bounding