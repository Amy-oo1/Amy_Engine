#include "animation/Animation_Loader.h"

namespace NameSpace_Function::NameSpace_Animation {

	Animation_Loader::Animation_Loader(Resource_Manager& Ref_Resource_Manager)
		:m_Ref_Resource_Manager{ Ref_Resource_Manager } {
	}

	shared_ptr<Skeleton_Data> Animation_Loader::Load_Skeleton_Data(const path& Skeleton_Data_URL) {
		return this->Load_Resource<Skeleton_Data>(Skeleton_Data_URL);
	}

	shared_ptr<Skeleton_Node_Map> Animation_Loader::Load_Skeleton_Node_Map(const path& _Skeleton_Node_Map_URL) {
		return this->Load_Resource<Skeleton_Node_Map>(_Skeleton_Node_Map_URL);
	}

	shared_ptr<Bone_Blend_Mask> Animation_Loader::Load_Bone_Blend_Mask(const path& Bone_Blend_Mask_URL) {
		return this->Load_Resource<Bone_Blend_Mask>(Bone_Blend_Mask_URL);
	}

	shared_ptr<Animation_Clip> Animation_Loader::Load_Animation_Clip(const path& Animation_Clip_URL) {
		return this->Load_Resource<Animation_Clip>(Animation_Clip_URL);
	}

	Animation_Loader& Animation_Loader::Get_Instance(Resource_Manager& Ref_Resource_Manager) {
		static Animation_Loader Instance{ Ref_Resource_Manager };

		return Instance;
	}



}// namespace NameSpace_Function::NameSpace_Animation