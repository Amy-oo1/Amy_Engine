#pragma once

#include<string>
#include<vector>
#include<memory>
#include<cstddef>

#include "json.h"

#include "meta/Reflection/Reflection_Instance.h"

#include "meta/Serializer/Serializer.h"

#include "D:/Amy_Engine/resource/include/components/rigid_body/Basic_Shape.h"

namespace NameSpace_Resource::NameSpace_Components{

    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;
    using std::static_pointer_cast;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

    class Reflection_Geometry_Base_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Geometry_Base"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Geometry_Base"};            
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

    class Reflection_Geometry_Box_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Geometry_Box"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Geometry_Box"};            
        }

            static const vector<Reflection_Instance<Geometry_Box>> Get_Base_Class_Reflection_Instance_List(shared_ptr<Geometry_Box> Instance){
                vector<Reflection_Instance<Geometry_Box>> Table;

                        Table.emplace_back(string{"Geometry_Base"},static_pointer_cast<Geometry_Box>(Instance));

                return Table;
            }

            static const string Get_Half_Extents_Type_Spelling(void){
                return string{"Vector3"};
            }

            static const string Get_Half_Extents_Spelling(void){
                return string{"m_Half_Extents"};
            }


            static const string Get_Half_Extents_Display_Name(void){
                return string{"Half_Extents"};
            }

            static const Vector3& Get_Half_Extents_Attribute(shared_ptr<Geometry_Box> Instance){
                return Instance->m_Half_Extents;
            }

            static void Set_Field_Half_Extents_Attribute(shared_ptr<Geometry_Box> Instance, const Vector3& Value){
                Instance->m_Half_Extents=Value;
            }

            static const bool Is_Filed_Half_Extents_CPPVector(void){
                return  false;
            }

            


    };
   
}// namespace NameSpace_Resource::NameSpace_Components

            namespace NameSpace_Core::NameSpace_Meta::NameSpace_Reflection {
                using ::NameSpace_Resource::NameSpace_Components::Geometry_Base;
	            using ::NameSpace_Resource::NameSpace_Components::Geometry_Box;

	            template<>
	            template<>
	            inline Reflection_Instance<Geometry_Box>::operator Reflection_Instance<Geometry_Base>(void) const {
		            return Reflection_Instance<Geometry_Base>{
			            std::string{"Geometry_Box"},
			            std::static_pointer_cast<Geometry_Base>(this->m_Instance)
		            }; 
	            }
            };// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Reflection




  //          namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer{
   //             using JSON = nlohmann::json;
//
   //             using ::NameSpace_Resource::NameSpace_Components::Geometry_Base;
	//            using ::NameSpace_Resource::NameSpace_Components::Geometry_Box;

     //          Reflection_Cast_Tale[string{"Geometry_Box"}]=[](const JSON& Json_Context){
      //              auto Temp_Instance=make_shared<Geometry_Box>();
       //             Serializer::Read(Json_Context,Temp_Instance);
//
      //              return static_pointer_cast<void>(Temp_Instance);
          //     };
//
    //        }// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer
 
namespace NameSpace_Resource::NameSpace_Components{

    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;
    using std::static_pointer_cast;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

    class Reflection_Geometry_Sphere_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Geometry_Sphere"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Geometry_Sphere"};            
        }

            static const vector<Reflection_Instance<Geometry_Sphere>> Get_Base_Class_Reflection_Instance_List(shared_ptr<Geometry_Sphere> Instance){
                vector<Reflection_Instance<Geometry_Sphere>> Table;

                        Table.emplace_back(string{"Geometry_Base"},static_pointer_cast<Geometry_Sphere>(Instance));

                return Table;
            }

            static const string Get_radius_Type_Spelling(void){
                return string{"float"};
            }

            static const string Get_radius_Spelling(void){
                return string{"m_radius"};
            }


            static const string Get_radius_Display_Name(void){
                return string{"radius"};
            }

            static const float& Get_radius_Attribute(shared_ptr<Geometry_Sphere> Instance){
                return Instance->m_radius;
            }

            static void Set_Field_radius_Attribute(shared_ptr<Geometry_Sphere> Instance, const float& Value){
                Instance->m_radius=Value;
            }

            static const bool Is_Filed_radius_CPPVector(void){
                return  false;
            }

            


    };
   
}// namespace NameSpace_Resource::NameSpace_Components

            namespace NameSpace_Core::NameSpace_Meta::NameSpace_Reflection {
                using ::NameSpace_Resource::NameSpace_Components::Geometry_Base;
	            using ::NameSpace_Resource::NameSpace_Components::Geometry_Sphere;

	            template<>
	            template<>
	            inline Reflection_Instance<Geometry_Sphere>::operator Reflection_Instance<Geometry_Base>(void) const {
		            return Reflection_Instance<Geometry_Base>{
			            std::string{"Geometry_Sphere"},
			            std::static_pointer_cast<Geometry_Base>(this->m_Instance)
		            }; 
	            }
            };// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Reflection




  //          namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer{
   //             using JSON = nlohmann::json;
