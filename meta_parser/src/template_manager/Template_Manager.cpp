#include "template_manager/Template_Manager.h"

#include "template_manager/Template_Manager_Utils.h"

namespace NameSpace_Meta_Parser::NameSpace_Template_Manager {

	Template_Manager& Template_Manager::Get_Instance() {
		static Template_Manager Manager{};
		return Manager;
	}

	const string Template_Manager::Render_Template(const path& Template_File_Path, const mustache::data& Template_Mustache_Data) {
		if (this->m_Template_Pool.find(Template_File_Path) == this->m_Template_Pool.end())
			this->m_Template_Pool.insert_or_assign(Template_File_Path, mustache::mustache{ NameSpace_Template_Manager_Utils::Load_File(Template_File_Path) });

		return  this->m_Template_Pool[Template_File_Path].render(Template_Mustache_Data);
	}

	const unordered_map<path, mustache::mustache>& Template_Manager::Get_Template_Pool(void) const {
		return this->m_Template_Pool;
	}

}// namespace NameSpace_Meta_Parser::NameSpace_Template_Manager