#pragma once

#include<string>
#include<vector>
#include<unordered_set>
#include<memory>

#include "file/File_System.h"

#include "meta/reflection/Reflection_Instance.h"

#include "common/Object_Resource.h"

#include "frame/components/Component.h"
#include "frame/object/GObject_ID_Allocator.h"

namespace NameSpace_Function::NameSpace_Frame::NameSpace_GObject {

	using std::string;
	using std::vector;
	using std::shared_ptr;

	using NameSpace_Platform::NameSpace_File::path;

	using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

	using NameSpace_Resource::NameSpace_Common::Object_Instance;

	using NameSpace_Components::Component;

	class GObject :public std::enable_shared_from_this<GObject> {
	private:
		GObject(const GObject&) = delete;
		GObject& operator=(const GObject&) = delete;

		GObject(GObject&&) = delete;
		GObject& operator=(GObject&&) = delete;

	public:
		GObject(void) = default;

		virtual ~GObject(void) = default;

	public:
		virtual void Tick(float Delta_Time);

		//NOTE : Ptr Fromt his is not safe In Construction
		bool Load(const shared_ptr<Object_Instance>& Object_Instance_Res);

		shared_ptr<Object_Instance> Save(void);

		const GObject_ID Get_ID(void) const;

		const string& Get_Name(void) const;
		void Set_Name(const string& Name);

		bool Has_Component(const string& Component_Name) const;

		const vector<Reflection_Instance<Component>>& Get_Components(void) const;

		template<typename Type>
		shared_ptr<Type> TryGet_Component(const string& Component_Type_Spelling) {
			for (auto& Component : m_Components)
				if (Component.Get_Type_Spelling() == Component_Type_Spelling)
					return std::static_pointer_cast<Type>(Component.Get_Instance());

			return nullptr;
		}

		template<typename Type>
		const shared_ptr<Type> TryGet_Component(const string& Component_Type_Spelling)const {
			for (auto& Component : m_Components)
				if (Component.Get_Type_Spelling() == Component_Type_Spelling)
					return std::static_pointer_cast<Type>(Component.Get_Instance());

			return nullptr;
		}

	protected:
		GObject_ID m_ID{ GObject_ID_Allocator::INVALID_GOBJECT_ID };
		string m_Name{};
		path m_Definition_URL{};

		vector<Reflection_Instance<Component>> m_Components{};

	private:
		void Load_Instance(const shared_ptr<Object_Instance>& Object_Instance_Res);
		bool Load_Definition(void);

	};

}// namespace NameSpace_Function::NameSpace_Frame::NameSpace_GObject