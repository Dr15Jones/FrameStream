#if !defined(EXPERIMENT_MWERKS_FLAGS_H)
#define EXPERIMENT_MWERKS_FLAGS_H
// -*- C++ -*-
//
// Package:     Cleo
// Module:      Cleo
// 
// Description: Experiement specific header
//
// Usage:
//    Set flags for known bugs in Metrowerks Codewarrior
//
// Author:      Simon Patton
// Created:     Mon July 7 08:38:02 EDT 1997
// $Id: mwerks_flags.h,v 1.9 1998/11/12 22:27:14 mkl Exp $
//
// Revision history
//
// $Log: mwerks_flags.h,v $
// Revision 1.9  1998/11/12 22:27:14  mkl
// renamed BOOLEAN_ALREADY_DEFINED_BUG to inverted BOO_NOT_DEFINED_BUG; new BOOL_IS_INT_BUG for Solaris
//
// Revision 1.8  1998/09/16 21:38:30  mkl
// use new bug flag for static/extern linkage of kFacilityStrings in Template .cc files
//
// Revision 1.7  1998/06/21 23:06:46  cdj
// add NO_STD_NAMESPACE_BUG and new bugs needed for cxx 6.0
//
// Revision 1.6  1997/09/04 16:08:36  sjp
// New bug flag for strings
//
// Revision 1.5  1997/09/03 20:05:23  sjp
// Uses CPP macros for STL containers
//
// Revision 1.4  1997/09/01 15:42:20  sjp
// Moved configuration flags out of this file
//
// Revision 1.3  1997/08/14 21:44:22  sjp
// Use implicit instantiation for CW
//
// Revision 1.2  1997/08/14 11:42:02  sjp
// Mods to run under CW Pro 1
//
// Revision 1.1.1.1  1997/07/11 16:58:36  sjp
// Cleo's implementation of the EXperiement directory.
//

#define NPOS_IS_GLOBAL_CONSTANT_BUG
#define CLASS_TYPEDEF_CONSTANT_FAILS_BUG
#define NO_DEFAULT_COMPARE_IN_STL_BUG
#define NO_DEFAULT_ALLOCATOR_IN_STL_BUG
#define NO_DEFAULT_ALLOCATOR_IN_STRING_BUG
#define NO_IMPLICIT_RESOLUTION_FOR_GLOBAL_TEMPLATE_FUNCTION_BUG
#define NO_STD_NAMESPACE_BUG

#define static static

#endif /* EXPERIMENT_MWERKS_FLAGS_H */

