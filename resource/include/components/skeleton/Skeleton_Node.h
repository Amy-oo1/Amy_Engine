#pragma once

#include<vector>
#include<cstddef>

#include "meta/reflection/Reflection_Macro.h"

namespace NameSpace_Resource::NameSpace_Components {

	using std::vector;

	REFLECTION_HEADER(Skeleton_Node_Map);
	REFLECTION_CLASS(Skeleton_Node_Map, All) final
	{
		REFLECTION_BODY(Skeleton_Node_Map);
	public:
		Skeleton_Node_Map(void) = default;

		~Skeleton_Node_Map(void) = default;

	private:
		vector<size_t> Convert{};

	};

}// namespace NameSpace_Resource::NameSpace_Components
