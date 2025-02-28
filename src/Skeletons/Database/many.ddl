#if !defined(OBSCHEMA_OBYOURITEMHERE_DDL)
#define OBSCHEMA_OBYOURITEMHERE_DDL
// -*- C++ -*-
//
// Package:     OBSchema
// Module:      OBYourItemHere
// 
// Description: <one line class summary>
//
// Usage:
//    <usage>
//
// Author:      John Doe
// Created:     day-mon-xx
// RCS(Id)
//
// Revision history at end of file
//

#include "Experiment/Experiment.h"

// system include files
#include "oo.h"

// user include files

// forward declarations

class OBYourItemHere
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      OBYourItemHere();
      OBYourItemHere( uint32 iIdentifier,
		      Type1 iType1,
		      Type2 iType2 );
      ~OBYourItemHere();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------

      // asccessor methods
      uint32   identifier() const { return m_identifier; }
      Type1 type1()         const { return m_type1; }
      Type2 type2()         const { return m_type2; }

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      // OBYourItemHere( const OBYourItemHere& ); // stop default

      // ---------- assignment operator(s) ---------------------
      // const OBYourItemHere& operator=( const OBYourItemHere& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      uint32  m_identifier;
      Type1   m_type1;
      Type2   m_type2;

      // ---------- static data members ------------------------

};

// declare and instantiate
declare( ooVArray, OBYourItemHere );
#include "OBSchema/Generated/OBBank_ref.h"
#include "OBSchema/Generated/OBBank.h"
template class OBBank< OBYourItemHere >;

// inline function definitions

// ----------------------------------------------------------
// Revision history
//
// RCS(Log)
//

#endif /* OBSCHEMA_OBYOURITEMHERE_DDL */
