#include "particle/Emitter_ID_Allocator.h"

#include "logger/System_Logger.h"

namespace NameSpace_Function::NameSpace_Particle {

	using NameSpace_Core::NameSpace_Logger::System_Logger;

	Particle_Emitter_ID Emitter_ID_Allocator::Allocate(void) {
		if (m_Next_ID.load() == INVALID_ID) {
			System_Logger::Get_Instance().Log(System_Logger::Level::err, "Emitter_ID_Allocator::Allocate: No more IDs available");

			return INVALID_ID;
		}

		return m_Next_ID.fetch_add(1);
	}

	Emitter_ID_Allocator& Emitter_ID_Allocator::Get_Instance(void) {
		static Emitter_ID_Allocator instance{};

		return instance;
	}

}// namespace NameSpace_Function::NameSpace_Particle