#if !defined(PACKEDDATASTREAMSFORMAT_PDSFIXEDTRUEZEROPACKER_H)
#define PACKEDDATASTREAMSFORMAT_PDSFIXEDTRUEZEROPACKER_H
// -*- C++ -*-
//
// Package:     <PackedDataStreamsFormat>
// Module:      PDSFixedTrueZeroPacker
// 
/**\class PDSFixedTrueZeroPacker PDSFixedTrueZeroPacker.h PackedDataStreamsFormat/PDSFixedTrueZeroPacker.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Fri Sep 15 20:10:07 EDT 2000
// $Id: PDSFixedTrueZeroPacker.h,v 1.4 2002/06/04 15:21:22 cdj Exp $
//
// Revision history
//
// $Log: PDSFixedTrueZeroPacker.h,v $
// Revision 1.4  2002/06/04 15:21:22  cdj
// had to 'not' the #if defined I added in the previous checkout
//
// Revision 1.3  2002/06/03 20:40:45  cleo3
// changed cpp switch from SUNCC to STATIC_LOCAL_VARIABLE_IN_INLINE_TEMPLATE_FUNC_BUG
//
// Revision 1.2  2000/10/02 20:30:40  cdj
// now compiles (and links) under cxx
//
// Revision 1.1.1.1  2000/09/29 17:46:15  cdj
// imported
//

// system include files

// user include files
#include "PackedDataStreamsFormat/PDSPackerTemplate.h"
#include "StorageManagement/Compression/SMIntNoPackPacker.h"
#include "StorageManagement/Compression/SMFloatNoPackPacker.h"
#include "StorageManagement/Compression/SMFixedTrueZeroPacker.h"

// forward declarations

template<class T>
class PDSFixedTrueZeroPacker : public PDSPackerTemplate<T>
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      PDSFixedTrueZeroPacker( const SMPackInfoFixedTemplate<T>& iPackInfo ) :
	 m_packer(
	    SMFixedTrueZeroPacker<T>::createFromMinMaxPrecision( 
	       iPackInfo.min(),
	       iPackInfo.max(),
	       iPackInfo.precision()
	       ) ) {}

      PDSFixedTrueZeroPacker(const UInt32*& ioBuffer, 
			     unsigned char& ioStartBit ) :
	 m_packer( readBuffer( ioBuffer, ioStartBit ) ) {}
      
      //virtual ~PDSFixedTrueZeroPacker();

      // ---------- member functions ---------------------------
      SMPackerTemplate<T>& packer() { return m_packer;}

      // ---------- const member functions ---------------------
      PDSPacking::Strategies strategy() const { 
	 return PDSPacking::kFixedTrueZeroPacking; }

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

	 precisionPacker().pack(m_packer.precision(),
				ioPackedWord,
				overflow,
				ioStartBit);
	 this->putInContainerIfPackedWordFull(ioPackedWord, overflow, ioStartBit,
					ioContainer);

	 offsetPacker().pack(m_packer.offset(),
			     ioPackedWord,
			     overflow,
			     ioStartBit);
	 this->putInContainerIfPackedWordFull(ioPackedWord, overflow, ioStartBit,
					ioContainer);
      }

   private:
      // ---------- Constructors and destructor ----------------
      PDSFixedTrueZeroPacker( const PDSFixedTrueZeroPacker& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const PDSFixedTrueZeroPacker& operator=( const PDSFixedTrueZeroPacker& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------
      static SMFixedTrueZeroPacker<T> readBuffer(const UInt32*(& ioBuffer), 
						 unsigned char& ioStartBit ) {
	 unsigned char numberOfBits = PDSPackerTemplate<T>::numberOfBitsPacker().unpack( 
	    *ioBuffer, *(ioBuffer+1), ioStartBit);
	 PDSPackerTemplate<T>::advanceBufferIfReadAllPackedWord( ioBuffer, ioStartBit );

	 T precision = precisionPacker().unpack(*ioBuffer, 
						*(ioBuffer+1), 
						ioStartBit);
	 PDSPackerTemplate<T>::advanceBufferIfReadAllPackedWord( ioBuffer, ioStartBit );

	 T offset = offsetPacker().unpack(*ioBuffer, 
					  *(ioBuffer+1), 
					  ioStartBit);
	 PDSPackerTemplate<T>::advanceBufferIfReadAllPackedWord( ioBuffer, ioStartBit );

	 return SMFixedTrueZeroPacker<T>( numberOfBits, precision, offset );
      }

      static SMPackerTemplate<T>& precisionPacker();
      static SMPackerTemplate<T>& offsetPacker();

      // ---------- data members -------------------------------
      SMFixedTrueZeroPacker<T> m_packer;
      // ---------- static data members ------------------------

};

// inline function definitions
template<>
SMPackerTemplate<float>&
PDSFixedTrueZeroPacker<float>::precisionPacker() {
   static SMFloatNoPackPacker<float> s_packer;
   return s_packer;

}
template<>
SMPackerTemplate<float>&
PDSFixedTrueZeroPacker<float>::offsetPacker() {
   static SMFloatNoPackPacker<float> s_packer;
   return s_packer;

}

template<>
SMPackerTemplate<double>&
PDSFixedTrueZeroPacker<double>::precisionPacker() {
   static SMFloatNoPackPacker<double> s_packer;
   return s_packer;
}
template<>
SMPackerTemplate<double>&
PDSFixedTrueZeroPacker<double>::offsetPacker() {
   static SMFloatNoPackPacker<double> s_packer;
   return s_packer;
}

//If use 'inline' on CC 4.2 the compiler thinks there are multiple versions
//  of s_packer
template <class T>
#if !defined(STATIC_LOCAL_VARIABLE_IN_INLINE_TEMPLATE_FUNC_BUG)
inline
#endif
SMPackerTemplate<T>& 
PDSFixedTrueZeroPacker<T>::precisionPacker() {
   static SMIntNoPackPacker<T> s_packer;
   return s_packer;
}

template <class T>
#if !defined(STATIC_LOCAL_VARIABLE_IN_INLINE_TEMPLATE_FUNC_BUG)
inline
#endif
SMPackerTemplate<T>& 
PDSFixedTrueZeroPacker<T>::offsetPacker() {
   static SMIntNoPackPacker<T> s_packer;
   return s_packer;
}

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "PackedDataStreamsFormat/Template/PDSFixedTrueZeroPacker.cc"
//#endif

#endif /* PACKEDDATASTREAMSFORMAT_PDSFIXEDTRUEZEROPACKER_H */
