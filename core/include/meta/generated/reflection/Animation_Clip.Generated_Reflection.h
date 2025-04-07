#pragma once

#include<string>
#include<vector>
#include<memory>
#include<cstddef>

#include "json.h"

#include "meta/Reflection/Reflection_Instance.h"

#include "meta/Serializer/Serializer.h"

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

        

            static const string Get_Convert_Type_Spelling(void){
                return string{"vector<string>"};
            }

            static const string Get_Convert_Spelling(void){
                return string{"m_Convert"};
            }


            static const string Get_Convert_Display_Name(void){
                return string{"Convert"};
            }

            static const vector<string>& Get_Convert_Attribute(shared_ptr<Animation_Node_Map> Instance){
                return Instance->m_Convert;
            }

            static void Set_Field_Convert_Attribute(shared_ptr<Animation_Node_Map> Instance, const vector<string>& Value){
                Instance->m_Convert=Value;
            }

            static const bool Is_Filed_Convert_CPPVector(void){
                return  !  false;
            }

                static const string Get_Convert_CPPVector_Element_Type_Spelling(void){
                    return string {"string"};
                }

                static const size_t Get_Convert_CPPVector_Capacity(shared_ptr<Animation_Node_Map> Instance){
                    return Instance->m_Convert.capacity();
                }

                static const size_t Get_Convert_CPPVector_Size(shared_ptr<Animation_Node_Map> Instance){
                    return Instance->m_Convert.size();
                }

                static const string& Get_Convert_CPPVector_Element(shared_ptr<Animation_Node_Map> Instance, size_t Index){
                    return Instance->m_Convert[Index];
                }

                static void Set_Convert_CPPVector_Element(shared_ptr<Animation_Node_Map> Instance, size_t Index, const string& Value){
                    Instance->m_Convert[Index]=Value;
                }

                static void Reserve_Convert_CPPVector(shared_ptr<Animation_Node_Map> Instance, size_t Capacity){
                    Instance->m_Convert.reserve(Capacity);
                }

                static void Push_Back_Convert_CPPVector(shared_ptr<Animation_Node_Map> Instance, const string& Value){
                    Instance->m_Convert.push_back(Value);
                }


    };
   
}// namespace NameSpace_Resource::NameSpace_Components

    
 
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

        

            static const string Get_Name_Type_Spelling(void){
                return string{"string"};
            }

            static const string Get_Name_Spelling(void){
                return string{"m_Name"};
            }


            static const string Get_Name_Display_Name(void){
                return string{"Name"};
            }

            static const string& Get_Name_Attribute(shared_ptr<Animation_Channel> Instance){
                return Instance->m_Name;
            }

            static void Set_Field_Name_Attribute(shared_ptr<Animation_Channel> Instance, const string& Value){
                Instance->m_Name=Value;
            }

            static const bool Is_Filed_Name_CPPVector(void){
                return  false;
            }

            

            static const string Get_Positions_Keys_Type_Spelling(void){
                return string{"vector<Vector3>"};
            }

            static const string Get_Positions_Keys_Spelling(void){
                return string{"m_Positions_Keys"};
            }


            static const string Get_Positions_Keys_Display_Name(void){
                return string{"Positions_Keys"};
            }

            static const vector<Vector3>& Get_Positions_Keys_Attribute(shared_ptr<Animation_Channel> Instance){
                return Instance->m_Positions_Keys;
            }

            static void Set_Field_Positions_Keys_Attribute(shared_ptr<Animation_Channel> Instance, const vector<Vector3>& Value){
                Instance->m_Positions_Keys=Value;
            }

            static const bool Is_Filed_Positions_Keys_CPPVector(void){
                return  !  false;
            }

                static const string Get_Positions_Keys_CPPVector_Element_Type_Spelling(void){
                    return string {"Vector3"};
                }

                static const size_t Get_Positions_Keys_CPPVector_Capacity(shared_ptr<Animation_Channel> Instance){
                    return Instance->m_Positions_Keys.capacity();
                }

                static const size_t Get_Positions_Keys_CPPVector_Size(shared_ptr<Animation_Channel> Instance){
                    return Instance->m_Positions_Keys.size();
                }

                static const Vector3& Get_Positions_Keys_CPPVector_Element(shared_ptr<Animation_Channel> Instance, size_t Index){
                    return Instance->m_Positions_Keys[Index];
                }

                static void Set_Positions_Keys_CPPVector_Element(shared_ptr<Animation_Channel> Instance, size_t Index, const Vector3& Value){
                    Instance->m_Positions_Keys[Index]=Value;
                }

                static void Reserve_Positions_Keys_CPPVector(shared_ptr<Animation_Channel> Instance, size_t Capacity){
                    Instance->m_Positions_Keys.reserve(Capacity);
                }

                static void Push_Back_Positions_Keys_CPPVector(shared_ptr<Animation_Channel> Instance, const Vector3& Value){
                    Instance->m_Positions_Keys.push_back(Value);
                }

            static const string Get_Rotations_Keys_Type_Spelling(void){
                return string{"vector<Quaternion>"};
            }

            static const string Get_Rotations_Keys_Spelling(void){
                return string{"m_Rotations_Keys"};
            }


            static const string Get_Rotations_Keys_Display_Name(void){
                return string{"Rotations_Keys"};
            }

            static const vector<Quaternion>& Get_Rotations_Keys_Attribute(shared_ptr<Animation_Channel> Instance){
                return Instance->m_Rotations_Keys;
            }

            static void Set_Field_Rotations_Keys_Attribute(shared_ptr<Animation_Channel> Instance, const vector<Quaternion>& Value){
                Instance->m_Rotations_Keys=Value;
            }

            static const bool Is_Filed_Rotations_Keys_CPPVector(void){
                return  !  false;
            }

                static const string Get_Rotations_Keys_CPPVector_Element_Type_Spelling(void){
                    return string {"Quaternion"};
                }

                static const size_t Get_Rotations_Keys_CPPVector_Capacity(shared_ptr<Animation_Channel> Instance){
                    return Instance->m_Rotations_Keys.capacity();
                }

                static const size_t Get_Rotations_Keys_CPPVector_Size(shared_ptr<Animation_Channel> Instance){
                    return Instance->m_Rotations_Keys.size();
                }

                static const Quaternion& Get_Rotations_Keys_CPPVector_Element(shared_ptr<Animation_Channel> Instance, size_t Index){
                    return Instance->m_Rotations_Keys[Index];
                }

                static void Set_Rotations_Keys_CPPVector_Element(shared_ptr<Animation_Channel> Instance, size_t Index, const Quaternion& Value){
                    Instance->m_Rotations_Keys[Index]=Value;
                }

                static void Reserve_Rotations_Keys_CPPVector(shared_ptr<Animation_Channel> Instance, size_t Capacity){
                    Instance->m_Rotations_Keys.reserve(Capacity);
                }

                static void Push_Back_Rotations_Keys_CPPVector(shared_ptr<Animation_Channel> Instance, const Quaternion& Value){
                    Instance->m_Rotations_Keys.push_back(Value);
                }

            static const string Get_Scales_Keys_Type_Spelling(void){
                return string{"vector<Vector3>"};
            }

            static const string Get_Scales_Keys_Spelling(void){
                return string{"m_Scales_Keys"};
            }


            static const string Get_Scales_Keys_Display_Name(void){
                return string{"Scales_Keys"};
            }

            static const vector<Vector3>& Get_Scales_Keys_Attribute(shared_ptr<Animation_Channel> Instance){
                return Instance->m_Scales_Keys;
            }

            static void Set_Field_Scales_Keys_Attribute(shared_ptr<Animation_Channel> Instance, const vector<Vector3>& Value){
                Instance->m_Scales_Keys=Value;
            }

            static const bool Is_Filed_Scales_Keys_CPPVector(void){
                return  !  false;
            }

                static const string Get_Scales_Keys_CPPVector_Element_Type_Spelling(void){
                    return string {"Vector3"};
                }

                static const size_t Get_Scales_Keys_CPPVector_Capacity(shared_ptr<Animation_Channel> Instance){
                    return Instance->m_Scales_Keys.capacity();
                }

                static const size_t Get_Scales_Keys_CPPVector_Size(shared_ptr<Animation_Channel> Instance){
                    return Instance->m_Scales_Keys.size();
                }

                static const Vector3& Get_Scales_Keys_CPPVector_Element(shared_ptr<Animation_Channel> Instance, size_t Index){
                    return Instance->m_Scales_Keys[Index];
                }

                static void Set_Scales_Keys_CPPVector_Element(shared_ptr<Animation_Channel> Instance, size_t Index, const Vector3& Value){
                    Instance->m_Scales_Keys[Index]=Value;
                }

                static void Reserve_Scales_Keys_CPPVector(shared_ptr<Animation_Channel> Instance, size_t Capacity){
                    Instance->m_Scales_Keys.reserve(Capacity);
                }

                static void Push_Back_Scales_Keys_CPPVector(shared_ptr<Animation_Channel> Instance, const Vector3& Value){
                    Instance->m_Scales_Keys.push_back(Value);
                }


    };
   
}// namespace NameSpace_Resource::NameSpace_Components

    
 
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

        

            static const string Get_Total_Frame_Type_Spelling(void){
                return string{"size_t"};
            }

            static const string Get_Total_Frame_Spelling(void){
                return string{"Total_Frame"};
            }


            static const string Get_Total_Frame_Display_Name(void){
                return string{"Total_Frame"};
            }

            static const size_t& Get_Total_Frame_Attribute(shared_ptr<Animation_Clip> Instance){
                return Instance->Total_Frame;
            }

            static void Set_Field_Total_Frame_Attribute(shared_ptr<Animation_Clip> Instance, const size_t& Value){
                Instance->Total_Frame=Value;
            }

            static const bool Is_Filed_Total_Frame_CPPVector(void){
                return  false;
            }

            

            static const string Get_Node_Channels_Type_Spelling(void){
                return string{"vector<shared_ptr<Animation_Channel>>"};
            }

            static const string Get_Node_Channels_Spelling(void){
                return string{"m_Node_Channels"};
            }


            static const string Get_Node_Channels_Display_Name(void){
                return string{"Node_Channels"};
            }

            static const vector<shared_ptr<Animation_Channel>>& Get_Node_Channels_Attribute(shared_ptr<Animation_Clip> Instance){
                return Instance->m_Node_Channels;
            }

            static void Set_Field_Node_Channels_Attribute(shared_ptr<Animation_Clip> Instance, const vector<shared_ptr<Animation_Channel>>& Value){
                Instance->m_Node_Channels=Value;
            }

            static const bool Is_Filed_Node_Channels_CPPVector(void){
                return  !  false;
            }

                static const string Get_Node_Channels_CPPVector_Element_Type_Spelling(void){
                    return string {"shared_ptr<Animation_Channel>"};
                }

                static const size_t Get_Node_Channels_CPPVector_Capacity(shared_ptr<Animation_Clip> Instance){
                    return Instance->m_Node_Channels.capacity();
                }

                static const size_t Get_Node_Channels_CPPVector_Size(shared_ptr<Animation_Clip> Instance){
                    return Instance->m_Node_Channels.size();
                }

                static const shared_ptr<Animation_Channel>& Get_Node_Channels_CPPVector_Element(shared_ptr<Animation_Clip> Instance, size_t Index){
                    return Instance->m_Node_Channels[Index];
                }

                static void Set_Node_Channels_CPPVector_Element(shared_ptr<Animation_Clip> Instance, size_t Index, const shared_ptr<Animation_Channel>& Value){
                    Instance->m_Node_Channels[Index]=Value;
                }

                static void Reserve_Node_Channels_CPPVector(shared_ptr<Animation_Clip> Instance, size_t Capacity){
                    Instance->m_Node_Channels.reserve(Capacity);
                }

                static void Push_Back_Node_Channels_CPPVector(shared_ptr<Animation_Clip> Instance, const shared_ptr<Animation_Channel>& Value){
                    Instance->m_Node_Channels.push_back(Value);
                }


    };
   
}// namespace NameSpace_Resource::NameSpace_Components

    
 
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

        

            static const string Get_Skeleton_Data_URL_Type_Spelling(void){
                return string{"path"};
            }

            static const string Get_Skeleton_Data_URL_Spelling(void){
                return string{"m_Skeleton_Data_URL"};
            }


            static const string Get_Skeleton_Data_URL_Display_Name(void){
                return string{"Skeleton_Data_URL"};
            }

            static const path& Get_Skeleton_Data_URL_Attribute(shared_ptr<Animation_Data> Instance){
                return Instance->m_Skeleton_Data_URL;
            }

            static void Set_Field_Skeleton_Data_URL_Attribute(shared_ptr<Animation_Data> Instance, const path& Value){
                Instance->m_Skeleton_Data_URL=Value;
            }

            static const bool Is_Filed_Skeleton_Data_URL_CPPVector(void){
                return  false;
            }

            

            static const string Get_Node_Map_Type_Spelling(void){
                return string{"shared_ptr<Animation_Node_Map>"};
            }

            static const string Get_Node_Map_Spelling(void){
                return string{"m_Node_Map"};
            }


            static const string Get_Node_Map_Display_Name(void){
                return string{"Node_Map"};
            }

            static const shared_ptr<Animation_Node_Map>& Get_Node_Map_Attribute(shared_ptr<Animation_Data> Instance){
                return Instance->m_Node_Map;
            }

            static void Set_Field_Node_Map_Attribute(shared_ptr<Animation_Data> Instance, const shared_ptr<Animation_Node_Map>& Value){
                Instance->m_Node_Map=Value;
            }

            static const bool Is_Filed_Node_Map_CPPVector(void){
                return  false;
            }

            

            static const string Get_Clips_Type_Spelling(void){
                return string{"vector<shared_ptr<Animation_Clip>>"};
            }

            static const string Get_Clips_Spelling(void){
                return string{"m_Clips"};
            }


            static const string Get_Clips_Display_Name(void){
                return string{"Clips"};
            }

            static const vector<shared_ptr<Animation_Clip>>& Get_Clips_Attribute(shared_ptr<Animation_Data> Instance){
                return Instance->m_Clips;
            }

            static void Set_Field_Clips_Attribute(shared_ptr<Animation_Data> Instance, const vector<shared_ptr<Animation_Clip>>& Value){
                Instance->m_Clips=Value;
            }

            static const bool Is_Filed_Clips_CPPVector(void){
                return  !  false;
            }

                static const string Get_Clips_CPPVector_Element_Type_Spelling(void){
                    return string {"shared_ptr<Animation_Clip>"};
                }

                static const size_t Get_Clips_CPPVector_Capacity(shared_ptr<Animation_Data> Instance){
                    return Instance->m_Clips.capacity();
                }

                static const size_t Get_Clips_CPPVector_Size(shared_ptr<Animation_Data> Instance){
                    return Instance->m_Clips.size();
                }

                static const shared_ptr<Animation_Clip>& Get_Clips_CPPVector_Element(shared_ptr<Animation_Data> Instance, size_t Index){
                    return Instance->m_Clips[Index];
                }

                static void Set_Clips_CPPVector_Element(shared_ptr<Animation_Data> Instance, size_t Index, const shared_ptr<Animation_Clip>& Value){
                    Instance->m_Clips[Index]=Value;
                }

                static void Reserve_Clips_CPPVector(shared_ptr<Animation_Data> Instance, size_t Capacity){
                    Instance->m_Clips.reserve(Capacity);
                }

                static void Push_Back_Clips_CPPVector(shared_ptr<Animation_Data> Instance, const shared_ptr<Animation_Clip>& Value){
                    Instance->m_Clips.push_back(Value);
                }


    };
   
}// namespace NameSpace_Resource::NameSpace_Components

    
 

