#pragma once

#include<vector>
#include<filesystem>

#include "cursor/Cursor.h"

namespace NameSpace_Meta_Parser::NameSpace_Cursor {

	using std::vector;
	using std::filesystem::path;

	using NameSpace_Cursor::Cursor;

	class TranslationUnit_Cursor final {
	private:
		TranslationUnit_Cursor(void) = delete;

		TranslationUnit_Cursor(const TranslationUnit_Cursor&) = delete;
		TranslationUnit_Cursor(TranslationUnit_Cursor&&) = delete;

		TranslationUnit_Cursor& operator=(const TranslationUnit_Cursor&) = delete;
		TranslationUnit_Cursor& operator=(TranslationUnit_Cursor&&) = delete;

	public:
		TranslationUnit_Cursor(const path& Source_File_Path, const vector<const char*>& clang_Command_Arguments);

		~TranslationUnit_Cursor(void);

	public:
		const Cursor& Get_Cursor(void)const;

	private:
		CXIndex m_Index{};
		CXTranslationUnit m_TranslationUnit{};

		Cursor m_Cursor;

	};

}// namespace NameSpace_Meta_Parser::NameSpace_Cursor 