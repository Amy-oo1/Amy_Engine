#include "default_editor/Editor_UI.h"

#include<cmath>
#include<algorithm>

#include "logger/System_Logger.h"

#include "math/Utilities.h"

#include "transform/Affine_Transform.h"

#include "config/Resource_Configer.h"
#include "manage/Resource_Manager.h"

#include "render/render_system/Render_Resource_Base.h"

#include "default_editor/Editor_Global_Context.h"

namespace NameSpace_Editor {

	using NameSpace_Core::NameSpace_Logger::System_Logger;
	using NameSpace_Core::NameSpace_Transform::Affine_Transform;

	using NameSpace_Resource::NameSpace_Config::Resource_Configer;
	using NameSpace_Resource::NameSpace_Manage::Resource_Manager;

	using NameSpace_Function::NameSpace_Render::NameSpace_Render_System::Render_Resource_Base;

	Editor_UI::Editor_UI(void)
		:Window_UI{} {
		this->m_editor_ui_creator["TreeNodePush"] = [this](const string& name, void* value_ptr) -> void {
			static ImGuiTableFlags flags = ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings;

			bool                   node_state = false;
			++this->g_node_depth;

			if (0 < this->g_node_depth) {
				if (this->g_editor_node_state_array[static_cast<size_t>(this->g_node_depth - 1)].second)
					node_state = ImGui::TreeNodeEx(name.c_str(), ImGuiTreeNodeFlags_SpanFullWidth);
				else
					this->g_editor_node_state_array.emplace_back(name.c_str(), node_state);
				return;
			}
			else
				node_state = ImGui::TreeNodeEx(name.c_str(), ImGuiTreeNodeFlags_SpanFullWidth);

			this->g_editor_node_state_array.emplace_back(name.c_str(), node_state);
			};
		this->m_editor_ui_creator["TreeNodePop"] = [this](const string& name, void* value_ptr) -> void {
			if (this->g_editor_node_state_array[this->g_node_depth].second)
				ImGui::TreePop();
			this->g_editor_node_state_array.pop_back();
			--this->g_node_depth;
			};
		this->m_editor_ui_creator["Transform"] = [this](const string& name, void* value_ptr) -> void {
			if (this->g_editor_node_state_array[this->g_node_depth].second) {
				//TODO :
			}
			};
		this->m_editor_ui_creator["bool"] = [this](const string& name, void* value_ptr)  -> void {
			if (-1 == this->g_node_depth) {
				string label{ "##" + name };
				ImGui::Text("%s", name.c_str());
				ImGui::SameLine();
				ImGui::Checkbox(label.c_str(), static_cast<bool*>(value_ptr));
			}
			else if (this->g_editor_node_state_array[this->g_node_depth].second) {
				string full_label{ "##" + Get_Leaf_UI_Node_Parent_Label() + name };
				ImGui::Text("%s", name.c_str());
				ImGui::Checkbox(full_label.c_str(), static_cast<bool*>(value_ptr));
			}
			};
		this->m_editor_ui_creator["int"] = [this](const string& name, void* value_ptr) -> void {
			if (-1 == this->g_node_depth) {
				string label{ "##" + name };
				ImGui::Text("%s", name.c_str());
				ImGui::SameLine();
				ImGui::InputInt(label.c_str(), static_cast<int*>(value_ptr));
			}
			else if (this->g_editor_node_state_array[this->g_node_depth].second) {
				string full_label{ "##" + Get_Leaf_UI_Node_Parent_Label() + name };
				ImGui::Text("%s", (name + ":").c_str());
				ImGui::InputInt(full_label.c_str(), static_cast<int*>(value_ptr));
			}
			};
		this->m_editor_ui_creator["float"] = [this](const string& name, void* value_ptr) -> void {
			if (-1 == this->g_node_depth) {
				string label{ "##" + name };
				ImGui::Text("%s", name.c_str());
				ImGui::SameLine();
				ImGui::InputFloat(label.c_str(), static_cast<float*>(value_ptr));
			}
			else if (this->g_editor_node_state_array[this->g_node_depth].second) {
				string full_label{ "##" + Get_Leaf_UI_Node_Parent_Label() + name };
				ImGui::Text("%s", (name + ":").c_str());
				ImGui::InputFloat(full_label.c_str(), static_cast<float*>(value_ptr));
			}
			};
		this->m_editor_ui_creator["Vector3"] = [this](const string& name, void* value_ptr) -> void {
			Vector3* vec_ptr = static_cast<Vector3*>(value_ptr);
			float val[3] = { vec_ptr->Get_X(), vec_ptr->Get_Y(), vec_ptr->Get_Z() };

			if (-1 == this->g_node_depth) {
				string label{ "##" + name };
				ImGui::Text("%s", name.c_str());
				ImGui::SameLine();
				ImGui::DragFloat3(label.c_str(), val);
			}
			else if (this->g_editor_node_state_array[this->g_node_depth].second) {
				string full_label{ "##" + Get_Leaf_UI_Node_Parent_Label() + name };
				ImGui::Text("%s", (name + ":").c_str());
				ImGui::DragFloat3(full_label.c_str(), val);
			}

			*vec_ptr = Vector3(val[0], val[1], val[2]);
			};
		this->m_editor_ui_creator["Quaternion"] = [this](const string& name, void* value_ptr) -> void {
			Quaternion* qua_ptr = static_cast<Quaternion*>(value_ptr);
			float  val[4] = {
				(*qua_ptr)[Quaternion::Index::s],
				(*qua_ptr)[Quaternion::Index::i],
				(*qua_ptr)[Quaternion::Index::j],
				(*qua_ptr)[Quaternion::Index::k],
			};

			if (-1 == this->g_node_depth) {
				string label{ "##" + name };
				ImGui::Text("%s", name.c_str());
				ImGui::SameLine();
				ImGui::DragFloat4(label.c_str(), val);
			}
			else if (this->g_editor_node_state_array[this->g_node_depth].second) {
				string full_label{ "##" + Get_Leaf_UI_Node_Parent_Label() + name };
				ImGui::Text("%s", (name + ":").c_str());
				ImGui::DragFloat4(full_label.c_str(), val);
			}

			*qua_ptr = Quaternion(val[0], val[1], val[2], val[3]);
			};
		this->m_editor_ui_creator["String"] = [this](const string& name, void* value_ptr) -> void {
			if (-1 == this->g_node_depth) {
				string label{ "##" + name };
				ImGui::Text("%s", name.c_str());
				ImGui::SameLine();
				ImGui::Text("%s", (*static_cast<string*>(value_ptr)).c_str());
			}
			else if (this->g_editor_node_state_array[this->g_node_depth].second) {
				string full_label{ "##" + Get_Leaf_UI_Node_Parent_Label() + name };
				ImGui::Text("%s", (name + ":").c_str());
				ImGui::SameLine();
				ImGui::Text("%s", static_cast<string*>(value_ptr)->c_str());
			}
			};

		this->Initialize_UI_Style();
	}

