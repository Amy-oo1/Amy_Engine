#pragma once

#include<string>
#include<vector>
#include<memory>
#include<cstddef>

#include "meta/Reflection/Reflection_Instance.h"
#include "meta/Reflection/Reflection_Register.h"

#include "D:/Amy_Engine/resource/include/components/skeleton/Skeleton_Mask.h"

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


    class Reflection_Skeleton_Mask_Operator {
    public:

        static const string Get_Class_Skeleton_Mask_Spelling(void){
            return string{"Skeleton_Mask"};
        }

        static const string Get_Class_Displaying_Name(void){
            return string{"Skeleton_Mask"};            
        }

            static const vector<Reflection_Instance<void>> Get_Base_Class_Skeleton_Mask_Reflection_Instance_List(shared_ptr<void> Instance){
                vector<Reflection_Instance<void>> Table;

                    

                return Table;
            }

            static const string Get_Field_enabled_Type_Spelling(void){
                return string{"vector<size_t>"};
            }

            static const string Get_Field_enabled_Spelling(void){
                return string{"enabled"};
            }


            static const string Get_Field_enabled_Display_Name(void){
                return string{"enabled"};
            }

            static const void *const Get_Filed_enabled_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Skeleton_Mask>(Instance)->enabled);
            }

            static void Set_Field_enabled_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Skeleton_Mask>(Instance)->enabled=*static_cast<const vector<size_t>*>(Value);
            }

            static const bool Is_Filed_enabled_CPPVector(void){
                return  !  false;
            }

                static const string Get_Field_enabled_CPPVector_Element_Type_Spelling(void){
                    return string {"enabled"};
                }

                static const size_t Get_Field_enabled_CPPVector_Capacity(shared_ptr<void> Instance){
                    return static_pointer_cast<Skeleton_Mask>(Instance)->enabled.capacity();
                }

                static const size_t Get_Field_enabled_CPPVector_Size(shared_ptr<void> Instance){
                    return static_pointer_cast<Skeleton_Mask>(Instance)->enabled.size();
                }

                static const void *Get_Field_enabled_CPPVector_Element(shared_ptr<void> Instance, size_t Index){
                    return static_cast<const void*>(&static_pointer_cast<Skeleton_Mask>(Instance)->enabled[Index]);
                }

                static void Set_Field_enabled_CPPVector_Element(shared_ptr<void> Instance, size_t Index,const void* Value){
                    static_pointer_cast<Skeleton_Mask>(Instance)->enabled[Index]=*static_cast<const size_t*>(Value);
                }


            static void TypeWrapper_Rigster(void){
                shared_ptr<Class_Func_Tuple> Temp_Class_Func_Tuple{nullptr};
                shared_ptr<Class_Base_Class_Tuple> Temp_Class_Base_Class_Tuple{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Field_Func_Tuple>>> Temp_Class_Field_Func_Tuple_Map{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Filed_CPPVector_Func_Tuple>>> Temp_Class_Filed_CPPVector_Func_Tuple_Map{nullptr};

                Temp_Class_Func_Tuple = make_shared<Class_Func_Tuple>(
                    Reflection_Skeleton_Mask_Operator::Get_Class_Skeleton_Mask_Spelling,
                    Reflection_Skeleton_Mask_Operator::Get_Class_Displaying_Name
                );

                Temp_Class_Base_Class_Tuple = make_shared<Class_Base_Class_Tuple>(
                    Reflection_Skeleton_Mask_Operator::Get_Base_Class_Skeleton_Mask_Reflection_Instance_List
                );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"enabled"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Skeleton_Mask_Operator::Get_Field_enabled_Type_Spelling,
                        Reflection_Skeleton_Mask_Operator::Get_Field_enabled_Spelling,
                        Reflection_Skeleton_Mask_Operator::Get_Field_enabled_Display_Name,
                        Reflection_Skeleton_Mask_Operator::Get_Filed_enabled_Attribute,
                        Reflection_Skeleton_Mask_Operator::Set_Field_enabled_Attribute,
                        Reflection_Skeleton_Mask_Operator::Is_Filed_enabled_CPPVector
                    )
                );

                    Temp_Class_Filed_CPPVector_Func_Tuple_Map->emplace(
                    string{"enabled"},
                        make_shared<Class_Filed_CPPVector_Func_Tuple>( 
                            Reflection_Skeleton_Mask_Operator::Get_Field_enabled_CPPVector_Element_Type_Spelling,
                            Reflection_Skeleton_Mask_Operator::Get_Field_enabled_CPPVector_Capacity,
                            Reflection_Skeleton_Mask_Operator::Get_Field_enabled_CPPVector_Size,
                            Reflection_Skeleton_Mask_Operator::Get_Field_enabled_CPPVector_Element,
                            Reflection_Skeleton_Mask_Operator::Set_Field_enabled_CPPVector_Element
                        )
                    );

                
            Reflection_Register::Get_Instance().Register_Class(string{"Skeleton_Mask"},Temp_Class_Func_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Base_Class(string{"Skeleton_Mask"},Temp_Class_Base_Class_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Filed(string{"Skeleton_Mask"},Temp_Class_Field_Func_Tuple_Map);
            Reflection_Register::Get_Instance().Register_Class_Field_CPPVector(string{"Skeleton_Mask"},Temp_Class_Filed_CPPVector_Func_Tuple_Map);
        }

    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection


