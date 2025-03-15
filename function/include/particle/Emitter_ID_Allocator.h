#pragma once

#include<cstddef>
#include<atomic>
#include<limits>

namespace NameSpace_Function::Namespace_Particle {

	using Particle_Emitter_ID = std::size_t;

	class Emitter_ID_Allocator final {
	private:
		Emitter_ID_Allocator(const Emitter_ID_Allocator&) = delete;
		Emitter_ID_Allocator& operator=(const Emitter_ID_Allocator&) = delete;

		Emitter_ID_Allocator(Emitter_ID_Allocator&&) = delete;
		Emitter_ID_Allocator& operator=(Emitter_ID_Allocator&&) = delete;

		Emitter_ID_Allocator() = default;

	public:
		~Emitter_ID_Allocator() = default;

	public:
		Particle_Emitter_ID Allocate(void);

	public:
		static Emitter_ID_Allocator& Get_Instance(void);

	public:
		static constexpr Particle_Emitter_ID Invalid_ID{ std::numeric_limits<Particle_Emitter_ID>::max() };

	private:
		std::atomic<Particle_Emitter_ID> m_Next_ID{ 0 };

	};

}// namespace NameSpace_Function::Namespace_Particle