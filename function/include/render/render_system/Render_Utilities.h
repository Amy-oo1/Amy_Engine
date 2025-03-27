#pragma once

#include "math/Matrix4x4.h"

//TODO : Dependency
#include "render/render_system/Render_Camera.h"
#include "render/render_system/Render_Scene.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System::NameSpace_Utilities {

	using NameSpace_Core::NameSpace_Math::Matrix4x4;

	const Matrix4x4 Calculate_Direction_Light_View_Matrix(
		const Render_Scene& Scene,
		const Render_Camera& Camera);

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System::NameSpace_Utilities