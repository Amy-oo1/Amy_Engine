#pragma once

#include<cstdint>
#include<string>
#include<array>

#include "math/Vector2.h"
#include "math/Vector3.h"
#include "math/Vector4.h"
#include "color/Color.h"

#include "rhi/empty_rhi/RHI_Struct.h"

namespace NameSpace_Render::NameSpace_Debug_Draw {

	using std::array;

	using NameSpace_Core::NameSpace_Math::Vector2;
	using NameSpace_Core::NameSpace_Math::Vector3;
	using NameSpace_Core::NameSpace_Math::Vector4;
	using NameSpace_Core::NameSpace_Color::Color;

	
	using NameSpace_RHI::RHI_Vertex_Input_Binding_Description;
	using NameSpace_RHI::RHI_Vertex_Input_Attribute_Description;


	static constexpr float g_Debug_Draw_Infinity_Time{ -2.f };
	static constexpr float g_Debug_Draw_One_Frame{ 0.f };

	enum class DEBUG_DRAW_TIME_TYPE : uint32_t {
		DEBUG_DRAW_TIME_TYPE_INFINTY = 0,
		DEBUG_DRAW_TIME_TYPE_ONE_FRAME = 1,
		DEBUG_DRAW_TIME_TYPE_COMMON = 2
	};

	enum class DEBUG_DRAW_PRIMITIVE_TYPE : uint32_t {
		DEBUG_DRAW_PRIMITIVE_TYPE_POINT = 0,
		DEBUG_DRAW_PRIMITIVE_TYPE_LINE = 1,
		DEBUG_DRAW_PRIMITIVE_TYPE_TRIANGLE = 2,
		DEBUG_DRAW_PRIMITIVE_TYPE_QUAD = 3,
		DEBUG_DRAW_PRIMITIVE_TYPE_DRAW_BOX = 4,
		DEBUG_DRAW_PRIMITIVE_TYPE_DRAW_CYLINDER = 5,
		DEBUG_DRAW_PRIMITIVE_TYPE_DRAW_SPHERE = 6,
		DEBUG_DRAW_PRIMITIVE_TYPE_DRAW_SPHERE = 7,
		DEBUG_DRAW_PRIMITIVE_TYPE_DRAW_CAPSULE = 8,
		DEBUG_DRAW_PRIMITIVE_TYPE_DRAW_TEXT = 9,
		DEBUG_DRAW_PRIMITIVE_TYPE_DRAW_CONE = 10,
	};

	enum class FILL_MODE :uint32_t {
		FILL_MODE_SOLID = 0,
		FILL_MODE_WIREFRAME = 1,
		FILE_MODE_COUNT = 2
	};

	struct Debug_Draw_Vertex final {
		Vector3 Pos;
		Color Col;
		Vector2 Tex_Coord;

		static const array<RHI_Vertex_Input_Binding_Description, 1> Get_Binding_Description(void);

		static const array< RHI_Vertex_Input_Attribute_Description, 3> Get_ATtribute_Descriptions(void);

	};

	class Debug_Draw_Primitive {
	public:
		bool Is_Time_Out(float Delta_Time);
		void Set_Time(float In_Life_Time);

	public:
		DEBUG_DRAW_TIME_TYPE m_Time_Type = DEBUG_DRAW_TIME_TYPE::DEBUG_DRAW_TIME_TYPE_INFINTY;

		float m_Life_Time = g_Debug_Draw_Life_Time;

		FILL_MODE m_Fill_Mode = FILL_MODE::FILL_MODE_WIREFRAME;

		bool m_Depth_Test = true;

	private:
		bool m_Rendered = false;

	};

	class Debug_Draw_Point final :public Debug_Draw_Primitive {
	public:
		Debug_Draw_Vertex m_Vertex;

		static constexpr DEBUG_DRAW_PRIMITIVE_TYPE m_Type = DEBUG_DRAW_PRIMITIVE_TYPE::DEBUG_DRAW_PRIMITIVE_TYPE_POINT;
	};

	class Debug_Draw_Line final :public Debug_Draw_Primitive {
	public:
		array<Debug_Draw_Vertex, 2> m_Vertex;
		static constexpr DEBUG_DRAW_PRIMITIVE_TYPE m_Type = DEBUG_DRAW_PRIMITIVE_TYPE::DEBUG_DRAW_PRIMITIVE_TYPE_LINE;
	};

	class Debug_Draw_Triangle final :public Debug_Draw_Primitive {
	public:
		array<Debug_Draw_Vertex, 3> m_Vertex;
		static constexpr DEBUG_DRAW_PRIMITIVE_TYPE m_Type = DEBUG_DRAW_PRIMITIVE_TYPE::DEBUG_DRAW_PRIMITIVE_TYPE_TRIANGLE;
	};

	class Debug_Draw_Quad final :public Debug_Draw_Primitive {
	public:
		array<Debug_Draw_Vertex, 4> m_Vertex;

		static constexpr DEBUG_DRAW_PRIMITIVE_TYPE m_Type = DEBUG_DRAW_PRIMITIVE_TYPE::DEBUG_DRAW_PRIMITIVE_TYPE_QUAD;
	};

	class Debug_Draw_Box final :public Debug_Draw_Primitive {
	public:
		Vector3 m_Center_Pos;
		Vector3 m_Half_Extents;
		Color m_Col;
		Vector4 m_Rotation;

		static constexpr DEBUG_DRAW_PRIMITIVE_TYPE m_Type = DEBUG_DRAW_PRIMITIVE_TYPE::DEBUG_DRAW_PRIMITIVE_TYPE_DRAW_BOX;
	};

	class Debug_Draw_Cylinder final :public Debug_Draw_Primitive {
	public:
		Vector3 m_Center_Pos;
		float m_Radius;
		float m_Height;
		Color m_Col;
		Vector4 m_Rotation;

		static constexpr DEBUG_DRAW_PRIMITIVE_TYPE m_Type = DEBUG_DRAW_PRIMITIVE_TYPE::DEBUG_DRAW_PRIMITIVE_TYPE_DRAW_CYLINDER;
	};

	class Debug_Draw_Sphere final :public Debug_Draw_Primitive {
	public:
		Vector3 m_Center_Pos;
		float m_Radius;
		Color m_Col;

		static constexpr DEBUG_DRAW_PRIMITIVE_TYPE m_Type = DEBUG_DRAW_PRIMITIVE_TYPE::DEBUG_DRAW_PRIMITIVE_TYPE_DRAW_SPHERE;
	};

	class Debug_Draw_Capsule final :public Debug_Draw_Primitive {
	public:
		Vector3 m_Center_Pos;
		Vector4 m_Rotation;
		Vector3 m_Scale;
		float m_Radius;
		float m_Height;
		Color m_Col;

		static constexpr DEBUG_DRAW_PRIMITIVE_TYPE m_Type = DEBUG_DRAW_PRIMITIVE_TYPE::DEBUG_DRAW_PRIMITIVE_TYPE_DRAW_CAPSULE;
	};

	class Debug_Draw_Text final :public Debug_Draw_Primitive {
	public:
		std::string m_Content;
		Color     m_Col;
		Vector3     m_Coordinate;
		int         m_Size;
		bool        m_Is_Screen_Text;

		static constexpr DEBUG_DRAW_PRIMITIVE_TYPE m_Type = DEBUG_DRAW_PRIMITIVE_TYPE::DEBUG_DRAW_PRIMITIVE_TYPE_DRAW_TEXT;
	};


}// namespace NameSpace_Render::NameSpace_Debug_Draw