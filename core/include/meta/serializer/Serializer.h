#pragma once

#include "json.h"

#include<string>
#include<vector>
#include<memory>

#include "file/File_System.h"

#include "logger/System_Logger.h"

#include "math/Head_Math.h"
#include "transform/Head_Thansform.h"
#include "bounding/Head_Bounding.h"
#include "color/Color.h"

#include "meta/reflection/Reflection_Instance.h"

namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer {

	using std::string;
	using std::vector;
	using std::shared_ptr;
	using std::weak_ptr;
	using std::unique_ptr;


	using JSON = nlohmann::json;

	using NameSpace_Logger::System_Logger;

	using NameSpace_Platform::NameSpace_File::path;

	using namespace NameSpace_Math;
	using namespace NameSpace_Transform;
	using namespace NameSpace_Bounding;

	using NameSpace_Color::Color;

	using NameSpace_Reflection::Reflection_Instance;

	class Serializer final {
	public:
		Serializer(void) = delete;

		Serializer(const Serializer&) = delete;
		Serializer(Serializer&&) = delete;

		Serializer& operator=(const Serializer&) = delete;
		Serializer& operator=(Serializer&&) = delete;

	public:
		template<typename Type>
		static const JSON Write(const Type& Instance) {
			return JSON(Instance);
		}

		template<typename Type>
		static const JSON Write(const unique_ptr<Type>& Instance) {
			return Instance ? Write(*Instance) : JSON();
		}

		template<typename Type>
		static const JSON Write(const shared_ptr<Type>& Instance) {
			return Instance ? Write(*Instance) : JSON();
		}

		template<typename Type>
		static const JSON Write(const Reflection_Instance<Type>& Instance) {
			return JSON{
				{"Type_Spelling", Serializer::Write(Instance.m_Type_Spelling)},
				{"Instance", Serializer::Write(*Instance.m_Instance)}
			};
		}

		template<typename Type>
		static const JSON Write(const std::vector<Type>& Instances) {
			JSON Json_Context{ JSON::array() };
			for (const auto& Instance : Instances)
				Json_Context.push_back(Serializer::Write(Instance));

			return Json_Context;
		}

		template<typename Type>
		static const JSON Write(const std::vector<unique_ptr<Type>>& Instances) {
			JSON Json_Context{ JSON::array() };
			for (const auto& Instance : Instances)
				Json_Context.push_back(Serializer::Write(Instance));
			return Json_Context;
		}

		template<typename Type>
		static const JSON Write(const std::vector<shared_ptr<Type>>& Instances) {
			JSON Json_Context{ JSON::array() };
			for (const auto& Instance : Instances)
				Json_Context.push_back(Serializer::Write(Instance));
			return Json_Context;
		}

		template<typename Type>
		static const JSON Write(const std::vector<Reflection_Instance<Type>>& Instances) {
			JSON Json_Context{ JSON::array() };
			for (const auto& Instance : Instances)
				Json_Context.push_back(Serializer::Write(Instance));
			return Json_Context;
		}
	

		template<typename Type>
		static Type& Read(const JSON& Json_Context, Type& Instance) {
			if (Json_Context.is_null())
				return Instance;
			else
				return Instance = Json_Context.get<Type>();
		}

		template<typename Type>
		static  shared_ptr<Type>& Read(const JSON& Json_Context, shared_ptr<Type>& Instance) {
			if (Json_Context.is_null())
				return Instance;
			else {
				Instance = std::make_shared<Type>();
				Serializer::Read<Type>(Json_Context, *Instance);
				return Instance;
			}
		}

		template<typename Type>
		static  unique_ptr<Type>& Read(const JSON& Json_Context, unique_ptr<Type>& Instance) {
			if (Json_Context.is_null())
				return Instance;
			else {
				Instance = std::make_unique<Type>();
				Serializer::Read<Type>(Json_Context, *Instance);
				return Instance;
			}
		}

		template<typename Type>
		static Reflection_Instance<Type>& Read(const JSON& Json_Context, Reflection_Instance<Type>& Instance) {
			if (Json_Context.is_null()) {
				Instance.m_Instance = std::make_shared<Type>();
				Serializer::Read<std::string>(Json_Context["Type_Spelling"], Instance.m_Type_Spelling);
				Serializer::Read<Type>(Json_Context["Instance"], *Instance.m_Instance);
			}
			return Instance;
		}

		template<typename Type>
		static std::vector<Type>& Read(const JSON& Json_Contexts, std::vector<Type>& Instances) {
			if (!Json_Contexts.is_null()) {
				Instances.clear();

				Type Instance{};
				for (const auto& Json_Context : Json_Contexts)
					Instances.push_back(Serializer::Read<Type>(Json_Context, Instance));
			}

			return Instances;
		}

		template<typename Type>
		static std::vector<unique_ptr<Type>>& Read(const JSON& Json_Contexts, std::vector<unique_ptr<Type>>& Instances) {
			if (!Json_Contexts.is_null()) {
				Instances.clear();
				unique_ptr<Type> Instance{};
				for (const auto& Json_Context : Json_Contexts)
					Instances.push_back(Serializer::Read(Json_Context, Instance));
			}
			return Instances;
		}

		template<typename Type>
		static std::vector<shared_ptr<Type>>& Read(const JSON& Json_Contexts, std::vector<shared_ptr<Type>>& Instances) {
			if (!Json_Contexts.is_null()) {
				Instances.clear();

				shared_ptr<Type> Instance{};
				for (const auto& Json_Context : Json_Contexts)
					Instances.push_back(Serializer::Read(Json_Context, Instance));
			}
			return Instances;
		}

		template<typename Type>
		static std::vector<Reflection_Instance<Type>>& Read(const JSON& Json_Contexts, std::vector<Reflection_Instance<Type>>& Instances) {
			if (!Json_Contexts.is_null()) {
				Instances.clear();
				Reflection_Instance<Type> Instance{};
				for (const auto& Json_Context : Json_Contexts)
					Instances.push_back(Serializer::Read(Json_Context, Instance));
			}
			return Instances;
		}

	};

	//NOTE : Implement Base Type
	template<> inline const JSON Serializer::Write<bool>(const bool& Instance) {
		return JSON(Instance);
	}

	template<> inline const JSON Serializer::Write<char>(const char& Instance) {
		return JSON(Instance);
	}

	template<> inline const JSON Serializer::Write<unsigned char>(const unsigned char& Instance) {
		return JSON(Instance);
	}

	template<> inline const JSON Serializer::Write<int>(const int& Instance) {
		return JSON(Instance);
	}

	template<> inline const JSON Serializer::Write<unsigned int>(const unsigned int& Instance) {
		return JSON(Instance);
	}

	template<> inline const JSON Serializer::Write<long>(const long& Instance) {
		return JSON(Instance);
	}

	template<> inline const JSON Serializer::Write<unsigned long>(const unsigned long& Instance) {
		return JSON(Instance);
	}

	template<> inline const JSON Serializer::Write<long long>(const long long& Instance) {
		return JSON(Instance);
	}

	template<> inline const JSON Serializer::Write<float>(const float& Instance) {
		return JSON(Instance);
	}

	template<> inline const JSON Serializer::Write<double>(const double& Instance) {
		return JSON(Instance);
	}

	//NOTE : STD Type
	template<> inline const JSON Serializer::Write<std::string>(const std::string& Instance) {
		return JSON(Instance);
	}

	template<> inline const JSON Serializer::Write<path>(const path& Instance) {
		return JSON(Instance.generic_string());
	}

	//NOTE: My Type
	template<> inline const JSON Serializer::Write<Radian>(const Radian& Instance) {
		return JSON{
			"Radian", Serializer::Write<float>(Instance.Get_Radian())
		};
	}

	template<> inline const JSON Serializer::Write<Degree>(const Degree& Instance) {
		return JSON(Instance.Get_Degree());
	}

	template<> inline const JSON Serializer::Write<Vector2>(const Vector2& Instance) {
		return JSON{
			"X",Serializer::Write<float>(Instance.Get_X()),
			"Y",Serializer::Write<float>(Instance.Get_Y())
		};
	}

	template<> inline const JSON Serializer::Write<Vector3>(const Vector3& Instance) {
		return JSON{
			"X",Serializer::Write<float>(Instance.Get_X()),
			"Y",Serializer::Write<float>(Instance.Get_Y()),
			"Z",Serializer::Write<float>(Instance.Get_Z())
		};
	}

	template<> inline const JSON Serializer::Write<Vector4>(const Vector4& Instance) {
		return JSON{
			"X",Serializer::Write<float>(Instance.Get_X()),
			"Y",Serializer::Write<float>(Instance.Get_Y()),
			"Z",Serializer::Write<float>(Instance.Get_Z()),
			"W",Serializer::Write<float>(Instance.Get_W())
		};
	}

	template<> inline const JSON Serializer::Write<Matrix3x3>(const Matrix3x3& Instance) {
		return JSON{
			{"M11", Serializer::Write<float>(Instance[0][0])}, {"M12", Serializer::Write<float>(Instance[0][1])}, {"M13",Serializer::Write<float>(Instance[0][2])},
			{"M21", Serializer::Write<float>(Instance[1][0])}, {"M22", Serializer::Write<float>(Instance[1][1])}, {"M23",Serializer::Write<float>(Instance[1][2])},
			{"M31", Serializer::Write<float>(Instance[2][0])}, {"M32", Serializer::Write<float>(Instance[2][1])}, {"M33",Serializer::Write<float>(Instance[2][2])}
		};
	}

	template<> inline const JSON Serializer::Write<Matrix4x4>(const Matrix4x4& Instance) {
		return JSON{
			{"M11", Serializer::Write<float>(Instance[0][0])}, {"M12", Serializer::Write<float>(Instance[0][1])}, {"M13",Serializer::Write<float>(Instance[0][2])}, {"M14",Serializer::Write<float>(Instance[0][3])},
			{"M21", Serializer::Write<float>(Instance[1][0])}, {"M22", Serializer::Write<float>(Instance[1][1])}, {"M23",Serializer::Write<float>(Instance[1][2])}, {"M24",Serializer::Write<float>(Instance[1][3])},
			{"M31", Serializer::Write<float>(Instance[2][0])}, {"M32", Serializer::Write<float>(Instance[2][1])}, {"M33",Serializer::Write<float>(Instance[2][2])}, {"M34",Serializer::Write<float>(Instance[2][3])},
			{"M41", Serializer::Write<float>(Instance[3][0])}, {"M42", Serializer::Write<float>(Instance[3][1])}, {"M43",Serializer::Write<float>(Instance[3][2])}, {"M44",Serializer::Write<float>(Instance[3][3])}
		};
	}

	template<> inline const JSON Serializer::Write<Quaternion>(const Quaternion& Instance) {
		return JSON{
			{"S", Serializer::Write<float>(Instance.Get_S())},
			{"X", Serializer::Write<float>(Instance.Get_X())},
			{"Y", Serializer::Write<float>(Instance.Get_Y())},
			{"Z", Serializer::Write<float>(Instance.Get_Z())}
		};
	}

	template<> inline const JSON Serializer::Write<Orthogonal_Transform>(const Orthogonal_Transform& Instance) {
		return JSON{
			{"Rotation", Serializer::Write<Quaternion>(Instance.Get_Rotation())},
			{"Translation", Serializer::Write<Vector3>(Instance.Get_Translation())}
		};
	}

	template<> inline const JSON Serializer::Write<ScaleTranslation_Transform>(const ScaleTranslation_Transform& Instance) {
		return JSON{
			{"Scale", Serializer::Write<float>(Instance.Get_Scale())},
			{"Translation", Serializer::Write<Vector3>(Instance.Get_Translation())}
		};
	}

	template<> inline const JSON Serializer::Write<Uniform_Transform>(const Uniform_Transform& Instance) {
		return JSON{
			{"Rotation", Serializer::Write<Quaternion>(Instance.Get_Rotation())},
			{"Scale", Serializer::Write<float>(Instance.Get_Scale())},
			{"Translation", Serializer::Write<Vector3>(Instance.Get_Translation())}
		};
	}

	template<> inline const JSON Serializer::Write<Affine_Transform>(const Affine_Transform& Instance) {
		return JSON{
			{"Basis", Serializer::Write<Matrix3x3>(Instance.Get_Basis())},
			{"Translation", Serializer::Write<Vector3>(Instance.Get_Translation())}
		};
	}

	template<> inline const JSON Serializer::Write<AxisAligned_Bounding_Box>(const AxisAligned_Bounding_Box& Instance) {
		return JSON{
			{"Min", Serializer::Write<Vector3>(Instance.Get_Min())},
			{"Max", Serializer::Write<Vector3>(Instance.Get_Max())}
		};
	}

	template<> inline const JSON Serializer::Write<Oriented_Bounding_Box>(const Oriented_Bounding_Box& Instance) {
		return JSON{
			{"Transform", Serializer::Write<Affine_Transform>(Instance.Get_Transform())}
		};
	}

	template<> inline const JSON Serializer::Write<Bounding_Plane>(const Bounding_Plane& Instance) {
		return JSON{
			{"Normal", Serializer::Write<Vector3>(Instance.Get_Normal())},
			{"Point", Serializer::Write<Vector3>(Instance.Get_Point_On_Plane())}
		};
	}

	template<> inline const JSON Serializer::Write<Bounding_Sphere>(const Bounding_Sphere& Instance) {
		return JSON{
			{"Center", Serializer::Write<Vector3>(Instance.Get_Center())},
			{"Radius", Serializer::Write<float>(Instance.Get_Radius())}
		};
	}

	template<> inline const JSON Serializer::Write<Color>(const Color& Instance) {
		return JSON{
			{"Red", Serializer::Write<float>(Instance.Get_R()) },
			{"Green", Serializer::Write<float>(Instance.Get_G()) },
			{"Blue", Serializer::Write<float>(Instance.Get_B()) },
			{"Alpha", Serializer::Write<float>(Instance.Get_A())}
		};
	}

	//NOTE : Implement Base Type
	template<> inline bool& Serializer::Read(const JSON& Json_Context, bool& Instance) {
		if (Json_Context.is_null())
			return Instance;
		else
			return Instance = Json_Context.get<bool>();
	}

	template<> inline char& Serializer::Read(const JSON& Json_Context, char& Instance) {
		if (Json_Context.is_null())
			return Instance;
		else
			return Instance = Json_Context.get<char>();
	}

	template<> inline unsigned char& Serializer::Read(const JSON& Json_Context, unsigned char& Instance) {
		if (Json_Context.is_null())
			return Instance;
		else
			return Instance = Json_Context.get<unsigned char>();
	}

	template<> inline int& Serializer::Read(const JSON& Json_Context, int& Instance) {
		if (Json_Context.is_null())
			return Instance;
		else
			return Instance = Json_Context.get<int>();
	}

	template<> inline unsigned int& Serializer::Read(const JSON& Json_Context, unsigned int& Instance) {
		if (Json_Context.is_null())
			return Instance;
		else
			return Instance = Json_Context.get<unsigned int>();
	}

	template<> inline long& Serializer::Read(const JSON& Json_Context, long& Instance) {
		if (Json_Context.is_null())
			return Instance;
		else
			return Instance = Json_Context.get<long>();
	}

	template<> inline unsigned long& Serializer::Read(const JSON& Json_Context, unsigned long& Instance) {
		if (Json_Context.is_null())
			return Instance;
		else
			return Instance = Json_Context.get<unsigned long>();
	}

	template<> inline long long& Serializer::Read(const JSON& Json_Context, long long& Instance) {
		if (Json_Context.is_null())
			return Instance;
		else
			return Instance = Json_Context.get<long long>();
	}

	template<> inline float& Serializer::Read(const JSON& Json_Context, float& Instance) {
		if (Json_Context.is_null())
			return Instance;
		else
			return Instance = Json_Context.get<float>();
	}

	template<> inline double& Serializer::Read(const JSON& Json_Context, double& Instance) {
		if (Json_Context.is_null())
			return Instance;
		else
			return Instance = Json_Context.get<double>();
	}

	//NOTE : STD Type
	template<> inline std::string& Serializer::Read(const JSON& Json_Context, std::string& Instance) {
		if (Json_Context.is_null())
			return Instance;
		else
			return Instance = Json_Context.get<std::string>();
	}

	template<> inline path& Serializer::Read(const JSON& Json_Context, path& Instance) {
		if (Json_Context.is_null())
			return Instance;
		else
			return Instance = path{ Json_Context.get<std::string>(),path::generic_format };
	}

	//NOTE: My Type
	template<> inline Radian& Serializer::Read(const JSON& Json_Context, Radian& Instance) {
		if (Json_Context.is_null())
			return Instance;
		else
			return Instance = Radian{ Json_Context.get<float>() };
	}

	template<> inline Degree& Serializer::Read(const JSON& Json_Context, Degree& Instance) {
		if (Json_Context.is_null())
			return Instance;
		else
			return Instance = Degree{ Json_Context.get<float>() };
	}

	template<> inline Vector2& Serializer::Read(const JSON& Json_Context, Vector2& Instance) {
		if (Json_Context.is_null())
			return Instance;
		else
			return Instance = Vector2{
				Json_Context["X"].get<float>(),
				Json_Context["Y"].get<float>()
		};
	}

	template<> inline Vector3& Serializer::Read(const JSON& Json_Context, Vector3& Instance) {
		if (Json_Context.is_null())
			return Instance;
		else
			return Instance = Vector3{
				Json_Context["X"].get<float>(),
				Json_Context["Y"].get<float>(),
				Json_Context["Z"].get<float>()
		};
	}

	template<> inline Vector4& Serializer::Read(const JSON& Json_Context, Vector4& Instance) {
		if (Json_Context.is_null())
			return Instance;
		else
			return Instance = Vector4{
				Json_Context["X"].get<float>(),
				Json_Context["Y"].get<float>(),
				Json_Context["Z"].get<float>(),
				Json_Context["W"].get<float>()
		};
	}

	template<> inline Matrix3x3& Serializer::Read(const JSON& Json_Context, Matrix3x3& Instance) {
		if (Json_Context.is_null())
			return Instance;
		else
			return Instance = Matrix3x3{
				Json_Context["M11"].get<float>(), Json_Context["M12"].get<float>(), Json_Context["M13"].get<float>(),
				Json_Context["M21"].get<float>(), Json_Context["M22"].get<float>(), Json_Context["M23"].get<float>(),
				Json_Context["M31"].get<float>(), Json_Context["M32"].get<float>(), Json_Context["M33"].get<float>()
		};
	}

	template<> inline Matrix4x4& Serializer::Read(const JSON& Json_Context, Matrix4x4& Instance) {
		if (Json_Context.is_null())
			return Instance;
		else
			return Instance = Matrix4x4{
				Json_Context["M11"].get<float>(), Json_Context["M12"].get<float>(), Json_Context["M13"].get<float>(), Json_Context["M14"].get<float>(),
				Json_Context["M21"].get<float>(), Json_Context["M22"].get<float>(), Json_Context["M23"].get<float>(), Json_Context["M24"].get<float>(),
				Json_Context["M31"].get<float>(), Json_Context["M32"].get<float>(), Json_Context["M33"].get<float>(), Json_Context["M34"].get<float>(),
				Json_Context["M41"].get<float>(), Json_Context["M42"].get<float>(), Json_Context["M43"].get<float>(), Json_Context["M44"].get<float>()
		};
	}

	template<> inline Quaternion& Serializer::Read(const JSON& Json_Context, Quaternion& Instance) {
		if (Json_Context.is_null())
			return Instance;
		else
			return Instance = Quaternion{
				Json_Context["S"].get<float>(),
				Json_Context["X"].get<float>(),
				Json_Context["Y"].get<float>(),
				Json_Context["Z"].get<float>()
		};
	}

	template<> inline Orthogonal_Transform& Serializer::Read(const JSON& Json_Context, Orthogonal_Transform& Instance) {
		if (Json_Context.is_null())
			return Instance;
		else {
			Quaternion Temp_Rotation{};
			Vector3 Temp_Translation{};

			return Instance = Orthogonal_Transform{
				Serializer::Read<Quaternion>(Json_Context["Rotation"], Temp_Rotation),
				Serializer::Read<Vector3>(Json_Context["Translation"], Temp_Translation)
			};
		}
	}

	template<> inline ScaleTranslation_Transform& Serializer::Read(const JSON& Json_Context, ScaleTranslation_Transform& Instance) {
		if (Json_Context.is_null())
			return Instance;
		else {
			float Temp_Scale{};
			Vector3 Temp_Translation{};
			return Instance = ScaleTranslation_Transform{
				Serializer::Read<float>(Json_Context["Scale"], Temp_Scale),
				Serializer::Read<Vector3>(Json_Context["Translation"], Temp_Translation)
			};
		}
	}

	template<> inline Uniform_Transform& Serializer::Read(const JSON& Json_Context, Uniform_Transform& Instance) {
		if (Json_Context.is_null())
			return Instance;
		else {
			Quaternion Temp_Rotation{};
			float Temp_Scale{};
			Vector3 Temp_Translation{};
			return Instance = Uniform_Transform{
				Serializer::Read<Quaternion>(Json_Context["Rotation"], Temp_Rotation),
				Serializer::Read<float>(Json_Context["Scale"], Temp_Scale),
				Serializer::Read<Vector3>(Json_Context["Translation"], Temp_Translation)
			};
		}
	}

	template<> inline Affine_Transform& Serializer::Read(const JSON& Json_Context, Affine_Transform& Instance) {
		if (Json_Context.is_null())
			return Instance;
		else {
			Matrix3x3 Temp_Basis{};
			Vector3 Temp_Translation{};
			return Instance = Affine_Transform{
				Serializer::Read<Matrix3x3>(Json_Context["Basis"], Temp_Basis),
				Serializer::Read<Vector3>(Json_Context["Translation"], Temp_Translation)
			};
		}
	}

	template<> inline AxisAligned_Bounding_Box& Serializer::Read(const JSON& Json_Context, AxisAligned_Bounding_Box& Instance) {
		if (Json_Context.is_null())
			return Instance;
		else {
			Vector3 Temp_Min{};
			Vector3 Temp_Max{};
			return Instance = AxisAligned_Bounding_Box{
				Serializer::Read<Vector3>(Json_Context["Min"], Temp_Min),
				Serializer::Read<Vector3>(Json_Context["Max"], Temp_Max)
			};
		}
	}

	template<> inline Oriented_Bounding_Box& Serializer::Read(const JSON& Json_Context, Oriented_Bounding_Box& Instance) {
		if (Json_Context.is_null())
			return Instance;
		else {
			Affine_Transform Temp_Transform{};
			return Instance = Oriented_Bounding_Box{
				Serializer::Read<Affine_Transform>(Json_Context["Transform"], Temp_Transform)
			};
		}
	}

	template<> inline Bounding_Plane& Serializer::Read(const JSON& Json_Context, Bounding_Plane& Instance) {
		if (Json_Context.is_null())
			return Instance;
		else {
			Vector3 Temp_Normal{};
			Vector3 Temp_Point{};
			return Instance = Bounding_Plane{
				Serializer::Read<Vector3>(Json_Context["Normal"], Temp_Normal),
				Serializer::Read<Vector3>(Json_Context["Point"], Temp_Point)
			};
		}
	}

	template<> inline Bounding_Sphere& Serializer::Read(const JSON& Json_Context, Bounding_Sphere& Instance) {
		if (Json_Context.is_null())
			return Instance;
		else {
			Vector3 Temp_Center{};
			float Temp_Radius{};
			return Instance = Bounding_Sphere{
				Serializer::Read<Vector3>(Json_Context["Center"], Temp_Center),
				Serializer::Read<float>(Json_Context["Radius"], Temp_Radius)
			};
		}
	}

	template<> inline Color& Serializer::Read(const JSON& Json_Context, Color& Instance) {
		if (Json_Context.is_null())
			return Instance;
		else {
			float Temp_R{};
			float Temp_G{};
			float Temp_B{};
			float Temp_A{};
			return Instance = Color{
				Serializer::Read<float>(Json_Context["Red"], Temp_R),
				Serializer::Read<float>(Json_Context["Green"], Temp_G),
				Serializer::Read<float>(Json_Context["Blue"], Temp_B),
				Serializer::Read<float>(Json_Context["Alpha"], Temp_A)
			};
		}
	}

}// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer