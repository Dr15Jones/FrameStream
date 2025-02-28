// -*- C++ -*-
#if !defined(DAEXCEPTION_DAEXCEPTIONSTACKMANAGER_H)
#define DAEXCEPTION_DAEXCEPTIONSTACKMANAGER_H
//
// Package:     DAException
// Module:      DAExceptionStackManager
//
 
// Description: Abstract class DAExceptionStackManager
//
// Usage:
//    <usage>
//
// Author:      Valentine Kouznetsov
// Created:     Wed Mar 12 15:31:00 EST 2003
// $Id: DAExceptionStackManager.h,v 1.1 2003/04/25 15:19:54 vk Exp $
//
// Revision history
//
// $Log: DAExceptionStackManager.h,v $
// Revision 1.1  2003/04/25 15:19:54  vk
// Reorginize package, add new stack class
//
//

// user includes
#include "Experiment/Experiment.h"
#include "Experiment/types.h"
#include "Experiment/report.h"

// forward declarations
#include "C++Std/fwd_string.h"
#include "STLUtility/fwd_vector.h"
#include "STLUtility/fwd_map.h"
#include "STLUtility/fwd_list.h"

const char* const kDAExceptionStackManagerFacilityString = "DAExceptionStackManager";

template < class T >
class DAExceptionStackManager 
{
  public:
      DAExceptionStackManager();

      // constants, enums and typedefs
      typedef STL_VECTOR( T ) StackList;
      
      // stack keys (data written/accessing by Sinks/Processors)
      void add(const T& key);
      void pop();
      int  size() const;

      const StackList& stackList() const;

  protected:
      //DAExceptionStackManager(const DAExceptionStackManager&); // stop default
      //DAExceptionStackManager& operator= (const DAExceptionStackManager&); // stop default

  private:
      int m_index;
      StackList m_stack;
};

// Uncomment the following lines, if your class is templated
// and has an implementation file (in the Template directory)
#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
#include "DAException/Template/DAExceptionStackManager.cc"
#endif

#endif /* DAEXCEPTION_DAEXCEPTIONSTACKMANAGER_H */
