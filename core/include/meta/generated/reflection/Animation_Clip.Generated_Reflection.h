#pragma once

#include<string>
#include<vector>
#include<memory>
#include<cstddef>

#include "meta/Reflection/Reflection_Instance.h"

#include "D:/Amy_Engine/resource/include/components/animation/Animation_Clip.h"

namespace NameSpace_Resource::NameSpace_Components{

    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;
    using std::static_pointer_cast;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

    class Reflection_Animation_Node_Map_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Animation_Node_Map"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Animation_Node_Map"};            
        }

            static const vector<Reflection_Instance<Animation_Node_Map>> Get_Base_Class_Reflection_Instance_List(shared_ptr<Animation_Node_Map> Instance){
                vector<Reflection_Instance<Animation_Node_Map>> Table;

                    

                return Table;
            }

            static const string Get_onvert_Type_Spelling(void){
                return string{"vector<string>"};
            }

            static const string Get_onvert_Spelling(void){
                return string{"m_onvert"};
            }


            static const string Get_onvert_Display_Name(void){
                return string{"onvert"};
            }

            static const vector<string> Get_onvert_Attribute(shared_ptr<Animation_Node_Map> Instance){
                return Instance->m_onvert;
            }

            static void Set_Field_onvert_Attribute(shared_ptr<Animation_Node_Map> Instance, const vector<string>& Value){
                Instance->m_onvert=Value;
            }

            static const bool Is_Filed_onvert_CPPVector(void){
                return  !  false;
            }

                static const string Get_onvert_CPPVector_Element_Type_Spelling(void){
                    return string {"string"};
                }

                static const size_t Get_onvert_CPPVector_Capacity(shared_ptr<Animation_Node_Map> Instance){
                    return Instance->m_onvert.capacity();
                }

                static const size_t Get_onvert_CPPVector_Size(shared_ptr<Animation_Node_Map> Instance){
                    return Instance->m_onvert.size();
                }

                static const string Get_onvert_CPPVector_Element(shared_ptr<Animation_Node_Map> Instance, size_t Index){
                    return Instance->m_onvert[Index];
                }

                static void Set_onvert_CPPVector_Element(shared_ptr<Animation_Node_Map> Instance, size_t Index, const string& Value){
                    Instance->m_onvert[Index]=Value;
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

    class Reflection_Animation_Channel_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Animation_Channel"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Animation_Channel"};            
        }

            static const vector<Reflection_Instance<Animation_Channel>> Get_Base_Class_Reflection_Instance_List(shared_ptr<Animation_Channel> Instance){
                vector<Reflection_Instance<Animation_Channel>> Table;

                    

                return Table;
            }

            static const string Get_Name_Type_Spelling(void){
                return string{"string"};
            }

            static const string Get_Name_Spelling(void){
                return string{"m_Name"};
            }


            static const string Get_Name_Display_Name(void){
                return string{"Name"};
            }

            static const string Get_Name_Attribute(shared_ptr<Animation_Channel> Instance){
                return Instance->m_Name;
            }

            static void Set_Field_Name_Attribute(shared_ptr<Animation_Channel> Instance, const string& Value){
                Instance->m_Name=Value;
            }

            static const bool Is_Filed_Name_CPPVector(void){
                return  false;
            }

            

            static const string Get_Time_Type_Spelling(void){
                return string{"vector<float>"};
            }

            static const string Get_Time_Spelling(void){
                return string{"m_Time"};
            }


            static const string Get_Time_Display_Name(void){
                return string{"Time"};
            }

            static const vector<float> Get_Time_Attribute(shared_ptr<Animation_Channel> Instance){
                return Instance->m_Time;
            }

            static void Set_Field_Time_Attribute(shared_ptr<Animation_Channel> Instance, const vector<float>& Value){
                Instance->m_Time=Value;
            }

            static const bool Is_Filed_Time_CPPVector(void){
                return  !  false;
            }

                static const string Get_Time_CPPVector_Element_Type_Spelling(void){
                    return string {"float"};
                }

                static const size_t Get_Time_CPPVector_Capacity(shared_ptr<Animation_Channel> Instance){
                    return Instance->m_Time.capacity();
                }

                static const size_t Get_Time_CPPVector_Size(shared_ptr<Animation_Channel> Instance){
                    return Instance->m_Time.size();
                }

                static const float Get_Time_CPPVector_Element(shared_ptr<Animation_Channel> Instance, size_t Index){
                    return Instance->m_Time[Index];
                }

                static void Set_Time_CPPVector_Element(shared_ptr<Animation_Channel> Instance, size_t Index, const float& Value){
                    Instance->m_Time[Index]=Value;
                }

            static const string Get_Transform_Type_Spelling(void){
                return string{"Affine_Transform"};
            }

            static const string Get_Transform_Spelling(void){
                return string{"m_Transform"};
            }


            static const string Get_Transform_Display_Name(void){
                return string{"Transform"};
            }

            static const Affine_Transform Get_Transform_Attribute(shared_ptr<Animation_Channel> Instance){
                return Instance->m_Transform;
            }

            static void Set_Field_Transform_Attribute(shared_ptr<Animation_Channel> Instance, const Affine_Transform& Value){
                Instance->m_Transform=Value;
            }

            static const bool Is_Filed_Transform_CPPVector(void){
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

    class Reflection_Animation_Clip_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Animation_Clip"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Animation_Clip"};            
        }

            static const vector<Reflection_Instance<Animation_Clip>> Get_Base_Class_Reflection_Instance_List(shared_ptr<Animation_Clip> Instance){
                vector<Reflection_Instance<Animation_Clip>> Table;

                    

                return Table;
            }

            static const string Get_Total_Frame_Type_Spelling(void){
                return string{"size_t"};
            }

            static const string Get_Total_Frame_Spelling(void){
                return string{"Total_Frame"};
            }


            static const string Get_Total_Frame_Display_Name(void){
                return string{"Total_Frame"};
            }

            static const size_t Get_Total_Frame_Attribute(shared_ptr<Animation_Clip> Instance){
                return Instance->Total_Frame;
            }

            static void Set_Field_Total_Frame_Attribute(shared_ptr<Animation_Clip> Instance, const size_t& Value){
                Instance->Total_Frame=Value;
            }

            static const bool Is_Filed_Total_Frame_CPPVector(void){
                return  false;
            }

            

            static const string Get_Node_Channels_Type_Spelling(void){
                return string{"vector<Animation_Channel>"};
            }

            static const string Get_Node_Channels_Spelling(void){
                return string{"m_Node_Channels"};
            }


            static const string Get_Node_Channels_Display_Name(void){
                return string{"Node_Channels"};
            }

            static const vector<Animation_Channel> Get_Node_Channels_Attribute(shared_ptr<Animation_Clip> Instance){
                return Instance->m_Node_Channels;
            }

            static void Set_Field_Node_Channels_Attribute(shared_ptr<Animation_Clip> Instance, const vector<Animation_Channel>& Value){
                Instance->m_Node_Channels=Value;
            }

            static const bool Is_Filed_Node_Channels_CPPVector(void){
                return  !  false;
            }

                static const string Get_Node_Channels_CPPVector_Element_Type_Spelling(void){
                    return string {"Animation_Channel"};
                }

                static const size_t Get_Node_Channels_CPPVector_Capacity(shared_ptr<Animation_Clip> Instance){
                    return Instance->m_Node_Channels.capacity();
                }

                static const size_t Get_Node_Channels_CPPVector_Size(shared_ptr<Animation_Clip> Instance){
                    return Instance->m_Node_Channels.size();
                }

                static const Animation_Channel Get_Node_Channels_CPPVector_Element(shared_ptr<Animation_Clip> Instance, size_t Index){
                    return Instance->m_Node_Channels[Index];
                }

                static void Set_Node_Channels_CPPVector_Element(shared_ptr<Animation_Clip> Instance, size_t Index, const Animation_Channel& Value){
                    Instance->m_Node_Channels[Index]=Value;
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

    class Reflection_Animation_Data_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Animation_Data"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Animation_Data"};            
        }

            static const vector<Reflection_Instance<Animation_Data>> Get_Base_Class_Reflection_Instance_List(shared_ptr<Animation_Data> Instance){
                vector<Reflection_Instance<Animation_Data>> Table;

                    

                return Table;
            }

            static const string Get_Skeleton_File_Path_Type_Spelling(void){
                return string{"path"};
            }

            static const string Get_Skeleton_File_Path_Spelling(void){
                return string{"m_Skeleton_File_Path"};
            }


            static const string Get_Skeleton_File_Path_Display_Name(void){
                return string{"Skeleton_File_Path"};
            }

            static const path Get_Skeleton_File_Path_Attribute(shared_ptr<Animation_Data> Instance){
                return Instance->m_Skeleton_File_Path;
            }

            static void Set_Field_Skeleton_File_Path_Attribute(shared_ptr<Animation_Data> Instance, const path& Value){
                Instance->m_Skeleton_File_Path=Value;
            }

            static const bool Is_Filed_Skeleton_File_Path_CPPVector(void){
                return  false;
            }

            

            static const string Get_Node_Map_Type_Spelling(void){
                return string{"Animation_Node_Map"};
            }

            static const string Get_Node_Map_Spelling(void){
                return string{"m_Node_Map"};
            }


            static const string Get_Node_Map_Display_Name(void){
                return string{"Node_Map"};
            }

            static const Animation_Node_Map Get_Node_Map_Attribute(shared_ptr<Animation_Data> Instance){
                return Instance->m_Node_Map;
            }

            static void Set_Field_Node_Map_Attribute(shared_ptr<Animation_Data> Instance, const Animation_Node_Map& Value){
                Instance->m_Node_Map=Value;
            }

            static const bool Is_Filed_Node_Map_CPPVector(void){
                return  false;
            }

            

            static const string Get_Clips_Type_Spelling(void){
                return string{"vector<Animation_Clip>"};
            }

            static const string Get_Clips_Spelling(void){
                return string{"m_Clips"};
            }


            static const string Get_Clips_Display_Name(void){
                return string{"Clips"};
            }

            static const vector<Animation_Clip> Get_Clips_Attribute(shared_ptr<Animation_Data> Instance){
                return Instance->m_Clips;
            }

            static void Set_Field_Clips_Attribute(shared_ptr<Animation_Data> Instance, const vector<Animation_Clip>& Value){
                Instance->m_Clips=Value;
            }

            static const bool Is_Filed_Clips_CPPVector(void){
                return  !  false;
            }

                static const string Get_Clips_CPPVector_Element_Type_Spelling(void){
                    return string {"Animation_Clip"};
                }

                static const size_t Get_Clips_CPPVector_Capacity(shared_ptr<Animation_Data> Instance){
                    return Instance->m_Clips.capacity();
                }

                static const size_t Get_Clips_CPPVector_Size(shared_ptr<Animation_Data> Instance){
                    return Instance->m_Clips.size();
                }

                static const Animation_Clip Get_Clips_CPPVector_Element(shared_ptr<Animation_Data> Instance, size_t Index){
                    return Instance->m_Clips[Index];
                }

                static void Set_Clips_CPPVector_Element(shared_ptr<Animation_Data> Instance, size_t Index, const Animation_Clip& Value){
                    Instance->m_Clips[Index]=Value;
                }


    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection

