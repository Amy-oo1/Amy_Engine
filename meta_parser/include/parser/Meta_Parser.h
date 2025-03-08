#pragma once

#include<filesystem>
#include<fstream>
#include<string>
#include<vector>
#include<unordered_map>
#include<memory>

#include "cursor/Cursor.h"
#include "cursor/TranslationUnit_Cursor.h"
#include "language_type/Class.h"
#include "generator/Generator_Interface.h"

namespace NameSpace_Meta_Parser::NameSpace_Meta_Parser {

	using std::filesystem::path;
	using std::string;
	using std::vector;
	using std::shared_ptr;

	using NameSpace_Cursor::Cursor;
	using NameSpace_Cursor::TranslationUnit_Cursor;
	using NameSpace_Language_Type::Class;
	using NameSpace_Generator::Generator_Interface;

	class Meta_Parser {
	private:
		Meta_Parser(void) = delete;

		Meta_Parser(const Meta_Parser&) = delete;
		Meta_Parser(Meta_Parser&&) = delete;

		Meta_Parser& operator=(const Meta_Parser&) = delete;
		Meta_Parser& operator=(Meta_Parser&&) = delete;

	public:
		Meta_Parser(const path& Header_File_Path, const vector<const char*>& clang_Command_Arguments);

		~Meta_Parser(void) = default;

	public:
		void Build_AST(vector<string>& Current_NameSpace);

		void Generator_Files(const path& Source_File_Directory, const path& Reflection_Template, const path& Serializer_Template);

		void Finish_Generator(const path& Relection_Header_File, const path& Serializer_Header_File);

	private:
		const path Class_Get_Head_File(const string& Class_Name)const;

		void Base_Build_AST(const Cursor& Current_Cursor, vector<string>& Current_NameSpace);

	public:
		TranslationUnit_Cursor m_Handle;

		std::unordered_map<path, vector<shared_ptr<Class>>> m_Class_Modules{};
		std::unordered_map<string, path> m_Type_Table{};

		std::unique_ptr<Generator_Interface> m_Generator_Reflection{ nullptr };
		std::unique_ptr<Generator_Interface> m_Generator_Serializer{ nullptr };

	};

}// namespace NameSpace_Meta_Parser::NameSpace_Meta_Parser