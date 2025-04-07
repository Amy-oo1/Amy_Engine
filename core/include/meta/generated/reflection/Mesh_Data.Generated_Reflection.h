#pragma once

#include<string>
#include<vector>
#include<memory>
#include<cstddef>

#include "json.h"

#include "meta/Reflection/Reflection_Instance.h"

#include "meta/Serializer/Serializer.h"

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

            

            static const string Get_Texture_Coordinates_Type_Spelling(void){
                return string{"Vector2"};
            }

            static const string Get_Texture_Coordinates_Spelling(void){
                return string{"m_Texture_Coordinates"};
            }


            static const string Get_Texture_Coordinates_Display_Name(void){
                return string{"Texture_Coordinates"};
            }

            static const Vector2& Get_Texture_Coordinates_Attribute(shared_ptr<Mesh_Vertex> Instance){
                return Instance->m_Texture_Coordinates;
            }

            static void Set_Field_Texture_Coordinates_Attribute(shared_ptr<Mesh_Vertex> Instance, const Vector2& Value){
                Instance->m_Texture_Coordinates=Value;
            }

            static const bool Is_Filed_Texture_Coordinates_CPPVector(void){
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

    class Reflection_Meah_Skeleton_Binding_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Meah_Skeleton_Binding"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Meah_Skeleton_Binding"};            
        }

        

            static const string Get_Index_0_Type_Spelling(void){
                return string{"size_t"};
            }

            static const string Get_Index_0_Spelling(void){
                return string{"m_Index_0"};
            }


            static const string Get_Index_0_Display_Name(void){
                return string{"Index_0"};
            }

            static const size_t& Get_Index_0_Attribute(shared_ptr<Meah_Skeleton_Binding> Instance){
                return Instance->m_Index_0;
            }

            static void Set_Field_Index_0_Attribute(shared_ptr<Meah_Skeleton_Binding> Instance, const size_t& Value){
                Instance->m_Index_0=Value;
            }

            static const bool Is_Filed_Index_0_CPPVector(void){
                return  false;
            }

            

            static const string Get_Index_1_Type_Spelling(void){
                return string{"size_t"};
            }

            static const string Get_Index_1_Spelling(void){
                return string{"m_Index_1"};
            }


            static const string Get_Index_1_Display_Name(void){
                return string{"Index_1"};
            }

            static const size_t& Get_Index_1_Attribute(shared_ptr<Meah_Skeleton_Binding> Instance){
                return Instance->m_Index_1;
            }

            static void Set_Field_Index_1_Attribute(shared_ptr<Meah_Skeleton_Binding> Instance, const size_t& Value){
                Instance->m_Index_1=Value;
            }

            static const bool Is_Filed_Index_1_CPPVector(void){
                return  false;
            }

            

            static const string Get_Index_2_Type_Spelling(void){
                return string{"size_t"};
            }

            static const string Get_Index_2_Spelling(void){
                return string{"m_Index_2"};
            }


            static const string Get_Index_2_Display_Name(void){
                return string{"Index_2"};
            }

            static const size_t& Get_Index_2_Attribute(shared_ptr<Meah_Skeleton_Binding> Instance){
                return Instance->m_Index_2;
            }

            static void Set_Field_Index_2_Attribute(shared_ptr<Meah_Skeleton_Binding> Instance, const size_t& Value){
                Instance->m_Index_2=Value;
            }

            static const bool Is_Filed_Index_2_CPPVector(void){
                return  false;
            }

            

            static const string Get_Index_3_Type_Spelling(void){
                return string{"size_t"};
            }

            static const string Get_Index_3_Spelling(void){
                return string{"m_Index_3"};
            }


            static const string Get_Index_3_Display_Name(void){
                return string{"Index_3"};
            }

            static const size_t& Get_Index_3_Attribute(shared_ptr<Meah_Skeleton_Binding> Instance){
                return Instance->m_Index_3;
            }

            static void Set_Field_Index_3_Attribute(shared_ptr<Meah_Skeleton_Binding> Instance, const size_t& Value){
                Instance->m_Index_3=Value;
            }

            static const bool Is_Filed_Index_3_CPPVector(void){
                return  false;
            }

            

            static const string Get_Weight_0_Type_Spelling(void){
                return string{"float"};
            }

            static const string Get_Weight_0_Spelling(void){
                return string{"m_Weight_0"};
            }


            static const string Get_Weight_0_Display_Name(void){
                return string{"Weight_0"};
            }

            static const float& Get_Weight_0_Attribute(shared_ptr<Meah_Skeleton_Binding> Instance){
                return Instance->m_Weight_0;
            }

            static void Set_Field_Weight_0_Attribute(shared_ptr<Meah_Skeleton_Binding> Instance, const float& Value){
                Instance->m_Weight_0=Value;
            }

            static const bool Is_Filed_Weight_0_CPPVector(void){
                return  false;
            }

            

            static const string Get_Weight_1_Type_Spelling(void){
                return string{"float"};
            }

            static const string Get_Weight_1_Spelling(void){
                return string{"m_Weight_1"};
            }


            static const string Get_Weight_1_Display_Name(void){
                return string{"Weight_1"};
            }

            static const float& Get_Weight_1_Attribute(shared_ptr<Meah_Skeleton_Binding> Instance){
                return Instance->m_Weight_1;
            }

            static void Set_Field_Weight_1_Attribute(shared_ptr<Meah_Skeleton_Binding> Instance, const float& Value){
                Instance->m_Weight_1=Value;
            }

            static const bool Is_Filed_Weight_1_CPPVector(void){
                return  false;
            }

            

            static const string Get_Weight_2_Type_Spelling(void){
                return string{"float"};
            }

            static const string Get_Weight_2_Spelling(void){
                return string{"m_Weight_2"};
            }


            static const string Get_Weight_2_Display_Name(void){
                return string{"Weight_2"};
            }

            static const float& Get_Weight_2_Attribute(shared_ptr<Meah_Skeleton_Binding> Instance){
                return Instance->m_Weight_2;
            }

            static void Set_Field_Weight_2_Attribute(shared_ptr<Meah_Skeleton_Binding> Instance, const float& Value){
                Instance->m_Weight_2=Value;
            }

            static const bool Is_Filed_Weight_2_CPPVector(void){
                return  false;
            }

            

            static const string Get_Weight_3_Type_Spelling(void){
                return string{"float"};
            }

            static const string Get_Weight_3_Spelling(void){
                return string{"m_Weight_3"};
            }


            static const string Get_Weight_3_Display_Name(void){
                return string{"Weight_3"};
            }

            static const float& Get_Weight_3_Attribute(shared_ptr<Meah_Skeleton_Binding> Instance){
                return Instance->m_Weight_3;
            }

            static void Set_Field_Weight_3_Attribute(shared_ptr<Meah_Skeleton_Binding> Instance, const float& Value){
                Instance->m_Weight_3=Value;
            }

            static const bool Is_Filed_Weight_3_CPPVector(void){
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

    class Reflection_Mesh_Data_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Mesh_Data"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Mesh_Data"};            
        }

        

            static const string Get_Vertices_Buffer_Type_Spelling(void){
                return string{"vector<shared_ptr<Mesh_Vertex>>"};
            }

            static const string Get_Vertices_Buffer_Spelling(void){
                return string{"m_Vertices_Buffer"};
            }


            static const string Get_Vertices_Buffer_Display_Name(void){
                return string{"Vertices_Buffer"};
            }

            static const vector<shared_ptr<Mesh_Vertex>>& Get_Vertices_Buffer_Attribute(shared_ptr<Mesh_Data> Instance){
                return Instance->m_Vertices_Buffer;
            }

            static void Set_Field_Vertices_Buffer_Attribute(shared_ptr<Mesh_Data> Instance, const vector<shared_ptr<Mesh_Vertex>>& Value){
                Instance->m_Vertices_Buffer=Value;
            }

            static const bool Is_Filed_Vertices_Buffer_CPPVector(void){
                return  !  false;
            }

                static const string Get_Vertices_Buffer_CPPVector_Element_Type_Spelling(void){
                    return string {"shared_ptr<Mesh_Vertex>"};
                }

                static const size_t Get_Vertices_Buffer_CPPVector_Capacity(shared_ptr<Mesh_Data> Instance){
                    return Instance->m_Vertices_Buffer.capacity();
                }

                static const size_t Get_Vertices_Buffer_CPPVector_Size(shared_ptr<Mesh_Data> Instance){
                    return Instance->m_Vertices_Buffer.size();
                }

                static const shared_ptr<Mesh_Vertex>& Get_Vertices_Buffer_CPPVector_Element(shared_ptr<Mesh_Data> Instance, size_t Index){
                    return Instance->m_Vertices_Buffer[Index];
                }

                static void Set_Vertices_Buffer_CPPVector_Element(shared_ptr<Mesh_Data> Instance, size_t Index, const shared_ptr<Mesh_Vertex>& Value){
                    Instance->m_Vertices_Buffer[Index]=Value;
                }

                static void Reserve_Vertices_Buffer_CPPVector(shared_ptr<Mesh_Data> Instance, size_t Capacity){
                    Instance->m_Vertices_Buffer.reserve(Capacity);
                }

                static void Push_Back_Vertices_Buffer_CPPVector(shared_ptr<Mesh_Data> Instance, const shared_ptr<Mesh_Vertex>& Value){
                    Instance->m_Vertices_Buffer.push_back(Value);
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

            static const string Get_Skeleton_Bindings_Type_Spelling(void){
                return string{"vector<shared_ptr<Meah_Skeleton_Binding>>"};
            }

            static const string Get_Skeleton_Bindings_Spelling(void){
                return string{"m_Skeleton_Bindings"};
            }


            static const string Get_Skeleton_Bindings_Display_Name(void){
                return string{"Skeleton_Bindings"};
            }

            static const vector<shared_ptr<Meah_Skeleton_Binding>>& Get_Skeleton_Bindings_Attribute(shared_ptr<Mesh_Data> Instance){
                return Instance->m_Skeleton_Bindings;
            }

            static void Set_Field_Skeleton_Bindings_Attribute(shared_ptr<Mesh_Data> Instance, const vector<shared_ptr<Meah_Skeleton_Binding>>& Value){
                Instance->m_Skeleton_Bindings=Value;
            }

            static const bool Is_Filed_Skeleton_Bindings_CPPVector(void){
                return  !  false;
            }

                static const string Get_Skeleton_Bindings_CPPVector_Element_Type_Spelling(void){
                    return string {"shared_ptr<Meah_Skeleton_Binding>"};
                }

                static const size_t Get_Skeleton_Bindings_CPPVector_Capacity(shared_ptr<Mesh_Data> Instance){
                    return Instance->m_Skeleton_Bindings.capacity();
                }

                static const size_t Get_Skeleton_Bindings_CPPVector_Size(shared_ptr<Mesh_Data> Instance){
                    return Instance->m_Skeleton_Bindings.size();
                }

                static const shared_ptr<Meah_Skeleton_Binding>& Get_Skeleton_Bindings_CPPVector_Element(shared_ptr<Mesh_Data> Instance, size_t Index){
                    return Instance->m_Skeleton_Bindings[Index];
                }

                static void Set_Skeleton_Bindings_CPPVector_Element(shared_ptr<Mesh_Data> Instance, size_t Index, const shared_ptr<Meah_Skeleton_Binding>& Value){
                    Instance->m_Skeleton_Bindings[Index]=Value;
                }

                static void Reserve_Skeleton_Bindings_CPPVector(shared_ptr<Mesh_Data> Instance, size_t Capacity){
                    Instance->m_Skeleton_Bindings.reserve(Capacity);
                }

                static void Push_Back_Skeleton_Bindings_CPPVector(shared_ptr<Mesh_Data> Instance, const shared_ptr<Meah_Skeleton_Binding>& Value){
                    Instance->m_Skeleton_Bindings.push_back(Value);
                }


    };
   
}// namespace NameSpace_Resource::NameSpace_Components

    
 

