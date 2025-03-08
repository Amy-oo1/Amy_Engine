#pragma once

#include<functional>
#include<string>
#include<tuple>
#include<unordered_map>
#include<vector>
#include<memory>
#include<utility>
#include<optional>

namespace NameSpace_Core::NameSpace_Meta::NameSpace_Reflection {

	class Type_Meta;

	template<typename Type>
	class Reflection_Instance;

	using std::function;
	using std::tuple;
	using std::string;
	using std::vector;
	using std::shared_ptr;
	using std::optional;

	using Get_Class_Spelling_Func = function<const string(void)>;

	using Get_Class_Display_Name_Func = function<const string(void)>;
	
	using Get_Class_Base_Class_Reflection_Instance_List_Func = function<const vector<Reflection_Instance<void>>(shared_ptr<void>)>;

	using Get_Class_Field_Type_Spelling_Fun = function<const string(void)>;

	using Get_Class_Field_Spelling_Func = function<const string(void)>;

	using Get_Class_Field_Display_Name_Func = function<const string(void)>;

	using Get_Class_Filed_Attribute_Func = function<const void *const(shared_ptr<void>)>;

	using Set_Class_Field_Attribute_Func = function<void(shared_ptr<void>, const void* )>;

	using Is_Class_Field_CPPVector_Func = function<const bool(void)>;

	using Get_Class_Field_CPPVector_Element_Type_Spelling_Func = function<const string(void)>;

	using Get_Class_Field_CPPVector_Capacity_Func = function<const size_t(void*)>;

	using Get_Class_Field_CPPVector_Size_Func = function<const size_t(void*)>;

	using Get_Class_Field_CPPVector_Element_Func = function<const void*const(shared_ptr<void>, size_t)>;

	using Set_Class_Field_CPPVector_Element_Func = function<void(shared_ptr<void>, size_t, const void*)>;

	using Class_Func_Tuple = tuple<
		optional<Get_Class_Spelling_Func>,
		optional<Get_Class_Display_Name_Func>
	>;

	using Class_Base_Class_Tuple = tuple<
		optional<Get_Class_Base_Class_Reflection_Instance_List_Func>
	>;

	using Class_Field_Func_Tuple = tuple<
		optional<Get_Class_Field_Type_Spelling_Fun>,
		optional<Get_Class_Field_Spelling_Func>,
		optional<Get_Class_Field_Display_Name_Func>,
		optional<Get_Class_Filed_Attribute_Func>,
		optional<Set_Class_Field_Attribute_Func>,
		optional<Is_Class_Field_CPPVector_Func>
	>;

	using Class_Filed_CPPVector_Func_Tuple = tuple<
		optional<Get_Class_Field_CPPVector_Element_Type_Spelling_Func>,
		optional<Get_Class_Field_CPPVector_Capacity_Func>,
		optional<Get_Class_Field_CPPVector_Size_Func>,
		optional<Get_Class_Field_CPPVector_Element_Func>,
		optional<Set_Class_Field_CPPVector_Element_Func>
	>;

	class Reflection_Register final{
		friend class Type_Meta;

	private:
		Reflection_Register(const Reflection_Register&) = delete;
		Reflection_Register(Reflection_Register&) = delete;

		Reflection_Register& operator=(const Reflection_Register&) = delete;
		Reflection_Register& operator=(Reflection_Register&&) = delete;

	public:
		Reflection_Register(void) = default;

		~Reflection_Register(void) = default;

	public:
		void Register_Class(const string& Class_Spelling, shared_ptr<Class_Func_Tuple> Value);
		void Register_Class_Base_Class(const string& Class_Spelling, shared_ptr<Class_Base_Class_Tuple> Value);
		void Register_Class_Filed(const string& Class_Speling, shared_ptr<std::unordered_map<string, shared_ptr<Class_Field_Func_Tuple>>> Value);
		void Register_Class_Field_CPPVector(const string& Class_Speling, shared_ptr<std::unordered_map<string, shared_ptr<Class_Filed_CPPVector_Func_Tuple>>> Value);

		void Un_Register_Clsss(const string& ClassSpelling);
		void Un_Register_Base_Class(const string& ClassSpelling);
		void Un_Register_Field(const string& Class_Spelling);
		void Un_Register_CPPVector(const string& Class_Spelling);

	public:
		static Reflection_Register& Get_Instance(void);

	private:
		std::unordered_map<string, shared_ptr<Class_Func_Tuple>> m_Class_Map{};
		std::unordered_map<string, shared_ptr<Class_Base_Class_Tuple>> m_Base_Class_Map{};
		std::unordered_map<string, shared_ptr<std::unordered_map<string, shared_ptr<Class_Field_Func_Tuple>>>> m_Class_Field_Map{};
		std::unordered_map<string, shared_ptr<std::unordered_map<string, shared_ptr<Class_Filed_CPPVector_Func_Tuple>>>> m_Class_Field_CPPVector_Map{};

	};

};// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Reflection