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

            static const string Get_Field_Negative_X_Map_Type_Spelling(void){
                return string{"string"};
            }

            static const string Get_Field_Negative_X_Map_Spelling(void){
                return string{"m_Negative_X_Map"};
            }


            static const string Get_Field_Negative_X_Map_Display_Name(void){
                return string{"Negative_X_Map"};
            }

            static const void *const Get_Filed_Negative_X_Map_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<SkyBox_Irradiance_Map>(Instance)->m_Negative_X_Map);
            }

            static void Set_Field_Negative_X_Map_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<SkyBox_Irradiance_Map>(Instance)->m_Negative_X_Map=*static_cast<const string*>(Value);
            }

            static const bool Is_Filed_Negative_X_Map_CPPVector(void){
                return  false;
            }

            

            static const string Get_Field_Positive_X_Map_Type_Spelling(void){
                return string{"string"};
            }

            static const string Get_Field_Positive_X_Map_Spelling(void){
                return string{"m_Positive_X_Map"};
            }


            static const string Get_Field_Positive_X_Map_Display_Name(void){
                return string{"Positive_X_Map"};
            }

            static const void *const Get_Filed_Positive_X_Map_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<SkyBox_Irradiance_Map>(Instance)->m_Positive_X_Map);
            }

            static void Set_Field_Positive_X_Map_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<SkyBox_Irradiance_Map>(Instance)->m_Positive_X_Map=*static_cast<const string*>(Value);
            }

            static const bool Is_Filed_Positive_X_Map_CPPVector(void){
                return  false;
            }

            

            static const string Get_Field_Negative_Y_Map_Type_Spelling(void){
                return string{"string"};
            }

            static const string Get_Field_Negative_Y_Map_Spelling(void){
                return string{"m_Negative_Y_Map"};
            }


            static const string Get_Field_Negative_Y_Map_Display_Name(void){
                return string{"Negative_Y_Map"};
            }

            static const void *const Get_Filed_Negative_Y_Map_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<SkyBox_Irradiance_Map>(Instance)->m_Negative_Y_Map);
            }

            static void Set_Field_Negative_Y_Map_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<SkyBox_Irradiance_Map>(Instance)->m_Negative_Y_Map=*static_cast<const string*>(Value);
            }

            static const bool Is_Filed_Negative_Y_Map_CPPVector(void){
                return  false;
            }

            

            static const string Get_Field_Positive_Y_Map_Type_Spelling(void){
                return string{"string"};
            }

            static const string Get_Field_Positive_Y_Map_Spelling(void){
                return string{"m_Positive_Y_Map"};
            }


            static const string Get_Field_Positive_Y_Map_Display_Name(void){
                return string{"Positive_Y_Map"};
            }

            static const void *const Get_Filed_Positive_Y_Map_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<SkyBox_Irradiance_Map>(Instance)->m_Positive_Y_Map);
            }

            static void Set_Field_Positive_Y_Map_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<SkyBox_Irradiance_Map>(Instance)->m_Positive_Y_Map=*static_cast<const string*>(Value);
            }

            static const bool Is_Filed_Positive_Y_Map_CPPVector(void){
                return  false;
            }

            

            static const string Get_Field_Negative_Z_Map_Type_Spelling(void){
                return string{"string"};
            }

            static const string Get_Field_Negative_Z_Map_Spelling(void){
                return string{"m_Negative_Z_Map"};
            }


            static const string Get_Field_Negative_Z_Map_Display_Name(void){
                return string{"Negative_Z_Map"};
            }

            static const void *const Get_Filed_Negative_Z_Map_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<SkyBox_Irradiance_Map>(Instance)->m_Negative_Z_Map);
            }

            static void Set_Field_Negative_Z_Map_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<SkyBox_Irradiance_Map>(Instance)->m_Negative_Z_Map=*static_cast<const string*>(Value);
            }

            static const bool Is_Filed_Negative_Z_Map_CPPVector(void){
                return  false;
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
                    string{"m_Negative_X_Map"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_SkyBox_Irradiance_Map_Operator::Get_Field_Negative_X_Map_Type_Spelling,
                        Reflection_SkyBox_Irradiance_Map_Operator::Get_Field_Negative_X_Map_Spelling,
                        Reflection_SkyBox_Irradiance_Map_Operator::Get_Field_Negative_X_Map_Display_Name,
                        Reflection_SkyBox_Irradiance_Map_Operator::Get_Filed_Negative_X_Map_Attribute,
                        Reflection_SkyBox_Irradiance_Map_Operator::Set_Field_Negative_X_Map_Attribute,
                        Reflection_SkyBox_Irradiance_Map_Operator::Is_Filed_Negative_X_Map_CPPVector
                    )
                );

                

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Positive_X_Map"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_SkyBox_Irradiance_Map_Operator::Get_Field_Positive_X_Map_Type_Spelling,
                        Reflection_SkyBox_Irradiance_Map_Operator::Get_Field_Positive_X_Map_Spelling,
                        Reflection_SkyBox_Irradiance_Map_Operator::Get_Field_Positive_X_Map_Display_Name,
                        Reflection_SkyBox_Irradiance_Map_Operator::Get_Filed_Positive_X_Map_Attribute,
                        Reflection_SkyBox_Irradiance_Map_Operator::Set_Field_Positive_X_Map_Attribute,
                        Reflection_SkyBox_Irradiance_Map_Operator::Is_Filed_Positive_X_Map_CPPVector
                    )
                );

                

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Negative_Y_Map"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_SkyBox_Irradiance_Map_Operator::Get_Field_Negative_Y_Map_Type_Spelling,
                        Reflection_SkyBox_Irradiance_Map_Operator::Get_Field_Negative_Y_Map_Spelling,
                        Reflection_SkyBox_Irradiance_Map_Operator::Get_Field_Negative_Y_Map_Display_Name,
                        Reflection_SkyBox_Irradiance_Map_Operator::Get_Filed_Negative_Y_Map_Attribute,
                        Reflection_SkyBox_Irradiance_Map_Operator::Set_Field_Negative_Y_Map_Attribute,
                        Reflection_SkyBox_Irradiance_Map_Operator::Is_Filed_Negative_Y_Map_CPPVector
                    )
                );

                

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Positive_Y_Map"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_SkyBox_Irradiance_Map_Operator::Get_Field_Positive_Y_Map_Type_Spelling,
                        Reflection_SkyBox_Irradiance_Map_Operator::Get_Field_Positive_Y_Map_Spelling,
                        Reflection_SkyBox_Irradiance_Map_Operator::Get_Field_Positive_Y_Map_Display_Name,
                        Reflection_SkyBox_Irradiance_Map_Operator::Get_Filed_Positive_Y_Map_Attribute,
                        Reflection_SkyBox_Irradiance_Map_Operator::Set_Field_Positive_Y_Map_Attribute,
                        Reflection_SkyBox_Irradiance_Map_Operator::Is_Filed_Positive_Y_Map_CPPVector
                    )
                );

                

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Negative_Z_Map"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_SkyBox_Irradiance_Map_Operator::Get_Field_Negative_Z_Map_Type_Spelling,
                        Reflection_SkyBox_Irradiance_Map_Operator::Get_Field_Negative_Z_Map_Spelling,
                        Reflection_SkyBox_Irradiance_Map_Operator::Get_Field_Negative_Z_Map_Display_Name,
                        Reflection_SkyBox_Irradiance_Map_Operator::Get_Filed_Negative_Z_Map_Attribute,
                        Reflection_SkyBox_Irradiance_Map_Operator::Set_Field_Negative_Z_Map_Attribute,
                        Reflection_SkyBox_Irradiance_Map_Operator::Is_Filed_Negative_Z_Map_CPPVector
                    )
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

            static const string Get_Field_Negative_X_Map_Type_Spelling(void){
                return string{"string"};
            }

            static const string Get_Field_Negative_X_Map_Spelling(void){
                return string{"m_Negative_X_Map"};
            }


            static const string Get_Field_Negative_X_Map_Display_Name(void){
                return string{"Negative_X_Map"};
            }

            static const void *const Get_Filed_Negative_X_Map_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<SkyBox_Specular_Map>(Instance)->m_Negative_X_Map);
            }

            static void Set_Field_Negative_X_Map_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<SkyBox_Specular_Map>(Instance)->m_Negative_X_Map=*static_cast<const string*>(Value);
            }

            static const bool Is_Filed_Negative_X_Map_CPPVector(void){
                return  false;
            }

            

            static const string Get_Field_Positive_X_Map_Type_Spelling(void){
                return string{"string"};
            }

            static const string Get_Field_Positive_X_Map_Spelling(void){
                return string{"m_Positive_X_Map"};
            }


            static const string Get_Field_Positive_X_Map_Display_Name(void){
                return string{"Positive_X_Map"};
            }

            static const void *const Get_Filed_Positive_X_Map_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<SkyBox_Specular_Map>(Instance)->m_Positive_X_Map);
            }

            static void Set_Field_Positive_X_Map_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<SkyBox_Specular_Map>(Instance)->m_Positive_X_Map=*static_cast<const string*>(Value);
            }

            static const bool Is_Filed_Positive_X_Map_CPPVector(void){
                return  false;
            }

            

            static const string Get_Field_Negative_Y_Map_Type_Spelling(void){
                return string{"string"};
            }

            static const string Get_Field_Negative_Y_Map_Spelling(void){
                return string{"m_Negative_Y_Map"};
            }


            static const string Get_Field_Negative_Y_Map_Display_Name(void){
                return string{"Negative_Y_Map"};
            }

            static const void *const Get_Filed_Negative_Y_Map_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<SkyBox_Specular_Map>(Instance)->m_Negative_Y_Map);
            }

            static void Set_Field_Negative_Y_Map_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<SkyBox_Specular_Map>(Instance)->m_Negative_Y_Map=*static_cast<const string*>(Value);
            }

            static const bool Is_Filed_Negative_Y_Map_CPPVector(void){
                return  false;
            }

            

            static const string Get_Field_Positive_Y_Map_Type_Spelling(void){
                return string{"string"};
            }

            static const string Get_Field_Positive_Y_Map_Spelling(void){
                return string{"m_Positive_Y_Map"};
            }


            static const string Get_Field_Positive_Y_Map_Display_Name(void){
                return string{"Positive_Y_Map"};
            }

            static const void *const Get_Filed_Positive_Y_Map_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<SkyBox_Specular_Map>(Instance)->m_Positive_Y_Map);
            }

            static void Set_Field_Positive_Y_Map_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<SkyBox_Specular_Map>(Instance)->m_Positive_Y_Map=*static_cast<const string*>(Value);
            }

            static const bool Is_Filed_Positive_Y_Map_CPPVector(void){
                return  false;
            }

            

            static const string Get_Field_Negative_Z_Map_Type_Spelling(void){
                return string{"string"};
            }

            static const string Get_Field_Negative_Z_Map_Spelling(void){
                return string{"m_Negative_Z_Map"};
            }


            static const string Get_Field_Negative_Z_Map_Display_Name(void){
                return string{"Negative_Z_Map"};
            }

            static const void *const Get_Filed_Negative_Z_Map_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<SkyBox_Specular_Map>(Instance)->m_Negative_Z_Map);
            }

            static void Set_Field_Negative_Z_Map_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<SkyBox_Specular_Map>(Instance)->m_Negative_Z_Map=*static_cast<const string*>(Value);
            }

            static const bool Is_Filed_Negative_Z_Map_CPPVector(void){
                return  false;
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
                    string{"m_Negative_X_Map"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_SkyBox_Specular_Map_Operator::Get_Field_Negative_X_Map_Type_Spelling,
                        Reflection_SkyBox_Specular_Map_Operator::Get_Field_Negative_X_Map_Spelling,
                        Reflection_SkyBox_Specular_Map_Operator::Get_Field_Negative_X_Map_Display_Name,
                        Reflection_SkyBox_Specular_Map_Operator::Get_Filed_Negative_X_Map_Attribute,
                        Reflection_SkyBox_Specular_Map_Operator::Set_Field_Negative_X_Map_Attribute,
                        Reflection_SkyBox_Specular_Map_Operator::Is_Filed_Negative_X_Map_CPPVector
                    )
                );

                

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Positive_X_Map"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_SkyBox_Specular_Map_Operator::Get_Field_Positive_X_Map_Type_Spelling,
                        Reflection_SkyBox_Specular_Map_Operator::Get_Field_Positive_X_Map_Spelling,
                        Reflection_SkyBox_Specular_Map_Operator::Get_Field_Positive_X_Map_Display_Name,
                        Reflection_SkyBox_Specular_Map_Operator::Get_Filed_Positive_X_Map_Attribute,
                        Reflection_SkyBox_Specular_Map_Operator::Set_Field_Positive_X_Map_Attribute,
                        Reflection_SkyBox_Specular_Map_Operator::Is_Filed_Positive_X_Map_CPPVector
                    )
                );

                

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Negative_Y_Map"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_SkyBox_Specular_Map_Operator::Get_Field_Negative_Y_Map_Type_Spelling,
                        Reflection_SkyBox_Specular_Map_Operator::Get_Field_Negative_Y_Map_Spelling,
                        Reflection_SkyBox_Specular_Map_Operator::Get_Field_Negative_Y_Map_Display_Name,
                        Reflection_SkyBox_Specular_Map_Operator::Get_Filed_Negative_Y_Map_Attribute,
                        Reflection_SkyBox_Specular_Map_Operator::Set_Field_Negative_Y_Map_Attribute,
                        Reflection_SkyBox_Specular_Map_Operator::Is_Filed_Negative_Y_Map_CPPVector
                    )
                );

                

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Positive_Y_Map"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_SkyBox_Specular_Map_Operator::Get_Field_Positive_Y_Map_Type_Spelling,
                        Reflection_SkyBox_Specular_Map_Operator::Get_Field_Positive_Y_Map_Spelling,
                        Reflection_SkyBox_Specular_Map_Operator::Get_Field_Positive_Y_Map_Display_Name,
                        Reflection_SkyBox_Specular_Map_Operator::Get_Filed_Positive_Y_Map_Attribute,
                        Reflection_SkyBox_Specular_Map_Operator::Set_Field_Positive_Y_Map_Attribute,
                        Reflection_SkyBox_Specular_Map_Operator::Is_Filed_Positive_Y_Map_CPPVector
                    )
                );

                

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Negative_Z_Map"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_SkyBox_Specular_Map_Operator::Get_Field_Negative_Z_Map_Type_Spelling,
                        Reflection_SkyBox_Specular_Map_Operator::Get_Field_Negative_Z_Map_Spelling,
                        Reflection_SkyBox_Specular_Map_Operator::Get_Field_Negative_Z_Map_Display_Name,
                        Reflection_SkyBox_Specular_Map_Operator::Get_Filed_Negative_Z_Map_Attribute,
                        Reflection_SkyBox_Specular_Map_Operator::Set_Field_Negative_Z_Map_Attribute,
                        Reflection_SkyBox_Specular_Map_Operator::Is_Filed_Negative_Z_Map_CPPVector
                    )
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

            static const string Get_Field_Direction_List_Type_Spelling(void){
                return string{"Vector3"};
            }

            static const string Get_Field_Direction_List_Spelling(void){
                return string{"m_Direction_List"};
            }


            static const string Get_Field_Direction_List_Display_Name(void){
                return string{"Direction_List"};
            }

            static const void *const Get_Filed_Direction_List_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Directional_Light>(Instance)->m_Direction_List);
            }

            static void Set_Field_Direction_List_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Directional_Light>(Instance)->m_Direction_List=*static_cast<const Vector3*>(Value);
            }

            static const bool Is_Filed_Direction_List_CPPVector(void){
                return  false;
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
                    string{"m_Direction_List"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Directional_Light_Operator::Get_Field_Direction_List_Type_Spelling,
                        Reflection_Directional_Light_Operator::Get_Field_Direction_List_Spelling,
                        Reflection_Directional_Light_Operator::Get_Field_Direction_List_Display_Name,
                        Reflection_Directional_Light_Operator::Get_Filed_Direction_List_Attribute,
                        Reflection_Directional_Light_Operator::Set_Field_Direction_List_Attribute,
                        Reflection_Directional_Light_Operator::Is_Filed_Direction_List_CPPVector
                    )
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

            static const string Get_Field_Enable_FXAA_Type_Spelling(void){
                return string{"bool"};
            }

            static const string Get_Field_Enable_FXAA_Spelling(void){
                return string{"m_Enable_FXAA"};
            }


            static const string Get_Field_Enable_FXAA_Display_Name(void){
                return string{"Enable_FXAA"};
            }

            static const void *const Get_Filed_Enable_FXAA_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Global_Rendering>(Instance)->m_Enable_FXAA);
            }

            static void Set_Field_Enable_FXAA_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Global_Rendering>(Instance)->m_Enable_FXAA=*static_cast<const bool*>(Value);
            }

            static const bool Is_Filed_Enable_FXAA_CPPVector(void){
                return  false;
            }

            

            static const string Get_Field_Skybox_Irradiance_Map_Type_Spelling(void){
                return string{"SkyBox_Irradiance_Map"};
            }

            static const string Get_Field_Skybox_Irradiance_Map_Spelling(void){
                return string{"m_Skybox_Irradiance_Map"};
            }


            static const string Get_Field_Skybox_Irradiance_Map_Display_Name(void){
                return string{"Skybox_Irradiance_Map"};
            }

            static const void *const Get_Filed_Skybox_Irradiance_Map_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Global_Rendering>(Instance)->m_Skybox_Irradiance_Map);
            }

            static void Set_Field_Skybox_Irradiance_Map_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Global_Rendering>(Instance)->m_Skybox_Irradiance_Map=*static_cast<const SkyBox_Irradiance_Map*>(Value);
            }

            static const bool Is_Filed_Skybox_Irradiance_Map_CPPVector(void){
                return  false;
            }

            

            static const string Get_Field_Skybox_Specular_Map_Type_Spelling(void){
                return string{"SkyBox_Specular_Map"};
            }

            static const string Get_Field_Skybox_Specular_Map_Spelling(void){
                return string{"m_Skybox_Specular_Map"};
            }


            static const string Get_Field_Skybox_Specular_Map_Display_Name(void){
                return string{"Skybox_Specular_Map"};
            }

            static const void *const Get_Filed_Skybox_Specular_Map_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Global_Rendering>(Instance)->m_Skybox_Specular_Map);
            }

            static void Set_Field_Skybox_Specular_Map_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Global_Rendering>(Instance)->m_Skybox_Specular_Map=*static_cast<const SkyBox_Specular_Map*>(Value);
            }

            static const bool Is_Filed_Skybox_Specular_Map_CPPVector(void){
                return  false;
            }

            

            static const string Get_Field_BRDF_Map_Type_Spelling(void){
                return string{"std::string"};
            }

            static const string Get_Field_BRDF_Map_Spelling(void){
                return string{"m_BRDF_Map"};
            }


            static const string Get_Field_BRDF_Map_Display_Name(void){
                return string{"BRDF_Map"};
            }

            static const void *const Get_Filed_BRDF_Map_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Global_Rendering>(Instance)->m_BRDF_Map);
            }

            static void Set_Field_BRDF_Map_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Global_Rendering>(Instance)->m_BRDF_Map=*static_cast<const std::string*>(Value);
            }

            static const bool Is_Filed_BRDF_Map_CPPVector(void){
                return  false;
            }

            

            static const string Get_Field_Color_Grading_Map_Type_Spelling(void){
                return string{"std::string"};
            }

            static const string Get_Field_Color_Grading_Map_Spelling(void){
                return string{"m_Color_Grading_Map"};
            }


            static const string Get_Field_Color_Grading_Map_Display_Name(void){
                return string{"Color_Grading_Map"};
            }

            static const void *const Get_Filed_Color_Grading_Map_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Global_Rendering>(Instance)->m_Color_Grading_Map);
            }

            static void Set_Field_Color_Grading_Map_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Global_Rendering>(Instance)->m_Color_Grading_Map=*static_cast<const std::string*>(Value);
            }

            static const bool Is_Filed_Color_Grading_Map_CPPVector(void){
                return  false;
            }

            

            static const string Get_Field_Sky_Color_Type_Spelling(void){
                return string{"Color"};
            }

            static const string Get_Field_Sky_Color_Spelling(void){
                return string{"m_Sky_Color"};
            }


            static const string Get_Field_Sky_Color_Display_Name(void){
                return string{"Sky_Color"};
            }

            static const void *const Get_Filed_Sky_Color_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Global_Rendering>(Instance)->m_Sky_Color);
            }

            static void Set_Field_Sky_Color_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Global_Rendering>(Instance)->m_Sky_Color=*static_cast<const Color*>(Value);
            }

            static const bool Is_Filed_Sky_Color_CPPVector(void){
                return  false;
            }

            

            static const string Get_Field_Ambient_Light_Type_Spelling(void){
                return string{"Color"};
            }

            static const string Get_Field_Ambient_Light_Spelling(void){
                return string{"m_Ambient_Light"};
            }


            static const string Get_Field_Ambient_Light_Display_Name(void){
                return string{"Ambient_Light"};
            }

            static const void *const Get_Filed_Ambient_Light_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Global_Rendering>(Instance)->m_Ambient_Light);
            }

            static void Set_Field_Ambient_Light_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Global_Rendering>(Instance)->m_Ambient_Light=*static_cast<const Color*>(Value);
            }

            static const bool Is_Filed_Ambient_Light_CPPVector(void){
                return  false;
            }

            

            static const string Get_Field_Camera_Config_Type_Spelling(void){
                return string{"Camera_Config"};
            }

            static const string Get_Field_Camera_Config_Spelling(void){
                return string{"m_Camera_Config"};
            }


            static const string Get_Field_Camera_Config_Display_Name(void){
                return string{"Camera_Config"};
            }

            static const void *const Get_Filed_Camera_Config_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Global_Rendering>(Instance)->m_Camera_Config);
            }

            static void Set_Field_Camera_Config_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Global_Rendering>(Instance)->m_Camera_Config=*static_cast<const Camera_Config*>(Value);
            }

            static const bool Is_Filed_Camera_Config_CPPVector(void){
                return  false;
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
                    string{"m_Enable_FXAA"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Global_Rendering_Operator::Get_Field_Enable_FXAA_Type_Spelling,
                        Reflection_Global_Rendering_Operator::Get_Field_Enable_FXAA_Spelling,
                        Reflection_Global_Rendering_Operator::Get_Field_Enable_FXAA_Display_Name,
                        Reflection_Global_Rendering_Operator::Get_Filed_Enable_FXAA_Attribute,
                        Reflection_Global_Rendering_Operator::Set_Field_Enable_FXAA_Attribute,
                        Reflection_Global_Rendering_Operator::Is_Filed_Enable_FXAA_CPPVector
                    )
                );

                

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Skybox_Irradiance_Map"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Global_Rendering_Operator::Get_Field_Skybox_Irradiance_Map_Type_Spelling,
                        Reflection_Global_Rendering_Operator::Get_Field_Skybox_Irradiance_Map_Spelling,
                        Reflection_Global_Rendering_Operator::Get_Field_Skybox_Irradiance_Map_Display_Name,
                        Reflection_Global_Rendering_Operator::Get_Filed_Skybox_Irradiance_Map_Attribute,
                        Reflection_Global_Rendering_Operator::Set_Field_Skybox_Irradiance_Map_Attribute,
                        Reflection_Global_Rendering_Operator::Is_Filed_Skybox_Irradiance_Map_CPPVector
                    )
                );

                

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Skybox_Specular_Map"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Global_Rendering_Operator::Get_Field_Skybox_Specular_Map_Type_Spelling,
                        Reflection_Global_Rendering_Operator::Get_Field_Skybox_Specular_Map_Spelling,
                        Reflection_Global_Rendering_Operator::Get_Field_Skybox_Specular_Map_Display_Name,
                        Reflection_Global_Rendering_Operator::Get_Filed_Skybox_Specular_Map_Attribute,
                        Reflection_Global_Rendering_Operator::Set_Field_Skybox_Specular_Map_Attribute,
                        Reflection_Global_Rendering_Operator::Is_Filed_Skybox_Specular_Map_CPPVector
                    )
                );

                

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_BRDF_Map"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Global_Rendering_Operator::Get_Field_BRDF_Map_Type_Spelling,
                        Reflection_Global_Rendering_Operator::Get_Field_BRDF_Map_Spelling,
                        Reflection_Global_Rendering_Operator::Get_Field_BRDF_Map_Display_Name,
                        Reflection_Global_Rendering_Operator::Get_Filed_BRDF_Map_Attribute,
                        Reflection_Global_Rendering_Operator::Set_Field_BRDF_Map_Attribute,
                        Reflection_Global_Rendering_Operator::Is_Filed_BRDF_Map_CPPVector
                    )
                );

                

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Color_Grading_Map"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Global_Rendering_Operator::Get_Field_Color_Grading_Map_Type_Spelling,
                        Reflection_Global_Rendering_Operator::Get_Field_Color_Grading_Map_Spelling,
                        Reflection_Global_Rendering_Operator::Get_Field_Color_Grading_Map_Display_Name,
                        Reflection_Global_Rendering_Operator::Get_Filed_Color_Grading_Map_Attribute,
                        Reflection_Global_Rendering_Operator::Set_Field_Color_Grading_Map_Attribute,
                        Reflection_Global_Rendering_Operator::Is_Filed_Color_Grading_Map_CPPVector
                    )
                );

                

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Sky_Color"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Global_Rendering_Operator::Get_Field_Sky_Color_Type_Spelling,
                        Reflection_Global_Rendering_Operator::Get_Field_Sky_Color_Spelling,
                        Reflection_Global_Rendering_Operator::Get_Field_Sky_Color_Display_Name,
                        Reflection_Global_Rendering_Operator::Get_Filed_Sky_Color_Attribute,
                        Reflection_Global_Rendering_Operator::Set_Field_Sky_Color_Attribute,
                        Reflection_Global_Rendering_Operator::Is_Filed_Sky_Color_CPPVector
                    )
                );

                

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Ambient_Light"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Global_Rendering_Operator::Get_Field_Ambient_Light_Type_Spelling,
                        Reflection_Global_Rendering_Operator::Get_Field_Ambient_Light_Spelling,
                        Reflection_Global_Rendering_Operator::Get_Field_Ambient_Light_Display_Name,
                        Reflection_Global_Rendering_Operator::Get_Filed_Ambient_Light_Attribute,
                        Reflection_Global_Rendering_Operator::Set_Field_Ambient_Light_Attribute,
                        Reflection_Global_Rendering_Operator::Is_Filed_Ambient_Light_CPPVector
                    )
                );

                

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Camera_Config"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Global_Rendering_Operator::Get_Field_Camera_Config_Type_Spelling,
                        Reflection_Global_Rendering_Operator::Get_Field_Camera_Config_Spelling,
                        Reflection_Global_Rendering_Operator::Get_Field_Camera_Config_Display_Name,
                        Reflection_Global_Rendering_Operator::Get_Filed_Camera_Config_Attribute,
                        Reflection_Global_Rendering_Operator::Set_Field_Camera_Config_Attribute,
                        Reflection_Global_Rendering_Operator::Is_Filed_Camera_Config_CPPVector
                    )
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


