#include<string>
#include<vector>
#include<memory>
#include<filesystem>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_vulkan.h"

#include "meta/generated/Reflection_Header.h"
#include "meta/generated/Serializer_Header.h"

#include "file/File_System.h"

#include "Engine.h"

#include "default_editor/Editor.h"

//using std::shared_ptr;
using std::unique_ptr;

int main(int argc, char** argv) {

	std::filesystem::path Config_Path{ std::filesystem::current_path() / ".." / "bin" / "Amy_Engine_Config.ini" };

	std::vector<std::string> Argements{
		Config_Path.generic_string()
	};

	NameSpace_Editor::Amy_Editor Editor{ std::make_unique<NameSpace_Function::Amy_Engine>(Argements) };




	ImGui_ImplVulkan_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
};