#pragma once

#include<vector>
#include<memory>

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_vulkan.h"

#include "render/window/Window_UI.h"

#include "render/rhi/empty_rhi/RHI_Type.h"
#include "render/rhi/empty_rhi/RHI_Class.h"
#include "render/render_system/Render_Resource.h"
#include "render/render_pass/Render_Pass.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass {

	using std::shared_ptr;

	using NameSpace_Window::Window_UI;

	using NameSpace_RHI::RHI_Render_Pass;

	struct UI_Render_Pass_Pre_Initialize_Info final :public Render_Pass_Pre_Initialize_Info {
		RHI_Render_Pass* Render_Pass;
	};

	struct UI_Render_Pass_Post_Initialize_Info final :public Render_Pass_Post_Initialize_Info {
	};


	class UI_Pass final :public Render_Pass {
	private:
		UI_Pass(const UI_Pass&) = delete;
		UI_Pass& operator=(const UI_Pass&) = delete;
	public:
		UI_Pass(const Render_Pass_Command_Info& Command_Info);
		~UI_Pass(void) = default;

	public:
		void Set_Window_UI_System(shared_ptr<Window_UI> UI);

	private:

	private:
		RHI_Render_Pass* m_Render_Pass{ nullptr };
		shared_ptr<Window_UI> m_Window_UI{ nullptr };


	public:
		void Draw(void)override;
		void Pre_Inittialize(shared_ptr<Render_Pass_Pre_Initialize_Info> Init_Info) override;
		void Post_Inittialize(shared_ptr<Render_Pass_Post_Initialize_Info> Init_Info) override;
		void PrePare_Pass_Data(shared_ptr<Render_Resource_Base> Resource) override;

	};

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass