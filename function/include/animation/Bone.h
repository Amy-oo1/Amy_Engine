#pragma once

#include<string>
#include<vector>
#include<memory>

#include "math/Matrix4x4.h"
#include "math/Quaternion.h"
#include "transform/Affine_Transform.h"


namespace NameSpace_Function::NameSpace_Animation {

	using std::string;
	using std::vector;
	using std::weak_ptr;
	using std::shared_ptr;

	using NameSpace_Core::NameSpace_Math::Matrix4x4;
	using NameSpace_Core::NameSpace_Math::Quaternion;
	using NameSpace_Core::NameSpace_Transform::Affine_Transform;

	class Bone final {
		enum class Transform_Space {
			//NOTE : Transform is relative to the local space
			LOCAL,
			//NOTE : Transform is relative to the parent space
			AREN,
			//NOTE : Transform is relative to object space
			OBJECT,
		};

	public:
		Bone(void) = default;

		Bone(const Bone&) = default;
		Bone(Bone&&) = default;

		Bone& operator=(const Bone&) = default;
		Bone& operator=(Bone&&) = default;

		~Bone(void) = default;

	public:
		bool Is_Dirty(void) const;

		const string Get_Name(void) const;

		weak_ptr<Bone> Get_Parent(void) const;

		const Affine_Transform Get_Relative_Transform(void) const;

		void Set_Relative_Transform(const Affine_Transform& Temp_Affine_Transform);

		virtual void Set_Parent(const shared_ptr<Bone>& parent);

	private:
		bool m_Is_Dirty{ true };

		weak_ptr<Bone> m_Parent_Node;

		string m_Name{};

		Affine_Transform m_Relative_Transform{ Affine_Transform::IDENTITY };
		Affine_Transform m_Derived_Transform{ Affine_Transform::IDENTITY };
		Affine_Transform m_Initial_Transform{ Affine_Transform::IDENTITY };

		Matrix4x4 m_Inverse_Tpose{ Matrix4x4::IDENTITY };

	};

}// namespace NameSpace_Resource::NameSpace_Animation
