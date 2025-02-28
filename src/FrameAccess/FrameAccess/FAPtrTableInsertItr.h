#if !defined(FRAMEACCESS_FAPTRTABLEINSERTITR_H)
#define FRAMEACCESS_FAPTRTABLEINSERTITR_H
// -*- C++ -*-
//
// Package:     FrameAccess
// Module:      FAPtrTableInsertItr
// 
// Description: An insert iterator that can be used with an FAPtrTable
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Mon Jun  7 15:28:59 EDT 1999
// $Id: FAPtrTableInsertItr.h,v 1.3 2000/04/06 14:56:44 cdj Exp $
//
// Revision history
//
// $Log: FAPtrTableInsertItr.h,v $
// Revision 1.3  2000/04/06 14:56:44  cdj
// FAPtrTableInsertItr now typedefs the value_type to a pointer
//
// Revision 1.2  1999/12/17 16:46:48  cdj
// updated to work with new C++ standard iterator
//
// Revision 1.1  1999/09/22 15:24:42  cdj
// first submission
//

// system include files
#include <iterator>

// user include files
#include "FrameAccess/FAPtrTable.h"

// forward declarations

template< class T>
class FAPtrTableInsertItr : 
#if defined(OLD_ITERATOR_CLASSES_BUG)
public output_iterator 
#else
public iterator< output_iterator_tag, T>
#endif
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      typedef FAPtrTable<T> container_type;
      typedef T* value_type;

      // ---------- Constructors and destructor ----------------
      FAPtrTableInsertItr (container_type& x) : m_container(x) {}
      //virtual ~FAPtrTableInsertItr();

      // ---------- member functions ---------------------------
      const FAPtrTableInsertItr<T>& operator= (value_type value) {
	 m_container.insert(value); 
	 return *this;
      }
      FAPtrTableInsertItr<T>& operator*  ()    { return *this; }
      FAPtrTableInsertItr<T>& operator++ ()    { return *this; }
      FAPtrTableInsertItr<T> operator++ (int) { return *this; }

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      FAPtrTableInsertItr(); // stop default
      //FAPtrTableInsertItr( const FAPtrTableInsertItr& ); // allow default

      // ---------- assignment operator(s) ---------------------
      //const FAPtrTableInsertItr& operator=( const FAPtrTableInsertItr& ); //allow default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      FAPtrTable<T>& m_container;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "FrameAccess/Template/FAPtrTableInsertItr.cc"
//#endif

#endif /* FRAMEACCESS_FAPTRTABLEINSERTITR_H */
