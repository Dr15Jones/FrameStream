#if !defined(STORAGEMANAGEMENT_SMPTRTOREFINSERTITERATOR_H)
#define STORAGEMANAGEMENT_SMPTRTOREFINSERTITERATOR_H
// -*- C++ -*-
//
// Package:     <StorageManagement>
// Module:      SMPtrToRefInsertIterator
// 
/**\class SMPtrToRefInsertIterator SMPtrToRefInsertIterator.h StorageManagement/SMPtrToRefInsertIterator.h

 Description: Allows you to insert a pointer of type ValueType into a 
                container of holding ValueTypes

 Usage:
    This class is used when you are reading back a list of objects from the
    storage system.  Stored lists of objects always return pointers to the 
    objects.  If you actually want to retrieve a list of objects (instead
    of a list of pointers to objects) this insert iterator will make your
    container look like a container of pointers (and delete the objects 
    returned by the storage system).

*/
//
// Author:      Chris D Jones
// Created:     Wed Dec 20 16:22:21 EST 2000
// $Id: SMPtrToRefInsertIterator.h,v 1.1 2000/12/22 21:05:34 cdj Exp $
//
// Revision history
//
// $Log: SMPtrToRefInsertIterator.h,v $
// Revision 1.1  2000/12/22 21:05:34  cdj
// added SMPtrToRefInsertIterator to make it easier to handle containers that hold objects rather than pointers to objects
//

// system include files

// user include files
#include "STLUtility/iterator_traits_fix.h"

// forward declarations

template< class Iterator, class ValueType >
class SMPtrToRefInsertIterator :
#if defined(OLD_ITERATOR_CLASSES_BUG)
   public forward_iterator< ValueType*,
   ptrdiff_t >
#else
public iterator< forward_iterator_tag, const ValueType*>
#endif
{
   // ---------- friend classes and functions ---------------
   
  public:      
   
   // ---------- constants, enums and typedefs --------------
   typedef ValueType* value_type;
   
   // ---------- Constructors and destructor ----------------
   SMPtrToRefInsertIterator( Iterator& iIterator ) : m_iterator(iIterator) {}

   // ---------- member functions ---------------------------
   SMPtrToRefInsertIterator< Iterator, ValueType >& operator*() { return *this;}
   SMPtrToRefInsertIterator< Iterator, ValueType >& operator++() { 
      ++m_iterator; return *this;}
   
   SMPtrToRefInsertIterator< Iterator, ValueType >& operator=( value_type iValue ) {
      *m_iterator = *iValue;
      delete iValue;
      return *this;
   }
   
   // ---------- const member functions ---------------------
   
   // ---------- static member functions --------------------
   
  protected:
   // ---------- protected member functions -----------------
   
   // ---------- protected const member functions -----------
   
   private:
   // ---------- Constructors and destructor ----------------
   
   // ---------- assignment operator(s) ---------------------
   
   // ---------- private member functions -------------------
   
   // ---------- private const member functions -------------
   
   // ---------- data members -------------------------------
   Iterator& m_iterator;
   
   // ---------- static data members ------------------------
   
};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "StorageManagement/Template/SMPtrToRefInsertIterator.cc"
//#endif

#endif /* STORAGEMANAGEMENT_SMPTRTOREFINSERTITERATOR_H */
