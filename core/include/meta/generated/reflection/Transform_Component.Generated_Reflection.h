#pragma once

#include<string>
#include<vector>
#include<memory>
#include<cstddef>

#include "json.h"

#include "meta/Reflection/Reflection_Instance.h"

#include "meta/Serializer/Serializer.h"

#include "D:/Amy_Engine/function/include/frame/components/transform/Transform_Component.h"

namespace NameSpace_Function::NameSpace_Frame::NameSpace_Components::NameSpace_Transform{

    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;
    using std::static_pointer_cast;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

    class Reflection_Transform_Component_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Transform_Component"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Transform_Component"};            
        }

            static const vector<Reflection_Instance<Transform_Component>> Get_Base_Class_Reflection_Instance_List(shared_ptr<Transform_Component> Instance){
                vector<Reflection_Instance<Transform_Component>> Table;

                        Table.emplace_back(string{"Component"},static_pointer_cast<Transform_Component>(Instance));

                return Table;
            }

            static const string Get_Transform_Type_Spelling(void){
                return string{"Affine_Transform"};
            }

            static const string Get_Transform_Spelling(void){
                return string{"m_Transform"};
            }


            static const string Get_Transform_Display_Name(void){
                return string{"Transform"};
            }

            static const Affine_Transform& Get_Transform_Attribute(shared_ptr<Transform_Component> Instance){
                return Instance->m_Transform;
            }

            static void Set_Field_Transform_Attribute(shared_ptr<Transform_Component> Instance, const Affine_Transform& Value){
                Instance->m_Transform=Value;
            }

            static const bool Is_Filed_Transform_CPPVector(void){
                return  false;
            }

            


    };
   
}// namespace NameSpace_Function::NameSpace_Frame::NameSpace_Components::NameSpace_Transform

            namespace NameSpace_Core::NameSpace_Meta::NameSpace_Reflection {
                using ::NameSpace_Function::NameSpace_Frame::NameSpace_Components::Component;
	            using ::NameSpace_Function::NameSpace_Frame::NameSpace_Components::NameSpace_Transform::Transform_Component;

	            template<>
	            template<>
	            inline Reflection_Instance<Transform_Component>::operator Reflection_Instance<Component>(void) const {
		            return Reflection_Instance<Component>{
			            std::string{"Transform_Component"},
			            std::static_pointer_cast<Component>(this->m_Instance)
		            }; 
	            }
            };// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Reflection




  //          namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer{
   //             using JSON = nlohmann::json;
//
   //             using ::NameSpace_Function::NameSpace_Frame::NameSpace_Components::Component;
	//            using ::NameSpace_Function::NameSpace_Frame::NameSpace_Components::NameSpace_Transform::Transform_Component;

     //          Reflection_Cast_Tale[string{"Transform_Component"}]=[](const JSON& Json_Context){
      //              auto Temp_Instance=make_shared<Transform_Component>();
       //             Serializer::Read(Json_Context,Temp_Instance);
//
      //              return static_pointer_cast<void>(Temp_Instance);
          //     };
//
    //        }// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer
 

