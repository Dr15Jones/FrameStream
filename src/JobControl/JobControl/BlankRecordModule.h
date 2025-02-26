#if !defined(JOBCONTROL_BLANKRECORDMODULE_H)
#define JOBCONTROL_BLANKRECORDMODULE_H
// -*- C++ -*-
//
// Package:     JobControl
// Module:      BlankRecordModule
// 
// Description: <one line class summary>
//
// Usage:
//    <usage>
//
// Author:      Chris D. Jones
// Created:     Sun Mar 29 17:33:33 EST 1998
// $Id: BlankRecordModule.h,v 1.4 1999/06/14 15:55:47 mkl Exp $
//
// Revision history
//
// $Log: BlankRecordModule.h,v $
// Revision 1.4  1999/06/14 15:55:47  mkl
// return token name as tcl resultString
//
// Revision 1.3  1998/11/09 19:33:25  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
// Revision 1.2  1998/06/17 18:18:20  mkl
// allow dynamic loading of source and sink formats
//
// Revision 1.1  1998/04/01 19:43:18  mkl
// added Chris' BlankRecordDelivery handling
//

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "CommandPattern/Module.h"
#include "JobControl/BlankRecordCommand.h"

// STL include
#include <string>

// forward declarations
class StreamSet;
class BlankRecordStopsBase;
class SourceManager;
class BinderBase;

class BlankRecordModule : public Module
{
      // friend classes and functions

   public:
      // constants, enums and typedefs

      // Constructors and destructor
      BlankRecordModule( SourceManager& iSourceManager );
      virtual ~BlankRecordModule();

      // member functions
      DABoolean addSource( const string& iSourceName, 
			   const StreamSet& iReadStreams,
			   BlankRecordStopsBase* iStops,
			   string& ioToken );

      // const member functions

      // static member functions

   protected:
      // protected member functions
      BinderBase* createBinder( const string& sourceName,
				const StreamSet& readStreams,
				BlankRecordStopsBase* iStops );

      // protected const member functions

   private:
      // Constructors and destructor
      BlankRecordModule();
      BlankRecordModule( const BlankRecordModule& );

      // assignment operator(s)
      const BlankRecordModule& operator=( const BlankRecordModule& );

      // private member functions

      // private const member functions

      // data members
      BlankRecordCommand m_command;

      SourceManager& m_sourceManager;

      // static data members

};

// inline function definitions

//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// templated member function definitions
//# include "JobControl/Template/BlankRecordModule.cc"
//#endif

#endif /* JOBCONTROL_BLANKRECORDMODULE_H */
