#pragma once

#include<memory>

#include "meta/reflection/Reflection_Macro.h"

#include "animation/Skeleton.h"
#include "components/animation/Animation.h"


#include "frame/components/Component.h"

namespace NameSpace_Function::NameSpace_Frame::NameSpace_Components::NameSpace_Animation_Component {

	using std::shared_ptr;

	using NameSpace_Resource::NameSpace_Components::Animation_Component_Res;
	using NameSpace_Resource::NameSpace_Components::Animation_Effect;

	using NameSpace_Animation::Skeleton;

	REFLECTION_HEADER(Animation_Component);
	REFLECTION_CLASS(Animation_Component, All) final :public Component
	{
		REFLECTION_BODY(Animation_Component)
	public:
		Animation_Component(void) = default;

		 ~Animation_Component(void) = default;

	public:
		virtual void Post_Load_Resource(weak_ptr<GObject> Parent_Object) override;

		virtual void Tick(float Delta_Time) override;

		const Animation_Effect& Get_Resource(void)const;

		const Skeleton& Get_Skeleton(void)const;

	private:
		shared_ptr<Animation_Component_Res> m_Animation_Resource{};

	//	Skeleton m_Skeleton{ nullptr };

	};



}// namespace NameSpace_Function::NameSpace_Frame::NameSpace_Components::NameSpace_Animation_Component