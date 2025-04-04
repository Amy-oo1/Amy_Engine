#pragma once

#include<vector>

#include "render/rhi/empty_rhi/RHI_Type.h"
#include "render/rhi/empty_rhi/RHI_Class.h"
#include "render/render_system/Render_Resource.h"
#include "render/render_pass/Render_Pass.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass {

	using std::vector;

	struct Directioal_Light_Render_Pass_Pre_Initialize_Info final :public Render_Pass_Pre_Initialize_Info {
		//NOTE : Empty
	};

	struct Directioal_Light_Render_Pass_Post_Initialize_Info final :public Render_Pass_Post_Initialize_Info {
		NameSpace_RHI::RHI_Descriptor_Set_Layout* Per_Mesh_Set_Layout;
	};

	class Directional_Light_Pass final :public Render_Pass {
	private:
		Directional_Light_Pass(const Directional_Light_Pass&) = delete;

		Directional_Light_Pass& operator=(const Directional_Light_Pass&) = delete;
	public:
		Directional_Light_Pass(const Render_Pass_Command_Info& Command_Info);

		~Directional_Light_Pass(void) = default;

	public:


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
		void Pre_Inittialize(shared_ptr<Render_Pass_Pre_Initialize_Info> Init_Info) override;
		void Post_Inittialize(shared_ptr<Render_Pass_Post_Initialize_Info> Init_Info) override;
		void PrePare_Pass_Data(shared_ptr<Render_Resource_Base> Resource) override;
		void Draw(void) override;
	};

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass