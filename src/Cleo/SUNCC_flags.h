#if !defined(EXPERIMENT_SUNCC_FLAGS_H)
#define EXPERIMENT_SUNCC_FLAGS_H
// -*- C++ -*-
//
// Package:     Cleo
// Module:      Cleo
// 
// Description: Experiment specific header
//
// Usage:
//    Set flags for known bugs in SUNCC   
//
// Author:  Martin Lohner
// Created: 8/25/97 Cornell University
// $Id: SUNCC_flags.h,v 1.28 2003/11/10 15:20:58 cdj Exp $
//
// Revision history
//
// $Log: SUNCC_flags.h,v $
// Revision 1.28  2003/11/10 15:20:58  cdj
// re-enabled LARGE_FILES bug for SUN CC compiler (since we do not compile for 64 bit)
//
// Revision 1.27  2003/04/07 15:17:23  cdj
// added new bug flags to Solaris 8 compiler
//
// Revision 1.26  2002/12/05 21:12:05  cleo3
// added USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG
//
// Revision 1.25  2002/05/31 20:43:25  cleo3
// set flags for CC 5.3 and named bugs for CC 4.2
//
// Revision 1.24  2001/09/07 15:11:24  cleo3
// Updated for Solaris8
//
// Revision 1.23  2001/04/13 20:49:36  cdj
// new flags for Solaris 6.2 compiler
//
// Revision 1.22  2000/07/29 17:01:52  mkl
// catch non-standard Solaris exceptions (base class and out-of-memory)
//
// Revision 1.21  2000/05/05 19:38:34  mkl
// get started on linux
//
// Revision 1.20  1999/10/30 12:41:45  cleo3
// updated to work with cxx 6.2 and new bug checkers
//
// Revision 1.19  1999/09/06 21:26:37  mkl
// added NO_COVARIANT_RETURN_TYPE_BUG flag plus test program
//
// Revision 1.18  1999/08/26 18:35:29  mkl
// added NO_UPPERCASE_MANIP_BUG flag
//
// Revision 1.17  1999/07/21 17:03:09  mkl
// need PROTECTED_CTOR_NOT_ACCESSIBLE_BUG for Solaris
//
// Revision 1.16  1999/07/05 20:59:01  mkl
// new bug flag NO_GETLINE_ISTREAM_STRING_BUG
//
// Revision 1.15  1999/06/09 17:35:01  dlk
// Add new SUNCC flag FSTREAM_CANNOT_READ_LARGE_FILES_BUG
//
// Revision 1.14  1999/04/30 18:14:25  mkl
// undefined exception bugs
//
// Revision 1.13  1999/02/23 16:55:25  mkl
// rename STRSTREAM_DYNAMIC_CTOR_BUG OSTRSTREAM_NO_TERMINATION_BUG because it happens with only ostrstream, but ALL ctors of that class
//
// Revision 1.12  1999/02/23 05:06:35  mkl
// new SunOS CC bug: dynamic-alloc version of (io)strstream ctor does not terminate properly
//
// Revision 1.11  1998/12/30 20:37:46  mkl
// new bug flag INSTANTIATE_ALL_TEMPLATES_IN_FILE_BUG only needed for new (implicit) template instantiation scheme
//
// Revision 1.10  1998/12/29 18:59:56  mkl
// use INCLUDE_TEMPLATE_DEFINITIONS with new instantiation scheme
//
// 
//
#if __SUNPRO_CC < 0x500
#define typename
#endif
#define FILESCOPE_IN_TEMPLATE_CC_BUG extern

#if __SUNPRO_CC < 0x500
#include <ospace/type/prim.h>   /* ObjectSpace STL: defines bool */
#define BOOL_NOT_DEFINED_BUG    /* no bool in CC */
#define BOOL_IS_INT_BUG         /* but ObjectSpace STL defines one as int */
// bool and CLHEP/bool related bugs
#define HEP_HAVE_BOOL
#define CLHEP_TARGET_H "CLHEP/config/CLHEP-sparc-sun-solaris2.6-CC.h"
#else
//need to avoid class with algorithm 'max min' when 'using namespace std'
#define CLHEP_MAX_MIN_DEFINED
#define CLHEP_TARGET_H "CLHEP/config/CLHEP-sparc-sun-solaris2.8-CC.h"
#endif

// ------- new way of doing (implicit) template instantiation
// don't really need:
//    #define INCLUDE_TEMPLATE_DEFINITIONS

// necessary to force inclusion of template .cc files for 
// instantiating templates of template classes; this is ONLY
// needed in new (implicit) template instantiation scheme
#define INSTANTIATE_ALL_TEMPLATES_IN_FILE_BUG
// ------- end: new way of doing (implicit) template instantiation

//define this flag where FAItem< built-in > type is used! not here!
// #define DEREF_OP_FOR_BUILTIN_TYPES_BUG

#define ISTREAM_IS_A_CLASS_BUG
#define OSTREAM_IS_A_CLASS_BUG
#define USING_IOSTREAM_H_BUG
#define USING_OMANIP_BUG

//#define USING_RW_STRING
#define USING_OBJECTSPACE_STRING
#define NO_DEFAULT_PARAMETERS_FOR_TEMPLATES_BUG
//#define NO_DEFAULT_ALLOCATOR_IN_STL_BUG
#define NO_ALLOCATOR_IN_STL_DECLARATION_BUG
#define NO_STD_NAMESPACE_BUG
#define IOS_SETSTATE_IS_PROTECTED_BUG
#define PROTECTED_CTOR_NOT_ACCESSIBLE_BUG
#define STRSTREAMBUF_STR_RETURN_NOT_TERMINATED_BUG
#define NO_IS_OPEN_FUNCTION_IN_FSTREAM_BUG
#define IOMANIP_IS_CPP_MACRO_BUG
#define TYPEDEFS_IN_TEMPLATES_IN_ARGS_BUG
#define TYPEDEFS_IN_TEMPLATES_AS_RETURN_BUG
#define IOMANIP_MACRO_MISSES_SEMICOLON_BUG
#define NO_STATIC_CONST_INTEGRAL_DEFS_IN_CLASS_BUG
#define SEEKOFF_PROTOTYPE_WITHOUT_DEFAULT_3RDARG_BUG
#define FSTREAM_CANNOT_READ_LARGE_FILES_BUG
#define OSTRSTREAM_NO_TERMINATION_BUG
#define NO_GETLINE_ISTREAM_STRING_BUG
#define NO_UPPERCASE_MANIP_BUG
#define NO_COVARIANT_RETURN_TYPE_BUG
#define NO_TEMPLATED_MEMBER_FUNCTIONS_BUG
#define NO_KOENIG_LOOKUP_RULE_BUG
#define NO_NAMESPACE_BUG
#define TYPENAME_BUG
#define NEED_TYPESPEC_TO_INSTANTIATE_NAMESPACED_FUNCTION_BUG 
#define TEMPLATE_FRIEND_OVERLOADED_FUNC_INSTANTIATE_BUG
#define USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG
// undefined exception bugs
#define NON_STANDARD_EXCEPTION_BUG
#define XALLOC_NON_STANDARD_EXCEPTION_BUG
#define UNDEF_BAD_ALLOC_EXCEPT_BUG
#define UNDEF_BAD_EXCEPTION_EXCEPT_BUG
#define UNDEF_IOS_BASE_FAILURE_EXCEPT_BUG
#define UNDEF_BAD_TYPEID_EXCEPT_BUG
#define UNDEF_BAD_CAST_EXCEPT_BUG
#define UNDEF_UNDERFLOW_ERROR_EXCEPT_BUG
#define UNDEF_OVERFLOW_ERROR_EXCEPT_BUG
#define UNDEF_RANGE_ERROR_EXCEPT_BUG
#define UNDEF_STANDARD_BASE_EXCEPT_BUG

#define OLD_ITERATOR_CLASSES_BUG
#define NO_ITERATOR_TRAITS_BUG

//#define DEREF_OP_FOR_BUILTIN_TYPES_BUG
#define RETURN_TYPE_FROM_DEREFERENCING_OPERATOR_FOR_BUILTIN_TYPES_BUG
#define NO_DEFAULT_COMPARE_IN_STL_BUG

#define NO_PARTIAL_TEMPLATE_SPECIALIZATION_BUG

#define AUTO_INSTANTIATE_TEMPLATE_BUG
#define AUTO_INSTANTIATE_VECTOR_VECTOR_BUG
#define STATIC_LOCAL_VARIABLE_IN_TEMPLATE_FUNC_BUG
#define STATIC_LOCAL_VARIABLE_IN_INLINE_TEMPLATE_FUNC_BUG
#define MULTIPLE_INSTANCE_VIRTUAL_TABLE_BUG

#if __SUNPRO_CC >= 0x500
//Allow users to turn this off in cases of conflict
#if !defined(DO_NOT_DECLARE_USING_NAMESPACE_STD)
using namespace std;
#endif
#define USING_RW_STRING
#undef ISTREAM_IS_A_CLASS_BUG                  
#undef OSTREAM_IS_A_CLASS_BUG                  
#undef NO_DEFAULT_PARAMETERS_FOR_TEMPLATES_BUG //defined for CleoDB
#undef NO_ALLOCATOR_IN_STL_DECLARATION_BUG     //defined for CleoDB
#undef NO_DEFAULT_COMPARE_IN_STL_BUG
#undef NO_STD_NAMESPACE_BUG
#undef IOS_SETSTATE_IS_PROTECTED_BUG
#undef STRSTREAMBUF_STR_RETURN_NOT_TERMINATED_BUG
#undef NO_IS_OPEN_FUNCTION_IN_FSTREAM_BUG
#undef IOMANIP_IS_CPP_MACRO_BUG
//#undef TYPEDEFS_IN_TEMPLATES_IN_ARGS_BUG       //unclear whether necessary
//#undef TYPEDEFS_IN_TEMPLATES_AS_RETURN_BUG     //unclear whether necessary
#undef IOMANIP_MACRO_MISSES_SEMICOLON_BUG
#undef NO_STATIC_CONST_INTEGRAL_DEFS_IN_CLASS_BUG
#undef SEEKOFF_PROTOTYPE_WITHOUT_DEFAULT_3RDARG_BUG
//#undef FSTREAM_CANNOT_READ_LARGE_FILES_BUG
#undef USING_OBJECTSPACE_STRING
#undef OSTRSTREAM_NO_TERMINATION_BUG
#undef NO_GETLINE_ISTREAM_STRING_BUG
#undef NO_COVARIANT_RETURN_TYPE_BUG
#undef NO_KOENIG_LOOKUP_RULE_BUG
#undef NO_NAMESPACE_BUG
#undef TYPENAME_BUG
#undef NEED_TYPESPEC_TO_INSTANTIATE_NAMESPACED_FUNCTION_BUG 

#undef DEREF_OP_FOR_BUILTIN_TYPES_BUG
#undef RETURN_TYPE_FROM_DEREFERENCING_OPERATOR_FOR_BUILTIN_TYPES_BUG
#undef NO_DEFAULT_COMPARE_IN_STL_BUG
#endif

#if __SUNPRO_CC >= 0x510
//#undef TYPEDEFS_IN_TEMPLATES_IN_ARGS_BUG
//#undef TYPEDEFS_IN_TEMPLATES_AS_RETURN_BUG
#undef OLD_ITERATOR_CLASSES_BUG
#undef NO_TEMPLATED_MEMBER_FUNCTIONS_BUG
#undef NO_ITERATOR_TRAITS_BUG
#undef NO_PARTIAL_TEMPLATE_SPECIALIZATION_BUG
#undef USING_IOSTREAM_H_BUG
#undef USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG
#endif

#if __SUNPRO_CC >= 0x520
//There appears to be a bug in the configuration of the RW STL
// which doesn't allow partial template specialization to be used
#define NO_ITERATOR_TRAITS_BUG
#define TEMPLATE_TYPEDEF_IN_OVERLOADED_MEMBER_FUNCTION_OF_TEMPLATE_BUG
#undef USING_OMANIP_BUG
#undef XALLOC_NON_STANDARD_EXCEPTION_BUG
//std namespace has exception and so does math.h
#define EXCEPTION_CLASH_WITH_MATH_H_BUG
//bug in compiler doesn't allow STL to use templated member functions
#define NO_STL_TEMPLATED_MEMBER_FUNCTIONS_BUG
#define TEMPLATE_CLASS_FRIEND_FUNCTION_BUG
#define INHERITED_MEMBER_FUNCTION_ARG_IN_TEMPLATED_FUNCTION_BUG


#undef AUTO_INSTANTIATE_TEMPLATE_BUG
#undef AUTO_INSTANTIATE_VECTOR_VECTOR_BUG
#undef STATIC_LOCAL_VARIABLE_IN_TEMPLATE_FUNC_BUG
#undef STATIC_LOCAL_VARIABLE_IN_INLINE_TEMPLATE_FUNC_BUG
#undef MULTIPLE_INSTANCE_VIRTUAL_TABLE_BUG
#undef TEMPLATE_FRIEND_OVERLOADED_FUNC_INSTANTIATE_BUG

#undef PROTECTED_CTOR_NOT_ACCESSIBLE_BUG

#endif

#if defined(NO_TEMPLATED_MEMBER_FUNCTIONS_BUG)
#define NO_STL_TEMPLATED_MEMBER_FUNCTIONS_BUG
#endif

#if defined(NO_NAMESPACE_BUG)
#ifndef NO_KOENIG_LOOKUP_RULE_BUG
#define NO_KOENIG_LOOKUP_RULE_BUG
#endif
#ifndef NEED_TYPESPEC_TO_INSTANTIATE_NAMESPACED_FUNCTION_BUG
#define NEED_TYPESPEC_TO_INSTANTIATE_NAMESPACED_FUNCTION_BUG 
#endif
#ifndef NO_STD_NAMESPACE_BUG
#define NO_STD_NAMESPACE_BUG
#endif
#ifndef SEEKOFF_PROTOTYPE_WITHOUT_DEFAULT_3RDARG_BUG
#define SEEKOFF_PROTOTYPE_WITHOUT_DEFAULT_3RDARG_BUG
#endif
#endif // NO_NAMESPACE_BUG
#endif // EXPERIMENT_SUNCC_FLAGS_H 



