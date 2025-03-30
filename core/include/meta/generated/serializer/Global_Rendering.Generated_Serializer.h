#include<cstdint>
#include<string>
#include<vector>
#include<memory>

#include "meta/serializer/Serializer.h"
#include "meta/Reflection/Reflection_Instance.h"


#include "D:/Amy_Engine/resource/include/global/Global_Rendering.h"

    namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer{

        using std::string;
        using std::vector;
        using std::shared_ptr;
        using std::make_shared;
        using std::static_pointer_cast;

        using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

        using NameSpace_Resource::NameSpace_Global::SkyBox_Irradiance_Map;

        template<> inline const JSON Serializer::Write<SkyBox_Irradiance_Map>(const SkyBox_Irradiance_Map& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["Negative_X_Map_URL"] = Serializer::Write(Instance.m_Negative_X_Map_URL);
                Json_Context["Positive_X_Map_URL"] = Serializer::Write(Instance.m_Positive_X_Map_URL);
                Json_Context["Negative_Y_Map_URL"] = Serializer::Write(Instance.m_Negative_Y_Map_URL);
                Json_Context["Positive_Y_Map_URL"] = Serializer::Write(Instance.m_Positive_Y_Map_URL);
                Json_Context["Negative_Z_Map_URL"] = Serializer::Write(Instance.m_Negative_Z_Map_URL);
                Json_Context["Positive_Z_Map_URL"] = Serializer::Write(Instance.m_Positive_Z_Map_URL);

            return Json_Context;
        }

        template<> inline SkyBox_Irradiance_Map& Serializer::Read<SkyBox_Irradiance_Map>(const JSON& Json_Context, SkyBox_Irradiance_Map &Instance){
            

                Serializer::Read(Json_Context["Negative_X_Map_URL"],Instance.m_Negative_X_Map_URL);
                Serializer::Read(Json_Context["Positive_X_Map_URL"],Instance.m_Positive_X_Map_URL);
                Serializer::Read(Json_Context["Negative_Y_Map_URL"],Instance.m_Negative_Y_Map_URL);
                Serializer::Read(Json_Context["Positive_Y_Map_URL"],Instance.m_Positive_Y_Map_URL);
                Serializer::Read(Json_Context["Negative_Z_Map_URL"],Instance.m_Negative_Z_Map_URL);
                Serializer::Read(Json_Context["Positive_Z_Map_URL"],Instance.m_Positive_Z_Map_URL);

            return Instance;
        }

    }// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer
    namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer{

        using std::string;
        using std::vector;
        using std::shared_ptr;
        using std::make_shared;
        using std::static_pointer_cast;

        using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

        using NameSpace_Resource::NameSpace_Global::SkyBox_Specular_Map;

        template<> inline const JSON Serializer::Write<SkyBox_Specular_Map>(const SkyBox_Specular_Map& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["Negative_X_Map_URL"] = Serializer::Write(Instance.m_Negative_X_Map_URL);
                Json_Context["Positive_X_Map_URL"] = Serializer::Write(Instance.m_Positive_X_Map_URL);
                Json_Context["Negative_Y_Map_URL"] = Serializer::Write(Instance.m_Negative_Y_Map_URL);
                Json_Context["Positive_Y_Map_URL"] = Serializer::Write(Instance.m_Positive_Y_Map_URL);
                Json_Context["Negative_Z_Map_URL"] = Serializer::Write(Instance.m_Negative_Z_Map_URL);
                Json_Context["Positive_Z_Map_URL"] = Serializer::Write(Instance.m_Positive_Z_Map_URL);

            return Json_Context;
        }

        template<> inline SkyBox_Specular_Map& Serializer::Read<SkyBox_Specular_Map>(const JSON& Json_Context, SkyBox_Specular_Map &Instance){
            

                Serializer::Read(Json_Context["Negative_X_Map_URL"],Instance.m_Negative_X_Map_URL);
                Serializer::Read(Json_Context["Positive_X_Map_URL"],Instance.m_Positive_X_Map_URL);
                Serializer::Read(Json_Context["Negative_Y_Map_URL"],Instance.m_Negative_Y_Map_URL);
                Serializer::Read(Json_Context["Positive_Y_Map_URL"],Instance.m_Positive_Y_Map_URL);
                Serializer::Read(Json_Context["Negative_Z_Map_URL"],Instance.m_Negative_Z_Map_URL);
                Serializer::Read(Json_Context["Positive_Z_Map_URL"],Instance.m_Positive_Z_Map_URL);

            return Instance;
        }

    }// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer
    namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer{

        using std::string;
        using std::vector;
        using std::shared_ptr;
        using std::make_shared;
        using std::static_pointer_cast;

        using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

        using NameSpace_Resource::NameSpace_Global::Directional_Light;

        template<> inline const JSON Serializer::Write<Directional_Light>(const Directional_Light& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["Direction"] = Serializer::Write(Instance.m_Direction);
                Json_Context["Color"] = Serializer::Write(Instance.m_Color);

            return Json_Context;
        }

        template<> inline Directional_Light& Serializer::Read<Directional_Light>(const JSON& Json_Context, Directional_Light &Instance){
            

                Serializer::Read(Json_Context["Direction"],Instance.m_Direction);
                Serializer::Read(Json_Context["Color"],Instance.m_Color);

            return Instance;
        }

    }// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer
    namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer{

        using std::string;
        using std::vector;
        using std::shared_ptr;
        using std::make_shared;
        using std::static_pointer_cast;

        using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

        using NameSpace_Resource::NameSpace_Global::Global_Rendering;

        template<> inline const JSON Serializer::Write<Global_Rendering>(const Global_Rendering& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["Enable_FXAA"] = Serializer::Write(Instance.m_Enable_FXAA);
                Json_Context["Skybox_Irradiance_Map"] = Serializer::Write(Instance.m_Skybox_Irradiance_Map);
                Json_Context["Skybox_Specular_Map"] = Serializer::Write(Instance.m_Skybox_Specular_Map);
                Json_Context["BRDF_Map_URL"] = Serializer::Write(Instance.m_BRDF_Map_URL);
                Json_Context["Color_Grading_Map_URL"] = Serializer::Write(Instance.m_Color_Grading_Map_URL);
                Json_Context["Sky_Color"] = Serializer::Write(Instance.m_Sky_Color);
                Json_Context["Ambient_Light"] = Serializer::Write(Instance.m_Ambient_Light);
                Json_Context["Directional_Light"] = Serializer::Write(Instance.m_Directional_Light);
                Json_Context["Camera_Config"] = Serializer::Write(Instance.m_Camera_Config);

            return Json_Context;
        }

        template<> inline Global_Rendering& Serializer::Read<Global_Rendering>(const JSON& Json_Context, Global_Rendering &Instance){
            

                Serializer::Read(Json_Context["Enable_FXAA"],Instance.m_Enable_FXAA);
                Serializer::Read(Json_Context["Skybox_Irradiance_Map"],Instance.m_Skybox_Irradiance_Map);
                Serializer::Read(Json_Context["Skybox_Specular_Map"],Instance.m_Skybox_Specular_Map);
                Serializer::Read(Json_Context["BRDF_Map_URL"],Instance.m_BRDF_Map_URL);
                Serializer::Read(Json_Context["Color_Grading_Map_URL"],Instance.m_Color_Grading_Map_URL);
                Serializer::Read(Json_Context["Sky_Color"],Instance.m_Sky_Color);
                Serializer::Read(Json_Context["Ambient_Light"],Instance.m_Ambient_Light);
                Serializer::Read(Json_Context["Directional_Light"],Instance.m_Directional_Light);
                Serializer::Read(Json_Context["Camera_Config"],Instance.m_Camera_Config);

            return Instance;
        }

    }// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer

