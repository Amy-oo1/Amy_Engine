#pragma once

#include<vector>

#include "render/render_system/Render_Resource.h"
#include "render/render_pass/Render_Pass.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass {

	using std::vector;

	class Directional_Light_Pass final :public Render_Pass {
	private:
		Directional_Light_Pass(const Directional_Light_Pass&) = delete;

		Directional_Light_Pass& operator=(const Directional_Light_Pass&) = delete;
	public:
		Directional_Light_Pass(const Render_Pass_Command_Info& Command_Info);

		~Directional_Light_Pass(void) = default;

	private:
		void Setup_Attachments(void);
		void Setup_Render_Pass(void);
		void Setup_Frame_Buffer(void);
		void Setup_Descriptor_Set_Layout(void);
		void Setup_Descriptor_Set(void);
		void Setup_Pipeline(void);

		void Draw_Model(void);

	private:



	public:
		void Post_Inittialize(void) override;
		void PrePare_Pass_Data(shared_ptr<Render_Resource_Base> Resource) override;
		void Draw(void) override;
	};

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass