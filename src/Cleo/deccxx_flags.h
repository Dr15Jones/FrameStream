#if !defined(EXPERIMENT_DECCXX_FLAGS_H)
#define EXPERIMENT_DECCXX_FLAGS_H
// -*- C++ -*-
//
// Package:     Cleo
// Module:      Cleo
// 
// Description: Experiement specific header
//
// Usage:
//    Set flags for known bugs in DEC cxx
//
// Author:      Simon Patton
// Created:     Mon July 7 08:38:02 EDT 1997
// $Id: deccxx_flags.h,v 1.31 2001/09/07 15:11:58 cleo3 Exp $
//
// Revision history
//
// $Log: deccxx_flags.h,v $
// Revision 1.31  2001/09/07 15:11:58  cleo3
// added new flag USING_IOSTREAM_H_BUG
//
// Revision 1.30  1999/10/30 12:41:46  cleo3
// updated to work with cxx 6.2 and new bug checkers
//
// Revision 1.29  1999/09/06 21:26:38  mkl
// added NO_COVARIANT_RETURN_TYPE_BUG flag plus test program
//
// Revision 1.28  1999/08/26 18:35:30  mkl
// added NO_UPPERCASE_MANIP_BUG flag
//
// Revision 1.27  1999/07/05 20:59:02  mkl
// new bug flag NO_GETLINE_ISTREAM_STRING_BUG
//
// Revision 1.26  1999/04/30 18:14:26  mkl
// undefined exception bugs
//
// Revision 1.25  1998/12/03 21:42:04  mkl
// added HAVE_NO_CORBA for platforms/compilers that dont have CORBA ORB
//
// Revision 1.24  1998/11/20 18:27:16  marsh
// Added PROTECTED_CTOR_NOT_ACCESSIBLE_BUG
//
// Revision 1.23  1998/11/12 22:27:11  mkl
// renamed BOOLEAN_ALREADY_DEFINED_BUG to inverted BOO_NOT_DEFINED_BUG; new BOOL_IS_INT_BUG for Solaris
//
// Revision 1.22  1998/11/07 17:32:36  cdj
// cxx 6.1 does not have the XMAP_ALLOCATOR_ONLY_USES_CONTENTS_BUG
//
// Revision 1.21  1998/09/16 21:38:29  mkl
// use new bug flag for static/extern linkage of kFacilityStrings in Template .cc files
//
// Revision 1.20  1998/09/14 19:03:54  mkl
// corrected version number of Cornell OSF1 cxx
//
// Revision 1.19  1998/09/07 20:16:55  mkl
// added cpp-macro to define __rwstd::(__)rb_tree for different subversions of cxx 6.0 compiler's map implementations
//
// Revision 1.18  1998/07/18 19:39:06  mkl
// new solaris platform bug flags
//
// Revision 1.17  1998/06/23 19:37:12  cdj
// added NEED_NAMESPACE_TO_INSTANTIATE_OVERLOADED_FUNCTION_BUG
//
// Revision 1.16  1998/06/21 23:06:44  cdj
// add NO_STD_NAMESPACE_BUG and new bugs needed for cxx 6.0
//
// Revision 1.15  1998/04/09 23:15:20  cleo3
// port to egcs
//
// Revision 1.14  1998/03/31 20:19:06  cdj
// added NO_TEMPLATED_MEMBER_FUNCTIONS_BUG flag
//
// Revision 1.13  1998/02/04 23:45:59  mkl
// added CDF/BaBar bug flags for compiling InterfaceUtil
//
// Revision 1.12  1998/01/16 17:09:57  mkl
// backed out of 'undefined PRAGMA_TEMPLATE_INSTANTIATION_BUG for cxx >=5.6' because of missing symbols; cxx 5.6 not ready for prime time instantiation yet
//
// Revision 1.11  1998/01/15 21:24:10  mkl
// undefined PRAGMA_TEMPLATE_INSTANTIATION_BUG for cxx >=5.6
//
// Revision 1.10  1997/12/18 21:41:04  cleo3
// changed version for cxx5.6 from 50690010 to 50600000
//
// Revision 1.9  1997/09/04 20:04:51  sjp
// Added new bug flags
//
// Revision 1.8  1997/08/29 14:27:09  sjp
// added CXX_TYP.... flag
//
// Revision 1.7  1997/08/27 03:38:27  sjp
// Updated to new name for bug flags
//
// Revision 1.6  1997/08/14 19:30:41  sjp
// Added flag about defaults for rbtree
//
// Revision 1.5  1997/08/14 11:41:58  sjp
// Mods to run under CW Pro 1
//
// Revision 1.4  1997/08/06 14:08:04  sjp
// Updated the bug flags
//
// Revision 1.3  1997/07/28 18:04:24  sjp
// added new flags, and reorganised version handling
//
// Revision 1.2  1997/07/22 17:40:24  sjp
// Added flag because auto-instantation problem
//
// Revision 1.1.1.1  1997/07/11 16:58:36  sjp
// Cleo's implementation of the EXperiement directory.
//

// Base set of flags for __DECCXX_VER >= 50490006
#define BOOL_NOT_DEFINED_BUG

#define HAVE_NO_CORBA

#define PRAGMA_TEMPLATE_INSTANTIATION_BUG
#define OSTREAM_IS_A_CLASS_BUG
#define ISTREAM_IS_A_CLASS_BUG
#define USING_IOSTREAM_H_BUG

#define USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG
#define USES_STRING_CHAR_TRAIT_BUG
#define LOOSES_NESTED_CLASS_DECLARATION_BUG
#define CONSTRUCTOR_ACCESS_CONFUSED_FOR_TEMPLATES_BUG
#define CANNOT_USE_ENUMS_AS_TEMPLATE_ARGS_BUG
#define IOS_SETSTATE_IS_PROTECTED_BUG
#define IOMANIP_IS_CPP_MACRO_BUG
#define AUTO_INSTANTIATION_WITH_TEMPLATE_AS_ARGS_BUG
#define NO_ALLOCATOR_IN_STL_DECLARATION_BUG
#define PAIR_HAS_NOT_DEFAULT_CTOR_BUG
#define TEMPLATE_PARAMETERS_BREAK_TYEPDEFS_BUG
#define NO_DEFAULT_COMPARE_IN_STL_BUG
#define CANNOT_USE_TYPEDEF_IN_TYPEDEFED_TEMPLATED_CLASS_BUG
#define CXX_TYPEDEFED_BEFORE_DEFINITION_BUG
#define OLD_CXX_STRING_CLASS_BUG
#define OLD_CXX_STL_INCLUDE_FLAGS_BUG
#define NO_IS_OPEN_FUNCTION_IN_FSTREAM_BUG
#define NO_TEMPLATED_MEMBER_FUNCTIONS_BUG
#define NO_STD_NAMESPACE_BUG
#define PROTECTED_CTOR_NOT_ACCESSIBLE_BUG
#define NO_GETLINE_ISTREAM_STRING_BUG
#define NO_UPPERCASE_MANIP_BUG
#define NO_COVARIANT_RETURN_TYPE_BUG
#define OLD_ITERATOR_CLASSES_BUG

// undefined exception bugs
#define UNDEF_IOS_BASE_FAILURE_EXCEPT_BUG
#define UNDEF_BAD_TYPEID_EXCEPT_BUG
#define UNDEF_BAD_CAST_EXCEPT_BUG

// define "typename" to nothing (used in templates!)
#define typename
#define FILESCOPE_IN_TEMPLATE_CC_BUG static

// based on cdf/babar bug flags
#define DEFECT_OLD_IOSTREAM_HEADERS
#define DEFECT_NO_STDLIB_NAMESPACES


#if __DECCXX_VER >= 50590004
#undef  NO_ALLOCATOR_IN_STL_DECLARATION_BUG
#undef  NO_DEFAULT_COMPARE_IN_STL_BUG
#undef  CANNOT_USE_TYPEDEF_IN_TYPEDEFED_TEMPLATED_CLASS_BUG
#undef  OLD_CXX_STRING_CLASS_BUG
#define STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG
#define CXX_IMPLIED_SPECIALIZATION_BUG
#define EXCEPTION_CLASH_WITH_MATH_H_BUG
#endif /* __DECCXX_VER >= 50590004 */

/* #if __DECCXX_VER >= 50690010 */
#if __DECCXX_VER >= 50600000
/* not ready for prime time #undef  PRAGMA_TEMPLATE_INSTANTIATION_BUG */
#undef  PAIR_HAS_NOT_DEFAULT_CTOR_BUG
#undef  USES_STRING_CHAR_TRAIT_BUG
#undef  CXX_TYPEDEFED_BEFORE_DEFINITION_BUG
#undef  OLD_CXX_STL_INCLUDE_FLAGS_BUG
#define NO_DEFAULT_PARAMETERS_FOR_RBTREE_BUG
#endif /* __DECCXX_VER >= 50690010 */

#if __DECCXX_VER >= 60000000
#undef NO_STD_NAMESPACE_BUG
#define MAP_ALLOCATOR_ONLY_USES_CONTENTS_BUG
#define MULTIMAP_ALLOCATOR_ONLY_USES_CONTENTS_BUG
#define NEED_NAMESPACE_TO_INSTANTIATE_OVERLOADED_FUNCTION_BUG
#define STRING_ALLOCATOR_VOID_BUG
#undef PRAGMA_TEMPLATE_INSTANTIATION_BUG

/* needed for internal rb_tree name-spaced name */
#define STLUTILITY_FUNC( funcname ) __ ## funcname
#define STLUTILITY_SELECT1ST __rwstd::select1st
#define STLUTILITY_IDENT __rwstd::ident
#if __DECCXX_VER >= 60090021
#define STLUTILITY_RB_TREE __rwstd::__rb_tree
#else
#define STLUTILITY_RB_TREE __rwstd::rb_tree
#endif
#endif /* __DECCXX_VER >= 60000000 */

#if __DECCXX_VER >= 60190027
#undef typename           
#undef EXCEPTION_CLASH_WITH_MATH_H_BUG
#undef NO_TEMPLATED_MEMBER_FUNCTIONS_BUG
#undef LOOSES_NESTED_CLASS_DECLARATION_BUG
#undef BOOL_NOT_DEFINED_BUG
#undef MAP_ALLOCATOR_ONLY_USES_CONTENTS_BUG
#undef MULTIMAP_ALLOCATOR_ONLY_USES_CONTENTS_BUG
#undef CONSTRUCTOR_ACCESS_CONFUSED_FOR_TEMPLATES_BUG
#undef CANNOT_USE_ENUMS_AS_TEMPLATE_ARGS_BUG
#endif /* __DECCXX_VER >= 60190027 */

#if __DECCXX_VER >= 60290024
#undef OLD_ITERATOR_CLASSES_BUG
#undef STLUTILITY_RB_TREE
#define STLUTILITY_RB_TREE __RWSTD::_RWrb_tree
#undef STLUTILITY_SELECT1ST
#define STLUTILITY_SELECT1ST __RWSTD::_RWselect1st
#undef STLUTILITY_IDENT
#define STLUTILITY_IDENT __RWSTD::_RWident
#undef STLUTILITY_FUNC
#define STLUTILITY_FUNC( funcname ) _RW ## funcname
#undef STRING_ALLOCATOR_VOID_BUG
#endif /* __DECCXX_VER >= 60290024 */

#if __DECCXX_VER <= 50590004
// use standard cxx bool definition
#include <stl_macros>
#elif __DECCXX_VER <= 60000000
#include <stdcomp>
#endif

#undef _RWSTD_NO_NAMESPACE

#endif /* EXPERIMENT_DECCXX_FLAGS_H */
