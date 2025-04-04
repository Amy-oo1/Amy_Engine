#pragma once

#include<memory>

#include "render/rhi/empty_rhi/Empty_RHI.h"
#include "render/render_system/Render_Resource_Base.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass {

	using std::shared_ptr;

	using NameSpace_RHI::Empty_RHI;
	using NameSpace_Render_System::Render_Resource_Base;

	struct Render_Pass_Command_Info final {
		shared_ptr<Empty_RHI> RHI;
		shared_ptr<Render_Resource_Base> Resource;
	};

	struct Render_Pass_Pre_Initialize_Info {};
	struct Render_Pass_Post_Initialize_Info {};

	class Render_Pass_Base {
	private:
		Render_Pass_Base(const Render_Pass_Base&) = delete;

		Render_Pass_Base& operator=(const Render_Pass_Base&) = delete;


	public:
		Render_Pass_Base(const Render_Pass_Command_Info& Command_Info);

		virtual ~Render_Pass_Base(void) = default;

	public:
		//TODO
	public:
		shared_ptr<Empty_RHI> m_RHI;
		shared_ptr<Render_Resource_Base> m_Resource;

		virtual void Pre_Inittialize(shared_ptr<Render_Pass_Pre_Initialize_Info> Init_Info) = 0;
		virtual void Post_Inittialize(shared_ptr<Render_Pass_Post_Initialize_Info> Init_Info) = 0;
		virtual void PrePare_Pass_Data(shared_ptr<Render_Resource_Base> Resource) = 0;
		virtual void Draw(void) = 0;

	};

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass