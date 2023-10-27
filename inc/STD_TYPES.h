#ifndef STD_TYPES_H
#define STD_TYPES_H

typedef unsigned char       u8;
typedef signed char         s8;
typedef unsigned short int u16;
typedef signed short int   s16;
typedef unsigned long int  u32;
typedef signed long int    s32;
typedef float              f32;
typedef double             f64;
typedef long double        f128;
typedef void(*fptr_irq_t)(void);

#define TRUE                    1
#define FALSE                   0

#define STD_TYPES_OK            1
#define STD_TYPES_NOK           0

#define MAX_U64					9223372036854775807
#define MAX_U32					4294967295
#define MAX_U16					65535
#define MAX_U8					255

#define NULL                   ((void*)0)

#endif
