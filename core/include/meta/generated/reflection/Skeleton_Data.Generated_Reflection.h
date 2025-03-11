#pragma once

#include<string>
#include<vector>
#include<memory>
#include<cstddef>

#include "meta/Reflection/Reflection_Instance.h"
#include "meta/Reflection/Reflection_Register.h"

#include "D:/Amy_Engine/resource/include/components/skeleton/Skeleton_Data.h"

namespace NameSpace_Resource::NameSpace_Components{

    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;
    using std::static_pointer_cast;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Class_Func_Tuple;
    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Class_Base_Class_Tuple;
    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Class_Field_Func_Tuple;
    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Class_Filed_CPPVector_Func_Tuple;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Register;


    class Reflection_Bone_Raw_Operator {
    public:

        static const string Get_Class_Bone_Raw_Spelling(void){
            return string{"Bone_Raw"};
        }

        static const string Get_Class_Displaying_Name(void){
            return string{"Bone_Raw"};            
        }

            static const vector<Reflection_Instance<void>> Get_Base_Class_Bone_Raw_Reflection_Instance_List(shared_ptr<void> Instance){
                vector<Reflection_Instance<void>> Table;

                    

                return Table;
            }

            static const string Get_Field_Name_Type_Spelling(void){
                return string{"string"};
            }

            static const string Get_Field_Name_Spelling(void){
                return string{"m_Name"};
            }


            static const string Get_Field_Name_Display_Name(void){
                return string{"Name"};
            }

