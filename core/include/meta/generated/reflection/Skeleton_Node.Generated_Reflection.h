#pragma once

#include<string>
#include<vector>
#include<memory>
#include<cstddef>

#include "json.h"

#include "meta/Reflection/Reflection_Instance.h"

#include "meta/Serializer/Serializer.h"

#include "D:/Amy_Engine/resource/include/components/skeleton/Skeleton_Node.h"

namespace NameSpace_Resource::NameSpace_Components{

    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;
    using std::static_pointer_cast;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

    class Reflection_Skeleton_Node_Map_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Skeleton_Node_Map"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Skeleton_Node_Map"};            
        }

        

            static const string Get_Convert_Type_Spelling(void){
                return string{"vector<size_t>"};
            }

            static const string Get_Convert_Spelling(void){
                return string{"m_Convert"};
            }


            static const string Get_Convert_Display_Name(void){
                return string{"Convert"};
            }

            static const vector<size_t>& Get_Convert_Attribute(shared_ptr<Skeleton_Node_Map> Instance){
                return Instance->m_Convert;
            }

            static void Set_Field_Convert_Attribute(shared_ptr<Skeleton_Node_Map> Instance, const vector<size_t>& Value){
                Instance->m_Convert=Value;
            }

            static const bool Is_Filed_Convert_CPPVector(void){
                return  !  false;
            }

                static const string Get_Convert_CPPVector_Element_Type_Spelling(void){
                    return string {"size_t"};
                }

                static const size_t Get_Convert_CPPVector_Capacity(shared_ptr<Skeleton_Node_Map> Instance){
                    return Instance->m_Convert.capacity();
                }

                static const size_t Get_Convert_CPPVector_Size(shared_ptr<Skeleton_Node_Map> Instance){
                    return Instance->m_Convert.size();
                }

                static const size_t& Get_Convert_CPPVector_Element(shared_ptr<Skeleton_Node_Map> Instance, size_t Index){
                    return Instance->m_Convert[Index];
                }

                static void Set_Convert_CPPVector_Element(shared_ptr<Skeleton_Node_Map> Instance, size_t Index, const size_t& Value){
                    Instance->m_Convert[Index]=Value;
                }

                static void Reserve_Convert_CPPVector(shared_ptr<Skeleton_Node_Map> Instance, size_t Capacity){
                    Instance->m_Convert.reserve(Capacity);
                }

                static void Push_Back_Convert_CPPVector(shared_ptr<Skeleton_Node_Map> Instance, const size_t& Value){
                    Instance->m_Convert.push_back(Value);
                }


    };
   
}// namespace NameSpace_Resource::NameSpace_Components

    
 

