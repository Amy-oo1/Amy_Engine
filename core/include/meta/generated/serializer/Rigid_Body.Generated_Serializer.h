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

        template<> inline const JSON Serializer::Write<Rigid_Body_Shape>(const Rigid_Body_Shape& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["Global_Transform"] = Serializer::Write(Instance.m_Global_Transform);
                Json_Context["Local_Transform"] = Serializer::Write(Instance.m_Local_Transform);
                Json_Context["Bounding_Box"] = Serializer::Write(Instance.m_Bounding_Box);
                Json_Context["Type"] = Serializer::Write(Instance.m_Type);
                Json_Context["Geometry"] = Serializer::Write(Instance.m_Geometry);

            return Json_Context;
        }

        template<> inline Rigid_Body_Shape& Serializer::Read<Rigid_Body_Shape>(const JSON& Json_Context, Rigid_Body_Shape &Instance){
            

            if(Json_Context.contains("Global_Transform")&&!Json_Context["Global_Transform"].is_null())
                    Serializer::Read(Json_Context["Global_Transform"],Instance.m_Global_Transform);
            if(Json_Context.contains("Local_Transform")&&!Json_Context["Local_Transform"].is_null())
                    Serializer::Read(Json_Context["Local_Transform"],Instance.m_Local_Transform);
            if(Json_Context.contains("Bounding_Box")&&!Json_Context["Bounding_Box"].is_null())
                    Serializer::Read(Json_Context["Bounding_Box"],Instance.m_Bounding_Box);
            if(Json_Context.contains("Type")&&!Json_Context["Type"].is_null())
                    Serializer::Read(Json_Context["Type"],Instance.m_Type);
            if(Json_Context.contains("Geometry")&&!Json_Context["Geometry"].is_null())
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

        template<> inline const JSON Serializer::Write<Rigid_Body_Res>(const Rigid_Body_Res& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["Shapes"] = Serializer::Write(Instance.m_Shapes);
                Json_Context["Inverse_Mass"] = Serializer::Write(Instance.m_Inverse_Mass);
                Json_Context["Actor_Type"] = Serializer::Write(Instance.m_Actor_Type);

            return Json_Context;
        }

        template<> inline Rigid_Body_Res& Serializer::Read<Rigid_Body_Res>(const JSON& Json_Context, Rigid_Body_Res &Instance){
            

            if(Json_Context.contains("Shapes")&&!Json_Context["Shapes"].is_null())
                    Serializer::Read(Json_Context["Shapes"],Instance.m_Shapes);
            if(Json_Context.contains("Inverse_Mass")&&!Json_Context["Inverse_Mass"].is_null())
                    Serializer::Read(Json_Context["Inverse_Mass"],Instance.m_Inverse_Mass);
            if(Json_Context.contains("Actor_Type")&&!Json_Context["Actor_Type"].is_null())
                    Serializer::Read(Json_Context["Actor_Type"],Instance.m_Actor_Type);

            return Instance;
        }

    }// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer

