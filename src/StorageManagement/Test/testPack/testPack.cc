// -*- C++ -*-
//
// Package:     <StorageManagement>
// Module:      testPack
// 
/**\file testPack.cc

 Description: run tests on the different packing strategies

 Usage:
*/
//
// Author:      Chris D Jones
// Created:     Fri Mar 31 08:56:28 EST 2000
// $Id: testPack.cc,v 1.12 2003/08/21 17:15:41 vk Exp $
//
// Revision history
//
// $Log: testPack.cc,v $
// Revision 1.12  2003/08/21 17:15:41  vk
// Print error message while testing not NaN, for NaN skip it.
//
// Revision 1.11  2003/03/10 19:14:10  cdj
// fixed syntax error and made test compatable with new code
//
// Revision 1.10  2003/01/31 14:20:22  cdj
// get io headers from C++Std package
//
// Revision 1.9  2002/08/08 20:54:23  cdj
// replaced inappropriate use of reinterpret_cast with static_cast
//
// Revision 1.8  2002/03/17 16:06:33  cdj
// added optimized version of Fractional packing
//
// Revision 1.7  2001/05/11 20:32:50  cdj
// test for cases of +-Infinity and NaN
//
// Revision 1.6  2000/09/24 16:13:20  cdj
// added testing for SMContainerSizePacker
//
// Revision 1.5  2000/08/03 18:03:22  mkl
// check for overflow of exponent bits in fractional packing; add test cases for out-of-range
//
// Revision 1.4  2000/07/13 21:14:39  mkl
// properly handle 0 bit packing
//
// Revision 1.3  2000/07/12 21:43:12  cdj
// added test for compressing a 1 bit value
//
// Revision 1.2  2000/05/08 15:25:59  cdj
// added SMFixedTrueZeroPacker
//
// Revision 1.1  2000/04/04 18:56:51  cdj
// added Compression and compression testing code
//

#include "Experiment/Experiment.h"

#include "C++Std/iostream.h"
#include "C++Std/iomanip.h"
#include <vector>
#include <math.h>

#include "StorageManagement/Compression/SMFixedPacker.h"
#include "StorageManagement/Compression/SMFixedTrueZeroPacker.h"
#include "StorageManagement/Compression/SMFractionalPacker.h"
#include "StorageManagement/Compression/SMSharingCachingPolicy.h"
#include "StorageManagement/Compression/SMCachingFractionalPacker.h"
#include "StorageManagement/Compression/SMIntNoPackPacker.h"
#include "StorageManagement/Compression/SMFloatNoPackPacker.h"
#include "StorageManagement/Compression/SMContainerSizePacker.h"
#include "StorageManagement/SMPackInfo.h"

#if !defined(__DECCXX)
//cxx doesn't have IEEE compiliant math libraries
#define DO_EXTREME_TESTS
#endif

//-----------------------------------------------------------
// Classes used to compare the orignal value with the unpacked value
//-----------------------------------------------------------
class CompareBase
{
};

template<class T>
class Compare : public CompareBase
{
   public:
      virtual DABoolean areEqual( T , T ) const = 0;
};

template< class T>
class ExactMatchCompare : public Compare<T>
{
   public:
      virtual DABoolean areEqual( T iTrue, T iStored) const {
	 return iTrue == iStored;
      }
};

template< class T>
class PrecisionCompare : public Compare<T>
{
   public:
      PrecisionCompare( T iMin, T iMax, T iPrecision ) 
	 : m_min( iMin ), m_max( iMax ), m_precision(iPrecision) {}

      virtual DABoolean areEqual( T iTrue, T iStored) const {
	 T delta;

	 // out-of-bounds case
	 if( iTrue > m_max ) {
	    cout << "*** true > max -- out of range" << endl;
	    return (iStored >= m_max );
	 }
	 if( iTrue < m_min ) {
	    cout << "*** true < min -- out of range" << endl;
	    return (iStored-m_precision <= m_min );
	 }

	 // usual case
	 if( iTrue > iStored ) {
	    delta = iTrue - iStored;
	 } else {
	    delta = iStored - iTrue;
	 }
	 return ( delta <= m_precision) ;
      }      
   private:
      T m_min;
      T m_max;
      T m_precision;
};

template< class T>
class PrecisionTrueZeroCompare : public Compare<T>
{
   public:
      PrecisionTrueZeroCompare( T iMin, T iMax, T iPrecision ) : 
	 m_min(iMin), m_max(iMax), m_precision(iPrecision) {}

      virtual DABoolean areEqual( T iTrue, T iStored) const {
	 if( T(0) == iTrue ) {
	    return (iTrue == iStored);
	 }

	 if( iTrue != iTrue ) {
	    cout <<"*** stored NaN" << endl;
	    return ( iStored >= m_max || iStored <= m_min );
	 }

	 // out-of-bounds case
	 if( iTrue > m_max ) {
	    cout << "*** true > max -- out of range" << endl;
	    return (iStored >= m_max );
	 }
	 if( iTrue < m_min ) {
	    cout << "*** true < min -- out of range" << endl;
	    return (iStored-m_precision <= m_min );
	 }

	 T delta;
	 if( iTrue > iStored ) {
	    delta = iTrue - iStored;
	 } else {
	    delta = iStored - iTrue;
	 }
	 return ( delta <= m_precision) ;
      }      
   private:
      T m_min;
      T m_max;
      T m_precision;
};

template< class T>
class FractionCompare : public Compare<T>
{
   public:
      FractionCompare( T iMin, T iMax, float iFraction ) 
	 : m_min( iMin ), m_max( iMax ), m_fraction(iFraction) {}

      virtual DABoolean areEqual( T iTrue, T iStored) const {
	 if( 0 == iTrue ) {
	    return iTrue == iStored;
	 }
	 
	 // out-of-bounds case
	 if( iTrue != iTrue ) {
	    cout <<"*** stored NaN" << endl;
	    return ( iStored >= m_max || iStored <= m_min );
	 }

	 if( iTrue > m_max ) {
	    cout << "*** true > max -- out of range" << endl;
	    return (iStored >= m_max );
	 }
	 if( iTrue < -1.0*m_max ) {
	    cout << "*** true < -max -- out of range" << endl;
	    return (iStored <= -1.0*m_max );
	 }

	 // regular case
	 return ( fabs(iTrue-iStored)/fabs(iTrue) <= m_fraction );
      }      
   private:
      T m_min;
      T m_max;
      float m_fraction;
};

template< class T>
class DecimalPlaceCompare : public Compare<T>
{
   public:
      DecimalPlaceCompare( unsigned int iDecimalPlace ) : 
	 m_decPlace(iDecimalPlace) {}

      virtual DABoolean areEqual( T iTrue, T iStored) const {
	 if( iTrue != 0.0 ) {
	    while ( fabs(iTrue) > 10 ) {
	       iTrue /= 10.0;
	       iStored /= 10.0;
	    } 
	    while ( fabs( iTrue ) < 1.0 ) {
	       iTrue *= 10.0;
	       iStored *= 10.0;
	    }
	 }
	 return ( fabs( iTrue - iStored) <= pow(10.0, -1.0*m_decPlace) );
      }      
   private:
      float m_decPlace;
};


//-----------------------------------------------------------
// Simple class used to store all the objects associated with 
//   packing and comparing a value
//-----------------------------------------------------------
struct PackStuff
{
   public:
      const void* m_value;
      unsigned int m_type;
      SMPackerBase* m_packer;
      CompareBase* m_comparer;
};

typedef vector< PackStuff > PackingList;


//-----------------------------------------------------------
// Convenience routines to help create the packing objects 
//   for a particular value
//-----------------------------------------------------------
template< class T, class T1, class T2, class T3>
inline
PackStuff
fixPackStuff( const T& iValue, T1 iMin, T2 iMax, T3 iPrecision )
{
   PackStuff returnValue;
   returnValue.m_value = 0;
   returnValue.m_type = SMPackInfoFixedTemplate<T>::classFieldType();
   returnValue.m_packer = new SMFixedPacker<T>( 
      SMFixedPacker<T>::createFromMinMaxPrecision( T(iMin), 
						   T(iMax),
						   T(iPrecision) ) 
      ) ;

   returnValue.m_comparer = new PrecisionCompare<T>( iMin, iMax, iPrecision );

   return returnValue;
}

template< class T, class T1, class T2, class T3>
inline
PackStuff

fixTrueZeroPackStuff( const T& iValue, T1 iMin, T2 iMax, T3 iPrecision )
{
   PackStuff returnValue;
   returnValue.m_value = 0;
   returnValue.m_type = SMPackInfoFixedTemplate<T>::classFieldType();
   returnValue.m_packer = new SMFixedTrueZeroPacker<T>( 
      SMFixedTrueZeroPacker<T>::createFromMinMaxPrecision( T(iMin), 
							   T(iMax),
							   T(iPrecision) ) 
      ) ;

   returnValue.m_comparer = new PrecisionTrueZeroCompare<T>( T(iMin),
							     T(iMax),
							     T(iPrecision) );

   return returnValue;
}

template< class T, class T1, class T2 >
inline
PackStuff
fractionalPackStuff( const T& iValue, T1 iMin, T2 iMax, float iFraction )
{
   PackStuff returnValue;
   returnValue.m_value = &iValue;
   returnValue.m_type = SMPackInfoFixedTemplate<T>::classFieldType();
   returnValue.m_packer = new SMFractionalPacker<T>( 
      SMFractionalPacker<T>::createFromMinMaxFraction( T(iMin), 
						       T(iMax),
						       iFraction ) 
      ) ;

   returnValue.m_comparer = new FractionCompare<T>( iMin, iMax, iFraction );

   return returnValue;
}

template< class T, class T1, class T2 >
inline
PackStuff
cachingFractionalPackStuff( const T& iValue, T1 iMin, T2 iMax, float iFraction )
{
   PackStuff returnValue;
   returnValue.m_value = &iValue;
   returnValue.m_type = SMPackInfoFixedTemplate<T>::classFieldType();
   returnValue.m_packer = new SMCachingFractionalPacker<T,SMSharingCachingPolicy<T, 22, -22> >( 
      SMCachingFractionalPacker<T,SMSharingCachingPolicy<T, 22, -22> >::createFromMinMaxFraction( T(iMin), 
							      T(iMax),
							      iFraction ) 
      ) ;

   returnValue.m_comparer = new FractionCompare<T>( iMin, iMax, iFraction );

   return returnValue;
}

template< class T >
inline
PackStuff
intNoPackStuff( const T& iValue )
{
   PackStuff returnValue;
   returnValue.m_value = &iValue;
   returnValue.m_type = SMPackInfoFixedTemplate<T>::classFieldType();
   returnValue.m_packer = new SMIntNoPackPacker<T>(); 

   returnValue.m_comparer = new ExactMatchCompare<T>();

   return returnValue;
}

template< class T >
inline
PackStuff
floatNoPackStuff( const T& iValue )
{
   PackStuff returnValue;
   returnValue.m_value = &iValue;
   returnValue.m_type = SMPackInfoFixedTemplate<T>::classFieldType();
   returnValue.m_packer = new SMFloatNoPackPacker<T>(); 
   //only supposed to be good to 6 decimal places
   returnValue.m_comparer = new DecimalPlaceCompare<T>(6);

   return returnValue;
}

//This class allows me to do the test using standard tools

PackStuff
containerSizePackStuff( const UInt32& iValue )
{
   PackStuff returnValue;
   returnValue.m_value = &iValue;
   returnValue.m_type = SMPackInfo::kContainerSize;
   returnValue.m_packer = new SMContainerSizePacker(); 

   returnValue.m_comparer = new ExactMatchCompare<UInt32>();

   return returnValue;
}

//-----------------------------------------------------------
// Test to see if the value in iPackStuff is of the proper type
//  and if it is, then pack the value into ioStartWord and oOverflowWord
//-----------------------------------------------------------
template <class T >
inline
void 
try_to_pack_value( const T* iDummy,
		   const PackStuff& iPackStuff,
		   UInt32& ioStartWord,
		   UInt32& oOverflowWord,
		   unsigned char& iStartBit ) {
   if( iPackStuff.m_type == 
       SMPackInfoFixedTemplate<T>::classFieldType() ) {

      static_cast<SMPackerTemplate<T>* const>(iPackStuff.m_packer)->
	 pack( *static_cast<const T* >( iPackStuff.m_value),
	       ioStartWord,
	       oOverflowWord,
	       iStartBit );
   }
}


