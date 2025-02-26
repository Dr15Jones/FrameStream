#if !defined(JOBCONTROL_SOURCEMANAGER_H)
#define JOBCONTROL_SOURCEMANAGER_H
// -*- C++ -*-
//
// Package:     JobControl
// Module:      SourceManager
// 
// Description: handles sources (internally) and hands off DataBinders to 
//              FrameDeliverer
//
// Usage:
//         SourceManager has its own internal data base of sources
//         implemented as a map<token, sources>.
//      
//         "addSource()" will add file- plus stream names, either for
//         a given token, or if not specified, created, and saved in the
//         map of sources. When the time comes to ask for a databinder, 
//         SourceManager will create one via "nextDataBinderInChain( token )".
//
// Author:      Martin Lohner
// Created:     Tue Jul 22 10:53:30 EDT 1997
// $Id: SourceManager.h,v 1.25 2000/12/02 19:26:58 cdj Exp $
//
// Revision history (at end of file)

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */             

// user include files
#include "CommandPattern/Module.h"
#include "JobControl/SourceCommand.h"
#include "JobControl/StreamCommand.h"
#include "CommandPattern/OrderedMap.h"

// STL include
#include <string>
#include <vector>

// forward declarations
class FrameDeliverer;
class StreamSet;
class DataSourceDescriptor;
class MasterProcessor;
class BinderBase;
class SinkManager;

#if !defined(SOURCEMANAGER_SOURCEMAP)
#define SOURCEMANAGER_SOURCEMAP OrderedMap< SourceManager::Token, BinderBase* >
#endif

class SourceManager : public Module
{
      // friend classses and functions

   public:
      // constants, enums and typedefs
      typedef string SourceName;
      typedef string StreamName;
      typedef string Token;

      // Constructors and destructor
      SourceManager( FrameDeliverer& iFrameDeliverer );
      virtual ~SourceManager();

      // member functions

      // token
      DABoolean renameToken( const Token& iOldToken, const Token& iNewToken );

      // add DataSourceBinder
      DABoolean addSource( BinderBase* iBinder, Token& ioToken );

      // hand them over to FD engine
      DABoolean useSources( DABoolean& oNewSources );

      // remove chains and sources
      DABoolean editSource( const Token& iToken );
      DABoolean removeSourceInUse( const Token& iToken );
      DABoolean removeSource( const Token& iToken );
      DABoolean removeAllSources();
      DABoolean removeSourceFromChain( const Token& iToken, 
				       const SourceName& sourceName );

      // activation of streams
      void setStreamsToBeActivated( const StreamSet& streams ); 
      StreamSet& streamsToBeActivated( const MasterProcessor&,
				       const SinkManager& ); 
      DABoolean activateStreams( const MasterProcessor&,
				 const SinkManager& );

      DABoolean handActiveDSDToFrameDeliverer( 
	 const DataSourceDescriptor& activeSource );

      // binding streams to source
      DABoolean bindStreamsToSource( const Token& token, 
				     const StreamSet& streams );

      // keep track of streams to-be-active
      DABoolean setToBeActiveStreamsInSource( const Token& iToken,
					 const StreamSet& iStreams );
      DABoolean clearToBeActiveStreamsInSource( const Token& iToken );
      DABoolean clearToBeActiveStreamsInAllSources();

      // used when iterating over Frames
      void resetSourcesToBeginning();

      // listings
      string list( const Token& iToken ) const;
      string listAllSources() const;
      string listStreams() const;
      string listStreamsToBeActivated() const;
      string statusOfAllSources() const;

      // token stuff
      Token findTokenFor( const DataSourceDescriptor& iDescriptor) const;
      string listTokens() const;
      const vector<Token> tokens() const;

      DABoolean hasSource( const Token& iToken ) const;
      DABoolean checkIfTokenExists( const Token& iToken ) const;

      const StreamSet& streamsToBeActivated() const; 

      // static member functions

   protected:
      // protected member functions

      // protected const member functions

   private:
      // Constructors and destructor
      SourceManager( const SourceManager& );

      // assignment operator(s)
      const SourceManager& operator=( const SourceManager& );

      // private member functions
      DABoolean removeSourceInUseFromChain( const Token& iToken,
					    const SourceName& sourceName="" );
      // private const member functions
      string listSource( const Token& iToken ) const;
      string listSourceInUse( const Token& iToken ) const;
      string listSourcesInChain( const BinderBase* iBinder ) const;
      string listSourceImplementation( const Token& iToken, 
				       const SOURCEMANAGER_SOURCEMAP & iMap,
				       string iSpecialPrint="" ) const;

      DABoolean isSourceInMap( const Token& iToken ) const;
      DABoolean isSourceInUseMap( const Token& iToken ) const;

      const Token createToken( Token iToken ) const;

      // data members
      SourceCommand m_sourceCommand;
      StreamCommand m_streamCommand;

      // internal data base for sources
      SOURCEMANAGER_SOURCEMAP & m_sourceMap;
      SOURCEMANAGER_SOURCEMAP & m_sourceInUseMap;
      StreamSet& m_streamsToBeActivated;

      // use relationship
      FrameDeliverer& m_frameDeliverer;

      // static data members

};

// inline function definitions

// Revision history
//
// $Log: SourceManager.h,v $
// Revision 1.25  2000/12/02 19:26:58  cdj
// added findTokenFor so JobControl doesn't have to know how Tokens are built
//
// Revision 1.24  2000/03/17 15:36:38  cdj
// added resetSourcesToBeginning().  Needed for FrameIterate
//
// Revision 1.23  2000/01/19 16:53:15  mkl
// force reload of proxies after new source is added
//
// Revision 1.22  1999/12/11 19:07:39  mkl
// added 'source status' command; use bug flag for linux string compare function problem
//
// Revision 1.21  1999/06/14 15:55:48  mkl
// return token name as tcl resultString
//
// Revision 1.20  1999/04/30 18:15:25  mkl
// first version of source act command handling
//
// Revision 1.19  1999/04/24 17:06:27  mkl
// make cxx happy
//
// Revision 1.18  1999/04/24 16:23:00  mkl
// keep track of DataSourceDescriptors, not just names of files
//
// Revision 1.17  1999/04/14 21:16:29  mkl
// ordered container used in Suez
//
// Revision 1.16  1999/03/11 22:02:45  mkl
// source out stream will activate stream; turn off superfluous warning for 'param' command
//
// Revision 1.15  1999/02/22 23:41:49  mkl
// setResult( string ) insteadof report in Commands; added NamingService and DefaultModule; fixed bug in stream command
//
// Revision 1.14  1999/01/21 00:02:06  mkl
// added minor convenience functions 'hasSource/Sink'
//
// Revision 1.13  1998/11/09 19:33:29  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
// Revision 1.12  1998/06/17 18:18:23  mkl
// allow dynamic loading of source and sink formats
//
// Revision 1.11  1998/02/03 21:29:42  mkl
// switch over to STLUtility library
//
// Revision 1.10  1997/09/18 21:27:05  cdj
// changed Boolean to DABoolean
//
// Revision 1.9  1997/09/05 22:35:31  mkl
// undid singleton patteron for MasterProcessor
//
// Revision 1.8  1997/09/03 02:39:10  mkl
// restructuring suez libraries
//
// Revision 1.7  1997/08/29 04:22:17  mkl
// simplify JobControl: remove FileInput/Output files, bug flag changes, handling of suffix .gz etc.
//
// Revision 1.6  1997/08/22 06:27:51  mkl
// beauty
//
// Revision 1.5  1997/08/20 07:27:19  mkl
// minor fixes to make cxx5.4-6 happy
//
// Revision 1.4  1997/08/20 06:23:45  mkl
// symmetrized sinks with sources in terms of user interface
//
// Revision 1.3  1997/08/13 07:11:12  mkl
// Chains of Sources, new activation of streams, and ProxyDict
//
// Revision 1.2  1997/08/08 05:21:32  mkl
// first attempt at chains-of-files
//
// Revision 1.1  1997/07/24 04:59:55  mkl
// adding chains of sources
//

#endif /* JOBCONTROL_SOURCEMANAGER_H */
