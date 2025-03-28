#pragma once

#include<optional>
#include<string>
#include<fstream>
#include<sstream>
#include<memory>

#include "file/File_System.h"
#include "logger/System_Logger.h"
#include "meta/serializer/Serializer.h"
#include "config/Resource_Configer.h"


namespace NameSpace_Resource::NameSpace_Manage {

	using std::optional;
	using std::shared_ptr;

	using NameSpace_Platform::NameSpace_File::File_System;
	using NameSpace_Platform::NameSpace_File::path;

	using NameSpace_Core::NameSpace_Logger::System_Logger;
	using NameSpace_Core::NameSpace_Meta::NameSpacce_Serializer::JSON;
	using NameSpace_Core::NameSpace_Meta::NameSpacce_Serializer::Serializer;

	using NameSpace_Config::Resource_Configer;

	class [[nodiscard]] Resource_Manager final {
	private:
		Resource_Manager(const Resource_Manager&) = delete;
		Resource_Manager(Resource_Manager&&) = delete;

		Resource_Manager& operator=(const Resource_Manager&) = delete;
		Resource_Manager& operator=(Resource_Manager&&) = delete;

		Resource_Manager(void) = default;

	public:
		~Resource_Manager(void) = default;

	public:
		template<typename Resource_Type>
		const  shared_ptr<Resource_Type> Load(const path& Resource_URL) {
			if (Resource_URL.empty()) {
				System_Logger::Get_Instance().Log(System_Logger::Level::err, "Resource_Manager::Load: Resource URL {} is empty", Resource_URL.generic_string());
				return nullptr;
			}
			else if (!File_System::Is_File(Resource_URL)) {
				System_Logger::Get_Instance().Log(System_Logger::Level::err, "Resource_Manager::Load: Resource URL {} is not a file ", Resource_URL.generic_string());
				return nullptr;
			}

			path Resource_Path = this->Get_Resource_Path(Resource_URL);
			std::ifstream Resource_IFStream{ Resource_Path };
			if (!Resource_IFStream) {
				System_Logger::Get_Instance().Log(System_Logger::Level::err, "Resource_Manager::Load: Resource URL {} failed open ", Resource_Path.generic_string());
				return nullptr;
			}

			JSON Resource_JSON{ JSON::parse(Resource_IFStream) };
			Resource_IFStream.close();

			return nullptr;
			//TODO ::
			//return Serializer::Read<Resource_Type>(Resource_JSON);
		}

		bool Save(const path& Resource_URL, const JSON& Resource_JSON);

	public:
		static Resource_Manager& Get_Instance(void);

		const char* URL_To_File_Full_Path(const path& Resource_URL);

	private:
		const path Get_Resource_Path(const path& Resource_URL);

	};

}// namespace NameSpace_Resource::NameSpace_ManageSpace_Resource::NameSpace_Manage