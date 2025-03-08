#include "generator/Generator_Interface.h"

#include<string>

#include "generator/Generator_Utils.h"
#include "generator/Generator_Config.h"

namespace NameSpace_Meta_Parser::NameSpace_Generator {

	const mustache::data Generator_Interface::Generate_Class_Field_RenderData(shared_ptr<Class> Current_Class) {
		mustache::data Field_Define{ mustache::data::type::object };

		for (const auto& Temp_Field : Current_Class->Get_Fields())
			if (Temp_Field->Should_Compile()) {

				Field_Define.set(NameSpace_Generator_Config::Parameter_Field_Type_Spelling, Temp_Field->Get_Field_Type_Spelling());
				Field_Define.set(NameSpace_Generator_Config::Parameter_Field_Spelling, Temp_Field->Get_Field_Spelling());
				Field_Define.set(NameSpace_Generator_Config::Parameter_Field_Display_Name, Temp_Field->Get_Field_Display_Name());

				const bool Is_CPPVector = Temp_Field->Get_Field_Type_Spelling().find(NameSpace_Generator_Config::Vector_Prefix) != std::string::npos;

				Field_Define.set(NameSpace_Generator_Config::Parameter_Filed_Is_CPPVector, Is_CPPVector);

				if (Is_CPPVector) {
					mustache::data Field_CPPVector_Define_List{ mustache::data::type::list };
					Field_CPPVector_Define_List.push_back(mustache::data{ NameSpace_Generator_Config::Parameter_Filed_CPPVector_Element_Type_Spelling ,NameSpace_Generator_Utils::Get_CPPVector_Element_Type(Temp_Field->Get_Field_Type_Spelling()) });
					Field_Define.set(NameSpace_Generator_Config::Parameter_Filed_CPPVector_Define_List, Field_CPPVector_Define_List);
				}
			}

		return Field_Define;
	}

	const mustache::data Generator_Interface::Generate_Class_Method_RenderData(shared_ptr<Class> Current_Class) {
		mustache::data Method_define{ mustache::data::type::object };

		for (const auto& Temp_Method : Current_Class->Get_Mehtods())
			if (Temp_Method->Should_Compile()) {
				Method_define.set(NameSpace_Generator_Config::Parameter_Method_Display_Name, Temp_Method->Get_Method_Display_Name());
				Method_define.set(NameSpace_Generator_Config::Parameter_Method_Spelling, Temp_Method->Get_Method_Spelling());
			}

		return Method_define;
	}

	const mustache::data Generator_Interface::Generate_Class_RenderData(shared_ptr<Class> Current_Class) {
		mustache::data Class_Define{ mustache::data::type::object };

		Class_Define.set(NameSpace_Generator_Config::Parameter_Class_NameSpace, NameSpace_Generator_Utils::Connect_String(Current_Class->Type_Info::Get_Current_NameSpace(), std::string{ "::" }));

		Class_Define.set(NameSpace_Generator_Config::Parameter_Class_Display_Name, Current_Class->Get_Class_Display_Name());
		Class_Define.set(NameSpace_Generator_Config::Parameter_Class_Spelling, Current_Class->Get_Class_Spelling());

		Class_Define.set(NameSpace_Generator_Config::Parameter_Class_Has_Base_Class, !Current_Class->Get_Base_Classes().empty());

		mustache::data Class_Base_Class_Defines_List{ mustache::data::type::list };

		mustache::data Base_Class_Name{ mustache::data::type::list };

		for (const auto& Temp_Base_Class : Current_Class->Get_Base_Classes())
			Base_Class_Name.push_back(mustache::data{ NameSpace_Generator_Config::Parameter_Class_Base_Class_Spelling, Temp_Base_Class->Base_Class_Spelling() });

		Class_Base_Class_Defines_List.push_back(mustache::data{ NameSpace_Generator_Config::Parameter_Class_Base_Spelling_List ,Base_Class_Name });

		Class_Define.set(NameSpace_Generator_Config::Parameter_Class_Base_Class_Define_List, Class_Base_Class_Defines_List);
		Class_Define.set(NameSpace_Generator_Config::Parameter_Field_Define_List, Generator_Interface::Generate_Class_Field_RenderData(Current_Class));
		Class_Define.set(NameSpace_Generator_Config::Parameter_Method_Define_List, Generator_Interface::Generate_Class_Method_RenderData(Current_Class));

		return Class_Define;

	}

}// namespace NameSpace_Meta_Parser::NameSpace_Generator