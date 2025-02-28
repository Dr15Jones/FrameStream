#if !defined(PROCESSOR_MASTERPRODUCER_H)
#define PROCESSOR_MASTERPRODUCER_H
// -*- C++ -*-
//
// Package:     Processor
// Module:      MasterProducer
// 
// Description: Main Producer
//
// Usage:

// Author:      Martin  Lohner
// Created:     Thu Jan 15 15:48:09 EST 1998
// $Id: MasterProducer.h,v 1.16 2003/03/14 20:10:44 vk Exp $
//
// Revision history (at end of file)
//

// system include files
#include "C++Std/iostream.h"
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "CommandPattern/MultiLoader.h"
#include "Processor/Producer.h"

// forward declarations
#include "C++Std/fwd_string.h"
#include "STLUtility/fwd_vector.h"
#include "STLUtility/fwd_map.h"
class FrameDeliverer;
class StreamSet;
class ProducerCommand;

class MasterProducer : public MultiLoader< Producer >, public Producer
{
      // friend classses and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      MasterProducer( FrameDeliverer& iFrameDeliverer );
      virtual ~MasterProducer();

      // member functions

      // standard functions for startup and shutdown (anal1, anal5 equiv)
      virtual void init( void );
      virtual void terminate( void );
      virtual void hist_book( HIHistoManager& );

      // register proxies of all newly created producers
      void registerProviders( DABoolean iForceReload = false );

      // const member functions

      // list of streams bound to actions
      const StreamSet streamsToBeActivated() const;

      // pattern for listings
      virtual string listAvailablePatternString() const { 
	 //return string( "Pro[cd]" ); 
	 return string( "" ); 
      }

      // static member functions

   protected:
      // protected member functions

      // overriden Loader<> methods
      virtual void initialize( const string& iName, Producer& iProducer );
      virtual void initializeTag( const string& iTag, Producer& iProducer );
      virtual void finalize(   const string& iName, Producer& iProducer );

      // protected const member functions

      // warning/error message
      virtual string makeErrorMesg( const string& iName ) const;
      virtual string loadingAsSuperClassMesg( const string& iName ) const;

   private:
      // Constructors and destructor
      MasterProducer( const MasterProducer& );    // stop default
      
      // assignment operator(s)
      const MasterProducer& operator=( const MasterProducer& ); // stop default

      // private member functions

      // data members
      ProducerCommand& m_command;

      FrameDeliverer& m_frameDeliverer;

      // static data members

};

// inline function definitions


// ---------------------------------------------------------------
// Revision history
//
// $Log: MasterProducer.h,v $
// Revision 1.16  2003/03/14 20:10:44  vk
// Adjust Processor classes wrt to Loader/MultiLoader
//
// Revision 1.15  2002/08/16 15:46:40  cleo3
// replaced iostream.h with C++/iostream.h
//
// Revision 1.14  1999/10/08 21:44:37  mkl
// put in hooks for pattern searching in loading (if we ever decide to use it)
//
// Revision 1.13  1999/09/14 18:37:32  mkl
// print better message when loading processor as producer
//
// Revision 1.12  1999/09/06 22:21:34  mkl
// move to new histogramming interface
//
// Revision 1.11  1998/11/10 03:52:35  mkl
// unify producer/processor/module/source_format/sink_format commands
//
// Revision 1.10  1998/11/09 21:25:21  mkl
// loadable classes know their own factorySymbol string; improved user iface of ModuleCommand
//
// Revision 1.9  1998/11/09 19:34:47  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
// Revision 1.7  1998/09/08 19:37:58  mkl
// rename overloaded virtual function (renaming was in order anyways)
//
// Revision 1.6  1998/07/21 16:23:26  mkl
// register producer proxies AFTER source proxies; new ActionResult::kStopProcessLoop
//
// Revision 1.5  1998/06/23 23:01:01  mkl
// cleanup of LoadableInterface
//
// Revision 1.4  1998/06/17 18:16:51  mkl
// allow dynamic loading of source and sink formats
//
// Revision 1.3  1998/04/01 17:58:02  mkl
// switched to C++Std standard include area: fwd_string/istream/ostream
//
// Revision 1.2  1998/02/03 21:29:59  mkl
// switch over to STLUtility library
//
// Revision 1.1  1998/01/16 23:32:22  mkl
// added MasterProducer for selecting Producers at run time
//
#endif /* PROCESSOR_MASTERPRODUCER_H */
