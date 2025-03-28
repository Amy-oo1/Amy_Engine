#pragma once

#include<cstdint>
#include<vector>
#include<memory>

#include "render/rhi/empty_rhi/RHI_Type.h"
#include "render/rhi/empty_rhi/RHI_Class.h"

#include "render/render_system/Render_Commmon.h"
#include "render/render_system/Render_Resource.h"
#include "render/render_pass/Render_Pass_Base.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass {

	using std::vector;
	using std::unique_ptr;
	using std::shared_ptr;

	using NameSpace_RHI::RHI_FORMAT;

	using NameSpace_Render_System::Vulkan_Render_Mesh_Node;
	using NameSpace_Render_System::Vulkan_Render_Axis_Node;

	using NameSpace_RHI::RHI_Image;
	using NameSpace_RHI::RHI_Image_View;

	using NameSpace_RHI::RHI_Descriptor_Set_Layout;
	using NameSpace_RHI::RHI_Descriptor_Set;

	using NameSpace_RHI::RHI_Pipeline_Layout;
	using NameSpace_RHI::RHI_Pipeline;

	using NameSpace_RHI::RHI_Frame_Buffer;
	using NameSpace_RHI::RHI_Render_Pass;
	using NameSpace_RHI::RHI_Device_Memory;

	using NameSpace_Render_System::Global_Render_Resource;

	enum
	{
		_main_camera_pass_gbuffer_a = 0,
		_main_camera_pass_gbuffer_b = 1,
		_main_camera_pass_gbuffer_c = 2,
		_main_camera_pass_backup_buffer_odd = 3,
		_main_camera_pass_backup_buffer_even = 4,
		_main_camera_pass_post_process_buffer_odd = 5,
		_main_camera_pass_post_process_buffer_even = 6,
		_main_camera_pass_depth = 7,
		_main_camera_pass_swap_chain_image = 8,
		_main_camera_pass_custom_attachment_count = 5,
		_main_camera_pass_post_process_attachment_count = 2,
		_main_camera_pass_attachment_count = 9,
	};

	enum
	{
		_main_camera_subpass_basepass = 0,
		_main_camera_subpass_deferred_lighting,
		_main_camera_subpass_forward_lighting,
		_main_camera_subpass_tone_mapping,
		_main_camera_subpass_color_grading,
		_main_camera_subpass_fxaa,
		_main_camera_subpass_ui,
		_main_camera_subpass_combine_ui,
		_main_camera_subpass_count
	};

	struct Visiable_Node final {
		vector<Vulkan_Render_Mesh_Node>* Directional_Light_Visiable_Mesh_Nodes{ nullptr };
		vector<Vulkan_Render_Mesh_Node>* Point_Lights_Visiable_Mesh_Nodes{ nullptr };

		vector<Vulkan_Render_Mesh_Node>* Main_Camera_Visiable_Mesh_Nodes{ nullptr };

		Vulkan_Render_Axis_Node* Axis_Node{ nullptr };
	};


	class Render_Pass :public Render_Pass_Base {
	public:
		struct Frame_Buffer_Attachment final {
			RHI_FORMAT Format;

			unique_ptr<RHI_Image> Image;
			unique_ptr<RHI_Image_View> Image_View;
			unique_ptr<RHI_Device_Memory> Image_Memory;
		};

		struct Frame_Buffer final {
			uint32_t Width;
			uint32_t Height;
			uint32_t Layers;

			vector<Frame_Buffer_Attachment> Attachments;
			unique_ptr<RHI_Render_Pass> Render_Pass;
			unique_ptr<RHI_Frame_Buffer> Frame_Buffer;
		};

		struct Descriptor final {
			unique_ptr<RHI_Descriptor_Set_Layout> Descriptor_Set_Layout;
			unique_ptr<RHI_Descriptor_Set> Descriptor_Set;
		};

		struct Render_Pipeline final {
			unique_ptr<RHI_Pipeline_Layout> Pipeline_Layout;
			unique_ptr<RHI_Pipeline> Pipeline;
		};

	private:
		Render_Pass(const Render_Pass&) = delete;
		Render_Pass& operator=(const Render_Pass&) = delete;

	public:
		Render_Pass(const Render_Pass_Command_Info& Command_Info);

		virtual ~Render_Pass(void) = default;

	public:
		static Visiable_Node s_Visable_Node;


	public://TODO : 
		shared_ptr<Global_Render_Resource> m_Global_Render_Resource{ nullptr };

		Frame_Buffer m_Frame_Buffer{};
		vector<Descriptor> m_Descriptors{};
		vector<Render_Pipeline> m_Render_Pipelines{};


		/*virtual void Post_Inittialize(void) = 0;
		virtual void Draw(void) = 0;*/
	};


}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass