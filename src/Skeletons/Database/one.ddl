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
/// Author:      John Doe
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

class OBYourItemHere : public ooObj
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      // constructor given to-be-stored types
      OBYourItemHere( Type1 iType1, Type2 iType2 );
      ~OBYourItemHere();

      // ---------- member functions ---------------------------
      // accessor methods to stored types
      Type1 type1() const { return m_type1; }
      Type2 type2() const { return m_type2; }

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      OBYourItemHere( const OBYourItemHere& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const OBYourItemHere& operator=( const OBYourItemHere& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      // stored types
      Type1 m_type1;
      Type2 m_type2;

      // ---------- static data members ------------------------

};

// inline function definitions


// ---------------------------------------------------------
// Revision history
//
// RCS(Log)
//

#endif /* OBSCHEMA_OBYOURITEMHERE_DDL */
