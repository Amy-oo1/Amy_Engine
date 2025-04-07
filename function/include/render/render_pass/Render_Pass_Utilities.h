#pragma once

#include<cstdint>

namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass::NameSpace_Utilities {

	static inline uint32_t Round_Up(uint32_t Value, uint32_t Alignment) {
		return (Value + Alignment - 1) & ~(Alignment - 1);
	}

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Pass