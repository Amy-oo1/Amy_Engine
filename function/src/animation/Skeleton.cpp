#include "animation/Skeleton.h"

#include<limits>

#include "logger/System_Logger.h"

#include "math/Vector3.h"
#include "math/Utilities.h"

#include "transform/Orthogonal_Transform.h"
#include "transform/Affine_Transform.h"

#include "meta/generated/reflection/Skeleton_Node.Generated_Reflection.h"
#include "meta/generated/reflection/Skeleton_Data.Generated_Reflection.h"
#include "meta/generated/reflection/Animation_Clip.Generated_Reflection.h"
#include "meta/generated/reflection/Blend_State.Generated_Reflection.h"

#include "animation/Utilities.h"

namespace NameSpace_Function::NameSpace_Animation {

	using NameSpace_Core::NameSpace_Logger::System_Logger;

	using NameSpace_Core::NameSpace_Math::Vector3;
	using NameSpace_Core::NameSpace_Math::Quaternion;
	using namespace NameSpace_Core::NameSpace_Math::NameSpace_Utilities;
	using NameSpace_Core::NameSpace_Transform::Affine_Transform;

	using NameSpace_Resource::NameSpace_Components::Reflection_Bone_Raw_Operator;
	using NameSpace_Resource::NameSpace_Components::Reflection_Skeleton_Node_Map_Operator;
	using NameSpace_Resource::NameSpace_Components::Reflection_Animation_Channel_Operator;
	using NameSpace_Resource::NameSpace_Components::Reflection_Animation_Clip_Operator;
	using NameSpace_Resource::NameSpace_Components::Reflection_BlendState_With_Clip_Data_Operator;
	using NameSpace_Resource::NameSpace_Components::Reflection_Skeleton_Data_Operator;


	Skeleton::Skeleton(shared_ptr<Skeleton_Data> Skeleton_Data)
		:m_Skeleton_Data{ Skeleton_Data } {

		if (!Reflection_Skeleton_Data_Operator::Get_Is_Flat_Attribute(this->m_Skeleton_Data) ||
			!Reflection_Skeleton_Data_Operator::Get_In_Topological_Order_Attribute(this->m_Skeleton_Data))
			System_Logger::Get_Instance().Log(System_Logger::Level::err, "Skeleton is not in topological order");

		this->m_Bones.reserve(Reflection_Skeleton_Data_Operator::Get_Bones_CPPVector_Size(Skeleton_Data));
		for (const auto& Temp_Bone_Raw : Reflection_Skeleton_Data_Operator::Get_Bones_Attribute(Skeleton_Data)) {

			auto paretn_Bone = NameSpace_Utilities::Find_Bone(
				this->m_Bones,
				Reflection_Bone_Raw_Operator::Get_Parent_Index_Attribute(Temp_Bone_Raw),
				Reflection_Skeleton_Data_Operator::Get_Is_Flat_Attribute(Skeleton_Data)
			);

			this->m_Bones.push_back(std::make_shared<Bone>(Temp_Bone_Raw, paretn_Bone));
		}
	}

	void Skeleton::Apply_Animation(const shared_ptr<BlendState_With_Clip_Data>& Blend_State_Clip_Data) {
		if (this->m_Bones.empty())
			System_Logger::Get_Instance().Log(System_Logger::Level::err, "Bones Is Empty");

		this->ReSet_Init_Skeleton();

		for (const auto& [Clip, Phase, Steleton_Noe] : this->Extract_Clip_Data(Blend_State_Clip_Data)) {
			const auto [Low_Frame, Height_Fram, Lerp] = this->Calculate_Frame_Data(Clip, Phase);
			this->Apply_Clip_To_Skeleton(Clip, Steleton_Noe, Low_Frame, Height_Fram, Lerp);
		}

		for (auto& Bone : this->m_Bones)
			Bone->UpData_Derived_Transform();
	}

	void Skeleton::ReSet_Init_Skeleton(void) {
		for (auto& Temp_Bone : this->m_Bones)
			Temp_Bone->Reset_To_Binding_Pose();
	}

	const vector<tuple<shared_ptr<Animation_Clip>, float, shared_ptr<Skeleton_Node_Map>>> Skeleton::Extract_Clip_Data(const shared_ptr<BlendState_With_Clip_Data>& Temp_BlendState_With_Clip_Data) const {
		vector<tuple<shared_ptr<Animation_Clip>, float, shared_ptr<Skeleton_Node_Map>>> Res{};
		//NOTE : Just One Clip
		static const size_t Clip_Cut = 1;
		Res.reserve(Clip_Cut);

		if (Clip_Cut < Reflection_BlendState_With_Clip_Data_Operator::Get_Blend_Clip_CPPVector_Size(Temp_BlendState_With_Clip_Data))
			System_Logger::Get_Instance().Log(System_Logger::Level::err, "Clip_Cut is bigger than Blend_Clip_CPPVector_Size");

		for (size_t Index = 0; Index < Clip_Cut; ++Index)
			Res.emplace_back(
				Reflection_BlendState_With_Clip_Data_Operator::Get_Blend_Clip_CPPVector_Element(Temp_BlendState_With_Clip_Data, Index),
				Reflection_BlendState_With_Clip_Data_Operator::Get_Blend_ratio_CPPVector_Element(Temp_BlendState_With_Clip_Data, Index),
				Reflection_BlendState_With_Clip_Data_Operator::Get_Blend_Skeleton_CPPVector_Element(Temp_BlendState_With_Clip_Data, Index)
			);

		return Res;
	}

	tuple<int, int, float> Skeleton::Calculate_Frame_Data(const shared_ptr<Animation_Clip>& Temp_Clip, float Phase) const {
		const float Exact_Frame = (Reflection_Animation_Clip_Operator::Get_Total_Frame_Attribute(Temp_Clip) - 1) * Phase;

		const int Current_Low{ static_cast<int>(Floor(Exact_Frame)) };
		const int Current_High{ static_cast<int>(Ceil(Exact_Frame)) };

		const float Lerp_ratio{ Exact_Frame - Current_Low };

		return { Current_Low, Current_High, Lerp_ratio };
	}

	void Skeleton::Apply_Clip_To_Skeleton(shared_ptr<Animation_Clip> Temp_Clip, shared_ptr<Skeleton_Node_Map> Temp_Skeleton_Node_Map, int Low_Frame, int Height_Fram, float Lerp_Raotio) {
		for (size_t Index_Node = 0;
			Index_Node < Reflection_Skeleton_Node_Map_Operator::Get_Convert_CPPVector_Size(Temp_Skeleton_Node_Map) &&
			Index_Node < Reflection_Animation_Clip_Operator::Get_Node_Channels_CPPVector_Size(Temp_Clip);
			++Index_Node) {
			const size_t Index_Bone = Reflection_Skeleton_Node_Map_Operator::Get_Convert_CPPVector_Element(Temp_Skeleton_Node_Map, Index_Node);
			if (Index_Bone == std::numeric_limits<size_t>::max() || Index_Bone >= this->m_Bones.size()) {
				System_Logger::Get_Instance().Log(System_Logger::Level::err, "Index_Bone is max or valid");

				continue;
			}

			auto& Temp_Bone = this->m_Bones[Index_Bone];
			const auto& Temp_Channel = Reflection_Animation_Clip_Operator::Get_Node_Channels_CPPVector_Element(Temp_Clip, Index_Node);

			this->Clamp_Frame_Indices(Temp_Channel, Low_Frame, Height_Fram);
			this->Apply_Bone_Transform(Temp_Channel, Temp_Bone, Low_Frame, Height_Fram, Lerp_Raotio);
		}
	}


	tuple<int, int> Skeleton::Clamp_Frame_Indices(const shared_ptr<Animation_Channel>& Temp_Animation_Channel, int low_Frame, int Height_Frame) const {
		int Clamp_Height_Frame = Min({
			Height_Frame,
			static_cast<int>(Reflection_Animation_Channel_Operator::Get_Positions_Keys_CPPVector_Size(Temp_Animation_Channel) - 1),
			static_cast<int>(Reflection_Animation_Channel_Operator::Get_Rotations_Keys_CPPVector_Size(Temp_Animation_Channel) - 1),
			static_cast<int>(Reflection_Animation_Channel_Operator::Get_Scales_Keys_CPPVector_Size(Temp_Animation_Channel) - 1)
			}
		);

		int Clamp_Low_Frame = Clamp(low_Frame, 0, Clamp_Height_Frame - 1);

		return { Clamp_Low_Frame, Clamp_Height_Frame };
	}

	void Skeleton::Apply_Bone_Transform(const shared_ptr<Animation_Channel>& Temp_Animation_Channel, shared_ptr<Bone>& Apply_Bone, int Low_Frame, int Height_Frame, float Lerp_Ratio) {
		const auto& Temp_Position_Keys{ Reflection_Animation_Channel_Operator::Get_Positions_Keys_Attribute(Temp_Animation_Channel) };
		const auto& Temp_Rotation_Keys{ Reflection_Animation_Channel_Operator::Get_Rotations_Keys_Attribute(Temp_Animation_Channel) };
		const auto& Temp_Scale_Keys{ Reflection_Animation_Channel_Operator::Get_Scales_Keys_Attribute(Temp_Animation_Channel) };

		const Vector3 Scale{ Vector3::Lerp(Temp_Scale_Keys[Low_Frame],Temp_Scale_Keys[Height_Frame] ,Lerp_Ratio) };
		const Quaternion Rotation{ Quaternion::Normalized_Lerp(Temp_Rotation_Keys[Low_Frame],Temp_Rotation_Keys[Height_Frame], Lerp_Ratio,true) };
		const Vector3 Position{ Vector3::Lerp(Temp_Position_Keys[Low_Frame],Temp_Position_Keys[Height_Frame],Lerp_Ratio) };

		Affine_Transform Lerp_Transform{ Scale,Rotation,Position };

		Apply_Bone->Set_Transform(Affine_Transform{
			Apply_Bone->Get_Transform().Get_Basis() * Lerp_Transform.Get_Basis(),
			Apply_Bone->Get_Transform().Get_Translation() + Lerp_Transform.Get_Translation()
			}
		);
	}

}// namespace NameSpace_Function::NameSpace_Animation