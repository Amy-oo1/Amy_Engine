#include<filesystem>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<chrono>

#include "parser/Command_Config.h"
#include "parser/Meta_Parser.h"

#include "clang-c/Index.h"

int main(int argc, char* argv[]) {

	using namespace NameSpace_Meta_Parser::NameSpace_Parser::NameSpace_Command_Config;

	//----------------------------Header_File----------------------------------------------------------------
	std::filesystem::path Project_Inputs_File_Paths{ "D:/Amy_Engine/meta_parser/bin/project_input.txt",std::filesystem::path::generic_format };

	std::filesystem::path Parser_Header_File_Path{ "D:/Amy_Engine/core/include/meta/generated/Parser_Header.h",std::filesystem::path::generic_format };

	//-----------------------------Work Path------------------------------------------------------------------
	const std::filesystem::path Work_Directory{ Parser_Header_File_Path.parent_path()};
	std::filesystem::create_directories(Parser_Header_File_Path.parent_path());

#ifdef _DEBUG
	std::cout << "Project Need Headers All In File (In Line)    " << Project_Inputs_File_Paths.generic_string() << std::endl;
	std::cout << "Include All Heade To A Header File To Prser In      " << Parser_Header_File_Path.generic_string() << std::endl;
	std::cout << "Work Directory: Generacted In Here         " << Work_Directory.generic_string() << std::endl;
#endif // DEBUG

	std::ifstream Head_File_Paths{Project_Inputs_File_Paths};
	std::ofstream Header{Parser_Header_File_Path};

#ifdef _DEBUG
	if (Head_File_Paths.fail())
		std::cout << "Not Load File" << Project_Inputs_File_Paths.generic_string() << std::endl;
	if (!Header.is_open())
		std::cout << "Not Load File" << Parser_Header_File_Path.generic_string() << std::endl;
#endif // DEBUG

	Header << R"(#pragma once)" << std::endl;
	std::string line{};
	while (std::getline(Head_File_Paths, line))
		Header << R"(#include ")" << std::filesystem::path{ line,std::filesystem::path::generic_format }.generic_string() << R"(")" << std::endl;

	Head_File_Paths.close();
	Header.close();

	//-----------------------------clang_Command-------------------------------------------------------
	std::vector<const char *> clang_Command_Arguments{};
	for (const auto& Temp_Command : clang_line_Commands)
		clang_Command_Arguments.emplace_back(Temp_Command);

	for (const auto& Temp_Preprocess : Preprocessors)
		clang_Command_Arguments.emplace_back(Temp_Preprocess);

	for (const auto& Temp_Include : Includes)
		clang_Command_Arguments.emplace_back(Temp_Include);

	std::cout <<"Command Line : " << std::endl;
	for (const auto& Temp_Command : clang_Command_Arguments) {
		std::cout << Temp_Command << std::endl;
	}

	//-----------------------------Meta_parser_Build_AST---------------------------------------------------------------
	NameSpace_Meta_Parser::NameSpace_Meta_Parser::Meta_Parser Parser{Parser_Header_File_Path, clang_Command_Arguments};

	std::vector<std::string> NameSpace{};
	Parser.Build_AST(NameSpace);
	NameSpace.clear();

	////---------------------------Meta_parser_Generator_File---------------------------------------------------------------
	Parser.Generator_Files(
		Work_Directory,
		std::filesystem::path{ "D:/Amy_Engine/meta_parser/template/reflection/Common_Class_Reflection.mustache",std::filesystem::path::generic_format },
		std::filesystem::path{ "",std::filesystem::path::generic_format});
	
	////---------------------------Meta_parser_Finish_Generator---------------------------------------------------------------
	
	Parser.Finish_Generator(
		Work_Directory / "Reflection_Header.h",
		Work_Directory / "Serializer_Header.h"
	);


}
