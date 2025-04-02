#include "render/render_pass/UI_Pass.h"

#include "render/rhi/vulkan/Vulkan_RHI_Resource.h"
#include "render/rhi/vulkan/Vulkan_RHI.h"

#include "render/rhi/empty_rhi/RHI_Class.h"
#include "render/rhi/empty_rhi/RHI_Type.h"
#include "render/rhi/empty_rhi/RHI_Struct.h"

#include "render/render_system/Render_Commmon.h"
#include "render/render_system/Render_Mesh.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass {

	using NameSpace_RHI::NameSpace_Vulkan_RHI::Vulkan_RHI;
	using NameSpace_RHI::NameSpace_Vulkan_RHI::Vulkan_Instance;
	using NameSpace_RHI::NameSpace_Vulkan_RHI::Vulkan_Physical_Device;
	using NameSpace_RHI::NameSpace_Vulkan_RHI::Vulkan_Logical_Device;
	using NameSpace_RHI::NameSpace_Vulkan_RHI::Vulkan_Queue;
	using NameSpace_RHI::NameSpace_Vulkan_RHI::Vulkan_Descriptor_Pool;
	using NameSpace_RHI::NameSpace_Vulkan_RHI::Vulkan_Render_Pass;
	using NameSpace_RHI::NameSpace_Vulkan_RHI::Vulkan_Command_Buffer;

	UI_Pass::UI_Pass(const Render_Pass_Command_Info& Command_Info) :
		Render_Pass{ Command_Info } {

		//auto Ref_Vulkan_RHI{ std::static_pointer_cast<Vulkan_RHI>(this->m_RHI) };

		//ImGui_ImplGlfw_InitForVulkan(Ref_Vulkan_RHI->Get_GLFW_Window(), true);
		//ImGui_ImplVulkan_InitInfo Init_Info{};
		//{
		//	Init_Info.Instance = static_cast<Vulkan_Instance*>(Ref_Vulkan_RHI->Get_Instance())->Get();
		//	Init_Info.PhysicalDevice = static_cast<Vulkan_Physical_Device*>(Ref_Vulkan_RHI->Get_Physical_Device())->Get();
		//	Init_Info.Device = static_cast<Vulkan_Logical_Device*>(Ref_Vulkan_RHI->Get_Logical_Device())->Get();
		//	Init_Info.QueueFamily = Ref_Vulkan_RHI->Get_Graphics_Queue_Family();
		//	Init_Info.Queue = static_cast<Vulkan_Queue*>(Ref_Vulkan_RHI->Get_Graphics_Queue())->Get();
		//	Init_Info.PipelineCache = VK_NULL_HANDLE;
		//	Init_Info.DescriptorPool = static_cast<Vulkan_Descriptor_Pool*>(Ref_Vulkan_RHI->Get_Default_Descriptor_Pool())->Get();
		//	Init_Info.RenderPass = static_cast<Vulkan_Render_Pass*>(m_Render_Pass)->Get();
		//	Init_Info.MinImageCount = 3;
		//	Init_Info.ImageCount = 3;
		//	Init_Info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
		//	Init_Info.PipelineCache = nullptr;
		//	Init_Info.Subpass = _main_camera_subpass_ui;
		//	//TODO : 
		//	//TODO : 
		//	//TODO : 
		//	Init_Info.Allocator = Ref_Vulkan_RHI->Get_Allocator();
		//	Init_Info.CheckVkResultFn = nullptr;
		//}

		//ImGui_ImplVulkan_CreateFontsTexture();
		////ImGui_ImplVulkan_DestroyFontsTexture();
	}

	void UI_Pass::Draw(void) {
		//TODO : Implement
	}

	void UI_Pass::Pre_Inittialize(const Render_Pass_Pre_Initialize_Info* Init_Info){
		const auto UI_Info{ static_cast<const UI_Render_Pass_Pre_Initialize_Info*>(Init_Info) };
		{
			this->m_Render_Pass = UI_Info->Render_Pass;
		}


	}

	void UI_Pass::Post_Inittialize(const Render_Pass_Post_Initialize_Info* Init_Info)
	{
	}

	void UI_Pass::PrePare_Pass_Data(shared_ptr<Render_Resource_Base> Resource)
	{
	}

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass