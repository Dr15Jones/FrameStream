// -*- C++ -*-
//
// Package:     Bug
// Module:      string_allocator_void_bug
// 
// Description: check to see of basic_string uses an allocator of type
//              allocator<void> instead of allocator<char>
//
// Usage:
//     Some versions off DEC cxx compiler used incorrect allocator type.
//     If this fails to compiler, recompile using STRING_ALLOCATOR_VOID_BUG
//     flag set
//
// Author:      Chris D Jones
// Created:     Sat Oct 23 13:58:28 EDT 1999
// $Id: string_allocator_void_bug.cc,v 1.3 2001/01/16 22:25:23 cdj Exp $
//
// Revision history
//
// $Log: string_allocator_void_bug.cc,v $
// Revision 1.3  2001/01/16 22:25:23  cdj
// now closer to C++ standard
//
// Revision 1.2  2000/05/05 19:38:39  mkl
// get started on linux
//
// Revision 1.1  1999/10/23 20:57:06  cdj
// first submission
//
#include "Experiment/Experiment.h"

#include <string>

#if defined(STRING_ALLOCATOR_VOID_BUG)
#define ALLOCATOR_TYPE void
#else
#define ALLOCATOR_TYPE char
#endif

#if !defined(NO_STD_NAMESPACE_BUG)
namespace std {
typedef std::basic_string<char, 
#if !defined(USES_STRING_CHAR_TRAIT_BUG)
                  std::char_traits<char>,
#else
                  std::string_char_traits<char>,
#endif 
#if !defined(NON_STANDARD_ALLOCATOR_BUG)
                  std::allocator<ALLOCATOR_TYPE> > 
#else
#if defined(__APPLE__) || defined(__GNUG__)
                  alloc >
#endif
#endif
                 string;
}
#endif // NO_STD_NAMESPACE_BUG





