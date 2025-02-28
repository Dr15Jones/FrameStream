#if !defined(STORAGEMANAGEMENT_SMLATTICELINKINFODEFAULT_H)
#define STORAGEMANAGEMENT_SMLATTICELINKINFODEFAULT_H
// -*- C++ -*-
//
// Package:     <StorageManagement>
// Module:      SMLatticeLinkInfoDefault
// 
/**\class SMLatticeLinkInfoDefault SMLatticeLinkInfoDefault.h StorageManagement/SMLatticeLinkInfoDefault.h

 Description: A SMLatticeLinkInfoBase that is only used in the getDefault call

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Mon Oct 18 11:29:52 EDT 1999
// $Id: SMLatticeLinkInfoDefault.h,v 1.1 1999/10/18 18:29:18 cdj Exp $
//
// Revision history
//
// $Log: SMLatticeLinkInfoDefault.h,v $
// Revision 1.1  1999/10/18 18:29:18  cdj
// first submission
//

// system include files

// user include files

// forward declarations
#include "StorageManagement/SMLatticeLinkInfoBase.h"

template< class Lattice >
class SMLatticeLinkInfoDefault :
   public SMLatticeLinkInfoBase< Lattice >
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      SMLatticeLinkInfoDefault( const LeftIDs& iLeftIDs,
				const LinkData& iData,
				const RightIDs& iRightIDs ):
	 m_leftIDs( iLeftIDs ),
	 m_data( iData),
	 m_rightIDs( iRightIDs ) {}
      //virtual ~SMLatticeLinkInfoDefault();

      // ---------- member functions ---------------------------
      virtual void set( const LeftIDs& iLeftIDs, 
			const LinkData& iData, 
			const RightIDs& iRightIDs) {
	 m_leftIDs = iLeftIDs;
	 m_data = iData;
	 m_rightIDs = iRightIDs;
      }

      // ---------- const member functions ---------------------
      virtual const LinkData& linkData() const { return m_data; }
      virtual const LeftIDs&  vLeftID () const { return m_leftIDs; }
      virtual const RightIDs& vRightID() const { return m_rightIDs; }

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      SMLatticeLinkInfoDefault( const SMLatticeLinkInfoDefault& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const SMLatticeLinkInfoDefault& operator=( const SMLatticeLinkInfoDefault& ); // stop default

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
//# include "StorageManagement/Template/SMLatticeLinkInfoDefault.cc"
//#endif

#endif /* STORAGEMANAGEMENT_SMLATTICELINKINFODEFAULT_H */
