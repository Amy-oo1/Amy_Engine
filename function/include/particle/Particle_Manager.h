#pragma once

#include "global/Global_Particle.h"
#include "components/emitter/Particle.h"

#include "particle/Particle_Desc.h"

namespace NameSpace_Function::NameSpace_Particle {



	using NameSpace_Resource::NameSpace_Global::Global_Particle;

	class Particle_Manager final {
	private:
		Particle_Manager(const Particle_Manager&) = delete;
		Particle_Manager& operator=(const Particle_Manager&) = delete;

		Particle_Manager(Particle_Manager&&) = delete;
		Particle_Manager& operator=(Particle_Manager&&) = delete;

		Particle_Manager(void);

	public:
		~Particle_Manager(void) = default;

	public:
		static Particle_Manager& Get_Instance(void);

		const shared_ptr<Global_Particle>& Get_Global_Particle(void) const;

	private:
		shared_ptr<Global_Particle> m_Global_Particle{ nullptr };

	};

}// namespace NameSpace_Function::NameSpace_Particles