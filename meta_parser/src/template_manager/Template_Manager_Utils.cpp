#include "template_manager/Template_Manager_Utils.h"

#include<fstream>
#include<sstream>

namespace NameSpace_Meta_Parser::NameSpace_Template_Manager::NameSpace_Template_Manager_Utils {

	const string Load_File(const path& File_Path) {
		std::ifstream Ifstream_File{ File_Path };
		std::ostringstream Out_Stream_Template{};

		string String_Line{};
		while (std::getline(Ifstream_File, String_Line))
			Out_Stream_Template << String_Line << std::endl;

		Ifstream_File.close();

		return Out_Stream_Template.str();
	}

}// namespace NameSpace_Meta_Parser::NameSpace_Template_Manager::NameSpace_Template_Manager_Utils