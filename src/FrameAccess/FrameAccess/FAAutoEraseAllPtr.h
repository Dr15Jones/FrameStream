#if !defined(FRAMEACCESS_FAAUTOERASEALLPTR_H)
#define FRAMEACCESS_FAAUTOERASEALLPTR_H
// -*- C++ -*-
//
// Package:     <FrameAccess>
// Module:      FAAutoEraseAllPtr
// 
/**\class FAAutoEraseAllPtr FAAutoEraseAllPtr.h FrameAccess/FAAutoEraseAllPtr.h

 Description: Hold onto an FAPtrTable<> and in its destructor calls that
  FAPtrTable<>'s eraseAll method.

 Usage:
    This class is used to help exception safety of routines that fill 
    FAPtrTables.

    To use, 
    1) hand the FAPtrTable you want controlled to a FAAutoEraseAllPtr
    2) when you are all done with your operation, call FAAutoEraseAllPtr's
       release method.
    If an exception occurs between step 1 and 2, then the FAPtrTable's 
    eraseAll method will be called.

*/
//
// Author:      Chris D Jones
// Created:     Fri Nov 17 09:41:31 EST 2000
// $Id: FAAutoEraseAllPtr.h,v 1.1 2000/11/17 15:45:34 cdj Exp $
//
// Revision history
//
// $Log: FAAutoEraseAllPtr.h,v $
// Revision 1.1  2000/11/17 15:45:34  cdj
// added FAAutoEraseAllPtr
//

// system include files

// user include files
#include "FrameAccess/FAPtrTable.h"

// forward declarations

template<class T>
class FAAutoEraseAllPtr
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      FAAutoEraseAllPtr() : m_ptrTable(0) {}
      FAAutoEraseAllPtr( FAPtrTable<T>* iTable ) : m_ptrTable(iTable) {}
      ~FAAutoEraseAllPtr() { 
	 if( 0 != m_ptrTable ) { m_ptrTable->eraseAll(); } }

      FAAutoEraseAllPtr( const FAAutoEraseAllPtr<T>& iPtr ) :
	 m_ptrTable(iPtr.release() ) {}

      // ---------- assignment operator(s) ---------------------
      const FAAutoEraseAllPtr<T>& operator=( const FAAutoEraseAllPtr<T>& iRHS)
      { m_ptrTable = iRHS.release(); return *this; }

      const FAAutoEraseAllPtr<T>& operator=( FAPtrTable<T>* iRHS ) {
	 m_ptrTable = iRHS; return *this; }

      // ---------- member functions ---------------------------
      FAPtrTable<T>& operator*() { return *m_ptrTable; }
      FAPtrTable<T>* operator->() { return m_ptrTable; }

      FAPtrTable<T>* release() { 
	 FAPtrTable<T>* temp = m_ptrTable;
	 m_ptrTable=0;
	 return temp; }

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------


      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      FAPtrTable<T>* m_ptrTable;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "FrameAccess/Template/FAAutoEraseAllPtr.cc"
//#endif

#endif /* FRAMEACCESS_FAAUTOERASEALLPTR_H */
