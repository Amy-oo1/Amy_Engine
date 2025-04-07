#pragma once

#include<string>
#include<vector>
#include<memory>
#include<cstddef>

#include "json.h"

#include "meta/Reflection/Reflection_Instance.h"

#include "meta/Serializer/Serializer.h"

#include "D:/Amy_Engine/function/include/frame/components/camera/Camera_Component.h"

namespace NameSpace_Function::NameSpace_Frame::NameSpace_Components::NameSpace_Camera{

    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;
    using std::static_pointer_cast;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

    class Reflection_Camera_Component_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Camera_Component"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Camera_Component"};            
        }

            static const vector<Reflection_Instance<Camera_Component>> Get_Base_Class_Reflection_Instance_List(shared_ptr<Camera_Component> Instance){
                vector<Reflection_Instance<Camera_Component>> Table;

                        Table.emplace_back(string{"Component"},static_pointer_cast<Camera_Component>(Instance));

                return Table;
            }

            static const string Get_Camera_Resource_Type_Spelling(void){
                return string{"shared_ptr<Camera_Resource>"};
            }

            static const string Get_Camera_Resource_Spelling(void){
                return string{"m_Camera_Resource"};
            }


            static const string Get_Camera_Resource_Display_Name(void){
                return string{"Camera_Resource"};
            }

            static const shared_ptr<Camera_Resource>& Get_Camera_Resource_Attribute(shared_ptr<Camera_Component> Instance){
                return Instance->m_Camera_Resource;
            }

            static void Set_Field_Camera_Resource_Attribute(shared_ptr<Camera_Component> Instance, const shared_ptr<Camera_Resource>& Value){
                Instance->m_Camera_Resource=Value;
            }

            static const bool Is_Filed_Camera_Resource_CPPVector(void){
                return  false;
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

            static const Vector3& Get_Position_Attribute(shared_ptr<Camera_Component> Instance){
                return Instance->m_Position;
            }

            static void Set_Field_Position_Attribute(shared_ptr<Camera_Component> Instance, const Vector3& Value){
                Instance->m_Position=Value;
            }

            static const bool Is_Filed_Position_CPPVector(void){
                return  false;
            }

            

            static const string Get_Forward_Type_Spelling(void){
                return string{"Vector3"};
            }

            static const string Get_Forward_Spelling(void){
                return string{"m_Forward"};
            }


            static const string Get_Forward_Display_Name(void){
                return string{"Forward"};
            }

            static const Vector3& Get_Forward_Attribute(shared_ptr<Camera_Component> Instance){
                return Instance->m_Forward;
            }

            static void Set_Field_Forward_Attribute(shared_ptr<Camera_Component> Instance, const Vector3& Value){
                Instance->m_Forward=Value;
            }

            static const bool Is_Filed_Forward_CPPVector(void){
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

            static const Vector3& Get_Up_Attribute(shared_ptr<Camera_Component> Instance){
                return Instance->m_Up;
            }

            static void Set_Field_Up_Attribute(shared_ptr<Camera_Component> Instance, const Vector3& Value){
                Instance->m_Up=Value;
            }

            static const bool Is_Filed_Up_CPPVector(void){
                return  false;
            }

            

            static const string Get_Right_Type_Spelling(void){
                return string{"Vector3"};
            }

            static const string Get_Right_Spelling(void){
                return string{"m_Right"};
            }


            static const string Get_Right_Display_Name(void){
                return string{"Right"};
            }

            static const Vector3& Get_Right_Attribute(shared_ptr<Camera_Component> Instance){
                return Instance->m_Right;
            }

            static void Set_Field_Right_Attribute(shared_ptr<Camera_Component> Instance, const Vector3& Value){
                Instance->m_Right=Value;
            }

            static const bool Is_Filed_Right_CPPVector(void){
                return  false;
            }

            


    };
   
}// namespace NameSpace_Function::NameSpace_Frame::NameSpace_Components::NameSpace_Camera

            namespace NameSpace_Core::NameSpace_Meta::NameSpace_Reflection {
                using ::NameSpace_Function::NameSpace_Frame::NameSpace_Components::Component;
	            using ::NameSpace_Function::NameSpace_Frame::NameSpace_Components::NameSpace_Camera::Camera_Component;

	            template<>
	            template<>
	            inline Reflection_Instance<Camera_Component>::operator Reflection_Instance<Component>(void) const {
		            return Reflection_Instance<Component>{
			            std::string{"Camera_Component"},
			            std::static_pointer_cast<Component>(this->m_Instance)
		            }; 
	            }
            };// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Reflection




  //          namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer{
   //             using JSON = nlohmann::json;
//
   //             using ::NameSpace_Function::NameSpace_Frame::NameSpace_Components::Component;
	//            using ::NameSpace_Function::NameSpace_Frame::NameSpace_Components::NameSpace_Camera::Camera_Component;

     //          Reflection_Cast_Tale[string{"Camera_Component"}]=[](const JSON& Json_Context){
      //              auto Temp_Instance=make_shared<Camera_Component>();
       //             Serializer::Read(Json_Context,Temp_Instance);
//
      //              return static_pointer_cast<void>(Temp_Instance);
          //     };
//
    //        }// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer
 

