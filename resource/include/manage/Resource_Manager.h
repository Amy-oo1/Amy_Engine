#pragma once

#include<optional>
#include<string>
#include<fstream>
#include<sstream>
#include<exception>
#include<memory>

#include "file/File_System.h"
#include "logger/System_Logger.h"
#include "meta/serializer/Serializer.h"
#include "meta/generated/Serializer_Header.h"

#include "config/Resource_Configer.h"

namespace NameSpace_Resource::NameSpace_Manage {

	using std::optional;
	using std::shared_ptr;

	using NameSpace_Platform::NameSpace_File::File_System;
	using NameSpace_Platform::NameSpace_File::path;

	using NameSpace_Core::NameSpace_Logger::System_Logger;

	using NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::JSON;
	using NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer;

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
		static shared_ptr<Resource_Type> Load(const path& Resource_URL) {
			if (Resource_URL.empty()) {
				System_Logger::Get_Instance().Log(System_Logger::Level::err, "Resource_Manager::Load: Resource URL {} is empty", Resource_URL.generic_string());

				return nullptr;
			}

			std::ifstream Resource_IFStream{ Resource_Manager::URL_To_File_Full_Path(Resource_URL).generic_string().c_str() };
			if (!Resource_IFStream) {
				System_Logger::Get_Instance().Log(System_Logger::Level::err, "Resource_Manager::Load: Resource URL  failed open ");

				return nullptr;
			}

			JSON Resource_JSON{ JSON::parse(Resource_IFStream) };
			Resource_IFStream.close();

			shared_ptr<Resource_Type> Resource{};
			return Serializer::Read(Resource_JSON, Resource);
		}

		template<typename Resource_Type>
		static bool Save(const shared_ptr<Resource_Type>& Resource, const path& Resource_URL) {
			if (Resource_URL.empty()) {
				System_Logger::Get_Instance().Log(System_Logger::Level::err, "Resource_Manager::Save: Resource URL {} is empty", Resource_URL.generic_string());

				return false;
			}
			else if (!File_System::Is_File(Resource_URL)) {
				System_Logger::Get_Instance().Log(System_Logger::Level::err, "Resource_Manager::Save: Resource URL {} is not a file ", Resource_URL.generic_string());

				return false;
			}

			JSON Resource_JSON{ Serializer::Write(Resource) };
			if (Resource_JSON.empty()) {
				System_Logger::Get_Instance().Log(System_Logger::Level::err, "Resource_Manager::Save: Resource URL {} failed to serialize ", Resource_URL.generic_string());

				return false;
			}

			path Resource_Path = Resource_Manager::URL_To_File_Full_Path(Resource_URL);
			std::ofstream Resource_OFStream{ Resource_Path };
			if (!Resource_OFStream) {
				System_Logger::Get_Instance().Log(System_Logger::Level::err, "Resource_Manager::Save: Resource URL {} failed open ", Resource_Path.generic_string());

				return false;
			}
			Resource_OFStream << Resource_JSON.dump();
			Resource_OFStream.close();

			return true;
		}

	public:
		static const path URL_To_File_Full_Path(const path& Resource_URL);

	public:
		static Resource_Manager& Get_Instance(void);

	};

}// namespace NameSpace_Resource::NameSpace_ManageSpace_Resource::NameSpace_Manage