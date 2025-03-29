#include<cstdint>
#include<string>
#include<vector>
#include<memory>

#include "meta/serializer/Serializer.h"
#include "meta/Reflection/Reflection_Instance.h"


#include "D:/Amy_Engine/resource/include/components/emitter/Particle.h"

    namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer{

        using std::string;
        using std::vector;
        using std::shared_ptr;
        using std::make_shared;
        using std::static_pointer_cast;

        using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

        using NameSpace_Resource::NameSpace_Components::Particle_Res;

        template<> inline const JSON NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer::Write<Particle_Res>(const Particle_Res& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["Local_Transform"] = Serializer::Write(Instance.m_Local_Transform);
                Json_Context["Velocity"] = Serializer::Write(Instance.m_Velocity);
                Json_Context["Acceleration"] = Serializer::Write(Instance.m_Acceleration);
                Json_Context["Size"] = Serializer::Write(Instance.m_Size);
                Json_Context["Emitter_Type"] = Serializer::Write(Instance.m_Emitter_Type);
                Json_Context["Life"] = Serializer::Write(Instance.m_Life);
                Json_Context["Color"] = Serializer::Write(Instance.m_Color);

            return Json_Context;
        }

        template<> inline Particle_Res& NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer::Read<Particle_Res>(const JSON& Json_Context, Particle_Res &Instance){
            

                Serializer::Read(Json_Context["Local_Transform"],Instance.m_Local_Transform);
                Serializer::Read(Json_Context["Velocity"],Instance.m_Velocity);
                Serializer::Read(Json_Context["Acceleration"],Instance.m_Acceleration);
                Serializer::Read(Json_Context["Size"],Instance.m_Size);
                Serializer::Read(Json_Context["Emitter_Type"],Instance.m_Emitter_Type);
                Serializer::Read(Json_Context["Life"],Instance.m_Life);
                Serializer::Read(Json_Context["Color"],Instance.m_Color);

            return Instance;
        }

    }// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer

