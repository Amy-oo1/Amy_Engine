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

	class Color_Grading_Pass final :public Render_Pass {
	private:
		Color_Grading_Pass(const Color_Grading_Pass&) = delete;

		Color_Grading_Pass& operator=(const Color_Grading_Pass&) = delete;
	public:
		Color_Grading_Pass(const Render_Pass_Command_Info& Command_Info, RHI_Render_Pass* Render_Pass);

		~Color_Grading_Pass(void) = default;

	public:

	private:
		void Setup_Descriptor_Set_Layout(void);
		void Setup_Descriptor_Set(void);
		void Setup_Pipeline(void);

		void Updata_After_Frame_Buffer_ReCreate(RHI_Image_View* Image_View);

	private:
		vector<unsigned char> m_Vertex_Shader_Code;
		vector<unsigned char> m_Fragment_Shader_Code;

		RHI_Render_Pass* m_Render_Pass{ nullptr };

	public:
		void Draw(void) override;

	};



}//namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass