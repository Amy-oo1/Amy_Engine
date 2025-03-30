#include<cstdint>
#include<string>
#include<vector>
#include<memory>

#include "meta/serializer/Serializer.h"
#include "meta/Reflection/Reflection_Instance.h"


#include "D:/Amy_Engine/function/include/frame/components/camera/Camera_Component.h"

    namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer{

        using std::string;
        using std::vector;
        using std::shared_ptr;
        using std::make_shared;
        using std::static_pointer_cast;

        using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

        using NameSpace_Function::NameSpace_Frame::NameSpace_Components::NameSpace_Camera::Camera_Component;

        template<> inline const JSON Serializer::Write<Camera_Component>(const Camera_Component& Instance){
            JSON Json_Context { JSON::object() };

                    Json_Context["Component"]=Serializer::Write<NameSpace_Function::NameSpace_Frame::NameSpace_Components::Component>(*static_cast<const NameSpace_Function::NameSpace_Frame::NameSpace_Components::Component*>(&Instance));

                Json_Context["Camera_Resource"] = Serializer::Write(Instance.m_Camera_Resource);
                Json_Context["Position"] = Serializer::Write(Instance.m_Position);
                Json_Context["Forward"] = Serializer::Write(Instance.m_Forward);
                Json_Context["Up"] = Serializer::Write(Instance.m_Up);
                Json_Context["Right"] = Serializer::Write(Instance.m_Right);

            return Json_Context;
        }

        template<> inline Camera_Component& Serializer::Read<Camera_Component>(const JSON& Json_Context, Camera_Component &Instance){
                    Serializer::Read<NameSpace_Function::NameSpace_Frame::NameSpace_Components::Component>(Json_Context["Component"],*static_cast<NameSpace_Function::NameSpace_Frame::NameSpace_Components::Component*>(&Instance));

                Serializer::Read(Json_Context["Camera_Resource"],Instance.m_Camera_Resource);
                Serializer::Read(Json_Context["Position"],Instance.m_Position);
                Serializer::Read(Json_Context["Forward"],Instance.m_Forward);
                Serializer::Read(Json_Context["Up"],Instance.m_Up);
                Serializer::Read(Json_Context["Right"],Instance.m_Right);

            return Instance;
        }

    }// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer

