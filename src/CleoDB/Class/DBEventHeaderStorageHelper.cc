// -*- C++ -*-
//
// Package:     CleoDB
// Module:      DBEventHeaderStorageHelper
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Fri May 14 17:00:02 EDT 1999
// $Id: DBEventHeaderStorageHelper.cc,v 1.2 2001/05/23 16:47:41 bkh Exp $
//
// Revision history
//
// $Log: DBEventHeaderStorageHelper.cc,v $
// Revision 1.2  2001/05/23 16:47:41  bkh
// Add time word
//
// Revision 1.1  1999/11/04 14:43:10  mkl
// added storage helpers for DBRunHeader and DBEventHeader
//
// Revision 1.2  1999/09/30 22:38:33  cdj
// no longer need default constructor
//
// Revision 1.1.1.1  1999/09/13 21:21:45  cdj
// imported package
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
#include "CleoDB/DBEventHeaderStorageHelper.h"
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

static const char* const kFacilityString = "CleoDB.DBEventHeaderStorageHelper" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: DBEventHeaderStorageHelper.cc,v 1.2 2001/05/23 16:47:41 bkh Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
DBEventHeaderStorageHelper::DBEventHeaderStorageHelper()
{
   //registration of the different versions
   // NOTE: version number is determined by the order in which the
   // methods are registered
   registerVersion( &DBEventHeaderStorageHelper::deliverV1 );
   registerVersion( &DBEventHeaderStorageHelper::deliverV2 );
}

// DBEventHeaderStorageHelper::DBEventHeaderStorageHelper( const DBEventHeaderStorageHelper& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

//DBEventHeaderStorageHelper::~DBEventHeaderStorageHelper()
//{
//}

//
// assignment operators
//
// const DBEventHeaderStorageHelper& DBEventHeaderStorageHelper::operator=( const DBEventHeaderStorageHelper& rhs )
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
DBEventHeaderStorageHelper::implementStore( 
   SMSinkStream& iSink,
   const DBEventHeader& iData ) 
{
   iSink 
      << SM_VAR( iData, run       )   
      << SM_VAR( iData, number    )   
      << SM_VAR( iData, timeMost  )   
      << SM_VAR( iData, timeLeast )   
      ;
}

DBEventHeader* 
DBEventHeaderStorageHelper::deliverV1( SMSourceStream& iSource )
{
   
   Count run; 
   Count number; 

   iSource 
      >> run 
      >> number 
	 ;
   
   return make( DBEventHeader( 
      run    ,  
      number ,
      0 , 0               ) ); 
}

DBEventHeader* 
DBEventHeaderStorageHelper::deliverV2( SMSourceStream& iSource )
{
   
   Count  run       ; 
   Count  number    ; 
   UInt32 timeMost  ;
   UInt32 timeLeast ;

   iSource 
      >> run 
      >> number 
      >> timeMost
      >> timeLeast  
      ;

   return make( DBEventHeader( 
      run       ,  
      number    ,
      timeMost  ,
      timeLeast                ) ); 
}

//
// const member functions
//
const DBEventHeader& 
DBEventHeaderStorageHelper::getDefault() const
{
   //give constructor unique values to allow test of store and deliver 
   // functions
   static const DBEventHeader temp(
      Count  ( 1 ) ,    // run 
      Count  ( 2 ) ,    // number
      UInt32 ( 0 ) ,
      UInt32 ( 0 )   ); // times

   return temp;
}

DABoolean 
DBEventHeaderStorageHelper::compare( 
   const DBEventHeader* iNewData, 
   const DBEventHeader& iOldData ) const
{
   //write a comparison operation if operator== doesn't exist for DBEventHeader
   return (    (*iNewData).run()    == iOldData.run()    &&
	       (*iNewData).number() == iOldData.number() &&
	       (*iNewData).time()   == iOldData.time()      ) ;
}

//
// static member functions
//

//DBEventHeader*
//SMStorageHelper<DBEventHeader>::make( const DBEventHeader& iTempData ) const
//{
//   //change this line if DBEventHeader does not have a copy constructor
//   return new DBEventHeader( iTempData.run(), iTempData.number() );
//}

//------------------------------------------------------
// DO NOT DELETE 
#include "StorageManagement/SMDeliverer.h"
SM_REGISTER_VERSION_DEF( DBEventHeaderStorageHelper, DBEventHeader )

typedef DBEventHeader _store_element_;
#include "StorageManagement/instantiate_proxyhelper.h"
//------------------------------------------------------
