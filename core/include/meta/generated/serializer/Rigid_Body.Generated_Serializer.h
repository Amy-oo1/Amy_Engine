#include<cstdint>
#include<string>
#include<vector>
#include<memory>

#include "meta/serializer/Serializer.h"
#include "meta/Reflection/Reflection_Instance.h"


#include "D:/Amy_Engine/resource/include/components/rigid_body/Rigid_Body.h"

    namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer{

        using std::string;
        using std::vector;
        using std::shared_ptr;
        using std::make_shared;
        using std::static_pointer_cast;

        using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

        using NameSpace_Resource::NameSpace_Components::Rigid_Body_Shape;

        template<> inline const JSON NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer::Write<Rigid_Body_Shape>(const Rigid_Body_Shape& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["Global_Transform"] = Serializer::Write(Instance.m_Global_Transform);
                Json_Context["Local_Transform"] = Serializer::Write(Instance.m_Local_Transform);
                Json_Context["Bounding_Box"] = Serializer::Write(Instance.m_Bounding_Box);
                Json_Context["Type"] = Serializer::Write(Instance.m_Type);
                Json_Context["Geometry"] = Serializer::Write(Instance.m_Geometry);

            return Json_Context;
        }

        template<> inline Rigid_Body_Shape& NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer::Read<Rigid_Body_Shape>(const JSON& Json_Context, Rigid_Body_Shape &Instance){
            

                Serializer::Read(Json_Context["Global_Transform"],Instance.m_Global_Transform);
                Serializer::Read(Json_Context["Local_Transform"],Instance.m_Local_Transform);
                Serializer::Read(Json_Context["Bounding_Box"],Instance.m_Bounding_Box);
                Serializer::Read(Json_Context["Type"],Instance.m_Type);
                Serializer::Read(Json_Context["Geometry"],Instance.m_Geometry);

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

        using NameSpace_Resource::NameSpace_Components::Rigid_Body_Res;

        template<> inline const JSON NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer::Write<Rigid_Body_Res>(const Rigid_Body_Res& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["Shapes"] = Serializer::Write(Instance.m_Shapes);
                Json_Context["Inverse_Mass"] = Serializer::Write(Instance.m_Inverse_Mass);
                Json_Context["Actor_Type"] = Serializer::Write(Instance.m_Actor_Type);

            return Json_Context;
        }

        template<> inline Rigid_Body_Res& NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer::Read<Rigid_Body_Res>(const JSON& Json_Context, Rigid_Body_Res &Instance){
            

                Serializer::Read(Json_Context["Shapes"],Instance.m_Shapes);
                Serializer::Read(Json_Context["Inverse_Mass"],Instance.m_Inverse_Mass);
                Serializer::Read(Json_Context["Actor_Type"],Instance.m_Actor_Type);

            return Instance;
        }

    }// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer

