#if !defined(EXPERIMENT_HPCC_FLAGS_H)
#define EXPERIMENT_HPCC_FLAGS_H
// -*- C++ -*-
//
// Package:     BaBar
// Module:      BaBar
// 
// Description: Experiement specific header
//
// Usage:
//    Set flags for known bugs in HPCC   
//
// Author:  M. Turcotte
// Created: 8/25/97 University of Texas at Dallas
// $Id: HPCC_flags.h,v 1.5 1998/11/12 22:27:05 mkl Exp $
//
// Revision history
//
// 
//

#define BOOL_NOT_DEFINED_BUG
#define true  1
#define false 0

// Set of flags determined using the Bug tests from Simon Patton

#define OS_HPUX_10
#define OS_NO_WSTRING
#define OS_NO_ALLOCATORS
#define USING_OBJECTSPACE_STRING

#define PROTECTED_CTOR_NOT_ACCESSIBLE_BUG
#define ISTREAM_IS_A_CLASS_BUG
#define OSTREAM_IS_A_CLASS_BUG
#define NO_ALLOCATOR_IN_STL_DECLARATION_BUG
#define NO_DEFAULT_PARAMETERS_FOR_TEMPLATES_BUG
#define NO_DEFAULT_COMPARE_IN_STL_BUG
#define IOMANIP_IS_CPP_MACRO_BUG
#define NO_IS_OPEN_FUNCTION_IN_FSTREAM_BUG
#define NO_STD_NAMESPACE_BUG

#endif /* EXPERIMENT_HPCC_FLAGS_H */
