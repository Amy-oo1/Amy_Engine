#pragma once

#include<string>
#include<vector>
#include<memory>
#include<cstddef>

#include "meta/Reflection/Reflection_Instance.h"

#include "D:/Amy_Engine/function/include/frame/components/transform/Transform_Component.h"

namespace NameSpace_Function::NameSpace_Frame::NameSpace_Components::NameSpace_Transform{

    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;
    using std::static_pointer_cast;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

    class Reflection_Transform_Component_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Transform_Component"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Transform_Component"};            
        }

            static const vector<Reflection_Instance<Transform_Component>> Get_Base_Class_Reflection_Instance_List(shared_ptr<Transform_Component> Instance){
                vector<Reflection_Instance<Transform_Component>> Table;

                        Table.emplace_back(string{"Component"},static_pointer_cast<Transform_Component>(Instance));

                return Table;
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

            static const Affine_Transform& Get_Transform_Attribute(shared_ptr<Transform_Component> Instance){
                return Instance->m_Transform;
            }

            static void Set_Field_Transform_Attribute(shared_ptr<Transform_Component> Instance, const Affine_Transform& Value){
                Instance->m_Transform=Value;
            }

            static const bool Is_Filed_Transform_CPPVector(void){
                return  false;
            }

            

            static const string Get_Transform_Buffer_Type_Spelling(void){
                return string{"vector<Affine_Transform>"};
            }

            static const string Get_Transform_Buffer_Spelling(void){
                return string{"m_Transform_Buffer"};
            }


            static const string Get_Transform_Buffer_Display_Name(void){
                return string{"Transform_Buffer"};
            }

            static const vector<Affine_Transform>& Get_Transform_Buffer_Attribute(shared_ptr<Transform_Component> Instance){
                return Instance->m_Transform_Buffer;
            }

            static void Set_Field_Transform_Buffer_Attribute(shared_ptr<Transform_Component> Instance, const vector<Affine_Transform>& Value){
                Instance->m_Transform_Buffer=Value;
            }

            static const bool Is_Filed_Transform_Buffer_CPPVector(void){
                return  !  false;
            }

                static const string Get_Transform_Buffer_CPPVector_Element_Type_Spelling(void){
                    return string {"Affine_Transform"};
                }

                static const size_t Get_Transform_Buffer_CPPVector_Capacity(shared_ptr<Transform_Component> Instance){
                    return Instance->m_Transform_Buffer.capacity();
                }

                static const size_t Get_Transform_Buffer_CPPVector_Size(shared_ptr<Transform_Component> Instance){
                    return Instance->m_Transform_Buffer.size();
                }

                static const Affine_Transform& Get_Transform_Buffer_CPPVector_Element(shared_ptr<Transform_Component> Instance, size_t Index){
                    return Instance->m_Transform_Buffer[Index];
                }

                static void Set_Transform_Buffer_CPPVector_Element(shared_ptr<Transform_Component> Instance, size_t Index, const Affine_Transform& Value){
                    Instance->m_Transform_Buffer[Index]=Value;
                }

                static void Reserve_Transform_Buffer_CPPVector(shared_ptr<Transform_Component> Instance, size_t Capacity){
                    Instance->m_Transform_Buffer.reserve(Capacity);
                }

                static void Push_Back_Transform_Buffer_CPPVector(shared_ptr<Transform_Component> Instance, const Affine_Transform& Value){
                    Instance->m_Transform_Buffer.push_back(Value);
                }

            static const string Get_Currrent_Buffer_Index_Type_Spelling(void){
                return string{"size_t"};
            }

            static const string Get_Currrent_Buffer_Index_Spelling(void){
                return string{"m_Currrent_Buffer_Index"};
            }


            static const string Get_Currrent_Buffer_Index_Display_Name(void){
                return string{"Currrent_Buffer_Index"};
            }

            static const size_t& Get_Currrent_Buffer_Index_Attribute(shared_ptr<Transform_Component> Instance){
                return Instance->m_Currrent_Buffer_Index;
            }

            static void Set_Field_Currrent_Buffer_Index_Attribute(shared_ptr<Transform_Component> Instance, const size_t& Value){
                Instance->m_Currrent_Buffer_Index=Value;
            }

            static const bool Is_Filed_Currrent_Buffer_Index_CPPVector(void){
                return  false;
            }

            

            static const string Get_Next_Buffer_Index_Type_Spelling(void){
                return string{"size_t"};
            }

            static const string Get_Next_Buffer_Index_Spelling(void){
                return string{"m_Next_Buffer_Index"};
            }


            static const string Get_Next_Buffer_Index_Display_Name(void){
                return string{"Next_Buffer_Index"};
            }

            static const size_t& Get_Next_Buffer_Index_Attribute(shared_ptr<Transform_Component> Instance){
                return Instance->m_Next_Buffer_Index;
            }

            static void Set_Field_Next_Buffer_Index_Attribute(shared_ptr<Transform_Component> Instance, const size_t& Value){
                Instance->m_Next_Buffer_Index=Value;
            }

            static const bool Is_Filed_Next_Buffer_Index_CPPVector(void){
                return  false;
            }

            


    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection

