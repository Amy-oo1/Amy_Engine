#include "bounding//Bounding_Plane.h"

namespace NameSpace_Core::NameSpace_Bounding {

	Bounding_Plane::Bounding_Plane(const Vector4& Plane)
		:m_Plane{ Plane } {
	}

	Bounding_Plane::Bounding_Plane(float A, float B, float C, float D)
		:m_Plane{ A,B,C,D } {
	}

	Bounding_Plane::Bounding_Plane(const Vector3& Normal_Plane, float Distance_From_Origin)
		:m_Plane{ Normal_Plane,Distance_From_Origin } {
	}

	Bounding_Plane::Bounding_Plane(const Vector3& Point_On_Plane, const Vector3& Normal_Plane)
		:m_Plane{
			Normal_Plane.Normalize(),
			-Normal_Plane.Normalize().Dot_Product(Point_On_Plane)
		} {
	}

	Bounding_Plane::operator Vector4(void) const {
		return this->m_Plane;
	}

	const Bounding_Plane& Bounding_Plane::operator=(const Vector4& Plane) {
		return (*this) = Bounding_Plane{ Plane };
	}

	const Bounding_Plane operator*(const Orthogonal_Transform& Transform, const Bounding_Plane& Plane) {

		Vector3 Normal{ Transform.Get_Rotation() * Plane.Get_Normal() };
		float Distance_To_Origin{ Plane.m_Plane.Get_W() - Normal.Dot_Product(Transform.Get_Translation()) };

		return Bounding_Plane{ Normal,Distance_To_Origin };
	}

	const Vector3 Bounding_Plane::Get_Normal(void) const {
		return this->m_Plane.Get_XYZ();
	}

	const Vector3 Bounding_Plane::Get_Point_On_Plane(void) const {
		return -this->Get_Normal() * this->m_Plane.Get_W();
	}

	float Bounding_Plane::Distance_From_Origin(void) const {
		return this->m_Plane.Get_W();
	}

	float Bounding_Plane::Distance_From_Point(const Vector3& Point) const {
		// return this->m_Plane.Dot_Product(Vector4{ Point,1.0f });
		return this->Get_Normal().Dot_Product(Point) + this->m_Plane.Get_W();
	}

	float Bounding_Plane::Distance_From_Point(const Vector4& Point) const {
		return this->m_Plane.Dot_Product(Point);
	}

	const Bounding_Plane Bounding_Plane::Generate_From_Points_CCW(const Vector3& A, const Vector3& B, const Vector3& C) {
		return Bounding_Plane{
			A,
			(B - A).Cross_Product(C - A).Normalize()
		};
	}

	const Bounding_Plane Bounding_Plane::XY{ Vector4{ Vector3{0.f,0.f,1.f},0.f } };
	const Bounding_Plane Bounding_Plane::YZ{ Vector4{ Vector3{1.f,0.f,0.f},0.f } };
	const Bounding_Plane Bounding_Plane::ZX{ Vector4{ Vector3{0.f,1.f,0.f},0.f } };

}// namespace NameSpace_Core::NameSpace_Bounding