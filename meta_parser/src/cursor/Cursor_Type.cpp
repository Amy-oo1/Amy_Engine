#include "cursor/Cursor_Type.h"

#include "cursor/Cursor_Utils.h"

namespace NameSpace_Meta_Parser::NameSpace_Cursor {

	Cursor_Type::Cursor_Type(const CXType& CXType)
		:m_Handle{ CXType } {
	}

	Cursor_Type::Cursor_Type(CXType&& CXType) :
		m_Handle{ CXType } {
	}

	const string Cursor_Type::Get_Type_Spelling(void) const {
		return NameSpace_Utils::CXString_To_String(clang_getTypeSpelling(this->m_Handle));
	}

	int Cursor_Type::Get_Argument_Num(void) const {
		return clang_getNumArgTypes(this->m_Handle);
	}

	const Cursor_Type Cursor_Type::Get_Argument(unsigned Index) const {
		return Cursor_Type{ clang_getArgType(m_Handle, Index) };
	}

	const Cursor_Type Cursor_Type::Get_Type_Caninocal(void) const {
		return Cursor_Type{ clang_getCanonicalType(this->m_Handle) };
	}

	const CXCursor Cursor_Type::Get_Type_Declaration(void) const {
		return clang_getTypeDeclaration(this->m_Handle);
	}

	const CXTypeKind Cursor_Type::Get_Type_Kind(void) const {
		return m_Handle.kind;
	}

	bool Cursor_Type::Is_Const(void) const {
		return clang_isConstQualifiedType(this->m_Handle);
	}

}// namespace NameSpace_Meta_Parser::NameSpace_Cursor