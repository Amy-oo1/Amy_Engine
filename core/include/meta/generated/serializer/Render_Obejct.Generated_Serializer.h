#include<cstdint>
#include<string>
#include<vector>
#include<memory>

#include "meta/serializer/Serializer.h"
#include "meta/Reflection/Reflection_Instance.h"


#include "D:/Amy_Engine/function/include/render/render_system/Render_Obejct.h"

    namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer{

        using std::string;
        using std::vector;
        using std::shared_ptr;
        using std::make_shared;
        using std::static_pointer_cast;

        using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

        using NameSpace_Function::NameSpace_Render::NameSpace_Render_System::Game_Object_Mesh_Desc;

        template<> inline const JSON Serializer::Write<Game_Object_Mesh_Desc>(const Game_Object_Mesh_Desc& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["Mesh_URL"] = Serializer::Write(Instance.m_Mesh_URL);

            return Json_Context;
        }

        template<> inline Game_Object_Mesh_Desc& Serializer::Read<Game_Object_Mesh_Desc>(const JSON& Json_Context, Game_Object_Mesh_Desc &Instance){
            

            if(Json_Context.contains("Mesh_URL")&&!Json_Context["Mesh_URL"].is_null())
                    Serializer::Read(Json_Context["Mesh_URL"],Instance.m_Mesh_URL);

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

        using NameSpace_Function::NameSpace_Render::NameSpace_Render_System::Skeleton_Binding_Desc;

        template<> inline const JSON Serializer::Write<Skeleton_Binding_Desc>(const Skeleton_Binding_Desc& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["Skeleton_Binding_URL"] = Serializer::Write(Instance.m_Skeleton_Binding_URL);

            return Json_Context;
        }

        template<> inline Skeleton_Binding_Desc& Serializer::Read<Skeleton_Binding_Desc>(const JSON& Json_Context, Skeleton_Binding_Desc &Instance){
            

            if(Json_Context.contains("Skeleton_Binding_URL")&&!Json_Context["Skeleton_Binding_URL"].is_null())
                    Serializer::Read(Json_Context["Skeleton_Binding_URL"],Instance.m_Skeleton_Binding_URL);

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

        using NameSpace_Function::NameSpace_Render::NameSpace_Render_System::Skeleton_Animation_Result_Transform;

        template<> inline const JSON Serializer::Write<Skeleton_Animation_Result_Transform>(const Skeleton_Animation_Result_Transform& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["Matrix"] = Serializer::Write(Instance.m_Matrix);

            return Json_Context;
        }

        template<> inline Skeleton_Animation_Result_Transform& Serializer::Read<Skeleton_Animation_Result_Transform>(const JSON& Json_Context, Skeleton_Animation_Result_Transform &Instance){
            

            if(Json_Context.contains("Matrix")&&!Json_Context["Matrix"].is_null())
                    Serializer::Read(Json_Context["Matrix"],Instance.m_Matrix);

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

        using NameSpace_Function::NameSpace_Render::NameSpace_Render_System::Skeleton_Animation_Result;

        template<> inline const JSON Serializer::Write<Skeleton_Animation_Result>(const Skeleton_Animation_Result& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["Transforms"] = Serializer::Write(Instance.m_Transforms);

            return Json_Context;
        }

        template<> inline Skeleton_Animation_Result& Serializer::Read<Skeleton_Animation_Result>(const JSON& Json_Context, Skeleton_Animation_Result &Instance){
            

            if(Json_Context.contains("Transforms")&&!Json_Context["Transforms"].is_null())
                    Serializer::Read(Json_Context["Transforms"],Instance.m_Transforms);

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

        using NameSpace_Function::NameSpace_Render::NameSpace_Render_System::Game_Object_Material_Desc;

        template<> inline const JSON Serializer::Write<Game_Object_Material_Desc>(const Game_Object_Material_Desc& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["Base_Color_URL"] = Serializer::Write(Instance.m_Base_Color_URL);
                Json_Context["Metallic_Roughness_URL"] = Serializer::Write(Instance.m_Metallic_Roughness_URL);
                Json_Context["Normal_URL"] = Serializer::Write(Instance.m_Normal_URL);
                Json_Context["Occlusion_URL"] = Serializer::Write(Instance.m_Occlusion_URL);
                Json_Context["Emissive_URL"] = Serializer::Write(Instance.m_Emissive_URL);
                Json_Context["Is_With_Texture"] = Serializer::Write(Instance.m_Is_With_Texture);

            return Json_Context;
        }

        template<> inline Game_Object_Material_Desc& Serializer::Read<Game_Object_Material_Desc>(const JSON& Json_Context, Game_Object_Material_Desc &Instance){
            

            if(Json_Context.contains("Base_Color_URL")&&!Json_Context["Base_Color_URL"].is_null())
                    Serializer::Read(Json_Context["Base_Color_URL"],Instance.m_Base_Color_URL);
            if(Json_Context.contains("Metallic_Roughness_URL")&&!Json_Context["Metallic_Roughness_URL"].is_null())
                    Serializer::Read(Json_Context["Metallic_Roughness_URL"],Instance.m_Metallic_Roughness_URL);
            if(Json_Context.contains("Normal_URL")&&!Json_Context["Normal_URL"].is_null())
                    Serializer::Read(Json_Context["Normal_URL"],Instance.m_Normal_URL);
            if(Json_Context.contains("Occlusion_URL")&&!Json_Context["Occlusion_URL"].is_null())
                    Serializer::Read(Json_Context["Occlusion_URL"],Instance.m_Occlusion_URL);
            if(Json_Context.contains("Emissive_URL")&&!Json_Context["Emissive_URL"].is_null())
                    Serializer::Read(Json_Context["Emissive_URL"],Instance.m_Emissive_URL);
            if(Json_Context.contains("Is_With_Texture")&&!Json_Context["Is_With_Texture"].is_null())
                    Serializer::Read(Json_Context["Is_With_Texture"],Instance.m_Is_With_Texture);

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

        using NameSpace_Function::NameSpace_Render::NameSpace_Render_System::Game_Object_Transform_Desc;

        template<> inline const JSON Serializer::Write<Game_Object_Transform_Desc>(const Game_Object_Transform_Desc& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["Transform"] = Serializer::Write(Instance.m_Transform);

            return Json_Context;
        }

        template<> inline Game_Object_Transform_Desc& Serializer::Read<Game_Object_Transform_Desc>(const JSON& Json_Context, Game_Object_Transform_Desc &Instance){
            

            if(Json_Context.contains("Transform")&&!Json_Context["Transform"].is_null())
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

        using NameSpace_Function::NameSpace_Render::NameSpace_Render_System::Game_Object_Part_Desc;

        template<> inline const JSON Serializer::Write<Game_Object_Part_Desc>(const Game_Object_Part_Desc& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["Mesh_Desc"] = Serializer::Write(Instance.m_Mesh_Desc);
                Json_Context["Material_Desc"] = Serializer::Write(Instance.m_Material_Desc);
                Json_Context["Transform_Desc"] = Serializer::Write(Instance.m_Transform_Desc);
                Json_Context["Skeleton_Binding_Desc"] = Serializer::Write(Instance.m_Skeleton_Binding_Desc);
                Json_Context["Skeleton_Animation_Result"] = Serializer::Write(Instance.m_Skeleton_Animation_Result);
                Json_Context["Is_With_Skeleton"] = Serializer::Write(Instance.m_Is_With_Skeleton);

            return Json_Context;
        }

        template<> inline Game_Object_Part_Desc& Serializer::Read<Game_Object_Part_Desc>(const JSON& Json_Context, Game_Object_Part_Desc &Instance){
            

            if(Json_Context.contains("Mesh_Desc")&&!Json_Context["Mesh_Desc"].is_null())
                    Serializer::Read(Json_Context["Mesh_Desc"],Instance.m_Mesh_Desc);
            if(Json_Context.contains("Material_Desc")&&!Json_Context["Material_Desc"].is_null())
                    Serializer::Read(Json_Context["Material_Desc"],Instance.m_Material_Desc);
            if(Json_Context.contains("Transform_Desc")&&!Json_Context["Transform_Desc"].is_null())
                    Serializer::Read(Json_Context["Transform_Desc"],Instance.m_Transform_Desc);
            if(Json_Context.contains("Skeleton_Binding_Desc")&&!Json_Context["Skeleton_Binding_Desc"].is_null())
                    Serializer::Read(Json_Context["Skeleton_Binding_Desc"],Instance.m_Skeleton_Binding_Desc);
            if(Json_Context.contains("Skeleton_Animation_Result")&&!Json_Context["Skeleton_Animation_Result"].is_null())
                    Serializer::Read(Json_Context["Skeleton_Animation_Result"],Instance.m_Skeleton_Animation_Result);
            if(Json_Context.contains("Is_With_Skeleton")&&!Json_Context["Is_With_Skeleton"].is_null())
                    Serializer::Read(Json_Context["Is_With_Skeleton"],Instance.m_Is_With_Skeleton);

            return Instance;
        }

    }// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer

