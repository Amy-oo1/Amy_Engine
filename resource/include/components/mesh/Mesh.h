#pragma once

#include<vector>
#include<string>
#include<memory>

#include "meta/reflection/Reflection_Macro.h"

#include "file/File_System.h"
#include "transform/Affine_Transform.h"

namespace NameSpace_Resource::NameSpace_Components {

	using std::vector;
	using std::string;
	using std::shared_ptr;

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
		path m_OBJ_URL{};
		Affine_Transform m_Transform{ Affine_Transform::IDENTITY };
		path m_Material_URL{};

	};

	REFLECTION_HEADER(Mesh_Resource);
	REFLECTION_CLASS(Mesh_Resource, All) final
	{
		REFLECTION_BODY(Mesh_Resource);
	public:
		Mesh_Resource(void) = default;

		~Mesh_Resource(void) = default;

	private:
		vector<shared_ptr<Mesh_Sub>> m_Sub_Meshes{};

	};

}// namespace NameSpace_Resource::NameSpace_Components