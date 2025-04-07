#pragma once

#include<string>
#include<vector>
#include<memory>
#include<cstddef>

#include "json.h"

#include "meta/Reflection/Reflection_Instance.h"

#include "meta/Serializer/Serializer.h"

#include "D:/Amy_Engine/resource/include/components/animation/Animation.h"

namespace NameSpace_Resource::NameSpace_Components{

    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;
    using std::static_pointer_cast;

    using NameSpace_Core::NameSpace_Meta::NameSpace_Reflection::Reflection_Instance;

    class Reflection_Animation_Effect_Element_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Animation_Effect_Element"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Animation_Effect_Element"};            
        }

        

            static const string Get_Index_Type_Spelling(void){
                return string{"size_t"};
            }

            static const string Get_Index_Spelling(void){
                return string{"m_Index"};
            }


            static const string Get_Index_Display_Name(void){
                return string{"Index"};
            }

            static const size_t& Get_Index_Attribute(shared_ptr<Animation_Effect_Element> Instance){
                return Instance->m_Index;
            }

            static void Set_Field_Index_Attribute(shared_ptr<Animation_Effect_Element> Instance, const size_t& Value){
                Instance->m_Index=Value;
            }

            static const bool Is_Filed_Index_CPPVector(void){
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

            static const Affine_Transform& Get_Transform_Attribute(shared_ptr<Animation_Effect_Element> Instance){
                return Instance->m_Transform;
            }

            static void Set_Field_Transform_Attribute(shared_ptr<Animation_Effect_Element> Instance, const Affine_Transform& Value){
                Instance->m_Transform=Value;
            }

            static const bool Is_Filed_Transform_CPPVector(void){
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

    class Reflection_Animation_Effect_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Animation_Effect"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Animation_Effect"};            
        }

        

            static const string Get_Effects_Type_Spelling(void){
                return string{"vector<shared_ptr<Animation_Effect_Element>>"};
            }

            static const string Get_Effects_Spelling(void){
                return string{"m_Effects"};
            }


            static const string Get_Effects_Display_Name(void){
                return string{"Effects"};
            }

            static const vector<shared_ptr<Animation_Effect_Element>>& Get_Effects_Attribute(shared_ptr<Animation_Effect> Instance){
                return Instance->m_Effects;
            }

            static void Set_Field_Effects_Attribute(shared_ptr<Animation_Effect> Instance, const vector<shared_ptr<Animation_Effect_Element>>& Value){
                Instance->m_Effects=Value;
            }

            static const bool Is_Filed_Effects_CPPVector(void){
                return  !  false;
            }

                static const string Get_Effects_CPPVector_Element_Type_Spelling(void){
                    return string {"shared_ptr<Animation_Effect_Element>"};
                }

                static const size_t Get_Effects_CPPVector_Capacity(shared_ptr<Animation_Effect> Instance){
                    return Instance->m_Effects.capacity();
                }

                static const size_t Get_Effects_CPPVector_Size(shared_ptr<Animation_Effect> Instance){
                    return Instance->m_Effects.size();
                }

                static const shared_ptr<Animation_Effect_Element>& Get_Effects_CPPVector_Element(shared_ptr<Animation_Effect> Instance, size_t Index){
                    return Instance->m_Effects[Index];
                }

                static void Set_Effects_CPPVector_Element(shared_ptr<Animation_Effect> Instance, size_t Index, const shared_ptr<Animation_Effect_Element>& Value){
                    Instance->m_Effects[Index]=Value;
                }

                static void Reserve_Effects_CPPVector(shared_ptr<Animation_Effect> Instance, size_t Capacity){
                    Instance->m_Effects.reserve(Capacity);
                }

                static void Push_Back_Effects_CPPVector(shared_ptr<Animation_Effect> Instance, const shared_ptr<Animation_Effect_Element>& Value){
                    Instance->m_Effects.push_back(Value);
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

    class Reflection_Animation_Component_Res_Operator {
    public:
        static const string Get_Spelling(void){
            return string{"Animation_Component_Res"};
        }

        static const string Get_Displaying_Name(void){
            return string{"Animation_Component_Res"};            
        }

        

            static const string Get_Skeleton_URL_Type_Spelling(void){
                return string{"path"};
            }

            static const string Get_Skeleton_URL_Spelling(void){
                return string{"m_Skeleton_URL"};
            }


            static const string Get_Skeleton_URL_Display_Name(void){
                return string{"Skeleton_URL"};
            }

            static const path& Get_Skeleton_URL_Attribute(shared_ptr<Animation_Component_Res> Instance){
                return Instance->m_Skeleton_URL;
            }

            static void Set_Field_Skeleton_URL_Attribute(shared_ptr<Animation_Component_Res> Instance, const path& Value){
                Instance->m_Skeleton_URL=Value;
            }

            static const bool Is_Filed_Skeleton_URL_CPPVector(void){
                return  false;
            }

            

            static const string Get_Blend_State_Type_Spelling(void){
                return string{"shared_ptr<Blend_State>"};
            }

            static const string Get_Blend_State_Spelling(void){
                return string{"m_Blend_State"};
            }


            static const string Get_Blend_State_Display_Name(void){
                return string{"Blend_State"};
            }

            static const shared_ptr<Blend_State>& Get_Blend_State_Attribute(shared_ptr<Animation_Component_Res> Instance){
                return Instance->m_Blend_State;
            }

            static void Set_Field_Blend_State_Attribute(shared_ptr<Animation_Component_Res> Instance, const shared_ptr<Blend_State>& Value){
                Instance->m_Blend_State=Value;
            }

            static const bool Is_Filed_Blend_State_CPPVector(void){
                return  false;
            }

            

            static const string Get_Effect_Type_Spelling(void){
                return string{"shared_ptr<Animation_Effect>"};
            }

            static const string Get_Effect_Spelling(void){
                return string{"m_Effect"};
            }


            static const string Get_Effect_Display_Name(void){
                return string{"Effect"};
            }

            static const shared_ptr<Animation_Effect>& Get_Effect_Attribute(shared_ptr<Animation_Component_Res> Instance){
                return Instance->m_Effect;
            }

            static void Set_Field_Effect_Attribute(shared_ptr<Animation_Component_Res> Instance, const shared_ptr<Animation_Effect>& Value){
                Instance->m_Effect=Value;
            }

            static const bool Is_Filed_Effect_CPPVector(void){
                return  false;
            }

            


    };
   
}// namespace NameSpace_Resource::NameSpace_Components

    
 

