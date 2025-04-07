#pragma once

#include<string>
#include<vector>
#include<memory>
#include<cstddef>

#include "json.h"

#include "meta/Reflection/Reflection_Instance.h"

#include "meta/Serializer/Serializer.h"

#include "D:/Amy_Engine/resource/include/components/camera/Camera_Controller.h"

namespace NameSpace_Resource::NameSpace_Components{

    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;
    using std::static_pointer_cast;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

    class Reflection_Camera_Pose_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Camera_Pose"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Camera_Pose"};            
        }

        

            static const string Get_Position_Type_Spelling(void){
                return string{"Vector3"};
            }

            static const string Get_Position_Spelling(void){
                return string{"m_Position"};
            }


            static const string Get_Position_Display_Name(void){
                return string{"Position"};
            }

            static const Vector3& Get_Position_Attribute(shared_ptr<Camera_Pose> Instance){
                return Instance->m_Position;
            }

            static void Set_Field_Position_Attribute(shared_ptr<Camera_Pose> Instance, const Vector3& Value){
                Instance->m_Position=Value;
            }

            static const bool Is_Filed_Position_CPPVector(void){
                return  false;
            }

            

            static const string Get_Target_Type_Spelling(void){
                return string{"Vector3"};
            }

            static const string Get_Target_Spelling(void){
                return string{"m_Target"};
            }


            static const string Get_Target_Display_Name(void){
                return string{"Target"};
            }

            static const Vector3& Get_Target_Attribute(shared_ptr<Camera_Pose> Instance){
                return Instance->m_Target;
            }

            static void Set_Field_Target_Attribute(shared_ptr<Camera_Pose> Instance, const Vector3& Value){
                Instance->m_Target=Value;
            }

            static const bool Is_Filed_Target_CPPVector(void){
                return  false;
            }

            

            static const string Get_Up_Type_Spelling(void){
                return string{"Vector3"};
            }

            static const string Get_Up_Spelling(void){
                return string{"m_Up"};
            }


            static const string Get_Up_Display_Name(void){
                return string{"Up"};
            }

            static const Vector3& Get_Up_Attribute(shared_ptr<Camera_Pose> Instance){
                return Instance->m_Up;
            }

            static void Set_Field_Up_Attribute(shared_ptr<Camera_Pose> Instance, const Vector3& Value){
                Instance->m_Up=Value;
            }

            static const bool Is_Filed_Up_CPPVector(void){
                return  false;
            }

            


    };
   
}// namespace NameSpace_Resource::NameSpace_Components

    
 
namespace NameSpace_Resource::NameSpace_Components{

    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;
    using std::static_pointer_cast;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

    class Reflection_Camera_Config_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Camera_Config"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Camera_Config"};            
        }

        

            static const string Get_Pose_Type_Spelling(void){
                return string{"shared_ptr<Camera_Pose>"};
            }

            static const string Get_Pose_Spelling(void){
                return string{"m_Pose"};
            }


            static const string Get_Pose_Display_Name(void){
                return string{"Pose"};
            }

            static const shared_ptr<Camera_Pose>& Get_Pose_Attribute(shared_ptr<Camera_Config> Instance){
                return Instance->m_Pose;
            }

            static void Set_Field_Pose_Attribute(shared_ptr<Camera_Config> Instance, const shared_ptr<Camera_Pose>& Value){
                Instance->m_Pose=Value;
            }

            static const bool Is_Filed_Pose_CPPVector(void){
                return  false;
            }

            

            static const string Get_Aspect_Type_Spelling(void){
                return string{"Vector2"};
            }

            static const string Get_Aspect_Spelling(void){
                return string{"m_Aspect"};
            }


            static const string Get_Aspect_Display_Name(void){
                return string{"Aspect"};
            }

            static const Vector2& Get_Aspect_Attribute(shared_ptr<Camera_Config> Instance){
                return Instance->m_Aspect;
            }

            static void Set_Field_Aspect_Attribute(shared_ptr<Camera_Config> Instance, const Vector2& Value){
                Instance->m_Aspect=Value;
            }

            static const bool Is_Filed_Aspect_CPPVector(void){
                return  false;
            }

            

            static const string Get_Z_Near_Type_Spelling(void){
                return string{"float"};
            }

            static const string Get_Z_Near_Spelling(void){
                return string{"m_Z_Near"};
            }


            static const string Get_Z_Near_Display_Name(void){
                return string{"Z_Near"};
            }

            static const float& Get_Z_Near_Attribute(shared_ptr<Camera_Config> Instance){
                return Instance->m_Z_Near;
            }

            static void Set_Field_Z_Near_Attribute(shared_ptr<Camera_Config> Instance, const float& Value){
                Instance->m_Z_Near=Value;
            }

            static const bool Is_Filed_Z_Near_CPPVector(void){
                return  false;
            }

            

            static const string Get_Z_Far_Type_Spelling(void){
                return string{"float"};
            }

            static const string Get_Z_Far_Spelling(void){
                return string{"m_Z_Far"};
            }


            static const string Get_Z_Far_Display_Name(void){
                return string{"Z_Far"};
            }

            static const float& Get_Z_Far_Attribute(shared_ptr<Camera_Config> Instance){
                return Instance->m_Z_Far;
            }

            static void Set_Field_Z_Far_Attribute(shared_ptr<Camera_Config> Instance, const float& Value){
                Instance->m_Z_Far=Value;
            }

            static const bool Is_Filed_Z_Far_CPPVector(void){
                return  false;
            }

            


    };
   
}// namespace NameSpace_Resource::NameSpace_Components

    
 

