#include "render/render_system/Render_Utilities.h"

#include<cmath>
#include<algorithm>


#include "math/Utilities.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System::NameSpace_Utilities {

	using NameSpace_Core::NameSpace_Math::NameSpace_Utilities::Min;
	using NameSpace_Core::NameSpace_Math::NameSpace_Utilities::Max;
	//using NameSpace_Core::NameSpace_Math::NameSpace_Utilities::Abs;
	using NameSpace_Core::NameSpace_Math::NameSpace_Utilities::Make_Look_At;
	using NameSpace_Core::NameSpace_Math::NameSpace_Utilities::makeOrthographicProjectionMatrix01;

	bool TiledFrustumIntersectBox(ClusterFrustum const& f, AxisAligned_Bounding_Box const& b)
	{
		// we follow the "DirectX::BoundingFrustum::Intersects"

		// Center of the box.
		Vector4 box_center(b.Get_Center(), 1.0f);

		// Distance from the center to each side.
		// half extent //more exactly
		Vector3 box_extents{ b.Get_Dimensions() };

		// plane_right
		{
			float signed_distance_from_plane_right = f.m_plane_right.Dot_Product(box_center);
			float radius_project_plane_right =
				Vector3(std::fabs(f.m_plane_right.Get_X()), std::fabs(f.m_plane_right.Get_Y()), fabs(f.m_plane_right.Get_Z())).Dot_Product(box_extents);

			bool intersecting_or_inside_right = signed_distance_from_plane_right < radius_project_plane_right;
			if (!intersecting_or_inside_right)
			{
				return false;
			}
		}

		// plane_left
		{
			float signed_distance_from_plane_left = f.m_plane_left.Dot_Product(box_center);
			float radius_project_plane_left =
				Vector3(fabs(f.m_plane_left.Get_X()), fabs(f.m_plane_left.Get_Y()), fabs(f.m_plane_left.Get_Z())).Dot_Product(box_extents);

			bool intersecting_or_inside_left = signed_distance_from_plane_left < radius_project_plane_left;
			if (!intersecting_or_inside_left)
			{
				return false;
			}
		}

		// plane_top
		{
			float signed_distance_from_plane_top = f.m_plane_top.Dot_Product(box_center);
			float radius_project_plane_top =
				Vector3(fabs(f.m_plane_top.Get_X()), fabs(f.m_plane_top.Get_Y()), fabs(f.m_plane_top.Get_Z())).Dot_Product(box_extents);

			bool intersecting_or_inside_top = signed_distance_from_plane_top < radius_project_plane_top;
			if (!intersecting_or_inside_top)
			{
				return false;
			}
		}

		// plane_bottom
		{
			float signed_distance_from_plane_bottom = f.m_plane_bottom.Dot_Product(box_center);
			float radius_project_plane_bottom =
				Vector3(fabs(f.m_plane_bottom.Get_X()), fabs(f.m_plane_bottom.Get_Y()), fabs(f.m_plane_bottom.Get_Z())).Dot_Product(box_extents);

			bool intersecting_or_inside_bottom = signed_distance_from_plane_bottom < radius_project_plane_bottom;
			if (!intersecting_or_inside_bottom)
			{
				return false;
			}
		}

		// plane_near
		{
			float signed_distance_from_plane_near = f.m_plane_near.Dot_Product(box_center);
			float radius_project_plane_near =
				Vector3(fabs(f.m_plane_near.Get_X()), fabs(f.m_plane_near.Get_Y()), fabs(f.m_plane_near.Get_Z())).Dot_Product(box_extents);

			bool intersecting_or_inside_near = signed_distance_from_plane_near < radius_project_plane_near;
			if (!intersecting_or_inside_near)
			{
				return false;
			}
		}

		// plane_far
		{
			float signed_distance_from_plane_far = f.m_plane_far.Dot_Product(box_center);
			float radius_project_plane_far =
				Vector3(fabs(f.m_plane_far.Get_X()), fabs(f.m_plane_far.Get_Y()), fabs(f.m_plane_far.Get_Z())).Dot_Product(box_extents);

			bool intersecting_or_inside_far = signed_distance_from_plane_far < radius_project_plane_far;
			if (!intersecting_or_inside_far)
			{
				return false;
			}
		}

		return true;
	}

	const Matrix4x4 Calculate_Direction_Light_View_Matrix(const Render_Scene& scene, const Render_Camera& camera) {
		Matrix4x4 proj_view_matrix;
		{
			Matrix4x4 view_matrix = camera.Get_View_Matrix();
			Matrix4x4 proj_matrix = camera.Get_Projection_Matrix();
			proj_view_matrix = proj_matrix * view_matrix;
		}

		AxisAligned_Bounding_Box frustum_bounding_box{ AxisAligned_Bounding_Box::EMPTY };
		// CascadedShadowMaps11 / CreateFrustumPointsFromCascadeInterval
		{
			Vector3 const g_frustum_points_ndc_space[8] = { Vector3(-1.0f, -1.0f, 1.0f),
															 Vector3(1.0f, -1.0f, 1.0f),
															 Vector3(1.0f, 1.0f, 1.0f),
															 Vector3(-1.0f, 1.0f, 1.0f),
															 Vector3(-1.0f, -1.0f, 0.0f),
															 Vector3(1.0f, -1.0f, 0.0f),
															 Vector3(1.0f, 1.0f, 0.0f),
															 Vector3(-1.0f, 1.0f, 0.0f) };

			Matrix4x4 inverse_proj_view_matrix = proj_view_matrix.Inverse();

			size_t const CORNER_COUNT = 8;
			for (size_t i = 0; i < CORNER_COUNT; ++i)
			{
				Vector4 frustum_point_with_w = inverse_proj_view_matrix * Vector4(
					g_frustum_points_ndc_space[i].Get_X(),
					g_frustum_points_ndc_space[i].Get_Y(),
					g_frustum_points_ndc_space[i].Get_Z(),
					1.0
				);

				Vector3   frustum_point = Vector3(
					frustum_point_with_w.Get_X() / frustum_point_with_w.Get_W(),
					frustum_point_with_w.Get_Y() / frustum_point_with_w.Get_W(),
					frustum_point_with_w.Get_Y() / frustum_point_with_w.Get_W());

				frustum_bounding_box.Add_Point(frustum_point);
			}
		}

		AxisAligned_Bounding_Box scene_bounding_box{ AxisAligned_Bounding_Box::EMPTY };
		{

			for (const auto& entity : scene.m_Render_Entities)
			{
				AxisAligned_Bounding_Box mesh_asset_bounding_box{ entity.Bounding_Box };

				AxisAligned_Bounding_Box mesh_bounding_box_world =
					BoundingBoxTransform(mesh_asset_bounding_box, entity.Model_Matrix);
				scene_bounding_box.Add_Bounding_Box(mesh_bounding_box_world);
			}
		}

		// CascadedShadowMaps11 / ComputeNearAndFar
		Matrix4x4 light_view;
		Matrix4x4 light_proj;
		{
			Vector3 box_center(
				(frustum_bounding_box.Get_Max().Get_X() + frustum_bounding_box.Get_Min().Get_Y()) * 0.5,
				(frustum_bounding_box.Get_Max().Get_Y() + frustum_bounding_box.Get_Min().Get_Y()) * 0.5,
				(frustum_bounding_box.Get_Max().Get_Z() + frustum_bounding_box.Get_Min().Get_Z()) * 0.5
			);

			Vector3 box_extents(
				(frustum_bounding_box.Get_Max().Get_X() - frustum_bounding_box.Get_Min().Get_X()) * 0.5,
				(frustum_bounding_box.Get_Max().Get_Y() - frustum_bounding_box.Get_Min().Get_Y()) * 0.5,
				(frustum_bounding_box.Get_Max().Get_Z() - frustum_bounding_box.Get_Min().Get_Z()) * 0.5
			);

			Vector3 eye =
				box_center + scene.m_Directional_Light.Direction * box_extents.Length();
			Vector3 center = box_center;
			light_view = Make_Look_At(eye, center, Vector3(0.0, 0.0, 1.0));

			AxisAligned_Bounding_Box frustum_bounding_box_light_view = BoundingBoxTransform(frustum_bounding_box, light_view);
			AxisAligned_Bounding_Box scene_bounding_box_light_view = BoundingBoxTransform(scene_bounding_box, light_view);
			light_proj = makeOrthographicProjectionMatrix01(
				std::max(frustum_bounding_box_light_view.Get_Min().Get_X(), scene_bounding_box_light_view.Get_Min().Get_X()),
				std::min(frustum_bounding_box_light_view.Get_Max().Get_X(), scene_bounding_box_light_view.Get_Max().Get_X()),
				std::max(frustum_bounding_box_light_view.Get_Min().Get_Y(), scene_bounding_box_light_view.Get_Min().Get_Y()),
				std::min(frustum_bounding_box_light_view.Get_Max().Get_Y(), scene_bounding_box_light_view.Get_Max().Get_Y()),
				-scene_bounding_box_light_view.Get_Max().Get_Z(),
				// the objects which are nearer than the frustum bounding box may caster shadow as well
				-std::max(frustum_bounding_box_light_view.Get_Min().Get_Z(), scene_bounding_box_light_view.Get_Min().Get_Z())
			);
		}

		Matrix4x4 light_proj_view = (light_proj * light_view);
		return light_proj_view;
	}

	AxisAligned_Bounding_Box BoundingBoxTransform(AxisAligned_Bounding_Box const& b, Matrix4x4 const& m)
	{
		// we follow the "BoundingBox::Transform"

		Vector3 const g_BoxOffset[8] = { Vector3(-1.0f, -1.0f, 1.0f),
										  Vector3(1.0f, -1.0f, 1.0f),
										  Vector3(1.0f, 1.0f, 1.0f),
										  Vector3(-1.0f, 1.0f, 1.0f),
										  Vector3(-1.0f, -1.0f, -1.0f),
										  Vector3(1.0f, -1.0f, -1.0f),
										  Vector3(1.0f, 1.0f, -1.0f),
										  Vector3(-1.0f, 1.0f, -1.0f) };

		size_t const CORNER_COUNT = 8;

		// Load center and extents.
		// Center of the box.
		Vector3 center(
			(b.Get_Min().Get_X() + b.Get_Max().Get_X()) * 0.5,
			(b.Get_Min().Get_Y() + b.Get_Max().Get_Y()) * 0.5,
			(b.Get_Min().Get_Z() + b.Get_Max().Get_Z()) * 0.5);

		// Distance from the center to each side.
		// half extent //more exactly
		Vector3 extents(
			(b.Get_Max().Get_X() - b.Get_Min().Get_X()) * 0.5,
			(b.Get_Max().Get_Y() - b.Get_Min().Get_Y()) * 0.5,
			(b.Get_Max().Get_Z() - b.Get_Min().Get_Z()) * 0.5);

		Vector3 min;
		Vector3 max;

		// Compute and transform the corners and find new min/max bounds.
		for (size_t i = 0; i < CORNER_COUNT; ++i)
		{
			Vector3 corner_before = extents * g_BoxOffset[i] + center;
			Vector4 corner_with_w = m * Vector4(corner_before, 1.0);
			Vector3 corner = Vector3(
				corner_with_w.Get_X() / corner_with_w.Get_W(),
				corner_with_w.Get_Y() / corner_with_w.Get_W(),
				corner_with_w.Get_Z() / corner_with_w.Get_W());

			if (0 == i)
			{
				min = corner;
				max = corner;
			}
			else
			{
				min = Min(min, corner);
				max = Max(max, corner);
			}
		}

		return AxisAligned_Bounding_Box{ min,max };
	}

	bool BoxIntersectsWithSphere(AxisAligned_Bounding_Box const& b, Bounding_Sphere const& s)
	{
		for (size_t i = 0; i < 3; ++i)
		{
			if (s.Get_Center()[i] < b.Get_Min()[i])
			{
				if ((b.Get_Min()[i] - s.Get_Center()[i]) > s.Get_Radius())
				{
					return false;
				}
			}
			else if (s.Get_Center()[i] > b.Get_Max()[i])
			{
				if ((s.Get_Center()[i] - b.Get_Max()[i]) > s.Get_Radius())
				{
					return false;
				}
			}
		}

		return true;
	}


	ClusterFrustum CreateClusterFrustumFromMatrix(Matrix4x4 mat, float x_left, float x_right, float y_top, float y_bottom, float z_near, float z_far) {
		ClusterFrustum f;

		// the following is in the vulkan space
		// note that the Y axis is flipped in Vulkan
		assert(y_top < y_bottom);

		assert(x_left < x_right);
		assert(z_near < z_far);

		// calculate the tiled frustum
		// [Fast Extraction of Viewing Frustum Planes from the WorldView - Projection
		// Matrix](http://gamedevs.org/uploads/fast-extraction-viewing-frustum-planes-from-world-view-projection-matrix.pdf)

		Matrix4x4 mat_column = mat;

		// [vec.xyz 1][mat.col0] / [vec.xyz 1][mat.col3] > x_right
		// [vec.xyz 1][mat.col0 - mat.col3*x_right] > 0
		f.m_plane_right = Vector4(mat_column[0]) - (Vector4(mat_column[3]) * x_right);
		// normalize
		f.m_plane_right *= (1.0 / Vector3(f.m_plane_right.Get_X(), f.m_plane_right.Get_Y(), f.m_plane_right.Get_Z()).Length());

		// for example, we try to calculate the "plane_left" of the tile frustum
		// note that we use the row vector to be consistent with the DirectXMath
		// [vec.xyz 1][mat.col0] / [vec.xyz 1][mat.col3] < x_left
		//
		// evidently, the value "[vec.xyz 1][mat.col3]" is expected to be greater than
		// 0 (w of clip space) and we multiply both sides by "[vec.xyz 1][mat.col3]",
		// the inequality symbol remains the same [vec.xyz 1][mat.col0] < [vec.xyz
		// 1][mat.col3]*x_left
		//
		// since "x_left" is a scalar, the "scalar multiplication" is applied
		// [vec.xyz 1][mat.col0] < [vec.xyz 1][mat.col3*x_left]
		// [vec.xyz 1][mat.col0 - mat.col3*x_left] < 0
		//
		// we follow the "DirectX::BoundingFrustum::Intersects", the normal of the
		// plane is pointing ourward [vec.xyz 1][mat.col3*x_left - mat.col0] > 0
		//
		// the plane can be defined as [x y z 1][A B C D] = 0 and the [A B C D] is
		// exactly [mat.col0 - mat.col3*x_left] and we need to normalize the normal[A
		// B C] of the plane let [A B C D] = [mat.col3*x_left - mat.col0] [A B C D] /=
		// length([A B C].xyz)
		f.m_plane_left = (Vector4(mat_column[3]) * x_left) - Vector4(mat_column[0]);
		// normalize
		f.m_plane_left *= (1.0 / Vector3(f.m_plane_left.Get_X(), f.m_plane_left.Get_Y(), f.m_plane_left.Get_Z()).Length());

		// [vec.xyz 1][mat.col1] / [vec.xyz 1][mat.col3] < y_top
		// [vec.xyz 1][mat.col3*y_top - mat.col1] > 0
		f.m_plane_top = (Vector4(mat_column[3]) * y_top) - Vector4(mat_column[1]);
		// normalize
		f.m_plane_top *= (1.0 / Vector3(f.m_plane_top.Get_X(), f.m_plane_top.Get_Y(), f.m_plane_top.Get_Z()).Length());

		// [vec.xyz 1][mat.col1] / [vec.xyz 1][mat.col3] > y_bottom
		// [vec.xyz 1][mat.col1 - mat.col3*y_bottom] > 0
		f.m_plane_bottom = Vector4(mat_column[1]) - (Vector4(mat_column[3]) * y_bottom);
		// normalize
		f.m_plane_bottom *= (1.0 / Vector3(f.m_plane_bottom.Get_X(), f.m_plane_bottom.Get_Y(), f.m_plane_bottom.Get_Z()).Length());

		// [vec.xyz 1][mat.col2] / [vec.xyz 1][mat.col3] < z_near
		// [vec.xyz 1][mat.col3*z_near - mat.col2] > 0
		f.m_plane_near = (Vector4(mat_column[3]) * z_near) - Vector4(mat_column[2]);
		f.m_plane_near *= (1.0 / Vector3(f.m_plane_near.Get_X(), f.m_plane_near.Get_Y(), f.m_plane_near.Get_Z()).Length());

		// [vec.xyz 1][mat.col2] / [vec.xyz 1][mat.col3] > z_far
		// [vec.xyz 1][mat.col2 - mat.col3*z_far] > 0
		f.m_plane_far = Vector4(mat_column[2]) - (Vector4(mat_column[3]) * z_far);
		f.m_plane_far *= (1.0 / Vector3(f.m_plane_far.Get_X(), f.m_plane_far.Get_Y(), f.m_plane_far.Get_Z()).Length());

		return f;
	}

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System::NameSpace_Utilities
