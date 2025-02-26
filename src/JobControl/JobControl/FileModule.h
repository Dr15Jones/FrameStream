#if !defined(JOBCONTROL_FILEMODULE_H)
#define JOBCONTROL_FILEMODULE_H
// -*- C++ -*-
//
// Package:     JobControl
// Module:      FileModule
// 
// Description: Mediator Class for FileInputModule and FileOutputModule
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Wed Aug 20 00:47:44 EST 1997
// $Id: FileModule.h,v 1.9 2001/06/15 21:06:28 cdj Exp $
//
// Revision history
//
// $Log: FileModule.h,v $
// Revision 1.9  2001/06/15 21:06:28  cdj
// can now specify data (not) to store in a sink
//
// Revision 1.8  1999/06/14 15:55:47  mkl
// return token name as tcl resultString
//
// Revision 1.7  1998/11/09 19:33:25  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
// Revision 1.6  1998/06/17 20:20:56  mkl
// clean-out
//
// Revision 1.5  1998/06/17 18:18:20  mkl
// allow dynamic loading of source and sink formats
//
// Revision 1.4  1997/09/18 21:27:01  cdj
// changed Boolean to DABoolean
//
// Revision 1.3  1997/09/03 02:38:58  mkl
// restructuring suez libraries
//
// Revision 1.2  1997/08/29 04:22:14  mkl
// simplify JobControl: remove FileInput/Output files, bug flag changes, handling of suffix .gz etc.
//
// Revision 1.1  1997/08/20 06:23:41  mkl
// symmetrized sinks with sources in terms of user interface
//
//

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "CommandPattern/Module.h"
#include "JobControl/FileCommand.h"
#include "DataStorage/StreamToDataStringTagsToStoreMap.h"
// STL include
#include <string>

// forward declarations
class StreamSet;
class SourceFormatMap;
class SinkFormatMap;
class SourceManager;
class SinkManager;

class FileModule : public Module
{
      // friend classses and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      FileModule( SourceFormatMap& sourceFormatMap, 
		  SinkFormatMap& sinkFormatMap,
		  SourceManager& sourceM, SinkManager& sinkM  );
      virtual ~FileModule();

      // member functions

      // ------------ input module -----------------
      DABoolean addSource( const string& iSourceName, 
			   const StreamSet& iReadStreams,
			   string& iToken );
      DABoolean checkIfSourceExists( string& iSourceName );
      
      // ------------ output module -----------------
      DABoolean addSink( const string& iSinkName, 
			 const StreamSet& iStreamSet );
      DABoolean addSink( const string& iSinkName, 
			 const StreamSet& iStreamSet,
			 const  StreamToDataStringTagsToStoreMap& iStreamTagsMap);
      DABoolean checkSinkName( string& iSinkName );
      
      // const member functions
      
      // static member functions
      
   protected:
      // protected member functions
      
      // protected const member functions

   private:
      // Constructors and destructor
      FileModule( const FileModule& );

      // assignment operator(s)
      const FileModule& operator=( const FileModule& );

      // private member functions

      // private const member functions

      // data members
      FileCommand m_command;
      
      SourceFormatMap& m_sourceFormatMap;
      SinkFormatMap&   m_sinkFormatMap;
      SourceManager&   m_sourceManager;
      SinkManager&     m_sinkManager;

      // static data members

};

// inline function definitions

#endif /* JOBCONTROL_FILEMODULE_H */
