#pragma once

#include "components/skeleton/Skeleton_Data.h"
#include "components/animation/Blend_State.h"

namespace NameSpace_Function::NameSpace_Animation {

	using NameSpace_Resource::NameSpace_Components::Skeleton_Data;
	using NameSpace_Resource::NameSpace_Components::BlendState_With_Clip_Data;

	class Skeleton final {

	public:
		Skeleton(void) = default;
		Skeleton(const Skeleton&) = default;
		Skeleton(Skeleton&&) = default;
		Skeleton& operator=(const Skeleton&) = default;
		Skeleton& operator=(Skeleton&&) = default;
		~Skeleton(void) = default;

	};

}// namespace NameSpace_Function::NameSpace_Animation
