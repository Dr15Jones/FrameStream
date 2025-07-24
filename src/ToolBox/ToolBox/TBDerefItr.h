#if !defined(TOOLBOX_TBDEREFITR_H)
#define TOOLBOX_TBDEREFITR_H
// -*- C++ -*-
//
// Package:     <ToolBox>
// Module:      TBDerefItr
// 
// Description: A smart pointer that implements an iterator over a
//              container of T*, eliminating the need for users to
//              double dereference.
//
// Usage:
//    This is a template class meant to implement a more convenient
//    iterator for container<T*> -- an iterator that reduces the 
//    level of indirection by one.
//
//    To use this template, the user must supply three classes:
//       T_iter      - an iterator class for the container<T*>.
//                     Eg: "vector<MCVertex*>::iterator"
//       T_return    - the return type desired ("const'ness" must 
//                     be consistent w/ T_iter)
//                     Eg: "const MCVertex" for the T_iter example above
//       T_valueType - the underlying class type that is returned,
//                     so that the value_type typedef can be defined
//                     in a standard STL-like fashion
//                     Eg: "MCVertex" for a T_return of "const MCVertex"
//
// Author:      Lawrence Gibbons
// Created:     Sat Feb 13 13:18:44 EST 1999
// $Id: TBDerefItr.h,v 1.2 2001/02/26 20:48:21 cleo3 Exp $
//
// Revision history
//
// $Log: TBDerefItr.h,v $
// Revision 1.2  2001/02/26 20:48:21  cleo3
// changed OLD_ITERATOR_CLASSES_BUG to NO_ITERATOR_TRAITS_BUG
//
// Revision 1.1  2000/10/06 18:12:31  lkg
// New dereferencing iterator for containers holding T*. Based on the
// MCListItr class in MCInfo
//
//

// system include files
#include <list>

// user include files

// forward declarations
#include <list>

typedef long relative_address;

template < class T_iter, class T_return, class T_valueType >
class TBDerefItr
{
      // ---------- private typedefs ---------------
      typedef TBDerefItr< T_iter, T_return, T_valueType > self;
      
   public:
      // ---------- constants, enums and typedefs --------------
      typedef T_valueType      value_type;
      typedef relative_address difference_type;
      typedef T_return&        reference;
      typedef T_return*        pointer;

#if !defined(NO_ITERATOR_TRAITS_BUG)
      typedef  typename iterator_traits<T_iter>::iterator_category iterator_category;
#endif

      // ---------- Constructors and destructor ----------------
      // default constructor
      TBDerefItr();
      // constructor based on the STL implemented iterator for the
      // list of T* (takes double-dereferencing to get to T)
      TBDerefItr( const T_iter& anIterator );

      // copy constructor
      TBDerefItr( const self& rhs );

      // assignment operator
      const self& operator=( const self& rhs );

      virtual ~TBDerefItr();

      // ---------- member functions ---------------------------
      self& operator++();
      self  operator++(int);

      self& operator--();
      self  operator--(int);

      self& operator+=( relative_address n);
      self& operator-=( relative_address n);
      
      // dereferencing operators
      T_return& operator*();
      T_return* operator->();

      // ---------- const member functions ---------------------

      // comparison operators
      DABoolean operator==( const self& aTBDerefItr ) const;
      DABoolean operator!=( const self& aTBDerefItr ) const;

      // iterator addition/subtraction
      self  operator+(  relative_address n) const;
      self  operator-(  relative_address n) const;

   protected:
      // --------- not intended for public use -----------
      const T_iter& bareIterator() const;

   private:
      // ---------- data members -------------------------------
      T_iter m_iterator;

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
# include "ToolBox/Template/TBDerefItr.cc"
#endif

#endif /* TOOLBOX_TBDEREFITR_H */
