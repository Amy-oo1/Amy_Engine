#include "transform/Orthogonal_Transform.h"

namespace NameSpace_Core::NameSpace_Transform {

	Orthogonal_Transform::Orthogonal_Transform(const Quaternion& Rotate_Quaternion, const Vector3& Translate) :
		m_Rotation{ Rotate_Quaternion },
		m_Translation{ Translate } {
	}

	Orthogonal_Transform::Orthogonal_Transform(const Vector3& Translate_Vector3)
		:m_Translation{ Translate_Vector3 } {
	}

	const Orthogonal_Transform& Orthogonal_Transform::operator=(const Quaternion& Rotate_Quaternion) {
		return (*this) = Orthogonal_Transform{ Rotate_Quaternion };
	}

	const Orthogonal_Transform& Orthogonal_Transform::operator=(const Vector3& Translate) {
		return (*this) = Orthogonal_Transform{ Translate };
	}

	const Orthogonal_Transform Orthogonal_Transform::operator~(void) const {
		return Orthogonal_Transform{
			~this->m_Rotation,
			~this->m_Rotation * (-this->m_Translation)
		};
	}

	bool Orthogonal_Transform::operator==(const Orthogonal_Transform& R_HS) const {
		return  this->m_Rotation.Is_Equivalence_Rotate(R_HS.m_Rotation) &&
			this->m_Translation == R_HS.m_Translation;
	}

	bool Orthogonal_Transform::operator!=(const Orthogonal_Transform& RHS) const {
		return !(*this == RHS);
	}

	const Orthogonal_Transform Orthogonal_Transform::operator*(const Orthogonal_Transform& R_HS) const {
		return Orthogonal_Transform{
			this->m_Rotation * R_HS.m_Rotation,
			this->m_Rotation * R_HS.m_Translation + this->m_Translation
		};
	}

	const Vector3 Orthogonal_Transform::operator*(const Vector3& Vec3) const {
		return this->m_Rotation * Vec3 + this->m_Translation;
	}

	const Vector4 Orthogonal_Transform::operator*(const Vector4& Vec4) const {
		return
			Vector4{ this->m_Rotation * Vec4.Get_XYZ(),0.f } +
			Vector4{ this->m_Translation,1.f }*Vec4.Get_W();
	}

	const Quaternion Orthogonal_Transform::Get_Rotation(void) const {
		return this->m_Rotation;
	}

	const Vector3 Orthogonal_Transform::Get_Translation(void) const {
		return this->m_Translation;
	}

	void Orthogonal_Transform::Set_Rotation(const Quaternion& Rotate_Quaternion) {
		this->m_Rotation = Rotate_Quaternion;
	}

	void Orthogonal_Transform::Set_Translation(const Vector3& Translate) {
		this->m_Translation = Translate;
	}

	bool Orthogonal_Transform::Has_Rotation(void) const {
		return this->m_Rotation != Quaternion::IDENTITY;
	}

	bool Orthogonal_Transform::Has_Translation(void) const {
		return this->m_Translation != Vector3::ZERO;
	}

	const Matrix4x4 Orthogonal_Transform::Get_Matrix4x4(void) const {
		Matrix4x4 Temp_Matrix4x4{ this->m_Rotation.Get_Rotation_Matrix4x4() };
		Temp_Matrix4x4.Set_Column(3, Vector4{ this->m_Translation,1.f });

		return Temp_Matrix4x4;
	}

	const Orthogonal_Transform Orthogonal_Transform::Generate_Rotation_X(const Radian& Angle) {
		return Orthogonal_Transform::Generate_Rotation(Vector3::UNIT_X, Angle);
	}

	const Orthogonal_Transform Orthogonal_Transform::Generate_Rotation_Y(const Radian& Angle) {
		return Orthogonal_Transform::Generate_Rotation(Vector3::UNIT_Y, Angle);
	}

	const Orthogonal_Transform Orthogonal_Transform::Generate_Rotation_Z(const Radian& Angle) {
		return Orthogonal_Transform::Generate_Rotation(Vector3::UNIT_Z, Angle);
	}

	const Orthogonal_Transform Orthogonal_Transform::Generate_Rotation(const Vector3& Axis, const Radian& Angle) {
		return Orthogonal_Transform{ Quaternion {Axis,Angle} };
	}

	const Orthogonal_Transform Orthogonal_Transform::Generate_Rotation(const Quaternion& Rotate_Quaternion) {
		return Orthogonal_Transform{ Rotate_Quaternion };
	}

	const Orthogonal_Transform Orthogonal_Transform::Generate_Translation(const Vector3& Translate) {
		return Orthogonal_Transform{ Translate };
	}

	const Orthogonal_Transform Orthogonal_Transform::IDENTITY{};

}// NameSpace_Core::NameSpace_Transform