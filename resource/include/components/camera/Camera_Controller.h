#pragma once

#include "meta/reflection/Reflection_Macro.h"

#include "math/Vector2.h"
#include "math/Vector3.h"

namespace NameSpace_Resource::NameSpace_Components {

	using NameSpace_Core::NameSpace_Math::Vector2;
	using NameSpace_Core::NameSpace_Math::Vector3;

	REFLECTION_HEADER(Camera_Pose);
		REFLECTION_CLASS(Camera_Pose, All)
	{
		REFLECTION_BODY(Camera_Pose);
	public:

		Camera_Pose(void) = default;

		~Camera_Pose(void) = default;

	private:
		Vector3 m_Position{ Vector3::ZERO };
		Vector3 m_Target{ Vector3::UNIT_Z };
		Vector3 m_Up{Vector3::UNIT_Y};

	};

	REFLECTION_HEADER(Camera_Config);
	REFLECTION_CLASS(Camera_Config, All)
	{
		REFLECTION_BODY(Camera_Config);
	public:
		Camera_Config(void) = default;

		~Camera_Config(void) = default;

	private:
		Camera_Pose M_Pose{};
		Vector2 m_Aspect{ Vector2::ONE };
		float m_Z_Near{ 0.1f };
		float m_Z_Far{100.f};

	};

}// namespace NameSpace_Resource::NameSpace_Components
