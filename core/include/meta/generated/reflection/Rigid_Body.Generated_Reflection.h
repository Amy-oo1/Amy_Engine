#pragma once

#include<string>
#include<vector>
#include<memory>
#include<cstddef>

#include "meta/Reflection/Reflection_Instance.h"
#include "meta/Reflection/Reflection_Register.h"

#include "D:/Amy_Engine/resource/include/components/rigid_body/Rigid_Body.h"

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


    class Reflection_Rigid_Body_Shape_Operator {
    public:

        static const string Get_Class_Rigid_Body_Shape_Spelling(void){
            return string{"Rigid_Body_Shape"};
        }

        static const string Get_Class_Displaying_Name(void){
            return string{"Rigid_Body_Shape"};            
        }

            static const vector<Reflection_Instance<void>> Get_Base_Class_Rigid_Body_Shape_Reflection_Instance_List(shared_ptr<void> Instance){
                vector<Reflection_Instance<void>> Table;

                    

                return Table;
            }

            static const string Get_Field_Global_Transform_Type_Spelling(void){
                return string{"Orthogonal_Transform"};
            }

            static const string Get_Field_Global_Transform_Spelling(void){
                return string{"m_Global_Transform"};
            }


            static const string Get_Field_Global_Transform_Display_Name(void){
                return string{"Global_Transform"};
            }

            static const void *const Get_Filed_Global_Transform_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Rigid_Body_Shape>(Instance)->m_Global_Transform);
            }

            static void Set_Field_Global_Transform_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Rigid_Body_Shape>(Instance)->m_Global_Transform=*static_cast<const Orthogonal_Transform*>(Value);
            }

            static const bool Is_Filed_Global_Transform_CPPVector(void){
                return  false;
            }

            

            static const string Get_Field_Local_Transform_Type_Spelling(void){
                return string{"Orthogonal_Transform"};
            }

            static const string Get_Field_Local_Transform_Spelling(void){
                return string{"m_Local_Transform"};
            }


            static const string Get_Field_Local_Transform_Display_Name(void){
                return string{"Local_Transform"};
            }

            static const void *const Get_Filed_Local_Transform_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Rigid_Body_Shape>(Instance)->m_Local_Transform);
            }

            static void Set_Field_Local_Transform_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Rigid_Body_Shape>(Instance)->m_Local_Transform=*static_cast<const Orthogonal_Transform*>(Value);
            }

            static const bool Is_Filed_Local_Transform_CPPVector(void){
                return  false;
            }

            

            static const string Get_Field_Bounding_Box_Type_Spelling(void){
                return string{"AxisAligned_Bounding_Box"};
            }

            static const string Get_Field_Bounding_Box_Spelling(void){
                return string{"m_Bounding_Box"};
            }


            static const string Get_Field_Bounding_Box_Display_Name(void){
                return string{"Bounding_Box"};
            }

            static const void *const Get_Filed_Bounding_Box_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Rigid_Body_Shape>(Instance)->m_Bounding_Box);
            }

            static void Set_Field_Bounding_Box_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Rigid_Body_Shape>(Instance)->m_Bounding_Box=*static_cast<const AxisAligned_Bounding_Box*>(Value);
            }

            static const bool Is_Filed_Bounding_Box_CPPVector(void){
                return  false;
            }

            

            static const string Get_Field_Type_Type_Spelling(void){
                return string{"Rigid_Body_Type"};
            }

            static const string Get_Field_Type_Spelling(void){
                return string{"m_Type"};
            }


            static const string Get_Field_Type_Display_Name(void){
                return string{"Type"};
            }

            static const void *const Get_Filed_Type_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Rigid_Body_Shape>(Instance)->m_Type);
            }

            static void Set_Field_Type_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Rigid_Body_Shape>(Instance)->m_Type=*static_cast<const Rigid_Body_Type*>(Value);
            }

            static const bool Is_Filed_Type_CPPVector(void){
                return  false;
            }

            

            static const string Get_Field_Instance_Type_Spelling(void){
                return string{"Reflection_Instance<Geometry_Base>"};
            }

            static const string Get_Field_Instance_Spelling(void){
                return string{"m_Instance"};
            }


            static const string Get_Field_Instance_Display_Name(void){
                return string{"Instance"};
            }

            static const void *const Get_Filed_Instance_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Rigid_Body_Shape>(Instance)->m_Instance);
            }

            static void Set_Field_Instance_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Rigid_Body_Shape>(Instance)->m_Instance=*static_cast<const Reflection_Instance<Geometry_Base>*>(Value);
            }

            static const bool Is_Filed_Instance_CPPVector(void){
                return  false;
            }

            


            static void TypeWrapper_Rigster(void){
                shared_ptr<Class_Func_Tuple> Temp_Class_Func_Tuple{nullptr};
                shared_ptr<Class_Base_Class_Tuple> Temp_Class_Base_Class_Tuple{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Field_Func_Tuple>>> Temp_Class_Field_Func_Tuple_Map{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Filed_CPPVector_Func_Tuple>>> Temp_Class_Filed_CPPVector_Func_Tuple_Map{nullptr};

                Temp_Class_Func_Tuple = make_shared<Class_Func_Tuple>(
                    Reflection_Rigid_Body_Shape_Operator::Get_Class_Rigid_Body_Shape_Spelling,
                    Reflection_Rigid_Body_Shape_Operator::Get_Class_Displaying_Name
                );

                Temp_Class_Base_Class_Tuple = make_shared<Class_Base_Class_Tuple>(
                    Reflection_Rigid_Body_Shape_Operator::Get_Base_Class_Rigid_Body_Shape_Reflection_Instance_List
                );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Global_Transform"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Rigid_Body_Shape_Operator::Get_Field_Global_Transform_Type_Spelling,
                        Reflection_Rigid_Body_Shape_Operator::Get_Field_Global_Transform_Spelling,
                        Reflection_Rigid_Body_Shape_Operator::Get_Field_Global_Transform_Display_Name,
                        Reflection_Rigid_Body_Shape_Operator::Get_Filed_Global_Transform_Attribute,
                        Reflection_Rigid_Body_Shape_Operator::Set_Field_Global_Transform_Attribute,
                        Reflection_Rigid_Body_Shape_Operator::Is_Filed_Global_Transform_CPPVector
                    )
                );

                

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Local_Transform"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Rigid_Body_Shape_Operator::Get_Field_Local_Transform_Type_Spelling,
                        Reflection_Rigid_Body_Shape_Operator::Get_Field_Local_Transform_Spelling,
                        Reflection_Rigid_Body_Shape_Operator::Get_Field_Local_Transform_Display_Name,
                        Reflection_Rigid_Body_Shape_Operator::Get_Filed_Local_Transform_Attribute,
                        Reflection_Rigid_Body_Shape_Operator::Set_Field_Local_Transform_Attribute,
                        Reflection_Rigid_Body_Shape_Operator::Is_Filed_Local_Transform_CPPVector
                    )
                );

                

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Bounding_Box"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Rigid_Body_Shape_Operator::Get_Field_Bounding_Box_Type_Spelling,
                        Reflection_Rigid_Body_Shape_Operator::Get_Field_Bounding_Box_Spelling,
                        Reflection_Rigid_Body_Shape_Operator::Get_Field_Bounding_Box_Display_Name,
                        Reflection_Rigid_Body_Shape_Operator::Get_Filed_Bounding_Box_Attribute,
                        Reflection_Rigid_Body_Shape_Operator::Set_Field_Bounding_Box_Attribute,
                        Reflection_Rigid_Body_Shape_Operator::Is_Filed_Bounding_Box_CPPVector
                    )
                );

                

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Type"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Rigid_Body_Shape_Operator::Get_Field_Type_Type_Spelling,
                        Reflection_Rigid_Body_Shape_Operator::Get_Field_Type_Spelling,
                        Reflection_Rigid_Body_Shape_Operator::Get_Field_Type_Display_Name,
                        Reflection_Rigid_Body_Shape_Operator::Get_Filed_Type_Attribute,
                        Reflection_Rigid_Body_Shape_Operator::Set_Field_Type_Attribute,
                        Reflection_Rigid_Body_Shape_Operator::Is_Filed_Type_CPPVector
                    )
                );

                

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Instance"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Rigid_Body_Shape_Operator::Get_Field_Instance_Type_Spelling,
                        Reflection_Rigid_Body_Shape_Operator::Get_Field_Instance_Spelling,
                        Reflection_Rigid_Body_Shape_Operator::Get_Field_Instance_Display_Name,
                        Reflection_Rigid_Body_Shape_Operator::Get_Filed_Instance_Attribute,
                        Reflection_Rigid_Body_Shape_Operator::Set_Field_Instance_Attribute,
                        Reflection_Rigid_Body_Shape_Operator::Is_Filed_Instance_CPPVector
                    )
                );

                

                
            Reflection_Register::Get_Instance().Register_Class(string{"Rigid_Body_Shape"},Temp_Class_Func_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Base_Class(string{"Rigid_Body_Shape"},Temp_Class_Base_Class_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Filed(string{"Rigid_Body_Shape"},Temp_Class_Field_Func_Tuple_Map);
            Reflection_Register::Get_Instance().Register_Class_Field_CPPVector(string{"Rigid_Body_Shape"},Temp_Class_Filed_CPPVector_Func_Tuple_Map);
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


    class Reflection_Rigid_Body_Operator {
    public:

        static const string Get_Class_Rigid_Body_Spelling(void){
            return string{"Rigid_Body"};
        }

        static const string Get_Class_Displaying_Name(void){
            return string{"Rigid_Body"};            
        }

            static const vector<Reflection_Instance<void>> Get_Base_Class_Rigid_Body_Reflection_Instance_List(shared_ptr<void> Instance){
                vector<Reflection_Instance<void>> Table;

                    

                return Table;
            }

            static const string Get_Field_Shapes_Type_Spelling(void){
                return string{"vector<Rigid_Body_Shape>"};
            }

            static const string Get_Field_Shapes_Spelling(void){
                return string{"m_Shapes"};
            }


            static const string Get_Field_Shapes_Display_Name(void){
                return string{"Shapes"};
            }

            static const void *const Get_Filed_Shapes_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Rigid_Body>(Instance)->m_Shapes);
            }

            static void Set_Field_Shapes_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Rigid_Body>(Instance)->m_Shapes=*static_cast<const vector<Rigid_Body_Shape>*>(Value);
            }

            static const bool Is_Filed_Shapes_CPPVector(void){
                return  !  false;
            }

                static const string Get_Field_Shapes_CPPVector_Element_Type_Spelling(void){
                    return string {"m_Shapes"};
                }

                static const size_t Get_Field_Shapes_CPPVector_Capacity(shared_ptr<void> Instance){
                    return static_pointer_cast<Rigid_Body>(Instance)->m_Shapes.capacity();
                }

                static const size_t Get_Field_Shapes_CPPVector_Size(shared_ptr<void> Instance){
                    return static_pointer_cast<Rigid_Body>(Instance)->m_Shapes.size();
                }

                static const void *Get_Field_Shapes_CPPVector_Element(shared_ptr<void> Instance, size_t Index){
                    return static_cast<const void*>(&static_pointer_cast<Rigid_Body>(Instance)->m_Shapes[Index]);
                }

                static void Set_Field_Shapes_CPPVector_Element(shared_ptr<void> Instance, size_t Index,const void* Value){
                    static_pointer_cast<Rigid_Body>(Instance)->m_Shapes[Index]=*static_cast<const Rigid_Body_Shape*>(Value);
                }

            static const string Get_Field_Inverse_Mass_Type_Spelling(void){
                return string{"float"};
            }

            static const string Get_Field_Inverse_Mass_Spelling(void){
                return string{"m_Inverse_Mass"};
            }


            static const string Get_Field_Inverse_Mass_Display_Name(void){
                return string{"Inverse_Mass"};
            }

            static const void *const Get_Filed_Inverse_Mass_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Rigid_Body>(Instance)->m_Inverse_Mass);
            }

            static void Set_Field_Inverse_Mass_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Rigid_Body>(Instance)->m_Inverse_Mass=*static_cast<const float*>(Value);
            }

            static const bool Is_Filed_Inverse_Mass_CPPVector(void){
                return  false;
            }

            

            static const string Get_Field_Actor_Type_Type_Spelling(void){
                return string{"int"};
            }

            static const string Get_Field_Actor_Type_Spelling(void){
                return string{"m_Actor_Type"};
            }


            static const string Get_Field_Actor_Type_Display_Name(void){
                return string{"Actor_Type"};
            }

            static const void *const Get_Filed_Actor_Type_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Rigid_Body>(Instance)->m_Actor_Type);
            }

            static void Set_Field_Actor_Type_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Rigid_Body>(Instance)->m_Actor_Type=*static_cast<const int*>(Value);
            }

            static const bool Is_Filed_Actor_Type_CPPVector(void){
                return  false;
            }

            


            static void TypeWrapper_Rigster(void){
                shared_ptr<Class_Func_Tuple> Temp_Class_Func_Tuple{nullptr};
                shared_ptr<Class_Base_Class_Tuple> Temp_Class_Base_Class_Tuple{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Field_Func_Tuple>>> Temp_Class_Field_Func_Tuple_Map{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Filed_CPPVector_Func_Tuple>>> Temp_Class_Filed_CPPVector_Func_Tuple_Map{nullptr};

                Temp_Class_Func_Tuple = make_shared<Class_Func_Tuple>(
                    Reflection_Rigid_Body_Operator::Get_Class_Rigid_Body_Spelling,
                    Reflection_Rigid_Body_Operator::Get_Class_Displaying_Name
                );

                Temp_Class_Base_Class_Tuple = make_shared<Class_Base_Class_Tuple>(
                    Reflection_Rigid_Body_Operator::Get_Base_Class_Rigid_Body_Reflection_Instance_List
                );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Shapes"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Rigid_Body_Operator::Get_Field_Shapes_Type_Spelling,
                        Reflection_Rigid_Body_Operator::Get_Field_Shapes_Spelling,
                        Reflection_Rigid_Body_Operator::Get_Field_Shapes_Display_Name,
                        Reflection_Rigid_Body_Operator::Get_Filed_Shapes_Attribute,
                        Reflection_Rigid_Body_Operator::Set_Field_Shapes_Attribute,
                        Reflection_Rigid_Body_Operator::Is_Filed_Shapes_CPPVector
                    )
                );

                    Temp_Class_Filed_CPPVector_Func_Tuple_Map->emplace(
                    string{"m_Shapes"},
                        make_shared<Class_Filed_CPPVector_Func_Tuple>( 
                            Reflection_Rigid_Body_Operator::Get_Field_Shapes_CPPVector_Element_Type_Spelling,
                            Reflection_Rigid_Body_Operator::Get_Field_Shapes_CPPVector_Capacity,
                            Reflection_Rigid_Body_Operator::Get_Field_Shapes_CPPVector_Size,
                            Reflection_Rigid_Body_Operator::Get_Field_Shapes_CPPVector_Element,
                            Reflection_Rigid_Body_Operator::Set_Field_Shapes_CPPVector_Element
                        )
                    );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Inverse_Mass"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Rigid_Body_Operator::Get_Field_Inverse_Mass_Type_Spelling,
                        Reflection_Rigid_Body_Operator::Get_Field_Inverse_Mass_Spelling,
                        Reflection_Rigid_Body_Operator::Get_Field_Inverse_Mass_Display_Name,
                        Reflection_Rigid_Body_Operator::Get_Filed_Inverse_Mass_Attribute,
                        Reflection_Rigid_Body_Operator::Set_Field_Inverse_Mass_Attribute,
                        Reflection_Rigid_Body_Operator::Is_Filed_Inverse_Mass_CPPVector
                    )
                );

                

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Actor_Type"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Rigid_Body_Operator::Get_Field_Actor_Type_Type_Spelling,
                        Reflection_Rigid_Body_Operator::Get_Field_Actor_Type_Spelling,
                        Reflection_Rigid_Body_Operator::Get_Field_Actor_Type_Display_Name,
                        Reflection_Rigid_Body_Operator::Get_Filed_Actor_Type_Attribute,
                        Reflection_Rigid_Body_Operator::Set_Field_Actor_Type_Attribute,
                        Reflection_Rigid_Body_Operator::Is_Filed_Actor_Type_CPPVector
                    )
                );

                

                
            Reflection_Register::Get_Instance().Register_Class(string{"Rigid_Body"},Temp_Class_Func_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Base_Class(string{"Rigid_Body"},Temp_Class_Base_Class_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Filed(string{"Rigid_Body"},Temp_Class_Field_Func_Tuple_Map);
            Reflection_Register::Get_Instance().Register_Class_Field_CPPVector(string{"Rigid_Body"},Temp_Class_Filed_CPPVector_Func_Tuple_Map);
        }

    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection


