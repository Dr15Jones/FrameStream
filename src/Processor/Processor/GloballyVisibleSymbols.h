#if !defined(PROCESSOR_GLOBALLYVISIBLESYMBOLS_H)
#define PROCESSOR_GLOBALLYVISIBLESYMBOLS_H
// -*- C++ -*-
//
// Package:     <Processor>
// Module:      GloballyVisibleSymbols
// 
// Description: globally visible symbols for debugging with shared libraries
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Fri Jan 16 16:43:56 EST 1998
// $Id: GloballyVisibleSymbols.h,v 1.3 1998/09/08 19:06:27 mkl Exp $
//
// Revision history
//
// $Log: GloballyVisibleSymbols.h,v $
// Revision 1.3  1998/09/08 19:06:27  mkl
// removed superfluous volatile modifier
//
// Revision 1.2  1998/01/19 21:51:33  mkl
// changed procSel to procsel; same with prodsel
//
// Revision 1.1  1998/01/16 23:31:46  mkl
// added globally visible symbols to make debugging with shared libraries easier
//

extern "C" void procsel();
extern "C" void prodsel();

#endif /* PROCESSOR_GLOBALLYVISIBLESYMBOLS_H */
