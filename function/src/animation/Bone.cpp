#include "animation/Bone.h"

namespace NameSpace_Function::NameSpace_Animation {
	bool Bone::Is_Dirty(void) const {
		return this->m_Is_Dirty;
	}

	const string Bone::Get_Name(void) const {
		return this->m_Name;
	}

	weak_ptr<Bone> Bone::Get_Parent(void) const {
		return this->m_Parent_Node;
	}

	const Affine_Transform Bone::Get_Relative_Transform(void) const {
		return this->m_Relative_Transform;
	}

	void Bone::Set_Relative_Transform(const Affine_Transform& Temp_Affine_Transform) {
		this->m_Relative_Transform = Temp_Affine_Transform;
		this->m_Is_Dirty = true;
	}

	void Bone::Set_Parent(const shared_ptr<Bone>& parent) {
		this->m_Parent_Node = parent;
		this->m_Is_Dirty = true;
	}

}// NameSpace_Function::NameSpace_Animation