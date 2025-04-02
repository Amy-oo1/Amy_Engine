#pragma once

#include<vector>

#include "render/rhi/empty_rhi/RHI_Type.h"
#include "render/rhi/empty_rhi/RHI_Class.h"
#include "render/render_system/Render_Resource.h"
#include "render/render_pass/Render_Pass.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass {

	using std::vector;

	using NameSpace_RHI::RHI_Render_Pass;
	using NameSpace_RHI::RHI_Image_View;

	struct Tone_Mapping_Render_Pass_Pre_Initialize_Info final :public Render_Pass_Pre_Initialize_Info {
		RHI_Render_Pass* Render_Pass;
		RHI_Image_View* Input_Attachment;
	};

	struct Tone_Mapping_Render_Pass_Post_Initialize_Info final :public Render_Pass_Post_Initialize_Info {
		//NOTE : Empty
	};


	class Tone_Mapping_Pass final :public Render_Pass {
	private:
		Tone_Mapping_Pass(const Tone_Mapping_Pass&) = delete;

		Tone_Mapping_Pass& operator=(const Tone_Mapping_Pass&) = delete;

	public:
		Tone_Mapping_Pass(const Render_Pass_Command_Info& Command_Info);

		~Tone_Mapping_Pass(void) = default;

	private:
		void Setup_Descriptor_Set_Layout(void);
		void Setup_Descriptor_Set(void);
		void Setup_Pipeline(void);

	private:
		RHI_Render_Pass* m_Render_Pass{ nullptr };
		RHI_Image_View* m_Input_Attachment{ nullptr };

	public:
		void Draw(void)override;
		void Pre_Inittialize(const Render_Pass_Pre_Initialize_Info* Init_Info) override;
		void Post_Inittialize(const Render_Pass_Post_Initialize_Info* Init_Info) override;
		void PrePare_Pass_Data(shared_ptr<Render_Resource_Base> Resource) override;

	};

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass