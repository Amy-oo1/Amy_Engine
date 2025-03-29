#include<cstdint>
#include<string>
#include<vector>
#include<memory>

#include "meta/serializer/Serializer.h"
#include "meta/Reflection/Reflection_Instance.h"


#include "D:/Amy_Engine/resource/include/components/skeleton/Skeleton_Node.h"

    namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer{

        using std::string;
        using std::vector;
        using std::shared_ptr;
        using std::make_shared;
        using std::static_pointer_cast;

        using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

        using NameSpace_Resource::NameSpace_Components::Skeleton_Node_Map;

        template<> inline const JSON NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer::Write<Skeleton_Node_Map>(const Skeleton_Node_Map& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["Convert"] = Serializer::Write(Instance.m_Convert);

            return Json_Context;
        }

        template<> inline Skeleton_Node_Map& NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer::Read<Skeleton_Node_Map>(const JSON& Json_Context, Skeleton_Node_Map &Instance){
            

                Serializer::Read(Json_Context["Convert"],Instance.m_Convert);

            return Instance;
        }

    }// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer

