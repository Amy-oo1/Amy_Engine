#pragma once

#include<vector>
#include<memory>
#include<utility>


#include "meta/reflection/Reflection_Macro.h"

#include "components/mesh/Mesh.h"

#include "frame/components/Component.h"

#include "render/render_system/Render_Obejct.h"


namespace NameSpace_Function::NameSpace_Frame::NameSpace_Components {

	using std::vector;
	using std::shared_ptr;
	using std::weak_ptr;

	using NameSpace_Resource::NameSpace_Components::Mesh_Sub;
	using NameSpace_Resource::NameSpace_Components::Mesh_Resource;

	using NameSpace_Render::NameSpace_Render_System::Game_Object_Part_Desc;

	REFLECTION_HEADER(Mesh_Component);
	REFLECTION_CLASS(Mesh_Component, All) final : public Component
	{
		REFLECTION_BODY(Mesh_Component);
	public:
		Mesh_Component(void) = default;

		~Mesh_Component(void) = default;

	public:
		void Post_Load_Resource(weak_ptr<GObject> Parent_Object) override;
		
		void Tick(float Delta_Time) override;

	private:
		shared_ptr<Mesh_Resource> m_Mesh_Res;

		META(Disable) vector<shared_ptr<Game_Object_Part_Desc>> m_Raw_Meshes{};
	};
}