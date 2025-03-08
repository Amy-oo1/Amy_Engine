#include "bounding/Bounding_Box_Oriented.h"

namespace NameSpace_Core::NameSpace_Bounding {

	Oriented_Bounding_Box::Oriented_Bounding_Box(const Affine_Transform& Transform)
		:m_Transform{ Transform } {
	}

	Oriented_Bounding_Box::Oriented_Bounding_Box(const AxisAligned_Bounding_Box& Box)
		:m_Transform{
			Affine_Transform::Generate_Scale(Box.Get_Dimensions()).Get_Basis(),
			Box.Get_Min()
		} {
	}

	Oriented_Bounding_Box& Oriented_Bounding_Box::operator=(const Affine_Transform& Transform) {
		return (*this) = Oriented_Bounding_Box{ Transform };
	}

	Oriented_Bounding_Box& Oriented_Bounding_Box::operator=(const AxisAligned_Bounding_Box& Box) {
		return (*this) = Oriented_Bounding_Box{ Box };
	}

	const Affine_Transform& Oriented_Bounding_Box::Get_Transform(void) const {
		return this->m_Transform;
	}

	const Vector3 Oriented_Bounding_Box::Get_Center(void) const {
		return this->m_Transform.Get_Translation() + this->Get_Dimensions() * 0.5f;
	}

	const Vector3 Oriented_Bounding_Box::Get_Dimensions(void) const {
		return
			this->m_Transform.Get_X() +
			this->m_Transform.Get_Y() +
			this->m_Transform.Get_Z();
	}

	const Oriented_Bounding_Box Oriented_Bounding_Box::EMPTY{};

	const Oriented_Bounding_Box operator*(const Affine_Transform& Transform, const Oriented_Bounding_Box& Box) {
		return Oriented_Bounding_Box{ Transform * Box.Get_Transform() };
	}

	const Oriented_Bounding_Box operator*(const Uniform_Transform& Transform, const Oriented_Bounding_Box& Box) {
		return Oriented_Bounding_Box{ Affine_Transform{Transform} *Box.Get_Transform() };
	}

	const Oriented_Bounding_Box operator*(const Uniform_Transform& Transform, const AxisAligned_Bounding_Box& Box) {
		return Oriented_Bounding_Box{ Affine_Transform{Transform} *Oriented_Bounding_Box{Box} };
	}

}// namespace NameSpace_Core::NameSpace_Bounding