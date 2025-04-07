#pragma once

#include<string>
#include<vector>
#include<memory>
#include<cstddef>

#include "json.h"

#include "meta/Reflection/Reflection_Instance.h"

#include "meta/Serializer/Serializer.h"

#include "D:/Amy_Engine/resource/include/components/material/Materia.h"

namespace NameSpace_Resource::NameSpace_Components{

    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;
    using std::static_pointer_cast;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

    class Reflection_Material_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Material"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Material"};            
        }

        

            static const string Get_Base_Colour_Texture_URL_Type_Spelling(void){
                return string{"path"};
            }

            static const string Get_Base_Colour_Texture_URL_Spelling(void){
                return string{"m_Base_Colour_Texture_URL"};
            }


            static const string Get_Base_Colour_Texture_URL_Display_Name(void){
                return string{"Base_Colour_Texture_URL"};
            }

            static const path& Get_Base_Colour_Texture_URL_Attribute(shared_ptr<Material> Instance){
                return Instance->m_Base_Colour_Texture_URL;
            }

            static void Set_Field_Base_Colour_Texture_URL_Attribute(shared_ptr<Material> Instance, const path& Value){
                Instance->m_Base_Colour_Texture_URL=Value;
            }

            static const bool Is_Filed_Base_Colour_Texture_URL_CPPVector(void){
                return  false;
            }

            

            static const string Get_Metallic_Roughness_Texture_URL_Type_Spelling(void){
                return string{"path"};
            }

            static const string Get_Metallic_Roughness_Texture_URL_Spelling(void){
                return string{"m_Metallic_Roughness_Texture_URL"};
            }


            static const string Get_Metallic_Roughness_Texture_URL_Display_Name(void){
                return string{"Metallic_Roughness_Texture_URL"};
            }

            static const path& Get_Metallic_Roughness_Texture_URL_Attribute(shared_ptr<Material> Instance){
                return Instance->m_Metallic_Roughness_Texture_URL;
            }

            static void Set_Field_Metallic_Roughness_Texture_URL_Attribute(shared_ptr<Material> Instance, const path& Value){
                Instance->m_Metallic_Roughness_Texture_URL=Value;
            }

            static const bool Is_Filed_Metallic_Roughness_Texture_URL_CPPVector(void){
                return  false;
            }

            

            static const string Get_Normal_Texture_URL_Type_Spelling(void){
                return string{"path"};
            }

            static const string Get_Normal_Texture_URL_Spelling(void){
                return string{"m_Normal_Texture_URL"};
            }


            static const string Get_Normal_Texture_URL_Display_Name(void){
                return string{"Normal_Texture_URL"};
            }

            static const path& Get_Normal_Texture_URL_Attribute(shared_ptr<Material> Instance){
                return Instance->m_Normal_Texture_URL;
            }

            static void Set_Field_Normal_Texture_URL_Attribute(shared_ptr<Material> Instance, const path& Value){
                Instance->m_Normal_Texture_URL=Value;
            }

            static const bool Is_Filed_Normal_Texture_URL_CPPVector(void){
                return  false;
            }

            

            static const string Get_Occlusion_Texture_URL_Type_Spelling(void){
                return string{"path"};
            }

            static const string Get_Occlusion_Texture_URL_Spelling(void){
                return string{"m_Occlusion_Texture_URL"};
            }


            static const string Get_Occlusion_Texture_URL_Display_Name(void){
                return string{"Occlusion_Texture_URL"};
            }

            static const path& Get_Occlusion_Texture_URL_Attribute(shared_ptr<Material> Instance){
                return Instance->m_Occlusion_Texture_URL;
            }

            static void Set_Field_Occlusion_Texture_URL_Attribute(shared_ptr<Material> Instance, const path& Value){
                Instance->m_Occlusion_Texture_URL=Value;
            }

            static const bool Is_Filed_Occlusion_Texture_URL_CPPVector(void){
                return  false;
            }

            

            static const string Get_Emissive_Texture_URL_Type_Spelling(void){
                return string{"path"};
            }

            static const string Get_Emissive_Texture_URL_Spelling(void){
                return string{"m_Emissive_Texture_URL"};
            }


            static const string Get_Emissive_Texture_URL_Display_Name(void){
                return string{"Emissive_Texture_URL"};
            }

            static const path& Get_Emissive_Texture_URL_Attribute(shared_ptr<Material> Instance){
                return Instance->m_Emissive_Texture_URL;
            }

            static void Set_Field_Emissive_Texture_URL_Attribute(shared_ptr<Material> Instance, const path& Value){
                Instance->m_Emissive_Texture_URL=Value;
            }

            static const bool Is_Filed_Emissive_Texture_URL_CPPVector(void){
                return  false;
            }

            


    };
   
}// namespace NameSpace_Resource::NameSpace_Components

    
 

