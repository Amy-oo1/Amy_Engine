#pragma once

#include<cstdint>
#include<memory>
#include<string>
#include<optional>
#include<deque>
#include<array>
#include<vector>

#include "file/File_System.h"

#include "math/Matrix4x4.h"

#include "global/Global_Particle.h"
#include "global/Global_Rendering.h"

#include "particle/Emitter_ID_Allocator.h"
#include "particle/Particle_Desc.h"
#include "render/render_system/Render_Camera.h"
#include "render/render_system/Render_Obejct.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System {

	using std::array;
	using std::vector;
	using std::shared_ptr;
	using std::optional;

	using NameSpace_Platform::NameSpace_File::path;

	using NameSpace_Core::NameSpace_Math::Matrix4x4;

	using NameSpace_Resource::NameSpace_Global::SkyBox_Irradiance_Map;
	using NameSpace_Resource::NameSpace_Global::SkyBox_Specular_Map;

	using NameSpace_Particle::Particle_Emitter_ID;
	using NameSpace_Particle::Particle_Emitter_Desc;
	using NameSpace_Particle::Particle_Emitter_Transform_Desc;

	struct Levle_IBL_Resource_Desc final {
		shared_ptr<SkyBox_Irradiance_Map> Irradiance_Map{ nullptr };
		shared_ptr<SkyBox_Specular_Map> Specular_Map{ nullptr };
		path BRDF_Map_URL;

	};

	struct Level_Coror_Grading_Resource_Desc final {
		path Color_Grading_Map_URL;

	};

	struct Level_Resource_Desc final {
		Levle_IBL_Resource_Desc IBL_Resource_Desc;
		Level_Coror_Grading_Resource_Desc Color_Grading_Resource_Desc;

	};

	struct Camera_SwapData final {
		optional<float> FOV_X;
		optional<RENDER_CAMERA_TYPE> Camera_Type;
		optional<Matrix4x4> View_Matrix;

	};

	struct Game_Object_Resource_Desc final {
		std::deque<Game_Object_Desc> Game_Object_Descs;

		void Add(const Game_Object_Desc& Game_Object_Desc);
		void Pop(void);

		bool Is_Empty(void) const;

		const Game_Object_Desc& Get_Next_Process_Object(void) const;
	};

	struct Emitter_Tick_Request final {
		vector<Particle_Emitter_ID> Emitter_IDs;

	};

	struct Particle_Submit_Request final {
		vector<Particle_Emitter_Desc> Emitter_Descs;

		void Add(const Particle_Emitter_Desc& Emitter_Desc);

		unsigned int Get_Emitter_Count(void) const;

		const Particle_Emitter_Desc& Get_Emitter_Desc(unsigned int Index) const;
	};

	struct Emitter_Transform_Request final {
		vector<Particle_Emitter_Transform_Desc> Emitter_Transform_Descs;

		void Add(const Particle_Emitter_Transform_Desc& Emitter_Transform_Desc);

		void Clear(void);

		unsigned int Get_Emitter_Transform_Count(void) const;

		const Particle_Emitter_Transform_Desc& Get_Next_Emitter_Transform_Desc(unsigned int Index) const;

	};

	struct Render_SwapData final {
		optional<Level_Resource_Desc> Level_Resource_Desc;
		optional<Game_Object_Resource_Desc> GO_Resource_Desc;
		optional<Game_Object_Resource_Desc> GO_Resource_To_Delete;
		optional<Camera_SwapData> Camera_SwapData;
		optional<Particle_Submit_Request> m_Particle_Submit_Request;
		optional<Emitter_Tick_Request> m_Emitter_Tick_Request;
		optional<Emitter_Transform_Request> m_Emitter_Transform_Request;

		void Add_Dierty_Game_Object(const Game_Object_Desc& Game_Object_Desc);

		void Add_Delete_Game_Object(const Game_Object_Desc& Game_Object_Desc);

		void Add_Particle_Emitter(const Particle_Emitter_Desc& Emitter_Desc);

		void Add_Emitter_Tick_Request(const Particle_Emitter_ID& Emitter_ID);

		void Add_Emitter_Transform_Request(const Particle_Emitter_Transform_Desc& Emitter_Transform_Desc);
	};

	class Render_Swap_Context final {
	public:
		enum class SWAPDATA_TYPE :uint32_t {
			SWAPDATA_TYPE_LOGIC = 0,
			SWAPDATA_TYPE_RENDER,
			SWAPDATA_TYPE_COUNT
		};

		const Render_SwapData& Get_SwapData(SWAPDATA_TYPE Type) const;

		void Swap_Logic_Render_Data(void);

		void Reset_Level_Resource_SwapData(void);
		void Reset_Game_Object_Resource_SwapData(void);
		void Reset_Game_Object_Resource_To_Delete_SwapData(void);
		void Reset_Camera_SwapData(void);
		void Reset_Particle_Submit_Request_SwapData(void);
		void Reset_Emitter_Tick_Request_SwapData(void);
		void Reset_Emitter_Transform_Request_SwapData(void);

	private:
		uint32_t m_Logic_SwapData_Index{ static_cast<uint32_t>(SWAPDATA_TYPE::SWAPDATA_TYPE_LOGIC) };
		uint32_t m_Render_SwapData_Index{ static_cast<uint32_t>(SWAPDATA_TYPE::SWAPDATA_TYPE_RENDER) };
		array<Render_SwapData, static_cast<uint32_t>(SWAPDATA_TYPE::SWAPDATA_TYPE_COUNT)>  m_SwapData;

		bool Is_Ready_To_Swap(void)const;
		void Swap(void);
	};

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System