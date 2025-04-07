#include<cstdint>
#include<string>
#include<vector>
#include<memory>

#include "meta/serializer/Serializer.h"
#include "meta/Reflection/Reflection_Instance.h"


#include "D:/Amy_Engine/resource/include/components/mesh/Mesh.h"

    namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer{

        using std::string;
        using std::vector;
        using std::shared_ptr;
        using std::make_shared;
        using std::static_pointer_cast;

        using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

        using NameSpace_Resource::NameSpace_Components::Mesh_Sub;

        template<> inline const JSON Serializer::Write<Mesh_Sub>(const Mesh_Sub& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["OBJ_URL"] = Serializer::Write(Instance.m_OBJ_URL);
                Json_Context["Transform"] = Serializer::Write(Instance.m_Transform);
                Json_Context["Material_URL"] = Serializer::Write(Instance.m_Material_URL);

            return Json_Context;
        }

        template<> inline Mesh_Sub& Serializer::Read<Mesh_Sub>(const JSON& Json_Context, Mesh_Sub &Instance){
            

            if(Json_Context.contains("OBJ_URL")&&!Json_Context["OBJ_URL"].is_null())
                    Serializer::Read(Json_Context["OBJ_URL"],Instance.m_OBJ_URL);
            if(Json_Context.contains("Transform")&&!Json_Context["Transform"].is_null())
                    Serializer::Read(Json_Context["Transform"],Instance.m_Transform);
            if(Json_Context.contains("Material_URL")&&!Json_Context["Material_URL"].is_null())
                    Serializer::Read(Json_Context["Material_URL"],Instance.m_Material_URL);

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

        using NameSpace_Resource::NameSpace_Components::Mesh_Resource;

        template<> inline const JSON Serializer::Write<Mesh_Resource>(const Mesh_Resource& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["Sub_Meshes"] = Serializer::Write(Instance.m_Sub_Meshes);

            return Json_Context;
        }

        template<> inline Mesh_Resource& Serializer::Read<Mesh_Resource>(const JSON& Json_Context, Mesh_Resource &Instance){
            

            if(Json_Context.contains("Sub_Meshes")&&!Json_Context["Sub_Meshes"].is_null())
                    Serializer::Read(Json_Context["Sub_Meshes"],Instance.m_Sub_Meshes);

            return Instance;
        }

    }// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer

