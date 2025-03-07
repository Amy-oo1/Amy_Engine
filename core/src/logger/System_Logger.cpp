
#include "logger/System_Logger.h"  

#include<iostream>

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/async.h"

namespace NameSpace_Core::NameSpace_System_Logger {
	System_Logger::System_Logger(void) {
		//Consoule Sink
		auto ConsoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		ConsoleSink->set_level(spdlog::level::trace);
		ConsoleSink->set_pattern("[%H:%M:%S %e] [%^%l%$] [thread %t] %v");

		//Default Get_Instance Thread Pool
		spdlog::init_thread_pool(8192, 1);

		this->m_Logger = std::make_shared<spdlog::async_logger>("System_Logger", ConsoleSink, spdlog::thread_pool(), spdlog::async_overflow_policy::block); this->m_Logger->set_level(spdlog::level::trace);
		spdlog::register_logger(m_Logger);
	}

	System_Logger::~System_Logger(void) {
		m_Logger->flush();
		spdlog::drop_all();
	}

	System_Logger& System_Logger::Get_Instance(void) {
		static System_Logger Get_Instance{};
		return Get_Instance;
	}

}// namespace NameSpace_Core::NameSpace_System_Logger