#pragma once

#include<string>
#include<vector>
#include<memory>
#include<cstddef>

#include "meta/Reflection/Reflection_Instance.h"

#include "D:/Amy_Engine/resource/include/components/mesh/Mesh_Data.h"

namespace NameSpace_Resource::NameSpace_Components{

    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;
    using std::static_pointer_cast;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

    class Reflection_Mesh_Vertex_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Mesh_Vertex"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Mesh_Vertex"};            
        }

            static const vector<Reflection_Instance<Mesh_Vertex>> Get_Base_Class_Reflection_Instance_List(shared_ptr<Mesh_Vertex> Instance){
                vector<Reflection_Instance<Mesh_Vertex>> Table;

                    

                return Table;
            }

            static const string Get_Position_Type_Spelling(void){
                return string{"Vector3"};
            }

            static const string Get_Position_Spelling(void){
                return string{"m_Position"};
            }


            static const string Get_Position_Display_Name(void){
                return string{"Position"};
            }

            static const Vector3& Get_Position_Attribute(shared_ptr<Mesh_Vertex> Instance){
                return Instance->m_Position;
            }

            static void Set_Field_Position_Attribute(shared_ptr<Mesh_Vertex> Instance, const Vector3& Value){
                Instance->m_Position=Value;
            }

            static const bool Is_Filed_Position_CPPVector(void){
                return  false;
            }

            

            static const string Get_Normal_Type_Spelling(void){
                return string{"Vector3"};
            }

            static const string Get_Normal_Spelling(void){
                return string{"m_Normal"};
            }


            static const string Get_Normal_Display_Name(void){
                return string{"Normal"};
            }

            static const Vector3& Get_Normal_Attribute(shared_ptr<Mesh_Vertex> Instance){
                return Instance->m_Normal;
            }

            static void Set_Field_Normal_Attribute(shared_ptr<Mesh_Vertex> Instance, const Vector3& Value){
                Instance->m_Normal=Value;
            }

            static const bool Is_Filed_Normal_CPPVector(void){
                return  false;
            }

            

            static const string Get_Tangent_Type_Spelling(void){
                return string{"Vector3"};
            }

            static const string Get_Tangent_Spelling(void){
                return string{"m_Tangent"};
            }


            static const string Get_Tangent_Display_Name(void){
                return string{"Tangent"};
            }

            static const Vector3& Get_Tangent_Attribute(shared_ptr<Mesh_Vertex> Instance){
                return Instance->m_Tangent;
            }

            static void Set_Field_Tangent_Attribute(shared_ptr<Mesh_Vertex> Instance, const Vector3& Value){
                Instance->m_Tangent=Value;
            }

            static const bool Is_Filed_Tangent_CPPVector(void){
                return  false;
            }

            

            static const string Get_Bitangent_Type_Spelling(void){
                return string{"Vector3"};
            }

            static const string Get_Bitangent_Spelling(void){
                return string{"m_Bitangent"};
            }


            static const string Get_Bitangent_Display_Name(void){
                return string{"Bitangent"};
            }

            static const Vector3& Get_Bitangent_Attribute(shared_ptr<Mesh_Vertex> Instance){
                return Instance->m_Bitangent;
            }

            static void Set_Field_Bitangent_Attribute(shared_ptr<Mesh_Vertex> Instance, const Vector3& Value){
                Instance->m_Bitangent=Value;
            }

            static const bool Is_Filed_Bitangent_CPPVector(void){
                return  false;
            }

            

            static const string Get_Texture_Coordinate_Type_Spelling(void){
                return string{"Vector2"};
            }

            static const string Get_Texture_Coordinate_Spelling(void){
                return string{"m_Texture_Coordinate"};
            }


            static const string Get_Texture_Coordinate_Display_Name(void){
                return string{"Texture_Coordinate"};
            }

            static const Vector2& Get_Texture_Coordinate_Attribute(shared_ptr<Mesh_Vertex> Instance){
                return Instance->m_Texture_Coordinate;
            }

            static void Set_Field_Texture_Coordinate_Attribute(shared_ptr<Mesh_Vertex> Instance, const Vector2& Value){
                Instance->m_Texture_Coordinate=Value;
            }

            static const bool Is_Filed_Texture_Coordinate_CPPVector(void){
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

    class Reflection_Meah_SkeletonBinding_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Meah_SkeletonBinding"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Meah_SkeletonBinding"};            
        }

            static const vector<Reflection_Instance<Meah_SkeletonBinding>> Get_Base_Class_Reflection_Instance_List(shared_ptr<Meah_SkeletonBinding> Instance){
                vector<Reflection_Instance<Meah_SkeletonBinding>> Table;

                    

                return Table;
            }

            static const string Get_Bone_Indices_Type_Spelling(void){
                return string{"vector<int>"};
            }

            static const string Get_Bone_Indices_Spelling(void){
                return string{"m_Bone_Indices"};
            }


            static const string Get_Bone_Indices_Display_Name(void){
                return string{"Bone_Indices"};
            }

            static const vector<int>& Get_Bone_Indices_Attribute(shared_ptr<Meah_SkeletonBinding> Instance){
                return Instance->m_Bone_Indices;
            }

            static void Set_Field_Bone_Indices_Attribute(shared_ptr<Meah_SkeletonBinding> Instance, const vector<int>& Value){
                Instance->m_Bone_Indices=Value;
            }

            static const bool Is_Filed_Bone_Indices_CPPVector(void){
                return  !  false;
            }

                static const string Get_Bone_Indices_CPPVector_Element_Type_Spelling(void){
                    return string {"int"};
                }

                static const size_t Get_Bone_Indices_CPPVector_Capacity(shared_ptr<Meah_SkeletonBinding> Instance){
                    return Instance->m_Bone_Indices.capacity();
                }

                static const size_t Get_Bone_Indices_CPPVector_Size(shared_ptr<Meah_SkeletonBinding> Instance){
                    return Instance->m_Bone_Indices.size();
                }

                static const int& Get_Bone_Indices_CPPVector_Element(shared_ptr<Meah_SkeletonBinding> Instance, size_t Index){
                    return Instance->m_Bone_Indices[Index];
                }

                static void Set_Bone_Indices_CPPVector_Element(shared_ptr<Meah_SkeletonBinding> Instance, size_t Index, const int& Value){
                    Instance->m_Bone_Indices[Index]=Value;
                }

                static void Reserve_Bone_Indices_CPPVector(shared_ptr<Meah_SkeletonBinding> Instance, size_t Capacity){
                    Instance->m_Bone_Indices.reserve(Capacity);
                }

                static void Push_Back_Bone_Indices_CPPVector(shared_ptr<Meah_SkeletonBinding> Instance, const int& Value){
                    Instance->m_Bone_Indices.push_back(Value);
                }

            static const string Get_Weights_Type_Spelling(void){
                return string{"Vector4"};
            }

            static const string Get_Weights_Spelling(void){
                return string{"m_Weights"};
            }


            static const string Get_Weights_Display_Name(void){
                return string{"Weights"};
            }

            static const Vector4& Get_Weights_Attribute(shared_ptr<Meah_SkeletonBinding> Instance){
                return Instance->m_Weights;
            }

            static void Set_Field_Weights_Attribute(shared_ptr<Meah_SkeletonBinding> Instance, const Vector4& Value){
                Instance->m_Weights=Value;
            }

            static const bool Is_Filed_Weights_CPPVector(void){
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

    class Reflection_Mesh_Data_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Mesh_Data"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Mesh_Data"};            
        }

            static const vector<Reflection_Instance<Mesh_Data>> Get_Base_Class_Reflection_Instance_List(shared_ptr<Mesh_Data> Instance){
                vector<Reflection_Instance<Mesh_Data>> Table;

                    

                return Table;
            }

            static const string Get_Vertices_buffer_Type_Spelling(void){
                return string{"vector<Mesh_Vertex>"};
            }

            static const string Get_Vertices_buffer_Spelling(void){
                return string{"m_Vertices_buffer"};
            }


            static const string Get_Vertices_buffer_Display_Name(void){
                return string{"Vertices_buffer"};
            }

            static const vector<Mesh_Vertex>& Get_Vertices_buffer_Attribute(shared_ptr<Mesh_Data> Instance){
                return Instance->m_Vertices_buffer;
            }

            static void Set_Field_Vertices_buffer_Attribute(shared_ptr<Mesh_Data> Instance, const vector<Mesh_Vertex>& Value){
                Instance->m_Vertices_buffer=Value;
            }

            static const bool Is_Filed_Vertices_buffer_CPPVector(void){
                return  !  false;
            }

                static const string Get_Vertices_buffer_CPPVector_Element_Type_Spelling(void){
                    return string {"Mesh_Vertex"};
                }

                static const size_t Get_Vertices_buffer_CPPVector_Capacity(shared_ptr<Mesh_Data> Instance){
                    return Instance->m_Vertices_buffer.capacity();
                }

                static const size_t Get_Vertices_buffer_CPPVector_Size(shared_ptr<Mesh_Data> Instance){
                    return Instance->m_Vertices_buffer.size();
                }

                static const Mesh_Vertex& Get_Vertices_buffer_CPPVector_Element(shared_ptr<Mesh_Data> Instance, size_t Index){
                    return Instance->m_Vertices_buffer[Index];
                }

                static void Set_Vertices_buffer_CPPVector_Element(shared_ptr<Mesh_Data> Instance, size_t Index, const Mesh_Vertex& Value){
                    Instance->m_Vertices_buffer[Index]=Value;
                }

                static void Reserve_Vertices_buffer_CPPVector(shared_ptr<Mesh_Data> Instance, size_t Capacity){
                    Instance->m_Vertices_buffer.reserve(Capacity);
                }

                static void Push_Back_Vertices_buffer_CPPVector(shared_ptr<Mesh_Data> Instance, const Mesh_Vertex& Value){
                    Instance->m_Vertices_buffer.push_back(Value);
                }

            static const string Get_Indices_Buffer_Type_Spelling(void){
                return string{"vector<size_t>"};
            }

            static const string Get_Indices_Buffer_Spelling(void){
                return string{"m_Indices_Buffer"};
            }


            static const string Get_Indices_Buffer_Display_Name(void){
                return string{"Indices_Buffer"};
            }

            static const vector<size_t>& Get_Indices_Buffer_Attribute(shared_ptr<Mesh_Data> Instance){
                return Instance->m_Indices_Buffer;
            }

            static void Set_Field_Indices_Buffer_Attribute(shared_ptr<Mesh_Data> Instance, const vector<size_t>& Value){
                Instance->m_Indices_Buffer=Value;
            }

            static const bool Is_Filed_Indices_Buffer_CPPVector(void){
                return  !  false;
            }

                static const string Get_Indices_Buffer_CPPVector_Element_Type_Spelling(void){
                    return string {"size_t"};
                }

                static const size_t Get_Indices_Buffer_CPPVector_Capacity(shared_ptr<Mesh_Data> Instance){
                    return Instance->m_Indices_Buffer.capacity();
                }

                static const size_t Get_Indices_Buffer_CPPVector_Size(shared_ptr<Mesh_Data> Instance){
                    return Instance->m_Indices_Buffer.size();
                }

                static const size_t& Get_Indices_Buffer_CPPVector_Element(shared_ptr<Mesh_Data> Instance, size_t Index){
                    return Instance->m_Indices_Buffer[Index];
                }

                static void Set_Indices_Buffer_CPPVector_Element(shared_ptr<Mesh_Data> Instance, size_t Index, const size_t& Value){
                    Instance->m_Indices_Buffer[Index]=Value;
                }

                static void Reserve_Indices_Buffer_CPPVector(shared_ptr<Mesh_Data> Instance, size_t Capacity){
                    Instance->m_Indices_Buffer.reserve(Capacity);
                }

                static void Push_Back_Indices_Buffer_CPPVector(shared_ptr<Mesh_Data> Instance, const size_t& Value){
                    Instance->m_Indices_Buffer.push_back(Value);
                }

            static const string Get_SkeletonBindings_Type_Spelling(void){
                return string{"vector<Meah_SkeletonBinding>"};
            }

            static const string Get_SkeletonBindings_Spelling(void){
                return string{"m_SkeletonBindings"};
            }


            static const string Get_SkeletonBindings_Display_Name(void){
                return string{"SkeletonBindings"};
            }

            static const vector<Meah_SkeletonBinding>& Get_SkeletonBindings_Attribute(shared_ptr<Mesh_Data> Instance){
                return Instance->m_SkeletonBindings;
            }

            static void Set_Field_SkeletonBindings_Attribute(shared_ptr<Mesh_Data> Instance, const vector<Meah_SkeletonBinding>& Value){
                Instance->m_SkeletonBindings=Value;
            }

            static const bool Is_Filed_SkeletonBindings_CPPVector(void){
                return  !  false;
            }

                static const string Get_SkeletonBindings_CPPVector_Element_Type_Spelling(void){
                    return string {"Meah_SkeletonBinding"};
                }

                static const size_t Get_SkeletonBindings_CPPVector_Capacity(shared_ptr<Mesh_Data> Instance){
                    return Instance->m_SkeletonBindings.capacity();
                }

                static const size_t Get_SkeletonBindings_CPPVector_Size(shared_ptr<Mesh_Data> Instance){
                    return Instance->m_SkeletonBindings.size();
                }

                static const Meah_SkeletonBinding& Get_SkeletonBindings_CPPVector_Element(shared_ptr<Mesh_Data> Instance, size_t Index){
                    return Instance->m_SkeletonBindings[Index];
                }

                static void Set_SkeletonBindings_CPPVector_Element(shared_ptr<Mesh_Data> Instance, size_t Index, const Meah_SkeletonBinding& Value){
                    Instance->m_SkeletonBindings[Index]=Value;
                }

                static void Reserve_SkeletonBindings_CPPVector(shared_ptr<Mesh_Data> Instance, size_t Capacity){
                    Instance->m_SkeletonBindings.reserve(Capacity);
                }

                static void Push_Back_SkeletonBindings_CPPVector(shared_ptr<Mesh_Data> Instance, const Meah_SkeletonBinding& Value){
                    Instance->m_SkeletonBindings.push_back(Value);
                }


    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection

