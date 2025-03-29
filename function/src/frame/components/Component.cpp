#include "frame/components/Component.h"

namespace NameSpace_Function::Namespace_Frame::NameSpace_Components {

	void Component::Set_Dirty_Flag(bool Flag) {
		this->m_Is_Dirty = Flag;
	}

	void Component::Tick(float Delta_Time) {
	}

	bool Component::Is_Dirty(void) const {
		return this->m_Is_Dirty;
	}

}// namespace NameSpace_Function::Namespace_Frame::NameSpace_Components