//-----------------------------------------------------------
// Test to see if the value in iPackStuff is of the proper type
//  and if it is, then unpack the value and compare it to the
//  original value
//-----------------------------------------------------------
template <class T, class Iterator >
inline
void 
check_stored_value( const T* iDummy,
		    const PackStuff& iPackStuff,
		    const Iterator iIterator,
		    unsigned char& iStartBit ) {
   if( iPackStuff.m_type == 
       SMPackInfoFixedTemplate<T>::classFieldType() ) {
      T temp =
	 static_cast<SMPackerTemplate<T>* const>(iPackStuff.m_packer)->unpack(
	    *iIterator,
	    *(iIterator+1),
	    iStartBit );

      T value = *static_cast<const T*>( iPackStuff.m_value ) ;
      
      if( static_cast<Compare<T>* const >(iPackStuff.m_comparer)->areEqual( 
	 value, temp ) ) {
	 cout <<"value unpacked "<< temp << endl;
      } else {
         if( !(value != value) ) { // not NaN
	 cout <<"ERROR: original value:" << value <<
	    " unpacked " << temp << endl;
	 }
      }
   }
}

template < class T >
inline
void
fill_pack_list( PackingList& iPackList, const T* itStart, const T* itEnd,
		const PackStuff& iPackStuff, unsigned int iNumberOfTimes ) {
   PackStuff packStuff = iPackStuff;
   for( unsigned int index = 0; index < iNumberOfTimes; ++index ) {
      for( const T* itValue = itStart; itValue != itEnd; ++itValue ) {
	 packStuff.m_value = &(*itValue);
	 iPackList.push_back( packStuff );
      }
   }
}

