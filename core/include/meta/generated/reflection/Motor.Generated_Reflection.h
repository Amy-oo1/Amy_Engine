#pragma once

#include<string>
#include<vector>
#include<memory>
#include<cstddef>

#include "meta/Reflection/Reflection_Instance.h"
#include "meta/Reflection/Reflection_Register.h"

#include "D:/Amy_Engine/resource/include/components/motor/Motor.h"

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


    class Reflection_Physics_Controller_Config_Operator {
    public:

        static const string Get_Class_Physics_Controller_Config_Spelling(void){
            return string{"Physics_Controller_Config"};
        }

        static const string Get_Class_Displaying_Name(void){
            return string{"Physics_Controller_Config"};            
        }

            static const vector<Reflection_Instance<void>> Get_Base_Class_Physics_Controller_Config_Reflection_Instance_List(shared_ptr<void> Instance){
                vector<Reflection_Instance<void>> Table;

                    

                return Table;
            }

            static const string Get_Field_Cylinder_Type_Spelling(void){
                return string{"Geometry_Cylinder"};
            }

            static const string Get_Field_Cylinder_Spelling(void){
                return string{"m_Cylinder"};
            }


            static const string Get_Field_Cylinder_Display_Name(void){
                return string{"Cylinder"};
            }

            static const void *const Get_Filed_Cylinder_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Physics_Controller_Config>(Instance)->m_Cylinder);
            }

            static void Set_Field_Cylinder_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Physics_Controller_Config>(Instance)->m_Cylinder=*static_cast<const Geometry_Cylinder*>(Value);
            }

            static const bool Is_Filed_Cylinder_CPPVector(void){
                return  false;
            }

            


            static void TypeWrapper_Rigster(void){
                shared_ptr<Class_Func_Tuple> Temp_Class_Func_Tuple{nullptr};
                shared_ptr<Class_Base_Class_Tuple> Temp_Class_Base_Class_Tuple{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Field_Func_Tuple>>> Temp_Class_Field_Func_Tuple_Map{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Filed_CPPVector_Func_Tuple>>> Temp_Class_Filed_CPPVector_Func_Tuple_Map{nullptr};

                Temp_Class_Func_Tuple = make_shared<Class_Func_Tuple>(
                    Reflection_Physics_Controller_Config_Operator::Get_Class_Physics_Controller_Config_Spelling,
                    Reflection_Physics_Controller_Config_Operator::Get_Class_Displaying_Name
                );

                Temp_Class_Base_Class_Tuple = make_shared<Class_Base_Class_Tuple>(
                    Reflection_Physics_Controller_Config_Operator::Get_Base_Class_Physics_Controller_Config_Reflection_Instance_List
                );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Cylinder"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Physics_Controller_Config_Operator::Get_Field_Cylinder_Type_Spelling,
                        Reflection_Physics_Controller_Config_Operator::Get_Field_Cylinder_Spelling,
                        Reflection_Physics_Controller_Config_Operator::Get_Field_Cylinder_Display_Name,
                        Reflection_Physics_Controller_Config_Operator::Get_Filed_Cylinder_Attribute,
                        Reflection_Physics_Controller_Config_Operator::Set_Field_Cylinder_Attribute,
                        Reflection_Physics_Controller_Config_Operator::Is_Filed_Cylinder_CPPVector
                    )
                );

                

                
            Reflection_Register::Get_Instance().Register_Class(string{"Physics_Controller_Config"},Temp_Class_Func_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Base_Class(string{"Physics_Controller_Config"},Temp_Class_Base_Class_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Filed(string{"Physics_Controller_Config"},Temp_Class_Field_Func_Tuple_Map);
            Reflection_Register::Get_Instance().Register_Class_Field_CPPVector(string{"Physics_Controller_Config"},Temp_Class_Filed_CPPVector_Func_Tuple_Map);
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


    class Reflection_Motor_Operator {
    public:

        static const string Get_Class_Motor_Spelling(void){
            return string{"Motor"};
        }

        static const string Get_Class_Displaying_Name(void){
            return string{"Motor"};            
        }

            static const vector<Reflection_Instance<void>> Get_Base_Class_Motor_Reflection_Instance_List(shared_ptr<void> Instance){
                vector<Reflection_Instance<void>> Table;

                    

                return Table;
            }

            static const string Get_Field_Sprint_Acceleration_Type_Spelling(void){
                return string{"float"};
            }

            static const string Get_Field_Sprint_Acceleration_Spelling(void){
                return string{"m_Sprint_Acceleration"};
            }


            static const string Get_Field_Sprint_Acceleration_Display_Name(void){
                return string{"Sprint_Acceleration"};
            }

            static const void *const Get_Filed_Sprint_Acceleration_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Motor>(Instance)->m_Sprint_Acceleration);
            }

            static void Set_Field_Sprint_Acceleration_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Motor>(Instance)->m_Sprint_Acceleration=*static_cast<const float*>(Value);
            }

            static const bool Is_Filed_Sprint_Acceleration_CPPVector(void){
                return  false;
            }

            


            static void TypeWrapper_Rigster(void){
                shared_ptr<Class_Func_Tuple> Temp_Class_Func_Tuple{nullptr};
                shared_ptr<Class_Base_Class_Tuple> Temp_Class_Base_Class_Tuple{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Field_Func_Tuple>>> Temp_Class_Field_Func_Tuple_Map{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Filed_CPPVector_Func_Tuple>>> Temp_Class_Filed_CPPVector_Func_Tuple_Map{nullptr};

                Temp_Class_Func_Tuple = make_shared<Class_Func_Tuple>(
                    Reflection_Motor_Operator::Get_Class_Motor_Spelling,
                    Reflection_Motor_Operator::Get_Class_Displaying_Name
                );

                Temp_Class_Base_Class_Tuple = make_shared<Class_Base_Class_Tuple>(
                    Reflection_Motor_Operator::Get_Base_Class_Motor_Reflection_Instance_List
                );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Sprint_Acceleration"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Motor_Operator::Get_Field_Sprint_Acceleration_Type_Spelling,
                        Reflection_Motor_Operator::Get_Field_Sprint_Acceleration_Spelling,
                        Reflection_Motor_Operator::Get_Field_Sprint_Acceleration_Display_Name,
                        Reflection_Motor_Operator::Get_Filed_Sprint_Acceleration_Attribute,
                        Reflection_Motor_Operator::Set_Field_Sprint_Acceleration_Attribute,
                        Reflection_Motor_Operator::Is_Filed_Sprint_Acceleration_CPPVector
                    )
                );

                

                
            Reflection_Register::Get_Instance().Register_Class(string{"Motor"},Temp_Class_Func_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Base_Class(string{"Motor"},Temp_Class_Base_Class_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Filed(string{"Motor"},Temp_Class_Field_Func_Tuple_Map);
            Reflection_Register::Get_Instance().Register_Class_Field_CPPVector(string{"Motor"},Temp_Class_Filed_CPPVector_Func_Tuple_Map);
        }

    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection


