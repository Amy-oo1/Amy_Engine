#pragma once

#include<string>
#include<vector>
#include<memory>
#include<cstddef>

#include "meta/Reflection/Reflection_Instance.h"
#include "meta/Reflection/Reflection_Register.h"

#include "D:/Amy_Engine/resource/include/components/animation/Animation.h"

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


    class Reflection_Animation_Effect_Element_Operator {
    public:

        static const string Get_Class_Animation_Effect_Element_Spelling(void){
            return string{"Animation_Effect_Element"};
        }

        static const string Get_Class_Displaying_Name(void){
            return string{"Animation_Effect_Element"};            
        }

            static const vector<Reflection_Instance<void>> Get_Base_Class_Animation_Effect_Element_Reflection_Instance_List(shared_ptr<void> Instance){
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
                return static_cast<void*>(&static_pointer_cast<Animation_Effect_Element>(Instance)->m_Transform);
            }

            static void Set_Field_Transform_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Animation_Effect_Element>(Instance)->m_Transform=*static_cast<const Affine_Transform*>(Value);
            }

            static const bool Is_Filed_Transform_CPPVector(void){
                return  false;
            }

            


            static void TypeWrapper_Rigster(void){
                shared_ptr<Class_Func_Tuple> Temp_Class_Func_Tuple{nullptr};
                shared_ptr<Class_Base_Class_Tuple> Temp_Class_Base_Class_Tuple{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Field_Func_Tuple>>> Temp_Class_Field_Func_Tuple_Map{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Filed_CPPVector_Func_Tuple>>> Temp_Class_Filed_CPPVector_Func_Tuple_Map{nullptr};

                Temp_Class_Func_Tuple = make_shared<Class_Func_Tuple>(
                    Reflection_Animation_Effect_Element_Operator::Get_Class_Animation_Effect_Element_Spelling,
                    Reflection_Animation_Effect_Element_Operator::Get_Class_Displaying_Name
                );

                Temp_Class_Base_Class_Tuple = make_shared<Class_Base_Class_Tuple>(
                    Reflection_Animation_Effect_Element_Operator::Get_Base_Class_Animation_Effect_Element_Reflection_Instance_List
                );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Transform"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Animation_Effect_Element_Operator::Get_Field_Transform_Type_Spelling,
                        Reflection_Animation_Effect_Element_Operator::Get_Field_Transform_Spelling,
                        Reflection_Animation_Effect_Element_Operator::Get_Field_Transform_Display_Name,
                        Reflection_Animation_Effect_Element_Operator::Get_Filed_Transform_Attribute,
                        Reflection_Animation_Effect_Element_Operator::Set_Field_Transform_Attribute,
                        Reflection_Animation_Effect_Element_Operator::Is_Filed_Transform_CPPVector
                    )
                );

                

                
            Reflection_Register::Get_Instance().Register_Class(string{"Animation_Effect_Element"},Temp_Class_Func_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Base_Class(string{"Animation_Effect_Element"},Temp_Class_Base_Class_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Filed(string{"Animation_Effect_Element"},Temp_Class_Field_Func_Tuple_Map);
            Reflection_Register::Get_Instance().Register_Class_Field_CPPVector(string{"Animation_Effect_Element"},Temp_Class_Filed_CPPVector_Func_Tuple_Map);
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


    class Reflection_Animation_Effect_Operator {
    public:

        static const string Get_Class_Animation_Effect_Spelling(void){
            return string{"Animation_Effect"};
        }

        static const string Get_Class_Displaying_Name(void){
            return string{"Animation_Effect"};            
        }

            static const vector<Reflection_Instance<void>> Get_Base_Class_Animation_Effect_Reflection_Instance_List(shared_ptr<void> Instance){
                vector<Reflection_Instance<void>> Table;

                    

                return Table;
            }

            static const string Get_Field_Effects_Type_Spelling(void){
                return string{"vector<Animation_Effect_Element>"};
            }

            static const string Get_Field_Effects_Spelling(void){
                return string{"m_Effects"};
            }


            static const string Get_Field_Effects_Display_Name(void){
                return string{"Effects"};
            }

            static const void *const Get_Filed_Effects_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Animation_Effect>(Instance)->m_Effects);
            }

            static void Set_Field_Effects_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Animation_Effect>(Instance)->m_Effects=*static_cast<const vector<Animation_Effect_Element>*>(Value);
            }

            static const bool Is_Filed_Effects_CPPVector(void){
                return  !  false;
            }

                static const string Get_Field_Effects_CPPVector_Element_Type_Spelling(void){
                    return string {"m_Effects"};
                }

                static const size_t Get_Field_Effects_CPPVector_Capacity(shared_ptr<void> Instance){
                    return static_pointer_cast<Animation_Effect>(Instance)->m_Effects.capacity();
                }

                static const size_t Get_Field_Effects_CPPVector_Size(shared_ptr<void> Instance){
                    return static_pointer_cast<Animation_Effect>(Instance)->m_Effects.size();
                }

                static const void *Get_Field_Effects_CPPVector_Element(shared_ptr<void> Instance, size_t Index){
                    return static_cast<const void*>(&static_pointer_cast<Animation_Effect>(Instance)->m_Effects[Index]);
                }

                static void Set_Field_Effects_CPPVector_Element(shared_ptr<void> Instance, size_t Index,const void* Value){
                    static_pointer_cast<Animation_Effect>(Instance)->m_Effects[Index]=*static_cast<const Animation_Effect_Element*>(Value);
                }


            static void TypeWrapper_Rigster(void){
                shared_ptr<Class_Func_Tuple> Temp_Class_Func_Tuple{nullptr};
                shared_ptr<Class_Base_Class_Tuple> Temp_Class_Base_Class_Tuple{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Field_Func_Tuple>>> Temp_Class_Field_Func_Tuple_Map{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Filed_CPPVector_Func_Tuple>>> Temp_Class_Filed_CPPVector_Func_Tuple_Map{nullptr};

                Temp_Class_Func_Tuple = make_shared<Class_Func_Tuple>(
                    Reflection_Animation_Effect_Operator::Get_Class_Animation_Effect_Spelling,
                    Reflection_Animation_Effect_Operator::Get_Class_Displaying_Name
                );

                Temp_Class_Base_Class_Tuple = make_shared<Class_Base_Class_Tuple>(
                    Reflection_Animation_Effect_Operator::Get_Base_Class_Animation_Effect_Reflection_Instance_List
                );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Effects"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Animation_Effect_Operator::Get_Field_Effects_Type_Spelling,
                        Reflection_Animation_Effect_Operator::Get_Field_Effects_Spelling,
                        Reflection_Animation_Effect_Operator::Get_Field_Effects_Display_Name,
                        Reflection_Animation_Effect_Operator::Get_Filed_Effects_Attribute,
                        Reflection_Animation_Effect_Operator::Set_Field_Effects_Attribute,
                        Reflection_Animation_Effect_Operator::Is_Filed_Effects_CPPVector
                    )
                );

                    Temp_Class_Filed_CPPVector_Func_Tuple_Map->emplace(
                    string{"m_Effects"},
                        make_shared<Class_Filed_CPPVector_Func_Tuple>( 
                            Reflection_Animation_Effect_Operator::Get_Field_Effects_CPPVector_Element_Type_Spelling,
                            Reflection_Animation_Effect_Operator::Get_Field_Effects_CPPVector_Capacity,
                            Reflection_Animation_Effect_Operator::Get_Field_Effects_CPPVector_Size,
                            Reflection_Animation_Effect_Operator::Get_Field_Effects_CPPVector_Element,
                            Reflection_Animation_Effect_Operator::Set_Field_Effects_CPPVector_Element
                        )
                    );

                
            Reflection_Register::Get_Instance().Register_Class(string{"Animation_Effect"},Temp_Class_Func_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Base_Class(string{"Animation_Effect"},Temp_Class_Base_Class_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Filed(string{"Animation_Effect"},Temp_Class_Field_Func_Tuple_Map);
            Reflection_Register::Get_Instance().Register_Class_Field_CPPVector(string{"Animation_Effect"},Temp_Class_Filed_CPPVector_Func_Tuple_Map);
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


    class Reflection_Animation_Operator {
    public:

        static const string Get_Class_Animation_Spelling(void){
            return string{"Animation"};
        }

        static const string Get_Class_Displaying_Name(void){
            return string{"Animation"};            
        }

            static const vector<Reflection_Instance<void>> Get_Base_Class_Animation_Reflection_Instance_List(shared_ptr<void> Instance){
                vector<Reflection_Instance<void>> Table;

                    

                return Table;
            }

            static const string Get_Field_Effect_Type_Spelling(void){
                return string{"Animation_Effect"};
            }

            static const string Get_Field_Effect_Spelling(void){
                return string{"m_Effect"};
            }


            static const string Get_Field_Effect_Display_Name(void){
                return string{"Effect"};
            }

            static const void *const Get_Filed_Effect_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Animation>(Instance)->m_Effect);
            }

            static void Set_Field_Effect_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Animation>(Instance)->m_Effect=*static_cast<const Animation_Effect*>(Value);
            }

            static const bool Is_Filed_Effect_CPPVector(void){
                return  false;
            }

            


            static void TypeWrapper_Rigster(void){
                shared_ptr<Class_Func_Tuple> Temp_Class_Func_Tuple{nullptr};
                shared_ptr<Class_Base_Class_Tuple> Temp_Class_Base_Class_Tuple{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Field_Func_Tuple>>> Temp_Class_Field_Func_Tuple_Map{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Filed_CPPVector_Func_Tuple>>> Temp_Class_Filed_CPPVector_Func_Tuple_Map{nullptr};

                Temp_Class_Func_Tuple = make_shared<Class_Func_Tuple>(
                    Reflection_Animation_Operator::Get_Class_Animation_Spelling,
                    Reflection_Animation_Operator::Get_Class_Displaying_Name
                );

                Temp_Class_Base_Class_Tuple = make_shared<Class_Base_Class_Tuple>(
                    Reflection_Animation_Operator::Get_Base_Class_Animation_Reflection_Instance_List
                );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Effect"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Animation_Operator::Get_Field_Effect_Type_Spelling,
                        Reflection_Animation_Operator::Get_Field_Effect_Spelling,
                        Reflection_Animation_Operator::Get_Field_Effect_Display_Name,
                        Reflection_Animation_Operator::Get_Filed_Effect_Attribute,
                        Reflection_Animation_Operator::Set_Field_Effect_Attribute,
                        Reflection_Animation_Operator::Is_Filed_Effect_CPPVector
                    )
                );

                

                
            Reflection_Register::Get_Instance().Register_Class(string{"Animation"},Temp_Class_Func_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Base_Class(string{"Animation"},Temp_Class_Base_Class_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Filed(string{"Animation"},Temp_Class_Field_Func_Tuple_Map);
            Reflection_Register::Get_Instance().Register_Class_Field_CPPVector(string{"Animation"},Temp_Class_Filed_CPPVector_Func_Tuple_Map);
        }

    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection


