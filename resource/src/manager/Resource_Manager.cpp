#include "manage/Resource_Manager.h"

#include "file/File_System.h"

namespace NameSpace_Resource::NameSpace_Manage {

	Resource_Manager::Resource_Manager(const Resource_Configer& Configer, std::shared_ptr<System_Logger> Logger) :
		m_Configer{ Configer },
		m_Logger{ Logger } {
	}

	Resource_Manager& Resource_Manager::Get_Instance(const Resource_Configer& Configer, std::shared_ptr<System_Logger> Logger) {
		static Resource_Manager Instance{ Configer ,Logger };

		return Instance;
	}

	const path Resource_Manager::Get_Resource_Path(const path& Resource_URL) {
		return std::filesystem::absolute(this->m_Configer.Get_Root_Directory() / Resource_URL);
	}

}// namespace NameSpace_Resource::NameSpace_Manage