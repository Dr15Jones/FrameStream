// -*- C++ -*-
//
// Package:     CleoDB
// Module:      DBRunHeaderStorageHelper
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Martin Lohner
// Created:     Thu Nov 4 17:00:02 EDT 1999
// $Id: DBRunHeaderStorageHelper.cc,v 1.1 1999/11/04 14:43:11 mkl Exp $
//
// Revision history
//
// $Log: DBRunHeaderStorageHelper.cc,v $
// Revision 1.1  1999/11/04 14:43:11  mkl
// added storage helpers for DBRunHeader and DBEventHeader
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"
#include "CleoDB/DBRunHeaderStorageHelper.h"
#include "StorageManagement/SMSinkStream.h"
#include "StorageManagement/SMSourceStream.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "CleoDB.DBRunHeaderStorageHelper" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: DBRunHeaderStorageHelper.cc,v 1.1 1999/11/04 14:43:11 mkl Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
DBRunHeaderStorageHelper::DBRunHeaderStorageHelper()
{
   //registration of the different versions
   // NOTE: version number is determined by the order in which the
   // methods are registered
   registerVersion( &DBRunHeaderStorageHelper::deliverV1 );
}

// DBRunHeaderStorageHelper::DBRunHeaderStorageHelper( const DBRunHeaderStorageHelper& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

//DBRunHeaderStorageHelper::~DBRunHeaderStorageHelper()
//{
//}

//
// assignment operators
//
// const DBRunHeaderStorageHelper& DBRunHeaderStorageHelper::operator=( const DBRunHeaderStorageHelper& rhs )
// {
//   if( this != &rhs ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( rhs );
//   }
//
//   return *this;
// }

//
// member functions
//
void 
DBRunHeaderStorageHelper::implementStore( 
   SMSinkStream& iSink,
   const DBRunHeader& iData ) 
{
   iSink 
      << SM_VAR( iData, number )   
      ;
}

DBRunHeader* 
DBRunHeaderStorageHelper::deliverV1( SMSourceStream& iSource )
{
   
   Count number; 

   iSource 
      >> number 
	 ;
   
   return make( DBRunHeader( 

      number ) ); 
}

//
// const member functions
//
const DBRunHeader& 
DBRunHeaderStorageHelper::getDefault() const
{
   //give constructor unique values to allow test of store and deliver 
   // functions
   static const DBRunHeader temp(

      Count ( 1 ) ); // number 
   return temp;
}

DABoolean 
DBRunHeaderStorageHelper::compare( 
   const DBRunHeader* iNewData, 
   const DBRunHeader& iOldData ) const
{
   //write a comparison operation if operator== doesn't exist for DBRunHeader
   return ( (*iNewData).number() == iOldData.number() ) ;
}

//
// static member functions
//

//DBRunHeader*
//SMStorageHelper<DBRunHeader>::make( const DBRunHeader& iTempData ) const
//{
   //change this line if DBRunHeader does not have a copy constructor
//   return new DBRunHeader( iTempData );
//}

//------------------------------------------------------
// DO NOT DELETE 
#include "StorageManagement/SMDeliverer.h"
SM_REGISTER_VERSION_DEF( DBRunHeaderStorageHelper, DBRunHeader )

typedef DBRunHeader _store_element_;
#include "StorageManagement/instantiate_proxyhelper.h"
//------------------------------------------------------
