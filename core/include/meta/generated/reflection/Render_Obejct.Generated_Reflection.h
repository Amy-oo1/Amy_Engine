#pragma once

#include<string>
#include<vector>
#include<memory>
#include<cstddef>

#include "meta/Reflection/Reflection_Instance.h"

#include "D:/Amy_Engine/function/include/render/render_system/Render_Obejct.h"

namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System{

    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;
    using std::static_pointer_cast;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

    class Reflection_Game_Object_Mesh_Desc_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Game_Object_Mesh_Desc"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Game_Object_Mesh_Desc"};            
        }

        

            static const string Get_Mesh_URL_Type_Spelling(void){
                return string{"path"};
            }

            static const string Get_Mesh_URL_Spelling(void){
                return string{"m_Mesh_URL"};
            }


            static const string Get_Mesh_URL_Display_Name(void){
                return string{"Mesh_URL"};
            }

            static const path& Get_Mesh_URL_Attribute(shared_ptr<Game_Object_Mesh_Desc> Instance){
                return Instance->m_Mesh_URL;
            }

            static void Set_Field_Mesh_URL_Attribute(shared_ptr<Game_Object_Mesh_Desc> Instance, const path& Value){
                Instance->m_Mesh_URL=Value;
            }

            static const bool Is_Filed_Mesh_URL_CPPVector(void){
                return  false;
            }

            


    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection
namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System{

    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;
    using std::static_pointer_cast;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

    class Reflection_Skeleton_Binding_Desc_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Skeleton_Binding_Desc"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Skeleton_Binding_Desc"};            
        }

        

            static const string Get_Skeleton_Binding_URL_Type_Spelling(void){
                return string{"path"};
            }

            static const string Get_Skeleton_Binding_URL_Spelling(void){
                return string{"m_Skeleton_Binding_URL"};
            }


            static const string Get_Skeleton_Binding_URL_Display_Name(void){
                return string{"Skeleton_Binding_URL"};
            }

            static const path& Get_Skeleton_Binding_URL_Attribute(shared_ptr<Skeleton_Binding_Desc> Instance){
                return Instance->m_Skeleton_Binding_URL;
            }

            static void Set_Field_Skeleton_Binding_URL_Attribute(shared_ptr<Skeleton_Binding_Desc> Instance, const path& Value){
                Instance->m_Skeleton_Binding_URL=Value;
            }

            static const bool Is_Filed_Skeleton_Binding_URL_CPPVector(void){
                return  false;
            }

            


    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection
namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System{

    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;
    using std::static_pointer_cast;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

    class Reflection_Skeleton_Animation_Result_Transform_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Skeleton_Animation_Result_Transform"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Skeleton_Animation_Result_Transform"};            
        }

        

            static const string Get_Matrix_Type_Spelling(void){
                return string{"Matrix4x4"};
            }

            static const string Get_Matrix_Spelling(void){
                return string{"m_Matrix"};
            }


            static const string Get_Matrix_Display_Name(void){
                return string{"Matrix"};
            }

            static const Matrix4x4& Get_Matrix_Attribute(shared_ptr<Skeleton_Animation_Result_Transform> Instance){
                return Instance->m_Matrix;
            }

            static void Set_Field_Matrix_Attribute(shared_ptr<Skeleton_Animation_Result_Transform> Instance, const Matrix4x4& Value){
                Instance->m_Matrix=Value;
            }

            static const bool Is_Filed_Matrix_CPPVector(void){
                return  false;
            }

            


    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection
namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System{

    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;
    using std::static_pointer_cast;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

    class Reflection_Skeleton_Animation_Result_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Skeleton_Animation_Result"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Skeleton_Animation_Result"};            
        }

        

            static const string Get_Transforms_Type_Spelling(void){
                return string{"vector<shared_ptr<Skeleton_Animation_Result_Transform>>"};
            }

            static const string Get_Transforms_Spelling(void){
                return string{"m_Transforms"};
            }


            static const string Get_Transforms_Display_Name(void){
                return string{"Transforms"};
            }

            static const vector<shared_ptr<Skeleton_Animation_Result_Transform>>& Get_Transforms_Attribute(shared_ptr<Skeleton_Animation_Result> Instance){
                return Instance->m_Transforms;
            }

            static void Set_Field_Transforms_Attribute(shared_ptr<Skeleton_Animation_Result> Instance, const vector<shared_ptr<Skeleton_Animation_Result_Transform>>& Value){
                Instance->m_Transforms=Value;
            }

            static const bool Is_Filed_Transforms_CPPVector(void){
                return  !  false;
            }

                static const string Get_Transforms_CPPVector_Element_Type_Spelling(void){
                    return string {"shared_ptr<Skeleton_Animation_Result_Transform>"};
                }

                static const size_t Get_Transforms_CPPVector_Capacity(shared_ptr<Skeleton_Animation_Result> Instance){
                    return Instance->m_Transforms.capacity();
                }

                static const size_t Get_Transforms_CPPVector_Size(shared_ptr<Skeleton_Animation_Result> Instance){
                    return Instance->m_Transforms.size();
                }

                static const shared_ptr<Skeleton_Animation_Result_Transform>& Get_Transforms_CPPVector_Element(shared_ptr<Skeleton_Animation_Result> Instance, size_t Index){
                    return Instance->m_Transforms[Index];
                }

                static void Set_Transforms_CPPVector_Element(shared_ptr<Skeleton_Animation_Result> Instance, size_t Index, const shared_ptr<Skeleton_Animation_Result_Transform>& Value){
                    Instance->m_Transforms[Index]=Value;
                }

                static void Reserve_Transforms_CPPVector(shared_ptr<Skeleton_Animation_Result> Instance, size_t Capacity){
                    Instance->m_Transforms.reserve(Capacity);
                }

                static void Push_Back_Transforms_CPPVector(shared_ptr<Skeleton_Animation_Result> Instance, const shared_ptr<Skeleton_Animation_Result_Transform>& Value){
                    Instance->m_Transforms.push_back(Value);
                }


    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection
namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System{

    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;
    using std::static_pointer_cast;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

    class Reflection_Game_Object_Material_Desc_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Game_Object_Material_Desc"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Game_Object_Material_Desc"};            
        }

        

            static const string Get_Base_Color_URL_Type_Spelling(void){
                return string{"path"};
            }

            static const string Get_Base_Color_URL_Spelling(void){
                return string{"m_Base_Color_URL"};
            }


            static const string Get_Base_Color_URL_Display_Name(void){
                return string{"Base_Color_URL"};
            }

            static const path& Get_Base_Color_URL_Attribute(shared_ptr<Game_Object_Material_Desc> Instance){
                return Instance->m_Base_Color_URL;
            }

            static void Set_Field_Base_Color_URL_Attribute(shared_ptr<Game_Object_Material_Desc> Instance, const path& Value){
                Instance->m_Base_Color_URL=Value;
            }

            static const bool Is_Filed_Base_Color_URL_CPPVector(void){
                return  false;
            }

            

            static const string Get_Metallic_Roughness_URL_Type_Spelling(void){
                return string{"path"};
            }

            static const string Get_Metallic_Roughness_URL_Spelling(void){
                return string{"m_Metallic_Roughness_URL"};
            }


            static const string Get_Metallic_Roughness_URL_Display_Name(void){
                return string{"Metallic_Roughness_URL"};
            }

            static const path& Get_Metallic_Roughness_URL_Attribute(shared_ptr<Game_Object_Material_Desc> Instance){
                return Instance->m_Metallic_Roughness_URL;
            }

            static void Set_Field_Metallic_Roughness_URL_Attribute(shared_ptr<Game_Object_Material_Desc> Instance, const path& Value){
                Instance->m_Metallic_Roughness_URL=Value;
            }

            static const bool Is_Filed_Metallic_Roughness_URL_CPPVector(void){
                return  false;
            }

            

            static const string Get_Normal_URL_Type_Spelling(void){
                return string{"path"};
            }

            static const string Get_Normal_URL_Spelling(void){
                return string{"m_Normal_URL"};
            }


            static const string Get_Normal_URL_Display_Name(void){
                return string{"Normal_URL"};
            }

            static const path& Get_Normal_URL_Attribute(shared_ptr<Game_Object_Material_Desc> Instance){
                return Instance->m_Normal_URL;
            }

            static void Set_Field_Normal_URL_Attribute(shared_ptr<Game_Object_Material_Desc> Instance, const path& Value){
                Instance->m_Normal_URL=Value;
            }

            static const bool Is_Filed_Normal_URL_CPPVector(void){
                return  false;
            }

            

            static const string Get_Occlusion_URL_Type_Spelling(void){
                return string{"path"};
            }

            static const string Get_Occlusion_URL_Spelling(void){
                return string{"m_Occlusion_URL"};
            }


            static const string Get_Occlusion_URL_Display_Name(void){
                return string{"Occlusion_URL"};
            }

            static const path& Get_Occlusion_URL_Attribute(shared_ptr<Game_Object_Material_Desc> Instance){
                return Instance->m_Occlusion_URL;
            }

            static void Set_Field_Occlusion_URL_Attribute(shared_ptr<Game_Object_Material_Desc> Instance, const path& Value){
                Instance->m_Occlusion_URL=Value;
            }

            static const bool Is_Filed_Occlusion_URL_CPPVector(void){
                return  false;
            }

            

            static const string Get_Emissive_URL_Type_Spelling(void){
                return string{"path"};
            }

            static const string Get_Emissive_URL_Spelling(void){
                return string{"m_Emissive_URL"};
            }


            static const string Get_Emissive_URL_Display_Name(void){
                return string{"Emissive_URL"};
            }

            static const path& Get_Emissive_URL_Attribute(shared_ptr<Game_Object_Material_Desc> Instance){
                return Instance->m_Emissive_URL;
            }

            static void Set_Field_Emissive_URL_Attribute(shared_ptr<Game_Object_Material_Desc> Instance, const path& Value){
                Instance->m_Emissive_URL=Value;
            }

            static const bool Is_Filed_Emissive_URL_CPPVector(void){
                return  false;
            }

            

            static const string Get_Is_With_Texture_Type_Spelling(void){
                return string{"bool"};
            }

            static const string Get_Is_With_Texture_Spelling(void){
                return string{"m_Is_With_Texture"};
            }


            static const string Get_Is_With_Texture_Display_Name(void){
                return string{"Is_With_Texture"};
            }

            static const bool& Get_Is_With_Texture_Attribute(shared_ptr<Game_Object_Material_Desc> Instance){
                return Instance->m_Is_With_Texture;
            }

            static void Set_Field_Is_With_Texture_Attribute(shared_ptr<Game_Object_Material_Desc> Instance, const bool& Value){
                Instance->m_Is_With_Texture=Value;
            }

            static const bool Is_Filed_Is_With_Texture_CPPVector(void){
                return  false;
            }

            


    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection
namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System{

    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;
    using std::static_pointer_cast;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

    class Reflection_Game_Object_Transform_Desc_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Game_Object_Transform_Desc"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Game_Object_Transform_Desc"};            
        }

        

            static const string Get_Transform_Type_Spelling(void){
                return string{"Matrix4x4"};
            }

            static const string Get_Transform_Spelling(void){
                return string{"m_Transform"};
            }


            static const string Get_Transform_Display_Name(void){
                return string{"Transform"};
            }

            static const Matrix4x4& Get_Transform_Attribute(shared_ptr<Game_Object_Transform_Desc> Instance){
                return Instance->m_Transform;
            }

            static void Set_Field_Transform_Attribute(shared_ptr<Game_Object_Transform_Desc> Instance, const Matrix4x4& Value){
                Instance->m_Transform=Value;
            }

            static const bool Is_Filed_Transform_CPPVector(void){
                return  false;
            }

            


    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection
namespace NameSpace_Function::NameSpace_Render::NameSpace_Render_System{

    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;
    using std::static_pointer_cast;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

    class Reflection_Game_Object_Part_Desc_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Game_Object_Part_Desc"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Game_Object_Part_Desc"};            
        }

        

            static const string Get_Mesh_Desc_Type_Spelling(void){
                return string{"shared_ptr<Game_Object_Mesh_Desc>"};
            }

            static const string Get_Mesh_Desc_Spelling(void){
                return string{"m_Mesh_Desc"};
            }


            static const string Get_Mesh_Desc_Display_Name(void){
                return string{"Mesh_Desc"};
            }

            static const shared_ptr<Game_Object_Mesh_Desc>& Get_Mesh_Desc_Attribute(shared_ptr<Game_Object_Part_Desc> Instance){
                return Instance->m_Mesh_Desc;
            }

            static void Set_Field_Mesh_Desc_Attribute(shared_ptr<Game_Object_Part_Desc> Instance, const shared_ptr<Game_Object_Mesh_Desc>& Value){
                Instance->m_Mesh_Desc=Value;
            }

            static const bool Is_Filed_Mesh_Desc_CPPVector(void){
                return  false;
            }

            

            static const string Get_Material_Desc_Type_Spelling(void){
                return string{"shared_ptr<Game_Object_Material_Desc>"};
            }

            static const string Get_Material_Desc_Spelling(void){
                return string{"m_Material_Desc"};
            }


            static const string Get_Material_Desc_Display_Name(void){
                return string{"Material_Desc"};
            }

            static const shared_ptr<Game_Object_Material_Desc>& Get_Material_Desc_Attribute(shared_ptr<Game_Object_Part_Desc> Instance){
                return Instance->m_Material_Desc;
            }

            static void Set_Field_Material_Desc_Attribute(shared_ptr<Game_Object_Part_Desc> Instance, const shared_ptr<Game_Object_Material_Desc>& Value){
                Instance->m_Material_Desc=Value;
            }

            static const bool Is_Filed_Material_Desc_CPPVector(void){
                return  false;
            }

            

            static const string Get_Transform_Desc_Type_Spelling(void){
                return string{"shared_ptr<Game_Object_Transform_Desc>"};
            }

            static const string Get_Transform_Desc_Spelling(void){
                return string{"m_Transform_Desc"};
            }


            static const string Get_Transform_Desc_Display_Name(void){
                return string{"Transform_Desc"};
            }

            static const shared_ptr<Game_Object_Transform_Desc>& Get_Transform_Desc_Attribute(shared_ptr<Game_Object_Part_Desc> Instance){
                return Instance->m_Transform_Desc;
            }

            static void Set_Field_Transform_Desc_Attribute(shared_ptr<Game_Object_Part_Desc> Instance, const shared_ptr<Game_Object_Transform_Desc>& Value){
                Instance->m_Transform_Desc=Value;
            }

            static const bool Is_Filed_Transform_Desc_CPPVector(void){
                return  false;
            }

            

            static const string Get_Skeleton_Binding_Desc_Type_Spelling(void){
                return string{"shared_ptr<Skeleton_Binding_Desc>"};
            }

            static const string Get_Skeleton_Binding_Desc_Spelling(void){
                return string{"m_Skeleton_Binding_Desc"};
            }


            static const string Get_Skeleton_Binding_Desc_Display_Name(void){
                return string{"Skeleton_Binding_Desc"};
            }

            static const shared_ptr<Skeleton_Binding_Desc>& Get_Skeleton_Binding_Desc_Attribute(shared_ptr<Game_Object_Part_Desc> Instance){
                return Instance->m_Skeleton_Binding_Desc;
            }

            static void Set_Field_Skeleton_Binding_Desc_Attribute(shared_ptr<Game_Object_Part_Desc> Instance, const shared_ptr<Skeleton_Binding_Desc>& Value){
                Instance->m_Skeleton_Binding_Desc=Value;
            }

            static const bool Is_Filed_Skeleton_Binding_Desc_CPPVector(void){
                return  false;
            }

            

            static const string Get_Skeleton_Animation_Result_Type_Spelling(void){
                return string{"shared_ptr<Skeleton_Animation_Result>"};
            }

            static const string Get_Skeleton_Animation_Result_Spelling(void){
                return string{"m_Skeleton_Animation_Result"};
            }


            static const string Get_Skeleton_Animation_Result_Display_Name(void){
                return string{"Skeleton_Animation_Result"};
            }

            static const shared_ptr<Skeleton_Animation_Result>& Get_Skeleton_Animation_Result_Attribute(shared_ptr<Game_Object_Part_Desc> Instance){
                return Instance->m_Skeleton_Animation_Result;
            }

            static void Set_Field_Skeleton_Animation_Result_Attribute(shared_ptr<Game_Object_Part_Desc> Instance, const shared_ptr<Skeleton_Animation_Result>& Value){
                Instance->m_Skeleton_Animation_Result=Value;
            }

            static const bool Is_Filed_Skeleton_Animation_Result_CPPVector(void){
                return  false;
            }

            

            static const string Get_Is_With_Skeleton_Type_Spelling(void){
                return string{"bool"};
            }

            static const string Get_Is_With_Skeleton_Spelling(void){
                return string{"m_Is_With_Skeleton"};
            }


            static const string Get_Is_With_Skeleton_Display_Name(void){
                return string{"Is_With_Skeleton"};
            }

            static const bool& Get_Is_With_Skeleton_Attribute(shared_ptr<Game_Object_Part_Desc> Instance){
                return Instance->m_Is_With_Skeleton;
            }

            static void Set_Field_Is_With_Skeleton_Attribute(shared_ptr<Game_Object_Part_Desc> Instance, const bool& Value){
                Instance->m_Is_With_Skeleton=Value;
            }

            static const bool Is_Filed_Is_With_Skeleton_CPPVector(void){
                return  false;
            }

            


    };
   
}// NameSpace_Core::NameSpace_Meta::NameSpace_Generated::NameSpace_Reflection

