#include "physics/Utilities_Physics.h"

#include<limits>
#include<string>

#include "Jolt/Physics/Collision/Shape/BoxShape.h"
#include "Jolt/Physics/Collision/Shape/SphereShape.h"
#include "Jolt/Physics/Collision/Shape/CylinderShape.h"

#include "meta/generated/reflection/Basic_Shape.Generated_Reflection.h"
#include "meta/generated/reflection/Rigid_Body.Generated_Reflection.h"

namespace NameSpace_Function::Namespace_Physics::NameSpace_Utilites {

	using std::string;
	using std::static_pointer_cast;

	using JPH::BoxShape;
	using JPH::SphereShape;
	using JPH::CylinderShape;

	using NameSpace_Resource::NameSpace_Components::Geometry_Box;
	using NameSpace_Resource::NameSpace_Components::Geometry_Sphere;
	using NameSpace_Resource::NameSpace_Components::Geometry_Cylinder;

	using NameSpace_Resource::NameSpace_Components::Reflection_Geometry_Base_Operator;
	using NameSpace_Resource::NameSpace_Components::Reflection_Geometry_Box_Operator;
	using NameSpace_Resource::NameSpace_Components::Reflection_Geometry_Sphere_Operator;
	using NameSpace_Resource::NameSpace_Components::Reflection_Geometry_Cylinder_Operator;
	using NameSpace_Resource::NameSpace_Components::Reflection_Rigid_Body_Shape_Operator;

	NameSpace_Function::Namespace_Physics::NameSpace_Utilites::BP_Layer_Interface_Impl::BP_Layer_Interface_Impl(void) {
		this->m_object_to_broad_phase[Layers::UNUSED1] = BroadPhase_Layers::UNUSED;
		this->m_object_to_broad_phase[Layers::UNUSED2] = BroadPhase_Layers::UNUSED;
		this->m_object_to_broad_phase[Layers::UNUSED3] = BroadPhase_Layers::UNUSED;
		this->m_object_to_broad_phase[Layers::UNUSED4] = BroadPhase_Layers::UNUSED;
		this->m_object_to_broad_phase[Layers::NON_MOVING] = BroadPhase_Layers::NON_MOVING;
		this->m_object_to_broad_phase[Layers::MOVING] = BroadPhase_Layers::MOVING;
		this->m_object_to_broad_phase[Layers::DEBRIS] = BroadPhase_Layers::DEBRIS;
		this->m_object_to_broad_phase[Layers::SENSOR] = BroadPhase_Layers::SENSOR;
	}

	JPH::uint BP_Layer_Interface_Impl::GetNumBroadPhaseLayers(void) const {
		return BroadPhase_Layers::NUM_LAYERS;
	}

	BroadPhaseLayer BP_Layer_Interface_Impl::GetBroadPhaseLayer(ObjectLayer InLayer) const {
		if (InLayer >= std::numeric_limits<uint8_t>::max() || InLayer >= Layers::NUM_LAYERS) {
			System_Logger::Get_Instance().Log(System_Logger::Level::err, "Invalid Layer");

			return BroadPhase_Layers::UNUSED;
		}

		return this->m_object_to_broad_phase[InLayer];
	}

#if defined(JPH_EXTERNAL_PROFILE) || defined(JPH_PROFILE_ENABLED)
	/// Get the user readable name of a broadphase layer (debugging purposes)
	const char* NameSpace_Function::Namespace_Physics::NameSpace_Utilites::BP_Layer_Interface_Impl::GetBroadPhaseLayerName(BroadPhaseLayer InLayer) const {
		switch (static_cast<BroadPhaseLayer::Type>(InLayer))
		{
		case static_cast<BroadPhaseLayer::Type>(BroadPhase_Layers::NON_MOVING):
			return "NON_MOVING";
		case static_cast<BroadPhaseLayer::Type>(BroadPhase_Layers::MOVING):
			return "MOVING";
		case static_cast<BroadPhaseLayer::Type>(BroadPhase_Layers::DEBRIS):
			return "DEBRIS";
		case static_cast<BroadPhaseLayer::Type>(BroadPhase_Layers::SENSOR):
			return "SENSOR";
		case static_cast<BroadPhaseLayer::Type>(BroadPhase_Layers::UNUSED):
			return "UNUSED";
		default:
			System_Logger::Get_Instance().Log(System_Logger::Level::err, "Invalid Layer");
			return "INVALID";
		}
	}
#endif // JPH_EXTERNAL_PROFILE || JPH_PROFILE_ENABLED

