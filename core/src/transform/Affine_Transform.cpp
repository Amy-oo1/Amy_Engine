#include "transform/Affine_Transform.h"

namespace NameSpace_Core::NameSpace_Transform {

	Affine_Tranform::Affine_Tranform(const Matrix3x3& Basis, const Vector3 Translate) :
		m_Basis{ Basis },
		m_Translation{ Translate } {
	}

	Affine_Tranform::Affine_Tranform(const Quaternion& Rotate_Quaternion, const Vector3& Translate_Vector3) :
		m_Basis{ Rotate_Quaternion.Get_Rotation_Matrix3x3() },
		m_Translation{ Translate_Vector3 } {
	}

	Affine_Tranform::Affine_Tranform(const Vector3& Translate_Vector3)
		:m_Translation{ Translate_Vector3 } {
	}

	Affine_Tranform::Affine_Tranform(float Scale_X, float Scale_Y, float Scale_Z, const Vector3& Translate) :
		m_Basis{ Vector3::UNIT_X * Scale_X,Vector3::UNIT_Y * Scale_Y,Vector3::UNIT_Z * Scale_Z },
		m_Translation{ Translate } {
	}

	Affine_Tranform::Affine_Tranform(const Orthogonal_Transform& Temp_Orthogonal_Transform) :
		m_Basis{ Temp_Orthogonal_Transform.Get_Rotation().Get_Rotation_Matrix3x3() },
		m_Translation{ Temp_Orthogonal_Transform.Get_Translation() } {
	}

	Affine_Tranform::Affine_Tranform(const Uniform_Transform& Temp_Unifom_Transform)
		:m_Basis{ Temp_Unifom_Transform.Get_Matrix4x4().Get_LeftTop_Matrix3x3() }
		, m_Translation{ Temp_Unifom_Transform.Get_Translation() } {
	}

	Affine_Tranform& Affine_Tranform::operator=(const Quaternion& Rotate_Quaternion) {
		return *this = Affine_Tranform{ Rotate_Quaternion };
	}

	Affine_Tranform& Affine_Tranform::operator=(const Vector3& Translate_Vector3) {
		return *this = Affine_Tranform{ Translate_Vector3 };
	}

	Affine_Tranform& Affine_Tranform::operator=(const Orthogonal_Transform& Temp_Orthogonal_Transform) {
		return *this = Affine_Tranform{ Temp_Orthogonal_Transform };
	}

	Affine_Tranform& Affine_Tranform::operator=(const Uniform_Transform& Temp_Unifom_Transform) {
		return *this = Affine_Tranform{ Temp_Unifom_Transform };
	}

	Affine_Tranform::operator Matrix4x4(void) const {
		return Matrix4x4{
			Vector4{this->m_Basis[0],this->m_Translation[0]},
			Vector4{this->m_Basis[1],this->m_Translation[1]},
			Vector4{this->m_Basis[2],this->m_Translation[2]},
			Vector4::UNIT_W
		};
	}

	bool Affine_Tranform::operator==(const Affine_Tranform& R_HS) const {
		return
			this->m_Basis == R_HS.m_Basis &&
			this->m_Translation == R_HS.m_Translation;
	}

	bool Affine_Tranform::operator!=(const Affine_Tranform& R_HS) const {
		return !(*this == R_HS);
	}

	const Affine_Tranform Affine_Tranform::operator*(const Affine_Tranform& R_HS) const {
		return Affine_Tranform{
			this->m_Basis * R_HS.m_Basis,
			this->m_Basis * R_HS.m_Translation + this->m_Translation
		};
	}

	const Vector3 Affine_Tranform::operator*(const Vector3& Vec3) const {
		return this->m_Basis * Vec3 + this->m_Translation;
	}

	const Vector4 Affine_Tranform::operator*(const Vector4& Vec4) const {
		return
			Vector4{ this->m_Basis * Vec4.Get_XYZ(),0.f } +
			Vector4{ this->m_Translation,1.f }*Vec4.Get_W();
	}

