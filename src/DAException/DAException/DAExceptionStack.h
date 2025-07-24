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
//#include "DataHandler/DurableDataKey.h"
#include "DAException/DAExceptionStackManager.h"

// forward declarations
#include <string>
#include <vector>
#include <map>
#include <list>
//#include <utility>

const char* const kDAExceptionStackFacilityString = "DAExceptionStack";

struct DAExceptionStackDataKey {
    template<typename T>
    static DAExceptionStackDataKey from(T const& iKey) {
        DAExceptionStackDataKey to;
        to.m_type = iKey.type().name();
        to.m_usage = iKey.usage().value();
        to.m_production = iKey.production().value();
        return to;
    }
    const char *m_type;
    const char *m_usage;
    const char *m_production;
};
struct DAExceptionStackDurableDataKey {
    std::string m_type;
    std::string m_usage;
    std::string m_production;
};

class DAExceptionStack
{
  public:
      // constants, enums and typedefs
      typedef std::pair<std::string,int> StackPair;
      typedef std::vector< DAExceptionStackDataKey > StackList;
      typedef std::vector< StackPair > StackNames;
      
      // member functions
      static DAExceptionStack* instance();

      // stack keys (data written/accessing by Sinks/Processors)
      template<typename TKey>
      void add(const TKey& key) {
          add(DAExceptionStackDataKey::from(key));
      }
      template<typename TKey>
      void addDurable(const TKey& key) {
          addDurable(DAExceptionStackDataKey::from(key));
      }

      void add(const DAExceptionStackDataKey& key);
      void addDurable(const DAExceptionStackDataKey& key);

      void pop();
      int  size() const;

      // stack names (Processors/Sinks)
      void addName(const std::string& name);
      void popName();
      int  nameIndex() const;

      const StackList& stackList() const;
      const StackNames& stackNames() const;

  protected:
      DAExceptionStack();
      DAExceptionStack(const DAExceptionStack&) = delete; // stop default
      DAExceptionStack& operator= (const DAExceptionStack&) = delete; // stop default

  private:
      DAExceptionStackDurableDataKey m_durableKey;
      DAExceptionStackManager<DAExceptionStackDataKey> m_keyManager;
      DAExceptionStackManager<StackPair> m_pairManager;
};

#endif /* DAEXCEPTION_DAEXCEPTIONSTACK_H */
