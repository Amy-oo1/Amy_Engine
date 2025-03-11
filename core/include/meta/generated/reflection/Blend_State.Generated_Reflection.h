#pragma once

#include<string>
#include<vector>
#include<memory>
#include<cstddef>

#include "meta/Reflection/Reflection_Instance.h"

#include "D:/Amy_Engine/resource/include/components/animation/Blend_State.h"

namespace NameSpace_Resource::NameSpace_Components{

    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;
    using std::static_pointer_cast;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

    class Reflection_Bone_Blend_Weight_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Bone_Blend_Weight"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Bone_Blend_Weight"};            
        }

            static const vector<Reflection_Instance<Bone_Blend_Weight>> Get_Base_Class_Reflection_Instance_List(shared_ptr<Bone_Blend_Weight> Instance){
                vector<Reflection_Instance<Bone_Blend_Weight>> Table;

                    

                return Table;
            }

            static const string Get_Blend_Weights_Type_Spelling(void){
                return string{"vector<float>"};
            }

            static const string Get_Blend_Weights_Spelling(void){
                return string{"m_Blend_Weights"};
            }


            static const string Get_Blend_Weights_Display_Name(void){
                return string{"Blend_Weights"};
            }

            static const vector<float>& Get_Blend_Weights_Attribute(shared_ptr<Bone_Blend_Weight> Instance){
                return Instance->m_Blend_Weights;
            }

            static void Set_Field_Blend_Weights_Attribute(shared_ptr<Bone_Blend_Weight> Instance, const vector<float>& Value){
                Instance->m_Blend_Weights=Value;
            }

            static const bool Is_Filed_Blend_Weights_CPPVector(void){
                return  !  false;
            }

                static const string Get_Blend_Weights_CPPVector_Element_Type_Spelling(void){
                    return string {"float"};
                }

                static const size_t Get_Blend_Weights_CPPVector_Capacity(shared_ptr<Bone_Blend_Weight> Instance){
                    return Instance->m_Blend_Weights.capacity();
                }

                static const size_t Get_Blend_Weights_CPPVector_Size(shared_ptr<Bone_Blend_Weight> Instance){
                    return Instance->m_Blend_Weights.size();
                }

                static const float& Get_Blend_Weights_CPPVector_Element(shared_ptr<Bone_Blend_Weight> Instance, size_t Index){
                    return Instance->m_Blend_Weights[Index];
                }

                static void Set_Blend_Weights_CPPVector_Element(shared_ptr<Bone_Blend_Weight> Instance, size_t Index, const float& Value){
                    Instance->m_Blend_Weights[Index]=Value;
                }

                static void Reserve_Blend_Weights_CPPVector(shared_ptr<Bone_Blend_Weight> Instance, size_t Capacity){
                    Instance->m_Blend_Weights.reserve(Capacity);
                }

                static void Push_Back_Blend_Weights_CPPVector(shared_ptr<Bone_Blend_Weight> Instance, const float& Value){
                    Instance->m_Blend_Weights.push_back(Value);
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

    class Reflection_BlendState_With_Clip_Data_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"BlendState_With_Clip_Data"};
        }

        static const string Get_Displaying_Name(void){
            return string{"BlendState_With_Clip_Data"};            
        }

            static const vector<Reflection_Instance<BlendState_With_Clip_Data>> Get_Base_Class_Reflection_Instance_List(shared_ptr<BlendState_With_Clip_Data> Instance){
                vector<Reflection_Instance<BlendState_With_Clip_Data>> Table;

                    

                return Table;
            }

            static const string Get_Blend_Clip_Type_Spelling(void){
                return string{"vector<shared_ptr<Animation_Clip>>"};
            }

            static const string Get_Blend_Clip_Spelling(void){
                return string{"m_Blend_Clip"};
            }


            static const string Get_Blend_Clip_Display_Name(void){
                return string{"Blend_Clip"};
            }

            static const vector<shared_ptr<Animation_Clip>>& Get_Blend_Clip_Attribute(shared_ptr<BlendState_With_Clip_Data> Instance){
                return Instance->m_Blend_Clip;
            }

            static void Set_Field_Blend_Clip_Attribute(shared_ptr<BlendState_With_Clip_Data> Instance, const vector<shared_ptr<Animation_Clip>>& Value){
                Instance->m_Blend_Clip=Value;
            }

            static const bool Is_Filed_Blend_Clip_CPPVector(void){
                return  !  false;
            }

                static const string Get_Blend_Clip_CPPVector_Element_Type_Spelling(void){
                    return string {"shared_ptr<Animation_Clip>"};
                }

                static const size_t Get_Blend_Clip_CPPVector_Capacity(shared_ptr<BlendState_With_Clip_Data> Instance){
                    return Instance->m_Blend_Clip.capacity();
                }

                static const size_t Get_Blend_Clip_CPPVector_Size(shared_ptr<BlendState_With_Clip_Data> Instance){
                    return Instance->m_Blend_Clip.size();
                }

                static const shared_ptr<Animation_Clip>& Get_Blend_Clip_CPPVector_Element(shared_ptr<BlendState_With_Clip_Data> Instance, size_t Index){
                    return Instance->m_Blend_Clip[Index];
                }

                static void Set_Blend_Clip_CPPVector_Element(shared_ptr<BlendState_With_Clip_Data> Instance, size_t Index, const shared_ptr<Animation_Clip>& Value){
                    Instance->m_Blend_Clip[Index]=Value;
                }

                static void Reserve_Blend_Clip_CPPVector(shared_ptr<BlendState_With_Clip_Data> Instance, size_t Capacity){
                    Instance->m_Blend_Clip.reserve(Capacity);
                }

                static void Push_Back_Blend_Clip_CPPVector(shared_ptr<BlendState_With_Clip_Data> Instance, const shared_ptr<Animation_Clip>& Value){
                    Instance->m_Blend_Clip.push_back(Value);
                }

            static const string Get_Blend_Skeleton_Type_Spelling(void){
                return string{"vector<shared_ptr<Skeleton_Node_Map>>"};
            }

            static const string Get_Blend_Skeleton_Spelling(void){
                return string{"m_Blend_Skeleton"};
            }


            static const string Get_Blend_Skeleton_Display_Name(void){
                return string{"Blend_Skeleton"};
            }

            static const vector<shared_ptr<Skeleton_Node_Map>>& Get_Blend_Skeleton_Attribute(shared_ptr<BlendState_With_Clip_Data> Instance){
                return Instance->m_Blend_Skeleton;
            }

            static void Set_Field_Blend_Skeleton_Attribute(shared_ptr<BlendState_With_Clip_Data> Instance, const vector<shared_ptr<Skeleton_Node_Map>>& Value){
                Instance->m_Blend_Skeleton=Value;
            }

            static const bool Is_Filed_Blend_Skeleton_CPPVector(void){
                return  !  false;
            }

                static const string Get_Blend_Skeleton_CPPVector_Element_Type_Spelling(void){
                    return string {"shared_ptr<Skeleton_Node_Map>"};
                }

                static const size_t Get_Blend_Skeleton_CPPVector_Capacity(shared_ptr<BlendState_With_Clip_Data> Instance){
                    return Instance->m_Blend_Skeleton.capacity();
                }

                static const size_t Get_Blend_Skeleton_CPPVector_Size(shared_ptr<BlendState_With_Clip_Data> Instance){
                    return Instance->m_Blend_Skeleton.size();
                }

                static const shared_ptr<Skeleton_Node_Map>& Get_Blend_Skeleton_CPPVector_Element(shared_ptr<BlendState_With_Clip_Data> Instance, size_t Index){
                    return Instance->m_Blend_Skeleton[Index];
                }

                static void Set_Blend_Skeleton_CPPVector_Element(shared_ptr<BlendState_With_Clip_Data> Instance, size_t Index, const shared_ptr<Skeleton_Node_Map>& Value){
                    Instance->m_Blend_Skeleton[Index]=Value;
                }

                static void Reserve_Blend_Skeleton_CPPVector(shared_ptr<BlendState_With_Clip_Data> Instance, size_t Capacity){
                    Instance->m_Blend_Skeleton.reserve(Capacity);
                }

                static void Push_Back_Blend_Skeleton_CPPVector(shared_ptr<BlendState_With_Clip_Data> Instance, const shared_ptr<Skeleton_Node_Map>& Value){
                    Instance->m_Blend_Skeleton.push_back(Value);
                }

            static const string Get_Blend_Weights_Type_Spelling(void){
                return string{"vector<shared_ptr<Bone_Blend_Weight>>"};
            }

            static const string Get_Blend_Weights_Spelling(void){
                return string{"m_Blend_Weights"};
            }


            static const string Get_Blend_Weights_Display_Name(void){
                return string{"Blend_Weights"};
            }

            static const vector<shared_ptr<Bone_Blend_Weight>>& Get_Blend_Weights_Attribute(shared_ptr<BlendState_With_Clip_Data> Instance){
                return Instance->m_Blend_Weights;
            }

            static void Set_Field_Blend_Weights_Attribute(shared_ptr<BlendState_With_Clip_Data> Instance, const vector<shared_ptr<Bone_Blend_Weight>>& Value){
                Instance->m_Blend_Weights=Value;
            }

            static const bool Is_Filed_Blend_Weights_CPPVector(void){
                return  !  false;
            }

                static const string Get_Blend_Weights_CPPVector_Element_Type_Spelling(void){
                    return string {"shared_ptr<Bone_Blend_Weight>"};
                }

                static const size_t Get_Blend_Weights_CPPVector_Capacity(shared_ptr<BlendState_With_Clip_Data> Instance){
                    return Instance->m_Blend_Weights.capacity();
                }

                static const size_t Get_Blend_Weights_CPPVector_Size(shared_ptr<BlendState_With_Clip_Data> Instance){
                    return Instance->m_Blend_Weights.size();
                }

                static const shared_ptr<Bone_Blend_Weight>& Get_Blend_Weights_CPPVector_Element(shared_ptr<BlendState_With_Clip_Data> Instance, size_t Index){
                    return Instance->m_Blend_Weights[Index];
                }

                static void Set_Blend_Weights_CPPVector_Element(shared_ptr<BlendState_With_Clip_Data> Instance, size_t Index, const shared_ptr<Bone_Blend_Weight>& Value){
                    Instance->m_Blend_Weights[Index]=Value;
                }

                static void Reserve_Blend_Weights_CPPVector(shared_ptr<BlendState_With_Clip_Data> Instance, size_t Capacity){
                    Instance->m_Blend_Weights.reserve(Capacity);
                }

                static void Push_Back_Blend_Weights_CPPVector(shared_ptr<BlendState_With_Clip_Data> Instance, const shared_ptr<Bone_Blend_Weight>& Value){
                    Instance->m_Blend_Weights.push_back(Value);
                }

            static const string Get_Blend_ratio_Type_Spelling(void){
                return string{"vector<float>"};
            }

            static const string Get_Blend_ratio_Spelling(void){
                return string{"m_Blend_ratio"};
            }


            static const string Get_Blend_ratio_Display_Name(void){
                return string{"Blend_ratio"};
            }

            static const vector<float>& Get_Blend_ratio_Attribute(shared_ptr<BlendState_With_Clip_Data> Instance){
                return Instance->m_Blend_ratio;
            }

            static void Set_Field_Blend_ratio_Attribute(shared_ptr<BlendState_With_Clip_Data> Instance, const vector<float>& Value){
                Instance->m_Blend_ratio=Value;
            }

            static const bool Is_Filed_Blend_ratio_CPPVector(void){
                return  !  false;
            }

                static const string Get_Blend_ratio_CPPVector_Element_Type_Spelling(void){
                    return string {"float"};
                }

                static const size_t Get_Blend_ratio_CPPVector_Capacity(shared_ptr<BlendState_With_Clip_Data> Instance){
                    return Instance->m_Blend_ratio.capacity();
                }

                static const size_t Get_Blend_ratio_CPPVector_Size(shared_ptr<BlendState_With_Clip_Data> Instance){
                    return Instance->m_Blend_ratio.size();
                }

                static const float& Get_Blend_ratio_CPPVector_Element(shared_ptr<BlendState_With_Clip_Data> Instance, size_t Index){
                    return Instance->m_Blend_ratio[Index];
                }

                static void Set_Blend_ratio_CPPVector_Element(shared_ptr<BlendState_With_Clip_Data> Instance, size_t Index, const float& Value){
                    Instance->m_Blend_ratio[Index]=Value;
                }

                static void Reserve_Blend_ratio_CPPVector(shared_ptr<BlendState_With_Clip_Data> Instance, size_t Capacity){
                    Instance->m_Blend_ratio.reserve(Capacity);
                }

                static void Push_Back_Blend_ratio_CPPVector(shared_ptr<BlendState_With_Clip_Data> Instance, const float& Value){
                    Instance->m_Blend_ratio.push_back(Value);
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

    class Reflection_Blend_State_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Blend_State"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Blend_State"};            
        }

            static const vector<Reflection_Instance<Blend_State>> Get_Base_Class_Reflection_Instance_List(shared_ptr<Blend_State> Instance){
                vector<Reflection_Instance<Blend_State>> Table;

                    

                return Table;
            }

            static const string Get_Blend_Clip_File_Path_Type_Spelling(void){
                return string{"vector<path>"};
            }

            static const string Get_Blend_Clip_File_Path_Spelling(void){
                return string{"m_Blend_Clip_File_Path"};
            }


            static const string Get_Blend_Clip_File_Path_Display_Name(void){
                return string{"Blend_Clip_File_Path"};
            }

            static const vector<path>& Get_Blend_Clip_File_Path_Attribute(shared_ptr<Blend_State> Instance){
                return Instance->m_Blend_Clip_File_Path;
            }

            static void Set_Field_Blend_Clip_File_Path_Attribute(shared_ptr<Blend_State> Instance, const vector<path>& Value){
                Instance->m_Blend_Clip_File_Path=Value;
            }

            static const bool Is_Filed_Blend_Clip_File_Path_CPPVector(void){
                return  !  false;
            }

                static const string Get_Blend_Clip_File_Path_CPPVector_Element_Type_Spelling(void){
                    return string {"path"};
                }

                static const size_t Get_Blend_Clip_File_Path_CPPVector_Capacity(shared_ptr<Blend_State> Instance){
                    return Instance->m_Blend_Clip_File_Path.capacity();
                }

                static const size_t Get_Blend_Clip_File_Path_CPPVector_Size(shared_ptr<Blend_State> Instance){
                    return Instance->m_Blend_Clip_File_Path.size();
                }

                static const path& Get_Blend_Clip_File_Path_CPPVector_Element(shared_ptr<Blend_State> Instance, size_t Index){
                    return Instance->m_Blend_Clip_File_Path[Index];
                }

                static void Set_Blend_Clip_File_Path_CPPVector_Element(shared_ptr<Blend_State> Instance, size_t Index, const path& Value){
                    Instance->m_Blend_Clip_File_Path[Index]=Value;
                }

                static void Reserve_Blend_Clip_File_Path_CPPVector(shared_ptr<Blend_State> Instance, size_t Capacity){
                    Instance->m_Blend_Clip_File_Path.reserve(Capacity);
                }

                static void Push_Back_Blend_Clip_File_Path_CPPVector(shared_ptr<Blend_State> Instance, const path& Value){
                    Instance->m_Blend_Clip_File_Path.push_back(Value);
                }

            static const string Get_Blend_Clip_File_Length_Type_Spelling(void){
                return string{"vector<float>"};
            }

            static const string Get_Blend_Clip_File_Length_Spelling(void){
                return string{"m_Blend_Clip_File_Length"};
            }


            static const string Get_Blend_Clip_File_Length_Display_Name(void){
                return string{"Blend_Clip_File_Length"};
            }

            static const vector<float>& Get_Blend_Clip_File_Length_Attribute(shared_ptr<Blend_State> Instance){
                return Instance->m_Blend_Clip_File_Length;
            }

            static void Set_Field_Blend_Clip_File_Length_Attribute(shared_ptr<Blend_State> Instance, const vector<float>& Value){
                Instance->m_Blend_Clip_File_Length=Value;
            }

            static const bool Is_Filed_Blend_Clip_File_Length_CPPVector(void){
                return  !  false;
            }

                static const string Get_Blend_Clip_File_Length_CPPVector_Element_Type_Spelling(void){
                    return string {"float"};
                }

                static const size_t Get_Blend_Clip_File_Length_CPPVector_Capacity(shared_ptr<Blend_State> Instance){
                    return Instance->m_Blend_Clip_File_Length.capacity();
                }

                static const size_t Get_Blend_Clip_File_Length_CPPVector_Size(shared_ptr<Blend_State> Instance){
                    return Instance->m_Blend_Clip_File_Length.size();
                }

                static const float& Get_Blend_Clip_File_Length_CPPVector_Element(shared_ptr<Blend_State> Instance, size_t Index){
                    return Instance->m_Blend_Clip_File_Length[Index];
                }

                static void Set_Blend_Clip_File_Length_CPPVector_Element(shared_ptr<Blend_State> Instance, size_t Index, const float& Value){
                    Instance->m_Blend_Clip_File_Length[Index]=Value;
                }

                static void Reserve_Blend_Clip_File_Length_CPPVector(shared_ptr<Blend_State> Instance, size_t Capacity){
                    Instance->m_Blend_Clip_File_Length.reserve(Capacity);
                }

                static void Push_Back_Blend_Clip_File_Length_CPPVector(shared_ptr<Blend_State> Instance, const float& Value){
                    Instance->m_Blend_Clip_File_Length.push_back(Value);
                }

            static const string Get_Blend_Skeleton_Map_File_Path_Type_Spelling(void){
                return string{"vector<path>"};
            }

            static const string Get_Blend_Skeleton_Map_File_Path_Spelling(void){
                return string{"m_Blend_Skeleton_Map_File_Path"};
            }


            static const string Get_Blend_Skeleton_Map_File_Path_Display_Name(void){
                return string{"Blend_Skeleton_Map_File_Path"};
            }

            static const vector<path>& Get_Blend_Skeleton_Map_File_Path_Attribute(shared_ptr<Blend_State> Instance){
                return Instance->m_Blend_Skeleton_Map_File_Path;
            }

            static void Set_Field_Blend_Skeleton_Map_File_Path_Attribute(shared_ptr<Blend_State> Instance, const vector<path>& Value){
                Instance->m_Blend_Skeleton_Map_File_Path=Value;
            }

            static const bool Is_Filed_Blend_Skeleton_Map_File_Path_CPPVector(void){
                return  !  false;
            }

                static const string Get_Blend_Skeleton_Map_File_Path_CPPVector_Element_Type_Spelling(void){
                    return string {"path"};
                }

                static const size_t Get_Blend_Skeleton_Map_File_Path_CPPVector_Capacity(shared_ptr<Blend_State> Instance){
                    return Instance->m_Blend_Skeleton_Map_File_Path.capacity();
                }

                static const size_t Get_Blend_Skeleton_Map_File_Path_CPPVector_Size(shared_ptr<Blend_State> Instance){
                    return Instance->m_Blend_Skeleton_Map_File_Path.size();
                }

                static const path& Get_Blend_Skeleton_Map_File_Path_CPPVector_Element(shared_ptr<Blend_State> Instance, size_t Index){
                    return Instance->m_Blend_Skeleton_Map_File_Path[Index];
                }

                static void Set_Blend_Skeleton_Map_File_Path_CPPVector_Element(shared_ptr<Blend_State> Instance, size_t Index, const path& Value){
                    Instance->m_Blend_Skeleton_Map_File_Path[Index]=Value;
                }

                static void Reserve_Blend_Skeleton_Map_File_Path_CPPVector(shared_ptr<Blend_State> Instance, size_t Capacity){
                    Instance->m_Blend_Skeleton_Map_File_Path.reserve(Capacity);
                }

                static void Push_Back_Blend_Skeleton_Map_File_Path_CPPVector(shared_ptr<Blend_State> Instance, const path& Value){
                    Instance->m_Blend_Skeleton_Map_File_Path.push_back(Value);
                }

            static const string Get_Blend_Weights_Type_Spelling(void){
                return string{"vector<float>"};
            }

            static const string Get_Blend_Weights_Spelling(void){
                return string{"m_Blend_Weights"};
            }


            static const string Get_Blend_Weights_Display_Name(void){
                return string{"Blend_Weights"};
            }

            static const vector<float>& Get_Blend_Weights_Attribute(shared_ptr<Blend_State> Instance){
                return Instance->m_Blend_Weights;
            }

            static void Set_Field_Blend_Weights_Attribute(shared_ptr<Blend_State> Instance, const vector<float>& Value){
                Instance->m_Blend_Weights=Value;
            }

            static const bool Is_Filed_Blend_Weights_CPPVector(void){
                return  !  false;
            }

                static const string Get_Blend_Weights_CPPVector_Element_Type_Spelling(void){
                    return string {"float"};
                }

                static const size_t Get_Blend_Weights_CPPVector_Capacity(shared_ptr<Blend_State> Instance){
                    return Instance->m_Blend_Weights.capacity();
                }

                static const size_t Get_Blend_Weights_CPPVector_Size(shared_ptr<Blend_State> Instance){
                    return Instance->m_Blend_Weights.size();
                }

                static const float& Get_Blend_Weights_CPPVector_Element(shared_ptr<Blend_State> Instance, size_t Index){
                    return Instance->m_Blend_Weights[Index];
                }

                static void Set_Blend_Weights_CPPVector_Element(shared_ptr<Blend_State> Instance, size_t Index, const float& Value){
                    Instance->m_Blend_Weights[Index]=Value;
                }

                static void Reserve_Blend_Weights_CPPVector(shared_ptr<Blend_State> Instance, size_t Capacity){
                    Instance->m_Blend_Weights.reserve(Capacity);
                }

                static void Push_Back_Blend_Weights_CPPVector(shared_ptr<Blend_State> Instance, const float& Value){
                    Instance->m_Blend_Weights.push_back(Value);
                }

            static const string Get_Blend_Mask_File_Path_Type_Spelling(void){
                return string{"vector<path>"};
            }

            static const string Get_Blend_Mask_File_Path_Spelling(void){
                return string{"m_Blend_Mask_File_Path"};
            }


            static const string Get_Blend_Mask_File_Path_Display_Name(void){
                return string{"Blend_Mask_File_Path"};
            }

            static const vector<path>& Get_Blend_Mask_File_Path_Attribute(shared_ptr<Blend_State> Instance){
                return Instance->m_Blend_Mask_File_Path;
            }

            static void Set_Field_Blend_Mask_File_Path_Attribute(shared_ptr<Blend_State> Instance, const vector<path>& Value){
                Instance->m_Blend_Mask_File_Path=Value;
            }

            static const bool Is_Filed_Blend_Mask_File_Path_CPPVector(void){
                return  !  false;
            }

                static const string Get_Blend_Mask_File_Path_CPPVector_Element_Type_Spelling(void){
                    return string {"path"};
                }

                static const size_t Get_Blend_Mask_File_Path_CPPVector_Capacity(shared_ptr<Blend_State> Instance){
                    return Instance->m_Blend_Mask_File_Path.capacity();
                }

                static const size_t Get_Blend_Mask_File_Path_CPPVector_Size(shared_ptr<Blend_State> Instance){
                    return Instance->m_Blend_Mask_File_Path.size();
                }

                static const path& Get_Blend_Mask_File_Path_CPPVector_Element(shared_ptr<Blend_State> Instance, size_t Index){
                    return Instance->m_Blend_Mask_File_Path[Index];
                }

                static void Set_Blend_Mask_File_Path_CPPVector_Element(shared_ptr<Blend_State> Instance, size_t Index, const path& Value){
                    Instance->m_Blend_Mask_File_Path[Index]=Value;
                }

                static void Reserve_Blend_Mask_File_Path_CPPVector(shared_ptr<Blend_State> Instance, size_t Capacity){
                    Instance->m_Blend_Mask_File_Path.reserve(Capacity);
                }

                static void Push_Back_Blend_Mask_File_Path_CPPVector(shared_ptr<Blend_State> Instance, const path& Value){
                    Instance->m_Blend_Mask_File_Path.push_back(Value);
                }

            static const string Get_BlendState_Type_Spelling(void){
                return string{"vector<shared_ptr<BlendState_With_Clip_Data>>"};
            }

            static const string Get_BlendState_Spelling(void){
                return string{"m_BlendState"};
            }


            static const string Get_BlendState_Display_Name(void){
                return string{"BlendState"};
            }

            static const vector<shared_ptr<BlendState_With_Clip_Data>>& Get_BlendState_Attribute(shared_ptr<Blend_State> Instance){
                return Instance->m_BlendState;
            }

            static void Set_Field_BlendState_Attribute(shared_ptr<Blend_State> Instance, const vector<shared_ptr<BlendState_With_Clip_Data>>& Value){
                Instance->m_BlendState=Value;
            }

            static const bool Is_Filed_BlendState_CPPVector(void){
                return  !  false;
            }

                static const string Get_BlendState_CPPVector_Element_Type_Spelling(void){
                    return string {"shared_ptr<BlendState_With_Clip_Data>"};
                }

                static const size_t Get_BlendState_CPPVector_Capacity(shared_ptr<Blend_State> Instance){
                    return Instance->m_BlendState.capacity();
                }

                static const size_t Get_BlendState_CPPVector_Size(shared_ptr<Blend_State> Instance){
                    return Instance->m_BlendState.size();
                }

                static const shared_ptr<BlendState_With_Clip_Data>& Get_BlendState_CPPVector_Element(shared_ptr<Blend_State> Instance, size_t Index){
                    return Instance->m_BlendState[Index];
                }

                static void Set_BlendState_CPPVector_Element(shared_ptr<Blend_State> Instance, size_t Index, const shared_ptr<BlendState_With_Clip_Data>& Value){
                    Instance->m_BlendState[Index]=Value;
                }

                static void Reserve_BlendState_CPPVector(shared_ptr<Blend_State> Instance, size_t Capacity){
                    Instance->m_BlendState.reserve(Capacity);
                }

                static void Push_Back_BlendState_CPPVector(shared_ptr<Blend_State> Instance, const shared_ptr<BlendState_With_Clip_Data>& Value){
                    Instance->m_BlendState.push_back(Value);
                }

            static const string Get_Blend_ratio_Type_Spelling(void){
                return string{"vector<float>"};
            }

            static const string Get_Blend_ratio_Spelling(void){
                return string{"m_Blend_ratio"};
            }


            static const string Get_Blend_ratio_Display_Name(void){
                return string{"Blend_ratio"};
            }

            static const vector<float>& Get_Blend_ratio_Attribute(shared_ptr<Blend_State> Instance){
                return Instance->m_Blend_ratio;
            }

            static void Set_Field_Blend_ratio_Attribute(shared_ptr<Blend_State> Instance, const vector<float>& Value){
                Instance->m_Blend_ratio=Value;
            }

            static const bool Is_Filed_Blend_ratio_CPPVector(void){
                return  !  false;
            }

                static const string Get_Blend_ratio_CPPVector_Element_Type_Spelling(void){
                    return string {"float"};
                }

                static const size_t Get_Blend_ratio_CPPVector_Capacity(shared_ptr<Blend_State> Instance){
                    return Instance->m_Blend_ratio.capacity();
                }

                static const size_t Get_Blend_ratio_CPPVector_Size(shared_ptr<Blend_State> Instance){
                    return Instance->m_Blend_ratio.size();
                }

                static const float& Get_Blend_ratio_CPPVector_Element(shared_ptr<Blend_State> Instance, size_t Index){
                    return Instance->m_Blend_ratio[Index];
                }

                static void Set_Blend_ratio_CPPVector_Element(shared_ptr<Blend_State> Instance, size_t Index, const float& Value){
                    Instance->m_Blend_ratio[Index]=Value;
                }

                static void Reserve_Blend_ratio_CPPVector(shared_ptr<Blend_State> Instance, size_t Capacity){
                    Instance->m_Blend_ratio.reserve(Capacity);
                }

                static void Push_Back_Blend_ratio_CPPVector(shared_ptr<Blend_State> Instance, const float& Value){
                    Instance->m_Blend_ratio.push_back(Value);
                }


    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection

