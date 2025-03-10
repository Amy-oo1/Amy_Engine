#pragma once

#include "meta/reflection/Reflection_Macro.h"

#include "file/File_System.h"
#include "math/Vector3.h"

namespace NameSpace_Resource::NameSpace_Global {

	using NameSpace_Core::NameSpace_Math::Vector3;
	using NameSpace_Platform::NameSpace_File::path;

	REFLECTION_HEADER(Global_Particle);
	REFLECTION_CLASS(Global_Particle, All) final
	{
		REFLECTION_BODY(Global_Particle);
	public:
		Global_Particle(void) = default;

		~Global_Particle(void) = default;

	private:
		int  m_Emit_Gap;
		int m_Emit_Count;
		int m_Time_Step;
		float m_Max_Life;

		Vector3 m_Gravity{ 0.0f, -9.8f, 0.0f };

		path m_Particle_Billboard_Texture_File_Path;
		path m_Piccolo_Logo_Texture_File_Path;

	};

}// namespace NameSpace_Resource::NameSpace_Global