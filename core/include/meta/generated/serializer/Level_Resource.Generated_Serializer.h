#include<cstdint>
#include<string>
#include<vector>
#include<memory>

#include "meta/serializer/Serializer.h"
#include "meta/Reflection/Reflection_Instance.h"


#include "D:/Amy_Engine/resource/include/common/Level_Resource.h"

    namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer{

        using std::string;
        using std::vector;
        using std::shared_ptr;
        using std::make_shared;
        using std::static_pointer_cast;

        using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

        using NameSpace_Resource::NameSpace_Common::Level_Resource;

        template<> inline const JSON Serializer::Write<Level_Resource>(const Level_Resource& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["Gravity"] = Serializer::Write(Instance.m_Gravity);
                Json_Context["Character_Name"] = Serializer::Write(Instance.m_Character_Name);
                Json_Context["Objects"] = Serializer::Write(Instance.m_Objects);

            return Json_Context;
        }

        template<> inline Level_Resource& Serializer::Read<Level_Resource>(const JSON& Json_Context, Level_Resource &Instance){
            

            if(Json_Context.contains("Gravity")&&!Json_Context["Gravity"].is_null())
                    Serializer::Read(Json_Context["Gravity"],Instance.m_Gravity);
            if(Json_Context.contains("Character_Name")&&!Json_Context["Character_Name"].is_null())
                    Serializer::Read(Json_Context["Character_Name"],Instance.m_Character_Name);
            if(Json_Context.contains("Objects")&&!Json_Context["Objects"].is_null())
                    Serializer::Read(Json_Context["Objects"],Instance.m_Objects);

            return Instance;
        }

    }// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer

