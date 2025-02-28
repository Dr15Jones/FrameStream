#if !defined(FRAMEACCESS_FACONSTANTS_H)
#define FRAMEACCESS_FACONSTANTS_H
// -*- C++ -*-
//
// Package:     FrameAccess
// Module:      FAConstants
// 
/**\class FAConstants FAConstants.h FrameAccess/FAConstants.h

 Description: Allows access to sequential constants from the Frame

 Usage:
    Used To extract sequential constants from the Frame

    \code
    //get the constants
    FAConstants<DBSVChannel> svChannelConsts;
    extract( svchannelRecord, svChannelConsts);  
 
    //get the channel with index 12
    DBSVChannel svChannel = svChannelConsts[12];
    \endcode

*/
//
// Author:      Chris D Jones
// Created:     Fri Apr 30 15:22:54 EDT 1999
// $Id: FAConstants.h,v 1.4 2000/04/21 17:49:29 cdj Exp $
//
// Revision history
//
// $Log: FAConstants.h,v $
// Revision 1.4  2000/04/21 17:49:29  cdj
// added bounds checking to operator[]
//
// Revision 1.3  1999/12/10 14:20:57  cdj
// added exception macro
//
// Revision 1.2  1999/10/31 15:39:23  cdj
// doxygenated the comments
//
// Revision 1.1  1999/05/07 01:26:29  cdj
// Added smart pointers for Constants access
//

///short hand for the type of exception thrown by extract
#define NO_CONSTANTS_EXCEPTION(_type_) DANoDataException<FAConstants<_type_>::contents>

// system include files
#include <assert.h>
#include <stdlib.h>

// user include files
#include "CLEOConstants.hxx"

// forward declarations

template< class T >
class FAConstants
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      typedef T value_type;
      typedef const value_type& const_reference;
      typedef CLEOConstants<T> contents;
      typedef typename CLEOConstants<T>::const_iterator const_iterator;

      // ---------- Constructors and destructor ----------------
      FAConstants() : m_constants(0) {}
      FAConstants( const CLEOConstants<T>* pConstants ) :
	 m_constants(pConstants) { checkIfSequential();}

      //virtual ~FAConstants();

      // ---------- member functions ---------------------------
      void setContents( const CLEOConstants<T>* pConstants ) {
	 m_constants=pConstants; 
	 if( 0 != m_constants ) {checkIfSequential();} }

      // ---------- const member functions ---------------------
      DABoolean       valid() const {return (0 != m_constants);}
      Count           size() const { assert(valid()); return m_constants->size(); }
      DABoolean       empty() const {return (0 == size() ); }

      const_iterator  begin() const {return m_constants->begin(); }
      const_iterator  end() const {return m_constants->end(); }

      const_reference front() const {return m_constants->front();}
      const_reference back() const { return m_constants->back();}

      const_iterator find( long iIndex ) const {
	 return &( operator[]( iIndex ) ) ; }

      const_reference operator[]( long iIndex ) const {
	 assert( valid() );
	 assert( (iIndex >= m_firstIndex) && ((iIndex - m_firstIndex ) < size()) );
	 return m_constants->operator[]( iIndex - m_firstIndex ); }

      const CLEOConstants<T>* getContents() const { return m_constants; }
      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      //FAConstants( const FAConstants& ); // use default

      // ---------- assignment operator(s) ---------------------
      //const FAConstants& operator=( const FAConstants& ); // use default

      // ---------- private member functions -------------------
      void checkIfSequential() {
	 m_firstIndex = m_constants->operator[]( 0 ).getIndex();
	 const unsigned long kSize = m_constants->size();
	 if( (kSize != 0) && 
	     ( kSize != m_constants->operator[]( kSize - 1).getIndex() 
	       - m_firstIndex + 1 ) ) {
	    assert(false);
	    ::exit(-1);
	 }
      }

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      unsigned long m_firstIndex;
      const CLEOConstants<T>* m_constants;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "FrameAccess/Template/FAConstants.cc"
//#endif

#endif /* FRAMEACCESS_FACONSTANTS_H */
