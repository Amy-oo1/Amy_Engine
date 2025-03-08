#include "cursor/Cursor.h"

#include "cursor/Cursor_Utils.h"

namespace NameSpace_Meta_Parser::NameSpace_Cursor {

	Cursor::Cursor(const CXCursor& Temp_CXCursor) :
		m_Handle{ Temp_CXCursor } {
	}

	Cursor::Cursor(CXCursor&& Temp_CXCursor) :
		m_Handle{ Temp_CXCursor } {
	}

	const Cursor::Cursor_Kind Cursor::Get_Cursor_Kind(void) const {
		return Cursor::CXCursotKind_To_Cursor_Kind(clang_getCursorKind(this->m_Handle));
	}

	const string Cursor::Get_Cursor_Spelling(void) const {
		return NameSpace_Utils::CXString_To_String(clang_getCursorSpelling(this->m_Handle));
	}

	const string Cursor::Get_Display_Name(void) const {
		return NameSpace_Utils::CXString_To_String(clang_getCursorDisplayName(this->m_Handle));
	}

	const path Cursor::Get_File_path(void) const {
		CXSourceLocation Location_Start = clang_getRangeStart(clang_Cursor_getSpellingNameRange(this->m_Handle, 0, 0));

		CXFile File{ nullptr };
		clang_getFileLocation(Location_Start, &File, nullptr, nullptr, nullptr);

		return path{ NameSpace_Utils::CXString_To_String(clang_getFileName(File)),path::generic_format };
	}

	bool Cursor::Is_Definition(void) const {
		return clang_isCursorDefinition(this->m_Handle);
	}

	const Cursor_Type Cursor::Get_Type(void) const {
		return Cursor_Type{ clang_getCursorType(this->m_Handle) };
	}

	const vector<Cursor> Cursor::Get_Children(void) const {

		static auto Visistor = [](CXCursor CurrentCXCursor, CXCursor ParentCursor, CXClientData ClientData)->CXChildVisitResult {
			auto List = reinterpret_cast<vector<Cursor>*>(ClientData);

			List->emplace_back(Cursor{ CurrentCXCursor });

			return CXChildVisit_Continue;
			};

		vector<Cursor> Children{};
		clang_visitChildren(this->m_Handle, Visistor, &Children);

		return Children;
	}

	const Cursor::Cursor_Kind Cursor::CXCursotKind_To_Cursor_Kind(const CXCursorKind& Temp_CXCursorKind) {
		switch (Temp_CXCursorKind) {
		case CXCursor_CXXBaseSpecifier:return Cursor::Cursor_Kind::CURSOR_CXXBASESPECIFIER;
		case CXCursor_FieldDecl:return Cursor::Cursor_Kind::CURSOR_FIELDDECL;
		case CXCursor_CXXMethod:return Cursor::Cursor_Kind::CURSOR_CXXMETHOD;
		case CXCursor_AnnotateAttr:return Cursor::Cursor_Kind::CURSOR_ANNOTATEATTR;
		case CXCursor_Namespace:return Cursor::Cursor_Kind::CURSOR_NAMESPACE;
		case CXCursor_ClassDecl:return Cursor::Cursor_Kind::CURSOR_CLASSDECL;
		case CXCursor_StructDecl:return Cursor::Cursor_Kind::CURSOR_STRUCTDECL;
		default:
			return Cursor::Cursor_Kind::CURSOR_OTHERS;
		}
	}

}// namespace NameSpace_Meta_Parser::NameSpace_Cursor