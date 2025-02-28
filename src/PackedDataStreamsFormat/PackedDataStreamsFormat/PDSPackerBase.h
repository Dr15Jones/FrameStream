#if !defined(PACKEDDATASTREAMSFORMAT_PDSPACKERBASE_H)
#define PACKEDDATASTREAMSFORMAT_PDSPACKERBASE_H
// -*- C++ -*-
//
// Package:     <PackedDataStreamsFormat>
// Module:      PDSPackerBase
// 
/**\class PDSPackerBase PDSPackerBase.h PackedDataStreamsFormat/PDSPackerBase.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Fri Sep 15 13:27:57 EDT 2000
// $Id: PDSPackerBase.h,v 1.3 2002/04/04 19:12:30 cdj Exp $
//
// Revision history
//
// $Log: PDSPackerBase.h,v $
// Revision 1.3  2002/04/04 19:12:30  cdj
// speed optimization: use SMPackerBase instead of PDSPackerBase when reading back
//
// Revision 1.2  2000/10/01 15:01:46  cdj
// now properly initialize overflow variable
//
// Revision 1.1.1.1  2000/09/29 17:46:15  cdj
// imported
//

// system include files
#include <vector>
#include <math.h>
#include <assert.h>

// user include files
#include "PackedDataStreamsFormat/pds_packing_enums.h"
#include "StorageManagement/Compression/SMFixedPacker.h"

// forward declarations
#include "STLUtility/fwd_vector.h"

class PDSPackerBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      PDSPackerBase() {}
      virtual ~PDSPackerBase() {}

      // ---------- member functions ---------------------------
      virtual SMPackerBase* smPacker() = 0;
      
      // ---------- const member functions ---------------------
      void storePackingInfo( UInt32& ioPackedWord,
			     unsigned char& ioStartBit,
			     STL_VECTOR(UInt32)& oContainer) const {
	 storeType( ioPackedWord, ioStartBit, oContainer );
	 storeStrategy( ioPackedWord, ioStartBit, oContainer );
	 storeStrategyInfo( ioPackedWord, ioStartBit, oContainer);
      }

      virtual PDSPacking::Types type() const = 0;
      virtual PDSPacking::Strategies strategy() const = 0;

      // ---------- static member functions --------------------
      static void readTypeAndStrategy( const UInt32*& ioBuffer,
				       unsigned char& ioStartBit,
				       PDSPacking::Types& oType,
				       PDSPacking::Strategies& oStrategy ) {
	 unsigned char type = s_typePacker.unpack( *ioBuffer,
						   *(ioBuffer+1),
						   ioStartBit );
	 assert(type < PDSPacking::kNumberOfTypes );
	 oType = static_cast<PDSPacking::Types>(type);
	 advanceBufferIfReadAllPackedWord( ioBuffer, ioStartBit );
	 
	 unsigned char strategy = s_strategyPacker.unpack( *ioBuffer,
							   *(ioBuffer+1),
							   ioStartBit );
	 assert(strategy < PDSPacking::kNumberOfStrategies );
	 oStrategy = static_cast<PDSPacking::Strategies>(strategy);
	 advanceBufferIfReadAllPackedWord( ioBuffer, ioStartBit );
      }

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------
      virtual void storeStrategyInfo( UInt32& ioPackedWord,
				     unsigned char& ioStartBit,
				     STL_VECTOR(UInt32)& ) const = 0;

      void putInContainerIfPackedWordFull( UInt32& ioPackedWord,
					   UInt32& ioOverflow,
					   unsigned char& ioStartBit,
					   STL_VECTOR(UInt32)& oContainer ) const{
	 if( ioStartBit >= 32 ) {
	    ioStartBit -= 32;
	    oContainer.push_back( ioPackedWord );
	    ioPackedWord = ioOverflow;
	    ioOverflow = 0;
	 }

      }

      static void advanceBufferIfReadAllPackedWord( const UInt32*& ioBuffer,
					     unsigned char& ioStartBit) {
	 if( ioStartBit >= 32 ) { ++ioBuffer; ioStartBit -= 32; } }
	 

      ///useful to inheriting classes
      static SMFixedPacker<unsigned char>& numberOfBitsPacker() {
	 static SMFixedPacker<unsigned char> s_packer(
	    SMFixedPacker<unsigned char>::createFromMinMaxPrecision(
	       0, 32, 1) );
	 return s_packer;
      }

   private:
      // ---------- Constructors and destructor ----------------
      PDSPackerBase( const PDSPackerBase& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const PDSPackerBase& operator=( const PDSPackerBase& ); // stop default

      // ---------- private member functions -------------------
      void storeType( UInt32& ioPackedWord, 
		      unsigned char& ioStartBit,
		      STL_VECTOR(UInt32)& oContainer ) const {
	 UInt32 overflow=0;
	 s_typePacker.pack( type(), ioPackedWord, overflow, ioStartBit ); 
	 putInContainerIfPackedWordFull( ioPackedWord, overflow, ioStartBit,
					 oContainer);
      }

      void storeStrategy( UInt32& ioPackedWord, 
			  unsigned char& ioStartBit,
			  STL_VECTOR(UInt32)& oContainer ) const {
	 UInt32 overflow=0;
	 s_strategyPacker.pack(strategy(), ioPackedWord, overflow, ioStartBit); 
	 putInContainerIfPackedWordFull( ioPackedWord, overflow, ioStartBit,
					 oContainer);
      }

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------
      static SMFixedPacker<unsigned char> s_typePacker;
      static SMFixedPacker<unsigned char> s_strategyPacker;
};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "PackedDataStreamsFormat/Template/PDSPackerBase.cc"
//#endif

#endif /* PACKEDDATASTREAMSFORMAT_PDSPACKERBASE_H */
