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

        template<> inline const JSON Serializer::Write<Particle_Res>(const Particle_Res& Instance){
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

        template<> inline Particle_Res& Serializer::Read<Particle_Res>(const JSON& Json_Context, Particle_Res &Instance){
            

            if(Json_Context.contains("Local_Transform")&&!Json_Context["Local_Transform"].is_null())
                    Serializer::Read(Json_Context["Local_Transform"],Instance.m_Local_Transform);
            if(Json_Context.contains("Velocity")&&!Json_Context["Velocity"].is_null())
                    Serializer::Read(Json_Context["Velocity"],Instance.m_Velocity);
            if(Json_Context.contains("Acceleration")&&!Json_Context["Acceleration"].is_null())
                    Serializer::Read(Json_Context["Acceleration"],Instance.m_Acceleration);
            if(Json_Context.contains("Size")&&!Json_Context["Size"].is_null())
                    Serializer::Read(Json_Context["Size"],Instance.m_Size);
            if(Json_Context.contains("Emitter_Type")&&!Json_Context["Emitter_Type"].is_null())
                    Serializer::Read(Json_Context["Emitter_Type"],Instance.m_Emitter_Type);
            if(Json_Context.contains("Life")&&!Json_Context["Life"].is_null())
                    Serializer::Read(Json_Context["Life"],Instance.m_Life);
            if(Json_Context.contains("Color")&&!Json_Context["Color"].is_null())
                    Serializer::Read(Json_Context["Color"],Instance.m_Color);

            return Instance;
        }

    }// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer

