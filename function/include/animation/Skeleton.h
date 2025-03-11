#pragma once

#include<cstddef>
#include<tuple>
#include<vector>

#include "components/skeleton/Skeleton_Data.h"
#include "components/skeleton/Skeleton_Node.h"
#include "components/animation/Blend_State.h"
#include "components/animation/Animation.h"

#include "animation/Bone.h"

namespace NameSpace_Function::NameSpace_Animation {

	using std::tuple;
	using std::vector;

	using NameSpace_Resource::NameSpace_Components::Skeleton_Node_Map;
	using NameSpace_Resource::NameSpace_Components::Skeleton_Data;
	using NameSpace_Resource::NameSpace_Components::Animation_Channel;
	using NameSpace_Resource::NameSpace_Components::Animation_Clip;
	using NameSpace_Resource::NameSpace_Components::BlendState_With_Clip_Data;
	using NameSpace_Resource::NameSpace_Components::Animation_Effect_Element;

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

	public:
		void Apply_Animation(const shared_ptr<BlendState_With_Clip_Data>& Blend_State_Clip_Data);

		void OutPut_Animation(void)const;

	private:
		void ReSet_Init_Skeleton(void);

		const vector<tuple<shared_ptr<Animation_Clip>, float, shared_ptr<Skeleton_Node_Map>>> Extract_Clip_Data(const shared_ptr<BlendState_With_Clip_Data>& Temp_BlendState_With_Clip_Data) const;

		tuple<int, int, float> Calculate_Frame_Data(const shared_ptr<Animation_Clip>& Temp_Clip, float Phase)const;

		tuple<int, int> Clamp_Frame_Indices(const shared_ptr<Animation_Channel>& Temp_Animation_Channel, int low_Frame, int Height_Frame) const;

		void Apply_Clip_To_Skeleton(shared_ptr<Animation_Clip> Temp_Clip, shared_ptr<Skeleton_Node_Map> Animotaon_Map, int Low_Frame, int Height_Fram, float Lerp_Raotio);

		void Apply_Bone_Transform(const shared_ptr<Animation_Channel>& Temp_Animation_Channel, shared_ptr<Bone>& Apply_Bone, int Low_Frame, int Height_Frame, float Lerp_Ratio);

		shared_ptr<Animation_Effect_Element> Create_Bone_Result_Element(const shared_ptr<Bone>& Temp_Bone)const;

	private:
		shared_ptr<Skeleton_Data> m_Skeleton_Data;
		vector<shared_ptr<Bone>> m_Bones{};

	};

}// namespace NameSpace_Function::NameSpace_Animation
