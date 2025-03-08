#include "bounding/Bounding_Sphere.h"

namespace NameSpace_Core::NameSpace_Bounding {

	using NameSpace_Math::NameSpace_Utilities::Max;

	Bounding_Sphere::Bounding_Sphere(const Vector4& Sphere)
		: Bounding_Sphere{ Sphere.Get_XYZ(),Sphere.Get_W() } {
	}

	Bounding_Sphere::Bounding_Sphere(const Vector3& Center, float Radius)
		: m_Center{ Center },
		m_Radius{ Radius } {
	}

	Bounding_Sphere& Bounding_Sphere::operator=(const Vector4& Sphere) {
		return (*this) = Bounding_Sphere{ Sphere };
	}

	Bounding_Sphere::operator Vector4(void) const {
		return Vector4{ this->m_Center, this->m_Radius };
	}

	const Vector3 Bounding_Sphere::Get_Center(void) const {
		return m_Center;
	}

	 float Bounding_Sphere::Get_Radius(void) const {
		return m_Radius;
	}

	const Bounding_Sphere Bounding_Sphere::Union(const Bounding_Sphere& A, const Bounding_Sphere& B) {
		float radA = A.m_Radius, radB = B.m_Radius;

		if (radA == 0.0f) return B;
		else if (radB == 0.0f) return A;

		Vector3 diff = A.m_Center - B.m_Center;

		float dist = diff.Length();

		// Safe normalize vector between sphere centers
		diff = dist < 1e-6f ? Vector3::UNIT_X : diff.Normalize();

		Vector3 extremeA = A.m_Center + diff * Max(radA, radB - dist);
		Vector3 extremeB = B.m_Center - diff * Max(radB, radA - dist);

		return Bounding_Sphere{
			(extremeA + extremeB) * 0.5f,
			(extremeA - extremeB).Length() * 0.5f
		};
	}

	const Bounding_Sphere Bounding_Sphere::EMPTY{ Vector3::ZERO, 0.0f };

}// namespace NameSpace_Core::NameSpace_Bounding