	const string Editor_UI::Get_Leaf_UI_Node_Parent_Label(void) {
		std::string Parent_Label{};
		for (const auto& [Name, _] : this->m_editor_ui_creator)
			Parent_Label += Name + "::";

		return Parent_Label;
	}

	//	void Editor_UI::showEditorUI()
	//	{
	//		showEditorMenu(&m_editor_menu_window_open);
	//		showEditorWorldObjectsWindow(&m_asset_window_open);
	//		showEditorGameWindow(&m_game_engine_window_open);
	//		showEditorFileContentWindow(&m_file_content_window_open);
	//		showEditorDetailWindow(&m_detail_window_open);
	//	}
	//
	//	void Editor_UI::showEditorMenu(bool* p_open)
	//	{
	//		ImGuiDockNodeFlags dock_flags = ImGuiDockNodeFlags_DockSpace;
	//		ImGuiWindowFlags   window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar |
	//			ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
	//			ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground |
	//			ImGuiConfigFlags_NoMouseCursorChange | ImGuiWindowFlags_NoBringToFrontOnFocus;
	//
	//		const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
	//		ImGui::SetNextWindowPos(main_viewport->WorkPos, ImGuiCond_Always);
	//		std::array<int, 2> window_size = g_editor_global_context.m_window_system->getWindowSize();
	//		ImGui::SetNextWindowSize(ImVec2((float)window_size[0], (float)window_size[1]), ImGuiCond_Always);
	//
	//		ImGui::SetNextWindowViewport(main_viewport->ID);
	//
	//		ImGui::Begin("Editor menu", p_open, window_flags);
	//
	//		ImGuiID main_docking_id = ImGui::GetID("Main Docking");
	//		if (ImGui::DockBuilderGetNode(main_docking_id) == nullptr)
	//		{
	//			ImGui::DockBuilderRemoveNode(main_docking_id);
	//
	//			ImGui::DockBuilderAddNode(main_docking_id, dock_flags);
	//			ImGui::DockBuilderSetNodePos(main_docking_id,
	//				ImVec2(main_viewport->WorkPos.x, main_viewport->WorkPos.y + 18.0f));
	//			ImGui::DockBuilderSetNodeSize(main_docking_id,
	//				ImVec2((float)window_size[0], (float)window_size[1] - 18.0f));
	//
	//			ImGuiID center = main_docking_id;
	//			ImGuiID left;
	//			ImGuiID right = ImGui::DockBuilderSplitNode(center, ImGuiDir_Right, 0.25f, nullptr, &left);
	//
	//			ImGuiID left_other;
	//			ImGuiID left_file_content = ImGui::DockBuilderSplitNode(left, ImGuiDir_Down, 0.30f, nullptr, &left_other);
	//
	//			ImGuiID left_game_engine;
	//			ImGuiID left_asset =
	//				ImGui::DockBuilderSplitNode(left_other, ImGuiDir_Left, 0.30f, nullptr, &left_game_engine);
	//
	//			ImGui::DockBuilderDockWindow("World Objects", left_asset);
	//			ImGui::DockBuilderDockWindow("Components Details", right);
	//			ImGui::DockBuilderDockWindow("File Content", left_file_content);
	//			ImGui::DockBuilderDockWindow("Game Engine", left_game_engine);
	//
	//			ImGui::DockBuilderFinish(main_docking_id);
	//		}
	//
	//		ImGui::DockSpace(main_docking_id);
	//
	//		if (ImGui::BeginMenuBar())
	//		{
	//			if (ImGui::BeginMenu("Menu"))
	//			{
	//				if (ImGui::MenuItem("Reload Current Level"))
	//				{
	//					g_runtime_global_context.m_world_manager->reloadCurrentLevel();
	//					g_runtime_global_context.m_render_system->clearForLevelReloading();
	//					g_editor_global_context.m_scene_manager->onGObjectSelected(k_invalid_gobject_id);
	//				}
	//				if (ImGui::MenuItem("Save Current Level"))
	//				{
	//					g_runtime_global_context.m_world_manager->saveCurrentLevel();
	//				}
	//				if (ImGui::BeginMenu("Debug"))
	//				{
	//					if (ImGui::BeginMenu("Animation"))
	//					{
	//						if (ImGui::MenuItem(g_runtime_global_context.m_render_debug_config->animation.show_skeleton ? "off skeleton" : "show skeleton"))
	//						{
	//							g_runtime_global_context.m_render_debug_config->animation.show_skeleton = !g_runtime_global_context.m_render_debug_config->animation.show_skeleton;
	//						}
	//						if (ImGui::MenuItem(g_runtime_global_context.m_render_debug_config->animation.show_bone_name ? "off bone name" : "show bone name"))
	//						{
	//							g_runtime_global_context.m_render_debug_config->animation.show_bone_name = !g_runtime_global_context.m_render_debug_config->animation.show_bone_name;
	//						}
	//						ImGui::EndMenu();
	//					}
	//					if (ImGui::BeginMenu("Camera"))
	//					{
	//						if (ImGui::MenuItem(g_runtime_global_context.m_render_debug_config->camera.show_runtime_info ? "off runtime info" : "show runtime info"))
	//						{
	//							g_runtime_global_context.m_render_debug_config->camera.show_runtime_info = !g_runtime_global_context.m_render_debug_config->camera.show_runtime_info;
	//						}
	//						ImGui::EndMenu();
	//					}
	//					if (ImGui::BeginMenu("Game Object"))
	//					{
	//						if (ImGui::MenuItem(g_runtime_global_context.m_render_debug_config->gameObject.show_bounding_box ? "off bounding box" : "show bounding box"))
	//						{
	//							g_runtime_global_context.m_render_debug_config->gameObject.show_bounding_box = !g_runtime_global_context.m_render_debug_config->gameObject.show_bounding_box;
	//						}
	//						ImGui::EndMenu();
	//					}
	//					ImGui::EndMenu();
	//				}
	//				if (ImGui::MenuItem("Exit"))
	//				{
	//					g_editor_global_context.m_engine_runtime->shutdownEngine();
	//					exit(0);
	//				}
	//				ImGui::EndMenu();
	//			}
	//			if (ImGui::BeginMenu("Window"))
	//			{
	//				ImGui::MenuItem("World Objects", nullptr, &m_asset_window_open);
	//				ImGui::MenuItem("Game", nullptr, &m_game_engine_window_open);
	//				ImGui::MenuItem("File Content", nullptr, &m_file_content_window_open);
	//				ImGui::MenuItem("Detail", nullptr, &m_detail_window_open);
	//				ImGui::EndMenu();
	//			}
	//			ImGui::EndMenuBar();
	//		}
	//
	//		ImGui::End();
	//	}
	//
	//	void Editor_UI::showEditorWorldObjectsWindow(bool* p_open)
	//	{
	//		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
	//
	//		const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
	//
	//		if (!*p_open)
	//			return;
	//
	//		if (!ImGui::Begin("World Objects", p_open, window_flags))
	//		{
	//			ImGui::End();
	//			return;
	//		}
	//
	//		std::shared_ptr<Level> current_active_level =
	//			g_runtime_global_context.m_world_manager->getCurrentActiveLevel().lock();
	//		if (current_active_level == nullptr)
	//			return;
	//
	//		const LevelObjectsMap& all_gobjects = current_active_level->getAllGObjects();
	//		for (auto& id_object_pair : all_gobjects)
	//		{
	//			const GObjectID          object_id = id_object_pair.first;
	//			std::shared_ptr<GObject> object = id_object_pair.second;
	//			const std::string        name = object->getName();
	//			if (name.size() > 0)
	//			{
	//				if (ImGui::Selectable(name.c_str(),
	//					g_editor_global_context.m_scene_manager->getSelectedObjectID() == object_id))
	//				{
	//					if (g_editor_global_context.m_scene_manager->getSelectedObjectID() != object_id)
	//					{
	//						g_editor_global_context.m_scene_manager->onGObjectSelected(object_id);
	//					}
	//					else
	//					{
	//						g_editor_global_context.m_scene_manager->onGObjectSelected(k_invalid_gobject_id);
	//					}
	//					break;
	//				}
	//			}
	//		}
	//		ImGui::End();
	//	}
	//
	//	void Editor_UI::createClassUI(Reflection::ReflectionInstance& instance)
	//	{
	//		Reflection::ReflectionInstance* reflection_instance;
	//		int count = instance.m_meta.getBaseClassReflectionInstanceList(reflection_instance, instance.m_instance);
	//		for (int index = 0; index < count; index++)
	//		{
	//			createClassUI(reflection_instance[index]);
	//		}
	//		createLeafNodeUI(instance);
	//
	//		if (count > 0)
	//			delete[] reflection_instance;
	//	}
	//
	//	void Editor_UI::createLeafNodeUI(Reflection::ReflectionInstance& instance)
	//	{
	//		Reflection::FieldAccessor* fields;
	//		int                        fields_count = instance.m_meta.getFieldsList(fields);
	//
	//		for (size_t index = 0; index < fields_count; index++)
	//		{
	//			auto field = fields[index];
	//			if (field.isArrayType())
	//			{
	//				Reflection::ArrayAccessor array_accessor;
	//				if (Reflection::TypeMeta::newArrayAccessorFromName(field.getFieldTypeName(), array_accessor))
	//				{
	//					void* field_instance = field.get(instance.m_instance);
	//					int   array_count = array_accessor.getSize(field_instance);
	//					m_editor_ui_creator["TreeNodePush"](
	//						std::string(field.getFieldName()) + "[" + std::to_string(array_count) + "]", nullptr);
	//					auto item_type_meta_item =
	//						Reflection::TypeMeta::newMetaFromName(array_accessor.getElementTypeName());
	//					auto item_ui_creator_iterator = m_editor_ui_creator.find(item_type_meta_item.getTypeName());
	//					for (int index = 0; index < array_count; index++)
	//					{
	//						if (item_ui_creator_iterator == m_editor_ui_creator.end())
	//						{
	//							m_editor_ui_creator["TreeNodePush"]("[" + std::to_string(index) + "]", nullptr);
	//							auto object_instance = Reflection::ReflectionInstance(
	//								Piccolo::Reflection::TypeMeta::newMetaFromName(item_type_meta_item.getTypeName().c_str()),
	//								array_accessor.get(index, field_instance));
	//							createClassUI(object_instance);
	//							m_editor_ui_creator["TreeNodePop"]("[" + std::to_string(index) + "]", nullptr);
	//						}
	//						else
	//						{
	//							if (item_ui_creator_iterator == m_editor_ui_creator.end())
	//							{
	//								continue;
	//							}
	//							m_editor_ui_creator[item_type_meta_item.getTypeName()](
	//								"[" + std::to_string(index) + "]", array_accessor.get(index, field_instance));
	//						}
	//					}
	//					m_editor_ui_creator["TreeNodePop"](field.getFieldName(), nullptr);
	//				}
	//			}
	//			auto ui_creator_iterator = m_editor_ui_creator.find(field.getFieldTypeName());
	//			if (ui_creator_iterator == m_editor_ui_creator.end())
	//			{
	//				Reflection::TypeMeta field_meta =
	//					Reflection::TypeMeta::newMetaFromName(field.getFieldTypeName());
	//				if (field.getTypeMeta(field_meta))
	//				{
	//					auto child_instance =
	//						Reflection::ReflectionInstance(field_meta, field.get(instance.m_instance));
	//					m_editor_ui_creator["TreeNodePush"](field_meta.getTypeName(), nullptr);
	//					createClassUI(child_instance);
	//					m_editor_ui_creator["TreeNodePop"](field_meta.getTypeName(), nullptr);
	//				}
	//				else
	//				{
	//					if (ui_creator_iterator == m_editor_ui_creator.end())
	//					{
	//						continue;
	//					}
	//					m_editor_ui_creator[field.getFieldTypeName()](field.getFieldName(),
	//						field.get(instance.m_instance));
	//				}
	//			}
	//			else
	//			{
	//				m_editor_ui_creator[field.getFieldTypeName()](field.getFieldName(),
	//					field.get(instance.m_instance));
	//			}
	//		}
	//		delete[] fields;
	//	}
	//
	//	void Editor_UI::showEditorDetailWindow(bool* p_open)
	//	{
	//		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
	//
	//		const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
	//
	//		if (!*p_open)
	//			return;
	//
	//		if (!ImGui::Begin("Components Details", p_open, window_flags))
	//		{
	//			ImGui::End();
	//			return;
	//		}
	//
	//		std::shared_ptr<GObject> selected_object = g_editor_global_context.m_scene_manager->getSelectedGObject().lock();
	//		if (selected_object == nullptr)
	//		{
	//			ImGui::End();
	//			return;
	//		}
	//
	//		const std::string& name = selected_object->getName();
	//		static char        cname[128];
	//		memset(cname, 0, 128);
	//		memcpy(cname, name.c_str(), name.size());
	//
	//		ImGui::Text("Name");
	//		ImGui::SameLine();
	//		ImGui::InputText("##Name", cname, IM_ARRAYSIZE(cname), ImGuiInputTextFlags_ReadOnly);
	//
	//		static ImGuiTableFlags flags = ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings;
	//		auto&& selected_object_components = selected_object->getComponents();
	//		for (auto component_ptr : selected_object_components)
	//		{
	//			m_editor_ui_creator["TreeNodePush"](("<" + component_ptr.getTypeName() + ">").c_str(), nullptr);
	//			auto object_instance = Reflection::ReflectionInstance(
	//				Piccolo::Reflection::TypeMeta::newMetaFromName(component_ptr.getTypeName().c_str()),
	//				component_ptr.operator->());
	//			createClassUI(object_instance);
	//			m_editor_ui_creator["TreeNodePop"](("<" + component_ptr.getTypeName() + ">").c_str(), nullptr);
	//		}
	//		ImGui::End();
	//	}
	//
	//	void Editor_UI::showEditorFileContentWindow(bool* p_open)
	//	{
	//		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
	//
	//		const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
	//
	//		if (!*p_open)
	//			return;
	//
	//		if (!ImGui::Begin("File Content", p_open, window_flags))
	//		{
	//			ImGui::End();
	//			return;
	//		}
	//
	//		static ImGuiTableFlags flags = ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersOuterH |
	//			ImGuiTableFlags_Resizable | ImGuiTableFlags_RowBg |
	//			ImGuiTableFlags_NoBordersInBody;
	//
	//		if (ImGui::BeginTable("File Content", 2, flags))
	//		{
	//			ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_NoHide);
	//			ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_WidthFixed);
	//			ImGui::TableHeadersRow();
	//
	//			auto current_time = std::chrono::steady_clock::now();
	//			if (current_time - m_last_file_tree_update > std::chrono::seconds(1))
	//			{
	//				m_editor_file_service.buildEngineFileTree();
	//				m_last_file_tree_update = current_time;
	//			}
	//			m_last_file_tree_update = current_time;
	//
	//			EditorFileNode* editor_root_node = m_editor_file_service.getEditorRootNode();
	//			buildEditorFileAssetsUITree(editor_root_node);
	//			ImGui::EndTable();
	//		}
	//
	//		// file image list
	//
	//		ImGui::End();
	//	}
	//
	//	void Editor_UI::showEditorGameWindow(bool* p_open)
	//	{
	//		ImGuiIO& io = ImGui::GetIO();
	//		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_MenuBar;
	//
	//		const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
	//
	//		if (!*p_open)
	//			return;
	//
	//		if (!ImGui::Begin("Game Engine", p_open, window_flags))
	//		{
	//			ImGui::End();
	//			return;
	//		}
	//
	//		static bool trans_button_ckecked = false;
	//		static bool rotate_button_ckecked = false;
	//		static bool scale_button_ckecked = false;
	//
	//		switch (g_editor_global_context.m_scene_manager->getEditorAxisMode())
	//		{
	//		case EditorAxisMode::TranslateMode:
	//			trans_button_ckecked = true;
	//			rotate_button_ckecked = false;
	//			scale_button_ckecked = false;
	//			break;
	//		case EditorAxisMode::RotateMode:
	//			trans_button_ckecked = false;
	//			rotate_button_ckecked = true;
	//			scale_button_ckecked = false;
	//			break;
	//		case EditorAxisMode::ScaleMode:
	//			trans_button_ckecked = false;
	//			rotate_button_ckecked = false;
	//			scale_button_ckecked = true;
	//			break;
	//		default:
	//			break;
	//		}
	//
	//		if (ImGui::BeginMenuBar())
	//		{
	//			ImGui::Indent(10.f);
	//			drawAxisToggleButton("Trans", trans_button_ckecked, (int)EditorAxisMode::TranslateMode);
	//			ImGui::Unindent();
	//
	//			ImGui::SameLine();
	//
	//			drawAxisToggleButton("Rotate", rotate_button_ckecked, (int)EditorAxisMode::RotateMode);
	//
	//			ImGui::SameLine();
	//
	//			drawAxisToggleButton("Scale", scale_button_ckecked, (int)EditorAxisMode::ScaleMode);
	//
	//			ImGui::SameLine();
	//
	//			float indent_val = 0.0f;
	//
	//#if defined(__GNUC__) && defined(__MACH__)
	//			float indent_scale = 1.0f;
	//#else // Not tested on Linux
	//			float x_scale, y_scale;
	//			glfwGetWindowContentScale(g_editor_global_context.m_window_system->getWindow(), &x_scale, &y_scale);
	//			float indent_scale = fmaxf(1.0f, fmaxf(x_scale, y_scale));
	//#endif
	//			indent_val = g_editor_global_context.m_input_manager->getEngineWindowSize().x - 100.0f * indent_scale;
	//
	//			ImGui::Indent(indent_val);
	//			if (g_is_editor_mode)
	//			{
	//				ImGui::PushID("Editor Mode");
	//				if (ImGui::Button("Editor Mode"))
	//				{
	//					g_is_editor_mode = false;
	//					g_editor_global_context.m_scene_manager->drawSelectedEntityAxis();
	//					g_editor_global_context.m_input_manager->resetEditorCommand();
	//					g_editor_global_context.m_window_system->setFocusMode(true);
	//				}
	//				ImGui::PopID();
	//			}
	//			else
	//			{
	//				if (ImGui::Button("Game Mode"))
	//				{
	//					g_is_editor_mode = true;
	//					g_editor_global_context.m_scene_manager->drawSelectedEntityAxis();
	//					g_runtime_global_context.m_input_system->resetGameCommand();
	//					g_editor_global_context.m_render_system->getRenderCamera()->setMainViewMatrix(
	//						g_editor_global_context.m_scene_manager->getEditorCamera()->getViewMatrix());
	//				}
	//			}
	//
	//			ImGui::Unindent();
	//			ImGui::EndMenuBar();
	//		}
	//
	//		if (!g_is_editor_mode)
	//		{
	//			ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Press Left Alt key to display the mouse cursor!");
	//		}
	//		else
	//		{
	//			ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f),
	//				"Current editor camera move speed: [%f]",
	//				g_editor_global_context.m_input_manager->getCameraSpeed());
	//		}
	//
	//		// GetWindowPos() ----->  X--------------------------------------------O
	//		//                        |                                            |
	//		//                        |                                            |
	//		// menu_bar_rect.Min -->  X--------------------------------------------O
	//		//                        |    It is the menu bar window.              |
	//		//                        |                                            |
	//		//                        O--------------------------------------------X  <-- menu_bar_rect.Max
	//		//                        |                                            |
	//		//                        |     It is the render target window.        |
	//		//                        |                                            |
	//		//                        O--------------------------------------------O
	//
	//		Vector2 render_target_window_pos = { 0.0f, 0.0f };
	//		Vector2 render_target_window_size = { 0.0f, 0.0f };
	//
	//		auto menu_bar_rect = ImGui::GetCurrentWindow()->MenuBarRect();
	//
	//		render_target_window_pos.x = ImGui::GetWindowPos().x;
	//		render_target_window_pos.y = menu_bar_rect.Max.y;
	//		render_target_window_size.x = ImGui::GetWindowSize().x;
	//		render_target_window_size.y = (ImGui::GetWindowSize().y + ImGui::GetWindowPos().y) - menu_bar_rect.Max.y; // coord of right bottom point of full window minus coord of right bottom point of menu bar window.
	//
	//		// if (new_window_pos != m_engine_window_pos || new_window_size != m_engine_window_size)
	//		{
	//#if defined(__MACH__)
	//			// The dpi_scale is not reactive to DPI changes or monitor switching, it might be a bug from ImGui.
	//			// Return value from ImGui::GetMainViewport()->DpiScal is always the same as first frame.
	//			// glfwGetMonitorContentScale and glfwSetWindowContentScaleCallback are more adaptive.
	//			float dpi_scale = main_viewport->DpiScale;
	//			g_runtime_global_context.m_render_system->updateEngineContentViewport(render_target_window_pos.x * dpi_scale,
	//				render_target_window_pos.y * dpi_scale,
	//				render_target_window_size.x * dpi_scale,
	//				render_target_window_size.y * dpi_scale);
	//#else
	//			g_runtime_global_context.m_render_system->updateEngineContentViewport(
	//				render_target_window_pos.x, render_target_window_pos.y, render_target_window_size.x, render_target_window_size.y);
	//#endif
	//			g_editor_global_context.m_input_manager->setEngineWindowPos(render_target_window_pos);
	//			g_editor_global_context.m_input_manager->setEngineWindowSize(render_target_window_size);
	//		}
	//
	//		ImGui::End();
	//	}
	//
	//	void Editor_UI::drawAxisToggleButton(const char* string_id, bool check_state, int axis_mode)
	//	{
	//		if (check_state)
	//		{
	//			ImGui::PushID(string_id);
	//			ImVec4 check_button_color = ImVec4(93.0f / 255.0f, 10.0f / 255.0f, 66.0f / 255.0f, 1.00f);
	//			ImGui::PushStyleColor(ImGuiCol_Button,
	//				ImVec4(check_button_color.x, check_button_color.y, check_button_color.z, 0.40f));
	//			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, check_button_color);
	//			ImGui::PushStyleColor(ImGuiCol_ButtonActive, check_button_color);
	//			ImGui::Button(string_id);
	//			ImGui::PopStyleColor(3);
	//			ImGui::PopID();
	//		}
	//		else
	//		{
	//			if (ImGui::Button(string_id))
	//			{
	//				check_state = true;
	//				g_editor_global_context.m_scene_manager->setEditorAxisMode((EditorAxisMode)axis_mode);
	//				g_editor_global_context.m_scene_manager->drawSelectedEntityAxis();
	//			}
	//		}
	//	}
	//
	//	void Editor_UI::buildEditorFileAssetsUITree(EditorFileNode* node)
	//	{
	//		ImGui::TableNextRow();
	//		ImGui::TableNextColumn();
	//		const bool is_folder = (node->m_child_nodes.size() > 0);
	//		if (is_folder)
	//		{
	//			bool open = ImGui::TreeNodeEx(node->m_file_name.c_str(), ImGuiTreeNodeFlags_SpanFullWidth);
	//			ImGui::TableNextColumn();
	//			ImGui::SetNextItemWidth(100.0f);
	//			ImGui::TextUnformatted(node->m_file_type.c_str());
	//			if (open)
	//			{
	//				for (int child_n = 0; child_n < node->m_child_nodes.size(); child_n++)
	//					buildEditorFileAssetsUITree(node->m_child_nodes[child_n].get());
	//				ImGui::TreePop();
	//			}
	//		}
	//		else
	//		{
	//			ImGui::TreeNodeEx(node->m_file_name.c_str(),
	//				ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen |
	//				ImGuiTreeNodeFlags_SpanFullWidth);
	//			if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
	//			{
	//				onFileContentItemClicked(node);
	//			}
	//			ImGui::TableNextColumn();
	//			ImGui::SetNextItemWidth(100.0f);
	//			ImGui::TextUnformatted(node->m_file_type.c_str());
	//		}
	//	}
	//
	//	void Editor_UI::onFileContentItemClicked(EditorFileNode* node)
	//	{
	//		if (node->m_file_type != "object")
	//			return;
	//
	//		std::shared_ptr<Level> level = g_runtime_global_context.m_world_manager->getCurrentActiveLevel().lock();
	//		if (level == nullptr)
	//			return;
	//
	//		const unsigned int new_object_index = ++m_new_object_index_map[node->m_file_name];
	//
	//		ObjectInstanceRes new_object_instance_res;
	//		new_object_instance_res.m_name =
	//			"New_" + Path::getFilePureName(node->m_file_name) + "_" + std::to_string(new_object_index);
	//		new_object_instance_res.m_definition =
	//			g_runtime_global_context.m_asset_manager->getFullPath(node->m_file_path).generic_string();
	//
	//		size_t new_gobject_id = level->createObject(new_object_instance_res);
	//		if (new_gobject_id != k_invalid_gobject_id)
	//		{
	//			g_editor_global_context.m_scene_manager->onGObjectSelected(new_gobject_id);
	//		}
	//	}


