#pragma once

#include<memory>

#include "meta/reflection/Reflection_Macro.h"

namespace NameSpace_Function::NameSpace_Frame::NameSpace_GObject {
	class GObject;
}// namespace NameSpace_Function::NameSpace_Frame::NameSpace_GObject


namespace NameSpace_Function::NameSpace_Frame::NameSpace_Components {

	using std::weak_ptr;

	using NameSpace_Frame::NameSpace_GObject::GObject;

	REFLECTION_HEADER(Component);
	REFLECTION_CLASS(Component, All)
	{
		REFLECTION_BODY(Component)
	public:
		Component(void) = default;

		virtual ~Component(void) = default;

	public:
		virtual void Post_Load_Resource(weak_ptr<GObject> Parent_Object);

		virtual void Tick(float Delta_Time);

		bool Is_Dirty(void)const;

		void Set_Dirty_Flag(bool Flag);

	protected:
		META(Disable) weak_ptr<GObject> m_Parent_GObject{};

		bool m_Is_Dirty{ false };
		bool m_Is_Scale_Dirty{ false };

	private:
		bool m_Tick_In_Editor_Mode{ false };
	};


}// namespace NameSpace_Function::NameSpace_Frame::NameSpace_Components