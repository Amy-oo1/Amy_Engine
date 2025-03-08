#pragma once

#include<string>
#include<vector>
#include<filesystem>

#include "cursor/Cursor.h"
#include "meta/Meta_Info.h"

namespace NameSpace_Meta_Parser::NameSpace_Language_Type {

	using std::string;
	using std::vector;
	using std::filesystem::path;

	using NameSpace_Cursor::Cursor;
	using NameSpace_Meta::Meta_Info;

	class Type_Info {
	private:
		Type_Info(void) = delete;

	public:
		Type_Info(const Type_Info&) = default;
		Type_Info(Type_Info&&) = default;

		Type_Info& operator=(const Type_Info&) = default;
		Type_Info& operator=(Type_Info&&) = default;

		Type_Info(const Cursor& Temp_Cursor, const vector<string>& Current_NameSpace);

		virtual ~Type_Info(void) = default;

	public:
		const path& Get_Source_File_Path(void)const;

		const vector<string>& Get_Current_NameSpace(void)const;

		const Meta_Info& Get_Meta_Data(void)const;

	protected:
		const Cursor& Get_Cursor(void)const;

		const string& Get_Cursor_Spelling(void)const;

		const string& Get_Type_Spelling(void)const;

		const string& Get_Display_Name(void)const;

	private:
		Cursor m_Root_Cursor;

		Meta_Info m_Meta_Data;

		path m_File_Path{};

		vector<string> m_NameSpace{};

		string m_Cursor_Spelling{};
		string m_Type_Spelling{};
		string m_Display_Name{};

	};

}// namespace NameSpace_Meta_Parser::NameSpace_Language_Type

