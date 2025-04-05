#pragma once

#include "file/File_System.h"

namespace NameSpace_Resource::NameSpace_Config {

	using NameSpace_Platform::NameSpace_File::path;

	class Resource_Configer final {
	private:
		Resource_Configer(void) = delete;

		Resource_Configer(const Resource_Configer&) = delete;
		Resource_Configer(Resource_Configer&&) = delete;

		Resource_Configer& operator=(const Resource_Configer&) = delete;
		Resource_Configer& operator=(Resource_Configer&&) = delete;

		Resource_Configer(const path& Confige_file);

	public:
		~Resource_Configer(void) = default;

	public:
		const path Get_Root_Directory(void) const;
		const path Get_Engine_Resource_Directory(void) const;
		const path Get_User_Resource_Directory(void) const;

		const path Get_Global_Particle_Resource_URL(void)const;
		const path Get_Global_Render_Resource_URL(void)const;

		const path Get_Engine_Big_Icon_URL(void) const;
		const path Get_Engine_Small_Icon_URL(void) const;
		const path Get_Editor_Font_URL(void) const;

		const path Get_Default_World_Resource_URL(void)const;

		const path Get_Default_Base_Color_Image_URL(void) const;
		const path Get_Default_Metallic_Roughness_Image_URL(void) const;
		const path Get_Default_Normal_Image_URL(void) const;
		const path Get_Default_Occlusion_Image_URL(void) const;
		const path Get_Default_Emissive_Image_URL(void) const;

	public:
		static Resource_Configer& Get_Instance(void);

	public:
		static inline path s_Config_File_Name{ "Amy_Engine_Config.ini" };//TODO : Set Default Path

	private:
		path m_Root_Directory{};
		path m_Engine_Resource_Directory{};
		path m_User_Resource_Directory{};

		path m_Engine_Big_Icon_URL{};
		path m_Engine_Small_Icon_URL{};

		path m_Editor_Font_URL;

		path m_Global_Render_Resource_URL{};
		path m_Global_Particle_Resource_URL{};

		path m_Default_World_Resource_URL{};

		path m_Default_Base_Color_Image_URL{};
		path m_Default_Metallic_Roughness_Image_URL{};
		path m_Default_Normal_Image_URL{};
		path m_Default_Occlusion_Image_URL{};
		path m_Default_Emissive_Image_URL{};

	};

}// namespace NameSpace_Resource::NameSpace_Config