//
   //             using ::NameSpace_Resource::NameSpace_Components::Geometry_Base;
	//            using ::NameSpace_Resource::NameSpace_Components::Geometry_Sphere;

     //          Reflection_Cast_Tale[string{"Geometry_Sphere"}]=[](const JSON& Json_Context){
      //              auto Temp_Instance=make_shared<Geometry_Sphere>();
       //             Serializer::Read(Json_Context,Temp_Instance);
//
      //              return static_pointer_cast<void>(Temp_Instance);
          //     };
//
    //        }// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer
 
namespace NameSpace_Resource::NameSpace_Components{

    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;
    using std::static_pointer_cast;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

    class Reflection_Geometry_Cylinder_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Geometry_Cylinder"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Geometry_Cylinder"};            
        }

            static const vector<Reflection_Instance<Geometry_Cylinder>> Get_Base_Class_Reflection_Instance_List(shared_ptr<Geometry_Cylinder> Instance){
                vector<Reflection_Instance<Geometry_Cylinder>> Table;

                        Table.emplace_back(string{"Geometry_Base"},static_pointer_cast<Geometry_Cylinder>(Instance));

                return Table;
            }

            static const string Get_Radius_Type_Spelling(void){
                return string{"float"};
            }

            static const string Get_Radius_Spelling(void){
                return string{"m_Radius"};
            }


            static const string Get_Radius_Display_Name(void){
                return string{"Radius"};
            }

            static const float& Get_Radius_Attribute(shared_ptr<Geometry_Cylinder> Instance){
                return Instance->m_Radius;
            }

            static void Set_Field_Radius_Attribute(shared_ptr<Geometry_Cylinder> Instance, const float& Value){
                Instance->m_Radius=Value;
            }

            static const bool Is_Filed_Radius_CPPVector(void){
                return  false;
            }

            

            static const string Get_Half_Height_Type_Spelling(void){
                return string{"float"};
            }

            static const string Get_Half_Height_Spelling(void){
                return string{"m_Half_Height"};
            }


            static const string Get_Half_Height_Display_Name(void){
                return string{"Half_Height"};
            }

            static const float& Get_Half_Height_Attribute(shared_ptr<Geometry_Cylinder> Instance){
                return Instance->m_Half_Height;
            }

            static void Set_Field_Half_Height_Attribute(shared_ptr<Geometry_Cylinder> Instance, const float& Value){
                Instance->m_Half_Height=Value;
            }

            static const bool Is_Filed_Half_Height_CPPVector(void){
                return  false;
            }

            


    };
   
}// namespace NameSpace_Resource::NameSpace_Components

            namespace NameSpace_Core::NameSpace_Meta::NameSpace_Reflection {
                using ::NameSpace_Resource::NameSpace_Components::Geometry_Base;
	            using ::NameSpace_Resource::NameSpace_Components::Geometry_Cylinder;

	            template<>
	            template<>
	            inline Reflection_Instance<Geometry_Cylinder>::operator Reflection_Instance<Geometry_Base>(void) const {
		            return Reflection_Instance<Geometry_Base>{
			            std::string{"Geometry_Cylinder"},
			            std::static_pointer_cast<Geometry_Base>(this->m_Instance)
		            }; 
	            }
            };// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Reflection




  //          namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer{
   //             using JSON = nlohmann::json;
//
   //             using ::NameSpace_Resource::NameSpace_Components::Geometry_Base;
	//            using ::NameSpace_Resource::NameSpace_Components::Geometry_Cylinder;

     //          Reflection_Cast_Tale[string{"Geometry_Cylinder"}]=[](const JSON& Json_Context){
      //              auto Temp_Instance=make_shared<Geometry_Cylinder>();
       //             Serializer::Read(Json_Context,Temp_Instance);
//
      //              return static_pointer_cast<void>(Temp_Instance);
          //     };
//
    //        }// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer
 

