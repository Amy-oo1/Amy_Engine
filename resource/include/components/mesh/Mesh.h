#pragma once

#include<vector>
#include<string>

#include "meta/reflection/Reflection_Macro.h"

#include "file/File_System.h"
#include "transform/Affine_Transform.h"

namespace NameSpace_Resource::NameSpace_Components {

	using std::vector;
	using std::string;

	using NameSpace_Core::NameSpace_Transform::Affine_Transform;

	using  NameSpace_Platform::NameSpace_File::path;

	REFLECTION_HEADER(Mesh_Sub);
	REFLECTION_CLASS(Mesh_Sub, All) final
	{
		REFLECTION_BODY(Mesh_Sub);
	public:
		Mesh_Sub(void) = default;

		~Mesh_Sub(void) = default;

	private:
		path m_Object_Path{};
		Affine_Transform m_Transform{ Affine_Transform::IDENTITY };
		string m_Material{};

	};

	REFLECTION_HEADER(Mesh);
	REFLECTION_CLASS(Mesh, All) final
	{
		REFLECTION_BODY(Mesh);
	public:
		Mesh(void) = default;

		~Mesh(void) = default;

	private:
		vector<Mesh_Sub> m_Meshes{};

	};

}// namespace NameSpace_Resource::NameSpace_Components