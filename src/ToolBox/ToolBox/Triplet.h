#if !defined(TOOLBOX_TRIPLET_H)
#define TOOLBOX_TRIPLET_H
// -*- C++ -*-
//
// Package:     ToolBox
// Module:      Triplet
// 
// Description: templated class to handle triplets of anything
//
// Usage:
//
// Author:      Brian K. Heltsley
// Created:     Wed Aug 19 13:48:37 EDT 1998
// $Id: Triplet.h,v 1.4 1999/07/01 14:59:58 bkh Exp $
//
// Revision history
//
// $Log: Triplet.h,v $
// Revision 1.4  1999/07/01 14:59:58  bkh
// Install operator< so can be a key in sets & maps
//
// Revision 1.3  1998/11/06 17:14:53  bkh
// avoid warning messages by removing unesthetic 'const'
//
// Revision 1.2  1998/08/20 19:51:59  bkh
// Fix for g++
//
// Revision 1.1  1998/08/19 21:10:18  bkh
// new class
//

// system include files

// user include files

// forward declarations

template < class T1, class T2, class T3 >
class Triplet
{
      // ---------- friend classes and functions ---------------
   public:
      // ---------- constants, enums and typedefs --------------
      // ---------- Constructors and destructor ----------------

      Triplet();
      Triplet( const T1& aFirst  ,
	       const T2& aSecond ,
	       const T3& aThird    ) ;

      Triplet( const Triplet& aTriplet ) ;

      //virtual ~Triplet();

      // ---------- member functions ---------------------------

      const Triplet& operator=( const Triplet& rhs ) ;

      // ---------- const member functions ---------------------

      const T1& first()  const ;
      const T2& second() const ;
      const T3& third()  const ;

      DABoolean operator==( const Triplet& aRHS ) const ;
      DABoolean operator<(  const Triplet& aRHS ) const ;

      // ---------- static member functions --------------------
   protected:
      // ---------- protected member functions -----------------
      // ---------- protected const member functions -----------
   private:
      // ---------- Constructors and destructor ----------------
      // ---------- private member functions -------------------
      // ---------- private const member functions -------------
      // ---------- data members -------------------------------
      T1 m_first  ;
      T2 m_second ;
      T3 m_third  ;
      // ---------- static data members ------------------------
};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
# include "ToolBox/Template/Triplet.cc"
#endif

#endif /* TOOLBOX_TRIPLET_H */
