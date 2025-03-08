#pragma once

#include<filesystem>
#include<vector>
#include<string>
#include<memory>

#include "generator/Generator_Interface.h"

namespace NameSpace_Meta_Parser::NameSpace_Generator {

	using std::filesystem::path;
	using std::vector;
	using std::string;
	using std::shared_ptr;

	class Generator_Reflection final :public Generator_Interface {
	private:
		Generator_Reflection(void) = delete;

	public:
		Generator_Reflection(const Generator_Reflection&) = default;
		Generator_Reflection(Generator_Reflection&&) = default;

		Generator_Reflection& operator=(const Generator_Reflection&) = default;
		Generator_Reflection& operator=(Generator_Reflection&&) = default;

		explicit Generator_Reflection(const path& Generated_Directory);

		virtual ~Generator_Reflection(void)override = default;

	public:
		virtual void Generate(const path& Src_File_path, const path& Template_File_Path, const vector<shared_ptr<Class>>& Moudle_Classes) override;

		virtual const path Process_Dst_File_Path(const path& Src_File_Path)override;

	private:
		path m_Generated_Directory{};

		vector<path> m_Generatored_Files{};
	};

};// namespace NameSpace_Meta_Parser::NameSpace_Generator