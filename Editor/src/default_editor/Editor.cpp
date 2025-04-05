#include "default_editor/Editor.h"

#include "global/Global_Config.h"

#include "default_editor/Editor_Global_Context.h"

#include "default_editor/Editor_UI.h"

namespace NameSpace_Editor {

	using std::static_pointer_cast;

	Amy_Editor::Amy_Editor(unique_ptr<Amy_Engine>&& Engine) :
		m_Engine{ std::move(Engine) },
		m_Editor_UI{ std::make_shared<Editor_UI>() } {

		//TODO : Insert Into UI Pass Per_Info
		Editor_Global_Context::Get_Instance().m_Render_System->Set_Window_UI_System(this->m_Editor_UI);

		NameSpace_Function::Namespace_Global::Is_Editor_Mode = true;

		//NOTE : Initialize Editor Global Context
		auto& Ref_Global_Context{ Editor_Global_Context::Get_Instance() };

		Ref_Global_Context.m_Input_Manager->Register_Input();

		Ref_Global_Context.m_Scene_Manager->UpData_Axis_Resource();

		this->Register_Editor_Tick_Component("TransformComponent");
		this->Register_Editor_Tick_Component("MeshComponent");
	}

	Amy_Editor::~Amy_Editor(void) {
		ImGui::DestroyContext();
	}

	void Amy_Editor::Register_Editor_Tick_Component(const string& Name) {
		this->m_Editor_Tick_Component_Type.emplace(Name);
	}

	void Amy_Editor::Run(void) {
		float Delta_Time{};

		auto& Ref_Editor_Scene_Manage{ *Editor_Global_Context::Get_Instance().m_Scene_Manager };
		auto& Ref_Editor_Input_Manager{ *Editor_Global_Context::Get_Instance().m_Input_Manager };

		while (true) {
			Delta_Time = this->m_Engine->Calculate_Delta_Time();

			Ref_Editor_Scene_Manage.Tick(Delta_Time);
			Ref_Editor_Input_Manager.Tick(Delta_Time);

			if (!this->m_Engine->Tick_One_Frame(Delta_Time))
				break;
		}
	}

}// namespace NameSpace_Editor