#pragma once

#include<string>
#include<vector>
#include<memory>
#include<cstddef>

#include "meta/Reflection/Reflection_Instance.h"

#include "D:/Amy_Engine/resource/include/common/Level.h"

namespace NameSpace_Resource::NameSpace_Common{

    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;
    using std::static_pointer_cast;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

    class Reflection_Level_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Level"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Level"};            
        }

            static const vector<Reflection_Instance<Level>> Get_Base_Class_Reflection_Instance_List(shared_ptr<Level> Instance){
                vector<Reflection_Instance<Level>> Table;

                    

                return Table;
            }

            static const string Get_Gravity_Type_Spelling(void){
                return string{"Vector3"};
            }

            static const string Get_Gravity_Spelling(void){
                return string{"m_Gravity"};
            }


            static const string Get_Gravity_Display_Name(void){
                return string{"Gravity"};
            }

            static const Vector3& Get_Gravity_Attribute(shared_ptr<Level> Instance){
                return Instance->m_Gravity;
            }

            static void Set_Field_Gravity_Attribute(shared_ptr<Level> Instance, const Vector3& Value){
                Instance->m_Gravity=Value;
            }

            static const bool Is_Filed_Gravity_CPPVector(void){
                return  false;
            }

            

            static const string Get_Character_Name_Type_Spelling(void){
                return string{"string"};
            }

            static const string Get_Character_Name_Spelling(void){
                return string{"m_Character_Name"};
            }


            static const string Get_Character_Name_Display_Name(void){
                return string{"Character_Name"};
            }

            static const string& Get_Character_Name_Attribute(shared_ptr<Level> Instance){
                return Instance->m_Character_Name;
            }

            static void Set_Field_Character_Name_Attribute(shared_ptr<Level> Instance, const string& Value){
                Instance->m_Character_Name=Value;
            }

            static const bool Is_Filed_Character_Name_CPPVector(void){
                return  false;
            }

            

            static const string Get_Objects_Type_Spelling(void){
                return string{"vector<Object_Instance>"};
            }

            static const string Get_Objects_Spelling(void){
                return string{"m_Objects"};
            }


            static const string Get_Objects_Display_Name(void){
                return string{"Objects"};
            }

            static const vector<Object_Instance>& Get_Objects_Attribute(shared_ptr<Level> Instance){
                return Instance->m_Objects;
            }

            static void Set_Field_Objects_Attribute(shared_ptr<Level> Instance, const vector<Object_Instance>& Value){
                Instance->m_Objects=Value;
            }

            static const bool Is_Filed_Objects_CPPVector(void){
                return  !  false;
            }

                static const string Get_Objects_CPPVector_Element_Type_Spelling(void){
                    return string {"Object_Instance"};
                }

                static const size_t Get_Objects_CPPVector_Capacity(shared_ptr<Level> Instance){
                    return Instance->m_Objects.capacity();
                }

                static const size_t Get_Objects_CPPVector_Size(shared_ptr<Level> Instance){
                    return Instance->m_Objects.size();
                }

                static const Object_Instance& Get_Objects_CPPVector_Element(shared_ptr<Level> Instance, size_t Index){
                    return Instance->m_Objects[Index];
                }

                static void Set_Objects_CPPVector_Element(shared_ptr<Level> Instance, size_t Index, const Object_Instance& Value){
                    Instance->m_Objects[Index]=Value;
                }

                static void Reserve_Objects_CPPVector(shared_ptr<Level> Instance, size_t Capacity){
                    Instance->m_Objects.reserve(Capacity);
                }

                static void Push_Back_Objects_CPPVector(shared_ptr<Level> Instance, const Object_Instance& Value){
                    Instance->m_Objects.push_back(Value);
                }


    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection

