#if !defined(EXPERIMENT_XLC_FLAGS_H)
#define EXPERIMENT_XLC_FLAGS_H
// -*- C++ -*-
//
// Package:     BaBar
// Module:      BaBar
// 
// Description: Experiement specific header
//
// Usage:
//    Set flags for known bugs in xlC   
//
// Author:      Simon Patton
// Created:     Thu Dec 18 11:54:19 PST 1997
// $Id: xlc_flags.h,v 1.4 1998/11/12 22:27:18 mkl Exp $
//
// Revision history
//
// $Log: xlc_flags.h,v $
// Revision 1.4  1998/11/12 22:27:18  mkl
// renamed BOOLEAN_ALREADY_DEFINED_BUG to inverted BOO_NOT_DEFINED_BUG; new BOOL_IS_INT_BUG for Solaris
//
// Revision 1.3  1998/09/16 21:38:31  mkl
// use new bug flag for static/extern linkage of kFacilityStrings in Template .cc files
//
// Revision 1.2  1998/06/21 23:06:48  cdj
// add NO_STD_NAMESPACE_BUG and new bugs needed for cxx 6.0
//
// Revision 1.1  1997/12/19 01:32:52  sjp
// New file to manage compiler flags
//

// Set of flags determined using the Bug tests from Simon Patton

#define BOOL_NOT_DEFINED_BUG

#define ISTREAM_IS_A_CLASS_BUG
#define OSTREAM_IS_A_CLASS_BUG
#define USING_RW_STRING
#define NO_STD_NAMESPACE_BUG

#define static static

#endif /* EXPERIMENT_XLC_FLAGS_H */
