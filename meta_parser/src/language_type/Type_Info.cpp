#include "language_type/Type_Info.h"

#include "language_type/Language_Type_Config.h"
#include "language_type/Language_Utils.h"

namespace NameSpace_Meta_Parser::NameSpace_Language_Type {

	Type_Info::Type_Info(const Cursor& Temp_Cursor, const vector<string>& Current_NameSpace) :
		m_Root_Cursor{ Temp_Cursor },
		m_Meta_Data{ Temp_Cursor },
		m_File_Path{ Temp_Cursor.Get_File_path() },
		m_NameSpace{ Current_NameSpace },
		m_Cursor_Spelling{ Temp_Cursor.Get_Cursor_Spelling() },
		m_Type_Spelling{ Temp_Cursor.Get_Type().Get_Type_Spelling() },
		m_Display_Name{ Temp_Cursor.Get_Display_Name() } {
	}

	const Meta_Info& Type_Info::Get_Meta_Data(void) const {
		return this->m_Meta_Data;
	}

	const path& Type_Info::Get_Source_File_Path(void) const {
		return this->m_File_Path;
	}

	const vector<string>& Type_Info::Get_Current_NameSpace(void) const {
		return this->m_NameSpace;
	}

	const Cursor& Type_Info::Get_Cursor(void) const {
		return this->m_Root_Cursor;
	}

	const string& Type_Info::Get_Cursor_Spelling(void)const {
		return this->m_Cursor_Spelling;
	}

	const string& Type_Info::Get_Type_Spelling(void) const {
		return this->m_Type_Spelling;
	}

	const string& Type_Info::Get_Display_Name(void) const {
		return this->m_Display_Name;
	}

}// namespace NameSpace_Meta_Parser::NameSpace_Language_Type

