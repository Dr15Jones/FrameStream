#if !defined(STORAGEMANAGEMENT_SMFRACTIONALPACKER_H)
#define STORAGEMANAGEMENT_SMFRACTIONALPACKER_H
// -*- C++ -*-
//
// Package:     <StorageManagement>
// Module:      SMFractionalPacker
// 
/**\class SMFractionalPacker SMFractionalPacker.h StorageManagement/SMFractionalPacker.h

 Description: Compresses a value of type T into tow UInt32s using Fractional
              compression

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Wed Mar 29 17:11:27 EST 2000
// $Id: SMFractionalPacker.h,v 1.10 2003/03/08 20:56:00 cdj Exp $
//
// Revision history
//
// $Log: SMFractionalPacker.h,v $
// Revision 1.10  2003/03/08 20:56:00  cdj
// made sure that recompressing using fractional packing returns the same result as the first compression
//
// Revision 1.9  2003/03/07 02:54:29  cdj
// numbers smaller than min value for fractional packing are now set to 0 rather than a 'random' value slightly larger than min
//
// Revision 1.8  2003/01/30 15:51:09  cleo3
// explicitly use global namespace versions of frexp and log
//
// Revision 1.7  2002/11/13 21:14:52  cdj
// make sure attempting to store NaN on Solaris 8 doesn't cause a crash
//
// Revision 1.6  2002/03/17 16:06:30  cdj
// added optimized version of Fractional packing
//
// Revision 1.5  2001/09/07 17:38:23  cleo3
// now use cleo_math.h
//
// Revision 1.4  2001/05/11 20:31:55  cdj
// properly handle storage of +-Infinity
//
// Revision 1.3  2000/08/03 18:03:21  mkl
// check for overflow of exponent bits in fractional packing; add test cases for out-of-range
//
// Revision 1.2  2000/07/13 21:14:37  mkl
// properly handle 0 bit packing
//
// Revision 1.1  2000/04/04 18:56:41  cdj
// added Compression and compression testing code
//

// system include files

// user include files
#include "Experiment/cleo_math.h"
#include "StorageManagement/Compression/SMPackerTemplate.h"

// forward declarations

template <class T>
class SMFractionalPacker : public SMPackerTemplate<T>
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      SMFractionalPacker( unsigned int iTotalNumberOfBits,
			  unsigned int iNumberOfExponentBits,
			  float iFraction,
			  int iExponentOffset ) :
	 SMPackerTemplate<T>( iTotalNumberOfBits ),
	 m_numberOfExponentBits( iNumberOfExponentBits ),
	 m_fraction( iFraction ),
	 m_fractionInv( 1.0/iFraction ),
	 m_exponentOffset( iExponentOffset ),
	 m_signWord( 1 << (iTotalNumberOfBits - 1 ) ),
	 m_mask( ( ~UInt32(0) ) >> (32 - m_numberOfExponentBits )) {
	 // shifting out ALL bits is undefined operation
	 if( 0 == m_numberOfExponentBits ) { m_mask=0; }
      }
      //virtual ~SMFractionalPacker();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      void pack( T iValue,
		 UInt32& ioStartWord,
		 UInt32& oOverflowWord,
		 unsigned char& ioStartBit ) const {
	 if( iValue == T(0) ) {
	    doBitShifting( T(0), ioStartWord, oOverflowWord, ioStartBit );
	    return;
	 }
	 if( iValue != iValue ) {
	    //NaN
	    // store as -0
	    UInt32 compressedValue = m_signWord;
	    doBitShifting( compressedValue,
			   ioStartWord,
			   oOverflowWord,
			   ioStartBit );
	    return;
	 }

	 //Split value into fractional and exponent where iValue = f*2^n
	 int n;
	 double f = ::frexp( iValue, &n);
	 //compress the exponent
	 long exponent = n - m_exponentOffset;
	 if( exponent < 0 ) {
	    doBitShifting( T(0), ioStartWord, oOverflowWord, ioStartBit );
	    return;
	 }
	 else if( exponent > m_mask ) {
	    exponent=m_mask;
	    f =1.0-m_fraction;
	 }
	 UInt32 compressedValue = exponent;
	 //compress the fractional part
	 // NOTE: the value returned from frexp is between 0.5 <= f <1.0
	 UInt32 f_compressed = (fabs(f) - 0.5)*m_fractionInv;
	 if( f >= 1.0) {
	    //positive infinity
	    compressedValue = m_mask;
	    f_compressed = m_fractionInv;
	 }
	 if( f <= -1.0 ) {
	    //negative infinity
	    compressedValue = m_mask;
	    f_compressed = m_fractionInv;
	 }
	 compressedValue |= f_compressed << m_numberOfExponentBits;
	 //add 1 because iValue != 0
	 compressedValue += 1;
	 //set the sign bit if this value is negative
	 if(iValue < 0) {
	    compressedValue |= m_signWord;
	 }

	 doBitShifting( compressedValue,
			ioStartWord,
			oOverflowWord,
			ioStartBit );
      }


      virtual T unpack( const UInt32 iStartWord,
			const UInt32 iOverflowWord,
			unsigned char& ioStartBit ) const {

	 UInt32 compressedValue = undoBitShifting( iStartWord,
						   iOverflowWord,
						   ioStartBit );
	 if( compressedValue == 0 ) {
	    return T(0);
	 }
	 //See if the value is supposed to be negative
	 double sign = 1.0;
	 if( m_signWord <= compressedValue  ) {
	    sign = -1.0;
	    compressedValue -= m_signWord;
	 }
	 //remove the 1 we added because the packed value was not 0
	 compressedValue -= 1;

	 int n = (m_mask & compressedValue ) + m_exponentOffset;
	 double f = ( (compressedValue >> m_numberOfExponentBits)+0.5 )*m_fraction 
	    + 0.5;
	 return sign*ldexp( f, n );
      }
      
      ///Number of bits used to store the exponent
      unsigned int numberOfExponentBits() const {
	 return m_numberOfExponentBits; }

      ///the fractional precision
      float fraction() const { return m_fraction; }
 
      ///The smallest allowed exponent value (in powers of 2)
      int exponentOffset() const {return m_exponentOffset; }

      // ---------- static member functions --------------------
      static SMFractionalPacker<T> createFromMinMaxFraction(
	 T iMin, T iMax, float iFraction ) {
	 float fraction = iFraction/2.0;
	 unsigned int numberOfNBits = calcNumberOfNBitsNeeded( iMin, iMax );
	 unsigned int totalNumberOfBits = calcTotalNumberOfBitsNeeded( 
	    numberOfNBits,
	    fraction );
	 int exponentOffset;
	 ::frexp( iMin, &exponentOffset );
	 
	 
	 return SMFractionalPacker<T>( totalNumberOfBits,
				       numberOfNBits,
				       fraction, 
				       exponentOffset );	 
      }

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------
      static unsigned int calcNumberOfNBitsNeeded( T iMin, T iMax ) {
	 int n_max, n_min;
	 ::frexp( iMin, &n_min);
	 ::frexp( iMax, &n_max);
	 return calcNumberOfBitsNeeded( n_max - n_min, int(1) );
      }

      //The result includes the one bit needed by the sign AND
      // the extra space needed to store the number 0
      static unsigned int calcTotalNumberOfBitsNeeded(
	 unsigned int iNumberOfNBits,
	 float iFraction ) {
	 const double kLog2Inv = 1.0/::log(2);
	 return iNumberOfNBits + 
	    ::log(1.0/iFraction + 1.0/( 1 <<iNumberOfNBits) )*kLog2Inv + 1 + 1 ;
      }

      UInt32 signWord() const { return m_signWord;}
      UInt32 mask() const {return m_mask;}
   private:
      // ---------- Constructors and destructor ----------------
      //SMFractionalPacker( const SMFractionalPacker& ); // stop default

      // ---------- assignment operator(s) ---------------------
      //const SMFractionalPacker& operator=( const SMFractionalPacker& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      ///Number of bits used to store the exponent
      unsigned int m_numberOfExponentBits ;
      float m_fraction;
      ///inverse of the fractional precision
      float m_fractionInv ;
      ///The smallest allowed exponent value (in powers of 2)
      int m_exponentOffset ;
      UInt32 m_signWord;
      UInt32 m_mask;
      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "StorageManagement/Template/SMFractionalPacker.cc"
//#endif

#endif /* STORAGEMANAGEMENT_SMFRACTIONALPACKER_H */
