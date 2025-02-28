#if !defined(DAEXCEPTION_DAEXCEPTIONSTACKNAMEENTRY_H)
#define DAEXCEPTION_DAEXCEPTIONSTACKNAMEENTRY_H
//
// Package:     DAException
// Module:      DAExceptionStackNameEntry
//
//
// Description: DAExceptionStackNameEntry adds names of processors/sinks into the stack
//
// Usage:
//    <usage>
//
// Author:      Valentine Kouznetsov
// Created:     Wed Mar 12 15:31:00 EST 2003
// $Id: DAExceptionStackNameEntry.h,v 1.1 2003/04/25 15:19:54 vk Exp $
//
// Revision history
//
// $Log: DAExceptionStackNameEntry.h,v $
// Revision 1.1  2003/04/25 15:19:54  vk
// Reorginize package, add new stack class
//
//

// user includes
#include "Experiment/Experiment.h"
#include "Experiment/types.h"
#include "Experiment/report.h"
#include "DAException/DAExceptionStack.h"

const char* const kDAExceptionStackNameEntryFacilityString = "DAExceptionStackNameEntry";

class DAExceptionStackNameEntry
{
  public:
     DAExceptionStackNameEntry(const string& name);
     ~DAExceptionStackNameEntry();

   private:
      DAExceptionStackNameEntry(const DAExceptionStackNameEntry&); // stop default
      DAExceptionStackNameEntry& operator= (const DAExceptionStackNameEntry&); // stop default
      DAExceptionStack* m_stack;
};

#endif /* DAEXCEPTION_DAEXCEPTIONSTACKNAMEENTRY_H */
