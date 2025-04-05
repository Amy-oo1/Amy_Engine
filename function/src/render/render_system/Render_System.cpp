#include "render/render_system/Render_System.h"

#include "meta/generated/reflection/Global_Rendering.Generated_Reflection.h"
#include "meta/generated/reflection/Camera_Controller.Generated_Reflection.h"
#include "meta/generated/reflection/Render_Obejct.Generated_Reflection.h"


#include "config/Resource_Configer.h"
#include "manage/Resource_Manager.h"
#include "components/camera/Camera_Controller.h"

#include "render/render_system/Light.h"

#include "global/Global_Rendering.h"

#include "render/rhi/vulkan/Vulkan_RHI.h"

#include "render/render_system/Render_Resource.h"
#include "render/render_pass/Particle_Pass.h"
#include "render/render_pass/Main_Camera_Pass.h"
#include "render/render_system/Render_Pipeline.h"

#include "default_editor/Editor_Axis.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System {

	using std::static_pointer_cast;

	using NameSpace_Resource::NameSpace_Global::Global_Rendering;
	using NameSpace_Resource::NameSpace_Global::Reflection_Global_Rendering_Operator;
	//using NameSpace_Resource::NameSpace_Global::Reflection_SkyBox_Irradiance_Map_Operator;
	//using NameSpace_Resource::NameSpace_Global::Reflection_SkyBox_Specular_Map_Operator;
	using NameSpace_Resource::NameSpace_Components::Reflection_Camera_Config_Operator;
	using NameSpace_Resource::NameSpace_Components::Reflection_Camera_Pose_Operator;
	using NameSpace_Resource::NameSpace_Global::Reflection_Directional_Light_Operator;

	using NameSpace_Resource::NameSpace_Config::Resource_Configer;
	using NameSpace_Resource::NameSpace_Manage::Resource_Manager;

	using NameSpace_RHI::NameSpace_Vulkan_RHI::Vulkan_RHI;
	using NameSpace_RHI::RHI_Initialization_Info;

	using NameSpace_Pass::Particle_Pass;
	using NameSpace_Pass::Main_Camera_Pass;

	using NameSpace_Editor::Editor_Translation_Axis;
	using NameSpace_Editor::Editor_Rotation_Axis;
	using NameSpace_Editor::Editor_Scale_Axis;

	Render_System::Render_System(const Render_System_Initialization_Info& Initialization_Info) :
		m_Window_System{ Initialization_Info.Window_System },
		m_RHI{ std::make_shared<Vulkan_RHI>(RHI_Initialization_Info{Initialization_Info.Window_System}) },
		m_Render_Resource{ std::make_shared<Render_Resource>() },
		m_Render_Camera{ std::make_shared<Render_Camera>() },
		m_Render_Scene{ std::make_shared<Render_Scene>() } {

		this->m_RHI->Initialize();


		auto Global_Rendering_Resource = Resource_Manager::Load<Global_Rendering>(Resource_Configer::Get_Instance().Get_Global_Render_Resource_URL());

		Level_Resource_Desc Level_Resource_Desc{};
		{
			Level_Resource_Desc.IBL_Resource_Desc.m_SkyBox_Irradiance_Map = Reflection_Global_Rendering_Operator::Get_Skybox_Irradiance_Map_Attribute(Global_Rendering_Resource);
			Level_Resource_Desc.IBL_Resource_Desc.m_SkyBox_Specular_Map = Reflection_Global_Rendering_Operator::Get_Skybox_Specular_Map_Attribute(Global_Rendering_Resource);
			Level_Resource_Desc.IBL_Resource_Desc.BRDF_Map_URL = Reflection_Global_Rendering_Operator::Get_BRDF_Map_URL_Attribute(Global_Rendering_Resource);
			Level_Resource_Desc.Color_Grading_Resource_Desc.Color_Grading_Map_URL = Reflection_Global_Rendering_Operator::Get_Color_Grading_Map_URL_Attribute(Global_Rendering_Resource);
		}
		this->m_Render_Resource->Upload_Global_Render_Resource(this->m_RHI, Level_Resource_Desc);

		//NOTE : Camera
		{
			const auto& Camera_Config = Reflection_Global_Rendering_Operator::Get_Camera_Config_Attribute(Global_Rendering_Resource);
			const auto& Pose = Reflection_Camera_Config_Operator::Get_Pose_Attribute(Camera_Config);

			const auto& Position = Reflection_Camera_Pose_Operator::Get_Position_Attribute(Pose);
			const auto& Target = Reflection_Camera_Pose_Operator::Get_Target_Attribute(Pose);
			const auto& Up = Reflection_Camera_Pose_Operator::Get_Up_Attribute(Pose);

			this->m_Render_Camera->Set_Z_Near(Reflection_Camera_Config_Operator::Get_Z_Near_Attribute(Camera_Config));
			this->m_Render_Camera->Set_Z_Far(Reflection_Camera_Config_Operator::Get_Z_Far_Attribute(Camera_Config));
			this->m_Render_Camera->Set_Aspect(Reflection_Camera_Config_Operator::Get_Aspect_Attribute(Camera_Config));

			this->m_Render_Camera->Look_At(Position, Target, Up);
		}

		//NOTE : Scence
		{
			const auto& Temp_Directional_Light = Reflection_Global_Rendering_Operator::Get_Directional_Light_Attribute(Global_Rendering_Resource);
			const auto& Direction = Reflection_Directional_Light_Operator::Get_Direction_Attribute(Temp_Directional_Light);
			const auto& Directional_Light_Color = Reflection_Directional_Light_Operator::Get_Color_Attribute(Temp_Directional_Light);

			this->m_Render_Scene->Set_Ambient_Light(Reflection_Global_Rendering_Operator::Get_Ambient_Light_Attribute(Global_Rendering_Resource));
			this->m_Render_Scene->Set_Directional_Light(Directional_Light{ Direction.Normalize() ,Directional_Light_Color });

			this->m_Render_Scene->Set_Visiable_Nodes();
		}

		//NOTE : Pipeline
		{
			Render_Pipeline_Info Pipeline_Info{};;
			{
				Pipeline_Info.RHI = this->m_RHI;
				Pipeline_Info.Resource = this->m_Render_Resource;
			}
			this->m_Render_Pipeline = std::make_shared<Render_Pipeline>(Pipeline_Info);

			Render_Passes_Info Passes_Info{};
			{
				Passes_Info.Enable_FXAA = Reflection_Global_Rendering_Operator::Get_Enable_FXAA_Attribute(Global_Rendering_Resource);
			}
			static_pointer_cast<Render_Pipeline>(this->m_Render_Pipeline)->Build_Render_Passes(Passes_Info);
		}

		//descriptor set layout in main camera pass will be used when uploading resource
		static_pointer_cast<Render_Resource>(this->m_Render_Resource)->Set_Mesh_Descriptor_Set_Layout(
			static_pointer_cast<Main_Camera_Pass>(static_pointer_cast<Render_Pipeline>(this->m_Render_Pipeline)->m_Main_Camera_Pass)->Get_Descriptor_Set_Layouts(NameSpace_Pass::_per_mesh));

		static_pointer_cast<Render_Resource>(this->m_Render_Resource)->Set_Material_Descriptor_Set_Layout(
			static_pointer_cast<Main_Camera_Pass>(static_pointer_cast<Render_Pipeline>(this->m_Render_Pipeline)->m_Main_Camera_Pass)->Get_Descriptor_Set_Layouts(NameSpace_Pass::_mesh_per_material));

	}

	void Render_System::Set_Visable_Axis(const optional<Render_Entity>& Axis) {
		this->m_Render_Scene->m_Render_Axis = Axis;

		if (Axis.has_value())
			static_pointer_cast<Render_Pipeline>(this->m_Render_Pipeline)->Set_Axis_Visable_State(true);
		else
			static_pointer_cast<Render_Pipeline>(this->m_Render_Pipeline)->Set_Axis_Visable_State(false);
	}

	shared_ptr<Render_GUID_Allocator<Game_Object_Part_ID>> Render_System::Get_Instance_ID_Allocator(void) const {
		return this->m_Render_Scene->Get_Instance_ID_Allocator();
	}

	shared_ptr<Render_GUID_Allocator<Mesh_Source_Desc>> Render_System::Get_Mesh_Resource_ID_Allocator(void) const {
		return this->m_Render_Scene->Get_Mesh_Resource_ID_Allocator();
	}

	shared_ptr<Render_GUID_Allocator<Material_Source_Desc>> Render_System::Get_Material_Resource_ID_Allocator(void) const {
		return this->m_Render_Scene->Get_Material_Resource_ID_Allocator();
	};

	shared_ptr<Render_Camera> Render_System::Get_Render_Camera(void) const {
		return this->m_Render_Camera;
	}

	shared_ptr<Render_Swap_Context> Render_System::Get_Render_Swap_Context(void) const {
		return this->m_Render_Swap_Context;
	}

	void Render_System::Set_Window_UI_System(shared_ptr<Window_UI> UI) const {
		static_pointer_cast<Render_Pipeline>(this->m_Render_Pipeline)->Set_Window_UI_System(UI);
	}

	void Render_System::Create_Axis(Render_Entity* Translation_Axis, Render_Entity* Rotation_Axis, Render_Entity* Scale_Axis) {
		this->m_Render_Resource->Upload_Game_Object_Render_Resource(
			this->m_RHI,
			*Translation_Axis,
			static_cast<Editor_Translation_Axis*>(Translation_Axis)->Mesh_Data
		);
		this->m_Render_Resource->Upload_Game_Object_Render_Resource(
			this->m_RHI,
			*Rotation_Axis,
			static_cast<Editor_Rotation_Axis*>(Rotation_Axis)->Mesh_Data
		);
		this->m_Render_Resource->Upload_Game_Object_Render_Resource(
			this->m_RHI,
			*Scale_Axis,
			static_cast<Editor_Scale_Axis*>(Scale_Axis)->Mesh_Data
		);
	}

	void Render_System::Swap_Logic_Render_Data(void) {
		this->m_Render_Swap_Context->Swap_Logic_Render_Data();
	}

	void Render_System::Proccess_Swap_Data(void) {
		auto& Swap_Data{ this->m_Render_Swap_Context->Get_SwapData(Render_Swap_Context::SWAPDATA_TYPE::SWAPDATA_TYPE_RENDER) };

		if (Swap_Data.Level_Resource_Desc.has_value()) {
			this->m_Render_Resource->Upload_Global_Render_Resource(this->m_RHI, Swap_Data.Level_Resource_Desc.value());
			this->m_Render_Swap_Context->Reset_Level_Resource_SwapData();
		}

		if (Swap_Data.GO_Resource_Desc.has_value()) {
			const auto& Object_Desc{ Swap_Data.GO_Resource_Desc->Get_Next_Process_Object() };

			while (!Swap_Data.GO_Resource_Desc->Is_Empty()) {

				for (size_t Part_Index = 0; Part_Index < Object_Desc.Get_Part_Descs().size(); ++Part_Index) {
					const auto& Part_Desc{ Object_Desc.Get_Part_Descs()[Part_Index] };
					Game_Object_Part_ID Part_ID{ Object_Desc.Get_ID(), static_cast<uint32_t>(Part_Index) };

					Render_Entity Entity{};

					//NOTE : Instance
					bool Is_Entity_In_Scene{ false };
					if (this->m_Render_Scene->Get_Instance_ID_Allocator()->Has_Element(Part_ID))
						Is_Entity_In_Scene = true;

					Entity.Instance_ID = this->m_Render_Scene->Get_Instance_ID_Allocator()->Allocate_GUID(Part_ID);
					Entity.Model_Matrix = Reflection_Game_Object_Transform_Desc_Operator::Get_Transform_Attribute(Reflection_Game_Object_Part_Desc_Operator::Get_Transform_Desc_Attribute(Part_Desc));

					//NOTYE: Add
					this->m_Render_Scene->Add_Entity(Entity.Instance_ID, Object_Desc.Get_ID());

					//NOTE : Mesh Data
					Render_Mesh_Data Mesh_data{};
					bool Is_Mesh_Loaded{ false };
					{
						const auto& Mesh_URL{ Reflection_Game_Object_Mesh_Desc_Operator::Get_Mesh_URL_Attribute(Reflection_Game_Object_Part_Desc_Operator::Get_Mesh_Desc_Attribute(Part_Desc)) };
						if (!(Is_Mesh_Loaded = this->m_Render_Scene->Get_Mesh_Resource_ID_Allocator()->Has_Element(Mesh_Source_Desc{ Mesh_URL })))
							Mesh_data = this->m_Render_Resource->Load_Mesh(Mesh_URL, Entity.Bounding_Box);
						else
							Entity.Bounding_Box = this->m_Render_Resource->Get_Bounding_Box(Mesh_URL);

						Entity.Mesh_Resource_ID = this->m_Render_Scene->Get_Mesh_Resource_ID_Allocator()->Allocate_GUID(Mesh_Source_Desc{ Mesh_URL });

						const auto& Skeleton_Animation_Result{ Reflection_Game_Object_Part_Desc_Operator::Get_Skeleton_Animation_Result_Attribute(Part_Desc) };
						Entity.Enable_Vertex_Blending = Reflection_Skeleton_Animation_Result_Operator::Get_Transforms_CPPVector_Size(Skeleton_Animation_Result) > 1;
						Entity.Joint_Matrices.reserve(Reflection_Skeleton_Animation_Result_Operator::Get_Transforms_CPPVector_Size(Skeleton_Animation_Result));
						for (const auto& Transform : Reflection_Skeleton_Animation_Result_Operator::Get_Transforms_Attribute(Skeleton_Animation_Result))
							Entity.Joint_Matrices.push_back(Reflection_Skeleton_Animation_Result_Transform_Operator::Get_Matrix_Attribute(Transform));
					}

					Render_Material_Data Material_data{};
					bool Is_Material_Loaded{ false };
					// NOTE : Material Data
					{
						const auto& Material_Desc = Reflection_Game_Object_Part_Desc_Operator::Get_Material_Desc_Attribute(Part_Desc);

						Material_Source_Desc Sourec_Desc{};
						if (Reflection_Game_Object_Material_Desc_Operator::Get_Is_With_Texture_Attribute(Material_Desc)) {
							Sourec_Desc.Base_Color_URL = Reflection_Game_Object_Material_Desc_Operator::Get_Base_Color_URL_Attribute(Material_Desc);
							Sourec_Desc.Metallic_Roughness_URL = Reflection_Game_Object_Material_Desc_Operator::Get_Metallic_Roughness_URL_Attribute(Material_Desc);
							Sourec_Desc.Normal_URL = Reflection_Game_Object_Material_Desc_Operator::Get_Normal_URL_Attribute(Material_Desc);
							Sourec_Desc.Occlusion_URL = Reflection_Game_Object_Material_Desc_Operator::Get_Occlusion_URL_Attribute(Material_Desc);
							Sourec_Desc.Emissive_URL = Reflection_Game_Object_Material_Desc_Operator::Get_Emissive_URL_Attribute(Material_Desc);
						}
						else {
							Sourec_Desc.Base_Color_URL = Resource_Configer::Get_Instance().Get_Default_Base_Color_Image_URL();
							Sourec_Desc.Metallic_Roughness_URL = Resource_Configer::Get_Instance().Get_Default_Metallic_Roughness_Image_URL();
							Sourec_Desc.Normal_URL = Resource_Configer::Get_Instance().Get_Default_Normal_Image_URL();
							Sourec_Desc.Occlusion_URL = Resource_Configer::Get_Instance().Get_Default_Occlusion_Image_URL();
							Sourec_Desc.Emissive_URL = Resource_Configer::Get_Instance().Get_Default_Emissive_Image_URL();
						}

						if (!(Is_Material_Loaded = this->m_Render_Scene->Get_Material_Resource_ID_Allocator()->Has_Element(Sourec_Desc)))
							Material_data = Render_Resource_Base::Load_Material(Sourec_Desc);
						Entity.Material_Resource_ID = this->m_Render_Scene->Get_Material_Resource_ID_Allocator()->Allocate_GUID(Sourec_Desc);
					}


					if (!Is_Mesh_Loaded)
						this->m_Render_Resource->Upload_Game_Object_Render_Resource(this->m_RHI, Entity, Mesh_data);
					if (!Is_Material_Loaded)
						this->m_Render_Resource->Upload_Game_Object_Render_Resource(this->m_RHI, Entity, Material_data);

					if (!Is_Entity_In_Scene)
						this->m_Render_Scene->m_Render_Entities.emplace_back(Entity);
					else {
						for (auto& Loaded_Entity : this->m_Render_Scene->m_Render_Entities)
							if (Loaded_Entity.Instance_ID == Entity.Instance_ID) {
								Loaded_Entity = Entity;

								break;
							}
					}
				}

				Swap_Data.GO_Resource_Desc->Pop();
			}

			this->m_Render_Swap_Context->Reset_Game_Object_Resource_SwapData();
		}

		if (Swap_Data.GO_Resource_To_Delete.has_value()) {
			while (!Swap_Data.GO_Resource_To_Delete->Is_Empty()) {
				this->m_Render_Scene->Delete_Entity(Swap_Data.GO_Resource_To_Delete->Get_Next_Process_Object().Get_ID());
				Swap_Data.GO_Resource_To_Delete->Pop();
			}

			this->m_Render_Swap_Context->Reset_Game_Object_Resource_To_Delete_SwapData();
		}

		if (Swap_Data.Camera_SwapData.has_value()) {
			if (Swap_Data.Camera_SwapData->FOV_X.has_value())
				this->m_Render_Camera->Set_FOV_X(Swap_Data.Camera_SwapData->FOV_X.value());

			if (Swap_Data.Camera_SwapData->Camera_Type.has_value())
				this->m_Render_Camera->Set_Current_Camera_Type(Swap_Data.Camera_SwapData->Camera_Type.value());

			if (Swap_Data.Camera_SwapData->View_Matrix.has_value())
				this->m_Render_Camera->Set_Main_View_Matrix(Swap_Data.Camera_SwapData->View_Matrix.value());

			this->m_Render_Swap_Context->Reset_Camera_SwapData();
		}

		if (Swap_Data.m_Particle_Submit_Request.has_value()) {
			auto Ref_Particle_Pass{ static_pointer_cast<Particle_Pass>(static_pointer_cast<Render_Pipeline>(this->m_Render_Pipeline)->m_Particle_Pass) };

			uint32_t Emitter_Count{ Swap_Data.m_Particle_Submit_Request->Get_Emitter_Count() };
			Ref_Particle_Pass->Set_Emitter_Count(Emitter_Count);

			for (uint32_t Index = 0; Index < Emitter_Count; ++Index) {
				const auto& Emitter_Desc{ Swap_Data.m_Particle_Submit_Request->Get_Emitter_Desc(Index) };
				Ref_Particle_Pass->Create_Emitter(Index, Emitter_Desc);
			}
			//TODO :
			/*ef_Particle_Pass->Ini*/

			this->m_Render_Swap_Context->Reset_Particle_Submit_Request_SwapData();
		}

		if (Swap_Data.m_Emitter_Tick_Request.has_value()) {
			//TODO:

			this->m_Render_Swap_Context->Reset_Emitter_Tick_Request_SwapData();
		}

		if (Swap_Data.m_Emitter_Transform_Request.has_value()) {
			//TODO : 

			this->m_Render_Swap_Context->Reset_Emitter_Transform_Request_SwapData();
		}
	}

	void Render_System::Tick(float Delta_Time) {
		this->Proccess_Swap_Data();

		this->m_RHI->Prepare_Context();

		this->m_Render_Resource->Updata_Per_Frame_Buffer(this->m_Render_Scene, this->m_Render_Camera);

		this->m_Render_Scene->Updata_Visiable_Objects(static_pointer_cast<Render_Resource>(this->m_Render_Resource), this->m_Render_Camera);

	}



}// namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System