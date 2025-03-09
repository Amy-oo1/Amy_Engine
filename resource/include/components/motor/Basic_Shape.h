#pragma once

#include "meta/reflection/Reflection_Macro.h"

#include"math/Vector3.h"

namespace NameSpace_Resource::NameSpace_Components {

	using NameSpace_Core::NameSpace_Math::Vector3;

	REFLECTION_HEADER(Geometry_Base);
	REFLECTION_CLASS(Geometry_Base, All)
	{
		REFLECTION_BODY(Geometry_Base);
	public:
		Geometry_Base(void) = default;
		virtual ~Geometry_Base(void) = default;

	};

	REFLECTION_HEADER(Geometry_Box);
	REFLECTION_CLASS(Geometry_Box, All) :public Geometry_Base
	{
		REFLECTION_BODY(Geometry_Box);
	public:
		Geometry_Box(void) = default;

		~Geometry_Box(void) override = default;
	
	private:
		Vector3 m_Half_Extents{ 0.5f, 0.5f, 0.5f };

	};

	REFLECTION_HEADER(Geometry_Sphere);
	REFLECTION_CLASS(Geometry_Sphere, All) :public Geometry_Base
	{
		REFLECTION_BODY(Geometry_Sphere);
	public:
		Geometry_Sphere(void) = default;

		~Geometry_Sphere(void) override = default;

	private:
		float m_radius{ 0.5f };

	};

	REFLECTION_HEADER(Geometry_Cylinder);
	REFLECTION_CLASS(Geometry_Cylinder, All) :public Geometry_Base
	{
		REFLECTION_BODY(Geometry_Cylinder);
	public:
		Geometry_Cylinder(void) = default;

		~Geometry_Cylinder(void) override = default;

	private:
		float m_Radius{ 0.5f };
		float m_Half_Height{ 1.0f };

	};

}// namespace NameSpace_Resource::NameSpace_Componentss