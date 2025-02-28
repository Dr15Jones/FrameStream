#if !defined(CPPSTD_FSTREAM_H)
#define CPPSTD_FSTREAM_H
// -*- C++ -*-
//
// Package:     <C++Std>
// Module:      fstream
// 
/**\class fstream fstream.h C++Std/fstream.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Fri Aug 24 09:03:11 EDT 2001
// $Id: fstream.h,v 1.1 2002/11/18 16:39:46 cleo3 Exp $
//
// Revision history
//
// $Log: fstream.h,v $
// Revision 1.1  2002/11/18 16:39:46  cleo3
// added fstream.h support
//
// Revision 1.1  2001/09/07 16:49:42  cleo3
// first submission
//

// system include files

#if defined(USING_IOSTREAM_H_BUG)
#include <fstream.h>
#else
#include <fstream>
#endif

#endif /* CPPSTD_FSTREAM_H */
