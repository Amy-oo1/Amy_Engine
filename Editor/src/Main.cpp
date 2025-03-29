#include<string>
#include<vector>
#include<memory>
#include<filesystem>

#include "meta/generated/Reflection_Header.h"
#include "meta/generated/Serializer_Header.h"

#include "file/File_System.h"

#include "Engine.h"

using std::unique_ptr;

using NameSpace_Function::Amy_Engine;

int main(int argc, char** argv) {

	std::filesystem::path Config_Path{ std::filesystem::current_path() / ".." / "bin" / "Amy_Engine_Config.ini" };

	std::vector<std::string> Argements{
		Config_Path.generic_string()
	};

	unique_ptr<Amy_Engine> Engine = std::make_unique<Amy_Engine>(Argements);


};