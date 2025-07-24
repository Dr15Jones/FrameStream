#if !defined(STLUTILITY_FWD_MULTISET_H)
#define STLUTILITY_FWD_MULTISET_H
// -*- C++ -*-
//
// Package:     STLUtility
// Module:      fwd_multiset
// 
// Description: Handle the forward declaration of the STL multiset
//
// Usage:
//    include this file wherever you'd normally forward declare a STL multiset
//
// Author:      Simon Patton
// Created:     Thu Jul  3 14:44:35 EDT 1997
// $Id: fwd_multiset.h,v 1.6 2000/12/02 20:10:02 cdj Exp $
//
// Revision history
//
// $Log: fwd_multiset.h,v $
// Revision 1.6  2000/12/02 20:10:02  cdj
// made C++ standards compliant (no longer forward declare items in std namespace)
//
// Revision 1.5  1998/07/02 22:14:38  cdj
// added "using namespace std" when using namespaces (needed by cxx 6.0)
//
// Revision 1.4  1998/06/21 23:11:53  cdj
// added NO_STD_NAMESPACE_BUG and bug flags needed for cxx 6.0
//
// Revision 1.3  1998/04/09 23:20:33  cleo3
// port to egcs
//
// Revision 1.2  1998/02/03 22:13:21  mkl
// changed *_COMPARE macros to *_COMP
//
// Revision 1.1.1.1  1998/02/02 23:25:34  sjp
// New package for files that help STL usage
//
// Revision 1.10  1998/01/07 22:36:58  sjp
// Corrected position in file of ALL cpp macros
//
// Revision 1.9  1998/01/06 21:22:17  sjp
// Added STL_ALLOCATORS_NOT_TEMPLATE option and macros
//
// Revision 1.8  1997/09/04 19:33:15  sjp
// Changed "less" to be a struct
//
// Revision 1.7  1997/09/04 16:05:32  sjp
// fixed problem with "undef"
//
// Revision 1.6  1997/09/03 20:05:41  sjp
// Uses CPP macros for STL containers
//
// Revision 1.5  1997/08/27 03:38:39  sjp
// Updated to new name for bug flags
//
// Revision 1.4  1997/08/14 11:42:15  sjp
// Mods to run under CW Pro 1
//
// Revision 1.3  1997/08/06 14:10:45  sjp
// Updated the bug flags
//
// Revision 1.2  1997/07/28 17:13:17  sjp
// Fixed to work under cxx 5.6
//
// Revision 1.1  1997/07/18 16:55:33  sjp
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

#if !defined(STL_MULTISET)
#  define std::multiset< c > multiset< c >
#  define STL_MULTISET_COMP( c , l ) multiset< c , l >
#  define STL_MULTISET_COMP_ALLOC( c , l , a ) multiset< c , l , a >

#if defined(NO_ALLOCATOR_IN_STL_DECLARATION_BUG)

#if (defined(NO_DEFAULT_COMPARE_IN_STL_BUG) || defined(NO_DEFAULT_PARAMETERS_FOR_TEMPLATES_BUG))
#  undef STL_MULTISET
#  define std::multiset< c > multiset< c , less< c > >
#  undef STL_MULTISET_COMP_ALLOC
#endif  /* NO_DEFAULT_COMPARE_IN_STL_BUG || NO_DEFAULT_PARAMETERS_FOR_TEMPLATES_BUG */

#else

#if (defined(NO_DEFAULT_COMPARE_IN_STL_BUG) || defined(NO_DEFAULT_PARAMETERS_FOR_TEMPLATES_BUG))

#if (defined(NO_DEFAULT_ALLOCATOR_IN_STL_BUG) || defined(NO_DEFAULT_PARAMETERS_FOR_TEMPLATES_BUG))
#  undef STL_MULTISET
#  define std::multiset< c > multiset< c , less< c > , STL_ALLOCATOR( c ) >
#  undef STL_MULTISET_COMP
#  define STL_MULTISET_COMP( c , l ) multiset< c , l , STL_ALLOCATOR( c ) >
#else

#  undef STL_MULTISET
#  define std::multiset< c > multiset< c , less< c > >
#endif /* NO_DEFAULT_ALLOCATOR_IN_STL_BUG || NO_DEFAULT_PARAMETERS_FOR_TEMPLATES_BUG */

#endif /* NO_DEFAULT_COMPARE_IN_STL_BUG || NO_DEFAULT_PARAMETERS_FOR_TEMPLATES_BUG */

#endif /* NO_ALLOCATOR_IN_STL_DECLARATION_BUG */

#endif /* STL_MULTISET */

#include <set>

#ifndef NO_STD_NAMESPACE_BUG
using namespace std;
#endif // NO_STD_NAMEPSACE_BUG


#endif /* STLUTILITY_FWD_MULTISET_H */

