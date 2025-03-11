#include "animation/Skeleton.h"

#include "logger/System_Logger.h"
#include "meta/generated/reflection/Skeleton_Data.Generated_Reflection.h"
#include "animation/Utilities.h"

namespace NameSpace_Function::NameSpace_Animation {

	using NameSpace_Resource::NameSpace_Components::Reflection_Bone_Raw_Operator;
	using NameSpace_Resource::NameSpace_Components::Reflection_Skeleton_Data_Operator;
	using NameSpace_Core::NameSpace_Logger::System_Logger;

	Skeleton::Skeleton(shared_ptr<Skeleton_Data> Skeleton_Data)
		:m_Skeleton_Data{ Skeleton_Data } {

		if (!Reflection_Skeleton_Data_Operator::Get_Is_Flat_Attribute(this->m_Skeleton_Data) ||
			!Reflection_Skeleton_Data_Operator::Get_In_Topological_Order_Attribute(this->m_Skeleton_Data)) {
			System_Logger::Get_Instance().Log(System_Logger::Level::err, "Skeleton is not in topological order");
		}

		this->m_Bones.reserve(Reflection_Skeleton_Data_Operator::Get_Bones_CPPVector_Size(Skeleton_Data));
		for (const auto& Temp_Bone_Raw : Reflection_Skeleton_Data_Operator::Get_Bones_Attribute(Skeleton_Data)) {

			auto paretn_Bone = NameSpace_Utilities::Find_Bone(this->m_Bones, Reflection_Bone_Raw_Operator::Get_Parent_Index_Attribute(Temp_Bone_Raw), Reflection_Skeleton_Data_Operator::Get_Is_Flat_Attribute(Skeleton_Data));

			this->m_Bones.push_back(std::make_shared<Bone>(Temp_Bone_Raw, paretn_Bone));
		}



	}

}// namespace NameSpace_Function::NameSpace_Animation