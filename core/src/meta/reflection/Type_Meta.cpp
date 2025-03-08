#include "meta/Reflection/Type_Meta.h"

namespace NameSpace_Core::NameSpace_Meta::NameSpace_Reflection {

	Type_Meta::Type_Meta(const string& Spelling)
		:m_Spelling{ Spelling } {

		if (Type_Meta::Type_Table.find(Spelling) == Type_Table.end()) {
			Type_Meta Object{};
			
			Object.m_Class_Func_Tuple = Reflection_Register::Get_Instance().m_Class_Map[Spelling];
			Object.m_Base_Class_Tuple = Reflection_Register::Get_Instance().m_Base_Class_Map[Spelling];
			Object.m_Field_Class_Func_Tuple = Reflection_Register::Get_Instance().m_Class_Field_Map[Spelling];
			Object.m_Filed_CPPVector_Func_Tuple = Reflection_Register::Get_Instance().m_Class_Field_CPPVector_Map[Spelling];

			Type_Meta::Type_Table[Spelling] = std::make_shared<Type_Meta>(Object);
		}
	}
	const string Type_Meta::Get_Spelling(void) const{
		return this->m_Spelling;
	}

	std::unordered_map<string, shared_ptr<Type_Meta>> Type_Meta::Type_Table{};

}// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Reflection

