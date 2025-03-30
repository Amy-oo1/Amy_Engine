#pragma once

#include<cstddef>
#include<limits>
#include<atomic>

namespace NameSpace_Function::NameSpace_Frame::NameSpace_GObject {

	using GObject_ID = std::size_t;

	class GObject_ID_Allocator final {
	private:
		GObject_ID_Allocator(void) = delete;

	public:
		~GObject_ID_Allocator(void) = default;

	public:
		static GObject_ID Alloc(void);

	public:
		static constexpr GObject_ID INVALID_GOBJECT_ID{ std::numeric_limits<GObject_ID>::max() };

	private:
		static inline std::atomic<GObject_ID> m_Next_ID{ 0 };

	};

}// namespace NameSpace_Function::NameSpace_Frame::NameSpace_GObject