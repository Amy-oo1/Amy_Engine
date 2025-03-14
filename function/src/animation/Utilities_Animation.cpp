#include "animation/Utilities_Animation.h"

#include "meta/generated/reflection/Skeleton_Data.Generated_Reflection.h"

namespace NameSpace_Function::NameSpace_Animation::NameSpace_Utilities {

	using NameSpace_Resource::NameSpace_Components::Reflection_Bone_Raw_Operator;

	shared_ptr<Bone> Find_Bone(const vector<shared_ptr<Bone>>& Bones, const  size_t Index, bool Is_flat) {
		if (Index == std::numeric_limits<size_t>::max())
			return nullptr;

		if (Is_flat)
			return (Index < Bones.size()) ? Bones[Index] : nullptr;
		else {
			const auto It = std::find_if(Bones.begin(), Bones.end(), [Index](const shared_ptr<Bone>& Temp_Bone) {
				return Index == Reflection_Bone_Raw_Operator::Get_Current_Index_Attribute(Temp_Bone->Get_Definition()); }
			);

			return (Bones.end() == It) ? nullptr : *It;
		}
	}

}// namespace NameSpace_Function::NameSpace_Animation::NameSpace_Utilities 