            static const void *const Get_Filed_Name_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Bone_Raw>(Instance)->m_Name);
            }

            static void Set_Field_Name_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Bone_Raw>(Instance)->m_Name=*static_cast<const string*>(Value);
            }

            static const bool Is_Filed_Name_CPPVector(void){
                return  false;
            }

            

            static const string Get_Field_CurrentIndex_Type_Spelling(void){
                return string{"size_t"};
            }

            static const string Get_Field_CurrentIndex_Spelling(void){
                return string{"m_CurrentIndex"};
            }


            static const string Get_Field_CurrentIndex_Display_Name(void){
                return string{"CurrentIndex"};
            }

            static const void *const Get_Filed_CurrentIndex_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Bone_Raw>(Instance)->m_CurrentIndex);
            }

            static void Set_Field_CurrentIndex_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Bone_Raw>(Instance)->m_CurrentIndex=*static_cast<const size_t*>(Value);
            }

            static const bool Is_Filed_CurrentIndex_CPPVector(void){
                return  false;
            }

            

            static const string Get_Field_Parent_Index_Type_Spelling(void){
                return string{"size_t"};
            }

            static const string Get_Field_Parent_Index_Spelling(void){
                return string{"m_Parent_Index"};
            }


            static const string Get_Field_Parent_Index_Display_Name(void){
                return string{"Parent_Index"};
            }

            static const void *const Get_Filed_Parent_Index_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Bone_Raw>(Instance)->m_Parent_Index);
            }

            static void Set_Field_Parent_Index_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Bone_Raw>(Instance)->m_Parent_Index=*static_cast<const size_t*>(Value);
            }

            static const bool Is_Filed_Parent_Index_CPPVector(void){
                return  false;
            }

            

            static const string Get_Field_Binding_Pose_Type_Spelling(void){
                return string{"Orthogonal_Transform"};
            }

            static const string Get_Field_Binding_Pose_Spelling(void){
                return string{"m_Binding_Pose"};
            }


            static const string Get_Field_Binding_Pose_Display_Name(void){
                return string{"Binding_Pose"};
            }

            static const void *const Get_Filed_Binding_Pose_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Bone_Raw>(Instance)->m_Binding_Pose);
            }

            static void Set_Field_Binding_Pose_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Bone_Raw>(Instance)->m_Binding_Pose=*static_cast<const Orthogonal_Transform*>(Value);
            }

            static const bool Is_Filed_Binding_Pose_CPPVector(void){
                return  false;
            }

            

            static const string Get_Field_Tpose_Matrix_Type_Spelling(void){
                return string{"Matrix4x4"};
            }

            static const string Get_Field_Tpose_Matrix_Spelling(void){
                return string{"m_Tpose_Matrix"};
            }


            static const string Get_Field_Tpose_Matrix_Display_Name(void){
                return string{"Tpose_Matrix"};
            }

            static const void *const Get_Filed_Tpose_Matrix_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Bone_Raw>(Instance)->m_Tpose_Matrix);
            }

            static void Set_Field_Tpose_Matrix_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Bone_Raw>(Instance)->m_Tpose_Matrix=*static_cast<const Matrix4x4*>(Value);
            }

            static const bool Is_Filed_Tpose_Matrix_CPPVector(void){
                return  false;
            }

            


            static void TypeWrapper_Rigster(void){
                shared_ptr<Class_Func_Tuple> Temp_Class_Func_Tuple{nullptr};
                shared_ptr<Class_Base_Class_Tuple> Temp_Class_Base_Class_Tuple{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Field_Func_Tuple>>> Temp_Class_Field_Func_Tuple_Map{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Filed_CPPVector_Func_Tuple>>> Temp_Class_Filed_CPPVector_Func_Tuple_Map{nullptr};

                Temp_Class_Func_Tuple = make_shared<Class_Func_Tuple>(
                    Reflection_Bone_Raw_Operator::Get_Class_Bone_Raw_Spelling,
                    Reflection_Bone_Raw_Operator::Get_Class_Displaying_Name
                );

                Temp_Class_Base_Class_Tuple = make_shared<Class_Base_Class_Tuple>(
                    Reflection_Bone_Raw_Operator::Get_Base_Class_Bone_Raw_Reflection_Instance_List
                );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Name"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Bone_Raw_Operator::Get_Field_Name_Type_Spelling,
                        Reflection_Bone_Raw_Operator::Get_Field_Name_Spelling,
                        Reflection_Bone_Raw_Operator::Get_Field_Name_Display_Name,
                        Reflection_Bone_Raw_Operator::Get_Filed_Name_Attribute,
                        Reflection_Bone_Raw_Operator::Set_Field_Name_Attribute,
                        Reflection_Bone_Raw_Operator::Is_Filed_Name_CPPVector
                    )
                );

                

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_CurrentIndex"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Bone_Raw_Operator::Get_Field_CurrentIndex_Type_Spelling,
                        Reflection_Bone_Raw_Operator::Get_Field_CurrentIndex_Spelling,
                        Reflection_Bone_Raw_Operator::Get_Field_CurrentIndex_Display_Name,
                        Reflection_Bone_Raw_Operator::Get_Filed_CurrentIndex_Attribute,
                        Reflection_Bone_Raw_Operator::Set_Field_CurrentIndex_Attribute,
                        Reflection_Bone_Raw_Operator::Is_Filed_CurrentIndex_CPPVector
                    )
                );

                

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Parent_Index"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Bone_Raw_Operator::Get_Field_Parent_Index_Type_Spelling,
                        Reflection_Bone_Raw_Operator::Get_Field_Parent_Index_Spelling,
                        Reflection_Bone_Raw_Operator::Get_Field_Parent_Index_Display_Name,
                        Reflection_Bone_Raw_Operator::Get_Filed_Parent_Index_Attribute,
                        Reflection_Bone_Raw_Operator::Set_Field_Parent_Index_Attribute,
                        Reflection_Bone_Raw_Operator::Is_Filed_Parent_Index_CPPVector
                    )
                );

                

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Binding_Pose"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Bone_Raw_Operator::Get_Field_Binding_Pose_Type_Spelling,
                        Reflection_Bone_Raw_Operator::Get_Field_Binding_Pose_Spelling,
                        Reflection_Bone_Raw_Operator::Get_Field_Binding_Pose_Display_Name,
                        Reflection_Bone_Raw_Operator::Get_Filed_Binding_Pose_Attribute,
                        Reflection_Bone_Raw_Operator::Set_Field_Binding_Pose_Attribute,
                        Reflection_Bone_Raw_Operator::Is_Filed_Binding_Pose_CPPVector
                    )
                );

                

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Tpose_Matrix"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Bone_Raw_Operator::Get_Field_Tpose_Matrix_Type_Spelling,
                        Reflection_Bone_Raw_Operator::Get_Field_Tpose_Matrix_Spelling,
                        Reflection_Bone_Raw_Operator::Get_Field_Tpose_Matrix_Display_Name,
                        Reflection_Bone_Raw_Operator::Get_Filed_Tpose_Matrix_Attribute,
                        Reflection_Bone_Raw_Operator::Set_Field_Tpose_Matrix_Attribute,
                        Reflection_Bone_Raw_Operator::Is_Filed_Tpose_Matrix_CPPVector
                    )
                );

                

                
            Reflection_Register::Get_Instance().Register_Class(string{"Bone_Raw"},Temp_Class_Func_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Base_Class(string{"Bone_Raw"},Temp_Class_Base_Class_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Filed(string{"Bone_Raw"},Temp_Class_Field_Func_Tuple_Map);
            Reflection_Register::Get_Instance().Register_Class_Field_CPPVector(string{"Bone_Raw"},Temp_Class_Filed_CPPVector_Func_Tuple_Map);
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

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Class_Func_Tuple;
    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Class_Base_Class_Tuple;
    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Class_Field_Func_Tuple;
    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Class_Filed_CPPVector_Func_Tuple;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Register;


    class Reflection_Skeleton_Data_Operator {
    public:

        static const string Get_Class_Skeleton_Data_Spelling(void){
            return string{"Skeleton_Data"};
        }

        static const string Get_Class_Displaying_Name(void){
            return string{"Skeleton_Data"};            
        }

            static const vector<Reflection_Instance<void>> Get_Base_Class_Skeleton_Data_Reflection_Instance_List(shared_ptr<void> Instance){
                vector<Reflection_Instance<void>> Table;

                    

                return Table;
            }

            static const string Get_Field_Bones_Type_Spelling(void){
                return string{"vector<Bone_Raw>"};
            }

            static const string Get_Field_Bones_Spelling(void){
                return string{"m_Bones"};
            }


            static const string Get_Field_Bones_Display_Name(void){
                return string{"Bones"};
            }

            static const void *const Get_Filed_Bones_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Skeleton_Data>(Instance)->m_Bones);
            }

            static void Set_Field_Bones_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Skeleton_Data>(Instance)->m_Bones=*static_cast<const vector<Bone_Raw>*>(Value);
            }

            static const bool Is_Filed_Bones_CPPVector(void){
                return  !  false;
            }

                static const string Get_Field_Bones_CPPVector_Element_Type_Spelling(void){
                    return string {"m_Bones"};
                }

                static const size_t Get_Field_Bones_CPPVector_Capacity(shared_ptr<void> Instance){
                    return static_pointer_cast<Skeleton_Data>(Instance)->m_Bones.capacity();
                }

                static const size_t Get_Field_Bones_CPPVector_Size(shared_ptr<void> Instance){
                    return static_pointer_cast<Skeleton_Data>(Instance)->m_Bones.size();
                }

                static const void *Get_Field_Bones_CPPVector_Element(shared_ptr<void> Instance, size_t Index){
                    return static_cast<const void*>(&static_pointer_cast<Skeleton_Data>(Instance)->m_Bones[Index]);
                }

                static void Set_Field_Bones_CPPVector_Element(shared_ptr<void> Instance, size_t Index,const void* Value){
                    static_pointer_cast<Skeleton_Data>(Instance)->m_Bones[Index]=*static_cast<const Bone_Raw*>(Value);
                }

            static const string Get_Field_Is_Flat_Type_Spelling(void){
                return string{"bool"};
            }

            static const string Get_Field_Is_Flat_Spelling(void){
                return string{"m_Is_Flat"};
            }


            static const string Get_Field_Is_Flat_Display_Name(void){
                return string{"Is_Flat"};
            }

            static const void *const Get_Filed_Is_Flat_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Skeleton_Data>(Instance)->m_Is_Flat);
            }

            static void Set_Field_Is_Flat_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Skeleton_Data>(Instance)->m_Is_Flat=*static_cast<const bool*>(Value);
            }

            static const bool Is_Filed_Is_Flat_CPPVector(void){
                return  false;
            }

            

            static const string Get_Field_root_index_Type_Spelling(void){
                return string{"size_t"};
            }

            static const string Get_Field_root_index_Spelling(void){
                return string{"root_index"};
            }


            static const string Get_Field_root_index_Display_Name(void){
                return string{"root_index"};
            }

            static const void *const Get_Filed_root_index_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Skeleton_Data>(Instance)->root_index);
            }

            static void Set_Field_root_index_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Skeleton_Data>(Instance)->root_index=*static_cast<const size_t*>(Value);
            }

            static const bool Is_Filed_root_index_CPPVector(void){
                return  false;
            }

            

            static const string Get_Field_In_Topological_Order_Type_Spelling(void){
                return string{"bool"};
            }

            static const string Get_Field_In_Topological_Order_Spelling(void){
                return string{"In_Topological_Order"};
            }


            static const string Get_Field_In_Topological_Order_Display_Name(void){
                return string{"In_Topological_Order"};
            }

            static const void *const Get_Filed_In_Topological_Order_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Skeleton_Data>(Instance)->In_Topological_Order);
            }

            static void Set_Field_In_Topological_Order_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Skeleton_Data>(Instance)->In_Topological_Order=*static_cast<const bool*>(Value);
            }

            static const bool Is_Filed_In_Topological_Order_CPPVector(void){
                return  false;
            }

            


            static void TypeWrapper_Rigster(void){
                shared_ptr<Class_Func_Tuple> Temp_Class_Func_Tuple{nullptr};
                shared_ptr<Class_Base_Class_Tuple> Temp_Class_Base_Class_Tuple{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Field_Func_Tuple>>> Temp_Class_Field_Func_Tuple_Map{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Filed_CPPVector_Func_Tuple>>> Temp_Class_Filed_CPPVector_Func_Tuple_Map{nullptr};

                Temp_Class_Func_Tuple = make_shared<Class_Func_Tuple>(
                    Reflection_Skeleton_Data_Operator::Get_Class_Skeleton_Data_Spelling,
                    Reflection_Skeleton_Data_Operator::Get_Class_Displaying_Name
                );

                Temp_Class_Base_Class_Tuple = make_shared<Class_Base_Class_Tuple>(
                    Reflection_Skeleton_Data_Operator::Get_Base_Class_Skeleton_Data_Reflection_Instance_List
                );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Bones"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Skeleton_Data_Operator::Get_Field_Bones_Type_Spelling,
                        Reflection_Skeleton_Data_Operator::Get_Field_Bones_Spelling,
                        Reflection_Skeleton_Data_Operator::Get_Field_Bones_Display_Name,
                        Reflection_Skeleton_Data_Operator::Get_Filed_Bones_Attribute,
                        Reflection_Skeleton_Data_Operator::Set_Field_Bones_Attribute,
                        Reflection_Skeleton_Data_Operator::Is_Filed_Bones_CPPVector
                    )
                );

                    Temp_Class_Filed_CPPVector_Func_Tuple_Map->emplace(
                    string{"m_Bones"},
                        make_shared<Class_Filed_CPPVector_Func_Tuple>( 
                            Reflection_Skeleton_Data_Operator::Get_Field_Bones_CPPVector_Element_Type_Spelling,
                            Reflection_Skeleton_Data_Operator::Get_Field_Bones_CPPVector_Capacity,
                            Reflection_Skeleton_Data_Operator::Get_Field_Bones_CPPVector_Size,
                            Reflection_Skeleton_Data_Operator::Get_Field_Bones_CPPVector_Element,
                            Reflection_Skeleton_Data_Operator::Set_Field_Bones_CPPVector_Element
                        )
                    );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Is_Flat"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Skeleton_Data_Operator::Get_Field_Is_Flat_Type_Spelling,
                        Reflection_Skeleton_Data_Operator::Get_Field_Is_Flat_Spelling,
                        Reflection_Skeleton_Data_Operator::Get_Field_Is_Flat_Display_Name,
                        Reflection_Skeleton_Data_Operator::Get_Filed_Is_Flat_Attribute,
                        Reflection_Skeleton_Data_Operator::Set_Field_Is_Flat_Attribute,
                        Reflection_Skeleton_Data_Operator::Is_Filed_Is_Flat_CPPVector
                    )
                );

                

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"root_index"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Skeleton_Data_Operator::Get_Field_root_index_Type_Spelling,
                        Reflection_Skeleton_Data_Operator::Get_Field_root_index_Spelling,
                        Reflection_Skeleton_Data_Operator::Get_Field_root_index_Display_Name,
                        Reflection_Skeleton_Data_Operator::Get_Filed_root_index_Attribute,
                        Reflection_Skeleton_Data_Operator::Set_Field_root_index_Attribute,
                        Reflection_Skeleton_Data_Operator::Is_Filed_root_index_CPPVector
                    )
                );

                

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"In_Topological_Order"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Skeleton_Data_Operator::Get_Field_In_Topological_Order_Type_Spelling,
                        Reflection_Skeleton_Data_Operator::Get_Field_In_Topological_Order_Spelling,
                        Reflection_Skeleton_Data_Operator::Get_Field_In_Topological_Order_Display_Name,
                        Reflection_Skeleton_Data_Operator::Get_Filed_In_Topological_Order_Attribute,
                        Reflection_Skeleton_Data_Operator::Set_Field_In_Topological_Order_Attribute,
                        Reflection_Skeleton_Data_Operator::Is_Filed_In_Topological_Order_CPPVector
                    )
                );

                

                
            Reflection_Register::Get_Instance().Register_Class(string{"Skeleton_Data"},Temp_Class_Func_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Base_Class(string{"Skeleton_Data"},Temp_Class_Base_Class_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Filed(string{"Skeleton_Data"},Temp_Class_Field_Func_Tuple_Map);
            Reflection_Register::Get_Instance().Register_Class_Field_CPPVector(string{"Skeleton_Data"},Temp_Class_Filed_CPPVector_Func_Tuple_Map);
        }

    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection


