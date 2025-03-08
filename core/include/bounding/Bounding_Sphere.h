#pragma once

#include "math/Head_Math.h"

namespace NameSpace_Core::NameSpace_Bounding {

	using NameSpace_Math::Vector3;
	using NameSpace_Math::Vector4;

	class Bounding_Sphere final {
	public:
		Bounding_Sphere(void) = default;

		Bounding_Sphere(const Bounding_Sphere&) = default;
		Bounding_Sphere(Bounding_Sphere&&) = default;

		Bounding_Sphere& operator=(const Bounding_Sphere&) = default;
		Bounding_Sphere& operator=(Bounding_Sphere&&) = default;

		explicit Bounding_Sphere(const Vector4& Sphere);
		Bounding_Sphere(const Vector3& Center, float Radius);

		~Bounding_Sphere(void) = default;

	public:
		Bounding_Sphere& operator=(const Vector4& Sphere);

		explicit operator Vector4(void)const;

	public:
		const Vector3 Get_Center(void)const;
		 float Get_Radius(void)const;

	public:
		static const Bounding_Sphere Union(const Bounding_Sphere& A, const Bounding_Sphere& B);


	public:
		static const Bounding_Sphere EMPTY;

	private:
		Vector3 m_Center{ Vector3::ZERO };
		float m_Radius{ 0.f };

	};

}// namespace NameSpace_Core::NameSpace_Bounding
