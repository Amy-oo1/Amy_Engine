#pragma once

#include<string>
#include<optional>

#include "meta/Reflection/Reflection_Register.h"

namespace NameSpace_Core::NameSpace_Meta::NameSpace_Reflection {

	using std::string;
	using std::optional;
	using std::nullopt;
	
	class Type_Meta final {
	private:
		Type_Meta(void) = default;

	public:
		Type_Meta(const Type_Meta&) = default;
		Type_Meta(Type_Meta&&) = default;

		Type_Meta& operator=(const Type_Meta&) = default;
		Type_Meta& operator=(Type_Meta&&) = default;

		Type_Meta(const string& Spelling);

		~Type_Meta(void) = default;

	public:
		const string Get_Spelling(void) const;

	public:
		static std::unordered_map<string, shared_ptr<Type_Meta>> Type_Table;

	private:
		string m_Spelling{};

		optional<shared_ptr<Class_Func_Tuple>> m_Class_Func_Tuple{ nullopt };
		optional<shared_ptr<Class_Base_Class_Tuple>> m_Base_Class_Tuple{ nullopt };
		optional<shared_ptr<std::unordered_map<string, shared_ptr<Class_Field_Func_Tuple>>>> m_Field_Class_Func_Tuple{ nullopt };
		optional<shared_ptr<std::unordered_map<string, shared_ptr<Class_Filed_CPPVector_Func_Tuple>>>> m_Filed_CPPVector_Func_Tuple{ nullopt };

	};

};// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Reflection
