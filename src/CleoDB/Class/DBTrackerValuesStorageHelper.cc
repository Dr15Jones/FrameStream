// -*- C++ -*-
//
// Package:     CleoDB
// Module:      DBTrackerValuesStorageHelper
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Fri May 14 17:00:02 EDT 1999
// $Id: DBTrackerValuesStorageHelper.cc,v 1.2 2000/06/16 00:57:54 marsh Exp $
//
// Revision history
//
// $Log: DBTrackerValuesStorageHelper.cc,v $
// Revision 1.2  2000/06/16 00:57:54  marsh
// Purged tool box typedefs.
//
// Revision 1.1  2000/03/01 00:40:18  cdj
// first submission
//
// Revision 1.4  2000/01/21 21:07:39  cdj
// helper skeletons now include SMPackInfo.h
//
// Revision 1.3  1999/10/18 18:15:05  cdj
// now uses instantiate_proxyhelper.h
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
#include "CleoDB/DBTrackerValuesStorageHelper.h"
#include "StorageManagement/SMSinkStream.h"
#include "StorageManagement/SMSourceStream.h"
#include "StorageManagement/SMPackInfo.h" //defines sm_pack*

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

static const char* const kFacilityString = "CleoDB.DBTrackerValuesStorageHelper" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: DBTrackerValuesStorageHelper.cc,v 1.2 2000/06/16 00:57:54 marsh Exp $";
static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
DBTrackerValuesStorageHelper::DBTrackerValuesStorageHelper()
{
   //registration of the different versions
   // NOTE: version number is determined by the order in which the
   // methods are registered
   registerVersion( &DBTrackerValuesStorageHelper::deliverV1 );
}

// DBTrackerValuesStorageHelper::DBTrackerValuesStorageHelper( const DBTrackerValuesStorageHelper& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

//DBTrackerValuesStorageHelper::~DBTrackerValuesStorageHelper()
//{
//}

//
// assignment operators
//
// const DBTrackerValuesStorageHelper& DBTrackerValuesStorageHelper::operator=( const DBTrackerValuesStorageHelper& rhs )
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
DBTrackerValuesStorageHelper::implementStore( 
   SMSinkStream& iSink,
   const DBTrackerValues& iData ) 
{
   const char* const massNames[] = {"photonMass",
				    "electronMass",
				    "muonMass",
				    "pionMass",
				    "kaonMass",
				    "protonMass",
				    "exitElectronMass",
				    "exitMuonMass",
				    "exitPionMass",
				    "exitKaonMass",
				    "exitProtonMass" };

   GeV packInfo[][2] = {{  1E-6, 1E-5 },
			{ 0.0005, 0.00052 },
			{ 0.105 , 0.106 },
			{ 0.138 , 0.141 },
			{ 0.493 , 0.494 },
			{ 0.937 , 0.939},
			{ 0.0005, 0.00052 },
			{ 0.105 , 0.106 },
			{ 0.138 , 0.141 },
			{ 0.493 , 0.494 },
			{ 0.937 , 0.939} } ;

   assert( sizeof(massNames)/sizeof(const char*) == DBCandidate::kMaxHypo );

   iSink 
      << sm_pack(SM_VAR( iData, magneticField().x ), -10.0, 10.0, 1E-5)   
      << sm_pack(SM_VAR( iData, magneticField().y ), -10.0, 10.0, 1E-5)   
      << sm_pack(SM_VAR( iData, magneticField().z ), -20.0, 20.0, 1E-5);

   for( unsigned int index = 0; index < DBCandidate::kMaxHypo; ++index ) {
      iSink << sm_pack_fraction( sm_field(massNames[index], 
					  iData.mass( (DBCandidate::Hypo)
						      (index) ) ),
				 packInfo[index][0],
				 packInfo[index][1],
				 1E-6);
   }
}

DBTrackerValues* 
DBTrackerValuesStorageHelper::deliverV1( SMSourceStream& iSource )
{
   double x,y,z;
   GeV masses[DBCandidate::kMaxHypo]; 

   iSource 
      >> x >>y >>z ;
   for( unsigned int index = 0; index < DBCandidate::kMaxHypo; ++index ) {
      iSource >> masses[index];
   }
   
   HepVector3D magneticField(x,y,z);
 
   return make( DBTrackerValues( 
      magneticField,  
      masses ) ); 
}

//
// const member functions
//
const DBTrackerValues& 
DBTrackerValuesStorageHelper::getDefault() const
{
   GeV masses[DBCandidate::kMaxHypo] = { 0.,
					 0.000511,
					 0.1057,
					 0.1396,
					 0.4937,
					 0.9383,
					 0.000511,
					 0.1057,
					 0.1396,
					 0.4937,
					 0.9383 };

   //give constructor unique values to allow test of store and deliver 
   // functions
   static const DBTrackerValues temp(
      HepVector3D ( 0, 0.01, -14.9 ), // aMagneticField 
      masses ); // aMasses 
   return temp;
}

DABoolean 
DBTrackerValuesStorageHelper::compare( 
   const DBTrackerValues* iNewData, 
   const DBTrackerValues& iOldData ) const
{
   //write a comparison operation if operator== doesn't exist for DBTrackerValues
   return (*iNewData == iOldData ) ;
}

//
// static member functions
//

//DBTrackerValues*
//SMStorageHelper<DBTrackerValues>::make( const DBTrackerValues& iTempData ) const
//{
   //change this line if DBTrackerValues does not have a copy constructor
//   return new DBTrackerValues( iTempData );
//}

//------------------------------------------------------
// DO NOT DELETE 
#include "StorageManagement/SMDeliverer.h"
SM_REGISTER_VERSION_DEF( DBTrackerValuesStorageHelper, DBTrackerValues )

typedef DBTrackerValues _store_element_;
#include "StorageManagement/instantiate_proxyhelper.h"
//------------------------------------------------------
