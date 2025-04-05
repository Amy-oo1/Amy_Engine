#pragma once

#include<vector>
#include<memory>

#include "math/Vector3.h"
#include "math/Quaternion.h"
#include "transform/Affine_Transform.h"

#include "frame/object/GObject.h"
#include "frame/object/GObject_ID_Allocator.h"
#include "frame/components/Component.h"
#include "frame/components/camera/Camera_Component.h"

namespace NameSpace_Function::Namespace_Character {

	using std::vector;
	using std::shared_ptr;
	using std::weak_ptr;

	using NameSpace_Core::NameSpace_Math::Vector3;
	using NameSpace_Core::NameSpace_Math::Quaternion;
	using NameSpace_Core::NameSpace_Transform::Affine_Transform;

	using NameSpace_Frame::NameSpace_GObject::GObject;
	using NameSpace_Frame::NameSpace_GObject::GObject_ID;
	using NameSpace_Frame::NameSpace_GObject::GObject_ID_Allocator;

	using NameSpace_Frame::NameSpace_Components::NameSpace_Camera::CAMERA_MODE;
	using NameSpace_Frame::NameSpace_Components::NameSpace_Camera::Camera_Component;

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

		GObject_ID Get_Object_ID(void)const;

		void Set_Character_Object(shared_ptr<GObject> Character_Object);

		void Tick(float Delta_Time);

	private:


	private:
		static constexpr float s_Camera_Blend_Time{ 0.3f };

	private:
		Vector3 m_Position;
		Quaternion m_Rotation;

		shared_ptr<GObject> m_Character_Object;

		Quaternion m_Rotation_Buffer;
		bool m_Rotation_Dirty{ false };

		CAMERA_MODE m_Original_Camera_Mode{ CAMERA_MODE::INVALID };
	};

}// namespace NameSpace_Function::Namespace_Character