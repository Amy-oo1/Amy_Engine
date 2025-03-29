#pragma once

#include<string>
#include<vector>
#include<memory>
#include<cstddef>

#include "meta/Reflection/Reflection_Instance.h"

#include "D:/Amy_Engine/resource/include/global/Global_Particle.h"

namespace NameSpace_Resource::NameSpace_Global{

    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;
    using std::static_pointer_cast;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

    class Reflection_Global_Particle_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Global_Particle"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Global_Particle"};            
        }

        

            static const string Get_Emit_Gap_Type_Spelling(void){
                return string{"int"};
            }

            static const string Get_Emit_Gap_Spelling(void){
                return string{"m_Emit_Gap"};
            }


            static const string Get_Emit_Gap_Display_Name(void){
                return string{"Emit_Gap"};
            }

            static const int& Get_Emit_Gap_Attribute(shared_ptr<Global_Particle> Instance){
                return Instance->m_Emit_Gap;
            }

            static void Set_Field_Emit_Gap_Attribute(shared_ptr<Global_Particle> Instance, const int& Value){
                Instance->m_Emit_Gap=Value;
            }

            static const bool Is_Filed_Emit_Gap_CPPVector(void){
                return  false;
            }

            

            static const string Get_Emit_Count_Type_Spelling(void){
                return string{"int"};
            }

            static const string Get_Emit_Count_Spelling(void){
                return string{"m_Emit_Count"};
            }


            static const string Get_Emit_Count_Display_Name(void){
                return string{"Emit_Count"};
            }

            static const int& Get_Emit_Count_Attribute(shared_ptr<Global_Particle> Instance){
                return Instance->m_Emit_Count;
            }

            static void Set_Field_Emit_Count_Attribute(shared_ptr<Global_Particle> Instance, const int& Value){
                Instance->m_Emit_Count=Value;
            }

            static const bool Is_Filed_Emit_Count_CPPVector(void){
                return  false;
            }

            

            static const string Get_Time_Step_Type_Spelling(void){
                return string{"int"};
            }

            static const string Get_Time_Step_Spelling(void){
                return string{"m_Time_Step"};
            }


            static const string Get_Time_Step_Display_Name(void){
                return string{"Time_Step"};
            }

            static const int& Get_Time_Step_Attribute(shared_ptr<Global_Particle> Instance){
                return Instance->m_Time_Step;
            }

            static void Set_Field_Time_Step_Attribute(shared_ptr<Global_Particle> Instance, const int& Value){
                Instance->m_Time_Step=Value;
            }

            static const bool Is_Filed_Time_Step_CPPVector(void){
                return  false;
            }

            

            static const string Get_Max_Life_Type_Spelling(void){
                return string{"float"};
            }

            static const string Get_Max_Life_Spelling(void){
                return string{"m_Max_Life"};
            }


            static const string Get_Max_Life_Display_Name(void){
                return string{"Max_Life"};
            }

            static const float& Get_Max_Life_Attribute(shared_ptr<Global_Particle> Instance){
                return Instance->m_Max_Life;
            }

            static void Set_Field_Max_Life_Attribute(shared_ptr<Global_Particle> Instance, const float& Value){
                Instance->m_Max_Life=Value;
            }

            static const bool Is_Filed_Max_Life_CPPVector(void){
                return  false;
            }

            

            static const string Get_Gravity_Type_Spelling(void){
                return string{"Vector3"};
            }

            static const string Get_Gravity_Spelling(void){
                return string{"m_Gravity"};
            }


            static const string Get_Gravity_Display_Name(void){
                return string{"Gravity"};
            }

            static const Vector3& Get_Gravity_Attribute(shared_ptr<Global_Particle> Instance){
                return Instance->m_Gravity;
            }

            static void Set_Field_Gravity_Attribute(shared_ptr<Global_Particle> Instance, const Vector3& Value){
                Instance->m_Gravity=Value;
            }

            static const bool Is_Filed_Gravity_CPPVector(void){
                return  false;
            }

            

            static const string Get_Particle_Billboard_Image_URL_Type_Spelling(void){
                return string{"path"};
            }

            static const string Get_Particle_Billboard_Image_URL_Spelling(void){
                return string{"m_Particle_Billboard_Image_URL"};
            }


            static const string Get_Particle_Billboard_Image_URL_Display_Name(void){
                return string{"Particle_Billboard_Image_URL"};
            }

            static const path& Get_Particle_Billboard_Image_URL_Attribute(shared_ptr<Global_Particle> Instance){
                return Instance->m_Particle_Billboard_Image_URL;
            }

            static void Set_Field_Particle_Billboard_Image_URL_Attribute(shared_ptr<Global_Particle> Instance, const path& Value){
                Instance->m_Particle_Billboard_Image_URL=Value;
            }

            static const bool Is_Filed_Particle_Billboard_Image_URL_CPPVector(void){
                return  false;
            }

            

            static const string Get_Logo_Image_URL_Type_Spelling(void){
                return string{"path"};
            }

            static const string Get_Logo_Image_URL_Spelling(void){
                return string{"m_Logo_Image_URL"};
            }


            static const string Get_Logo_Image_URL_Display_Name(void){
                return string{"Logo_Image_URL"};
            }

            static const path& Get_Logo_Image_URL_Attribute(shared_ptr<Global_Particle> Instance){
                return Instance->m_Logo_Image_URL;
            }

            static void Set_Field_Logo_Image_URL_Attribute(shared_ptr<Global_Particle> Instance, const path& Value){
                Instance->m_Logo_Image_URL=Value;
            }

            static const bool Is_Filed_Logo_Image_URL_CPPVector(void){
                return  false;
            }

            


    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection

