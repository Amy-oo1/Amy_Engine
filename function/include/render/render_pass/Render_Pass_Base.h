#pragma once

#include<memory>

#include "render/rhi/empty_rhi/Empty_RHI.h"
#include "render/render_system/Render_Data_Struct.h"

#include "render/render_system/Render_Camera.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass {

	using std::shared_ptr;

	using NameSpace_RHI::Empty_RHI;
	using NameSpace_Render_System::Render_Mesh_Data;
	using NameSpace_Render_System::Render_Material_Data;


	struct Render_Pass_Command_Info final{
		shared_ptr<Empty_RHI> RHI;
	};

	class Render_Pass_Base {
	private:
		Render_Pass_Base(const Render_Pass_Base&) = delete;
		Render_Pass_Base& operator=(const Render_Pass_Base&) = delete;

	public:
		Render_Pass_Base(void) = default;
		virtual ~Render_Pass_Base(void) = default;

	public:




	};

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass