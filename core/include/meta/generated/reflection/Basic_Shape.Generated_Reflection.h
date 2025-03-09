#pragma once

#include<string>
#include<vector>
#include<memory>
#include<cstddef>

#include "meta/Reflection/Reflection_Instance.h"
#include "meta/Reflection/Reflection_Register.h"

#include "D:/Amy_Engine/resource/include/components/rigid_body/Basic_Shape.h"

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


    class Reflection_Geometry_Base_Operator {
    public:

        static const string Get_Class_Geometry_Base_Spelling(void){
            return string{"Geometry_Base"};
        }

        static const string Get_Class_Displaying_Name(void){
            return string{"Geometry_Base"};            
        }

            static const vector<Reflection_Instance<void>> Get_Base_Class_Geometry_Base_Reflection_Instance_List(shared_ptr<void> Instance){
                vector<Reflection_Instance<void>> Table;

                    

                return Table;
            }

            static const string Get_Field__Type_Spelling(void){
                return string{""};
            }

            static const string Get_Field__Spelling(void){
                return string{""};
            }


            static const string Get_Field__Display_Name(void){
                return string{""};
            }

            static const void *const Get_Filed__Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Geometry_Base>(Instance)->);
            }

            static void Set_Field__Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Geometry_Base>(Instance)->=*static_cast<const *>(Value);
            }

            static const bool Is_Filed__CPPVector(void){
                return  false;
            }

            


            static void TypeWrapper_Rigster(void){
                shared_ptr<Class_Func_Tuple> Temp_Class_Func_Tuple{nullptr};
                shared_ptr<Class_Base_Class_Tuple> Temp_Class_Base_Class_Tuple{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Field_Func_Tuple>>> Temp_Class_Field_Func_Tuple_Map{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Filed_CPPVector_Func_Tuple>>> Temp_Class_Filed_CPPVector_Func_Tuple_Map{nullptr};

                Temp_Class_Func_Tuple = make_shared<Class_Func_Tuple>(
                    Reflection_Geometry_Base_Operator::Get_Class_Geometry_Base_Spelling,
                    Reflection_Geometry_Base_Operator::Get_Class_Displaying_Name
                );

                Temp_Class_Base_Class_Tuple = make_shared<Class_Base_Class_Tuple>(
                    Reflection_Geometry_Base_Operator::Get_Base_Class_Geometry_Base_Reflection_Instance_List
                );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{""},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Geometry_Base_Operator::Get_Field__Type_Spelling,
                        Reflection_Geometry_Base_Operator::Get_Field__Spelling,
                        Reflection_Geometry_Base_Operator::Get_Field__Display_Name,
                        Reflection_Geometry_Base_Operator::Get_Filed__Attribute,
                        Reflection_Geometry_Base_Operator::Set_Field__Attribute,
                        Reflection_Geometry_Base_Operator::Is_Filed__CPPVector
                    )
                );

                

                
            Reflection_Register::Get_Instance().Register_Class(string{"Geometry_Base"},Temp_Class_Func_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Base_Class(string{"Geometry_Base"},Temp_Class_Base_Class_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Filed(string{"Geometry_Base"},Temp_Class_Field_Func_Tuple_Map);
            Reflection_Register::Get_Instance().Register_Class_Field_CPPVector(string{"Geometry_Base"},Temp_Class_Filed_CPPVector_Func_Tuple_Map);
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


    class Reflection_Geometry_Box_Operator {
    public:

        static const string Get_Class_Geometry_Box_Spelling(void){
            return string{"Geometry_Box"};
        }

        static const string Get_Class_Displaying_Name(void){
            return string{"Geometry_Box"};            
        }

            static const vector<Reflection_Instance<void>> Get_Base_Class_Geometry_Box_Reflection_Instance_List(shared_ptr<void> Instance){
                vector<Reflection_Instance<void>> Table;

                        Table.emplace_back(string{"Geometry_Base"},static_pointer_cast<Geometry_Base>(Instance));

                return Table;
            }

            static const string Get_Field_Half_Extents_Type_Spelling(void){
                return string{"Vector3"};
            }

            static const string Get_Field_Half_Extents_Spelling(void){
                return string{"m_Half_Extents"};
            }


            static const string Get_Field_Half_Extents_Display_Name(void){
                return string{"Half_Extents"};
            }

            static const void *const Get_Filed_Half_Extents_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Geometry_Box>(Instance)->m_Half_Extents);
            }

            static void Set_Field_Half_Extents_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Geometry_Box>(Instance)->m_Half_Extents=*static_cast<const Vector3*>(Value);
            }

            static const bool Is_Filed_Half_Extents_CPPVector(void){
                return  false;
            }

            


            static void TypeWrapper_Rigster(void){
                shared_ptr<Class_Func_Tuple> Temp_Class_Func_Tuple{nullptr};
                shared_ptr<Class_Base_Class_Tuple> Temp_Class_Base_Class_Tuple{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Field_Func_Tuple>>> Temp_Class_Field_Func_Tuple_Map{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Filed_CPPVector_Func_Tuple>>> Temp_Class_Filed_CPPVector_Func_Tuple_Map{nullptr};

                Temp_Class_Func_Tuple = make_shared<Class_Func_Tuple>(
                    Reflection_Geometry_Box_Operator::Get_Class_Geometry_Box_Spelling,
                    Reflection_Geometry_Box_Operator::Get_Class_Displaying_Name
                );

                Temp_Class_Base_Class_Tuple = make_shared<Class_Base_Class_Tuple>(
                    Reflection_Geometry_Box_Operator::Get_Base_Class_Geometry_Box_Reflection_Instance_List
                );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Half_Extents"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Geometry_Box_Operator::Get_Field_Half_Extents_Type_Spelling,
                        Reflection_Geometry_Box_Operator::Get_Field_Half_Extents_Spelling,
                        Reflection_Geometry_Box_Operator::Get_Field_Half_Extents_Display_Name,
                        Reflection_Geometry_Box_Operator::Get_Filed_Half_Extents_Attribute,
                        Reflection_Geometry_Box_Operator::Set_Field_Half_Extents_Attribute,
                        Reflection_Geometry_Box_Operator::Is_Filed_Half_Extents_CPPVector
                    )
                );

                

                
            Reflection_Register::Get_Instance().Register_Class(string{"Geometry_Box"},Temp_Class_Func_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Base_Class(string{"Geometry_Box"},Temp_Class_Base_Class_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Filed(string{"Geometry_Box"},Temp_Class_Field_Func_Tuple_Map);
            Reflection_Register::Get_Instance().Register_Class_Field_CPPVector(string{"Geometry_Box"},Temp_Class_Filed_CPPVector_Func_Tuple_Map);
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


    class Reflection_Geometry_Sphere_Operator {
    public:

        static const string Get_Class_Geometry_Sphere_Spelling(void){
            return string{"Geometry_Sphere"};
        }

        static const string Get_Class_Displaying_Name(void){
            return string{"Geometry_Sphere"};            
        }

            static const vector<Reflection_Instance<void>> Get_Base_Class_Geometry_Sphere_Reflection_Instance_List(shared_ptr<void> Instance){
                vector<Reflection_Instance<void>> Table;

                        Table.emplace_back(string{"Geometry_Base"},static_pointer_cast<Geometry_Base>(Instance));

                return Table;
            }

            static const string Get_Field_radius_Type_Spelling(void){
                return string{"float"};
            }

            static const string Get_Field_radius_Spelling(void){
                return string{"m_radius"};
            }


            static const string Get_Field_radius_Display_Name(void){
                return string{"radius"};
            }

            static const void *const Get_Filed_radius_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Geometry_Sphere>(Instance)->m_radius);
            }

            static void Set_Field_radius_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Geometry_Sphere>(Instance)->m_radius=*static_cast<const float*>(Value);
            }

            static const bool Is_Filed_radius_CPPVector(void){
                return  false;
            }

            


            static void TypeWrapper_Rigster(void){
                shared_ptr<Class_Func_Tuple> Temp_Class_Func_Tuple{nullptr};
                shared_ptr<Class_Base_Class_Tuple> Temp_Class_Base_Class_Tuple{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Field_Func_Tuple>>> Temp_Class_Field_Func_Tuple_Map{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Filed_CPPVector_Func_Tuple>>> Temp_Class_Filed_CPPVector_Func_Tuple_Map{nullptr};

                Temp_Class_Func_Tuple = make_shared<Class_Func_Tuple>(
                    Reflection_Geometry_Sphere_Operator::Get_Class_Geometry_Sphere_Spelling,
                    Reflection_Geometry_Sphere_Operator::Get_Class_Displaying_Name
                );

                Temp_Class_Base_Class_Tuple = make_shared<Class_Base_Class_Tuple>(
                    Reflection_Geometry_Sphere_Operator::Get_Base_Class_Geometry_Sphere_Reflection_Instance_List
                );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_radius"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Geometry_Sphere_Operator::Get_Field_radius_Type_Spelling,
                        Reflection_Geometry_Sphere_Operator::Get_Field_radius_Spelling,
                        Reflection_Geometry_Sphere_Operator::Get_Field_radius_Display_Name,
                        Reflection_Geometry_Sphere_Operator::Get_Filed_radius_Attribute,
                        Reflection_Geometry_Sphere_Operator::Set_Field_radius_Attribute,
                        Reflection_Geometry_Sphere_Operator::Is_Filed_radius_CPPVector
                    )
                );

                

                
            Reflection_Register::Get_Instance().Register_Class(string{"Geometry_Sphere"},Temp_Class_Func_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Base_Class(string{"Geometry_Sphere"},Temp_Class_Base_Class_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Filed(string{"Geometry_Sphere"},Temp_Class_Field_Func_Tuple_Map);
            Reflection_Register::Get_Instance().Register_Class_Field_CPPVector(string{"Geometry_Sphere"},Temp_Class_Filed_CPPVector_Func_Tuple_Map);
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


    class Reflection_Geometry_Cylinder_Operator {
    public:

        static const string Get_Class_Geometry_Cylinder_Spelling(void){
            return string{"Geometry_Cylinder"};
        }

        static const string Get_Class_Displaying_Name(void){
            return string{"Geometry_Cylinder"};            
        }

            static const vector<Reflection_Instance<void>> Get_Base_Class_Geometry_Cylinder_Reflection_Instance_List(shared_ptr<void> Instance){
                vector<Reflection_Instance<void>> Table;

                        Table.emplace_back(string{"Geometry_Base"},static_pointer_cast<Geometry_Base>(Instance));

                return Table;
            }

            static const string Get_Field_Half_Height_Type_Spelling(void){
                return string{"float"};
            }

            static const string Get_Field_Half_Height_Spelling(void){
                return string{"m_Half_Height"};
            }


            static const string Get_Field_Half_Height_Display_Name(void){
                return string{"Half_Height"};
            }

            static const void *const Get_Filed_Half_Height_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Geometry_Cylinder>(Instance)->m_Half_Height);
            }

            static void Set_Field_Half_Height_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Geometry_Cylinder>(Instance)->m_Half_Height=*static_cast<const float*>(Value);
            }

            static const bool Is_Filed_Half_Height_CPPVector(void){
                return  false;
            }

            


            static void TypeWrapper_Rigster(void){
                shared_ptr<Class_Func_Tuple> Temp_Class_Func_Tuple{nullptr};
                shared_ptr<Class_Base_Class_Tuple> Temp_Class_Base_Class_Tuple{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Field_Func_Tuple>>> Temp_Class_Field_Func_Tuple_Map{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Filed_CPPVector_Func_Tuple>>> Temp_Class_Filed_CPPVector_Func_Tuple_Map{nullptr};

                Temp_Class_Func_Tuple = make_shared<Class_Func_Tuple>(
                    Reflection_Geometry_Cylinder_Operator::Get_Class_Geometry_Cylinder_Spelling,
                    Reflection_Geometry_Cylinder_Operator::Get_Class_Displaying_Name
                );

                Temp_Class_Base_Class_Tuple = make_shared<Class_Base_Class_Tuple>(
                    Reflection_Geometry_Cylinder_Operator::Get_Base_Class_Geometry_Cylinder_Reflection_Instance_List
                );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Half_Height"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Geometry_Cylinder_Operator::Get_Field_Half_Height_Type_Spelling,
                        Reflection_Geometry_Cylinder_Operator::Get_Field_Half_Height_Spelling,
                        Reflection_Geometry_Cylinder_Operator::Get_Field_Half_Height_Display_Name,
                        Reflection_Geometry_Cylinder_Operator::Get_Filed_Half_Height_Attribute,
                        Reflection_Geometry_Cylinder_Operator::Set_Field_Half_Height_Attribute,
                        Reflection_Geometry_Cylinder_Operator::Is_Filed_Half_Height_CPPVector
                    )
                );

                

                
            Reflection_Register::Get_Instance().Register_Class(string{"Geometry_Cylinder"},Temp_Class_Func_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Base_Class(string{"Geometry_Cylinder"},Temp_Class_Base_Class_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Filed(string{"Geometry_Cylinder"},Temp_Class_Field_Func_Tuple_Map);
            Reflection_Register::Get_Instance().Register_Class_Field_CPPVector(string{"Geometry_Cylinder"},Temp_Class_Filed_CPPVector_Func_Tuple_Map);
        }

    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection


