#include "render/render_pass/UI_Pass.h"

#include "render/rhi/vulkan/Vulkan_RHI_Resource.h"
#include "render/rhi/vulkan/Vulkan_RHI.h"

#include "render/rhi/empty_rhi/RHI_Class.h"
#include "render/rhi/empty_rhi/RHI_Type.h"
#include "render/rhi/empty_rhi/RHI_Struct.h"

#include "render/render_system/Render_Commmon.h"
#include "render/render_system/Render_Mesh.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass {

	using std::static_pointer_cast;

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
	}

	void UI_Pass::Set_Window_UI_System(shared_ptr<Window_UI> UI) {
		this->m_Window_UI = UI;

		auto Ref_Vulkan_RHI{ std::static_pointer_cast<Vulkan_RHI>(this->m_RHI) };

		ImGui_ImplGlfw_InitForVulkan(Ref_Vulkan_RHI->Get_GLFW_Window(), true);
		ImGui_ImplVulkan_InitInfo ImGui_Init_Info{};
		{
			ImGui_Init_Info.Instance = static_cast<Vulkan_Instance*>(Ref_Vulkan_RHI->Get_Instance())->Get();
			ImGui_Init_Info.PhysicalDevice = static_cast<Vulkan_Physical_Device*>(Ref_Vulkan_RHI->Get_Physical_Device())->Get();
			ImGui_Init_Info.Device = static_cast<Vulkan_Logical_Device*>(Ref_Vulkan_RHI->Get_Logical_Device())->Get();
			ImGui_Init_Info.QueueFamily = Ref_Vulkan_RHI->Get_Graphics_Queue_Family();
			ImGui_Init_Info.Queue = static_cast<Vulkan_Queue*>(Ref_Vulkan_RHI->Get_Graphics_Queue())->Get();
			ImGui_Init_Info.PipelineCache = VK_NULL_HANDLE;
			ImGui_Init_Info.DescriptorPool = static_cast<Vulkan_Descriptor_Pool*>(Ref_Vulkan_RHI->Get_Default_Descriptor_Pool())->Get();
			ImGui_Init_Info.RenderPass = static_cast<Vulkan_Render_Pass*>(m_Render_Pass)->Get();
			ImGui_Init_Info.MinImageCount = 3;
			ImGui_Init_Info.ImageCount = 3;
			ImGui_Init_Info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
			ImGui_Init_Info.Subpass = _main_camera_subpass_ui;
			//TODO : 
			//TODO : 
			//TODO : 
			ImGui_Init_Info.Allocator = Ref_Vulkan_RHI->Get_Allocator();
			ImGui_Init_Info.CheckVkResultFn = nullptr;
		}

		ImGui_ImplVulkan_Init(&ImGui_Init_Info);

		ImGui_ImplVulkan_CreateFontsTexture();
	}

	void UI_Pass::Draw(void) {
		//TODO : Implement
	}

	void UI_Pass::Pre_Inittialize(shared_ptr<Render_Pass_Pre_Initialize_Info> Init_Info) {
		const auto UI_Info{ static_pointer_cast<UI_Render_Pass_Pre_Initialize_Info>(Init_Info) };
		{
			this->m_Render_Pass = UI_Info->Render_Pass;
		}

	}

	void UI_Pass::Post_Inittialize(shared_ptr<Render_Pass_Post_Initialize_Info> Init_Info)
	{
	}

	void UI_Pass::PrePare_Pass_Data(shared_ptr<Render_Resource_Base> Resource)
	{
	}

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass