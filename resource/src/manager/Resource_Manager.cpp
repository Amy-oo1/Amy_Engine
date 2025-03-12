#include "manage/Resource_Manager.h"

namespace NameSpace_Resource::NameSpace_Manage {

	Resource_Manager::Resource_Manager(const Resource_Configer& Configer)
		: m_Configer{ Configer } {
	}
	

	const bool Resource_Manager::Save(const path& Resource_URL, const JSON& Resource_JSON) {
		if (Resource_URL.empty()) {
			System_Logger::Get_Instance().Log(System_Logger::Level::err, "Resource_Manager::Save: Resource URL {} is empty", Resource_URL.generic_string());
			return false;
		}
		else if (!File_System::Is_File(Resource_URL)) {
			System_Logger::Get_Instance().Log(System_Logger::Level::err, "Resource_Manager::Save: Resource URL {} is not a file ", Resource_URL.generic_string());
			return false;
		}

		path Resource_Path = this->Get_Resource_Path(Resource_URL);
		std::ofstream Resource_OFStream{ Resource_Path };
		if (!Resource_OFStream) {
			System_Logger::Get_Instance().Log(System_Logger::Level::err, "Resource_Manager::Save: Resource URL {} failed open ", Resource_Path.generic_string());
			return false;
		}

		Resource_OFStream << Resource_JSON.dump(4);
		Resource_OFStream.close();

		return true;
	}

	Resource_Manager& Resource_Manager::Get_Instance(const Resource_Configer& Configer) {
		static Resource_Manager Instance{ Configer };

		return Instance;
	}

	const path Resource_Manager::Get_Resource_Path(const path& Resource_URL) {
		return std::filesystem::absolute(this->m_Configer.Get_Root_Directory() / Resource_URL);
	}

}// namespace NameSpace_Resource::NameSpace_Manage