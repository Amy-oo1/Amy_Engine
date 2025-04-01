#pragma once

#include<cstdint>
#include<vector>
#include<memory>

#include "vma/vk_mem_alloc.h"

#include "math/Vector3.h"
#include "math/Vector4.h"
#include "math/Random.h"

#include "render/rhi/empty_rhi/RHI_Type.h"
#include "render/rhi/empty_rhi/RHI_Class.h"
#include "render/render_pass/Render_Pass.h"

#include "render/render_system/Render_Commmon.h"
#include "render/render_system/Render_Resource.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass {

	using std::unique_ptr;
	using std::shared_ptr;

	using NameSpace_Core::NameSpace_Math::Vector3;
	using NameSpace_Core::NameSpace_Math::Vector4;
	using NameSpace_Core::NameSpace_Math::Default_RNG;


	using NameSpace_RHI::RHI_Viewport;

	using NameSpace_RHI::RHI_Command_Buffer;
	using NameSpace_RHI::RHI_Buffer;
	using NameSpace_RHI::RHI_Image;
	using NameSpace_RHI::RHI_Image_View;
	using NameSpace_RHI::RHI_Device_Memory;
	using NameSpace_RHI::RHI_Fence;


	using NameSpace_Render_System::Patricle_Collision_Pre_Frame_Storage_Buffer_Object;
	using NameSpace_Render_System::Particle_Billboard_Per_Frame_Storage_Buffer_Object;

	struct Uvec4 final {
		float X;
		float Y;
		float Z;
		float W;
	};

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

	struct Particel_Paas_Inittialize_Info final :public Render_Pass_Inittialize_Info {
		shared_ptr<Particle_Emitter_Buffer> Emitter_Buffer{ nullptr };
	};

	struct alignas(16) Compute_Uniform_Buffer_Object final {
		uint32_t		Emit_Gap;
		uint32_t		Emit_Count;
		float			Max_Life;
		float			Time_Step;
		Vector3			Gravity;
		Vector4			Pack; // randomness 3 | frame index 1
		Uvec4			Viewport; // x, y, width, height
		Vector4			Extent;   // width, height, near, far
	};

	class Particle_Pass final :public Render_Pass {
	private:
		Particle_Pass(const Particle_Pass&) = delete;

		Particle_Pass& operator=(const Particle_Pass&) = delete;
	public:
		Particle_Pass(const Render_Pass_Command_Info& Command_Info);

		~Particle_Pass(void) = default;

	public:
		void Set_Per_Mesh_Set_Layout(NameSpace_RHI::RHI_Descriptor_Set_Layout* Set_Layout);


		void Set_Depth_and_Normal_Image(RHI_Image* Depth_Image, RHI_Image* Normal_Image);
		void Set_Render_Pass_Handle(RHI_Render_Pass* Render_Pass);

	private:
		void Setup_Uniform_Buffer(void);

		void Setup_Attachments(void);
		void Setup_Render_Pass(void);
		void Setup_Frame_Buffer(void);
		void Setup_Descriptor_Set_Layout(void);
		void Setup_Descriptor_Set(void);
		void Setup_Pipeline(void);

		void Setup_Graphics_Pipeline(void);
		void Setup_Compute_Pipeline(void);

	private:
		Default_RNG m_Random_Engine{};

		vector<unsigned char> m_Kickoff_Compute_Shader_Code;
		vector<unsigned char> m_Emit_Compute_Shader_Code;
		vector<unsigned char> m_Simulate_Compute_Shader_Code;

		vector<unique_ptr<RHI_Pipeline>> m_Compute_Pipelines{};

		vector<unsigned char> m_Vertex_Shader_Code;
		vector<unsigned char> m_Fragment_Shader_Code;

		unique_ptr<RHI_Command_Buffer> m_Compute_Command_Buffer{ nullptr };
		unique_ptr<RHI_Command_Buffer> m_Copy_Command_Buffer{ nullptr };
		unique_ptr<RHI_Fence> m_Fence{ nullptr };


		NameSpace_RHI::RHI_Descriptor_Set_Layout* m_Per_Mesh_Set_Layout{ nullptr };

		unique_ptr<RHI_Buffer> m_Scene_Uniform_Buffer{ nullptr };
		unique_ptr<RHI_Device_Memory> m_Scene_Uniform_Memory{ nullptr };
		void* m_Scene_Uniform_Buffer_Mapped{ nullptr };

		unique_ptr<RHI_Buffer> m_Compute_Uniform_Buffer{ nullptr };
		unique_ptr<RHI_Device_Memory> m_Compute_Uniform_Memory{ nullptr };
		void* m_Compute_Uniform_Buffer_Mapped{ nullptr };
		Compute_Uniform_Buffer_Object m_Compute_Uniform_Buffer_Object{};

		unique_ptr<RHI_Buffer> m_Particle_Billbord_Uniform_Buffer{ nullptr };
		unique_ptr<RHI_Device_Memory> m_Particle_Billbord_Uniform_Memory{ nullptr };
		void* m_Particle_Billbord_Uniform_Buffer_Mapped{ nullptr };


		RHI_Image* m_Src_Depth_Image{ nullptr };
		RHI_Image* m_Src_Normal_Image{ nullptr };
		RHI_Render_Pass* m_Render_Pass{ nullptr };

	public:
		void Pre_Inittialize(const Render_Pass_Inittialize_Info* Init_Info) override;
		void Post_Inittialize(void) override;
		void PrePare_Pass_Data(shared_ptr<Render_Resource_Base> Resource) override;
		void Draw(void) override;

	};



}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass