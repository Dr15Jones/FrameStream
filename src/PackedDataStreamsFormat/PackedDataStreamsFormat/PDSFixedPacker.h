#if !defined(PACKEDDATASTREAMSFORMAT_PDSFIXEDPACKER_H)
#define PACKEDDATASTREAMSFORMAT_PDSFIXEDPACKER_H
// -*- C++ -*-
//
// Package:     <PackedDataStreamsFormat>
// Module:      PDSFixedPacker
// 
/**\class PDSFixedPacker PDSFixedPacker.h PackedDataStreamsFormat/PDSFixedPacker.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Fri Sep 15 20:10:20 EDT 2000
// $Id: PDSFixedPacker.h,v 1.4 2002/06/04 15:21:22 cdj Exp $
//
// Revision history
//
// $Log: PDSFixedPacker.h,v $
// Revision 1.4  2002/06/04 15:21:22  cdj
// had to 'not' the #if defined I added in the previous checkout
//
// Revision 1.3  2002/06/03 20:40:45  cleo3
// changed cpp switch from SUNCC to STATIC_LOCAL_VARIABLE_IN_INLINE_TEMPLATE_FUNC_BUG
//
// Revision 1.2  2000/10/02 20:30:39  cdj
// now compiles (and links) under cxx
//
// Revision 1.1.1.1  2000/09/29 17:46:15  cdj
// imported
//

// system include files

// user include files
#include "PackedDataStreamsFormat/PDSPackerTemplate.h"
#include "StorageManagement/SMPackInfo.h"

// forward declarations

template<class T>
class PDSFixedPacker : public PDSPackerTemplate<T>
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      PDSFixedPacker(const SMPackInfoFixedTemplate<T>& iPackInfo ) : 
	 m_packer(
	    SMFixedPacker<T>::createFromMinMaxPrecision( iPackInfo.min(),
							 iPackInfo.max(),
							 iPackInfo.precision()
							 ) ) {}

      PDSFixedPacker(const UInt32*& ioBuffer, unsigned char& ioStartBit ) :
	 m_packer( readBuffer( ioBuffer, ioStartBit ) ) {}
      //virtual ~PDSFixedPacker();

      // ---------- member functions ---------------------------
      SMPackerTemplate<T>& packer() { return m_packer;}

      // ---------- const member functions ---------------------
      PDSPacking::Strategies strategy() const { return PDSPacking::kFixedPacking; }

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------
      void storeStrategyInfo( UInt32& ioPackedWord,
			     unsigned char& ioStartBit,
			     std::vector<UInt32>& ioContainer ) const {
	 UInt32 overflow = 0;
	 numberOfBitsPacker().pack(m_packer.numberOfBits(),
				   ioPackedWord,
				   overflow,
				   ioStartBit);
	 putInContainerIfPackedWordFull(ioPackedWord, overflow, ioStartBit,
					ioContainer);

	 precisionPacker().pack(m_packer.precision(),
				ioPackedWord,
				overflow,
				ioStartBit);
	 putInContainerIfPackedWordFull(ioPackedWord, overflow, ioStartBit,
					ioContainer);

	 offsetPacker().pack(m_packer.offset(),
			     ioPackedWord,
			     overflow,
			     ioStartBit);
	 putInContainerIfPackedWordFull(ioPackedWord, overflow, ioStartBit,
					ioContainer);
      }

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      PDSFixedPacker( const PDSFixedPacker& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const PDSFixedPacker& operator=( const PDSFixedPacker& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------
      static SMPackerTemplate<T>& precisionPacker(); 

      static SMPackerTemplate<T>& offsetPacker() ;

      static SMFixedPacker<T> readBuffer(const UInt32*(& ioBuffer), 
					 unsigned char& ioStartBit ) {
	 unsigned char numberOfBits = numberOfBitsPacker().unpack( 
	    *ioBuffer, *(ioBuffer+1), ioStartBit);
	 advanceBufferIfReadAllPackedWord( ioBuffer, ioStartBit );

	 T precision = precisionPacker().unpack(*ioBuffer, 
						*(ioBuffer+1), 
						ioStartBit);
	 advanceBufferIfReadAllPackedWord( ioBuffer, ioStartBit );

	 T offset = offsetPacker().unpack(*ioBuffer, 
					  *(ioBuffer+1), 
					  ioStartBit);
	 advanceBufferIfReadAllPackedWord( ioBuffer, ioStartBit );

	 return SMFixedPacker<T>( numberOfBits, precision, offset );
      }
      // ---------- data members -------------------------------
      SMFixedPacker<T> m_packer;

      // ---------- static data members ------------------------

};

// inline function definitions
template<>
SMPackerTemplate<float>&
PDSFixedPacker<float>::precisionPacker() {
   static SMFloatNoPackPacker<float> s_packer;
   return s_packer;
}
template<>
SMPackerTemplate<float>&
PDSFixedPacker<float>::offsetPacker() {
   static SMFloatNoPackPacker<float> s_packer;
   return s_packer;
}

template<>
SMPackerTemplate<double>&
PDSFixedPacker<double>::precisionPacker() {
   static SMFloatNoPackPacker<double> s_packer;
   return s_packer;
}
template<>
SMPackerTemplate<double>&
PDSFixedPacker<double>::offsetPacker() {
   static SMFloatNoPackPacker<double> s_packer;
   return s_packer;
}

template<class T>
#if !defined(STATIC_LOCAL_VARIABLE_IN_INLINE_TEMPLATE_FUNC_BUG)
inline
#endif
SMPackerTemplate<T>& 
PDSFixedPacker<T>::precisionPacker() {
   static SMIntNoPackPacker<T> s_packer;
   return s_packer;
}

template< class T>
#if !defined(STATIC_LOCAL_VARIABLE_IN_INLINE_TEMPLATE_FUNC_BUG)
inline
#endif
SMPackerTemplate<T>& 
PDSFixedPacker<T>::offsetPacker() {
   static SMIntNoPackPacker<T> s_packer;
   return s_packer;
}

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "PackedDataStreamsFormat/Template/PDSFixedPacker.cc"
//#endif

#endif /* PACKEDDATASTREAMSFORMAT_PDSFIXEDPACKER_H */

