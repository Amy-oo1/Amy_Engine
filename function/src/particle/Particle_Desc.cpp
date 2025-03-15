#include "particle/Particle_Desc.h"

#include "meta/generated/reflection/Particle.Generated_Reflection.h"

namespace NameSpace_Function::Namespace_Particle {

	using NameSpace_Resource::NameSpace_Components::Reflection_Particle_Res_Operator;

	Particle_Emitter_Desc::Particle_Emitter_Desc(const shared_ptr<Particle_Res>& Temp_Particle_Res, const Particle_Emitter_Transform_Desc& Temp_Transform_Desc) :
		m_ID{ Temp_Transform_Desc.ID },
		m_Transform{ Temp_Transform_Desc.Transform },
		m_Velocity{ Reflection_Particle_Res_Operator::Get_Velocity_Attribute(Temp_Particle_Res) },
		m_Acceleration{ Reflection_Particle_Res_Operator::Get_Acceleration_Attribute(Temp_Particle_Res) },
		m_Size{ Reflection_Particle_Res_Operator::Get_Size_Attribute(Temp_Particle_Res) },
		m_Emitter_Type{ Reflection_Particle_Res_Operator::Get_Emitter_Type_Attribute(Temp_Particle_Res) },
		m_Life{ Reflection_Particle_Res_Operator::Get_Life_Attribute(Temp_Particle_Res) },
		m_Color{ Reflection_Particle_Res_Operator::Get_Color_Attribute(Temp_Particle_Res) } {
	}

}// namespace NameSpace_Function::Namespace_Particle