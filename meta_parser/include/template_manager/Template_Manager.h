#pragma once

#include<filesystem>
#include<unordered_map>
#include<string>

#include "mustache.hpp"

namespace NameSpace_Meta_Parser::NameSpace_Template_Manager {

	using std::filesystem::path;
	using std::string;
	using std::unordered_map;

	class Template_Manager final {
	private:
		Template_Manager(void) = default;

		Template_Manager(const Template_Manager&) = delete;
		Template_Manager(Template_Manager&&) = delete;

		Template_Manager& operator=(const Template_Manager&) = delete;
		Template_Manager& operator=(Template_Manager&&) = delete;

	public:
		~Template_Manager(void) = default;

	public:
		const string Render_Template(const path& Template_File_Path, const mustache::data& Template_Mustache_Data);

		const unordered_map<path, mustache::mustache>& Get_Template_Pool(void)const;

	public:
		static Template_Manager& Get_Instance();

	private:
		unordered_map<path, mustache::mustache> m_Template_Pool;

	};
}// namespace NameSpace_Meta_Parser::NameSpace_Template_Manager