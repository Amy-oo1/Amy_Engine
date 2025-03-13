#pragma once

#include<string>
#include<vector>
#include<memory>
#include<cstddef>

#include "meta/Reflection/Reflection_Instance.h"

#include "D:/Amy_Engine/resource/include/components/skeleton/Skeleton_Mask.h"

namespace NameSpace_Resource::NameSpace_Components{

    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;
    using std::static_pointer_cast;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

    class Reflection_Bone_Blend_Mask_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Bone_Blend_Mask"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Bone_Blend_Mask"};            
        }

            static const vector<Reflection_Instance<Bone_Blend_Mask>> Get_Base_Class_Reflection_Instance_List(shared_ptr<Bone_Blend_Mask> Instance){
                vector<Reflection_Instance<Bone_Blend_Mask>> Table;

                    

                return Table;
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

            static const path& Get_Skeleton_Data_URL_Attribute(shared_ptr<Bone_Blend_Mask> Instance){
                return Instance->m_Skeleton_Data_URL;
            }

            static void Set_Field_Skeleton_Data_URL_Attribute(shared_ptr<Bone_Blend_Mask> Instance, const path& Value){
                Instance->m_Skeleton_Data_URL=Value;
            }

            static const bool Is_Filed_Skeleton_Data_URL_CPPVector(void){
                return  false;
            }

            

            static const string Get_Enabled_Type_Spelling(void){
                return string{"vector<size_t>"};
            }

            static const string Get_Enabled_Spelling(void){
                return string{"Enabled"};
            }


            static const string Get_Enabled_Display_Name(void){
                return string{"Enabled"};
            }

            static const vector<size_t>& Get_Enabled_Attribute(shared_ptr<Bone_Blend_Mask> Instance){
                return Instance->Enabled;
            }

            static void Set_Field_Enabled_Attribute(shared_ptr<Bone_Blend_Mask> Instance, const vector<size_t>& Value){
                Instance->Enabled=Value;
            }

            static const bool Is_Filed_Enabled_CPPVector(void){
                return  !  false;
            }

                static const string Get_Enabled_CPPVector_Element_Type_Spelling(void){
                    return string {"size_t"};
                }

                static const size_t Get_Enabled_CPPVector_Capacity(shared_ptr<Bone_Blend_Mask> Instance){
                    return Instance->Enabled.capacity();
                }

                static const size_t Get_Enabled_CPPVector_Size(shared_ptr<Bone_Blend_Mask> Instance){
                    return Instance->Enabled.size();
                }

                static const size_t& Get_Enabled_CPPVector_Element(shared_ptr<Bone_Blend_Mask> Instance, size_t Index){
                    return Instance->Enabled[Index];
                }

                static void Set_Enabled_CPPVector_Element(shared_ptr<Bone_Blend_Mask> Instance, size_t Index, const size_t& Value){
                    Instance->Enabled[Index]=Value;
                }

                static void Reserve_Enabled_CPPVector(shared_ptr<Bone_Blend_Mask> Instance, size_t Capacity){
                    Instance->Enabled.reserve(Capacity);
                }

                static void Push_Back_Enabled_CPPVector(shared_ptr<Bone_Blend_Mask> Instance, const size_t& Value){
                    Instance->Enabled.push_back(Value);
                }


    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection

