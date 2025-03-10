#pragma once

#include<string>
#include<vector>
#include<memory>
#include<cstddef>

#include "meta/Reflection/Reflection_Instance.h"
#include "meta/Reflection/Reflection_Register.h"

#include "D:/Amy_Engine/resource/include/common/Object.h"

namespace NameSpace_Resource::NameSpace_Common{

    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;
    using std::static_pointer_cast;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Class_Func_Tuple;
    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Class_Base_Class_Tuple;
    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Class_Field_Func_Tuple;
    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Class_Filed_CPPVector_Func_Tuple;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Register;


    class Reflection_Component_Definition_Operator {
    public:

        static const string Get_Class_Component_Definition_Spelling(void){
            return string{"Component_Definition"};
        }

        static const string Get_Class_Displaying_Name(void){
            return string{"Component_Definition"};            
        }

            static const vector<Reflection_Instance<void>> Get_Base_Class_Component_Definition_Reflection_Instance_List(shared_ptr<void> Instance){
                vector<Reflection_Instance<void>> Table;

                    

                return Table;
            }

            static const string Get_Field_Component_Type_Spelling(void){
                return string{"string"};
            }

            static const string Get_Field_Component_Spelling(void){
                return string{"m_Component"};
            }


            static const string Get_Field_Component_Display_Name(void){
                return string{"Component"};
            }

