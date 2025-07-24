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

#include <cstdint>
typedef uint8_t   UInt8;
typedef int8_t     Int8;

typedef uint16_t  UInt16;
typedef int16_t    Int16;

typedef uint32_t     UInt32;
typedef int32_t       Int32;

typedef uint64_t    UInt64;
typedef int64_t      Int64;

#endif /* COMMON_CLEO3_STDTYPES */

