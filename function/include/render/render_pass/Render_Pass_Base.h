#pragma once

#include<memory>

#include "render/rhi/empty_rhi/Empty_RHI.h"

#include "render/render_system/Render_Camera.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass {

	using std::shared_ptr;

	using NameSpace_RHI::Empty_RHI;

	class Render_Pass_Base {
	private:
		Render_Pass_Base(const Render_Pass_Base&) = delete;
		Render_Pass_Base& operator=(const Render_Pass_Base&) = delete;

	public:
		Render_Pass_Base(void) = default;
		virtual ~Render_Pass_Base(void) = default;

	public:

		/*virtual void 
			UpLoad_Globa_Render_Resource(
			shared_ptr<Empty_RHI> RHI,
				)*/


	};

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass