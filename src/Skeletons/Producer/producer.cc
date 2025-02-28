// -*- C++ -*-
//
// Package:     <prodname>
// Module:      prodname
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

// user include files
#include "prodname/prodname.h"
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
static const char* const kFacilityString = "prodname.prodname" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: producer.cc,v 1.19 2000/12/04 19:11:13 cdj Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
prodname::prodname( void )               // anal1
   : Producer( "prodname" )
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
#if 0
   registerProxyFactory( Stream::kEvent, 
			 new ProxyFactory< MyProxy >, 
			 UsageTag() );    // or UsageTag( "MyUsage" )
#endif
   // or
   //    register non-default-ctor proxy 
   //       (don't forget to write "prodname::makeMyProxy()")
#if 0
   registerProxyFactory( 
      Stream::kEvent, 
      new ProxyFactoryFunction< prodname, MyProxy >( *this, 
						     &prodname::makeMyProxy ),
      UsageTag() );    // or UsageTag( "MyUsage" )
#endif
}

// Proxy Registration Step 2:
// template instantiations for proxy factories
#if 0
#include "DataHandler/Template/ProxyFactory.cc"
template class ProxyFactory< MyProxy >;
#include "DataHandler/Template/ProxyFactoryFunction.cc"
template class ProxyFactoryFunction< prodname, MyProxy >;
#endif

// non-trivial proxyfactory producer method used above
// (if you want to use it, don't forget to declare this method 
//  in "producer.h"!)
#if 0
ProxyBase*
prodname::makeMyProxy()
{ 
   return new MyProxy( "pass me something" );
}
#endif

// prodname::prodname( const prodname& iprodname )
// {
//    *this = iprodname;
// }

prodname::~prodname()                    // anal5
{
   report( DEBUG, kFacilityString ) << "here in dtor()" << endl;
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}

//
// assignment operators
//
// const prodname& prodname::operator=( const prodname& iprodname )
// {
//   if( this != &iprodname ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( iprodname );
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
prodname::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
prodname::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}

// ---------------- standard place to book histograms ---------------
void
prodname::hist_book( HIHistoManager& )
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
