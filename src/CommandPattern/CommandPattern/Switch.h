#if !defined(COMMANDPATTERN_SWITCH_H)
#define COMMANDPATTERN_SWITCH_H
// -*- C++ -*-
//
// Package:     <CommandPattern>
// Module:      Switch
// 
// Description: Switch to turn on/off
//
// Usage:
//    <usage>
//
// Author:      Martin Lohner
// Created:     Thu Feb 18 17:44:07 EST 1999
// $Id: Switch.h,v 1.2 1999/06/23 04:35:52 mkl Exp $
//
// Revision history
//
// $Log: Switch.h,v $
// Revision 1.2  1999/06/23 04:35:52  mkl
// added 'toBoolean' method to Switch class
//
// Revision 1.1  1999/02/22 23:40:51  mkl
// setResult( string ) insteadof report in Commands; added NamingService and DefaultModule; fixed bug in stream command
//

// system include files

// user include files

// forward declarations

class Switch
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      enum OnOff { kOn, kOff };

      // ---------- Constructors and destructor ----------------
      Switch( OnOff iDefault=kOn );
      //virtual ~Switch();
      ~Switch();

      // ---------- member functions ---------------------------
      OnOff turn( OnOff iOn );

      // ---------- const member functions ---------------------
      OnOff setting() const;

      // ---------- static member functions --------------------
      static string toString( OnOff iSetting );
      static DABoolean toBoolean( OnOff iSetting );
      static OnOff toSwitch( const string& iSetting );

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      Switch( const Switch& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const Switch& operator=( const Switch& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      OnOff m_switch;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "CommandPattern/Template/Switch.cc"
//#endif

#endif /* COMMANDPATTERN_SWITCH_H */
