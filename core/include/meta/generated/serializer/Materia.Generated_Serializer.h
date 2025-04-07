#include<cstdint>
#include<string>
#include<vector>
#include<memory>

#include "meta/serializer/Serializer.h"
#include "meta/Reflection/Reflection_Instance.h"


#include "D:/Amy_Engine/resource/include/components/material/Materia.h"

    namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer{

        using std::string;
        using std::vector;
        using std::shared_ptr;
        using std::make_shared;
        using std::static_pointer_cast;

        using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

        using NameSpace_Resource::NameSpace_Components::Material;

        template<> inline const JSON Serializer::Write<Material>(const Material& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["Base_Colour_Texture_URL"] = Serializer::Write(Instance.m_Base_Colour_Texture_URL);
                Json_Context["Metallic_Roughness_Texture_URL"] = Serializer::Write(Instance.m_Metallic_Roughness_Texture_URL);
                Json_Context["Normal_Texture_URL"] = Serializer::Write(Instance.m_Normal_Texture_URL);
                Json_Context["Occlusion_Texture_URL"] = Serializer::Write(Instance.m_Occlusion_Texture_URL);
                Json_Context["Emissive_Texture_URL"] = Serializer::Write(Instance.m_Emissive_Texture_URL);

            return Json_Context;
        }

        template<> inline Material& Serializer::Read<Material>(const JSON& Json_Context, Material &Instance){
            

            if(Json_Context.contains("Base_Colour_Texture_URL")&&!Json_Context["Base_Colour_Texture_URL"].is_null())
                    Serializer::Read(Json_Context["Base_Colour_Texture_URL"],Instance.m_Base_Colour_Texture_URL);
            if(Json_Context.contains("Metallic_Roughness_Texture_URL")&&!Json_Context["Metallic_Roughness_Texture_URL"].is_null())
                    Serializer::Read(Json_Context["Metallic_Roughness_Texture_URL"],Instance.m_Metallic_Roughness_Texture_URL);
            if(Json_Context.contains("Normal_Texture_URL")&&!Json_Context["Normal_Texture_URL"].is_null())
                    Serializer::Read(Json_Context["Normal_Texture_URL"],Instance.m_Normal_Texture_URL);
            if(Json_Context.contains("Occlusion_Texture_URL")&&!Json_Context["Occlusion_Texture_URL"].is_null())
                    Serializer::Read(Json_Context["Occlusion_Texture_URL"],Instance.m_Occlusion_Texture_URL);
            if(Json_Context.contains("Emissive_Texture_URL")&&!Json_Context["Emissive_Texture_URL"].is_null())
                    Serializer::Read(Json_Context["Emissive_Texture_URL"],Instance.m_Emissive_Texture_URL);

            return Instance;
        }

    }// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer

