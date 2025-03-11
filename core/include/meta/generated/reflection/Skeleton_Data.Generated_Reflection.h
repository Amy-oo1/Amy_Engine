#pragma once

#include<string>
#include<vector>
#include<memory>
#include<cstddef>

#include "meta/Reflection/Reflection_Instance.h"

#include "D:/Amy_Engine/resource/include/components/skeleton/Skeleton_Data.h"

namespace NameSpace_Resource::NameSpace_Components{

    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;
    using std::static_pointer_cast;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

    class Reflection_Bone_Raw_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Bone_Raw"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Bone_Raw"};            
        }

            static const vector<Reflection_Instance<Bone_Raw>> Get_Base_Class_Reflection_Instance_List(shared_ptr<Bone_Raw> Instance){
                vector<Reflection_Instance<Bone_Raw>> Table;

                    

                return Table;
            }

            static const string Get_Name_Type_Spelling(void){
                return string{"string"};
            }

            static const string Get_Name_Spelling(void){
                return string{"m_Name"};
            }


            static const string Get_Name_Display_Name(void){
                return string{"Name"};
            }

            static const string& Get_Name_Attribute(shared_ptr<Bone_Raw> Instance){
                return Instance->m_Name;
            }

            static void Set_Field_Name_Attribute(shared_ptr<Bone_Raw> Instance, const string& Value){
                Instance->m_Name=Value;
            }

            static const bool Is_Filed_Name_CPPVector(void){
                return  false;
            }

            

            static const string Get_Current_Index_Type_Spelling(void){
                return string{"size_t"};
            }

            static const string Get_Current_Index_Spelling(void){
                return string{"m_Current_Index"};
            }


            static const string Get_Current_Index_Display_Name(void){
                return string{"Current_Index"};
            }

            static const size_t& Get_Current_Index_Attribute(shared_ptr<Bone_Raw> Instance){
                return Instance->m_Current_Index;
            }

            static void Set_Field_Current_Index_Attribute(shared_ptr<Bone_Raw> Instance, const size_t& Value){
                Instance->m_Current_Index=Value;
            }

            static const bool Is_Filed_Current_Index_CPPVector(void){
                return  false;
            }

            

            static const string Get_Parent_Index_Type_Spelling(void){
                return string{"size_t"};
            }

            static const string Get_Parent_Index_Spelling(void){
                return string{"m_Parent_Index"};
            }


            static const string Get_Parent_Index_Display_Name(void){
                return string{"Parent_Index"};
            }

            static const size_t& Get_Parent_Index_Attribute(shared_ptr<Bone_Raw> Instance){
                return Instance->m_Parent_Index;
            }

            static void Set_Field_Parent_Index_Attribute(shared_ptr<Bone_Raw> Instance, const size_t& Value){
                Instance->m_Parent_Index=Value;
            }

            static const bool Is_Filed_Parent_Index_CPPVector(void){
                return  false;
            }

            

            static const string Get_Binding_Pose_Type_Spelling(void){
                return string{"Affine_Transform"};
            }

            static const string Get_Binding_Pose_Spelling(void){
                return string{"m_Binding_Pose"};
            }


            static const string Get_Binding_Pose_Display_Name(void){
                return string{"Binding_Pose"};
            }

            static const Affine_Transform& Get_Binding_Pose_Attribute(shared_ptr<Bone_Raw> Instance){
                return Instance->m_Binding_Pose;
            }

            static void Set_Field_Binding_Pose_Attribute(shared_ptr<Bone_Raw> Instance, const Affine_Transform& Value){
                Instance->m_Binding_Pose=Value;
            }

            static const bool Is_Filed_Binding_Pose_CPPVector(void){
                return  false;
            }

            

            static const string Get_Tpose_Matrix_Type_Spelling(void){
                return string{"Matrix4x4"};
            }

            static const string Get_Tpose_Matrix_Spelling(void){
                return string{"m_Tpose_Matrix"};
            }


            static const string Get_Tpose_Matrix_Display_Name(void){
                return string{"Tpose_Matrix"};
            }

            static const Matrix4x4& Get_Tpose_Matrix_Attribute(shared_ptr<Bone_Raw> Instance){
                return Instance->m_Tpose_Matrix;
            }

            static void Set_Field_Tpose_Matrix_Attribute(shared_ptr<Bone_Raw> Instance, const Matrix4x4& Value){
                Instance->m_Tpose_Matrix=Value;
            }

            static const bool Is_Filed_Tpose_Matrix_CPPVector(void){
                return  false;
            }

            


    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection
namespace NameSpace_Resource::NameSpace_Components{

    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;
    using std::static_pointer_cast;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

    class Reflection_Skeleton_Data_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Skeleton_Data"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Skeleton_Data"};            
        }

            static const vector<Reflection_Instance<Skeleton_Data>> Get_Base_Class_Reflection_Instance_List(shared_ptr<Skeleton_Data> Instance){
                vector<Reflection_Instance<Skeleton_Data>> Table;

                    

                return Table;
            }

            static const string Get_Bones_Type_Spelling(void){
                return string{"vector<shared_ptr<Bone_Raw>>"};
            }

            static const string Get_Bones_Spelling(void){
                return string{"m_Bones"};
            }


            static const string Get_Bones_Display_Name(void){
                return string{"Bones"};
            }

            static const vector<shared_ptr<Bone_Raw>>& Get_Bones_Attribute(shared_ptr<Skeleton_Data> Instance){
                return Instance->m_Bones;
            }

            static void Set_Field_Bones_Attribute(shared_ptr<Skeleton_Data> Instance, const vector<shared_ptr<Bone_Raw>>& Value){
                Instance->m_Bones=Value;
            }

            static const bool Is_Filed_Bones_CPPVector(void){
                return  !  false;
            }

                static const string Get_Bones_CPPVector_Element_Type_Spelling(void){
                    return string {"shared_ptr<Bone_Raw>"};
                }

                static const size_t Get_Bones_CPPVector_Capacity(shared_ptr<Skeleton_Data> Instance){
                    return Instance->m_Bones.capacity();
                }

                static const size_t Get_Bones_CPPVector_Size(shared_ptr<Skeleton_Data> Instance){
                    return Instance->m_Bones.size();
                }

                static const shared_ptr<Bone_Raw>& Get_Bones_CPPVector_Element(shared_ptr<Skeleton_Data> Instance, size_t Index){
                    return Instance->m_Bones[Index];
                }

                static void Set_Bones_CPPVector_Element(shared_ptr<Skeleton_Data> Instance, size_t Index, const shared_ptr<Bone_Raw>& Value){
                    Instance->m_Bones[Index]=Value;
                }

                static void Reserve_Bones_CPPVector(shared_ptr<Skeleton_Data> Instance, size_t Capacity){
                    Instance->m_Bones.reserve(Capacity);
                }

                static void Push_Back_Bones_CPPVector(shared_ptr<Skeleton_Data> Instance, const shared_ptr<Bone_Raw>& Value){
                    Instance->m_Bones.push_back(Value);
                }

            static const string Get_Is_Flat_Type_Spelling(void){
                return string{"bool"};
            }

            static const string Get_Is_Flat_Spelling(void){
                return string{"m_Is_Flat"};
            }


            static const string Get_Is_Flat_Display_Name(void){
                return string{"Is_Flat"};
            }

            static const bool& Get_Is_Flat_Attribute(shared_ptr<Skeleton_Data> Instance){
                return Instance->m_Is_Flat;
            }

            static void Set_Field_Is_Flat_Attribute(shared_ptr<Skeleton_Data> Instance, const bool& Value){
                Instance->m_Is_Flat=Value;
            }

            static const bool Is_Filed_Is_Flat_CPPVector(void){
                return  false;
            }

            

            static const string Get_Root_Index_Type_Spelling(void){
                return string{"size_t"};
            }

            static const string Get_Root_Index_Spelling(void){
                return string{"Root_Index"};
            }


            static const string Get_Root_Index_Display_Name(void){
                return string{"Root_Index"};
            }

            static const size_t& Get_Root_Index_Attribute(shared_ptr<Skeleton_Data> Instance){
                return Instance->Root_Index;
            }

            static void Set_Field_Root_Index_Attribute(shared_ptr<Skeleton_Data> Instance, const size_t& Value){
                Instance->Root_Index=Value;
            }

            static const bool Is_Filed_Root_Index_CPPVector(void){
                return  false;
            }

            

            static const string Get_In_Topological_Order_Type_Spelling(void){
                return string{"bool"};
            }

            static const string Get_In_Topological_Order_Spelling(void){
                return string{"In_Topological_Order"};
            }


            static const string Get_In_Topological_Order_Display_Name(void){
                return string{"In_Topological_Order"};
            }

            static const bool& Get_In_Topological_Order_Attribute(shared_ptr<Skeleton_Data> Instance){
                return Instance->In_Topological_Order;
            }

            static void Set_Field_In_Topological_Order_Attribute(shared_ptr<Skeleton_Data> Instance, const bool& Value){
                Instance->In_Topological_Order=Value;
            }

            static const bool Is_Filed_In_Topological_Order_CPPVector(void){
                return  false;
            }

            


    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection

