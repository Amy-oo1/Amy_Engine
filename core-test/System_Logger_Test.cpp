#include "pch.h"

#include "logger/System_Logger.h"

namespace Core::Logger::System_logger {

	using  NameSpace_Core::NameSpace_Logger::System_Logger;

	TEST(System_Logger_Test, Sygn_Instance) {
		System_Logger::Get_Instance();
	}

	TEST(System_Logger_Test, Log_Trace) {
		System_Logger& system_logger = System_Logger::Get_Instance();
		system_logger.Log(System_Logger::Level::trace, "Log_Trace");
	}

	TEST(System_Logger_Test, Log_Debug) {
		System_Logger& system_logger = System_Logger::Get_Instance();
		system_logger.Log(System_Logger::Level::trace, "Log_Debug");
	}

	TEST(System_Logger_Test, Log_Info) {
		System_Logger& system_logger = System_Logger::Get_Instance();
		system_logger.Log(System_Logger::Level::trace, "Log_Info");
	}

	TEST(System_Logger_Test, Log_Warn) {
		System_Logger& system_logger = System_Logger::Get_Instance();
		system_logger.Log(System_Logger::Level::trace, "Log_Warn");
	}

	TEST(System_Logger_Test, Log_Err) {
		System_Logger& system_logger = System_Logger::Get_Instance();
		system_logger.Log(System_Logger::Level::trace, "Log_Err");
	}

}// namespace Core::Logger::System_logger