#include "global/Global_Systemer.h"  
#include "Jolt/RegisterTypes.h"  
#include "file/File_System.h"  

namespace NameSpace_Function::Namespace_Global {

	using NameSpace_Render::NameSpace_Render_System::Render_System_Initialization_Info;

	using NameSpace_Core::NameSpace_Logger::System_Logger;

	Global_Systemer::Global_Systemer(void) :
		System_Logger{ System_Logger::Get_Instance() },
		Resource_Configer{ Resource_Configer::Get_Instance() },
		Resource_Manager{ Resource_Manager::Get_Instance() },
		Physics_Manager{ Physics_Manager::Get_Instance() },
		World_Manager{ World_Manager::Get_Instance() },
		Particle_Manager{ Particle_Manager::Get_Instance() }
		/*,
		Animation_Loader{ Animation_Loader::Get_Instance() },
		Factory_Instance{ Factory::sInstance = new Factory() } */ {
		if (Global_Systemer::s_Arguments.empty())
			System_Logger::Get_Instance().Log(System_Logger::Level::critical, "Global Systemer No Initialized");

		this->Main_Window = std::make_shared<Window_System>();
		this->Main_Input = std::make_shared<Input_System>(this->Main_Window);

		Render_System_Initialization_Info Render_System_Info{};
		{
			Render_System_Info.Window_System = this->Main_Window;
		}
		this->Main_Render_System = std::make_shared<Render_System>(Render_System_Info);

		//JPH::RegisterTypes();  
	}

	Global_Systemer::~Global_Systemer(void) {
		//delete Factory_Instance;  
	}

	void Global_Systemer::Initialize(const vector<string>& Arguments) {
		//TODO : change this to a config file  
		Global_Systemer::s_Arguments = Arguments;

		Resource_Configer::s_Config_File_Name = path(Arguments.front(), path::generic_format);

		//NOTE: Init  
		Global_Systemer::Get_Instance();
	}

	Global_Systemer& Global_Systemer::Get_Instance(void) {
		static Global_Systemer Instance{};

		return Instance;
	}

}// namespace NameSpace_Function::Namespace_Global