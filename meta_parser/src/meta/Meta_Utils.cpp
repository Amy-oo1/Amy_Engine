#include "meta/Meta_Utils.h"

#include<cstdint>
#include<sstream>
#include<cctype>

namespace NameSpace_Meta_Parser::NameSpace_Meta::NameSpace_Utils {

	const vector<string> Split(const string& Src, const string::value_type& Pat) {
		vector<string> List;
		std::istringstream String_In_Stream{ Src };

		string Item;
		while (std::getline(String_In_Stream, Item, Pat))
			List.emplace_back(Item);

		return List;
	}

	const string Trim(const string& Src) {
		auto Begin_Iter = Src.begin();
		while (Begin_Iter != Src.end() && std::isspace(*Begin_Iter))
			++Begin_Iter;

		auto End_Iter = Src.rbegin();
		while (End_Iter.base() != Begin_Iter && std::isspace(*End_Iter))
			++End_Iter;

		return { Begin_Iter, End_Iter.base() };
	}

}// namespace NameSpace_Meta_Parser::NameSpace_Meta::NameSpace_Utils