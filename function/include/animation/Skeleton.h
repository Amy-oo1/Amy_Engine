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
		Skeleton(const Skeleton_Data& skeleton_data);
		Skeleton(const Skeleton_Data& skeleton_data, const BlendState_With_Clip_Data& blend_state_with_clip_data);
		Skeleton(const Skeleton_Data& skeleton_data, const vector<BlendState_With_Clip_Data>& blend_state_with_clip_data);
		Skeleton(const Skeleton_Data& skeleton_data, const vector<BlendState_With_Clip_Data>& blend_state_with_clip_data, const vector<Bone>& bones);
		Skeleton(const Skeleton_Data& skeleton_data, const vector<BlendState_With_Clip_Data>& blend_state_with_clip_data, const vector<Bone>& bones, const vector<Bone>& flat_bones);
		Skeleton(const Skeleton_Data& skeleton_data, const vector<BlendState_With_Clip_Data>& blend_state_with_clip_data, const vector<Bone>& bones, const vector<Bone>& flat_bones, const vector<Bone>& flat_bones_with_clip);

	private:
		bool is_flat{ false };
		//TODO : Implement the flat array of bones
		Bone* m_Bones{ nullptr };
		size_t m_Bones_Size{ 0 };

	};

}// namespace NameSpace_Function::NameSpace_Animation
