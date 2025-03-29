#include<cstdint>
#include<string>
#include<vector>
#include<memory>

#include "meta/serializer/Serializer.h"
#include "meta/Reflection/Reflection_Instance.h"


#include "D:/Amy_Engine/resource/include/components/mesh/mesh.h"

    namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer{

        using std::string;
        using std::vector;
        using std::shared_ptr;
        using std::make_shared;
        using std::static_pointer_cast;

        using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

        using NameSpace_Resource::NameSpace_Components::Mesh_Sub;

        template<> inline const JSON NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer::Write<Mesh_Sub>(const Mesh_Sub& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["Object_Path"] = Serializer::Write(Instance.m_Object_Path);
                Json_Context["Transform"] = Serializer::Write(Instance.m_Transform);
                Json_Context["Material"] = Serializer::Write(Instance.m_Material);

            return Json_Context;
        }

        template<> inline Mesh_Sub& NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer::Read<Mesh_Sub>(const JSON& Json_Context, Mesh_Sub &Instance){
            

                Serializer::Read(Json_Context["Object_Path"],Instance.m_Object_Path);
                Serializer::Read(Json_Context["Transform"],Instance.m_Transform);
                Serializer::Read(Json_Context["Material"],Instance.m_Material);

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

        using NameSpace_Resource::NameSpace_Components::Mesh;

        template<> inline const JSON NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer::Write<Mesh>(const Mesh& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["Meshes"] = Serializer::Write(Instance.m_Meshes);

            return Json_Context;
        }

        template<> inline Mesh& NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer::Read<Mesh>(const JSON& Json_Context, Mesh &Instance){
            

                Serializer::Read(Json_Context["Meshes"],Instance.m_Meshes);

            return Instance;
        }

    }// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer

