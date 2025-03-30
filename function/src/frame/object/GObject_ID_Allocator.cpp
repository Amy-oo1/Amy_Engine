#include "frame/object/GObject_ID_Allocator.h"

#include "logger/System_Logger.h"

namespace NameSpace_Function::NameSpace_Frame::NameSpace_GObject {

	using NameSpace_Core::NameSpace_Logger::System_Logger;

	GObject_ID GObject_ID_Allocator::Alloc(void) {

		if (m_Next_ID == INVALID_GOBJECT_ID)
			System_Logger::Get_Instance().Log(System_Logger::Level::critical, "GObject_ID_Allocator::Alloc: m_Next_ID is INVALID_GOBJECT_ID");

		return m_Next_ID.fetch_add(1);
	}

}// namespace NameSpace_Function::NameSpace_Frame::NameSpace_GObject