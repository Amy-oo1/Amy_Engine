#pragma once

#include<vector>
#include<string>
#include<cstddef>

#include "meta/reflection/Reflection_Macro.h"

#include "file/File_System.h"
#include "components/skeleton/Skeleton_Node.h"
#include "components/animation/Animation_Clip.h"

namespace NameSpace_Resource::NameSpace_Components {

	using std::vector;
	using std::string;

	using  NameSpace_Platform::NameSpace_File::path;

	REFLECTION_HEADER(Bone_Blend_Weight);
	REFLECTION_CLASS(Bone_Blend_Weight, All) final
	{
		REFLECTION_BODY(Bone_Blend_Weight);
	public:
		Bone_Blend_Weight(void) = default;

		~Bone_Blend_Weight(void) = default;

	private:
		vector<float> m_Blend_Weights{};

	};

	REFLECTION_HEADER(BlendState_With_Clip_Data);
	REFLECTION_CLASS(BlendState_With_Clip_Data, All) final
	{
		REFLECTION_BODY(BlendState_With_Clip_Data);
	public:
		BlendState_With_Clip_Data(void) = default;

		~BlendState_With_Clip_Data(void) = default;

	private:
		vector<Animation_Clip> m_Blend_Clip{};
		vector<Skeleton_Node_Map> m_Blend_Skeleton{};
		vector<Bone_Blend_Weight> m_Blend_Weights{};
		vector<float> m_Blend_ratio{};

	};

	REFLECTION_HEADER(Blend_State);
	REFLECTION_CLASS(Blend_State, All) final
	{
		REFLECTION_BODY(Blend_State);
	public:
		Blend_State(void) = default;

		~Blend_State(void) = default;

	private:
		vector<path> m_Blend_Clip_File_Path{};
		vector<float> m_Blend_Clip_File_Length{};

		vector<path> m_Blend_Skeleton_Map_File_Path{};

		vector<float> m_Blend_Weights{};

		vector<path> m_Blend_Mask_File_Path{};

		vector<BlendState_With_Clip_Data> m_BlendState{};

		vector<float> m_Blend_ratio{};

	};

}// namespace NameSpace_Resource::NameSpace_Components