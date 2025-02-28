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

#include <memory>  //for auto_ptr

// user include files
#include "Experiment/report.h"

#include "DataHandler/Record.h"
#include "FrameAccess/extract.h"           
#include "FrameAccess/FATable.h"

#include "package/proxynameProxy.h"
#include "ProxyBind/ProxyBoundMethodAction.h" //need for PROXY_BIND_METHOD

#if 0
#include "TrackDelivery/TDKinematicPionFit.h" 
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
static const char* const kIdString  = "$Id: proxyone.cc,v 1.12 2000/12/04 19:11:16 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
proxynameProxy::proxynameProxy()
   : m_proxyname( 0 )
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
   delete m_proxyname ;
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
   delete m_proxyname ;
   m_proxyname = 0 ;
}

const proxynameProxy::value_type*
proxynameProxy::faultHandler( const Record& iRecord,
			      const DataKey& iKey )
{

   // be assertive: there should be no cached data at this point, else
   // it's a programming error
   assert( 0 == m_proxyname );

   //if an exception is thrown during this function, p_proxyname will
   // automatically delete the object it is refering to
   auto_ptr<YourItemHere> p_proxyname;
#if 0
// ---------------- Sample implementation -------------------
   // ---------- create the new object --------------------

   // first get ahold of 
   FATable< TDKinematicPionFit > pions ; 
   extract( iRecord, pions ); 


   HepVector3D varproxyname; 

   // loop over pions with new STL-style iterator for loop 
   FATable< TDKinematicPionFit >::const_iterator endIter = pions.end(); 
   for( FATable< TDKinematicPionFit >::const_iterator pion = pions.begin();
        pion != endIter; 
        ++pion ) 
   { 
      varproxyname += (*pion).momentum(); 
   } 

   //have p_proxyname hold onto the new object
   p_proxyname.reset( new YourItemHere( varproxyname ) );
#endif
   
   //Since no exception happened, tell p_proxyname to give its pointer to
   // m_proxyname
   return ( m_proxyname = p_proxyname.release() ) ;
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
//   report( INFO, kFacilityString) <<"BoundMethod: " <<iRecord.stream().value() << endl;
//}

//-----------------------------------------------
// DO NOT DELETE
#include "ProxyBind/Template/ProxyBindableTemplate.cc"
template class ProxyBindableTemplate< YourItemHere >;

PROXY_BIND_METHOD( proxynameProxy )
//-----------------------------------------------

