#if !defined(TOOLBOX_TBNTUPLEVARNAMES_H)
#define TOOLBOX_TBNTUPLEVARNAMES_H
// -*- C++ -*-
//
// Package:     ToolBox
// Module:      TBNTupleVarNames
// 
// Description: Provides a safe way to construct names for NTuple variables
//
// Usage:
//    When the user is going to initialize an NTuple they can use this
//     class to define the names of the various variables.
//
//    We assume that they have created an enum with the different names and
//     the last entry in the enum gives the number of variables
//
//       //NTuple variables
//       enum { kX, kY, kZ, kNumVars };
//
//    Then when they are going to create the ntuple they us TBNTupleVarNames
// 
//       //Set up variable names
//       TBNTupleVarNames varNames( kNumVars );
//
//       varNames.addVar( kX, "x" );
//       varNames.addVar( kY, "y" );
//       varNames.addVar( kZ, "z" );
//
//       //Create the ntuple
//       m_ntuple = aHistManager.ntuple( 100, "Title", kNumVars,
//                                       50000, varNames.names() );
//
//     The class does the following consistency checks
//     1) the number of variables added equals the number of
//        variables specified in the constructor call
//     2) each variable has a unique index and name
//
//     If any of these consistency checks fail an error message will be
//      printed and the program will be terminated.
//
//
// Author:      Chris D. Jones
// Created:     Fri Jul 24 12:03:44 EDT 1998
// $Id: TBNTupleVarNames.h,v 1.2 1998/10/22 17:38:52 cdj Exp $
//
// Revision history
//
// $Log: TBNTupleVarNames.h,v $
// Revision 1.2  1998/10/22 17:38:52  cdj
// name() now returns a const char* const *
//
// Revision 1.1  1998/07/24 18:32:06  cdj
// First submission
//

// system include files

// user include files

// forward declarations

class TBNTupleVarNames
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      TBNTupleVarNames( unsigned int iNumberOfVariables );
      ~TBNTupleVarNames();

      // ---------- member functions ---------------------------
      void addVar( unsigned int iIndex, const char* iName );

      // ---------- const member functions ---------------------
      const char* const* names() const;

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      TBNTupleVarNames();
      TBNTupleVarNames( const TBNTupleVarNames& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const TBNTupleVarNames& operator=( const TBNTupleVarNames& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      unsigned int m_nVars;
      char** m_varNames;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "ToolBox/Template/TBNTupleVarNames.cc"
//#endif

#endif /* TOOLBOX_TBNTUPLEVARNAMES_H */
