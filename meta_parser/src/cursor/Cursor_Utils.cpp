#include "cursor/Cursor_Utils.h"

namespace NameSpace_Meta_Parser::NameSpace_Cursor::NameSpace_Utils {

	const string CXString_To_String(const CXString& CXString_Temp) {
		auto cStr = clang_getCString(CXString_Temp);
		string Str{ cStr };
		clang_disposeString(CXString_Temp);
		return Str;
	}

}// namespace NameSpace_Meta_Parser::NameSpace_Cursor::NameSpace_Utils