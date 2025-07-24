// -*- C++ -*-
//
// Package:     <DBEventHeaderProd>
// Module:      DBEventHeaderProd
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Martin Lohner
// Created:     Tue Jun  1 14:15:24 EDT 1999
// $Id: DBEventHeaderProd.cc,v 1.2 1999/11/16 14:33:15 mkl Exp $
//
// Revision history
//
// $Log: DBEventHeaderProd.cc,v $
// Revision 1.2  1999/11/16 14:33:15  mkl
// added DBEventHeader proxy with UsageTag
//
// Revision 1.1.1.1  1999/06/01 18:58:32  mkl
// imported sources
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
#include "DBEventHeaderProd/DBEventHeaderProd.h"
#include "DBEventHeaderProd/DBEventHeaderProxy.h"
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
static const char* const kFacilityString = "DBEventHeaderProd.DBEventHeaderProd" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: DBEventHeaderProd.cc,v 1.2 1999/11/16 14:33:15 mkl Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
DBEventHeaderProd::DBEventHeaderProd( void )               // anal1
   : Producer( "DBEventHeaderProd" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << std::endl;

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
   registerProxyFactory( Stream::kEvent, 
			 new ProxyFactory< DBEventHeaderProxy >, 
			 UsageTag() );    // or UsageTag( "MyUsage" )
   registerProxyFactory( Stream::kEvent, 
			 new ProxyFactory< DBEventHeaderProxy >, 
			 UsageTag( "MyPersonalUse" ) );  
}

// Proxy Registration Step 2:
// template instantiations for proxy factories
#include "DataHandler/Template/ProxyFactory.cc"
template class ProxyFactory< DBEventHeaderProxy >;

// DBEventHeaderProd::DBEventHeaderProd( const DBEventHeaderProd& iDBEventHeaderProd )
// {
//    *this = iDBEventHeaderProd;
// }

DBEventHeaderProd::~DBEventHeaderProd()                    // anal5
{
   report( DEBUG, kFacilityString ) << "here in dtor()" << std::endl;
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}

//
// assignment operators
//
// const DBEventHeaderProd& DBEventHeaderProd::operator=( const DBEventHeaderProd& iDBEventHeaderProd )
// {
//   if( this != &iDBEventHeaderProd ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( iDBEventHeaderProd );
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
DBEventHeaderProd::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << std::endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
DBEventHeaderProd::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << std::endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}

// ---------------- standard place to book histograms ---------------
void
DBEventHeaderProd::hist_book( TBHistoManager& )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << std::endl;

   // book your histograms here

}

//
// const member functions
//

//
// static member functions
//
