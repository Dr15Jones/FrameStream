// -*- C++ -*-
//
// Bug Name:    ISTREAM_IS_A_CLASS_BUG
// 
// Description: 
//     The C++ standard specifics the istream (and ostream) is
// actually the following type of typedef:
//
//	typedef basic_istream<char, char_traits <char> > istream ;
//
// Many compilers still define this as a class, which will confuse a
// forward declaration of istream
//
// Existence:
//   g++: v2.7.2
//   cxx: all versions
//
// Author:      Simon Patton
// Created:     Tue Aug  26 21:13:76 EDT 1997
// $Id: istream_is_a_class_bug.cc,v 1.3 2001/01/16 22:25:17 cdj Exp $
//
// Revision history
//
// $Log: istream_is_a_class_bug.cc,v $
// Revision 1.3  2001/01/16 22:25:17  cdj
// now closer to C++ standard
//
// Revision 1.2  2000/05/05 19:38:37  mkl
// get started on linux
//
// Revision 1.1  1998/03/16 22:59:53  mkl
// Simon's bug code snipplets for bug/feature flags
//
//

#include "Experiment/Experiment.h"

#include <iostream.h>

#if defined(ISTREAM_IS_A_CLASS_BUG)
class istream ;
#else
#if !defined(NO_STD_NAMESPACE_BUG)
namespace std {
#endif
template <class charT> class char_traits ;
template <class charT, class traits> class basic_istream;
typedef basic_istream<char, char_traits <char> > istream;
#if !defined(NO_STD_NAMESPACE_BUG)
}
#endif
#endif // ISTREAM_IS_A_CLASS_BUG 


