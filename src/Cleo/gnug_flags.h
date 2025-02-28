#if !defined(EXPERIMENT_GNUG_FLAGS_H)
#define EXPERIMENT_GNUG_FLAGS_H
// -*- C++ -*-
//
// Package:     Cleo
// Module:      Cleo
// 
// Description: Experiment specific header
//
// Usage:
//    Set flags for known bugs in g++
//
// Author:      Simon Patton, Martin Lohner, Chris Jones
// Created:     Mon July 7 08:38:02 EDT 1997
// $Id: gnug_flags.h,v 1.22 2002/12/05 20:45:54 cleo3 Exp $
//
// Revision history
//
// $Log: gnug_flags.h,v $
// Revision 1.22  2002/12/05 20:45:54  cleo3
// first approximation of g++ flags for Linux
//
// Revision 1.21  2001/01/16 22:20:01  cdj
// updated bug flags
//
// Revision 1.20  2000/05/05 19:38:35  mkl
// get started on linux
//
// Revision 1.19  1999/12/11 18:33:52  mkl
// new linux/gnu bug flag: string compare args reversed
//
// Revision 1.18  1999/08/26 18:35:30  mkl
// added NO_UPPERCASE_MANIP_BUG flag
//
// Revision 1.17  1999/04/30 18:14:26  mkl
// undefined exception bugs
//
// Revision 1.16  1998/12/03 21:42:05  mkl
// added HAVE_NO_CORBA for platforms/compilers that dont have CORBA ORB
//
// Revision 1.15  1998/11/12 22:27:13  mkl
// renamed BOOLEAN_ALREADY_DEFINED_BUG to inverted BOO_NOT_DEFINED_BUG; new BOOL_IS_INT_BUG for Solaris
//
// Revision 1.14  1998/09/16 21:38:29  mkl
// use new bug flag for static/extern linkage of kFacilityStrings in Template .cc files
//
// Revision 1.13  1998/09/10 19:55:29  mkl
// handle new version of egcs compiler (2.91)
//
// Revision 1.12  1998/09/09 22:58:33  mkl
// handling of new version of egcs compiler (2.9)
//
// Revision 1.11  1998/06/21 23:06:45  cdj
// add NO_STD_NAMESPACE_BUG and new bugs needed for cxx 6.0
//
// Revision 1.10  1998/04/10 14:25:41  cleo3
// screwup: had deleted NO_ALLOCATOR_IN_STL_DECLARATION_BUG define statement by mistake
//
// Revision 1.9  1998/04/09 23:15:20  cleo3
// port to egcs
//
// Revision 1.8  1998/03/31 20:19:08  cdj
// added NO_TEMPLATED_MEMBER_FUNCTIONS_BUG flag
//
// Revision 1.7  1998/02/04 23:46:00  mkl
// added CDF/BaBar bug flags for compiling InterfaceUtil
//
// Revision 1.6  1997/09/04 16:07:19  sjp
// New bug flag for strings
//
// Revision 1.5  1997/08/29 14:23:19  sjp
// renamed typedef problem to be forard declaration problem
//
// Revision 1.4  1997/08/27 03:38:30  sjp
// Updated to new name for bug flags
//
// Revision 1.3  1997/08/14 11:42:00  sjp
// Mods to run under CW Pro 1
//
// Revision 1.2  1997/08/06 14:08:07  sjp
// Updated the bug flags
//
// Revision 1.1.1.1  1997/07/11 16:58:36  sjp
// Cleo's implementation of the EXperiement directory.
//
/*
#define BOOL_NOT_DEFINED_BUG

#define HAVE_NO_CORBA

#define OSTREAM_IS_A_CLASS_BUG
#define ISTREAM_IS_A_CLASS_BUG
#define USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG
#define USES_STRING_CHAR_TRAIT_BUG
#define NO_ALLOCATOR_IN_STL_DECLARATION_BUG
#define NO_ALLOCATOR_IN_STRING_DECLARATION_BUG
#define NO_DEFAULT_COMPARE_IN_STL_BUG
#define MULTIMAP_IS_SEPARATE_FILE_BUG
#define MULTISET_IS_SEPARATE_FILE_BUG
#define AMBIGUOUS_STRING_FUNCTIONS_BUG
#define GLOBAL_AND_MEMBER_FUNCTION_RESOLUTION_BUG
#define PROTECTED_CTOR_NOT_ACCESSIBLE_BUG
#define TYPEDEFS_IN_TEMPLATES_IN_ARGS_BUG
#define TYPEDEFS_IN_TEMPLATES_AS_RETURN_BUG
#define NESTED_TYPEDEF_USED_IN_TEMPLATE_RETURN_BUG
#define FORWARD_DECLARATION_NOT_BOUND_TO_DEFINITION_BUG
#define NO_TEMPLATED_MEMBER_FUNCTIONS_BUG
#define NO_STD_NAMESPACE_BUG
#define NO_UPPERCASE_MANIP_BUG

#define FILESCOPE_IN_TEMPLATE_CC_BUG static

// undefined exception bugs
#define UNDEF_IOS_BASE_FAILURE_EXCEPT_BUG
#define UNDEF_BAD_TYPEID_EXCEPT_BUG
#define UNDEF_BAD_CAST_EXCEPT_BUG

// ------- bug flags for ecgs and g++ 2.8.0 and higher --------

// -- bug flags for ecgs and g++ 2.8.0 <= vers < 2.9.0
#if __GNUC__ == 2 && __GNUC_MINOR__ >= 80

#define STRING_IN_STL_TOO_LONG_SYMBOL_BUG

// undefining "features" above
// checked OSTREAM_IS_A_CLASS_BUG
// checked ISTREAM_IS_A_CLASS_BUG
// not yet USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG
// checked USES_STRING_CHAR_TRAIT_BUG
#undef NO_ALLOCATOR_IN_STL_DECLARATION_BUG
// not yet NO_ALLOCATOR_IN_STRING_DECLARATION_BUG
#undef NO_DEFAULT_COMPARE_IN_STL_BUG
#undef MULTIMAP_IS_SEPARATE_FILE_BUG
#undef MULTISET_IS_SEPARATE_FILE_BUG
// not yet AMBIGUOUS_STRING_FUNCTIONS_BUG
#undef GLOBAL_AND_MEMBER_FUNCTION_RESOLUTION_BUG
// checked PROTECTED_CTOR_NOT_ACCESSIBLE_BUG
#undef TYPEDEFS_IN_TEMPLATES_IN_ARGS_BUG
#undef TYPEDEFS_IN_TEMPLATES_AS_RETURN_BUG
// not yet NESTED_TYPEDEF_USED_IN_TEMPLATE_RETURN_BUG
// not yet FORWARD_DECLARATION_NOT_BOUND_TO_DEFINITION_BUG
// not yet NO_TEMPLATED_MEMBER_FUNCTIONS_BUG

// new "features"
#define STL_ALLOCATORS_NOT_TEMPLATED
#define ALLOCATOR_IS_TYPEDEF_BUG

#undef  NO_ALLOCATOR_IN_STRING_DECLARATION_BUG
#define NO_ALLOCATOR_NOR_TRAITS_IN_STRING_TYPEDEF_BUG

#endif


// -- bug flags for ecgs and g++ >= 2.90
#if __GNUC_MINOR__ >= 90

#undef STL_ALLOCATORS_NOT_TEMPLATED
#undef ALLOCATOR_IS_TYPEDEF_BUG
#undef NO_ALLOCATOR_NOR_TRAITS_IN_STRING_TYPEDEF_BUG

#endif

// -- bug flags for ecgs and g++ >= 2.91
#if __GNUC_MINOR__ >= 91

#define STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG
#define INCLUDE_TEMPLATE_DEFINITIONS
#undef NO_ALLOCATOR_IN_STL_DECLARATION_BUG
#undef NO_ALLOCATOR_IN_STRING_DECLARATION_BUG
#undef NO_DEFAULT_COMPARE_IN_STL_BUG

// -----------------------------------------------------------
// Harris and Anton: here is where you start!
// new Linux Redhat >=6.1 gnu 2.91x flags
#define STRING_COMPARE_ARGS_REVERSED
#define OLD_ITERATOR_CLASSES_BUG
#define NEED_TYPESPEC_TO_INSTANTIATE_NAMESPACED_FUNCTION_BUG

#define NEED_TO_BE_IN_NAMESPACE_TO_INSTANTIATE_FUNCTION_BUG
#define STRING_ALLOCATOR_VOID_BUG
#define NON_STANDARD_ALLOCATOR_BUG

#undef USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG
#undef AMBIGUOUS_STRING_FUNCTIONS_BUG
#undef PROTECTED_CTOR_NOT_ACCESSIBLE_BUG
#undef NESTED_TYPEDEF_USED_IN_TEMPLATE_RETURN_BUG
#undef FORWARD_DECLARATION_NOT_BOUND_TO_DEFINITION_BUG
#undef NO_TEMPLATED_MEMBER_FUNCTIONS_BUG
#undef NO_STD_NAMESPACE_BUG
#undef NO_UPPERCASE_MANIP_BUG
#undef INCLUDE_TEMPLATE_DEFINITIONS
#undef STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG
#undef STL_ALLOCATORS_NOT_TEMPLATED
#undef ALLOCATOR_IS_TYPEDEF_BUG
#undef NO_ALLOCATOR_NOR_TRAITS_IN_STRING_TYPEDEF_BUG
#undef STRING_IN_STL_TOO_LONG_SYMBOL_BUG
 
#endif

//Eddy undefined these, but he's not sure what compiler he's using
#undef USES_STRING_CHAR_TRAIT_BUG
#undef NO_ALLOCATOR_IN_STL_DECLARATION_BUG
#undef NO_ALLOCATOR_IN_STRING_DECLARATION_BUG
#undef NO_DEFAULT_COMPARE_IN_STL_BUG
#undef MULTIMAP_IS_SEPARATE_FILE_BUG
#undef MULTISET_IS_SEPARATE_FILE_BUG
#undef GLOBAL_AND_MEMBER_FUNCTION_RESOLUTION_BUG
#undef TYPEDEFS_IN_TEMPLATES_IN_ARGS_BUG
#undef TYPEDEFS_IN_TEMPLATES_AS_RETURN_BUG

#if __SUNPRO_CC >= 0x500
#undef MULTIMAP_IS_A_SEPARATE_FILE_BUG
#endif
*/
#define NEED_TO_BE_IN_NAMESPACE_TO_INSTANTIATE_TEMPLATE_BUG
#define FILESCOPE_IN_TEMPLATE_CC_BUG static
using namespace std;
#define PROTECTED_CTOR_NOT_ACCESSIBLE_BUG
#endif /* EXPERIMENT_GNUG_FLAGS_H */
