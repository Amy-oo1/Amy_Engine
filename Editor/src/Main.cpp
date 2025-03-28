#include<string>
#include<vector>
#include<memory>

#include "Engine.h"

using std::unique_ptr;

using NameSpace_Function::Amy_Engine;

int main() {
	std::vector<std::string> Argements{ "Hello", "World" };

	unique_ptr<Amy_Engine> Engine = std::make_unique<Amy_Engine>(Argements);


};