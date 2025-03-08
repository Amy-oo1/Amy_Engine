#pragma once

#include<string>
#include<vector>
#include<memory>
#include<cstddef>

#include "meta/Reflection/Reflection_Instance.h"
#include "meta/Reflection/Reflection_Register.h"

#include "D:/Amy_Engine/resource/include/components/mesh/mesh.h"

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


    class Reflection_Mesh_Sub_Operator {
    public:

        static const string Get_Class_Mesh_Sub_Spelling(void){
            return string{"Mesh_Sub"};
        }

        static const string Get_Class_Displaying_Name(void){
            return string{"Mesh_Sub"};            
        }

            static const vector<Reflection_Instance<void>> Get_Base_Class_Mesh_Sub_Reflection_Instance_List(shared_ptr<void> Instance){
                vector<Reflection_Instance<void>> Table;

                    

                return Table;
            }

            static const string Get_Field_Material_Type_Spelling(void){
                return string{"string"};
            }

            static const string Get_Field_Material_Spelling(void){
                return string{"m_Material"};
            }


            static const string Get_Field_Material_Display_Name(void){
                return string{"Material"};
            }

            static const void *const Get_Filed_Material_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Mesh_Sub>(Instance)->m_Material);
            }

            static void Set_Field_Material_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Mesh_Sub>(Instance)->m_Material=*static_cast<const string*>(Value);
            }

            static const bool Is_Filed_Material_CPPVector(void){
                return  false;
            }

            


            static void TypeWrapper_Rigster(void){
                shared_ptr<Class_Func_Tuple> Temp_Class_Func_Tuple{nullptr};
                shared_ptr<Class_Base_Class_Tuple> Temp_Class_Base_Class_Tuple{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Field_Func_Tuple>>> Temp_Class_Field_Func_Tuple_Map{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Filed_CPPVector_Func_Tuple>>> Temp_Class_Filed_CPPVector_Func_Tuple_Map{nullptr};

                Temp_Class_Func_Tuple = make_shared<Class_Func_Tuple>(
                    Reflection_Mesh_Sub_Operator::Get_Class_Mesh_Sub_Spelling,
                    Reflection_Mesh_Sub_Operator::Get_Class_Displaying_Name
                );

                Temp_Class_Base_Class_Tuple = make_shared<Class_Base_Class_Tuple>(
                    Reflection_Mesh_Sub_Operator::Get_Base_Class_Mesh_Sub_Reflection_Instance_List
                );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Material"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Mesh_Sub_Operator::Get_Field_Material_Type_Spelling,
                        Reflection_Mesh_Sub_Operator::Get_Field_Material_Spelling,
                        Reflection_Mesh_Sub_Operator::Get_Field_Material_Display_Name,
                        Reflection_Mesh_Sub_Operator::Get_Filed_Material_Attribute,
                        Reflection_Mesh_Sub_Operator::Set_Field_Material_Attribute,
                        Reflection_Mesh_Sub_Operator::Is_Filed_Material_CPPVector
                    )
                );

                

                
            Reflection_Register::Get_Instance().Register_Class(string{"Mesh_Sub"},Temp_Class_Func_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Base_Class(string{"Mesh_Sub"},Temp_Class_Base_Class_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Filed(string{"Mesh_Sub"},Temp_Class_Field_Func_Tuple_Map);
            Reflection_Register::Get_Instance().Register_Class_Field_CPPVector(string{"Mesh_Sub"},Temp_Class_Filed_CPPVector_Func_Tuple_Map);
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


    class Reflection_Mesh_Operator {
    public:

        static const string Get_Class_Mesh_Spelling(void){
            return string{"Mesh"};
        }

        static const string Get_Class_Displaying_Name(void){
            return string{"Mesh"};            
        }

            static const vector<Reflection_Instance<void>> Get_Base_Class_Mesh_Reflection_Instance_List(shared_ptr<void> Instance){
                vector<Reflection_Instance<void>> Table;

                    

                return Table;
            }

            static const string Get_Field_Meshes_Type_Spelling(void){
                return string{"vector<Mesh_Sub>"};
            }

            static const string Get_Field_Meshes_Spelling(void){
                return string{"m_Meshes"};
            }


            static const string Get_Field_Meshes_Display_Name(void){
                return string{"Meshes"};
            }

            static const void *const Get_Filed_Meshes_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Mesh>(Instance)->m_Meshes);
            }

            static void Set_Field_Meshes_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Mesh>(Instance)->m_Meshes=*static_cast<const vector<Mesh_Sub>*>(Value);
            }

            static const bool Is_Filed_Meshes_CPPVector(void){
                return  !  false;
            }

                static const string Get_Field_Meshes_CPPVector_Element_Type_Spelling(void){
                    return string {"m_Meshes"};
                }

                static const size_t Get_Field_Meshes_CPPVector_Capacity(shared_ptr<void> Instance){
                    return static_pointer_cast<Mesh>(Instance)->m_Meshes.capacity();
                }

                static const size_t Get_Field_Meshes_CPPVector_Size(shared_ptr<void> Instance){
                    return static_pointer_cast<Mesh>(Instance)->m_Meshes.size();
                }

                static const void *Get_Field_Meshes_CPPVector_Element(shared_ptr<void> Instance, size_t Index){
                    return static_cast<const void*>(&static_pointer_cast<Mesh>(Instance)->m_Meshes[Index]);
                }

                static void Set_Field_Meshes_CPPVector_Element(shared_ptr<void> Instance, size_t Index,const void* Value){
                    static_pointer_cast<Mesh>(Instance)->m_Meshes[Index]=*static_cast<const Mesh_Sub*>(Value);
                }


            static void TypeWrapper_Rigster(void){
                shared_ptr<Class_Func_Tuple> Temp_Class_Func_Tuple{nullptr};
                shared_ptr<Class_Base_Class_Tuple> Temp_Class_Base_Class_Tuple{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Field_Func_Tuple>>> Temp_Class_Field_Func_Tuple_Map{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Filed_CPPVector_Func_Tuple>>> Temp_Class_Filed_CPPVector_Func_Tuple_Map{nullptr};

                Temp_Class_Func_Tuple = make_shared<Class_Func_Tuple>(
                    Reflection_Mesh_Operator::Get_Class_Mesh_Spelling,
                    Reflection_Mesh_Operator::Get_Class_Displaying_Name
                );

                Temp_Class_Base_Class_Tuple = make_shared<Class_Base_Class_Tuple>(
                    Reflection_Mesh_Operator::Get_Base_Class_Mesh_Reflection_Instance_List
                );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Meshes"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Mesh_Operator::Get_Field_Meshes_Type_Spelling,
                        Reflection_Mesh_Operator::Get_Field_Meshes_Spelling,
                        Reflection_Mesh_Operator::Get_Field_Meshes_Display_Name,
                        Reflection_Mesh_Operator::Get_Filed_Meshes_Attribute,
                        Reflection_Mesh_Operator::Set_Field_Meshes_Attribute,
                        Reflection_Mesh_Operator::Is_Filed_Meshes_CPPVector
                    )
                );

                    Temp_Class_Filed_CPPVector_Func_Tuple_Map->emplace(
                    string{"m_Meshes"},
                        make_shared<Class_Filed_CPPVector_Func_Tuple>( 
                            Reflection_Mesh_Operator::Get_Field_Meshes_CPPVector_Element_Type_Spelling,
                            Reflection_Mesh_Operator::Get_Field_Meshes_CPPVector_Capacity,
                            Reflection_Mesh_Operator::Get_Field_Meshes_CPPVector_Size,
                            Reflection_Mesh_Operator::Get_Field_Meshes_CPPVector_Element,
                            Reflection_Mesh_Operator::Set_Field_Meshes_CPPVector_Element
                        )
                    );

                
            Reflection_Register::Get_Instance().Register_Class(string{"Mesh"},Temp_Class_Func_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Base_Class(string{"Mesh"},Temp_Class_Base_Class_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Filed(string{"Mesh"},Temp_Class_Field_Func_Tuple_Map);
            Reflection_Register::Get_Instance().Register_Class_Field_CPPVector(string{"Mesh"},Temp_Class_Filed_CPPVector_Func_Tuple_Map);
        }

    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection


