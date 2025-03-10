#pragma once

#include<string>
#include<vector>
#include<memory>
#include<cstddef>

#include "meta/Reflection/Reflection_Instance.h"
#include "meta/Reflection/Reflection_Register.h"

#include "D:/Amy_Engine/resource/include/common/World.h"

namespace NameSpace_Resource::NameSpace_Common{

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


    class Reflection_World_Operator {
    public:

        static const string Get_Class_World_Spelling(void){
            return string{"World"};
        }

        static const string Get_Class_Displaying_Name(void){
            return string{"World"};            
        }

            static const vector<Reflection_Instance<void>> Get_Base_Class_World_Reflection_Instance_List(shared_ptr<void> Instance){
                vector<Reflection_Instance<void>> Table;

                    

                return Table;
            }

            static const string Get_Field_Levels_URL_Type_Spelling(void){
                return string{"vector<path>"};
            }

            static const string Get_Field_Levels_URL_Spelling(void){
                return string{"m_Levels_URL"};
            }


            static const string Get_Field_Levels_URL_Display_Name(void){
                return string{"Levels_URL"};
            }

            static const void *const Get_Filed_Levels_URL_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<World>(Instance)->m_Levels_URL);
            }

            static void Set_Field_Levels_URL_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<World>(Instance)->m_Levels_URL=*static_cast<const vector<path>*>(Value);
            }

            static const bool Is_Filed_Levels_URL_CPPVector(void){
                return  !  false;
            }

                static const string Get_Field_Levels_URL_CPPVector_Element_Type_Spelling(void){
                    return string {"m_Levels_URL"};
                }

                static const size_t Get_Field_Levels_URL_CPPVector_Capacity(shared_ptr<void> Instance){
                    return static_pointer_cast<World>(Instance)->m_Levels_URL.capacity();
                }

                static const size_t Get_Field_Levels_URL_CPPVector_Size(shared_ptr<void> Instance){
                    return static_pointer_cast<World>(Instance)->m_Levels_URL.size();
                }

                static const void *Get_Field_Levels_URL_CPPVector_Element(shared_ptr<void> Instance, size_t Index){
                    return static_cast<const void*>(&static_pointer_cast<World>(Instance)->m_Levels_URL[Index]);
                }

                static void Set_Field_Levels_URL_CPPVector_Element(shared_ptr<void> Instance, size_t Index,const void* Value){
                    static_pointer_cast<World>(Instance)->m_Levels_URL[Index]=*static_cast<const path*>(Value);
                }


            static void TypeWrapper_Rigster(void){
                shared_ptr<Class_Func_Tuple> Temp_Class_Func_Tuple{nullptr};
                shared_ptr<Class_Base_Class_Tuple> Temp_Class_Base_Class_Tuple{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Field_Func_Tuple>>> Temp_Class_Field_Func_Tuple_Map{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Filed_CPPVector_Func_Tuple>>> Temp_Class_Filed_CPPVector_Func_Tuple_Map{nullptr};

                Temp_Class_Func_Tuple = make_shared<Class_Func_Tuple>(
                    Reflection_World_Operator::Get_Class_World_Spelling,
                    Reflection_World_Operator::Get_Class_Displaying_Name
                );

                Temp_Class_Base_Class_Tuple = make_shared<Class_Base_Class_Tuple>(
                    Reflection_World_Operator::Get_Base_Class_World_Reflection_Instance_List
                );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Levels_URL"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_World_Operator::Get_Field_Levels_URL_Type_Spelling,
                        Reflection_World_Operator::Get_Field_Levels_URL_Spelling,
                        Reflection_World_Operator::Get_Field_Levels_URL_Display_Name,
                        Reflection_World_Operator::Get_Filed_Levels_URL_Attribute,
                        Reflection_World_Operator::Set_Field_Levels_URL_Attribute,
                        Reflection_World_Operator::Is_Filed_Levels_URL_CPPVector
                    )
                );

                    Temp_Class_Filed_CPPVector_Func_Tuple_Map->emplace(
                    string{"m_Levels_URL"},
                        make_shared<Class_Filed_CPPVector_Func_Tuple>( 
                            Reflection_World_Operator::Get_Field_Levels_URL_CPPVector_Element_Type_Spelling,
                            Reflection_World_Operator::Get_Field_Levels_URL_CPPVector_Capacity,
                            Reflection_World_Operator::Get_Field_Levels_URL_CPPVector_Size,
                            Reflection_World_Operator::Get_Field_Levels_URL_CPPVector_Element,
                            Reflection_World_Operator::Set_Field_Levels_URL_CPPVector_Element
                        )
                    );

                
            Reflection_Register::Get_Instance().Register_Class(string{"World"},Temp_Class_Func_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Base_Class(string{"World"},Temp_Class_Base_Class_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Filed(string{"World"},Temp_Class_Field_Func_Tuple_Map);
            Reflection_Register::Get_Instance().Register_Class_Field_CPPVector(string{"World"},Temp_Class_Filed_CPPVector_Func_Tuple_Map);
        }

    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection


