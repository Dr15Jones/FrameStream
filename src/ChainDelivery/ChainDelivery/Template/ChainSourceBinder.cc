#if !defined(CHAINDELIVERY_CHAINSOURCEBINDER_CC)
#define CHAINDELIVERY_CHAINSOURCEBINDER_CC
// -*- C++ -*-
//
// Package:     ChainDelivery
// Module:      ChainSourceBinder
// 
// Description: <one line class summary>
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Chris D. Jones
// Created:     Sat Jul 26 10:33:16 EDT 1997
// $Id: ChainSourceBinder.cc,v 1.12 1998/10/21 15:31:12 marsh Exp $
//
// Revision history
//
// $Log: ChainSourceBinder.cc,v $
// Revision 1.12  1998/10/21 15:31:12  marsh
// Protected against multiple inclusion.
//
// Revision 1.11  1998/09/16 21:45:18  mkl
// use new bug flag for static/extern linkage of kFacilityStrings in Template .cc files
//
// Revision 1.10  1998/09/11 18:45:40  mkl
// rename kFacilityString to avoid clashes
//
// Revision 1.9  1998/09/11 16:14:51  mkl
// had to make kFacilityString unique, since potentially included as Template implementation
//
// Revision 1.8  1998/07/29 02:27:03  mkl
// switch to static const char* const kFacilityString
//
// Revision 1.7  1998/06/17 18:25:43  mkl
// allow dynamic loading of source and sink formats
//
// Revision 1.6  1997/09/18 20:50:57  cdj
// Changed Boolean to DABoolean
//
// Revision 1.5  1997/09/03 20:06:51  sjp
// Uses CPP macros for STL containers
//
// Revision 1.4  1997/09/01 15:35:46  sjp
// Changed report include to be in Experiment
//
// Revision 1.3  1997/08/14 11:44:04  sjp
// Mods to run under CW Pro 1
//
// Revision 1.2  1997/08/08 05:12:42  mkl
// added ChainSourceBinderBase.h
//
// Revision 1.1  1997/07/26 16:36:33  cdj
// First submission
//

#include "Experiment/Experiment.h"

// system include files
#include <assert.h>

// user include files
#include "Experiment/report.h" // for `report'
#include "ChainDelivery/ChainSourceController.h"
#include "ChainDelivery/ChainSourceBinder.h"

// STL classes

//
// constants, enums and typedefs
//
FILESCOPE_IN_TEMPLATE_CC_BUG const char* const kChainSourceBinderFacilityString 
= "ChainDelivery.ChainSourceBinder" ;

//
// static data member definitions
//

//
// constructors and destructor
//
template< class Binder>
ChainSourceBinder< Binder >::ChainSourceBinder( const string& iName,
#if defined(TYPEDEFS_IN_TEMPLATES_IN_ARGS_BUG)
						const _chainsourcebinder_binders_& iBinders ,
#else
						const Binders& iBinders,
#endif /* TYPEDEFS_IN_TEMPLATES_IN_ARGS_BUG */
						const Stream::Set& iBindStreams):
   ChainSourceBinderBase( iName, string(""), iBindStreams ),
   m_binders( *( new Binders( iBinders ) ) )
{
   if( 0 == &m_binders ){
      report( EMERGENCY ,
              kChainSourceBinderFacilityString )
                 << "Unable to allocate memory"
                 << endl ;
      assert(false);
      exit( 1);
   }
}

template< class Binder>
ChainSourceBinder< Binder >::ChainSourceBinder( const string& iName,
						const Stream::Set& iBindStreams):
   ChainSourceBinderBase( iName, string(""), iBindStreams ),
   m_binders( *( new Binders ) )
{
   if( 0 == &m_binders ){
      report( EMERGENCY ,
              kChainSourceBinderFacilityString )
                 << "Unable to allocate memory"
                 << endl ;
      assert(false);
      exit( 1);
   }
}

// ChainSourceBinder::ChainSourceBinder( const ChainSourceBinder& )
// {
// }
template< class Binder>
ChainSourceBinder< Binder >::~ChainSourceBinder()
{
   delete &m_binders;
}

//
// assignment operators
//
// const ChainSourceBinder& ChainSourceBinder::operator=( const ChainSourceBinder& )
// {
// }

//
// member functions
//

template< class Binder>
void
ChainSourceBinder< Binder >::addSource( const Binder& iBinder )
{
   m_binders.push_back( iBinder );
}

template< class Binder>
DABoolean
ChainSourceBinder< Binder >::removeSource( const DataSourceDescriptor&
					 iDescriptor )
{
   DABoolean success = false;

   Binders::iterator itEnd = m_binders.end();
   for( Binders::iterator itBinder = m_binders.begin();
	itBinder != itEnd;
	++itBinder ){
      if( iDescriptor == *itBinder ){
	 success = true;
	 m_binders.erase( itBinder );
	 break;
      }
   }

   return success;
}

//
// const member functions
//
template< class Binder>
DataSourceController*
ChainSourceBinder< Binder >::createDataSourceController( void ) const
{
   //Force all the binders to read the same Streams
   Binders::iterator itEnd = m_binders.end();
   for( Binders::iterator itBinder = m_binders.begin();
	itBinder != itEnd;
	++itBinder ){

      (*itBinder ).bindStreams( boundStreams() );
   }

   return (new ChainSourceController< Binder >( name(),
						m_binders,
						boundStreams() ) );
}

template< class Binder >
#if defined(TYPEDEFS_IN_TEMPLATES_AS_RETURN_BUG)
const _chainsourcebinderbase_descriptors_
#else
const ChainSourceBinder< Binder >::Descriptors
#endif /* TYPEDEFS_IN_TEMPLATES_AS_RETURN_BUG */
ChainSourceBinder< Binder >::sources() const
{
   Descriptors returnValue;

   Binders::const_iterator itEnd = m_binders.end();
   for( Binders::const_iterator itBinder = m_binders.begin();
        itBinder != itEnd;
        ++itBinder ){
      DataSourceDescriptor temp( *itBinder );
      returnValue.push_back( temp );
   }

   return returnValue;
}

//
// static member functions
//
#endif /* CHAINDELIVERY_CHAINSOURCEBINDER_CC */
