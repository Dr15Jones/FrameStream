#if !defined(CPPSTD_FWD_ISTREAM_H)
#define CPPSTD_FWD_ISTREAM_H
// -*- C++ -*-
//
// Package:     C++Std
// Module:      fwd_istream
// 
// Description: Handle the forward declaration of the C++ istream
//
// Usage:
//    include this file wherever you'd normally forward declare an istream
//
// Author:      Simon Patton
// Created:     Thu Jul  3 14:44:35 EDT 1997
// $Id: fwd_istream.h,v 1.2 2001/09/07 16:50:33 cleo3 Exp $
//
// Revision history
//
// $Log: fwd_istream.h,v $
// Revision 1.2  2001/09/07 16:50:33  cleo3
// updated for Solaris 8
//
// Revision 1.1.1.1  1998/04/01 15:12:18  mkl
// imported sources
//
// Revision 1.1  1997/08/14 11:46:37  sjp
// Mods to run under CW Pro 1
//

#if !defined(USING_IOSTREAM_H_BUG)

#if !defined(NO_IOSFWD_BUG)
#include <iosfwd>
#else
#include <istream>
#endif /* NO_IOSFWD_BUG */

#else

#if defined(ISTREAM_IS_A_CLASS_BUG)
class istream ;
#else
template <class charT> class char_traits ;
template <class charT, class traits> class basic_istream;
typedef basic_istream<char, char_traits <char> > istream;
#endif /* ISTREAM_IS_A_CLASS_BUG */

#endif /* CPPSTD_FWD_ISTREAM_H */

#endif /* USING_IOSTREAM_H_BUG */
