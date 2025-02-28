#if !defined(PACKAGE_SSCONNECTEDSIGNALS_H)
#define PACKAGE_SSCONNECTEDSIGNALS_H
// -*- C++ -*-
//
// Package:     <package>
// Module:      SSConnectedSignals
// 
/**\class SSConnectedSignals SSConnectedSignals.h package/SSConnectedSignals.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Wed Jul  9 15:31:06 EDT 2003
// $Id: SSConnectedSignals.h,v 1.1.1.1 2003/09/09 13:15:02 cdj Exp $
//
// Revision history
//
// $Log: SSConnectedSignals.h,v $
// Revision 1.1.1.1  2003/09/09 13:15:02  cdj
// imported SignalsSlots source
//

// system include files

// user include files

// forward declarations

class SSConnectedSignals
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      SSConnectedSignals();
      virtual ~SSConnectedSignals();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      SSConnectedSignals( const SSConnectedSignals& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const SSConnectedSignals& operator=( const SSConnectedSignals& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "package/Template/SSConnectedSignals.cc"
//#endif

#endif /* PACKAGE_SSCONNECTEDSIGNALS_H */
