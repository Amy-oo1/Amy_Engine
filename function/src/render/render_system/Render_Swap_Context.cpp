#include "render/render_system/Render_Swap_Context.h"

#include<utility>
#include<exception>

namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System {

	using std::runtime_error;

	void Game_Object_Resource_Desc::Add(const Game_Object_Desc& Game_Object_Desc) {
		Game_Object_Descs.push_back(Game_Object_Desc);
	}

	void Game_Object_Resource_Desc::Pop(void) {
		Game_Object_Descs.pop_front();
	}

	bool Game_Object_Resource_Desc::Is_Empty(void) const {
		return Game_Object_Descs.empty();
	}

	const Game_Object_Desc& Game_Object_Resource_Desc::Get_Next_Process_Object(void) const {
		return Game_Object_Descs.front();
	}

	void Particle_Submit_Request::Add(const Particle_Emitter_Desc& Emitter_Desc) {
		Emitter_Descs.push_back(Emitter_Desc);
	}

	unsigned int Particle_Submit_Request::Get_Emitter_Count(void) const {
		return static_cast<unsigned int>(Emitter_Descs.size());
	}

	const Particle_Emitter_Desc& Particle_Submit_Request::Get_Emitter_Desc(unsigned int Index) const {
		return Emitter_Descs[Index];
	}

	void Emitter_Transform_Request::Add(const Particle_Emitter_Transform_Desc& Emitter_Transform_Desc) {
		this->Emitter_Transform_Descs.push_back(Emitter_Transform_Desc);
	}

	void Emitter_Transform_Request::Clear(void) {
		this->Emitter_Transform_Descs.clear();
	}

	unsigned int Emitter_Transform_Request::Get_Emitter_Transform_Count(void) const {
		return static_cast<unsigned int>(this->Emitter_Transform_Descs.size());
	}

	const Particle_Emitter_Transform_Desc& Emitter_Transform_Request::Get_Next_Emitter_Transform_Desc(unsigned int Index) const {
		return this->Emitter_Transform_Descs[Index];
	}

	void Render_SwapData::Add_Dierty_Game_Object(const Game_Object_Desc& Game_Object_Desc) {
		if (!this->GO_Resource_Desc.has_value())
			this->GO_Resource_Desc = std::make_optional(Game_Object_Resource_Desc());

		this->GO_Resource_Desc->Add(Game_Object_Desc);
	}

	void Render_SwapData::Add_Delete_Game_Object(const Game_Object_Desc& Game_Object_Desc) {
		if (!this->GO_Resource_To_Delete.has_value())
			this->GO_Resource_To_Delete = std::make_optional(Game_Object_Resource_Desc());
		this->GO_Resource_To_Delete->Add(Game_Object_Desc);
	}

	void Render_SwapData::Add_Particle_Emitter(const Particle_Emitter_Desc& Emitter_Desc) {
		if (!this->m_Particle_Submit_Request.has_value())
			this->m_Particle_Submit_Request = std::make_optional(Particle_Submit_Request());
		this->m_Particle_Submit_Request->Add(Emitter_Desc);
	}

	void Render_SwapData::Add_Emitter_Tick_Request(const Particle_Emitter_ID& Emitter_ID) {
		if (!this->m_Emitter_Tick_Request.has_value())
			this->m_Emitter_Tick_Request = std::make_optional(Emitter_Tick_Request());
		this->m_Emitter_Tick_Request->Emitter_IDs.push_back(Emitter_ID);
	}

	void Render_SwapData::Add_Emitter_Transform_Request(const Particle_Emitter_Transform_Desc& Emitter_Transform_Desc) {
		if (!this->m_Emitter_Transform_Request.has_value())
			this->m_Emitter_Transform_Request = std::make_optional(Emitter_Transform_Request());
		this->m_Emitter_Transform_Request->Add(Emitter_Transform_Desc);
	}

	Render_SwapData& Render_Swap_Context::Get_SwapData(SWAPDATA_TYPE Type) {
		switch (Type)
		{
		case SWAPDATA_TYPE::SWAPDATA_TYPE_LOGIC:
			return this->m_SwapData[this->m_Logic_SwapData_Index];
		case SWAPDATA_TYPE::SWAPDATA_TYPE_RENDER:
			return m_SwapData[this->m_Render_SwapData_Index];
		case SWAPDATA_TYPE::SWAPDATA_TYPE_COUNT:
			throw runtime_error("Invalid SWAPDATA_TYPE");
		default:
			throw runtime_error("Invalid SWAPDATA_TYPE");
		}
	}

	void Render_Swap_Context::Swap_Logic_Render_Data(void) {
		if (this->Is_Ready_To_Swap())
			this->Swap();
	}

	void Render_Swap_Context::Reset_Level_Resource_SwapData(void) {
		m_SwapData[m_Render_SwapData_Index].Level_Resource_Desc.reset();
	}

	void Render_Swap_Context::Reset_Game_Object_Resource_SwapData(void) {
		m_SwapData[m_Render_SwapData_Index].GO_Resource_Desc.reset();
	}

	void Render_Swap_Context::Reset_Game_Object_Resource_To_Delete_SwapData(void) {
		m_SwapData[m_Render_SwapData_Index].GO_Resource_To_Delete.reset();
	}

	void Render_Swap_Context::Reset_Camera_SwapData(void) {
		m_SwapData[m_Render_SwapData_Index].Camera_SwapData.reset();
	}

	void Render_Swap_Context::Reset_Particle_Submit_Request_SwapData(void) {
		m_SwapData[m_Render_SwapData_Index].m_Particle_Submit_Request.reset();
	}

	void Render_Swap_Context::Reset_Emitter_Tick_Request_SwapData(void) {
		m_SwapData[m_Render_SwapData_Index].m_Emitter_Tick_Request.reset();
	}

	void Render_Swap_Context::Reset_Emitter_Transform_Request_SwapData(void) {
		m_SwapData[m_Render_SwapData_Index].m_Emitter_Transform_Request.reset();
	}

	bool Render_Swap_Context::Is_Ready_To_Swap(void) const {
		return
			this->m_SwapData[this->m_Render_SwapData_Index].Level_Resource_Desc.has_value() &&
			this->m_SwapData[this->m_Render_SwapData_Index].GO_Resource_Desc.has_value() &&
			this->m_SwapData[this->m_Render_SwapData_Index].GO_Resource_To_Delete.has_value() &&
			this->m_SwapData[this->m_Render_SwapData_Index].Camera_SwapData.has_value() &&
			this->m_SwapData[this->m_Render_SwapData_Index].m_Particle_Submit_Request.has_value() &&
			this->m_SwapData[this->m_Render_SwapData_Index].m_Emitter_Tick_Request.has_value() &&
			this->m_SwapData[this->m_Render_SwapData_Index].m_Emitter_Transform_Request.has_value();
	}

	void Render_Swap_Context::Swap(void) {
		this->Reset_Level_Resource_SwapData();
		this->Reset_Game_Object_Resource_SwapData();
		this->Reset_Game_Object_Resource_To_Delete_SwapData();
		this->Reset_Camera_SwapData();
		this->Reset_Particle_Submit_Request_SwapData();
		this->Reset_Emitter_Tick_Request_SwapData();
		this->Reset_Emitter_Transform_Request_SwapData();

		std::swap(this->m_Logic_SwapData_Index, this->m_Render_SwapData_Index);
	}

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System