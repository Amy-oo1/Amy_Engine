#pragma once

#define REFLECTION_HEADER(Class_Name) 				class Reflection_##Class_Name##_Operator;

#if defined(__REFLECTION_PARSER__)
#define REFLECTION_CLASS(Class_Name , ...)			class __attribute__((annotate(#__VA_ARGS__))) Class_Name
#define REFLECTION_STRUCT(Struct_Name, ...)			struct __attribute__((annotate(#__VA_ARGS__))) Struct_Name
#define META(...)									__attribute__((annotate(#__VA_ARGS__)))
#else
#define REFLECTION_CLASS(Class_Name, ...)			class Class_Name 
#define REFLECTION_STRUCT(Struct_Name, ...)			struct Struct_Name 
#define META(...)									
#endif // __REFLECTION_PARSER__

#define REFLECTION_BODY(Class_Name)					friend class Reflection_##Class_Name##_Operator; friend  NameSpace_Core::NameSpace_Meta::NameSpace_Serializer::Serializer;

namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer {
	class Serializer;
}// namespace NameSpace_Core::NameSpace_Meta::NameSpace_Serializer