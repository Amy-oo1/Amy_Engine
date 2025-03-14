#pragma once

#include<cstddef>
#include<limits>
#include<vector>
#include<memory>
#include<iterator>
#include<algorithm>

#include "animation/Bone.h"

namespace NameSpace_Function::NameSpace_Animation::NameSpace_Utilities {

	using std::vector;
	using std::shared_ptr;

	shared_ptr<Bone> Find_Bone(const vector<shared_ptr<Bone>>& Bones, size_t Index, bool Is_flat = false);

}// NameSpace_Function::NameSpace_Animation::NameSpace_Utilities