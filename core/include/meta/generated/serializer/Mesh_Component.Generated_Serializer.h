#include<cstdint>
#include<string>
#include<vector>
#include<memory>

#include "meta/serializer/Serializer.h"
#include "meta/Reflection/Reflection_Instance.h"


#include "D:/Amy_Engine/function/include/frame/components/mesh/Mesh_Component.h"

    namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer{

        using std::string;
        using std::vector;
        using std::shared_ptr;
        using std::make_shared;
        using std::static_pointer_cast;

        using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

        using NameSpace_Function::NameSpace_Frame::NameSpace_Components::Mesh_Component;

        template<> inline const JSON Serializer::Write<Mesh_Component>(const Mesh_Component& Instance){
            JSON Json_Context { JSON::object() };

                    Json_Context["Component"]=Serializer::Write<NameSpace_Function::NameSpace_Frame::NameSpace_Components::Component>(*static_cast<const NameSpace_Function::NameSpace_Frame::NameSpace_Components::Component*>(&Instance));

                Json_Context["Mesh_Res"] = Serializer::Write(Instance.m_Mesh_Res);

            return Json_Context;
        }

        template<> inline Mesh_Component& Serializer::Read<Mesh_Component>(const JSON& Json_Context, Mesh_Component &Instance){
                    Serializer::Read<NameSpace_Function::NameSpace_Frame::NameSpace_Components::Component>(Json_Context["Component"],*static_cast<NameSpace_Function::NameSpace_Frame::NameSpace_Components::Component*>(&Instance));

            if(Json_Context.contains("Mesh_Res")&&!Json_Context["Mesh_Res"].is_null())
                    Serializer::Read(Json_Context["Mesh_Res"],Instance.m_Mesh_Res);

            return Instance;
        }

    }// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer

