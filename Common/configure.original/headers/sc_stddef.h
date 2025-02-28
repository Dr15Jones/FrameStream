#ifndef COMSYS_SC_STDDEF_H
#define COMSYS_SC_STDDEF_H

#if (HAVE_CONFIG_H == 1)
#include <sc_config.h>
#endif

#include <cleo3_stdtypes.h>

/* VxWorks headers */
#if defined(__vxworks)
#include <vxWorks.h>
#endif

#if (CXX_NEEDS_TYPEINFO == 1)
#if defined(GCC272)
#include <typeinfo>
#endif
#endif

/* Set exactly one of these macros to determine
 * the correct date string parsing order */
#define DATEIS_MON_DAY_YEAR
/*#define DATEIS_DAY_MON_YEAR*/

typedef int SCBoolean;

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

typedef int SCFuncReturn;

#ifndef OKAY
#define OKAY 0
#endif

#ifndef NULL
#define NULL 0
#endif

#define MAXCORBASTRING 128

#define VOIDFPTR(f)       void (*f)(void)
#define VOIDFPTR_CAST     void (*)(void)
#define VOIDFPTRVP(f)     void (*f)(void *)
#define VOIDFPTRVP_CAST   void (*)(void *)
#define INTFPTRVAR(f)     int (*f)(...)
#define INTFPTRVAR_CAST   int (*)(...)
#define VOIDPFPTRVP(f)    void*(*f)(void *)
#define VOIDPFPTRVP_CAST  void*(*)(void *)

#endif // COMSYS_SC_STDDEF_H
