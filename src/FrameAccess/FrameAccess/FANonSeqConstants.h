#if !defined(FRAMEACCESS_FANONSEQCONSTANTS_H)
#define FRAMEACCESS_FANONSEQCONSTANTS_H
// -*- C++ -*-
//
// Package:     FrameAccess
// Module:      FANonSeqConstants
// 
/**\class FANonSeqConstants FANonSeqContants.h FrameAccess/FANonSeqConstants.h

 Description: Allows access to constants within a CLEOConstants that are
               not in sequential order

 Usage:
    Used to extract non-sequential constants from the Frame

*/
//
// Author:      Chris D Jones
// Created:     Sat May  1 17:51:12 EDT 1999
// $Id: FANonSeqConstants.h,v 1.4 1999/12/10 14:20:58 cdj Exp $
//
// Revision history
//
// $Log: FANonSeqConstants.h,v $
// Revision 1.4  1999/12/10 14:20:58  cdj
// added exception macro
//
// Revision 1.3  1999/11/07 02:17:46  cdj
// fixed bug in find method
//
// Revision 1.2  1999/10/31 15:38:43  cdj
// -find now calls CleoConstants<>::getIterator method
// -doxygenated the comments
//
// Revision 1.1  1999/05/07 01:26:30  cdj
// Added smart pointers for Constants access
//

///shorthand for the type of exception thrown by extract
#define NO_NONSEQCONSTANTS_EXCEPTION(_type_) DANoDataException<FANonSeqConstants<_type_>::contents>

// system include files
#include <assert.h>
#include <stdlib.h>

// user include files
#include "CLEOConstants.hxx"

// forward declarations

template< class T >
class FANonSeqConstants
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      typedef T value_type;
      typedef const value_type& const_reference;
      typedef CLEOConstants<T> contents;
      typedef typename CLEOConstants<T>::const_iterator const_iterator;

      // ---------- Constructors and destructor ----------------
      FANonSeqConstants() : m_constants(0) {}
      FANonSeqConstants( const CLEOConstants<T>* pConstants) : 
	 m_constants(pConstants) {}
      //virtual ~FANonSeqConstants();
      
      // ---------- member functions ---------------------------
      void setContents( const CLEOConstants<T>* pConstants ) {
	 m_constants=pConstants; }

      // ---------- const member functions ---------------------
      DABoolean       valid() const {return (0 != m_constants);}
      Count           size() const { assert(valid()); 
                                     return m_constants->size(); }
      DABoolean       empty() const {return (0 == size() ); }

      const_iterator  begin() const {return m_constants->begin(); }
      const_iterator  end() const {return m_constants->end(); }

      const_reference front() const {return m_constants->front();}
      const_reference back() const { return m_constants->back();}

      const_iterator find( long iIndex ) const {
	 return m_constants->get_iterator( iIndex ); }
      const_reference operator[]( long iIndex ) const {
	 assert(valid());
	 return m_constants->get_index( iIndex ); }

      const CLEOConstants<T>* getContents() const { return m_constants; }
      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      FANonSeqConstants( const FANonSeqConstants& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const FANonSeqConstants& operator=( const FANonSeqConstants& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      const CLEOConstants<T>* m_constants;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "FrameAccess/Template/FANonSeqConstants.cc"
//#endif

#endif /* FRAMEACCESS_FANONSEQCONSTANTS_H */
