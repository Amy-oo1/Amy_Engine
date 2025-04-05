#include<cstdint>
#include<string>
#include<vector>
#include<memory>

#include "meta/serializer/Serializer.h"
#include "meta/Reflection/Reflection_Instance.h"


#include "D:/Amy_Engine/resource/include/components/mesh/Mesh_Data.h"

    namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer{

        using std::string;
        using std::vector;
        using std::shared_ptr;
        using std::make_shared;
        using std::static_pointer_cast;

        using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

        using NameSpace_Resource::NameSpace_Components::Mesh_Vertex;

        template<> inline const JSON Serializer::Write<Mesh_Vertex>(const Mesh_Vertex& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["Position"] = Serializer::Write(Instance.m_Position);
                Json_Context["Normal"] = Serializer::Write(Instance.m_Normal);
                Json_Context["Tangent"] = Serializer::Write(Instance.m_Tangent);
                Json_Context["Texture_Coordinate"] = Serializer::Write(Instance.m_Texture_Coordinate);

            return Json_Context;
        }

        template<> inline Mesh_Vertex& Serializer::Read<Mesh_Vertex>(const JSON& Json_Context, Mesh_Vertex &Instance){
            

                Serializer::Read(Json_Context["Position"],Instance.m_Position);
                Serializer::Read(Json_Context["Normal"],Instance.m_Normal);
                Serializer::Read(Json_Context["Tangent"],Instance.m_Tangent);
                Serializer::Read(Json_Context["Texture_Coordinate"],Instance.m_Texture_Coordinate);

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

        using NameSpace_Resource::NameSpace_Components::Meah_Skeleton_Binding;

        template<> inline const JSON Serializer::Write<Meah_Skeleton_Binding>(const Meah_Skeleton_Binding& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["Bone_Indices"] = Serializer::Write(Instance.m_Bone_Indices);
                Json_Context["Weights"] = Serializer::Write(Instance.m_Weights);

            return Json_Context;
        }

        template<> inline Meah_Skeleton_Binding& Serializer::Read<Meah_Skeleton_Binding>(const JSON& Json_Context, Meah_Skeleton_Binding &Instance){
            

                Serializer::Read(Json_Context["Bone_Indices"],Instance.m_Bone_Indices);
                Serializer::Read(Json_Context["Weights"],Instance.m_Weights);

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

        using NameSpace_Resource::NameSpace_Components::Mesh_Data;

        template<> inline const JSON Serializer::Write<Mesh_Data>(const Mesh_Data& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["Vertices_Buffer"] = Serializer::Write(Instance.m_Vertices_Buffer);
                Json_Context["Indices_Buffer"] = Serializer::Write(Instance.m_Indices_Buffer);
                Json_Context["Skeleton_Bindings"] = Serializer::Write(Instance.m_Skeleton_Bindings);

            return Json_Context;
        }

        template<> inline Mesh_Data& Serializer::Read<Mesh_Data>(const JSON& Json_Context, Mesh_Data &Instance){
            

                Serializer::Read(Json_Context["Vertices_Buffer"],Instance.m_Vertices_Buffer);
                Serializer::Read(Json_Context["Indices_Buffer"],Instance.m_Indices_Buffer);
                Serializer::Read(Json_Context["Skeleton_Bindings"],Instance.m_Skeleton_Bindings);

            return Instance;
        }

    }// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer

