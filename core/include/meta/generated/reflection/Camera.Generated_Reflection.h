#pragma once

#include<string>
#include<vector>
#include<memory>
#include<cstddef>

#include "meta/Reflection/Reflection_Instance.h"

#include "D:/Amy_Engine/resource/include/components/camera/Camera.h"

namespace NameSpace_Resource::NameSpace_Components{

    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;
    using std::static_pointer_cast;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

    class Reflection_Camera_Base_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Camera_Base"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Camera_Base"};            
        }

            static const vector<Reflection_Instance<Camera_Base>> Get_Base_Class_Reflection_Instance_List(shared_ptr<Camera_Base> Instance){
                vector<Reflection_Instance<Camera_Base>> Table;

                    

                return Table;
            }

            static const string Get_FOV_Type_Spelling(void){
                return string{"float"};
            }

            static const string Get_FOV_Spelling(void){
                return string{"m_FOV"};
            }


            static const string Get_FOV_Display_Name(void){
                return string{"FOV"};
            }

            static const float& Get_FOV_Attribute(shared_ptr<Camera_Base> Instance){
                return Instance->m_FOV;
            }

            static void Set_Field_FOV_Attribute(shared_ptr<Camera_Base> Instance, const float& Value){
                Instance->m_FOV=Value;
            }

            static const bool Is_Filed_FOV_CPPVector(void){
                return  false;
            }

            


    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection
namespace NameSpace_Resource::NameSpace_Components{

    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;
    using std::static_pointer_cast;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

    class Reflection_Camera_First_Persion_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Camera_First_Persion"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Camera_First_Persion"};            
        }

            static const vector<Reflection_Instance<Camera_First_Persion>> Get_Base_Class_Reflection_Instance_List(shared_ptr<Camera_First_Persion> Instance){
                vector<Reflection_Instance<Camera_First_Persion>> Table;

                        Table.emplace_back(string{"Camera_Base"},static_pointer_cast<Camera_Base>(Instance));

                return Table;
            }

            static const string Get_Vertical_Offset_Type_Spelling(void){
                return string{"float"};
            }

            static const string Get_Vertical_Offset_Spelling(void){
                return string{"m_Vertical_Offset"};
            }


            static const string Get_Vertical_Offset_Display_Name(void){
                return string{"Vertical_Offset"};
            }

            static const float& Get_Vertical_Offset_Attribute(shared_ptr<Camera_First_Persion> Instance){
                return Instance->m_Vertical_Offset;
            }

            static void Set_Field_Vertical_Offset_Attribute(shared_ptr<Camera_First_Persion> Instance, const float& Value){
                Instance->m_Vertical_Offset=Value;
            }

            static const bool Is_Filed_Vertical_Offset_CPPVector(void){
                return  false;
            }

            


    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection
namespace NameSpace_Resource::NameSpace_Components{

    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;
    using std::static_pointer_cast;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

    class Reflection_Camera_Third_Persion_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Camera_Third_Persion"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Camera_Third_Persion"};            
        }

            static const vector<Reflection_Instance<Camera_Third_Persion>> Get_Base_Class_Reflection_Instance_List(shared_ptr<Camera_Third_Persion> Instance){
                vector<Reflection_Instance<Camera_Third_Persion>> Table;

                        Table.emplace_back(string{"Camera_Base"},static_pointer_cast<Camera_Base>(Instance));

                return Table;
            }

            static const string Get_Horizontal_Offset_Type_Spelling(void){
                return string{"float"};
            }

            static const string Get_Horizontal_Offset_Spelling(void){
                return string{"m_Horizontal_Offset"};
            }


            static const string Get_Horizontal_Offset_Display_Name(void){
                return string{"Horizontal_Offset"};
            }

            static const float& Get_Horizontal_Offset_Attribute(shared_ptr<Camera_Third_Persion> Instance){
                return Instance->m_Horizontal_Offset;
            }

            static void Set_Field_Horizontal_Offset_Attribute(shared_ptr<Camera_Third_Persion> Instance, const float& Value){
                Instance->m_Horizontal_Offset=Value;
            }

            static const bool Is_Filed_Horizontal_Offset_CPPVector(void){
                return  false;
            }

            

            static const string Get_Vertical_Offset_Type_Spelling(void){
                return string{"float"};
            }

            static const string Get_Vertical_Offset_Spelling(void){
                return string{"m_Vertical_Offset"};
            }


            static const string Get_Vertical_Offset_Display_Name(void){
                return string{"Vertical_Offset"};
            }

            static const float& Get_Vertical_Offset_Attribute(shared_ptr<Camera_Third_Persion> Instance){
                return Instance->m_Vertical_Offset;
            }

            static void Set_Field_Vertical_Offset_Attribute(shared_ptr<Camera_Third_Persion> Instance, const float& Value){
                Instance->m_Vertical_Offset=Value;
            }

            static const bool Is_Filed_Vertical_Offset_CPPVector(void){
                return  false;
            }

            

            static const string Get_Cursor_Pitch_Type_Spelling(void){
                return string{"Quaternion"};
            }

            static const string Get_Cursor_Pitch_Spelling(void){
                return string{"m_Cursor_Pitch"};
            }


            static const string Get_Cursor_Pitch_Display_Name(void){
                return string{"Cursor_Pitch"};
            }

            static const Quaternion& Get_Cursor_Pitch_Attribute(shared_ptr<Camera_Third_Persion> Instance){
                return Instance->m_Cursor_Pitch;
            }

            static void Set_Field_Cursor_Pitch_Attribute(shared_ptr<Camera_Third_Persion> Instance, const Quaternion& Value){
                Instance->m_Cursor_Pitch=Value;
            }

            static const bool Is_Filed_Cursor_Pitch_CPPVector(void){
                return  false;
            }

            

            static const string Get_Cursor_Yaw_Type_Spelling(void){
                return string{"Quaternion"};
            }

            static const string Get_Cursor_Yaw_Spelling(void){
                return string{"m_Cursor_Yaw"};
            }


            static const string Get_Cursor_Yaw_Display_Name(void){
                return string{"Cursor_Yaw"};
            }

            static const Quaternion& Get_Cursor_Yaw_Attribute(shared_ptr<Camera_Third_Persion> Instance){
                return Instance->m_Cursor_Yaw;
            }

            static void Set_Field_Cursor_Yaw_Attribute(shared_ptr<Camera_Third_Persion> Instance, const Quaternion& Value){
                Instance->m_Cursor_Yaw=Value;
            }

            static const bool Is_Filed_Cursor_Yaw_CPPVector(void){
                return  false;
            }

            


    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection
namespace NameSpace_Resource::NameSpace_Components{

    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;
    using std::static_pointer_cast;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

    class Reflection_Camera_Free_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Camera_Free"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Camera_Free"};            
        }

            static const vector<Reflection_Instance<Camera_Free>> Get_Base_Class_Reflection_Instance_List(shared_ptr<Camera_Free> Instance){
                vector<Reflection_Instance<Camera_Free>> Table;

                        Table.emplace_back(string{"Camera_Base"},static_pointer_cast<Camera_Base>(Instance));

                return Table;
            }

            static const string Get_Speed_Type_Spelling(void){
                return string{"float"};
            }

            static const string Get_Speed_Spelling(void){
                return string{"m_Speed"};
            }


            static const string Get_Speed_Display_Name(void){
                return string{"Speed"};
            }

            static const float& Get_Speed_Attribute(shared_ptr<Camera_Free> Instance){
                return Instance->m_Speed;
            }

            static void Set_Field_Speed_Attribute(shared_ptr<Camera_Free> Instance, const float& Value){
                Instance->m_Speed=Value;
            }

            static const bool Is_Filed_Speed_CPPVector(void){
                return  false;
            }

            


    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection
namespace NameSpace_Resource::NameSpace_Components{

    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;
    using std::static_pointer_cast;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

    class Reflection_Camera_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Camera"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Camera"};            
        }

            static const vector<Reflection_Instance<Camera>> Get_Base_Class_Reflection_Instance_List(shared_ptr<Camera> Instance){
                vector<Reflection_Instance<Camera>> Table;

                    

                return Table;
            }

            static const string Get_Camera_Type_Spelling(void){
                return string{"Reflection_Instance<Camera_Base>"};
            }

            static const string Get_Camera_Spelling(void){
                return string{"m_Camera"};
            }


            static const string Get_Camera_Display_Name(void){
                return string{"Camera"};
            }

            static const Reflection_Instance<Camera_Base>& Get_Camera_Attribute(shared_ptr<Camera> Instance){
                return Instance->m_Camera;
            }

            static void Set_Field_Camera_Attribute(shared_ptr<Camera> Instance, const Reflection_Instance<Camera_Base>& Value){
                Instance->m_Camera=Value;
            }

            static const bool Is_Filed_Camera_CPPVector(void){
                return  false;
            }

            


    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection

