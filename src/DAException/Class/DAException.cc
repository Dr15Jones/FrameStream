// -*- C++ -*-
//
// Package:     DAException
// Module:      DAExceptionBase
//
 
// Description: Base class for exception mechanism
//
// Usage:
//    <usage>
//
// Author:      Valentine Kouznetsov
// Created:     Wed Mar 12 15:31:00 EST 2003
// $Id: DAException.cc,v 1.1 2003/04/25 15:19:45 vk Exp $
//
// Revision history
//
// $Log: DAException.cc,v $
// Revision 1.1  2003/04/25 15:19:45  vk
// Reorginize package, add new stack class
//
//

// top level CLEO include
#include "Experiment/Experiment.h"

// user includes
#include "DAException/DAException.h"

//
// constructors and destructor
//
DAException::DAException() 
  : m_message( "" ), m_ownMemory( false ) 
{
}

DAException::DAException(const char* iMessage, DABoolean iOwnMemory)
  : m_message( iMessage ),  m_ownMemory( iOwnMemory ) 
{
  if( true == m_ownMemory && 0 != iMessage ) {
    m_message = new char[strlen(iMessage)+1];
    strcpy( const_cast<char*>(m_message), iMessage );
  }
}

DAException::~DAException() 
{ 
  if( true == m_ownMemory ) { 
    delete [] const_cast<char*>(m_message); 
  } 
}

// copy ctor and assignment op are defined here to allow
// simpler derivation (no disallowing of copy ctor and ass.op. necessary
// in derived class)
DAException::DAException( const DAException& iRHS ) 
  : m_message(iRHS.m_message), m_ownMemory(iRHS.m_ownMemory)
{
  if( m_ownMemory) {
    m_message = new char[strlen(iRHS.m_message)+1];
    strcpy( const_cast<char*>(m_message), iRHS.m_message );
  }
}

const DAException& 
DAException::operator=( const DAException& iRHS ) 
{
  DAException temp(iRHS);
  swap(temp);
  return *this;
}

//
// member functions
//
const char*
DAException::what() const 
{ 
  return m_message; 
}

void DAException::swap( DAException& iFrom ) 
{
  DABoolean ownMemory = m_ownMemory ;
  m_ownMemory = iFrom.m_ownMemory;
  iFrom.m_ownMemory = ownMemory;

  const char* message = m_message;
  m_message = iFrom.m_message;
  iFrom.m_message = message;
}
