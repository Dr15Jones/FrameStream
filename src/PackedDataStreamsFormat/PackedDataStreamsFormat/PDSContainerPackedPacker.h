#if !defined(PACKEDDATASTREAMSFORMAT_PDSCONTAINERPACKEDPACKER_H)
#define PACKEDDATASTREAMSFORMAT_PDSCONTAINERPACKEDPACKER_H
// -*- C++ -*-
//
// Package:     <PackedDataStreamsFormat>
// Module:      PDSContainerPackedPacker
// 
/**\class PDSContainerPackedPacker PDSContainerPackedPacker.h PackedDataStreamsFormat/PDSContainerPackedPacker.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Sun Sep 17 12:26:00 EDT 2000
// $Id: PDSContainerPackedPacker.h,v 1.2 2002/04/04 19:12:30 cdj Exp $
//
// Revision history
//
// $Log: PDSContainerPackedPacker.h,v $
// Revision 1.2  2002/04/04 19:12:30  cdj
// speed optimization: use SMPackerBase instead of PDSPackerBase when reading back
//
// Revision 1.1.1.1  2000/09/29 17:46:15  cdj
// imported
//

// system include files
#include <assert.h>

// user include files
#include "PackedDataStreamsFormat/PDSPackerBase.h"

// forward declarations

class PDSContainerPackedPacker : public PDSPackerBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      PDSContainerPackedPacker( PDSPackerBase* iPacker ): m_packer(iPacker) {
	 assert( 0 != m_packer) ; }
      virtual ~PDSContainerPackedPacker() {
	 delete m_packer;
      }

      SMPackerBase* smPacker() { return m_packer->smPacker(); }
      
      // ---------- member functions ---------------------------
      PDSPacking::Types type() const {
	 return PDSPacking::kContainerType; }
      PDSPacking::Strategies strategy() const {
	 return m_packer->strategy(); }

      PDSPackerBase* packer() const { return m_packer; }
      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions ----------------
      void storeStrategyInfo( UInt32& ioPackedWord,
			      unsigned char& ioStartBit,
			      STL_VECTOR(UInt32)& ioContainer ) const {
	 m_packer->storePackingInfo( ioPackedWord,
				     ioStartBit,
				     ioContainer );
      }

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      PDSContainerPackedPacker( const PDSContainerPackedPacker& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const PDSContainerPackedPacker& operator=( const PDSContainerPackedPacker& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      PDSPackerBase* m_packer;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "PackedDataStreamsFormat/Template/PDSContainerPackedPacker.cc"
//#endif

#endif /* PACKEDDATASTREAMSFORMAT_PDSCONTAINERPACKEDPACKER_H */
