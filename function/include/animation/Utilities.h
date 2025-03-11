#pragma once

#include<cstddef>
#include<limits>
#include<vector>
#include<string>
#include<memory>
#include<iterator>
#include<algorithm>

#include "animation/Bone.h"

#include "meta/generated/reflection/Skeleton_Data.Generated_Reflection.h"

namespace NameSpace_Function::NameSpace_Animation::NameSpace_Utilities {

	using std::vector;
	using std::string;
	using std::shared_ptr;
	using std::weak_ptr;

	using NameSpace_Resource::NameSpace_Components::Reflection_Bone_Raw_Operator;

	shared_ptr<Bone> Find_Bone(const vector<shared_ptr<Bone>>& Bones, size_t Index, bool Is_flat = false) {
		if (Index == std::numeric_limits<size_t>::max()) {
			return nullptr;
		}
		if (Is_flat)
			return (Index < Bones.size()) ? Bones[Index] : __nullptr;
		else {
			const auto It = std::find_if(Bones.begin(), Bones.end(), [Index](const shared_ptr<Bone>& Temp_Bone) {
				return Reflection_Bone_Raw_Operator::Get_Current_Index_Attribute(Temp_Bone->Get_Definition()) == Index; }
			);

			return (Bones.end() == It) ? nullptr : *It;
		}
	}

	template<typename Type>
	size_t Iindex(const vector<Type>& container, const Type& value) {
		auto iterator = std::find(container.begin(), container.end(), value);
		if (iterator == container.end()) {
			return -1;
		}
		return std::distance(container.begin(), iterator);
	}

	template<typename Type>
	void Append_Vector(vector<Type>& Base, vector<Type>& Addition) {
		Base.insert(Base.end(), Addition.begin(), Addition.end());
	}

	//TODO : Implement this function
	//shared_ptr<Bone> Find_Bone(shared_ptr<Bone> Bones, int Key, int Size, bool Is_flat = false);

}// NameSpace_Function::NameSpace_Animation::NameSpace_Utilities