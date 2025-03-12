#pragma once

#include<optional>
#include<string>
#include<fstream>
#include<sstream>

#include "file/File_System.h"
#include "logger/System_Logger.h"
#include "meta/serializer/Serializer.h"
#include "config/Resource_Configer.h"


namespace NameSpace_Resource::NameSpace_Manage {

	using std::optional;

	using NameSpace_Platform::NameSpace_File::File_System;
	using NameSpace_Platform::NameSpace_File::path;

	using NameSpace_Core::NameSpace_Logger::System_Logger;
	using NameSpace_Core::NameSpace_Meta::NameSpacce_Serializer::JSON;
	using NameSpace_Core::NameSpace_Meta::NameSpacce_Serializer::Serializer;

	using NameSpace_Config::Resource_Configer;

	class [[nodiscard]] Resource_Manager final {
	private:
		Resource_Manager(void) = delete;

		Resource_Manager(const Resource_Manager&) = delete;
		Resource_Manager(Resource_Manager&&) = delete;

		Resource_Manager& operator=(const Resource_Manager&) = delete;
		Resource_Manager& operator=(Resource_Manager&&) = delete;

		Resource_Manager(const Resource_Configer& Configer);

	public:
		~Resource_Manager(void) = default;

	public:
		template<typename Resource_Type>
		const  optional<Resource_Type> Load(const path& Resource_URL) {
			if (Resource_URL.empty()) {
				System_Logger::Get_Instance().Log(System_Logger::Level::err, "Resource_Manager::Load: Resource URL {} is empty", Resource_URL.generic_string());
				return std::nullopt;
			}
			else if (!File_System::Is_File(Resource_URL)) {
				System_Logger::Get_Instance().Log(System_Logger::Level::err, "Resource_Manager::Load: Resource URL {} is not a file ", Resource_URL.generic_string());
				return std::nullopt;
			}

			path Resource_Path = this->Get_Resource_Path(Resource_URL);
			std::ifstream Resource_IFStream{ Resource_Path };
			if (!Resource_IFStream) {
				System_Logger::Get_Instance().Log(System_Logger::Level::err, "Resource_Manager::Load: Resource URL {} failed open ", Resource_Path.generic_string());
				return std::nullopt;
			}

			JSON Resource_JSON{ JSON::parse(Resource_IFStream) };
			Resource_IFStream.close();

			return Serializer::Read<Resource_Type>(Resource_JSON);
		}

		const bool Save(const path& Resource_URL, const JSON& Resource_JSON);

	public:
		static Resource_Manager& Get_Instance(const Resource_Configer& Configer);

	private:
		const path Get_Resource_Path(const path& Resource_URL);

	private:
		const Resource_Configer& m_Configer;

	};

}// namespace NameSpace_Resource::NameSpace_ManageSpace_Resource::NameSpace_Manage