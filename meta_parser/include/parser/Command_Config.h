#pragma once

namespace NameSpace_Meta_Parser::NameSpace_Parser::NameSpace_Command_Config {

	constexpr const char* clang_line_Commands[]{
		"-x",
		"c++",
		"-std=c++17",
		"-w",
		"-MG",
		"-M",
		"-ferror-limit=0",
		"-o clangLog.txt"
	};

	constexpr const char* Preprocessor__REFLECTION_PARSER__{ "-D__REFLECTION_PARSER__" };

	constexpr const char* Preprocessor_NDEBUG{ "-DNDEBUG" };

	constexpr const char* Preprocessor___clang__{ "-D__clang__" };

	constexpr const char* Preprocessors[]{
		Preprocessor__REFLECTION_PARSER__,
		Preprocessor_NDEBUG,
		Preprocessor___clang__
	};

	constexpr const char* Include_Platform{ "-ID:/Amy_Engine/platform/include" };

	constexpr const char* Include_Core{ "-ID:/Amy_Engine/core/include" };

	constexpr const char* Include_Resource{ "-ID:/Amy_Engine/resource/include" };

	constexpr const char* Include_Function{ "-ID:/Amy_Engine/function/include" };

	constexpr const char* Include_third_part_clang{ "-ID:/Amy_Engine/third_party/clang+llvm-18.1.8-x86_64-pc-windows-msvc/include" };

	constexpr const char* Include_Third_Part_SpdLog{ "-ID:/Amy_Engine/third_party/spdlog-1.15.0/include" };

	constexpr const char* Include_Third_Part_Mustance{ "-ID:/Amy_Engine/third_party/mustache/include" };

	constexpr const char* Include_Third_Part_Json{ "-ID:/Amy_Engine/third_party/nlohmann-3.11.3/include" };

	constexpr const char* Include_Third_Part_Jolt{ "-D:/Amy_Engine/third_party/JoltPhysics-5.2.0/include" };

	constexpr const char* Include_Third_Part_GLFW{ "-D:/Amy_Engine/third_party/glfw-3.4/include" };

	constexpr const char* Include_Third_Part_STB{ "-D:/Amy_Engine/third_party/stb-master/include" };

	constexpr const char* Include_Third_Part_Tiny_OBJ_Loader{ "-D:/Amy_Engine/third_party/tinyobjloader-release/include" };

	constexpr const char* Include_Third_Part_Vulkan{ "-D:/Amy_Engine/third_party/VulkanSDK/1.4.309.0/Include" };

	constexpr const char* Includes[]{
		Include_Platform,
		Include_Core,
		Include_Resource,
		Include_Function,
		Include_third_part_clang,
		Include_Third_Part_SpdLog,
		Include_Third_Part_Mustance,
		Include_Third_Part_Json,
		Include_Third_Part_GLFW,
		Include_Third_Part_STB,
		Include_Third_Part_Tiny_OBJ_Loader,
		Include_Third_Part_Vulkan,

	};

}// namespace NameSpace_Meta_Parser::NameSpace_Parser::NameSpace_Command_Config