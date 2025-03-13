#include "global/Global_Systemer.h"

#include "file/File_System.h"

namespace NameSpace_Function::Namespace_Global {

	using NameSpace_Core::NameSpace_Logger::System_Logger;

	Global_Systemer::Global_Systemer(const vector<string>& Arguments) :
		Resource_Configer{ Resource_Configer::Get_Instance(Arguments[0]) },
		Resource_Manager{ Resource_Manager::Get_Instance(this->Resource_Configer) },
		Animation_Loader{ Animation_Loader::Get_Instance(this->Resource_Manager) } {
		if (!Global_Systemer::g_Arguments.empty())
			System_Logger::Get_Instance().Log(System_Logger::Level::critical, "Global Systemer Already Initialized");

		Global_Systemer::g_Arguments = Arguments;
	}

	Global_Systemer& Global_Systemer::Get_Instance(const vector<string>& Arguments) {
		static Global_Systemer Instance{ Arguments };

		return Instance;
	}

	Global_Systemer& Global_Systemer::Get_Instance(void) {
		if (Global_Systemer::g_Arguments.empty())
			System_Logger::Get_Instance().Log(System_Logger::Level::critical, "Global Systemer Not Initialized");

		return Global_Systemer::Get_Instance(Global_Systemer::g_Arguments);
	}

}// namespace NameSpace_Function::Namespace_Global