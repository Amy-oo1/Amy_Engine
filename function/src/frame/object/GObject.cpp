#include "frame/object/GObject.h"

#include<optional>

#include "logger/System_Logger.h"
#include "meta/generated/reflection/Object_Resource.Generated_Reflection.h"

#include "global/Global_Systemer.h"

namespace NameSpace_Function::Namespace_Frame::NameSpace_GObject {

	using NameSpace_Core::NameSpace_Logger::System_Logger;
	using NameSpace_Resource::NameSpace_Common::Reflection_Object_Definition_Operator;
	using NameSpace_Resource::NameSpace_Common::Reflection_Object_Instance_Operator;

	using NameSpace_Resource::NameSpace_Common::Object_Definition;

	using Namespace_Global::Global_Systemer;

	void GObject::Tick(float Delta_Time) {
		//TODO : Add Tick If
		for (auto& Temp_Component : m_Components)
			Temp_Component->Tick(Delta_Time);
	}

	bool GObject::Load(const shared_ptr<Object_Instance>& Object_Instance_Res) {
		this->Load_Instance(Object_Instance_Res);
		return this->Load_Definition();
	}
	shared_ptr<Object_Instance> GObject::Save(void) {
		shared_ptr<Object_Instance> Res{ std::make_shared<Object_Instance>() };

		Reflection_Object_Instance_Operator::Set_Field_Name_Attribute(Res, this->m_Name);
		Reflection_Object_Instance_Operator::Set_Field_Definition_URL_Attribute(Res, this->m_Definition_URL);
		Reflection_Object_Instance_Operator::Set_Field_Instanced_Components_Attribute(Res, this->m_Components);

		return Res;
	}

	const GObject_ID GObject::Get_ID(void) const {
		return this->m_ID;
	}

	const string& GObject::Get_Name(void) const {
		return this->m_Name;
	}

	void GObject::Set_Name(const string& Name) {
		this->m_Name = Name;
	}

	bool GObject::Has_Component(const string& Component_Name) const {
		for (auto& Temp_Component : this->m_Components)
			if (Temp_Component.Get_Type_Spelling() == Component_Name)
				return true;

		return false;
	}

	const vector<Reflection_Instance<Component>>& GObject::Get_Components(void) const {
		return this->m_Components;
	}

	void GObject::Load_Instance(const shared_ptr<Object_Instance>& Object_Instance_Res) {
		this->m_Name = Reflection_Object_Instance_Operator::Get_Name_Attribute(Object_Instance_Res);
		this->m_Definition_URL = Reflection_Object_Instance_Operator::Get_Definition_URL_Attribute(Object_Instance_Res);

		this->m_Components.clear();
		this->m_Components = Reflection_Object_Instance_Operator::Get_Instanced_Components_Attribute(Object_Instance_Res);
		for (auto& Temp_Component : this->m_Components)
			Temp_Component->Post_Load_Resource(this->std::enable_shared_from_this<GObject>::weak_from_this());
	}

	bool GObject::Load_Definition(void) {
		shared_ptr< Object_Definition> Temp_Definition = nullptr; //Global_Systemer::Get_Instance().Resource_Manager.Load<Object_Definition>(this->m_Definition_URL);
		if (nullptr == Temp_Definition) {
			System_Logger::Get_Instance().Log(System_Logger::Level::err, "Failed to Load Definition :{} ", this->m_Definition_URL.generic_string());

			return false;
		}

		for (auto& Temp_Component : Reflection_Object_Definition_Operator::Get_Components_Attribute(Temp_Definition))
			if (!this->Has_Component(Temp_Component.Get_Type_Spelling())) {
				this->m_Components.push_back(Temp_Component);

				this->m_Components.back()->Post_Load_Resource(this->std::enable_shared_from_this<GObject>::weak_from_this());
			}

		return true;
	}
}// namespace NameSpace_Function::Namespace_Frame::NameSpace_GObject