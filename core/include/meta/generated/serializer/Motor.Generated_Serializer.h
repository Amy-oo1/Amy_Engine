#include<cstdint>
#include<string>
#include<vector>
#include<memory>

#include "meta/serializer/Serializer.h"
#include "meta/Reflection/Reflection_Instance.h"


#include "D:/Amy_Engine/resource/include/components/motor/Motor.h"

    namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer{

        using std::string;
        using std::vector;
        using std::shared_ptr;
        using std::make_shared;
        using std::static_pointer_cast;

        using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

        using NameSpace_Resource::NameSpace_Components::Physics_Controller_Config;

        template<> inline const JSON NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer::Write<Physics_Controller_Config>(const Physics_Controller_Config& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["Cylinder"] = Serializer::Write(Instance.m_Cylinder);

            return Json_Context;
        }

        template<> inline Physics_Controller_Config& NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer::Read<Physics_Controller_Config>(const JSON& Json_Context, Physics_Controller_Config &Instance){
            

                Serializer::Read(Json_Context["Cylinder"],Instance.m_Cylinder);

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

        using NameSpace_Resource::NameSpace_Components::Motor;

        template<> inline const JSON NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer::Write<Motor>(const Motor& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["Physics_Controller_Config"] = Serializer::Write(Instance.m_Physics_Controller_Config);
                Json_Context["Move_Speed"] = Serializer::Write(Instance.m_Move_Speed);
                Json_Context["Jump_Height"] = Serializer::Write(Instance.m_Jump_Height);
                Json_Context["Max_Move_Speed_Ratio"] = Serializer::Write(Instance.m_Max_Move_Speed_Ratio);
                Json_Context["Max_Sprint_Speed_Ratio"] = Serializer::Write(Instance.m_Max_Sprint_Speed_Ratio);
                Json_Context["Move_Acceleration"] = Serializer::Write(Instance.m_Move_Acceleration);
                Json_Context["Sprint_Acceleration"] = Serializer::Write(Instance.m_Sprint_Acceleration);

            return Json_Context;
        }

        template<> inline Motor& NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer::Read<Motor>(const JSON& Json_Context, Motor &Instance){
            

                Serializer::Read(Json_Context["Physics_Controller_Config"],Instance.m_Physics_Controller_Config);
                Serializer::Read(Json_Context["Move_Speed"],Instance.m_Move_Speed);
                Serializer::Read(Json_Context["Jump_Height"],Instance.m_Jump_Height);
                Serializer::Read(Json_Context["Max_Move_Speed_Ratio"],Instance.m_Max_Move_Speed_Ratio);
                Serializer::Read(Json_Context["Max_Sprint_Speed_Ratio"],Instance.m_Max_Sprint_Speed_Ratio);
                Serializer::Read(Json_Context["Move_Acceleration"],Instance.m_Move_Acceleration);
                Serializer::Read(Json_Context["Sprint_Acceleration"],Instance.m_Sprint_Acceleration);

            return Instance;
        }

    }// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer

