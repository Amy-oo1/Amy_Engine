#pragma once

#include<string>
#include<vector>
#include<memory>
#include<cstddef>

#include "meta/Reflection/Reflection_Instance.h"
#include "meta/Reflection/Reflection_Register.h"

#include "D:/Amy_Engine/resource/include/components/rigid_body/Rigid_Body.h"

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


    class Reflection_Rigid_Body_Shape_Operator {
    public:

        static const string Get_Class_Rigid_Body_Shape_Spelling(void){
            return string{"Rigid_Body_Shape"};
        }

        static const string Get_Class_Displaying_Name(void){
            return string{"Rigid_Body_Shape"};            
        }

            static const vector<Reflection_Instance<void>> Get_Base_Class_Rigid_Body_Shape_Reflection_Instance_List(shared_ptr<void> Instance){
                vector<Reflection_Instance<void>> Table;

                    

                return Table;
            }

            static const string Get_Field_Instance_Type_Spelling(void){
                return string{"Reflection_Instance<Geometry_Base>"};
            }

            static const string Get_Field_Instance_Spelling(void){
                return string{"m_Instance"};
            }


            static const string Get_Field_Instance_Display_Name(void){
                return string{"Instance"};
            }

            static const void *const Get_Filed_Instance_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Rigid_Body_Shape>(Instance)->m_Instance);
            }

            static void Set_Field_Instance_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Rigid_Body_Shape>(Instance)->m_Instance=*static_cast<const Reflection_Instance<Geometry_Base>*>(Value);
            }

            static const bool Is_Filed_Instance_CPPVector(void){
                return  false;
            }

            


            static void TypeWrapper_Rigster(void){
                shared_ptr<Class_Func_Tuple> Temp_Class_Func_Tuple{nullptr};
                shared_ptr<Class_Base_Class_Tuple> Temp_Class_Base_Class_Tuple{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Field_Func_Tuple>>> Temp_Class_Field_Func_Tuple_Map{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Filed_CPPVector_Func_Tuple>>> Temp_Class_Filed_CPPVector_Func_Tuple_Map{nullptr};

                Temp_Class_Func_Tuple = make_shared<Class_Func_Tuple>(
                    Reflection_Rigid_Body_Shape_Operator::Get_Class_Rigid_Body_Shape_Spelling,
                    Reflection_Rigid_Body_Shape_Operator::Get_Class_Displaying_Name
                );

                Temp_Class_Base_Class_Tuple = make_shared<Class_Base_Class_Tuple>(
                    Reflection_Rigid_Body_Shape_Operator::Get_Base_Class_Rigid_Body_Shape_Reflection_Instance_List
                );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Instance"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Rigid_Body_Shape_Operator::Get_Field_Instance_Type_Spelling,
                        Reflection_Rigid_Body_Shape_Operator::Get_Field_Instance_Spelling,
                        Reflection_Rigid_Body_Shape_Operator::Get_Field_Instance_Display_Name,
                        Reflection_Rigid_Body_Shape_Operator::Get_Filed_Instance_Attribute,
                        Reflection_Rigid_Body_Shape_Operator::Set_Field_Instance_Attribute,
                        Reflection_Rigid_Body_Shape_Operator::Is_Filed_Instance_CPPVector
                    )
                );

                

                
            Reflection_Register::Get_Instance().Register_Class(string{"Rigid_Body_Shape"},Temp_Class_Func_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Base_Class(string{"Rigid_Body_Shape"},Temp_Class_Base_Class_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Filed(string{"Rigid_Body_Shape"},Temp_Class_Field_Func_Tuple_Map);
            Reflection_Register::Get_Instance().Register_Class_Field_CPPVector(string{"Rigid_Body_Shape"},Temp_Class_Filed_CPPVector_Func_Tuple_Map);
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


    class Reflection_Rigid_Body_Operator {
    public:

        static const string Get_Class_Rigid_Body_Spelling(void){
            return string{"Rigid_Body"};
        }

        static const string Get_Class_Displaying_Name(void){
            return string{"Rigid_Body"};            
        }

            static const vector<Reflection_Instance<void>> Get_Base_Class_Rigid_Body_Reflection_Instance_List(shared_ptr<void> Instance){
                vector<Reflection_Instance<void>> Table;

                    

                return Table;
            }

            static const string Get_Field_Actor_Type_Type_Spelling(void){
                return string{"int"};
            }

            static const string Get_Field_Actor_Type_Spelling(void){
                return string{"m_Actor_Type"};
            }


            static const string Get_Field_Actor_Type_Display_Name(void){
                return string{"Actor_Type"};
            }

            static const void *const Get_Filed_Actor_Type_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Rigid_Body>(Instance)->m_Actor_Type);
            }

            static void Set_Field_Actor_Type_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Rigid_Body>(Instance)->m_Actor_Type=*static_cast<const int*>(Value);
            }

            static const bool Is_Filed_Actor_Type_CPPVector(void){
                return  false;
            }

                static const string Get_Field_Actor_Type_CPPVector_Element_Type_Spelling(void){
                    return string {"m_Actor_Type"};
                }

                static const size_t Get_Field_Actor_Type_CPPVector_Capacity(shared_ptr<void> Instance){
                    return static_pointer_cast<Rigid_Body>(Instance)->m_Actor_Type.capacity();
                }

                static const size_t Get_Field_Actor_Type_CPPVector_Size(shared_ptr<void> Instance){
                    return static_pointer_cast<Rigid_Body>(Instance)->m_Actor_Type.size();
                }

                static const void *Get_Field_Actor_Type_CPPVector_Element(shared_ptr<void> Instance, size_t Index){
                    return static_cast<const void*>(&static_pointer_cast<Rigid_Body>(Instance)->m_Actor_Type[Index]);
                }

                static void Set_Field_Actor_Type_CPPVector_Element(shared_ptr<void> Instance, size_t Index,const void* Value){
                    static_pointer_cast<Rigid_Body>(Instance)->m_Actor_Type[Index]=*static_cast<const Rigid_Body_Shape*>(Value);
                }


            static void TypeWrapper_Rigster(void){
                shared_ptr<Class_Func_Tuple> Temp_Class_Func_Tuple{nullptr};
                shared_ptr<Class_Base_Class_Tuple> Temp_Class_Base_Class_Tuple{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Field_Func_Tuple>>> Temp_Class_Field_Func_Tuple_Map{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Filed_CPPVector_Func_Tuple>>> Temp_Class_Filed_CPPVector_Func_Tuple_Map{nullptr};

                Temp_Class_Func_Tuple = make_shared<Class_Func_Tuple>(
                    Reflection_Rigid_Body_Operator::Get_Class_Rigid_Body_Spelling,
                    Reflection_Rigid_Body_Operator::Get_Class_Displaying_Name
                );

                Temp_Class_Base_Class_Tuple = make_shared<Class_Base_Class_Tuple>(
                    Reflection_Rigid_Body_Operator::Get_Base_Class_Rigid_Body_Reflection_Instance_List
                );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Actor_Type"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Rigid_Body_Operator::Get_Field_Actor_Type_Type_Spelling,
                        Reflection_Rigid_Body_Operator::Get_Field_Actor_Type_Spelling,
                        Reflection_Rigid_Body_Operator::Get_Field_Actor_Type_Display_Name,
                        Reflection_Rigid_Body_Operator::Get_Filed_Actor_Type_Attribute,
                        Reflection_Rigid_Body_Operator::Set_Field_Actor_Type_Attribute,
                        Reflection_Rigid_Body_Operator::Is_Filed_Actor_Type_CPPVector
                    )
                );

                    Temp_Class_Filed_CPPVector_Func_Tuple_Map->emplace(
                    string{"m_Actor_Type"},
                        make_shared<Class_Filed_CPPVector_Func_Tuple>( 
                            Reflection_Rigid_Body_Operator::Get_Field_Actor_Type_CPPVector_Element_Type_Spelling,
                            Reflection_Rigid_Body_Operator::Get_Field_Actor_Type_CPPVector_Capacity,
                            Reflection_Rigid_Body_Operator::Get_Field_Actor_Type_CPPVector_Size,
                            Reflection_Rigid_Body_Operator::Get_Field_Actor_Type_CPPVector_Element,
                            Reflection_Rigid_Body_Operator::Set_Field_Actor_Type_CPPVector_Element
                        )
                    );

                
            Reflection_Register::Get_Instance().Register_Class(string{"Rigid_Body"},Temp_Class_Func_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Base_Class(string{"Rigid_Body"},Temp_Class_Base_Class_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Filed(string{"Rigid_Body"},Temp_Class_Field_Func_Tuple_Map);
            Reflection_Register::Get_Instance().Register_Class_Field_CPPVector(string{"Rigid_Body"},Temp_Class_Filed_CPPVector_Func_Tuple_Map);
        }

    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection


