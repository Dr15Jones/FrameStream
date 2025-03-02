// -*- C++ -*-
//
// Package:     DAException
// Module:      DAExceptionStackManager
//
 
// Description: Abstract class for the stack, basic functinonality add, pop, size
//
// Usage:
//    <usage>
//
// Author:      Valentine Kouznetsov
// Created:     Wed Mar 12 15:31:00 EST 2003
// $Id: DAExceptionStackManager.cc,v 1.1 2003/04/25 15:20:01 vk Exp $
//
// Revision history
//
// $Log: DAExceptionStackManager.cc,v $
// Revision 1.1  2003/04/25 15:20:01  vk
// Reorginize package, add new stack class
//
//

// top level CLEO include
#include "Experiment/Experiment.h"

// user includes
#include "DAException/DAExceptionStackManager.h"


//
// constructors and destructor
//
template < class T >
DAExceptionStackManager<T>::DAExceptionStackManager() : 
  m_index(0), m_stack()
{
}

//
// member functions
//
template < class T >
void DAExceptionStackManager<T>::add(const T& key) 
{ 
  if(m_stack.size()>m_index) m_stack[m_index]=key;
  else m_stack.push_back(key);

  // increment stack index
  m_index++;
}

template < class T >
void DAExceptionStackManager<T>::pop() 
{ 
  m_index--; 
}

template < class T >
int DAExceptionStackManager<T>::size() const 
{ 
  return m_index; 
}

template < class T >
const typename DAExceptionStackManager<T>::StackList&
DAExceptionStackManager<T>::stackList() const 
{ 
  return m_stack; 
}



