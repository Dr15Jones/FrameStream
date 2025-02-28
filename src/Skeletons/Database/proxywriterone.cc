// -*- C++ -*-
//
// Package:     DBObjects
// Module:      DBYourItemHereWriter
// 
// Description: Specialize the faultHandler function for YourItemHere
//
// Implementation:
//     <Notes on implementation>
//
// Author:      John Doe
// Created:     day-mon-xx
// RCS(Id)
//
// Revision history at end of file
//

#include "Experiment/Experiment.h"

// system include files
#include "oo.h"
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// If necessary, change "YourLibrary" to the correct library
#include "YourLibrary/YourItemHere.h"
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#include "OBSchema/Generated/OBYourItemHere_ref.h"
#include "OBSchema/Generated/OBYourItemHere.h"

#include "OBSchema/Generated/OBYourStream.h"

#include "DBStorage/DBProxyStorer.h"
#include "DBObjects/DBOneWriter.h"

// STL classes
#include <vector>

//
// constants, enums and typedefs
//

//
// static data member definitions
//
static const char* const kFacilityString = "DBObjects.YourItemHere";

//
// const member functions
//

DABoolean
DBOneWriter< YourItemHere >::storeContents( const YourItemHere& iItem,
					    ClusteringHint& iClusteringHint
   ) const
{
   DABoolean storeStatus = true;

#ifdef CLEO_DEBUG   
   report( DEBUG, kFacilityString )
      << "DBOneWriter< YourItemHere >::storeContents()" << endl;
#endif   

   // get ahold of proper handle for stream
   ooHandle( OBYourStream ) streamHandle 
      = m_storer.handle( Stream::kYourStream );

   // create object in db
   ooHandle( OBYourItemHere ) storable
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// You should only have to change these lines here:
// Change the "iItem->type()" functions to reflect the accessor functions
// in your (memory) class
      = new(iClusteringHint) OBYourItemHere( iItem.type1(),
					     iItem.type2() );
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

   // and attach to stream handle
   ooStatus status = streamHandle->set_obyouritemhere( storable );

   storeStatus = ( status == oocSuccess ) ? true : false;

   return storeStatus;
}

const string&
DBOneWriter< YourItemHere >::storageName() const
{
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Please fill in the storage category name:
// (e.g. Tracking, Showering, Misc, etc.)
   static string returnValue( "Misc" );
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   return returnValue;
}


// ------------------------------------------------------------------
// Revision history
//
// RCS(Log)
//
