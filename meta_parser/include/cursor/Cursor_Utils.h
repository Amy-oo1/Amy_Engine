#pragma once

#include<string>

#include "clang-c/Index.h"

namespace NameSpace_Meta_Parser::NameSpace_Cursor::NameSpace_Utils {

	using std::string;

	const string CXString_To_String(const CXString& CXString_Temp);

}// namespace NameSpace_Meta_Parser::NameSpace_Cursor::NameSpace_Utils