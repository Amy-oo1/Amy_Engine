#pragma once

#include<malloc.h>

namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System {

	class Buffer_Data final {
	private:
		Buffer_Data(const Buffer_Data&) = delete;
		Buffer_Data& operator=(const Buffer_Data&) = delete;

	public:
		Buffer_Data(size_t Size) :
			m_Size{ Size },
			m_Data{ malloc(Size) } {
		}


		~Buffer_Data() { if (nullptr != this->m_Data) { free(this->m_Data); } }

		bool Is_Valid(void)const { return nullptr != this->m_Data; }

		size_t m_Size{ 0 };
		void* m_Data{ nullptr };

	};


}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System