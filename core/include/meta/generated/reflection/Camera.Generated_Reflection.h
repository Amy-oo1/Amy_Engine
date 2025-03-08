#pragma once

#include<string>
#include<vector>
#include<memory>
#include<cstddef>

#include "meta/Reflection/Reflection_Instance.h"
#include "meta/Reflection/Reflection_Register.h"

#include "D:/Amy_Engine/resource/include/components/Camera.h"

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


    class Reflection_Camera_Base_Operator {
    public:

        static const string Get_Class_Camera_Base_Spelling(void){
            return string{"Camera_Base"};
        }

        static const string Get_Class_Displaying_Name(void){
            return string{"Camera_Base"};            
        }

            static const vector<Reflection_Instance<void>> Get_Base_Class_Camera_Base_Reflection_Instance_List(shared_ptr<void> Instance){
                vector<Reflection_Instance<void>> Table;

                    

                return Table;
            }

            static const string Get_Field_FOV_Type_Spelling(void){
                return string{"float"};
            }

            static const string Get_Field_FOV_Spelling(void){
                return string{"m_FOV"};
            }


            static const string Get_Field_FOV_Display_Name(void){
                return string{"FOV"};
            }

            static const void *const Get_Filed_FOV_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Camera_Base>(Instance)->m_FOV);
            }

            static void Set_Field_FOV_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Camera_Base>(Instance)->m_FOV=*static_cast<const float*>(Value);
            }

            static const bool Is_Filed_FOV_CPPVector(void){
                return  false;
            }

            


            static void TypeWrapper_Rigster(void){
                shared_ptr<Class_Func_Tuple> Temp_Class_Func_Tuple{nullptr};
                shared_ptr<Class_Base_Class_Tuple> Temp_Class_Base_Class_Tuple{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Field_Func_Tuple>>> Temp_Class_Field_Func_Tuple_Map{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Filed_CPPVector_Func_Tuple>>> Temp_Class_Filed_CPPVector_Func_Tuple_Map{nullptr};

                Temp_Class_Func_Tuple = make_shared<Class_Func_Tuple>(
                    Reflection_Camera_Base_Operator::Get_Class_Camera_Base_Spelling,
                    Reflection_Camera_Base_Operator::Get_Class_Displaying_Name
                );

                Temp_Class_Base_Class_Tuple = make_shared<Class_Base_Class_Tuple>(
                    Reflection_Camera_Base_Operator::Get_Base_Class_Camera_Base_Reflection_Instance_List
                );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_FOV"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Camera_Base_Operator::Get_Field_FOV_Type_Spelling,
                        Reflection_Camera_Base_Operator::Get_Field_FOV_Spelling,
                        Reflection_Camera_Base_Operator::Get_Field_FOV_Display_Name,
                        Reflection_Camera_Base_Operator::Get_Filed_FOV_Attribute,
                        Reflection_Camera_Base_Operator::Set_Field_FOV_Attribute,
                        Reflection_Camera_Base_Operator::Is_Filed_FOV_CPPVector
                    )
                );

                

                
            Reflection_Register::Get_Instance().Register_Class(string{"Camera_Base"},Temp_Class_Func_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Base_Class(string{"Camera_Base"},Temp_Class_Base_Class_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Filed(string{"Camera_Base"},Temp_Class_Field_Func_Tuple_Map);
            Reflection_Register::Get_Instance().Register_Class_Field_CPPVector(string{"Camera_Base"},Temp_Class_Filed_CPPVector_Func_Tuple_Map);
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


    class Reflection_Camera_First_Persion_Operator {
    public:

        static const string Get_Class_Camera_First_Persion_Spelling(void){
            return string{"Camera_First_Persion"};
        }

        static const string Get_Class_Displaying_Name(void){
            return string{"Camera_First_Persion"};            
        }

            static const vector<Reflection_Instance<void>> Get_Base_Class_Camera_First_Persion_Reflection_Instance_List(shared_ptr<void> Instance){
                vector<Reflection_Instance<void>> Table;

                        Table.emplace_back(string{"Camera_Base"},static_pointer_cast<Camera_Base>(Instance));

                return Table;
            }

            static const string Get_Field_vertical_offset_Type_Spelling(void){
                return string{"float"};
            }

            static const string Get_Field_vertical_offset_Spelling(void){
                return string{"m_vertical_offset"};
            }


            static const string Get_Field_vertical_offset_Display_Name(void){
                return string{"vertical_offset"};
            }

            static const void *const Get_Filed_vertical_offset_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Camera_First_Persion>(Instance)->m_vertical_offset);
            }

            static void Set_Field_vertical_offset_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Camera_First_Persion>(Instance)->m_vertical_offset=*static_cast<const float*>(Value);
            }

            static const bool Is_Filed_vertical_offset_CPPVector(void){
                return  false;
            }

            


            static void TypeWrapper_Rigster(void){
                shared_ptr<Class_Func_Tuple> Temp_Class_Func_Tuple{nullptr};
                shared_ptr<Class_Base_Class_Tuple> Temp_Class_Base_Class_Tuple{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Field_Func_Tuple>>> Temp_Class_Field_Func_Tuple_Map{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Filed_CPPVector_Func_Tuple>>> Temp_Class_Filed_CPPVector_Func_Tuple_Map{nullptr};

                Temp_Class_Func_Tuple = make_shared<Class_Func_Tuple>(
                    Reflection_Camera_First_Persion_Operator::Get_Class_Camera_First_Persion_Spelling,
                    Reflection_Camera_First_Persion_Operator::Get_Class_Displaying_Name
                );

                Temp_Class_Base_Class_Tuple = make_shared<Class_Base_Class_Tuple>(
                    Reflection_Camera_First_Persion_Operator::Get_Base_Class_Camera_First_Persion_Reflection_Instance_List
                );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_vertical_offset"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Camera_First_Persion_Operator::Get_Field_vertical_offset_Type_Spelling,
                        Reflection_Camera_First_Persion_Operator::Get_Field_vertical_offset_Spelling,
                        Reflection_Camera_First_Persion_Operator::Get_Field_vertical_offset_Display_Name,
                        Reflection_Camera_First_Persion_Operator::Get_Filed_vertical_offset_Attribute,
                        Reflection_Camera_First_Persion_Operator::Set_Field_vertical_offset_Attribute,
                        Reflection_Camera_First_Persion_Operator::Is_Filed_vertical_offset_CPPVector
                    )
                );

                

                
            Reflection_Register::Get_Instance().Register_Class(string{"Camera_First_Persion"},Temp_Class_Func_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Base_Class(string{"Camera_First_Persion"},Temp_Class_Base_Class_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Filed(string{"Camera_First_Persion"},Temp_Class_Field_Func_Tuple_Map);
            Reflection_Register::Get_Instance().Register_Class_Field_CPPVector(string{"Camera_First_Persion"},Temp_Class_Filed_CPPVector_Func_Tuple_Map);
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


    class Reflection_Camera_Third_Persion_Operator {
    public:

        static const string Get_Class_Camera_Third_Persion_Spelling(void){
            return string{"Camera_Third_Persion"};
        }

        static const string Get_Class_Displaying_Name(void){
            return string{"Camera_Third_Persion"};            
        }

            static const vector<Reflection_Instance<void>> Get_Base_Class_Camera_Third_Persion_Reflection_Instance_List(shared_ptr<void> Instance){
                vector<Reflection_Instance<void>> Table;

                        Table.emplace_back(string{"Camera_Base"},static_pointer_cast<Camera_Base>(Instance));

                return Table;
            }

            static const string Get_Field_Cursor_Yaw_Type_Spelling(void){
                return string{"NameSpace_Core::NameSpace_Math::Quaternion"};
            }

            static const string Get_Field_Cursor_Yaw_Spelling(void){
                return string{"m_Cursor_Yaw"};
            }


            static const string Get_Field_Cursor_Yaw_Display_Name(void){
                return string{"Cursor_Yaw"};
            }

            static const void *const Get_Filed_Cursor_Yaw_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Camera_Third_Persion>(Instance)->m_Cursor_Yaw);
            }

            static void Set_Field_Cursor_Yaw_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Camera_Third_Persion>(Instance)->m_Cursor_Yaw=*static_cast<const NameSpace_Core::NameSpace_Math::Quaternion*>(Value);
            }

            static const bool Is_Filed_Cursor_Yaw_CPPVector(void){
                return  false;
            }

            


            static void TypeWrapper_Rigster(void){
                shared_ptr<Class_Func_Tuple> Temp_Class_Func_Tuple{nullptr};
                shared_ptr<Class_Base_Class_Tuple> Temp_Class_Base_Class_Tuple{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Field_Func_Tuple>>> Temp_Class_Field_Func_Tuple_Map{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Filed_CPPVector_Func_Tuple>>> Temp_Class_Filed_CPPVector_Func_Tuple_Map{nullptr};

                Temp_Class_Func_Tuple = make_shared<Class_Func_Tuple>(
                    Reflection_Camera_Third_Persion_Operator::Get_Class_Camera_Third_Persion_Spelling,
                    Reflection_Camera_Third_Persion_Operator::Get_Class_Displaying_Name
                );

                Temp_Class_Base_Class_Tuple = make_shared<Class_Base_Class_Tuple>(
                    Reflection_Camera_Third_Persion_Operator::Get_Base_Class_Camera_Third_Persion_Reflection_Instance_List
                );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Cursor_Yaw"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Camera_Third_Persion_Operator::Get_Field_Cursor_Yaw_Type_Spelling,
                        Reflection_Camera_Third_Persion_Operator::Get_Field_Cursor_Yaw_Spelling,
                        Reflection_Camera_Third_Persion_Operator::Get_Field_Cursor_Yaw_Display_Name,
                        Reflection_Camera_Third_Persion_Operator::Get_Filed_Cursor_Yaw_Attribute,
                        Reflection_Camera_Third_Persion_Operator::Set_Field_Cursor_Yaw_Attribute,
                        Reflection_Camera_Third_Persion_Operator::Is_Filed_Cursor_Yaw_CPPVector
                    )
                );

                

                
            Reflection_Register::Get_Instance().Register_Class(string{"Camera_Third_Persion"},Temp_Class_Func_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Base_Class(string{"Camera_Third_Persion"},Temp_Class_Base_Class_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Filed(string{"Camera_Third_Persion"},Temp_Class_Field_Func_Tuple_Map);
            Reflection_Register::Get_Instance().Register_Class_Field_CPPVector(string{"Camera_Third_Persion"},Temp_Class_Filed_CPPVector_Func_Tuple_Map);
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


    class Reflection_Camera_Free_Operator {
    public:

        static const string Get_Class_Camera_Free_Spelling(void){
            return string{"Camera_Free"};
        }

        static const string Get_Class_Displaying_Name(void){
            return string{"Camera_Free"};            
        }

            static const vector<Reflection_Instance<void>> Get_Base_Class_Camera_Free_Reflection_Instance_List(shared_ptr<void> Instance){
                vector<Reflection_Instance<void>> Table;

                        Table.emplace_back(string{"Camera_Base"},static_pointer_cast<Camera_Base>(Instance));

                return Table;
            }

            static const string Get_Field_Speed_Type_Spelling(void){
                return string{"float"};
            }

            static const string Get_Field_Speed_Spelling(void){
                return string{"m_Speed"};
            }


            static const string Get_Field_Speed_Display_Name(void){
                return string{"Speed"};
            }

            static const void *const Get_Filed_Speed_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Camera_Free>(Instance)->m_Speed);
            }

            static void Set_Field_Speed_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Camera_Free>(Instance)->m_Speed=*static_cast<const float*>(Value);
            }

            static const bool Is_Filed_Speed_CPPVector(void){
                return  false;
            }

            


            static void TypeWrapper_Rigster(void){
                shared_ptr<Class_Func_Tuple> Temp_Class_Func_Tuple{nullptr};
                shared_ptr<Class_Base_Class_Tuple> Temp_Class_Base_Class_Tuple{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Field_Func_Tuple>>> Temp_Class_Field_Func_Tuple_Map{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Filed_CPPVector_Func_Tuple>>> Temp_Class_Filed_CPPVector_Func_Tuple_Map{nullptr};

                Temp_Class_Func_Tuple = make_shared<Class_Func_Tuple>(
                    Reflection_Camera_Free_Operator::Get_Class_Camera_Free_Spelling,
                    Reflection_Camera_Free_Operator::Get_Class_Displaying_Name
                );

                Temp_Class_Base_Class_Tuple = make_shared<Class_Base_Class_Tuple>(
                    Reflection_Camera_Free_Operator::Get_Base_Class_Camera_Free_Reflection_Instance_List
                );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Speed"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Camera_Free_Operator::Get_Field_Speed_Type_Spelling,
                        Reflection_Camera_Free_Operator::Get_Field_Speed_Spelling,
                        Reflection_Camera_Free_Operator::Get_Field_Speed_Display_Name,
                        Reflection_Camera_Free_Operator::Get_Filed_Speed_Attribute,
                        Reflection_Camera_Free_Operator::Set_Field_Speed_Attribute,
                        Reflection_Camera_Free_Operator::Is_Filed_Speed_CPPVector
                    )
                );

                

                
            Reflection_Register::Get_Instance().Register_Class(string{"Camera_Free"},Temp_Class_Func_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Base_Class(string{"Camera_Free"},Temp_Class_Base_Class_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Filed(string{"Camera_Free"},Temp_Class_Field_Func_Tuple_Map);
            Reflection_Register::Get_Instance().Register_Class_Field_CPPVector(string{"Camera_Free"},Temp_Class_Filed_CPPVector_Func_Tuple_Map);
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


    class Reflection_Component_Camera_Resource_Operator {
    public:

        static const string Get_Class_Component_Camera_Resource_Spelling(void){
            return string{"Component_Camera_Resource"};
        }

        static const string Get_Class_Displaying_Name(void){
            return string{"Component_Camera_Resource"};            
        }

            static const vector<Reflection_Instance<void>> Get_Base_Class_Component_Camera_Resource_Reflection_Instance_List(shared_ptr<void> Instance){
                vector<Reflection_Instance<void>> Table;

                    

                return Table;
            }

            static const string Get_Field_Camera_Type_Spelling(void){
                return string{"Reflection_Instance<Camera_Base>"};
            }

            static const string Get_Field_Camera_Spelling(void){
                return string{"m_Camera"};
            }


            static const string Get_Field_Camera_Display_Name(void){
                return string{"Camera"};
            }

            static const void *const Get_Filed_Camera_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Component_Camera_Resource>(Instance)->m_Camera);
            }

            static void Set_Field_Camera_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Component_Camera_Resource>(Instance)->m_Camera=*static_cast<const Reflection_Instance<Camera_Base>*>(Value);
            }

            static const bool Is_Filed_Camera_CPPVector(void){
                return  false;
            }

            


            static void TypeWrapper_Rigster(void){
                shared_ptr<Class_Func_Tuple> Temp_Class_Func_Tuple{nullptr};
                shared_ptr<Class_Base_Class_Tuple> Temp_Class_Base_Class_Tuple{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Field_Func_Tuple>>> Temp_Class_Field_Func_Tuple_Map{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Filed_CPPVector_Func_Tuple>>> Temp_Class_Filed_CPPVector_Func_Tuple_Map{nullptr};

                Temp_Class_Func_Tuple = make_shared<Class_Func_Tuple>(
                    Reflection_Component_Camera_Resource_Operator::Get_Class_Component_Camera_Resource_Spelling,
                    Reflection_Component_Camera_Resource_Operator::Get_Class_Displaying_Name
                );

                Temp_Class_Base_Class_Tuple = make_shared<Class_Base_Class_Tuple>(
                    Reflection_Component_Camera_Resource_Operator::Get_Base_Class_Component_Camera_Resource_Reflection_Instance_List
                );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Camera"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Component_Camera_Resource_Operator::Get_Field_Camera_Type_Spelling,
                        Reflection_Component_Camera_Resource_Operator::Get_Field_Camera_Spelling,
                        Reflection_Component_Camera_Resource_Operator::Get_Field_Camera_Display_Name,
                        Reflection_Component_Camera_Resource_Operator::Get_Filed_Camera_Attribute,
                        Reflection_Component_Camera_Resource_Operator::Set_Field_Camera_Attribute,
                        Reflection_Component_Camera_Resource_Operator::Is_Filed_Camera_CPPVector
                    )
                );

                

                
            Reflection_Register::Get_Instance().Register_Class(string{"Component_Camera_Resource"},Temp_Class_Func_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Base_Class(string{"Component_Camera_Resource"},Temp_Class_Base_Class_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Filed(string{"Component_Camera_Resource"},Temp_Class_Field_Func_Tuple_Map);
            Reflection_Register::Get_Instance().Register_Class_Field_CPPVector(string{"Component_Camera_Resource"},Temp_Class_Filed_CPPVector_Func_Tuple_Map);
        }

    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection


