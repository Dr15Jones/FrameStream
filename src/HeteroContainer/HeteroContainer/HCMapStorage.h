#if !defined(HETEROCONTAINER_HCMAPSTORAGE_H)
#define HETEROCONTAINER_HCMAPSTORAGE_H
// -*- C++ -*-
//
// Package:     HeteroContainer
// Module:      HCMapStorage
// 
// Description: Adapts an STL map to be used as a Storage
//
// Usage:
//    <usage>
//
// Author:      Chris D. Jones
// Created:     Sun Sep 20 16:46:47 EDT 1998
// $Id: HCMapStorage.h,v 1.2 2003/01/29 21:42:32 cleo3 Exp $
//
// Revision history
//
// $Log: HCMapStorage.h,v $
// Revision 1.2  2003/01/29 21:42:32  cleo3
// added missing typename keyword needed by g++
//
// Revision 1.1.1.1  1998/09/23 14:13:12  cdj
// first submission
//

// system include files

// user include files

// forward declarations

template< class MAP >
class HCMapStorage
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      typedef typename MAP::key_type key_type;
      typedef typename MAP::mapped_type Type;

      // ---------- Constructors and destructor ----------------
      HCMapStorage( MAP& iMap ) : m_map( iMap ) {}
      //virtual ~HCMapStorage();

      // ---------- member functions ---------------------------
      DABoolean insert( const key_type& iKey, Type iType ) {
	 if( m_map.end() == m_map.find( iKey ) ) {
	    m_map.insert( typename MAP::value_type( iKey, iType ) );
	    return true;
	 }
	 return false;
      }

      // ---------- const member functions ---------------------
      Type find( const key_type& iKey ) const {
	 typename MAP::iterator itFind( m_map.find( iKey ) );
	 if( m_map.end() == itFind ) {
	    return 0;
	 } 
	 return (*itFind).second;
      }

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      HCMapStorage();
      HCMapStorage( const HCMapStorage& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const HCMapStorage& operator=( const HCMapStorage& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      MAP& m_map;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "HeteroContainer/Template/HCMapStorage.cc"
//#endif

#endif /* HETEROCONTAINER_HCMAPSTORAGE_H */
