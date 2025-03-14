#pragma once

#include<cstdint>
#include<string>
#include<vector>
#include<memory>

#include "meta/reflection/Reflection_Macro.h"

#include "transform/Affine_Transform.h"
#include  "bounding/Bounding_Box_AxisAligned.h"
#include "meta/reflection/Reflection_Instance.h"
#include "components/rigid_body/Basic_Shape.h"

namespace NameSpace_Resource::NameSpace_Components {

	using std::string;
	using std::vector;
	using std::shared_ptr;

	using NameSpace_Core::NameSpace_Transform::Affine_Transform;
	using NameSpace_Core::NameSpace_Bounding::AxisAligned_Bounding_Box;
	using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

	enum class Rigid_Body_Type :uint8_t {
		BOX,
		SPHERE,
		CAPSULE,
		INVALID
	};

	REFLECTION_HEADER(Rigid_Body_Shape);
	REFLECTION_CLASS(Rigid_Body_Shape, All) final
	{
		REFLECTION_BODY(Rigid_Body_Shape);
	public:
		Rigid_Body_Shape(void) = default;

		Rigid_Body_Shape(const Rigid_Body_Shape&) = default;
		Rigid_Body_Shape(Rigid_Body_Shape&&) = default;

		Rigid_Body_Shape& operator=(const Rigid_Body_Shape&) = default;
		Rigid_Body_Shape& operator=(Rigid_Body_Shape&&) = default;

		~Rigid_Body_Shape(void) = default;

	private:
		Affine_Transform m_Global_Transform{ Affine_Transform::IDENTITY };
		Affine_Transform m_Local_Transform{ Affine_Transform::IDENTITY };

		AxisAligned_Bounding_Box m_Bounding_Box{ AxisAligned_Bounding_Box::EMPTY };
		Rigid_Body_Type m_Type{ Rigid_Body_Type::INVALID };

		Reflection_Instance<Geometry_Base> m_Geometry{ string{"Geometry_Base"} };

	};

	REFLECTION_HEADER(Rigid_Body_Res);
	REFLECTION_CLASS(Rigid_Body_Res, All) final
	{
		REFLECTION_BODY(Rigid_Body_Res);
	public:
		Rigid_Body_Res(void) = default;

		~Rigid_Body_Res(void) = default;

	private:
		vector<shared_ptr<Rigid_Body_Shape>> m_Shapes{};

		float m_Inverse_Mass{ 0.0f };
		int m_Actor_Type;
	};

}// namespace NameSpace_Resource::NameSpace_Components