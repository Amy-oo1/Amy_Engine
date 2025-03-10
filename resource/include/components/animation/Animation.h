#pragma once

#include<vector>
#include<string>
#include<cstddef>

#include "meta/reflection/Reflection_Macro.h"

#include "file/File_System.h"
#include "transform/Affine_Transform.h"
#include "components/animation/Blend_State.h"

namespace NameSpace_Resource::NameSpace_Components {

	using std::vector;
	using std::string;

	using NameSpace_Core::NameSpace_Transform::Affine_Transform;
	using  NameSpace_Platform::NameSpace_File::path;

	REFLECTION_HEADER(Animation_Effect_Element);
	REFLECTION_CLASS(Animation_Effect_Element, All) final
	{
		REFLECTION_BODY(Animation_Effect_Element);
	public:
		Animation_Effect_Element(void) = default;

		~Animation_Effect_Element(void) = default;

	private:
		size_t m_Index;
		Affine_Transform m_Transform{ Affine_Transform::IDENTITY };

	};

	REFLECTION_HEADER(Animation_Effect);
	REFLECTION_CLASS(Animation_Effect, All) final
	{
		REFLECTION_BODY(Animation_Effect);
	public:
		Animation_Effect(void) = default;

		~Animation_Effect(void) = default;

	private:
		vector<Animation_Effect_Element> m_Effects{};

	};

	REFLECTION_HEADER(Animation_Component_Res);
	REFLECTION_CLASS(Animation_Component_Res, All) final
	{
		REFLECTION_BODY(Animation_Component_Res);
	public:
		Animation_Component_Res(void) = default;

		~Animation_Component_Res(void) = default;

	private:
		path m_skeleton_File_Path{};

		Blend_State m_Blend_State{};

		Animation_Effect m_Effect{};

	};

}// namespace NameSpace_Resource::NameSpace_Components
