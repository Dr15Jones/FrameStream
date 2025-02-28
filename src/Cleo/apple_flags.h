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
//    Set flags for known bugs in Apple's c++
//
// Author:      Simon Patton, Martin Lohner, Chris Jones
// Created:     Mon July 7 08:38:02 EDT 1997
// $Id: apple_flags.h,v 1.1 2001/01/16 22:30:17 cdj Exp $
//
// Revision history
//
// $Log: apple_flags.h,v $
// Revision 1.1  2001/01/16 22:30:17  cdj
// first submission
//

//#define BOOL_NOT_DEFINED_BUG

#define HAVE_NO_CORBA

//NOTE ISTREAM and OSTREAM are a class because we include
//  iostream.h instead of using iostream
#define ISTREAM_IS_A_CLASS_BUG
#define OSTREAM_IS_A_CLASS_BUG

#define NEED_TO_BE_IN_NAMESPACE_TO_INSTANTIATE_FUNCTION_BUG
#define NO_UPPERCASE_MANIP_BUG
#define PROTECTED_CTOR_NOT_ACCESSIBLE_BUG
#define USES_STRING_CHAR_TRAIT_BUG
#define NON_STANDARD_ALLOCTOR_BUG
#define STRING_COMPARE_ARGS_REVERSED

//#define FILESCOPE_IN_TEMPLATE_CC_BUG static

// undefined exception bugs
//#define UNDEF_IOS_BASE_FAILURE_EXCEPT_BUG
//#define UNDEF_BAD_TYPEID_EXCEPT_BUG
//#define UNDEF_BAD_CAST_EXCEPT_BUG


#endif /* EXPERIMENT_GNUG_FLAGS_H */
