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
// $Id: DAExceptionBase.cc,v 1.2 2003/09/11 19:04:29 vk Exp $
//
// Revision history
//
// $Log: DAExceptionBase.cc,v $
// Revision 1.2  2003/09/11 19:04:29  vk
// Replace ends to have the same behaviour on OSF/Solaris/Linux
//
// Revision 1.1  2003/04/25 15:19:46  vk
// Reorginize package, add new stack class
//
//

// top level CLEO include
#include "Experiment/Experiment.h"

// system include files
#include <string>
#if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
#include <strstream.h>
#else
#include <sstream>
#endif

// user includes
#include "DAException/DAExceptionBase.h"
#include "DAException/DAExceptionStack.h"
#include "DAException/instantiate_DAExceptionStack.h"

//
// constructors and destructor
//
DAExceptionBase::DAExceptionBase()
  : m_size( DAExceptionStack::instance()->size() ) 
{ 
}

//
// member functions
//
const string 
DAExceptionBase::exceptionStack () const 
{
#if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
   strstream message;
#else
   stringstream message;
#endif
   DAExceptionStack* stack = DAExceptionStack::instance();
   if(stack) {

     DAExceptionStack::StackNames names = stack->stackNames();
     if(names.size()) 
     {
       message << "Starting from " << names[0].first << " we called extract for" << endl;
     } else {
       message << "no names of procs/sinks recorded into stack" << endl;
     }

     DAExceptionStack::StackList list = stack->stackList();
     if(!list.size()) 
     {
       message << "no extracts called" << endl;
     }

     for(int i=0; i<m_size; i++) {
       
       for(int j=1; j<names.size(); j++)
       {
         if(i==names[j].second)
         {
           message << " while in " << names[j].first << " we called extract for" << endl;
         }
       }
       
       message << "["<<i+1<<"] type \""<<(list[i]).type().name() <<"\""
               << " usage \""<<(list[i]).usage().value() <<"\""
               << " production \""<<(list[i]).production().value()<<"\"";
       if(0 != stack->size() && i == stack->size() -1) 
       {
           message <<" <== exception caught";	
       }
       if(i==m_size-1) 
       {
           message <<" <== exception occured";
       }
       message << endl;
     }


   } else {
     message << "There is no stack" << endl;
   }
   message << "\0" << flush;
   return message.str();
}

