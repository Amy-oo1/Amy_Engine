#pragma once

#include<vector>
#include<memory>

#include "math/Vector2.h"

#include "render/rhi/empty_rhi/Empty_RHI.h"
#include "render/render_system/Render_Resource.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System {

	class Render_System;

	using std::unique_ptr;
	using std::shared_ptr;

	using NameSpace_RHI::Empty_RHI;

	struct Render_Pipeline_Info final {
		shared_ptr<Empty_RHI> RHI{ nullptr };
		shared_ptr<Render_Resource_Base> Resource{ nullptr };

	};

	struct Render_Passes_Info final {
		bool Enable_FXAA{ false };
	};

	class Render_Pipeline_Base {
		friend class Render_System;
	private:
		Render_Pipeline_Base(const Render_Pipeline_Base&) = delete;
		Render_Pipeline_Base& operator=(const Render_Pipeline_Base&) = delete;

	public:
		Render_Pipeline_Base(const Render_Pipeline_Info& Pipeline_Info);

		virtual ~Render_Pipeline_Base(void) = default;

	public:
		virtual void Build_Render_Passes(const Render_Passes_Info& Passes_Info) = 0;

		virtual void Prepare_Pass_Data(shared_ptr<Render_Resource_Base> Render_Resource);

		virtual void Forwad_Render(shared_ptr<Empty_RHI> RHI, shared_ptr<Render_Resource_Base> Render_Resource);

		virtual void Deferred_Render(shared_ptr<Empty_RHI> RHI, shared_ptr<Render_Resource_Base> Render_Resource);

	protected:
		shared_ptr<Empty_RHI> m_RHI{ nullptr };

		shared_ptr<Render_Resource_Base> m_Render_Resource{ nullptr };
	};

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System