// -*- C++ -*-
//
// Bug Name:    OSTREAM_IS_A_CLASS_BUG
// 
// Description: 
//     The C++ standard specifies the ostream (and istream) is
// actually the following type of typedef:
//
//	typedef basic_ostream<char, char_traits <char> > ostream ;
//
// Many compilers still define this as a class, which will confuse a
// forward declaration of ostream
//
// Existence:
//   g++: v2.7.2
//   cxx: all versions
//
// Author:      Simon Patton
// Created:     Tue Aug  26 20:10:42 EDT 1997
// $Id: ostream_is_a_class_bug.cc,v 1.3 2001/01/16 22:25:21 cdj Exp $
//
// Revision history
//
// $Log: ostream_is_a_class_bug.cc,v $
// Revision 1.3  2001/01/16 22:25:21  cdj
// now closer to C++ standard
//
// Revision 1.2  2000/05/05 19:38:38  mkl
// get started on linux
//
// Revision 1.1  1998/03/16 22:59:59  mkl
// Simon's bug code snipplets for bug/feature flags
//
//

#include "Experiment/Experiment.h"

#include <iostream.h>

#if defined(OSTREAM_IS_A_CLASS_BUG)
class ostream ;
#else
#if !defined(NO_STD_NAMESPACE_BUG)
namespace std {
#endif
template <class charT> class char_traits ;
template <class charT, class traits> class basic_ostream;
typedef basic_ostream<char, char_traits <char> > ostream;
#if !defined(NO_STD_NAMESPACE_BUG)
}
#endif
#endif // OSTREAM_IS_A_CLASS_BUG 


