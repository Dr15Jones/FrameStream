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
#include "OBSchema/Generated/OBYourItemHeres_ref.h"
#include "OBSchema/Generated/OBYourItemHeres.h"

#include "OBSchema/Generated/OBYourStream.h"

#include "DBStorage/DBProxyStorer.h"
#include "DBObjects/DBManyWriter.h"

// STL classes
#include <vector>

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "DBObjects.YourItemHere";

//
// static data member definitions
//

//
// const member functions
//
DABoolean
DBManyWriter< YourItemHere >::storeContents( const YourItemHere& iItem,
					     Count iSize,
					     ClusteringHint& iClusteringHint
   ) const
{
   DABoolean storeStatus = true;

#ifdef CLEO_DEBUG
   report( DEBUG, kFacilityString )
      << "DBManyWriter< YourItemHere >::storeContents()" 
      << std::endl;
#endif

   // get ahold of proper handle for stream
   ooHandle( OBYourStream ) streamHandle 
      = m_storer.handle( Stream::kYourStream );

   // create new OBBank< OBYourItemHere > if necessary
   ooHandle( OBBank< OBYourItemHere > ) bank;
   if( streamHandle->exist_obyouritemheres() == false ) 
   {
#ifdef CLEO_DEBUG
      report( DEBUG, kFacilityString )
	 << "creating new OBBank< OBYourItemHere >" << std::endl;
#endif
      bank = new(iClusteringHint) OBBank< OBYourItemHere >( iSize );
      ooStatus status = streamHandle->set_obyouritemheres( bank );

      storeStatus = ( status == oocSuccess ) ? true : false;
      if( false == storeStatus ) return storeStatus;
   }
   bank = streamHandle->obyouritemheres();

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// You should only have to change these lines here:
// Change the "iItem->function()" functions to reflect the accessor functions
// in your (memory) class
   OBYourItemHere storable( iItem.identifier(),
			    iItem.name().c_str(),
			    iItem.type1(),
			    iItem.type2()
      );
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

   ooStatus status = bank->push_back( storable );

   storeStatus = ( status == oocSuccess ) ? true : false;

   return storeStatus;
}

const std::string&
DBManyWriter< YourItemHere >::storageName() const
{
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Please fill in the storage category name:
// (e.g. Tracking, Showering, Misc, etc.)
   static std::string returnValue( "Misc" );
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
   return returnValue;
}


// ------------------------------------------------------------------
// Revision history
//
// RCS(Log)
//
