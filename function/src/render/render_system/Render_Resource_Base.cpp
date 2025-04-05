#include "render/render_system/Render_Resource_Base.h"

#include<limits>
#include<exception>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include "logger/System_Logger.h"

#include "meta/generated/reflection/Mesh.Generated_Reflection.h"
#include "meta/generated/reflection/Mesh_Data.Generated_Reflection.h"

#include "components/mesh/Mesh_Data.h"
#include "config/Resource_Configer.h"
#include "manage/Resource_Manager.h"


#include "render/rhi/empty_rhi/RHI_Type.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System {

	using std::runtime_error;

	using NameSpace_Core::NameSpace_Logger::System_Logger;

	using NameSpace_Resource::NameSpace_Components::Mesh_Data;
	using NameSpace_Resource::NameSpace_Components::Mesh_Vertex;
	using NameSpace_Resource::NameSpace_Components::Meah_Skeleton_Binding;
	using NameSpace_Resource::NameSpace_Components::Reflection_Meah_Skeleton_Binding_Operator;
	using NameSpace_Resource::NameSpace_Components::Reflection_Mesh_Vertex_Operator;
	using NameSpace_Resource::NameSpace_Components::Reflection_Mesh_Data_Operator;

	using NameSpace_Resource::NameSpace_Config::Resource_Configer;
	using NameSpace_Resource::NameSpace_Manage::Resource_Manager;

	using NameSpace_RHI::RHI_FORMAT;

	shared_ptr<Texture_Data> Render_Resource_Base::Load_Texture_HDR(const path& Texture_URL, int desired_Channels) {

		static const auto Texture_Data_Deleter = [](void* Pixels) { stbi_image_free(Pixels); };
		shared_ptr<Texture_Data> Texture = std::make_shared<Texture_Data>();

		void* Pixels = nullptr;
		int width{}, height{}, channels{};
		Pixels = stbi_loadf(Resource_Manager::URL_To_File_Full_Path(Texture_URL).generic_string().c_str(), &width, &height, &channels, desired_Channels);
		if (nullptr == Pixels)
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

		//NOTE : Default
		/*Texture->Depth = 1;
		Texture->Array_Layes = 1;
		Texture->Mip_Levels = 1;*/

		return Texture;
	}

	shared_ptr<Texture_Data> Render_Resource_Base::Load_Texture(const path& Texture_URL, bool Is_SRGB) {
		static const auto Texture_Data_Deleter = [](void* Pixels) { stbi_image_free(Pixels); };

		shared_ptr<Texture_Data> Texture = std::make_shared<Texture_Data>();

		void* Pixels = nullptr;
		int width{}, height{}, channels{};
		Pixels = stbi_load(Resource_Manager::URL_To_File_Full_Path(Texture_URL).generic_string().c_str(), &width, &height, &channels, 4);

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

	const Render_Mesh_Data Render_Resource_Base::Load_Mesh(const path& Mesh_URL, AxisAligned_Bounding_Box& Bounding_Box) {
		Render_Mesh_Data Ret{};
		if (".obj" == Mesh_URL.extension())
			Ret.Static_Mesh_Data = Render_Resource_Base::Load_Static_Mesh(Mesh_URL, Bounding_Box);
		else if (".json" == Mesh_URL.extension()) {
			auto Bind_Data{ Resource_Manager::Load<Mesh_Data>(Mesh_URL) };

			//NOTE : Vertex Buffer
			{
				const auto& Vertexs_Buffer{ Reflection_Mesh_Data_Operator::Get_Vertices_Buffer_Attribute(Bind_Data) };
				size_t Vertex_Size{ Vertexs_Buffer.size() * sizeof(Mesh_Vertex_Data_Definition) };
				Ret.Static_Mesh_Data.Vertex_Buffer = std::make_shared<Buffer_Data>(Vertex_Size);

				Mesh_Vertex_Data_Definition* Ref_Vertex_Data =
					static_cast<Mesh_Vertex_Data_Definition*>(Ret.Static_Mesh_Data.Vertex_Buffer->Data);
				for (size_t Index = 0; Index < Vertexs_Buffer.size(); ++Index)
				{
					Ref_Vertex_Data[Index].X = Reflection_Mesh_Vertex_Operator::Get_Position_Attribute(Vertexs_Buffer[Index]).Get_X();
					Ref_Vertex_Data[Index].Y = Reflection_Mesh_Vertex_Operator::Get_Position_Attribute(Vertexs_Buffer[Index]).Get_Y();
					Ref_Vertex_Data[Index].Z = Reflection_Mesh_Vertex_Operator::Get_Position_Attribute(Vertexs_Buffer[Index]).Get_Z();

					Ref_Vertex_Data[Index].NX = Reflection_Mesh_Vertex_Operator::Get_Normal_Attribute(Vertexs_Buffer[Index]).Get_X();
					Ref_Vertex_Data[Index].NY = Reflection_Mesh_Vertex_Operator::Get_Normal_Attribute(Vertexs_Buffer[Index]).Get_Y();
					Ref_Vertex_Data[Index].NZ = Reflection_Mesh_Vertex_Operator::Get_Normal_Attribute(Vertexs_Buffer[Index]).Get_Z();

					Ref_Vertex_Data[Index].TX = Reflection_Mesh_Vertex_Operator::Get_Tangent_Attribute(Vertexs_Buffer[Index]).Get_X();
					Ref_Vertex_Data[Index].TY = Reflection_Mesh_Vertex_Operator::Get_Tangent_Attribute(Vertexs_Buffer[Index]).Get_Y();
					Ref_Vertex_Data[Index].TZ = Reflection_Mesh_Vertex_Operator::Get_Tangent_Attribute(Vertexs_Buffer[Index]).Get_Z();

					Ref_Vertex_Data[Index].U = Reflection_Mesh_Vertex_Operator::Get_Texture_Coordinate_Attribute(Vertexs_Buffer[Index])[0];
					Ref_Vertex_Data[Index].V = Reflection_Mesh_Vertex_Operator::Get_Texture_Coordinate_Attribute(Vertexs_Buffer[Index])[1];

					Bounding_Box.Add_Point(Reflection_Mesh_Vertex_Operator::Get_Position_Attribute(Vertexs_Buffer[Index]));
				}
			}

			// NOTE : Index_Buffer
			{
				const auto& Index_Buffer{ Reflection_Mesh_Data_Operator::Get_Indices_Buffer_Attribute(Bind_Data) };
				size_t Index_Size{ Index_Buffer.size() * sizeof(uint16_t) };
				Ret.Static_Mesh_Data.Index_Buffer = std::make_shared<Buffer_Data>(Index_Size);

				uint16_t* Ref_Index_Data = static_cast<uint16_t*>(Ret.Static_Mesh_Data.Index_Buffer->Data);
				for (size_t Index = 0; Index < Index_Buffer.size(); ++Index)
					Ref_Index_Data[Index] = static_cast<uint16_t>(Index_Buffer[Index]);
			}

			// NOTE : Skeleton Binding Buffer
			{
				const auto& Skeleton_Bindings{ Reflection_Mesh_Data_Operator::Get_Skeleton_Bindings_Attribute(Bind_Data) };
				size_t data_size = Skeleton_Bindings.size() * sizeof(Mesh_Vertx_Binding_Data_Definition);
				Ret.Skeletion_Binding_Buffer = std::make_shared<Buffer_Data>(data_size);

				Mesh_Vertx_Binding_Data_Definition* Ref_Binding_Data =
					reinterpret_cast<Mesh_Vertx_Binding_Data_Definition*>(Ret.Skeletion_Binding_Buffer->Data);

				for (size_t Index = 0; Index < Skeleton_Bindings.size(); ++Index) {
					Ref_Binding_Data[Index].Index0 = Reflection_Meah_Skeleton_Binding_Operator::Get_Bone_Indices_Attribute(Skeleton_Bindings[Index])[0];
					Ref_Binding_Data[Index].Index1 = Reflection_Meah_Skeleton_Binding_Operator::Get_Bone_Indices_Attribute(Skeleton_Bindings[Index])[1];
					Ref_Binding_Data[Index].Index2 = Reflection_Meah_Skeleton_Binding_Operator::Get_Bone_Indices_Attribute(Skeleton_Bindings[Index])[2];
					Ref_Binding_Data[Index].Index3 = Reflection_Meah_Skeleton_Binding_Operator::Get_Bone_Indices_Attribute(Skeleton_Bindings[Index])[3];

					Ref_Binding_Data[Index].Weight0 = Reflection_Meah_Skeleton_Binding_Operator::Get_Weights_Attribute(Skeleton_Bindings[Index])[0];
					Ref_Binding_Data[Index].Weight1 = Reflection_Meah_Skeleton_Binding_Operator::Get_Weights_Attribute(Skeleton_Bindings[Index])[1];
					Ref_Binding_Data[Index].Weight2 = Reflection_Meah_Skeleton_Binding_Operator::Get_Weights_Attribute(Skeleton_Bindings[Index])[2];
					Ref_Binding_Data[Index].Weight3 = Reflection_Meah_Skeleton_Binding_Operator::Get_Weights_Attribute(Skeleton_Bindings[Index])[3];
				}
			}
		}
		else {
			System_Logger::Get_Instance().Log(System_Logger::Level::err, "Invalid mesh file type: {}", Mesh_URL.generic_string());

			throw runtime_error("Invalid mesh file type");
		}

		this->m_Bounding_Box_Cache[Mesh_URL] = Bounding_Box;

		return Ret;
	}

	const Render_Material_Data Render_Resource_Base::Load_Material(const Material_Source_Desc& Sourec_Desc) {
		Render_Material_Data Ret{};
		{
			if (!Sourec_Desc.Base_Color_URL.empty())
				Ret.Base_Color_Texture = Render_Resource_Base::Load_Texture(Sourec_Desc.Base_Color_URL, true);
			if (Sourec_Desc.Metallic_Roughness_URL.empty())
				Ret.Metallic_Roughness_Texture = Render_Resource_Base::Load_Texture(Sourec_Desc.Metallic_Roughness_URL, false);
			if (!Sourec_Desc.Normal_URL.empty())
				Ret.Normal_Texture = Render_Resource_Base::Load_Texture(Sourec_Desc.Normal_URL, false);
			if (Sourec_Desc.Occlusion_URL.empty())
				Ret.Occlusion_Texture = Render_Resource_Base::Load_Texture(Sourec_Desc.Occlusion_URL, false);
			if (Sourec_Desc.Emissive_URL.empty())
				Ret.Emissive_Texture = Render_Resource_Base::Load_Texture(Sourec_Desc.Emissive_URL, false);
		}

		return Ret;
	}

	const AxisAligned_Bounding_Box& Render_Resource_Base::Get_Bounding_Box(const path& Mesh_URL) {
		auto Iter = this->m_Bounding_Box_Cache.find(Mesh_URL);
		if (Iter != this->m_Bounding_Box_Cache.end())
			return Iter->second;

		return AxisAligned_Bounding_Box{ AxisAligned_Bounding_Box::EMPTY };
	}

	Static_Mesh_Data Render_Resource_Base::Load_Static_Mesh(const path& Mesh_URL, AxisAligned_Bounding_Box& Bounding_Box) {
		tinyobj::ObjReaderConfig Reader_Config{};
		{
			/*Reader_Config.mtl_search_path */
			Reader_Config.triangulate = true;
			Reader_Config.vertex_color = false;
		}

		tinyobj::ObjReader Reader{};
		if (false == Reader.ParseFromFile(Resource_Manager::URL_To_File_Full_Path(Mesh_URL).generic_string().c_str(), Reader_Config)) {
			System_Logger::Get_Instance().Log(System_Logger::Level::err, "Failed to load mesh: {},Error : {}", Mesh_URL.generic_string(), Reader.Error());

			throw runtime_error("Failed to load mesh");
		}

		if (false == Reader.Warning().empty())
			System_Logger::Get_Instance().Log(System_Logger::Level::warn, "Mesh loading {},Warning: {}", Mesh_URL.generic_string(), Reader.Warning());

		if (false == Reader.Error().empty())
			System_Logger::Get_Instance().Log(System_Logger::Level::err, "Mesh loading {},Error: {}", Mesh_URL.generic_string(), Reader.Warning());

		auto& Attrib{ Reader.GetAttrib() };
		auto& Shapes{ Reader.GetShapes() };

		vector<Mesh_Vertex_Data_Definition> Mesh_Vertex{};

		for (size_t Index_Shape = 0; Index_Shape < Shapes.size(); ++Index_Shape) {
			size_t Index_Offset{ 0 };

			for (size_t Index_Face = 0; Index_Face < Shapes[Index_Shape].mesh.num_face_vertices.size(); ++Index_Face) {
				size_t Face_Vertex_Count{ Shapes[Index_Shape].mesh.num_face_vertices[Index_Face] };
				if (3 != Face_Vertex_Count) {
					System_Logger::Get_Instance().Log(System_Logger::Level::err, "Mesh loading {},Error: Face vertex count is not 3", Mesh_URL.generic_string());

					continue;
				}

				bool With_Normal{ true };
				bool With_TexCoord{ true };

				Vector3 Vertex[3]{};
				Vector3 Normal[3]{};
				Vector2 TexCoord[3]{};

				for (size_t Index_Vertex = 0; Index_Vertex < Face_Vertex_Count; ++Index_Vertex) {
					tinyobj::index_t Index{ Shapes[Index_Shape].mesh.indices[Index_Offset + Index_Vertex] };
					Vertex[Index_Vertex] = Vector3{
						Attrib.vertices[3 * Index.vertex_index + 0],
						Attrib.vertices[3 * Index.vertex_index + 1],
						Attrib.vertices[3 * Index.vertex_index + 2]
					};

					//NOTE : Bounding Box
					Bounding_Box.Add_Point(Vertex[Index_Vertex]);

					if (Index.normal_index >= 0) {
						Normal[Index_Vertex] = Vector3{
							Attrib.normals[3 * Index.normal_index + 0],
							Attrib.normals[3 * Index.normal_index + 1],
							Attrib.normals[3 * Index.normal_index + 2]
						};
					}
					else
						With_Normal = false;
					if (Index.texcoord_index >= 0) {
						TexCoord[Index_Vertex] = Vector2{
							Attrib.texcoords[2 * Index.texcoord_index + 0],
							Attrib.texcoords[2 * Index.texcoord_index + 1]
						};
					}
					else
						With_TexCoord = false;
				}
				Index_Offset += Face_Vertex_Count;

				if (!With_Normal) {
					Vector3 VO{ Vertex[1] - Vertex[0] };
					Vector3 VT{ Vertex[2] - Vertex[0] };

					Normal[0] = Normal[1] = Normal[2] = VO.Cross_Product(VT).Normalize();
				}

				if (!With_TexCoord) {
					TexCoord[0] = Vector2(0.5f, 0.5f);
					TexCoord[1] = Vector2(0.5f, 0.5f);
					TexCoord[2] = Vector2(0.5f, 0.5f);
				}

				Vector3 Tangent{ 1.f,0.f,0.f };
				{
					Vector3 Degelation_1{ Vertex[1] - Vertex[0] };
					Vector3 Degelation_2{ Vertex[2] - Vertex[1] };

					Vector2 Delta_UV_1{ TexCoord[1] - TexCoord[0] };
					Vector2 Delta_UV_2{ TexCoord[2] - TexCoord[1] };

					auto Divide{ Delta_UV_1.Cross_Product(Delta_UV_2) };
					if (Divide >= 0.f && Divide < 1.e-6f)
						Divide = 1.e-6f;
					else if (Divide<0.f && Divide>-1.e-6f)
						Divide = -1.e-6f;

					float DF = 1.f / Divide;
					Tangent.Set_X((Degelation_1.Get_X() * Delta_UV_2.Get_Y() - Degelation_2.Get_X() * Delta_UV_1.Get_Y()) * DF);
					Tangent.Set_Y((Degelation_1.Get_Y() * Delta_UV_2.Get_Y() - Degelation_2.Get_Y() * Delta_UV_1.Get_Y()) * DF);
					Tangent.Set_Z((Degelation_1.Get_Z() * Delta_UV_2.Get_Y() - Degelation_2.Get_Z() * Delta_UV_1.Get_Y()) * DF);
					Tangent.To_Normalized();
				}

				for (size_t Index_Vertex = 0; Index_Vertex < Face_Vertex_Count; ++Index_Vertex) {
					Mesh_Vertex_Data_Definition Mesh_Vertex_Data{};
					{
						Mesh_Vertex_Data.X = Vertex[Index_Vertex].Get_X();
						Mesh_Vertex_Data.Y = Vertex[Index_Vertex].Get_Y();
						Mesh_Vertex_Data.Z = Vertex[Index_Vertex].Get_Z();

						Mesh_Vertex_Data.NX = Normal[Index_Vertex].Get_X();
						Mesh_Vertex_Data.NY = Normal[Index_Vertex].Get_Y();
						Mesh_Vertex_Data.NZ = Normal[Index_Vertex].Get_Z();

						Mesh_Vertex_Data.TX = Tangent.Get_X();
						Mesh_Vertex_Data.TY = Tangent.Get_Y();
						Mesh_Vertex_Data.TZ = Tangent.Get_Z();

						Mesh_Vertex_Data.U = TexCoord[Index_Vertex].Get_X();
						Mesh_Vertex_Data.V = TexCoord[Index_Vertex].Get_Y();
					}
					Mesh_Vertex.push_back(Mesh_Vertex_Data);
				}
			}
		}

		Static_Mesh_Data Mesh_Data{};
		Mesh_Data.Vertex_Buffer = std::make_shared<Buffer_Data>(Mesh_Vertex.size() * sizeof(Mesh_Vertex_Data_Definition));
		Mesh_Data.Index_Buffer = std::make_shared<Buffer_Data>(Mesh_Vertex.size() * sizeof(uint16_t));//NOTE :Index buffer size Used uint16_t

		if (Mesh_Vertex.size() >= std::numeric_limits<uint16_t>::max()) // take care of the index range, should be
			System_Logger::Get_Instance().Log(System_Logger::Level::critical, "Mesh loading {},Error: Mesh vertex count is too large", Mesh_URL.generic_string());
		// consistent with the index range used by Vulkan

		for (size_t Index = 0; Index < Mesh_Vertex.size(); ++Index) {
			static_cast<Mesh_Vertex_Data_Definition*>(Mesh_Data.Vertex_Buffer->Data)[Index] = Mesh_Vertex[Index];
			static_cast<uint16_t*>(Mesh_Data.Index_Buffer->Data)[Index] = static_cast<uint16_t>(Index);
		}

		return Mesh_Data;
	}

}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System