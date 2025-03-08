#pragma once

#include "file/File_System.h"

namespace NameSpace_Resource::NameSpace_Config {

	using NameSpace_Platform::NameSpace_File::path;

	class Resource_Configer final {
	private:
		Resource_Configer(void) = delete;

		Resource_Configer(const Resource_Configer&) = delete;
		Resource_Configer(Resource_Configer&&) = delete;

		Resource_Configer& operator=(const Resource_Configer&) = delete;
		Resource_Configer& operator=(Resource_Configer&&) = delete;

		Resource_Configer(const path& Confige_file);

	public:
		~Resource_Configer(void) = default;

	public:
		const path Get_Root_Directory(void) const;

	public:
		static Resource_Configer& Get_Instance(const path& Confige_file);

	private:
		path m_Root_Directory{};

	};

}// namespace NameSpace_Resource::NameSpace_Config