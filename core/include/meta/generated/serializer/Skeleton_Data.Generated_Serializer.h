#include<cstdint>
#include<string>
#include<vector>
#include<memory>

#include "meta/serializer/Serializer.h"
#include "meta/Reflection/Reflection_Instance.h"


#include "D:/Amy_Engine/resource/include/components/skeleton/Skeleton_Data.h"

    namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer{

        using std::string;
        using std::vector;
        using std::shared_ptr;
        using std::make_shared;
        using std::static_pointer_cast;

        using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

        using NameSpace_Resource::NameSpace_Components::Bone_Raw;

        template<> inline const JSON NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer::Write<Bone_Raw>(const Bone_Raw& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["Name"] = Serializer::Write(Instance.m_Name);
                Json_Context["Current_Index"] = Serializer::Write(Instance.m_Current_Index);
                Json_Context["Parent_Index"] = Serializer::Write(Instance.m_Parent_Index);
                Json_Context["Binding_Pose"] = Serializer::Write(Instance.m_Binding_Pose);
                Json_Context["Tpose_Matrix"] = Serializer::Write(Instance.m_Tpose_Matrix);

            return Json_Context;
        }

        template<> inline Bone_Raw& NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer::Read<Bone_Raw>(const JSON& Json_Context, Bone_Raw &Instance){
            

                Serializer::Read(Json_Context["Name"],Instance.m_Name);
                Serializer::Read(Json_Context["Current_Index"],Instance.m_Current_Index);
                Serializer::Read(Json_Context["Parent_Index"],Instance.m_Parent_Index);
                Serializer::Read(Json_Context["Binding_Pose"],Instance.m_Binding_Pose);
                Serializer::Read(Json_Context["Tpose_Matrix"],Instance.m_Tpose_Matrix);

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

        using NameSpace_Resource::NameSpace_Components::Skeleton_Data;

        template<> inline const JSON NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer::Write<Skeleton_Data>(const Skeleton_Data& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["Bones"] = Serializer::Write(Instance.m_Bones);
                Json_Context["Is_Flat"] = Serializer::Write(Instance.m_Is_Flat);
                Json_Context["Root_Index"] = Serializer::Write(Instance.Root_Index);
                Json_Context["In_Topological_Order"] = Serializer::Write(Instance.In_Topological_Order);

            return Json_Context;
        }

        template<> inline Skeleton_Data& NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer::Read<Skeleton_Data>(const JSON& Json_Context, Skeleton_Data &Instance){
            

                Serializer::Read(Json_Context["Bones"],Instance.m_Bones);
                Serializer::Read(Json_Context["Is_Flat"],Instance.m_Is_Flat);
                Serializer::Read(Json_Context["Root_Index"],Instance.Root_Index);
                Serializer::Read(Json_Context["In_Topological_Order"],Instance.In_Topological_Order);

            return Instance;
        }

    }// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer

