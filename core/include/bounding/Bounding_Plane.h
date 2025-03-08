#pragma once

#include "math/Head_Math.h"
#include "transform/Orthogonal_Transform.h"

namespace NameSpace_Core::NameSpace_Bounding {

	using NameSpace_Math::Vector3;
	using NameSpace_Math::Vector4;

	using NameSpace_Transform::Orthogonal_Transform;

	class Bounding_Plane final {
	public:
		Bounding_Plane(void) = default;

		Bounding_Plane(const Bounding_Plane&) = default;
		Bounding_Plane(Bounding_Plane&&) = default;

		Bounding_Plane& operator=(const Bounding_Plane&) = default;
		Bounding_Plane& operator=(Bounding_Plane&&) = default;

		friend const Bounding_Plane operator*(const Orthogonal_Transform& Transform, const Bounding_Plane& Plane);

		explicit Bounding_Plane(const Vector4& Plane);
		Bounding_Plane(float A, float B, float C, float D);
		Bounding_Plane(const Vector3& Normal_Plane, float Distance_From_Origin);
		Bounding_Plane(const Vector3& Point_On_Plane, const Vector3& Normal_Plane);

		~Bounding_Plane(void) = default;

	public:
		operator Vector4(void)const;

		const Bounding_Plane& operator=(const Vector4& Plane);

	public:
		const Vector3 Get_Normal(void)const;
		const Vector3 Get_Point_On_Plane(void)const;

		float Distance_From_Origin(void)const;
		float Distance_From_Point(const Vector3& Point)const;
		float Distance_From_Point(const Vector4& Point)const;

	public:
		static const Bounding_Plane XY;
		static const Bounding_Plane YZ;
		static const Bounding_Plane ZX;

	public:
		static const Bounding_Plane Generate_From_Points_CCW(const Vector3& Point_1, const Vector3& Point_2, const Vector3& Point_3);

	private:
		Vector4 m_Plane{ Vector4::ZERO };

	};

}// namespace NameSpace_Core::NameSpace_Bounding
