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
void DAExceptionStack::addDurable(const DAExceptionStackDataKey& key) 
{
  DAExceptionStackDataKey newKey;
    m_durableKey.m_type = key.m_type;
    newKey.m_type = m_durableKey.m_type.data();
    if( key.m_usage) {
      m_durableKey.m_usage = key.m_usage;
      newKey.m_usage = m_durableKey.m_usage.data();
    } else {
      newKey.m_usage = nullptr;
    }
    if(key.m_production) {
      m_durableKey.m_production = key.m_production;
      newKey.m_production = m_durableKey.m_production.data();
    } else {
      newKey.m_production = nullptr;
    }
    m_keyManager.add(newKey);
}

void DAExceptionStack::add(const DAExceptionStackDataKey& key) 
{ 
  m_keyManager.add(key);
}


void DAExceptionStack::pop() 
{
  m_keyManager.pop(); 
}

void DAExceptionStack::addName(const std::string& name) 
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



