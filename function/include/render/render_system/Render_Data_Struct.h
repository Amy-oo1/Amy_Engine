#pragma once

#include<malloc.h>
#include<cstdint>
#include<memory>
#include<xhash>
#include<functional>

#include "file/File_System.h"

#include "render/rhi/empty_rhi/RHI_Type.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System {

	using std::unique_ptr;
	using std::shared_ptr;
	using std::function;

	using NameSpace_Platform::NameSpace_File::path;

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
		uint32_t Depth{ 1 };
		RHI_FORMAT Format{ RHI_FORMAT::RHI_FORMAT_UNDEFINED };
		uint32_t Mip_Levels{ 1 };
		uint32_t Array_Layes{ 1 };
		unique_ptr<void, function<void(void*)>> Pixels{ nullptr };

	};

	struct Static_Mesh_Data final {
		shared_ptr<Buffer_Data> Vertex_Buffer;
		shared_ptr<Buffer_Data> Index_Buffer;

	};

	struct Render_Mesh_Data final {
		Static_Mesh_Data Static_Mesh_Data;
		shared_ptr<Buffer_Data> Skeletion_Binding_Buffer{ nullptr };

	};

	struct Render_Material_Data final {
		shared_ptr<Texture_Data> Base_Color_Texture;
		shared_ptr<Texture_Data> Metallic_Roughness_Texture;
		shared_ptr<Texture_Data> Normal_Texture;
		shared_ptr<Texture_Data> Occlusion_Texture;
		shared_ptr<Texture_Data> Emissive_Texture;

	};

	struct Mesh_Source_Desc final {
		path Mesh_URL;
		bool operator==(const Mesh_Source_Desc& rhs) const {
			return
				this->Mesh_URL == rhs.Mesh_URL;
		}
		size_t Get_Has_Value(void)const {
			return
				std::hash<std::string>()(this->Mesh_URL.generic_string());
		}
	};


	struct Material_Source_Desc final {
		path Base_Color_URL;
		path Metallic_Roughness_URL;
		path Normal_URL;
		path Occlusion_URL;
		path Emissive_URL;

		bool operator==(const Material_Source_Desc& rhs) const {
			return
				this->Base_Color_URL == rhs.Base_Color_URL &&
				this->Metallic_Roughness_URL == rhs.Metallic_Roughness_URL &&
				this->Normal_URL == rhs.Normal_URL &&
				this->Occlusion_URL == rhs.Occlusion_URL &&
				this->Emissive_URL == rhs.Emissive_URL;
		}

		size_t Get_Has_Value(void)const {
			return
				std::hash<std::string>()(this->Base_Color_URL.string()) ^
				std::hash<std::string>()(this->Metallic_Roughness_URL.string()) ^
				std::hash<std::string>()(this->Normal_URL.string()) ^
				std::hash<std::string>()(this->Occlusion_URL.string()) ^
				std::hash<std::string>()(this->Emissive_URL.string());
		}
	};

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System

namespace std {

	template<>
	struct hash<NameSpace_Function::NameSpace_Render::NameSpace_Render_System::Mesh_Source_Desc> {
		size_t operator()(const NameSpace_Function::NameSpace_Render::NameSpace_Render_System::Mesh_Source_Desc& id) const {
			return id.Get_Has_Value();
		}
	};

	template<>
	struct hash<NameSpace_Function::NameSpace_Render::NameSpace_Render_System::Material_Source_Desc> {
		size_t operator()(const NameSpace_Function::NameSpace_Render::NameSpace_Render_System::Material_Source_Desc& id) const {
			return id.Get_Has_Value();
		}

	};

}// namespace std