#pragma once

#include "meta/reflection/Reflection_Macro.h"

#include "file/File_System.h"

namespace NameSpace_Resource::NameSpace_Components {

	using NameSpace_Platform::NameSpace_File::path;

	REFLECTION_HEADER(Material);
	REFLECTION_CLASS(Material, All)
	{
		REFLECTION_BODY(Material);
	public:
		Material(void) = default;

		~Material(void) = default;

	private: 
		path m_Base_Colour_Texture_File_Path{};
		path m_Metallic_Roughness_Texture_File_Path{};
		path m_Normal_Texture_File_Path;
		path m_Occlusion_Texture_File_Path;
		path m_Emissive_Texture_File_Path;

	};

}// namespace NameSpace_Resource::NameSpace_Components