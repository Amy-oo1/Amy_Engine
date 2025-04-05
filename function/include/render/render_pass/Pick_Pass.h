#pragma once

#include<vector>
#include<memory>

#include "math/Vector2.h"

#include "render/rhi/empty_rhi/Empty_RHI.h"

#include "render/render_system/Render_Resource.h"
#include "render/render_system/Render_Commmon.h"

#include "render/render_pass/Render_Pass.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass {

	using std::vector;
	using std::shared_ptr;

	using NameSpace_RHI::RHI_Descriptor_Set_Layout;

	using NameSpace_Render_System::Mesh_Inefficient_Pick_Per_Frame_Storage_Buffer_Object;

	struct Pick_Render_Pass_Pre_Initialize_Info final :public Render_Pass_Pre_Initialize_Info {
		RHI_Descriptor_Set_Layout* Per_Mesh_Set_Layout;
	};

	struct Pick_Render_Pass_Post_Initialize_Info final :public Render_Pass_Post_Initialize_Info {
		//NOTE : Empty
	};


	class Pick_Pass final :public Render_Pass {
	private:
		Pick_Pass(const Pick_Pass&) = delete;

		Pick_Pass& operator=(const Pick_Pass&) = delete;
	public:
		Pick_Pass(const Render_Pass_Command_Info& Command_Info);

		~Pick_Pass(void) = default;

	public:
		void Set_Per_Mesh_Set_Layout(NameSpace_RHI::RHI_Descriptor_Set_Layout* Set_Layout);

		void ReCreate_Frame_Buffer(void);

	private:
		void Setup_Attachments(void);
		void Setup_Render_Pass(void);
		void Setup_Frame_Buffer(void);
		void Setup_Descriptor_Set_Layout(void);
		void Setup_Descriptor_Set(void);
		void Setup_Pipeline(void);

	private:
		RHI_Descriptor_Set_Layout* m_Per_Mesh_Set_Layout{ nullptr };

		Mesh_Inefficient_Pick_Per_Frame_Storage_Buffer_Object m_Mesh_Inefficient_Pick_Per_Frame_Storage_Buffer_Object;


	public:
		void Pre_Inittialize(shared_ptr<Render_Pass_Pre_Initialize_Info> Init_Info) override;
		void Post_Inittialize(shared_ptr<Render_Pass_Post_Initialize_Info> Init_Info) override;
		void PrePare_Pass_Data(shared_ptr<Render_Resource_Base> Resource) override;
		void Draw(void) override;

	};

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass