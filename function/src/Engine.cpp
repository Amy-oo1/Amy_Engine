#include "Engine.h"

#include "global/Global_Systemer.h"

namespace NameSpace_Function {

	using Namespace_Global::Global_Systemer;

	Amy_Engine::Amy_Engine(const std::vector<string>& Arguments) {

		Global_Systemer::Initialize(Arguments);

		//const Global_Systemer& Systemer = Global_Systemer::Get_Instance();
	}

	float Amy_Engine::Calculate_Delta_Time(void) {
		using namespace std::chrono;

		float delta_time{};
		{
			using namespace std::chrono;

			steady_clock::time_point tick_time_point = steady_clock::now();
			duration<float> time_span = duration_cast<duration<float>>(tick_time_point - m_last_tick_time_point);
			delta_time = time_span.count();

			m_last_tick_time_point = tick_time_point;
		}
		return delta_time;
	}

	bool Amy_Engine::Tick_One_Frame(float Delta_Time) {
		auto& Ref_Global_System{ Global_Systemer::Get_Instance() };

		this->Logical_Tick(Delta_Time);
		this->Calculate_FPS(Delta_Time);

		Ref_Global_System.Main_Render_System->Swap_Logic_Render_Data();
		this->Renderer_Tick(Delta_Time);

		Ref_Global_System.Main_Window->Poll_Window_Events();
		Ref_Global_System.Main_Window->ReSet_Window_Title(
			string{ "Amy_Engine" } +
			"FPS : " + std::to_string(this->m_FPS) +
			" Delta Time : " + std::to_string(Delta_Time)
		);

		return !Ref_Global_System.Main_Window->Is_WIndow_Shoule_Close();
	}

	void Amy_Engine::Logical_Tick(float Delta_tTme) {
		Global_Systemer::Get_Instance().World_Manager.Tick(Delta_tTme);
		Global_Systemer::Get_Instance().Main_Input->Tick();
	}

	void Amy_Engine::Renderer_Tick(float Delta_Time){
		Global_Systemer::Get_Instance().Main_Render_System->Tick(Delta_Time);
	}

	void Amy_Engine::Calculate_FPS(float Delta_Time) {

		if (1 == ++this->m_Frame_Count)
			this->m_Average_Duration = Delta_Time;
		else
			this->m_Average_Duration = this->m_Average_Duration * (1 - Amy_Engine::s_FPS_Alpha) + Delta_Time * Amy_Engine::s_FPS_Alpha;

		this->m_FPS = static_cast<int>(1.f / this->m_Average_Duration);
	}

}// namespace NameSpace_Function