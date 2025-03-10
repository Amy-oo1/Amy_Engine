#pragma once

#include<cstddef>
#include<vector>
#include<string>
#include<memory>
#include<iterator>
#include<algorithm>

#include "animation/Bone.h"

namespace NameSpace_Function::NameSpace_Animation::NameSpace_Utilities {

	using std::vector;
	using std::string;
	using std::shared_ptr;
	using std::weak_ptr;

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