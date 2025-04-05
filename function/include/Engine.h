#pragma once

#include<string>
#include <atomic>
#include <chrono>
#include <filesystem>
#include <unordered_set>
#include<memory>

namespace NameSpace_Function {

	using std::string;
	using std::vector;
	using std::unordered_set;
	using std::shared_ptr;

	class Amy_Engine final {
	private:
		Amy_Engine(void) = delete;

		Amy_Engine(const Amy_Engine&) = delete;
		Amy_Engine(Amy_Engine&&) = delete;

		Amy_Engine& operator=(const Amy_Engine&) = delete;
		Amy_Engine& operator=(Amy_Engine&&) = delete;

	public:
		Amy_Engine(const std::vector<string>& Arguments);

		~Amy_Engine(void) = default;

	public:
		float Calculate_Delta_Time(void);

		bool Tick_One_Frame(float Delta_Time);

	private:
		void Logical_Tick(float Delta_tTme);
		void Renderer_Tick(float Delta_Time);


		void Calculate_FPS(float Delta_Time);

	private:

		static inline float s_FPS_Alpha{ 1.f / 100 };
	private:


		bool m_Is_Quit{ false };

		std::chrono::steady_clock::time_point m_last_tick_time_point{ std::chrono::steady_clock::now() };

		float m_Average_Duration{ 0.f };
		int   m_Frame_Count{ 0 };
		int   m_FPS{ 0 };
	};

}// namespace NameSpace_Function