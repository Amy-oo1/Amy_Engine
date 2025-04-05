#pragma once

#include<string>
#include<vector>
#include<memory>
#include<cstddef>

#include "meta/Reflection/Reflection_Instance.h"

#include "D:/Amy_Engine/resource/include/components/mesh/Mesh.h"

namespace NameSpace_Resource::NameSpace_Components{

    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;
    using std::static_pointer_cast;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

    class Reflection_Mesh_Sub_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Mesh_Sub"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Mesh_Sub"};            
        }

        

            static const string Get_Object_Path_Type_Spelling(void){
                return string{"path"};
            }

            static const string Get_Object_Path_Spelling(void){
                return string{"m_Object_Path"};
            }


            static const string Get_Object_Path_Display_Name(void){
                return string{"Object_Path"};
            }

            static const path& Get_Object_Path_Attribute(shared_ptr<Mesh_Sub> Instance){
                return Instance->m_Object_Path;
            }

            static void Set_Field_Object_Path_Attribute(shared_ptr<Mesh_Sub> Instance, const path& Value){
                Instance->m_Object_Path=Value;
            }

            static const bool Is_Filed_Object_Path_CPPVector(void){
                return  false;
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

            static const Affine_Transform& Get_Transform_Attribute(shared_ptr<Mesh_Sub> Instance){
                return Instance->m_Transform;
            }

            static void Set_Field_Transform_Attribute(shared_ptr<Mesh_Sub> Instance, const Affine_Transform& Value){
                Instance->m_Transform=Value;
            }

            static const bool Is_Filed_Transform_CPPVector(void){
                return  false;
            }

            

            static const string Get_Material_Type_Spelling(void){
                return string{"string"};
            }

            static const string Get_Material_Spelling(void){
                return string{"m_Material"};
            }


            static const string Get_Material_Display_Name(void){
                return string{"Material"};
            }

            static const string& Get_Material_Attribute(shared_ptr<Mesh_Sub> Instance){
                return Instance->m_Material;
            }

            static void Set_Field_Material_Attribute(shared_ptr<Mesh_Sub> Instance, const string& Value){
                Instance->m_Material=Value;
            }

            static const bool Is_Filed_Material_CPPVector(void){
                return  false;
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

    class Reflection_Mesh_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Mesh"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Mesh"};            
        }

        

            static const string Get_Meshes_Type_Spelling(void){
                return string{"vector<shared_ptr<Mesh_Sub>>"};
            }

            static const string Get_Meshes_Spelling(void){
                return string{"m_Meshes"};
            }


            static const string Get_Meshes_Display_Name(void){
                return string{"Meshes"};
            }

            static const vector<shared_ptr<Mesh_Sub>>& Get_Meshes_Attribute(shared_ptr<Mesh> Instance){
                return Instance->m_Meshes;
            }

            static void Set_Field_Meshes_Attribute(shared_ptr<Mesh> Instance, const vector<shared_ptr<Mesh_Sub>>& Value){
                Instance->m_Meshes=Value;
            }

            static const bool Is_Filed_Meshes_CPPVector(void){
                return  !  false;
            }

                static const string Get_Meshes_CPPVector_Element_Type_Spelling(void){
                    return string {"shared_ptr<Mesh_Sub>"};
                }

                static const size_t Get_Meshes_CPPVector_Capacity(shared_ptr<Mesh> Instance){
                    return Instance->m_Meshes.capacity();
                }

                static const size_t Get_Meshes_CPPVector_Size(shared_ptr<Mesh> Instance){
                    return Instance->m_Meshes.size();
                }

                static const shared_ptr<Mesh_Sub>& Get_Meshes_CPPVector_Element(shared_ptr<Mesh> Instance, size_t Index){
                    return Instance->m_Meshes[Index];
                }

                static void Set_Meshes_CPPVector_Element(shared_ptr<Mesh> Instance, size_t Index, const shared_ptr<Mesh_Sub>& Value){
                    Instance->m_Meshes[Index]=Value;
                }

                static void Reserve_Meshes_CPPVector(shared_ptr<Mesh> Instance, size_t Capacity){
                    Instance->m_Meshes.reserve(Capacity);
                }

                static void Push_Back_Meshes_CPPVector(shared_ptr<Mesh> Instance, const shared_ptr<Mesh_Sub>& Value){
                    Instance->m_Meshes.push_back(Value);
                }


    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection

