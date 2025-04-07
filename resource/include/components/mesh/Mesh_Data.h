#pragma once

#include "meta/reflection/Reflection_Macro.h"

#include<cstdint>
#include<string>
#include<array>
#include<vector>
#include<memory>

#include "math/Vector2.h"
#include "math/Vector3.h"
#include "math/Vector4.h"
#include "file/File_System.h"

namespace NameSpace_Resource::NameSpace_Components {

	using std::string;
	using std::array;
	using std::vector;
	using std::shared_ptr;

	using NameSpace_Core::NameSpace_Math::Vector2;
	using NameSpace_Core::NameSpace_Math::Vector3;
	using NameSpace_Core::NameSpace_Math::Vector4;
	using NameSpace_Platform::NameSpace_File::path;

	REFLECTION_HEADER(Mesh_Vertex);
	REFLECTION_CLASS(Mesh_Vertex, All)
	{
		REFLECTION_BODY(Mesh_Vertex);
	public:
		Mesh_Vertex(void) = default;

		~Mesh_Vertex(void) = default;

	private:
		Vector3 m_Position{ Vector3::ZERO };
		Vector3 m_Normal{ Vector3::UNIT_Z };
		Vector3 m_Tangent{ Vector3::UNIT_X };
		//Vector3 m_Bitangent{ Vector3::UNIT_Y };
		Vector2 m_Texture_Coordinates{};

	};

	REFLECTION_HEADER(Meah_Skeleton_Binding);
	REFLECTION_CLASS(Meah_Skeleton_Binding, All)
	{
		REFLECTION_BODY(Meah_Skeleton_Binding);
	public:
		Meah_Skeleton_Binding(void) = default;

		~Meah_Skeleton_Binding(void) = default;
	private:
		size_t m_Index_0{ 0 };
		size_t m_Index_1{ 0 };
		size_t m_Index_2{ 0 };
		size_t m_Index_3{ 0 };

		float m_Weight_0{ 0.f };
		float m_Weight_1{ 0.f };
		float m_Weight_2{ 0.f };
		float m_Weight_3{ 0.f };
	};

	REFLECTION_HEADER(Mesh_Data);
	REFLECTION_CLASS(Mesh_Data, All)
	{
		REFLECTION_BODY(Mesh_Data);
	public:
		Mesh_Data(void) = default;

		~Mesh_Data(void) = default;

	private:
		vector<shared_ptr<Mesh_Vertex>> m_Vertices_Buffer{};
		vector<size_t> m_Indices_Buffer{};
		vector<shared_ptr<Meah_Skeleton_Binding>> m_Skeleton_Bindings{};

	};
}// namespace NameSpace_Resource::NameSpace_Components
