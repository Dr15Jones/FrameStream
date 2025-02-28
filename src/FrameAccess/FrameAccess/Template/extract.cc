#if !defined(FRAMEACCESS_EXTRACTOR_CC)
#define FRAMEACCESS_EXTRACTOR_CC
// -*- C++ -*-
//
// Package:     FrameAccess
// Module:      extract
// 
// Description: Template for standard extract
//
// Implimentation:
//     <Notes on implimentation>
//
// Author:      Simon Patton
// Created:     Mon Apr 14 13:44:54 EDT 1997
// $Id: extract.cc,v 1.13 2003/04/25 15:24:58 vk Exp $
//
// Revision history
//
// $Log: extract.cc,v $
// Revision 1.13  2003/04/25 15:24:58  vk
// Take advantage of new DAExceptionStack class and throw DANoProxyException when proxy is not present
//
// Revision 1.12  1999/12/10 14:20:12  cdj
// throw DANoDataException if no proxy found
//
// Revision 1.11  1999/10/09 21:53:17  cdj
// can now use ProductionTag when extracting
//
// Revision 1.10  1998/10/19 20:51:05  mkl
// changed kFacilityString to unique kExtractFacilityString
//
// Revision 1.9  1998/09/25 19:58:12  cdj
// no longer use ProxyDict
//
// Revision 1.8  1998/09/16 21:36:34  mkl
// use new bug flag for static/extern linkage of kFacilityStrings in Template .cc files
//
// Revision 1.7  1998/05/07 19:46:23  mkl
// check for null labels
//
// Revision 1.6  1998/04/09 23:19:42  cleo3
// port to egcs
//
// Revision 1.5  1997/12/20 20:04:20  cleo3
// now use Producer label for insert/extract
//
// Revision 1.4  1997/12/12 21:04:51  mkl
// changed const*const to const* for extract and insert labels -- why necessary to get working?
//
// Revision 1.3  1997/12/12 05:13:03  mkl
// undid processor label for extract and insert functions -- doesn't work
//
// Revision 1.2  1997/12/11 23:10:14  mkl
// bug fixes to new files extract, insert etc.
//
// Revision 1.1  1997/12/09 01:14:01  mkl
// Extractor --> extract
//
// Revision 1.1  1997/12/05 03:04:17  mkl
// moved sources from DataHandler
//
// Revision 1.10  1997/08/06 16:56:55  sjp
// Non-label version now uses Ifd
//
// Revision 1.9  1997/08/06 15:35:35  sjp
// Changed to handle ProxyDict
//
// Revision 1.8  1997/07/24 16:25:48  sjp
// rename "contents" call to be "get" call
//
// Revision 1.7  1997/07/22 17:37:24  sjp
// Added inlining because auto-instantiation bug
//
// Revision 1.6  1997/07/21 18:36:59  sjp
// put in CPP flags to stop double inclusion
//
// Revision 1.5  1997/07/09 18:00:28  sjp
// New <Package>/<File>.h structure
// Modified so can also compile under cxx v5.5
//
// Revision 1.4  1997/06/03 17:13:03  sjp
// CHanged to work with DataFieldextract
//
// Revision 1.3  1997/05/12 15:32:38  sjp
// Modified to handle extracts with Labels
//
// Revision 1.2  1997/04/20 18:37:45  sjp
// Renamed DD handling classes to FA classes
//
// Revision 1.1  1997/04/14 19:50:12  sjp
// Standard extractor for normal DataFields
//

#include "Experiment/Experiment.h"
// system include files

// user include files
#include "Experiment/report.h"
#include "DataHandler/RecordMethods.h"
#include "DataHandler/Record.h"
#include "FrameAccess/extract.h"

#include "DAException/DANoProxyException.h"
#include "DAException/DAExceptionStack.h"
#include "DAException/DAExceptionStackEntry.h"

// STL classes

//
// constants, enums and typedefs
//
FILESCOPE_IN_TEMPLATE_CC_BUG const char* const kExtractFacilityString 
= "FrameAccess.extract";

template < class FAContainer >
#if (defined(INCLUDE_TEMPLATE_DEFINITIONS) && defined(AUTO_INSTANTIATION_WITH_TEMPLATE_AS_ARGS_BUG))
inline
#endif /*INCLUDE_TEMPLATE_DEFINITIONS && AUTO_INSTANTIATION_WITH_TEMPLATE_AS_ARGS_BUG */
void extract( const Record& aRecord ,
	      FAContainer& aContainer ,
	      const char* aUseLabel ,
	      const char* aProducerLabel )
{
//   // construct key
//   typedef FAContainer::contents DataType;
//   static IfdDictKeyT< DataType > key( IfdTypeKey< DataType >() );
//   key.add( IfdStrKey( string( aUseLabel ) ) );
//   if( ! strcmp( aProducerLabel, "" ) ) {
//      key.add( IfdStrKey( string( aProducerLabel ) ) );
//   }
//
//   // for now just ignore producer label
//   const DataType* hold 
//      = Ifd< DataType >::get( aRecord, key ) ;

   ProxyTemplate< typename FAContainer::contents >* proxy =
      RecordMethods< typename FAContainer::contents >::extractProxy( 
	 aRecord, 
	 UsageTag(aUseLabel), 
	 ProductionTag( aProducerLabel ) );

   // make data key
   DataKey d_key = RecordMethods< typename FAContainer::contents >::makeKey(
		  UsageTag(aUseLabel), 
		  ProductionTag(aProducerLabel) );

   const typename FAContainer::contents* hold = 0;
   if( 0 != proxy ) {
      // add data key to the stack
      DAExceptionStackEntry stackEntry(d_key);
      
      hold = proxy->get( aRecord, d_key );
   } else {
      // add durable data key to the stack in order to catch it
      DAExceptionStackEntry stackEntry(d_key,DAExceptionStackEntry::kUseDurable);

      throw DANoProxyException<typename FAContainer::contents >(
	          aRecord, d_key );
   }

#ifdef CLEO_DEBUG   
   if( 0 == hold )
   {
      report( WARNING, kExtractFacilityString )
	 << "contents=0" << endl;
   }
#endif

   aContainer.setContents( hold );
}


template < class FAContainer >
#if (defined(INCLUDE_TEMPLATE_DEFINITIONS) && defined(AUTO_INSTANTIATION_WITH_TEMPLATE_AS_ARGS_BUG))
inline
#endif /*INCLUDE_TEMPLATE_DEFINITIONS && AUTO_INSTANTIATION_WITH_TEMPLATE_AS_ARGS_BUG */
void extract( const Record& aRecord ,
	      FAContainer& aContainer ,
	      const char* aUseLabel )
{
   extract( aRecord, aContainer, aUseLabel, "" );
}


template < class FAContainer >
#if (defined(INCLUDE_TEMPLATE_DEFINITIONS) && defined(AUTO_INSTANTIATION_WITH_TEMPLATE_AS_ARGS_BUG))
inline
#endif /*INCLUDE_TEMPLATE_DEFINITIONS && AUTO_INSTANTIATION_WITH_TEMPLATE_AS_ARGS_BUG */
void extract( const Record& aRecord ,
	      FAContainer& aContainer )
{
   extract( aRecord, aContainer, "", "" );
}

#endif /* FRAMEACCESS_EXTRACTOR_CC */

