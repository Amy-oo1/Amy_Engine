#include<cstdint>
#include<string>
#include<vector>
#include<memory>

#include "meta/serializer/Serializer.h"
#include "meta/Reflection/Reflection_Instance.h"


#include "D:/Amy_Engine/resource/include/common/World_Resource.h"

    namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer{

        using std::string;
        using std::vector;
        using std::shared_ptr;
        using std::make_shared;
        using std::static_pointer_cast;

        using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

        using NameSpace_Resource::NameSpace_Common::World_Resource;

        template<> inline const JSON NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer::Write<World_Resource>(const World_Resource& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["Name"] = Serializer::Write(Instance.m_Name);
                Json_Context["Default_Level_URL"] = Serializer::Write(Instance.m_Default_Level_URL);
                Json_Context["Levels_URL"] = Serializer::Write(Instance.m_Levels_URL);

            return Json_Context;
        }

        template<> inline World_Resource& NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer::Read<World_Resource>(const JSON& Json_Context, World_Resource &Instance){
            

                Serializer::Read(Json_Context["Name"],Instance.m_Name);
                Serializer::Read(Json_Context["Default_Level_URL"],Instance.m_Default_Level_URL);
                Serializer::Read(Json_Context["Levels_URL"],Instance.m_Levels_URL);

            return Instance;
        }

    }// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer

