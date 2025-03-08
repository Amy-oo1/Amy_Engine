#pragma once

#include<string>

#include "meta/reflection/Reflection_Macro.h"
#include "meta/reflection/Reflection_Instance.h"

#include "math/Quaternion.h"

namespace NameSpace_Resource::NameSpace_Components {

	using std::string;
	using NameSpace_Core::NameSpace_Math::Quaternion;
	using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;
	
	REFLECTION_HEADER(Camera_Base);
	REFLECTION_CLASS(Camera_Base, All) 
	{
		REFLECTION_BODY(Camera_Base);
	public:
		Camera_Base(void) = default;

		virtual ~Camera_Base(void) = default;


	private:
		float m_FOV{ 50.0f };

	};

	REFLECTION_HEADER(Camera_First_Persion);
	REFLECTION_CLASS(Camera_First_Persion, All) :public Camera_Base
	{
		REFLECTION_BODY(Camera_First_Persion);
	public:
		Camera_First_Persion(void) = default;

		virtual ~Camera_First_Persion(void) = default;

	private:
		float m_vertical_offset{ 0.6f };

	};
	
	REFLECTION_HEADER(Camera_Third_Persion);
	REFLECTION_CLASS(Camera_Third_Persion, All) :public Camera_Base
	{


		REFLECTION_BODY(Camera_Third_Persion);
	public:
		Camera_Third_Persion(void) = default;

		virtual ~Camera_Third_Persion(void) = default;
	private:

		float m_horizontal_offset{ 3.f };
		float m_vertical_offset{ 2.5f };

		NameSpace_Core::NameSpace_Math::Quaternion m_Cursor_Pitch{ NameSpace_Core::NameSpace_Math::Quaternion::IDENTITY };
		NameSpace_Core::NameSpace_Math::Quaternion m_Cursor_Yaw{ NameSpace_Core::NameSpace_Math::Quaternion::IDENTITY };

	};

	REFLECTION_HEADER(Camera_Free);
	REFLECTION_CLASS(Camera_Free, All) :public Camera_Base
	{
		REFLECTION_BODY(Camera_Free);
	public:
		Camera_Free(void) = default;

		virtual ~Camera_Free(void) = default;

	private:
		float m_Speed{ 1.0f };

	};

	REFLECTION_HEADER(Component_Camera_Resource);
	REFLECTION_CLASS(Component_Camera_Resource, All) final
	{
		REFLECTION_BODY(Component_Camera_Resource);
	public:
		Component_Camera_Resource(void) = default;

		~Component_Camera_Resource(void) = default;

	private:
		Reflection_Instance<Camera_Base> m_Camera{ string{"Camera_Base"} };

	};

}// namespace NameSpace_Resource::NameSpace_Components
