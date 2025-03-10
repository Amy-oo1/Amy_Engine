#pragma once

#include<string>
#include<vector>

#include "meta/reflection/Reflection_Macro.h"

#include "file/File_System.h"
#include "common/Level.h"

namespace NameSpace_Resource::NameSpace_Common {

	using std::string;
	using std::vector;

	using NameSpace_Platform::NameSpace_File::path;

	REFLECTION_HEADER(World);
	REFLECTION_CLASS(World, All) final
	{
		REFLECTION_BODY(World);
	public:
		World(void) = default;

		~World(void) = default;

	private:
		string m_Name;

		//NOTE : Default Level URL which should be first loading level
		path m_Default_Level_URL;
		vector<path> m_Levels_URL;

	};

}// namespace NameSpace_Resource::NameSpace_Common