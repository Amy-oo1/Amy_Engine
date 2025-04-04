#pragma once

#include<cstdint>
#include<vector>
#include<unordered_map>
#include<functional>
#include<memory>
#include<chrono>
#include<utility>

#include "imgui.h"
#include "imgui_internal.h"

#include "file/File_System.h"

#include "math//Degree.h"
#include "math/Radian.h"
#include "math/Vector2.h"
#include "math/Vector3.h"
#include "math/Quaternion.h"

#include "frame/object/GObject.h"

#include "render/window/Window_UI.h"
#include "render/render_system/Render_Data_Struct.h"
#include "render/render_system/Render_Entity.h"

#include "default_editor/Editor_Axis.h"

namespace NameSpace_Editor {

	using std::pair;
	using std::string;
	using std::vector;
	using std::unordered_map;
	using std::function;
	using std::shared_ptr;
	using std::chrono::high_resolution_clock;

	using  NameSpace_Platform::NameSpace_File::path;

	using NameSpace_Core::NameSpace_Math::Degree;
	using NameSpace_Core::NameSpace_Math::Radian;

	using NameSpace_Core::NameSpace_Math::Vector2;
	using NameSpace_Core::NameSpace_Math::Vector3;
	using NameSpace_Core::NameSpace_Math::Quaternion;

	using NameSpace_Function::NameSpace_Render::NameSpace_Window::Window_UI;


	class Editor_UI final :public Window_UI, public std::enable_shared_from_this<Editor_UI> {

	private:
		/*void        onFileContentItemClicked(EditorFileNode* node);
		void        buildEditorFileAssetsUITree(EditorFileNode* node);
		void        drawAxisToggleButton(const char* string_id, bool check_state, int axis_mode);
		void        createClassUI(Reflection::ReflectionInstance& instance);
		void        createLeafNodeUI(Reflection::ReflectionInstance& instance);
		std::string getLeafUINodeParentLabel();*/

		void showEditorUI();
		void showEditorMenu(bool* p_open);
		void showEditorWorldObjectsWindow(bool* p_open);
		void showEditorFileContentWindow(bool* p_open);
		void showEditorGameWindow(bool* p_open);
		void showEditorDetailWindow(bool* p_open);

		static void Set_UI_Color_Style();

	public:
		void Initialize_UI_Style(void);

	private:
		std::unordered_map<std::string, unsigned int>                            m_new_object_index_map;
		std::chrono::time_point<std::chrono::steady_clock>                       m_last_file_tree_update;



	private:
		Editor_UI(const Editor_UI&) = delete;
		Editor_UI(Editor_UI&&) = delete;

		Editor_UI& operator=(const Editor_UI&) = delete;
		Editor_UI& operator=(Editor_UI&&) = delete;
	public:
		Editor_UI(void);

		~Editor_UI(void) = default;

	public:

		vector<pair<string, bool>>g_editor_node_state_array{};
		int32_t g_node_depth = -1;


		unordered_map<string, function<void(string, void*)>> m_editor_ui_creator{};


	private:
		const string Get_Leaf_UI_Node_Parent_Label(void);


	private:
		bool m_Editor_Menu_Window_Open = true;
		bool m_Resource_Window_Open = true;
		bool m_Game_Engine_Window_Open = true;
		bool m_File_Content_Window_Open = true;
		bool m_Detail_Window_Open = true;
		bool m_Scene_Lights_Window_open = true;
		bool m_Scene_Lights_Data_Window_Open = true;
	};

}// namespace NameSpace_Editor