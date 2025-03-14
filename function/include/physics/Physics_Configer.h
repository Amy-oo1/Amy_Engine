#pragma once

#include<cstdint>

#include "math/Vector3.h"

namespace NameSpace_Function::Namespace_Physics {

	using NameSpace_Core::NameSpace_Math::Vector3;

	class Physics_Configer final {
	private:
		Physics_Configer(const Physics_Configer&) = delete;
		Physics_Configer(Physics_Configer&&) = delete;

		Physics_Configer& operator=(const Physics_Configer&) = delete;
		Physics_Configer& operator=(Physics_Configer&&) = delete;

		Physics_Configer(void) = default;

	public:
		~Physics_Configer(void) = default;

	public:
		//TODO : Dynamic change
		static Physics_Configer& Get_Instance(void);

	public:
		static constexpr uint32_t Max_Body_Count{ 1024 };
		static constexpr uint32_t Body_Mutex_Count{ 0 };
		static constexpr uint32_t Max_body_Pair{ 65536 };
		static constexpr uint32_t Max_Contact_COnstraints{ 1024 };

		static constexpr uint32_t MAx_JOb_Count{ 1024 };
		static constexpr uint32_t Max_Barrier_Count{ 8 };
		static constexpr uint32_t Max_Conccurrent_Job_Count{ 4 };

		static inline Vector3 Gravity{ 0.0f, 0.f,-9.8f };

		static constexpr float Updata_Frequency{ 60.0f };
	};

}// namespace NameSpace_Function::Namespace_Physics