#pragma once

#include "json.h"

namespace NameSpace_Core::NameSpace_Meta::NameSpacce_Serializer{

	using JSON = nlohmann::json;

	class Serializer final {
	public:
		Serializer(void) = delete;

		Serializer(const Serializer&) = delete;
		Serializer(Serializer&&) = delete;

		Serializer& operator=(const Serializer&) = delete;
		Serializer& operator=(Serializer&&) = delete;

	public:
		template<typename Type>
		static const JSON Write(const Type& Instance) {
			return JSON(Instance);
		}

		template<typename Type>
		static const Type Read(const JSON& Json_Context) {
			return Json_Context.get<Type>();
		}

	};

}// namespace NameSpace_Core::NameSpace_Meta::NameSpacce_Serializer


