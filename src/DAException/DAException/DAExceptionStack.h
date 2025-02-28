// -*- C++ -*-
#if !defined(DAEXCEPTION_DAEXCEPTIONSTACK_H)
#define DAEXCEPTION_DAEXCEPTIONSTACK_H
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
// $Id: DAExceptionStack.h,v 1.1 2003/04/25 15:19:52 vk Exp $
//
// Revision history
//
// $Log: DAExceptionStack.h,v $
// Revision 1.1  2003/04/25 15:19:52  vk
// Reorginize package, add new stack class
//
//

// user includes
#include "Experiment/Experiment.h"
#include "Experiment/types.h"
#include "Experiment/report.h"
#include "DataHandler/DurableDataKey.h"
#include "DAException/DAExceptionStackManager.h"

// forward declarations
#include "C++Std/fwd_string.h"
#include "STLUtility/fwd_vector.h"
#include "STLUtility/fwd_map.h"
#include "STLUtility/fwd_list.h"
//#include <utility>

const char* const kDAExceptionStackFacilityString = "DAExceptionStack";

class DAExceptionStack 
{
  public:
      // constants, enums and typedefs
      typedef pair<string,int> StackPair;
      typedef STL_VECTOR( DataKey ) StackList;
      typedef STL_VECTOR( StackPair ) StackNames;
      
      // member functions
      static DAExceptionStack* instance();

      // stack keys (data written/accessing by Sinks/Processors)
      void add(const DataKey& key);
      void addDurable(const DataKey& key);
      void pop();
      int  size() const;

      // stack names (Processors/Sinks)
      void addName(const string& name);
      void popName();
      int  nameIndex() const;

      const StackList& stackList() const;
      const StackNames& stackNames() const;

  protected:
      DAExceptionStack();
      DAExceptionStack(const DAExceptionStack&); // stop default
      DAExceptionStack& operator= (const DAExceptionStack&); // stop default

  private:
      DurableDataKey m_durableKey;
      DAExceptionStackManager<DataKey> m_keyManager;
      DAExceptionStackManager<StackPair> m_pairManager;
};

#endif /* DAEXCEPTION_DAEXCEPTIONSTACK_H */
