#include "math/Quaternion.h"

#include<cassert>

#include "math/Utilities.h"

namespace NameSpace_Core::NameSpace_Math {

	NameSpace_Core::NameSpace_Math::Quaternion::Quaternion(float S, float X, float Y, float Z)
		:Quaternion{ S,Vector3{X,Y,Z} } {
	}

	Quaternion::Quaternion(float Real_Part, const Vector3& Imaginary_Part)
		:m_Quat{ Real_Part,Imaginary_Part } {
	}

	Quaternion::Quaternion(const Vector3& Axis, const Radian& Angle)
		:Quaternion{ Quaternion::Generate_By_AxisAngle(Axis,Angle) } {
	}

	Quaternion::Quaternion(const Radian& Pitch, const Radian& Yaw, const Radian& Roll)
		:Quaternion{
			Quaternion{Vector3::UNIT_Y,Yaw} *
			Quaternion{Vector3::UNIT_X,Pitch}*
			Quaternion{Vector3::UNIT_Z,Roll}
		} {
	}

	Quaternion::Quaternion(const Matrix3x3& Rotation_Matrix3x3)
		:Quaternion{ Quaternion::Generate_By_RotationMatrix(Rotation_Matrix3x3) } {
	}

	Quaternion::Quaternion(const Matrix4x4& Rotation_Matrix4x4)
		:Quaternion{ Quaternion::Generate_By_RotationMatrix(Rotation_Matrix4x4) } {
	}

	Quaternion& Quaternion::operator=(const Matrix3x3& Rotation_Matrix3x3) {
		return *this = Quaternion{ Rotation_Matrix3x3 };
	}

	Quaternion& Quaternion::operator=(const Matrix4x4& Rotation_Matrix4x4) {
		return *this = Quaternion{ Rotation_Matrix4x4 };
	}

	const Quaternion Quaternion::operator+(void) const {
		return *this;
	}

	const Quaternion Quaternion::operator-(void) const {
		return Quaternion{ -this->m_Quat.first,-this->m_Quat.second };
	}

	const Quaternion Quaternion::operator~(void) const {
		return this->Conjugation();
	}

	bool Quaternion::operator==(const Quaternion& Temp_Quaternion) const {
		return NameSpace_Utilities::Real_Equal(this->m_Quat.first, Temp_Quaternion.m_Quat.first) &&
			this->m_Quat.second == Temp_Quaternion.m_Quat.second;
	}

	bool Quaternion::operator!=(const Quaternion& Temp_Quaternion) const {
		return !(*this == Temp_Quaternion);
	}

	const Quaternion Quaternion::operator+(const Quaternion& R_HS) const {
		return Quaternion{
			this->m_Quat.first + R_HS.m_Quat.first,
			this->m_Quat.second + R_HS.m_Quat.second
		};
	}

	const Quaternion Quaternion::operator-(const Quaternion& R_HS) const {
		return Quaternion{
			this->m_Quat.first - R_HS.m_Quat.first,
			this->m_Quat.second - R_HS.m_Quat.second
		};
	}

	const Quaternion Quaternion::operator*(const Quaternion& R_HS) const {
		float Sa = this->m_Quat.first, Xa = this->m_Quat.second[0], Ya = this->m_Quat.second[1], Za = this->m_Quat.second[2];
		float Sb = R_HS.m_Quat.first, Xb = R_HS.m_Quat.second[0], Yb = R_HS.m_Quat.second[1], Zb = R_HS.m_Quat.second[2];

		return Quaternion{
			Sa * Sb - Xa * Xb - Ya * Yb - Za * Zb,
			Sa * Xb + Xa * Sb + Ya * Zb - Za * Yb,
			Sa * Yb + Ya * Sb + Za * Xb - Xa * Zb,
			Sa * Zb + Za * Sb + Xa * Yb - Ya * Xb
		};
	}

	const Quaternion Quaternion::operator*(float R_HS) const {
		return Quaternion{
			this->m_Quat.first * R_HS,
			this->m_Quat.second * R_HS
		};
	}

	const Quaternion operator*(float L_HS, const Quaternion& R_HS) {
		return R_HS * L_HS;
	}

	const Vector3 Quaternion::operator*(const Vector3& v) const {
		float w = this->m_Quat.first;
		Vector3 q = this->m_Quat.second;

		return Vector3{
			v +
			2.f * w * (q.Cross_Product(v)) +
			2.f * q.Cross_Product((q.Cross_Product(v)))
		};
	}

	Quaternion& Quaternion::operator+=(const Quaternion& R_HS) {
		return *this = *this + R_HS;
	}

	Quaternion& Quaternion::operator-=(const Quaternion& R_HS) {
		return *this = *this - R_HS;
	}

	Quaternion& Quaternion::operator*=(const Quaternion& R_HS) {
		return *this = (*this) * R_HS;
	}

	Quaternion& Quaternion::operator*=(float R_HS) {
		return *this = (*this) * R_HS;
	}

	const float& Quaternion::operator[](Quaternion::Index Index) const {
		assert(static_cast<size_t>(Index) < 4 && "Index Out Range");

		return static_cast<size_t>(Index) == 0 ?
			this->m_Quat.first :
			this->m_Quat.second[static_cast<size_t>(Index) - 1];
	}

	float& Quaternion::operator[](Quaternion::Index Index) {
		assert(static_cast<size_t>(Index) < 4 && "Index Out Range");

		return static_cast<size_t>(Index) == 0 ?
			this->m_Quat.first :
			this->m_Quat.second[static_cast<size_t>(Index) - 1];
	}

	float Quaternion::Length(void) const {
		return NameSpace_Utilities::Sqrt(this->Dot_Product(*this));
	}

	float Quaternion::Length_Square(void) const {
		return this->Dot_Product(*this);
	}

	bool Quaternion::Is_Equivalence_Rotate(const Quaternion& Temp_Quaternion, float Tolerance) const {
		return NameSpace_Utilities::Real_Equal(this->Dot_Product(Temp_Quaternion), 1.f, Tolerance);
	}

	const Quaternion Quaternion::Normalize(void) const {
		assert(!NameSpace_Utilities::Real_Equal(this->Length(), 0.f));

		return Quaternion{ (*this) * (1.f / this->Length()) };
	}

	Quaternion& Quaternion::To_Normalize(void) {
		return *this = this->Normalize();
	}

	const Quaternion Quaternion::Conjugation(void) const {
		return Quaternion{
			this->m_Quat.first,
			-this->m_Quat.second
		};
	}

	const Quaternion Quaternion::Inverse(void) const {
		assert(!NameSpace_Utilities::Real_Equal(this->Length(), 0.f));

		return this->Conjugation() * (1.f / this->Dot_Product(*this));
	}

	const float Quaternion::Dot_Product(const Quaternion& Temp_Quaternion) const {
		return
			this->m_Quat.first * Temp_Quaternion.m_Quat.first +
			this->m_Quat.second.Dot_Product(Temp_Quaternion.m_Quat.second);
	}

	const Matrix3x3 Quaternion::Get_Rotation_Matrix3x3(void) const {
		float
			s = this->Get_S(),
			x = this->Get_X(),
			y = this->Get_Y(),
			z = this->Get_Z();

		return Matrix3x3{
			1 - 2 * y * y - 2 * z * z,		2 * x * y - 2 * s * z,			2 * x * z + 2 * s * y,
			2 * x * y + 2 * s * z,			1 - 2 * x * x - 2 * z * z,		2 * y * z - 2 * s * x,
			2 * x * z - 2 * s * y,			2 * y * z + 2 * s * x,			1 - 2 * x * x - 2 * y * y
		};
	}

	const Matrix4x4 Quaternion::Get_Rotation_Matrix4x4(void) const {
		auto Temp_Matrix3x3 = this->Get_Rotation_Matrix3x3();

		return Matrix4x4{
			Vector4{Temp_Matrix3x3[0],0},
			Vector4{Temp_Matrix3x3[1],0},
			Vector4{Temp_Matrix3x3[2],0},
			Vector4::UNIT_W
		};
	}

	const pair<Vector3, Radian> Quaternion::Get_AxisAngle(void) const {
		assert(this->Get_Imaginary_Part().Length_Square() > 0 && "Quaternion Is Not A Rotate Quaternion");

		float Squared_Length = this->Get_Imaginary_Part().Length_Square();
		float Inverse_Length = 1.f / this->Get_Imaginary_Part().Length();

		Vector3 Axis = Vector3{
			this->Get_X() * Inverse_Length,
			this->Get_Y() * Inverse_Length,
			this->Get_Z() * Inverse_Length
		};

		Radian Angle = 2.f * NameSpace_Utilities::Acos(this->Get_S());

		return std::make_pair(Axis, Angle);
	}

	const Radian Quaternion::Get_Yaw(void) const {
		float
			S = this->m_Quat.first,
			X = this->m_Quat.second[0],
			Y = this->m_Quat.second[1],
			Z = this->m_Quat.second[2];

		return Radian{ NameSpace_Utilities::Atan2(2 * (X * Y + S * Z),1.f - 2 * (Y * Y - Z * Z)) };
	}

	const Radian Quaternion::Get_Pitch(void) const {
		float
			S = this->m_Quat.first,
			X = this->m_Quat.second[0],
			Y = this->m_Quat.second[1],
			Z = this->m_Quat.second[2];

		return Radian{ NameSpace_Utilities::Atan2(2 * (Y * Z + S * X),1.f - 2 * (X * X - Z * Z)) };
	}

	const Radian Quaternion::Get_Roll(void) const {
		float
			S = this->m_Quat.first,
			X = this->m_Quat.second[0],
			Y = this->m_Quat.second[1],
			Z = this->m_Quat.second[2];

		return Radian{ NameSpace_Utilities::Atan2(2 * (X * Z + S * Y),1.f - 2 * (X * X + Y * Y)) };
	}

	float Quaternion::Get_S(void) const {
		return this->m_Quat.first;
	}

	float Quaternion::Get_X(void) const {
		return this->m_Quat.second.Get_X();
	}

	float Quaternion::Get_Y(void) const {
		return this->m_Quat.second.Get_Y();
	}

	float Quaternion::Get_Z(void) const {
		return this->m_Quat.second.Get_Z();
	}

	float Quaternion::Get_Real_Part(void) const {
		return this->m_Quat.first;
	}

	const Vector3 Quaternion::Get_Imaginary_Part(void) const {
		return this->m_Quat.second;
	}

	const bool Quaternion::Is_NaN(void) const {
		return
			NameSpace_Utilities::Is_NaN(this->Get_S()) ||
			this->m_Quat.second.Is_NaN();
	}

	const Quaternion Quaternion::Generate_By_AxisAngle(const Vector3& Axis, const Radian& Angle) {
		assert(Axis.Is_Unit() && "Axis Is Not A Unit Vector");

		Radian Half_Angle = 0.5f * Angle;
		return Quaternion{
			NameSpace_Utilities::Cos(Half_Angle),
			Axis * NameSpace_Utilities::Sin(Half_Angle)
		};
	}

	const Quaternion Quaternion::Generate_By_RotationMatrix(const Matrix3x3& Rotation_Matrix3x3) {
		float Trace = Rotation_Matrix3x3.Trace();

		if (Trace > 0.f) {
			float S = NameSpace_Utilities::Sqrt(Trace + 1.f) * 0.5f;
			return Quaternion{
				S,
				(Rotation_Matrix3x3[2][1] - Rotation_Matrix3x3[1][2]) / (4.f * S),
				(Rotation_Matrix3x3[0][2] - Rotation_Matrix3x3[2][0]) / (4.f * S),
				(Rotation_Matrix3x3[1][0] - Rotation_Matrix3x3[0][1]) / (4.f * S)
			};
		}
		else {
			size_t i = 0, s_iNext[3]{ 1,2,0 };
			if (Rotation_Matrix3x3[0][0] > Rotation_Matrix3x3[1][1])
				i = 1;
			if (Rotation_Matrix3x3[2][2] > Rotation_Matrix3x3[i][i])
				i = 2;
			size_t j = s_iNext[i], k = s_iNext[j];

			float Root = NameSpace_Utilities::Sqrt(Rotation_Matrix3x3[i][i] - Rotation_Matrix3x3[j][j] - Rotation_Matrix3x3[k][k] + 1.f);

			return Quaternion{
				(Rotation_Matrix3x3[k][j] - Rotation_Matrix3x3[j][k]) / (2 * Root),
				Root * 0.5f,
				(Rotation_Matrix3x3[j][i] + Rotation_Matrix3x3[i][j]) / (2 * Root),
				(Rotation_Matrix3x3[k][i] + Rotation_Matrix3x3[i][k]) / (2 * Root)
			};
		}
	}

	const Quaternion Quaternion::Generate_By_RotationMatrix(const Matrix4x4& Rotation_Matrix4x4) {
		return Quaternion::Generate_By_RotationMatrix(Rotation_Matrix4x4.Get_LeftTop_Matrix3x3());
	}

	const Quaternion Quaternion::Normalized_Lerp(const Quaternion& P, const Quaternion& Q, float T, bool Use_Shortest_Path) {
		if (P.Dot_Product(Q) < 0.f && Use_Shortest_Path)
			return (P + T * ((-Q) - P)).Normalize();
		else
			return (P + T * (Q - P)).Normalize();
	}

	const Quaternion Quaternion::Spherical_Lerp(const Quaternion& P, const Quaternion& Q, float T, bool Use_Shortest_Path) {
		assert(!NameSpace_Utilities::Real_Equal(P.Length(), 0.f) && "zero begin");
		assert(!NameSpace_Utilities::Real_Equal(Q.Length(), 0.f) && "zero end");

		float Cos_V = P.Dot_Product(Q);
		Quaternion TQ = Q;
		if (Cos_V < 0.f && Use_Shortest_Path) {
			Cos_V = -Cos_V;
			TQ = -Q;
		}

		if (NameSpace_Utilities::Abs(Cos_V) < 1.f) {
			float Sin_V = NameSpace_Utilities::Sqrt(1.f - Cos_V * Cos_V);
			Radian Angle = NameSpace_Utilities::Atan2(Sin_V, Cos_V);

			return (NameSpace_Utilities::Sin((1.f - T) * Angle) / (1.f / Sin_V) * P
				+ NameSpace_Utilities::Sin(T * Angle) / (1.f / Sin_V) * TQ).Normalize();
		}
		else
			return ((1.f - T) * P + T * TQ).Normalize();
	}

	const Quaternion Quaternion::ZERO{};
	const Quaternion Quaternion::IDENTITY{ 1.f, Vector3::ZERO };

}// namespace NameSpace_Core::NameSpace_Math