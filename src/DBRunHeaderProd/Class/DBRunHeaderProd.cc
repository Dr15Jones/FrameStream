// -*- C++ -*-
//
// Package:     <DBRunHeaderProd>
// Module:      DBRunHeaderProd
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Andreas Wolf
// Created:     Thu Jul 22 12:18:25 EDT 1999
// $Id: DBRunHeaderProd.cc,v 1.1.1.1 1999/07/22 18:20:51 aw Exp $
//
// Revision history
//
// $Log: DBRunHeaderProd.cc,v $
// Revision 1.1.1.1  1999/07/22 18:20:51  aw
// Imported initial DBRunHeaderProd sources
//
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
#include <string>
#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "DBRunHeaderProd/DBRunHeaderProd.h"
#include "DBRunHeaderProd/DBRunHeaderProxy.h"
#include "Experiment/report.h"

#include "DataHandler/RecordMethods.h"
#include "DataHandler/ProxyFactory.h"
#include "DataHandler/ProxyFactoryFunction.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
#include <string>
#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "DBRunHeaderProd.DBRunHeaderProd" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: DBRunHeaderProd.cc,v 1.1.1.1 1999/07/22 18:20:51 aw Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
DBRunHeaderProd::DBRunHeaderProd( void )               // anal1
   : Producer( "DBRunHeaderProd" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ----- register proxy factories ------------------
   // (Please see the "ProxyExample" library for examples!)
   //
   // Two steps: 1) use "registerProxyFactory" to register
   //            2) instantiate ProxyFactory/Function
   //               (if you're using the standard templated factories;
   //                you may of course roll your own!)

   // Proxy Registration Step 1:
   // either
   //    register default-ctor proxy
   registerProxyFactory( Stream::kBeginRun, 
			 new ProxyFactory< DBRunHeaderProxy >, 
			 UsageTag() );    // or UsageTag( "MyUsage" )
}

// Proxy Registration Step 2:
// template instantiations for proxy factories
#include "DataHandler/Template/ProxyFactory.cc"
template class ProxyFactory< DBRunHeaderProxy >;

// DBRunHeaderProd::DBRunHeaderProd( const DBRunHeaderProd& iDBRunHeaderProd )
// {
//    *this = iDBRunHeaderProd;
// }

DBRunHeaderProd::~DBRunHeaderProd()                    // anal5
{
   report( DEBUG, kFacilityString ) << "here in dtor()" << endl;
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}

//
// assignment operators
//
// const DBRunHeaderProd& DBRunHeaderProd::operator=( const DBRunHeaderProd& iDBRunHeaderProd )
// {
//   if( this != &iDBRunHeaderProd ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( iDBRunHeaderProd );
//   }
//
//   return *this;
// }

//
// member functions
//

// ------------ methods for beginning/end "Interactive" ------------
// --------------------------- init method -------------------------
void
DBRunHeaderProd::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
DBRunHeaderProd::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}

// ---------------- standard place to book histograms ---------------
void
DBRunHeaderProd::hist_book( TBHistoManager& )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

}

//
// const member functions
//

//
// static member functions
//
