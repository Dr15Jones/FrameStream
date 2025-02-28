#if !defined(STORAGEMANAGEMENT_SMFIXEDPACKER_H)
#define STORAGEMANAGEMENT_SMFIXEDPACKER_H
// -*- C++ -*-
//
// Package:     <StorageManagement>
// Module:      SMFixedPacker
// 
/**\class SMFixedPacker SMFixedPacker.h StorageManagement/Compression/SMFixedPacker.h

 Description: Compresses a value of type T into two UInt32s using Fixed compression

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Sat Mar 25 13:46:59 EST 2000
// $Id: SMFixedPacker.h,v 1.7 2003/03/10 19:14:08 cdj Exp $
//
// Revision history
//
// $Log: SMFixedPacker.h,v $
// Revision 1.7  2003/03/10 19:14:08  cdj
// fixed syntax error and made test compatable with new code
//
// Revision 1.6  2003/03/10 16:32:07  cdj
// if the floating point packing precision is exactly a power of 2, do not shift to center of bin since it is impossible to get rounding problems on recompression (also returns correct value if only storing integral values with precision 1.0)
//
// Revision 1.5  2003/03/09 00:50:37  cdj
// made sure that recompressing using fixed packing returns the same result as the first compression
//
// Revision 1.4  2002/11/20 21:59:24  cdj
// catch possible floating point overflow cases during storage
//
// Revision 1.3  2002/04/01 19:04:10  cdj
// optimized doBitShift used while unpacking
//
// Revision 1.2  2000/04/24 20:21:58  mkl
// add accessor functions to data members.
//
// Revision 1.1  2000/04/04 18:56:39  cdj
// added Compression and compression testing code
//

// system include files

// user include files
#include "StorageManagement/Compression/SMPackerTemplate.h"
#include "StorageManagement/Compression/SMUnpackingShift.h"

// forward declarations

template <class T>
class SMFixedPacker : public SMPackerTemplate<T>
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      SMFixedPacker( unsigned int iNumberOfBits,
		     T iPrecision,
		     T iOffset ) : 
	 SMPackerTemplate<T>( iNumberOfBits ),
	 m_precision( iPrecision ),
	 m_offset( iOffset ),
	 m_maxValue( ( ~UInt32(0) >> (32 - numberOfBits()) ) ),
	 m_tooBig( calculate_tooBig(m_precision,m_offset,m_maxValue) ),
	 m_shift( SMUnpackingShift<T>::shift(iPrecision))
      {}

      //virtual ~SMFixedPacker();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      void pack( T iValue,
		 UInt32& ioStartWord,
		 UInt32& oOverflowWord,
		 unsigned char& ioStartBit ) const {
	 //first do compression
	 UInt32 compressedValue;
	 if( iValue < m_offset ) {
	    compressedValue = 0;
	 } else if( willOverflow(iValue) ) {
	    //avoids floating point overflow
	    compressedValue = m_maxValue;
	 } else {
	    compressedValue = (iValue - m_offset)/m_precision;
	 }
	 if( compressedValue > m_maxValue ) {
	    compressedValue = m_maxValue;
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
	 //Now convert this to the proper type
	 return ( compressedValue + m_shift
	    )*m_precision + m_offset;
      }

      // accessors
      T precision() const { return m_precision; }
      T offset() const { return m_offset; }

      // ---------- static member functions --------------------
      static SMFixedPacker<T> createFromMinMaxPrecision( 
	 T iMin, T iMax, T iPrecision ) {
	 return SMFixedPacker<T>( 
	    calcNumberOfBitsNeeded( iMax - iMin, iPrecision ),
	    iPrecision,
	    iMin );
      }

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      //SMFixedPacker( const SMFixedPacker& ); // stop default

      // ---------- assignment operator(s) ---------------------
      //const SMFixedPacker& operator=( const SMFixedPacker& ); // stop default

      // ---------- private member functions -------------------
      static T calculate_tooBig(T iPrecision, T iOffset, UInt32 iMaxValue);
      DABoolean willOverflow(T iValue) const;

      // ---------- private const member functions -------------

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
SMFixedPacker<double>::calculate_tooBig(double iPrecision,
					double iOffset,
					UInt32 iMaxValue)
{
   // the 2 is a safety margin requested by dsr
   if( iMaxValue < (~UInt32(0)) - 2 ) {
      ++iMaxValue;
   }
   return iPrecision*iMaxValue + iOffset;
}

template<>
inline
float
SMFixedPacker<float>::calculate_tooBig(float iPrecision,
				       float iOffset,
				       UInt32 iMaxValue)
{
   // the 2 is a safety margin requested by dsr
   if( iMaxValue < (~UInt32(0)) - 2 ) {
      ++iMaxValue;
   }
   return iPrecision*iMaxValue + iOffset;
}

template<class T>
inline
T
SMFixedPacker<T>::calculate_tooBig(T iPrecision,
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
SMFixedPacker<double>::willOverflow(double iValue ) const
{
   return iValue > m_tooBig;
}

template<>
inline
DABoolean
SMFixedPacker<float>::willOverflow(float iValue ) const
{
   return iValue > m_tooBig;
}

template<class T>
inline
DABoolean
SMFixedPacker<T>::willOverflow(T iValue ) const
{
   //no possibility of overflow with integral value
   return false;
}

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "StorageManagement/Template/SMFixedPacker.cc"
//#endif

#endif /* STORAGEMANAGEMENT_SMFIXEDPACKER_H */
