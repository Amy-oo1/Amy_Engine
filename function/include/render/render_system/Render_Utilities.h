#pragma once

#include "math/Matrix4x4.h"
#include "bounding/Bounding_Box_AxisAligned.h"
#include "bounding/Bounding_Sphere.h"

//TODO : Dependency
#include "render/render_system/Render_Camera.h"
#include "render/render_system/Render_Scene.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System::NameSpace_Utilities {

	using NameSpace_Core::NameSpace_Math::Matrix4x4;
	using NameSpace_Core::NameSpace_Bounding::AxisAligned_Bounding_Box;
	using NameSpace_Core::NameSpace_Bounding::Bounding_Sphere;

	// TODO: support cluster lighting
	struct ClusterFrustum
	{
		// we don't consider the near and far plane currently
		Vector4 m_plane_right;
		Vector4 m_plane_left;
		Vector4 m_plane_top;
		Vector4 m_plane_bottom;
		Vector4 m_plane_near;
		Vector4 m_plane_far;
	};

	bool TiledFrustumIntersectBox(ClusterFrustum const& f, AxisAligned_Bounding_Box const& b);

	const Matrix4x4 Calculate_Direction_Light_View_Matrix(
		const Render_Scene& Scene,
		const Render_Camera& Camera);

	AxisAligned_Bounding_Box BoundingBoxTransform(AxisAligned_Bounding_Box const& b, Matrix4x4 const& m);

	bool BoxIntersectsWithSphere(AxisAligned_Bounding_Box const& b, Bounding_Sphere const& s);

	ClusterFrustum CreateClusterFrustumFromMatrix(Matrix4x4 mat,
		float     x_left,
		float     x_right,
		float     y_top,
		float     y_bottom,
		float     z_near,
		float     z_far);


}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System::NameSpace_Utilities