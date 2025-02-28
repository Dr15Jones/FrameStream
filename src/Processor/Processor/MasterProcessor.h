#if !defined(PROCESSOR_MASTERPROCESSOR_H)
#define PROCESSOR_MASTERPROCESSOR_H
// -*- C++ -*-
//
// Package:     Processor
// Module:      MasterProcessor
// 
// Description: Main Processor
//
// Usage:

// Author:       Martin  Lohner
// Created:     Tue Mar 18 15:48:09 EST 1997
// $Id: MasterProcessor.h,v 1.30 2003/09/19 19:35:42 cdj Exp $
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
#include "Processor/Processor.h"
#include "DataHandler/StreamSet.h"

#include "SignalsSlots/SSSignal_1.h"
#include "SignalsSlots/SSSignal_2.h"

// forward declarations
#include "C++Std/fwd_string.h"
#include "STLUtility/fwd_vector.h"
#include "STLUtility/fwd_map.h"
class Frame;
class FrameDeliverer;
class StreamSet;
class ProcessorCommand;

class MasterProcessor : public MultiLoader< Processor >, public Processor
{
      // friend classes and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      MasterProcessor( FrameDeliverer& iFrameDeliverer );
      virtual ~MasterProcessor();

      // member functions

      //signals
      SSSignal_1<const string&> addedProcessor;
      SSSignal_1<const string&> removingProcessor;
      ///set second argument to false if should not remove Processor in question
      SSSignal_2<const string&, DABoolean&> requestToRemoveProcessor;

      // standard functions for startup and shutdown (anal1, anal5 equiv)
      virtual void init( void );
      virtual void terminate( void );
      virtual void hist_book( HIHistoManager& );

      // all stream-based methods go through Actions! (e.g. event, beginRun)
      ActionBase::ActionResult executeActions( const Stream::Type&, Frame& );

      // register proxies of all newly created producers
      void registerProviders( DABoolean iForceReload = false );

      // const member functions

      // list of streams bound to actions
      const StreamSet streamsToBeActivated() const;

      // pattern for listings
      virtual string listAvailablePatternString() const { 
	 //return string( "Proc" ); 
	 return string( "" ); 
      }

      STL_VECTOR(string) loadedNames() const;

      // static member functions

   protected:
      // protected member functions

      // overriden Loader<> methods
      virtual void initialize( const string& iName, Processor& iProcessor );
      virtual void initializeTag( const string& iTag, Processor& iProcessor );
      virtual void finalize(   const string& iName, Processor& iProcessor );
      virtual DABoolean canUnload(const string& iName, Processor&);

      // protected const member functions

      // warning/error messages
      virtual string makeErrorMesg( const string& iName ) const;

   private:
      // Constructors and destructor
      MasterProcessor( const MasterProcessor& );    // stop default
      
      // assignment operator(s)
      const MasterProcessor& operator=( const MasterProcessor& ); // stop default

      // private member functions

      // private const member functions

      // data members
      ProcessorCommand& m_command;

      FrameDeliverer& m_frameDeliverer;

      // how to make processors (either static factory or dynamic loading!)

      // static data members

};

// inline function definitions


// -----------------------------------------------------------------
// Revision history
//
// $Log: MasterProcessor.h,v $
// Revision 1.30  2003/09/19 19:35:42  cdj
// added signals to communicate what Processors are available
//
// Revision 1.29  2003/03/14 20:10:44  vk
// Adjust Processor classes wrt to Loader/MultiLoader
//
// Revision 1.28  2002/08/16 15:46:39  cleo3
// replaced iostream.h with C++/iostream.h
//
// Revision 1.27  1999/10/08 21:44:36  mkl
// put in hooks for pattern searching in loading (if we ever decide to use it)
//
// Revision 1.26  1999/09/14 18:37:32  mkl
// print better message when loading processor as producer
//
// Revision 1.25  1999/09/06 22:21:34  mkl
// move to new histogramming interface
//
// Revision 1.24  1998/11/10 03:52:35  mkl
// unify producer/processor/module/source_format/sink_format commands
//
// Revision 1.23  1998/11/09 21:25:20  mkl
// loadable classes know their own factorySymbol string; improved user iface of ModuleCommand
//
// Revision 1.22  1998/11/09 19:34:46  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
// Revision 1.20  1998/09/08 19:37:58  mkl
// rename overloaded virtual function (renaming was in order anyways)
//
// Revision 1.19  1998/07/21 16:23:26  mkl
// register producer proxies AFTER source proxies; new ActionResult::kStopProcessLoop
//
// Revision 1.18  1998/06/23 23:01:01  mkl
// cleanup of LoadableInterface
//
// Revision 1.17  1998/06/17 18:16:50  mkl
// allow dynamic loading of source and sink formats
//
// Revision 1.16  1998/04/01 17:58:01  mkl
// switched to C++Std standard include area: fwd_string/istream/ostream
//
// Revision 1.15  1998/02/03 21:29:59  mkl
// switch over to STLUtility library
//
// Revision 1.14  1998/01/16 23:32:21  mkl
// added MasterProducer for selecting Producers at run time
//
// Revision 1.13  1997/10/07 04:15:25  mkl
// replaced HbookManager by HIHistoManager
//
// Revision 1.12  1997/09/18 21:29:05  cdj
// changed Boolean to DABoolean
//
// Revision 1.11  1997/09/10 01:45:46  mkl
// rearranged timing of init and terminate calls
//
// Revision 1.10  1997/09/05 22:33:54  mkl
// moved init/terminate to Producer; implemented hist_book routine
//
// Revision 1.9  1997/08/29 04:19:36  mkl
// bug flag name change
//
// Revision 1.8  1997/08/12 22:20:40  mkl
// added method to return streams bound to actions
//
// Revision 1.7  1997/07/22 05:21:05  mkl
// use factory method for statically linked processors
//
// Revision 1.6  1997/07/11 05:59:26  mkl
// // New <Package>/<File>.h structure
// // Modified so can also compile under cxx v5.5
//
// Revision 1.5  1997/07/01 03:16:55  mkl
// moved typedef map statements to .cc files
//
// Revision 1.4  1997/06/14 03:52:54  mkl
// replaced static function calls with pointers to member functions
//
// Revision 1.3  1997/06/03 18:39:56  mkl
// allow any stream to have actions
//
// Revision 1.2  1997/05/28 21:49:58  mkl
// beautifications
//
// Revision 1.1.1.1  1997/05/23 20:18:00  mkl
// imported processor sources
//
// Revision 1.3  1997/05/15 17:40:53  mkl
// MasterProcessor now contains a SharedObjectHandler. Added "processor
// reorder" command.
//
// Revision 1.2  1997/05/14 17:14:21  mkl
// added capability to load/unload shared objects.
//
// Revision 1.1  1997/03/27 06:53:49  mkl
// imported sources.

#endif /* PROCESSOR_MASTERPROCESSOR_H */
