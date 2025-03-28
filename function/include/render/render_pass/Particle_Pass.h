#pragma once

#include<vector>
#include<memory>

#include "vma/vk_mem_alloc.h"

#include "render/rhi/empty_rhi/RHI_Type.h"
#include "render/rhi/empty_rhi/RHI_Class.h"
#include "render/render_pass/Render_Pass.h"

#include "render/render_system/Render_Commmon.h"
#include "render/render_system/Render_Resource.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass {

	using std::unique_ptr;

	using NameSpace_RHI::RHI_Viewport;

	using NameSpace_RHI::RHI_Command_Buffer;
	using NameSpace_RHI::RHI_Buffer;
	using NameSpace_RHI::RHI_Image;
	using NameSpace_RHI::RHI_Image_View;
	using NameSpace_RHI::RHI_Device_Memory;
	using NameSpace_RHI::RHI_Fence;

	using NameSpace_Render_System::Particle_Billboard_Per_Draw_Call_Storage_Buffer_Object;
	using NameSpace_Render_System::Particle_Billboard_Per_Frame_Storage_Buffer_Object;

	struct Particle_Emitter_Buffer final {
		unique_ptr<RHI_Buffer> Storage_Buffer{ nullptr };
		unique_ptr<RHI_Buffer> Position_Render_Buffer{ nullptr };
		unique_ptr<RHI_Buffer> Position_Device_Buffer{ nullptr };
		unique_ptr<RHI_Buffer> Position_Host_Buffer{ nullptr };
		unique_ptr<RHI_Buffer> Counter_Device_Buffer{ nullptr };
		unique_ptr<RHI_Buffer> Counter_Host_Buffer{ nullptr };
		unique_ptr<RHI_Buffer> Indirect_Dispatch_Argument_Buffer{ nullptr };
		unique_ptr<RHI_Buffer> Alive_List_Buffer{ nullptr };
		unique_ptr<RHI_Buffer> Alive_list_Next_Buffer{ nullptr };
		unique_ptr<RHI_Buffer> Dead_List_Buffer{ nullptr };
		unique_ptr<RHI_Buffer> Particle_Resource_Buffer{ nullptr };

		unique_ptr<RHI_Device_Memory> Storage_Memory{ nullptr };
		unique_ptr<RHI_Device_Memory> Position_Render_Memory{ nullptr };
		unique_ptr<RHI_Device_Memory> Position_Device_Memory{ nullptr };
		unique_ptr<RHI_Device_Memory> Position_Host_Memory{ nullptr };
		unique_ptr<RHI_Device_Memory> Counter_Device_Memory{ nullptr };
		unique_ptr<RHI_Device_Memory> Counter_Host_Memory{ nullptr };
		unique_ptr<RHI_Device_Memory> Indirect_Dispatch_Argument_Memory{ nullptr };
		unique_ptr<RHI_Device_Memory> Alive_List_Memory{ nullptr };
		unique_ptr<RHI_Device_Memory> Alive_list_Next_Memory{ nullptr };
		unique_ptr<RHI_Device_Memory> Dead_List_Memory{ nullptr };
		unique_ptr<RHI_Device_Memory> Particle_Resource_Memory{ nullptr };
	};

	/*class Particle_Pass final :public Render_Pass {
	private:
		Particle_Pass(const Particle_Pass&) = delete;

		Particle_Pass& operator=(const Particle_Pass&) = delete;
	public:
		Particle_Pass(const Render_Pass_Command_Info& Command_Info);

		~Particle_Pass(void) = default;

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
*/


}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass