#pragma once

#include<string>
#include<vector>
#include<unordered_map>
#include<memory>

#include "file/File_System.h"

#include "bounding/Bounding_Box_AxisAligned.h"

#include "render/rhi/empty_rhi/Empty_RHI.h"
#include "render/render_system/Render_Data_Struct.h"
#include "render/render_system/Render_Entity.h"
#include "render/render_system/Render_Camera.h"
#include "render/render_system/Render_Swap_Context.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System {

	//TODO : Remove
	class Render_Scene;

	using std::shared_ptr;
	using std::unordered_map;

	using NameSpace_Platform::NameSpace_File::path;

	using NameSpace_RHI::Empty_RHI;


	class Render_Resource_Base {
	private:
		Render_Resource_Base(const Render_Resource_Base&) = delete;
		Render_Resource_Base& operator=(const Render_Resource_Base&) = delete;

	public:
		Render_Resource_Base(void) = default;

		virtual ~Render_Resource_Base(void) = default;

	public:
		static shared_ptr<Texture_Data>
			Load_Texture_HDR(const path& Texture_URL, int desired_Channels = 4);

		static shared_ptr<Texture_Data>
			Load_Texture(const path& Texture_URL, bool Is_SRGB = false);

		const Render_Mesh_Data
			Load_Mesh(const path& Mesh_URL, AxisAligned_Bounding_Box& Bounding_Box);

		//TODO :
		static const Render_Material_Data
			Load_Material(const Material_Source_Desc& Sourec_Desc);

		const AxisAligned_Bounding_Box& Get_Bounding_Box(const path& Mesh_URL);

	private:
		static Static_Mesh_Data Load_Static_Mesh(const path& Mesh_URL, AxisAligned_Bounding_Box& Bounding_Box);

	private:
		unordered_map<path, AxisAligned_Bounding_Box>
			m_Bounding_Box_Cache;


	public:
		virtual void
			Upload_Global_Render_Resource(
				shared_ptr<Empty_RHI> RHI,
				const Level_Resource_Desc& Level_Resource_Desc
			) = 0;


		virtual void Upload_Game_Object_Render_Resource(
			shared_ptr<Empty_RHI> RHI,
			const Render_Entity& Render_Entity,
			const Render_Mesh_Data& Meshe_Data,
			const Render_Material_Data& Material_Data
		) = 0;


		virtual void Upload_Game_Object_Render_Resource(
			shared_ptr<Empty_RHI> RHI,
			const Render_Entity& Render_Entity,
			const Render_Mesh_Data& Meshe_Data
		) = 0;


		virtual void Upload_Game_Object_Render_Resource(
			shared_ptr<Empty_RHI> RHI,
			const Render_Entity& Render_Entity,
			const Render_Material_Data& Material_Data
		) = 0;


		virtual void Updata_Per_Frame_Buffer(
			shared_ptr<Render_Scene> Scene,
			shared_ptr<Render_Camera> Camera
		) = 0;

	};


}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System