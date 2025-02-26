#if !defined(HETEROCONTAINER_HCMETHODS_H)
#define HETEROCONTAINER_HCMETHODS_H
// -*- C++ -*-
//
// Package:     HeteroContainer
// Module:      HCMethods
// 
// Description: Templated methods to be used to 'construct' a 
//              heterogenous container
//
// Usage:
//    <usage>
//
// Author:      Chris D. Jones
// Created:     Sun Sep 20 15:58:05 EDT 1998
// $Id: HCMethods.h,v 1.1.1.1 1998/09/23 14:13:12 cdj Exp $
//
// Revision history
//
// $Log: HCMethods.h,v $
// Revision 1.1.1.1  1998/09/23 14:13:12  cdj
// first submission
//

// system include files

// user include files

// forward declarations
class DummyClass;

template< class Type, class ItemType, class Storage, class Key, class IdTag >
class HCMethods
{
      // ---------- friend classes and functions ---------------
      friend class DummyClass ; //Stops complaint about no
                                // accessable constructors
   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- static member functions --------------------
      static Key makeKey( const IdTag& );
      static DABoolean insert( Storage&, ItemType*, const IdTag& );
      static ItemType* find( const Storage&, const IdTag& );

   private:
      // ---------- Constructors and destructor ----------------
      HCMethods();
      //virtual ~HCMethods();
      HCMethods( const HCMethods& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const HCMethods& operator=( const HCMethods& ); // stop default

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "HeteroContainer/Template/HCMethods.cc"
//#endif

#endif /* HETEROCONTAINER_HCMETHODS_H */
