#if !defined(STLUTILITY_FWD_VECTOR_H)
#define STLUTILITY_FWD_VECTOR_H
// -*- C++ -*-
//
// Package:     STLUtility
// Module:      fwd_vector
// 
// Description: Handle the forward declaration of the STL vector
//
// Usage:
//    include this file wherever you'd normally forward declare a STL vector
//
// Author:      Simon Patton
// Created:     Thu Jul  3 14:44:35 EDT 1997
// $Id: fwd_vector.h,v 1.5 2000/12/02 20:10:02 cdj Exp $
//
// Revision history
//
// $Log: fwd_vector.h,v $
// Revision 1.5  2000/12/02 20:10:02  cdj
// made C++ standards compliant (no longer forward declare items in std namespace)
//
// Revision 1.4  1998/07/02 22:14:40  cdj
// added "using namespace std" when using namespaces (needed by cxx 6.0)
//
// Revision 1.3  1998/06/21 23:11:55  cdj
// added NO_STD_NAMESPACE_BUG and bug flags needed for cxx 6.0
//
// Revision 1.2  1998/04/09 23:20:35  cleo3
// port to egcs
//
// Revision 1.1.1.1  1998/02/02 23:25:35  sjp
// New package for files that help STL usage
//
// Revision 1.10  1998/01/07 22:36:56  sjp
// Corrected position in file of ALL cpp macros
//
// Revision 1.9  1998/01/06 21:22:16  sjp
// Added STL_ALLOCATORS_NOT_TEMPLATE option and macros
//
// Revision 1.8  1997/09/04 16:05:34  sjp
// fixed problem with "undef"
//
// Revision 1.7  1997/09/03 20:05:44  sjp
// Uses CPP macros for STL containers
//
// Revision 1.6  1997/08/27 03:38:44  sjp
// Updated to new name for bug flags
//
// Revision 1.5  1997/08/14 11:42:20  sjp
// Mods to run under CW Pro 1
//
// Revision 1.4  1997/08/06 14:10:51  sjp
// Updated the bug flags
//
// Revision 1.3  1997/07/28 16:34:12  sjp
// Fixed to work under cxx 5.6
//
// Revision 1.2  1997/07/18 16:59:50  sjp
// Changed to handle auto-instantiation in cxx
//
// Revision 1.1  1997/07/09 17:41:46  sjp
// New file for STL forward declaration
//

//
// Set up pre-processor macros
//

#if !defined(STL_ALLOCATOR)

#if defined(STL_ALLOCATORS_NOT_TEMPLATED)
#  define STL_ALLOCATOR( c ) allocator
#else
#  define STL_ALLOCATOR( c ) allocator< c >
#endif /* STL_ALLOCATORS_NOT_TEMPLATED) */

#endif /* STL_ALLOCATOR */

#if !defined(STL_VECTOR)
#  define STL_VECTOR( c ) vector< c >
#  define STL_VECTOR_ALLOC( c , a ) vector< c , a >

#if defined(NO_ALLOCATOR_IN_STL_DECLARATION_BUG)
#  undef STL_VECTOR_ALLOC
#else

#if (defined(NO_DEFAULT_ALLOCATOR_IN_STL_BUG) || defined(NO_DEFAULT_PARAMETERS_FOR_TEMPLATES_BUG))
#  undef STL_VECTOR
#  define STL_VECTOR( c ) vector< c , allocator< c > >
#endif /* NO_DEFAULT_ALLOCATOR_IN_STL_BUG || NO_DEFAULT_PARAMETERS_FOR_TEMPLATES_BUG */

#endif /* NO_ALLOCATOR_IN_STL_DECLARATION_BUG */

#endif /* STL_VECTOR */

#include <vector>

#ifndef NO_STD_NAMESPACE_BUG
using namespace std;
#endif // NO_STD_NAMESPACE_BUG

#endif /* STLUTILITY_FWD_VECTOR_H */
