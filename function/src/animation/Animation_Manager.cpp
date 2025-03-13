#include "animation/Animation_Manager.h"

#include<algorithm>

#include "math/Utilities.h"

#include "meta/generated/reflection/Skeleton_Data.Generated_Reflection.h"
#include "meta/generated/reflection/Blend_State.Generated_Reflection.h"
#include "meta/generated/reflection/Skeleton_Mask.Generated_Reflection.h"

namespace NameSpace_Function::NameSpace_Animation {

	using NameSpace_Core::NameSpace_Math::NameSpace_Utilities::Abs;

	using NameSpace_Resource::NameSpace_Components::Bone_Blend_Weight;

	using NameSpace_Resource::NameSpace_Components::Reflection_Skeleton_Data_Operator;
	using NameSpace_Resource::NameSpace_Components::Reflection_BlendState_With_Clip_Data_Operator;
	using NameSpace_Resource::NameSpace_Components::Reflection_Bone_Blend_Weight_Operator;
	using NameSpace_Resource::NameSpace_Components::Reflection_Bone_Blend_Mask_Operator;
	using NameSpace_Resource::NameSpace_Components::Reflection_Blend_State_Operator;


	Animation_Manager::Animation_Manager(Animation_Loader& Ref_Animation_Loader)
		:m_Ref_Animation_Loader{ Ref_Animation_Loader } {
	}

	shared_ptr<Skeleton_Data> Animation_Manager::TryLoad_Skeleton_Data(const path& Skeleton_Data_URL) {
		return this->TryLoad_Resource<Skeleton_Data>(
			Skeleton_Data_URL,
			this->m_Skeleton_Data_Cache,
			[this](const path& URL) {return this->m_Ref_Animation_Loader.Load_Skeleton_Data(URL); }
		);
	}

	shared_ptr<Skeleton_Node_Map> Animation_Manager::TryLoad_Skeleton_Node_Map(const path& Skeleton_Node_Map_RUL) {
		return this->TryLoad_Resource<Skeleton_Node_Map>(
			Skeleton_Node_Map_RUL,
			this->m_Skeleton_Node_Map_Cache,
			[this](const path& URL) {return this->m_Ref_Animation_Loader.Load_Skeleton_Node_Map(URL); }
		);
	}

	shared_ptr<Bone_Blend_Mask> Animation_Manager::TryLoad_Bone_Blend_Mask(const path& Bone_Blend_Mask_URL) {
		return this->TryLoad_Resource<Bone_Blend_Mask>(
			Bone_Blend_Mask_URL,
			this->m_Bone_Blend_Mask_Cache,
			[this](const path& URL) {return this->m_Ref_Animation_Loader.Load_Bone_Blend_Mask(URL); }
		);
	}

	shared_ptr<Animation_Clip> Animation_Manager::TryLoad_Animation_Clip(const path& Animation_Clip_URL) {
		return this->TryLoad_Resource<Animation_Clip>(
			Animation_Clip_URL,
			this->m_Animation_Clip_Cache,
			[this](const path& URL) {return this->m_Ref_Animation_Loader.Load_Animation_Clip(URL); }
		);
	}

	shared_ptr<BlendState_With_Clip_Data> Animation_Manager::Get_Blend_State_And_Clip_Data(const shared_ptr<Blend_State>& Blend) {
		shared_ptr<BlendState_With_Clip_Data> Res{ std::make_shared<BlendState_With_Clip_Data>() };

		for (const auto& Skeleton_Node_Map_URL : Reflection_Blend_State_Operator::Get_Blend_Skeleton_Node_Map_URL_Attribute(Blend))
			Reflection_BlendState_With_Clip_Data_Operator::Push_Back_Blend_Skeleton_CPPVector(
				Res,
				this->TryLoad_Skeleton_Node_Map(Skeleton_Node_Map_URL)
			);

		for (const auto& Animation_Clip_URL : Reflection_Blend_State_Operator::Get_Blend_Clip_URL_Attribute(Blend))
			Reflection_BlendState_With_Clip_Data_Operator::Push_Back_Blend_Clip_CPPVector(
				Res,
				this->TryLoad_Animation_Clip(Animation_Clip_URL)
			);

		Reflection_BlendState_With_Clip_Data_Operator::Set_Field_Blend_ratio_Attribute(Res, Reflection_Blend_State_Operator::Get_Blend_Ratio_Attribute(Blend));

		vector<shared_ptr<Bone_Blend_Mask>> Bone_Blend_Mask_List{};
		Bone_Blend_Mask_List.reserve(this->m_Bone_Blend_Mask_Cache.size());
		for (const auto& Bone_Blend_Mask_URL : Reflection_Blend_State_Operator::Get_Blend_Mask_URL_Attribute(Blend)) {
			auto Mask = this->TryLoad_Bone_Blend_Mask(Bone_Blend_Mask_URL);

			this->TryLoad_Skeleton_Data(Reflection_Bone_Blend_Mask_Operator::Get_Skeleton_Data_URL_Attribute(Mask));
			Bone_Blend_Mask_List.emplace_back(Mask);
		}

		const vector<float> Sum_Weights{ this->Calculate_Bone_Weights(Bone_Blend_Mask_List,Reflection_Blend_State_Operator::Get_Blend_Weights_Attribute(Blend)) };

		Reflection_BlendState_With_Clip_Data_Operator::Set_Field_Blend_Weights_Attribute(
			Res,
			this->Normalize_Weights_For_Bone(Bone_Blend_Mask_List, Reflection_Blend_State_Operator::Get_Blend_Weights_Attribute(Blend), Sum_Weights)
		);

		return Res;
	}

	const vector<float> Animation_Manager::Calculate_Bone_Weights(const vector<shared_ptr<Bone_Blend_Mask>>& Bone_Blend_Mask_List, const vector<float>& Clip_Weights) const {
		size_t Clip_Size{ Clip_Weights.size() };
		size_t Bones_Size{ Bone_Blend_Mask_List.size() };

		vector<float> Bone_Weight_List{};
		Bone_Weight_List.reserve(Bones_Size);

		for (size_t Index_Bone = 0; Index_Bone < Bones_Size; ++Index_Bone) {
			float Sum_Weight{ 0.f };

			for (size_t Index_Clip = 0; Index_Clip < Clip_Size; ++Index_Clip)
				if (Reflection_Bone_Blend_Mask_Operator::Get_Enabled_CPPVector_Element(Bone_Blend_Mask_List[Index_Clip], Index_Bone))
					Sum_Weight += Clip_Weights[Index_Clip];

			if (Abs(Sum_Weight) < 0.0001f) {
				System_Logger::Get_Instance().Log(System_Logger::Level::err, "Sum_Weight is Zero");
				continue;
			}

			Bone_Weight_List.emplace_back(Sum_Weight);
		}
		return Bone_Weight_List;
	}

	const vector<shared_ptr<Bone_Blend_Weight>> Animation_Manager::Normalize_Weights_For_Bone(const vector<shared_ptr<Bone_Blend_Mask>>& Bone_Blend_Mask_List, const vector<float>& Bone_Weight_List, const vector<float>& Sum_Weights) const {
		size_t Clip_Size{ Bone_Blend_Mask_List.size() };
		size_t Bones_Size{ Bone_Weight_List.size() };

		vector<shared_ptr<Bone_Blend_Weight>> Temp_Bone_Weight_List{};
		Temp_Bone_Weight_List.reserve(Clip_Size);

		for (size_t Index_Clip = 0; Index_Clip < Clip_Size; ++Index_Clip) {
			Temp_Bone_Weight_List.emplace_back(std::make_shared<Bone_Blend_Weight>());

			for (size_t Index_Bone = 0; Index_Bone < Bones_Size; ++Index_Bone)
				Reflection_Bone_Blend_Weight_Operator::Push_Back_Blend_Weights_CPPVector(Temp_Bone_Weight_List[Index_Clip], 0.f);
		}

		for (size_t Index_Bone = 0; Index_Bone < Bones_Size; ++Index_Bone) {
			for (size_t Index_Clip = 0; Index_Clip < Clip_Size; ++Index_Clip)
				if (Reflection_Bone_Blend_Mask_Operator::Get_Enabled_CPPVector_Element(Bone_Blend_Mask_List[Index_Clip], Index_Bone))
					Reflection_Bone_Blend_Weight_Operator::Set_Blend_Weights_CPPVector_Element(
						Temp_Bone_Weight_List[Index_Clip],
						Index_Bone,
						Bone_Weight_List[Index_Bone] / Sum_Weights[Index_Bone]
					);
		}

		return Temp_Bone_Weight_List;
	}


	/*void Animation_Manager::Resource_Dependencies(const shared_ptr<Blend_State>& Blend) {
		auto Load_Resource_Func = [this](const vector<path>& URLs, auto  Loader) {
			std::for_each(URLs.cbegin(), URLs.cend(), [&](const auto& URL) {(this->*Loader)(URL); });
			};

		Load_Resource_Func(Reflection_Blend_State_Operator::Get_Blend_Skeleton_Node_Map_URL_Attribute(Blend), &Animation_Manager::TryLoad_Skeleton_Node_Map);
		Load_Resource_Func(Reflection_Blend_State_Operator::Get_Blend_Clip_URL_Attribute(Blend), &Animation_Manager::TryLoad_Animation_Clip);
		Load_Resource_Func(Reflection_Blend_State_Operator::Get_Blend_Mask_URL_Attribute(Blend), &Animation_Manager::TryLoad_Bone_Blend_Mask);

		for (const auto& [URl, Mask] : this->m_Bone_Blend_Mask_Cache)
			this->TryLoad_Skeleton_Data(Reflection_Bone_Blend_Mask_Operator::Get_Skeleton_Data_URL_Attribute(Mask));

	}

	const tuple<vector<shared_ptr<Animation_Clip>>, vector<shared_ptr<Skeleton_Node_Map>>> Animation_Manager::Populate_Blend_Data(void) const {
		vector <shared_ptr<Animation_Clip>> Temp_Clips{};
		vector<shared_ptr<Skeleton_Node_Map>> Temp_Skeleton_Node_Maps{};

		Temp_Clips.reserve(this->m_Animation_Clip_Cache.size());
		Temp_Skeleton_Node_Maps.reserve(this->m_Animation_Clip_Cache.size());

		for (const auto& [URL, Temp_Clip] : this->m_Animation_Clip_Cache)
			Temp_Clips.push_back(Temp_Clip);

		for (const auto& [URL, Temp_Skeleton_Node_Map] : this->m_Skeleton_Node_Map_Cache)
			Temp_Skeleton_Node_Maps.push_back(Temp_Skeleton_Node_Map);

		return{ Temp_Clips, Temp_Skeleton_Node_Maps };
	}*/

	Animation_Manager& Animation_Manager::Get_Instance(Animation_Loader& Ref_Animation_Loader) {
		static Animation_Manager Instance{ Ref_Animation_Loader };

		return Instance;
	}

}// namespace NameSpace_Function::NameSpace_Animation