	const Vector3 Affine_Tranform::Get_X(void) const {
		return this->m_Basis.Get_Row(0);
	}

	const Vector3 Affine_Tranform::Get_Y(void) const {
		return this->m_Basis.Get_Row(1);
	}

	const Vector3 Affine_Tranform::Get_Z(void) const {
		return this->m_Basis.Get_Row(2);
	}

	const Matrix3x3 Affine_Tranform::Get_Basis(void) const {
		return this->m_Basis;
	}

	const Vector3 Affine_Tranform::Get_Translation(void) const {
		return this->m_Translation;
	}

	void Affine_Tranform::Set_X(const Vector3& X) {
		this->m_Basis.Set_Row(0, X);
	}

	void Affine_Tranform::Set_Y(const Vector3& Y) {
		this->m_Basis.Set_Row(1, Y);
	}

	void Affine_Tranform::Set_Z(const Vector3& Z) {
		this->m_Basis.Set_Row(2, Z);
	}

	void Affine_Tranform::Set_Basis(const Matrix3x3& Basis) {
		this->m_Basis = Basis;
	}

	void Affine_Tranform::Set_Translation(const Vector3& Translation) {
		this->m_Translation = Translation;
	}

	bool Affine_Tranform::Has_Rotation(void) const {
		return
			!this->m_Basis.Is_Singular() &&
			this->m_Basis * this->m_Basis.Inverse() == Matrix3x3::IDENTITY;
	}

	bool Affine_Tranform::Has_Scale(void) const {
		return
			!this->m_Basis.Get_Column(0).Is_Unit() ||
			!this->m_Basis.Get_Column(1).Is_Unit() ||
			!this->m_Basis.Get_Column(2).Is_Unit();
	}

	bool Affine_Tranform::Has_Negative_Scale(void) const {
		return this->m_Basis.Determinant() < 0.f;
	}

	bool Affine_Tranform::Has_Translation(void) const {
		return this->m_Translation != Vector3::ZERO;
	}

	const Affine_Tranform Affine_Tranform::Generate_Rotation_X(const Radian& Angle) {
		return Affine_Tranform::Generate_Rotation(Vector3::UNIT_X, Angle);
	}

	const Affine_Tranform Affine_Tranform::Generate_Rotation_Y(const Radian& Angle) {
		return Affine_Tranform::Generate_Rotation(Vector3::UNIT_Y, Angle);
	}

	const Affine_Tranform Affine_Tranform::Generate_Rotation_Z(const Radian& Angle) {
		return Affine_Tranform::Generate_Rotation(Vector3::UNIT_Z, Angle);
	}

	const Affine_Tranform Affine_Tranform::Generate_Rotation(const Vector3& Axis, const Radian& Angle) {
		return Affine_Tranform{ Quaternion{Axis,Angle} };
	}

	const Affine_Tranform Affine_Tranform::Generate_Rotation(const Quaternion& Rotate_Quaternion) {
		return Affine_Tranform{ Rotate_Quaternion };
	}

	const Affine_Tranform Affine_Tranform::Generate_Scale(const Vector3& Not_Uniform_Scales) {
		return Affine_Tranform{ Not_Uniform_Scales.Get_X(),Not_Uniform_Scales.Get_Y(),Not_Uniform_Scales.Get_Z() };
	}

	const Affine_Tranform Affine_Tranform::Generate_Scale(float Uniform_Scale) {
		return Affine_Tranform{ Vector3{Uniform_Scale} };
	}

	const Affine_Tranform Affine_Tranform::Generate_Translation(const Vector3& Translate_Vector3) {
		return Affine_Tranform{ Translate_Vector3 };
	}

	const Affine_Tranform Affine_Tranform::IDENTITY{};

} // namespace NameSpace_Core::NameSpace_Transform