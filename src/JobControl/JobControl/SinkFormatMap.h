#if !defined(JOBCONTROL_SINKFORMATMAP_H)
#define JOBCONTROL_SINKFORMATMAP_H
// -*- C++ -*-
//
// Package:     <JobControl>
// Module:      SinkFormatMap
// 
// Description: look-up table for formats (loaded or statically added)
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Mon May 25 17:41:54 EDT 1998
// $Id: SinkFormatMap.h,v 1.13 2003/02/20 18:45:04 cdj Exp $
//
// Revision history (at end of file)
//

// system include files

// user include files
#include "JobControl/FormatMap.h"
#include "DataHandler/Stream.h"
#include "Utility/StringWrapper.h"
#include "DataStorage/SinkFormat.h"
#include "JobControl/FormatCommand.h"

// forward declarations
class DataSinkBinder;
#include "STLUtility/fwd_map.h"
#if !defined(_extensionname_map_)
#define _extensionname_map_ map< string, StringWrapper, less< string > >
#endif
template< class T > class FormatCommand;


class SinkFormatMap : public FormatMap< SinkFormat >
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      SinkFormatMap( const string& environment = "C3_SHLIB" );
      virtual ~SinkFormatMap();

      // ---------- member functions ---------------------------

      DataSinkBinder* createBinder( const string& iName,
				    const Stream::Set& iBindStreams );

      virtual DataSinkBinder*
      createBinder( const string& iName,
	            const Stream::Set& iBindStreams,
                    const StreamToDataStringTagsToStoreMap& iStreamTagsMap);
      
      // add statically

      // clear all formats
      virtual DABoolean clearAll();

      // ---------- const member functions ---------------------

      // overridden Loader< SinkFormat > method
      virtual string listLoaded() const;

      // pattern for listings
      virtual string listAvailablePatternString() const { 
	 //return string( "SinkFormat" ); 
	 return string( "" ); 
      }

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // overriden Loader<> methods
      virtual void initialize( const string& iName, 
			       SinkFormat& iSinkFormat );
      virtual void finalize(   const string& iName, 
			       SinkFormat& iSinkFormat );
      virtual void errorMesg( const string& iName ) const;

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      SinkFormatMap( const SinkFormatMap& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const SinkFormatMap& operator=( const SinkFormatMap& ); // stop default

      // ---------- private member functions -------------------
      // bind extensions to formats
      virtual DABoolean bind( const string& iFormatName,
			      const string& iExtension );
      virtual DABoolean unbind( const string& iExtension );
      virtual DABoolean unbindAll();

      DABoolean bind( const string& iFormatName,
		      const SinkFormat::Extensions& iExtensions );

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      FormatCommand< SinkFormatMap >& m_command;

      // binding: extension vs name
      _extensionname_map_& m_extensionVsName;

      // ---------- static data members ------------------------

};

// inline function definitions


// ------------------------------------------------------------
// Revision history
//
// $Log: SinkFormatMap.h,v $
// Revision 1.13  2003/02/20 18:45:04  cdj
// fixed improper casting of Source(Sink)Format to Source(Sink)FormatModule
//
// Revision 1.12  2001/06/15 21:06:28  cdj
// can now specify data (not) to store in a sink
//
// Revision 1.11  1999/10/08 21:46:47  mkl
// put in hooks for pattern searching in loading (if we ever decide to use it); fix bug with file chaining
//
// Revision 1.10  1999/02/22 23:41:47  mkl
// setResult( string ) insteadof report in Commands; added NamingService and DefaultModule; fixed bug in stream command
//
// Revision 1.9  1998/12/02 05:55:31  mkl
// towards interacting with Source- and SinkFormats
//
// Revision 1.8  1998/11/10 03:52:28  mkl
// unify producer/processor/module/source_format/sink_format commands
//
// Revision 1.7  1998/11/09 21:25:07  mkl
// loadable classes know their own factorySymbol string; improved user iface of ModuleCommand
//
// Revision 1.6  1998/11/09 19:33:28  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
// Revision 1.5  1998/07/29 02:16:01  mkl
// disallow explicit extension setting for source/sink formats; formats know their extensions
//
// Revision 1.4  1998/07/27 17:41:14  mkl
// shorten names to allow compiling under g++
//
// Revision 1.3  1998/07/25 16:10:06  mkl
// add static linking of sources/sinks
//
// Revision 1.2  1998/06/23 23:00:50  mkl
// cleanup of LoadableInterface
//
// Revision 1.1  1998/06/17 18:18:23  mkl
// allow dynamic loading of source and sink formats
//
#endif /* JOBCONTROL_SINKFORMATMAP_H */
