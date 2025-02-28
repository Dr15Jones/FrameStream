#if !defined(DAEXCEPTION_DAEXCEPTIONSTACKENTRY_H)
#define DAEXCEPTION_DAEXCEPTIONSTACKENTRY_H
//
// Package:     DAException
// Module:      DAExceptionStackEntry
//
//
// Description: DAExceptionStackEntry adds entry 
//              (data accessing/written by procs/sinks) to the stack
//
// Usage:
//    <usage>
//
// Author:      Valentine Kouznetsov
// Created:     Wed Mar 12 15:31:00 EST 2003
// $Id: DAExceptionStackEntry.h,v 1.1 2003/04/25 15:19:53 vk Exp $
//
// Revision history
//
// $Log: DAExceptionStackEntry.h,v $
// Revision 1.1  2003/04/25 15:19:53  vk
// Reorginize package, add new stack class
//
//

// user includes
#include "Experiment/Experiment.h"
#include "Experiment/types.h"
#include "Experiment/report.h"
#include "DataHandler/DataKey.h"
#include "DAException/DAExceptionStack.h"

const char* const kDAExceptionStackEntryFacilityString = "DAExceptionStackEntry";

class DAExceptionStackEntry
{
  public:
     enum UseDurable {kUseDurable};
     DAExceptionStackEntry(const DataKey& key);
     DAExceptionStackEntry(const DataKey& key, UseDurable);
     ~DAExceptionStackEntry();

   private:
      DAExceptionStackEntry(const DAExceptionStackEntry&); // stop default
      DAExceptionStackEntry& operator= (const DAExceptionStackEntry&); // stop default
      DAExceptionStack* m_stack;
};

#endif /* DAEXCEPTION_DAEXCEPTIONSTACKENTRY_H */
