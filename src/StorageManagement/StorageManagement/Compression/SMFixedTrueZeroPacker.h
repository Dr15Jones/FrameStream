#if !defined(STORAGEMANAGEMENT_SMFIXEDTRUEZEROPACKER_H)
#define STORAGEMANAGEMENT_SMFIXEDTRUEZEROPACKER_H
// -*- C++ -*-
//
// Package:     StorageManagement
// Module:      SMFixedTrueZeroPacker
// 
/**\class SMFixedTrueZeroPacker SMFixedTrueZeroPacker.h StorageManagement/SMFixedTrueZeroPacker.h

 Description: Compresses a value of type T into two UInt32s using Fixed 
              compression but guarantees that a packed value of 0 always
	      returns 0

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Mon May  8 10:27:45 EDT 2000
// $Id: SMFixedTrueZeroPacker.h,v 1.7 2003/03/10 16:32:08 cdj Exp $
//
// Revision history
//
// $Log: SMFixedTrueZeroPacker.h,v $
// Revision 1.7  2003/03/10 16:32:08  cdj
// if the floating point packing precision is exactly a power of 2, do not shift to center of bin since it is impossible to get rounding problems on recompression (also returns correct value if only storing integral values with precision 1.0)
//
// Revision 1.6  2003/03/09 00:50:37  cdj
// made sure that recompressing using fixed packing returns the same result as the first compression
//
// Revision 1.5  2002/11/20 21:59:25  cdj
// catch possible floating point overflow cases during storage
//
// Revision 1.4  2002/11/13 21:14:52  cdj
// make sure attempting to store NaN on Solaris 8 doesn't cause a crash
//
// Revision 1.3  2002/04/01 19:04:10  cdj
// optimized doBitShift used while unpacking
//
// Revision 1.2  2001/05/11 20:31:24  cdj
// handles +-Infintity and NaN and properly calculate number of bits needed
//
// Revision 1.1  2000/05/08 15:25:57  cdj
// added SMFixedTrueZeroPacker
//

// system include files

// user include files
#include "StorageManagement/Compression/SMPackerTemplate.h"

#include "StorageManagement/Compression/SMUnpackingShift.h"

// forward declarations

template< class T>
class SMFixedTrueZeroPacker : public SMPackerTemplate<T>
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      SMFixedTrueZeroPacker( unsigned int iNumberOfBits,
			     T iPrecision,
			     T iOffset ) : 
	 SMPackerTemplate<T>( iNumberOfBits ),
	 m_precision( iPrecision ),
	 m_offset( iOffset ),
	 m_maxValue( ( ~UInt32(0) >> (32 - numberOfBits()) ) ),
	 m_tooBig( calculate_tooBig(m_precision,m_offset,m_maxValue) ),
	 m_shift( SMUnpackingShift<T>::shift(iPrecision) )
      {}
      //virtual ~SMFixedTrueZeroPacker();

      // ---------- member functions ---------------------------
      void pack( T iValue,
		 UInt32& ioStartWord,
		 UInt32& oOverflowWord,
		 unsigned char& ioStartBit ) const {
	 //first do compression
	 UInt32 compressedValue;

	 if( T(0) == iValue ) {
	    //always store 0 as 0
	    compressedValue = 0;
	 } else {
	    //shift all other values by 1
	    if( iValue < m_offset ) {
	       compressedValue = 1;
	    } else if( willOverflow(iValue) ) {
	       //avoids floating point overflow
	       compressedValue = m_maxValue;
	    } else {
		compressedValue = (iValue - m_offset)/m_precision + 1;
		if(compressedValue != compressedValue) {
		  //This is NaN so what should I do?
		  // for now make it max value, but in future
		  // I should probably throw an exception.
		  compressedValue = m_maxValue;
		}
	    }
	    if( compressedValue > m_maxValue ) {
	       compressedValue = m_maxValue;
	    }
	 }
	 doBitShifting( compressedValue,
			ioStartWord,
			oOverflowWord,
			ioStartBit );
      }

      T unpack( const UInt32 iStartWord,
		const UInt32 iOverflowWord,
		unsigned char& ioStartBit ) const {

	 UInt32 compressedValue = undoBitShifting( iStartWord,
						   iOverflowWord,
						   ioStartBit );
	 if( 0 == compressedValue ) {
	    return compressedValue ;
	 }
	 //Now convert this to the proper type
	 return (compressedValue - 1 
		 + m_shift)*m_precision + m_offset;
      }

      // accessors
      T precision() const { return m_precision; }
      T offset() const { return m_offset; }


      // ---------- static member functions --------------------
      static SMFixedTrueZeroPacker<T> createFromMinMaxPrecision( 
	 T iMin, T iMax, T iPrecision ) {
	 return SMFixedTrueZeroPacker<T>( 
	    //the +iPrecision is because we treat 0 special
	    calcNumberOfBitsNeeded( iMax - iMin + iPrecision, iPrecision ),
	    iPrecision,
	    iMin );
      }

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      //SMFixedTrueZeroPacker( const SMFixedTrueZeroPacker& ); // stop default

      // ---------- assignment operator(s) ---------------------
      //const SMFixedTrueZeroPacker& operator=( const SMFixedTrueZeroPacker& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------
      static T calculate_tooBig(T iPrecision, T iOffset, UInt32 iMaxValue);
      DABoolean willOverflow(T iValue) const;

      // ---------- data members -------------------------------
      T m_precision;
      T m_offset;
      unsigned int m_maxValue;
      T m_tooBig;
      const T m_shift;

      // ---------- static data members ------------------------

};

// inline function definitions

template<>
inline
double
SMFixedTrueZeroPacker<double>::calculate_tooBig(double iPrecision,
					double iOffset,
					UInt32 iMaxValue)
{
   // the 2 is a safety margin requested by dsr
   if( iMaxValue < (~UInt32(0)) - 2 ) {
      ++iMaxValue;
   }
   return iPrecision*(iMaxValue-1) + iOffset;
}

template<>
inline
float
SMFixedTrueZeroPacker<float>::calculate_tooBig(float iPrecision,
				       float iOffset,
				       UInt32 iMaxValue)
{
   // the 2 is a safety margin requested by dsr
   if( iMaxValue < (~UInt32(0)) - 2 ) {
      ++iMaxValue;
   }
   return iPrecision*(iMaxValue - 1) + iOffset ;
}

template<class T>
inline
T
SMFixedTrueZeroPacker<T>::calculate_tooBig(T iPrecision,
				   T iOffset,
				   UInt32 iMaxValue ) 
{
   //No value is too big
   return 0;
/*
   const UInt32 kMaxValue = ~UInt32(0);
   if( iOffset < 0 ) {
      return kMaxValue + iOffset;
   }
   return kMaxValue;
   */
}

template<>
inline
DABoolean
SMFixedTrueZeroPacker<double>::willOverflow(double iValue ) const
{
   return iValue > m_tooBig;
}

template<>
inline
DABoolean
SMFixedTrueZeroPacker<float>::willOverflow(float iValue ) const
{
   return iValue > m_tooBig;
}

template<class T>
inline
DABoolean
SMFixedTrueZeroPacker<T>::willOverflow(T iValue ) const
{
   //no possibility of overflow with integral value
   return false;
}

#endif /* STORAGEMANAGEMENT_SMFIXEDTRUEZEROPACKER_H */

