#include "frame/world/World_Manager.h"

namespace NameSpace_Function::Namespace_Frame::NameSpace_World {

	World_Manager& World_Manager::Get_Instance(void) {
		static World_Manager Instance{};

		return Instance;
	}

}// namespace NameSpace_Function::Namespace_Frame::NameSpace_World