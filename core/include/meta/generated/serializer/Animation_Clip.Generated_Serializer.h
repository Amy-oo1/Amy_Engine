#include<cstdint>
#include<string>
#include<vector>
#include<memory>

#include "meta/serializer/Serializer.h"
#include "meta/Reflection/Reflection_Instance.h"


#include "D:/Amy_Engine/resource/include/components/animation/Animation_Clip.h"

    namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer{

        using std::string;
        using std::vector;
        using std::shared_ptr;
        using std::make_shared;
        using std::static_pointer_cast;

        using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

        using NameSpace_Resource::NameSpace_Components::Animation_Node_Map;

        template<> inline const JSON NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer::Write<Animation_Node_Map>(const Animation_Node_Map& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["Convert"] = Serializer::Write(Instance.m_Convert);

            return Json_Context;
        }

        template<> inline Animation_Node_Map& NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer::Read<Animation_Node_Map>(const JSON& Json_Context, Animation_Node_Map &Instance){
            

                Serializer::Read(Json_Context["Convert"],Instance.m_Convert);

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

        using NameSpace_Resource::NameSpace_Components::Animation_Channel;

        template<> inline const JSON NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer::Write<Animation_Channel>(const Animation_Channel& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["Name"] = Serializer::Write(Instance.m_Name);
                Json_Context["Positions_Keys"] = Serializer::Write(Instance.m_Positions_Keys);
                Json_Context["Rotations_Keys"] = Serializer::Write(Instance.m_Rotations_Keys);
                Json_Context["Scales_Keys"] = Serializer::Write(Instance.m_Scales_Keys);

            return Json_Context;
        }

        template<> inline Animation_Channel& NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer::Read<Animation_Channel>(const JSON& Json_Context, Animation_Channel &Instance){
            

                Serializer::Read(Json_Context["Name"],Instance.m_Name);
                Serializer::Read(Json_Context["Positions_Keys"],Instance.m_Positions_Keys);
                Serializer::Read(Json_Context["Rotations_Keys"],Instance.m_Rotations_Keys);
                Serializer::Read(Json_Context["Scales_Keys"],Instance.m_Scales_Keys);

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

        using NameSpace_Resource::NameSpace_Components::Animation_Clip;

        template<> inline const JSON NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer::Write<Animation_Clip>(const Animation_Clip& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["Total_Frame"] = Serializer::Write(Instance.Total_Frame);
                Json_Context["Node_Channels"] = Serializer::Write(Instance.m_Node_Channels);

            return Json_Context;
        }

        template<> inline Animation_Clip& NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer::Read<Animation_Clip>(const JSON& Json_Context, Animation_Clip &Instance){
            

                Serializer::Read(Json_Context["Total_Frame"],Instance.Total_Frame);
                Serializer::Read(Json_Context["Node_Channels"],Instance.m_Node_Channels);

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

        using NameSpace_Resource::NameSpace_Components::Animation_Data;

        template<> inline const JSON NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer::Write<Animation_Data>(const Animation_Data& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["Skeleton_Data_URL"] = Serializer::Write(Instance.m_Skeleton_Data_URL);
                Json_Context["Node_Map"] = Serializer::Write(Instance.m_Node_Map);
                Json_Context["Clips"] = Serializer::Write(Instance.m_Clips);

            return Json_Context;
        }

        template<> inline Animation_Data& NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer::Read<Animation_Data>(const JSON& Json_Context, Animation_Data &Instance){
            

                Serializer::Read(Json_Context["Skeleton_Data_URL"],Instance.m_Skeleton_Data_URL);
                Serializer::Read(Json_Context["Node_Map"],Instance.m_Node_Map);
                Serializer::Read(Json_Context["Clips"],Instance.m_Clips);

            return Instance;
        }

    }// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer

