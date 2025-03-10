#pragma once

#include<string>

#include "meta/reflection/Reflection_Macro.h"

#include "math/Vector3.h"
#include "color/Color.h"

#include "components/camera/Camera_Controller.h"

namespace NameSpace_Resource::NameSpace_Global {

	using std::string;

	using NameSpace_Core::NameSpace_Math::Vector3;
	using NameSpace_Core::NameSpace_Color::Color;
	using NameSpace_Resource::NameSpace_Components::Camera_Config;

	REFLECTION_HEADER(SkyBox_Irradiance_Map);
	REFLECTION_CLASS(SkyBox_Irradiance_Map, All) final
	{
		REFLECTION_BODY(SkyBox_Irradiance_Map);
	public:
		SkyBox_Irradiance_Map(void) = default;

		~SkyBox_Irradiance_Map(void) = default;

	private:
		string m_Negative_X_Map;
		string m_Positive_X_Map;
		string m_Negative_Y_Map;
		string m_Positive_Y_Map;
		string m_Negative_Z_Map;
		string m_Positive_Z_Map;

	};

	REFLECTION_HEADER(SkyBox_Specular_Map);
	REFLECTION_CLASS(SkyBox_Specular_Map, All) final
	{
		REFLECTION_BODY(SkyBox_Specular_Map);
	public:
		SkyBox_Specular_Map(void) = default;

		~SkyBox_Specular_Map(void) = default;

	private:
		string m_Negative_X_Map;
		string m_Positive_X_Map;
		string m_Negative_Y_Map;
		string m_Positive_Y_Map;
		string m_Negative_Z_Map;
		string m_Positive_Z_Map;
	};

	REFLECTION_STRUCT(Directional_Light);
	REFLECTION_STRUCT(Directional_Light, All) final
	{
		REFLECTION_BODY(Directional_Light);
	public:
		Directional_Light(void) = default;

		~Directional_Light(void) = default;

	private:
		Vector3 m_Direction_List{ 0.0f, -1.0f, 0.0f };
		Color m_Color{ 0.0f, 0.0f, 0.0f, 1.0f };

	};


	REFLECTION_HEADER(Global_Rendering);
	REFLECTION_CLASS(Global_Rendering, All) final
	{
		REFLECTION_BODY(Global_Rendering);
	public:
		Global_Rendering(void) = default;

		~Global_Rendering(void) = default;
	private:
		bool m_Enable_FXAA{ false };

		SkyBox_Irradiance_Map m_Skybox_Irradiance_Map;
		SkyBox_Specular_Map   m_Skybox_Specular_Map;

		std::string m_BRDF_Map;
		std::string m_Color_Grading_Map;

		Color m_Sky_Color;
		Color m_Ambient_Light;
		Camera_Config m_Camera_Config;
		Directional_Light m_Directional_Light;

	};

}// namespace NameSpace_Resource::NameSpace_Global