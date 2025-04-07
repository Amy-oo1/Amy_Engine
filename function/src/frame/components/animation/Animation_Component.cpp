#include "frame/components/animation/Animation_Component.h"

#include "meta/generated/reflection/Animation.Generated_Reflection.h"

#include "animation/Animation_Manager.h"

namespace NameSpace_Function::NameSpace_Frame::NameSpace_Components::NameSpace_Animation_Component {

	using NameSpace_Resource::NameSpace_Components::Reflection_Animation_Component_Res_Operator;

	using NameSpace_Animation::Animation_Manager;

	void Animation_Component::Post_Load_Resource(weak_ptr<GObject> Parent_Object) {
		this->Component::m_Parent_GObject = Parent_Object;

		auto Skeleton_Res{ Animation_Manager::Get_Instance().TryLoad_Skeleton_Data(Reflection_Animation_Component_Res_Operator::Get_Skeleton_URL_Attribute(this->m_Animation_Resource)) };

		//this->m_Skeleton
	
	
	}

}// namespace NameSpace_Function::NameSpace_Frame::NameSpace_Components::NameSpace_Animation_Component