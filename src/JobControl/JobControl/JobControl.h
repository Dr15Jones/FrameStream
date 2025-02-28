#if !defined(JOBCONTROL_JOBCONTROL_H)
#define JOBCONTROL_JOBCONTROL_H
// -*- C++ -*-
//
// Package:     JobControl
// Module:      JobControl
// 
// Description: among other things base class for CLI and GUI
//              implemented as singleton, but instance() method is
//              implemented in subclasses CLI and GUI!
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Tue Mar 18 15:47:12 EST 1997
// $Id: JobControl.h,v 1.48 2003/11/21 20:09:18 cdj Exp $
//
// Revision history (at end of file)
//

// system include files

// user include files
#include "CommandPattern/LoaderModule.h"
#include "DataHandler/Stream.h"
#include "JobControl/StopCounter.h"
#include "HistogramInterface/HIHistoManager.h"

// commands
#include "JobControl/StartCommand.h"
#include "JobControl/SkipCommand.h"
#include "JobControl/GotoCommand.h"
#include "JobControl/ReprocessCommand.h"
#include "JobControl/ParameterCommand.h"
#include "JobControl/InteractCommand.h"
#include "JobControl/ExceptionControlCommand.h"

// forward declarations
class FrameDeliverer;
class FrameStorer;
class FrameLogger;

// "static" modules
class SummaryModule;
class MasterProcessor;
class MasterProducer;
class SourceManager;
class SinkManager;
class SourceFormatMap;
class SinkFormatMap;
class PathModule;
class DefaultModule;

class JobControl : public LoaderModule
{
      // friend classses and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      virtual ~JobControl( void );

      // member functions

      // what do to when event/go command occurs
      DABoolean eventLoop( StopCounter& iCounter );
      DABoolean eventLoopSetup();
      DABoolean goTo( int runNumber, int eventNumber, const StreamType& iStream );
      DABoolean gotoNextStop( Stream::Type& oCurrentStop, DABoolean& oNoError );
      DABoolean processStop();


      // access methods
      FrameDeliverer& frameDeliverer( void );

      MasterProcessor& masterProcessor( void );
      MasterProducer&  masterProducer( void );
      SourceManager&   sourceManager( void );
      SinkManager&     sinkManager( void );
      SourceFormatMap& sourceFormats( void );
      SinkFormatMap&   sinkFormats( void );
      DefaultModule&   defaultModule( void );

      // FrameLogger
      void initLogger( FrameLogger& logger );
      void finalizeLogger( FrameLogger& logger );

      // for external setting/loading of HistogramManager
      void setHistogramManager( HIHistoManager* iHistoM );
      HIHistoManager* histogramManagerP();

      // switch on/off exception handling in event loop
      void setContinueEventLoopAfterException( DABoolean iFlag );

      // choose whether to delete sources when they reach their end
      void setDoDeleteSourceAtEnd( DABoolean iFlag );

      // const member functions

      // access methods
      const FrameDeliverer& frameDeliverer( void ) const;

      const MasterProcessor& masterProcessor( void ) const;
      const MasterProducer& masterProducer( void ) const;
      const SourceManager& sourceManager( void ) const;
      const SinkManager& sinkManager( void ) const;
      const SourceFormatMap& sourceFormats( void ) const;
      const SinkFormatMap&   sinkFormats( void ) const;
      const DefaultModule&   defaultModule( void ) const;

      const HIHistoManager* histogramManagerP() const;
      DABoolean isHistogramManagerLocked() const;

      DABoolean continueEventLoopAfterException() const;
      DABoolean doDeleteSourceAtEnd() const { return m_doDeleteSourceAtEnd;}

      // static member functions
      static JobControl* instance( void );
      static void destroy( void );

   protected:
      // protected member functions
      JobControl( void );

      // protected const member functions

      // static data members
      // either CLI or GUI subclasses have to have access
      static JobControl* m_instance;

   private:
      // Constructors and destructor
      JobControl( const JobControl& );

      // assignment operator(s)
      const JobControl& operator=( const JobControl& );

      // private member functions
      DABoolean deleteSourceAtEnd( void );

      // private const member functions

      // ---------- data members ---------------
      
      // frame stuff
      FrameDeliverer& m_frameDeliverer;

      // "static" modules
      SummaryModule&    m_summaryM;

      SourceFormatMap&  m_sourceFM;
      SinkFormatMap&    m_sinkFM;
      SourceManager&    m_sourceM;
      SinkManager&      m_sinkM;

      MasterProducer&   m_producerM;
      MasterProcessor&  m_processorM;

      PathModule&       m_pathM;

      DefaultModule&    m_defaultM;


      // commands
      StartCommand            m_startCommand;
      StartCommand            m_nextStopsCommand;
      SkipCommand             m_skipCommand;
      GotoCommand             m_gotoCommand;
      ReprocessCommand        m_reprocessCommand;
      ParameterCommand        m_parameterCommand;
      InteractCommand         m_interactCommand;
      ExceptionControlCommand m_exceptionControlCommand;

      // externally settable modules 
      // (will be replaced by JobContext lookup service)

      // Histogram stuff
      HIHistoManager* m_histoM;
      HIHistoManager* m_defaultHistoM;
      DABoolean m_histoLockedIn;

      // certain low-level internal parameters
      DABoolean m_alreadyAtStop;
      DABoolean m_continueEventLoopAfterException;
      DABoolean m_doDeleteSourceAtEnd;

      // static data members

};

// inline function definitions

// Revision history
//
// $Log: JobControl.h,v $
// Revision 1.48  2003/11/21 20:09:18  cdj
// goto command now takes an optional argument that sets the Record type (default is event if event#> 0 else beginrun)
//
// Revision 1.47  2003/09/19 21:20:35  cdj
// changes needed for Path implementation
//
// Revision 1.46  2001/12/18 21:51:47  cdj
// go command now returns a TCL ERROR if something went wrong
//
// Revision 1.45  2000/03/17 15:37:31  cdj
// Can now set whether sources are deleted when they reach their end.  Needed for FrameIterate
//
// Revision 1.44  2000/03/01 00:08:55  mkl
// control if should continue event loop in case of DataAccess Exceptions: exception command
//
// Revision 1.43  2000/02/29 17:53:53  mkl
// change skip and goto commands to properly work as expected: skip won't write nor process; goto and subsequent go will properly process the run/event in question
//
// Revision 1.42  1999/12/15 20:28:55  mkl
// delete processors/producers before histogram module
//
// Revision 1.41  1999/09/06 22:20:15  mkl
// move to new histogramming interface
//
// Revision 1.40  1999/06/04 18:05:49  mkl
// fix up processStop() function to allow skimming
//
// Revision 1.39.2.2  1999/05/28 21:44:54  billm
// Fixed a ptr bug and removed useless HistogramManager files.
//
// Revision 1.39.2.1  1999/05/21 04:18:36  billm
// Now compatible with new histo interface.
//
// Revision 1.39  1999/03/15 19:14:23  mkl
// InteractCommand
//
// Revision 1.38  1999/02/22 23:41:47  mkl
// setResult( string ) insteadof report in Commands; added NamingService and DefaultModule; fixed bug in stream command
//
// Revision 1.37  1998/11/21 05:09:08  mkl
// this is scary: order of library destruction matters on solaris: first delete all processors, then all producers, then source formats etc
//
// Revision 1.36  1998/11/20 07:11:30  mkl
// HistogramModule now dynamically loaded
//
// Revision 1.35  1998/11/10 19:55:09  mkl
// bug fix: delete source/sink-formats before source/sink-manager
//
// Revision 1.34  1998/11/09 19:33:27  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
// Revision 1.33  1998/09/22 15:48:42  mkl
// use bkh's new FrameLogger
//
// Revision 1.32  1998/07/29 20:06:53  mkl
// new summary command implemented
//
// Revision 1.31  1998/07/28 22:13:47  mkl
// change StopCounter from pass-by-value to pass-by-ref in event loop
//
// Revision 1.30  1998/07/27 23:31:47  mkl
// skip command: need to process streams with higher or equal priority (which are not included in skip set
//
// Revision 1.29  1998/07/25 16:10:12  mkl
// add static linking of sources/sinks
//
// Revision 1.28  1998/07/13 22:22:10  mkl
// added skip command
//
// Revision 1.27  1998/06/17 18:18:22  mkl
// allow dynamic loading of source and sink formats
//
// Revision 1.26  1998/05/12 20:00:19  mkl
// new histogram command: for now can only set filename
//
// Revision 1.25  1998/05/09 20:28:20  mkl
// get rid of NextStopsCommand
//
// Revision 1.24  1998/05/08 22:14:01  mkl
// deprecated nextstop in favor of fancier go command
//
// Revision 1.23  1998/04/01 19:43:19  mkl
// added Chris' BlankRecordDelivery handling
//
// Revision 1.22  1998/03/28 20:16:06  mkl
// do implicit bind of Parameter/Command to Module
//
// Revision 1.21  1998/03/13 03:55:48  mkl
// moved all commands from CommandLineInterface to JobControl where they belong
//
// Revision 1.20  1998/02/03 21:29:40  mkl
// switch over to STLUtility library
//
// Revision 1.19  1998/01/23 05:09:34  mkl
// CompositeDelivery, RawData, and ProxyExample are now DL producers
//
// Revision 1.18  1998/01/16 23:34:32  mkl
// added MasterProducer for selecting Producers at run time
//
// Revision 1.17  1997/11/01 21:23:13  mkl
// added RawDataProvider
//
// Revision 1.16  1997/10/07 04:19:10  mkl
// report --> cout for INFO messages
//
// Revision 1.15  1997/09/18 21:27:02  cdj
// changed Boolean to DABoolean
//
// Revision 1.14  1997/09/13 19:50:00  sjp
// Added CompositeProvider to system
//
// Revision 1.13  1997/09/05 22:35:30  mkl
// undid singleton patteron for MasterProcessor
//
// Revision 1.12  1997/09/03 02:39:01  mkl
// restructuring suez libraries
//
// Revision 1.11  1997/08/20 06:23:43  mkl
// symmetrized sinks with sources in terms of user interface
//
// Revision 1.10  1997/08/18 20:56:34  mkl
// restored storage code
//
// Revision 1.9  1997/08/13 07:11:10  mkl
// Chains of Sources, new activation of streams, and ProxyDict
//
// Revision 1.8  1997/07/24 04:59:54  mkl
// adding chains of sources
//
// Revision 1.7  1997/07/11 06:55:50  mkl
// // New <Package>/<File>.h structure
// // Modified so can also compile under cxx v5.5
//
// Revision 1.6  1997/07/01 03:16:41  mkl
// moved typedef map statements to .cc files
//
// Revision 1.5  1997/06/06 06:18:27  mkl
// handle --> execute and other minor stuff
//
// Revision 1.4  1997/06/03 18:41:01  mkl
// allow any stream to have actions
//
// Revision 1.3  1997/05/23 20:22:34  mkl
// separated Processor stuff from JobControl
//
// Revision 1.2  1997/05/06 18:36:07  mkl
// added GotoCommand and ReprocessCommand
//
// Revision 1.1  1997/03/27 06:53:48  mkl
// imported sources.
//

#endif /* JOBCONTROL_JOBCONTROL_H */
