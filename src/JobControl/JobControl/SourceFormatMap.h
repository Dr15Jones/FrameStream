#if !defined(JOBCONTROL_SOURCEFORMATMAP_H)
#define JOBCONTROL_SOURCEFORMATMAP_H
// -*- C++ -*-
//
// Package:     <JobControl>
// Module:      SourceFormatMap
// 
// Description: look-up table for formats (loaded or statically added)
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Mon May 25 17:41:54 EDT 1998
// $Id: SourceFormatMap.h,v 1.13 2003/02/20 18:45:04 cdj Exp $
//
// Revision history (at end of file)
//

// system include files

// user include files
#include "JobControl/FormatMap.h"
#include "DataHandler/Stream.h"
#include "Utility/StringWrapper.h"
#include "DataDelivery/SourceFormat.h"

// forward declarations
class BinderBase;
#include <map>
#if !defined(_extensionname_map_)
#define _extensionname_map_ std::map< std::string, StringWrapper, std::less< std::string > >
#endif
template< class T > class FormatCommand;

class SourceFormatMap : public FormatMap< SourceFormat >
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      SourceFormatMap( const std::string& environment = "C3_SHLIB" );
      virtual ~SourceFormatMap();

      // ---------- member functions ---------------------------

      BinderBase* createBinder( const std::string& iName,
				const Stream::Set& iBindStreams );
      // default streams based on extension (given by name)
      Stream::Set defaultStreams( const std::string& iName );

      // clear all formats
      virtual DABoolean clearAll();

      // ---------- const member functions ---------------------

      // overridden Loader< SourceFormat > method
      virtual std::string listLoaded() const;

      // pattern for listings
      virtual std::string listAvailablePatternString() const { 
	 //return std::string( "SourceFormat" ); 
	 return std::string( "" ); 
      }

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // overriden Loader<> methods
      virtual void initialize( const std::string& iName, 
			       SourceFormat& iSourceFormat );
      virtual void finalize(   const std::string& iName, 
			       SourceFormat& iSourceFormat );
      virtual void errorMesg( const std::string& iName ) const;

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      SourceFormatMap( const SourceFormatMap& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const SourceFormatMap& operator=( const SourceFormatMap& ); // stop default

      // ---------- private member functions -------------------
      // bind extensions to formats
      virtual DABoolean bind( const std::string& iFormatName,
			      const std::string& iExtension );
      virtual DABoolean unbind( const std::string& iExtension );
      virtual DABoolean unbindAll();

      DABoolean bind( const std::string& iFormatName,
		      const SourceFormat::Extensions& iExtensions );

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      FormatCommand< SourceFormatMap >& m_command;
      
      // binding: extension vs name
      _extensionname_map_& m_extensionVsName;

      // ---------- static data members ------------------------

};

// inline function definitions

// -----------------------------------------------------------------
// Revision history
//
// $Log: SourceFormatMap.h,v $
// Revision 1.13  2003/02/20 18:45:04  cdj
// fixed improper casting of Source(Sink)Format to Source(Sink)FormatModule
//
// Revision 1.12  1999/10/08 21:46:47  mkl
// put in hooks for pattern searching in loading (if we ever decide to use it); fix bug with file chaining
//
// Revision 1.11  1999/06/12 00:04:01  mkl
// allow to specify default streams per source format
//
// Revision 1.10  1999/02/22 23:41:49  mkl
// setResult( string ) insteadof report in Commands; added NamingService and DefaultModule; fixed bug in stream command
//
// Revision 1.9  1998/12/02 05:55:33  mkl
// towards interacting with Source- and SinkFormats
//
// Revision 1.8  1998/11/10 03:52:28  mkl
// unify producer/processor/module/source_format/sink_format commands
//
// Revision 1.7  1998/11/09 21:25:07  mkl
// loadable classes know their own factorySymbol string; improved user iface of ModuleCommand
//
// Revision 1.6  1998/11/09 19:33:29  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
// Revision 1.5  1998/07/29 02:16:01  mkl
// disallow explicit extension setting for source/sink formats; formats know their extensions
//
// Revision 1.4  1998/07/27 17:41:14  mkl
// shorten names to allow compiling under g++
//
// Revision 1.3  1998/07/25 16:10:07  mkl
// add static linking of sources/sinks
//
// Revision 1.2  1998/06/23 23:00:50  mkl
// cleanup of LoadableInterface
//
// Revision 1.1  1998/06/17 18:19:30  mkl
// allow dynamic loading of source and sink formats
//
#endif /* JOBCONTROL_SOURCEFORMATMAP_H */
