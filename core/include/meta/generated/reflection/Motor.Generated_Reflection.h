#pragma once

#include<string>
#include<vector>
#include<memory>
#include<cstddef>

#include "meta/Reflection/Reflection_Instance.h"

#include "D:/Amy_Engine/resource/include/components/motor/Motor.h"

namespace NameSpace_Resource::NameSpace_Components{

    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;
    using std::static_pointer_cast;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

    class Reflection_Physics_Controller_Config_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Physics_Controller_Config"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Physics_Controller_Config"};            
        }

            static const vector<Reflection_Instance<Physics_Controller_Config>> Get_Base_Class_Reflection_Instance_List(shared_ptr<Physics_Controller_Config> Instance){
                vector<Reflection_Instance<Physics_Controller_Config>> Table;

                    

                return Table;
            }

            static const string Get_Cylinder_Type_Spelling(void){
                return string{"Geometry_Cylinder"};
            }

            static const string Get_Cylinder_Spelling(void){
                return string{"m_Cylinder"};
            }


            static const string Get_Cylinder_Display_Name(void){
                return string{"Cylinder"};
            }

            static const Geometry_Cylinder& Get_Cylinder_Attribute(shared_ptr<Physics_Controller_Config> Instance){
                return Instance->m_Cylinder;
            }

            static void Set_Field_Cylinder_Attribute(shared_ptr<Physics_Controller_Config> Instance, const Geometry_Cylinder& Value){
                Instance->m_Cylinder=Value;
            }

            static const bool Is_Filed_Cylinder_CPPVector(void){
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

    class Reflection_Motor_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Motor"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Motor"};            
        }

            static const vector<Reflection_Instance<Motor>> Get_Base_Class_Reflection_Instance_List(shared_ptr<Motor> Instance){
                vector<Reflection_Instance<Motor>> Table;

                    

                return Table;
            }

            static const string Get_Physics_Controller_Config_Type_Spelling(void){
                return string{"Reflection_Instance<Physics_Controller_Config>"};
            }

            static const string Get_Physics_Controller_Config_Spelling(void){
                return string{"m_Physics_Controller_Config"};
            }


            static const string Get_Physics_Controller_Config_Display_Name(void){
                return string{"Physics_Controller_Config"};
            }

            static const Reflection_Instance<Physics_Controller_Config>& Get_Physics_Controller_Config_Attribute(shared_ptr<Motor> Instance){
                return Instance->m_Physics_Controller_Config;
            }

            static void Set_Field_Physics_Controller_Config_Attribute(shared_ptr<Motor> Instance, const Reflection_Instance<Physics_Controller_Config>& Value){
                Instance->m_Physics_Controller_Config=Value;
            }

            static const bool Is_Filed_Physics_Controller_Config_CPPVector(void){
                return  false;
            }

            

            static const string Get_Move_Speed_Type_Spelling(void){
                return string{"float"};
            }

            static const string Get_Move_Speed_Spelling(void){
                return string{"m_Move_Speed"};
            }


            static const string Get_Move_Speed_Display_Name(void){
                return string{"Move_Speed"};
            }

            static const float& Get_Move_Speed_Attribute(shared_ptr<Motor> Instance){
                return Instance->m_Move_Speed;
            }

            static void Set_Field_Move_Speed_Attribute(shared_ptr<Motor> Instance, const float& Value){
                Instance->m_Move_Speed=Value;
            }

            static const bool Is_Filed_Move_Speed_CPPVector(void){
                return  false;
            }

            

            static const string Get_Jump_Height_Type_Spelling(void){
                return string{"float"};
            }

            static const string Get_Jump_Height_Spelling(void){
                return string{"m_Jump_Height"};
            }


            static const string Get_Jump_Height_Display_Name(void){
                return string{"Jump_Height"};
            }

            static const float& Get_Jump_Height_Attribute(shared_ptr<Motor> Instance){
                return Instance->m_Jump_Height;
            }

            static void Set_Field_Jump_Height_Attribute(shared_ptr<Motor> Instance, const float& Value){
                Instance->m_Jump_Height=Value;
            }

            static const bool Is_Filed_Jump_Height_CPPVector(void){
                return  false;
            }

            

            static const string Get_Max_Move_Speed_Ratio_Type_Spelling(void){
                return string{"float"};
            }

            static const string Get_Max_Move_Speed_Ratio_Spelling(void){
                return string{"m_Max_Move_Speed_Ratio"};
            }


            static const string Get_Max_Move_Speed_Ratio_Display_Name(void){
                return string{"Max_Move_Speed_Ratio"};
            }

            static const float& Get_Max_Move_Speed_Ratio_Attribute(shared_ptr<Motor> Instance){
                return Instance->m_Max_Move_Speed_Ratio;
            }

            static void Set_Field_Max_Move_Speed_Ratio_Attribute(shared_ptr<Motor> Instance, const float& Value){
                Instance->m_Max_Move_Speed_Ratio=Value;
            }

            static const bool Is_Filed_Max_Move_Speed_Ratio_CPPVector(void){
                return  false;
            }

            

            static const string Get_Max_Sprint_Speed_Ratio_Type_Spelling(void){
                return string{"float"};
            }

            static const string Get_Max_Sprint_Speed_Ratio_Spelling(void){
                return string{"m_Max_Sprint_Speed_Ratio"};
            }


            static const string Get_Max_Sprint_Speed_Ratio_Display_Name(void){
                return string{"Max_Sprint_Speed_Ratio"};
            }

            static const float& Get_Max_Sprint_Speed_Ratio_Attribute(shared_ptr<Motor> Instance){
                return Instance->m_Max_Sprint_Speed_Ratio;
            }

            static void Set_Field_Max_Sprint_Speed_Ratio_Attribute(shared_ptr<Motor> Instance, const float& Value){
                Instance->m_Max_Sprint_Speed_Ratio=Value;
            }

            static const bool Is_Filed_Max_Sprint_Speed_Ratio_CPPVector(void){
                return  false;
            }

            

            static const string Get_Move_Acceleration_Type_Spelling(void){
                return string{"float"};
            }

            static const string Get_Move_Acceleration_Spelling(void){
                return string{"m_Move_Acceleration"};
            }


            static const string Get_Move_Acceleration_Display_Name(void){
                return string{"Move_Acceleration"};
            }

            static const float& Get_Move_Acceleration_Attribute(shared_ptr<Motor> Instance){
                return Instance->m_Move_Acceleration;
            }

            static void Set_Field_Move_Acceleration_Attribute(shared_ptr<Motor> Instance, const float& Value){
                Instance->m_Move_Acceleration=Value;
            }

            static const bool Is_Filed_Move_Acceleration_CPPVector(void){
                return  false;
            }

            

            static const string Get_Sprint_Acceleration_Type_Spelling(void){
                return string{"float"};
            }

            static const string Get_Sprint_Acceleration_Spelling(void){
                return string{"m_Sprint_Acceleration"};
            }


            static const string Get_Sprint_Acceleration_Display_Name(void){
                return string{"Sprint_Acceleration"};
            }

            static const float& Get_Sprint_Acceleration_Attribute(shared_ptr<Motor> Instance){
                return Instance->m_Sprint_Acceleration;
            }

            static void Set_Field_Sprint_Acceleration_Attribute(shared_ptr<Motor> Instance, const float& Value){
                Instance->m_Sprint_Acceleration=Value;
            }

            static const bool Is_Filed_Sprint_Acceleration_CPPVector(void){
                return  false;
            }

            


    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection

