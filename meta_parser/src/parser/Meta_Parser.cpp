#include "parser/Meta_Parser.h"

#include<utility>

#include "generator/Generator_Reflection.h"
#include "generator/Generator_Serializer.h"

namespace NameSpace_Meta_Parser::NameSpace_Meta_Parser {

	using NameSpace_Generator::Generator_Reflection;
	using NameSpace_Generator::Generator_Serializer;

	Meta_Parser::Meta_Parser(const path& Header_File_Path, const vector<const char*>& clang_Command_Arguments)
		:m_Handle{ Header_File_Path,clang_Command_Arguments } {
	}

	void Meta_Parser::Build_AST(vector<string>& Current_NameSpace) {
		this->Base_Build_AST(this->m_Handle.Get_Cursor(), Current_NameSpace);
	}

	void Meta_Parser::Generator_Files(const path& Source_File_Directory, const path& Reflection_Template, const path& Serializer_Template) {
		this->m_Generator_Reflection = std::make_unique<NameSpace_Generator::Generator_Reflection>(Source_File_Directory);
		this->m_Generator_Serializer = std::make_unique<NameSpace_Generator::Generator_Serializer>(Source_File_Directory);

		for (const auto& [Temp_Source_File_Path, Temp_Module_Classess] : this->m_Class_Modules) {
			this->m_Generator_Reflection->Generate(Temp_Source_File_Path, Reflection_Template, Temp_Module_Classess);
			this->m_Generator_Serializer->Generate(Temp_Source_File_Path, Serializer_Template, Temp_Module_Classess);
		}
	}

	void Meta_Parser::Finish_Generator(const path& Relection_Header_Name, const path& Serializer_Header_Name) {
		std::ofstream Reflection_Header{ Relection_Header_Name }, Serializer_Header{ Serializer_Header_Name };

		Reflection_Header << R"(#pragma once)" << std::endl;
		Serializer_Header << R"(#pragma once)" << std::endl;

		for (const auto& [Src_Path, Classes] : this->m_Class_Modules) {
			Reflection_Header << R"(#include ")" << this->m_Generator_Reflection->Process_Dst_File_Path(Src_Path).generic_string() << R"(")" << std::endl;
			Serializer_Header << R"(#include ")" << this->m_Generator_Serializer->Process_Dst_File_Path(Src_Path).generic_string() << R"(")" << std::endl;
		}

	}

	const path Meta_Parser::Class_Get_Head_File(const string& Class_Name)const {
		auto iter = this->m_Type_Table.find(Class_Name);

		return (iter == this->m_Type_Table.end()) ? string{} : iter->second;
	}

	void Meta_Parser::Base_Build_AST(const Cursor& Current_Cursor, vector<string>& Current_NameSpace) {
		for (const auto& Temp_Child : Current_Cursor.Get_Children()) {
			auto Temp_Cursor_Kind = Temp_Child.Get_Cursor_Kind();

			if (Temp_Child.Is_Definition() && (Temp_Cursor_Kind == Cursor::Cursor_Kind::CURSOR_CLASSDECL || Temp_Cursor_Kind == Cursor::Cursor_Kind::CURSOR_STRUCTDECL)) {

				shared_ptr<Class> Temp_Class{ Class::Create_Class(Temp_Child, Current_NameSpace) };
				if (Temp_Class->Should_Compile()) {
					path Temp_Source_File_Path = Temp_Class->Get_Source_File_Path();
					this->m_Type_Table[Temp_Class->Get_Class_Spelling()] = Temp_Source_File_Path;

					this->m_Class_Modules[Temp_Source_File_Path].emplace_back(std::move(Temp_Class));
				}
			}
			else if (Temp_Cursor_Kind == Cursor::Cursor_Kind::CURSOR_NAMESPACE) {
				Current_NameSpace.emplace_back(Temp_Child.Get_Cursor_Spelling());
				this->Base_Build_AST(Temp_Child, Current_NameSpace);
				Current_NameSpace.pop_back();
			}
		}
	}

}// namespace NameSpace_Meta_Parser::NameSpace_Meta_Parser