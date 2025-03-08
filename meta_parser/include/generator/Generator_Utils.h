#pragma once

#include<string>
#include<filesystem>
#include<vector>

namespace NameSpace_Meta_Parser::NameSpace_Generator::NameSpace_Generator_Utils {

	using std::string;
	using std::filesystem::path;
	using std::vector;

	void Save_File(const string& Out_string, const path& Out_File_Path);

	const string Connect_String(const vector<string>& Strs, const string& Connect);

	const string Get_CPPVector_Element_Type(const string& Field_Type_Spelling);

}// namespace NameSpace_Meta_Parser::NameSpace_Generator::NameSpace_Generator_Utils {