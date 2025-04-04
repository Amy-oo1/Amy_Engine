#pragma once

#include "render/render_system/Render_Data_Struct.h"
#include "render/render_system/Render_Entity.h"


namespace NameSpace_Editor {

	using NameSpace_Function::NameSpace_Render::NameSpace_Render_System::Render_Entity;
	using NameSpace_Function::NameSpace_Render::NameSpace_Render_System::Render_Mesh_Data;

	struct Editor_Translation_Axis final :public Render_Entity {
		Editor_Translation_Axis(void);
		Render_Mesh_Data Mesh_Data;
	};

	struct Editor_Scale_Axis final :public Render_Entity {
		Editor_Scale_Axis(void);
		Render_Mesh_Data Mesh_Data;
	};

	struct Editor_Rotation_Axis final :public Render_Entity {
		Editor_Rotation_Axis(void);
		Render_Mesh_Data Mesh_Data;
	};


}// namespace NameSpace_Editor