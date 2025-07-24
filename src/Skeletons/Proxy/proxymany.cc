// -*- C++ -*-
//
// Package:     <package>
// Module:      proxynameProxy
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      John Doe
// Created:     day-mon-xx
// RCS(Id)
//
// Revision history
//
// RCS(Log)
//

#include "Experiment/Experiment.h"

// system include files
#include <stdlib.h>   // for ::exit
#include <assert.h>

// user include files
#include "Experiment/report.h"

#include "DataHandler/Record.h"
#include "FrameAccess/extract.h"           
#include "FrameAccess/FATable.h"
#include "FrameAccess/FAPtrTable.h"
#include "FrameAccess/FAAutoEraseAllPtr.h"

#include "package/proxynameProxy.h"
#include "ProxyBind/ProxyBoundMethodAction.h" //need for PROXY_BIND_METHOD

#if 0
#include "Navigation/NavTrack.h" 
#endif

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
#include <vector>
//#include <set>
#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "package.proxynameProxy" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: proxymany.cc,v 1.14 2000/12/04 19:11:16 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
proxynameProxy::proxynameProxy()
   : m_ptrTable( new value_type )
{

   //bind 'auxilliary' functions that you want called when a
   // new Record on the particular Stream appears
   //bind( &proxynameProxy::boundMethod, Stream::kBeginRun );
}

// proxynameProxy::proxynameProxy( const proxynameProxy& iproxy )
// {
//   *this = iproxy;
// }

proxynameProxy::~proxynameProxy()
{
   // calls "eraseAll" internally!
   delete m_ptrTable ;
}

//
// assignment operators
//
// const proxynameProxy& proxynameProxy::operator=( const proxynameProxy& iproxy )
// {
//   if( this != &iproxy ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( iproxy );
//   }
//
//   return *this;
// }

//
// member functions
//
void
proxynameProxy::invalidateCache()
{
   if ( 0 != m_ptrTable ) {
      (*m_ptrTable).eraseAll() ;
   }
}

const proxynameProxy::value_type*
proxynameProxy::faultHandler( const Record& iRecord,
			      const DataKey& iKey )
{

   // be assertive: table should be empty 
   // else it's a programming error
   assert( 0 == (*m_ptrTable).size() );

   //If an exception is thrown in this routine, m_ptrTable will be
   // automatically emptied (which is the proper behavior).
   // Use ptrTable just like you would use m_ptrTable
   FAAutoEraseAllPtr<YourItemHere> ptrTable( m_ptrTable );

#if 0
   // ---------- sample implementation ---------------------

   // ---------- fill FAPtrTable with new items ----------------

   // this typedef here for convenience
   typedef FATable< NavTrack > NavTrackTable;

   // get the table out of the Record
   NavTrackTable table;
   extract( iRecord, table ); 

   //create YourItemHere from NavTracks
   NavTrackTable::const_iterator tableEnd( table.end() );
   for ( NavTrackTable::const_iterator item( table.begin() ) ;
         item != tableEnd ;
         ++item ) 
   {
      ptrTable->insert( new YourItemHere( (*item).identifier(),
					  *item ) ) ;
   }
#endif

   //The release returns m_ptrTable and stops ptrTable from erasing the 
   // contents of m_ptrTable.
   return ( ptrTable.release() ) ;
}

//
// const member functions
//

//
// static member functions
//

//
// 'bound' functions
//

//void
//proxynameProxy::boundMethod( const Record& iRecord )
//{
//   report( INFO, kFacilityString) <<"BoundMethod: " <<iRecord.stream().value() << std::endl;
//}

//-----------------------------------------------
// DO NOT DELETE
#include "ProxyBind/Template/ProxyBindableTemplate.cc"
template class ProxyBindableTemplate< FAPtrTable< YourItemHere > >;

PROXY_BIND_METHOD( proxynameProxy )
//-----------------------------------------------


