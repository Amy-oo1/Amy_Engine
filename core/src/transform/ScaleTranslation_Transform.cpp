#include "transform/ScaleTranslation_Transform.h"

namespace NameSpace_Core::NameSpace_Transform {

	NameSpace_Core::NameSpace_Transform::ScaleTranslation_Transform::ScaleTranslation_Transform(float Scale, const Vector3& Tranlste)
		:m_Scale_Translation{ Tranlste,Scale } {
	}

	ScaleTranslation_Transform::ScaleTranslation_Transform(const Vector3& Tranlste)
		:m_Scale_Translation{ Tranlste,1.f } {
	}

	bool ScaleTranslation_Transform::operator==(const ScaleTranslation_Transform& R_HS) const {
		return this->m_Scale_Translation == R_HS.m_Scale_Translation;
	}

	bool ScaleTranslation_Transform::operator!=(const ScaleTranslation_Transform& R_HS) const {
		return !(*this == R_HS);
	}

	const Vector3 ScaleTranslation_Transform::Get_Translation(void) const {
		return this->m_Scale_Translation.Get_XYZ();
	}

	float ScaleTranslation_Transform::Get_Scale(void) const {
		return this->m_Scale_Translation.Get_W();
	}

	void ScaleTranslation_Transform::Set_Translation(const Vector3& Translate) {
		this->m_Scale_Translation.Set_XYZ(Translate);
	}

	void ScaleTranslation_Transform::Set_Translation(float X, float Y, float Z) {
		this->m_Scale_Translation.Set_XYZ(Vector3{ X,Y,Z });
	}

	const Matrix4x4 ScaleTranslation_Transform::Get_Matrix4x4(void) const {
		return Matrix4x4{
			Vector4{ Vector3::UNIT_X * this->m_Scale_Translation.Get_W(),this->m_Scale_Translation.Get_X()},
			Vector4{ Vector3::UNIT_Y * this->m_Scale_Translation.Get_W(),this->m_Scale_Translation.Get_Y()},
			Vector4{ Vector3::UNIT_Z * this->m_Scale_Translation.Get_W(),this->m_Scale_Translation.Get_Z()},
			Vector4::UNIT_W
		};
	}

	void ScaleTranslation_Transform::Set_Scale(float Scale) {
		return this->m_Scale_Translation.Set_W(Scale);
	}

	bool ScaleTranslation_Transform::Has_Scale(void) const {
		return !NameSpace_Math::NameSpace_Utilities::Real_Equal(this->m_Scale_Translation.Get_W(), 1.f);
	}

	bool ScaleTranslation_Transform::Has_Negative_Scale(void) const {
		return this->m_Scale_Translation.Get_W() < 0.f;
	}

	bool ScaleTranslation_Transform::Has_Tranlation(void) const {
		return this->m_Scale_Translation.Get_XYZ() != Vector3::ZERO;
	}

	const ScaleTranslation_Transform ScaleTranslation_Transform::Generate_Scale(float Scale) {
		return ScaleTranslation_Transform{ Scale };
	}

	const ScaleTranslation_Transform ScaleTranslation_Transform::Generate_Translation(const Vector3& Translate) {
		return ScaleTranslation_Transform{ Translate };
	}

	const ScaleTranslation_Transform ScaleTranslation_Transform::IDENTITY{};

}// namespace NameSpace_Core::NameSpace_Transform