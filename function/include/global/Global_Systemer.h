#pragma once

#include<vector>
#include<string>

#include "file/File_System.h"

#include "config/Resource_Configer.h"
#include "manage/Resource_Manager.h"

#include "animation/Animation_Loader.h"

namespace NameSpace_Function::Namespace_Global {

	using std::vector;
	using std::string;

	using NameSpace_Platform::NameSpace_File::path;

	using NameSpace_Resource::NameSpace_Config::Resource_Configer;
	using NameSpace_Resource::NameSpace_Manage::Resource_Manager;

	using NameSpace_Animation::Animation_Loader;

	class Global_Systemer final {
	private:
		Global_Systemer(void) = delete;

		Global_Systemer(const Global_Systemer&) = delete;
		Global_Systemer(Global_Systemer&&) = delete;

		Global_Systemer& operator=(const Global_Systemer&) = delete;
		Global_Systemer& operator=(Global_Systemer&&) = delete;

		Global_Systemer(const vector<string>& Arguments);

	public:
		~Global_Systemer(void) = default;

	public:
		static Global_Systemer& Get_Instance(const vector<string>& Arguments);

		static Global_Systemer& Get_Instance(void);

	public:
		Resource_Configer& Resource_Configer;
		Resource_Manager& Resource_Manager;

		Animation_Loader& Animation_Loader;

	private:
		static inline vector<string> g_Arguments{};

	};

}// namespace NameSpace_Function::Namespace_Global