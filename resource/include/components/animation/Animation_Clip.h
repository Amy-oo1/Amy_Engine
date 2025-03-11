#pragma once

#include<vector>
#include<string>
#include<memory>
#include<cstddef>

#include "meta/reflection/Reflection_Macro.h"

#include "file/File_System.h"
#include "math/Vector3.h"
#include "math/Quaternion.h"
#include "transform/Affine_Transform.h"

namespace NameSpace_Resource::NameSpace_Components {

	using std::vector;
	using std::string;
	using std::shared_ptr;

	using  NameSpace_Platform::NameSpace_File::path;
	using NameSpace_Core::NameSpace_Math::Vector3;
	using NameSpace_Core::NameSpace_Math::Quaternion;
	using NameSpace_Core::NameSpace_Transform::Affine_Transform;


	REFLECTION_HEADER(Animation_Node_Map);
	REFLECTION_CLASS(Animation_Node_Map, All) final
	{
		REFLECTION_BODY(Animation_Node_Map);
	public:
		Animation_Node_Map(void) = default;

		~Animation_Node_Map(void) = default;

	private:
		vector<string> m_onvert{};

	};

	REFLECTION_HEADER(Animation_Channel);
	REFLECTION_CLASS(Animation_Channel, All) final
	{
		REFLECTION_BODY(Animation_Channel);
	public:
		Animation_Channel(void) = default;

		~Animation_Channel(void) = default;

	private:
		string m_Name{};

		vector<Vector3> m_Positions_Keys{};
		vector<Quaternion> m_Rotations_Keys{};
		vector<Vector3> m_Scales_Keys{};

	};

	REFLECTION_HEADER(Animation_Clip);
	REFLECTION_CLASS(Animation_Clip, All) final
	{
		REFLECTION_BODY(Animation_Clip);
	public:
		Animation_Clip(void) = default;

		~Animation_Clip(void) = default;

	private:
		size_t Total_Frame{ 0 };
		vector<shared_ptr<Animation_Channel>> m_Node_Channels{};

	};

	REFLECTION_HEADER(Animation_Data);
	REFLECTION_CLASS(Animation_Data, All) final
	{
		REFLECTION_BODY(Animation_Data);
	public:
		Animation_Data(void) = default;

		~Animation_Data(void) = default;

	private:
		path m_Skeleton_File_Path{};
		shared_ptr<Animation_Node_Map> m_Node_Map{};
		vector<shared_ptr<Animation_Clip>> m_Clips{};
	};


}// namespace NameSpace_Resource::NameSpace_Components
