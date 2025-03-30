#pragma once

#include<string>
#include<vector>

#include "file/File_System.h"

#include "meta/reflection/Reflection_Macro.h"

#include "meta/reflection/Reflection_Instance.h"

namespace NameSpace_Function::NameSpace_Frame::NameSpace_Components {
	class Component;
}

namespace NameSpace_Resource::NameSpace_Common {

	using std::string;
	using std::vector;

	using NameSpace_Platform::NameSpace_File::path;

	using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;
	using NameSpace_Function::NameSpace_Frame::NameSpace_Components::Component;

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
		string m_Name;
		path m_Definition_URL;

		vector<Reflection_Instance<Component>> m_Instanced_Components;
	};

} // NameSpace_Resource::NameSpace_Common