#pragma once

#include<string>
#include<vector>

#include "Jolt/Jolt.h"
#include "Jolt/Core/Factory.h"

#include "file/File_System.h"

#include "logger/System_Logger.h"

#include "config/Resource_Configer.h"
#include "manage/Resource_Manager.h"

#include "animation/Animation_Loader.h"

#include "physics/Physics_Manager.h"
#include "frame/world/World_Manager.h"

#include "render/window/Window_System.h"
#include "input/Input_System.h"

#include "render/render_system/Render_Obejct.h"
#include "render/render_system/Render_GUID_Allocator.h"

namespace NameSpace_Function::Namespace_Global {

	using std::string;
	using std::vector;
	using std::shared_ptr;

	using JPH::Factory;

	using NameSpace_Platform::NameSpace_File::path;

	using NameSpace_Core::NameSpace_Logger::System_Logger;

	using NameSpace_Resource::NameSpace_Config::Resource_Configer;
	using NameSpace_Resource::NameSpace_Manage::Resource_Manager;

	using Namespace_Physics::Physics_Manager;
	using Namespace_Frame::NameSpace_World::World_Manager;

	using NameSpace_Animation::Animation_Loader;

	using NameSpace_Render::NameSpace_Window::Window_System;
	using Namespace_Input::Input_System;

	using NameSpace_Render::NameSpace_Render_System::Render_GUID_Allocator;
	using NameSpace_Render::NameSpace_Render_System::Game_Object_Part_ID;

	class Global_Systemer final {
	private:
		Global_Systemer(const Global_Systemer&) = delete;
		Global_Systemer(Global_Systemer&&) = delete;

		Global_Systemer& operator=(const Global_Systemer&) = delete;
		Global_Systemer& operator=(Global_Systemer&&) = delete;

		Global_Systemer(void);

	public:
		~Global_Systemer(void);

	public:
		static void Initialize(const vector<string>& Arguments);

		static Global_Systemer& Get_Instance(void);

	public:
		System_Logger& System_Logger;

		Resource_Configer& Resource_Configer;
		Resource_Manager& Resource_Manager;

		Physics_Manager& Physics_Manager;
		World_Manager& World_Manager;

		//Animation_Loader& Animation_Loader;

		//Factory*& Factory_Instance;

		shared_ptr<Window_System> Main_Window{ nullptr };
		shared_ptr<Input_System> Main_Input{ nullptr };

		//Render_GUID_Allocator<Game_Object_Part_ID>& Render_GUID_Allocator;


	private:
		static inline vector<string> s_Arguments{};

	};

}// namespace NameSpace_Function::Namespace_Global