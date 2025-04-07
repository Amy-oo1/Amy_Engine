#include<cstdint>
#include<string>
#include<vector>
#include<memory>

#include "meta/serializer/Serializer.h"
#include "meta/Reflection/Reflection_Instance.h"


#include "D:/Amy_Engine/resource/include/components/rigid_body/Basic_Shape.h"

    namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer{

        using std::string;
        using std::vector;
        using std::shared_ptr;
        using std::make_shared;
        using std::static_pointer_cast;

        using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

        using NameSpace_Resource::NameSpace_Components::Geometry_Base;

        template<> inline const JSON Serializer::Write<Geometry_Base>(const Geometry_Base& Instance){
            JSON Json_Context { JSON::object() };

            

            

            return Json_Context;
        }

        template<> inline Geometry_Base& Serializer::Read<Geometry_Base>(const JSON& Json_Context, Geometry_Base &Instance){
            

            

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

        using NameSpace_Resource::NameSpace_Components::Geometry_Box;

        template<> inline const JSON Serializer::Write<Geometry_Box>(const Geometry_Box& Instance){
            JSON Json_Context { JSON::object() };

                    Json_Context["Geometry_Base"]=Serializer::Write<NameSpace_Resource::NameSpace_Components::Geometry_Base>(*static_cast<const NameSpace_Resource::NameSpace_Components::Geometry_Base*>(&Instance));

                Json_Context["Half_Extents"] = Serializer::Write(Instance.m_Half_Extents);

            return Json_Context;
        }

        template<> inline Geometry_Box& Serializer::Read<Geometry_Box>(const JSON& Json_Context, Geometry_Box &Instance){
                    Serializer::Read<NameSpace_Resource::NameSpace_Components::Geometry_Base>(Json_Context["Geometry_Base"],*static_cast<NameSpace_Resource::NameSpace_Components::Geometry_Base*>(&Instance));

            if(Json_Context.contains("Half_Extents")&&!Json_Context["Half_Extents"].is_null())
                    Serializer::Read(Json_Context["Half_Extents"],Instance.m_Half_Extents);

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

        using NameSpace_Resource::NameSpace_Components::Geometry_Sphere;

        template<> inline const JSON Serializer::Write<Geometry_Sphere>(const Geometry_Sphere& Instance){
            JSON Json_Context { JSON::object() };

                    Json_Context["Geometry_Base"]=Serializer::Write<NameSpace_Resource::NameSpace_Components::Geometry_Base>(*static_cast<const NameSpace_Resource::NameSpace_Components::Geometry_Base*>(&Instance));

                Json_Context["radius"] = Serializer::Write(Instance.m_radius);

            return Json_Context;
        }

        template<> inline Geometry_Sphere& Serializer::Read<Geometry_Sphere>(const JSON& Json_Context, Geometry_Sphere &Instance){
                    Serializer::Read<NameSpace_Resource::NameSpace_Components::Geometry_Base>(Json_Context["Geometry_Base"],*static_cast<NameSpace_Resource::NameSpace_Components::Geometry_Base*>(&Instance));

            if(Json_Context.contains("radius")&&!Json_Context["radius"].is_null())
                    Serializer::Read(Json_Context["radius"],Instance.m_radius);

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

        using NameSpace_Resource::NameSpace_Components::Geometry_Cylinder;

        template<> inline const JSON Serializer::Write<Geometry_Cylinder>(const Geometry_Cylinder& Instance){
            JSON Json_Context { JSON::object() };

                    Json_Context["Geometry_Base"]=Serializer::Write<NameSpace_Resource::NameSpace_Components::Geometry_Base>(*static_cast<const NameSpace_Resource::NameSpace_Components::Geometry_Base*>(&Instance));

                Json_Context["Radius"] = Serializer::Write(Instance.m_Radius);
                Json_Context["Half_Height"] = Serializer::Write(Instance.m_Half_Height);

            return Json_Context;
        }

        template<> inline Geometry_Cylinder& Serializer::Read<Geometry_Cylinder>(const JSON& Json_Context, Geometry_Cylinder &Instance){
                    Serializer::Read<NameSpace_Resource::NameSpace_Components::Geometry_Base>(Json_Context["Geometry_Base"],*static_cast<NameSpace_Resource::NameSpace_Components::Geometry_Base*>(&Instance));

            if(Json_Context.contains("Radius")&&!Json_Context["Radius"].is_null())
                    Serializer::Read(Json_Context["Radius"],Instance.m_Radius);
            if(Json_Context.contains("Half_Height")&&!Json_Context["Half_Height"].is_null())
                    Serializer::Read(Json_Context["Half_Height"],Instance.m_Half_Height);

            return Instance;
        }

    }// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer

