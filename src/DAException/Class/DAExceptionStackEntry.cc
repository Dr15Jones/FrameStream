// -*- C++ -*-
//
// Package:     DAException
// Module:      DAExceptionStackEntry
//
//
// Description: add data accessing/written by processors/sinks into stack
//
// Usage:
//    <usage>
//
// Author:      Valentine Kouznetsov
// Created:     Wed Mar 12 15:31:00 EST 2003
// $Id: DAExceptionStackEntry.cc,v 1.1 2003/04/25 15:19:47 vk Exp $
//
// Revision history
//
// $Log: DAExceptionStackEntry.cc,v $
// Revision 1.1  2003/04/25 15:19:47  vk
// Reorginize package, add new stack class
//
//

// top level CLEO include
#include "Experiment/Experiment.h"

// user includes
#include "DAException/DAExceptionStackEntry.h"


void DAExceptionStackEntry::passToStack(DAExceptionStackDataKey const&iKey, bool iDurable) {
       m_stack = DAExceptionStack::instance();
       if(iDurable) {
              m_stack->addDurable(iKey);
       } else {
              m_stack->add(iKey);
       }
}

DAExceptionStackEntry::~DAExceptionStackEntry() {
       m_stack->pop();
}
