#pragma once

#include<malloc.h>
#include<cstdint>
#include<memory>
#include<functional>

#include "render/rhi/empty_rhi/RHI_Type.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System {

	using std::unique_ptr;
	using std::shared_ptr;
	using std::function;

	using NameSpace_RHI::RHI_FORMAT;

	struct Mesh_Vertex_Data_Definition final {
		float X, Y, Z;
		float NX, NY, NZ;
		float TX, TY, TZ;
		float U, V;
	};

	struct Mesh_Vertx_Binding_Data_Definition final {
		int Index0, Index1, Index2, Index3;
		float Weight0{ 0 }, Weight1{ 0 }, Weight2{ 0 }, Weight3{ 0 };
	};


	class Buffer_Data final {
	private:
		Buffer_Data(const Buffer_Data&) = delete;
		Buffer_Data& operator=(const Buffer_Data&) = delete;

	public:
		Buffer_Data(size_t Size) :
			Data_Size{ Size },
			Data{ malloc(Size) } {
		}


		~Buffer_Data() { if (nullptr != this->Data) { free(this->Data); } }

		bool Is_Valid(void)const { return nullptr != this->Data; }

		size_t Data_Size{ 0 };
		void* Data{ nullptr };

	};

	class Texture_Data final {
	private:
		Texture_Data(const Texture_Data&) = delete;
		Texture_Data& operator=(const Texture_Data&) = delete;

	public:
		Texture_Data(void) = default;

		~Texture_Data(void) = default;

		bool Is_Valid(void)const { return nullptr != this->Pixels; }

	public:
		uint32_t Width;
		uint32_t Height;
		uint32_t Depth;
		RHI_FORMAT Format;
		uint32_t Mip_Levels{ 0 };
		uint32_t Array_Layes{ 0 };
		unique_ptr<void, function<void(void*)>> Pixels{ nullptr };

	};

	struct Static_Mesh_Data final {
		shared_ptr<Buffer_Data> Vertex_Buffer;
		shared_ptr<Buffer_Data> Index_Buffer;

	};

	struct Render_Mesh_Data final {
		Static_Mesh_Data Static_Mesh_Data;
		shared_ptr<Buffer_Data> Skeletion_Binding_Buffer{nullptr};

	};

	struct Render_Material_Data final {
		shared_ptr<Texture_Data> Base_Color_Texture;
		shared_ptr<Texture_Data> Metallic_Roughness_Texture;
		shared_ptr<Texture_Data> Normal_Texture;
		shared_ptr<Texture_Data> Occlusion_Texture;
		shared_ptr<Texture_Data> Emissive_Texture;

	};



}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System