#include "particle/Particle_Manager.h"

#include "logger/System_Logger.h"
#include "meta/generated/reflection/Global_Particle.Generated_Reflection.h"

#include "config/Resource_Configer.h"
#include "manage/Resource_Manager.h"

#include "particle/Particle_Config.h" 

namespace NameSpace_Function::NameSpace_Particle {

	using NameSpace_Core::NameSpace_Logger::System_Logger;

	using NameSpace_Resource::NameSpace_Config::Resource_Configer;
	using NameSpace_Resource::NameSpace_Manage::Resource_Manager;

	using NameSpace_Resource::NameSpace_Global::Reflection_Global_Particle_Operator;

	Particle_Manager::Particle_Manager(void)
		/*:m_Global_Particle{ Resource_Manager::Get_Instance().Load<Global_Particle>(Resource_Configer::Get_Instance().Get_Global_Particle_Resource_URL()) }*/ {

		if (0 > Reflection_Global_Particle_Operator::Get_Emit_Count_Attribute(this->m_Global_Particle)) {
			Reflection_Global_Particle_Operator::Set_Field_Emit_Count_Attribute(this->m_Global_Particle, Particle_Config::Default_Particle_Emitter_Count);
			System_Logger::Get_Instance().Log(System_Logger::Level::err, "Particle_Manager::Particle_Manager: Global Particle Emit Count is less than 0");
		}

		if (0 > Reflection_Global_Particle_Operator::Get_Emit_Gap_Attribute(this->m_Global_Particle)) {
			Reflection_Global_Particle_Operator::Set_Field_Emit_Gap_Attribute(this->m_Global_Particle, Particle_Config::Default_Particle_Emitter_Gap);

			System_Logger::Get_Instance().Log(System_Logger::Level::err, "Particle_Manager::Particle_Manager: Global Particle Emit Gap is less than 0");
		}

		if (0 != Reflection_Global_Particle_Operator::Get_Emit_Gap_Attribute(this->m_Global_Particle) % 2) {
			Reflection_Global_Particle_Operator::Set_Field_Emit_Gap_Attribute(this->m_Global_Particle, Particle_Config::Default_Particle_Emitter_Gap);

			System_Logger::Get_Instance().Log(System_Logger::Level::err, "Particle_Manager::Particle_Manager: Global Particle Emit Gap is 0");
		}

		if (1e-6 > Reflection_Global_Particle_Operator::Get_Time_Step_Attribute(this->m_Global_Particle)) {
			Reflection_Global_Particle_Operator::Set_Field_Time_Step_Attribute(this->m_Global_Particle, Particle_Config::Default_Particle_Time_Step);

			System_Logger::Get_Instance().Log(System_Logger::Level::err, "Particle_Manager::Particle_Manager: Global Particle Time Step is less than 0");
		}

		if (Reflection_Global_Particle_Operator::Get_Max_Life_Attribute(this->m_Global_Particle) < Reflection_Global_Particle_Operator::Get_Time_Step_Attribute(this->m_Global_Particle)) {
			Reflection_Global_Particle_Operator::Set_Field_Max_Life_Attribute(this->m_Global_Particle, Particle_Config::Default_Particle_Life_Time * Particle_Config::Default_Particle_Time_Step);

			System_Logger::Get_Instance().Log(System_Logger::Level::err, "Particle_Manager::Particle_Manager: Global Particle Max Life is less than Time Step");
		}

	}

	Particle_Manager& Particle_Manager::Get_Instance(void) {
		static Particle_Manager Instance;

		return Instance;
	}

	const shared_ptr<Global_Particle>& Particle_Manager::Get_Global_Particle(void) const {
		return this->m_Global_Particle;
	}

}// namespace NameSpace_Function::NameSpace_Particle