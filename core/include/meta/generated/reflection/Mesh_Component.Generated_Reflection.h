#pragma once

#include<string>
#include<vector>
#include<memory>
#include<cstddef>

#include "json.h"

#include "meta/Reflection/Reflection_Instance.h"

#include "meta/Serializer/Serializer.h"

#include "D:/Amy_Engine/function/include/frame/components/mesh/Mesh_Component.h"

namespace NameSpace_Function::NameSpace_Frame::NameSpace_Components{

    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;
    using std::static_pointer_cast;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

    class Reflection_Mesh_Component_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Mesh_Component"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Mesh_Component"};            
        }

            static const vector<Reflection_Instance<Mesh_Component>> Get_Base_Class_Reflection_Instance_List(shared_ptr<Mesh_Component> Instance){
                vector<Reflection_Instance<Mesh_Component>> Table;

                        Table.emplace_back(string{"Component"},static_pointer_cast<Mesh_Component>(Instance));

                return Table;
            }

            static const string Get_Mesh_Res_Type_Spelling(void){
                return string{"shared_ptr<Mesh_Resource>"};
            }

            static const string Get_Mesh_Res_Spelling(void){
                return string{"m_Mesh_Res"};
            }


            static const string Get_Mesh_Res_Display_Name(void){
                return string{"Mesh_Res"};
            }

            static const shared_ptr<Mesh_Resource>& Get_Mesh_Res_Attribute(shared_ptr<Mesh_Component> Instance){
                return Instance->m_Mesh_Res;
            }

            static void Set_Field_Mesh_Res_Attribute(shared_ptr<Mesh_Component> Instance, const shared_ptr<Mesh_Resource>& Value){
                Instance->m_Mesh_Res=Value;
            }

            static const bool Is_Filed_Mesh_Res_CPPVector(void){
                return  false;
            }

            


    };
   
}// namespace NameSpace_Function::NameSpace_Frame::NameSpace_Components

            namespace NameSpace_Core::NameSpace_Meta::NameSpace_Reflection {
                using ::NameSpace_Function::NameSpace_Frame::NameSpace_Components::Component;
	            using ::NameSpace_Function::NameSpace_Frame::NameSpace_Components::Mesh_Component;

	            template<>
	            template<>
	            inline Reflection_Instance<Mesh_Component>::operator Reflection_Instance<Component>(void) const {
		            return Reflection_Instance<Component>{
			            std::string{"Mesh_Component"},
			            std::static_pointer_cast<Component>(this->m_Instance)
		            }; 
	            }
            };// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Reflection




  //          namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer{
   //             using JSON = nlohmann::json;
//
   //             using ::NameSpace_Function::NameSpace_Frame::NameSpace_Components::Component;
	//            using ::NameSpace_Function::NameSpace_Frame::NameSpace_Components::Mesh_Component;

     //          Reflection_Cast_Tale[string{"Mesh_Component"}]=[](const JSON& Json_Context){
      //              auto Temp_Instance=make_shared<Mesh_Component>();
       //             Serializer::Read(Json_Context,Temp_Instance);
//
      //              return static_pointer_cast<void>(Temp_Instance);
          //     };
//
    //        }// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer
 

