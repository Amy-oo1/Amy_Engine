#include "animation/Bone.h"

#include "logger/System_Logger.h"

#include "meta/generated/reflection/Skeleton_Data.Generated_Reflection.h"

namespace NameSpace_Function::NameSpace_Animation {

	using NameSpace_Core::NameSpace_Logger::System_Logger;

	using NameSpace_Resource::NameSpace_Components::Reflection_Bone_Raw_Operator;

	Bone::Bone(shared_ptr<Bone_Raw> Definition, shared_ptr<Bone> Parent_Bone) :
		m_Parent_Bone{ Parent_Bone },
		m_Definition{ Definition },
		m_Transform{ Reflection_Bone_Raw_Operator::Get_Binding_Pose_Attribute(Definition) },
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

	const Affine_Transform& Bone::Get_Transform(void) {
		return this->m_Transform;
	}

	const Affine_Transform& Bone::Get_Derived_Transform(void) {
		return this->m_Derived_Transform;
	}

	void Bone::Set_Transform(const Affine_Transform& Transform) {
		this->m_Transform = Transform;

		this->m_Is_Dirty = true;
	}

	void Bone::Set_Parent(const shared_ptr<Bone>& parent) {
		this->m_Parent_Bone = parent;
		this->m_Is_Dirty = true;
	}

	void Bone::Reset_To_Binding_Pose(void) {
		this->m_Transform = Reflection_Bone_Raw_Operator::Get_Binding_Pose_Attribute(this->m_Definition);

		this->m_Is_Dirty = true;
	}

	void Bone::UpData_Derived_Transform(void) {
		if (!this->m_Parent_Bone.expired()) {
			auto Parent = this->m_Parent_Bone.lock();
			if (nullptr == Parent)
				System_Logger::Get_Instance().Log(System_Logger::Level::err, "Bone Parent Is Expired");

			this->m_Derived_Transform = Parent->m_Derived_Transform * this->m_Transform;
		}
		else
			this->m_Derived_Transform = this->m_Transform;

		this->m_Is_Dirty = false;
	}

}// NameSpace_Function::NameSpace_Animation