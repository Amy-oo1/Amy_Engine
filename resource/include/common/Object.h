#pragma once

#include<string>
#include<vector>

#include "meta/reflection/Reflection_Macro.h"

#include "meta/reflection/Reflection_Instance.h"

namespace NameSpace_Function::Namespace_Frame::NameSpace_Component {
	class Component;
}

namespace NameSpace_Resource::NameSpace_Common {

	using std::string;
	using std::vector;

	using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;
	using NameSpace_Function::Namespace_Frame::NameSpace_Component::Component;

	REFLECTION_HEADER(Component_Definition);
	REFLECTION_CLASS(Component_Definition, All) final
	{
		REFLECTION_BODY(Component_Definition);
	public:
		Component_Definition(void) = default;

		~Component_Definition(void) = default;

	private:
		string m_Type_Name;
		string m_Component;

	};

	REFLECTION_HEADER(Object_Definition);
	REFLECTION_CLASS(Object_Definition, All) final
	{
		REFLECTION_BODY(Object_Definition);
	public:
		Object_Definition(void) = default;

		~Object_Definition(void) = default;

	private:
		string m_Seplling;
		vector<Reflection_Instance<Component>> m_Components;

	};

	REFLECTION_HEADER(Object_Instance);
	REFLECTION_CLASS(Object_Instance, All) final
	{
		REFLECTION_BODY(Object_Instance);
	public:
		Object_Instance(void) = default;

		~Object_Instance(void) = default;

	private:
		std::string m_Name;
		std::string m_Definition;

		std::vector<Reflection_Instance<Component>> m_Instanced_Components;
	};
} // NameSpace_Resource::NameSpace_Common