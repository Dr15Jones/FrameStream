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

//
// constructors and destructor
//
DAExceptionStackEntry::DAExceptionStackEntry(const DataKey& key) :
       m_stack( DAExceptionStack::instance() )
{
       m_stack->add(key);
}

DAExceptionStackEntry::DAExceptionStackEntry(const DataKey& key, UseDurable) :
       m_stack( DAExceptionStack::instance() )
{
       m_stack->addDurable(key);
}

DAExceptionStackEntry::~DAExceptionStackEntry() {
       m_stack->pop();
}
