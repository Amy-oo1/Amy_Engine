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
                Json_Context["Texture_Coordinates"] = Serializer::Write(Instance.m_Texture_Coordinates);

            return Json_Context;
        }

        template<> inline Mesh_Vertex& Serializer::Read<Mesh_Vertex>(const JSON& Json_Context, Mesh_Vertex &Instance){
            

            if(Json_Context.contains("Position")&&!Json_Context["Position"].is_null())
                    Serializer::Read(Json_Context["Position"],Instance.m_Position);
            if(Json_Context.contains("Normal")&&!Json_Context["Normal"].is_null())
                    Serializer::Read(Json_Context["Normal"],Instance.m_Normal);
            if(Json_Context.contains("Tangent")&&!Json_Context["Tangent"].is_null())
                    Serializer::Read(Json_Context["Tangent"],Instance.m_Tangent);
            if(Json_Context.contains("Texture_Coordinates")&&!Json_Context["Texture_Coordinates"].is_null())
                    Serializer::Read(Json_Context["Texture_Coordinates"],Instance.m_Texture_Coordinates);

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

            

                Json_Context["Index_0"] = Serializer::Write(Instance.m_Index_0);
                Json_Context["Index_1"] = Serializer::Write(Instance.m_Index_1);
                Json_Context["Index_2"] = Serializer::Write(Instance.m_Index_2);
                Json_Context["Index_3"] = Serializer::Write(Instance.m_Index_3);
                Json_Context["Weight_0"] = Serializer::Write(Instance.m_Weight_0);
                Json_Context["Weight_1"] = Serializer::Write(Instance.m_Weight_1);
                Json_Context["Weight_2"] = Serializer::Write(Instance.m_Weight_2);
                Json_Context["Weight_3"] = Serializer::Write(Instance.m_Weight_3);

            return Json_Context;
        }

        template<> inline Meah_Skeleton_Binding& Serializer::Read<Meah_Skeleton_Binding>(const JSON& Json_Context, Meah_Skeleton_Binding &Instance){
            

            if(Json_Context.contains("Index_0")&&!Json_Context["Index_0"].is_null())
                    Serializer::Read(Json_Context["Index_0"],Instance.m_Index_0);
            if(Json_Context.contains("Index_1")&&!Json_Context["Index_1"].is_null())
                    Serializer::Read(Json_Context["Index_1"],Instance.m_Index_1);
            if(Json_Context.contains("Index_2")&&!Json_Context["Index_2"].is_null())
                    Serializer::Read(Json_Context["Index_2"],Instance.m_Index_2);
            if(Json_Context.contains("Index_3")&&!Json_Context["Index_3"].is_null())
                    Serializer::Read(Json_Context["Index_3"],Instance.m_Index_3);
            if(Json_Context.contains("Weight_0")&&!Json_Context["Weight_0"].is_null())
                    Serializer::Read(Json_Context["Weight_0"],Instance.m_Weight_0);
            if(Json_Context.contains("Weight_1")&&!Json_Context["Weight_1"].is_null())
                    Serializer::Read(Json_Context["Weight_1"],Instance.m_Weight_1);
            if(Json_Context.contains("Weight_2")&&!Json_Context["Weight_2"].is_null())
                    Serializer::Read(Json_Context["Weight_2"],Instance.m_Weight_2);
            if(Json_Context.contains("Weight_3")&&!Json_Context["Weight_3"].is_null())
                    Serializer::Read(Json_Context["Weight_3"],Instance.m_Weight_3);

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
            

            if(Json_Context.contains("Vertices_Buffer")&&!Json_Context["Vertices_Buffer"].is_null())
                    Serializer::Read(Json_Context["Vertices_Buffer"],Instance.m_Vertices_Buffer);
            if(Json_Context.contains("Indices_Buffer")&&!Json_Context["Indices_Buffer"].is_null())
                    Serializer::Read(Json_Context["Indices_Buffer"],Instance.m_Indices_Buffer);
            if(Json_Context.contains("Skeleton_Bindings")&&!Json_Context["Skeleton_Bindings"].is_null())
                    Serializer::Read(Json_Context["Skeleton_Bindings"],Instance.m_Skeleton_Bindings);

            return Instance;
        }

    }// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer

