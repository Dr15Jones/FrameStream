#if !defined(CPPSTD_FWD_STRING_H)
#define CPPSTD_FWD_STRING_H
// -*- C++ -*-
//
// Package:     C++Std
// Module:      fwd_string
// 
// Description: Handle the forward declaration of the STL string
//
// Usage:
//    include this file wherever you'd normally forward declare a STL string
//
// Author:      Simon Patton
// Created:     Thu Jul  3 14:44:35 EDT 1997
// $Id: fwd_string.h,v 1.8 2001/04/17 01:13:37 cleo3 Exp $
//
// Revision history
//
// $Log: fwd_string.h,v $
// Revision 1.8  2001/04/17 01:13:37  cleo3
// now only include string since C++ standard says no forward decleration of items in std namespace
//
// Revision 1.7  1998/07/07 21:17:16  mkl
// dont check for defined(INCLUDE_TEMPLATE_DEFINITIONS); Simon says it 'works' better
//
// Revision 1.6  1998/07/03 20:41:17  mkl
// fix parentheses
//
// Revision 1.5  1998/07/03 20:21:13  mkl
// added USING_RW_STRING
//
// Revision 1.4  1998/07/02 22:13:00  cdj
// added "using namespace std" when needed (used by cxx 6.0)
//
// Revision 1.3  1998/07/02 19:04:46  cdj
// uses std namespace when available (needed by cxx 6.0)
//
// Revision 1.2  1998/04/09 23:18:09  cleo3
// port to egcs
//
// Revision 1.1.1.1  1998/04/01 15:12:21  mkl
// imported sources
//
// Revision 1.6  1997/09/04 16:04:41  sjp
// Set up to use new bug flag
//
// Revision 1.5  1997/08/27 03:38:43  sjp
// Updated to new name for bug flags
//
// Revision 1.4  1997/08/14 11:42:18  sjp
// Mods to run under CW Pro 1
//
// Revision 1.3  1997/08/06 14:10:49  sjp
// Updated the bug flags
//
// Revision 1.2  1997/07/18 16:59:47  sjp
// Changed to handle auto-instantiation in cxx
//
// Revision 1.1  1997/07/09 17:41:45  sjp
// New file for STL forward declaration
//

#if defined(OLD_CXX_STRING_CLASS_BUG)
#  include <String.h>
typedef String string ;
#else

#include <string>

#endif /*OLD_CXX_STRING_CLASS_BUG */

#endif /* CPPSTD_FWD_STRING_H */

