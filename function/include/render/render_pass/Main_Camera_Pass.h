#pragma once

#include<vector>
#include<memory>

#include "render/render_pass/Render_Pass.h"

#include "render/render_pass/Particle_Pass.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass {

	using std::vector;
	using std::shared_ptr;

	struct Main_Camera_Pass_Inittialize_Info final :public Render_Pass_Inittialize_Info {
		bool Enable_FXAA{ false };
		shared_ptr<Particle_Pass> Particle_Pass{ nullptr };

	};

	class Main_Camera_Pass final :public Render_Pass {
		enum LayoutType : uint8_t
		{
			_per_mesh = 0,
			_mesh_global,
			_mesh_per_material,
			_skybox,
			_axis,
			_particle,
			_deferred_lighting,
			_layout_type_count
		};

		enum RenderPipeLineType : uint8_t
		{
			_render_pipeline_type_mesh_gbuffer = 0,
			_render_pipeline_type_deferred_lighting,
			_render_pipeline_type_mesh_lighting,
			_render_pipeline_type_skybox,
			_render_pipeline_type_axis,
			_render_pipeline_type_particle,
			_render_pipeline_type_count
		};

	private:
		Main_Camera_Pass(const Main_Camera_Pass&) = delete;
		Main_Camera_Pass& operator=(const Main_Camera_Pass&) = delete;

	public:
		Main_Camera_Pass(const Render_Pass_Command_Info& Command_Info);
		~Main_Camera_Pass(void) = default;

	public:
		void Set_Per_Mesh_Set_Layout(NameSpace_RHI::RHI_Descriptor_Set_Layout* Set_Layout);

	public:
		void Setup_Attachments(void);
		void Setup_Render_Pass(void);
		void Setup_Frame_Buffer(void);
		void Setup_Descriptor_Set_Layout(void);
		void Setup_Descriptor_Set(void);
		void Setup_Pipeline(void);

		void Setup_Model_Global_Descriptor_Set(void);
		void Setup_Skybox_Descriptor_Set(void);
		void Setup_Axis_Descriptor_Set(void);
		void Setup_GBuffer_Light_Descriptor_Set(void);
		void Setup_Frame_Buffer_Descriptor_Set(void);
		void Setup_Swapchain_Frame_Buffers(void);
		void Setup_Particle_Pass(void);

		void Set_Driectional_Light_Shadow_Color_Image_View(RHI_Image_View* Image_View);
		void Set_Point_Light_Shadow_Color_Image_View(RHI_Image_View* Image_View);


	private:
		bool m_Enable_FXAA{ false };
		shared_ptr<Particle_Pass> m_Particle_Pass{ nullptr };

		RHI_Image_View* m_Directional_Light_Shadow_Color_Image_View{ nullptr };
		RHI_Image_View* m_Point_Light_Shadow_Color_Image_View{ nullptr };

		vector<unsigned char> m_Vertex_Shader_Code;
		vector<unsigned char> m_Fragment_Shader_Code;
		NameSpace_RHI::RHI_Descriptor_Set_Layout* m_Per_Mesh_Set_Layout{ nullptr };

		vector<unique_ptr<RHI_Frame_Buffer>> m_Swapchain_Frame_Buffers{};

	public:
		void Pre_Inittialize(const Render_Pass_Inittialize_Info* Init_Info) override;
		void Post_Inittialize(void) override;
		void PrePare_Pass_Data(shared_ptr<Render_Resource_Base> Resource) override;
		void Draw(void) override;
	};



}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass