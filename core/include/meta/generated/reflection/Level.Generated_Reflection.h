#pragma once

#include<string>
#include<vector>
#include<memory>
#include<cstddef>

#include "meta/Reflection/Reflection_Instance.h"
#include "meta/Reflection/Reflection_Register.h"

#include "D:/Amy_Engine/resource/include/common/Level.h"

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


    class Reflection_Level_Operator {
    public:

        static const string Get_Class_Level_Spelling(void){
            return string{"Level"};
        }

        static const string Get_Class_Displaying_Name(void){
            return string{"Level"};            
        }

            static const vector<Reflection_Instance<void>> Get_Base_Class_Level_Reflection_Instance_List(shared_ptr<void> Instance){
                vector<Reflection_Instance<void>> Table;

                    

                return Table;
            }

            static const string Get_Field_Objects_Type_Spelling(void){
                return string{"vector<Object_Instance>"};
            }

            static const string Get_Field_Objects_Spelling(void){
                return string{"m_Objects"};
            }


            static const string Get_Field_Objects_Display_Name(void){
                return string{"Objects"};
            }

            static const void *const Get_Filed_Objects_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Level>(Instance)->m_Objects);
            }

            static void Set_Field_Objects_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Level>(Instance)->m_Objects=*static_cast<const vector<Object_Instance>*>(Value);
            }

            static const bool Is_Filed_Objects_CPPVector(void){
                return  !  false;
            }

                static const string Get_Field_Objects_CPPVector_Element_Type_Spelling(void){
                    return string {"m_Objects"};
                }

                static const size_t Get_Field_Objects_CPPVector_Capacity(shared_ptr<void> Instance){
                    return static_pointer_cast<Level>(Instance)->m_Objects.capacity();
                }

                static const size_t Get_Field_Objects_CPPVector_Size(shared_ptr<void> Instance){
                    return static_pointer_cast<Level>(Instance)->m_Objects.size();
                }

                static const void *Get_Field_Objects_CPPVector_Element(shared_ptr<void> Instance, size_t Index){
                    return static_cast<const void*>(&static_pointer_cast<Level>(Instance)->m_Objects[Index]);
                }

                static void Set_Field_Objects_CPPVector_Element(shared_ptr<void> Instance, size_t Index,const void* Value){
                    static_pointer_cast<Level>(Instance)->m_Objects[Index]=*static_cast<const Object_Instance*>(Value);
                }


            static void TypeWrapper_Rigster(void){
                shared_ptr<Class_Func_Tuple> Temp_Class_Func_Tuple{nullptr};
                shared_ptr<Class_Base_Class_Tuple> Temp_Class_Base_Class_Tuple{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Field_Func_Tuple>>> Temp_Class_Field_Func_Tuple_Map{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Filed_CPPVector_Func_Tuple>>> Temp_Class_Filed_CPPVector_Func_Tuple_Map{nullptr};

                Temp_Class_Func_Tuple = make_shared<Class_Func_Tuple>(
                    Reflection_Level_Operator::Get_Class_Level_Spelling,
                    Reflection_Level_Operator::Get_Class_Displaying_Name
                );

                Temp_Class_Base_Class_Tuple = make_shared<Class_Base_Class_Tuple>(
                    Reflection_Level_Operator::Get_Base_Class_Level_Reflection_Instance_List
                );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Objects"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Level_Operator::Get_Field_Objects_Type_Spelling,
                        Reflection_Level_Operator::Get_Field_Objects_Spelling,
                        Reflection_Level_Operator::Get_Field_Objects_Display_Name,
                        Reflection_Level_Operator::Get_Filed_Objects_Attribute,
                        Reflection_Level_Operator::Set_Field_Objects_Attribute,
                        Reflection_Level_Operator::Is_Filed_Objects_CPPVector
                    )
                );

                    Temp_Class_Filed_CPPVector_Func_Tuple_Map->emplace(
                    string{"m_Objects"},
                        make_shared<Class_Filed_CPPVector_Func_Tuple>( 
                            Reflection_Level_Operator::Get_Field_Objects_CPPVector_Element_Type_Spelling,
                            Reflection_Level_Operator::Get_Field_Objects_CPPVector_Capacity,
                            Reflection_Level_Operator::Get_Field_Objects_CPPVector_Size,
                            Reflection_Level_Operator::Get_Field_Objects_CPPVector_Element,
                            Reflection_Level_Operator::Set_Field_Objects_CPPVector_Element
                        )
                    );

                
            Reflection_Register::Get_Instance().Register_Class(string{"Level"},Temp_Class_Func_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Base_Class(string{"Level"},Temp_Class_Base_Class_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Filed(string{"Level"},Temp_Class_Field_Func_Tuple_Map);
            Reflection_Register::Get_Instance().Register_Class_Field_CPPVector(string{"Level"},Temp_Class_Filed_CPPVector_Func_Tuple_Map);
        }

    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection


