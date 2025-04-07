#include<cstdint>
#include<string>
#include<vector>
#include<memory>

#include "meta/serializer/Serializer.h"
#include "meta/Reflection/Reflection_Instance.h"


#include "D:/Amy_Engine/resource/include/components/camera/Camera_Controller.h"

    namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer{

        using std::string;
        using std::vector;
        using std::shared_ptr;
        using std::make_shared;
        using std::static_pointer_cast;

        using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

        using NameSpace_Resource::NameSpace_Components::Camera_Pose;

        template<> inline const JSON Serializer::Write<Camera_Pose>(const Camera_Pose& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["Position"] = Serializer::Write(Instance.m_Position);
                Json_Context["Target"] = Serializer::Write(Instance.m_Target);
                Json_Context["Up"] = Serializer::Write(Instance.m_Up);

            return Json_Context;
        }

        template<> inline Camera_Pose& Serializer::Read<Camera_Pose>(const JSON& Json_Context, Camera_Pose &Instance){
            

            if(Json_Context.contains("Position")&&!Json_Context["Position"].is_null())
                    Serializer::Read(Json_Context["Position"],Instance.m_Position);
            if(Json_Context.contains("Target")&&!Json_Context["Target"].is_null())
                    Serializer::Read(Json_Context["Target"],Instance.m_Target);
            if(Json_Context.contains("Up")&&!Json_Context["Up"].is_null())
                    Serializer::Read(Json_Context["Up"],Instance.m_Up);

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

        using NameSpace_Resource::NameSpace_Components::Camera_Config;

        template<> inline const JSON Serializer::Write<Camera_Config>(const Camera_Config& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["Pose"] = Serializer::Write(Instance.m_Pose);
                Json_Context["Aspect"] = Serializer::Write(Instance.m_Aspect);
                Json_Context["Z_Near"] = Serializer::Write(Instance.m_Z_Near);
                Json_Context["Z_Far"] = Serializer::Write(Instance.m_Z_Far);

            return Json_Context;
        }

        template<> inline Camera_Config& Serializer::Read<Camera_Config>(const JSON& Json_Context, Camera_Config &Instance){
            

            if(Json_Context.contains("Pose")&&!Json_Context["Pose"].is_null())
                    Serializer::Read(Json_Context["Pose"],Instance.m_Pose);
            if(Json_Context.contains("Aspect")&&!Json_Context["Aspect"].is_null())
                    Serializer::Read(Json_Context["Aspect"],Instance.m_Aspect);
            if(Json_Context.contains("Z_Near")&&!Json_Context["Z_Near"].is_null())
                    Serializer::Read(Json_Context["Z_Near"],Instance.m_Z_Near);
            if(Json_Context.contains("Z_Far")&&!Json_Context["Z_Far"].is_null())
                    Serializer::Read(Json_Context["Z_Far"],Instance.m_Z_Far);

            return Instance;
        }

    }// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer

