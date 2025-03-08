#pragma once

#define REFLECTION_HEADER(Class_Name)				class Reflection_##Class_Name##_Operator;

#if defined(__REFLECTION_PARSER__)
#define REFLECTION_CLASS(Class_Name , ...)			class __attribute__((annotate(#__VA_ARGS__))) Class_Name
#define REFLECTION_STRUCT(Struct_Name, ...)			struct __attribute__((annotate(#__VA_ARGS__))) Struct_Name
#else
#define REFLECTION_CLASS(Class_Name, ...)			class Class_Name 
#define REFLECTION_STRUCT(Struct_Name, ...)			struct Struct_Name 
#endif // __REFLECTION_PARSER__

#define REFLECTION_BODY(Class_Name)					friend class Reflection_##Class_Name##_Operator;
