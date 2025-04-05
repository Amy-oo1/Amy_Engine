#pragma once

#include<string>
#include<vector>
#include<memory>

#include "meta/reflection/Reflection_Macro.h"

#include "math/Vector3.h"
#include "common/Object_Resource.h"

namespace NameSpace_Resource::NameSpace_Common {

	using std::string;
	using std::vector;
	using std::shared_ptr;

	using NameSpace_Core::NameSpace_Math::Vector3;

	REFLECTION_HEADER(Level_Resource);
	REFLECTION_CLASS(Level_Resource, All) final
	{
		REFLECTION_BODY(Level_Resource);
	public:
		Level_Resource(void) = default;

		~Level_Resource(void) = default;

	private:
		Vector3 m_Gravity{ 0.f, 0.f, -9.8f };

		string m_Character_Name;
		vector<shared_ptr<Object_Instance>> m_Objects;

	};

}// namespace NameSpace_Resource::NameSpace_Common
