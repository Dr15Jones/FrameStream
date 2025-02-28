#if !defined(RICHAVERAGEANGLESPROD_SMPTRHOLDERSTORAGEHELPER_H)
#define RICHAVERAGEANGLESPROD_SMPTRHOLDERSTORAGEHELPER_H
// -*- C++ -*-
//
// Package:     StorageManagement
// Module:      SMPtrHolderStorageHelper
// 
// Description: StorageHelper to store a SMPtrHolder
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Fri May 14 16:55:38 EDT 1999
// $Id: SMPtrHolderStorageHelper.h,v 1.2 2000/11/01 07:09:45 kbukin Exp $
//
// Revision history
//
// $Log: SMPtrHolderStorageHelper.h,v $
// Revision 1.2  2000/11/01 07:09:45  kbukin
// fix missing declaration of operator>>( SMSourceStream& , SMPtrHolder<T,C>& )
//
// Revision 1.1  2000/11/01 02:21:06  kbukin
// added T_vector_UInt8_helper.cc and added SMPtrHolder with it's storage helper
//
// Revision 1.1  1999/10/18 18:13:05  cdj
// first submission
//
// Revision 1.1.1.1  1999/09/13 21:21:45  cdj
// imported package
//

// system include files

// user include files
#include "StorageManagement/SMProxyBase.h"
#include "StorageManagement/SMStorageHelper.h"
#include "StorageManagement/SMPtrHolder.h"

// forward declarations
template<class T_Ptr, class T_valueType>
SMSourceStream& operator>>( SMSourceStream& , SMPtrHolder<T_Ptr,T_valueType>& );

template <class T_Ptr, class T_val>
class SMPtrHolderStorageHelper :
     public SMStorageHelper< SMPtrHolder<T_Ptr, T_val> >
{
      // ---------- friend classes and functions ---------------

   public:
     typedef SMPtrHolder<T_Ptr, T_val> StoreType;
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      SMPtrHolderStorageHelper() ;
      //virtual ~SMPtrHolderStorageHelper();

      // ---------- member functions ---------------------------

     virtual StoreType* deliverV1( SMSourceStream& iSource );

     void setPtr(StoreType* aPtr){
          m_ptr=aPtr;
     }
      // ---------- const member functions ---------------------
     //SMProxyBase* makeProxy() const;
     
      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      virtual void implementStore( SMSinkStream& iSink,
				   const StoreType& iData );

     //functions to deliver specific storage versions of SMPtrHolder
     //SMPtrHolder<T_Ptr, T_val>* deliverV1( SMSourceStream& iSource );

      // ---------- protected const member functions -----------
      virtual const StoreType& getDefault() const;
      virtual DABoolean compare( const StoreType* iNewData, 
				 const StoreType& iOldData ) const;

   private:
      // ---------- Constructors and destructor ----------------
      SMPtrHolderStorageHelper( const SMPtrHolderStorageHelper& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const SMPtrHolderStorageHelper& operator=( const SMPtrHolderStorageHelper& ); // stop default

      // ---------- private member functions -------------------
     void registerVersion( SMPtrHolder<T_Ptr, T_val>* (SMPtrHolderStorageHelper::*iMethod)( SMSourceStream&) );

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

     StoreType* m_ptr;
      // ---------- static data members ------------------------

};

// inline function definitions

#endif /* RICHAVERAGEANGLESPROD_SMPTRHOLDERSTORAGEHELPER_H */
