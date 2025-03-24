#include "render/debug_draw/Debug_Draw_Primitive.h"

#include<cmath>
#include<algorithm>

#include "render/rhi/empty_rhi/RHI_Type.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Debug_Draw {

	using NameSpace_RHI::RHI_FORMAT;
	using NameSpace_RHI::RHI_VERTEX_INPUT_RATE;

	const array<RHI_Vertex_Input_Binding_Description, 1> Debug_Draw_Vertex::Get_Binding_Description(void) {
		array<RHI_Vertex_Input_Binding_Description, 1> Binding{};
		{
			Binding[0].Binding = 0;
			Binding[0].Stride = sizeof(Debug_Draw_Vertex);
			Binding[0].Input_Rate = RHI_VERTEX_INPUT_RATE::RHI_VERTEX_INPUT_RATE_VERTEX;
		}

		return Binding;
	}

	const array<RHI_Vertex_Input_Attribute_Description, 3> Debug_Draw_Vertex::Get_ATtribute_Descriptions(void) {
		array< RHI_Vertex_Input_Attribute_Description, 3> Attribute{}; {
			Attribute[0].Binding = 0;
			Attribute[0].Location = 0;
			Attribute[0].Format = RHI_FORMAT::RHI_FORMAT_R32G32B32_SFLOAT;
			Attribute[0].Offset = offsetof(Debug_Draw_Vertex, Pos);
			Attribute[1].Binding = 0;
			Attribute[1].Location = 1;
			Attribute[1].Format = RHI_FORMAT::RHI_FORMAT_R32G32B32A32_SFLOAT;
			Attribute[1].Offset = offsetof(Debug_Draw_Vertex, Col);
			Attribute[2].Binding = 0;
			Attribute[2].Location = 2;
			Attribute[2].Format = RHI_FORMAT::RHI_FORMAT_R32G32_SFLOAT;
			Attribute[2].Offset = offsetof(Debug_Draw_Vertex, Tex_Coord);
		}

		return Attribute;
	}

	bool Debug_Draw_Primitive::Is_Time_Out(float Delta_Time) {
		if (this->m_Time_Type == DEBUG_DRAW_TIME_TYPE::DEBUG_DRAW_TIME_TYPE_INFINTY) {
			return false;
		}
		else if (this->m_Time_Type == DEBUG_DRAW_TIME_TYPE::DEBUG_DRAW_TIME_TYPE_ONE_FRAME) {
			if (!this->m_Rendered) {
				this->m_Rendered = true;
				return false;
			}
			else
				return true;
		}
		else {
			this->m_Life_Time -= Delta_Time;
			return this->m_Life_Time <= 0.f;
		}
	}

	void Debug_Draw_Primitive::Set_Time(float In_Life_Time) {
		if (fabs(In_Life_Time - g_Debug_Draw_Infinity_Time) < 0.0001f) {
			this->m_Time_Type = DEBUG_DRAW_TIME_TYPE::DEBUG_DRAW_TIME_TYPE_INFINTY;
			this->m_Life_Time = 0.f;
		}
		else if (fabs(In_Life_Time - g_Debug_Draw_One_Frame) < 0.0001f) {
			this->m_Time_Type = DEBUG_DRAW_TIME_TYPE::DEBUG_DRAW_TIME_TYPE_ONE_FRAME;
			this->m_Life_Time = 0.03f;
		}
		else {
			this->m_Time_Type = DEBUG_DRAW_TIME_TYPE::DEBUG_DRAW_TIME_TYPE_COMMON;
			this->m_Life_Time = In_Life_Time;
		}
	}

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Debug_Draw