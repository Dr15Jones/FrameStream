#if !defined(STORAGEMANAGEMENT_SMFLOATNOPACKPACKER_H)
#define STORAGEMANAGEMENT_SMFLOATNOPACKPACKER_H
// -*- C++ -*-
//
// Package:     <StorageManagement>
// Module:      SMFloatNoPackPacker
// 
/**\class SMFloatNoPackPacker SMFloatNoPackPacker.h StorageManagement/SMFloatNoPackPacker.h

 Description: Does no compression when doing PackPacker.  Only works with floating
   point types

 Usage:
    Since we store all information into 32 bits, a double value is first
    'truncated' to a float and then the float is packed for storage.

    The compression uses the following bit pattern

    0 - 7  exponent (base 2)
    8 - 30 mantessa
    31     sign
    
*/
//
// Author:      Chris D Jones
// Created:     Fri Mar 31 11:26:47 EST 2000
// $Id: SMFloatNoPackPacker.h,v 1.4 2003/03/10 16:32:08 cdj Exp $
//
// Revision history
//
// $Log: SMFloatNoPackPacker.h,v $
// Revision 1.4  2003/03/10 16:32:08  cdj
// if the floating point packing precision is exactly a power of 2, do not shift to center of bin since it is impossible to get rounding problems on recompression (also returns correct value if only storing integral values with precision 1.0)
//
// Revision 1.3  2003/03/08 20:56:00  cdj
// made sure that recompressing using fractional packing returns the same result as the first compression
//
// Revision 1.2  2001/09/07 17:38:23  cleo3
// now use cleo_math.h
//
// Revision 1.1  2000/04/04 18:56:40  cdj
// added Compression and compression testing code
//

// system include files

// user include files
#include "Experiment/cleo_math.h"
#include "StorageManagement/Compression/SMPackerTemplate.h"

// forward declarations

template <class T>
class SMFloatNoPackPacker : public SMPackerTemplate<T>
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      SMFloatNoPackPacker() : SMPackerTemplate<T>(32) {}
      //virtual ~SMFloatNoPackPacker();

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      void pack( T iValue,
		 UInt32& ioStartWord,
		 UInt32& oOverflowWord,
		 unsigned char& ioStartBit ) const {
	 if ( iValue == 0.0 ) {
	    doBitShifting( 0,
			   ioStartWord,
			   oOverflowWord,
			   ioStartBit );
	    return;
	 }
	 float value = (float) iValue;

	 //Split value into fractional and exponent where iValue = f*2^n
	 int n;
	 double f = frexp( value, &n);
	 
	 //compress the exponent
	 UInt32 compressedValue = n - exponentOffset();
	 //compress the fractional part
	 // NOTE: the value returned from frexp is between 0.5 <= f <1.0
	 UInt32 f_compressed = (fabs(f) - 0.5)*invPrecision();
	 compressedValue |= f_compressed << numberOfExponentBits();
	 //set the sign bit if this value is negative
	 if(iValue < 0) {
	    compressedValue |= signWord();
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
	    return T(0);
	 }

	 //See if the value is supposed to be negative
	 double sign = 1.0;
	 if( signWord() <= compressedValue  ) {
	    sign = -1.0;
	    compressedValue -= signWord();
	 }

	 int n = (mask() & compressedValue ) + exponentOffset();
	 double f = (compressedValue >> numberOfExponentBits() )*precision() 
	    + 0.5;
	 return sign*ldexp( f, n );
      }

      // ---------- static member functions --------------------
      static unsigned int numberOfExponentBits() {
	 return 8; }

      static int exponentOffset() {
	 return -127;
      }
      
      static double invPrecision() {
	 return (1 << (32 - numberOfExponentBits() - 1 ) );
      }

      static double precision() { return 1.0/invPrecision(); }

      static UInt32 signWord() { return (UInt32(1) << 31 ); }

      static UInt32 mask() {
	 return ( ~UInt32(0) ) >> (32 - numberOfExponentBits() );     
      }

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      //SMFloatNoPackPacker( const SMFloatNoPackPacker& ); // stop default

      // ---------- assignment operator(s) ---------------------
      //const SMFloatNoPackPacker& operator=( const SMFloatNoPackPacker& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "StorageManagement/Template/SMFloatNoPackPacker.cc"
//#endif

#endif /* STORAGEMANAGEMENT_SMFLOATNOPACKPACKER_H */



