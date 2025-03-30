#include "frame/components/transform/Transform_Component.h"

#include<utility>

namespace NameSpace_Function::NameSpace_Frame::NameSpace_Components::NameSpace_Transform {

	void Transform_Component::Post_Load_Resource(weak_ptr<GObject> Parent_Object) {
		this->Component::m_Parent_GObject = Parent_Object;

		this->m_Transform_Buffer[this->m_Currrent_Buffer_Index] = m_Transform;
		this->m_Transform_Buffer[this->m_Next_Buffer_Index] = m_Transform;

		this->Component::m_Is_Dirty = true;
	}

	void Transform_Component::Tick(float Delta_Time) {
		std::swap(this->m_Currrent_Buffer_Index, this->m_Next_Buffer_Index);

		if (this->Component::m_Is_Dirty) {
			//TODO : Implement the logic to update the transform of the parent object
		}

		//TODO : g_is_editor_mode is a global variable that is set to true when the editor is running
	}

	const Affine_Transform& Transform_Component::Get_Current_Transform(void) const {
		return this->m_Transform_Buffer[this->m_Currrent_Buffer_Index];
	}

	void Transform_Component::Set_New_Transform(const Affine_Transform& Transform) {
		this->m_Transform_Buffer[this->m_Next_Buffer_Index] = Transform;

		this->Component::m_Is_Dirty = true;
	}

}// namespace NameSpace_Function::NameSpace_Frame::NameSpace_Com