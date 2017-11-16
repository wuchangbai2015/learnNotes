#ifndef     __CONFIG_H__
#define     __CONFIG_H__


typedef unsigned char   u8;
typedef signed   char   s8;
typedef unsigned int    u16;
typedef signed   int    s16;
typedef unsigned long   u32;
typedef signed   long   s32;
typedef unsigned char   BOOL;

#ifndef TRUE
# define TRUE       1
#endif

#ifndef FALSE
# define FALSE      0
#endif

#ifndef NULL
# define NULL       0
#endif

#define Fpclk       33000000

#include <stdio.h>
#include "STC12C5A.H"
#include "lcd.h"


#endif // end of __CONFIG_H__


