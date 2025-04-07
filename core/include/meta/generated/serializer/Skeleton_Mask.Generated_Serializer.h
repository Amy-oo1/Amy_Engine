#include<cstdint>
#include<string>
#include<vector>
#include<memory>

#include "meta/serializer/Serializer.h"
#include "meta/Reflection/Reflection_Instance.h"


#include "D:/Amy_Engine/resource/include/components/skeleton/Skeleton_Mask.h"

    namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer{

        using std::string;
        using std::vector;
        using std::shared_ptr;
        using std::make_shared;
        using std::static_pointer_cast;

        using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

        using NameSpace_Resource::NameSpace_Components::Bone_Blend_Mask;

        template<> inline const JSON Serializer::Write<Bone_Blend_Mask>(const Bone_Blend_Mask& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["Skeleton_Data_URL"] = Serializer::Write(Instance.m_Skeleton_Data_URL);
                Json_Context["Enabled"] = Serializer::Write(Instance.Enabled);

            return Json_Context;
        }

        template<> inline Bone_Blend_Mask& Serializer::Read<Bone_Blend_Mask>(const JSON& Json_Context, Bone_Blend_Mask &Instance){
            

            if(Json_Context.contains("Skeleton_Data_URL")&&!Json_Context["Skeleton_Data_URL"].is_null())
                    Serializer::Read(Json_Context["Skeleton_Data_URL"],Instance.m_Skeleton_Data_URL);
            if(Json_Context.contains("Enabled")&&!Json_Context["Enabled"].is_null())
                    Serializer::Read(Json_Context["Enabled"],Instance.Enabled);

            return Instance;
        }

    }// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer

