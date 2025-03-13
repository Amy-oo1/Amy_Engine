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

	REFLECTION_HEADER(Bone_Blend_Mask);
	REFLECTION_CLASS(Bone_Blend_Mask, All) final
	{
		REFLECTION_BODY(Bone_Blend_Mask);
	public:
		Bone_Blend_Mask(void) = default;

		~Bone_Blend_Mask(void) = default;

	private:
		path m_Skeleton_Data_URL{};
		vector<size_t> Enabled{};

	};

}// namespace NameSpace_Resource::NameSpace_Components