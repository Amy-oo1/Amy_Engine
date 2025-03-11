#pragma once

#include<string>
#include<vector>
#include<memory>
#include<cstddef>

#include "meta/Reflection/Reflection_Instance.h"
#include "meta/Reflection/Reflection_Register.h"

#include "D:/Amy_Engine/resource/include/components/camera/Camera_Controller.h"

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


    class Reflection_Camera_Pose_Operator {
    public:

        static const string Get_Class_Camera_Pose_Spelling(void){
            return string{"Camera_Pose"};
        }

        static const string Get_Class_Displaying_Name(void){
            return string{"Camera_Pose"};            
        }

            static const vector<Reflection_Instance<void>> Get_Base_Class_Camera_Pose_Reflection_Instance_List(shared_ptr<void> Instance){
                vector<Reflection_Instance<void>> Table;

                    

                return Table;
            }

            static const string Get_Field_Position_Type_Spelling(void){
                return string{"Vector3"};
            }

            static const string Get_Field_Position_Spelling(void){
                return string{"m_Position"};
            }


            static const string Get_Field_Position_Display_Name(void){
                return string{"Position"};
            }

            static const void *const Get_Filed_Position_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Camera_Pose>(Instance)->m_Position);
            }

            static void Set_Field_Position_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Camera_Pose>(Instance)->m_Position=*static_cast<const Vector3*>(Value);
            }

            static const bool Is_Filed_Position_CPPVector(void){
                return  false;
            }

            

            static const string Get_Field_Target_Type_Spelling(void){
                return string{"Vector3"};
            }

            static const string Get_Field_Target_Spelling(void){
                return string{"m_Target"};
            }


            static const string Get_Field_Target_Display_Name(void){
                return string{"Target"};
            }

            static const void *const Get_Filed_Target_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Camera_Pose>(Instance)->m_Target);
            }

            static void Set_Field_Target_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Camera_Pose>(Instance)->m_Target=*static_cast<const Vector3*>(Value);
            }

            static const bool Is_Filed_Target_CPPVector(void){
                return  false;
            }

            

            static const string Get_Field_Up_Type_Spelling(void){
                return string{"Vector3"};
            }

            static const string Get_Field_Up_Spelling(void){
                return string{"m_Up"};
            }


            static const string Get_Field_Up_Display_Name(void){
                return string{"Up"};
            }

            static const void *const Get_Filed_Up_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Camera_Pose>(Instance)->m_Up);
            }

            static void Set_Field_Up_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Camera_Pose>(Instance)->m_Up=*static_cast<const Vector3*>(Value);
            }

            static const bool Is_Filed_Up_CPPVector(void){
                return  false;
            }

            


            static void TypeWrapper_Rigster(void){
                shared_ptr<Class_Func_Tuple> Temp_Class_Func_Tuple{nullptr};
                shared_ptr<Class_Base_Class_Tuple> Temp_Class_Base_Class_Tuple{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Field_Func_Tuple>>> Temp_Class_Field_Func_Tuple_Map{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Filed_CPPVector_Func_Tuple>>> Temp_Class_Filed_CPPVector_Func_Tuple_Map{nullptr};

                Temp_Class_Func_Tuple = make_shared<Class_Func_Tuple>(
                    Reflection_Camera_Pose_Operator::Get_Class_Camera_Pose_Spelling,
                    Reflection_Camera_Pose_Operator::Get_Class_Displaying_Name
                );

                Temp_Class_Base_Class_Tuple = make_shared<Class_Base_Class_Tuple>(
                    Reflection_Camera_Pose_Operator::Get_Base_Class_Camera_Pose_Reflection_Instance_List
                );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Position"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Camera_Pose_Operator::Get_Field_Position_Type_Spelling,
                        Reflection_Camera_Pose_Operator::Get_Field_Position_Spelling,
                        Reflection_Camera_Pose_Operator::Get_Field_Position_Display_Name,
                        Reflection_Camera_Pose_Operator::Get_Filed_Position_Attribute,
                        Reflection_Camera_Pose_Operator::Set_Field_Position_Attribute,
                        Reflection_Camera_Pose_Operator::Is_Filed_Position_CPPVector
                    )
                );

                

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Target"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Camera_Pose_Operator::Get_Field_Target_Type_Spelling,
                        Reflection_Camera_Pose_Operator::Get_Field_Target_Spelling,
                        Reflection_Camera_Pose_Operator::Get_Field_Target_Display_Name,
                        Reflection_Camera_Pose_Operator::Get_Filed_Target_Attribute,
                        Reflection_Camera_Pose_Operator::Set_Field_Target_Attribute,
                        Reflection_Camera_Pose_Operator::Is_Filed_Target_CPPVector
                    )
                );

                

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Up"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Camera_Pose_Operator::Get_Field_Up_Type_Spelling,
                        Reflection_Camera_Pose_Operator::Get_Field_Up_Spelling,
                        Reflection_Camera_Pose_Operator::Get_Field_Up_Display_Name,
                        Reflection_Camera_Pose_Operator::Get_Filed_Up_Attribute,
                        Reflection_Camera_Pose_Operator::Set_Field_Up_Attribute,
                        Reflection_Camera_Pose_Operator::Is_Filed_Up_CPPVector
                    )
                );

                

                
            Reflection_Register::Get_Instance().Register_Class(string{"Camera_Pose"},Temp_Class_Func_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Base_Class(string{"Camera_Pose"},Temp_Class_Base_Class_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Filed(string{"Camera_Pose"},Temp_Class_Field_Func_Tuple_Map);
            Reflection_Register::Get_Instance().Register_Class_Field_CPPVector(string{"Camera_Pose"},Temp_Class_Filed_CPPVector_Func_Tuple_Map);
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


    class Reflection_Camera_Config_Operator {
    public:

        static const string Get_Class_Camera_Config_Spelling(void){
            return string{"Camera_Config"};
        }

        static const string Get_Class_Displaying_Name(void){
            return string{"Camera_Config"};            
        }

            static const vector<Reflection_Instance<void>> Get_Base_Class_Camera_Config_Reflection_Instance_List(shared_ptr<void> Instance){
                vector<Reflection_Instance<void>> Table;

                    

                return Table;
            }

            static const string Get_Field_M_Pose_Type_Spelling(void){
                return string{"Camera_Pose"};
            }

            static const string Get_Field_M_Pose_Spelling(void){
                return string{"M_Pose"};
            }


            static const string Get_Field_M_Pose_Display_Name(void){
                return string{"M_Pose"};
            }

            static const void *const Get_Filed_M_Pose_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Camera_Config>(Instance)->M_Pose);
            }

            static void Set_Field_M_Pose_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Camera_Config>(Instance)->M_Pose=*static_cast<const Camera_Pose*>(Value);
            }

            static const bool Is_Filed_M_Pose_CPPVector(void){
                return  false;
            }

            

            static const string Get_Field_Aspect_Type_Spelling(void){
                return string{"Vector2"};
            }

            static const string Get_Field_Aspect_Spelling(void){
                return string{"m_Aspect"};
            }


            static const string Get_Field_Aspect_Display_Name(void){
                return string{"Aspect"};
            }

            static const void *const Get_Filed_Aspect_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Camera_Config>(Instance)->m_Aspect);
            }

            static void Set_Field_Aspect_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Camera_Config>(Instance)->m_Aspect=*static_cast<const Vector2*>(Value);
            }

            static const bool Is_Filed_Aspect_CPPVector(void){
                return  false;
            }

            

            static const string Get_Field_Z_Near_Type_Spelling(void){
                return string{"float"};
            }

            static const string Get_Field_Z_Near_Spelling(void){
                return string{"m_Z_Near"};
            }


            static const string Get_Field_Z_Near_Display_Name(void){
                return string{"Z_Near"};
            }

            static const void *const Get_Filed_Z_Near_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Camera_Config>(Instance)->m_Z_Near);
            }

            static void Set_Field_Z_Near_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Camera_Config>(Instance)->m_Z_Near=*static_cast<const float*>(Value);
            }

            static const bool Is_Filed_Z_Near_CPPVector(void){
                return  false;
            }

            

            static const string Get_Field_Z_Far_Type_Spelling(void){
                return string{"float"};
            }

            static const string Get_Field_Z_Far_Spelling(void){
                return string{"m_Z_Far"};
            }


            static const string Get_Field_Z_Far_Display_Name(void){
                return string{"Z_Far"};
            }

            static const void *const Get_Filed_Z_Far_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Camera_Config>(Instance)->m_Z_Far);
            }

            static void Set_Field_Z_Far_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Camera_Config>(Instance)->m_Z_Far=*static_cast<const float*>(Value);
            }

            static const bool Is_Filed_Z_Far_CPPVector(void){
                return  false;
            }

            


            static void TypeWrapper_Rigster(void){
                shared_ptr<Class_Func_Tuple> Temp_Class_Func_Tuple{nullptr};
                shared_ptr<Class_Base_Class_Tuple> Temp_Class_Base_Class_Tuple{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Field_Func_Tuple>>> Temp_Class_Field_Func_Tuple_Map{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Filed_CPPVector_Func_Tuple>>> Temp_Class_Filed_CPPVector_Func_Tuple_Map{nullptr};

                Temp_Class_Func_Tuple = make_shared<Class_Func_Tuple>(
                    Reflection_Camera_Config_Operator::Get_Class_Camera_Config_Spelling,
                    Reflection_Camera_Config_Operator::Get_Class_Displaying_Name
                );

                Temp_Class_Base_Class_Tuple = make_shared<Class_Base_Class_Tuple>(
                    Reflection_Camera_Config_Operator::Get_Base_Class_Camera_Config_Reflection_Instance_List
                );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"M_Pose"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Camera_Config_Operator::Get_Field_M_Pose_Type_Spelling,
                        Reflection_Camera_Config_Operator::Get_Field_M_Pose_Spelling,
                        Reflection_Camera_Config_Operator::Get_Field_M_Pose_Display_Name,
                        Reflection_Camera_Config_Operator::Get_Filed_M_Pose_Attribute,
                        Reflection_Camera_Config_Operator::Set_Field_M_Pose_Attribute,
                        Reflection_Camera_Config_Operator::Is_Filed_M_Pose_CPPVector
                    )
                );

                

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Aspect"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Camera_Config_Operator::Get_Field_Aspect_Type_Spelling,
                        Reflection_Camera_Config_Operator::Get_Field_Aspect_Spelling,
                        Reflection_Camera_Config_Operator::Get_Field_Aspect_Display_Name,
                        Reflection_Camera_Config_Operator::Get_Filed_Aspect_Attribute,
                        Reflection_Camera_Config_Operator::Set_Field_Aspect_Attribute,
                        Reflection_Camera_Config_Operator::Is_Filed_Aspect_CPPVector
                    )
                );

                

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Z_Near"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Camera_Config_Operator::Get_Field_Z_Near_Type_Spelling,
                        Reflection_Camera_Config_Operator::Get_Field_Z_Near_Spelling,
                        Reflection_Camera_Config_Operator::Get_Field_Z_Near_Display_Name,
                        Reflection_Camera_Config_Operator::Get_Filed_Z_Near_Attribute,
                        Reflection_Camera_Config_Operator::Set_Field_Z_Near_Attribute,
                        Reflection_Camera_Config_Operator::Is_Filed_Z_Near_CPPVector
                    )
                );

                

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Z_Far"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Camera_Config_Operator::Get_Field_Z_Far_Type_Spelling,
                        Reflection_Camera_Config_Operator::Get_Field_Z_Far_Spelling,
                        Reflection_Camera_Config_Operator::Get_Field_Z_Far_Display_Name,
                        Reflection_Camera_Config_Operator::Get_Filed_Z_Far_Attribute,
                        Reflection_Camera_Config_Operator::Set_Field_Z_Far_Attribute,
                        Reflection_Camera_Config_Operator::Is_Filed_Z_Far_CPPVector
                    )
                );

                

                
            Reflection_Register::Get_Instance().Register_Class(string{"Camera_Config"},Temp_Class_Func_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Base_Class(string{"Camera_Config"},Temp_Class_Base_Class_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Filed(string{"Camera_Config"},Temp_Class_Field_Func_Tuple_Map);
            Reflection_Register::Get_Instance().Register_Class_Field_CPPVector(string{"Camera_Config"},Temp_Class_Filed_CPPVector_Func_Tuple_Map);
        }

    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection


