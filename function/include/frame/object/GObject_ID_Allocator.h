#pragma once

#include<cstddef>
#include<limits>
#include<atomic>

namespace NameSpace_Function::Namespace_Frame::NameSpace_GObject {

	using GObject_ID = std::size_t;

	constexpr GObject_ID INVALID_GOBJECT_ID = std::numeric_limits<GObject_ID>::max();

	class GObject_ID_Allocator final {
	private:
		GObject_ID_Allocator(void) = delete;

	public:
		~GObject_ID_Allocator(void) = default;

	public:
		static GObject_ID Alloc(void);
	private:
		static std::atomic<GObject_ID> m_Next_ID;

	};

}// namespace NameSpace_Function::Namespace_Frame::NameSpace_GObject