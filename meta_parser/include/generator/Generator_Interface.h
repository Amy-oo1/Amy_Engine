#pragma once

#include<vector>
#include<filesystem>
#include<memory>

#include "mustache.hpp"

#include "language_type/Class.h"

namespace NameSpace_Meta_Parser::NameSpace_Generator {

	using std::vector;
	using std::filesystem::path;
	using std::shared_ptr;

	using NameSpace_Language_Type::Class;

	class Generator_Interface {
	public:
		Generator_Interface(void) = default;

		Generator_Interface(const Generator_Interface&) = default;
		Generator_Interface(Generator_Interface&&) = default;

		Generator_Interface& operator=(const Generator_Interface&) = default;
		Generator_Interface& operator=(Generator_Interface&&) = default;

		virtual ~Generator_Interface(void) = default;

	public:
		virtual void Generate(const path& Src_File_path, const path& Template_File_Path, const vector<shared_ptr<Class>>& Moudle_Classes) = 0;

		virtual const path Process_Dst_File_Path(const path& Src_File_Path) = 0;

	protected:
		static const mustache::data Generate_Class_Field_RenderData(shared_ptr<Class> Current_Class);

		static const mustache::data Generate_Class_Method_RenderData(shared_ptr<Class> Current_Class);

		static const mustache::data Generate_Class_RenderData(shared_ptr<Class> Current_Class);

	};

}// namespace  NameSpace_Meta_Parser::NameSpace_Generator