#include "meta/Reflection/Reflection_Register.h"

namespace NameSpace_Core::NameSpace_Meta::NameSpace_Reflection {

	void Reflection_Register::Register_Class(const string& Class_Spelling, shared_ptr<Class_Func_Tuple> Value){
		this->m_Class_Map.emplace(std::make_pair(Class_Spelling, std::move(Value)));
	}

	void Reflection_Register::Register_Class_Base_Class(const string& Class_Spelling, shared_ptr<Class_Base_Class_Tuple> Value){
		this->m_Base_Class_Map.emplace(std::make_pair(Class_Spelling, std::move(Value)));
	}

	void Reflection_Register::Register_Class_Filed(const string& Class_Speling, shared_ptr<std::unordered_map<string, shared_ptr<Class_Field_Func_Tuple>>> Value){
		this->m_Class_Field_Map[Class_Speling]=std::move(Value);
	}

	void Reflection_Register::Register_Class_Field_CPPVector(const string& Class_Speling, shared_ptr<std::unordered_map<string, shared_ptr<Class_Filed_CPPVector_Func_Tuple>>> Value) {
		this->m_Class_Field_CPPVector_Map[Class_Speling] = std::move(Value);
	}

	void Reflection_Register::Un_Register_Clsss(const string& Class_Spelling){
		this->m_Class_Map.erase(Class_Spelling);
	}

	void Reflection_Register::Un_Register_Base_Class(const string& Class_Spelling){
		this->m_Base_Class_Map.erase(Class_Spelling);
	}

	void Reflection_Register::Un_Register_Field(const string& Class_Spelling){
		this->m_Class_Field_Map[Class_Spelling]->clear();
	}

	void Reflection_Register::Un_Register_CPPVector(const string& Class_Spelling){
		this->m_Class_Field_CPPVector_Map[Class_Spelling]->clear();
	}

	Reflection_Register& Reflection_Register::Get_Instance(void){
		static Reflection_Register Instance{};

		return Instance;
	}

};// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Reflection