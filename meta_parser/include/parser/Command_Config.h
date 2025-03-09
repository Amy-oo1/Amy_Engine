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

	constexpr const char* Include_Core{"-ID:/Amy_Engine/core/include" };

	constexpr const char* Include_Resource{ "-ID:/Amy_Engine/resource/include" };

	constexpr const char* Include_third_part_clang{ "-ID:/Amy_Engine/third_party/clang+llvm-18.1.8-x86_64-pc-windows-msvc/include" };

	constexpr const char* Include_Third_Part_SpdLog{ "-ID:/Amy_Engine/third_party/spdlog-1.15.0/include" };

	constexpr const char* Include_Third_Part_Mustance{ "-ID:/Amy_Engine/third_party/mustache/include" };

	constexpr const char* Include_Third_Part_Json{ "-ID:/Amy_Engine/third_party/nlohmann-3.11.3/include" };

	constexpr const char* Includes[]{
		Include_Platform,
		Include_Core,
		Include_Resource,
		Include_third_part_clang,
		Include_Third_Part_SpdLog,
		Include_Third_Part_Mustance,
		Include_Third_Part_Json
	};

}// namespace NameSpace_Meta_Parser::NameSpace_Parser::NameSpace_Command_Config