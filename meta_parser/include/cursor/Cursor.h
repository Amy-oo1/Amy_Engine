#pragma once

#include<string>
#include<vector>
#include<filesystem>

#include "clang-c/Index.h"

#include "cursor/Cursor_Type.h"

namespace NameSpace_Meta_Parser::NameSpace_Cursor {

	using std::string;
	using std::vector;
	using std::filesystem::path;

	using NameSpace_Cursor::Cursor_Type;

	class Cursor final {
	public:
		enum class Cursor_Kind {
			CURSOR_CXXBASESPECIFIER = CXCursor_CXXBaseSpecifier,
			CURSOR_FIELDDECL = CXCursor_FieldDecl,
			CURSOR_CXXMETHOD = CXCursor_CXXMethod,
			CURSOR_NAMESPACE = CXCursor_Namespace,
			CURSOR_CLASSDECL = CXCursor_ClassDecl,
			CURSOR_STRUCTDECL = CXCursor_StructDecl,
			CURSOR_ANNOTATEATTR = CXCursor_AnnotateAttr,
			CURSOR_OTHERS
		};

	private:
		Cursor(void) = delete;

	public:
		Cursor(const Cursor&) = default;
		Cursor(Cursor&&) = default;

		Cursor& operator=(const Cursor&) = default;
		Cursor& operator=(Cursor&&) = default;

		explicit Cursor(const CXCursor& Temp_CXCursor);
		explicit Cursor(CXCursor&& Temp_CXCursor);

		~Cursor(void) = default;

	public:
		const Cursor_Kind Get_Cursor_Kind(void)const;

		const string Get_Cursor_Spelling(void)const;

		const string Get_Display_Name(void)const;

		const path Get_File_path(void)const;

		bool Is_Definition(void)const;

		const Cursor_Type Get_Type(void)const;

		const vector<Cursor> Get_Children(void)const;

	private:
		static const Cursor_Kind CXCursotKind_To_Cursor_Kind(const CXCursorKind& Temp_CXCursorKind);

	private:
		CXCursor m_Handle;

	};

}// namespace NameSpace_Meta_Parser::NameSpace_Cursor