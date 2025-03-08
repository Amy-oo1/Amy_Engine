#include "language_type/Field.h"

#include "language_type/Language_Type_Config.h"
#include "language_type/Language_Utils.h"
#include "language_type/Class.h"

namespace NameSpace_Meta_Parser::NameSpace_Language_Type {

	using namespace  NameSpace_Language_Type_Utils;

	Field::Field(const Cursor& Temp_Cursor, const vector<string>& Current_NameSpace, shared_ptr<Class> Parent) :
		Type_Info{ Temp_Cursor,Current_NameSpace },
		m_Parent{ Parent },
		m_Field_Spelling{ this->Type_Info::Get_Cursor_Spelling() },
		m_Field_Type{ Temp_Cursor.Get_Type().Get_Type_Spelling() },
		m_Field_Display_Name{ Cut_Angle_brackets(Display_Name_Cut_FirstM(this->Type_Info::Get_Display_Name())) },
		m_Is_Const{ Temp_Cursor.Get_Type().Is_Const() } {

	}

	const string& Field::Get_Field_Spelling(void) const {
		return this->m_Field_Spelling;
	}

	const string& Field::Get_Field_Type_Spelling(void) const {
		return this->m_Field_Type;
	}

	const string& Field::Get_Field_Display_Name(void) const {
		return this->m_Field_Display_Name;
	}

	const bool Field::Is_Count(void) const {
		return this->m_Is_Const;
	}

	const bool Field::Should_Compile(void) const {
		return Is_Accessable();
	}

	const bool Field::Is_Accessable(void) const {
		return
			m_Parent->Get_Meta_Data().Get_Flag(NameSpace_Language_Type_Config::Property_Fields) ||
			m_Parent->Get_Meta_Data().Get_Flag(NameSpace_Language_Type_Config::Property_All) ||
			m_Parent->Get_Meta_Data().Get_Flag(NameSpace_Language_Type_Config::Property_Fileds_CPPVector);
	}

}// namespace NameSpace_Meta_Parser::NameSpace_Language_Type