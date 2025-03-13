#pragma once

#include<optional>
#include<memory>
#include<utility>

#include "file/File_System.h"

#include "manage/Resource_Manager.h"

#include "components/skeleton/Skeleton_Data.h"
#include "components/skeleton/Skeleton_Node.h"
#include "components/skeleton/Skeleton_Mask.h"
#include "components/animation/Animation_Clip.h"

namespace NameSpace_Function::NameSpace_Animation {

	using std::shared_ptr;

	using NameSpace_Platform::NameSpace_File::path;

	using NameSpace_Core::NameSpace_Logger::System_Logger;

	using NameSpace_Resource::NameSpace_Manage::Resource_Manager;
	using NameSpace_Resource::NameSpace_Components::Skeleton_Data;
	using NameSpace_Resource::NameSpace_Components::Skeleton_Node_Map;
	using NameSpace_Resource::NameSpace_Components::Bone_Blend_Mask;
	using NameSpace_Resource::NameSpace_Components::Animation_Clip;

	class [[nodiscard]] Animation_Loader final {
	private:
		Animation_Loader(void) = delete;

		Animation_Loader(const Animation_Loader&) = delete;
		Animation_Loader(Animation_Loader&&) = delete;

		Animation_Loader& operator=(const Animation_Loader&) = delete;
		Animation_Loader& operator=(Animation_Loader&&) = delete;

		Animation_Loader(Resource_Manager& Ref_Resource_Manager);

	public:
		~Animation_Loader(void) = default;

	public:
		shared_ptr<Skeleton_Data> Load_Skeleton_Data(const path& Skeleton_Data_URL);
		shared_ptr<Skeleton_Node_Map> Load_Skeleton_Node_Map(const path& _Skeleton_Node_Map_URL);
		shared_ptr<Bone_Blend_Mask> Load_Bone_Blend_Mask(const path& Bone_Blend_Mask_URL);
		shared_ptr<Animation_Clip> Load_Animation_Clip(const path& Animation_Clip_URL);

	public:
		static Animation_Loader& Get_Instance(Resource_Manager& Ref_Resource_Manager);

	private:
		template<typename Resource_Type>
		shared_ptr<Resource_Type> Load_Resource(const path& Resource_URL) {
			std::optional<Resource_Type> Resource{ m_Ref_Resource_Manager.Load<Resource_Type>(Resource_URL) };

			if (!Resource.has_value()) {
				//TODO : Logg Repeat
				System_Logger::Get_Instance().Log(System_Logger::Level::err, "Failure Load File :{} ", Resource_URL.string());
				return nullptr;
			}

			return std::make_shared<Resource_Type>(std::move(Resource.value()));
		}

	private:
		Resource_Manager& m_Ref_Resource_Manager;

	};

}// namespace NameSpace_Function::NameSpace_Animation