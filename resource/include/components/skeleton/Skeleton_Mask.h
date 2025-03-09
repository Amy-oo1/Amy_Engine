#pragma once

#include<string>
#include<vector>
#include<cstddef>

#include "meta/reflection/Reflection_Macro.h"

#include "file/File_System.h"

namespace NameSpace_Resource::NameSpace_Components {

	using std::vector;
	using std::string;

	using NameSpace_Platform::NameSpace_File::path;

	REFLECTION_HEADER(Skeleton_Mask);
	REFLECTION_CLASS(Skeleton_Mask, All) final
	{
		REFLECTION_BODY(Skeleton_Mask);
	public:
		Skeleton_Mask(void) = default;

		~Skeleton_Mask(void) = default;

	private:
		path m_Skeleton_File_Path{};
		vector<size_t> enabled{};

	};

}// namespace NameSpace_Resource::NameSpace_Components