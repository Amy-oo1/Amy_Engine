#include "language_type/Language_Utils.h"

namespace NameSpace_Meta_Parser::NameSpace_Language_Type::NameSpace_Language_Type_Utils {

	const string Display_Name_Cut_FirstM(const string& Src) {
		if (Src.size() > 2 && Src[0] == 'm' && Src[1] == '_')
			return Src.substr(2);
		return Src;
	}

	const string Cut_Angle_brackets(string Src) {
		for (auto Iter_begin = Src.begin(); Iter_begin != Src.end(); ++Iter_begin)
			if (*Iter_begin == '<')
				*Iter_begin = 'L';
			else if (*Iter_begin == '>')
				*Iter_begin = 'R';

		return Src;
	}

	const string String_Erase(const string& Src, const string& Erase_Sub) {
		string::size_type Index_Begin = 0;
		string Dst{ Src };

		while ((Index_Begin = Src.find(Erase_Sub)) != string::npos)
			Dst.replace(Index_Begin, Erase_Sub.length(), "");

		return Dst;
	}

	const string String_Cut_Quot(const string& Src) {
		string::size_type Index_Begin = Src.find_first_of('\"') + 1;
		string::size_type Index_End = Src.find_last_of('\"');
		if (Index_Begin > 0 && Index_End < Src.size() && Index_Begin < Index_End)
			return Src.substr(Index_Begin, Index_End - Index_Begin);

		return Src;
	}

}// namespace NameSpace_Meta_Parser::NameSpace_Language_Type::NameSpace_Language_Type_Utils