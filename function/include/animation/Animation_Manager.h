#pragma once

#include<tuple>
#include<string>
#include<iterator>
#include<unordered_map>
#include<functional>
#include <memory>

#include "file/File_System.h"

#include "logger/System_Logger.h"

#include "components/skeleton/Skeleton_Data.h"
#include "components/skeleton/Skeleton_Node.h"
#include "components/skeleton/Skeleton_Mask.h"
#include "components/animation/Animation_Clip.h"
#include "components/animation/Blend_State.h"

#include "animation/Bone.h"
#include "animation/Skeleton.h"
#include "animation/Animation_Loader.h"

namespace NameSpace_Function::NameSpace_Animation {

	using std::tuple;
	using std::string;
	using std::unordered_map;
	using std::function;
	using std::shared_ptr;

	using NameSpace_Platform::NameSpace_File::path;

	using NameSpace_Core::NameSpace_Logger::System_Logger;

	using NameSpace_Resource::NameSpace_Components::Skeleton_Data;
	using NameSpace_Resource::NameSpace_Components::Skeleton_Node_Map;
	using NameSpace_Resource::NameSpace_Components::Bone_Blend_Mask;
	using NameSpace_Resource::NameSpace_Components::Bone_Blend_Weight;
	using NameSpace_Resource::NameSpace_Components::Animation_Clip;
	using NameSpace_Resource::NameSpace_Components::BlendState_With_Clip_Data;
	using NameSpace_Resource::NameSpace_Components::Blend_State;

	class  Animation_Manager final {
	private:
		Animation_Manager(const Animation_Manager&) = delete;
		Animation_Manager(Animation_Manager&&) = delete;

		Animation_Manager& operator=(const Animation_Manager&) = delete;
		Animation_Manager& operator=(Animation_Manager&&) = delete;

		Animation_Manager(void) = default;

	public:
		~Animation_Manager(void) = default;

	public:
		shared_ptr<Skeleton_Data> TryLoad_Skeleton_Data(const path& Skeleton_Data_URL);
		shared_ptr<Skeleton_Node_Map> TryLoad_Skeleton_Node_Map(const path& Skeleton_Node_Map_RUL);
		shared_ptr<Bone_Blend_Mask> TryLoad_Bone_Blend_Mask(const path& Bone_Blend_Mask_URL);
		shared_ptr<Animation_Clip> TryLoad_Animation_Clip(const path& Animation_Clip_URL);

		[[nodiscard]] shared_ptr<BlendState_With_Clip_Data> Get_Blend_State_And_Clip_Data(const shared_ptr<Blend_State>& Blend);

	private:
		template<typename Resource_Type>
		[[nodiscard]] std::shared_ptr<Resource_Type> TryLoad_Resource(const path& Resource_URL, unordered_map<path, shared_ptr<Resource_Type>>& Cache, function<shared_ptr<Resource_Type>(const path&)> Load_Function) {
			const auto  It = Cache.find(Resource_URL);
			if (Cache.end() != It)
				return It->second;

			shared_ptr<Resource_Type> Resource{ Load_Function(Resource_URL) };
			if (nullptr == Resource) {
				System_Logger::Get_Instance().Log(System_Logger::Level::err, "Failure Load File :{} ", Resource_URL.generic_string());
				return nullptr;
			}

			return Cache[Resource_URL] = Resource;
		}

		const vector<float> Calculate_Bone_Weights(const vector<shared_ptr<Bone_Blend_Mask>>& Bone_Blend_Mask_List, const vector<float>& Clip_Weights)const;

		const vector<shared_ptr<Bone_Blend_Weight>> Normalize_Weights_For_Bone(const vector<shared_ptr<Bone_Blend_Mask>>& Bone_Blend_Mask_List, const vector<float>& Bone_Weights, const vector<float>& Sum_Weights)const;

		//TODO : Erase
		//void Resource_Dependencies(const shared_ptr<Blend_State>& Blend);

		//TODO : Erase
		//const tuple<vector<shared_ptr<Animation_Clip>>, vector<shared_ptr<Skeleton_Node_Map>>> Populate_Blend_Data(void)const;

	public:
		[[nodiscard]] static Animation_Manager& Get_Instance(void);

	private:

		unordered_map<path, shared_ptr<Skeleton_Data>> m_Skeleton_Data_Cache{};
		unordered_map<path, shared_ptr<Skeleton_Node_Map>> m_Skeleton_Node_Map_Cache{};
		unordered_map<path, shared_ptr<Bone_Blend_Mask>> m_Bone_Blend_Mask_Cache{};
		unordered_map<path, shared_ptr<Animation_Clip>> m_Animation_Clip_Cache{};

	};

}// namespace NameSpace_Function::NameSpace_Animation