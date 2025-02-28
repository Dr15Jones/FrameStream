#if !defined(STORAGEMANAGEMENT_SMMAKECONTENTS_CC)
#define STORAGEMANAGEMENT_SMMAKECONTENTS_CC
// -*- C++ -*-
//
// Package:     <StorageManagement>
// Module:      SMMakeContents
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Fri May 21 14:09:18 EDT 1999
// $Id: SMMakeContents.cc,v 1.7 2002/08/11 11:53:14 cdj Exp $
//
// Revision history
//
// $Log: SMMakeContents.cc,v $
// Revision 1.7  2002/08/11 11:53:14  cdj
// changed previous change to static_cast to C style cast to work around bug in CC 4.2
//
// Revision 1.6  2002/08/08 20:54:20  cdj
// replaced inappropriate use of reinterpret_cast with static_cast
//
// Revision 1.5  2000/05/12 15:44:03  cdj
// made changes to be more C++ standards compliant (needed for g++)
//
// Revision 1.4  2000/04/27 21:47:57  mkl
// undo use of 'size_type' in external function
//
// Revision 1.3  2000/04/27 21:07:30  mkl
// moved 'begin/endObject' logic to SMStorageHelper::deliver( SourceStream, iVersion ) function
//
// Revision 1.2  2000/04/06 14:59:08  cdj
// Now expects an insert iterator with value_type that is a pointer
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
#include "StorageManagement/SMMakeContents.h"
#include "StorageManagement/SMStorageHelperManager.h"
#include "StorageManagement/SMStorageHelper.h"
#include "StorageManagement/SMSourceStream.h"
#include "StorageManagement/sm_iterator_traits.h"

#include "DataHandler/RecordMethods.h"
#include "DataHandler/DataKey.h"

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

//static const char* const kFacilityString = "StorageManagement.SMMakeContents" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
//static const char* const kIdString  = "$Id: SMMakeContents.cc,v 1.7 2002/08/11 11:53:14 cdj Exp $";
//static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
//SMMakeContents::SMMakeContents()
//{
//}

// SMMakeContents::SMMakeContents( const SMMakeContents& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

//SMMakeContents::~SMMakeContents()
//{
//}

//
// assignment operators
//
// const SMMakeContents& SMMakeContents::operator=( const SMMakeContents& rhs )
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

//The value_type of our Iterator template parameter is a pointer
//  but we need the type of the pointer
template < class T, class Iterator>
inline
void
smmakecontents_deliver( T*, 
			SMSourceStream& iSource, 
			unsigned int iSizeOfContainer,
			const Iterator& iIterator,
			SMStorageHelperBase& iHelperBase ) {

   typedef SMStorageHelper< T > Helper;
   
   //in future should use dynamic_cast
   // NOTE: CC 4.2 can not use static_cast here
   Helper& helper = ( Helper& ) ( iHelperBase );
   Iterator inserter = iIterator;

   unsigned int version = iSource.versionUsed( helper.typeTag() );
   for( unsigned long index = 0; 
	index != iSizeOfContainer; 
	++index, ++inserter ) {
      *inserter = helper.deliver( iSource, version );
   }
}

template <class Iterator>
void 
SMMakeContents<Iterator>::deliver( SMSourceStream& iSource,
				   size_type iSizeOfContainer ) const
{
   //need to use a helper function to deduce the type that the pointer
   //  iDummy is pointing to 
   typename sm_iterator_traits<Iterator>::value_type iDummy = 0;
   smmakecontents_deliver( iDummy, 
			   iSource,
			   iSizeOfContainer,
			   m_inserter,
			   storageHelper() );
}

template <class Iterator>
const TypeTag& 
SMMakeContents<Iterator>::typeTag() const
{
   return getTypeTag();
}

//
// static member functions
//
template< class T>
inline
const TypeTag&
smmakecontents_getTypeTag( T* )
{
   return RecordMethods< T >::makeKey("","").type() ;
}

template< class Iterator>
const TypeTag&
SMMakeContents<Iterator>::getTypeTag()
{
   typename sm_iterator_traits< Iterator>::value_type iDummy = 0;
   static const TypeTag tag = smmakecontents_getTypeTag(iDummy);
   return tag;
}

template< class Iterator>
SMStorageHelperBase&
SMMakeContents<Iterator>::storageHelper() {
   SMStorageHelperBase* helper = 0;
   if( 0 == helper ) {
      SMStorageHelperManager::iterator found = 
	 SMStorageHelperManager::instance().find( getTypeTag() );
      assert( found != SMStorageHelperManager::instance().end() );

      helper = ( *found );
   }

   return *helper;
}


#endif /* STORAGEMANAGEMENT_SMMAKECONTENTS_CC */
