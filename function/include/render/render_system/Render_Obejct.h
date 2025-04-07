#pragma once

#include<cstdint>
#include<limits>
#include<string>
#include<vector>
#include<memory>

#include "file/File_System.h"

#include "meta/reflection/Reflection_Macro.h"
#include "math/Matrix4x4.h"

#include "frame/object/GObject_ID_Allocator.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System {

	using std::string;
	using std::vector;
	using std::shared_ptr;

	using NameSpace_Platform::NameSpace_File::path;

	using NameSpace_Frame::NameSpace_GObject::GObject_ID;
	using NameSpace_Frame::NameSpace_GObject::GObject_ID_Allocator;

	using NameSpace_Core::NameSpace_Math::Matrix4x4;

	REFLECTION_HEADER(Game_Object_Mesh_Desc);
	REFLECTION_CLASS(Game_Object_Mesh_Desc, All) final
	{
		REFLECTION_BODY(Game_Object_Mesh_Desc);
	private:
		path m_Mesh_URL;

	};

	REFLECTION_HEADER(Skeleton_Binding_Desc);
	REFLECTION_CLASS(Skeleton_Binding_Desc, All) final
	{
		REFLECTION_BODY(Skeleton_Binding_Desc);
	private:
		path m_Skeleton_Binding_URL;

	};

	REFLECTION_HEADER(Skeleton_Animation_Result_Transform);
	REFLECTION_CLASS(Skeleton_Animation_Result_Transform, All) final
	{
		REFLECTION_BODY(Skeleton_Animation_Result_Transform);
	private:
		Matrix4x4 m_Matrix;

	};

	REFLECTION_HEADER(Skeleton_Animation_Result);
	REFLECTION_CLASS(Skeleton_Animation_Result, All) final
	{
		REFLECTION_BODY(Skeleton_Animation_Result);
	private:
		vector<shared_ptr<Skeleton_Animation_Result_Transform>> m_Transforms;

	};

	REFLECTION_HEADER(Game_Object_Material_Desc);
	REFLECTION_CLASS(Game_Object_Material_Desc, All) final
	{
		REFLECTION_BODY(Game_Object_Material_Desc);
	private:
		path m_Base_Color_URL;
		path m_Metallic_Roughness_URL;
		path m_Normal_URL;
		path m_Occlusion_URL;
		path m_Emissive_URL;
		bool m_Is_With_Texture{ false };

	};

	REFLECTION_HEADER(Game_Object_Transform_Desc);
	REFLECTION_CLASS(Game_Object_Transform_Desc, All) final
	{
		REFLECTION_BODY(Game_Object_Transform_Desc);
	private:
		Matrix4x4 m_Transform{ Matrix4x4::IDENTITY };

	};

	REFLECTION_HEADER(Game_Object_Part_Desc);
	REFLECTION_CLASS(Game_Object_Part_Desc, All) final
	{
		REFLECTION_BODY(Game_Object_Part_Desc);
	private:
		shared_ptr<Game_Object_Mesh_Desc> m_Mesh_Desc;
		shared_ptr<Game_Object_Material_Desc> m_Material_Desc;
		shared_ptr<Game_Object_Transform_Desc> m_Transform_Desc;
		//TODO :zhis is empty
		shared_ptr<Skeleton_Binding_Desc> m_Skeleton_Binding_Desc;
		shared_ptr<Skeleton_Animation_Result> m_Skeleton_Animation_Result;
		bool m_Is_With_Skeleton{ false };

	};

	struct Game_Object_Part_ID final {
		GObject_ID m_GO_ID{ GObject_ID_Allocator::INVALID_GOBJECT_ID };
		size_t m_Part_ID{ std::numeric_limits<size_t>::max() };

		bool operator==(const Game_Object_Part_ID& rhs) const {
			return
				m_GO_ID == rhs.m_GO_ID &&
				m_Part_ID == rhs.m_Part_ID;
		}

		size_t Get_Has_Value() const {
			return this->m_GO_ID ^ (this->m_Part_ID << 1);
		}

		bool Is_Valid() const {
			return
				this->m_GO_ID != GObject_ID_Allocator::INVALID_GOBJECT_ID &&
				this->m_Part_ID != std::numeric_limits<size_t>::max();
		}

	};

	class Game_Object_Desc final {
	public:
		Game_Object_Desc() = default;

		Game_Object_Desc(const GObject_ID& ID, const vector<shared_ptr<Game_Object_Part_Desc>>& Parts) :
			m_ID{ ID },
			m_Part_Descs{ Parts } {
		}

		const GObject_ID& Get_ID() const {
			return m_ID;
		}

		const vector<shared_ptr<Game_Object_Part_Desc>>& Get_Part_Descs() const {
			return m_Part_Descs;
		}

	private:
		GObject_ID m_ID{ GObject_ID_Allocator::INVALID_GOBJECT_ID };
		vector<shared_ptr<Game_Object_Part_Desc>> m_Part_Descs;

	};


}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System

namespace std {

	template<>
	struct hash<NameSpace_Function::NameSpace_Render::NameSpace_Render_System::Game_Object_Part_ID> {
		size_t operator()(const NameSpace_Function::NameSpace_Render::NameSpace_Render_System::Game_Object_Part_ID& id) const {
			return id.Get_Has_Value();
		}

	};

}// namespace std