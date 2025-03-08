#include "generator/Generator_Serializer.h"

#include "template_manager/Template_Manager.h"

#include "generator/Generator_Config.h"

namespace NameSpace_Meta_Parser::NameSpace_Generator {

	Generator_Serializer::Generator_Serializer(const path& Generated_Directory)
		:m_Generated_Directory{ Generated_Directory } {
	}

	void Generator_Serializer::Generate(const path& Src_File_path, const path& Template_File_Path, const vector<shared_ptr<Class>>& Moudle_Classes) {

	}

	const path Generator_Serializer::Process_Dst_File_Path(const path& Src_File_Path) {
		return this->m_Generated_Directory / "erializer" / Src_File_Path.filename().replace_extension("Generated_Serializer.h");
	}

}// namespace NameSpace_Meta_Parser::NameSpace_Generator