	void Editor_UI::Initialize_UI_Style(void) {
		//NOTE : Ref In ImGui GitHub https:// github.com/ocornut/imgui/issues/6342

		float x_scale{}, y_scale{};
		glfwGetWindowContentScale(Editor_Global_Context::Get_Instance().m_Window_System->Get_Window(), &x_scale, &y_scale);
		float content_scale{ std::max({1.0f, x_scale, y_scale}) };

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigWindowsMoveFromTitleBarOnly = true;
		io.Fonts->AddFontFromFileTTF(
			Resource_Manager::URL_To_File_Full_Path(Resource_Configer::Get_Instance().Get_Editor_Font_URL()).generic_string().c_str(),
			content_scale * 16,
			nullptr,
			nullptr
		);
		io.Fonts->Build();

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsLight();

		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowPadding = ImVec2(1.0, 0);
		style.FramePadding = ImVec2(14.0, 2.0f);
		style.ChildBorderSize = 0.0f;
		style.FrameRounding = 5.0f;
		style.FrameBorderSize = 1.5f;

		// set imgui color style
		Editor_UI::Set_UI_Color_Style();

		// setup window icon
		auto Big_Icon{ Render_Resource_Base::Load_Texture_HDR(Resource_Configer::Get_Instance().Get_Engine_Big_Icon_URL()) };
		auto Small_Icon{ Render_Resource_Base::Load_Texture_HDR(Resource_Configer::Get_Instance().Get_Engine_Small_Icon_URL()) };

		GLFWimage Window_Icons[2]{};
		{
			Window_Icons[0].width = Big_Icon->Width;
			Window_Icons[0].height = Big_Icon->Height;
			Window_Icons[0].pixels = static_cast<unsigned char*>(Big_Icon->Pixels.get());

			Window_Icons[1].width = Small_Icon->Width;
			Window_Icons[1].height = Small_Icon->Height;
			Window_Icons[1].pixels = static_cast<unsigned char*>(Small_Icon->Pixels.get());
		}
		glfwSetWindowIcon(Editor_Global_Context::Get_Instance().m_Window_System->Get_Window(), 2, Window_Icons);
	};

