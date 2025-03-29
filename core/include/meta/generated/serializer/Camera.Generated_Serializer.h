#include<cstdint>
#include<string>
#include<vector>
#include<memory>

#include "meta/serializer/Serializer.h"
#include "meta/Reflection/Reflection_Instance.h"


#include "D:/Amy_Engine/resource/include/components/camera/Camera.h"

    namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer{

        using std::string;
        using std::vector;
        using std::shared_ptr;
        using std::make_shared;
        using std::static_pointer_cast;

        using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

        using NameSpace_Resource::NameSpace_Components::Camera_Base;

        template<> inline const JSON NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer::Write<Camera_Base>(const Camera_Base& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["FOV"] = Serializer::Write(Instance.m_FOV);

            return Json_Context;
        }

        template<> inline Camera_Base& NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer::Read<Camera_Base>(const JSON& Json_Context, Camera_Base &Instance){
            

                Serializer::Read(Json_Context["FOV"],Instance.m_FOV);

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

        using NameSpace_Resource::NameSpace_Components::Camera_First_Persion;

        template<> inline const JSON NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer::Write<Camera_First_Persion>(const Camera_First_Persion& Instance){
            JSON Json_Context { JSON::object() };

                  // Json_Context["Camera_Base"]=Serializer::Write<NameSpace_Resource::NameSpace_Components::Camera_Base>(*static_cast<const NameSpace_Resource::NameSpace_Components::Camera_Base*>(&Instance));

                Json_Context["Vertical_Offset"] = Serializer::Write(Instance.m_Vertical_Offset);

            return Json_Context;
        }

        template<> inline Camera_First_Persion& NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer::Read<Camera_First_Persion>(const JSON& Json_Context, Camera_First_Persion &Instance){
                  //  Serializer::Read(Json_Context["Camera_Base"],*static_cast<const NameSpace_Resource::NameSpace_Components::Camera_Base*>(&Instance));

                Serializer::Read(Json_Context["Vertical_Offset"],Instance.m_Vertical_Offset);

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

        using NameSpace_Resource::NameSpace_Components::Camera_Third_Persion;

        template<> inline const JSON NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer::Write<Camera_Third_Persion>(const Camera_Third_Persion& Instance){
            JSON Json_Context { JSON::object() };

                  // Json_Context["Camera_Base"]=Serializer::Write<NameSpace_Resource::NameSpace_Components::Camera_Base>(*static_cast<const NameSpace_Resource::NameSpace_Components::Camera_Base*>(&Instance));

                Json_Context["Horizontal_Offset"] = Serializer::Write(Instance.m_Horizontal_Offset);
                Json_Context["Vertical_Offset"] = Serializer::Write(Instance.m_Vertical_Offset);
                Json_Context["Cursor_Pitch"] = Serializer::Write(Instance.m_Cursor_Pitch);
                Json_Context["Cursor_Yaw"] = Serializer::Write(Instance.m_Cursor_Yaw);

            return Json_Context;
        }

        template<> inline Camera_Third_Persion& NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer::Read<Camera_Third_Persion>(const JSON& Json_Context, Camera_Third_Persion &Instance){
                  //  Serializer::Read(Json_Context["Camera_Base"],*static_cast<const NameSpace_Resource::NameSpace_Components::Camera_Base*>(&Instance));

                Serializer::Read(Json_Context["Horizontal_Offset"],Instance.m_Horizontal_Offset);
                Serializer::Read(Json_Context["Vertical_Offset"],Instance.m_Vertical_Offset);
                Serializer::Read(Json_Context["Cursor_Pitch"],Instance.m_Cursor_Pitch);
                Serializer::Read(Json_Context["Cursor_Yaw"],Instance.m_Cursor_Yaw);

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

        using NameSpace_Resource::NameSpace_Components::Camera_Free;

        template<> inline const JSON NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer::Write<Camera_Free>(const Camera_Free& Instance){
            JSON Json_Context { JSON::object() };

                  // Json_Context["Camera_Base"]=Serializer::Write<NameSpace_Resource::NameSpace_Components::Camera_Base>(*static_cast<const NameSpace_Resource::NameSpace_Components::Camera_Base*>(&Instance));

                Json_Context["Speed"] = Serializer::Write(Instance.m_Speed);

            return Json_Context;
        }

        template<> inline Camera_Free& NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer::Read<Camera_Free>(const JSON& Json_Context, Camera_Free &Instance){
                  //  Serializer::Read(Json_Context["Camera_Base"],*static_cast<const NameSpace_Resource::NameSpace_Components::Camera_Base*>(&Instance));

                Serializer::Read(Json_Context["Speed"],Instance.m_Speed);

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

        using NameSpace_Resource::NameSpace_Components::Camera_Resource;

        template<> inline const JSON NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer::Write<Camera_Resource>(const Camera_Resource& Instance){
            JSON Json_Context { JSON::object() };

            

                Json_Context["Camera"] = Serializer::Write(Instance.m_Camera);

            return Json_Context;
        }

        template<> inline Camera_Resource& NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer::Read<Camera_Resource>(const JSON& Json_Context, Camera_Resource &Instance){
            

                Serializer::Read(Json_Context["Camera"],Instance.m_Camera);

            return Instance;
        }

    }// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer

