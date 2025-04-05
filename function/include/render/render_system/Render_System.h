#pragma once

#include<cstdint>
#include<optional>
#include<array>
#include<memory>

#include "render/rhi/empty_rhi/Empty_RHI.h"
#include "render/window/Window_System.h"

#include "render/render_system/Render_Swap_Context.h"

#include "render/render_system/Render_GUID_Allocator.h"
#include "render/render_system/Render_Data_Struct.h"
#include "render/render_system/Render_Entity.h"
#include "render/render_system/Render_Obejct.h"
#include "render/render_system/Render_Resource_Base.h"
#include "render/render_system/Render_Camera.h"
#include "render/render_system/Render_Scene.h"
#include "render/window/Window_UI.h"
#include "render/render_system/Render_Pipeline_Base.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System {

	using std::array;
	using std::shared_ptr;

	using NameSpace_Window::Window_System;
	using NameSpace_Window::Window_UI;

	struct Render_System_Initialization_Info final {
		shared_ptr<Window_System> Window_System;
	};


	class Render_System final {
	public:
		enum class RENDER_PIPELINE_TYPE :uint32_t {
			FORWARD_PIPELINE = 0,
			DEFERRED_PIPELINE,
			PIPELINE_TYPE_COUNT
		};


	private:
		Render_System(void) = delete;

		Render_System(const Render_System&) = delete;
		Render_System& operator=(const Render_System&) = delete;

	public:
		Render_System(const Render_System_Initialization_Info& Initialization_Info);

		~Render_System(void) = default;

		void Set_Visable_Axis(const optional<Render_Entity>& Axis);

		shared_ptr<Render_GUID_Allocator<Game_Object_Part_ID>> Get_Instance_ID_Allocator(void) const;
		shared_ptr<Render_GUID_Allocator<Mesh_Source_Desc>> Get_Mesh_Resource_ID_Allocator(void) const;
		shared_ptr<Render_GUID_Allocator<Material_Source_Desc>> Get_Material_Resource_ID_Allocator(void) const;


		shared_ptr<Render_Camera> Get_Render_Camera(void)const;
		shared_ptr<Render_Swap_Context> Get_Render_Swap_Context(void)const;

		void Set_Window_UI_System(shared_ptr<Window_UI> UI) const;


		void Create_Axis(Render_Entity* Translation_Axis, Render_Entity* Rotation_Axis, Render_Entity* Scale_Axis);

		void Swap_Logic_Render_Data(void);

		void Proccess_Swap_Data(void);

		void Tick(float Delta_Time);


	private:
		//NOTE: WIndow_Sync RHI Window
		shared_ptr<Window_System> m_Window_System{ nullptr };
		shared_ptr<NameSpace_RHI::Empty_RHI> m_RHI{ nullptr };

		shared_ptr<Render_Resource_Base> m_Render_Resource{ nullptr };
		shared_ptr<Render_Camera> m_Render_Camera{ nullptr };
		shared_ptr<Render_Scene> m_Render_Scene{ nullptr };
		shared_ptr<Render_Pipeline_Base> m_Render_Pipeline{ nullptr };
		shared_ptr<Render_Swap_Context> m_Render_Swap_Context{ std::make_shared<Render_Swap_Context>() };
	};

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System