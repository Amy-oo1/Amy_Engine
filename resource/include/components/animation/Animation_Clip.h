#pragma once

#include<vector>
#include<string>
#include<cstddef>

#include "meta/reflection/Reflection_Macro.h"

#include "file/File_System.h"
#include "transform/Affine_Transform.h"

namespace NameSpace_Resource::NameSpace_Components {
	using std::vector;
	using std::string;

	using NameSpace_Core::NameSpace_Transform::Affine_Transform;
	using  NameSpace_Platform::NameSpace_File::path;

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

		vector<float> m_Time{};
		Affine_Transform m_Transform{ Affine_Transform::IDENTITY };

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
		vector<Animation_Channel> m_Node_Channels{};

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
		Animation_Node_Map m_Node_Map{};
		vector<Animation_Clip> m_Clips{};
	};


}// namespace NameSpace_Resource::NameSpace_Components
