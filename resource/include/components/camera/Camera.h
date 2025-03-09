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
	REFLECTION_CLASS(Camera_First_Persion, All) final : public Camera_Base
	{
		REFLECTION_BODY(Camera_First_Persion);
	public:
		Camera_First_Persion(void) = default;

		~Camera_First_Persion(void) = default;

	private:
		float m_Vertical_Offset{ 0.6f };

	};

	REFLECTION_HEADER(Camera_Third_Persion);
	REFLECTION_CLASS(Camera_Third_Persion, All) final :public Camera_Base
	{
		REFLECTION_BODY(Camera_Third_Persion);
	public:
		Camera_Third_Persion(void) = default;

		~Camera_Third_Persion(void) = default;
	
	private:

		float m_Horizontal_Offset{ 3.f };
		float m_Vertical_Offset{ 2.5f };

		Quaternion m_Cursor_Pitch{ Quaternion::IDENTITY };
		Quaternion m_Cursor_Yaw{ Quaternion::IDENTITY };

	};

	REFLECTION_HEADER(Camera_Free);
	REFLECTION_CLASS(Camera_Free, All) final :public Camera_Base
	{
		REFLECTION_BODY(Camera_Free);
	public:
		Camera_Free(void) = default;

		~Camera_Free(void) = default;

	private:
		float m_Speed{ 1.0f };

	};

	REFLECTION_HEADER(Camera);
	REFLECTION_CLASS(Camera, All) final
	{
		REFLECTION_BODY(Camera);
	public:
		Camera(void) = default;

		Camera(const Camera&) = default;
		Camera(Camera&&) = default;

		~Camera(void) = default;

	private:
		Reflection_Instance<Camera_Base> m_Camera{};

	};

}// namespace NameSpace_Resource::NameSpace_Components

CONVERT_UP(NameSpace_Resource::NameSpace_Components, Camera_Base, Camera_First_Persion);
CONVERT_UP(NameSpace_Resource::NameSpace_Components, Camera_Base, Camera_Third_Persion);
CONVERT_UP(NameSpace_Resource::NameSpace_Components, Camera_Base, Camera_Free);