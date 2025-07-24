#if !defined(STLUTILITY_FWD_MAP_H)
#define STLUTILITY_FWD_MAP_H
// -*- C++ -*-
//
// Package:     STLUtility
// Module:      fwd_map
// 
// Description: Handle the forward declaration of the STL map
//
// Usage:
//    include this file wherever you'd normally forward declare a STL map
//
// Author:      Simon Patton
// Created:     Thu Jul  3 14:44:35 EDT 1997
// $Id: fwd_map.h,v 1.7 2000/12/02 20:10:01 cdj Exp $
//
// Revision history
//
// $Log: fwd_map.h,v $
// Revision 1.7  2000/12/02 20:10:01  cdj
// made C++ standards compliant (no longer forward declare items in std namespace)
//
// Revision 1.6  1998/07/18 19:51:48  mkl
// solaris: introduce extra spaces around < and >
//
// Revision 1.5  1998/07/02 22:14:35  cdj
// added "using namespace std" when using namespaces (needed by cxx 6.0)
//
// Revision 1.4  1998/06/21 23:11:50  cdj
// added NO_STD_NAMESPACE_BUG and bug flags needed for cxx 6.0
//
// Revision 1.3  1998/04/09 23:20:31  cleo3
// port to egcs
//
// Revision 1.2  1998/02/03 22:13:20  mkl
// changed *_COMPARE macros to *_COMP
//
// Revision 1.1.1.1  1998/02/02 23:25:34  sjp
// New package for files that help STL usage
//
// Revision 1.11  1998/01/07 22:36:59  sjp
// Corrected position in file of ALL cpp macros
//
// Revision 1.10  1998/01/06 21:22:20  sjp
// Added STL_ALLOCATORS_NOT_TEMPLATE option and macros
//
// Revision 1.9  1997/09/04 19:33:11  sjp
// Changed "less" to be a struct
//
// Revision 1.8  1997/09/04 16:05:29  sjp
// fixed problem with "undef"
//
// Revision 1.7  1997/09/03 20:05:37  sjp
// Uses CPP macros for STL containers
//
// Revision 1.6  1997/08/27 03:38:35  sjp
// Updated to new name for bug flags
//
// Revision 1.5  1997/08/14 11:42:12  sjp
// Mods to run under CW Pro 1
//
// Revision 1.4  1997/08/06 14:10:40  sjp
// Updated the bug flags
//
// Revision 1.3  1997/07/28 16:34:08  sjp
// Fixed to work under cxx 5.6
//
// Revision 1.2  1997/07/18 16:59:42  sjp
// Changed to handle auto-instantiation in cxx
//
// Revision 1.1  1997/07/09 17:41:40  sjp
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

#if !defined(STL_ALLOCATOR_TWO)

#if defined(STL_ALLOCATORS_NOT_TEMPLATED)
#  define STL_ALLOCATOR_TWO( c , d ) allocator
#else
#  define STL_ALLOCATOR_TWO( c , d ) allocator< c , d >
#endif /* STL_ALLOCATORS_NOT_TEMPLATED) */

#endif /* STL_ALLOCATOR_TWO */

#if !defined(STL_MAP)
#  define std::map< k , c > map< k , c >
#  define STL_MAP_COMP( k , c , l ) map< k , c , l >
#  define STL_MAP_COMP_ALLOC( k , c , l , a ) map< k , c , l , a >

#if defined(NO_ALLOCATOR_IN_STL_DECLARATION_BUG)

#if (defined(NO_DEFAULT_COMPARE_IN_STL_BUG) || defined(NO_DEFAULT_PARAMETERS_FOR_TEMPLATES_BUG))
#  undef STL_MAP
#  define std::map< k , c > map< k , c , less< k > >
#  undef STL_MAP_COMP_ALLOC
#endif  /* NO_DEFAULT_COMPARE_IN_STL_BUG || NO_DEFAULT_PARAMETERS_FOR_TEMPLATES_BUG */

#else

#if (defined(NO_DEFAULT_COMPARE_IN_STL_BUG) || defined(NO_DEFAULT_PARAMETERS_FOR_TEMPLATES_BUG))

#if (defined(NO_DEFAULT_ALLOCATOR_IN_STL_BUG) || defined(NO_DEFAULT_PARAMETERS_FOR_TEMPLATES_BUG))
#  undef STL_MAP
#  define std::map< k , c > map< k , c , less< k > , STL_ALLOCATOR_TWO( pair < const k , c > ) >
#  undef STL_MAP_COMP
#  define STL_MAP_COMP( k , c , l ) map< k , c , l , STL_ALLOCATOR_TWO( pair < const k , c > ) >
#else

#if defined(MAP_ALLOCATOR_ONLY_USES_CONTENTS_BUG)
#  undef STL_MAP
#  define std::map< k , c > map< k , c , less< k > , STL_ALLOCATOR( c ) >
#  undef STL_MAP_COMP
#  define STL_MAP_COMP( k , c , l ) map< k , c , l , STL_ALLOCATOR( c ) >
#else

#  undef STL_MAP
#  define std::map< k , c > map< k , c , less< k > >
#endif /* MAP_ALLOCATOR_ONLY_USES_CONTENTS_BUG */

#endif /* NO_DEFAULT_ALLOCATOR_IN_STL_BUG || NO_DEFAULT_PARAMETERS_FOR_TEMPLATES_BUG */

#endif /* NO_DEFAULT_COMPARE_IN_STL_BUG || NO_DEFAULT_PARAMETERS_FOR_TEMPLATES_BUG */

#endif /* NO_ALLOCATOR_IN_STL_DECLARATION_BUG */

#endif /* STL_MAP */

#include <map>

#ifndef NO_STD_NAMESPACE_BUG
using namespace std;
#endif // NO_STD_NAMESPACE_BUG

#include <map>

#endif /* STLUTILITY_FWD_MAP_H */
