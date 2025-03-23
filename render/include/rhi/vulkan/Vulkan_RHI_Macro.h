#pragma once

#include<sstream>
#include<exception>

#include<vulkan/vulkan.h>

inline static const char* vkResultToString(VkResult result) {
	switch (result) {
	case VK_SUCCESS: return "VK_SUCCESS";
	case VK_NOT_READY: return "VK_NOT_READY";
	case VK_TIMEOUT: return "VK_TIMEOUT";
	case VK_ERROR_OUT_OF_HOST_MEMORY: return "VK_ERROR_OUT_OF_HOST_MEMORY";
	default: return "UNKNOWN_ERROR";
	}
}

#define THROW_IF_VK_FAILED(VK_CALL)                                       \
	do {                                                                      \
		VkResult __result = (VK_CALL);                                        \
		if (__result != VK_SUCCESS) {                                         \
			std::ostringstream __oss;                                         \
			__oss << "Vulkan error in " << __FILE__                           \
				  << "(" << __LINE__ << "): " << #VK_CALL                     \
				  << "\n  Code: " << vkResultToString(__result)				  \
				  << " (" << static_cast<int>(__result) << ")";               \
			throw std::runtime_error(__oss.str());                           \
		}                                                                     \
	} while (0)

