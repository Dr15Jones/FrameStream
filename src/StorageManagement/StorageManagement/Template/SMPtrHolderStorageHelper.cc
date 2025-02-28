#if !defined(STORAGEMANAGEMENT_SMPTRHOLDERSTORAGEHELPER_CC)
#define STORAGEMANAGEMENT_SMPTRHOLDERSTORAGEHELPER_CC
// -*- C++ -*-
//
// Package:     RichAverageAnglesProd
// Module:      SMPtrHolderStorageHelper
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Fri May 14 17:00:02 EDT 1999
// $Id: SMPtrHolderStorageHelper.cc,v 1.4 2002/06/04 19:51:18 cleo3 Exp $
//
// Revision history
//

#define DO_EQUAL_INSTANTIATION

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
//#include "Experiment/report.h"
#include "StorageManagement/SMPtrHolderStorageHelper.h"
#include "StorageManagement/SMSinkStream.h"
#include "StorageManagement/SMSourceStream.h"
#include "StorageManagement/SMContents.h"
#include "StorageManagement/SMField.h"
#include "StorageManagement/SMMakeContents.h"

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

//static const char* const kFacilityString = "RichAverageAnglesProd.SMPtrHolderStorageHelper" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
//static const char* const kIdString  = "$Id: SMPtrHolderStorageHelper.cc,v 1.4 2002/06/04 19:51:18 cleo3 Exp $";
//static const char* const kTagString = "$Name:  $";

//
// static data member definitions
//

//
// constructors and destructor
//

   //define a Deliverer class that only calls deliverV1() method

template <class T_Ptr, class T_val>
class SMPtrHolderDeliverer : public 
SMStorageHelper<SMPtrHolder<T_Ptr, T_val> >::DelivererBase {
   public:
      SMPtrHolderDeliverer( SMPtrHolderStorageHelper<T_Ptr, T_val>* iHelper ) :
	 m_helper(iHelper ) {}
      SMPtrHolder<T_Ptr, T_val>* deliver( SMSourceStream& iSource ) {
	 return m_helper->deliverV1( iSource ); }
   private:
      SMPtrHolderStorageHelper<T_Ptr, T_val>* m_helper;
};

template <class T_Ptr, class T_val>
SMPtrHolderStorageHelper<T_Ptr, T_val>::SMPtrHolderStorageHelper() :
     m_ptr(0)
{
   //registration of the different versions
   // NOTE: version number is determined by the order in which the
   // methods are registered
     //registerVersion( &SMPtrHolderStorageHelper<T_Ptr, T_val>::deliverV1 );
     registerDeliverVersion(new SMPtrHolderDeliverer<T_Ptr, T_val>(this) );
}

// SMPtrHolderStorageHelper::SMPtrHolderStorageHelper( const SMPtrHolderStorageHelper& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

//SMPtrHolderStorageHelper::~SMPtrHolderStorageHelper()
//{
//}

//
// assignment operators
//
// const SMPtrHolderStorageHelper& SMPtrHolderStorageHelper::operator=( const SMPtrHolderStorageHelper& rhs )
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

template <class T_Ptr, class T_val>
void 
SMPtrHolderStorageHelper<T_Ptr, T_val>::implementStore( 
   SMSinkStream& iSink,
   const SMPtrHolder<T_Ptr, T_val>& iData ) 
{
     iSink 
          << sm_field("pointer",
                      sm_contents(iData.begin(), iData.end()));
      ;
}

template <class T_Ptr, class T_val>
SMPtrHolder<T_Ptr, T_val>* 
SMPtrHolderStorageHelper<T_Ptr, T_val>::deliverV1( SMSourceStream& iSource )
{
     SMPtrHolder<T_Ptr, T_val> temp;
     iSource >> temp;
     return make (SMPtrHolder<T_Ptr, T_val>(temp));
}

template <class Container>
class setPointer_insert_iterator 
{
   public:
      typedef typename Container::pointer_type value_type;
      typedef value_type* pointer;
      typedef value_type& reference;
      typedef long difference_type;
      typedef output_iterator_tag iterator_category;

      setPointer_insert_iterator( Container& iContainer ) : 
	 m_container(iContainer) {}

      setPointer_insert_iterator& operator++(int) {
	 return *this; }
      setPointer_insert_iterator& operator++() {
	 return *this; }

      setPointer_insert_iterator& operator*() { return *this; }

      setPointer_insert_iterator& operator=( const value_type& iValue ) {
	 m_container.setPointer( iValue );
	 return *this;
      }

   private:
      Container& m_container;
};

template <class T_Ptr, class T_val>
SMSourceStream& operator>>( SMSourceStream& iSource, SMPtrHolder<T_Ptr, T_val>& r)
{
     r.eraseAll();
     
     setPointer_insert_iterator<SMPtrHolder<T_Ptr, T_val> > iter(r);

     iSource >> sm_make_contents(iter);

     return iSource;
}

//
// const member functions
//
template <class T_Ptr, class T_val>
const SMPtrHolder<T_Ptr, T_val>& 
SMPtrHolderStorageHelper<T_Ptr, T_val>::getDefault() const
{
   //give constructor unique values to allow test of store and deliver 
   // functions
     static const SMPtrHolder<T_Ptr, T_val> temp;
     return temp;
}

template <class T_Ptr, class T_val>
DABoolean 
SMPtrHolderStorageHelper<T_Ptr, T_val>::compare( 
   const SMPtrHolder<T_Ptr, T_val>* iNewData, 
   const SMPtrHolder<T_Ptr, T_val>& iOldData ) const
{
   //write a comparison operation if operator== doesn't exist for SMPtrHolder
   return (*iNewData == iOldData ) ;
}

//
// static member functions
//

//SMPtrHolder*
//SMStorageHelper<SMPtrHolder>::make( const SMPtrHolder& iTempData ) const
//{
   //change this line if SMPtrHolder does not have a copy constructor
//   return new SMPtrHolder( iTempData );
//}

#define SMSTORAGEHELPER_MAKE_PTR( M_PTR, M_VAL ) \
template<> \
SMPtrHolder<M_PTR, M_VAL>* \
SMStorageHelper<SMPtrHolder<M_PTR, M_VAL> >::make( const SMPtrHolder<M_PTR, M_VAL>& iPtr ) const { \
   return new SMPtrHolder<M_PTR, M_VAL>; \
} 
#endif
