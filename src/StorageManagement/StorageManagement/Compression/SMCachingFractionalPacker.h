#if !defined(PACKAGE_SMCACHINGFRACTIONALPACKER_H)
#define PACKAGE_SMCACHINGFRACTIONALPACKER_H
// -*- C++ -*-
//
// Package:     <package>
// Module:      SMCachingFractionalPacker
// 
/**\class SMCachingFractionalPacker SMCachingFractionalPacker.h package/SMCachingFractionalPacker.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Chris D Jones
// Created:     Mon Mar 11 11:26:25 EST 2002
// $Id: SMCachingFractionalPacker.h,v 1.2 2002/11/13 21:14:52 cdj Exp $
//
// Revision history
//
// $Log: SMCachingFractionalPacker.h,v $
// Revision 1.2  2002/11/13 21:14:52  cdj
// make sure attempting to store NaN on Solaris 8 doesn't cause a crash
//
// Revision 1.1  2002/03/17 16:06:30  cdj
// added optimized version of Fractional packing
//

// system include files

// user include files
#include "StorageManagement/Compression/SMFractionalPacker.h"

// forward declarations
template <class T, class TPolicy>
class SMCachingFractionalPacker : public SMFractionalPacker<T>
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      SMCachingFractionalPacker( unsigned int iTotalNumberOfBits,
				 unsigned int iNumberOfExponentBits,
				 float iFraction,
				 int iExponentOffset ):
	 SMFractionalPacker<T>(iTotalNumberOfBits,
			       iNumberOfExponentBits,
			       iFraction,
			       iExponentOffset ) {
	    calculateCachedValues(iTotalNumberOfBits,
				  iNumberOfExponentBits,
				  iFraction,
				  iExponentOffset );
      }
      //virtual ~SMCachingFractionalPacker();

      // ---------- member functions ---------------------------
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
	 T sign = 1;
	 if( signWord() <= compressedValue  ) {
	    sign = -1;
	    compressedValue -= signWord();
	 }
	 if( compressedValue == 0 ) {
	    //this can happen if packed NaN
	    return T(0);
	 }
	 //remove the 1 we added because the packed value was not 0
	 compressedValue -= 1;

	 T power = m_powerArray[mask() & compressedValue];
	 //cout <<"power " <<power<<endl;
	 //cout <<" index " << (compressedValue >> numberOfExponentBits())<<endl;
	 T f = m_fractionArray[compressedValue >> numberOfExponentBits()];
         //cout <<"fraction "<<f<<endl;
	 return sign*f*power;
      }

      // ---------- const member functions ---------------------

      // ---------- static member functions --------------------
      static SMCachingFractionalPacker<T,TPolicy> 
      createFromMinMaxFraction(T iMin, T iMax, float iFraction ) {
	 float fraction = iFraction/2.0;
	 unsigned int numberOfNBits = calcNumberOfNBitsNeeded( iMin, iMax );
	 unsigned int totalNumberOfBits = calcTotalNumberOfBitsNeeded( 
	    numberOfNBits,
	    fraction );
	 int exponentOffset;
	 frexp( iMin, &exponentOffset );
	 
	 
	 return SMCachingFractionalPacker<T,TPolicy>( 
	    totalNumberOfBits,
	    numberOfNBits,
	    fraction, 
	    exponentOffset );	 
      }

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      //SMCachingFractionalPacker( const SMCachingFractionalPacker& ); // stop default

      // ---------- assignment operator(s) ---------------------
      //const SMCachingFractionalPacker& operator=( const SMCachingFractionalPacker& ); // stop default

      // ---------- private member functions -------------------
      void calculateCachedValues( unsigned int iTotalNumberOfBits,
	  		     unsigned int iNumberOfExponentBits,
			     float iFraction,
			     int iExponentOffset ) {
	 m_powerArray = TPolicy::powerArray(iNumberOfExponentBits,
					    iExponentOffset);
	 //Also take off the sign bit
	 m_fractionArray = TPolicy::fractionArray(
	    iTotalNumberOfBits - iNumberOfExponentBits - 1,
	    iFraction );
      }

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      const T* m_powerArray;
      const T* m_fractionArray;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "package/Template/SMCachingFractionalPacker.cc"
//#endif

#endif /* PACKAGE_SMCACHINGFRACTIONALPACKER_H */
