#include "character/Character.h"

#include "global/Global_Systemer.h"

#include "frame/components/transform/Transform_Component.h"

namespace NameSpace_Function::Namespace_Character {

	using Namespace_Global::Global_Systemer;

	using NameSpace_Frame::NameSpace_Components::NameSpace_Transform::Transform_Component;

	Character::Character(shared_ptr<GObject> Character_Object)
		:m_Character_Object{ Character_Object } {

	}

	GObject_ID Character::Get_Object_ID(void) const {
		return this->m_Character_Object ? this->m_Character_Object->Get_ID() : GObject_ID_Allocator::INVALID_GOBJECT_ID;
	}

	void Character::Set_Character_Object(shared_ptr<GObject> Character_Object) {
		this->m_Character_Object = Character_Object;
		if (Character_Object) {
			auto Transform{ Character_Object->TryGet_Component<Transform_Component>("TransformComponent") };
			const auto& Trans{ Transform->Get_Current_Transform() };

			this->m_Position = Trans.Get_Translation();
			this->m_Rotation = Trans.Get_Rotation();
		}
		else {
			this->m_Position = Vector3::ZERO;
			this->m_Rotation = Quaternion::IDENTITY;
		}
	}

	void Character::Tick(float Delta_Time) {
		if (this->m_Character_Object) {
			size_t Commmand{ Global_Systemer::Get_Instance().Main_Input->Get_Game_Command() };
			//TODO : Add Command
		}
	}

}// namespace NameSpace_Function::Namespace_Character