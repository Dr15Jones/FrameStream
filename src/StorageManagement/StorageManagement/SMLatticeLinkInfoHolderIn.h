#if !defined(STORAGEMANAGEMENT_SMLATTICELINKINFOHOLDERIN_H)
#define STORAGEMANAGEMENT_SMLATTICELINKINFOHOLDERIN_H
// -*- C++ -*-
//
// Package:     <StorageManagement>
// Module:      SMLatticeLinkInfoHolderIn
// 
/**\class SMLatticeLinkInfoHolderIn SMLatticeLinkInfoHolderIn.h StorageManagement/SMLatticeLinkInfoHolderIn.h

 Description: Helper function for reading back a Lattice from storage

 Usage:
    This class is used to optimize reading back the Link information for
   a Lattice.  
   This class assumes
      1) the vectors of Left and Right IDs live beyond the lifetime
          of the function call (i.e. they are 'static' or member data)
      2) only 1 SMLatticeLinkInfoHolderIn<X> is in existance at a time
         (since the specialized 'new' method always returns the same
          memory address)

*/
//
// Author:      Chris D Jones
// Created:     Mon Mar 25 16:27:21 EST 2002
// $Id: SMLatticeLinkInfoHolderIn.h,v 1.1 2002/03/25 22:05:55 cdj Exp $
//
// Revision history
//
// $Log: SMLatticeLinkInfoHolderIn.h,v $
// Revision 1.1  2002/03/25 22:05:55  cdj
// added an optimized method for reading back Lattice Link info
//

// system include files

// user include files

// forward declarations

template <class TLattice>
class SMLatticeLinkInfoHolderIn : public SMLatticeLinkInfoBase<TLattice>
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      //SMLatticeLinkInfoHolderIn();  //allow default
      //virtual ~SMLatticeLinkInfoHolderIn();

      // ---------- member functions ---------------------------
      virtual void set( const LeftIDs& iLeftIDs, 
			const LinkData& iData, 
			const RightIDs& iRightIDs) {
	 m_leftIDs = &iLeftIDs;
	 m_data = iData;
	 m_rightIDs = &iRightIDs;
      }

      virtual const LinkData& linkData() const { return m_data; }
      virtual const LeftIDs&  vLeftID () const { return *m_leftIDs; }
      virtual const RightIDs& vRightID() const { return *m_rightIDs; }

      void* operator new(size_t size) {
         assert( size == sizeof(SMLatticeLinkInfoHolderIn<TLattice>)/sizeof(char));
         return sharedMemory();
      }
      void operator delete( void*, size_t ) {}

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      //SMLatticeLinkInfoHolderIn( const SMLatticeLinkInfoHolderIn& ); // stop default

      // ---------- assignment operator(s) ---------------------
      //const SMLatticeLinkInfoHolderIn& operator=( const SMLatticeLinkInfoHolderIn& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      const LeftIDs* m_leftIDs;
      LinkData m_data;
      const RightIDs* m_rightIDs;

      static void* sharedMemory() {
         static char s_memory[ sizeof(SMLatticeLinkInfoHolderIn<TLattice>)/sizeof(char)];
         return s_memory;
      }

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "StorageManagement/Template/SMLatticeLinkInfoHolderIn.cc"
//#endif

#endif /* STORAGEMANAGEMENT_SMLATTICELINKINFOHOLDERIN_H */
