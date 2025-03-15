#pragma once

#include<limits>

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


	REFLECTION_HEADER(Particle_Res);
	REFLECTION_CLASS(Particle_Res, All) final
	{
		REFLECTION_BODY(Particle_Res);
	public:
		Particle_Res(void) = default;

		~Particle_Res(void) = default;
	private:
		Orthogonal_Transform m_Local_Transform{ Orthogonal_Transform::IDENTITY };

		Vector4 m_Velocity{ Vector4::ZERO };
		Vector4 m_Acceleration{ Vector4::ZERO };
		Vector3 m_Size{ Vector3::ZERO };
		int m_Emitter_Type{ std::numeric_limits<int>::max() };
		Vector2 m_Life{};
		Color m_Color{};

	};

}// namespace NameSpace_Resource::NameSpace_Components