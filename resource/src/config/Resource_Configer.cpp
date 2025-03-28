#include "config/Resource_Configer.h"

namespace NameSpace_Resource::NameSpace_Config {

	Resource_Configer::Resource_Configer(const path& Confige_file)
		:m_Root_Directory{ Confige_file } {

	}

	const path Resource_Configer::Get_Root_Directory(void) const {
		return this->m_Root_Directory;
	}

	Resource_Configer& Resource_Configer::Get_Instance(void) {
		static Resource_Configer Instance{ "resource" };//TODO : change this to a config file

		return Instance;
	}

}// namespace NameSpace_Resource::NameSpace_Config