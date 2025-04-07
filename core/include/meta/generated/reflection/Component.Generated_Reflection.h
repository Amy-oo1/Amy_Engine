#pragma once

#include<string>
#include<vector>
#include<memory>
#include<cstddef>

#include "json.h"

#include "meta/Reflection/Reflection_Instance.h"

#include "meta/Serializer/Serializer.h"

#include "D:/Amy_Engine/function/include/frame/components/Component.h"

namespace NameSpace_Function::NameSpace_Frame::NameSpace_Components{

    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;
    using std::static_pointer_cast;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

    class Reflection_Component_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Component"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Component"};            
        }

        

            static const string Get_Is_Dirty_Type_Spelling(void){
                return string{"bool"};
            }

            static const string Get_Is_Dirty_Spelling(void){
                return string{"m_Is_Dirty"};
            }


            static const string Get_Is_Dirty_Display_Name(void){
                return string{"Is_Dirty"};
            }

            static const bool& Get_Is_Dirty_Attribute(shared_ptr<Component> Instance){
                return Instance->m_Is_Dirty;
            }

            static void Set_Field_Is_Dirty_Attribute(shared_ptr<Component> Instance, const bool& Value){
                Instance->m_Is_Dirty=Value;
            }

            static const bool Is_Filed_Is_Dirty_CPPVector(void){
                return  false;
            }

            

            static const string Get_Is_Scale_Dirty_Type_Spelling(void){
                return string{"bool"};
            }

            static const string Get_Is_Scale_Dirty_Spelling(void){
                return string{"m_Is_Scale_Dirty"};
            }


            static const string Get_Is_Scale_Dirty_Display_Name(void){
                return string{"Is_Scale_Dirty"};
            }

            static const bool& Get_Is_Scale_Dirty_Attribute(shared_ptr<Component> Instance){
                return Instance->m_Is_Scale_Dirty;
            }

            static void Set_Field_Is_Scale_Dirty_Attribute(shared_ptr<Component> Instance, const bool& Value){
                Instance->m_Is_Scale_Dirty=Value;
            }

            static const bool Is_Filed_Is_Scale_Dirty_CPPVector(void){
                return  false;
            }

            

            static const string Get_Tick_In_Editor_Mode_Type_Spelling(void){
                return string{"bool"};
            }

            static const string Get_Tick_In_Editor_Mode_Spelling(void){
                return string{"m_Tick_In_Editor_Mode"};
            }


            static const string Get_Tick_In_Editor_Mode_Display_Name(void){
                return string{"Tick_In_Editor_Mode"};
            }

            static const bool& Get_Tick_In_Editor_Mode_Attribute(shared_ptr<Component> Instance){
                return Instance->m_Tick_In_Editor_Mode;
            }

            static void Set_Field_Tick_In_Editor_Mode_Attribute(shared_ptr<Component> Instance, const bool& Value){
                Instance->m_Tick_In_Editor_Mode=Value;
            }

            static const bool Is_Filed_Tick_In_Editor_Mode_CPPVector(void){
                return  false;
            }

            


    };
   
}// namespace NameSpace_Function::NameSpace_Frame::NameSpace_Components

    
 

