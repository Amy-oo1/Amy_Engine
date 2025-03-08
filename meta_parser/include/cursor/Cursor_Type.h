#pragma once

#include<string>

#include "clang-c/Index.h"

namespace NameSpace_Meta_Parser::NameSpace_Cursor {

	using std::string;

	class Cursor_Type  final {
	private:
		Cursor_Type(void) = delete;

	public:
		Cursor_Type(const Cursor_Type&) = default;
		Cursor_Type(Cursor_Type&&) = default;

		Cursor_Type& operator=(const Cursor_Type&) = default;
		Cursor_Type& operator=(Cursor_Type&&) = default;

		explicit Cursor_Type(const CXType& CXType);
		explicit Cursor_Type(CXType&& CXType);

		~Cursor_Type(void) = default;

	public:
		const string Get_Type_Spelling(void)const;

		int Get_Argument_Num(void)const;

		const Cursor_Type Get_Argument(unsigned Index) const;

		const Cursor_Type Get_Type_Caninocal(void)const;

		const CXCursor Get_Type_Declaration(void)const;

		const CXTypeKind Get_Type_Kind(void)const;

		bool Is_Const(void)const;

	private:
		CXType m_Handle{};

	};

}// namespace NameSpace_Meta_Parser::NameSpace_Cursor