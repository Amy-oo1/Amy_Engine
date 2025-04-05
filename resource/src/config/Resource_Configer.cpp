#include "config/Resource_Configer.h"

#include<cstdint>
#include<fstream>
#include<sstream>
#include<string>

namespace NameSpace_Resource::NameSpace_Config {

	using NameSpace_Platform::NameSpace_File::File_System;

	Resource_Configer::Resource_Configer(const path& Confige_file_path) {

		std::ifstream Configs{ path(Confige_file_path) };
		std::string Config_Line{};
		while (std::getline(Configs, Config_Line)) {
			size_t Seperate_Pos{ Config_Line.find('=') };
			if (Seperate_Pos == std::string::npos)
				continue;

			std::string Config_Name{ Config_Line.substr(0, Seperate_Pos) };
			std::string Config_Value{ Config_Line.substr(Seperate_Pos + 1) };

			if ("Binary_Root_Directory" == Config_Name)
				File_System::Set_Lexically_Normal(this->m_Root_Directory = Confige_file_path.parent_path() / Config_Value);
			else if ("Engine_Resource_Directory" == Config_Name)
				File_System::Set_Lexically_Normal(this->m_Engine_Resource_Directory = this->m_Root_Directory / Config_Value);
			else if ("User_Resource_Directory" == Config_Name)
				File_System::Set_Lexically_Normal(this->m_User_Resource_Directory = this->m_Root_Directory / Config_Value);
			else if ("Engine_Big_Icon_URL" == Config_Name)
				File_System::Set_Lexically_Normal(this->m_Engine_Big_Icon_URL = Config_Value);
			else if ("Engine_Small_Icon_URL" == Config_Name)
				File_System::Set_Lexically_Normal(this->m_Engine_Small_Icon_URL = Config_Value);
			else if ("Editor_Font_URL" == Config_Name)
				File_System::Set_Lexically_Normal(this->m_Editor_Font_URL = Config_Value);
			else if ("Global_Particle_Resource_URL" == Config_Name)
				File_System::Set_Lexically_Normal(this->m_Global_Particle_Resource_URL = Config_Value);
			else if ("Global_Render_Resource_URL" == Config_Name)
				File_System::Set_Lexically_Normal(this->m_Global_Render_Resource_URL = Config_Value);
		}
	}

	const path Resource_Configer::Get_Root_Directory(void) const {
		return this->m_Root_Directory;
	}

	const path Resource_Configer::Get_Engine_Resource_Directory(void) const {
		return this->m_Engine_Resource_Directory;
	}

	const path Resource_Configer::Get_User_Resource_Directory(void) const {
		return this->m_User_Resource_Directory;
	}

	const path Resource_Configer::Get_Global_Particle_Resource_URL(void) const {
		return this->m_Global_Particle_Resource_URL;
	}

	const path Resource_Configer::Get_Global_Render_Resource_URL(void) const {
		return this->m_Global_Render_Resource_URL;
	}

	const path Resource_Configer::Get_Engine_Big_Icon_URL(void) const {
		return this->m_Engine_Big_Icon_URL;
	}

	const path Resource_Configer::Get_Engine_Small_Icon_URL(void) const {
		return this->m_Engine_Small_Icon_URL;
	}

	const path Resource_Configer::Get_Editor_Font_URL(void) const {
		return this->m_Editor_Font_URL;
	}

	const path Resource_Configer::Get_Default_World_Resource_URL(void) const {
		return this->m_Default_World_Resource_URL;
	}

	const path Resource_Configer::Get_Default_Base_Color_Image_URL(void) const {
		return this->m_Default_Base_Color_Image_URL;
	}

	const path Resource_Configer::Get_Default_Metallic_Roughness_Image_URL(void) const {
		return this->m_Default_Metallic_Roughness_Image_URL;
	}

	const path Resource_Configer::Get_Default_Normal_Image_URL(void) const {
		return this->m_Default_Normal_Image_URL;
	}

	const path Resource_Configer::Get_Default_Occlusion_Image_URL(void) const{
		return this->m_Default_Occlusion_Image_URL;
	}

	const path Resource_Configer::Get_Default_Emissive_Image_URL(void) const{
		return this->m_Default_Emissive_Image_URL;
	}

	Resource_Configer& Resource_Configer::Get_Instance(void) {
		static Resource_Configer Instance{ s_Config_File_Name };//TODO : change this to a config file

		return Instance;
	}

}// namespace NameSpace_Resource::NameSpace_Config