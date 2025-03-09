#pragma once

#include "meta/reflection/Reflection_Macro.h"

#include "math/Vector2.h"
#include "math/Vector3.h"
#include "math/Vector4.h"
#include "transform/Orthogonal_Transform.h"
#include "color/Color.h"

namespace NameSpace_Resource::NameSpace_Components {

	using NameSpace_Core::NameSpace_Math::Vector2;
	using NameSpace_Core::NameSpace_Math::Vector3;
	using NameSpace_Core::NameSpace_Math::Vector4;
	using NameSpace_Core::NameSpace_Transform::Orthogonal_Transform;
	using NameSpace_Core::NameSpace_Color::Color;


	REFLECTION_HEADER(Particle);
	REFLECTION_CLASS(Particle, All) final
	{
		REFLECTION_BODY(Particle);
	public:
		Particle(void) = default;

		~Particle(void) = default;
	private:
		Orthogonal_Transform m_Loac_Transform{};

		Vector4 m_Velocity{};
		Vector4 m_Acceleration{};
		Vector3 m_Size{};
		int m_Emitter_Type{};
		Vector2 m_Life{};
		Color m_Color{};

	};

}