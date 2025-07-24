// -*- C++ -*-
//
// Package:     <CommandPattern>
// Module:      ParameterBase
// 
// Description: <one line class summary>
//
// Implementation:
//              based on BaBar/CDF implementation
//
// Author:      Martin Lohner
// Created:     Wed Jan 28 18:07:49 EST 1998
// $Id: ParameterBase.cc,v 1.8 2003/02/13 21:03:24 ajm36 Exp $
//
// Revision history
//
// $Log: ParameterBase.cc,v $
// Revision 1.8  2003/02/13 21:03:24  ajm36
// parameters now return their value to tcl when they are changed or checked
//
// Revision 1.7  2000/08/04 15:51:26  mkl
// since failed call-back message is at system level, print out 'ERROR' to make clear what's happening
//
// Revision 1.6  2000/08/04 15:15:07  mkl
// call-back function now returns DABoolean (if false, value gets reset to default)
//
// Revision 1.5  2000/08/03 22:05:24  mkl
// parameters now have optional call-back mechanism
//
// Revision 1.4  1998/06/17 18:17:16  mkl
// allow dynamic loading of source and sink formats
//
// Revision 1.3  1998/04/08 19:49:16  mkl
// improved parameter help page
//
// Revision 1.2  1998/03/14 01:52:55  mkl
// added default value
//
// Revision 1.1  1998/03/11 19:11:04  mkl
// new Parameter sources
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"

#include "CommandPattern/ParameterBase.h"
#include "CommandPattern/Module.h"

// STL classes
#include <cstring>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "CommandPattern.ParameterBase" ;

//
// static data member definitions
//

//
// constructors and destructor
//
ParameterBase::ParameterBase( const Command::Name& iName,
			      Module* iTarget )
   : Command( iName, iTarget ),
     m_parmChangeCallBack( 0 )
{
}

// ParameterBase::ParameterBase( const ParameterBase& )
// {
// }

ParameterBase::~ParameterBase()
{
   // if we were given a callback object, we own it, so delete it
   if( 0 != m_parmChangeCallBack ) { delete m_parmChangeCallBack; }
}

//
// assignment operators
//
// const ParameterBase& ParameterBase::operator=( const ParameterBase& )
// {
// }

//
// member functions
//
int
ParameterBase::execute( int argc, char* argv[] )
{
   int result = COMMAND_ERROR;

   setArgs( argc, argv );
   if ( 1 <= argc ) {
      if( 2 == argc && 0 == strcmp( argv[1], "help" ) ) {
	 result = helpHandler();
      } else
      if( 2 == argc && 0 == strcmp( argv[1], "def" ) ) {
	 result = setDefaultHandler();
      } 
      else {
	 if( 1 == argc ) {
	    result = listHandler();
	 } else
	 if( 1 < argc ) {
	    result = setHandler();
	 }
      }
   } 
   else {
      report( ERROR, kFacilityString )
	 << "wrong # args" << std::endl;
      result = COMMAND_ERROR;
   }
   
   return result;
}

void
ParameterBase::setParameterChangeCallBack( ParameterChangeCallBackBase* iCallBack )
{
   m_parmChangeCallBack = iCallBack;
}

int
ParameterBase::setHandler()
{
   Command::Result returnValue = Command::COMMAND_OK;
   
   // call real implementation of setHandler
   if( Command::COMMAND_OK == 
       (returnValue=static_cast<Command::Result>(implementSetHandler())) )
   {
      // force call of init() function! (and along with it terminate())
      target()->setCallInit( true );

      // call callback
      if( 0 != m_parmChangeCallBack ) {
	 // turn DABoolean into COMMAND return code
	 returnValue= ((*m_parmChangeCallBack)()==true) ? COMMAND_OK : COMMAND_ERROR; 
	 if( COMMAND_ERROR == returnValue ) {
	    report( SYSTEM, kFacilityString )
	       << "ERROR: resetting to default" << std::endl;
	    setDefaultHandler();
	 }
      }
   }

   return returnValue;
}

int
ParameterBase::setDefaultHandler()
{
   Command::Result returnValue = Command::COMMAND_OK;
   
   // call real implementation of setHandler
   if( Command::COMMAND_OK == 
       (returnValue=static_cast<Command::Result>(implementSetDefaultHandler())) )
   {
      // force call of init() function! (and along with it terminate())
      target()->setCallInit( true );

      // call callback
      if( 0 != m_parmChangeCallBack ) { 
	 // turn DABoolean into COMMAND return code
	 returnValue= ((*m_parmChangeCallBack)()==true) ? COMMAND_OK : COMMAND_ERROR; 
      }
   }

   return returnValue;
}

int
ParameterBase::helpHandler()
{
   const std::string helpMessage1 = 
      std::string( "                                                          \n" )+
      std::string( "  Description: Parameter " ) + name() + std::string( "         \n" );

   const std::string helpMessage2 =
      std::string( "  Valid subcommands are:                                  \n" )+
      std::string( "                                                          \n" )+
      std::string( "  " ) + name() + std::string( " help      prints this help page\n" )+
      std::string( "  " ) + name() + std::string( " <value>   " ) 
      + name() + std::string( " = <value>       \n" )+
      std::string( "  " ) + name() + std::string( "           list value           \n" )+
      std::string( "  " ) + name() + std::string( " def       " )
      + name() + std::string( " = default       \n" )+
      std::string( "                                                          \n" );

   // print help
   report( INFO, kFacilityString )
      << "\n" << helpMessage1
      << "\n" << "  Type: " << typeName() << "\n"
      << "\n" << helpString() << "\n"
      << "\n" << helpMessage2 << std::endl;
      
   return COMMAND_OK;
}

const char* 
ParameterBase::typeName()
{
   return 0;
}

//
// const member functions
//

//
// static member functions
//