            static const void *const Get_Filed_Component_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Component_Definition>(Instance)->m_Component);
            }

            static void Set_Field_Component_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Component_Definition>(Instance)->m_Component=*static_cast<const string*>(Value);
            }

            static const bool Is_Filed_Component_CPPVector(void){
                return  false;
            }

            


            static void TypeWrapper_Rigster(void){
                shared_ptr<Class_Func_Tuple> Temp_Class_Func_Tuple{nullptr};
                shared_ptr<Class_Base_Class_Tuple> Temp_Class_Base_Class_Tuple{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Field_Func_Tuple>>> Temp_Class_Field_Func_Tuple_Map{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Filed_CPPVector_Func_Tuple>>> Temp_Class_Filed_CPPVector_Func_Tuple_Map{nullptr};

                Temp_Class_Func_Tuple = make_shared<Class_Func_Tuple>(
                    Reflection_Component_Definition_Operator::Get_Class_Component_Definition_Spelling,
                    Reflection_Component_Definition_Operator::Get_Class_Displaying_Name
                );

                Temp_Class_Base_Class_Tuple = make_shared<Class_Base_Class_Tuple>(
                    Reflection_Component_Definition_Operator::Get_Base_Class_Component_Definition_Reflection_Instance_List
                );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Component"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Component_Definition_Operator::Get_Field_Component_Type_Spelling,
                        Reflection_Component_Definition_Operator::Get_Field_Component_Spelling,
                        Reflection_Component_Definition_Operator::Get_Field_Component_Display_Name,
                        Reflection_Component_Definition_Operator::Get_Filed_Component_Attribute,
                        Reflection_Component_Definition_Operator::Set_Field_Component_Attribute,
                        Reflection_Component_Definition_Operator::Is_Filed_Component_CPPVector
                    )
                );

                

                
            Reflection_Register::Get_Instance().Register_Class(string{"Component_Definition"},Temp_Class_Func_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Base_Class(string{"Component_Definition"},Temp_Class_Base_Class_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Filed(string{"Component_Definition"},Temp_Class_Field_Func_Tuple_Map);
            Reflection_Register::Get_Instance().Register_Class_Field_CPPVector(string{"Component_Definition"},Temp_Class_Filed_CPPVector_Func_Tuple_Map);
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

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Class_Func_Tuple;
    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Class_Base_Class_Tuple;
    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Class_Field_Func_Tuple;
    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Class_Filed_CPPVector_Func_Tuple;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Register;


    class Reflection_Object_Definition_Operator {
    public:

        static const string Get_Class_Object_Definition_Spelling(void){
            return string{"Object_Definition"};
        }

        static const string Get_Class_Displaying_Name(void){
            return string{"Object_Definition"};            
        }

            static const vector<Reflection_Instance<void>> Get_Base_Class_Object_Definition_Reflection_Instance_List(shared_ptr<void> Instance){
                vector<Reflection_Instance<void>> Table;

                    

                return Table;
            }

            static const string Get_Field_Components_Type_Spelling(void){
                return string{"vector<Reflection_Instance<Component>>"};
            }

            static const string Get_Field_Components_Spelling(void){
                return string{"m_Components"};
            }


            static const string Get_Field_Components_Display_Name(void){
                return string{"Components"};
            }

            static const void *const Get_Filed_Components_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Object_Definition>(Instance)->m_Components);
            }

            static void Set_Field_Components_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Object_Definition>(Instance)->m_Components=*static_cast<const vector<Reflection_Instance<Component>>*>(Value);
            }

            static const bool Is_Filed_Components_CPPVector(void){
                return  !  false;
            }

                static const string Get_Field_Components_CPPVector_Element_Type_Spelling(void){
                    return string {"m_Components"};
                }

                static const size_t Get_Field_Components_CPPVector_Capacity(shared_ptr<void> Instance){
                    return static_pointer_cast<Object_Definition>(Instance)->m_Components.capacity();
                }

                static const size_t Get_Field_Components_CPPVector_Size(shared_ptr<void> Instance){
                    return static_pointer_cast<Object_Definition>(Instance)->m_Components.size();
                }

                static const void *Get_Field_Components_CPPVector_Element(shared_ptr<void> Instance, size_t Index){
                    return static_cast<const void*>(&static_pointer_cast<Object_Definition>(Instance)->m_Components[Index]);
                }

                static void Set_Field_Components_CPPVector_Element(shared_ptr<void> Instance, size_t Index,const void* Value){
                    static_pointer_cast<Object_Definition>(Instance)->m_Components[Index]=*static_cast<const Reflection_Instance<Component>*>(Value);
                }


            static void TypeWrapper_Rigster(void){
                shared_ptr<Class_Func_Tuple> Temp_Class_Func_Tuple{nullptr};
                shared_ptr<Class_Base_Class_Tuple> Temp_Class_Base_Class_Tuple{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Field_Func_Tuple>>> Temp_Class_Field_Func_Tuple_Map{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Filed_CPPVector_Func_Tuple>>> Temp_Class_Filed_CPPVector_Func_Tuple_Map{nullptr};

                Temp_Class_Func_Tuple = make_shared<Class_Func_Tuple>(
                    Reflection_Object_Definition_Operator::Get_Class_Object_Definition_Spelling,
                    Reflection_Object_Definition_Operator::Get_Class_Displaying_Name
                );

                Temp_Class_Base_Class_Tuple = make_shared<Class_Base_Class_Tuple>(
                    Reflection_Object_Definition_Operator::Get_Base_Class_Object_Definition_Reflection_Instance_List
                );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Components"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Object_Definition_Operator::Get_Field_Components_Type_Spelling,
                        Reflection_Object_Definition_Operator::Get_Field_Components_Spelling,
                        Reflection_Object_Definition_Operator::Get_Field_Components_Display_Name,
                        Reflection_Object_Definition_Operator::Get_Filed_Components_Attribute,
                        Reflection_Object_Definition_Operator::Set_Field_Components_Attribute,
                        Reflection_Object_Definition_Operator::Is_Filed_Components_CPPVector
                    )
                );

                    Temp_Class_Filed_CPPVector_Func_Tuple_Map->emplace(
                    string{"m_Components"},
                        make_shared<Class_Filed_CPPVector_Func_Tuple>( 
                            Reflection_Object_Definition_Operator::Get_Field_Components_CPPVector_Element_Type_Spelling,
                            Reflection_Object_Definition_Operator::Get_Field_Components_CPPVector_Capacity,
                            Reflection_Object_Definition_Operator::Get_Field_Components_CPPVector_Size,
                            Reflection_Object_Definition_Operator::Get_Field_Components_CPPVector_Element,
                            Reflection_Object_Definition_Operator::Set_Field_Components_CPPVector_Element
                        )
                    );

                
            Reflection_Register::Get_Instance().Register_Class(string{"Object_Definition"},Temp_Class_Func_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Base_Class(string{"Object_Definition"},Temp_Class_Base_Class_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Filed(string{"Object_Definition"},Temp_Class_Field_Func_Tuple_Map);
            Reflection_Register::Get_Instance().Register_Class_Field_CPPVector(string{"Object_Definition"},Temp_Class_Filed_CPPVector_Func_Tuple_Map);
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

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Class_Func_Tuple;
    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Class_Base_Class_Tuple;
    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Class_Field_Func_Tuple;
    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Class_Filed_CPPVector_Func_Tuple;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Register;


    class Reflection_Object_Instance_Operator {
    public:

        static const string Get_Class_Object_Instance_Spelling(void){
            return string{"Object_Instance"};
        }

        static const string Get_Class_Displaying_Name(void){
            return string{"Object_Instance"};            
        }

            static const vector<Reflection_Instance<void>> Get_Base_Class_Object_Instance_Reflection_Instance_List(shared_ptr<void> Instance){
                vector<Reflection_Instance<void>> Table;

                    

                return Table;
            }

            static const string Get_Field_Instanced_Components_Type_Spelling(void){
                return string{"std::vector<Reflection_Instance<Component>>"};
            }

            static const string Get_Field_Instanced_Components_Spelling(void){
                return string{"m_Instanced_Components"};
            }


            static const string Get_Field_Instanced_Components_Display_Name(void){
                return string{"Instanced_Components"};
            }

            static const void *const Get_Filed_Instanced_Components_Attribute(shared_ptr<void> Instance){
                return static_cast<void*>(&static_pointer_cast<Object_Instance>(Instance)->m_Instanced_Components);
            }

            static void Set_Field_Instanced_Components_Attribute(shared_ptr<void> Instance, const void * Value){
                static_pointer_cast<Object_Instance>(Instance)->m_Instanced_Components=*static_cast<const std::vector<Reflection_Instance<Component>>*>(Value);
            }

            static const bool Is_Filed_Instanced_Components_CPPVector(void){
                return  !  false;
            }

                static const string Get_Field_Instanced_Components_CPPVector_Element_Type_Spelling(void){
                    return string {"m_Instanced_Components"};
                }

                static const size_t Get_Field_Instanced_Components_CPPVector_Capacity(shared_ptr<void> Instance){
                    return static_pointer_cast<Object_Instance>(Instance)->m_Instanced_Components.capacity();
                }

                static const size_t Get_Field_Instanced_Components_CPPVector_Size(shared_ptr<void> Instance){
                    return static_pointer_cast<Object_Instance>(Instance)->m_Instanced_Components.size();
                }

                static const void *Get_Field_Instanced_Components_CPPVector_Element(shared_ptr<void> Instance, size_t Index){
                    return static_cast<const void*>(&static_pointer_cast<Object_Instance>(Instance)->m_Instanced_Components[Index]);
                }

                static void Set_Field_Instanced_Components_CPPVector_Element(shared_ptr<void> Instance, size_t Index,const void* Value){
                    static_pointer_cast<Object_Instance>(Instance)->m_Instanced_Components[Index]=*static_cast<const Reflection_Instance<Component>*>(Value);
                }


            static void TypeWrapper_Rigster(void){
                shared_ptr<Class_Func_Tuple> Temp_Class_Func_Tuple{nullptr};
                shared_ptr<Class_Base_Class_Tuple> Temp_Class_Base_Class_Tuple{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Field_Func_Tuple>>> Temp_Class_Field_Func_Tuple_Map{nullptr};
                shared_ptr<std::unordered_map<string, shared_ptr<Class_Filed_CPPVector_Func_Tuple>>> Temp_Class_Filed_CPPVector_Func_Tuple_Map{nullptr};

                Temp_Class_Func_Tuple = make_shared<Class_Func_Tuple>(
                    Reflection_Object_Instance_Operator::Get_Class_Object_Instance_Spelling,
                    Reflection_Object_Instance_Operator::Get_Class_Displaying_Name
                );

                Temp_Class_Base_Class_Tuple = make_shared<Class_Base_Class_Tuple>(
                    Reflection_Object_Instance_Operator::Get_Base_Class_Object_Instance_Reflection_Instance_List
                );

                    Temp_Class_Field_Func_Tuple_Map->emplace(
                    string{"m_Instanced_Components"},
                    make_shared<Class_Field_Func_Tuple>(
                        Reflection_Object_Instance_Operator::Get_Field_Instanced_Components_Type_Spelling,
                        Reflection_Object_Instance_Operator::Get_Field_Instanced_Components_Spelling,
                        Reflection_Object_Instance_Operator::Get_Field_Instanced_Components_Display_Name,
                        Reflection_Object_Instance_Operator::Get_Filed_Instanced_Components_Attribute,
                        Reflection_Object_Instance_Operator::Set_Field_Instanced_Components_Attribute,
                        Reflection_Object_Instance_Operator::Is_Filed_Instanced_Components_CPPVector
                    )
                );

                    Temp_Class_Filed_CPPVector_Func_Tuple_Map->emplace(
                    string{"m_Instanced_Components"},
                        make_shared<Class_Filed_CPPVector_Func_Tuple>( 
                            Reflection_Object_Instance_Operator::Get_Field_Instanced_Components_CPPVector_Element_Type_Spelling,
                            Reflection_Object_Instance_Operator::Get_Field_Instanced_Components_CPPVector_Capacity,
                            Reflection_Object_Instance_Operator::Get_Field_Instanced_Components_CPPVector_Size,
                            Reflection_Object_Instance_Operator::Get_Field_Instanced_Components_CPPVector_Element,
                            Reflection_Object_Instance_Operator::Set_Field_Instanced_Components_CPPVector_Element
                        )
                    );

                
            Reflection_Register::Get_Instance().Register_Class(string{"Object_Instance"},Temp_Class_Func_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Base_Class(string{"Object_Instance"},Temp_Class_Base_Class_Tuple);
            Reflection_Register::Get_Instance().Register_Class_Filed(string{"Object_Instance"},Temp_Class_Field_Func_Tuple_Map);
            Reflection_Register::Get_Instance().Register_Class_Field_CPPVector(string{"Object_Instance"},Temp_Class_Filed_CPPVector_Func_Tuple_Map);
        }

    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection


