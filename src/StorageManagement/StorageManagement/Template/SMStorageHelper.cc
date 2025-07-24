#if !defined(STORAGEMANAGEMENT_SMSTORAGEHELPER_CC)
#define STORAGEMANAGEMENT_SMSTORAGEHELPER_CC
// -*- C++ -*-
//
// Package:     StorageManagement
// Module:      SMStorageHelper
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Fri May 14 15:34:34 EDT 1999
// $Id: SMStorageHelper.cc,v 1.4 2000/04/27 21:07:30 mkl Exp $
//
// Revision history
//
// $Log: SMStorageHelper.cc,v $
// Revision 1.4  2000/04/27 21:07:30  mkl
// moved 'begin/endObject' logic to SMStorageHelper::deliver( SourceStream, iVersion ) function
//
// Revision 1.3  2000/04/24 20:22:27  mkl
// surround deliver call by "beginObject"/"endObject" calls.
//
// Revision 1.2  1999/10/18 18:24:51  cdj
// no longer creates proxies
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

// user include files
//#include "Experiment/report.h"
#include "StorageManagement/SMStorageHelper.h"
#include "StorageManagement/SMSinkStream.h"
#include "StorageManagement/SMSourceStream.h"
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

//static const char* const kFacilityString = "StorageManagement.SMStorageHelper" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
//static const char* const kIdString  = "$Id: SMStorageHelper.cc,v 1.4 2000/04/27 21:07:30 mkl Exp $";
//static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//
template< class T>
SMStorageHelper<T>::SMStorageHelper() :
   SMStorageHelperRegisterBase( RecordMethods<T>::makeKey("","").type() )
{
   m_deliverers.reserve(1);
}

// SMStorageHelper::SMStorageHelper( const SMStorageHelper& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

template< class T>
SMStorageHelper<T>::~SMStorageHelper()
{
   //need to delete the contents
   std::vector<void*>::iterator itEnd = m_deliverers.end();
   for( std::vector<void*>::iterator itDel = m_deliverers.begin();
	itDel != itEnd;
	++itDel ) {
      void* temp = *itDel;
     delete static_cast<DelivererBase*>(temp);
   }
}

//
// assignment operators
//
// const SMStorageHelper& SMStorageHelper::operator=( const SMStorageHelper& rhs )
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
template< class T>
DABoolean 
SMStorageHelper<T>::checkConsistance(SMSinkStream&iSink, 
				     SMSourceStream& iSource )
{
   store( iSink, getDefault() );
   T* temp = deliver( iSource );
   DABoolean returnValue = compare( deliver( iSource ), getDefault() );
   delete temp;
   return returnValue;
}

template< class T>
void 
SMStorageHelper<T>::useDefault( SMSinkStream& iSink )
{
   store( iSink, getDefault() );
}

template< class T>
void 
SMStorageHelper<T>::store( SMSinkStream& iSink, const T& iData )
{
   iSink.beginObject( typeTag() );
   implementStore( iSink, iData );
   iSink.endObject();
}

template< class T>
T* 
SMStorageHelper<T>::deliver( SMSourceStream& iSource)
{
   T* returnValue = 0;

   unsigned int version = iSource.versionUsed( typeTag() );
   assert( version != kNoVersionsDefined );
   returnValue = deliver( iSource, version );

   return returnValue;
}

//in future, we will replace this with a better way of managing memory
template< class T>
T*
SMStorageHelper<T>::make( const T& iTempData ) const
{
   return new T( iTempData );
}

//
// const member functions
//

//
// static member functions
//

#endif /* STORAGEMANAGEMENT_SMSTORAGEHELPER_CC */
