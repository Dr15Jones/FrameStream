#if !defined(NAMINGSERVICE_NAMINGSERVICE_H)
#define NAMINGSERVICE_NAMINGSERVICE_H
// -*- C++ -*-
//
// Package:     <NamingService>
// Module:      NamingService
// 
// Description: <one line class summary>
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Thu Feb 18 18:38:58 EST 1999
// $Id: NamingService.h,v 1.2 1999/12/11 19:10:11 mkl Exp $
//
// Revision history
//
// $Log: NamingService.h,v $
// Revision 1.2  1999/12/11 19:10:11  mkl
// added more history command help info; minor fix-ups for Linux
//
// Revision 1.1  1999/02/22 23:40:50  mkl
// setResult( string ) insteadof report in Commands; added NamingService and DefaultModule; fixed bug in stream command
//

// system include files

// user include files

// forward declarations
#include "C++Std/fwd_string.h"
#include "STLUtility/fwd_map.h"
#if !defined(_naming_service_namemap_)
#define _naming_service_namemap_ STL_MAP( string, T* ) 
#endif

template< class T >
class NamingService
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      NamingService();
      virtual ~NamingService();

      // ---------- member functions ---------------------------
      DABoolean registerObject( const string& iName,
				T* iObject );
      DABoolean deregisterObject( const string& iName );

      // ---------- const member functions ---------------------
      T* resolve( const string& iName );

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      NamingService( const NamingService& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const NamingService& operator=( const NamingService& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      _naming_service_namemap_& m_name2Object;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
# include "CommandPattern/Template/NamingService.cc"
#endif

#endif /* NAMINGSERVICE_NAMINGSERVICE_H */
