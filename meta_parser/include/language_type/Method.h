#pragma once
#pragma once

#include<string>
#include<vector>
#include<memory>

#include "language_type/Type_Info.h"
#include "cursor/Cursor.h"

namespace NameSpace_Meta_Parser::NameSpace_Language_Type {

	using std::string;
	using std::vector;
	using std::shared_ptr;

	using NameSpace_Cursor::Cursor;

	class Class;

	class Method final :public Type_Info {
	private:
		Method(void) = delete;

	public:
		Method(const Method&) = default;
		Method(Method&&) = default;

		Method& operator=(const Method&) = default;
		Method& operator=(Method&&) = default;

		Method(const Cursor& Temp_Cursor, const vector<string>& Current_NameSpace, shared_ptr<Class> Parent);

		~Method(void) = default;

	public:
		const string& Get_Method_Spelling(void)const;
		const string& Get_Method_Display_Name(void)const;

		bool Should_Compile(void)const;

	private:
		bool Is_Accessible(void)const;

	private:
		shared_ptr<Class> m_Parent{ nullptr };

		string m_Method_Spelling{};
		string m_Method_Display_Name{};

	};

}// namespace NameSpace_Meta_Parser::NameSpace_Language_Type