#include "Engine.h"

#include "global/Global_Systemer.h"

namespace NameSpace_Function {
	
	using Namespace_Global::Global_Systemer;

	Amy_Engine::Amy_Engine(const std::vector<std::string>& Arguments){

		Global_Systemer::Initialize(Arguments);

		const Global_Systemer& Systemer = Global_Systemer::Get_Instance();
	}
}// namespace NameSpace_Function