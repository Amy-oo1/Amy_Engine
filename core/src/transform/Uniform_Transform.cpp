#include "transform/Uniform_Transform.h"

namespace NameSpace_Core::NameSpace_Transform {

	Uniform_Transform::Uniform_Transform(const ScaleTranslation_Transform& ScaleTranslation)
		:m_Sacle_Transform{ ScaleTranslation } {
	}

	Uniform_Transform::Uniform_Transform(const Quaternion& Rotation, const ScaleTranslation_Transform& Scale_Translation) :
		m_Rotation{ Rotation },
		m_Sacle_Transform{ Scale_Translation } {
	}

	Uniform_Transform::Uniform_Transform(const Quaternion& Rotation, float Scale, const Vector3& Translate) :
		m_Rotation{ Rotation },
		m_Sacle_Transform{ Scale,Translate } {
	}

	Uniform_Transform& Uniform_Transform::operator=(const Quaternion& Rotate) {
		return *this = Uniform_Transform{ Rotate };
	}

	Uniform_Transform& Uniform_Transform::operator=(const ScaleTranslation_Transform& ScaleTranslation) {
		return *this = Uniform_Transform{ ScaleTranslation };
	}

	bool Uniform_Transform::operator==(const Uniform_Transform& R_HS) const {
		return this->m_Rotation.Is_Equivalence_Rotate(R_HS.m_Rotation) &&
			this->m_Sacle_Transform == R_HS.m_Sacle_Transform;
	}

	bool Uniform_Transform::operator!=(const Uniform_Transform& R_HS) const {
		return !(*this == R_HS);
	}

	const Vector3 Uniform_Transform::operator*(const Vector3& Vec3) const {
		return this->m_Rotation * (Vec3 * this->m_Sacle_Transform.Get_Scale()) +
			this->m_Sacle_Transform.Get_Translation();
	}

	const Quaternion Uniform_Transform::Get_Rotation(void) const {
		return this->m_Rotation;
	}

	const float Uniform_Transform::Get_Scale(void) const {
		return this->m_Sacle_Transform.Get_Scale();
	}

	const Vector3 Uniform_Transform::Get_Translation(void) const {
		return this->m_Sacle_Transform.Get_Translation();
	}

	const ScaleTranslation_Transform Uniform_Transform::Get_Scale_Translation(void) const {
		return this->m_Sacle_Transform;
	}

	const Matrix4x4 Uniform_Transform::Get_Matrix4x4(void) const {
		return this->m_Sacle_Transform.Get_Matrix4x4() * this->m_Rotation.Get_Rotation_Matrix4x4();
	}

	void Uniform_Transform::Set_Rotation(const Quaternion& Rotation) {
		this->m_Rotation = Rotation;
	}

	void Uniform_Transform::Set_Scale(float Scale) {
		this->m_Sacle_Transform.Set_Scale(Scale);
	}

	void Uniform_Transform::Set_Translation(const Vector3& Translate) {
		this->m_Sacle_Transform.Set_Translation(Translate);
	}

	void Uniform_Transform::Set_Scale_Translation(const ScaleTranslation_Transform& Scale_Translation) {
		this->m_Sacle_Transform = Scale_Translation;
	}

	bool Uniform_Transform::Has_Rotation(void) const {
		return this->m_Rotation != Quaternion::IDENTITY;
	}

	bool Uniform_Transform::Has_Scale(void) const {
		return this->m_Sacle_Transform.Has_Scale();
	}

	bool Uniform_Transform::Has_Negative_Scale(void) const {
		return this->m_Sacle_Transform.Has_Negative_Scale();
	}

	bool Uniform_Transform::Has_Tranlation(void) const {
		return this->m_Sacle_Transform.Has_Tranlation();
	}

	const Uniform_Transform Uniform_Transform::Generate_Rotation_X(const Radian& Angle) {
		return Uniform_Transform::Generate_Rotation(Vector3::UNIT_X, Angle);
	}

	const Uniform_Transform Uniform_Transform::Generate_Rotation_Y(const Radian& Angle) {
		return Uniform_Transform::Generate_Rotation(Vector3::UNIT_Y, Angle);
	}

	const Uniform_Transform Uniform_Transform::Generate_Rotation_Z(const Radian& Angle) {
		return Uniform_Transform::Generate_Rotation(Vector3::UNIT_Z, Angle);
	}

	const Uniform_Transform Uniform_Transform::Generate_Rotation(const Vector3& Axis, const Radian& Angle) {
		return Uniform_Transform{ Quaternion{Axis, Angle} };
	}

	const Uniform_Transform Uniform_Transform::Generate_Rotation(const Quaternion& Rotate_Quaternion) {
		return Uniform_Transform{ Rotate_Quaternion };
	}

	const Uniform_Transform Uniform_Transform::Generate_Scale(float Scale) {
		return Uniform_Transform{ ScaleTranslation_Transform{ Scale } };
	}

	const Uniform_Transform Uniform_Transform::Generate_Translation(const Vector3& Translate) {
		return Uniform_Transform{ ScaleTranslation_Transform{Translate} };
	}

	const Uniform_Transform Uniform_Transform::IDENTITY{};

}// namespace NameSpace_Core::NameSpace_Transform