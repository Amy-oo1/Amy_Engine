#pragma once

#include<string>
#include<vector>
#include<cstddef>

#include "meta/reflection/Reflection_Macro.h"

#include "math/Matrix4x4.h"
#include "transform/Orthogonal_Transform.h"

namespace NameSpace_Resource::NameSpace_Components {

	using std::vector;
	using std::string;

	using NameSpace_Core::NameSpace_Math::Matrix4x4;
	using NameSpace_Core::NameSpace_Transform::Orthogonal_Transform;


	REFLECTION_HEADER(Bone_Raw);
	REFLECTION_CLASS(Bone_Raw, All) final
	{
		REFLECTION_BODY(Bone_Raw);
	public:
		Bone_Raw(void) = default;

		~Bone_Raw(void) = default;

	private:
		string m_Name{};
		size_t m_CurrentIndex;
		size_t m_Parent_Index;

		Orthogonal_Transform m_Binding_Pose{ Orthogonal_Transform::IDENTITY };
		Matrix4x4 m_Tpose_Matrix{ Matrix4x4::IDENTITY };

	};

	REFLECTION_HEADER(Skeleton_Data);
	REFLECTION_CLASS(Skeleton_Data, All) final
	{
		REFLECTION_BODY(Skeleton_Data);
	public:
		Skeleton_Data(void) = default;

		~Skeleton_Data(void) = default;

	private:
		vector<Bone_Raw> m_Bones{};

		bool m_Is_Flat = false; //"bone.index" equals index in bones_map
		size_t root_index;
		bool In_Topological_Order = false; // TODO: if not in topological order, we need to topology sort in skeleton

	};

}// namespace NameSpace_Resource::NameSpace_Components