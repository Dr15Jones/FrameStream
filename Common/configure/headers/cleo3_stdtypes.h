#ifndef COMMON_CLEO3_STDTYPES
#define COMMON_CLEO3_STDTYPES
/* This is a pure C file. Do not add C++ things in here! */

/**************************************************/
/*                                                */
/* CLEO3 standard sized types with 8, 16 or       */
/* 32 bits. Both signed and unsigned              */
/*                                                */
/*****/
/*                                                */
/* NOTE: You must have included the header file   */
/*       that is generated per platform to make   */
/*       this work correctly!                     */
/* Lesson: Do *not* include this file directly!   */
/*       ALWAYS use cleo3_stddef.h or sc_stddef.h */
/*****/
/* $Id: cleo3_stdtypes.h,v 1.4 2001/07/19 23:25:07 hubert Exp $ */
/*                                                */
/* Author: Andreas H. Wolf, Cornell               */
/* Created: 02-27-99
 * $Log: cleo3_stdtypes.h,v $
 * Revision 1.4  2001/07/19 23:25:07  hubert
 * Taken out nested comments
 *               
 * Revision 1.3  1999/04/05 15:02:07  hubert
 * Adapted from online for cygwin
 *
 * Revision 1.3  1999/03/12 00:44:10  ahw
 * Added NT special 64bit
 *
 * Revision 1.2  1999/03/02 02:34:49  ahw
 * Do not define Int64 for VxWorks
 *
 * Revision 1.1  1999/03/02 01:57:58  ahw
 * Temporarily borrowed from Common area
 *
**
***************************************************/

/* typedef UINTXX if possible */
#if (HAVE_STANDARD_SIZES == 1)
/* simple cases that must be ok */
#if (SIZEOF_UNSIGNED_CHAR == 1)
typedef unsigned char   UInt8;
typedef signed char     Int8;
#else
#error "Can not find type matching (U)Int8!"
#endif

#if (SIZEOF_UNSIGNED_SHORT == 2)
typedef unsigned short  UInt16;
typedef signed short    Int16;
#else
#error "Can not find type matching (U)Int16!"
#endif

/* We must be careful here */
#if (SIZEOF_UNSIGNED_INT == 4)
typedef unsigned int     UInt32;
typedef signed int       Int32;
#elif  (SIZEOF_UNSIGNED_LONG == 4)
typedef unsigned long    UInt32;
typedef signed long      Int32;
#else
#error "Can not find type matching (U)Int32!"
#endif

/* Another tricky thing */
#if defined(_WIN32)
/* Special NT type... Bill, why are you doing this? */
typedef unsigned __int64 UInt64;
typedef __int64          Int64;
#else /* _WIN32 */
#if (SIZEOF_UNSIGNED_LONG == 8)
typedef unsigned long    UInt64;
typedef signed long      Int64;
#elif  (SIZEOF_UNSIGNED_LONG_LONG == 8)
typedef unsigned long long   UInt64;
typedef signed long long     Int64;
#else

#if !defined(__vxworks)
#error "Can not find type matching (U)Int64!"
#endif /* __vxworks */
#endif /* SIZEOF */
#endif /* NOT _WIN32 */

#endif /* HAVE_STANDARD_SIZES */

#endif /* COMMON_CLEO3_STDTYPES */

