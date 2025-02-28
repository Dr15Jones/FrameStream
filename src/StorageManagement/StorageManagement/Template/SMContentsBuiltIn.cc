// -*- C++ -*-
#if !defined(STORAGEMANAGEMENT_SMCONTENTSBUILTIN_CC)
#define STORAGEMANAGEMENT_SMCONTENTSBUILTIN_CC
//
// Package:     <StorageManagement>
// Module:      SMContentsBuiltIn
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Thu Sep 30 21:22:01 EDT 1999
// $Id: SMContentsBuiltIn.cc,v 1.3 2000/10/01 15:00:18 cdj Exp $
//
// Revision history
//
// $Log: SMContentsBuiltIn.cc,v $
// Revision 1.3  2000/10/01 15:00:18  cdj
// properly handle lack of iterator_traits on Solaris
//
// Revision 1.2  2000/04/27 21:07:29  mkl
// moved 'begin/endObject' logic to SMStorageHelper::deliver( SourceStream, iVersion ) function
//
// Revision 1.1  1999/10/11 22:00:48  cdj
// added Lattice storage code
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
#include "StorageManagement/SMContentsBuiltIn.h"
#include "StorageManagement/SMSinkStream.h"
#include "StorageManagement/SMField.h"
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

//static const char* const kFacilityString = "StorageManagement.SMContentsBuiltIn" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
//static const char* const kIdString  = "$Id: SMContentsBuiltIn.cc,v 1.3 2000/10/01 15:00:18 cdj Exp $";
//static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
//SMContentsBuiltIn::SMContentsBuiltIn()
//{
//}

// SMContentsBuiltIn::SMContentsBuiltIn( const SMContentsBuiltIn& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

//SMContentsBuiltIn::~SMContentsBuiltIn()
//{
//}

//
// assignment operators
//
// const SMContentsBuiltIn& SMContentsBuiltIn::operator=( const SMContentsBuiltIn& rhs )
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
SMContentsBuiltIn<Iterator>::size() const
{
   unsigned long count = 0;
   for( Iterator itItem = m_begin; itItem != m_end; ++itItem, ++count );

   return count;
}

template< class Iterator>
void
SMContentsBuiltIn<Iterator>::store( SMSinkStream& iSink ) const
{
   for( Iterator itItem = m_begin; itItem != m_end; ++itItem ) {
      iSink << sm_field( "value", *itItem ) ;
   }
}

template< class Iterator>
const TypeTag&
SMContentsBuiltIn<Iterator>::typeTag() const
{
   return getTypeTag();
}

//
// static member functions
//
template< class Iterator>
const TypeTag&
SMContentsBuiltIn<Iterator>::getTypeTag()
{
   static const TypeTag tag = RecordMethods< typename iterator_traits< Iterator>::value_type >::makeKey("","").type() ;
   return tag;
}

#endif /* STORAGEMANAGEMENT_SMCONTENTSBUILTIN_CC */
