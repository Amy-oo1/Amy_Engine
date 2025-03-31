#pragma once

#include<vector>
#include<memory>

#include "math/Vector2.h"

#include "render/rhi/empty_rhi/Empty_RHI.h"
#include "render/render_system/Render_Resource.h"

#include "render/render_pass/Render_Pass.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass {

	class Pick_Pass final :public Render_Pass {
	private:
		Pick_Pass(const Pick_Pass&) = delete;

		Pick_Pass& operator=(const Pick_Pass&) = delete;
	public:
		Pick_Pass(const Render_Pass_Command_Info& Command_Info);

		~Pick_Pass(void) = default;

	public:
		void Set_Per_Mesh_Set_Layout(NameSpace_RHI::RHI_Descriptor_Set_Layout* Set_Layout);


	private:
		void Setup_Attachments(void);
		void Setup_Render_Pass(void);
		void Setup_Frame_Buffer(void);
		void Setup_Descriptor_Set_Layout(void);
		void Setup_Descriptor_Set(void);
		void Setup_Pipeline(void);

	private:
		vector<unsigned char> m_Vertex_Shader_Code;
		vector<unsigned char> m_Fragment_Shader_Code;

		NameSpace_RHI::RHI_Descriptor_Set_Layout* m_Per_Mesh_Set_Layout{ nullptr };

	public:
		void Pre_Inittialize(const Render_Pass_Inittialize_Info* Init_Info) override;
		void Post_Inittialize(void) override;
		void PrePare_Pass_Data(shared_ptr<Render_Resource_Base> Resource) override;
		void Draw(void) override;

	};

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass