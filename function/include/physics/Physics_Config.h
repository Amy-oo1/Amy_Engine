#pragma once

#include<cstdint>

#include "math/Vector3.h"

namespace NameSpace_Function::Namespace_Physics {

	using NameSpace_Core::NameSpace_Math::Vector3;

	class Physics_Config final {
	public:
		Physics_Config(void) = default;

		Physics_Config(const Physics_Config&) = default;
		Physics_Config(Physics_Config&&) = default;

		Physics_Config& operator=(const Physics_Config&) = default;
		Physics_Config& operator=(Physics_Config&&) = default;

		~Physics_Config(void) = default;

	public:
		uint32_t Max_Body_Count{ 1024 };
		uint32_t Body_Mutex_Count{ 0 };
		uint32_t Max_body_Pair{ 65536 };
		uint32_t Max_Contact_COnstraints{ 1024 };

		uint32_t MAx_JOb_Count{ 1024 };
		uint32_t Max_Barrier_Count{ 8 };
		uint32_t Max_Conccurrent_Job_Count{ 4 };

		Vector3 Gravity{ 0.0f, 0.f,-9.8f };

		float Updata_Frequency{ 60.0f };

	};

}// namespace NameSpace_Function::Namespace_Physics