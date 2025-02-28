#if !defined(COMMANDPATTERN_PARAMETER_CC)
#define COMMANDPATTERN_PARAMETER_CC
// -*- C++ -*-
//
// Package:     <CommandPattern>
// Module:      Parameter
// 
// Description: <one line class summary>
//
// Implementation:
//
// Author:      Martin Lohner
// Created:     Wed Jan 28 15:55:05 EST 1998
// $Id: Parameter.cc,v 1.14 2003/02/14 15:17:23 ajm36 Exp $
//
// Revision history (at end of file)
//

#include "Experiment/Experiment.h"

// system include files
#include <stdlib.h>
#include <assert.h>
#if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
#include <strstream.h>
#else
#include <sstream>
#endif
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "CommandPattern/Parameter.h"
#include "CommandPattern/Module.h"
#include "CommandPattern/Interpreter.h"

// STL classes

//
// constants, enums and typedefs
//

FILESCOPE_IN_TEMPLATE_CC_BUG const char* const kParameterFacilityString 
= "CommandPattern.Parameter" ;

//
// static data member definitions
//

//
// constructors and destructor
//
template< class T >
Parameter<T>::Parameter( const Command::Name& iName, 
			 Module* iTarget,
			 const T& defaultValue )
   : ParameterBase( iName, iTarget ),
     m_value( *new T( defaultValue ) ),
     m_defaultValue( *new T( defaultValue ) )
{
   if(    0 == &m_value 
       || 0 == &m_defaultValue 
      ) {
      report( EMERGENCY, kParameterFacilityString )
	 << "no memory left" << endl;
      assert( false );
      ::exit( 1 );
   }
}

template< class T >
Parameter<T>::Parameter( const Command::Name& iName, 
			 Module* iTarget )
   : ParameterBase( iName, iTarget ),
     m_value( *new T ),
     m_defaultValue( *new T )
{
   if(    0 == &m_value 
       || 0 == &m_defaultValue 
      ) {
      report( EMERGENCY, kParameterFacilityString )
	 << "no memory left" << endl;
      assert( false );
      ::exit( 1 );
   }
}

// Parameter::Parameter( const Parameter& )
// {
// }

template< class T >
Parameter<T>::~Parameter()
{
   delete &m_defaultValue;
   delete &m_value;
}

//
// assignment operators
//
// const Parameter& Parameter::operator=( const Parameter& )
// {
// }

//
// member functions
//
template< class T >
void
Parameter<T>::setParameterChangeCallBack( ParameterChangeCallBack* iCallBack )
{
   if( 0 != iCallBack ) {
      iCallBack->setParameter( this );
      ParameterBase::setParameterChangeCallBack( iCallBack );
   }
}

template< class T >
void
Parameter<T>::setDefault( const T& iDefault )
{
   m_value = iDefault;
   m_defaultValue = iDefault;
}

template< class T >
int
Parameter<T>::implementSetHandler()
{
   Command::Result returnValue = Command::COMMAND_OK;
   
   if ( m_argc < 2 ) {
      report( SYSTEM, kParameterFacilityString )
	 << "too few arguments" << endl;
      returnValue = Command::COMMAND_ERROR;
   }
   else {
      setValue( m_value );
#if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
ostrstream str;
#define GET_STR(_var_) _var_.str()
#else
ostringstream str;
#define GET_STR(_var_) _var_.str().c_str()
#endif
      str<<m_value<<ends;
      Interpreter::interpreter()->setResult(GET_STR(str));
   }

   return returnValue;
}

template< class T >
int
Parameter<T>::implementSetDefaultHandler()
{
   Command::Result returnValue = Command::COMMAND_OK;
   
   if ( m_argc < 2 ) {
      report( SYSTEM, kParameterFacilityString )
	 << "too few arguments" << endl;
      returnValue = Command::COMMAND_ERROR;
   }
   else {
      m_value = m_defaultValue;
#if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
ostrstream str;
#else
ostringstream str;
#endif
      str<<m_value<<ends;
      Interpreter::interpreter()->setResult(GET_STR(str));
   }

   return returnValue;
}

template< class T >
int
Parameter<T>::listHandler()
{
   Command::Result returnValue = Command::COMMAND_OK;

#if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
ostrstream str;
#else
ostringstream str;
#endif
   str<<m_value<<ends;
   Interpreter::interpreter()->setResult(GET_STR(str));
   
   return returnValue;
}

template< class T >
void 
Parameter< T >::setValue( T& value )
{
   assert( 2 <= m_argc );

   if( 2 < m_argc ) {
      report( SYSTEM, kParameterFacilityString )
	 << "will ignore extra arguments!" << endl;
   }

#if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
istrstream str( getArgument( 1 ) );
#else
istringstream str( getArgument( 1 ) );
#endif

   str >> value;
   // error handling
   if( ios::failbit == str.fail() ) {
      report( SYSTEM, kParameterFacilityString )
	 << "bad argument; can't interpret" << endl;
   }
}

//
// const member functions
//
template< class T >
const T&
Parameter<T>::value() const
{
   return m_value;
}

//
// static member functions
//
// don't want generalization, because some compilers complain about
// specialization plus generalization when instantiating; better this way anyways
// because now user gets unresolved symbol
#if 0 
template< class T >
const char*
Parameter<T>::typeName()
{ 
   return "";
}
#endif


// --------------------------------------------------------
// Revision history
//
// $Log: Parameter.cc,v $
// Revision 1.14  2003/02/14 15:17:23  ajm36
// fix stringstream bug for solaris 8 compiler
//
// Revision 1.13  2003/02/13 21:03:30  ajm36
// parameters now return their value to tcl when they are changed or checked
//
// Revision 1.12  2003/01/27 19:12:41  cdj
// use stringstream if available
//
// Revision 1.11  2000/08/03 22:05:27  mkl
// parameters now have optional call-back mechanism
//
// Revision 1.10  2000/06/01 18:02:25  mkl
// shorten some system-level kFacilityStrings to 'Suez' for better readability
//
// Revision 1.9  2000/06/01 17:49:29  mkl
// switch all Suez messages to SYSTEM level
//
// Revision 1.8  2000/01/04 20:53:33  mkl
// now print type with parameter value
//
// Revision 1.7  1998/11/09 19:31:56  mkl
// revamped Module/Command system to allow uniform loading of source/sink-formats, modules, processors/producers
//
// Revision 1.6  1998/09/23 19:04:54  mkl
// typename; protect against multiple inclusion. All the make egcs happy
//
// Revision 1.5  1998/03/28 18:13:15  mkl
// eliminate g++ warnings (unused this, unsed that)
//
// Revision 1.4  1998/03/15 00:08:15  mkl
// Parameter< vector< T > >
//
// Revision 1.3  1998/03/14 01:53:02  mkl
// added default value
//
// Revision 1.2  1998/03/12 15:00:21  mkl
// Parameter.h comes from CommandPattern
//
// Revision 1.1  1998/03/11 19:10:42  mkl
// new Parameter sources
#endif /* COMMANDPATTERN_PARAMETER_CC */
