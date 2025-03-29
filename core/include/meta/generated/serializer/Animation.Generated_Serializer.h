#include<cstdint>
#include<string>
#include<vector>
#include<memory>

#include "meta/serializer/Serializer.h"
#include "meta/Reflection/Reflection_Instance.h"


#include "D:/Amy_Engine/resource/include/components/animation/Animation.h"

    namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer{

        using std::string;
        using std::vector;
        using std::shared_ptr;
        using std::make_shared;
        using std::static_pointer_cast;

        using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

        using NameSpace_Resource::NameSpace_Components::Animation_Effect_Element;

        template<> inline const JSON NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer::Write<Animation_Effect_Element>(const Animation_Effect_Element& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["Index"] = Serializer::Write(Instance.m_Index);
                Json_Context["Transform"] = Serializer::Write(Instance.m_Transform);

            return Json_Context;
        }

        template<> inline Animation_Effect_Element& NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer::Read<Animation_Effect_Element>(const JSON& Json_Context, Animation_Effect_Element &Instance){
            

                Serializer::Read(Json_Context["Index"],Instance.m_Index);
                Serializer::Read(Json_Context["Transform"],Instance.m_Transform);

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

        using NameSpace_Resource::NameSpace_Components::Animation_Effect;

        template<> inline const JSON NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer::Write<Animation_Effect>(const Animation_Effect& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["Effects"] = Serializer::Write(Instance.m_Effects);

            return Json_Context;
        }

        template<> inline Animation_Effect& NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer::Read<Animation_Effect>(const JSON& Json_Context, Animation_Effect &Instance){
            

                Serializer::Read(Json_Context["Effects"],Instance.m_Effects);

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

        using NameSpace_Resource::NameSpace_Components::Animation_Component_Res;

        template<> inline const JSON NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer::Write<Animation_Component_Res>(const Animation_Component_Res& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["skeleton_File_Path"] = Serializer::Write(Instance.m_skeleton_File_Path);
                Json_Context["Blend_State"] = Serializer::Write(Instance.m_Blend_State);
                Json_Context["Effect"] = Serializer::Write(Instance.m_Effect);

            return Json_Context;
        }

        template<> inline Animation_Component_Res& NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer::Read<Animation_Component_Res>(const JSON& Json_Context, Animation_Component_Res &Instance){
            

                Serializer::Read(Json_Context["skeleton_File_Path"],Instance.m_skeleton_File_Path);
                Serializer::Read(Json_Context["Blend_State"],Instance.m_Blend_State);
                Serializer::Read(Json_Context["Effect"],Instance.m_Effect);

            return Instance;
        }

    }// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer

