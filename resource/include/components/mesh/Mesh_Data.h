#pragma once

#include "meta/reflection/Reflection_Macro.h"

#include<vector>
#include<string>

#include "math/Vector2.h"
#include "math/Vector3.h"
#include "math/Vector4.h"
#include "file/File_System.h"

namespace NameSpace_Resource::NameSpace_Components {

	using std::vector;
	using std::string;

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
		Vector3 m_Bitangent{ Vector3::UNIT_Y };
		Vector2 m_Texture_Coordinate{ Vector2::ZERO };

	};

	REFLECTION_HEADER(Meah_SkeletonBinding);
	REFLECTION_CLASS(Meah_SkeletonBinding, All)
	{
		REFLECTION_BODY(Meah_SkeletonBinding);
	public:
		Meah_SkeletonBinding(void) = default;

		~Meah_SkeletonBinding(void) = default;
	private:
		vector<int> m_Bone_Indices{ -1,-1,-1,-1 };
		Vector4 m_Weights{ Vector4::ZERO };
		
	};

	REFLECTION_HEADER(Mesh_Data);
	REFLECTION_CLASS(Mesh_Data, All)
	{
		REFLECTION_BODY(Mesh_Data);
	public:
		Mesh_Data(void) = default;

		~Mesh_Data(void) = default;

	private:
		vector<Mesh_Vertex> m_Vertices_buffer{};
		vector<size_t> m_Indices_Buffer{};
		vector<Meah_SkeletonBinding> m_SkeletonBindings{};

	};
}// namespace NameSpace_Resource::NameSpace_Components
