#include<cstdint>
#include<string>
#include<vector>
#include<memory>

#include "meta/serializer/Serializer.h"
#include "meta/Reflection/Reflection_Instance.h"


#include "D:/Amy_Engine/function/include/frame/components/transform/Transform_Component.h"

    namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer{

        using std::string;
        using std::vector;
        using std::shared_ptr;
        using std::make_shared;
        using std::static_pointer_cast;

        using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

        using NameSpace_Function::NameSpace_Frame::NameSpace_Components::NameSpace_Transform::Transform_Component;

        template<> inline const JSON Serializer::Write<Transform_Component>(const Transform_Component& Instance){
            JSON Json_Context { JSON::object() };

                    Json_Context["Component"]=Serializer::Write<NameSpace_Function::NameSpace_Frame::NameSpace_Components::Component>(*static_cast<const NameSpace_Function::NameSpace_Frame::NameSpace_Components::Component*>(&Instance));

                Json_Context["Transform"] = Serializer::Write(Instance.m_Transform);

            return Json_Context;
        }

        template<> inline Transform_Component& Serializer::Read<Transform_Component>(const JSON& Json_Context, Transform_Component &Instance){
                    Serializer::Read<NameSpace_Function::NameSpace_Frame::NameSpace_Components::Component>(Json_Context["Component"],*static_cast<NameSpace_Function::NameSpace_Frame::NameSpace_Components::Component*>(&Instance));

            if(Json_Context.contains("Transform")&&!Json_Context["Transform"].is_null())
                    Serializer::Read(Json_Context["Transform"],Instance.m_Transform);

            return Instance;
        }

    }// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer

