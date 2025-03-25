#pragma once

#include<vector>
#include<memory>

#include "math/Constant.h"
#include "math/Vector3.h"

#include "render/rhi/empty_rhi/RHI_Type.h"
#include "render/render_system/Render_Data_Struct.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System {

	using std::vector;
	using std::shared_ptr;

	using NameSpace_Core::NameSpace_Math::Vector3;

	struct Point_Light final {
		Vector3 Position;
		Vector3 Flux;

		float Calculate_Radius(void) const;

	};

	struct Ambient_Light final {
		Vector3 Irradiance;

	};

	struct PDirectional_Light final {
		Vector3 Direction;
		Vector3 Irradiance;

	};

	struct Light_List  {

		struct alignas(16) Point_Light_Vertex final {
			Vector3 Position;
			Vector3 Intensity;
			float Radius;

		};
	};

	class Point_Light_List :public Light_List {
	public:
		//TODO
		vector<Point_Light> m_Light;
		shared_ptr<Buffer_Data> m_Buffer;
	
	};

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System