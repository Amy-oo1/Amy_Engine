#include "physics/Physics_Configer.h"

namespace NameSpace_Function::Namespace_Physics {

	Physics_Configer& Namespace_Physics::Physics_Configer::Get_Instance(void) {
		static Physics_Configer instance{};

		return instance;
	}

}// namespace NameSpace_Function::Namespace_Physics