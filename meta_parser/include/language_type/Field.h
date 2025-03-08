#pragma once

#include<string>
#include<memory>

#include "cursor/Cursor.h"
#include "language_type/Type_Info.h"

namespace NameSpace_Meta_Parser::NameSpace_Language_Type {

	using std::string;
	using std::shared_ptr;

	using NameSpace_Cursor::Cursor;

	class Class;

	class Field final :public Type_Info {
	private:
		Field(void) = delete;

	public:
		Field(const Field&) = default;
		Field(Field&&) = default;

		Field& operator=(const Field&) = default;
		Field& operator=(Field&&) = default;

		Field(const Cursor& Temp_Cursor, const vector<string>& Current_NameSpace, shared_ptr<Class> Parent);

		~Field(void) = default;

	public:
		const string& Get_Field_Spelling(void)const;
		const string& Get_Field_Type_Spelling(void)const;
		const string& Get_Field_Display_Name(void)const;

		const bool Is_Count(void)const;

		const bool Should_Compile(void)const;

	private:
		const bool Is_Accessable(void)const;

	public:
		shared_ptr<Class> m_Parent{ nullptr };

		string m_Field_Spelling{};
		string m_Field_Type{};
		string m_Field_Display_Name{};

		bool m_Is_Const{};

	};

}// namespace NameSpace_Meta_Parser::NameSpace_Language_Type