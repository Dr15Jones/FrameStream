// -*- C++ -*-
//
// Package:     DAException
// Module:      DAExceptionStackNameEntry
//
//
// Description: Add names of processors/sinks into stack
//
// Usage:
//    <usage>
//
// Author:      Valentine Kouznetsov
// Created:     Wed Mar 12 15:31:00 EST 2003
// $Id: DAExceptionStackNameEntry.cc,v 1.1 2003/04/25 15:19:48 vk Exp $
//
// Revision history
//
// $Log: DAExceptionStackNameEntry.cc,v $
// Revision 1.1  2003/04/25 15:19:48  vk
// Reorginize package, add new stack class
//
//

// top level CLEO include
#include "Experiment/Experiment.h"

// user includes
#include "DAException/DAExceptionStackNameEntry.h"

//
// constructors and destructor
//
DAExceptionStackNameEntry::DAExceptionStackNameEntry(const string& name) :
       m_stack( DAExceptionStack::instance() )
{
       m_stack->addName(name);
}

DAExceptionStackNameEntry::~DAExceptionStackNameEntry() {
       m_stack->popName();
}
