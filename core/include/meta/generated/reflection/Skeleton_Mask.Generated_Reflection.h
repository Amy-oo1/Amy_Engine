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

    class Reflection_Skeleton_Mask_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Skeleton_Mask"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Skeleton_Mask"};            
        }

            static const vector<Reflection_Instance<Skeleton_Mask>> Get_Base_Class_Reflection_Instance_List(shared_ptr<Skeleton_Mask> Instance){
                vector<Reflection_Instance<Skeleton_Mask>> Table;

                    

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

            static const path Get_Skeleton_File_Path_Attribute(shared_ptr<Skeleton_Mask> Instance){
                return Instance->m_Skeleton_File_Path;
            }

            static void Set_Field_Skeleton_File_Path_Attribute(shared_ptr<Skeleton_Mask> Instance, const path& Value){
                Instance->m_Skeleton_File_Path=Value;
            }

            static const bool Is_Filed_Skeleton_File_Path_CPPVector(void){
                return  false;
            }

            

            static const string Get_enabled_Type_Spelling(void){
                return string{"vector<size_t>"};
            }

            static const string Get_enabled_Spelling(void){
                return string{"enabled"};
            }


            static const string Get_enabled_Display_Name(void){
                return string{"enabled"};
            }

            static const vector<size_t> Get_enabled_Attribute(shared_ptr<Skeleton_Mask> Instance){
                return Instance->enabled;
            }

            static void Set_Field_enabled_Attribute(shared_ptr<Skeleton_Mask> Instance, const vector<size_t>& Value){
                Instance->enabled=Value;
            }

            static const bool Is_Filed_enabled_CPPVector(void){
                return  !  false;
            }

                static const string Get_enabled_CPPVector_Element_Type_Spelling(void){
                    return string {"size_t"};
                }

                static const size_t Get_enabled_CPPVector_Capacity(shared_ptr<Skeleton_Mask> Instance){
                    return Instance->enabled.capacity();
                }

                static const size_t Get_enabled_CPPVector_Size(shared_ptr<Skeleton_Mask> Instance){
                    return Instance->enabled.size();
                }

                static const size_t Get_enabled_CPPVector_Element(shared_ptr<Skeleton_Mask> Instance, size_t Index){
                    return Instance->enabled[Index];
                }

                static void Set_enabled_CPPVector_Element(shared_ptr<Skeleton_Mask> Instance, size_t Index, const size_t& Value){
                    Instance->enabled[Index]=Value;
                }


    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection

