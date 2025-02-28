#if !defined(STORAGEMANAGEMENT_SMFILLCONTENTS_CC)
#define STORAGEMANAGEMENT_SMFILLCONTENTS_CC
// -*- C++ -*-
//
// Package:     <StorageManagement>
// Module:      SMFillContents
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Tue Jun  8 09:04:14 EDT 1999
// $Id: SMFillContents.cc,v 1.3 2000/05/12 15:44:02 cdj Exp $
//
// Revision history
//
// $Log: SMFillContents.cc,v $
// Revision 1.3  2000/05/12 15:44:02  cdj
// made changes to be more C++ standards compliant (needed for g++)
//
// Revision 1.2  2000/04/27 21:07:29  mkl
// moved 'begin/endObject' logic to SMStorageHelper::deliver( SourceStream, iVersion ) function
//
// Revision 1.1.1.1  1999/09/13 21:21:43  cdj
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

// user include files
//#include "Experiment/report.h"
#include "StorageManagement/SMFillContents.h"
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

//static const char* const kFacilityString = "StorageManagement.SMFillContents" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
//static const char* const kIdString  = "$Id: SMFillContents.cc,v 1.3 2000/05/12 15:44:02 cdj Exp $";
//static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
//SMFillContents::SMFillContents()
//{
//}

// SMFillContents::SMFillContents( const SMFillContents& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

//SMFillContents::~SMFillContents()
//{
//}

//
// assignment operators
//
// const SMFillContents& SMFillContents::operator=( const SMFillContents& rhs )
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
template <class Iterator>
void 
SMFillContents<Iterator>::deliver( SMSourceStream& iSource,
				   size_type iSizeOfContainer ) const
{
   //create a temporary variable which we will fill
   typename sm_iterator_traits<Iterator>::value_type temp;

   Iterator inserter = m_inserter;

   for( unsigned long index = 0; 
	index != iSizeOfContainer; 
	++index, ++inserter ) {
      iSource >> temp;
      *inserter = temp;
   }
}

template <class Iterator>
const TypeTag& 
SMFillContents<Iterator>::typeTag() const
{
   return getTypeTag();
}

//
// static member functions
//
template< class Iterator>
const TypeTag&
SMFillContents<Iterator>::getTypeTag()
{
   static const TypeTag tag = RecordMethods< typename sm_iterator_traits< Iterator>::value_type >::makeKey("","").type() ;
   return tag;
}

#endif /* STORAGEMANAGEMENT_SMFILLCONTENTS_CC */