	// load font for imgui

	void Editor_UI::Set_UI_Color_Style() {
		ImGuiStyle* Style = &ImGui::GetStyle();
		ImVec4* Color = Style->Colors;

		Color[ImGuiCol_Text] = ImVec4(0.4745f, 0.4745f, 0.4745f, 1.00f);
		Color[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		Color[ImGuiCol_WindowBg] = ImVec4(0.0078f, 0.0078f, 0.0078f, 1.00f);
		Color[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		Color[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
		Color[ImGuiCol_Border] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		Color[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		Color[ImGuiCol_FrameBg] = ImVec4(0.047f, 0.047f, 0.047f, 0.5411f);
		Color[ImGuiCol_FrameBgHovered] = ImVec4(0.196f, 0.196f, 0.196f, 0.40f);
		Color[ImGuiCol_FrameBgActive] = ImVec4(0.294f, 0.294f, 0.294f, 0.67f);
		Color[ImGuiCol_TitleBg] = ImVec4(0.0039f, 0.0039f, 0.0039f, 1.00f);
		Color[ImGuiCol_TitleBgActive] = ImVec4(0.0039f, 0.0039f, 0.0039f, 1.00f);
		Color[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.50f);
		Color[ImGuiCol_MenuBarBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
		Color[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
		Color[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
		Color[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
		Color[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
		Color[ImGuiCol_CheckMark] = ImVec4(93.0f / 255.0f, 10.0f / 255.0f, 66.0f / 255.0f, 1.00f);
		Color[ImGuiCol_SliderGrab] = Color[ImGuiCol_CheckMark];
		Color[ImGuiCol_SliderGrabActive] = ImVec4(0.3647f, 0.0392f, 0.2588f, 0.50f);
		Color[ImGuiCol_Button] = ImVec4(0.0117f, 0.0117f, 0.0117f, 1.00f);
		Color[ImGuiCol_ButtonHovered] = ImVec4(0.0235f, 0.0235f, 0.0235f, 1.00f);
		Color[ImGuiCol_ButtonActive] = ImVec4(0.0353f, 0.0196f, 0.0235f, 1.00f);
		Color[ImGuiCol_Header] = ImVec4(0.1137f, 0.0235f, 0.0745f, 0.588f);
		Color[ImGuiCol_HeaderHovered] = ImVec4(5.0f / 255.0f, 5.0f / 255.0f, 5.0f / 255.0f, 1.00f);
		Color[ImGuiCol_HeaderActive] = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
		Color[ImGuiCol_Separator] = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);
		Color[ImGuiCol_SeparatorHovered] = ImVec4(45.0f / 255.0f, 7.0f / 255.0f, 26.0f / 255.0f, 1.00f);
		Color[ImGuiCol_SeparatorActive] = ImVec4(45.0f / 255.0f, 7.0f / 255.0f, 26.0f / 255.0f, 1.00f);
		Color[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.20f);
		Color[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
		Color[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
		Color[ImGuiCol_Tab] = ImVec4(6.0f / 255.0f, 6.0f / 255.0f, 8.0f / 255.0f, 1.00f);
		Color[ImGuiCol_TabHovered] = ImVec4(45.0f / 255.0f, 7.0f / 255.0f, 26.0f / 255.0f, 150.0f / 255.0f);
		Color[ImGuiCol_TabActive] = ImVec4(47.0f / 255.0f, 6.0f / 255.0f, 29.0f / 255.0f, 1.0f);
		Color[ImGuiCol_TabUnfocused] = ImVec4(45.0f / 255.0f, 7.0f / 255.0f, 26.0f / 255.0f, 25.0f / 255.0f);
		Color[ImGuiCol_TabUnfocusedActive] = ImVec4(6.0f / 255.0f, 6.0f / 255.0f, 8.0f / 255.0f, 200.0f / 255.0f);
		Color[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		Color[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		Color[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		Color[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		Color[ImGuiCol_TableHeaderBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
		Color[ImGuiCol_TableBorderStrong] = ImVec4(2.0f / 255.0f, 2.0f / 255.0f, 2.0f / 255.0f, 1.0f);
		Color[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
		Color[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		Color[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
		Color[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
		Color[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
		Color[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		Color[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		Color[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
		Color[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
	}

	//void Editor_UI::preRender() { showEditorUI(); }

	/*void DrawVecControl(const std::string& label, const Quaternion& values, float resetValue, float columnWidth)
	{
		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text("%s", label.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(4, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

		float  lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		if (ImGui::Button("X", buttonSize))
			values.x = resetValue;
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.45f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.55f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.45f, 0.2f, 1.0f });
		if (ImGui::Button("Y", buttonSize))
			values.y = resetValue;
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		if (ImGui::Button("Z", buttonSize))
			values.z = resetValue;
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.5f, 0.25f, 0.5f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.6f, 0.35f, 0.6f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.5f, 0.25f, 0.5f, 1.0f });
		if (ImGui::Button("W", buttonSize))
			values.w = resetValue;
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##W", &values.w, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();

		ImGui::Columns(1);
		ImGui::PopID();
	}*/


}// namespace NameSpace_Editor