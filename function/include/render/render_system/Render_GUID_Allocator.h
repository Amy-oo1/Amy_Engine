#pragma once

#include<vector>
#include<unordered_map>
#include<utility>

namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System {

	using std::pair;
	using std::vector;
	using std::unordered_map;

	static constexpr size_t INVALID_GUID{ 0 };

	template<typename T>
	class Render_GUID_Allocator final {
		friend class Render_GUID_Allocator<T>;

	private:
		Render_GUID_Allocator(const Render_GUID_Allocator&) = delete;
		Render_GUID_Allocator(Render_GUID_Allocator&&) = delete;

		Render_GUID_Allocator& operator=(const Render_GUID_Allocator&) = delete;
		Render_GUID_Allocator& operator=(Render_GUID_Allocator&&) = delete;

	public:
		Render_GUID_Allocator() = default;

		~Render_GUID_Allocator() = default;

		size_t Allocate_GUID(const T& Element) {
			if (this->m_Element_TO_GUID_Map.find(Element) != this->m_Element_TO_GUID_Map.end())
				return this->m_Element_TO_GUID_Map[Element];

			for (size_t Index = 0; Index < this->m_Element_TO_GUID_Map.size() + 1; ++Index) {
				size_t Guid = Index + 1;
				if (this->m_GUID_To_Element_Map.find(Guid) == this->m_GUID_To_Element_Map.end()) {
					this->m_Element_TO_GUID_Map[Element] = Guid;
					this->m_GUID_To_Element_Map[Guid] = Element;

					return Guid;
				}
			}

			return INVALID_GUID;
		}

		bool Has_Element(const T& Element) const {
			return this->m_Element_TO_GUID_Map.find(Element) != this->m_Element_TO_GUID_Map.end();
		}

		pair<const T&, bool> Get_Element(const size_t Guid) const {
			auto Iter = this->m_GUID_To_Element_Map.find(Guid);
			if (Iter != this->m_GUID_To_Element_Map.end())
				return std::make_pair(Iter->second, true);

			return std::make_pair(T{}, false);
		}

		size_t Get_GUID(const T& Element) const {
			auto Iter = this->m_Element_TO_GUID_Map.find(Element);
			if (Iter != this->m_Element_TO_GUID_Map.end())
				return Iter->second;

			return INVALID_GUID;
		}

		void Deallocate_GUID(const size_t Guid) {
			auto Iter = this->m_GUID_To_Element_Map.find(Guid);
			if (Iter != this->m_GUID_To_Element_Map.end()) {
				this->m_Element_TO_GUID_Map.erase(Iter->second);
				this->m_GUID_To_Element_Map.erase(Iter);
			}
		}

		void Deallocate_Element(const T& Element) {
			auto Iter = this->m_Element_TO_GUID_Map.find(Element);

			if (Iter != this->m_Element_TO_GUID_Map.end()) {
				this->m_GUID_To_Element_Map.erase(Iter->second);
				this->m_Element_TO_GUID_Map.erase(Iter);
			}
		}

		const  vector<size_t> Get_Allocated_GUD(void) {
			vector<size_t> GUIDs{};
			GUIDs.reserve(this->m_GUID_To_Element_Map.size());
			for (const auto& Pair : this->m_GUID_To_Element_Map)
				GUIDs.push_back(Pair.first);

			return GUIDs;
		}

		void Clear(void) {
			this->m_Element_TO_GUID_Map.clear();
			this->m_GUID_To_Element_Map.clear();
		}
	private:
		unordered_map<T, size_t> m_Element_TO_GUID_Map;
		unordered_map<size_t, T> m_GUID_To_Element_Map;

	};
}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System