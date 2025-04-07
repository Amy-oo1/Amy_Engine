#pragma once

#include<vector>
#include<memory>

#include "math/Matrix4x4.h"

#include "render/render_system/Render_Commmon.h"
#include "render/render_pass/Render_Pass.h"

#include "render/render_pass/Particle_Pass.h"
#include "render/render_pass/Color_Grading_Pass.h"
#include "render/render_pass/Combine_UI_Pass.h"
#include "render/render_pass/FXAA_Pass.h"
#include "render/render_pass/Tone_Mapping_Pass.h"
#include "render/render_pass/UI_Pass.h"


#include<vector>
#include<map>

#include "render/rhi/empty_rhi/RHI_Type.h"
#include "render/rhi/empty_rhi/RHI_Class.h"

#include "render/render_system/Render_Commmon.h"
#include "render/render_system/Render_Resource.h"
#include "render/render_pass/Render_Pass.h"

#include<cstdint>
#include<optional>
#include<array>
#include<vector>

#include "render/rhi/empty_rhi/RHI_Type.h"
#include "render/rhi/empty_rhi/RHI_Class.h"

#include "render/render_system/Render_Commmon.h"
#include "render/render_system/Render_Resource.h"
#include "render/render_pass/Render_Pass.h"


#include "render/render_pass/Render_Pass_Utilities.h"


namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass {

	using NameSpace_Render_System::Mesh_Per_Frame_Storage_Buffer_Object;
	using NameSpace_Render_System::Axis_Storage_Buffer_Object;

	using std::vector;
	using std::shared_ptr;

	using NameSpace_Core::NameSpace_Math::Matrix4x4;



	///TTOD: Move
	using NameSpace_RHI::RHI_Clear_Color_Value;
	using NameSpace_RHI::RHI_Clear_Depth_Stencil_Value;
	using NameSpace_RHI::RHI_Clear_Value_Builder;
	using NameSpace_RHI::RHI_Clear_Value;
	using NameSpace_RHI::RHI_Render_Pass_Begin_Info;
	using NameSpace_RHI::RHI_PIPELINE_BIND_POINT;

	using NameSpace_RHI::RHI_SUBPASS_CONTENTS;

	using NameSpace_Render_System::Vulkan_PBR_Material;
	using NameSpace_Render_System::Vulkan_Mesh;

	using NameSpace_Render_System::Mesh_Point_Light_Shadow_Per_Frame_Storage_Buffer_Object;
	using NameSpace_Render_System::Mesh_Point_Light_Shadow_Per_Draw_Call_Storage_Buffer_Object;
	using NameSpace_Render_System::Mesh_Point_Light_Shadow_Per_Draw_Call_Vertex_Blending_Storage_Buffer_Object;;


	using NameSpace_Render_System::Render_Resource;
	using NameSpace_Render_System::Mesh_Vertex;


	using std::optional;
	using std::vector;
	using std::array;
	using std::map;

	using  NameSpace_Render_System::Mesh_Directional_Light_Shadow_Per_Frame_Storage_Buffer_Object;
	using  NameSpace_Render_System::Mesh_Per_Frame_Storage_Buffer_Object;




	using NameSpace_RHI::RHI_Descriptor_Set_Layout;

	using NameSpace_Render_System::Mesh_Point_Light_Shadow_Per_Frame_Storage_Buffer_Object;


	using NameSpace_Render_System::Mesh_Directional_Light_Shadow_Per_Frame_Storage_Buffer_Object;
	using NameSpace_Render_System::Mesh_Directional_Light_Shadow_Per_Draw_Call_Storage_Buffer_Object;
	using NameSpace_Render_System::Mesh_Directional_Light_Shadow_Per_Draw_CallVertex_Blending_Storage_Buffer_Object;

	using NameSpace_Render_System::Mesh_Vertex;
	using NameSpace_Render_System::Render_Resource;

	using  NameSpace_Render_System::Mesh_Directional_Light_Shadow_Per_Frame_Storage_Buffer_Object;
	using  NameSpace_Render_System::Mesh_Per_Frame_Storage_Buffer_Object;
	using NameSpace_Render_System::Vulkan_PBR_Material;
	using NameSpace_Render_System::Vulkan_Mesh;
	using NameSpace_Render_System::Vulkan_Render_Mesh_Node;
	using NameSpace_Render_System::Vulkan_Render_Axis_Node;
	using namespace	NameSpace_Utilities;

	using NameSpace_Render_System::Vulkan_PBR_Material;
	using NameSpace_Render_System::Vulkan_Mesh;


	enum LayoutType : uint32_t
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

	enum RenderPipeLineType : uint32_t
	{
		_render_pipeline_type_mesh_gbuffer = 0,
		_render_pipeline_type_deferred_lighting,
		_render_pipeline_type_mesh_lighting,
		_render_pipeline_type_skybox,
		_render_pipeline_type_axis,
		_render_pipeline_type_particle,
		_render_pipeline_type_count
	};

	struct Main_Camera_Render_Pass_Per_Initialize_Info final :public Render_Pass_Pre_Initialize_Info {
		bool Enable_FXAA{ false };
		RHI_Image_View* Directional_Light_Shadow_Color_Image_View;
		RHI_Image_View* Point_Light_Shadow_Color_Image_View;
	};

	class Main_Camera_Pass final :public Render_Pass {
	public:


	private:
		Main_Camera_Pass(const Main_Camera_Pass&) = delete;
		Main_Camera_Pass& operator=(const Main_Camera_Pass&) = delete;

	public:
		Main_Camera_Pass(const Render_Pass_Command_Info& Command_Info);
		~Main_Camera_Pass(void) = default;

	public:
		void Set_Per_Mesh_Set_Layout(NameSpace_RHI::RHI_Descriptor_Set_Layout* Set_Layout);

		bool Get_Axis_State(void)const;
		void Set_Aixs_State(bool State);

		void Draw_Forward(
			shared_ptr<Color_Grading_Pass> Color_Grading_Pass,
			shared_ptr<FXAA_Pass> FXAA_Pass,
			shared_ptr<Tone_Mapping_Pass> Tone_Mapping_Pass,
			shared_ptr<UI_Pass> UI_Pass,
			shared_ptr<Combine_UI_Pass> Combine_UI_Pass,
			uint32_t Frame_Index
		);

		void Draw_Mesh_Lighting(void);

		void Draw_SkeBox(void);


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
		void Setup_GBuffer_Lighting_Descriptor_Set(void);
		void Setup_Frame_Buffer_Descriptor_Set(void);
		void Setup_SwapChain_Frame_Buffers(void);


		void Update_After_Frame_Buffer_ReCreate(void);

	private:
		bool m_Enable_FXAA{ false };
		RHI_Image_View* m_Directional_Light_Shadow_Color_Image_View{ nullptr };
		RHI_Image_View* m_Point_Light_Shadow_Color_Image_View{ nullptr };

	private:
		vector<unique_ptr<RHI_Frame_Buffer>> m_Swapchain_Frame_Buffers{};


		bool m_Is_Show_Axis{ false };

		Mesh_Per_Frame_Storage_Buffer_Object m_Mesh_Per_Frame_Storage_Buffer_Object{};
		Axis_Storage_Buffer_Object m_Axis_Storage_Buffer_Object{};

	public:
		void Pre_Inittialize(shared_ptr<Render_Pass_Pre_Initialize_Info> Init_Info) override;
		void Post_Inittialize(shared_ptr<Render_Pass_Post_Initialize_Info> Init_Info) override;
		void PrePare_Pass_Data(shared_ptr<Render_Resource_Base> Resource) override;
		void Draw(void) override;

	};



}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass