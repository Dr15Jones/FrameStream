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
#include "Experiment/report.h" // For error report

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// If necessary, change "YourLibrary" to the correct library
#include "YourLibrary/YourItemHere.h"
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#include "OBSchema/Generated/OBYourItemHeres_ref.h"
#include "OBSchema/Generated/OBYourItemHeres.h"

#include "OBSchema/Generated/OBYourStream.h"

#include "FrameAccess/FAPtrTable.h"
#include "DBObjects/DBMany.h"
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
DBMany< YourItemHere >::fillContents( FAPtrTable< YourItemHere >& aTable )
{
   DABoolean returnValue = true;

#ifdef CLEO_DEBUG
   report( DEBUG, kFacilityString )
      << "DBMany< YourItemHere >::fillContents()" << endl;
#endif

   // get ahold of proper handle for stream
   DBHandle< OBYourStream >* streamHandle
      = (DBHandle< OBEvent >*)m_deliverer.handle( Stream::kYourStream );
   assert( 0 != streamHandle );

   DABoolean validAssociation = (*streamHandle)()->exist_obyouritemheres();
   if( true == validAssociation ) 
   {
      ooHandle( OBBank< OBYourItemHere > ) bank
	 = (*streamHandle)()->obyouritemheres();

      d_Iterator<OBYourItemHere> iter = bank->getIterator();
      while( iter.not_done() ) 
      {
	 // get next in line
	 const OBYourItemHere& item = iter.get_element();
	 YourItemHere* tmp( 
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// You should only have to change these lines here:
// Change the "item->function()" functions to reflect the accessor functions
// in the .ddl file
	    new YourItemHere( item.identifier(),
			      item.name(),
			      item.type1(),
			      item.type2() )
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	    ); 
	 
	 if( 0 == tmp ) 
	 {
	    report( EMERGENCY, kFacilityString )
	       << "out of memory"
	       << endl;
	    assert( false );
	    exit( 1 );
	 }	

	 // insert in table
	 aTable.insert( tmp ) ;

	 // increment
	 ++iter;
      }
   }
   else 
   {
#ifdef CLEO_DEBUG
      report( DEBUG, kFacilityString )
	 << "no YourItemHeres available" << endl;
#endif CLEO_DEBUG
      returnValue = false;
   }

   return returnValue;
}


// ------------------------------------------------------------------
// Revision history
//
// RCS(Log)
//
