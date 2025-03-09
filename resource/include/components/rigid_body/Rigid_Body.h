#pragma once

#include<cstdint>
#include<vector>

#include "meta/reflection/Reflection_Macro.h"

#include "transform/Orthogonal_Transform.h"
#include  "bounding/Bounding_Box_AxisAligned.h"
#include "meta/reflection/Reflection_Instance.h"
#include "components/rigid_body/Basic_Shape.h"

namespace NameSpace_Resource::NameSpace_Components {

	using std::vector;

	using NameSpace_Core::NameSpace_Transform::Orthogonal_Transform;
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

		~Rigid_Body_Shape(void) = default;

	private:
		Orthogonal_Transform m_Global_Transform{ Orthogonal_Transform::IDENTITY };
		Orthogonal_Transform m_Local_Transform{ Orthogonal_Transform::IDENTITY };

		AxisAligned_Bounding_Box m_Bounding_Box{ AxisAligned_Bounding_Box::EMPTY };
		Rigid_Body_Type m_Type{ Rigid_Body_Type::INVALID };

		Reflection_Instance<Geometry_Base> m_Instance{ "Geometry_Base" };

	};

	REFLECTION_HEADER(Rigid_Body);
	REFLECTION_CLASS(Rigid_Body, All) final
	{
		REFLECTION_BODY(Rigid_Body);
	public:
		Rigid_Body(void) = default;

		~Rigid_Body(void) = default;

	private:
		vector<Rigid_Body_Shape> m_Shapes{};

		float m_Inverse_Mass{ 0.0f };
		int m_Actor_Type;
	};


}// namespace NameSpace_Resource::NameSpace_Components