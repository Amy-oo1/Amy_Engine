#pragma once

#include<string>
#include<vector>
#include<memory>
#include<cstddef>

#include "meta/Reflection/Reflection_Instance.h"

#include "D:/Amy_Engine/resource/include/components/rigid_body/Rigid_Body.h"

namespace NameSpace_Resource::NameSpace_Components{

    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;
    using std::static_pointer_cast;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

    class Reflection_Rigid_Body_Shape_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Rigid_Body_Shape"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Rigid_Body_Shape"};            
        }

            static const vector<Reflection_Instance<Rigid_Body_Shape>> Get_Base_Class_Reflection_Instance_List(shared_ptr<Rigid_Body_Shape> Instance){
                vector<Reflection_Instance<Rigid_Body_Shape>> Table;

                    

                return Table;
            }

            static const string Get_Global_Transform_Type_Spelling(void){
                return string{"Orthogonal_Transform"};
            }

            static const string Get_Global_Transform_Spelling(void){
                return string{"m_Global_Transform"};
            }


            static const string Get_Global_Transform_Display_Name(void){
                return string{"Global_Transform"};
            }

            static const Orthogonal_Transform& Get_Global_Transform_Attribute(shared_ptr<Rigid_Body_Shape> Instance){
                return Instance->m_Global_Transform;
            }

            static void Set_Field_Global_Transform_Attribute(shared_ptr<Rigid_Body_Shape> Instance, const Orthogonal_Transform& Value){
                Instance->m_Global_Transform=Value;
            }

            static const bool Is_Filed_Global_Transform_CPPVector(void){
                return  false;
            }

            

            static const string Get_Local_Transform_Type_Spelling(void){
                return string{"Orthogonal_Transform"};
            }

            static const string Get_Local_Transform_Spelling(void){
                return string{"m_Local_Transform"};
            }


            static const string Get_Local_Transform_Display_Name(void){
                return string{"Local_Transform"};
            }

            static const Orthogonal_Transform& Get_Local_Transform_Attribute(shared_ptr<Rigid_Body_Shape> Instance){
                return Instance->m_Local_Transform;
            }

            static void Set_Field_Local_Transform_Attribute(shared_ptr<Rigid_Body_Shape> Instance, const Orthogonal_Transform& Value){
                Instance->m_Local_Transform=Value;
            }

            static const bool Is_Filed_Local_Transform_CPPVector(void){
                return  false;
            }

            

            static const string Get_Bounding_Box_Type_Spelling(void){
                return string{"AxisAligned_Bounding_Box"};
            }

            static const string Get_Bounding_Box_Spelling(void){
                return string{"m_Bounding_Box"};
            }


            static const string Get_Bounding_Box_Display_Name(void){
                return string{"Bounding_Box"};
            }

            static const AxisAligned_Bounding_Box& Get_Bounding_Box_Attribute(shared_ptr<Rigid_Body_Shape> Instance){
                return Instance->m_Bounding_Box;
            }

            static void Set_Field_Bounding_Box_Attribute(shared_ptr<Rigid_Body_Shape> Instance, const AxisAligned_Bounding_Box& Value){
                Instance->m_Bounding_Box=Value;
            }

            static const bool Is_Filed_Bounding_Box_CPPVector(void){
                return  false;
            }

            

            static const string Get_Type_Type_Spelling(void){
                return string{"Rigid_Body_Type"};
            }

            static const string Get_Type_Spelling(void){
                return string{"m_Type"};
            }


            static const string Get_Type_Display_Name(void){
                return string{"Type"};
            }

            static const Rigid_Body_Type& Get_Type_Attribute(shared_ptr<Rigid_Body_Shape> Instance){
                return Instance->m_Type;
            }

            static void Set_Field_Type_Attribute(shared_ptr<Rigid_Body_Shape> Instance, const Rigid_Body_Type& Value){
                Instance->m_Type=Value;
            }

            static const bool Is_Filed_Type_CPPVector(void){
                return  false;
            }

            

            static const string Get_Instance_Type_Spelling(void){
                return string{"Reflection_Instance<Geometry_Base>"};
            }

            static const string Get_Instance_Spelling(void){
                return string{"m_Instance"};
            }


            static const string Get_Instance_Display_Name(void){
                return string{"Instance"};
            }

            static const Reflection_Instance<Geometry_Base>& Get_Instance_Attribute(shared_ptr<Rigid_Body_Shape> Instance){
                return Instance->m_Instance;
            }

            static void Set_Field_Instance_Attribute(shared_ptr<Rigid_Body_Shape> Instance, const Reflection_Instance<Geometry_Base>& Value){
                Instance->m_Instance=Value;
            }

            static const bool Is_Filed_Instance_CPPVector(void){
                return  false;
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

    class Reflection_Rigid_Body_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Rigid_Body"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Rigid_Body"};            
        }

            static const vector<Reflection_Instance<Rigid_Body>> Get_Base_Class_Reflection_Instance_List(shared_ptr<Rigid_Body> Instance){
                vector<Reflection_Instance<Rigid_Body>> Table;

                    

                return Table;
            }

            static const string Get_Shapes_Type_Spelling(void){
                return string{"vector<Rigid_Body_Shape>"};
            }

            static const string Get_Shapes_Spelling(void){
                return string{"m_Shapes"};
            }


            static const string Get_Shapes_Display_Name(void){
                return string{"Shapes"};
            }

            static const vector<Rigid_Body_Shape>& Get_Shapes_Attribute(shared_ptr<Rigid_Body> Instance){
                return Instance->m_Shapes;
            }

            static void Set_Field_Shapes_Attribute(shared_ptr<Rigid_Body> Instance, const vector<Rigid_Body_Shape>& Value){
                Instance->m_Shapes=Value;
            }

            static const bool Is_Filed_Shapes_CPPVector(void){
                return  !  false;
            }

                static const string Get_Shapes_CPPVector_Element_Type_Spelling(void){
                    return string {"Rigid_Body_Shape"};
                }

                static const size_t Get_Shapes_CPPVector_Capacity(shared_ptr<Rigid_Body> Instance){
                    return Instance->m_Shapes.capacity();
                }

                static const size_t Get_Shapes_CPPVector_Size(shared_ptr<Rigid_Body> Instance){
                    return Instance->m_Shapes.size();
                }

                static const Rigid_Body_Shape& Get_Shapes_CPPVector_Element(shared_ptr<Rigid_Body> Instance, size_t Index){
                    return Instance->m_Shapes[Index];
                }

                static void Set_Shapes_CPPVector_Element(shared_ptr<Rigid_Body> Instance, size_t Index, const Rigid_Body_Shape& Value){
                    Instance->m_Shapes[Index]=Value;
                }

                static void Reserve_Shapes_CPPVector(shared_ptr<Rigid_Body> Instance, size_t Capacity){
                    Instance->m_Shapes.reserve(Capacity);
                }

                static void Push_Back_Shapes_CPPVector(shared_ptr<Rigid_Body> Instance, const Rigid_Body_Shape& Value){
                    Instance->m_Shapes.push_back(Value);
                }

            static const string Get_Inverse_Mass_Type_Spelling(void){
                return string{"float"};
            }

            static const string Get_Inverse_Mass_Spelling(void){
                return string{"m_Inverse_Mass"};
            }


            static const string Get_Inverse_Mass_Display_Name(void){
                return string{"Inverse_Mass"};
            }

            static const float& Get_Inverse_Mass_Attribute(shared_ptr<Rigid_Body> Instance){
                return Instance->m_Inverse_Mass;
            }

            static void Set_Field_Inverse_Mass_Attribute(shared_ptr<Rigid_Body> Instance, const float& Value){
                Instance->m_Inverse_Mass=Value;
            }

            static const bool Is_Filed_Inverse_Mass_CPPVector(void){
                return  false;
            }

            

            static const string Get_Actor_Type_Type_Spelling(void){
                return string{"int"};
            }

            static const string Get_Actor_Type_Spelling(void){
                return string{"m_Actor_Type"};
            }


            static const string Get_Actor_Type_Display_Name(void){
                return string{"Actor_Type"};
            }

            static const int& Get_Actor_Type_Attribute(shared_ptr<Rigid_Body> Instance){
                return Instance->m_Actor_Type;
            }

            static void Set_Field_Actor_Type_Attribute(shared_ptr<Rigid_Body> Instance, const int& Value){
                Instance->m_Actor_Type=Value;
            }

            static const bool Is_Filed_Actor_Type_CPPVector(void){
                return  false;
            }

            


    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection

