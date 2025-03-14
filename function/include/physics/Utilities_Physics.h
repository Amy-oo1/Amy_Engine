#pragma once

#include<cstdint>
#include<memory>

#include "Jolt/Jolt.h"
#include "Jolt/Math/Vec3.h"
#include "Jolt/Math/Vec4.h"
#include "Jolt/Math/Mat44.h"
#include "Jolt/Math/Quat.h"
#include "Jolt/Physics/Collision/Shape/Shape.h"
#include "Jolt/Physics/Collision/BroadPhase/BroadPhaseLayer.h"

#include "logger/System_Logger.h"
#include "math/Vector3.h"
#include "math/Vector4.h"
#include "math/Matrix4x4.h"
#include "math/Quaternion.h"

#include "components/rigid_body/Basic_Shape.h"
#include "components/rigid_body/Rigid_Body.h"

namespace NameSpace_Function::Namespace_Physics::NameSpace_Utilites {

	using std::shared_ptr;

	using JPH::Vec3;
	using JPH::Vec4;
	using JPH::Mat44;
	using JPH::Quat;
	using JPH::BroadPhaseLayerInterface;
	using JPH::BroadPhaseLayer;
	using JPH::ObjectLayer;
	using JPH::Shape;

	using NameSpace_Core::NameSpace_Logger::System_Logger;
	using NameSpace_Core::NameSpace_Math::Vector3;
	using NameSpace_Core::NameSpace_Math::Vector4;
	using NameSpace_Core::NameSpace_Math::Matrix4x4;
	using NameSpace_Core::NameSpace_Math::Quaternion;

	using NameSpace_Resource::NameSpace_Components::Rigid_Body_Shape;

	//TODO : Add Enum Func
	class Layers final {
	public:
		static constexpr uint8_t UNUSED1{ 0 };
		static constexpr uint8_t UNUSED2{ 1 };
		static constexpr uint8_t UNUSED3{ 2 };
		static constexpr uint8_t UNUSED4{ 3 };
		static constexpr uint8_t NON_MOVING{ 4 };
		static constexpr uint8_t MOVING{ 5 };
		static constexpr uint8_t DEBRIS{ 6 };
		static constexpr uint8_t SENSOR{ 7 };
		static constexpr uint8_t NUM_LAYERS{ 8 };
	};

	class BroadPhase_Layers final {
	public:
		static constexpr BroadPhaseLayer NON_MOVING{ 0 };
		static constexpr BroadPhaseLayer MOVING{ 1 };
		static constexpr BroadPhaseLayer DEBRIS{ 2 };
		static constexpr BroadPhaseLayer SENSOR{ 3 };
		static constexpr BroadPhaseLayer UNUSED{ 4 };
		static constexpr uint8_t NUM_LAYERS{ 5 };
	};

	class BP_Layer_Interface_Impl final :public BroadPhaseLayerInterface {
	private:
		BP_Layer_Interface_Impl(const BP_Layer_Interface_Impl&) = delete;
		BP_Layer_Interface_Impl(BP_Layer_Interface_Impl&&) = delete;

		BP_Layer_Interface_Impl& operator=(const BP_Layer_Interface_Impl&) = delete;
		BP_Layer_Interface_Impl& operator=(BP_Layer_Interface_Impl&&) = delete;

	public:
		BP_Layer_Interface_Impl(void);

		~BP_Layer_Interface_Impl(void) = default;

	public:
		//NOTE : Override Virtual Func
		JPH::uint GetNumBroadPhaseLayers(void)const override;

		BroadPhaseLayer GetBroadPhaseLayer(ObjectLayer InLayer) const override;

#if defined(JPH_EXTERNAL_PROFILE) || defined(JPH_PROFILE_ENABLED)
		/// Get the user readable name of a broadphase layer (debugging purposes)
		virtual const char* GetBroadPhaseLayerName(BroadPhaseLayer InLayer) const override;
#endif // JPH_EXTERNAL_PROFILE || JPH_PROFILE_ENABLED

	private:
		BroadPhaseLayer m_object_to_broad_phase[Layers::NUM_LAYERS];

	};

	bool Objects_Can_Collide(ObjectLayer InLayer1, ObjectLayer InLayer2);

	bool BroadPhase_Can_Collide(ObjectLayer InLayer1, BroadPhaseLayer InLayer2);

	const Vec3 Convert_Vec3(const Vector3& InVector);
	const Vector3 Convert_Vec3(const Vec3& InVector);

	const Vec4 Convert_Vec4(const Vector4& InVector);
	const Vector4 Convert_Vec4(const Vec4& InVector);

	const Mat44 Convert_Mat44(const Matrix4x4& InMatrix);
	const Matrix4x4 Convert_Mat44(const Mat44& InMatrix);

	const Quat Convert_Quat(const Quaternion& InQuat);
	const Quaternion Convert_Quat(const Quat& InQuat);

	shared_ptr<Shape> Convert_Shape(const shared_ptr<Rigid_Body_Shape>& InShape, const Vector3& Scale);

}// namespace NameSpace_Function::Namespace_Physics::NameSpace_Utilites