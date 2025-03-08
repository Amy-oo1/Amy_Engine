#pragma once

#include<string>

namespace NameSpace_Meta_Parser::NameSpace_Language_Type::NameSpace_Language_Type_Utils {

	using std::string;

	const string Display_Name_Cut_FirstM(const string& Src);

	const string Cut_Angle_brackets(string Src);

	const string String_Erase(const string& Src, const string& Erase_Sub);

	const string String_Cut_Quot(const string& Src);

}// namespace NameSpace_Meta_Parser::NameSpace_Language_Type::NameSpace_Language_Type_Utils
