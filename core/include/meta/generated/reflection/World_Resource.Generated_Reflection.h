#pragma once

#include<string>
#include<vector>
#include<memory>
#include<cstddef>

#include "meta/Reflection/Reflection_Instance.h"

#include "D:/Amy_Engine/resource/include/common/World_Resource.h"

namespace NameSpace_Resource::NameSpace_Common{

    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;
    using std::static_pointer_cast;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

    class Reflection_World_Resource_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"World_Resource"};
        }

        static const string Get_Displaying_Name(void){
            return string{"World_Resource"};            
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

            static const string& Get_Name_Attribute(shared_ptr<World_Resource> Instance){
                return Instance->m_Name;
            }

            static void Set_Field_Name_Attribute(shared_ptr<World_Resource> Instance, const string& Value){
                Instance->m_Name=Value;
            }

            static const bool Is_Filed_Name_CPPVector(void){
                return  false;
            }

            

            static const string Get_Default_Level_URL_Type_Spelling(void){
                return string{"path"};
            }

            static const string Get_Default_Level_URL_Spelling(void){
                return string{"m_Default_Level_URL"};
            }


            static const string Get_Default_Level_URL_Display_Name(void){
                return string{"Default_Level_URL"};
            }

            static const path& Get_Default_Level_URL_Attribute(shared_ptr<World_Resource> Instance){
                return Instance->m_Default_Level_URL;
            }

            static void Set_Field_Default_Level_URL_Attribute(shared_ptr<World_Resource> Instance, const path& Value){
                Instance->m_Default_Level_URL=Value;
            }

            static const bool Is_Filed_Default_Level_URL_CPPVector(void){
                return  false;
            }

            

            static const string Get_Levels_URL_Type_Spelling(void){
                return string{"vector<path>"};
            }

            static const string Get_Levels_URL_Spelling(void){
                return string{"m_Levels_URL"};
            }


            static const string Get_Levels_URL_Display_Name(void){
                return string{"Levels_URL"};
            }

            static const vector<path>& Get_Levels_URL_Attribute(shared_ptr<World_Resource> Instance){
                return Instance->m_Levels_URL;
            }

            static void Set_Field_Levels_URL_Attribute(shared_ptr<World_Resource> Instance, const vector<path>& Value){
                Instance->m_Levels_URL=Value;
            }

            static const bool Is_Filed_Levels_URL_CPPVector(void){
                return  !  false;
            }

                static const string Get_Levels_URL_CPPVector_Element_Type_Spelling(void){
                    return string {"path"};
                }

                static const size_t Get_Levels_URL_CPPVector_Capacity(shared_ptr<World_Resource> Instance){
                    return Instance->m_Levels_URL.capacity();
                }

                static const size_t Get_Levels_URL_CPPVector_Size(shared_ptr<World_Resource> Instance){
                    return Instance->m_Levels_URL.size();
                }

                static const path& Get_Levels_URL_CPPVector_Element(shared_ptr<World_Resource> Instance, size_t Index){
                    return Instance->m_Levels_URL[Index];
                }

                static void Set_Levels_URL_CPPVector_Element(shared_ptr<World_Resource> Instance, size_t Index, const path& Value){
                    Instance->m_Levels_URL[Index]=Value;
                }

                static void Reserve_Levels_URL_CPPVector(shared_ptr<World_Resource> Instance, size_t Capacity){
                    Instance->m_Levels_URL.reserve(Capacity);
                }

                static void Push_Back_Levels_URL_CPPVector(shared_ptr<World_Resource> Instance, const path& Value){
                    Instance->m_Levels_URL.push_back(Value);
                }


    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection

