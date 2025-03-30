#include<cstdint>
#include<string>
#include<vector>
#include<memory>

#include "meta/serializer/Serializer.h"
#include "meta/Reflection/Reflection_Instance.h"


#include "D:/Amy_Engine/resource/include/global/Global_Particle.h"

    namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer{

        using std::string;
        using std::vector;
        using std::shared_ptr;
        using std::make_shared;
        using std::static_pointer_cast;

        using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

        using NameSpace_Resource::NameSpace_Global::Global_Particle;

        template<> inline const JSON Serializer::Write<Global_Particle>(const Global_Particle& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["Emit_Gap"] = Serializer::Write(Instance.m_Emit_Gap);
                Json_Context["Emit_Count"] = Serializer::Write(Instance.m_Emit_Count);
                Json_Context["Time_Step"] = Serializer::Write(Instance.m_Time_Step);
                Json_Context["Max_Life"] = Serializer::Write(Instance.m_Max_Life);
                Json_Context["Gravity"] = Serializer::Write(Instance.m_Gravity);
                Json_Context["Particle_Billboard_Image_URL"] = Serializer::Write(Instance.m_Particle_Billboard_Image_URL);
                Json_Context["Logo_Image_URL"] = Serializer::Write(Instance.m_Logo_Image_URL);

            return Json_Context;
        }

        template<> inline Global_Particle& Serializer::Read<Global_Particle>(const JSON& Json_Context, Global_Particle &Instance){
            

                Serializer::Read(Json_Context["Emit_Gap"],Instance.m_Emit_Gap);
                Serializer::Read(Json_Context["Emit_Count"],Instance.m_Emit_Count);
                Serializer::Read(Json_Context["Time_Step"],Instance.m_Time_Step);
                Serializer::Read(Json_Context["Max_Life"],Instance.m_Max_Life);
                Serializer::Read(Json_Context["Gravity"],Instance.m_Gravity);
                Serializer::Read(Json_Context["Particle_Billboard_Image_URL"],Instance.m_Particle_Billboard_Image_URL);
                Serializer::Read(Json_Context["Logo_Image_URL"],Instance.m_Logo_Image_URL);

            return Instance;
        }

    }// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer

