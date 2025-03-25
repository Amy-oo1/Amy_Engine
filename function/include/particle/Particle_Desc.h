#pragma once

#include<limits>
#include<memory>

#include "math/Vector2.h"
#include "math/Vector3.h"
#include "math/Vector4.h"
#include "math/Matrix4x4.h"
#include "math//Quaternion.h"
#include "color/Color.h"
#include "transform/Orthogonal_Transform.h"

#include "components/emitter/Particle.h"

#include "particle/Emitter_ID_Allocator.h"


namespace NameSpace_Function::NameSpace_Particle {

	using std::shared_ptr;

	using NameSpace_Core::NameSpace_Math::Vector2;
	using NameSpace_Core::NameSpace_Math::Vector3;
	using NameSpace_Core::NameSpace_Math::Vector4;
	using NameSpace_Core::NameSpace_Math::Matrix4x4;
	using NameSpace_Core::NameSpace_Math::Quaternion;
	using NameSpace_Core::NameSpace_Color::Color;
	using NameSpace_Core::NameSpace_Transform::Orthogonal_Transform;

	using NameSpace_Resource::NameSpace_Components::Particle_Res;

	struct Particle_Emitter_Transform_Desc final {
		Particle_Emitter_ID ID{ Emitter_ID_Allocator::INVALID_ID };
		Orthogonal_Transform Transform{ Orthogonal_Transform::IDENTITY };
	};

	class Particle_Emitter_Desc final {
	public:
		Particle_Emitter_Desc(void) = default;

		Particle_Emitter_Desc(const Particle_Emitter_Desc&) = default;
		Particle_Emitter_Desc(Particle_Emitter_Desc&&) = default;

		Particle_Emitter_Desc& operator=(const Particle_Emitter_Desc&) = default;
		Particle_Emitter_Desc& operator=(Particle_Emitter_Desc&&) = default;

		Particle_Emitter_Desc(const shared_ptr<Particle_Res>& Temp_Particle_Res, const Particle_Emitter_Transform_Desc& Temp_Transform_Desc);

		~Particle_Emitter_Desc(void) = default;

	public:
		//TODO : Add Get Function?
		Particle_Emitter_ID m_ID{ Emitter_ID_Allocator::INVALID_ID };
		Orthogonal_Transform m_Transform{ Orthogonal_Transform::IDENTITY };
		Vector4   m_Velocity{ Vector4::ZERO };
		Vector4   m_Acceleration{ Vector4::ZERO };
		Vector3   m_Size{ Vector3::ZERO };
		int       m_Emitter_Type{ std::numeric_limits<int>::max() };
		Vector2   m_Life{ Vector2::ZERO };
		Color   m_Color{};

		Vector2   m_Padding{ Vector2::ZERO };

	};

}// namespace NameSpace_Function::NameSpace_Particle
