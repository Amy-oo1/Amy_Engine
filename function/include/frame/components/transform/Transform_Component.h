#pragma once

#include<cstddef>
#include<vector>

#include "transform/Affine_Transform.h"

#include "meta/reflection/Reflection_Macro.h"

#include "frame/components/Component.h"
#include "frame/object/GObject.h"

namespace NameSpace_Function::NameSpace_Frame::NameSpace_Components::NameSpace_Transform {

	using std::vector;

	using NameSpace_Core::NameSpace_Transform::Affine_Transform;

	using NameSpace_GObject::GObject;

	REFLECTION_HEADER(Transform_Component);
	REFLECTION_CLASS(Transform_Component, All) final :public Component
	{
		REFLECTION_BODY(Transform_Component)
	public:
		Transform_Component(void) = default;

		virtual ~Transform_Component(void) override = default;

	public:
		virtual void Post_Load_Resource(weak_ptr<GObject> Parent_Object) override;
		virtual void Tick(float Delta_Time) override;

		const Affine_Transform& Get_Current_Transform(void)const;

		void Set_New_Transform(const Affine_Transform& Transform);

	protected:
		Affine_Transform m_Transform{ Affine_Transform::IDENTITY };

		vector<Affine_Transform> m_Transform_Buffer{ Affine_Transform::IDENTITY ,Affine_Transform::IDENTITY };

		size_t m_Currrent_Buffer_Index{ 0 };
		size_t m_Next_Buffer_Index{ 1 };

	};

}// namespace NameSpace_Function::NameSpace_Frame::NameSpace_Com