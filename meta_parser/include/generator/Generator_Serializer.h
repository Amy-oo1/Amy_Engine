#pragma once

#include<filesystem>
#include<functional>
#include<unordered_map>
#include<string>
#include<memory>

#include "mustache.hpp"

#include "generator/Generator_Interface.h"

namespace NameSpace_Meta_Parser::NameSpace_Generator {

	using std::filesystem::path;
	using std::string;
	using std::shared_ptr;

	class Generator_Serializer final :public Generator_Interface {
	private:
		Generator_Serializer(void) = delete;

	public:
		Generator_Serializer(const Generator_Serializer&) = default;
		Generator_Serializer(Generator_Serializer&&) = default;

		Generator_Serializer& operator=(const Generator_Serializer&) = default;
		Generator_Serializer& operator=(Generator_Serializer&&) = default;

		explicit Generator_Serializer(const path& Generated_Directory);

		virtual ~Generator_Serializer(void)override = default;

	public:
		virtual void Generate(const path& Src_File_path, const path& Template_File_Path, const vector<shared_ptr<Class>>& Moudle_Classes) override;

		virtual const path Process_Dst_File_Path(const path& Src_File_Path)override;

	private:
		path m_Generated_Directory{};

		vector<path> m_Generatored_Files{};

	};

}//namespace NameSpace_Meta_Parser::NameSpace_Generator
