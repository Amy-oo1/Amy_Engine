#pragma once

#include<utility>
#include<string>
#include<vector>
#include<unordered_map>

#include "cursor/Cursor.h"

namespace NameSpace_Meta_Parser::NameSpace_Meta {

	using std::pair;
	using std::string;
	using std::vector;

	using NameSpace_Cursor::Cursor;

	class Meta_Info final {
	private:
		Meta_Info(void) = delete;

	public:
		Meta_Info(const Meta_Info&) = default;
		Meta_Info(Meta_Info&&) = default;

		Meta_Info& operator=(const Meta_Info&) = default;
		Meta_Info& operator=(Meta_Info&&) = default;

		explicit Meta_Info(const Cursor& Temp_Cusror);

		~Meta_Info(void) = default;

	public:
		const string Get_Property(const string& Key)const;

		 bool Get_Flag(const string& Key)const;

	private:
		static const vector<pair<string, string>> Extract_Properties(const Cursor& Temp_Cursor);

	private:
		std::unordered_map<string, string> m_Properties{};

	};

}// namespace NameSpace_Meta_Parser::NameSpace_Meta