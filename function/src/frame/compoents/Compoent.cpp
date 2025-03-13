#include "frame/compoents/Compoent.h"

namespace NameSpace_Function::Namespace_Frame::NameSpace_Components {

	void Component::Post_Load_Resource(weak_ptr<GObject> Parent_Object) {
		this->m_Parent_GObject = Parent_Object;
	}

	void Component::Set_Dirty_Flag(bool Flag) {
		this->m_Is_Dirty = Flag;
	}

	void Component::Tick(float Delta_Time) {
	}

	bool Component::Is_Dirty(void) const {
		return this->m_Is_Dirty;
	}

}// namespace NameSpace_Function::Namespace_Frame::NameSpace_Components