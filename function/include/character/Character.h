#pragma once

#include<vector>
#include<memory>

#include "math/Vector3.h"
#include "math/Quaternion.h"
#include "transform/Affine_Transform.h"

#include "frame/object/GObject.h"
#include "frame/compoents/camera/Camera_Component.h"

namespace NameSpace_Function::Namespace_Character {

	using std::vector;
	using std::shared_ptr;
	using std::weak_ptr;

	using NameSpace_Core::NameSpace_Math::Vector3;
	using NameSpace_Core::NameSpace_Math::Quaternion;
	using NameSpace_Core::NameSpace_Transform::Affine_Transform;

	using Namespace_Frame::NameSpace_GObject::GObject;

	using Namespace_Frame::NameSpace_Components::NameSpace_Camera::CAMERA_MODE;
	using Namespace_Frame::NameSpace_Components::NameSpace_Camera::Camera_Component;

	class Character final {
	private:
		Character(void) = delete;

		Character(const Character&) = delete;
		Character(Character&&) = delete;

		Character& operator=(const Character&) = delete;
		Character& operator=(Character&&) = delete;

	public:
		~Character(void) = default;

	public:
		Character(shared_ptr<GObject> Character_Object);


	private:


	private:
		static constexpr float s_Camera_Blend_Time{ 0.3f };

	private:
		Vector3 Position;
		Quaternion Rotation;

		shared_ptr<GObject> m_Camera_Component;

		Quaternion m_Rotation_Buffer;
		bool m_Rotation_Dirty{ false };

		CAMERA_MODE m_Original_Camera_Mode{ CAMERA_MODE::INVALID };
	};

}// namespace NameSpace_Function::Namespace_Character