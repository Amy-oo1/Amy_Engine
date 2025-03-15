#pragma once

#include<string>
#include<vector>
#include<memory>
#include<cstddef>

#include "meta/Reflection/Reflection_Instance.h"

#include "D:/Amy_Engine/resource/include/components/emitter/Particle.h"

namespace NameSpace_Resource::NameSpace_Components{

    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;
    using std::static_pointer_cast;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

    class Reflection_Particle_Res_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Particle_Res"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Particle_Res"};            
        }

            static const vector<Reflection_Instance<Particle_Res>> Get_Base_Class_Reflection_Instance_List(shared_ptr<Particle_Res> Instance){
                vector<Reflection_Instance<Particle_Res>> Table;

                    

                return Table;
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

            static const Orthogonal_Transform& Get_Local_Transform_Attribute(shared_ptr<Particle_Res> Instance){
                return Instance->m_Local_Transform;
            }

            static void Set_Field_Local_Transform_Attribute(shared_ptr<Particle_Res> Instance, const Orthogonal_Transform& Value){
                Instance->m_Local_Transform=Value;
            }

            static const bool Is_Filed_Local_Transform_CPPVector(void){
                return  false;
            }

            

            static const string Get_Velocity_Type_Spelling(void){
                return string{"Vector4"};
            }

            static const string Get_Velocity_Spelling(void){
                return string{"m_Velocity"};
            }


            static const string Get_Velocity_Display_Name(void){
                return string{"Velocity"};
            }

            static const Vector4& Get_Velocity_Attribute(shared_ptr<Particle_Res> Instance){
                return Instance->m_Velocity;
            }

            static void Set_Field_Velocity_Attribute(shared_ptr<Particle_Res> Instance, const Vector4& Value){
                Instance->m_Velocity=Value;
            }

            static const bool Is_Filed_Velocity_CPPVector(void){
                return  false;
            }

            

            static const string Get_Acceleration_Type_Spelling(void){
                return string{"Vector4"};
            }

            static const string Get_Acceleration_Spelling(void){
                return string{"m_Acceleration"};
            }


            static const string Get_Acceleration_Display_Name(void){
                return string{"Acceleration"};
            }

            static const Vector4& Get_Acceleration_Attribute(shared_ptr<Particle_Res> Instance){
                return Instance->m_Acceleration;
            }

            static void Set_Field_Acceleration_Attribute(shared_ptr<Particle_Res> Instance, const Vector4& Value){
                Instance->m_Acceleration=Value;
            }

            static const bool Is_Filed_Acceleration_CPPVector(void){
                return  false;
            }

            

            static const string Get_Size_Type_Spelling(void){
                return string{"Vector3"};
            }

            static const string Get_Size_Spelling(void){
                return string{"m_Size"};
            }


            static const string Get_Size_Display_Name(void){
                return string{"Size"};
            }

            static const Vector3& Get_Size_Attribute(shared_ptr<Particle_Res> Instance){
                return Instance->m_Size;
            }

            static void Set_Field_Size_Attribute(shared_ptr<Particle_Res> Instance, const Vector3& Value){
                Instance->m_Size=Value;
            }

            static const bool Is_Filed_Size_CPPVector(void){
                return  false;
            }

            

            static const string Get_Emitter_Type_Type_Spelling(void){
                return string{"int"};
            }

            static const string Get_Emitter_Type_Spelling(void){
                return string{"m_Emitter_Type"};
            }


            static const string Get_Emitter_Type_Display_Name(void){
                return string{"Emitter_Type"};
            }

            static const int& Get_Emitter_Type_Attribute(shared_ptr<Particle_Res> Instance){
                return Instance->m_Emitter_Type;
            }

            static void Set_Field_Emitter_Type_Attribute(shared_ptr<Particle_Res> Instance, const int& Value){
                Instance->m_Emitter_Type=Value;
            }

            static const bool Is_Filed_Emitter_Type_CPPVector(void){
                return  false;
            }

            

            static const string Get_Life_Type_Spelling(void){
                return string{"Vector2"};
            }

            static const string Get_Life_Spelling(void){
                return string{"m_Life"};
            }


            static const string Get_Life_Display_Name(void){
                return string{"Life"};
            }

            static const Vector2& Get_Life_Attribute(shared_ptr<Particle_Res> Instance){
                return Instance->m_Life;
            }

            static void Set_Field_Life_Attribute(shared_ptr<Particle_Res> Instance, const Vector2& Value){
                Instance->m_Life=Value;
            }

            static const bool Is_Filed_Life_CPPVector(void){
                return  false;
            }

            

            static const string Get_Color_Type_Spelling(void){
                return string{"Color"};
            }

            static const string Get_Color_Spelling(void){
                return string{"m_Color"};
            }


            static const string Get_Color_Display_Name(void){
                return string{"Color"};
            }

            static const Color& Get_Color_Attribute(shared_ptr<Particle_Res> Instance){
                return Instance->m_Color;
            }

            static void Set_Field_Color_Attribute(shared_ptr<Particle_Res> Instance, const Color& Value){
                Instance->m_Color=Value;
            }

            static const bool Is_Filed_Color_CPPVector(void){
                return  false;
            }

            


    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection

