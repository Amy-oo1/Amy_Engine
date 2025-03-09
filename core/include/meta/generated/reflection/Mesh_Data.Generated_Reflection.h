#pragma once

#include<string>
#include<vector>
#include<memory>
#include<cstddef>

#include "meta/Reflection/Reflection_Instance.h"
#include "meta/Reflection/Reflection_Register.h"

#include "D:/Amy_Engine/resource/include/components/mesh/Mesh_Data.h"

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


    class Reflection_Mesh_Vertex_Operator {
    public:

        static const string Get_Class_Mesh_Vertex_Spelling(void){
            return string{"Mesh_Vertex"};
        }

        static const string Get_Class_Displaying_Name(void){
            return string{"Mesh_Vertex"};            
        }

            static const vector<Reflection_Instance<void>> Get_Base_Class_Mesh_Vertex_Reflection_Instance_List(shared_ptr<void> Instance){
                vector<Reflection_Instance<void>> Table;

                    

                return Table;
            }

            static const string Get_Field_Texture_Coordinate_Type_Spelling(void){
                return string{"Vector2"};
            }

            static const string Get_Field_Texture_Coordinate_Spelling(void){
                return string{"m_Texture_Coordinate"};
            }


            static const string Get_Field_Texture_Coordinate_Display_Name(void){
                return string{"Texture_Coordinate"};
            }

            static const void *const Get_Filed_Texture_Coordinate_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Mesh_Vertex>(Instance)->m_Texture_Coordinate);
            }

            static void Set_Field_Texture_Coordinate_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Mesh_Vertex>(Instance)->m_Texture_Coordinate=*static_cast<const Vector2*>(Value);
            }

            static const bool Is_Filed_Texture_Coordinate_CPPVector(void){
                return  false;
            }

            


            static void TypeWrapper_Rigster(void){
                shared_ptr<Class_Func_Tuple> Temp_Class_Func_Tuple{nullptr};
                shared_ptr<Class_Base_Class_Tuple> Temp_Class_Base_Class_Tuple{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Field_Func_Tuple>>> Temp_Class_Field_Func_Tuple_Map{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Filed_CPPVector_Func_Tuple>>> Temp_Class_Filed_CPPVector_Func_Tuple_Map{nullptr};

                Temp_Class_Func_Tuple = make_shared<Class_Func_Tuple>(
                    Reflection_Mesh_Vertex_Operator::Get_Class_Mesh_Vertex_Spelling,
                    Reflection_Mesh_Vertex_Operator::Get_Class_Displaying_Name
                );

                Temp_Class_Base_Class_Tuple = make_shared<Class_Base_Class_Tuple>(
                    Reflection_Mesh_Vertex_Operator::Get_Base_Class_Mesh_Vertex_Reflection_Instance_List
                );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Texture_Coordinate"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Mesh_Vertex_Operator::Get_Field_Texture_Coordinate_Type_Spelling,
                        Reflection_Mesh_Vertex_Operator::Get_Field_Texture_Coordinate_Spelling,
                        Reflection_Mesh_Vertex_Operator::Get_Field_Texture_Coordinate_Display_Name,
                        Reflection_Mesh_Vertex_Operator::Get_Filed_Texture_Coordinate_Attribute,
                        Reflection_Mesh_Vertex_Operator::Set_Field_Texture_Coordinate_Attribute,
                        Reflection_Mesh_Vertex_Operator::Is_Filed_Texture_Coordinate_CPPVector
                    )
                );

                

                
            Reflection_Register::Get_Instance().Register_Class(string{"Mesh_Vertex"},Temp_Class_Func_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Base_Class(string{"Mesh_Vertex"},Temp_Class_Base_Class_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Filed(string{"Mesh_Vertex"},Temp_Class_Field_Func_Tuple_Map);
            Reflection_Register::Get_Instance().Register_Class_Field_CPPVector(string{"Mesh_Vertex"},Temp_Class_Filed_CPPVector_Func_Tuple_Map);
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


    class Reflection_Meah_SkeletonBinding_Operator {
    public:

        static const string Get_Class_Meah_SkeletonBinding_Spelling(void){
            return string{"Meah_SkeletonBinding"};
        }

        static const string Get_Class_Displaying_Name(void){
            return string{"Meah_SkeletonBinding"};            
        }

            static const vector<Reflection_Instance<void>> Get_Base_Class_Meah_SkeletonBinding_Reflection_Instance_List(shared_ptr<void> Instance){
                vector<Reflection_Instance<void>> Table;

                    

                return Table;
            }

            static const string Get_Field_Weights_Type_Spelling(void){
                return string{"Vector4"};
            }

            static const string Get_Field_Weights_Spelling(void){
                return string{"m_Weights"};
            }


            static const string Get_Field_Weights_Display_Name(void){
                return string{"Weights"};
            }

            static const void *const Get_Filed_Weights_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Meah_SkeletonBinding>(Instance)->m_Weights);
            }

            static void Set_Field_Weights_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Meah_SkeletonBinding>(Instance)->m_Weights=*static_cast<const Vector4*>(Value);
            }

            static const bool Is_Filed_Weights_CPPVector(void){
                return  false;
            }

                static const string Get_Field_Weights_CPPVector_Element_Type_Spelling(void){
                    return string {"m_Weights"};
                }

                static const size_t Get_Field_Weights_CPPVector_Capacity(shared_ptr<void> Instance){
                    return static_pointer_cast<Meah_SkeletonBinding>(Instance)->m_Weights.capacity();
                }

                static const size_t Get_Field_Weights_CPPVector_Size(shared_ptr<void> Instance){
                    return static_pointer_cast<Meah_SkeletonBinding>(Instance)->m_Weights.size();
                }

                static const void *Get_Field_Weights_CPPVector_Element(shared_ptr<void> Instance, size_t Index){
                    return static_cast<const void*>(&static_pointer_cast<Meah_SkeletonBinding>(Instance)->m_Weights[Index]);
                }

                static void Set_Field_Weights_CPPVector_Element(shared_ptr<void> Instance, size_t Index,const void* Value){
                    static_pointer_cast<Meah_SkeletonBinding>(Instance)->m_Weights[Index]=*static_cast<const int*>(Value);
                }


            static void TypeWrapper_Rigster(void){
                shared_ptr<Class_Func_Tuple> Temp_Class_Func_Tuple{nullptr};
                shared_ptr<Class_Base_Class_Tuple> Temp_Class_Base_Class_Tuple{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Field_Func_Tuple>>> Temp_Class_Field_Func_Tuple_Map{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Filed_CPPVector_Func_Tuple>>> Temp_Class_Filed_CPPVector_Func_Tuple_Map{nullptr};

                Temp_Class_Func_Tuple = make_shared<Class_Func_Tuple>(
                    Reflection_Meah_SkeletonBinding_Operator::Get_Class_Meah_SkeletonBinding_Spelling,
                    Reflection_Meah_SkeletonBinding_Operator::Get_Class_Displaying_Name
                );

                Temp_Class_Base_Class_Tuple = make_shared<Class_Base_Class_Tuple>(
                    Reflection_Meah_SkeletonBinding_Operator::Get_Base_Class_Meah_SkeletonBinding_Reflection_Instance_List
                );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Weights"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Meah_SkeletonBinding_Operator::Get_Field_Weights_Type_Spelling,
                        Reflection_Meah_SkeletonBinding_Operator::Get_Field_Weights_Spelling,
                        Reflection_Meah_SkeletonBinding_Operator::Get_Field_Weights_Display_Name,
                        Reflection_Meah_SkeletonBinding_Operator::Get_Filed_Weights_Attribute,
                        Reflection_Meah_SkeletonBinding_Operator::Set_Field_Weights_Attribute,
                        Reflection_Meah_SkeletonBinding_Operator::Is_Filed_Weights_CPPVector
                    )
                );

                    Temp_Class_Filed_CPPVector_Func_Tuple_Map->emplace(
                    string{"m_Weights"},
                        make_shared<Class_Filed_CPPVector_Func_Tuple>( 
                            Reflection_Meah_SkeletonBinding_Operator::Get_Field_Weights_CPPVector_Element_Type_Spelling,
                            Reflection_Meah_SkeletonBinding_Operator::Get_Field_Weights_CPPVector_Capacity,
                            Reflection_Meah_SkeletonBinding_Operator::Get_Field_Weights_CPPVector_Size,
                            Reflection_Meah_SkeletonBinding_Operator::Get_Field_Weights_CPPVector_Element,
                            Reflection_Meah_SkeletonBinding_Operator::Set_Field_Weights_CPPVector_Element
                        )
                    );

                
            Reflection_Register::Get_Instance().Register_Class(string{"Meah_SkeletonBinding"},Temp_Class_Func_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Base_Class(string{"Meah_SkeletonBinding"},Temp_Class_Base_Class_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Filed(string{"Meah_SkeletonBinding"},Temp_Class_Field_Func_Tuple_Map);
            Reflection_Register::Get_Instance().Register_Class_Field_CPPVector(string{"Meah_SkeletonBinding"},Temp_Class_Filed_CPPVector_Func_Tuple_Map);
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


    class Reflection_Mesh_Data_Operator {
    public:

        static const string Get_Class_Mesh_Data_Spelling(void){
            return string{"Mesh_Data"};
        }

        static const string Get_Class_Displaying_Name(void){
            return string{"Mesh_Data"};            
        }

            static const vector<Reflection_Instance<void>> Get_Base_Class_Mesh_Data_Reflection_Instance_List(shared_ptr<void> Instance){
                vector<Reflection_Instance<void>> Table;

                    

                return Table;
            }

            static const string Get_Field_SkeletonBindings_Type_Spelling(void){
                return string{"vector<Meah_SkeletonBinding>"};
            }

            static const string Get_Field_SkeletonBindings_Spelling(void){
                return string{"m_SkeletonBindings"};
            }


            static const string Get_Field_SkeletonBindings_Display_Name(void){
                return string{"SkeletonBindings"};
            }

            static const void *const Get_Filed_SkeletonBindings_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Mesh_Data>(Instance)->m_SkeletonBindings);
            }

            static void Set_Field_SkeletonBindings_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Mesh_Data>(Instance)->m_SkeletonBindings=*static_cast<const vector<Meah_SkeletonBinding>*>(Value);
            }

            static const bool Is_Filed_SkeletonBindings_CPPVector(void){
                return  !  false;
            }

                static const string Get_Field_SkeletonBindings_CPPVector_Element_Type_Spelling(void){
                    return string {"m_SkeletonBindings"};
                }

                static const size_t Get_Field_SkeletonBindings_CPPVector_Capacity(shared_ptr<void> Instance){
                    return static_pointer_cast<Mesh_Data>(Instance)->m_SkeletonBindings.capacity();
                }

                static const size_t Get_Field_SkeletonBindings_CPPVector_Size(shared_ptr<void> Instance){
                    return static_pointer_cast<Mesh_Data>(Instance)->m_SkeletonBindings.size();
                }

                static const void *Get_Field_SkeletonBindings_CPPVector_Element(shared_ptr<void> Instance, size_t Index){
                    return static_cast<const void*>(&static_pointer_cast<Mesh_Data>(Instance)->m_SkeletonBindings[Index]);
                }

                static void Set_Field_SkeletonBindings_CPPVector_Element(shared_ptr<void> Instance, size_t Index,const void* Value){
                    static_pointer_cast<Mesh_Data>(Instance)->m_SkeletonBindings[Index]=*static_cast<const Meah_SkeletonBinding*>(Value);
                }


            static void TypeWrapper_Rigster(void){
                shared_ptr<Class_Func_Tuple> Temp_Class_Func_Tuple{nullptr};
                shared_ptr<Class_Base_Class_Tuple> Temp_Class_Base_Class_Tuple{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Field_Func_Tuple>>> Temp_Class_Field_Func_Tuple_Map{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Filed_CPPVector_Func_Tuple>>> Temp_Class_Filed_CPPVector_Func_Tuple_Map{nullptr};

                Temp_Class_Func_Tuple = make_shared<Class_Func_Tuple>(
                    Reflection_Mesh_Data_Operator::Get_Class_Mesh_Data_Spelling,
                    Reflection_Mesh_Data_Operator::Get_Class_Displaying_Name
                );

                Temp_Class_Base_Class_Tuple = make_shared<Class_Base_Class_Tuple>(
                    Reflection_Mesh_Data_Operator::Get_Base_Class_Mesh_Data_Reflection_Instance_List
                );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_SkeletonBindings"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Mesh_Data_Operator::Get_Field_SkeletonBindings_Type_Spelling,
                        Reflection_Mesh_Data_Operator::Get_Field_SkeletonBindings_Spelling,
                        Reflection_Mesh_Data_Operator::Get_Field_SkeletonBindings_Display_Name,
                        Reflection_Mesh_Data_Operator::Get_Filed_SkeletonBindings_Attribute,
                        Reflection_Mesh_Data_Operator::Set_Field_SkeletonBindings_Attribute,
                        Reflection_Mesh_Data_Operator::Is_Filed_SkeletonBindings_CPPVector
                    )
                );

                    Temp_Class_Filed_CPPVector_Func_Tuple_Map->emplace(
                    string{"m_SkeletonBindings"},
                        make_shared<Class_Filed_CPPVector_Func_Tuple>( 
                            Reflection_Mesh_Data_Operator::Get_Field_SkeletonBindings_CPPVector_Element_Type_Spelling,
                            Reflection_Mesh_Data_Operator::Get_Field_SkeletonBindings_CPPVector_Capacity,
                            Reflection_Mesh_Data_Operator::Get_Field_SkeletonBindings_CPPVector_Size,
                            Reflection_Mesh_Data_Operator::Get_Field_SkeletonBindings_CPPVector_Element,
                            Reflection_Mesh_Data_Operator::Set_Field_SkeletonBindings_CPPVector_Element
                        )
                    );

                
            Reflection_Register::Get_Instance().Register_Class(string{"Mesh_Data"},Temp_Class_Func_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Base_Class(string{"Mesh_Data"},Temp_Class_Base_Class_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Filed(string{"Mesh_Data"},Temp_Class_Field_Func_Tuple_Map);
            Reflection_Register::Get_Instance().Register_Class_Field_CPPVector(string{"Mesh_Data"},Temp_Class_Filed_CPPVector_Func_Tuple_Map);
        }

    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection


