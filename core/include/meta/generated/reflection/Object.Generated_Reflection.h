#pragma once

#include<string>
#include<vector>
#include<memory>
#include<cstddef>

#include "meta/Reflection/Reflection_Instance.h"

#include "D:/Amy_Engine/resource/include/common/Object.h"

namespace NameSpace_Resource::NameSpace_Common{

    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;
    using std::static_pointer_cast;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

    class Reflection_Component_Definition_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Component_Definition"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Component_Definition"};            
        }

            static const vector<Reflection_Instance<Component_Definition>> Get_Base_Class_Reflection_Instance_List(shared_ptr<Component_Definition> Instance){
                vector<Reflection_Instance<Component_Definition>> Table;

                    

                return Table;
            }

            static const string Get_Type_Name_Type_Spelling(void){
                return string{"string"};
            }

            static const string Get_Type_Name_Spelling(void){
                return string{"m_Type_Name"};
            }


            static const string Get_Type_Name_Display_Name(void){
                return string{"Type_Name"};
            }

            static const string& Get_Type_Name_Attribute(shared_ptr<Component_Definition> Instance){
                return Instance->m_Type_Name;
            }

            static void Set_Field_Type_Name_Attribute(shared_ptr<Component_Definition> Instance, const string& Value){
                Instance->m_Type_Name=Value;
            }

            static const bool Is_Filed_Type_Name_CPPVector(void){
                return  false;
            }

            

            static const string Get_Component_Type_Spelling(void){
                return string{"string"};
            }

            static const string Get_Component_Spelling(void){
                return string{"m_Component"};
            }


            static const string Get_Component_Display_Name(void){
                return string{"Component"};
            }

            static const string& Get_Component_Attribute(shared_ptr<Component_Definition> Instance){
                return Instance->m_Component;
            }

            static void Set_Field_Component_Attribute(shared_ptr<Component_Definition> Instance, const string& Value){
                Instance->m_Component=Value;
            }

            static const bool Is_Filed_Component_CPPVector(void){
                return  false;
            }

            


    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection
namespace NameSpace_Resource::NameSpace_Common{

    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;
    using std::static_pointer_cast;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

    class Reflection_Object_Definition_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Object_Definition"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Object_Definition"};            
        }

            static const vector<Reflection_Instance<Object_Definition>> Get_Base_Class_Reflection_Instance_List(shared_ptr<Object_Definition> Instance){
                vector<Reflection_Instance<Object_Definition>> Table;

                    

                return Table;
            }

            static const string Get_Seplling_Type_Spelling(void){
                return string{"string"};
            }

            static const string Get_Seplling_Spelling(void){
                return string{"m_Seplling"};
            }


            static const string Get_Seplling_Display_Name(void){
                return string{"Seplling"};
            }

            static const string& Get_Seplling_Attribute(shared_ptr<Object_Definition> Instance){
                return Instance->m_Seplling;
            }

            static void Set_Field_Seplling_Attribute(shared_ptr<Object_Definition> Instance, const string& Value){
                Instance->m_Seplling=Value;
            }

            static const bool Is_Filed_Seplling_CPPVector(void){
                return  false;
            }

            

            static const string Get_Components_Type_Spelling(void){
                return string{"vector<Reflection_Instance<Component>>"};
            }

            static const string Get_Components_Spelling(void){
                return string{"m_Components"};
            }


            static const string Get_Components_Display_Name(void){
                return string{"Components"};
            }

            static const vector<Reflection_Instance<Component>>& Get_Components_Attribute(shared_ptr<Object_Definition> Instance){
                return Instance->m_Components;
            }

            static void Set_Field_Components_Attribute(shared_ptr<Object_Definition> Instance, const vector<Reflection_Instance<Component>>& Value){
                Instance->m_Components=Value;
            }

            static const bool Is_Filed_Components_CPPVector(void){
                return  !  false;
            }

                static const string Get_Components_CPPVector_Element_Type_Spelling(void){
                    return string {"Reflection_Instance<Component>"};
                }

                static const size_t Get_Components_CPPVector_Capacity(shared_ptr<Object_Definition> Instance){
                    return Instance->m_Components.capacity();
                }

                static const size_t Get_Components_CPPVector_Size(shared_ptr<Object_Definition> Instance){
                    return Instance->m_Components.size();
                }

                static const Reflection_Instance<Component>& Get_Components_CPPVector_Element(shared_ptr<Object_Definition> Instance, size_t Index){
                    return Instance->m_Components[Index];
                }

                static void Set_Components_CPPVector_Element(shared_ptr<Object_Definition> Instance, size_t Index, const Reflection_Instance<Component>& Value){
                    Instance->m_Components[Index]=Value;
                }

                static void Reserve_Components_CPPVector(shared_ptr<Object_Definition> Instance, size_t Capacity){
                    Instance->m_Components.reserve(Capacity);
                }

                static void Push_Back_Components_CPPVector(shared_ptr<Object_Definition> Instance, const Reflection_Instance<Component>& Value){
                    Instance->m_Components.push_back(Value);
                }


    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection
namespace NameSpace_Resource::NameSpace_Common{

    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;
    using std::static_pointer_cast;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

    class Reflection_Object_Instance_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Object_Instance"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Object_Instance"};            
        }

            static const vector<Reflection_Instance<Object_Instance>> Get_Base_Class_Reflection_Instance_List(shared_ptr<Object_Instance> Instance){
                vector<Reflection_Instance<Object_Instance>> Table;

                    

                return Table;
            }

            static const string Get_Name_Type_Spelling(void){
                return string{"std::string"};
            }

            static const string Get_Name_Spelling(void){
                return string{"m_Name"};
            }


            static const string Get_Name_Display_Name(void){
                return string{"Name"};
            }

            static const std::string& Get_Name_Attribute(shared_ptr<Object_Instance> Instance){
                return Instance->m_Name;
            }

            static void Set_Field_Name_Attribute(shared_ptr<Object_Instance> Instance, const std::string& Value){
                Instance->m_Name=Value;
            }

            static const bool Is_Filed_Name_CPPVector(void){
                return  false;
            }

            

            static const string Get_Definition_Type_Spelling(void){
                return string{"std::string"};
            }

            static const string Get_Definition_Spelling(void){
                return string{"m_Definition"};
            }


            static const string Get_Definition_Display_Name(void){
                return string{"Definition"};
            }

            static const std::string& Get_Definition_Attribute(shared_ptr<Object_Instance> Instance){
                return Instance->m_Definition;
            }

            static void Set_Field_Definition_Attribute(shared_ptr<Object_Instance> Instance, const std::string& Value){
                Instance->m_Definition=Value;
            }

            static const bool Is_Filed_Definition_CPPVector(void){
                return  false;
            }

            

            static const string Get_Instanced_Components_Type_Spelling(void){
                return string{"std::vector<Reflection_Instance<Component>>"};
            }

            static const string Get_Instanced_Components_Spelling(void){
                return string{"m_Instanced_Components"};
            }


            static const string Get_Instanced_Components_Display_Name(void){
                return string{"Instanced_Components"};
            }

            static const std::vector<Reflection_Instance<Component>>& Get_Instanced_Components_Attribute(shared_ptr<Object_Instance> Instance){
                return Instance->m_Instanced_Components;
            }

            static void Set_Field_Instanced_Components_Attribute(shared_ptr<Object_Instance> Instance, const std::vector<Reflection_Instance<Component>>& Value){
                Instance->m_Instanced_Components=Value;
            }

            static const bool Is_Filed_Instanced_Components_CPPVector(void){
                return  !  false;
            }

                static const string Get_Instanced_Components_CPPVector_Element_Type_Spelling(void){
                    return string {"Reflection_Instance<Component>"};
                }

                static const size_t Get_Instanced_Components_CPPVector_Capacity(shared_ptr<Object_Instance> Instance){
                    return Instance->m_Instanced_Components.capacity();
                }

                static const size_t Get_Instanced_Components_CPPVector_Size(shared_ptr<Object_Instance> Instance){
                    return Instance->m_Instanced_Components.size();
                }

                static const Reflection_Instance<Component>& Get_Instanced_Components_CPPVector_Element(shared_ptr<Object_Instance> Instance, size_t Index){
                    return Instance->m_Instanced_Components[Index];
                }

                static void Set_Instanced_Components_CPPVector_Element(shared_ptr<Object_Instance> Instance, size_t Index, const Reflection_Instance<Component>& Value){
                    Instance->m_Instanced_Components[Index]=Value;
                }

                static void Reserve_Instanced_Components_CPPVector(shared_ptr<Object_Instance> Instance, size_t Capacity){
                    Instance->m_Instanced_Components.reserve(Capacity);
                }

                static void Push_Back_Instanced_Components_CPPVector(shared_ptr<Object_Instance> Instance, const Reflection_Instance<Component>& Value){
                    Instance->m_Instanced_Components.push_back(Value);
                }


    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection

