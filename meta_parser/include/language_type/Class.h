#pragma once

#include<string>
#include<vector>
#include<memory>
#include<utility>

#include "cursor/Cursor.h"

#include "language_type/Type_Info.h"
#include "language_type/Field.h"
#include "language_type/Method.h"

namespace NameSpace_Meta_Parser::NameSpace_Language_Type {

	using std::string;
	using std::vector;
	using std::shared_ptr;

	using NameSpace_Cursor::Cursor;

	class Class final : public std::enable_shared_from_this<Class>, public Type_Info {
	private:
		Class(void) = delete;

	public:
		Class(const Class&) = default;
		Class(Class&&) = default;

		Class& operator=(const Class&) = default;
		Class& operator=(Class&&) = default;

		Class(const Cursor& Temp_Cursor, const vector<string>& Current_Namespace);

		~Class(void) = default;

	public:
		bool Should_Compile_Fields(void)const;

		bool Should_Compile_Methods(void)const;

		bool Should_Compile(void)const;

		const string& Get_Class_Display_Name(void)const;
		const string& Get_Class_Spelling(void)const;

		const string Base_Class_Spelling(void)const;

		const vector<shared_ptr<Field>>& Get_Fields(void)const;
		const vector<shared_ptr<Method>>& Get_Mehtods(void)const;
		const vector<shared_ptr<Class>>& Get_Base_Classes(void)const;

	private:
		void Initialize(const Cursor& Clss_Cursor);

	public:
		static const shared_ptr<Class> Create_Class(const Cursor& Temp_Cursor, const vector<string>& Current_Namespace);

	private:

		string m_Class_Display_Name{};
		string m_Class_Spelling{};

		vector<shared_ptr<Class>> m_Base_Classes{};
		vector<shared_ptr<Field>> m_Fields{};
		vector<shared_ptr<Method>> m_Methods{};

	};

}// namespace NameSpace_Meta_Parser::NameSpace_Language_Type