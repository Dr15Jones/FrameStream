// -*- C++ -*-
//
// Package:     ToolBox
// Module:      T_operator_iostream
// 
// Description: Instantiate operator<<(iostream)
//
// Author:      Martin Lohner
// Created:     Tue Dec 8 18:20:23 EDT 1998
// $Id: T_IOoperator_string.cc,v 1.2 1999/10/30 12:36:47 cleo3 Exp $
//
// Revision history
//
// $Log: T_IOoperator_string.cc,v $
// Revision 1.2  1999/10/30 12:36:47  cleo3
// updated to work with cxx 6.2
//
// Revision 1.1  1998/12/09 00:14:39  mkl
// split STL_string.cc into three files which do one and only instantiation
// (else "multiply-defined symbols" link errors could occur when a user
// instantiated one piece, but need to pull in STL_string.o for another).
//
//

#include "Experiment/Experiment.h"

// system include files

// STL include files
#include <string>

#if !defined(OLD_CXX_STRING_CLASS_BUG)
#  pragma define_template basic_string< char >
#endif

#if ( defined(PRAGMA_TEMPLATE_INSTANTIATION_BUG) && defined(__DECCXX) && (!defined(USES_STRING_CHAR_TRAIT_BUG)) )
#  pragma define_template operator>><char, char_traits<char>, allocator<void> >
#  pragma define_template operator<<<char, char_traits<char>, allocator<void> >

#else
#if ( defined(NO_IMPLICIT_INSTANTIATION) && defined(__DECCXX) )

#if defined(STRING_ALLOCATOR_VOID_BUG)
#define ALLOCATOR_TYPE void
#else
#define ALLOCATOR_TYPE char
#endif
template ostream& 
std::operator <<(ostream&, 
		 const std::basic_string<char, 
		                         std::char_traits<char>, 
		                         std::allocator<ALLOCATOR_TYPE> >&);
template istream&
std::operator >>(istream&, 
		 std::basic_string<char, 
		                   std::char_traits<char>, 
		                   std::allocator<ALLOCATOR_TYPE> >&);
#endif
#endif /* (defined(PRAGMA_TEMPLATE_INSTANTIATION_BUG) && defined(__DECCXX)) */
