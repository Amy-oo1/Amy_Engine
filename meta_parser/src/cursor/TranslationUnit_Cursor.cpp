#include "cursor/TranslationUnit_Cursor.h"

#include<cassert>

namespace NameSpace_Meta_Parser::NameSpace_Cursor {

	TranslationUnit_Cursor::TranslationUnit_Cursor(const path& Source_File_Path, const vector<const char*>& clang_Command_Arguments) :
		m_Index{ clang_createIndex(true,true) },
		m_TranslationUnit{ clang_createTranslationUnitFromSourceFile(this->m_Index, Source_File_Path.string().c_str(), static_cast<int>(clang_Command_Arguments.size()), clang_Command_Arguments.data(), 0, nullptr) },
		m_Cursor{ clang_getTranslationUnitCursor(this->m_TranslationUnit) } {

		assert(this->m_TranslationUnit != nullptr);
	}

	TranslationUnit_Cursor::~TranslationUnit_Cursor(void) {
		clang_disposeTranslationUnit(this->m_TranslationUnit);
		clang_disposeIndex(this->m_Index);
	}

	const Cursor& TranslationUnit_Cursor::Get_Cursor(void) const {
		return this->m_Cursor;
	}

}// namespace NameSpace_Meta_Parser::NameSpace_Cursor