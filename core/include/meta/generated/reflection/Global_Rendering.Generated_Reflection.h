#pragma once

#include<string>
#include<vector>
#include<memory>
#include<cstddef>

#include "meta/Reflection/Reflection_Instance.h"

#include "D:/Amy_Engine/resource/include/global/Global_Rendering.h"

namespace NameSpace_Resource::NameSpace_Global{

    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;
    using std::static_pointer_cast;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

    class Reflection_SkyBox_Irradiance_Map_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"SkyBox_Irradiance_Map"};
        }

        static const string Get_Displaying_Name(void){
            return string{"SkyBox_Irradiance_Map"};            
        }

        

            static const string Get_Negative_X_Map_URL_Type_Spelling(void){
                return string{"path"};
            }

            static const string Get_Negative_X_Map_URL_Spelling(void){
                return string{"m_Negative_X_Map_URL"};
            }


            static const string Get_Negative_X_Map_URL_Display_Name(void){
                return string{"Negative_X_Map_URL"};
            }

            static const path& Get_Negative_X_Map_URL_Attribute(shared_ptr<SkyBox_Irradiance_Map> Instance){
                return Instance->m_Negative_X_Map_URL;
            }

            static void Set_Field_Negative_X_Map_URL_Attribute(shared_ptr<SkyBox_Irradiance_Map> Instance, const path& Value){
                Instance->m_Negative_X_Map_URL=Value;
            }

            static const bool Is_Filed_Negative_X_Map_URL_CPPVector(void){
                return  false;
            }

            

            static const string Get_Positive_X_Map_URL_Type_Spelling(void){
                return string{"path"};
            }

            static const string Get_Positive_X_Map_URL_Spelling(void){
                return string{"m_Positive_X_Map_URL"};
            }


            static const string Get_Positive_X_Map_URL_Display_Name(void){
                return string{"Positive_X_Map_URL"};
            }

            static const path& Get_Positive_X_Map_URL_Attribute(shared_ptr<SkyBox_Irradiance_Map> Instance){
                return Instance->m_Positive_X_Map_URL;
            }

            static void Set_Field_Positive_X_Map_URL_Attribute(shared_ptr<SkyBox_Irradiance_Map> Instance, const path& Value){
                Instance->m_Positive_X_Map_URL=Value;
            }

            static const bool Is_Filed_Positive_X_Map_URL_CPPVector(void){
                return  false;
            }

            

            static const string Get_Negative_Y_Map_URL_Type_Spelling(void){
                return string{"path"};
            }

            static const string Get_Negative_Y_Map_URL_Spelling(void){
                return string{"m_Negative_Y_Map_URL"};
            }


            static const string Get_Negative_Y_Map_URL_Display_Name(void){
                return string{"Negative_Y_Map_URL"};
            }

            static const path& Get_Negative_Y_Map_URL_Attribute(shared_ptr<SkyBox_Irradiance_Map> Instance){
                return Instance->m_Negative_Y_Map_URL;
            }

            static void Set_Field_Negative_Y_Map_URL_Attribute(shared_ptr<SkyBox_Irradiance_Map> Instance, const path& Value){
                Instance->m_Negative_Y_Map_URL=Value;
            }

            static const bool Is_Filed_Negative_Y_Map_URL_CPPVector(void){
                return  false;
            }

            

            static const string Get_Positive_Y_Map_URL_Type_Spelling(void){
                return string{"path"};
            }

            static const string Get_Positive_Y_Map_URL_Spelling(void){
                return string{"m_Positive_Y_Map_URL"};
            }


            static const string Get_Positive_Y_Map_URL_Display_Name(void){
                return string{"Positive_Y_Map_URL"};
            }

            static const path& Get_Positive_Y_Map_URL_Attribute(shared_ptr<SkyBox_Irradiance_Map> Instance){
                return Instance->m_Positive_Y_Map_URL;
            }

            static void Set_Field_Positive_Y_Map_URL_Attribute(shared_ptr<SkyBox_Irradiance_Map> Instance, const path& Value){
                Instance->m_Positive_Y_Map_URL=Value;
            }

            static const bool Is_Filed_Positive_Y_Map_URL_CPPVector(void){
                return  false;
            }

            

            static const string Get_Negative_Z_Map_URL_Type_Spelling(void){
                return string{"path"};
            }

            static const string Get_Negative_Z_Map_URL_Spelling(void){
                return string{"m_Negative_Z_Map_URL"};
            }


            static const string Get_Negative_Z_Map_URL_Display_Name(void){
                return string{"Negative_Z_Map_URL"};
            }

            static const path& Get_Negative_Z_Map_URL_Attribute(shared_ptr<SkyBox_Irradiance_Map> Instance){
                return Instance->m_Negative_Z_Map_URL;
            }

            static void Set_Field_Negative_Z_Map_URL_Attribute(shared_ptr<SkyBox_Irradiance_Map> Instance, const path& Value){
                Instance->m_Negative_Z_Map_URL=Value;
            }

            static const bool Is_Filed_Negative_Z_Map_URL_CPPVector(void){
                return  false;
            }

            

            static const string Get_Positive_Z_Map_URL_Type_Spelling(void){
                return string{"path"};
            }

            static const string Get_Positive_Z_Map_URL_Spelling(void){
                return string{"m_Positive_Z_Map_URL"};
            }


            static const string Get_Positive_Z_Map_URL_Display_Name(void){
                return string{"Positive_Z_Map_URL"};
            }

            static const path& Get_Positive_Z_Map_URL_Attribute(shared_ptr<SkyBox_Irradiance_Map> Instance){
                return Instance->m_Positive_Z_Map_URL;
            }

            static void Set_Field_Positive_Z_Map_URL_Attribute(shared_ptr<SkyBox_Irradiance_Map> Instance, const path& Value){
                Instance->m_Positive_Z_Map_URL=Value;
            }

            static const bool Is_Filed_Positive_Z_Map_URL_CPPVector(void){
                return  false;
            }

            


    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection
namespace NameSpace_Resource::NameSpace_Global{

    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;
    using std::static_pointer_cast;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

    class Reflection_SkyBox_Specular_Map_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"SkyBox_Specular_Map"};
        }

        static const string Get_Displaying_Name(void){
            return string{"SkyBox_Specular_Map"};            
        }

        

            static const string Get_Negative_X_Map_URL_Type_Spelling(void){
                return string{"path"};
            }

            static const string Get_Negative_X_Map_URL_Spelling(void){
                return string{"m_Negative_X_Map_URL"};
            }


            static const string Get_Negative_X_Map_URL_Display_Name(void){
                return string{"Negative_X_Map_URL"};
            }

            static const path& Get_Negative_X_Map_URL_Attribute(shared_ptr<SkyBox_Specular_Map> Instance){
                return Instance->m_Negative_X_Map_URL;
            }

            static void Set_Field_Negative_X_Map_URL_Attribute(shared_ptr<SkyBox_Specular_Map> Instance, const path& Value){
                Instance->m_Negative_X_Map_URL=Value;
            }

            static const bool Is_Filed_Negative_X_Map_URL_CPPVector(void){
                return  false;
            }

            

            static const string Get_Positive_X_Map_URL_Type_Spelling(void){
                return string{"path"};
            }

            static const string Get_Positive_X_Map_URL_Spelling(void){
                return string{"m_Positive_X_Map_URL"};
            }


            static const string Get_Positive_X_Map_URL_Display_Name(void){
                return string{"Positive_X_Map_URL"};
            }

            static const path& Get_Positive_X_Map_URL_Attribute(shared_ptr<SkyBox_Specular_Map> Instance){
                return Instance->m_Positive_X_Map_URL;
            }

            static void Set_Field_Positive_X_Map_URL_Attribute(shared_ptr<SkyBox_Specular_Map> Instance, const path& Value){
                Instance->m_Positive_X_Map_URL=Value;
            }

            static const bool Is_Filed_Positive_X_Map_URL_CPPVector(void){
                return  false;
            }

            

            static const string Get_Negative_Y_Map_URL_Type_Spelling(void){
                return string{"path"};
            }

            static const string Get_Negative_Y_Map_URL_Spelling(void){
                return string{"m_Negative_Y_Map_URL"};
            }


            static const string Get_Negative_Y_Map_URL_Display_Name(void){
                return string{"Negative_Y_Map_URL"};
            }

            static const path& Get_Negative_Y_Map_URL_Attribute(shared_ptr<SkyBox_Specular_Map> Instance){
                return Instance->m_Negative_Y_Map_URL;
            }

            static void Set_Field_Negative_Y_Map_URL_Attribute(shared_ptr<SkyBox_Specular_Map> Instance, const path& Value){
                Instance->m_Negative_Y_Map_URL=Value;
            }

            static const bool Is_Filed_Negative_Y_Map_URL_CPPVector(void){
                return  false;
            }

            

            static const string Get_Positive_Y_Map_URL_Type_Spelling(void){
                return string{"path"};
            }

            static const string Get_Positive_Y_Map_URL_Spelling(void){
                return string{"m_Positive_Y_Map_URL"};
            }


            static const string Get_Positive_Y_Map_URL_Display_Name(void){
                return string{"Positive_Y_Map_URL"};
            }

            static const path& Get_Positive_Y_Map_URL_Attribute(shared_ptr<SkyBox_Specular_Map> Instance){
                return Instance->m_Positive_Y_Map_URL;
            }

            static void Set_Field_Positive_Y_Map_URL_Attribute(shared_ptr<SkyBox_Specular_Map> Instance, const path& Value){
                Instance->m_Positive_Y_Map_URL=Value;
            }

            static const bool Is_Filed_Positive_Y_Map_URL_CPPVector(void){
                return  false;
            }

            

            static const string Get_Negative_Z_Map_URL_Type_Spelling(void){
                return string{"path"};
            }

            static const string Get_Negative_Z_Map_URL_Spelling(void){
                return string{"m_Negative_Z_Map_URL"};
            }


            static const string Get_Negative_Z_Map_URL_Display_Name(void){
                return string{"Negative_Z_Map_URL"};
            }

            static const path& Get_Negative_Z_Map_URL_Attribute(shared_ptr<SkyBox_Specular_Map> Instance){
                return Instance->m_Negative_Z_Map_URL;
            }

            static void Set_Field_Negative_Z_Map_URL_Attribute(shared_ptr<SkyBox_Specular_Map> Instance, const path& Value){
                Instance->m_Negative_Z_Map_URL=Value;
            }

            static const bool Is_Filed_Negative_Z_Map_URL_CPPVector(void){
                return  false;
            }

            

            static const string Get_Positive_Z_Map_URL_Type_Spelling(void){
                return string{"path"};
            }

            static const string Get_Positive_Z_Map_URL_Spelling(void){
                return string{"m_Positive_Z_Map_URL"};
            }


            static const string Get_Positive_Z_Map_URL_Display_Name(void){
                return string{"Positive_Z_Map_URL"};
            }

            static const path& Get_Positive_Z_Map_URL_Attribute(shared_ptr<SkyBox_Specular_Map> Instance){
                return Instance->m_Positive_Z_Map_URL;
            }

            static void Set_Field_Positive_Z_Map_URL_Attribute(shared_ptr<SkyBox_Specular_Map> Instance, const path& Value){
                Instance->m_Positive_Z_Map_URL=Value;
            }

            static const bool Is_Filed_Positive_Z_Map_URL_CPPVector(void){
                return  false;
            }

            


    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection
namespace NameSpace_Resource::NameSpace_Global{

    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;
    using std::static_pointer_cast;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

    class Reflection_Directional_Light_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Directional_Light"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Directional_Light"};            
        }

        

            static const string Get_Direction_Type_Spelling(void){
                return string{"Vector3"};
            }

            static const string Get_Direction_Spelling(void){
                return string{"m_Direction"};
            }


            static const string Get_Direction_Display_Name(void){
                return string{"Direction"};
            }

            static const Vector3& Get_Direction_Attribute(shared_ptr<Directional_Light> Instance){
                return Instance->m_Direction;
            }

            static void Set_Field_Direction_Attribute(shared_ptr<Directional_Light> Instance, const Vector3& Value){
                Instance->m_Direction=Value;
            }

            static const bool Is_Filed_Direction_CPPVector(void){
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

            static const Color& Get_Color_Attribute(shared_ptr<Directional_Light> Instance){
                return Instance->m_Color;
            }

            static void Set_Field_Color_Attribute(shared_ptr<Directional_Light> Instance, const Color& Value){
                Instance->m_Color=Value;
            }

            static const bool Is_Filed_Color_CPPVector(void){
                return  false;
            }

            


    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection
namespace NameSpace_Resource::NameSpace_Global{

    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;
    using std::static_pointer_cast;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

    class Reflection_Global_Rendering_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Global_Rendering"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Global_Rendering"};            
        }

        

            static const string Get_Enable_FXAA_Type_Spelling(void){
                return string{"bool"};
            }

            static const string Get_Enable_FXAA_Spelling(void){
                return string{"m_Enable_FXAA"};
            }


            static const string Get_Enable_FXAA_Display_Name(void){
                return string{"Enable_FXAA"};
            }

            static const bool& Get_Enable_FXAA_Attribute(shared_ptr<Global_Rendering> Instance){
                return Instance->m_Enable_FXAA;
            }

            static void Set_Field_Enable_FXAA_Attribute(shared_ptr<Global_Rendering> Instance, const bool& Value){
                Instance->m_Enable_FXAA=Value;
            }

            static const bool Is_Filed_Enable_FXAA_CPPVector(void){
                return  false;
            }

            

            static const string Get_Skybox_Irradiance_Map_Type_Spelling(void){
                return string{"shared_ptr<SkyBox_Irradiance_Map>"};
            }

            static const string Get_Skybox_Irradiance_Map_Spelling(void){
                return string{"m_Skybox_Irradiance_Map"};
            }


            static const string Get_Skybox_Irradiance_Map_Display_Name(void){
                return string{"Skybox_Irradiance_Map"};
            }

            static const shared_ptr<SkyBox_Irradiance_Map>& Get_Skybox_Irradiance_Map_Attribute(shared_ptr<Global_Rendering> Instance){
                return Instance->m_Skybox_Irradiance_Map;
            }

            static void Set_Field_Skybox_Irradiance_Map_Attribute(shared_ptr<Global_Rendering> Instance, const shared_ptr<SkyBox_Irradiance_Map>& Value){
                Instance->m_Skybox_Irradiance_Map=Value;
            }

            static const bool Is_Filed_Skybox_Irradiance_Map_CPPVector(void){
                return  false;
            }

            

            static const string Get_Skybox_Specular_Map_Type_Spelling(void){
                return string{"shared_ptr<SkyBox_Specular_Map>"};
            }

            static const string Get_Skybox_Specular_Map_Spelling(void){
                return string{"m_Skybox_Specular_Map"};
            }


            static const string Get_Skybox_Specular_Map_Display_Name(void){
                return string{"Skybox_Specular_Map"};
            }

            static const shared_ptr<SkyBox_Specular_Map>& Get_Skybox_Specular_Map_Attribute(shared_ptr<Global_Rendering> Instance){
                return Instance->m_Skybox_Specular_Map;
            }

            static void Set_Field_Skybox_Specular_Map_Attribute(shared_ptr<Global_Rendering> Instance, const shared_ptr<SkyBox_Specular_Map>& Value){
                Instance->m_Skybox_Specular_Map=Value;
            }

            static const bool Is_Filed_Skybox_Specular_Map_CPPVector(void){
                return  false;
            }

            

            static const string Get_BRDF_Map_URL_Type_Spelling(void){
                return string{"path"};
            }

            static const string Get_BRDF_Map_URL_Spelling(void){
                return string{"m_BRDF_Map_URL"};
            }


            static const string Get_BRDF_Map_URL_Display_Name(void){
                return string{"BRDF_Map_URL"};
            }

            static const path& Get_BRDF_Map_URL_Attribute(shared_ptr<Global_Rendering> Instance){
                return Instance->m_BRDF_Map_URL;
            }

            static void Set_Field_BRDF_Map_URL_Attribute(shared_ptr<Global_Rendering> Instance, const path& Value){
                Instance->m_BRDF_Map_URL=Value;
            }

            static const bool Is_Filed_BRDF_Map_URL_CPPVector(void){
                return  false;
            }

            

            static const string Get_Color_Grading_Map_URL_Type_Spelling(void){
                return string{"path"};
            }

            static const string Get_Color_Grading_Map_URL_Spelling(void){
                return string{"m_Color_Grading_Map_URL"};
            }


            static const string Get_Color_Grading_Map_URL_Display_Name(void){
                return string{"Color_Grading_Map_URL"};
            }

            static const path& Get_Color_Grading_Map_URL_Attribute(shared_ptr<Global_Rendering> Instance){
                return Instance->m_Color_Grading_Map_URL;
            }

            static void Set_Field_Color_Grading_Map_URL_Attribute(shared_ptr<Global_Rendering> Instance, const path& Value){
                Instance->m_Color_Grading_Map_URL=Value;
            }

            static const bool Is_Filed_Color_Grading_Map_URL_CPPVector(void){
                return  false;
            }

            

            static const string Get_Sky_Color_Type_Spelling(void){
                return string{"Color"};
            }

            static const string Get_Sky_Color_Spelling(void){
                return string{"m_Sky_Color"};
            }


            static const string Get_Sky_Color_Display_Name(void){
                return string{"Sky_Color"};
            }

            static const Color& Get_Sky_Color_Attribute(shared_ptr<Global_Rendering> Instance){
                return Instance->m_Sky_Color;
            }

            static void Set_Field_Sky_Color_Attribute(shared_ptr<Global_Rendering> Instance, const Color& Value){
                Instance->m_Sky_Color=Value;
            }

            static const bool Is_Filed_Sky_Color_CPPVector(void){
                return  false;
            }

            

            static const string Get_Ambient_Light_Type_Spelling(void){
                return string{"Color"};
            }

            static const string Get_Ambient_Light_Spelling(void){
                return string{"m_Ambient_Light"};
            }


            static const string Get_Ambient_Light_Display_Name(void){
                return string{"Ambient_Light"};
            }

            static const Color& Get_Ambient_Light_Attribute(shared_ptr<Global_Rendering> Instance){
                return Instance->m_Ambient_Light;
            }

            static void Set_Field_Ambient_Light_Attribute(shared_ptr<Global_Rendering> Instance, const Color& Value){
                Instance->m_Ambient_Light=Value;
            }

            static const bool Is_Filed_Ambient_Light_CPPVector(void){
                return  false;
            }

            

            static const string Get_Directional_Light_Type_Spelling(void){
                return string{"shared_ptr<Directional_Light>"};
            }

            static const string Get_Directional_Light_Spelling(void){
                return string{"m_Directional_Light"};
            }


            static const string Get_Directional_Light_Display_Name(void){
                return string{"Directional_Light"};
            }

            static const shared_ptr<Directional_Light>& Get_Directional_Light_Attribute(shared_ptr<Global_Rendering> Instance){
                return Instance->m_Directional_Light;
            }

            static void Set_Field_Directional_Light_Attribute(shared_ptr<Global_Rendering> Instance, const shared_ptr<Directional_Light>& Value){
                Instance->m_Directional_Light=Value;
            }

            static const bool Is_Filed_Directional_Light_CPPVector(void){
                return  false;
            }

            

            static const string Get_Camera_Config_Type_Spelling(void){
                return string{"shared_ptr<Camera_Config>"};
            }

            static const string Get_Camera_Config_Spelling(void){
                return string{"m_Camera_Config"};
            }


            static const string Get_Camera_Config_Display_Name(void){
                return string{"Camera_Config"};
            }

            static const shared_ptr<Camera_Config>& Get_Camera_Config_Attribute(shared_ptr<Global_Rendering> Instance){
                return Instance->m_Camera_Config;
            }

            static void Set_Field_Camera_Config_Attribute(shared_ptr<Global_Rendering> Instance, const shared_ptr<Camera_Config>& Value){
                Instance->m_Camera_Config=Value;
            }

            static const bool Is_Filed_Camera_Config_CPPVector(void){
                return  false;
            }

            


    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection

