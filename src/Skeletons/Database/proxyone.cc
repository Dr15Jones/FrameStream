// -*- C++ -*-
//
// Package:     DBObjects
// Module:      DBYourItemHere
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
#include <stdlib.h>  // For 'exit'
#include <assert.h>
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

#include "DBObjects/DBOne.h"
#include "DBDelivery/DBHandle.h"
#include "DBDelivery/DBProxyDeliverer.h"

// STL classes
#include <vector>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "DBObjects.YourItemHere" ;

//
// static data member definitions
//

//
// member functions
//

DABoolean
DBOne< YourItemHere >::fillContents( YourItemHere*& pItem )
{
   DABoolean returnValue = true;

#ifdef CLEO_DEBUG
   report( DEBUG, kFacilityString )
      << "DBOne< YourItemHere >::fillContents()" << std::endl;
#endif

   // get ahold of proper handle for stream
   DBHandle< OBYourStream >* streamHandle 
      = (DBHandle< OBYourStream >*)m_deliverer.handle( Stream::kYourStream );
   assert( 0 != streamHandle );

   DABoolean validAssociation = (*streamHandle)()->exist_obyouritemhere();
   if( true == validAssociation ) 
   {
      ooHandle( OBYourItemHere ) handle = (*streamHandle)()->obyouritemhere();

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// You should only have to change these lines here:
// Change the "handle->type()" functions to reflect the accessor functions
// in the .ddl file
      pItem = new YourItemHere( handle->type1(),
				handle->type2() );
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
      if( 0 == pItem ) 
      {
	 report( EMERGENCY, kFacilityString )
	    << "out of memory"
	    << std::endl;
	 assert( false );
	 ::exit( 1 );
      }
   }
   else 
   {
#ifdef CLEO_DEBUG
      report( DEBUG, kFacilityString )
	 << "no YourItemHere association available" << std::endl;
#endif
      pItem = 0;
      returnValue = false;
   }

   return returnValue;
}

// ------------------------------------------------------------------
// Revision history
//
// RCS(Log)
//
