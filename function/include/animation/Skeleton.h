#pragma once

#include<cstddef>
#include<vector>

#include "components/skeleton/Skeleton_Data.h"
#include "components/animation/Blend_State.h"
#include "animation/Bone.h"

namespace NameSpace_Function::NameSpace_Animation {

	using std::vector;

	using NameSpace_Resource::NameSpace_Components::Skeleton_Data;
	using NameSpace_Resource::NameSpace_Components::BlendState_With_Clip_Data;

	class Skeleton final {
	private:
		Skeleton(void) = delete;

		Skeleton(const Skeleton&) = delete;
		Skeleton(Skeleton&&) = delete;

		Skeleton& operator=(const Skeleton&) = delete;
		Skeleton& operator=(Skeleton&&) = delete;

		~Skeleton(void) = default;

	public:
		Skeleton(shared_ptr<Skeleton_Data> Skeleton_Data);

	private:
		shared_ptr<Skeleton_Data> m_Skeleton_Data;
		vector<shared_ptr<Bone>> m_Bones{};

	};

}// namespace NameSpace_Function::NameSpace_Animation
