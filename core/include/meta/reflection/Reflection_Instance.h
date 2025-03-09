#pragma once

#include<memory>
#include<utility>
#include<string>

#include "meta/Reflection/Type_Meta.h"

namespace NameSpace_Core::NameSpace_Meta::NameSpace_Reflection {

	using std::shared_ptr;

	template<typename Type>
	class Reflection_Instance final {
		template<typename U>
		friend class Reflection_Instance;

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
			m_Type_Meta{ std::make_shared<Type_Meta>(Class_pelling) },
			m_Instance{ std::move(Temp_Stance) } {
		}

		~Reflection_Instance(void) = default;

	public:
		template<typename U, typename = std::enable_if_t<std::is_base_of_v<U, Type>>>
		operator Reflection_Instance<U>(void) const {
			Reflection_Instance<U> Instance{};
			Instance.Meta_Type = this->Meta_Type;
			Instance.Meta_Instance = std::static_pointer_cast<U>(this->Meta_Instance);
			return Instance;
		}

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

#define CONVERT_UP(NameSpace,Base,Sun)\
namespace NameSpace_Core::NameSpace_Meta::NameSpace_Reflection {\
	using NameSpace::Base;\
	using NameSpace::Sun;\
	template<>\
	template<>\
	Reflection_Instance<Sun>::operator Reflection_Instance<Base>() const {\
		return Reflection_Instance<Base>{\
			std::string{#Sun},\
			std::static_pointer_cast<Base>(this->m_Instance)\
		}; \
	}\
};