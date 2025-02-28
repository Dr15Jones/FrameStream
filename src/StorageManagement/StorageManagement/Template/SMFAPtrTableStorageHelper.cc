#if !defined(STORAGEMANAGEMENT_SMFAPTRTABLESTORAGEHELPER_CC)
#define STORAGEMANAGEMENT_SMFAPTRTABLESTORAGEHELPER_CC
// -*- C++ -*-
//
// Package:     StorageManagement
// Module:      SMFAPtrTableStorageHelper
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Fri Jun 11 14:38:37 EDT 1999
// $Id: SMFAPtrTableStorageHelper.cc,v 1.3 2002/06/04 19:51:18 cleo3 Exp $
//
// Revision history
//
// $Log: SMFAPtrTableStorageHelper.cc,v $
// Revision 1.3  2002/06/04 19:51:18  cleo3
// updated to new explicit template specialization syntax
//
// Revision 1.2  1999/12/15 22:06:05  cdj
// removed the destructor to avoid crash at Suez exit on OSF1
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
#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"
#include "StorageManagement/SMFAPtrTableStorageHelper.h"
#include "StorageManagement/SMFAPtrTableProxy.h"
#include "StorageManagement/SMSinkStream.h"
#include "StorageManagement/SMSourceStream.h"
#include "StorageManagement/SMContents.h"
#include "StorageManagement/SMField.h"
#include "StorageManagement/SMMakeContents.h"
#include "FrameAccess/FAPtrTableInsertItr.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//

//static const char* const kFacilityString = "StorageManagement.SMFAPtrTableStorageHelper" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
//static const char* const kIdString  = "$Id: SMFAPtrTableStorageHelper.cc,v 1.3 2002/06/04 19:51:18 cleo3 Exp $";
//static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//

   //define a Deliverer class that only calls deliverV1() method

template< class T>
class FAPtrTableDeliverer : public 
SMStorageHelper<FAPtrTable<T> >::DelivererBase {
   public:
      FAPtrTableDeliverer( SMFAPtrTableStorageHelper<T>* iHelper ) :
	 m_helper(iHelper ) {}
      FAPtrTable<T>* deliver( SMSourceStream& iSource ) {
	 return m_helper->deliverV1( iSource ); }
   private:
      SMFAPtrTableStorageHelper<T>* m_helper;
};

template< class T>
SMFAPtrTableStorageHelper<T>::SMFAPtrTableStorageHelper() :
   m_table(0)
{
   registerDeliverVersion( new FAPtrTableDeliverer<T>( this ) );
}

// SMFAPtrTableStorageHelper::SMFAPtrTableStorageHelper( const SMFAPtrTableStorageHelper& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

//template< class T>
//SMFAPtrTableStorageHelper<T>::~SMFAPtrTableStorageHelper()
//{
//}

//
// assignment operators
//
// const SMFAPtrTableStorageHelper& SMFAPtrTableStorageHelper::operator=( const SMFAPtrTableStorageHelper& rhs )
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
SMProxyBase* 
SMFAPtrTableStorageHelper<T>::makeProxy() const
{
   return new SMFAPtrTableProxy<T>( const_cast< SMFAPtrTableStorageHelper<T>* >(this) );
}

template< class T>
void 
SMFAPtrTableStorageHelper<T>::implementStore( 
   SMSinkStream& iSink,
   const FAPtrTable<T>& iData ) 
{
   iSink << sm_field( "contents", sm_contents( iData.begin(), iData.end() ) );
}


template< class T>
FAPtrTable<T>* 
SMFAPtrTableStorageHelper<T>::deliverV1( SMSourceStream& iSource )
{
   //if we have a table, use it just this once, else
   //  make a new one
   FAPtrTable<T>* tempTable = m_table;
   m_table = 0;
   if( 0 == tempTable) {
      tempTable = make( FAPtrTable<T>() );
   }

   FAPtrTableInsertItr<T > insertIterator( *tempTable);

   iSource >> sm_make_contents( insertIterator );
   
   return tempTable;
}

//
// const member functions
//
template< class T>
const FAPtrTable<T>& 
SMFAPtrTableStorageHelper<T>::getDefault() const
{
   static const FAPtrTable<T> temp;
   return temp;
}

template< class T>
DABoolean 
SMFAPtrTableStorageHelper<T>::compare( 
   const FAPtrTable<T>* iNewData, 
   const FAPtrTable<T>& iOldData ) const
{
   //need to compare contents
   return true;
}

//
// static member functions
//

#define SMSTORAGEHELPER_MAKE( M_TYPE ) \
template<> \
FAPtrTable<M_TYPE>* \
SMStorageHelper<FAPtrTable<M_TYPE> >::make( const FAPtrTable<M_TYPE>& iTable ) const { \
   return new FAPtrTable<M_TYPE>; \
} 


#endif /* STORAGEMANAGEMENT_SMFAPTRTABLESTORAGEHELPER_CC */
