#if !defined(STORAGEMANAGEMENT_SMLATTICELINKINFOOUT_H)
#define STORAGEMANAGEMENT_SMLATTICELINKINFOOUT_H
// -*- C++ -*-
//
// Package:     StorageManagement
// Module:      SMLatticeLinkInfoOut
// 
// Description: <one line class summary>
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Wed Jun  9 17:33:27 EDT 1999
// $Id: SMLatticeLinkInfoOut.h,v 1.1 1999/10/11 22:00:42 cdj Exp $
//
// Revision history
//
// $Log: SMLatticeLinkInfoOut.h,v $
// Revision 1.1  1999/10/11 22:00:42  cdj
// added Lattice storage code
//

// system include files
#include <assert.h>

// user include files
#include "StorageManagement/SMLatticeLinkInfoBase.h"

// forward declarations

template< class Lattice >
class SMLatticeLinkInfoOut :
   public SMLatticeLinkInfoBase< Lattice >
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      typedef typename Lattice::Link Link;

      // ---------- Constructors and destructor ----------------
      SMLatticeLinkInfoOut( const Link* iLink) : m_link(iLink) {}
      //virtual ~SMLatticeLinkInfoOut();

      // ---------- member functions ---------------------------
      virtual void set( const LeftIDs& iLeftIDs, 
			const LinkData& iData, 
			const RightIDs& iRightIDs) {
	 assert(false);
      }

      // ---------- const member functions ---------------------
      virtual const LinkData& linkData() const { return m_link->linkData(); }
      virtual const LeftIDs&  vLeftID () const { 
	 return m_link->vLeftID(); }
      virtual const RightIDs& vRightID() const { 
	 return m_link->vRightID(); }

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      SMLatticeLinkInfoOut() : m_link(0) {}
      //SMLatticeLinkInfoOut( const SMLatticeLinkInfoOut& ); // stop default

      // ---------- assignment operator(s) ---------------------
      //const SMLatticeLinkInfoOut& operator=( const SMLatticeLinkInfoOut& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      const Link* m_link;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "StorageManagement/Template/SMLatticeLinkInfoOut.cc"
//#endif

#endif /* STORAGEMANAGEMENT_SMLATTICELINKINFOOUT_H */
