#if !defined(STORAGEMANAGEMENT_SMLATTICELINKINFOIN_H)
#define STORAGEMANAGEMENT_SMLATTICELINKINFOIN_H
// -*- C++ -*-
//
// Package:     StorageManagement
// Module:      SMLatticeLinkInfoIn
// 
// Description: <one line class summary>
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Wed Jun  9 17:33:23 EDT 1999
// $Id: SMLatticeLinkInfoIn.h,v 1.1 1999/10/11 22:00:41 cdj Exp $
//
// Revision history
//
// $Log: SMLatticeLinkInfoIn.h,v $
// Revision 1.1  1999/10/11 22:00:41  cdj
// added Lattice storage code
//

// system include files
#include <vector>

// user include files
#include "StorageManagement/SMLatticeLinkInfoBase.h"

// forward declarations

template< class Lattice >
class SMLatticeLinkInfoIn : public SMLatticeLinkInfoBase< Lattice >
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      SMLatticeLinkInfoIn() {}
      //virtual ~SMLatticeLinkInfoIn();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      virtual void set( const LeftIDs& iLeftIDs, 
			const LinkData& iData, 
			const RightIDs& iRightIDs) {
	 m_leftIDs = iLeftIDs;
	 m_data = iData;
	 m_rightIDs = iRightIDs;
      }
      // ---------- static member functions --------------------
      virtual const LinkData& linkData() const { return m_data; }
      virtual const LeftIDs&  vLeftID () const { return m_leftIDs; }
      virtual const RightIDs& vRightID() const { return m_rightIDs; }

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      SMLatticeLinkInfoIn( const SMLatticeLinkInfoIn& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const SMLatticeLinkInfoIn& operator=( const SMLatticeLinkInfoIn& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      LeftIDs m_leftIDs;
      LinkData m_data;
      RightIDs m_rightIDs;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "StorageManagement/Template/SMLatticeLinkInfoIn.cc"
//#endif

#endif /* STORAGEMANAGEMENT_SMLATTICELINKINFOIN_H */
