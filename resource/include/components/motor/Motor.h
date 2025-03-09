#pragma once

#include <cstdint>

#include "meta/reflection/Reflection_Macro.h"

#include "meta/reflection/Reflection_Instance.h"
#include "components/rigid_body/Basic_Shape.h"

namespace NameSpace_Resource::NameSpace_Components {

	using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

	enum class Controller_Type :uint8_t {
		NONE,
		PHYSICS,
		INVALID
	};

	REFLECTION_HEADER(Physics_Controller_Config);
	REFLECTION_CLASS(Physics_Controller_Config, All) final
	{
		REFLECTION_BODY(Physics_Controller_Config);
	public:
		Physics_Controller_Config(void) = default;

		~Physics_Controller_Config(void) = default;

	private:
		Geometry_Cylinder m_Cylinder{};

	};

	REFLECTION_HEADER(Motor);
	REFLECTION_CLASS(Motor, All) final
	{
		REFLECTION_BODY(Motor);
	public:
		Motor(void) = default;

		~Motor(void) = default;

	private:
		Reflection_Instance< Physics_Controller_Config> m_Physics_Controller_Config{};

		float m_Move_Speed{ 0.f };
		float m_Jump_Height{ 0.f };
		float m_Max_Move_Speed_Ratio{ 0.f };
		float m_Max_Sprint_Speed_Ratio{ 0.f };
		float m_Move_Acceleration{ 0.f };
		float m_Sprint_Acceleration{ 0.f };
	};
} // namespace NameSpace_Resource::NameSpace_Components