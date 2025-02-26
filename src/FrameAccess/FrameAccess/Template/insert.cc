#if !defined(FRAMEACCESS_INSERTOR_CC)
#define FRAMEACCESS_INSERTOR_CC
// -*- C++ -*-
//
// Package:     <FrameAccess>
// Module:      insert
// 
// Description: Template for standard insert
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Martin Lohner
// Created:     Wed Dec  3 10:52:34 EST 1997
// $Id: insert.cc,v 1.10 2000/06/30 20:58:53 cdj Exp $
//
// Revision history
//
// $Log: insert.cc,v $
// Revision 1.10  2000/06/30 20:58:53  cdj
// removed last dependence on ProxyDict
//
// Revision 1.9  1998/10/20 17:18:54  mkl
// protect against multiple inclusions
//
// Revision 1.8  1998/09/25 19:58:13  cdj
// no longer use ProxyDict
//
// Revision 1.7  1998/09/16 21:36:35  mkl
// use new bug flag for static/extern linkage of kFacilityStrings in Template .cc files
//
// Revision 1.6  1998/05/07 19:46:23  mkl
// check for null labels
//
// Revision 1.5  1998/05/07 19:12:20  mkl
// support insertion without user and/or producer label
//
// Revision 1.4  1997/12/16 22:32:35  mkl
// fixes to insert function
//
// Revision 1.3  1997/12/12 21:04:52  mkl
// changed const*const to const* for extract and insert labels -- why necessary to get working?
//
// Revision 1.2  1997/12/12 05:13:04  mkl
// undid processor label for extract and insert functions -- doesn't work
//
// Revision 1.1  1997/12/11 23:11:04  mkl
// new files insert and ValueProxy
//

#include "Experiment/Experiment.h"

// system include files
#include <string.h> // for strcmp
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"

#include "DataHandler/Frame.h"
#include "FrameAccess/insert.h"
#include "FrameAccess/ValueProxy.h"

#include "DataHandler/RecordMethods.h"
#include "DataHandler/DataKey.h"

//#include "Processor/Producer.h"

// STL classes

//
// constants, enums and typedefs
//

FILESCOPE_IN_TEMPLATE_CC_BUG const char* const kInsertFacilityString 
= "FrameAccess.insert" ;

template < class DataType > 
#if (defined(INCLUDE_TEMPLATE_DEFINITIONS) && defined(AUTO_INSTANTIATION_WITH_TEMPLATE_AS_ARGS_BUG))
inline
#endif /*INCLUDE_TEMPLATE_DEFINITIONS && AUTO_INSTANTIATION_WITH_TEMPLATE_AS_ARGS_BUG */
DABoolean insert( Frame& aFrame ,
		  const DataType* aValue ,
		  const char* aUseLabel,
		  const char* aProducerLabel )
{   
   DABoolean returnValue = true;

//   // construct key

   // insert proxy (with value) into record with key
   if( string( aUseLabel) == string( "" ) ) {
      returnValue = RecordMethods< DataType >::insertProxy( 
	 aFrame.record( aFrame.stopStream() ), 
	 new ValueProxy< DataType >( aValue ),
	 UsageTag(), ProductionTag() );
   }
   else {
      returnValue = RecordMethods< DataType >::insertProxy( 
	 aFrame.record( aFrame.stopStream() ), 
	 new ValueProxy< DataType >( aValue ),
	 UsageTag( aUseLabel ), ProductionTag() );
   }

   if( false == returnValue )
   {
      report( ERROR, kInsertFacilityString )
	 << "couldn't insert transient proxy" << endl;
   }
   
   return returnValue;
}

#if 0 /* commented out */

template < class DataType > 
#if (defined(INCLUDE_TEMPLATE_DEFINITIONS) && defined(AUTO_INSTANTIATION_WITH_TEMPLATE_AS_ARGS_BUG))
inline
#endif /*INCLUDE_TEMPLATE_DEFINITIONS && AUTO_INSTANTIATION_WITH_TEMPLATE_AS_ARGS_BUG */
DABoolean insert( Frame& aFrame,
		  const DataType* aValue,
		  const char* aUseLabel, 
		  const Producer& producer )
{
#if defined(OLD_CXX_STRING_CLASS_BUG)       
   const char* producerLabel = (const char*)producer.identifier();
#else
   const char* producerLabel = (producer.identifier()).c_str();
#endif

   return insert( aFrame, aValue, aUseLabel, producerLabel );
}

#endif /* commented out */


#endif /* FRAMEACCESS_INSERTOR_CC */
