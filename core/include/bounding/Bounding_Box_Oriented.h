#pragma once

#include "transform/Head_Thansform.h"

#include "bounding/Bounding_Box_AxisAligned.h"

namespace NameSpace_Core::NameSpace_Bounding {

	using NameSpace_Transform::Uniform_Transform;
	using NameSpace_Transform::Affine_Tranform;

	class Oriented_Bounding_Box final {
	public:
		Oriented_Bounding_Box(void) = default;

		Oriented_Bounding_Box(const Oriented_Bounding_Box&) = default;
		Oriented_Bounding_Box(Oriented_Bounding_Box&&) = default;

		Oriented_Bounding_Box& operator=(const Oriented_Bounding_Box&) = default;
		Oriented_Bounding_Box& operator=(Oriented_Bounding_Box&&) = default;

		explicit Oriented_Bounding_Box(const Affine_Tranform& Transform);
		explicit Oriented_Bounding_Box(const AxisAligned_Bounding_Box& Box);

		~Oriented_Bounding_Box(void) = default;

	public:
		Oriented_Bounding_Box& operator=(const Affine_Tranform& Transform);
		Oriented_Bounding_Box& operator=(const AxisAligned_Bounding_Box& Box);

	public:
		const Affine_Tranform& Get_Transform(void)const;

		const Vector3 Get_Center(void)const;
		const Vector3 Get_Dimensions(void)const;

	public:
		static const Oriented_Bounding_Box EMPTY;

	private:
		Affine_Tranform m_Transform{ Affine_Tranform::IDENTITY };
	};

	const Oriented_Bounding_Box operator*(const Affine_Tranform& Transform, const Oriented_Bounding_Box& Box);

	const Oriented_Bounding_Box operator*(const Uniform_Transform& Transform, const Oriented_Bounding_Box& Box);

	const Oriented_Bounding_Box operator*(const Uniform_Transform& Transform, const AxisAligned_Bounding_Box& Box);

}// namespace NameSpace_Core::NameSpace_Bounding