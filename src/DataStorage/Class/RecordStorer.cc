// -*- C++ -*-
//
// Package:     DataStorage
// Module:      RecordStorer
// 
// Description: <one line class summary>
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Chris D. Jones
// Created:     Sun May 25 16:15:15 EDT 1997
// $Id: RecordStorer.cc,v 1.9 1997/09/18 21:13:14 cdj Exp $
//
// Revision history
//
// $Log: RecordStorer.cc,v $
// Revision 1.9  1997/09/18 21:13:14  cdj
// Changed Boolean to DABoolean
//
// Revision 1.8  1997/09/04 15:16:25  mkl
// moved to new bug flags
//
// Revision 1.7  1997/09/03 03:52:36  mkl
// renamed ToolBox/report to Experiment/report
//
// Revision 1.6  1997/08/18 18:00:04  mkl
// changed vector to list, because of problems with return type 'list<>::iterator' of function
//
// Revision 1.5  1997/08/16 17:45:36  cdj
// Modified to work with Proxies
//
// Revision 1.4  1997/07/11 06:20:11  mkl
// // New <Package>/<File>.h structure
// // Modified so can also compile under cxx v5.5
//
// Revision 1.3  1997/05/31 21:13:28  cdj
// No longer updated DataFieldStorer's status (DFS updates its own status)
//
// Revision 1.2  1997/05/31 20:51:26  cdj
// store now returns a status code
//
// Revision 1.1.1.1  1997/05/30 15:41:36  cdj
// First submission
//

#include "Experiment/Experiment.h"
// system include files
#include <assert.h>
#include <stdlib.h>  // For 'exit'
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <algorithm>
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "DataStorage/ProxyStorer.h"
#include "DataStorage/RecordStorer.h"


// STL classes
#include <algorithm>
#include <vector>

//
// constants, enums and typedefs
//
const string kFacilityString = "DataStorage.RecordStorer" ;

typedef vector< ProxyStorer* > StorerList ;

//
// static data member definitions
//

//
// constructors and destructor
//
RecordStorer::RecordStorer( const Stream::Type& iStream ) :
   m_stream( iStream ),
   m_storers( *( new StorerList ) )
{
   if (0 == &m_storers ) {
      delete &m_storers ;
      report( EMERGENCY ,
	      kFacilityString )
		 << "Unable to allocate memory"
		 << endl ;
      assert(false);
      exit( 1 ) ;
   }
}

// RecordStorer::RecordStorer( const RecordStorer& )
// {
// }

RecordStorer::~RecordStorer()
{
   delete &m_storers;
}

//
// assignment operators
//
// const RecordStorer& RecordStorer::operator=( const RecordStorer& )
// {
// }

//
// member functions
//
void 
RecordStorer::add( ProxyStorer& iStorer ) 
{
//
// if DataStorer can not store Records for this stream issue warning
//   and do nothing else.
//
   if ( ! iStorer.canStore( m_stream ) ) {
      report( WARNING ,
	      kFacilityString )
		 << "\n\tProxyStorer can not store "
		 << m_stream
		 << " stream! "
		 << "Will ignore it."
		 << endl ;
      return ;
   }
//
// check the ProxyStorer is not already in the list.  If it is
//   then this is an error, as each sink should only appear once.
//
   if ( m_storers.end() != find( m_storers.begin(),
				    m_storers.end(),
				    &iStorer) ) {
      report( ERROR ,
	      kFacilityString )
		 << "\n\tTrying to `add' ProxyStorer already being used."
		 << "\nAs order is important you need to `remove' is first."
		 << endl ;
      exit( 1 ) ;
   }
//
// add ProxyStorer to list and add new Proxys to Record
//
   m_storers.push_back( &iStorer ) ;
}      

void 
RecordStorer::remove( ProxyStorer& iStorer )
{
//
// find the ProxyStorer and erase it from the list if it exists
//
   StorerList::iterator itFind = find( m_storers.begin(),
					  m_storers.end(),
					  &iStorer) ;
   if( itFind != m_storers.end() ) {
      m_storers.erase( itFind ) ;
   }
#if defined(CLEO_DEBUG)
   else {
      report( WARNING ,
	      kFacilityString )
		 << "\n\tTrying to `remove' a ProxyStorer not used by "
		 << "this RecordStorer."
		 << endl ;
   }
#endif
}

void 
RecordStorer::removeAll( void )
{
   m_storers.erase( m_storers.begin() , m_storers.end() ) ;
}
 

RecordStorer::StoreStatus 
RecordStorer::store( const Frame& iFrame )
{
   //
   // if zero ProxyStorers, then there has been an error
   //
   if ( m_storers.empty() ) {
      report( ERROR ,
	      kFacilityString )
		 << "\n\tThe RecordStorer for "
		 << m_stream
		 << " has no sinks."
		 << "\nThis is a programming error."
		 << endl ;
      assert(false);
      exit( 1 ) ;
   }

   // Hand the record to each of the ProxyStorers
   const Record& record = iFrame.record( m_stream );
   
   //NOTE: Should change this to hand back a list of touched proxys
   // and the SyncValue of the Record

   StoreStatus storeStatus(kStoreNoError);
   ProxyStorer::StoreStatus worstStatus(ProxyStorer::kStoreNoError);

   StorerList::iterator itEnd = m_storers.end();
   for( StorerList::iterator itStorer = m_storers.begin();
	itStorer != itEnd;
	++itStorer){
      ProxyStorer::StoreStatus status = (*(*itStorer)).store( record );

      if(status > worstStatus){
	 worstStatus = status;
      }
   }

   //Set the correct return status
   if(worstStatus != ProxyStorer::kStoreNoError ){
      switch( worstStatus ){
	 case ProxyStorer::kStoreProblemWithSink:
	   storeStatus = kStoreProblemWithASink;
	   break;
	 case ProxyStorer::kStoreUnknownError:
	   storeStatus = kStoreUnknownSinkError;
	   break;
	 default:
	   storeStatus = kStoreUnknownError;
	   break;
      }
   }

   return storeStatus;
}

const vector< ProxyStorer* >& 
RecordStorer::storers( void ) const 
{
   return ( m_storers ) ;
}

//
// const member functions
//

DABoolean 
RecordStorer::isEmpty( void ) const
{
   return ( m_storers.empty() ) ;
}

//
// static member functions
//
