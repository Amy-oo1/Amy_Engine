#include "generator/Generator_Utils.h"

#include<fstream>
#include<algorithm>
#include <numeric>

namespace NameSpace_Meta_Parser::NameSpace_Generator::NameSpace_Generator_Utils {

	void Save_File(const string& Out_string, const path& Out_File_Path) {
		if (std::filesystem::exists(Out_File_Path.parent_path()))
			std::filesystem::create_directories(Out_File_Path.parent_path());

		std::fstream Output_File_Stream(Out_File_Path, std::ios_base::out);

		Output_File_Stream << Out_string << std::endl;
		Output_File_Stream.flush();
		Output_File_Stream.close();
	}

	const string Connect_String(const vector<string>& Strs, const string& Connect) {
		auto Ans = accumulate(Strs.begin(), Strs.end(), string{}, [&Connect](const string& Temp, const string& Temp_Str) {return Temp + Temp_Str + Connect; });

		Ans.erase(Ans.end() - Connect.size(), Ans.end());

		return Ans;
	}

	const string Get_CPPVector_Element_Type(const string& Field_Type_Spelling) {
		auto Iter_Left = Field_Type_Spelling.find_first_of('<');
		auto Iter_Right = Field_Type_Spelling.find_last_of('>');

		if (Iter_Left == string::npos || Iter_Right == string::npos)
			return string{};
		return Field_Type_Spelling.substr(Iter_Left + 1, Iter_Right - Iter_Left - 1);
	}

}// namespace NameSpace_Meta_Parser::NameSpace_Generator::NameSpace_Generator_Utils