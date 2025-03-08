#include "generator/Generator_Reflection.h"

#include "cursor/Cursor.h"
#include "template_manager/Template_Manager.h"

#include "generator/Generator_Config.h"
#include "generator/Generator_Utils.h"

namespace NameSpace_Meta_Parser::NameSpace_Generator {

	using NameSpace_Template_Manager::Template_Manager;

	Generator_Reflection::Generator_Reflection(const path& Generated_Directory) :
		Generator_Interface{},
		m_Generated_Directory{ Generated_Directory } {
	}

	void Generator_Reflection::Generate(const path& Src_File_path, const path& Template_File_Path, const vector<shared_ptr<Class>>& Moudle_Classes) {
		this->m_Generatored_Files.emplace_back(Src_File_path);

		mustache::data Include_File_Define_List{ mustache::data::type::list };
		Include_File_Define_List.push_back(mustache::data{ NameSpace_Generator_Config::Parameter_Src_File_Path, Src_File_path.generic_string() });

		mustache::data Class_NameSpace_Define_List{ mustache::data::type::list };
		mustache::data Class_Define_List{ mustache::data::type::list };

		for (auto Temp_Class : Moudle_Classes)
			if (Temp_Class->Should_Compile())
				Class_Define_List.push_back(this->Generator_Interface::Generate_Class_RenderData(Temp_Class));

		mustache::data MustacheData(mustache::data::type::object);
		MustacheData.set(NameSpace_Generator_Config::Parameter_Include_Define_List, Include_File_Define_List);
		MustacheData.set(NameSpace_Generator_Config::Parameter_Class_Define_List, Class_Define_List);

		NameSpace_Generator_Utils::Save_File(Template_Manager::Get_Instance().Render_Template(Template_File_Path, MustacheData), this->Process_Dst_File_Path(Src_File_path));
	}

	const path Generator_Reflection::Process_Dst_File_Path(const path& Src_File_Path) {
		return this->m_Generated_Directory / "reflection" / Src_File_Path.filename().replace_extension("Generated_Reflection.h");
	}
	
}// namespace NameSpace_Meta_Parser::NameSpace_Generator