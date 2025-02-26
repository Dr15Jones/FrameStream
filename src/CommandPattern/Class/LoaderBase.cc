// -*- C++ -*-
//
// Package:     CommandPattern
// Module:      LoaderBase
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Martin Lohner
// Created:     Thu Jan 15 12:52:59 EST 1998
// $Id: LoaderBase.cc,v 1.5 2000/12/01 20:23:19 cdj Exp $
//
// Revision history (at end of file)
//
//

#include "Experiment/Experiment.h"

// system include files
#include <stdlib.h>
#include <assert.h>

#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <string>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "CommandPattern/LoaderBase.h"

#include "DataDelivery/FrameDeliverer.h"
//#include "DynamicLoader/DLSharedObjectHandler.h"

// STL classes
#include <string>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "CommandPattern.LoaderBase" ;

//
// static data member definitions
//

//
// constructors and destructor
//
LoaderBase::LoaderBase( const string& environment )
//   : m_sharedObjectHandler( *new DLSharedObjectHandler( environment ) )
{
/*
   if( 0 == &m_sharedObjectHandler )
   {
      report( EMERGENCY, kFacilityString )
	 << "no memory allocated" << endl;
      assert( false );
      ::exit( 1 );
   }
   */
}

// LoaderBase::LoaderBase( const LoaderBase& )
// {
// }

LoaderBase::~LoaderBase()
{
//   m_sharedObjectHandler.unloadAll();
//   delete &m_sharedObjectHandler;
}

//
// assignment operators
//
// const LoaderBase& LoaderBase::operator=( const LoaderBase& )
// {
// }

//
// member functions
//
/*
DLSharedObjectHandler&
LoaderBase::sharedObjectHandler()
{
   return m_sharedObjectHandler;
}

void*
LoaderBase::getSymbol( const string& iSharedLibraryName,
		       const string& iFactoryString,
		       const DABoolean& iVerbose,
		       DABoolean& oStatus )
{
   void* symbol = 0;
   oStatus = sharedObjectHandler().getSymbol( iSharedLibraryName, 
					      iFactoryString,
					      iVerbose,
					      symbol );
   
   return symbol;
}
*/
//
// const member functions
//
/*
const DLSharedObjectHandler&
LoaderBase::sharedObjectHandler() const
{
   return m_sharedObjectHandler;
}

string 
LoaderBase::fullName( const string& iName ) const
{
   string returnValue = sharedObjectHandler().fullName( iName );
   if( returnValue == string( "" ) ) {
      returnValue = string( "memory" );
   }
   
   return returnValue;
}
*/

//
// static member functions
//


// ----------------------------------------------------------
// Revision history
//
// $Log: LoaderBase.cc,v $
// Revision 1.5  2000/12/01 20:23:19  cdj
// now uses DynamicLoader package
//
// Revision 1.4  1999/10/26 17:41:51  mkl
// print 'memory' properly for memory-based modules
//
// Revision 1.3  1999/02/22 23:40:40  mkl
// setResult( string ) insteadof report in Commands; added NamingService and DefaultModule; fixed bug in stream command
//
// Revision 1.2  1999/01/27 22:54:48  mkl
// rewrote StringUtil utility functions
//
// Revision 1.1  1998/11/09 19:31:01  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
// Revision 1.2  1998/06/23 23:01:09  mkl
// cleanup of LoaderBase
//
// Revision 1.1  1998/06/17 18:17:15  mkl
// allow dynamic loading of source and sink formats
//
// Revision 1.1  1998/01/16 23:33:14  mkl
// added MasterProducer for selecting Producers at run time
//
