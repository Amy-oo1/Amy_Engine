#include "animation/Bone.h"

#include "meta/generated/reflection/Skeleton_Data.Generated_Reflection.h"

namespace NameSpace_Function::NameSpace_Animation {

	using NameSpace_Resource::NameSpace_Components::Reflection_Bone_Raw_Operator;

	Bone::Bone(shared_ptr<Bone_Raw> Definition, shared_ptr<Bone> Parent_Bone) :
		m_Parent_Bone{ Parent_Bone },
		m_Definition{ Definition },
		m_Initial_Transform{ Reflection_Bone_Raw_Operator::Get_Binding_Pose_Attribute(Definition) },
		m_Is_Dirty{ true } {
	}

	bool Bone::Is_Dirty(void) const {
		return this->m_Is_Dirty;
	}

	shared_ptr<Bone> Bone::Get_Parent(void) const {
		return this->m_Parent_Bone.lock();
	}

	shared_ptr<Bone_Raw> Bone::Get_Definition(void) const {
		return this->m_Definition;
	}

	void Bone::Set_Parent(const shared_ptr<Bone>& parent) {
		this->m_Parent_Bone = parent;
		this->m_Is_Dirty = true;
	}

}// NameSpace_Function::NameSpace_Animation