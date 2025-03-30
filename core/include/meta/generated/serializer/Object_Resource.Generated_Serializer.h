#include<cstdint>
#include<string>
#include<vector>
#include<memory>

#include "meta/serializer/Serializer.h"
#include "meta/Reflection/Reflection_Instance.h"


#include "D:/Amy_Engine/resource/include/common/Object_Resource.h"

    namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer{

        using std::string;
        using std::vector;
        using std::shared_ptr;
        using std::make_shared;
        using std::static_pointer_cast;

        using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

        using NameSpace_Resource::NameSpace_Common::Component_Definition;

        template<> inline const JSON Serializer::Write<Component_Definition>(const Component_Definition& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["Type_Name"] = Serializer::Write(Instance.m_Type_Name);
                Json_Context["Component"] = Serializer::Write(Instance.m_Component);

            return Json_Context;
        }

        template<> inline Component_Definition& Serializer::Read<Component_Definition>(const JSON& Json_Context, Component_Definition &Instance){
            

                Serializer::Read(Json_Context["Type_Name"],Instance.m_Type_Name);
                Serializer::Read(Json_Context["Component"],Instance.m_Component);

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

        using NameSpace_Resource::NameSpace_Common::Object_Definition;

        template<> inline const JSON Serializer::Write<Object_Definition>(const Object_Definition& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["Seplling"] = Serializer::Write(Instance.m_Seplling);
                Json_Context["Components"] = Serializer::Write(Instance.m_Components);

            return Json_Context;
        }

        template<> inline Object_Definition& Serializer::Read<Object_Definition>(const JSON& Json_Context, Object_Definition &Instance){
            

                Serializer::Read(Json_Context["Seplling"],Instance.m_Seplling);
                Serializer::Read(Json_Context["Components"],Instance.m_Components);

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

        using NameSpace_Resource::NameSpace_Common::Object_Instance;

        template<> inline const JSON Serializer::Write<Object_Instance>(const Object_Instance& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["Name"] = Serializer::Write(Instance.m_Name);
                Json_Context["Definition_URL"] = Serializer::Write(Instance.m_Definition_URL);
                Json_Context["Instanced_Components"] = Serializer::Write(Instance.m_Instanced_Components);

            return Json_Context;
        }

        template<> inline Object_Instance& Serializer::Read<Object_Instance>(const JSON& Json_Context, Object_Instance &Instance){
            

                Serializer::Read(Json_Context["Name"],Instance.m_Name);
                Serializer::Read(Json_Context["Definition_URL"],Instance.m_Definition_URL);
                Serializer::Read(Json_Context["Instanced_Components"],Instance.m_Instanced_Components);

            return Instance;
        }

    }// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer

