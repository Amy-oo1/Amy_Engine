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

        

            static const string Get_Blend_Clip_URL_Type_Spelling(void){
                return string{"vector<path>"};
            }

            static const string Get_Blend_Clip_URL_Spelling(void){
                return string{"m_Blend_Clip_URL"};
            }


            static const string Get_Blend_Clip_URL_Display_Name(void){
                return string{"Blend_Clip_URL"};
            }

            static const vector<path>& Get_Blend_Clip_URL_Attribute(shared_ptr<Blend_State> Instance){
                return Instance->m_Blend_Clip_URL;
            }

            static void Set_Field_Blend_Clip_URL_Attribute(shared_ptr<Blend_State> Instance, const vector<path>& Value){
                Instance->m_Blend_Clip_URL=Value;
            }

            static const bool Is_Filed_Blend_Clip_URL_CPPVector(void){
                return  !  false;
            }

                static const string Get_Blend_Clip_URL_CPPVector_Element_Type_Spelling(void){
                    return string {"path"};
                }

                static const size_t Get_Blend_Clip_URL_CPPVector_Capacity(shared_ptr<Blend_State> Instance){
                    return Instance->m_Blend_Clip_URL.capacity();
                }

                static const size_t Get_Blend_Clip_URL_CPPVector_Size(shared_ptr<Blend_State> Instance){
                    return Instance->m_Blend_Clip_URL.size();
                }

                static const path& Get_Blend_Clip_URL_CPPVector_Element(shared_ptr<Blend_State> Instance, size_t Index){
                    return Instance->m_Blend_Clip_URL[Index];
                }

                static void Set_Blend_Clip_URL_CPPVector_Element(shared_ptr<Blend_State> Instance, size_t Index, const path& Value){
                    Instance->m_Blend_Clip_URL[Index]=Value;
                }

                static void Reserve_Blend_Clip_URL_CPPVector(shared_ptr<Blend_State> Instance, size_t Capacity){
                    Instance->m_Blend_Clip_URL.reserve(Capacity);
                }

                static void Push_Back_Blend_Clip_URL_CPPVector(shared_ptr<Blend_State> Instance, const path& Value){
                    Instance->m_Blend_Clip_URL.push_back(Value);
                }

            static const string Get_Blend_Clip_Length_Type_Spelling(void){
                return string{"vector<float>"};
            }

            static const string Get_Blend_Clip_Length_Spelling(void){
                return string{"m_Blend_Clip_Length"};
            }


            static const string Get_Blend_Clip_Length_Display_Name(void){
                return string{"Blend_Clip_Length"};
            }

            static const vector<float>& Get_Blend_Clip_Length_Attribute(shared_ptr<Blend_State> Instance){
                return Instance->m_Blend_Clip_Length;
            }

            static void Set_Field_Blend_Clip_Length_Attribute(shared_ptr<Blend_State> Instance, const vector<float>& Value){
                Instance->m_Blend_Clip_Length=Value;
            }

            static const bool Is_Filed_Blend_Clip_Length_CPPVector(void){
                return  !  false;
            }

                static const string Get_Blend_Clip_Length_CPPVector_Element_Type_Spelling(void){
                    return string {"float"};
                }

                static const size_t Get_Blend_Clip_Length_CPPVector_Capacity(shared_ptr<Blend_State> Instance){
                    return Instance->m_Blend_Clip_Length.capacity();
                }

                static const size_t Get_Blend_Clip_Length_CPPVector_Size(shared_ptr<Blend_State> Instance){
                    return Instance->m_Blend_Clip_Length.size();
                }

                static const float& Get_Blend_Clip_Length_CPPVector_Element(shared_ptr<Blend_State> Instance, size_t Index){
                    return Instance->m_Blend_Clip_Length[Index];
                }

                static void Set_Blend_Clip_Length_CPPVector_Element(shared_ptr<Blend_State> Instance, size_t Index, const float& Value){
                    Instance->m_Blend_Clip_Length[Index]=Value;
                }

                static void Reserve_Blend_Clip_Length_CPPVector(shared_ptr<Blend_State> Instance, size_t Capacity){
                    Instance->m_Blend_Clip_Length.reserve(Capacity);
                }

                static void Push_Back_Blend_Clip_Length_CPPVector(shared_ptr<Blend_State> Instance, const float& Value){
                    Instance->m_Blend_Clip_Length.push_back(Value);
                }

            static const string Get_Blend_Skeleton_Node_Map_URL_Type_Spelling(void){
                return string{"vector<path>"};
            }

            static const string Get_Blend_Skeleton_Node_Map_URL_Spelling(void){
                return string{"m_Blend_Skeleton_Node_Map_URL"};
            }


            static const string Get_Blend_Skeleton_Node_Map_URL_Display_Name(void){
                return string{"Blend_Skeleton_Node_Map_URL"};
            }

            static const vector<path>& Get_Blend_Skeleton_Node_Map_URL_Attribute(shared_ptr<Blend_State> Instance){
                return Instance->m_Blend_Skeleton_Node_Map_URL;
            }

            static void Set_Field_Blend_Skeleton_Node_Map_URL_Attribute(shared_ptr<Blend_State> Instance, const vector<path>& Value){
                Instance->m_Blend_Skeleton_Node_Map_URL=Value;
            }

            static const bool Is_Filed_Blend_Skeleton_Node_Map_URL_CPPVector(void){
                return  !  false;
            }

                static const string Get_Blend_Skeleton_Node_Map_URL_CPPVector_Element_Type_Spelling(void){
                    return string {"path"};
                }

                static const size_t Get_Blend_Skeleton_Node_Map_URL_CPPVector_Capacity(shared_ptr<Blend_State> Instance){
                    return Instance->m_Blend_Skeleton_Node_Map_URL.capacity();
                }

                static const size_t Get_Blend_Skeleton_Node_Map_URL_CPPVector_Size(shared_ptr<Blend_State> Instance){
                    return Instance->m_Blend_Skeleton_Node_Map_URL.size();
                }

                static const path& Get_Blend_Skeleton_Node_Map_URL_CPPVector_Element(shared_ptr<Blend_State> Instance, size_t Index){
                    return Instance->m_Blend_Skeleton_Node_Map_URL[Index];
                }

                static void Set_Blend_Skeleton_Node_Map_URL_CPPVector_Element(shared_ptr<Blend_State> Instance, size_t Index, const path& Value){
                    Instance->m_Blend_Skeleton_Node_Map_URL[Index]=Value;
                }

                static void Reserve_Blend_Skeleton_Node_Map_URL_CPPVector(shared_ptr<Blend_State> Instance, size_t Capacity){
                    Instance->m_Blend_Skeleton_Node_Map_URL.reserve(Capacity);
                }

                static void Push_Back_Blend_Skeleton_Node_Map_URL_CPPVector(shared_ptr<Blend_State> Instance, const path& Value){
                    Instance->m_Blend_Skeleton_Node_Map_URL.push_back(Value);
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

            static const string Get_Blend_Mask_URL_Type_Spelling(void){
                return string{"vector<path>"};
            }

            static const string Get_Blend_Mask_URL_Spelling(void){
                return string{"m_Blend_Mask_URL"};
            }


            static const string Get_Blend_Mask_URL_Display_Name(void){
                return string{"Blend_Mask_URL"};
            }

            static const vector<path>& Get_Blend_Mask_URL_Attribute(shared_ptr<Blend_State> Instance){
                return Instance->m_Blend_Mask_URL;
            }

            static void Set_Field_Blend_Mask_URL_Attribute(shared_ptr<Blend_State> Instance, const vector<path>& Value){
                Instance->m_Blend_Mask_URL=Value;
            }

            static const bool Is_Filed_Blend_Mask_URL_CPPVector(void){
                return  !  false;
            }

                static const string Get_Blend_Mask_URL_CPPVector_Element_Type_Spelling(void){
                    return string {"path"};
                }

                static const size_t Get_Blend_Mask_URL_CPPVector_Capacity(shared_ptr<Blend_State> Instance){
                    return Instance->m_Blend_Mask_URL.capacity();
                }

                static const size_t Get_Blend_Mask_URL_CPPVector_Size(shared_ptr<Blend_State> Instance){
                    return Instance->m_Blend_Mask_URL.size();
                }

                static const path& Get_Blend_Mask_URL_CPPVector_Element(shared_ptr<Blend_State> Instance, size_t Index){
                    return Instance->m_Blend_Mask_URL[Index];
                }

                static void Set_Blend_Mask_URL_CPPVector_Element(shared_ptr<Blend_State> Instance, size_t Index, const path& Value){
                    Instance->m_Blend_Mask_URL[Index]=Value;
                }

                static void Reserve_Blend_Mask_URL_CPPVector(shared_ptr<Blend_State> Instance, size_t Capacity){
                    Instance->m_Blend_Mask_URL.reserve(Capacity);
                }

                static void Push_Back_Blend_Mask_URL_CPPVector(shared_ptr<Blend_State> Instance, const path& Value){
                    Instance->m_Blend_Mask_URL.push_back(Value);
                }

            static const string Get_Blend_Ratio_Type_Spelling(void){
                return string{"vector<float>"};
            }

            static const string Get_Blend_Ratio_Spelling(void){
                return string{"m_Blend_Ratio"};
            }


            static const string Get_Blend_Ratio_Display_Name(void){
                return string{"Blend_Ratio"};
            }

            static const vector<float>& Get_Blend_Ratio_Attribute(shared_ptr<Blend_State> Instance){
                return Instance->m_Blend_Ratio;
            }

            static void Set_Field_Blend_Ratio_Attribute(shared_ptr<Blend_State> Instance, const vector<float>& Value){
                Instance->m_Blend_Ratio=Value;
            }

            static const bool Is_Filed_Blend_Ratio_CPPVector(void){
                return  !  false;
            }

                static const string Get_Blend_Ratio_CPPVector_Element_Type_Spelling(void){
                    return string {"float"};
                }

                static const size_t Get_Blend_Ratio_CPPVector_Capacity(shared_ptr<Blend_State> Instance){
                    return Instance->m_Blend_Ratio.capacity();
                }

                static const size_t Get_Blend_Ratio_CPPVector_Size(shared_ptr<Blend_State> Instance){
                    return Instance->m_Blend_Ratio.size();
                }

                static const float& Get_Blend_Ratio_CPPVector_Element(shared_ptr<Blend_State> Instance, size_t Index){
                    return Instance->m_Blend_Ratio[Index];
                }

                static void Set_Blend_Ratio_CPPVector_Element(shared_ptr<Blend_State> Instance, size_t Index, const float& Value){
                    Instance->m_Blend_Ratio[Index]=Value;
                }

                static void Reserve_Blend_Ratio_CPPVector(shared_ptr<Blend_State> Instance, size_t Capacity){
                    Instance->m_Blend_Ratio.reserve(Capacity);
                }

                static void Push_Back_Blend_Ratio_CPPVector(shared_ptr<Blend_State> Instance, const float& Value){
                    Instance->m_Blend_Ratio.push_back(Value);
                }


    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection

