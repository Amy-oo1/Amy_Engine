#include "manage/Resource_Manager.h"

namespace NameSpace_Resource::NameSpace_Manage {

	Resource_Manager& Resource_Manager::Get_Instance(void) {
		static Resource_Manager Instance{};

		return Instance;
	}

	const char* Resource_Manager::URL_To_File_Full_Path(const path& Resource_URL) {
		return nullptr;
	}

}// namespace NameSpace_Resource::NameSpace_Manage