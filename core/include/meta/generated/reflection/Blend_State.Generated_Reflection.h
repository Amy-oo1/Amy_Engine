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


