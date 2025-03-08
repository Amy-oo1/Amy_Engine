#pragma once

#include "math/Head_Math.h"

namespace NameSpace_Core::NameSpace_Transform {

	using NameSpace_Math::Vector3;
	using NameSpace_Math::Vector4;
	using NameSpace_Math::Matrix4x4;

	class ScaleTranslation_Transform final {
	public:
		ScaleTranslation_Transform(void) = default;

		ScaleTranslation_Transform(const ScaleTranslation_Transform&) = default;
		ScaleTranslation_Transform(ScaleTranslation_Transform&&) = default;

		ScaleTranslation_Transform& operator=(const ScaleTranslation_Transform&) = default;
		ScaleTranslation_Transform& operator=(ScaleTranslation_Transform&&) = default;

		explicit ScaleTranslation_Transform(float Scale, const Vector3& Tranlste = Vector3::ZERO);
		explicit ScaleTranslation_Transform(const Vector3& Tranlste);

		~ScaleTranslation_Transform(void) = default;

	public:
		bool operator==(const ScaleTranslation_Transform& R_HS)const;
		bool operator!=(const ScaleTranslation_Transform& R_HS)const;

	public:
		float Get_Scale(void)const;
		const Vector3 Get_Translation(void)const;

		void Set_Scale(float Scale);
		void Set_Translation(const Vector3& Translte);
		void Set_Translation(float X, float Y, float Z);

		const Matrix4x4 Get_Matrix4x4(void)const;

		bool Has_Scale(void)const;
		bool Has_Negative_Scale(void)const;
		bool Has_Tranlation(void)const;

	public:
		static const ScaleTranslation_Transform Generate_Scale(float Scale);
		static const ScaleTranslation_Transform Generate_Translation(const Vector3& Translate);

	public:
		static const ScaleTranslation_Transform IDENTITY;

	private:
		Vector4 m_Scale_Translation{ Vector4::UNIT_W };
	};

}// namespace NameSpace_Core::NameSpace_Transform