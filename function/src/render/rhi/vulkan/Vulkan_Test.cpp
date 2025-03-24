
#include<memory>


#include "render/window/Window_System.h"
#include "render/rhi/vulkan/Vulkan_RHI.h"

using namespace std;
using namespace NameSpace_Function;
using namespace NameSpace_Function::NameSpace_Render;
using namespace NameSpace_Function::NameSpace_Render::NameSpace_RHI;
using namespace NameSpace_Function::NameSpace_Render::NameSpace_Window;
using namespace NameSpace_Function::NameSpace_Render::NameSpace_RHI::NameSpace_Vulkan_RHI;


int main() {

	Window_System_Initialization_Info Wind_info;
	shared_ptr<Window_System> window = make_shared<Window_System>(Wind_info);
	RHI_Initialization_Info info{ window };

	shared_ptr<Empty_RHI> RHI = make_shared<Vulkan_RHI>(info);

	RHI->Run();

	return 0;
}