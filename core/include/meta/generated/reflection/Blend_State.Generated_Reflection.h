#pragma once

#include<string>
#include<vector>
#include<memory>
#include<cstddef>

#include "meta/Reflection/Reflection_Instance.h"
#include "meta/Reflection/Reflection_Register.h"

#include "D:/Amy_Engine/resource/include/components/animation/Blend_State.h"

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


    class Reflection_Bone_Blend_Weight_Operator {
    public:

        static const string Get_Class_Bone_Blend_Weight_Spelling(void){
            return string{"Bone_Blend_Weight"};
        }

        static const string Get_Class_Displaying_Name(void){
            return string{"Bone_Blend_Weight"};            
        }

            static const vector<Reflection_Instance<void>> Get_Base_Class_Bone_Blend_Weight_Reflection_Instance_List(shared_ptr<void> Instance){
                vector<Reflection_Instance<void>> Table;

                    

                return Table;
            }

            static const string Get_Field_Blend_Weights_Type_Spelling(void){
                return string{"vector<float>"};
            }

            static const string Get_Field_Blend_Weights_Spelling(void){
                return string{"m_Blend_Weights"};
            }


            static const string Get_Field_Blend_Weights_Display_Name(void){
                return string{"Blend_Weights"};
            }

            static const void *const Get_Filed_Blend_Weights_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Bone_Blend_Weight>(Instance)->m_Blend_Weights);
            }

            static void Set_Field_Blend_Weights_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Bone_Blend_Weight>(Instance)->m_Blend_Weights=*static_cast<const vector<float>*>(Value);
            }

            static const bool Is_Filed_Blend_Weights_CPPVector(void){
                return  !  false;
            }

                static const string Get_Field_Blend_Weights_CPPVector_Element_Type_Spelling(void){
                    return string {"m_Blend_Weights"};
                }

                static const size_t Get_Field_Blend_Weights_CPPVector_Capacity(shared_ptr<void> Instance){
                    return static_pointer_cast<Bone_Blend_Weight>(Instance)->m_Blend_Weights.capacity();
                }

                static const size_t Get_Field_Blend_Weights_CPPVector_Size(shared_ptr<void> Instance){
                    return static_pointer_cast<Bone_Blend_Weight>(Instance)->m_Blend_Weights.size();
                }

                static const void *Get_Field_Blend_Weights_CPPVector_Element(shared_ptr<void> Instance, size_t Index){
                    return static_cast<const void*>(&static_pointer_cast<Bone_Blend_Weight>(Instance)->m_Blend_Weights[Index]);
                }

                static void Set_Field_Blend_Weights_CPPVector_Element(shared_ptr<void> Instance, size_t Index,const void* Value){
                    static_pointer_cast<Bone_Blend_Weight>(Instance)->m_Blend_Weights[Index]=*static_cast<const float*>(Value);
                }


            static void TypeWrapper_Rigster(void){
                shared_ptr<Class_Func_Tuple> Temp_Class_Func_Tuple{nullptr};
                shared_ptr<Class_Base_Class_Tuple> Temp_Class_Base_Class_Tuple{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Field_Func_Tuple>>> Temp_Class_Field_Func_Tuple_Map{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Filed_CPPVector_Func_Tuple>>> Temp_Class_Filed_CPPVector_Func_Tuple_Map{nullptr};

                Temp_Class_Func_Tuple = make_shared<Class_Func_Tuple>(
                    Reflection_Bone_Blend_Weight_Operator::Get_Class_Bone_Blend_Weight_Spelling,
                    Reflection_Bone_Blend_Weight_Operator::Get_Class_Displaying_Name
                );

                Temp_Class_Base_Class_Tuple = make_shared<Class_Base_Class_Tuple>(
                    Reflection_Bone_Blend_Weight_Operator::Get_Base_Class_Bone_Blend_Weight_Reflection_Instance_List
                );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Blend_Weights"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Bone_Blend_Weight_Operator::Get_Field_Blend_Weights_Type_Spelling,
                        Reflection_Bone_Blend_Weight_Operator::Get_Field_Blend_Weights_Spelling,
                        Reflection_Bone_Blend_Weight_Operator::Get_Field_Blend_Weights_Display_Name,
                        Reflection_Bone_Blend_Weight_Operator::Get_Filed_Blend_Weights_Attribute,
                        Reflection_Bone_Blend_Weight_Operator::Set_Field_Blend_Weights_Attribute,
                        Reflection_Bone_Blend_Weight_Operator::Is_Filed_Blend_Weights_CPPVector
                    )
                );

                    Temp_Class_Filed_CPPVector_Func_Tuple_Map->emplace(
                    string{"m_Blend_Weights"},
                        make_shared<Class_Filed_CPPVector_Func_Tuple>( 
                            Reflection_Bone_Blend_Weight_Operator::Get_Field_Blend_Weights_CPPVector_Element_Type_Spelling,
                            Reflection_Bone_Blend_Weight_Operator::Get_Field_Blend_Weights_CPPVector_Capacity,
                            Reflection_Bone_Blend_Weight_Operator::Get_Field_Blend_Weights_CPPVector_Size,
                            Reflection_Bone_Blend_Weight_Operator::Get_Field_Blend_Weights_CPPVector_Element,
                            Reflection_Bone_Blend_Weight_Operator::Set_Field_Blend_Weights_CPPVector_Element
                        )
                    );

                
            Reflection_Register::Get_Instance().Register_Class(string{"Bone_Blend_Weight"},Temp_Class_Func_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Base_Class(string{"Bone_Blend_Weight"},Temp_Class_Base_Class_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Filed(string{"Bone_Blend_Weight"},Temp_Class_Field_Func_Tuple_Map);
            Reflection_Register::Get_Instance().Register_Class_Field_CPPVector(string{"Bone_Blend_Weight"},Temp_Class_Filed_CPPVector_Func_Tuple_Map);
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


    class Reflection_BlendState_With_Clip_Data_Operator {
    public:

        static const string Get_Class_BlendState_With_Clip_Data_Spelling(void){
            return string{"BlendState_With_Clip_Data"};
        }

        static const string Get_Class_Displaying_Name(void){
            return string{"BlendState_With_Clip_Data"};            
        }

            static const vector<Reflection_Instance<void>> Get_Base_Class_BlendState_With_Clip_Data_Reflection_Instance_List(shared_ptr<void> Instance){
                vector<Reflection_Instance<void>> Table;

                    

                return Table;
            }

            static const string Get_Field_Blend_Clip_Type_Spelling(void){
                return string{"vector<Animation_Clip>"};
            }

            static const string Get_Field_Blend_Clip_Spelling(void){
                return string{"m_Blend_Clip"};
            }


            static const string Get_Field_Blend_Clip_Display_Name(void){
                return string{"Blend_Clip"};
            }

            static const void *const Get_Filed_Blend_Clip_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<BlendState_With_Clip_Data>(Instance)->m_Blend_Clip);
            }

            static void Set_Field_Blend_Clip_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<BlendState_With_Clip_Data>(Instance)->m_Blend_Clip=*static_cast<const vector<Animation_Clip>*>(Value);
            }

            static const bool Is_Filed_Blend_Clip_CPPVector(void){
                return  !  false;
            }

                static const string Get_Field_Blend_Clip_CPPVector_Element_Type_Spelling(void){
                    return string {"m_Blend_Clip"};
                }

                static const size_t Get_Field_Blend_Clip_CPPVector_Capacity(shared_ptr<void> Instance){
                    return static_pointer_cast<BlendState_With_Clip_Data>(Instance)->m_Blend_Clip.capacity();
                }

                static const size_t Get_Field_Blend_Clip_CPPVector_Size(shared_ptr<void> Instance){
                    return static_pointer_cast<BlendState_With_Clip_Data>(Instance)->m_Blend_Clip.size();
                }

                static const void *Get_Field_Blend_Clip_CPPVector_Element(shared_ptr<void> Instance, size_t Index){
                    return static_cast<const void*>(&static_pointer_cast<BlendState_With_Clip_Data>(Instance)->m_Blend_Clip[Index]);
                }

                static void Set_Field_Blend_Clip_CPPVector_Element(shared_ptr<void> Instance, size_t Index,const void* Value){
                    static_pointer_cast<BlendState_With_Clip_Data>(Instance)->m_Blend_Clip[Index]=*static_cast<const Animation_Clip*>(Value);
                }

            static const string Get_Field_Blend_Skeleton_Type_Spelling(void){
                return string{"vector<Skeleton_Node_Map>"};
            }

            static const string Get_Field_Blend_Skeleton_Spelling(void){
                return string{"m_Blend_Skeleton"};
            }


            static const string Get_Field_Blend_Skeleton_Display_Name(void){
                return string{"Blend_Skeleton"};
            }

            static const void *const Get_Filed_Blend_Skeleton_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<BlendState_With_Clip_Data>(Instance)->m_Blend_Skeleton);
            }

            static void Set_Field_Blend_Skeleton_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<BlendState_With_Clip_Data>(Instance)->m_Blend_Skeleton=*static_cast<const vector<Skeleton_Node_Map>*>(Value);
            }

            static const bool Is_Filed_Blend_Skeleton_CPPVector(void){
                return  !  false;
            }

                static const string Get_Field_Blend_Skeleton_CPPVector_Element_Type_Spelling(void){
                    return string {"m_Blend_Skeleton"};
                }

                static const size_t Get_Field_Blend_Skeleton_CPPVector_Capacity(shared_ptr<void> Instance){
                    return static_pointer_cast<BlendState_With_Clip_Data>(Instance)->m_Blend_Skeleton.capacity();
                }

                static const size_t Get_Field_Blend_Skeleton_CPPVector_Size(shared_ptr<void> Instance){
                    return static_pointer_cast<BlendState_With_Clip_Data>(Instance)->m_Blend_Skeleton.size();
                }

                static const void *Get_Field_Blend_Skeleton_CPPVector_Element(shared_ptr<void> Instance, size_t Index){
                    return static_cast<const void*>(&static_pointer_cast<BlendState_With_Clip_Data>(Instance)->m_Blend_Skeleton[Index]);
                }

                static void Set_Field_Blend_Skeleton_CPPVector_Element(shared_ptr<void> Instance, size_t Index,const void* Value){
                    static_pointer_cast<BlendState_With_Clip_Data>(Instance)->m_Blend_Skeleton[Index]=*static_cast<const Skeleton_Node_Map*>(Value);
                }

            static const string Get_Field_Blend_Weights_Type_Spelling(void){
                return string{"vector<Bone_Blend_Weight>"};
            }

            static const string Get_Field_Blend_Weights_Spelling(void){
                return string{"m_Blend_Weights"};
            }


            static const string Get_Field_Blend_Weights_Display_Name(void){
                return string{"Blend_Weights"};
            }

            static const void *const Get_Filed_Blend_Weights_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<BlendState_With_Clip_Data>(Instance)->m_Blend_Weights);
            }

            static void Set_Field_Blend_Weights_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<BlendState_With_Clip_Data>(Instance)->m_Blend_Weights=*static_cast<const vector<Bone_Blend_Weight>*>(Value);
            }

            static const bool Is_Filed_Blend_Weights_CPPVector(void){
                return  !  false;
            }

                static const string Get_Field_Blend_Weights_CPPVector_Element_Type_Spelling(void){
                    return string {"m_Blend_Weights"};
                }

                static const size_t Get_Field_Blend_Weights_CPPVector_Capacity(shared_ptr<void> Instance){
                    return static_pointer_cast<BlendState_With_Clip_Data>(Instance)->m_Blend_Weights.capacity();
                }

                static const size_t Get_Field_Blend_Weights_CPPVector_Size(shared_ptr<void> Instance){
                    return static_pointer_cast<BlendState_With_Clip_Data>(Instance)->m_Blend_Weights.size();
                }

                static const void *Get_Field_Blend_Weights_CPPVector_Element(shared_ptr<void> Instance, size_t Index){
                    return static_cast<const void*>(&static_pointer_cast<BlendState_With_Clip_Data>(Instance)->m_Blend_Weights[Index]);
                }

                static void Set_Field_Blend_Weights_CPPVector_Element(shared_ptr<void> Instance, size_t Index,const void* Value){
                    static_pointer_cast<BlendState_With_Clip_Data>(Instance)->m_Blend_Weights[Index]=*static_cast<const Bone_Blend_Weight*>(Value);
                }

            static const string Get_Field_Blend_ratio_Type_Spelling(void){
                return string{"vector<float>"};
            }

            static const string Get_Field_Blend_ratio_Spelling(void){
                return string{"m_Blend_ratio"};
            }


            static const string Get_Field_Blend_ratio_Display_Name(void){
                return string{"Blend_ratio"};
            }

            static const void *const Get_Filed_Blend_ratio_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<BlendState_With_Clip_Data>(Instance)->m_Blend_ratio);
            }

            static void Set_Field_Blend_ratio_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<BlendState_With_Clip_Data>(Instance)->m_Blend_ratio=*static_cast<const vector<float>*>(Value);
            }

            static const bool Is_Filed_Blend_ratio_CPPVector(void){
                return  !  false;
            }

                static const string Get_Field_Blend_ratio_CPPVector_Element_Type_Spelling(void){
                    return string {"m_Blend_ratio"};
                }

                static const size_t Get_Field_Blend_ratio_CPPVector_Capacity(shared_ptr<void> Instance){
                    return static_pointer_cast<BlendState_With_Clip_Data>(Instance)->m_Blend_ratio.capacity();
                }

                static const size_t Get_Field_Blend_ratio_CPPVector_Size(shared_ptr<void> Instance){
                    return static_pointer_cast<BlendState_With_Clip_Data>(Instance)->m_Blend_ratio.size();
                }

                static const void *Get_Field_Blend_ratio_CPPVector_Element(shared_ptr<void> Instance, size_t Index){
                    return static_cast<const void*>(&static_pointer_cast<BlendState_With_Clip_Data>(Instance)->m_Blend_ratio[Index]);
                }

                static void Set_Field_Blend_ratio_CPPVector_Element(shared_ptr<void> Instance, size_t Index,const void* Value){
                    static_pointer_cast<BlendState_With_Clip_Data>(Instance)->m_Blend_ratio[Index]=*static_cast<const float*>(Value);
                }


            static void TypeWrapper_Rigster(void){
                shared_ptr<Class_Func_Tuple> Temp_Class_Func_Tuple{nullptr};
                shared_ptr<Class_Base_Class_Tuple> Temp_Class_Base_Class_Tuple{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Field_Func_Tuple>>> Temp_Class_Field_Func_Tuple_Map{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Filed_CPPVector_Func_Tuple>>> Temp_Class_Filed_CPPVector_Func_Tuple_Map{nullptr};

                Temp_Class_Func_Tuple = make_shared<Class_Func_Tuple>(
                    Reflection_BlendState_With_Clip_Data_Operator::Get_Class_BlendState_With_Clip_Data_Spelling,
                    Reflection_BlendState_With_Clip_Data_Operator::Get_Class_Displaying_Name
                );

                Temp_Class_Base_Class_Tuple = make_shared<Class_Base_Class_Tuple>(
                    Reflection_BlendState_With_Clip_Data_Operator::Get_Base_Class_BlendState_With_Clip_Data_Reflection_Instance_List
                );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Blend_Clip"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_BlendState_With_Clip_Data_Operator::Get_Field_Blend_Clip_Type_Spelling,
                        Reflection_BlendState_With_Clip_Data_Operator::Get_Field_Blend_Clip_Spelling,
                        Reflection_BlendState_With_Clip_Data_Operator::Get_Field_Blend_Clip_Display_Name,
                        Reflection_BlendState_With_Clip_Data_Operator::Get_Filed_Blend_Clip_Attribute,
                        Reflection_BlendState_With_Clip_Data_Operator::Set_Field_Blend_Clip_Attribute,
                        Reflection_BlendState_With_Clip_Data_Operator::Is_Filed_Blend_Clip_CPPVector
                    )
                );

                    Temp_Class_Filed_CPPVector_Func_Tuple_Map->emplace(
                    string{"m_Blend_Clip"},
                        make_shared<Class_Filed_CPPVector_Func_Tuple>( 
                            Reflection_BlendState_With_Clip_Data_Operator::Get_Field_Blend_Clip_CPPVector_Element_Type_Spelling,
                            Reflection_BlendState_With_Clip_Data_Operator::Get_Field_Blend_Clip_CPPVector_Capacity,
                            Reflection_BlendState_With_Clip_Data_Operator::Get_Field_Blend_Clip_CPPVector_Size,
                            Reflection_BlendState_With_Clip_Data_Operator::Get_Field_Blend_Clip_CPPVector_Element,
                            Reflection_BlendState_With_Clip_Data_Operator::Set_Field_Blend_Clip_CPPVector_Element
                        )
                    );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Blend_Skeleton"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_BlendState_With_Clip_Data_Operator::Get_Field_Blend_Skeleton_Type_Spelling,
                        Reflection_BlendState_With_Clip_Data_Operator::Get_Field_Blend_Skeleton_Spelling,
                        Reflection_BlendState_With_Clip_Data_Operator::Get_Field_Blend_Skeleton_Display_Name,
                        Reflection_BlendState_With_Clip_Data_Operator::Get_Filed_Blend_Skeleton_Attribute,
                        Reflection_BlendState_With_Clip_Data_Operator::Set_Field_Blend_Skeleton_Attribute,
                        Reflection_BlendState_With_Clip_Data_Operator::Is_Filed_Blend_Skeleton_CPPVector
                    )
                );

                    Temp_Class_Filed_CPPVector_Func_Tuple_Map->emplace(
                    string{"m_Blend_Skeleton"},
                        make_shared<Class_Filed_CPPVector_Func_Tuple>( 
                            Reflection_BlendState_With_Clip_Data_Operator::Get_Field_Blend_Skeleton_CPPVector_Element_Type_Spelling,
                            Reflection_BlendState_With_Clip_Data_Operator::Get_Field_Blend_Skeleton_CPPVector_Capacity,
                            Reflection_BlendState_With_Clip_Data_Operator::Get_Field_Blend_Skeleton_CPPVector_Size,
                            Reflection_BlendState_With_Clip_Data_Operator::Get_Field_Blend_Skeleton_CPPVector_Element,
                            Reflection_BlendState_With_Clip_Data_Operator::Set_Field_Blend_Skeleton_CPPVector_Element
                        )
                    );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Blend_Weights"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_BlendState_With_Clip_Data_Operator::Get_Field_Blend_Weights_Type_Spelling,
                        Reflection_BlendState_With_Clip_Data_Operator::Get_Field_Blend_Weights_Spelling,
                        Reflection_BlendState_With_Clip_Data_Operator::Get_Field_Blend_Weights_Display_Name,
                        Reflection_BlendState_With_Clip_Data_Operator::Get_Filed_Blend_Weights_Attribute,
                        Reflection_BlendState_With_Clip_Data_Operator::Set_Field_Blend_Weights_Attribute,
                        Reflection_BlendState_With_Clip_Data_Operator::Is_Filed_Blend_Weights_CPPVector
                    )
                );

                    Temp_Class_Filed_CPPVector_Func_Tuple_Map->emplace(
                    string{"m_Blend_Weights"},
                        make_shared<Class_Filed_CPPVector_Func_Tuple>( 
                            Reflection_BlendState_With_Clip_Data_Operator::Get_Field_Blend_Weights_CPPVector_Element_Type_Spelling,
                            Reflection_BlendState_With_Clip_Data_Operator::Get_Field_Blend_Weights_CPPVector_Capacity,
                            Reflection_BlendState_With_Clip_Data_Operator::Get_Field_Blend_Weights_CPPVector_Size,
                            Reflection_BlendState_With_Clip_Data_Operator::Get_Field_Blend_Weights_CPPVector_Element,
                            Reflection_BlendState_With_Clip_Data_Operator::Set_Field_Blend_Weights_CPPVector_Element
                        )
                    );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Blend_ratio"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_BlendState_With_Clip_Data_Operator::Get_Field_Blend_ratio_Type_Spelling,
                        Reflection_BlendState_With_Clip_Data_Operator::Get_Field_Blend_ratio_Spelling,
                        Reflection_BlendState_With_Clip_Data_Operator::Get_Field_Blend_ratio_Display_Name,
                        Reflection_BlendState_With_Clip_Data_Operator::Get_Filed_Blend_ratio_Attribute,
                        Reflection_BlendState_With_Clip_Data_Operator::Set_Field_Blend_ratio_Attribute,
                        Reflection_BlendState_With_Clip_Data_Operator::Is_Filed_Blend_ratio_CPPVector
                    )
                );

                    Temp_Class_Filed_CPPVector_Func_Tuple_Map->emplace(
                    string{"m_Blend_ratio"},
                        make_shared<Class_Filed_CPPVector_Func_Tuple>( 
                            Reflection_BlendState_With_Clip_Data_Operator::Get_Field_Blend_ratio_CPPVector_Element_Type_Spelling,
                            Reflection_BlendState_With_Clip_Data_Operator::Get_Field_Blend_ratio_CPPVector_Capacity,
                            Reflection_BlendState_With_Clip_Data_Operator::Get_Field_Blend_ratio_CPPVector_Size,
                            Reflection_BlendState_With_Clip_Data_Operator::Get_Field_Blend_ratio_CPPVector_Element,
                            Reflection_BlendState_With_Clip_Data_Operator::Set_Field_Blend_ratio_CPPVector_Element
                        )
                    );

                
            Reflection_Register::Get_Instance().Register_Class(string{"BlendState_With_Clip_Data"},Temp_Class_Func_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Base_Class(string{"BlendState_With_Clip_Data"},Temp_Class_Base_Class_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Filed(string{"BlendState_With_Clip_Data"},Temp_Class_Field_Func_Tuple_Map);
            Reflection_Register::Get_Instance().Register_Class_Field_CPPVector(string{"BlendState_With_Clip_Data"},Temp_Class_Filed_CPPVector_Func_Tuple_Map);
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


    class Reflection_Blend_State_Operator {
    public:

        static const string Get_Class_Blend_State_Spelling(void){
            return string{"Blend_State"};
        }

        static const string Get_Class_Displaying_Name(void){
            return string{"Blend_State"};            
        }

            static const vector<Reflection_Instance<void>> Get_Base_Class_Blend_State_Reflection_Instance_List(shared_ptr<void> Instance){
                vector<Reflection_Instance<void>> Table;

                    

                return Table;
            }

            static const string Get_Field_Blend_Clip_File_Path_Type_Spelling(void){
                return string{"vector<path>"};
            }

            static const string Get_Field_Blend_Clip_File_Path_Spelling(void){
                return string{"m_Blend_Clip_File_Path"};
            }


            static const string Get_Field_Blend_Clip_File_Path_Display_Name(void){
                return string{"Blend_Clip_File_Path"};
            }

            static const void *const Get_Filed_Blend_Clip_File_Path_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Blend_State>(Instance)->m_Blend_Clip_File_Path);
            }

            static void Set_Field_Blend_Clip_File_Path_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Blend_State>(Instance)->m_Blend_Clip_File_Path=*static_cast<const vector<path>*>(Value);
            }

            static const bool Is_Filed_Blend_Clip_File_Path_CPPVector(void){
                return  !  false;
            }

                static const string Get_Field_Blend_Clip_File_Path_CPPVector_Element_Type_Spelling(void){
                    return string {"m_Blend_Clip_File_Path"};
                }

                static const size_t Get_Field_Blend_Clip_File_Path_CPPVector_Capacity(shared_ptr<void> Instance){
                    return static_pointer_cast<Blend_State>(Instance)->m_Blend_Clip_File_Path.capacity();
                }

                static const size_t Get_Field_Blend_Clip_File_Path_CPPVector_Size(shared_ptr<void> Instance){
                    return static_pointer_cast<Blend_State>(Instance)->m_Blend_Clip_File_Path.size();
                }

                static const void *Get_Field_Blend_Clip_File_Path_CPPVector_Element(shared_ptr<void> Instance, size_t Index){
                    return static_cast<const void*>(&static_pointer_cast<Blend_State>(Instance)->m_Blend_Clip_File_Path[Index]);
                }

                static void Set_Field_Blend_Clip_File_Path_CPPVector_Element(shared_ptr<void> Instance, size_t Index,const void* Value){
                    static_pointer_cast<Blend_State>(Instance)->m_Blend_Clip_File_Path[Index]=*static_cast<const path*>(Value);
                }

            static const string Get_Field_Blend_Clip_File_Length_Type_Spelling(void){
                return string{"vector<float>"};
            }

            static const string Get_Field_Blend_Clip_File_Length_Spelling(void){
                return string{"m_Blend_Clip_File_Length"};
            }


            static const string Get_Field_Blend_Clip_File_Length_Display_Name(void){
                return string{"Blend_Clip_File_Length"};
            }

            static const void *const Get_Filed_Blend_Clip_File_Length_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Blend_State>(Instance)->m_Blend_Clip_File_Length);
            }

            static void Set_Field_Blend_Clip_File_Length_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Blend_State>(Instance)->m_Blend_Clip_File_Length=*static_cast<const vector<float>*>(Value);
            }

            static const bool Is_Filed_Blend_Clip_File_Length_CPPVector(void){
                return  !  false;
            }

                static const string Get_Field_Blend_Clip_File_Length_CPPVector_Element_Type_Spelling(void){
                    return string {"m_Blend_Clip_File_Length"};
                }

                static const size_t Get_Field_Blend_Clip_File_Length_CPPVector_Capacity(shared_ptr<void> Instance){
                    return static_pointer_cast<Blend_State>(Instance)->m_Blend_Clip_File_Length.capacity();
                }

                static const size_t Get_Field_Blend_Clip_File_Length_CPPVector_Size(shared_ptr<void> Instance){
                    return static_pointer_cast<Blend_State>(Instance)->m_Blend_Clip_File_Length.size();
                }

                static const void *Get_Field_Blend_Clip_File_Length_CPPVector_Element(shared_ptr<void> Instance, size_t Index){
                    return static_cast<const void*>(&static_pointer_cast<Blend_State>(Instance)->m_Blend_Clip_File_Length[Index]);
                }

                static void Set_Field_Blend_Clip_File_Length_CPPVector_Element(shared_ptr<void> Instance, size_t Index,const void* Value){
                    static_pointer_cast<Blend_State>(Instance)->m_Blend_Clip_File_Length[Index]=*static_cast<const float*>(Value);
                }

            static const string Get_Field_Blend_Skeleton_Map_File_Path_Type_Spelling(void){
                return string{"vector<path>"};
            }

            static const string Get_Field_Blend_Skeleton_Map_File_Path_Spelling(void){
                return string{"m_Blend_Skeleton_Map_File_Path"};
            }


            static const string Get_Field_Blend_Skeleton_Map_File_Path_Display_Name(void){
                return string{"Blend_Skeleton_Map_File_Path"};
            }

            static const void *const Get_Filed_Blend_Skeleton_Map_File_Path_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Blend_State>(Instance)->m_Blend_Skeleton_Map_File_Path);
            }

            static void Set_Field_Blend_Skeleton_Map_File_Path_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Blend_State>(Instance)->m_Blend_Skeleton_Map_File_Path=*static_cast<const vector<path>*>(Value);
            }

            static const bool Is_Filed_Blend_Skeleton_Map_File_Path_CPPVector(void){
                return  !  false;
            }

                static const string Get_Field_Blend_Skeleton_Map_File_Path_CPPVector_Element_Type_Spelling(void){
                    return string {"m_Blend_Skeleton_Map_File_Path"};
                }

                static const size_t Get_Field_Blend_Skeleton_Map_File_Path_CPPVector_Capacity(shared_ptr<void> Instance){
                    return static_pointer_cast<Blend_State>(Instance)->m_Blend_Skeleton_Map_File_Path.capacity();
                }

                static const size_t Get_Field_Blend_Skeleton_Map_File_Path_CPPVector_Size(shared_ptr<void> Instance){
                    return static_pointer_cast<Blend_State>(Instance)->m_Blend_Skeleton_Map_File_Path.size();
                }

                static const void *Get_Field_Blend_Skeleton_Map_File_Path_CPPVector_Element(shared_ptr<void> Instance, size_t Index){
                    return static_cast<const void*>(&static_pointer_cast<Blend_State>(Instance)->m_Blend_Skeleton_Map_File_Path[Index]);
                }

                static void Set_Field_Blend_Skeleton_Map_File_Path_CPPVector_Element(shared_ptr<void> Instance, size_t Index,const void* Value){
                    static_pointer_cast<Blend_State>(Instance)->m_Blend_Skeleton_Map_File_Path[Index]=*static_cast<const path*>(Value);
                }

            static const string Get_Field_Blend_Weights_Type_Spelling(void){
                return string{"vector<float>"};
            }

            static const string Get_Field_Blend_Weights_Spelling(void){
                return string{"m_Blend_Weights"};
            }


            static const string Get_Field_Blend_Weights_Display_Name(void){
                return string{"Blend_Weights"};
            }

            static const void *const Get_Filed_Blend_Weights_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Blend_State>(Instance)->m_Blend_Weights);
            }

            static void Set_Field_Blend_Weights_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Blend_State>(Instance)->m_Blend_Weights=*static_cast<const vector<float>*>(Value);
            }

            static const bool Is_Filed_Blend_Weights_CPPVector(void){
                return  !  false;
            }

                static const string Get_Field_Blend_Weights_CPPVector_Element_Type_Spelling(void){
                    return string {"m_Blend_Weights"};
                }

                static const size_t Get_Field_Blend_Weights_CPPVector_Capacity(shared_ptr<void> Instance){
                    return static_pointer_cast<Blend_State>(Instance)->m_Blend_Weights.capacity();
                }

                static const size_t Get_Field_Blend_Weights_CPPVector_Size(shared_ptr<void> Instance){
                    return static_pointer_cast<Blend_State>(Instance)->m_Blend_Weights.size();
                }

                static const void *Get_Field_Blend_Weights_CPPVector_Element(shared_ptr<void> Instance, size_t Index){
                    return static_cast<const void*>(&static_pointer_cast<Blend_State>(Instance)->m_Blend_Weights[Index]);
                }

                static void Set_Field_Blend_Weights_CPPVector_Element(shared_ptr<void> Instance, size_t Index,const void* Value){
                    static_pointer_cast<Blend_State>(Instance)->m_Blend_Weights[Index]=*static_cast<const float*>(Value);
                }

            static const string Get_Field_Blend_Mask_File_Path_Type_Spelling(void){
                return string{"vector<path>"};
            }

            static const string Get_Field_Blend_Mask_File_Path_Spelling(void){
                return string{"m_Blend_Mask_File_Path"};
            }


            static const string Get_Field_Blend_Mask_File_Path_Display_Name(void){
                return string{"Blend_Mask_File_Path"};
            }

            static const void *const Get_Filed_Blend_Mask_File_Path_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Blend_State>(Instance)->m_Blend_Mask_File_Path);
            }

            static void Set_Field_Blend_Mask_File_Path_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Blend_State>(Instance)->m_Blend_Mask_File_Path=*static_cast<const vector<path>*>(Value);
            }

            static const bool Is_Filed_Blend_Mask_File_Path_CPPVector(void){
                return  !  false;
            }

                static const string Get_Field_Blend_Mask_File_Path_CPPVector_Element_Type_Spelling(void){
                    return string {"m_Blend_Mask_File_Path"};
                }

                static const size_t Get_Field_Blend_Mask_File_Path_CPPVector_Capacity(shared_ptr<void> Instance){
                    return static_pointer_cast<Blend_State>(Instance)->m_Blend_Mask_File_Path.capacity();
                }

                static const size_t Get_Field_Blend_Mask_File_Path_CPPVector_Size(shared_ptr<void> Instance){
                    return static_pointer_cast<Blend_State>(Instance)->m_Blend_Mask_File_Path.size();
                }

                static const void *Get_Field_Blend_Mask_File_Path_CPPVector_Element(shared_ptr<void> Instance, size_t Index){
                    return static_cast<const void*>(&static_pointer_cast<Blend_State>(Instance)->m_Blend_Mask_File_Path[Index]);
                }

                static void Set_Field_Blend_Mask_File_Path_CPPVector_Element(shared_ptr<void> Instance, size_t Index,const void* Value){
                    static_pointer_cast<Blend_State>(Instance)->m_Blend_Mask_File_Path[Index]=*static_cast<const path*>(Value);
                }

            static const string Get_Field_BlendState_Type_Spelling(void){
                return string{"vector<BlendState_With_Clip_Data>"};
            }

            static const string Get_Field_BlendState_Spelling(void){
                return string{"m_BlendState"};
            }


            static const string Get_Field_BlendState_Display_Name(void){
                return string{"BlendState"};
            }

            static const void *const Get_Filed_BlendState_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Blend_State>(Instance)->m_BlendState);
            }

            static void Set_Field_BlendState_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Blend_State>(Instance)->m_BlendState=*static_cast<const vector<BlendState_With_Clip_Data>*>(Value);
            }

            static const bool Is_Filed_BlendState_CPPVector(void){
                return  !  false;
            }

                static const string Get_Field_BlendState_CPPVector_Element_Type_Spelling(void){
                    return string {"m_BlendState"};
                }

                static const size_t Get_Field_BlendState_CPPVector_Capacity(shared_ptr<void> Instance){
                    return static_pointer_cast<Blend_State>(Instance)->m_BlendState.capacity();
                }

                static const size_t Get_Field_BlendState_CPPVector_Size(shared_ptr<void> Instance){
                    return static_pointer_cast<Blend_State>(Instance)->m_BlendState.size();
                }

                static const void *Get_Field_BlendState_CPPVector_Element(shared_ptr<void> Instance, size_t Index){
                    return static_cast<const void*>(&static_pointer_cast<Blend_State>(Instance)->m_BlendState[Index]);
                }

                static void Set_Field_BlendState_CPPVector_Element(shared_ptr<void> Instance, size_t Index,const void* Value){
                    static_pointer_cast<Blend_State>(Instance)->m_BlendState[Index]=*static_cast<const BlendState_With_Clip_Data*>(Value);
                }

            static const string Get_Field_Blend_ratio_Type_Spelling(void){
                return string{"vector<float>"};
            }

            static const string Get_Field_Blend_ratio_Spelling(void){
                return string{"m_Blend_ratio"};
            }


            static const string Get_Field_Blend_ratio_Display_Name(void){
                return string{"Blend_ratio"};
            }

            static const void *const Get_Filed_Blend_ratio_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Blend_State>(Instance)->m_Blend_ratio);
            }

            static void Set_Field_Blend_ratio_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Blend_State>(Instance)->m_Blend_ratio=*static_cast<const vector<float>*>(Value);
            }

            static const bool Is_Filed_Blend_ratio_CPPVector(void){
                return  !  false;
            }

                static const string Get_Field_Blend_ratio_CPPVector_Element_Type_Spelling(void){
                    return string {"m_Blend_ratio"};
                }

                static const size_t Get_Field_Blend_ratio_CPPVector_Capacity(shared_ptr<void> Instance){
                    return static_pointer_cast<Blend_State>(Instance)->m_Blend_ratio.capacity();
                }

                static const size_t Get_Field_Blend_ratio_CPPVector_Size(shared_ptr<void> Instance){
                    return static_pointer_cast<Blend_State>(Instance)->m_Blend_ratio.size();
                }

                static const void *Get_Field_Blend_ratio_CPPVector_Element(shared_ptr<void> Instance, size_t Index){
                    return static_cast<const void*>(&static_pointer_cast<Blend_State>(Instance)->m_Blend_ratio[Index]);
                }

                static void Set_Field_Blend_ratio_CPPVector_Element(shared_ptr<void> Instance, size_t Index,const void* Value){
                    static_pointer_cast<Blend_State>(Instance)->m_Blend_ratio[Index]=*static_cast<const float*>(Value);
                }


            static void TypeWrapper_Rigster(void){
                shared_ptr<Class_Func_Tuple> Temp_Class_Func_Tuple{nullptr};
                shared_ptr<Class_Base_Class_Tuple> Temp_Class_Base_Class_Tuple{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Field_Func_Tuple>>> Temp_Class_Field_Func_Tuple_Map{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Filed_CPPVector_Func_Tuple>>> Temp_Class_Filed_CPPVector_Func_Tuple_Map{nullptr};

                Temp_Class_Func_Tuple = make_shared<Class_Func_Tuple>(
                    Reflection_Blend_State_Operator::Get_Class_Blend_State_Spelling,
                    Reflection_Blend_State_Operator::Get_Class_Displaying_Name
                );

                Temp_Class_Base_Class_Tuple = make_shared<Class_Base_Class_Tuple>(
                    Reflection_Blend_State_Operator::Get_Base_Class_Blend_State_Reflection_Instance_List
                );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Blend_Clip_File_Path"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Blend_State_Operator::Get_Field_Blend_Clip_File_Path_Type_Spelling,
                        Reflection_Blend_State_Operator::Get_Field_Blend_Clip_File_Path_Spelling,
                        Reflection_Blend_State_Operator::Get_Field_Blend_Clip_File_Path_Display_Name,
                        Reflection_Blend_State_Operator::Get_Filed_Blend_Clip_File_Path_Attribute,
                        Reflection_Blend_State_Operator::Set_Field_Blend_Clip_File_Path_Attribute,
                        Reflection_Blend_State_Operator::Is_Filed_Blend_Clip_File_Path_CPPVector
                    )
                );

                    Temp_Class_Filed_CPPVector_Func_Tuple_Map->emplace(
                    string{"m_Blend_Clip_File_Path"},
                        make_shared<Class_Filed_CPPVector_Func_Tuple>( 
                            Reflection_Blend_State_Operator::Get_Field_Blend_Clip_File_Path_CPPVector_Element_Type_Spelling,
                            Reflection_Blend_State_Operator::Get_Field_Blend_Clip_File_Path_CPPVector_Capacity,
                            Reflection_Blend_State_Operator::Get_Field_Blend_Clip_File_Path_CPPVector_Size,
                            Reflection_Blend_State_Operator::Get_Field_Blend_Clip_File_Path_CPPVector_Element,
                            Reflection_Blend_State_Operator::Set_Field_Blend_Clip_File_Path_CPPVector_Element
                        )
                    );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Blend_Clip_File_Length"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Blend_State_Operator::Get_Field_Blend_Clip_File_Length_Type_Spelling,
                        Reflection_Blend_State_Operator::Get_Field_Blend_Clip_File_Length_Spelling,
                        Reflection_Blend_State_Operator::Get_Field_Blend_Clip_File_Length_Display_Name,
                        Reflection_Blend_State_Operator::Get_Filed_Blend_Clip_File_Length_Attribute,
                        Reflection_Blend_State_Operator::Set_Field_Blend_Clip_File_Length_Attribute,
                        Reflection_Blend_State_Operator::Is_Filed_Blend_Clip_File_Length_CPPVector
                    )
                );

                    Temp_Class_Filed_CPPVector_Func_Tuple_Map->emplace(
                    string{"m_Blend_Clip_File_Length"},
                        make_shared<Class_Filed_CPPVector_Func_Tuple>( 
                            Reflection_Blend_State_Operator::Get_Field_Blend_Clip_File_Length_CPPVector_Element_Type_Spelling,
                            Reflection_Blend_State_Operator::Get_Field_Blend_Clip_File_Length_CPPVector_Capacity,
                            Reflection_Blend_State_Operator::Get_Field_Blend_Clip_File_Length_CPPVector_Size,
                            Reflection_Blend_State_Operator::Get_Field_Blend_Clip_File_Length_CPPVector_Element,
                            Reflection_Blend_State_Operator::Set_Field_Blend_Clip_File_Length_CPPVector_Element
                        )
                    );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Blend_Skeleton_Map_File_Path"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Blend_State_Operator::Get_Field_Blend_Skeleton_Map_File_Path_Type_Spelling,
                        Reflection_Blend_State_Operator::Get_Field_Blend_Skeleton_Map_File_Path_Spelling,
                        Reflection_Blend_State_Operator::Get_Field_Blend_Skeleton_Map_File_Path_Display_Name,
                        Reflection_Blend_State_Operator::Get_Filed_Blend_Skeleton_Map_File_Path_Attribute,
                        Reflection_Blend_State_Operator::Set_Field_Blend_Skeleton_Map_File_Path_Attribute,
                        Reflection_Blend_State_Operator::Is_Filed_Blend_Skeleton_Map_File_Path_CPPVector
                    )
                );

                    Temp_Class_Filed_CPPVector_Func_Tuple_Map->emplace(
                    string{"m_Blend_Skeleton_Map_File_Path"},
                        make_shared<Class_Filed_CPPVector_Func_Tuple>( 
                            Reflection_Blend_State_Operator::Get_Field_Blend_Skeleton_Map_File_Path_CPPVector_Element_Type_Spelling,
                            Reflection_Blend_State_Operator::Get_Field_Blend_Skeleton_Map_File_Path_CPPVector_Capacity,
                            Reflection_Blend_State_Operator::Get_Field_Blend_Skeleton_Map_File_Path_CPPVector_Size,
                            Reflection_Blend_State_Operator::Get_Field_Blend_Skeleton_Map_File_Path_CPPVector_Element,
                            Reflection_Blend_State_Operator::Set_Field_Blend_Skeleton_Map_File_Path_CPPVector_Element
                        )
                    );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Blend_Weights"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Blend_State_Operator::Get_Field_Blend_Weights_Type_Spelling,
                        Reflection_Blend_State_Operator::Get_Field_Blend_Weights_Spelling,
                        Reflection_Blend_State_Operator::Get_Field_Blend_Weights_Display_Name,
                        Reflection_Blend_State_Operator::Get_Filed_Blend_Weights_Attribute,
                        Reflection_Blend_State_Operator::Set_Field_Blend_Weights_Attribute,
                        Reflection_Blend_State_Operator::Is_Filed_Blend_Weights_CPPVector
                    )
                );

                    Temp_Class_Filed_CPPVector_Func_Tuple_Map->emplace(
                    string{"m_Blend_Weights"},
                        make_shared<Class_Filed_CPPVector_Func_Tuple>( 
                            Reflection_Blend_State_Operator::Get_Field_Blend_Weights_CPPVector_Element_Type_Spelling,
                            Reflection_Blend_State_Operator::Get_Field_Blend_Weights_CPPVector_Capacity,
                            Reflection_Blend_State_Operator::Get_Field_Blend_Weights_CPPVector_Size,
                            Reflection_Blend_State_Operator::Get_Field_Blend_Weights_CPPVector_Element,
                            Reflection_Blend_State_Operator::Set_Field_Blend_Weights_CPPVector_Element
                        )
                    );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Blend_Mask_File_Path"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Blend_State_Operator::Get_Field_Blend_Mask_File_Path_Type_Spelling,
                        Reflection_Blend_State_Operator::Get_Field_Blend_Mask_File_Path_Spelling,
                        Reflection_Blend_State_Operator::Get_Field_Blend_Mask_File_Path_Display_Name,
                        Reflection_Blend_State_Operator::Get_Filed_Blend_Mask_File_Path_Attribute,
                        Reflection_Blend_State_Operator::Set_Field_Blend_Mask_File_Path_Attribute,
                        Reflection_Blend_State_Operator::Is_Filed_Blend_Mask_File_Path_CPPVector
                    )
                );

                    Temp_Class_Filed_CPPVector_Func_Tuple_Map->emplace(
                    string{"m_Blend_Mask_File_Path"},
                        make_shared<Class_Filed_CPPVector_Func_Tuple>( 
                            Reflection_Blend_State_Operator::Get_Field_Blend_Mask_File_Path_CPPVector_Element_Type_Spelling,
                            Reflection_Blend_State_Operator::Get_Field_Blend_Mask_File_Path_CPPVector_Capacity,
                            Reflection_Blend_State_Operator::Get_Field_Blend_Mask_File_Path_CPPVector_Size,
                            Reflection_Blend_State_Operator::Get_Field_Blend_Mask_File_Path_CPPVector_Element,
                            Reflection_Blend_State_Operator::Set_Field_Blend_Mask_File_Path_CPPVector_Element
                        )
                    );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_BlendState"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Blend_State_Operator::Get_Field_BlendState_Type_Spelling,
                        Reflection_Blend_State_Operator::Get_Field_BlendState_Spelling,
                        Reflection_Blend_State_Operator::Get_Field_BlendState_Display_Name,
                        Reflection_Blend_State_Operator::Get_Filed_BlendState_Attribute,
                        Reflection_Blend_State_Operator::Set_Field_BlendState_Attribute,
                        Reflection_Blend_State_Operator::Is_Filed_BlendState_CPPVector
                    )
                );

                    Temp_Class_Filed_CPPVector_Func_Tuple_Map->emplace(
                    string{"m_BlendState"},
                        make_shared<Class_Filed_CPPVector_Func_Tuple>( 
                            Reflection_Blend_State_Operator::Get_Field_BlendState_CPPVector_Element_Type_Spelling,
                            Reflection_Blend_State_Operator::Get_Field_BlendState_CPPVector_Capacity,
                            Reflection_Blend_State_Operator::Get_Field_BlendState_CPPVector_Size,
                            Reflection_Blend_State_Operator::Get_Field_BlendState_CPPVector_Element,
                            Reflection_Blend_State_Operator::Set_Field_BlendState_CPPVector_Element
                        )
                    );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Blend_ratio"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Blend_State_Operator::Get_Field_Blend_ratio_Type_Spelling,
                        Reflection_Blend_State_Operator::Get_Field_Blend_ratio_Spelling,
                        Reflection_Blend_State_Operator::Get_Field_Blend_ratio_Display_Name,
                        Reflection_Blend_State_Operator::Get_Filed_Blend_ratio_Attribute,
                        Reflection_Blend_State_Operator::Set_Field_Blend_ratio_Attribute,
                        Reflection_Blend_State_Operator::Is_Filed_Blend_ratio_CPPVector
                    )
                );

                    Temp_Class_Filed_CPPVector_Func_Tuple_Map->emplace(
                    string{"m_Blend_ratio"},
                        make_shared<Class_Filed_CPPVector_Func_Tuple>( 
                            Reflection_Blend_State_Operator::Get_Field_Blend_ratio_CPPVector_Element_Type_Spelling,
                            Reflection_Blend_State_Operator::Get_Field_Blend_ratio_CPPVector_Capacity,
                            Reflection_Blend_State_Operator::Get_Field_Blend_ratio_CPPVector_Size,
                            Reflection_Blend_State_Operator::Get_Field_Blend_ratio_CPPVector_Element,
                            Reflection_Blend_State_Operator::Set_Field_Blend_ratio_CPPVector_Element
                        )
                    );

                
            Reflection_Register::Get_Instance().Register_Class(string{"Blend_State"},Temp_Class_Func_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Base_Class(string{"Blend_State"},Temp_Class_Base_Class_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Filed(string{"Blend_State"},Temp_Class_Field_Func_Tuple_Map);
            Reflection_Register::Get_Instance().Register_Class_Field_CPPVector(string{"Blend_State"},Temp_Class_Filed_CPPVector_Func_Tuple_Map);
        }

    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection


