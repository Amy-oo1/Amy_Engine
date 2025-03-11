#pragma once

#include<string>
#include<vector>
#include<memory>

#include "math/Matrix4x4.h"
#include "math/Quaternion.h"
#include "transform/Affine_Transform.h"

#include "components/skeleton/Skeleton_Data.h"


namespace NameSpace_Function::NameSpace_Animation {

	using std::string;
	using std::vector;
	using std::weak_ptr;
	using std::shared_ptr;

	using NameSpace_Core::NameSpace_Math::Matrix4x4;
	using NameSpace_Core::NameSpace_Math::Quaternion;
	using NameSpace_Core::NameSpace_Transform::Affine_Transform;
	using NameSpace_Resource::NameSpace_Components::Bone_Raw;

	class Bone final : public std::enable_shared_from_this<Bone> {
		enum class Transform_Space {
			//NOTE : Transform is relative to the local space
			LOCAL,
			//NOTE : Transform is relative to the parent space
			Parent,
			//NOTE : Transform is relative to object space
			Model,
		};

	public:
		Bone(void) = default;

		Bone(const Bone&) = default;
		Bone(Bone&&) = default;

		Bone& operator=(const Bone&) = default;
		Bone& operator=(Bone&&) = default;

		Bone(shared_ptr<Bone_Raw> Definition, shared_ptr<Bone> Parent_Bone);

		~Bone(void) = default;

	public:
		shared_ptr<Bone> Get_Parent(void) const;

		shared_ptr<Bone_Raw> Get_Definition(void) const;

		const Affine_Transform& Get_Transform(void);

		const Affine_Transform& Get_Derived_Transform(void);

		void Set_Transform(const Affine_Transform& Transform);

		void Reset_To_Binding_Pose(void);

		void UpData_Derived_Transform(void);

		bool Is_Dirty(void) const;

	private:
		void Set_Parent(const shared_ptr<Bone>& parent);

	public:
		weak_ptr<Bone> m_Parent_Bone{};

		shared_ptr<Bone_Raw> m_Definition{};

		Affine_Transform m_Transform{ Affine_Transform::IDENTITY };
		Affine_Transform m_Derived_Transform{ Affine_Transform::IDENTITY };

		bool m_Is_Dirty{ true };

	};

}// namespace NameSpace_Resource::NameSpace_Animation
