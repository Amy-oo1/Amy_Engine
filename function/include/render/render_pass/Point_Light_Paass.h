#pragma once

#include<vector>

#include "render/rhi/empty_rhi/RHI_Type.h"
#include "render/render_system/Render_Resource.h"
#include "render/render_pass/Render_Pass.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass {

	class Point_Light_Pass final :public Render_Pass {
	private:
		Point_Light_Pass(const Point_Light_Pass&) = delete;

		Point_Light_Pass& operator=(const Point_Light_Pass&) = delete;
	public:
		Point_Light_Pass(const Render_Pass_Command_Info& Command_Info);

		~Point_Light_Pass(void) = default;

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
		void Post_Inittialize(void) override;
		void PrePare_Pass_Data(shared_ptr<Render_Resource_Base> Resource) override;
		void Draw(void) override;
	};

}//namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass
