#include "language_type/Class.h"

#include "language_type/Language_Type_Config.h"
#include "language_type/Language_Utils.h"

namespace NameSpace_Meta_Parser::NameSpace_Language_Type {

	Class::Class(const Cursor& Temp_Cursor, const vector<string>& Current_NameSpace) :
		Type_Info{ Temp_Cursor,Current_NameSpace },
		m_Class_Display_Name{ NameSpace_Language_Type_Utils::Cut_Angle_brackets(this->Type_Info::Get_Display_Name()) },
		m_Class_Spelling{ this->Type_Info::Get_Cursor_Spelling() } {
	}

	bool Class::Should_Compile_Fields(void) const {
		return
			this->Get_Meta_Data().Get_Flag(NameSpace_Language_Type_Config::Property_All) ||
			this->Get_Meta_Data().Get_Flag(NameSpace_Language_Type_Config::Property_Fields) ||
			this->Get_Meta_Data().Get_Flag(NameSpace_Language_Type_Config::Property_Fileds_CPPVector);
	}

	bool Class::Should_Compile_Methods(void) const {
		return
			this->Get_Meta_Data().Get_Flag(NameSpace_Language_Type_Config::Property_All) ||
			this->Get_Meta_Data().Get_Flag(NameSpace_Language_Type_Config::Property_Methods);
	}

	bool Class::Should_Compile(void) const {
		return this->Should_Compile_Fields() || this->Should_Compile_Methods();
	}

	const string& Class::Get_Class_Display_Name(void) const {
		return this->m_Class_Display_Name;
	}

	const string& Class::Get_Class_Spelling(void) const {
		return this->m_Class_Spelling;
	}

	const string Class::Base_Class_Spelling(void) const {
		return  this->m_Class_Spelling.substr(this->m_Class_Spelling.find_last_of(':') + 1);
	}

	const vector<shared_ptr<Field>>& Class::Get_Fields(void) const {
		return this->m_Fields;
	}

	const vector<shared_ptr<Method>>& Class::Get_Mehtods(void) const {
		return this->m_Methods;
	}

	const vector<shared_ptr<Class>>& Class::Get_Base_Classes(void) const {
		return this->m_Base_Classes;
	}

	void Class::Initialize(const Cursor& Class_Cursor) {
		for (const auto& Child : Class_Cursor.Get_Children())
			switch (Child.Get_Cursor_Kind()) {
			case Cursor::Cursor_Kind::CURSOR_CXXBASESPECIFIER:
				this->m_Base_Classes.emplace_back(Class::Create_Class(Child, this->Type_Info::Get_Current_NameSpace()));
				break;
			case Cursor::Cursor_Kind::CURSOR_FIELDDECL:
				this->m_Fields.emplace_back(std::make_shared<Field>(Child, this->Type_Info::Get_Current_NameSpace(), this->std::enable_shared_from_this<Class>::shared_from_this()));
				break;
			case Cursor::Cursor_Kind::CURSOR_CXXMETHOD:
				this->m_Methods.emplace_back(std::make_shared<Method>(Child, this->Type_Info::Get_Current_NameSpace(), this->std::enable_shared_from_this<Class>::shared_from_this()));
				break;
			default:
				break;
			}
	}

	const shared_ptr<Class> Class::Create_Class(const Cursor& Class_Cursor, const vector<string>& Current_Namespace) {
		shared_ptr<Class>  Object = std::make_shared<Class>(Class_Cursor, Current_Namespace);
		Object->Initialize(Class_Cursor);
		return Object;
	}

}// namespace NameSpace_Meta_Parser::NameSpace_Language_Type