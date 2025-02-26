#if !defined(JobControl_GLOBALLYVISIBLESYMBOLS_H)
#define JobControl_GLOBALLYVISIBLESYMBOLS_H
// -*- C++ -*-
//
// Package:     <JobControl>
// Module:      GloballyVisibleSymbols
// 
// Description: globally visible symbols for debugging with shared libraries
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Mon June 15 16:43:56 EST 1998
// $Id: GloballyVisibleSymbols.h,v 1.2 1998/09/08 19:24:14 mkl Exp $
//
// Revision history
//
// $Log: GloballyVisibleSymbols.h,v $
// Revision 1.2  1998/09/08 19:24:14  mkl
// clean up for warning messages from cxx 6.0
//
// Revision 1.1  1998/06/17 18:18:21  mkl
// allow dynamic loading of source and sink formats
//
//

extern "C" void formatsel();

#endif /* JobControl_GLOBALLYVISIBLESYMBOLS_H */