#define ARRAY_SIZE(array_) sizeof(array_)/sizeof(array_[0])
#define ARRAY_END_ITR(array_) array_ + ARRAY_SIZE(array_)
//-----------------------------------------------------------
// main routine
//-----------------------------------------------------------
int main()
{

   vector<UInt32> buffer;
   PackingList packing;


   //Build up 'schema' info
   unsigned int index;

   
   //do fractionally packed doubles
   const double kFractDoubleValues[] = { 1.0235, -1.0235, 
					 4.0, -4.0, 
					 0.5005, -0.5005,
					 0.000001, -0.000001,
					 0.999, -0.999,
					 -10000., 10000., // test outside limits
#if defined(DO_EXTREME_TESTS)
					 0./0., -1.0/0., 1.0/0.,
#endif
					 0.0 };
   fill_pack_list( packing,
		   kFractDoubleValues,
		   ARRAY_END_ITR(kFractDoubleValues),
		   fractionalPackStuff( kFractDoubleValues[0], 
					0.000001, 
					4, 
					0.00025),
		   4 );
   cout << "number of bits " << packing.back().m_packer->numberOfBits() << endl;

   fill_pack_list( packing,
		   kFractDoubleValues,
		   ARRAY_END_ITR(kFractDoubleValues),
		   cachingFractionalPackStuff( kFractDoubleValues[0], 
					0.000001, 
					4, 
					0.00025),
		   4 );
   cout << "number of bits " << packing.back().m_packer->numberOfBits() << endl;

   //testing packing of no-exponential-bits
   const double kFractNoExpoBitValues[] = { 0.000511 };
   fill_pack_list( packing,
		   kFractNoExpoBitValues,
		   ARRAY_END_ITR(kFractNoExpoBitValues),
		   fractionalPackStuff( kFractNoExpoBitValues[0], 
					0.00050, 
					0.00052, 
					1.E-6),
		   4 );
   cout << "number of bits " << packing.back().m_packer->numberOfBits() << endl;

   fill_pack_list( packing,
		   kFractNoExpoBitValues,
		   ARRAY_END_ITR(kFractNoExpoBitValues),
		   cachingFractionalPackStuff( kFractNoExpoBitValues[0], 
					0.00050, 
					0.00052, 
					1.E-6),
		   4 );
   cout << "number of bits " << packing.back().m_packer->numberOfBits() << endl;

   //do fixed packed unsigned ints
   const unsigned int kFixUIntValues[] = { 0, 80, 23, 
					   10000 // test outside limits
   };
   fill_pack_list( packing,
		   kFixUIntValues,
		   ARRAY_END_ITR(kFixUIntValues),
		   fixPackStuff( kFixUIntValues[0], 
				 0, 
				 80, 
				 1),
		   4 );

   cout << "number of bits " 
	<< packing.back().m_packer->numberOfBits() 
	<< endl;


   //do fixed packed signed ints
   const int kFixIntValues[] = { -10, 0, 80, 23, 
				 -10000, 10000 // test outside limits
   };
   fill_pack_list( packing,
		   kFixIntValues,
		   ARRAY_END_ITR(kFixIntValues),
		   fixPackStuff( kFixIntValues[0], 
				 -10, 
				 80, 
				 1),
		   4 );

   cout << "number of bits " 
	<< packing.back().m_packer->numberOfBits() 
	<< endl;


   //do fixed packed unsigned ints with size right at a bit boundary
   const unsigned int kFixUInt15Values[] = { 0, 15, 7 };
   fill_pack_list( packing,
		   kFixUInt15Values,
		   ARRAY_END_ITR(kFixUInt15Values),
		   fixPackStuff( kFixUInt15Values[0], 
				 0, 
				 15, 
				 1),
		   4 );
   
   cout << "number of bits " 
	<< packing.back().m_packer->numberOfBits() 
	<< endl;
	
   //do fixed packed unsigned int with size of 1
   const unsigned int kFixBoolValues[] = { 0, 1 };
   fill_pack_list( packing,
		   kFixBoolValues,
		   ARRAY_END_ITR(kFixBoolValues),
		   fixPackStuff( kFixBoolValues[0], 
				 0, 
				 1, 
				 1),
		   4 );
   
   cout << "number of bits " 
	<< packing.back().m_packer->numberOfBits() 
	<< endl;
	
   //do fixed floats
   const float kFixFloatValues[] = { 0.24, 100.0, 
#if defined(DO_EXTREME_TESTS)
				     1.0/0., -1.0/0.,
#endif
				     -0.2, 54.298, 
				     0.0 };
   fill_pack_list( packing,
		   kFixFloatValues,
		   ARRAY_END_ITR(kFixFloatValues),
		   fixPackStuff( kFixFloatValues[0], 
				 -0.2, 
				 100, 
				 0.01),
		   4 );
   cout << "number of bits " 
	<< packing.back().m_packer->numberOfBits() 
	<< endl;

   //do floats using fixed with perfect 0
   fill_pack_list( packing,
		   kFixFloatValues,
		   ARRAY_END_ITR(kFixFloatValues),
		   fixTrueZeroPackStuff( kFixFloatValues[0], 
					 -0.2, 
					 100, 
					 0.01),
		   4 );
   cout << "number of bits " 
	<< packing.back().m_packer->numberOfBits() 
	<< endl;

   //do floats using fixed with perfect 0
   const float kFixFloatValues2[] = { 0.003, -0.003, 
				     -0.2, -3., 3.0, 
#if defined(DO_EXTREME_TESTS)
				      0./0., 1.0/0.,
#endif
				     0.0 };
   fill_pack_list( packing,
		   kFixFloatValues2,
		   ARRAY_END_ITR(kFixFloatValues2),
		   fixTrueZeroPackStuff( kFixFloatValues[0], 
					 -0.01, 
					 0.01, 
					 1E-6),
		   4 );
   cout << "number of bits " 
	<< packing.back().m_packer->numberOfBits() 
	<< endl;

   //do non-packed floats
   const float kNoPackFloatValues[] = { 1, -1, 
					3.2432, -3.2432, 
					0.9999999, -0.9999999,
					1E-37, -1E-37,
					1E+37, -1E+37,
					0.0 };
   fill_pack_list( packing,
		   kNoPackFloatValues,
		   ARRAY_END_ITR(kNoPackFloatValues),
		   floatNoPackStuff( kNoPackFloatValues[0] ), 
		   4 );
   cout << "number of bits " 
	<< packing.back().m_packer->numberOfBits() 
	<< endl;


   //do non-packed ints
   const int kNonPackIntValues[] = { 1, -1, 
				     265, -265, 
				     (1<<30) + ((1<<30) - 1), 
				     0 - (1<<30) - ((1<<30) - 1),
				     0 };
   fill_pack_list( packing,
		   kNonPackIntValues,
		   ARRAY_END_ITR(kNonPackIntValues),
		   intNoPackStuff( kNonPackIntValues[0]), 
		   4 );

   cout << "number of bits " 
	<< packing.back().m_packer->numberOfBits() 
	<< endl;

   //do non-packed shorts
   const short kNonPackShortValues[] = { 1, -1, 
				       265, -265, 
				       (1<<14) + ((1<<14) - 1), 
				       0 - (1<<14) - ((1<<14) - 1),
				       0 };
   fill_pack_list( packing,
		   kNonPackShortValues,
		   ARRAY_END_ITR(kNonPackShortValues),
		   intNoPackStuff( kNonPackShortValues[0]), 
		   4 );

   cout << "number of bits " 
	<< packing.back().m_packer->numberOfBits() 
	<< endl;


   //do non-packed chars
   const char kNonPackCharValues[] = { 1, 
				       45,
				       CHAR_MAX,
				       CHAR_MIN,
				       0 };
   fill_pack_list( packing,
		   kNonPackCharValues,
		   ARRAY_END_ITR(kNonPackCharValues),
		   intNoPackStuff( kNonPackCharValues[0]), 
		   4 );

   cout << "number of bits " 
	<< packing.back().m_packer->numberOfBits() 
	<< endl;


   //do container size 
   const UInt32 kContainerSizeValues[] = { 0, 
					   1,
					   1000,
					   10000,
					   100000 };
   fill_pack_list( packing,
		   kContainerSizeValues,
		   ARRAY_END_ITR(kContainerSizeValues),
		   containerSizePackStuff( kContainerSizeValues[0]), 
		   4 );

   cout << "number of bits " 
	<< packing.back().m_packer->numberOfBits() 
	<< endl;


   //Now compress this info into our buffer

   unsigned char startBit = 0;
   UInt32 startWord = 0;
   UInt32 overflowWord = 0;

   PackingList::iterator itEnd = packing.end();
   PackingList::iterator itPacking = packing.begin();
   for( ; itPacking != itEnd; ++itPacking ) {

      try_to_pack_value( (const unsigned int *) 0,
			 *itPacking,
			 startWord,
			 overflowWord,
			 startBit );

      try_to_pack_value( (const int *) 0,
			 *itPacking,
			 startWord,
			 overflowWord,
			 startBit );

      try_to_pack_value( (const short *) 0,
			 *itPacking,
			 startWord,
			 overflowWord,
			 startBit );

       try_to_pack_value( (const char *) 0,
			 *itPacking,
			 startWord,
			 overflowWord,
			 startBit );

     try_to_pack_value( (const float *) 0,
			 *itPacking,
			 startWord,
			 overflowWord,
			 startBit );

      try_to_pack_value( (const double *) 0,
			 *itPacking,
			 startWord,
			 overflowWord,
			 startBit );

      if( startBit >= 32 ) {
	 startBit -= 32;
	 cout << "storing " << hex << startWord << dec << endl;
	 buffer.push_back( startWord );
	 startWord = overflowWord;
	 overflowWord = 0;
      }

   }
   if( startBit != 0) {
      cout << "storing " << hex << startWord << dec << endl;
      buffer.push_back( startWord );
   }
   cout <<"buffer size " << buffer.size() << endl;


   //Now unpack and compare to original value
   vector<UInt32>::iterator itBuffer = buffer.begin();
   startBit = 0;

   for( itPacking = packing.begin();
	itPacking != itEnd;
	++itPacking ) {
      check_stored_value( (const unsigned int *) 0,
			  *itPacking,
			  itBuffer,
			  startBit );

      check_stored_value( (const int *) 0,
			  *itPacking,
			  itBuffer,
			  startBit );

      check_stored_value( (const short *) 0,
			  *itPacking,
			  itBuffer,
			  startBit );

      check_stored_value( (const char *) 0,
			  *itPacking,
			  itBuffer,
			  startBit );

      check_stored_value( (const float *) 0,
			  *itPacking,
			  itBuffer,
			  startBit );

      check_stored_value( (const double *) 0,
			  *itPacking,
			  itBuffer,
			  startBit );

      //check to see if we need to start reading from the next word
      if( startBit >= 32 ) {
	 startBit -= 32;
	 ++itBuffer;
      }
   }
   return 0;
}

typedef  PackStuff _vector_contents_;
#include "STLUtility/instantiate_vector.h"
