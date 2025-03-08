#pragma once

#include<string>
#include<vector>

namespace NameSpace_Meta_Parser::NameSpace_Meta::NameSpace_Utils {

	using std::string;
	using std::vector;

	const vector<string> Split(const string& Src, const  string::value_type& PSat);

	const string Trim(const string& Src);

}//namespace NameSpace_Utils