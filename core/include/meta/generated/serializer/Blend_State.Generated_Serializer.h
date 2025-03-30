#include<cstdint>
#include<string>
#include<vector>
#include<memory>

#include "meta/serializer/Serializer.h"
#include "meta/Reflection/Reflection_Instance.h"


#include "D:/Amy_Engine/resource/include/components/animation/Blend_State.h"

    namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer{

        using std::string;
        using std::vector;
        using std::shared_ptr;
        using std::make_shared;
        using std::static_pointer_cast;

        using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

        using NameSpace_Resource::NameSpace_Components::Bone_Blend_Weight;

        template<> inline const JSON Serializer::Write<Bone_Blend_Weight>(const Bone_Blend_Weight& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["Blend_Weights"] = Serializer::Write(Instance.m_Blend_Weights);

            return Json_Context;
        }

        template<> inline Bone_Blend_Weight& Serializer::Read<Bone_Blend_Weight>(const JSON& Json_Context, Bone_Blend_Weight &Instance){
            

                Serializer::Read(Json_Context["Blend_Weights"],Instance.m_Blend_Weights);

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

        using NameSpace_Resource::NameSpace_Components::BlendState_With_Clip_Data;

        template<> inline const JSON Serializer::Write<BlendState_With_Clip_Data>(const BlendState_With_Clip_Data& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["Blend_Clip"] = Serializer::Write(Instance.m_Blend_Clip);
                Json_Context["Blend_Skeleton"] = Serializer::Write(Instance.m_Blend_Skeleton);
                Json_Context["Blend_Weights"] = Serializer::Write(Instance.m_Blend_Weights);
                Json_Context["Blend_ratio"] = Serializer::Write(Instance.m_Blend_ratio);

            return Json_Context;
        }

        template<> inline BlendState_With_Clip_Data& Serializer::Read<BlendState_With_Clip_Data>(const JSON& Json_Context, BlendState_With_Clip_Data &Instance){
            

                Serializer::Read(Json_Context["Blend_Clip"],Instance.m_Blend_Clip);
                Serializer::Read(Json_Context["Blend_Skeleton"],Instance.m_Blend_Skeleton);
                Serializer::Read(Json_Context["Blend_Weights"],Instance.m_Blend_Weights);
                Serializer::Read(Json_Context["Blend_ratio"],Instance.m_Blend_ratio);

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

        using NameSpace_Resource::NameSpace_Components::Blend_State;

        template<> inline const JSON Serializer::Write<Blend_State>(const Blend_State& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["Blend_Clip_URL"] = Serializer::Write(Instance.m_Blend_Clip_URL);
                Json_Context["Blend_Clip_Length"] = Serializer::Write(Instance.m_Blend_Clip_Length);
                Json_Context["Blend_Skeleton_Node_Map_URL"] = Serializer::Write(Instance.m_Blend_Skeleton_Node_Map_URL);
                Json_Context["Blend_Weights"] = Serializer::Write(Instance.m_Blend_Weights);
                Json_Context["Blend_Mask_URL"] = Serializer::Write(Instance.m_Blend_Mask_URL);
                Json_Context["Blend_Ratio"] = Serializer::Write(Instance.m_Blend_Ratio);

            return Json_Context;
        }

        template<> inline Blend_State& Serializer::Read<Blend_State>(const JSON& Json_Context, Blend_State &Instance){
            

                Serializer::Read(Json_Context["Blend_Clip_URL"],Instance.m_Blend_Clip_URL);
                Serializer::Read(Json_Context["Blend_Clip_Length"],Instance.m_Blend_Clip_Length);
                Serializer::Read(Json_Context["Blend_Skeleton_Node_Map_URL"],Instance.m_Blend_Skeleton_Node_Map_URL);
                Serializer::Read(Json_Context["Blend_Weights"],Instance.m_Blend_Weights);
                Serializer::Read(Json_Context["Blend_Mask_URL"],Instance.m_Blend_Mask_URL);
                Serializer::Read(Json_Context["Blend_Ratio"],Instance.m_Blend_Ratio);

            return Instance;
        }

    }// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer

