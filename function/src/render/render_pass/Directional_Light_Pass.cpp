#include "render/render_pass/Directional_Light_Pass.h"

#include<tuple>
#include<utility>

#include "render/rhi/empty_rhi/RHI_Class.h"
#include "render/rhi/empty_rhi/RHI_Type.h"
#include "render/rhi/empty_rhi/RHI_Struct.h"

#include "render/render_system/Render_Commmon.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass {

	using NameSpace_RHI::RHI_IMAGE_TILING;
	using NameSpace_RHI::RHI_IMAGE_VIEW_TYPE;

	using NameSpace_RHI::RHI_Image_Usage_Flag_Bits;
	using NameSpace_RHI::RHI_Image_Aspect_Flag_Bits;
	using NameSpace_RHI::RHI_Memory_Property_Flag_Bits;

	using NameSpace_Render_System::g_Directional_Light_Shadow_map_Dimension;


	void Directional_Light_Pass::Setup__Attachments(void) {
		auto& Ref_Attachments{ this->Render_Pass::m_Frame_Buffer.Attachments };

		Ref_Attachments.resize(2);
		//NOTE : Color
		{
			Ref_Attachments[0].Format = RHI_FORMAT::RHI_FORMAT_R32_SFLOAT;

			std::tie(Ref_Attachments[0].Image, Ref_Attachments[0].Image_Memory) = this->m_RHI->Create_Image(
				{ g_Directional_Light_Shadow_map_Dimension,g_Directional_Light_Shadow_map_Dimension },
				Ref_Attachments[0].Format,
				1,
				1,
				RHI_IMAGE_TILING::RHI_IMAGE_TILING_OPTIMAL,
				RHI_Image_Usage_Flag_Bits::RHI_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | RHI_Image_Usage_Flag_Bits::RHI_IMAGE_USAGE_SAMPLED_BIT,
				RHI_Memory_Property_Flag_Bits::RHI_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
				0
			);

			Ref_Attachments[0].Image_View = this->m_RHI->Create_Image_View(
				Ref_Attachments[0].Image.get(),
				Ref_Attachments[0].Format,
				1,
				1,
				RHI_IMAGE_VIEW_TYPE::RHI_IMAGE_VIEW_TYPE_2D,
				RHI_Image_Aspect_Flag_Bits::RHI_IMAGE_ASPECT_COLOR_BIT
			);
		}

	}
	void Directional_Light_Pass::Post_Inittialize(void)
	{
	}
	void Directional_Light_Pass::PrePare_Pass_Data(shared_ptr<Render_Resource_Base> Resource)
	{
	}
	void Directional_Light_Pass::Draw(void)
	{
	}
}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass