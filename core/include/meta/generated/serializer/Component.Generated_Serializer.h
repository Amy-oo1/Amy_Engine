#include<cstdint>
#include<string>
#include<vector>
#include<memory>

#include "meta/serializer/Serializer.h"
#include "meta/Reflection/Reflection_Instance.h"


#include "D:/Amy_Engine/function/include/frame/components/Component.h"

    namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer{

        using std::string;
        using std::vector;
        using std::shared_ptr;
        using std::make_shared;
        using std::static_pointer_cast;

        using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

        using NameSpace_Function::Namespace_Frame::NameSpace_Components::Component;

        template<> inline const JSON NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer::Write<Component>(const Component& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["Parent_GObject"] = Serializer::Write(Instance.m_Parent_GObject);
                Json_Context["Is_Dirty"] = Serializer::Write(Instance.m_Is_Dirty);
                Json_Context["Is_Scale_Dirty"] = Serializer::Write(Instance.m_Is_Scale_Dirty);
                Json_Context["Tick_In_Editor_Mode"] = Serializer::Write(Instance.m_Tick_In_Editor_Mode);

            return Json_Context;
        }

        template<> inline Component& NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer::Read<Component>(const JSON& Json_Context, Component &Instance){
            

                Serializer::Read(Json_Context["Parent_GObject"],Instance.m_Parent_GObject);
                Serializer::Read(Json_Context["Is_Dirty"],Instance.m_Is_Dirty);
                Serializer::Read(Json_Context["Is_Scale_Dirty"],Instance.m_Is_Scale_Dirty);
                Serializer::Read(Json_Context["Tick_In_Editor_Mode"],Instance.m_Tick_In_Editor_Mode);

            return Instance;
        }

    }// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer

