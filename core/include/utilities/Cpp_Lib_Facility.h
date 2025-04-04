#pragma once

#include<cstdint>
#include<type_traits>

//NOTE : cpp23 : std::to_underlying is a new function in C++23
template <typename Enum>
constexpr std::underlying_type_t<Enum> to_underlying(Enum e) noexcept {
	return static_cast<std::underlying_type_t<Enum>>(e);
}