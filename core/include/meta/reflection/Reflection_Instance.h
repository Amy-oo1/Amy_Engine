#pragma once

#include<memory>
#include<utility>

#include "meta/Reflection/Type_Meta.h"

namespace NameSpace_Core::NameSpace_Meta::NameSpace_Reflection {

	using std::shared_ptr;

	template<typename Type>
	class Reflection_Instance final {
	public:
		Reflection_Instance(void) = default;

		Reflection_Instance(const Reflection_Instance&) = default;
		Reflection_Instance(Reflection_Instance&&) = default;

		Reflection_Instance& operator=(const Reflection_Instance&) = default;
		Reflection_Instance& operator=(Reflection_Instance&&) = default;

		Reflection_Instance(const string& Class_pelling) :
			m_Type_Meta{ Class_pelling } {
		}

		Reflection_Instance(const string& Class_pelling, shared_ptr<Type> Temp_Stance) :
			m_Type_Meta{ Class_pelling },
			m_Instance{ std::move(Temp_Stance) } {
		}

		~Reflection_Instance(void) = default;

	public:
		bool operator==(const Reflection_Instance& Other) const {
			return *this->m_Instance == *Other.m_Instance;
		}

		bool operator!=(const Reflection_Instance& Other) const {
			return !(*this == Other);
		}

		bool operator<(const Reflection_Instance& Other) const {
			return *this->m_Instance < *Other.m_Instance;
		}

		bool operator>(const Reflection_Instance& Other) const {
			return  *this->m_Instance > *Other.m_Instance;
		}

		bool operator<=(const Reflection_Instance& Other) const {
			return *this->m_Instance <= *Other.m_Instance;
		}

		bool operator>=(const Reflection_Instance& Other) const {
			return *this->m_Instance >= *Other.m_Instance;
		}

		Type& operator*(void) {
			return *this->m_Instance;
		}

		const Type& operator*(void) const {
			return *this->m_Instance;
		}

		Type* operator->(void) {
			return this->m_Instance.get();
		}

		const Type* operator->(void) const {
			return this->m_Instance.get();
		}

		operator Type& (void) {
			return *this->m_Instance;
		}

		operator const Type& (void) const {
			return *this->m_Instance;
		}

	private:
		shared_ptr<Type_Meta> m_Type_Meta{};
		shared_ptr<Type> m_Instance{ nullptr };

	};

}// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Reflection