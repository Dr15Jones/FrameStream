#if !defined(FRAMEACCESS_FACONSTPTRTABLE_H)
#define FRAMEACCESS_FACONSTPTRTABLE_H
// -*- C++ -*-
//
// Package:     FrameAccess
// Module:      FAConstPtrTable
// 
/**\class FAConstPtrTable FAConstPtrTable.h FrameAccess/FAConstPtrTable.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Brian K. Heltsley
// Created:     Fri Nov 26 13:18:32 EST 1999
// $Id: FAConstPtrTable.h,v 1.3 2004/02/13 20:40:43 cdj Exp $
//
// Revision history
//
// $Log: FAConstPtrTable.h,v $
// Revision 1.3  2004/02/13 20:40:43  cdj
// insert now returns an iterator (like FAPtrTable) and added operator= for use with new logical set operations
//
// Revision 1.2  2000/06/17 20:13:27  cdj
// added insert using an FAItem
//
// Revision 1.1  1999/12/03 15:01:24  bkh
// Make new class which handles const ptr tables which do not delete member ptrs
// Modify base ptr table class to have virtual eraseAll for protection
//

// system include files

// user include files

#include "FrameAccess/FAPtrTable.h"

// forward declarations

template < class T >
class FAConstPtrTable : public FAPtrTable< T >
{
      // ---------- friend classes and functions ---------------
   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      FAConstPtrTable() {};
      virtual ~FAConstPtrTable() { eraseWithoutDeleteAll() ; } ;

      // ---------- member functions ---------------------------

      virtual void eraseAll() { eraseWithoutDeleteAll(); } ; // stop deletion!

      FATableItr<T> insert( const T* aEntry ) { 
         // cast because FAPtrTable needs it!
	 return FAPtrTable<T>::insert( const_cast< T* >( aEntry ) ); } ;

      FATableItr<T> insert( const FAItem<T>& aItem ) { 
	 return insert( &(*aItem) ); }

      template<class TFill>
      const FAConstPtrTable<T>& operator=(const TFill& iFill) {
	 iFill.fill( *this);
	 return *this;
      }
      // ---------- const member functions ---------------------
      // ---------- static member functions --------------------
   protected:
      // ---------- protected member functions -----------------
      // ---------- protected const member functions -----------
   private:
      // ---------- Constructors and destructor ----------------
      FAConstPtrTable( const FAConstPtrTable& ); // stop default
      // ---------- assignment operator(s) ---------------------
      const FAConstPtrTable& operator=( const FAConstPtrTable& );
      // ---------- private member functions -------------------
      // ---------- private const member functions -------------
      // ---------- data members -------------------------------
      // ---------- static data members ------------------------
};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
#include "FrameAccess/Template/FAConstPtrTable.cc"
#endif

#endif /* FRAMEACCESS_FACONSTPTRTABLE_H */
