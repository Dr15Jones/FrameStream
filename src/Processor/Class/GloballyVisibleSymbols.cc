// -*- C++ -*-
//
// Package:     <Processor>
// Module:      GloballyVisibleSymbols
// 
// Description: globally visible symbols used for debugging with
//              shared libraries
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Martin Lohner
// Created:     Fri Jan 16 16:44:28 EST 1998
// $Id: GloballyVisibleSymbols.cc,v 1.3 1998/09/08 19:06:25 mkl Exp $
//
// Revision history
//
// $Log: GloballyVisibleSymbols.cc,v $
// Revision 1.3  1998/09/08 19:06:25  mkl
// removed superfluous volatile modifier
//
// Revision 1.2  1998/01/19 21:51:41  mkl
// changed procSel to procsel; same with prodsel
//
// Revision 1.1  1998/01/16 23:31:38  mkl
// added globally visible symbols to make debugging with shared libraries easier
//

#include "Processor/GloballyVisibleSymbols.h"

void procsel()
{
}

void prodsel()
{
}
