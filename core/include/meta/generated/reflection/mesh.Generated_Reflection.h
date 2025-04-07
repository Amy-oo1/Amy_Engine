#pragma once

#include<string>
#include<vector>
#include<memory>
#include<cstddef>

#include "json.h"

#include "meta/Reflection/Reflection_Instance.h"

#include "meta/Serializer/Serializer.h"

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

        

            static const string Get_OBJ_URL_Type_Spelling(void){
                return string{"path"};
            }

            static const string Get_OBJ_URL_Spelling(void){
                return string{"m_OBJ_URL"};
            }


            static const string Get_OBJ_URL_Display_Name(void){
                return string{"OBJ_URL"};
            }

            static const path& Get_OBJ_URL_Attribute(shared_ptr<Mesh_Sub> Instance){
                return Instance->m_OBJ_URL;
            }

            static void Set_Field_OBJ_URL_Attribute(shared_ptr<Mesh_Sub> Instance, const path& Value){
                Instance->m_OBJ_URL=Value;
            }

            static const bool Is_Filed_OBJ_URL_CPPVector(void){
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

            

            static const string Get_Material_URL_Type_Spelling(void){
                return string{"path"};
            }

            static const string Get_Material_URL_Spelling(void){
                return string{"m_Material_URL"};
            }


            static const string Get_Material_URL_Display_Name(void){
                return string{"Material_URL"};
            }

            static const path& Get_Material_URL_Attribute(shared_ptr<Mesh_Sub> Instance){
                return Instance->m_Material_URL;
            }

            static void Set_Field_Material_URL_Attribute(shared_ptr<Mesh_Sub> Instance, const path& Value){
                Instance->m_Material_URL=Value;
            }

            static const bool Is_Filed_Material_URL_CPPVector(void){
                return  false;
            }

            


    };
   
}// namespace NameSpace_Resource::NameSpace_Components

    
 
namespace NameSpace_Resource::NameSpace_Components{

    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;
    using std::static_pointer_cast;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

    class Reflection_Mesh_Resource_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Mesh_Resource"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Mesh_Resource"};            
        }

        

            static const string Get_Sub_Meshes_Type_Spelling(void){
                return string{"vector<shared_ptr<Mesh_Sub>>"};
            }

            static const string Get_Sub_Meshes_Spelling(void){
                return string{"m_Sub_Meshes"};
            }


            static const string Get_Sub_Meshes_Display_Name(void){
                return string{"Sub_Meshes"};
            }

            static const vector<shared_ptr<Mesh_Sub>>& Get_Sub_Meshes_Attribute(shared_ptr<Mesh_Resource> Instance){
                return Instance->m_Sub_Meshes;
            }

            static void Set_Field_Sub_Meshes_Attribute(shared_ptr<Mesh_Resource> Instance, const vector<shared_ptr<Mesh_Sub>>& Value){
                Instance->m_Sub_Meshes=Value;
            }

            static const bool Is_Filed_Sub_Meshes_CPPVector(void){
                return  !  false;
            }

                static const string Get_Sub_Meshes_CPPVector_Element_Type_Spelling(void){
                    return string {"shared_ptr<Mesh_Sub>"};
                }

                static const size_t Get_Sub_Meshes_CPPVector_Capacity(shared_ptr<Mesh_Resource> Instance){
                    return Instance->m_Sub_Meshes.capacity();
                }

                static const size_t Get_Sub_Meshes_CPPVector_Size(shared_ptr<Mesh_Resource> Instance){
                    return Instance->m_Sub_Meshes.size();
                }

                static const shared_ptr<Mesh_Sub>& Get_Sub_Meshes_CPPVector_Element(shared_ptr<Mesh_Resource> Instance, size_t Index){
                    return Instance->m_Sub_Meshes[Index];
                }

                static void Set_Sub_Meshes_CPPVector_Element(shared_ptr<Mesh_Resource> Instance, size_t Index, const shared_ptr<Mesh_Sub>& Value){
                    Instance->m_Sub_Meshes[Index]=Value;
                }

                static void Reserve_Sub_Meshes_CPPVector(shared_ptr<Mesh_Resource> Instance, size_t Capacity){
                    Instance->m_Sub_Meshes.reserve(Capacity);
                }

                static void Push_Back_Sub_Meshes_CPPVector(shared_ptr<Mesh_Resource> Instance, const shared_ptr<Mesh_Sub>& Value){
                    Instance->m_Sub_Meshes.push_back(Value);
                }


    };
   
}// namespace NameSpace_Resource::NameSpace_Components

    
 

