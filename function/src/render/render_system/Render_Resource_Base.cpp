#include "render/render_system/Render_Resource_Base.h"

#include<exception>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include "logger/System_Logger.h"

#include "global/Global_Systemer.h"

#include "render/rhi/empty_rhi/RHI_Type.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System {

	using std::runtime_error;

	using NameSpace_Core::NameSpace_Logger::System_Logger;

	using Namespace_Global::Global_Systemer;

	using NameSpace_RHI::RHI_FORMAT;

	shared_ptr<Texture_Data> Render_Resource_Base::Load_Texture_HDR(const path& Texture_URL, int desired_Channels) const {

		static const auto Texture_Data_Deleter = [](void* Pixels) { stbi_image_free(Pixels); };
		shared_ptr<Texture_Data> Texture = std::make_shared<Texture_Data>();

		void* Pixels = nullptr;
		int width{}, height{}, channels{};
		Pixels = stbi_loadf(Global_Systemer::Get_Instance().Resource_Manager.URL_To_File_Full_Path(Texture_URL), &width, &height, &channels, desired_Channels);
		if (nullptr == Texture->Pixels)
			return nullptr;

		Texture->Pixels.reset(Pixels);
		Texture->Pixels.get_deleter() = Texture_Data_Deleter;

		Texture->Width = width;
		Texture->Height = height;

		switch (desired_Channels)
		{
		case 2:
			Texture->Format = RHI_FORMAT::RHI_FORMAT_R32G32B32_SFLOAT;
			break;
		case 4:
			Texture->Format = RHI_FORMAT::RHI_FORMAT_R32G32B32A32_SFLOAT;
			break;
		default:
			throw runtime_error("Invalid desired channels");
			break;
		}

		Texture->Depth = 1;
		Texture->Array_Layes = 1;
		Texture->Mip_Levels = 1;

		return Texture;
	}

	shared_ptr<Texture_Data> Render_Resource_Base::Load_Texture(const path& Texture_URL, bool Is_SRGB)const {
		static const auto Texture_Data_Deleter = [](void* Pixels) { stbi_image_free(Pixels); };

		shared_ptr<Texture_Data> Texture = std::make_shared<Texture_Data>();

		void* Pixels = nullptr;
		int width{}, height{}, channels{};
		Pixels = stbi_load(Global_Systemer::Get_Instance().Resource_Manager.URL_To_File_Full_Path(Texture_URL), &width, &height, &channels, 4);

		if (nullptr == Texture->Pixels)
			return nullptr;

		Texture->Pixels.reset(Pixels);
		Texture->Pixels.get_deleter() = Texture_Data_Deleter;

		Texture->Width = width;
		Texture->Height = height;
		Texture->Format = Is_SRGB ? RHI_FORMAT::RHI_FORMAT_R8G8B8A8_SRGB : RHI_FORMAT::RHI_FORMAT_R8G8B8A8_UNORM;

		Texture->Depth = 1;
		Texture->Array_Layes = 1;
		Texture->Mip_Levels = 1;

		return Texture;
	}

	const Render_Mesh_Data Render_Resource_Base::Load_Mesh(const path& Mesh_URL) const {

		//TODO : 
		//if (".obj" == Mesh_URL.extension())
		return Render_Mesh_Data{};
	}

	const Render_Material_Data Render_Resource_Base::Load_Material(const path& Material_URL) const {
		return Render_Material_Data();
	}

	Static_Mesh_Data Render_Resource_Base::Load_Static_Mesh(const path& Mesh_URL, AxisAligned_Bounding_Box& Bounding_Box) const {
		Static_Mesh_Data Mesh_Data{};

		tinyobj::ObjReader Reader{};
		tinyobj::ObjReaderConfig Reader_Config{};
		Reader_Config.vertex_color = false;

		if (false == Reader.ParseFromFile(Global_Systemer::Get_Instance().Resource_Manager.URL_To_File_Full_Path(Mesh_URL), Reader_Config)) {
			System_Logger::Get_Instance().Log(System_Logger::Level::err, "Failed to load mesh: " + Mesh_URL.string());

			throw runtime_error("Failed to load mesh");
		}

		if (false == Reader.Warning().empty())
			System_Logger::Get_Instance().Log(System_Logger::Level::warn, "Mesh loading warning: " + Reader.Warning());

		if (false == Reader.Error().empty())
			System_Logger::Get_Instance().Log(System_Logger::Level::err, "Mesh loading error: " + Reader.Error());

		auto& Attrib{ Reader.GetAttrib() };
		auto& Shapes{ Reader.GetShapes() };

		/*	vector<Mesh_Vertex_Data_Definition> Mesh_Vertex{};

			for (size_t Index_Shap = 0; Index_Shap < Shapes.size(); ++Index_Shap) {
				size_t Index_Offset{ 0 };

				for (size_t F = 0; F < Shapes[Index_Shap].mesh.num_face_vertices.size(); ++F) {
					size_t
				}

			}*/

			//TODO : 

		return Mesh_Data;

	}

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System