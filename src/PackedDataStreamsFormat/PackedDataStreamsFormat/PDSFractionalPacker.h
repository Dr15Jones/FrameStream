#if !defined(PACKEDDATASTREAMSFORMAT_PDSFRACTIONALPACKER_H)
#define PACKEDDATASTREAMSFORMAT_PDSFRACTIONALPACKER_H
// -*- C++ -*-
//
// Package:     <PackedDataStreamsFormat>
// Module:      PDSFractionalPacker
// 
/**\class PDSFractionalPacker PDSFractionalPacker.h PackedDataStreamsFormat/PDSFractionalPacker.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Fri Sep 15 20:10:52 EDT 2000
// $Id: PDSFractionalPacker.h,v 1.1.1.1 2000/09/29 17:46:15 cdj Exp $
//
// Revision history
//
// $Log: PDSFractionalPacker.h,v $
// Revision 1.1.1.1  2000/09/29 17:46:15  cdj
// imported
//

// system include files

// user include files
#include "StorageManagement/Compression/SMFractionalPacker.h"
#include "StorageManagement/Compression/SMFloatNoPackPacker.h"
#include "StorageManagement/Compression/SMIntNoPackPacker.h"


// forward declarations

//declare these inline functions so that all instantiated instances of
// PDSFractionalPacker can use the same SMPackers.
inline
SMFloatNoPackPacker<float>& 
smfractionalpacker_fractionPacker()
{
   static SMFloatNoPackPacker<float> s_packer;
   return s_packer;
}

inline
SMIntNoPackPacker<int>& 
smfractionalpacker_exponentOffsetPacker()
{
   static SMIntNoPackPacker<int> s_packer;
   return s_packer;
}


template <class T>
class PDSFractionalPacker : public PDSPackerTemplate<T>
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      PDSFractionalPacker(const SMPackInfoFractionalTemplate<T>& iPackInfo) :
	 m_packer(
	    SMFractionalPacker<T>::createFromMinMaxFraction(
	       iPackInfo.min(), iPackInfo.max(), iPackInfo.fraction() ) ) {}

      PDSFractionalPacker(const UInt32*& ioBuffer, 
			  unsigned char& ioStartBit ) :
	 m_packer( readBuffer( ioBuffer, ioStartBit ) ) {}

      //virtual ~PDSFractionalPacker();

      // ---------- member functions ---------------------------
      SMPackerTemplate<T>& packer() { return m_packer;}

      // ---------- const member functions ---------------------
      PDSPacking::Strategies strategy() const { 
	 return PDSPacking::kFractionalPacking; }

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------
      void storeStrategyInfo( UInt32& ioPackedWord,
			     unsigned char& ioStartBit,
			     std::vector<UInt32>& ioContainer ) const {
	 UInt32 overflow = 0;
	 this->numberOfBitsPacker().pack(m_packer.numberOfBits(),
				   ioPackedWord,
				   overflow,
				   ioStartBit);
	 this->putInContainerIfPackedWordFull(ioPackedWord, overflow, ioStartBit,
					ioContainer);

	 this->numberOfBitsPacker().pack(m_packer.numberOfExponentBits(),
				ioPackedWord,
				overflow,
				ioStartBit);
	 this->putInContainerIfPackedWordFull(ioPackedWord, overflow, ioStartBit,
					ioContainer);

	 fractionPacker().pack(m_packer.fraction(),
			       ioPackedWord,
			       overflow,
			       ioStartBit);
	 this->putInContainerIfPackedWordFull(ioPackedWord, overflow, ioStartBit,
					ioContainer);

	 exponentOffsetPacker().pack(m_packer.exponentOffset(),
				     ioPackedWord,
				     overflow,
				     ioStartBit);
	 this->putInContainerIfPackedWordFull(ioPackedWord, overflow, ioStartBit,
					ioContainer);

      }

   private:
      // ---------- Constructors and destructor ----------------
      PDSFractionalPacker( const PDSFractionalPacker& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const PDSFractionalPacker& operator=( const PDSFractionalPacker& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      static SMFractionalPacker<T> readBuffer(const UInt32*(& ioBuffer), 
					      unsigned char& ioStartBit ) {
	 unsigned char numberOfBits = PDSPackerTemplate<T>::numberOfBitsPacker().unpack( 
	    *ioBuffer, *(ioBuffer+1), ioStartBit);
	 PDSPackerTemplate<T>::advanceBufferIfReadAllPackedWord( ioBuffer, ioStartBit );

	 unsigned char numberOfExponentBits = PDSPackerTemplate<T>::numberOfBitsPacker().unpack( 
	    *ioBuffer, *(ioBuffer+1), ioStartBit);
	 PDSPackerTemplate<T>::advanceBufferIfReadAllPackedWord( ioBuffer, ioStartBit );


	 float fraction = fractionPacker().unpack(*ioBuffer, 
						  *(ioBuffer+1), 
						  ioStartBit);
	 PDSPackerTemplate<T>::advanceBufferIfReadAllPackedWord( ioBuffer, ioStartBit );

	 int exponentOffset = exponentOffsetPacker().unpack(*ioBuffer, 
							    *(ioBuffer+1), 
							    ioStartBit);
	 PDSPackerTemplate<T>::advanceBufferIfReadAllPackedWord( ioBuffer, ioStartBit );

	 return SMFractionalPacker<T>( numberOfBits, 
				       numberOfExponentBits,
				       fraction, 
				       exponentOffset );
      }

      static SMFloatNoPackPacker<float>& fractionPacker() {
	 return smfractionalpacker_fractionPacker();
      }

      static SMIntNoPackPacker<int>& exponentOffsetPacker() {
	 return smfractionalpacker_exponentOffsetPacker();
      }

      // ---------- data members -------------------------------
      SMFractionalPacker<T> m_packer;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "PackedDataStreamsFormat/Template/PDSFractionalPacker.cc"
//#endif

#endif /* PACKEDDATASTREAMSFORMAT_PDSFRACTIONALPACKER_H */
