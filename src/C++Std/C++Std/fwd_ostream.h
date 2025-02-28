#if !defined(CPPSTD_FWD_OSTREAM_H)
#define CPPSTD_FWD_OSTREAM_H
// -*- C++ -*-
//
// Package:     C++Std
// Module:      fwd_ostream
// 
// Description: Handle the forward declaration of the C++ ostream
//
// Usage:
//    include this file wherever you'd normally forward declare an ostream
//
// Author:      Simon Patton
// Created:     Thu Jul  3 14:44:35 EDT 1997
// $Id: fwd_ostream.h,v 1.2 2001/09/07 16:50:33 cleo3 Exp $
//
// Revision history
//
// $Log: fwd_ostream.h,v $
// Revision 1.2  2001/09/07 16:50:33  cleo3
// updated for Solaris 8
//
// Revision 1.1.1.1  1998/04/01 15:12:21  mkl
// imported sources
//
// Revision 1.1  1997/08/14 11:46:39  sjp
// Mods to run under CW Pro 1
//

#if !defined(USING_IOSTREAM_H_BUG)

#if !defined(NO_IOSFWD_BUG)
#include <iosfwd>
#else
#include <ostream>
#endif /* NO_IOSFWD_BUG */

#else

#if defined(OSTREAM_IS_A_CLASS_BUG)
class ostream ;
#else
template <class charT> class char_traits ;
template <class charT, class traits> class basic_ostream;
typedef basic_ostream<char, char_traits <char> > ostream;
#endif /* OSTREAM_IS_A_CLASS_BUG */

#endif /* CPPSTD_FWD_OSTREAM_H */

#endif /* USING_IOSTREAM_H_BUG */

