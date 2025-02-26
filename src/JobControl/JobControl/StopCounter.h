#if !defined(JOBCONTROL_STOPCOUNTER_H)
#define JOBCONTROL_STOPCOUNTER_H
// -*- C++ -*-
//
// Package:     <JobControl>
// Module:      StopCounter
// 
// Description: Smart counter for stops.
//
//              The idea here is to only allow counter operations,
//              if the current stop is a member of the counter's stream::type,
//              but the default is that the list is empty!
//
//              Implementation and Usage: A negative number means, keep going.
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Fri May  8 11:05:46 EDT 1998
// $Id: StopCounter.h,v 1.8 2000/01/17 21:30:20 mkl Exp $
//
// Revision history
//
// $Log: StopCounter.h,v $
// Revision 1.8  2000/01/17 21:30:20  mkl
// StopCounter: have to check for active streams as precaution AFTER streams are activated
//
// Revision 1.7  1999/06/18 19:21:12  mkl
// changed 'go 10' to be 10 events; 'go 10 any' goes 10 of any active stream
//
// Revision 1.6  1998/07/28 22:13:48  mkl
// change StopCounter from pass-by-value to pass-by-ref in event loop
//
// Revision 1.5  1998/07/28 15:37:02  mkl
// forward declare stl container
//
// Revision 1.4  1998/07/27 23:31:48  mkl
// skip command: need to process streams with higher or equal priority (which are not included in skip set
//
// Revision 1.3  1998/05/12 21:12:19  mkl
// make g++ happy: stl set
//
// Revision 1.2  1998/05/12 20:55:26  mkl
// allow more than one stream types for go command
//
// Revision 1.1  1998/05/08 22:16:56  mkl
// needed by fancier go command
//

// system include files

// user include files
#include "DataHandler/Stream.h"
#include "DataHandler/StreamSet.h"

// forward declarations

class StopCounter
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      StopCounter( long iCounter=-1 );
      ~StopCounter();
      //StopCounter( const StopCounter& ); // use default copy ctor

      // ---------- member functions ---------------------------
      void setSkipLogic( DABoolean skipOrNot );

      void addStream( const Stream::Type& iStream );
      void clearStreams();

      long& operator()( const Stream::Type& iStream );
      long& operator()();

      // ---------- const member functions ---------------------
      // depending on the skip member, returns if this stop should be 
      // skipped or processed
      DABoolean skipThisStop( const Stream::Type& iStream );

      DABoolean checkAllStreamsToBeActive( const StreamSet& iStreams ) const;

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------

      // ---------- assignment operator(s) ---------------------
      StopCounter( const StopCounter& );                  // stop default
      const StopCounter& operator=( const StopCounter& ); // stop default

      // ---------- private member functions -------------------
      DABoolean find( const Stream::Type iStream );

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      long m_counter, m_tempCounter;
      DABoolean m_skipLogic;  // is this a skip counter or a process counter
      StreamSet m_streams;
      
      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "JobControl/Template/StopCounter.cc"
//#endif

#endif /* JOBCONTROL_STOPCOUNTER_H */
