#pragma once

#include<cstdint>

#include "math/Vector2.h"
#include "math/Vector3.h"
#include "math/Vector4.h"
#include "math/Matrix4x4.h"

namespace NameSpace_Function::Namespace_Particle {

	using NameSpace_Core::NameSpace_Math::Vector2;
	using NameSpace_Core::NameSpace_Math::Vector3;
	using NameSpace_Core::NameSpace_Math::Vector4;
	using NameSpace_Core::NameSpace_Math::Matrix4x4;

	struct Particle_Config final {
		static constexpr int Max_Particle_Size{ 300000 };
		static constexpr int Default_Particle_Emitter_gap{ 10 };
		static constexpr int Default_Particle_Emitter_Count{ 100000 };
		static constexpr int Default_Particle_Life_Time{ 10 };
		static constexpr float Default_Particle_Time_Step{ 0.004f };

		static inline const Vector4 Default_Emitter_Position{ 5.71f, 13.53f, 3.0f, 0.5f };
		static inline const Vector4 Default_Emitter_Velocity{ 0.02f, 0.02f, 2.5f, 4.0f };
		static inline const Vector4 Default_Emitter_Acceleration{ 0.f, 0.f, -2.5f, 0.f };
		static inline const Vector3 Default_Emitter_Size{ 0.02f, 0.02f, 0.f };
		static inline const Vector2 Default_Emitter_Life{ 1.2f, 0.f };
	};

	enum class EMITTER_TYPE :uint8_t
	{
		POINT = 0,
		MESH,
		INVALID
	};

}// namespace NameSpace_Function::Namespace_Particle