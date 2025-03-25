#include "render/render_system/Light.h"

#include<cmath>
#include<algorithm>

#include "math/Constant.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System {

	using NameSpace_Core::NameSpace_Math::Math_PI;

	float Point_Light::Calculate_Radius(void) const {
		static const float INTENSITY_CUTOFF{ 1.f };
		static const float ATTENTUATION_CUTOFF{ 0.05f };

		Vector3 Intensity{ this->Flux / (4 * Math_PI) };
		float Max_Intensity{ std::max({ Intensity.Get_X(), Intensity.Get_Y(), Intensity.Get_Z() }) };
		float Attenuation{ std::max(INTENSITY_CUTOFF, ATTENTUATION_CUTOFF * Max_Intensity) / Max_Intensity };

		return 1.f / sqrtf(Attenuation);
	}

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System