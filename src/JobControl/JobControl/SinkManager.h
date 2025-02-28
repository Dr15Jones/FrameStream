#if !defined(JOBCONTROL_SINKMANAGER_H)
#define JOBCONTROL_SINKMANAGER_H
// -*- C++ -*-
//
// Package:     JobControl
// Module:      SinkManager
// 
// Description: handles Sinks (internally) 
//
// Usage:  used by JobControl
//      
// Author:      Martin Lohner
// Created:     Tue Aug 19 14:53:30 EDT 1997
// $Id: SinkManager.h,v 1.11 2003/09/19 21:20:36 cdj Exp $
//
// Revision history
//
// $Log: SinkManager.h,v $
// Revision 1.11  2003/09/19 21:20:36  cdj
// changes needed for Path implementation
//
// Revision 1.10  1999/04/14 21:16:29  mkl
// ordered container used in Suez
//
// Revision 1.9  1999/03/11 22:02:45  mkl
// source out stream will activate stream; turn off superfluous warning for 'param' command
//
// Revision 1.8  1999/02/22 23:41:48  mkl
// setResult( string ) insteadof report in Commands; added NamingService and DefaultModule; fixed bug in stream command
//
// Revision 1.7  1999/01/21 00:02:04  mkl
// added minor convenience functions 'hasSource/Sink'
//
// Revision 1.6  1998/11/09 19:33:28  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
// Revision 1.5  1998/02/03 21:29:41  mkl
// switch over to STLUtility library
//
// Revision 1.4  1997/09/18 21:27:03  cdj
// changed Boolean to DABoolean
//
// Revision 1.3  1997/09/03 02:39:09  mkl
// restructuring suez libraries
//
// Revision 1.2  1997/08/20 07:27:18  mkl
// minor fixes to make cxx5.4-6 happy
//
// Revision 1.1  1997/08/20 06:23:45  mkl
// symmetrized sinks with sources in terms of user interface
//
//

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */             

// user include files
#include "CommandPattern/Module.h"
#include "JobControl/SinkCommand.h"
#include "CommandPattern/OrderedMap.h"

#include "SignalsSlots/SSSignal_1.h"
#include "SignalsSlots/SSSignal_2.h"

// STL include
#include <string>
#include "STLUtility/fwd_vector.h"

// forward declarations
class StreamSet;
class DataSinkBinder;

class SinkManager : public Module
{
      // friend classses and functions

   public:
      // constants, enums and typedefs
      typedef string SinkName;
      typedef string StreamName;

      // Constructors and destructor
      SinkManager( );
      virtual ~SinkManager();

      //signals
      //emitted just after sink added
      SSSignal_1<const string&> addedSink;

      //emitted just before sink info is deleted
      SSSignal_1<const string&> removingSink;
      SSSignal_1<const string&> removingSinkInUse;
      ///set second argument to false if should not remove Sink in question
      SSSignal_2<const string&, DABoolean&> requestToRemoveSink;

      // member functions

      // add DataSinkBinder
      DABoolean addSink( DataSinkBinder* iBinder );

      // mark all as in use
      DABoolean useSinks();

      DABoolean useSink( const DataSinkBinder* iBinder);
      
      // remove sinks
      DABoolean removeSinkInUse( const SinkName& iName );
      DABoolean removeSink( const SinkName& iName );
      DABoolean removeAllSinks();

      // binding streams to sink
      DABoolean bindStreamsToSink( const SinkName& iName, 
				   const StreamSet& streams );

      // const member functions

      DataSinkBinder* binderFor( const SinkName& iName ) const;

      STL_VECTOR(string) unusedSinks() const;

      // listings
      string list( const SinkName& iName ) const;
      string listAllSinks() const;

      // token stuff
      DABoolean hasSink( const SinkName& iName ) const;
      DABoolean checkIfSinkExists( const SinkName& iName ) const;
      DABoolean isUnused(const SinkName& iName ) const;

      // active stream stuff
      const StreamSet streamsToBeActivated() const;

      // static member functions

   protected:
      // protected member functions

      // protected const member functions

   private:
      // Constructors and destructor
      SinkManager( const SinkManager& );

      // assignment operator(s)
      const SinkManager& operator=( const SinkManager& );

      // private member functions

      // private const member functions
      string listSink( const SinkName& iName ) const;
      string listSinkInUse( const SinkName& iName ) const;

      // data members
      SinkCommand m_command;

      // internal data base for sinks (implemented as map)
      OrderedMap< SinkName, DataSinkBinder* >& m_sinkMap;
      OrderedMap< SinkName, DataSinkBinder* >& m_sinkInUseMap;

      // static data members

};

// inline function definitions

#endif /* JOBCONTROL_SINKMANAGER_H */
