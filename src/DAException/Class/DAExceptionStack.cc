// -*- C++ -*-
//
// Package:     DAException
// Module:      DAExceptionStack
//
// Description: singleton class of DAExceptionStack
//
// Usage:
//    <usage>
//
// Author:      Valentine Kouznetsov
// Created:     Wed Mar 12 15:31:00 EST 2003
// $Id: DAExceptionStack.cc,v 1.1 2003/04/25 15:19:46 vk Exp $
//
// Revision history
//
// $Log: DAExceptionStack.cc,v $
// Revision 1.1  2003/04/25 15:19:46  vk
// Reorginize package, add new stack class
//
//

// top level CLEO include
#include "Experiment/Experiment.h"

// user includes
#include "DAException/DAExceptionStack.h"
#include "DAException/DAExceptionStackManager.h"
#include "DataHandler/DataKey.h"

//
// constructors and destructor
//
DAExceptionStack::DAExceptionStack() : 
  m_durableKey()
{
}

// We skip implementation of this member function in a class
// to avoid inlinening and make static instance possible.
DAExceptionStack* DAExceptionStack::instance() 
{
  static DAExceptionStack s_this;
  return &s_this;
}


//
// member functions
//
void DAExceptionStack::addDurable(const DataKey& key) 
{
  m_durableKey=key; 
  m_keyManager.add(m_durableKey);
}

void DAExceptionStack::add(const DataKey& key) 
{ 
  m_keyManager.add(key);
}


void DAExceptionStack::pop() 
{
  m_keyManager.pop(); 
}

void DAExceptionStack::addName(const string& name) 
{ 
  m_pairManager.add(make_pair(name,this->size()));
}

void DAExceptionStack::popName() 
{ 
  m_pairManager.pop();
}

int DAExceptionStack::size() const 
{ 
  return m_keyManager.size();
}

int DAExceptionStack::nameIndex() const 
{ 
  return m_pairManager.size();
}

const DAExceptionStack::StackList&
DAExceptionStack::stackList() const 
{ 
  return m_keyManager.stackList();
}

const DAExceptionStack::StackNames&
DAExceptionStack::stackNames() const 
{ 
  return m_pairManager.stackList();
}



