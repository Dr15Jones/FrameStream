#if !defined(STORAGEMANAGEMENT_SMLATTICELINKINFOBASE_H)
#define STORAGEMANAGEMENT_SMLATTICELINKINFOBASE_H
// -*- C++ -*-
//
// Package:     StorageManagement
// Module:      SMLatticeLinkInfoBase
// 
// Description: Base class used to help store info from a Lattice
//
// Usage:
//    <usage>
//
// Author:      Chris D Jones
// Created:     Wed Jun  9 15:41:21 EDT 1999
// $Id: SMLatticeLinkInfoBase.h,v 1.2 2000/02/18 22:32:02 cdj Exp $
//
// Revision history
//
// $Log: SMLatticeLinkInfoBase.h,v $
// Revision 1.2  2000/02/18 22:32:02  cdj
// made class non-virtual to avoid problems with CC with templated LatticeLink Storage Helpers
//
// Revision 1.1  1999/10/11 22:00:41  cdj
// added Lattice storage code
//

// system include files
#include <iterator>
#include <assert.h>

// user include files
#include "StorageManagement/SMSourceStream.h"
#include "StorageManagement/SMFillContents.h"

// forward declarations
class SMSourceStream;


template< class Lattice >
class SMLatticeLinkInfoBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      typedef typename Lattice::VectorLeftID LeftIDs;
      typedef typename Lattice::VectorRightID RightIDs;
      typedef typename Lattice::LinkData LinkData;

      // ---------- Constructors and destructor ----------------
      SMLatticeLinkInfoBase() {}
      virtual ~SMLatticeLinkInfoBase();

      // ---------- member functions ---------------------------
      ///this function should always be overridden
      virtual void set( const LeftIDs& , const LinkData& , const RightIDs& ) {
	 assert(false); }

      // ---------- const member functions ---------------------
      ///this function should always be overridden
      virtual const LinkData& linkData() const {
	 assert(false); static LinkData temp; return temp; }
      ///this function should always be overridden
      virtual const LeftIDs&  vLeftID () const {
	 assert(false); static LeftIDs temp; return temp; }
      ///this function should always be overridden
      virtual const RightIDs& vRightID() const {
	 assert(false); static RightIDs temp; return temp; }

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      //SMLatticeLinkInfoBase( const SMLatticeLinkInfoBase& ); // stop default

      // ---------- assignment operator(s) ---------------------
      //const SMLatticeLinkInfoBase& operator=( const SMLatticeLinkInfoBase& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

template< class Lattice >
inline
SMLatticeLinkInfoBase<Lattice>::~SMLatticeLinkInfoBase() {}

/*
template< class Lattice >
SMSourceStream&
operator>>( SMSourceStream& iSource, 
	    SMLatticeLinkInfoBase< Lattice >& iLink );
{
   LeftIDs leftIDs;
   RightIDs rightIDs;
   Lattice::LinkData linkData;

   
   back_insert_iterator<LeftIDs> leftInsertIterator( leftIDs );
   back_insert_iterator<RightIDs> rightInsertIterator( rightIDs );

   iSource >> sm_fill_contents( leftInsertIterator )
           >> sm_fill_contents( rightInsertIterator )
           >> linkData;

   iLink.set( leftIDs, linkData, rightIDs );
   return iSource;
}
*/

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "StorageManagement/Template/SMLatticeLinkInfoBase.cc"
//#endif

#endif /* STORAGEMANAGEMENT_SMLATTICELINKINFOBASE_H */
