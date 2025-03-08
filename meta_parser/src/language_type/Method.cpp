#include "language_type/Method.h"

#include "language_type/Language_Type_Config.h"
#include "language_type/Language_Utils.h"
#include "language_type/Class.h"

namespace NameSpace_Meta_Parser::NameSpace_Language_Type {

	Method::Method(const Cursor& Cursor, const vector<string>& Current_NameSpace, shared_ptr<Class> Parent) :
		Type_Info{ Cursor,Current_NameSpace },
		m_Parent{ Parent },
		m_Method_Spelling{ this->Type_Info::Get_Cursor_Spelling() },
		m_Method_Display_Name{ this->Type_Info::Get_Display_Name() } {
	}

	const string& Method::Get_Method_Spelling(void) const {
		return this->m_Method_Spelling;
	}

	const string& Method::Get_Method_Display_Name(void) const {
		return this->m_Method_Display_Name;
	}

	bool Method::Should_Compile(void) const {
		return this->Is_Accessible();
	}

	bool Method::Is_Accessible(void) const {
		return
			m_Parent->Get_Meta_Data().Get_Flag(NameSpace_Language_Type_Config::Property_Methods) ||
			m_Parent->Get_Meta_Data().Get_Flag(NameSpace_Language_Type_Config::Property_All);
	}

}// namespace NameSpace_Meta_Parser::NameSpace_Language_Type