	bool My_ObjectVsBroadPhaseLayerFilter::ShouldCollide(ObjectLayer InLayer1, BroadPhaseLayer InLayer2) const {
		switch (InLayer1) {
		case Layers::NON_MOVING:
			return InLayer2 == BroadPhase_Layers::MOVING;
		case Layers::MOVING:
			return
				InLayer2 == BroadPhase_Layers::NON_MOVING ||
				InLayer2 == BroadPhase_Layers::MOVING ||
				InLayer2 == BroadPhase_Layers::SENSOR;
		case Layers::DEBRIS:
			return InLayer2 == BroadPhase_Layers::NON_MOVING;
		case Layers::SENSOR:
			return InLayer2 == BroadPhase_Layers::MOVING;
		case Layers::UNUSED1:
		case Layers::UNUSED2:
		case Layers::UNUSED3:
		case Layers::UNUSED4:
			return false;
		default:
			System_Logger::Get_Instance().Log(System_Logger::Level::err, "Invalid Case");
			return false;
		}
	}

	bool My_ObjectLayerPairFilter::ShouldCollide(ObjectLayer InLayer1, ObjectLayer InLayer2) const {
		switch (InLayer1) {
		case Layers::UNUSED1:
		case Layers::UNUSED2:
		case Layers::UNUSED3:
		case Layers::UNUSED4:
			return false;
		case Layers::NON_MOVING:
			return InLayer2 == Layers::MOVING || InLayer2 == Layers::DEBRIS;
		case Layers::MOVING:
			return InLayer2 == Layers::NON_MOVING || InLayer2 == Layers::MOVING || InLayer2 == Layers::SENSOR;
		case Layers::DEBRIS:
			return InLayer2 == Layers::NON_MOVING;
		case Layers::SENSOR:
			return InLayer2 == Layers::MOVING;
		default:
			System_Logger::Get_Instance().Log(System_Logger::Level::err, "Invalid Case");
			return false;
		}
	}

	const Vec3 Convert_Vec3(const Vector3& InVector) {
		return Vec3{ InVector.Get_X(),InVector.Get_Y(),InVector.Get_Z() };
	}

	const Vector3 Convert_Vec3(const Vec3& InVector) {
		return Vector3{ InVector.GetX(),InVector.GetY(),InVector.GetZ() };
	}

	const Vec4 Convert_Vec4(const Vector4& InVector) {
		return Vec4{ InVector.Get_X(),InVector.Get_Y(),InVector.Get_Z(),InVector.Get_W() };
	}

	const Vector4 Convert_Vec4(const Vec4& InVector) {
		return Vector4{ InVector.GetX(),InVector.GetY(),InVector.GetZ(),InVector.GetW() };
	}

	const Mat44 Convert_Mat44(const Matrix4x4& InMatrix) {
		return Mat44{
			Convert_Vec4(InMatrix.Get_Column(0)),
			Convert_Vec4(InMatrix.Get_Column(1)),
			Convert_Vec4(InMatrix.Get_Column(2)),
			Convert_Vec4(InMatrix.Get_Column(3))
		};
	}

	const Matrix4x4 Convert_Mat44(const Mat44& InMatrix) {
		return Matrix4x4{
			Convert_Vec4(InMatrix.GetColumn4(0)),
			Convert_Vec4(InMatrix.GetColumn4(1)),
			Convert_Vec4(InMatrix.GetColumn4(2)),
			Convert_Vec4(InMatrix.GetColumn4(3))
		};
	}

	const Quat Convert_Quat(const Quaternion& InQuat) {
		return Quat{ InQuat.Get_X(),InQuat.Get_Y(),InQuat.Get_Z(),InQuat.Get_S() };
	}

	const Quaternion Convert_Quat(const Quat& InQuat) {
		return Quaternion{ InQuat.GetW(), InQuat.GetX(),InQuat.GetY(),InQuat.GetZ() };
	}

	shared_ptr<Shape> Convert_Shape(const shared_ptr<Rigid_Body_Shape>& InShape, const Vector3& Scale) {
		shared_ptr<Shape> Res{ nullptr };
		const string Shape_Type_Spelling{ Reflection_Rigid_Body_Shape_Operator::Get_Geometry_Attribute(InShape).Get_Type_Spelling() };

		if (Reflection_Geometry_Box_Operator::Get_Spelling() == Shape_Type_Spelling) {
			shared_ptr<Geometry_Box> Box{ static_pointer_cast<Geometry_Box>(Reflection_Rigid_Body_Shape_Operator::Get_Geometry_Attribute(InShape).Get_Instance()) };
			if (nullptr != Box) {
				const Vec3 JPH_Box{
					Reflection_Geometry_Box_Operator::Get_Half_Extents_Attribute(Box).Get_X() * Scale.Get_X(),
					Reflection_Geometry_Box_Operator::Get_Half_Extents_Attribute(Box).Get_Y() * Scale.Get_Y(),
					Reflection_Geometry_Box_Operator::Get_Half_Extents_Attribute(Box).Get_Z() * Scale.Get_Z()
				};

				Res = std::make_shared<BoxShape>(JPH_Box);
			}
		}
		else if (Reflection_Geometry_Sphere_Operator::Get_Spelling() == Shape_Type_Spelling) {
			shared_ptr<Geometry_Sphere> Sphere{ static_pointer_cast<Geometry_Sphere>(Reflection_Rigid_Body_Shape_Operator::Get_Geometry_Attribute(InShape).Get_Instance()) };
			if (nullptr != Sphere) {
				const float JPH_Radius{ Reflection_Geometry_Sphere_Operator::Get_radius_Attribute(Sphere) * (Scale.Get_X() + Scale.Get_Y() + Scale.Get_Z()) / 3 };

				Res = std::make_shared<SphereShape>(JPH_Radius);
			}
		}
		else if (Reflection_Geometry_Cylinder_Operator::Get_Spelling() == Shape_Type_Spelling) {
			shared_ptr<Geometry_Cylinder> Cylinder{ static_pointer_cast<Geometry_Cylinder>(Reflection_Rigid_Body_Shape_Operator::Get_Geometry_Attribute(InShape).Get_Instance()) };
			if (nullptr != Cylinder) {
				const float JPH_Half_Height{ Reflection_Geometry_Cylinder_Operator::Get_Half_Height_Attribute(Cylinder) * Scale.Get_Z() };
				const float JPH_Radius{ Reflection_Geometry_Cylinder_Operator::Get_Radius_Attribute(Cylinder) * (Scale.Get_X() + Scale.Get_Y()) / 2 };

				Res = std::make_shared<CylinderShape>(JPH_Half_Height, JPH_Radius);
			}
		}
		else if (Reflection_Geometry_Base_Operator::Get_Spelling() == Shape_Type_Spelling)
			System_Logger::Get_Instance().Log(System_Logger::Level::err, "Shape Is Not Initialized(Base)");
		else
			System_Logger::Get_Instance().Log(System_Logger::Level::err, "Invalid Shape Type");

		return Res;
	}

}// namespace NameSpace_Function::Namespace_Physics::NameSpace_Utilites