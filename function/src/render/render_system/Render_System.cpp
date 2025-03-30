#include "render/render_system/Render_System.h"

#include "meta/generated/reflection/Global_Rendering.Generated_Reflection.h"
#include "meta/generated/reflection/Camera_Controller.Generated_Reflection.h"


#include "config/Resource_Configer.h"
#include "manage/Resource_Manager.h"
#include "components/camera/Camera_Controller.h"

#include "render/render_system/Light.h"

#include "global/Global_Rendering.h"

#include "render/rhi/vulkan/Vulkan_RHI.h"

#include "render/render_system/Render_Resource.h"
#include "render/render_system/Render_Pipeline.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System {

	using NameSpace_Resource::NameSpace_Global::Global_Rendering;
	using NameSpace_Resource::NameSpace_Global::Reflection_Global_Rendering_Operator;
	//using NameSpace_Resource::NameSpace_Global::Reflection_SkyBox_Irradiance_Map_Operator;
	//using NameSpace_Resource::NameSpace_Global::Reflection_SkyBox_Specular_Map_Operator;
	using NameSpace_Resource::NameSpace_Components::Reflection_Camera_Config_Operator;
	using NameSpace_Resource::NameSpace_Components::Reflection_Camera_Pose_Operator;
	using NameSpace_Resource::NameSpace_Global::Reflection_Directional_Light_Operator;


	using NameSpace_Resource::NameSpace_Config::Resource_Configer;
	using NameSpace_Resource::NameSpace_Manage::Resource_Manager;

	using NameSpace_RHI::NameSpace_Vulkan_RHI::Vulkan_RHI;
	using NameSpace_RHI::RHI_Initialization_Info;

	Render_System::Render_System(const Render_System_Initialization_Info& Initialization_Info) :
		m_Window_System{ Initialization_Info.Window_System },
		m_RHI{ std::make_shared<Vulkan_RHI>(RHI_Initialization_Info{Initialization_Info.Window_System}) },
		m_Render_Resource{ std::make_shared<Render_Resource>() },
		m_Render_Camera{ std::make_shared<Render_Camera>() },
		m_Render_Scene{ std::make_shared<Render_Scene>() } {

		this->m_RHI->Initialize();


		auto Global_Rendering_Resource = Resource_Manager::Load<Global_Rendering>(Resource_Configer::Get_Instance().Get_Global_Render_Resource_URL());

		Level_Resource_Desc Level_Resource_Desc{};
		{
			Level_Resource_Desc.IBL_Resource_Desc.m_SkyBox_Irradiance_Map = Reflection_Global_Rendering_Operator::Get_Skybox_Irradiance_Map_Attribute(Global_Rendering_Resource);
			Level_Resource_Desc.IBL_Resource_Desc.m_SkyBox_Specular_Map = Reflection_Global_Rendering_Operator::Get_Skybox_Specular_Map_Attribute(Global_Rendering_Resource);
			Level_Resource_Desc.IBL_Resource_Desc.BRDF_Map_URL = Reflection_Global_Rendering_Operator::Get_BRDF_Map_URL_Attribute(Global_Rendering_Resource);
			Level_Resource_Desc.Color_Grading_Resource_Desc.Color_Grading_Map_URL = Reflection_Global_Rendering_Operator::Get_Color_Grading_Map_URL_Attribute(Global_Rendering_Resource);
		}
		this->m_Render_Resource->Upload_Global_Render_Resource(this->m_RHI, Level_Resource_Desc);

		//NOTE : Camera
		{
			const auto& Camera_Config = Reflection_Global_Rendering_Operator::Get_Camera_Config_Attribute(Global_Rendering_Resource);
			const auto& Pose = Reflection_Camera_Config_Operator::Get_Pose_Attribute(Camera_Config);

			const auto& Position = Reflection_Camera_Pose_Operator::Get_Position_Attribute(Pose);
			const auto& Target = Reflection_Camera_Pose_Operator::Get_Target_Attribute(Pose);
			const auto& Up = Reflection_Camera_Pose_Operator::Get_Up_Attribute(Pose);

			this->m_Render_Camera->Set_Z_Near(Reflection_Camera_Config_Operator::Get_Z_Near_Attribute(Camera_Config));
			this->m_Render_Camera->Set_Z_Far(Reflection_Camera_Config_Operator::Get_Z_Far_Attribute(Camera_Config));
			this->m_Render_Camera->Set_Aspect(Reflection_Camera_Config_Operator::Get_Aspect_Attribute(Camera_Config));

			this->m_Render_Camera->Look_At(Position, Target, Up);
		}

		//NOTE : Scence
		{
			const auto& Temp_Directional_Light = Reflection_Global_Rendering_Operator::Get_Directional_Light_Attribute(Global_Rendering_Resource);
			const auto& Direction = Reflection_Directional_Light_Operator::Get_Direction_Attribute(Temp_Directional_Light);
			const auto& Directional_Light_Color = Reflection_Directional_Light_Operator::Get_Color_Attribute(Temp_Directional_Light);

			this->m_Render_Scene->Set_Ambient_Light(Reflection_Global_Rendering_Operator::Get_Ambient_Light_Attribute(Global_Rendering_Resource));
			this->m_Render_Scene->Set_Directional_Light(Directional_Light{ Direction.Normalize() ,Directional_Light_Color });

			this->m_Render_Scene->Set_Visiable_Nodes();
		}

		//NOTE : Pipeline
		{
			bool Enbale_FAXX = Reflection_Global_Rendering_Operator::Get_Enable_FXAA_Attribute(Global_Rendering_Resource);
			Render_Pipeline_Info Pipeline_Info{ Enbale_FAXX,this->m_RHI,this->m_Render_Resource };

			this->m_Render_Pipeline = std::make_shared<Render_Pipeline>(Pipeline_Info);

		}



	}

	void Render_System::Render(void){
	}

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System