// -*- C++ -*-
#if !defined(STORAGEMANAGEMENT_SMCONTENTS_CC)
#define STORAGEMANAGEMENT_SMCONTENTS_CC
//
// Package:     StorageManagement
// Module:      SMContents
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Wed May 19 14:14:19 EDT 1999
// $Id: SMContents.cc,v 1.6 2002/08/09 13:56:24 cdj Exp $
//
// Revision history
//
// $Log: SMContents.cc,v $
// Revision 1.6  2002/08/09 13:56:24  cdj
// worked around static_cast bug is CC 4.2
//
// Revision 1.5  2002/08/08 20:54:19  cdj
// replaced inappropriate use of reinterpret_cast with static_cast
//
// Revision 1.4  2000/10/01 15:00:17  cdj
// properly handle lack of iterator_traits on Solaris
//
// Revision 1.3  2000/04/27 21:07:29  mkl
// moved 'begin/endObject' logic to SMStorageHelper::deliver( SourceStream, iVersion ) function
//
// Revision 1.2  1999/10/11 21:55:53  cdj
// avoid multiple inclusion of the file
//
// Revision 1.1.1.1  1999/09/13 21:21:42  cdj
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
#include <assert.h>
#include <iterator>

// user include files
//#include "Experiment/report.h"
#include "StorageManagement/SMContents.h"
#include "StorageManagement/SMStorageHelperManager.h"
#include "StorageManagement/SMStorageHelper.h"
#include "StorageManagement/SMSinkStream.h"
#include "DataHandler/RecordMethods.h"
#include "DataHandler/DataKey.h"

#include "STLUtility/iterator_traits_fix.h"

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

//static const char* const kFacilityString = "StorageManagement.SMContents" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
//static const char* const kIdString  = "$Id: SMContents.cc,v 1.6 2002/08/09 13:56:24 cdj Exp $";
//static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
//template< class Iterator>
//SMContents::SMContents()
//{
//}

// SMContents::SMContents( const SMContents& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

//SMContents::~SMContents()
//{
//}

//
// assignment operators
//
// const SMContents& SMContents::operator=( const SMContents& rhs )
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

//
// const member functions
//
template< class Iterator>
SMContentsBase::size_type
SMContents<Iterator>::size() const
{
   unsigned long count = 0;
   for( Iterator itItem = m_begin; itItem != m_end; ++itItem, ++count );

   return count;
}

template< class Iterator>
void
SMContents<Iterator>::store( SMSinkStream& iSink ) const
{
   typedef SMStorageHelper< typename iterator_traits<Iterator>::value_type >
      Helper;

   //in future should use dynamic_cast
   // NOTE: CC 4.2 can not handle static_cast here
   Helper& helper = (Helper& ) (storageHelper() );
   for( Iterator itItem = m_begin; itItem != m_end; ++itItem ) {
      helper.store( iSink, *itItem );
   }
}

template< class Iterator>
const TypeTag&
SMContents<Iterator>::typeTag() const
{
   return getTypeTag();
}

//
// static member functions
//
template< class Iterator>
const TypeTag&
SMContents<Iterator>::getTypeTag()
{
   static const TypeTag tag = RecordMethods< typename iterator_traits< Iterator>::value_type >::makeKey("","").type() ;
   return tag;
}

template< class Iterator>
SMStorageHelperBase&
SMContents<Iterator>::storageHelper() {
   SMStorageHelperBase* helper = 0;
   if( 0 == helper ) {
      SMStorageHelperManager::iterator found = 
	 SMStorageHelperManager::instance().find( getTypeTag() );
      assert( found != SMStorageHelperManager::instance().end() );

      helper = ( *found );
   }

   return *helper;
}

#endif /* STORAGEMANAGEMENT_SMCONTENTS_CC */

