#pragma once

#include<string>
#include<vector>
#include<memory>
#include<cstddef>

#include "meta/Reflection/Reflection_Instance.h"
#include "meta/Reflection/Reflection_Register.h"

#include "D:/Amy_Engine/resource/include/components/material/Materia.h"

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


    class Reflection_Material_Operator {
    public:

        static const string Get_Class_Material_Spelling(void){
            return string{"Material"};
        }

        static const string Get_Class_Displaying_Name(void){
            return string{"Material"};            
        }

            static const vector<Reflection_Instance<void>> Get_Base_Class_Material_Reflection_Instance_List(shared_ptr<void> Instance){
                vector<Reflection_Instance<void>> Table;

                    

                return Table;
            }

            static const string Get_Field_Emissive_Texture_File_Path_Type_Spelling(void){
                return string{"path"};
            }

            static const string Get_Field_Emissive_Texture_File_Path_Spelling(void){
                return string{"m_Emissive_Texture_File_Path"};
            }


            static const string Get_Field_Emissive_Texture_File_Path_Display_Name(void){
                return string{"Emissive_Texture_File_Path"};
            }

            static const void *const Get_Filed_Emissive_Texture_File_Path_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Material>(Instance)->m_Emissive_Texture_File_Path);
            }

            static void Set_Field_Emissive_Texture_File_Path_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Material>(Instance)->m_Emissive_Texture_File_Path=*static_cast<const path*>(Value);
            }

            static const bool Is_Filed_Emissive_Texture_File_Path_CPPVector(void){
                return  false;
            }

            


            static void TypeWrapper_Rigster(void){
                shared_ptr<Class_Func_Tuple> Temp_Class_Func_Tuple{nullptr};
                shared_ptr<Class_Base_Class_Tuple> Temp_Class_Base_Class_Tuple{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Field_Func_Tuple>>> Temp_Class_Field_Func_Tuple_Map{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Filed_CPPVector_Func_Tuple>>> Temp_Class_Filed_CPPVector_Func_Tuple_Map{nullptr};

                Temp_Class_Func_Tuple = make_shared<Class_Func_Tuple>(
                    Reflection_Material_Operator::Get_Class_Material_Spelling,
                    Reflection_Material_Operator::Get_Class_Displaying_Name
                );

                Temp_Class_Base_Class_Tuple = make_shared<Class_Base_Class_Tuple>(
                    Reflection_Material_Operator::Get_Base_Class_Material_Reflection_Instance_List
                );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Emissive_Texture_File_Path"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Material_Operator::Get_Field_Emissive_Texture_File_Path_Type_Spelling,
                        Reflection_Material_Operator::Get_Field_Emissive_Texture_File_Path_Spelling,
                        Reflection_Material_Operator::Get_Field_Emissive_Texture_File_Path_Display_Name,
                        Reflection_Material_Operator::Get_Filed_Emissive_Texture_File_Path_Attribute,
                        Reflection_Material_Operator::Set_Field_Emissive_Texture_File_Path_Attribute,
                        Reflection_Material_Operator::Is_Filed_Emissive_Texture_File_Path_CPPVector
                    )
                );

                

                
            Reflection_Register::Get_Instance().Register_Class(string{"Material"},Temp_Class_Func_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Base_Class(string{"Material"},Temp_Class_Base_Class_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Filed(string{"Material"},Temp_Class_Field_Func_Tuple_Map);
            Reflection_Register::Get_Instance().Register_Class_Field_CPPVector(string{"Material"},Temp_Class_Filed_CPPVector_Func_Tuple_Map);
        }

    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection


