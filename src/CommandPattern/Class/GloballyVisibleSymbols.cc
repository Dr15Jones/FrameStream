// -*- C++ -*-
//
// Package:     <CommandPattern>
// Module:      GloballyVisibleSymbols
// 
// Description: globally visible symbols used for debugging with
//              shared libraries
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Martin Lohner
// Created:     Tue Oct 27 16:44:28 EST 1998
// $Id: GloballyVisibleSymbols.cc,v 1.2 2003/03/18 19:47:21 vk Exp $
//
// Revision history
//
// $Log: GloballyVisibleSymbols.cc,v $
// Revision 1.2  2003/03/18 19:47:21  vk
// Add comment to allow gdb stop in modsel
//
// Revision 1.1  1998/11/09 19:30:57  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
//

#include "CommandPattern/GloballyVisibleSymbols.h"

void modsel()
{
  // allow debugger to stop in:        Suez> mod sel YourModule
}
