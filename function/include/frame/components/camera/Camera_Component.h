#pragma once

#include<cstdint>
#include<memory>

#include "meta/reflection/Reflection_Macro.h"

#include "math/Vector3.h"

#include "components/camera/Camera.h"

#include "frame/components/Component.h"

namespace NameSpace_Function::Namespace_Frame::NameSpace_Components::NameSpace_Camera {

	using std::shared_ptr;
	using std::weak_ptr;

	using NameSpace_Core::NameSpace_Math::Vector3;

	using NameSpace_Resource::NameSpace_Components::Camera_Resource;

	enum class CAMERA_MODE :uint32_t {
		THIRD_PERSION,
		FIRST_PERSOON,
		FREE,
		INVALID
	};

	REFLECTION_HEADER(Camera_Component);
	REFLECTION_CLASS(Camera_Component, All) final :public Component
	{
		REFLECTION_BODY(Camera_Component)
	public:
		Camera_Component(void) = default;

		virtual ~Camera_Component(void) = default;

	public:
		void Post_Load_Resource(weak_ptr<GObject> Parent_Object)override;

		void Tick(float Delta_Time)override;

	private:
		META(Disable)
		CAMERA_MODE m_Camera_Mode{ CAMERA_MODE::INVALID };
		shared_ptr<Camera_Resource> m_Camera_Resource{};

		Vector3 m_Position{ Vector3::ZERO };

		Vector3 m_Forward{ -Vector3::UNIT_Y };
		Vector3 m_Up{ Vector3::UNIT_Z };
		Vector3 m_Right{ Vector3::UNIT_X };

	};


}// namespace NameSpace_Function::Namespace_Frame::NameSpace_Components::NameSpace_Transform