#pragma once

#include<string>
#include<vector>
#include<memory>
#include<cstddef>

#include "meta/Reflection/Reflection_Instance.h"
#include "meta/Reflection/Reflection_Register.h"

#include "D:/Amy_Engine/resource/include/components/animation/Animation_Clip.h"

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


    class Reflection_Animation_Node_Map_Operator {
    public:

        static const string Get_Class_Animation_Node_Map_Spelling(void){
            return string{"Animation_Node_Map"};
        }

        static const string Get_Class_Displaying_Name(void){
            return string{"Animation_Node_Map"};            
        }

            static const vector<Reflection_Instance<void>> Get_Base_Class_Animation_Node_Map_Reflection_Instance_List(shared_ptr<void> Instance){
                vector<Reflection_Instance<void>> Table;

                    

                return Table;
            }

            static const string Get_Field_onvert_Type_Spelling(void){
                return string{"vector<string>"};
            }

            static const string Get_Field_onvert_Spelling(void){
                return string{"m_onvert"};
            }


            static const string Get_Field_onvert_Display_Name(void){
                return string{"onvert"};
            }

            static const void *const Get_Filed_onvert_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Animation_Node_Map>(Instance)->m_onvert);
            }

            static void Set_Field_onvert_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Animation_Node_Map>(Instance)->m_onvert=*static_cast<const vector<string>*>(Value);
            }

            static const bool Is_Filed_onvert_CPPVector(void){
                return  !  false;
            }

                static const string Get_Field_onvert_CPPVector_Element_Type_Spelling(void){
                    return string {"m_onvert"};
                }

                static const size_t Get_Field_onvert_CPPVector_Capacity(shared_ptr<void> Instance){
                    return static_pointer_cast<Animation_Node_Map>(Instance)->m_onvert.capacity();
                }

                static const size_t Get_Field_onvert_CPPVector_Size(shared_ptr<void> Instance){
                    return static_pointer_cast<Animation_Node_Map>(Instance)->m_onvert.size();
                }

                static const void *Get_Field_onvert_CPPVector_Element(shared_ptr<void> Instance, size_t Index){
                    return static_cast<const void*>(&static_pointer_cast<Animation_Node_Map>(Instance)->m_onvert[Index]);
                }

                static void Set_Field_onvert_CPPVector_Element(shared_ptr<void> Instance, size_t Index,const void* Value){
                    static_pointer_cast<Animation_Node_Map>(Instance)->m_onvert[Index]=*static_cast<const string*>(Value);
                }


            static void TypeWrapper_Rigster(void){
                shared_ptr<Class_Func_Tuple> Temp_Class_Func_Tuple{nullptr};
                shared_ptr<Class_Base_Class_Tuple> Temp_Class_Base_Class_Tuple{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Field_Func_Tuple>>> Temp_Class_Field_Func_Tuple_Map{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Filed_CPPVector_Func_Tuple>>> Temp_Class_Filed_CPPVector_Func_Tuple_Map{nullptr};

                Temp_Class_Func_Tuple = make_shared<Class_Func_Tuple>(
                    Reflection_Animation_Node_Map_Operator::Get_Class_Animation_Node_Map_Spelling,
                    Reflection_Animation_Node_Map_Operator::Get_Class_Displaying_Name
                );

                Temp_Class_Base_Class_Tuple = make_shared<Class_Base_Class_Tuple>(
                    Reflection_Animation_Node_Map_Operator::Get_Base_Class_Animation_Node_Map_Reflection_Instance_List
                );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_onvert"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Animation_Node_Map_Operator::Get_Field_onvert_Type_Spelling,
                        Reflection_Animation_Node_Map_Operator::Get_Field_onvert_Spelling,
                        Reflection_Animation_Node_Map_Operator::Get_Field_onvert_Display_Name,
                        Reflection_Animation_Node_Map_Operator::Get_Filed_onvert_Attribute,
                        Reflection_Animation_Node_Map_Operator::Set_Field_onvert_Attribute,
                        Reflection_Animation_Node_Map_Operator::Is_Filed_onvert_CPPVector
                    )
                );

                    Temp_Class_Filed_CPPVector_Func_Tuple_Map->emplace(
                    string{"m_onvert"},
                        make_shared<Class_Filed_CPPVector_Func_Tuple>( 
                            Reflection_Animation_Node_Map_Operator::Get_Field_onvert_CPPVector_Element_Type_Spelling,
                            Reflection_Animation_Node_Map_Operator::Get_Field_onvert_CPPVector_Capacity,
                            Reflection_Animation_Node_Map_Operator::Get_Field_onvert_CPPVector_Size,
                            Reflection_Animation_Node_Map_Operator::Get_Field_onvert_CPPVector_Element,
                            Reflection_Animation_Node_Map_Operator::Set_Field_onvert_CPPVector_Element
                        )
                    );

                
            Reflection_Register::Get_Instance().Register_Class(string{"Animation_Node_Map"},Temp_Class_Func_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Base_Class(string{"Animation_Node_Map"},Temp_Class_Base_Class_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Filed(string{"Animation_Node_Map"},Temp_Class_Field_Func_Tuple_Map);
            Reflection_Register::Get_Instance().Register_Class_Field_CPPVector(string{"Animation_Node_Map"},Temp_Class_Filed_CPPVector_Func_Tuple_Map);
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


    class Reflection_Animation_Channel_Operator {
    public:

        static const string Get_Class_Animation_Channel_Spelling(void){
            return string{"Animation_Channel"};
        }

        static const string Get_Class_Displaying_Name(void){
            return string{"Animation_Channel"};            
        }

            static const vector<Reflection_Instance<void>> Get_Base_Class_Animation_Channel_Reflection_Instance_List(shared_ptr<void> Instance){
                vector<Reflection_Instance<void>> Table;

                    

                return Table;
            }

            static const string Get_Field_Transform_Type_Spelling(void){
                return string{"Affine_Transform"};
            }

            static const string Get_Field_Transform_Spelling(void){
                return string{"m_Transform"};
            }


            static const string Get_Field_Transform_Display_Name(void){
                return string{"Transform"};
            }

            static const void *const Get_Filed_Transform_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Animation_Channel>(Instance)->m_Transform);
            }

            static void Set_Field_Transform_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Animation_Channel>(Instance)->m_Transform=*static_cast<const Affine_Transform*>(Value);
            }

            static const bool Is_Filed_Transform_CPPVector(void){
                return  false;
            }

                static const string Get_Field_Transform_CPPVector_Element_Type_Spelling(void){
                    return string {"m_Transform"};
                }

                static const size_t Get_Field_Transform_CPPVector_Capacity(shared_ptr<void> Instance){
                    return static_pointer_cast<Animation_Channel>(Instance)->m_Transform.capacity();
                }

                static const size_t Get_Field_Transform_CPPVector_Size(shared_ptr<void> Instance){
                    return static_pointer_cast<Animation_Channel>(Instance)->m_Transform.size();
                }

                static const void *Get_Field_Transform_CPPVector_Element(shared_ptr<void> Instance, size_t Index){
                    return static_cast<const void*>(&static_pointer_cast<Animation_Channel>(Instance)->m_Transform[Index]);
                }

                static void Set_Field_Transform_CPPVector_Element(shared_ptr<void> Instance, size_t Index,const void* Value){
                    static_pointer_cast<Animation_Channel>(Instance)->m_Transform[Index]=*static_cast<const float*>(Value);
                }


            static void TypeWrapper_Rigster(void){
                shared_ptr<Class_Func_Tuple> Temp_Class_Func_Tuple{nullptr};
                shared_ptr<Class_Base_Class_Tuple> Temp_Class_Base_Class_Tuple{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Field_Func_Tuple>>> Temp_Class_Field_Func_Tuple_Map{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Filed_CPPVector_Func_Tuple>>> Temp_Class_Filed_CPPVector_Func_Tuple_Map{nullptr};

                Temp_Class_Func_Tuple = make_shared<Class_Func_Tuple>(
                    Reflection_Animation_Channel_Operator::Get_Class_Animation_Channel_Spelling,
                    Reflection_Animation_Channel_Operator::Get_Class_Displaying_Name
                );

                Temp_Class_Base_Class_Tuple = make_shared<Class_Base_Class_Tuple>(
                    Reflection_Animation_Channel_Operator::Get_Base_Class_Animation_Channel_Reflection_Instance_List
                );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Transform"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Animation_Channel_Operator::Get_Field_Transform_Type_Spelling,
                        Reflection_Animation_Channel_Operator::Get_Field_Transform_Spelling,
                        Reflection_Animation_Channel_Operator::Get_Field_Transform_Display_Name,
                        Reflection_Animation_Channel_Operator::Get_Filed_Transform_Attribute,
                        Reflection_Animation_Channel_Operator::Set_Field_Transform_Attribute,
                        Reflection_Animation_Channel_Operator::Is_Filed_Transform_CPPVector
                    )
                );

                    Temp_Class_Filed_CPPVector_Func_Tuple_Map->emplace(
                    string{"m_Transform"},
                        make_shared<Class_Filed_CPPVector_Func_Tuple>( 
                            Reflection_Animation_Channel_Operator::Get_Field_Transform_CPPVector_Element_Type_Spelling,
                            Reflection_Animation_Channel_Operator::Get_Field_Transform_CPPVector_Capacity,
                            Reflection_Animation_Channel_Operator::Get_Field_Transform_CPPVector_Size,
                            Reflection_Animation_Channel_Operator::Get_Field_Transform_CPPVector_Element,
                            Reflection_Animation_Channel_Operator::Set_Field_Transform_CPPVector_Element
                        )
                    );

                
            Reflection_Register::Get_Instance().Register_Class(string{"Animation_Channel"},Temp_Class_Func_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Base_Class(string{"Animation_Channel"},Temp_Class_Base_Class_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Filed(string{"Animation_Channel"},Temp_Class_Field_Func_Tuple_Map);
            Reflection_Register::Get_Instance().Register_Class_Field_CPPVector(string{"Animation_Channel"},Temp_Class_Filed_CPPVector_Func_Tuple_Map);
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


    class Reflection_Animation_Clip_Operator {
    public:

        static const string Get_Class_Animation_Clip_Spelling(void){
            return string{"Animation_Clip"};
        }

        static const string Get_Class_Displaying_Name(void){
            return string{"Animation_Clip"};            
        }

            static const vector<Reflection_Instance<void>> Get_Base_Class_Animation_Clip_Reflection_Instance_List(shared_ptr<void> Instance){
                vector<Reflection_Instance<void>> Table;

                    

                return Table;
            }

            static const string Get_Field_Node_Channels_Type_Spelling(void){
                return string{"vector<Animation_Channel>"};
            }

            static const string Get_Field_Node_Channels_Spelling(void){
                return string{"m_Node_Channels"};
            }


            static const string Get_Field_Node_Channels_Display_Name(void){
                return string{"Node_Channels"};
            }

            static const void *const Get_Filed_Node_Channels_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Animation_Clip>(Instance)->m_Node_Channels);
            }

            static void Set_Field_Node_Channels_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Animation_Clip>(Instance)->m_Node_Channels=*static_cast<const vector<Animation_Channel>*>(Value);
            }

            static const bool Is_Filed_Node_Channels_CPPVector(void){
                return  !  false;
            }

                static const string Get_Field_Node_Channels_CPPVector_Element_Type_Spelling(void){
                    return string {"m_Node_Channels"};
                }

                static const size_t Get_Field_Node_Channels_CPPVector_Capacity(shared_ptr<void> Instance){
                    return static_pointer_cast<Animation_Clip>(Instance)->m_Node_Channels.capacity();
                }

                static const size_t Get_Field_Node_Channels_CPPVector_Size(shared_ptr<void> Instance){
                    return static_pointer_cast<Animation_Clip>(Instance)->m_Node_Channels.size();
                }

                static const void *Get_Field_Node_Channels_CPPVector_Element(shared_ptr<void> Instance, size_t Index){
                    return static_cast<const void*>(&static_pointer_cast<Animation_Clip>(Instance)->m_Node_Channels[Index]);
                }

                static void Set_Field_Node_Channels_CPPVector_Element(shared_ptr<void> Instance, size_t Index,const void* Value){
                    static_pointer_cast<Animation_Clip>(Instance)->m_Node_Channels[Index]=*static_cast<const Animation_Channel*>(Value);
                }


            static void TypeWrapper_Rigster(void){
                shared_ptr<Class_Func_Tuple> Temp_Class_Func_Tuple{nullptr};
                shared_ptr<Class_Base_Class_Tuple> Temp_Class_Base_Class_Tuple{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Field_Func_Tuple>>> Temp_Class_Field_Func_Tuple_Map{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Filed_CPPVector_Func_Tuple>>> Temp_Class_Filed_CPPVector_Func_Tuple_Map{nullptr};

                Temp_Class_Func_Tuple = make_shared<Class_Func_Tuple>(
                    Reflection_Animation_Clip_Operator::Get_Class_Animation_Clip_Spelling,
                    Reflection_Animation_Clip_Operator::Get_Class_Displaying_Name
                );

                Temp_Class_Base_Class_Tuple = make_shared<Class_Base_Class_Tuple>(
                    Reflection_Animation_Clip_Operator::Get_Base_Class_Animation_Clip_Reflection_Instance_List
                );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Node_Channels"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Animation_Clip_Operator::Get_Field_Node_Channels_Type_Spelling,
                        Reflection_Animation_Clip_Operator::Get_Field_Node_Channels_Spelling,
                        Reflection_Animation_Clip_Operator::Get_Field_Node_Channels_Display_Name,
                        Reflection_Animation_Clip_Operator::Get_Filed_Node_Channels_Attribute,
                        Reflection_Animation_Clip_Operator::Set_Field_Node_Channels_Attribute,
                        Reflection_Animation_Clip_Operator::Is_Filed_Node_Channels_CPPVector
                    )
                );

                    Temp_Class_Filed_CPPVector_Func_Tuple_Map->emplace(
                    string{"m_Node_Channels"},
                        make_shared<Class_Filed_CPPVector_Func_Tuple>( 
                            Reflection_Animation_Clip_Operator::Get_Field_Node_Channels_CPPVector_Element_Type_Spelling,
                            Reflection_Animation_Clip_Operator::Get_Field_Node_Channels_CPPVector_Capacity,
                            Reflection_Animation_Clip_Operator::Get_Field_Node_Channels_CPPVector_Size,
                            Reflection_Animation_Clip_Operator::Get_Field_Node_Channels_CPPVector_Element,
                            Reflection_Animation_Clip_Operator::Set_Field_Node_Channels_CPPVector_Element
                        )
                    );

                
            Reflection_Register::Get_Instance().Register_Class(string{"Animation_Clip"},Temp_Class_Func_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Base_Class(string{"Animation_Clip"},Temp_Class_Base_Class_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Filed(string{"Animation_Clip"},Temp_Class_Field_Func_Tuple_Map);
            Reflection_Register::Get_Instance().Register_Class_Field_CPPVector(string{"Animation_Clip"},Temp_Class_Filed_CPPVector_Func_Tuple_Map);
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


    class Reflection_Animation_Data_Operator {
    public:

        static const string Get_Class_Animation_Data_Spelling(void){
            return string{"Animation_Data"};
        }

        static const string Get_Class_Displaying_Name(void){
            return string{"Animation_Data"};            
        }

            static const vector<Reflection_Instance<void>> Get_Base_Class_Animation_Data_Reflection_Instance_List(shared_ptr<void> Instance){
                vector<Reflection_Instance<void>> Table;

                    

                return Table;
            }

            static const string Get_Field_Clips_Type_Spelling(void){
                return string{"vector<Animation_Clip>"};
            }

            static const string Get_Field_Clips_Spelling(void){
                return string{"m_Clips"};
            }


            static const string Get_Field_Clips_Display_Name(void){
                return string{"Clips"};
            }

            static const void *const Get_Filed_Clips_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Animation_Data>(Instance)->m_Clips);
            }

            static void Set_Field_Clips_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Animation_Data>(Instance)->m_Clips=*static_cast<const vector<Animation_Clip>*>(Value);
            }

            static const bool Is_Filed_Clips_CPPVector(void){
                return  !  false;
            }

                static const string Get_Field_Clips_CPPVector_Element_Type_Spelling(void){
                    return string {"m_Clips"};
                }

                static const size_t Get_Field_Clips_CPPVector_Capacity(shared_ptr<void> Instance){
                    return static_pointer_cast<Animation_Data>(Instance)->m_Clips.capacity();
                }

                static const size_t Get_Field_Clips_CPPVector_Size(shared_ptr<void> Instance){
                    return static_pointer_cast<Animation_Data>(Instance)->m_Clips.size();
                }

                static const void *Get_Field_Clips_CPPVector_Element(shared_ptr<void> Instance, size_t Index){
                    return static_cast<const void*>(&static_pointer_cast<Animation_Data>(Instance)->m_Clips[Index]);
                }

                static void Set_Field_Clips_CPPVector_Element(shared_ptr<void> Instance, size_t Index,const void* Value){
                    static_pointer_cast<Animation_Data>(Instance)->m_Clips[Index]=*static_cast<const Animation_Clip*>(Value);
                }


            static void TypeWrapper_Rigster(void){
                shared_ptr<Class_Func_Tuple> Temp_Class_Func_Tuple{nullptr};
                shared_ptr<Class_Base_Class_Tuple> Temp_Class_Base_Class_Tuple{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Field_Func_Tuple>>> Temp_Class_Field_Func_Tuple_Map{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Filed_CPPVector_Func_Tuple>>> Temp_Class_Filed_CPPVector_Func_Tuple_Map{nullptr};

                Temp_Class_Func_Tuple = make_shared<Class_Func_Tuple>(
                    Reflection_Animation_Data_Operator::Get_Class_Animation_Data_Spelling,
                    Reflection_Animation_Data_Operator::Get_Class_Displaying_Name
                );

                Temp_Class_Base_Class_Tuple = make_shared<Class_Base_Class_Tuple>(
                    Reflection_Animation_Data_Operator::Get_Base_Class_Animation_Data_Reflection_Instance_List
                );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Clips"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Animation_Data_Operator::Get_Field_Clips_Type_Spelling,
                        Reflection_Animation_Data_Operator::Get_Field_Clips_Spelling,
                        Reflection_Animation_Data_Operator::Get_Field_Clips_Display_Name,
                        Reflection_Animation_Data_Operator::Get_Filed_Clips_Attribute,
                        Reflection_Animation_Data_Operator::Set_Field_Clips_Attribute,
                        Reflection_Animation_Data_Operator::Is_Filed_Clips_CPPVector
                    )
                );

                    Temp_Class_Filed_CPPVector_Func_Tuple_Map->emplace(
                    string{"m_Clips"},
                        make_shared<Class_Filed_CPPVector_Func_Tuple>( 
                            Reflection_Animation_Data_Operator::Get_Field_Clips_CPPVector_Element_Type_Spelling,
                            Reflection_Animation_Data_Operator::Get_Field_Clips_CPPVector_Capacity,
                            Reflection_Animation_Data_Operator::Get_Field_Clips_CPPVector_Size,
                            Reflection_Animation_Data_Operator::Get_Field_Clips_CPPVector_Element,
                            Reflection_Animation_Data_Operator::Set_Field_Clips_CPPVector_Element
                        )
                    );

                
            Reflection_Register::Get_Instance().Register_Class(string{"Animation_Data"},Temp_Class_Func_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Base_Class(string{"Animation_Data"},Temp_Class_Base_Class_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Filed(string{"Animation_Data"},Temp_Class_Field_Func_Tuple_Map);
            Reflection_Register::Get_Instance().Register_Class_Field_CPPVector(string{"Animation_Data"},Temp_Class_Filed_CPPVector_Func_Tuple_Map);
        }

    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection


