#pragma once

#include<string>
#include<vector>
#include<memory>
#include<cstddef>

#include "meta/Reflection/Reflection_Instance.h"
#include "meta/Reflection/Reflection_Register.h"

#include "D:/Amy_Engine/resource/include/global/Global_Rendering.h"

namespace NameSpace_Resource::NameSpace_Global{

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


    class Reflection_SkyBox_Irradiance_Map_Operator {
    public:

        static const string Get_Class_SkyBox_Irradiance_Map_Spelling(void){
            return string{"SkyBox_Irradiance_Map"};
        }

        static const string Get_Class_Displaying_Name(void){
            return string{"SkyBox_Irradiance_Map"};            
        }

            static const vector<Reflection_Instance<void>> Get_Base_Class_SkyBox_Irradiance_Map_Reflection_Instance_List(shared_ptr<void> Instance){
                vector<Reflection_Instance<void>> Table;

                    

                return Table;
            }

            static const string Get_Field_Positive_Z_Map_Type_Spelling(void){
                return string{"string"};
            }

            static const string Get_Field_Positive_Z_Map_Spelling(void){
                return string{"m_Positive_Z_Map"};
            }


            static const string Get_Field_Positive_Z_Map_Display_Name(void){
                return string{"Positive_Z_Map"};
            }

            static const void *const Get_Filed_Positive_Z_Map_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<SkyBox_Irradiance_Map>(Instance)->m_Positive_Z_Map);
            }

            static void Set_Field_Positive_Z_Map_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<SkyBox_Irradiance_Map>(Instance)->m_Positive_Z_Map=*static_cast<const string*>(Value);
            }

            static const bool Is_Filed_Positive_Z_Map_CPPVector(void){
                return  false;
            }

            


            static void TypeWrapper_Rigster(void){
                shared_ptr<Class_Func_Tuple> Temp_Class_Func_Tuple{nullptr};
                shared_ptr<Class_Base_Class_Tuple> Temp_Class_Base_Class_Tuple{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Field_Func_Tuple>>> Temp_Class_Field_Func_Tuple_Map{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Filed_CPPVector_Func_Tuple>>> Temp_Class_Filed_CPPVector_Func_Tuple_Map{nullptr};

                Temp_Class_Func_Tuple = make_shared<Class_Func_Tuple>(
                    Reflection_SkyBox_Irradiance_Map_Operator::Get_Class_SkyBox_Irradiance_Map_Spelling,
                    Reflection_SkyBox_Irradiance_Map_Operator::Get_Class_Displaying_Name
                );

                Temp_Class_Base_Class_Tuple = make_shared<Class_Base_Class_Tuple>(
                    Reflection_SkyBox_Irradiance_Map_Operator::Get_Base_Class_SkyBox_Irradiance_Map_Reflection_Instance_List
                );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Positive_Z_Map"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_SkyBox_Irradiance_Map_Operator::Get_Field_Positive_Z_Map_Type_Spelling,
                        Reflection_SkyBox_Irradiance_Map_Operator::Get_Field_Positive_Z_Map_Spelling,
                        Reflection_SkyBox_Irradiance_Map_Operator::Get_Field_Positive_Z_Map_Display_Name,
                        Reflection_SkyBox_Irradiance_Map_Operator::Get_Filed_Positive_Z_Map_Attribute,
                        Reflection_SkyBox_Irradiance_Map_Operator::Set_Field_Positive_Z_Map_Attribute,
                        Reflection_SkyBox_Irradiance_Map_Operator::Is_Filed_Positive_Z_Map_CPPVector
                    )
                );

                

                
            Reflection_Register::Get_Instance().Register_Class(string{"SkyBox_Irradiance_Map"},Temp_Class_Func_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Base_Class(string{"SkyBox_Irradiance_Map"},Temp_Class_Base_Class_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Filed(string{"SkyBox_Irradiance_Map"},Temp_Class_Field_Func_Tuple_Map);
            Reflection_Register::Get_Instance().Register_Class_Field_CPPVector(string{"SkyBox_Irradiance_Map"},Temp_Class_Filed_CPPVector_Func_Tuple_Map);
        }

    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection

namespace NameSpace_Resource::NameSpace_Global{

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


    class Reflection_SkyBox_Specular_Map_Operator {
    public:

        static const string Get_Class_SkyBox_Specular_Map_Spelling(void){
            return string{"SkyBox_Specular_Map"};
        }

        static const string Get_Class_Displaying_Name(void){
            return string{"SkyBox_Specular_Map"};            
        }

            static const vector<Reflection_Instance<void>> Get_Base_Class_SkyBox_Specular_Map_Reflection_Instance_List(shared_ptr<void> Instance){
                vector<Reflection_Instance<void>> Table;

                    

                return Table;
            }

            static const string Get_Field_Positive_Z_Map_Type_Spelling(void){
                return string{"string"};
            }

            static const string Get_Field_Positive_Z_Map_Spelling(void){
                return string{"m_Positive_Z_Map"};
            }


            static const string Get_Field_Positive_Z_Map_Display_Name(void){
                return string{"Positive_Z_Map"};
            }

            static const void *const Get_Filed_Positive_Z_Map_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<SkyBox_Specular_Map>(Instance)->m_Positive_Z_Map);
            }

            static void Set_Field_Positive_Z_Map_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<SkyBox_Specular_Map>(Instance)->m_Positive_Z_Map=*static_cast<const string*>(Value);
            }

            static const bool Is_Filed_Positive_Z_Map_CPPVector(void){
                return  false;
            }

            


            static void TypeWrapper_Rigster(void){
                shared_ptr<Class_Func_Tuple> Temp_Class_Func_Tuple{nullptr};
                shared_ptr<Class_Base_Class_Tuple> Temp_Class_Base_Class_Tuple{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Field_Func_Tuple>>> Temp_Class_Field_Func_Tuple_Map{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Filed_CPPVector_Func_Tuple>>> Temp_Class_Filed_CPPVector_Func_Tuple_Map{nullptr};

                Temp_Class_Func_Tuple = make_shared<Class_Func_Tuple>(
                    Reflection_SkyBox_Specular_Map_Operator::Get_Class_SkyBox_Specular_Map_Spelling,
                    Reflection_SkyBox_Specular_Map_Operator::Get_Class_Displaying_Name
                );

                Temp_Class_Base_Class_Tuple = make_shared<Class_Base_Class_Tuple>(
                    Reflection_SkyBox_Specular_Map_Operator::Get_Base_Class_SkyBox_Specular_Map_Reflection_Instance_List
                );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Positive_Z_Map"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_SkyBox_Specular_Map_Operator::Get_Field_Positive_Z_Map_Type_Spelling,
                        Reflection_SkyBox_Specular_Map_Operator::Get_Field_Positive_Z_Map_Spelling,
                        Reflection_SkyBox_Specular_Map_Operator::Get_Field_Positive_Z_Map_Display_Name,
                        Reflection_SkyBox_Specular_Map_Operator::Get_Filed_Positive_Z_Map_Attribute,
                        Reflection_SkyBox_Specular_Map_Operator::Set_Field_Positive_Z_Map_Attribute,
                        Reflection_SkyBox_Specular_Map_Operator::Is_Filed_Positive_Z_Map_CPPVector
                    )
                );

                

                
            Reflection_Register::Get_Instance().Register_Class(string{"SkyBox_Specular_Map"},Temp_Class_Func_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Base_Class(string{"SkyBox_Specular_Map"},Temp_Class_Base_Class_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Filed(string{"SkyBox_Specular_Map"},Temp_Class_Field_Func_Tuple_Map);
            Reflection_Register::Get_Instance().Register_Class_Field_CPPVector(string{"SkyBox_Specular_Map"},Temp_Class_Filed_CPPVector_Func_Tuple_Map);
        }

    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection

namespace NameSpace_Resource::NameSpace_Global{

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


    class Reflection_Directional_Light_Operator {
    public:

        static const string Get_Class_Directional_Light_Spelling(void){
            return string{"Directional_Light"};
        }

        static const string Get_Class_Displaying_Name(void){
            return string{"Directional_Light"};            
        }

            static const vector<Reflection_Instance<void>> Get_Base_Class_Directional_Light_Reflection_Instance_List(shared_ptr<void> Instance){
                vector<Reflection_Instance<void>> Table;

                    

                return Table;
            }

            static const string Get_Field_Color_Type_Spelling(void){
                return string{"Color"};
            }

            static const string Get_Field_Color_Spelling(void){
                return string{"m_Color"};
            }


            static const string Get_Field_Color_Display_Name(void){
                return string{"Color"};
            }

            static const void *const Get_Filed_Color_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Directional_Light>(Instance)->m_Color);
            }

            static void Set_Field_Color_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Directional_Light>(Instance)->m_Color=*static_cast<const Color*>(Value);
            }

            static const bool Is_Filed_Color_CPPVector(void){
                return  false;
            }

            


            static void TypeWrapper_Rigster(void){
                shared_ptr<Class_Func_Tuple> Temp_Class_Func_Tuple{nullptr};
                shared_ptr<Class_Base_Class_Tuple> Temp_Class_Base_Class_Tuple{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Field_Func_Tuple>>> Temp_Class_Field_Func_Tuple_Map{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Filed_CPPVector_Func_Tuple>>> Temp_Class_Filed_CPPVector_Func_Tuple_Map{nullptr};

                Temp_Class_Func_Tuple = make_shared<Class_Func_Tuple>(
                    Reflection_Directional_Light_Operator::Get_Class_Directional_Light_Spelling,
                    Reflection_Directional_Light_Operator::Get_Class_Displaying_Name
                );

                Temp_Class_Base_Class_Tuple = make_shared<Class_Base_Class_Tuple>(
                    Reflection_Directional_Light_Operator::Get_Base_Class_Directional_Light_Reflection_Instance_List
                );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Color"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Directional_Light_Operator::Get_Field_Color_Type_Spelling,
                        Reflection_Directional_Light_Operator::Get_Field_Color_Spelling,
                        Reflection_Directional_Light_Operator::Get_Field_Color_Display_Name,
                        Reflection_Directional_Light_Operator::Get_Filed_Color_Attribute,
                        Reflection_Directional_Light_Operator::Set_Field_Color_Attribute,
                        Reflection_Directional_Light_Operator::Is_Filed_Color_CPPVector
                    )
                );

                

                
            Reflection_Register::Get_Instance().Register_Class(string{"Directional_Light"},Temp_Class_Func_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Base_Class(string{"Directional_Light"},Temp_Class_Base_Class_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Filed(string{"Directional_Light"},Temp_Class_Field_Func_Tuple_Map);
            Reflection_Register::Get_Instance().Register_Class_Field_CPPVector(string{"Directional_Light"},Temp_Class_Filed_CPPVector_Func_Tuple_Map);
        }

    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection

namespace NameSpace_Resource::NameSpace_Global{

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


    class Reflection_Global_Rendering_Operator {
    public:

        static const string Get_Class_Global_Rendering_Spelling(void){
            return string{"Global_Rendering"};
        }

        static const string Get_Class_Displaying_Name(void){
            return string{"Global_Rendering"};            
        }

            static const vector<Reflection_Instance<void>> Get_Base_Class_Global_Rendering_Reflection_Instance_List(shared_ptr<void> Instance){
                vector<Reflection_Instance<void>> Table;

                    

                return Table;
            }

            static const string Get_Field_Directional_Light_Type_Spelling(void){
                return string{"Directional_Light"};
            }

            static const string Get_Field_Directional_Light_Spelling(void){
                return string{"m_Directional_Light"};
            }


            static const string Get_Field_Directional_Light_Display_Name(void){
                return string{"Directional_Light"};
            }

            static const void *const Get_Filed_Directional_Light_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Global_Rendering>(Instance)->m_Directional_Light);
            }

            static void Set_Field_Directional_Light_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Global_Rendering>(Instance)->m_Directional_Light=*static_cast<const Directional_Light*>(Value);
            }

            static const bool Is_Filed_Directional_Light_CPPVector(void){
                return  false;
            }

            


            static void TypeWrapper_Rigster(void){
                shared_ptr<Class_Func_Tuple> Temp_Class_Func_Tuple{nullptr};
                shared_ptr<Class_Base_Class_Tuple> Temp_Class_Base_Class_Tuple{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Field_Func_Tuple>>> Temp_Class_Field_Func_Tuple_Map{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Filed_CPPVector_Func_Tuple>>> Temp_Class_Filed_CPPVector_Func_Tuple_Map{nullptr};

                Temp_Class_Func_Tuple = make_shared<Class_Func_Tuple>(
                    Reflection_Global_Rendering_Operator::Get_Class_Global_Rendering_Spelling,
                    Reflection_Global_Rendering_Operator::Get_Class_Displaying_Name
                );

                Temp_Class_Base_Class_Tuple = make_shared<Class_Base_Class_Tuple>(
                    Reflection_Global_Rendering_Operator::Get_Base_Class_Global_Rendering_Reflection_Instance_List
                );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Directional_Light"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Global_Rendering_Operator::Get_Field_Directional_Light_Type_Spelling,
                        Reflection_Global_Rendering_Operator::Get_Field_Directional_Light_Spelling,
                        Reflection_Global_Rendering_Operator::Get_Field_Directional_Light_Display_Name,
                        Reflection_Global_Rendering_Operator::Get_Filed_Directional_Light_Attribute,
                        Reflection_Global_Rendering_Operator::Set_Field_Directional_Light_Attribute,
                        Reflection_Global_Rendering_Operator::Is_Filed_Directional_Light_CPPVector
                    )
                );

                

                
            Reflection_Register::Get_Instance().Register_Class(string{"Global_Rendering"},Temp_Class_Func_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Base_Class(string{"Global_Rendering"},Temp_Class_Base_Class_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Filed(string{"Global_Rendering"},Temp_Class_Field_Func_Tuple_Map);
            Reflection_Register::Get_Instance().Register_Class_Field_CPPVector(string{"Global_Rendering"},Temp_Class_Filed_CPPVector_Func_Tuple_Map);
        }

    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection


